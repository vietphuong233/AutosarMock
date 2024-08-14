/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Seat_Motor_Control_SWC.h"
#include "Rte_.h"


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

        if (MOVE_FORWARD_COMMAND == command)
        {

        }
        else if (MOVE_BACKWARD_COMMAND == command)
        {

        }
        else if (FOLD_COMMAND == command)
        {

        }
        else if (UNFOLD_COMMAND == command)
        {

        }
        else
        {
            /* MISRA */
        }
    }

    /* Simulate Watchdog checkpoint */
    WdgM_CheckpointReached(se_id, cp_id);
}

/* End of Seat_Motor_Control.c */
