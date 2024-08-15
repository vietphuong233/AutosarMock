#ifndef RTE_ELECTRICSEATCONTROL_H
#define RTE_ELECTRICSEATCONTROL_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_ElectricSeatControl_Type.h"

/*----------------------------------------------------------------------------*/
/* RTE APIs Prototype Declaration                                             */
/*----------------------------------------------------------------------------*/
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_RP_PositionData_ReceivePosition( P2VAR(AUTOSAR_uint8, AUTOMATIC, RTE_APPL_DATA) data );
#define Rte_Read_RP_PositionData_ReceivePosition    Rte_Read_ReceivePosition

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Write_PP_PositionCommand_SendCommand( VAR(AUTOSAR_uint8, AUTOMATIC) command );
#define Rte_Write_PP_PositionCommand_SendCommand    Rte_Write_SendCommand

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Read_RP_Parameter_ReceiveCalibParam( P2VAR(AUTOSAR_uint8, AUTOMATIC, RTE_APPL_DATA) data );
#define Rte_Read_RP_Parameter_ReceiveCalibParam     Rte_Read_ReceiveCalibParam

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_ReadBlock( VAR(NvM_BlockIdType, AUTOMATIC) BlockId, P2(void, AUTOMATIC) NvM_DstPtr );
#define Rte_Call_RP_MemorySeat_NvM_ReadBlock        Rte_Call_NvM_ReadBlock

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_WriteBlock( VAR(NvM_BlockIdType, AUTOMATIC) BlockId, P2(void, AUTOMATIC) NvM_SrcPtr );
#define Rte_Call_RP_MemorySeat_NvM_WriteBlock        Rte_Call_NvM_WriteBlock

/*----------------------------------------------------------------------------*/
/* Runnables Prototype Declaration                                            */
/*----------------------------------------------------------------------------*/
extern FUNC(void, RTE_CODE) Rte_ProcessCommand_10ms( VAR(void, AUTOMATIC) );

#endif /* RTE_ELECTRICSEATCONTROL_H */

/* End of Rte_ElectricSeatControl.h */
