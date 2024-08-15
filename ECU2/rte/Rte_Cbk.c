#include "Os.h"
#include "Rte_Cbk.h"


VAR(AUTOSAR_uint8, AUTOMATIC) Rte_CommandSignal;
extern FUNC(Std_ReturnType, Com_CODE) Com_ReceiveSignal( VAR(Com_SignalIdType, AUTOMATIC) SignalId, P2VAR(void, AUTOMATIC, RTE_APPL_DATA) SignalDataPtr );
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_COMCbk_CommandSignal                                     */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Receive command for Motor Control SW                         */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE_EcucPartition_0) Rte_COMCbk_CommandSignal( void )
{
    if (Rte_InitState == RTE_STATE_INIT)
    {
        (void)Com_ReceiveSignal(ComConf_ComSignal_CommandSignal, &Rte_CommanSignal);
    }	
}