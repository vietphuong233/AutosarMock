#include "Os.h"
#include "Rte_MotorControl.h"

extern FUNC(void, IoHwAb_CODE) IoHwAb_SeatMoveForward( VAR(void, AUTOMATIC));
/******************************************************************************/
/* Name        : Rte_Call_RP_MotorControl_IoHwAb_SeatMoveForward              */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Call IoHwAb to move seat forward                             */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MotorControl_IoHwAb_SeatMoveForward( VAR(void, AUTOMATIC) ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_SeatMoveForward();
    return ret_val;
}


extern FUNC(void, IoHwAb_CODE) IoHwAb_SeatMoveBack( VAR(void, AUTOMATIC));
/******************************************************************************/
/* Name        : Rte_Call_RP_MotorControl_IoHwAb_SeatMoveBack                 */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Call IoHwAb to move seat back                                */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MotorControl_IoHwAb_SeatMoveBack( VAR(void, AUTOMATIC) ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_SeatMoveBack();
    return ret_val;
}


extern FUNC(void, IoHwAb_CODE) IoHwAb_BackSeatFold( VAR(void, AUTOMATIC));
/******************************************************************************/
/* Name        : Rte_Call_RP_MotorControl_IoHwAb_BackSeatFold                 */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Call IoHwAb to fold backseat                                 */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MotorControl_IoHwAb_BackSeatFold( VAR(void, AUTOMATIC) ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_BackSeatFold();
    return ret_val;
}

extern FUNC(void, IoHwAb_CODE) IoHwAb_BackSeatUnFold( VAR(void, AUTOMATIC));
/******************************************************************************/
/* Name        : Rte_Call_RP_MotorControl_IoHwAb_BackSeatUnFold               */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Call IoHwAb to unfold backseat                               */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MotorControl_IoHwAb_BackSeatUnfold( VAR(void, AUTOMATIC) ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_BackSeatUnfold();
    return ret_val;
}


VAR(AUTOSAR_uint8, AUTOMATIC) Rte_Read_RP_PositionCommand_Command_value;
VAR(Std_ReturnType, AUTOMATIC) Rte_Read_RP_PositionCommand_Command_status = RTE_E_NEVER_RECEIVED;
/******************************************************************************/
/* Name        : Rte_Read_RP_PositionCommand_ReceiveCommand                   */
/* Param       : P2VAR: Pointer to memory location which save command         */
/* Return      :                                                              */
/* Contents    : Receive Command from Electric Seat Control SWC               */
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
/* Name        : Rte_HandlePositionCommand_10ms                               */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Runnable Handle Position Command                             */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE) Rte_HandlePositionCommand_10ms( VAR(void, AUTOMATIC) ) {

    HandlePositionCommand_10ms();

}

/* End of Rte_MotorControl.c */

