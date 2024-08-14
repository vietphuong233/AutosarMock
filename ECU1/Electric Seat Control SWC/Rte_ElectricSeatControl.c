#include "Os.h"
#include "Rte_ElectricSeatControl.h"


extern VAR(AUTOSAR_uint8, AUTOMATIC) adjust_data;
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Read_RP_PositionData_ReceivePosition                     */
/* Param       : P2VAR: Pointer to memory location which save position data   */
/* Return      :                                                              */
/* Contents    : Read position data from Seat Adjuster SWC                    */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Read_RP_PositionData_ReceivePosition( P2VAR(AUTOSAR_uint8, AUTOMATIC, RTE_APPL_DATA) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    *data = adjust_data;

    return ret_val;
}


/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Write_PP_PositionCommand_SendCommand                     */
/* Param       : VAR: Command to Motor Control SWC                            */
/* Return      :                                                              */
/* Contents    : Send Command to Motor Control SWC                            */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Write_PP_PositionCommand_SendCommand( VAR(AUTOSAR_uint8, AUTOMATIC) command ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    VAR(Std_ReturnType, AUTOMATIC) ret;
    VAR(AUTOSAR_uint8, AUTOMATIC) tmp_data = command;

    ret = Com_SendSignal( ComConf_ComSignal_ComISignal_HS_CAN1_CommandSignal, &tmp_data );
    switch( ret ) {
    case COM_SERVICE_NOT_AVAILABLE:
        ret_val = RTE_E_COM_STOPPED;
        break;
    case COM_BUSY:
        ret_val = RTE_E_COM_BUSY;
        break;
    default:
        /* nothing */
        break;
    }

    return ret_val;
}


extern VAR(ParameterType, AUTOMATIC) parm;
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Read_RP_Parameter_ReceiveCalibParam                      */
/* Param       : P2VAR: Pointer to memory location which save default data    */
/* Return      :                                                              */
/* Contents    : Receive default data from Parameter SWC                      */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Read_RP_Parameter_ReceiveCalibParam( P2VAR(AUTOSAR_uint8, AUTOMATIC, RTE_APPL_DATA) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    *data = parm;
    return ret_val;
}


extern FUNC(Std_ReturnType, NvM_CODE) NvM_ReadBlock( VAR(NvM_BlockIdType, AUTOMATIC) BlockId, P2(void, AUTOMATIC) NvM_DstPtr);
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_RP_MemorySeat_NvM_ReadBlock                         */
/* Param       : VAR: The block identifier uniquely identifies one NVRAM block*/
/*                    descriptor                                              */
/*               P2VAR: Pointer to the RAM data block                         */
/* Return      :                                                              */
/* Contents    : Read data from NV memory                                     */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MemorySeat_NvM_ReadBlock( VAR(NvM_BlockIdType, AUTOMATIC) BlockId, P2(void, AUTOMATIC) NvM_DstPtr ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val;

    ret_val = NvM_ReadBlock(BlockId, NvM_DstPtr)
    return ret_val;
}


extern FUNC(Std_ReturnType, NvM_CODE) NvM_WriteBlock( VAR(NvM_BlockIdType, AUTOMATIC) BlockId, P2(void, AUTOMATIC) NvM_SrcPtr);
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_Call_RP_MemorySeat_NvM_WriteBlock                        */
/* Param       : VAR: The block identifier uniquely identifies one NVRAM block*/
/*                    descriptor                                              */
/*               P2VAR: Pointer to the RAM data block                         */
/* Return      :                                                              */
/* Contents    : Write data to NV memory                                        */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MemorySeat_NvM_WriteBlock( VAR(NvM_BlockIdType, AUTOMATIC) BlockId, P2(void, AUTOMATIC) NvM_SrcPtr ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val;

    ret_val = NvM_WriteBlock(BlockId, NvM_SrcPtr)
    return ret_val;
}


extern FUNC(void, ElectricSeatControl_CODE) ProcessCommand_10ms( VAR(void, AUTOMATIC) );
/******************************************************************************/
/* ModuleID    :                                                              */
/* ServiceID   :                                                              */
/* Name        : Rte_ProcessCommand_10ms                                      */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Runnable Process Command                                     */
/* Author      : QINeS Ecuc Generator(Java)                                   */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE_EcucPartition_0) Rte_ProcessCommand_10ms( VAR(void, AUTOMATIC) ) {

    ProcessCommand_10ms();

}



