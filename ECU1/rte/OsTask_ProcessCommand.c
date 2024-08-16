/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_ElectricSeatControl.h"
#include "Rte_SeatAdjuster.h"
#include "Std_Type.h"
#include "Com.h"
#include "Os.h"

/*----------------------------------------------------------------------------*/
/* task impliment                                                             */
/*----------------------------------------------------------------------------*/

extern FUNC(void, RTE_CODE) Rte_InitElectricSeatControl( VAR(void, AUTOMATIC) )
extern FUNC(void, RTE_CODE) Rte_ProcessCommand_10ms( VAR(void, AUTOMATIC) );
extern FUNC(void, RTE_CODE) Rte_HandleSeatAdjuster_10ms( VAR(void, AUTOMATIC) );
/******************************************************************************/
/* Name        : OsTask_ProcessCommand                                        */
/* Param       :                                                              */
/* Return      :                                                              */
/* Note        :                                                              */
/******************************************************************************/
TASK (OsTask_ProcessCommand)
{
    VAR(EventMaskType, AUTOMATIC) ev;

    Rte_InitElectricSeatControl();

    while ( 1 )
    {
        (void) WaitEvent  (Periodic_SignalHandle_10ms | Periodic_ProcessCommand_10ms);
        (void) GetEvent   (OsTask_ProcessCommand, &ev);
        (void) ClearEvent (ev & (Periodic_SignalHandle_10ms | Periodic_ProcessCommand_10ms));

        if ((ev & Periodic_SignalHandle_10ms) != (EventMaskType) 0)
        {
            Rte_HandleSeatAdjuster_10ms();
        }

        if ((ev & Periodic_ProcessCommand_10ms) != (EventMaskType) 0)
        {
            Rte_ProcessCommand_10ms();
        }
    }
}

/* End of OsTask_ProcessCommand.c */
