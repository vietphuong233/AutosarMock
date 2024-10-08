#include "Os.h"
#include "Rte_Cbk.h"


extern VAR(AUTOSAR_uint8, AUTOMATIC) Rte_Read_RP_PositionCommand_Command_value;
/******************************************************************************/
/* Name        : Rte_COMCbk_CommandSignal                                     */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Receive command for Motor Control SW                         */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE) Rte_COMCbk_CommandSignal( void )
{

        (void)Com_ReceiveSignal(ComConf_ComSignal_CommandSignal, &Rte_Read_RP_PositionCommand_Command_value);

}

/* End of Rte_Cbk.c */
