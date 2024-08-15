/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_MotorControl.h"

/*----------------------------------------------------------------------------*/
/* runnables                                                                  */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* Name        : HandlePositionCommand_10ms                                   */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Read command signal then call corresponding hardware API     */
/* Author      :                                                              */
/* Note        : This runnable read command signal sent from Adjuster ECU     */
/*               then call the corressponding Motor Hardware Abstraction API  */
/******************************************************************************/
FUNC(void, MotorControl_CODE) HandlePositionCommand_10ms( VAR(void, AUTOMATIC) )
{
    command_signal command = 0;

    Rte_Read_RP_PositionCommand_Command(&command);

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

    /* Simulate Watchdog checkpoint */
    Rte_Call_WdgMCheckpointReached(se_id, cp_id);
}

/* End of Seat_Motor_Control.c */
