/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Seat_Motor_Control_SWC.h"
#include "Rte_MotorControl.h"

/*----------------------------------------------------------------------------*/
/* private functions                                                          */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* runnables                                                                  */
/*----------------------------------------------------------------------------*/

FUNC(void, MotorControl_CODE) HandlePositionCommand_10ms( VAR(void, AUTOMATIC) )
{
    command_signal command = 0;

	if(1 == abcxyz)
    {
        Rte_Read_RP_PositionCommand_Command(&command);
        abcxyz = 0;

        switch (command)
        {
        case MOVE_FORWARD_COMMAND:
            Rte_Call_RP_MotorControl_IoHwAb_SeatMoveForward();
            break;
        case MOVE_BACKWARD_COMMAND:
            Rte_Call_RP_MotorControl_IoHwAbSeatMoveBack();
            break;

        case FOLD_COMMAND:
            IoHwAb_BackSeatFold();
            break;

        case UNFOLD_COMMAND:
            IoHwAb_BackSeatUnFold();
            break;

        default:
            /* Do nothing */
            break;
        }
    }

    /* Simulate Watchdog checkpoint */
    WdgM_CheckpointReached(se_id, cp_id);
}

/* End of Seat_Motor_Control.c */
