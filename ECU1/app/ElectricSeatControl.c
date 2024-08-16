/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_ElectricSeatControl.h"

/*----------------------------------------------------------------------------*/
/* variables                                                                  */
/*----------------------------------------------------------------------------*/
static seat_control_t  g_CONTROL;         /* Controller for runnable */

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
static command_type_t GetCommandType( const command_signal command )
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
static position_status_t UpdatePosition( const command_signal command )
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
static void StartAdjusting( const seat_position_t new_positon )
{
    g_CONTROL.SEAT_MOVE     = new_positon.SEAT_POS - g_CONTROL.POSITION.SEAT_POS;
    g_CONTROL.BACKREST_MOVE = new_positon.BACKREST_POS - g_CONTROL.POSITION.BACKREST_POS;
    g_CONTROL.STATE         = ADJUSTING;
}

/******************************************************************************/
/* Name        : GetSettingMode                                               */
/* Param       : command      : command signal received                       */
/* Return      : setting mode : setting from button 1 or 2                    */
/* Contents    : Check command for corresponding NvMBlock ID                  */
/* Author      :                                                              */
/* Note        : This function read command signal to return the setting mode:*/
/*                   if command read button setting 1 -> SETTING_MODE1        */
/*                   if command read button setting 2 -> SETTING_MODE2        */
/******************************************************************************/
static setting_mode_t GetSettingMode( const command_signal command )
{
    setting_mode_t return_value = NO_SETTING;

    switch (command)
    {
        case MODE1_SIGNAL:
            return_value = SETTING_MODE1;
            break;
        case MODE2_SIGNAL:
            return_value = SETTING_MODE2;
            break;
        default:
            /* Do nothing */
            break;
    }

    return return_value;
}

/******************************************************************************/
/* Name        : GetSettingMode                                               */
/* Param       : mem_data : data read from Nv Memory                          */
/* Param       : mode     : setting mode read from setting button             */
/* Return      : position : position read from memory data                    */
/* Contents    : Extract seat position from memory data read in Nv Memory     */
/* Author      :                                                              */
/* Note        : This function extract seat position from memory data in      */
/*               Nv Memory, by decide from setting mode:                      */
/*                   if setting mode 1 -> read position from meme data 1      */
/*                   if setting mode 2 -> read position from meme data 2      */
/******************************************************************************/
static seat_position_t GetPosition(const setting_data_t mem_data,
                                   const setting_mode_t mode)
{
    seat_position_t return_value = {0, 0};

    switch (mode)
    {
        case SETTING_MODE1:
            return_value.SEAT_POS     = mem_data.MODE1_DATA.SEAT_POS;
            return_value.BACKREST_POS = mem_data.MODE1_DATA.BACKREST_POS;
            break;

        case SETTING_MODE2:
            return_value.SEAT_POS     = mem_data.MODE2_DATA.SEAT_POS;
            return_value.BACKREST_POS = mem_data.MODE2_DATA.BACKREST_POS;
            break;

        default
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
/* Note        : This Runnable initiate read data to initiate global var:     */
/*                   g_MAX_POSITION    : read from calibration paramter       */
/*                   g_CONTROL.POSITION: read from NvM                        */
/******************************************************************************/
FUNC(void, SeatAdjuster_CODE) InitElectricSeatControl( VAR(void, AUTOMATIC) )
{
    seat_position_t init_position;

    /* Read calibration parameter for max position allowed */
    Rte_Read_RP_Parameter_ReceiveCalibParam(&g_MAX_POSITION);
    /* Read previous position saved in NvM */
    Rte_Call_RP_MemorySeat_NvM_ReadCurrentPosition(&init_position);
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
    static command_signal  command;
    static command_type_t  command_type;
    static setting_mode_t  mode = GetSettingMode(command); /* Check mode */
    static seat_position_t setting_position;    /* Position data holder */
    static setting_data_t  mem_data;            /* Memory data holder */

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
                /* Read NvM block to mem_data */
                Rte_Call_RP_MemorySeat_NvM_ReadMode( (uint32*)(&mem_data) );
                /* Copy data to setting_position */
                setting_position = GetPosition(mem_data, mode);
                /* Check if setting and current position is the same */
                if (setting_position.SEAT_POS     != g_CONTROL.POSITION.SEAT_POS ||
                    setting_position.BACKREST_POS != g_CONTROL.POSITION.BACKREST_POS)
                {
                    StartAdjusting(setting_position);
                }
                break;

            case MEMORY_WRITE_COMMAND:
                /* Read NvM block to mem_data */
                Rte_Call_RP_MemorySeat_NvM_ReadMode( (uint32*)(&mem_data) );
                /* Update new position to mem_data */
                switch (mode)
                {
                    case SETTING_MODE1:
                        mem_data.MODE1_DATA.SEAT_POS     = g_CONTROL.POSITION.SEAT_POS;
                        mem_data.MODE1_DATA.BACKREST_POS = g_CONTROL.POSITION.BACKREST_POS;
                        break;

                    case SETTING_MODE2:
                        mem_data.MODE2_DATA.SEAT_POS     = g_CONTROL.POSITION.SEAT_POS;
                        mem_data.MODE2_DATA.BACKREST_POS = g_CONTROL.POSITION.BACKREST_POS;
                        break;

                    default:
                        /* Do nothing */
                        break;
                }
                /* Write new data to NvM  */
                Rte_Call_RP_MemorySeat_NvM_WriteMode( (uint32*)(&mem_data) );
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

    /* Save current position to Nv Memory */
    Rte_Call_RP_MemorySeat_NvM_WriteCurruntPosition( (uint16*)(&g_CONTROL.POSITION) );

    /* Simulate Watchdog checkpoint */
    Rte_Call_WdgMCheckpointReached(SE1_ID, CP_ID_1);
}

/* End of Seat_Adjuster.c */
