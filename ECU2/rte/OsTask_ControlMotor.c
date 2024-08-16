/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_MotorControl.h"
#include "Std_Type.h"
#include "Com.h"
#include "Os.h"

/*----------------------------------------------------------------------------*/
/* task impliment                                                             */
/*----------------------------------------------------------------------------*/

extern FUNC(void, RTE_CODE_EcucPartition_0) Rte_HandlePositionCommand_10ms( VAR(void, AUTOMATIC) );
/******************************************************************************/
/* Name        : OsTask_ControlMotor                                          */
/* Param       :                                                              */
/* Return      :                                                              */
/* Note        :                                                              */
/******************************************************************************/
TASK (OsTask_ControlMotor)
{
    VAR(EventMaskType, AUTOMATIC) ev;

    while ( 1 )
    {
        (void) WaitEvent  (Periodic_ControlMotor_10ms);
        (void) GetEvent   (OsTask_ControlMotor, &ev);
        (void) ClearEvent (ev & (Periodic_ControlMotor_10ms));

        if ((ev & Periodic_ControlMotor_10ms) != (EventMaskType) 0)
        {
            Rte_HandlePositionCommand_10ms();
        }
    }
}

/* End of OsTask_ProcessCommand.c */
