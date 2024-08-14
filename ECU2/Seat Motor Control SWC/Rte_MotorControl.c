#include "Os.h"
#include "Rte_MotorControl.h"

extern FUNC(void, IoHwAb_CODE) IoHwAb_SeatMoveForward( VAR(void, AUTOMATIC));
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_RP_MotorControl_IoHwAb_SeatMoveForward              */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MotorControl_IoHwAb_SeatMoveForward( VAR(void, AUTOMATIC) ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_SeatMoveForward();
    return ret_val;
}


extern FUNC(void, IoHwAb_CODE) IoHwAb_SeatMoveBack( VAR(void, AUTOMATIC));
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_RP_MotorControl_IoHwAb_SeatMoveBack                 */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MotorControl_IoHwAbSeatMoveBack( VAR(void, AUTOMATIC) ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_SeatMoveBack();
    return ret_val;
}


extern FUNC(void, IoHwAb_CODE) IoHwAb_BackSeatFold( VAR(void, AUTOMATIC));
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_RP_MotorControl_IoHwAb_BackSeatFold                 */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MotorControl_IoHwAb_BackSeatFold( VAR(void, AUTOMATIC) ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_BackSeatFold();
    return ret_val;
}

extern FUNC(void, IoHwAb_CODE) IoHwAb_BackSeatUnFold( VAR(void, AUTOMATIC));
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_RP_MotorControl_IoHwAb_BackSeatFold                 */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MotorControl_IoHwAb_BackSeatUnfold( VAR(void, AUTOMATIC) ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_BackSeatUnfold();
    return ret_val;
}


VAR(AUTOSAR_uint8, AUTOMATIC) Rte_Read_RP_PositionCommand_Command_value;
VAR(Std_ReturnType, AUTOMATIC) Rte_Read_RP_PositionCommand_Command_status = RTE_E_NEVER_RECEIVED;
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Read_RP_PositionCommand_ReceiveCommand                   */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Read_RP_PositionCommand_ReceiveCommand( P2VAR(AUTOSAR_uint8, AUTOMATIC, RTE_APPL_DATA) command ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val;

    RTE_Q_LOCK();
    *command = Rte_Read_RP_PositionCommand_Command_value;
    ret_val = Rte_Read_RP_PositionCommand_Command_status;
    RTE_Q_UNLOCK();

    return ret_val;
}


extern FUNC(void, MotorControl_CODE) HandlePositionCommand_10ms( VAR(void, AUTOMATIC) );
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_HandlePositionCommand_10ms                               */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Ecu Configuration(Ecuc)                                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE_EcucPartition_0) Rte_HandlePositionCommand_10ms( VAR(void, AUTOMATIC) ) {

    HandlePositionCommand_10ms();

}




// Motor Control - COMCbk
VAR(AUTOSAR_uint8, AUTOMATIC) Rte_CommandSignal[3];

FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_COMCbk_CommandSignal( void )
{
    if (Rte_InitState == RTE_STATE_INIT)
    {
        (void)GetSpinlock(Rte_Spinlock_CommandSignal);
        (void)Com_ReceiveSignalGroup(ComConf_ComSignalGroup_CommandSignal);
        (void)Com_ReceiveSignal(ComConf_ComSignalGroup_SeatSignal, &(*(&ComConf_ComSignalGroup_CommandSignal)).SeatSignal )
        // (void)Rte_QMApplication_Core2_RxUpdate_NetASIL_LOT_ADataRawSafe_LOT_ADataRawSafe_Sender = 1;
        (void)Rte_Update_Command = 1;
        (void)ReleaseSpinlock(Rte_Spinlock_CommandSignal);
    }	
	/* return true for accept this com Pdu */
	return TRUE;
}