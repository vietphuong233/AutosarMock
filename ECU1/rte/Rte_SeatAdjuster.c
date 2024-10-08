#include "Os.h"
#include "Rte_SeatAdjuster.h"


extern FUNC(void, IoHwAb_CODE) IoHwAb_DioReadChannelGroups( P2VAR(Dio_PortLevelType, AUTOMATIC, RTE_APPL_DATA) state );
/******************************************************************************/
/* Name        : Rte_Call_RP_AdjustData_DioReadChannelGroup                   */
/* Param       : P2CONST: Pointer to ChannelGroup                             */
/*               P2VAR: Pointer to memory location which save button state    */
/* Return      :                                                              */
/* Contents    : Read button state from IoHwAb                                */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_AdjustData_IoHwAb_DioReadChannelGroup( P2VAR(Dio_PortLevelType, AUTOMATIC, RTE_APPL_DATA) state ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    IoHwAb_DioReadChannelGroups( state );
    return ret_val;
}


VAR(AUTOSAR_uint8, AUTOMATIC) adjust_data;
/******************************************************************************/
/* Name        : Rte_Write_PP_PositionData_SendPosition                       */
/* Param       : VAR: Position data which send to Electric Seat Control SWC   */
/* Return      :                                                              */
/* Contents    : send position data to Electric Seat Control SWC              */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_PP_PositionData_SendPosition( VAR(AUTOSAR_uint8, AUTOMATIC) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    adjust_data = data;
    return ret_val;
}


extern FUNC(void, SeatAdjuster_CODE) HandleSeatAdjuster_10ms( VAR(void, AUTOMATIC) );
/******************************************************************************/
/* Name        : Rte_HandleSeatAdjuster_10ms                                  */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Runnable Handle Seat Adjuster                                */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE) Rte_HandleSeatAdjuster_10ms( VAR(void, AUTOMATIC) ) {

    HandleSeatAdjuster_10ms();

}
