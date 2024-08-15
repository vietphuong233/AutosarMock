/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_ElectricSeatControl.h"
#include "Rte_SeatAdjuster.h"

/*----------------------------------------------------------------------------*/
/* variables                                                                  */
/*----------------------------------------------------------------------------*/
static seat_control_t g_CONTROL;          /* Controller for runnable */

static seat_position_t g_MAX_POSITION;    /* Max position allowed */

/*----------------------------------------------------------------------------*/
/* private functions                                                          */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* Name        : GetCommandType                                               */
/* Param       : command signal : command signal provided                     */
/* Return      : command type   : type of the command: move, mem read/write   */
/* Contents    : Read command signal to determine command type                */
/* Author      :                                                              */
/* Note        : This function read command signal to check the command type  */
/*               base on the bit field. If signal is empty (0x00), the type   */
/*               is still move command, but its move nothing                  */
/******************************************************************************/
static command_type_t GetCommandType( command_signal command )
{
    command_type_t return_value = MOVE_COMMAND;

    if (0 != CHECK_MOVE_COMMAND(command))
    {
        return_value = MOVE_COMMAND;
    }
    else if (0 != CHECK_MEMORY_COMMAND(command))
    {
        if (0x01 == CHECK_MEMORY_COMMAND(command))
        {
            return_value = MEMORY_WRITE_COMMAND;
        }
        else /* CHECK_MEMORY_COMMAND(command) > 0x01 */
        {
            return_value = MEMORY_READ_COMMAND;
        }
    }
    else
    {
        /* Avoid MISRA */
    }

    return return_value;
}

/******************************************************************************/
/* Name        : UpdatePosition                                               */
/* Param       : command     : move command provided                          */
/* Return      : move status : OK if movable, NOT_OK if not                   */
/* Contents    : Update the control position and return move status           */
/* Author      :                                                              */
/* Note        : This function read the move command then check g_MAX_POSITION*/
/*               for possibility to move, then update g_CONTROL.POSITION and  */
/*               return movable status                                        */
/******************************************************************************/
static position_status_t UpdatePosition(command_signal command)
{
    position_status_t return_value = MOVE_OK;

    switch (command)
    {
        case MOVE_FORWARD_SIGNAL:
            if ( g_CONTROL.POSITION.SEAT_POS == g_MAX_POSITION.SEAT_POS )
            {
                /* Cannot move further */
                return_value = MOVE_NOT_OK;
            }
            else
            {
              g_CONTROL.POSITION.SEAT_POS++;
            }
            break;
        case MOVE_BACKWARD_SIGNAL:
            g_CONTROL.POSITION.SEAT_POS--;
            break;
        case FOLD_SIGNAL:
            if ( g_CONTROL.POSITION.BACKREST_POS == g_MAX_POSITION.BACKREST_POS )
            {
                /* Cannot move further */
                return_value = MOVE_NOT_OK;
            }
            else
            {
                g_CONTROL.POSITION.BACKREST_POS++;
            }
            break;
        case UNFOLD_SIGNAL:
            g_CONTROL.POSITION.BACKREST_POS--;
            break;
        default:
            /* Empty signal, do nothing */
            break;
    }

    return return_value;
}

/******************************************************************************/
/* Name        : StartAdjusting                                               */
/* Param       : new_position : new position provided for adjustment          */
/* Return      :                                                              */
/* Contents    : Initiate Adjusting sequence                                  */
/* Author      :                                                              */
/* Note        : This function read the new position to update the move needed*/
/*               g_CONTROL.SEAT_MOVE and g_CONTROL.BACKREST_MOVE, then start  */
/*               the adjusting sequence by set g_CONTROL.STATE to ADJUSTING   */
/******************************************************************************/
static void StartAdjusting(seat_position_t new_positon)
{
    g_CONTROL.SEAT_MOVE     = new_positon.SEAT_POS - g_CONTROL.POSITION.SEAT_POS;
    g_CONTROL.BACKREST_MOVE = new_positon.BACKREST_POS - g_CONTROL.POSITION.BACKREST_POS;
    g_CONTROL.STATE         = ADJUSTING;
}

/******************************************************************************/
/* Name        : GetMemoryId                                                  */
/* Param       : command    : command signal received                         */
/* Return      : NvMBlockID : simulated NvMBlockID                            */
/* Contents    : Check command for corresponding NvMBlock ID                  */
/* Author      :                                                              */
/* Note        : This function read command signal to return the block ID:    */
/*                   if command read button setting 1 -> BLOCKID1             */
/*                   if command read button setting 2 -> BLOCKID2             */
/******************************************************************************/
static uint32_t GetMemoryId(command_signal command)
{
    uint32_t return_value = 0;

    switch (command)
    {
        case MODE1_SIGNAL:
            return_value = BLOCKID1;
            break;
        case MODE2_SIGNAL:
            return_value = BLOCKID2;
            break;
        default:
            /* Do nothing */
            break;
    }

    return return_value;
}

/*----------------------------------------------------------------------------*/
/* runnables                                                                  */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* Name        : InitElectricSeatControl                                      */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Initiate Electric Seat Control SWC variables                 */
/* Author      :                                                              */
/* Note        : This Runnable initiate global variables g_...                */
/******************************************************************************/
FUNC(void, SeatAdjuster_CODE) InitElectricSeatControl( VAR(void, AUTOMATIC) )
{
    seat_position_t init_position;

    Rte_Read_RP_Parameter_ReceiveCalibParam(&g_MAX_POSITION);
    Rte_Call_RP_MemorySeat_NvM_ReadBlock(BLOCKIDOLD, &init_position);

    g_CONTROL.POSITION.SEAT_POS     = init_position.SEAT_POS;
    g_CONTROL.POSITION.BACKREST_POS = init_position.BACKREST_POS;
    g_CONTROL.SEAT_MOVE             = 0;
    g_CONTROL.BACKREST_MOVE         = 0;
    g_CONTROL.STATE                 = IDLING;
}

/******************************************************************************/
/* Name        : ProcessCommand_10ms                                          */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Process command signal received from Seat Adjuster SWC       */
/* Author      :                                                              */
/* Note        : This function read command signal from Seat Adjuster SWC,    */
/*               then process depend on the controll state g_CONTROL.STATE:   */
/*                   if control is idling, process 3 types of command:        */
/*                       move     : if moveable (MOVE_OK) send out command    */
/*                       mem read : read setting from NvM then start adjusting*/
/*                       mem write: save setting through NvM                  */
/*                   if control is adjusting, check the movement needed from  */
/*                   g_CONTROL.SEAT_MOVE and g_CONTROL.BACKREST_MOVE then     */
/*                   send out the corresponding command                       */
/******************************************************************************/
FUNC(void, SeatAdjuster_CODE) ProcessCommand_10ms( VAR(void, AUTOMATIC) )
{
    static command_signal command;
    static command_type_t command_type;

    if (IDLING == g_CONTROL.STATE)
    {
        Rte_Read_RP_PositionData_ReceivePosition(&command);
        command_type = GetCommandType(command);

        switch (command_type)
        {
            case MOVE_COMMAND:
                if (UpdatePosition(command) == MOVE_OK) /* Check & update move*/
                {
                    Rte_Write_PP_PositionCommand_SendCommand(command);
                }
                else
                {
                    /* Cannot move further, do nothing */
                }
                break;

            case MEMORY_READ_COMMAND:
                seat_position_t setting_position;
                uint32_t blockid = GetMemoryId(command);
                Rte_Call_RP_MemorySeat_NvM_ReadBlock(blockid, &setting_position);
                /* Check if setting and current position is the same */
                if (setting_position.SEAT_POS     != g_CONTROL.POSITION.SEAT_POS ||
                    setting_position.BACKREST_POS != g_CONTROL.POSITION.BACKREST_POS)
                {
                    StartAdjusting(setting_position);
                }
                break;

            case MEMORY_WRITE_COMMAND:
                uint32_t blockid = GetMemoryId(command);
                Rte_Call_RP_MemorySeat_NvM_WriteBlock(blockid, g_CONTROL.POSITION);
                break;

            default:
                /* Do nothing */
                break;
        }
    }
    else /* ADJUSTING == g_CONTROL.STATE */
    {
        /* Check any seat move left */
        if (0 != g_CONTROL.SEAT_MOVE)
        {
            if (g_CONTROL.SEAT_MOVE < 0)
            {
                Rte_Write_PP_PositionCommand_SendCommand(MOVE_FORWARD_SIGNAL);
                g_CONTROL.SEAT_MOVE++;
            }
            else /* g_CONTROL.SEATMOVE > 0 */
            {
                Rte_Write_PP_PositionCommand_SendCommand(MOVE_BACKWARD_SIGNAL);
                g_CONTROL.SEAT_MOVE--;
            }
        }
        /* Check any backrest move left */
        else if (0 != g_CONTROL.BACKREST_MOVE)
        {
            if (g_CONTROL.BACKREST_MOVE < 0)
            {
                Rte_Write_PP_PositionCommand_SendCommand(UNFOLD_SIGNAL);
                g_CONTROL.BACKREST_MOVE++;
            }
            else /* g_CONTROL.BACKREST_MOVE > 0 */
            {
                Rte_Write_PP_PositionCommand_SendCommand(FOLD_SIGNAL);
                g_CONTROL.BACKREST_MOVE--;
            }
        }
        else /* 0 = g_CONTROL.SEATMOVE = g_CONTROL.BACKREST_MOVE  */
        {
            /* No more movement needed, adjusting completed */
            g_CONTROL.STATE = IDLING;
        }
    }

    /* Simulate Watchdog checkpoint */
    Rte_Call_WdgMCheckpointReached(se_id, cp_id);
}

/* End of Seat_Adjuster.c */
