#include "Os.h"
#include "Rte_SeatAdjuster.h"


extern FUNC(void, IoHwAb_CODE) IoHwAb_DioReadChannelGroups( P2VAR(Dio_PortLevelType, AUTOMATIC, RTE_APPL_DATA) state );
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_RP_AdjustData_DioReadChannelGroup                   */
/* Param       : P2CONST: Pointer to ChannelGroup                             */
/*               P2VAR: Pointer to memory location which save button state    */
/* Return      :                                                              */
/* Contents    : Read button state from IoHwAb                                */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_AdjustData_IoHwAb_DioReadChannelGroup( P2VAR(Dio_PortLevelType, AUTOMATIC, RTE_APPL_DATA) state ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_DioReadChannelGroups( state );
    return ret_val;
}


VAR(AUTOSAR_uint8, AUTOMATIC) adjust_data;
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Write_PP_PositionData_SendPosition                       */
/* Param       : VAR: Position data which send to Electric Seat Control SWC   */
/* Return      :                                                              */
/* Contents    : send position data to Electric Seat Control SWC              */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_PP_PositionData_SendPosition( VAR(AUTOSAR_uint8, AUTOMATIC) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    adjust_data = data;
    return ret_val;
}


extern FUNC(void, SeatAdjuster_CODE) HandleSeatAdjuster_10ms( VAR(void, AUTOMATIC) );
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_HandleSeatAdjuster_10ms                                  */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Runnable Handle Seat Adjuster                                */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE_EcucPartition_0) Rte_HandleSeatAdjuster_10ms( VAR(void, AUTOMATIC) ) {

    HandleSeatAdjuster_10ms();

}