/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Seat_Adjuster_SWC.h"
#include "Electric_Seat_Control_SWC.h"
#include "Rte_ElectricSeatControl.h"

/*----------------------------------------------------------------------------*/
/* variables                                                                  */
/*----------------------------------------------------------------------------*/
static seat_control_t g_CONTROL;

static seat_position_t g_MAX_POSITION;

/*----------------------------------------------------------------------------*/
/* private functions                                                          */
/*----------------------------------------------------------------------------*/

command_type_t GetCommandType( command_signal command )
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

position_status_t UpdatePosition(command_signal command)
{
    position_status_t return_value = MOVE_OK;

    switch (command)
    {
        case MOVE_FORWARD_SIGNAL:
            if ( g_CONTROL.POSITION.SEAT_POS == g_MAX_POSITION.SEAT_POS )
            {
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

void StartAdjusting(seat_position_t new_positon)
{
    g_CONTROL.SEAT_MOVE     = new_positon.SEAT_POS - g_CONTROL.POSITION.SEAT_POS;
    g_CONTROL.BACKREST_MOVE = new_positon.BACKREST_POS - g_CONTROL.POSITION.BACKREST_POS;
    g_CONTROL.STATE         = ADJUSTING;
}

uint32_t GetMemoryId(command_signal command)
{
    uint32_t return_value = 0;

    switch (CHECK_MEMORY_COMMAND(command))
    {
        case 0x02:
            return_value = BLOCKID1;
            break;
        case 0x03:
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
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : ProcessCommand_10ms                                          */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Process command signal received from Seat Adjuster SWC       */
/* Author      :                                                              */
/* Note        : This function read command signal from                                                          */
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
                if (UpdatePosition(command) == MOVE_OK)
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
    WdgM_CheckpointReached(se_id, cp_id);
}

/* End of Seat_Adjuster.c */
