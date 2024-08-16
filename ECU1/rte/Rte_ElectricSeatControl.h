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

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_ReadCurrentPosition( P2(AUTOSAR_uint16, AUTOMATIC) NvM_DstPtr );
#define Rte_Call_RP_MemorySeat_NvM_ReadCurrentPosition  Rte_Call_NvM_ReadCurrentPosition

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_ReadMode( P2(AUTOSAR_uint32, AUTOMATIC) NvM_DstPtr );
#define Rte_Call_RP_MemorySeat_NvM_ReadMode             Rte_Call_NvM_ReadMode

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_WriteCurruntPosition( P2(AUTOSAR_uint16, AUTOMATIC) NvM_SrcPtr );
#define Rte_Call_RP_MemorySeat_NvM_WriteCurruntPosition Rte_Call_NvM_WriteCurruntPosition

FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_WriteMode( P2(AUTOSAR_uint32, AUTOMATIC) NvM_SrcPtr );
#define Rte_Call_RP_MemorySeat_NvM_WriteMode            Rte_Call_NvM_WriteMode

/*----------------------------------------------------------------------------*/
/* Runnables Prototype Declaration                                            */
/*----------------------------------------------------------------------------*/
extern FUNC(void, RTE_CODE) Rte_ProcessCommand_10ms( VAR(void, AUTOMATIC) );

#endif /* RTE_ELECTRICSEATCONTROL_H */

/* End of Rte_ElectricSeatControl.h */
