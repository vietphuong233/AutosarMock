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

static seat_positon_t g_CALIB_POSITION;
/*----------------------------------------------------------------------------*/
/* functions prototypes                                                       */
/*----------------------------------------------------------------------------*/
command_type_t GetCommandType( command_signal command );
void StartAdjusting(seat_positon_t new_positon);
uint32_t GetMemoryId(command_signal command)
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
        /* MISRA */
    }

    return return_value;
}

void UpdatePosition(command_signal command)
{
    switch (command)
    {
        case MOVE_FORWARD_SIGNAL:
            g_CONTROL.POSITION.SEAT_POS++;
            break;
        case MOVE_BACKWARD_SIGNAL:
            g_CONTROL.POSITION.SEAT_POS--;
            break;
        case FOLD_SIGNAL:
            g_CONTROL.POSITION.BACKREST_POS++;
            break;
        case UNFOLD_SIGNAL:
            g_CONTROL.POSITION.BACKREST_POS--;
            break;
        default:
            /* MISRA */
            break;
    }
}

void StartAdjusting(seat_positon_t new_positon)
{
    g_CONTROL.SEAT_MOVE     = new_positon.SEAT_POS - g_CONTROL.POSITION.SEAT_POS;
    g_CONTROL.BACKREST_MOVE = new_positon.BACKREST_POS - g_CONTROL.POSITION.BACKREST_POS;
    g_CONTROL.STATE         = ADJUSTING;
}

uint32_t GetMemoryId(command_signal command)
{
    uint32_t return_value = 0;
    if (0x02 == CHECK_MEMORY_COMMAND(command))
    {
        return_value = BLOCKID1;
    }
    else if (0x03 == CHECK_MEMORY_COMMAND(command))
    {
        return_value = BLOCKID2;
    }
    else
    {
        /* MISRA */
    }

    return return_value;
}

/*----------------------------------------------------------------------------*/
/* runnables                                                                  */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : InitElectricSeatControl                                      */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Initiate Electric Seat Control SWC variables                 */
/* Author      :                                                              */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, SeatAdjuster_CODE) InitElectricSeatControl( VAR(void, AUTOMATIC) )
{
    Rte_Read_RP_Parameter_ReceiveCalibParam(&g_CALIB_POSITION);
    Rte_Call_RP_MemorySeat_NvM_ReadBlock(BLOCKIDOLD, &g_CONTROL.POSITION);
}

/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : ProcessCommand_10ms                                          */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Process command signal received from Seat Adjuster SWC       */
/* Author      :                                                              */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, SeatAdjuster_CODE) ProcessCommand_10ms( VAR(void, AUTOMATIC) )
{
    static command_signal command;
    static command_type_t command_type;

    if (IDLING == g_CONTROL.STATE)
    {
        Rte_Read_RP_PositionData_ReceivePosition(&command);
        /* Get type of command to handle */
        command_type = GetCommandType(command);

        if (MOVE_COMMAND == command_type)
        {
            /* Send command to Motor */
            Rte_Write_PP_PositionCommand_SendCommand(command);
            /* Adjust Controller Position */
            UpdatePosition(command);
        }
        else if (MEMORY_READ_COMMAND == command_type)
        {
            seat_positon_t setting_position;
            uint32_t blockid = GetMemoryId(command);
            Rte_Call_RP_MemorySeat_NvM_ReadBlock(blockid, &setting_position);
            if (   setting_position.SEAT_POS     == g_CONTROL.POSITION.SEAT_POS
                && setting_position.BACKREST_POS == g_CONTROL.POSITION.BACKREST_POS )
            {
                /* No chaging in position, do nothing */
            }
            else
            {
                /* Start Adjusting Sequence */
                StartAdjusting(setting_position);
            }
        }
        else if (MEMORY_WRITE_COMMAND == command_type)
        {
            uint32_t blockid = GetMemoryId(command);
            Rte_Call_RP_MemorySeat_NvM_WriteBlock(blockid, cur_position);
        }
        else
        {
            /* MISRA */
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
