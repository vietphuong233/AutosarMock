#ifndef RTE_SEATADJUSTER_H
#define RTE_SEATADJUSTER_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_SeatAdjuster_Type.h"

/*----------------------------------------------------------------------------*/
/* RTE APIs Prototype Declaration                                             */
/*----------------------------------------------------------------------------*/
extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_AdjustData_IoHwAb_DioReadChannelGroup( P2VAR(Dio_PortLevelType, AUTOMATIC, RTE_APPL_DATA) state );
#define Rte_Call_IoHwAb_DioReadChannelGroup Rte_Call_RP_AdjustData_IoHwAb_DioReadChannelGroup

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_PP_PositionData_SendPosition( VAR(AUTOSAR_uint8, AUTOMATIC) data );
#define Rte_Write_Position  Rte_Write_PP_PositionData_Position

/*----------------------------------------------------------------------------*/
/* Runnables Prototype Declaration                                            */
/*----------------------------------------------------------------------------*/
extern FUNC(void, RTE_CODE) Rte_HandleSeatAdjuster_10ms( VAR(void, AUTOMATIC) );

#endif /* RTE_SEATADJUSTER_H */

/* End of Rte_SeatAdjuster.h */
