#ifndef RTE_SEATADJUSTMENT_H
#define RTE_SEATADJUSTMENT_H

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_AdjustData_IoHwAb_DioReadChannelGroup( P2CONST(Dio_ChannelGroupType , AUTOMATIC, RTE_APPL_DATA) id, P2VAR(Dio_PortLevelType, AUTOMATIC, RTE_APPL_DATA) state );
#define Rte_Call_IoHwAb_DioReadChannelGroup Rte_Call_RP_AdjustData_IoHwAb_DioReadChannelGroup

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_PP_PositionData_SendPosition( VAR(AUTOSAR_uint8, AUTOMATIC) data );
#define Rte_Write_Position  Rte_Write_PP_PositionData_Position

extern FUNC(void, RTE_CODE_EcucPartition_0) Rte_HandleSeatAdjuster_10ms( VAR(void, AUTOMATIC) );

#endif /* RTE_SEATADJUSTMENT_H */