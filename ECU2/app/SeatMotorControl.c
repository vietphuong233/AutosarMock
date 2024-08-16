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
            Rte_Call_RP_MotorControl_IoHwAb_SeatMoveBack();
            break;

        case FOLD_COMMAND:
            Rte_Call_RP_MotorControl_IoHwAb_BackSeatFold();
            break;

        case UNFOLD_COMMAND:
            Rte_Call_RP_MotorControl_IoHwAb_BackSeatUnfold();
            break;

        default:
            /* Do nothing */
            break;
    }

    /* Simulate Watchdog checkpoint */
    Rte_Call_WdgMCheckpointReached(SE3_ID, CP_ID_3);
}

/* End of Seat_Motor_Control.c */
