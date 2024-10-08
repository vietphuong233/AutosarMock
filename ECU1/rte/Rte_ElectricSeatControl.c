#include "Os.h"
#include "Rte_ElectricSeatControl.h"


extern VAR(AUTOSAR_uint8, AUTOMATIC) adjust_data;
/******************************************************************************/
/* Name        : Rte_Read_RP_PositionData_ReceivePosition                     */
/* Param       : P2VAR: Pointer to memory location which save position data   */
/* Return      :                                                              */
/* Contents    : Read position data from Seat Adjuster SWC                    */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_RP_PositionData_ReceivePosition( P2VAR(AUTOSAR_uint8, AUTOMATIC, RTE_APPL_DATA) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    *data = adjust_data;

    return ret_val;
}


/******************************************************************************/
/* Name        : Rte_Write_PP_PositionCommand_SendCommand                     */
/* Param       : VAR: Command to Motor Control SWC                            */
/* Return      :                                                              */
/* Contents    : Send Command to Motor Control SWC                            */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Write_PP_PositionCommand_SendCommand( VAR(AUTOSAR_uint8, AUTOMATIC) command ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;
    VAR(Std_ReturnType, AUTOMATIC) ret;
    VAR(AUTOSAR_uint8, AUTOMATIC) tmp_data = command;

    ret = Com_SendSignal( ComConf_ComSignal_CommandSignal, &tmp_data );
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
/* Name        : Rte_Read_RP_Parameter_ReceiveCalibParam                      */
/* Param       : P2VAR: Pointer to memory location which save default data    */
/* Return      :                                                              */
/* Contents    : Receive default data from Parameter SWC                      */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Read_RP_Parameter_ReceiveCalibParam( P2VAR(AUTOSAR_uint8, AUTOMATIC, RTE_APPL_DATA) data ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    *data = parm;
    return ret_val;
}


/******************************************************************************/
/* Name        : Rte_Call_RP_MemorySeat_NvM_ReadCurrentPosition               */
/* Param       : P2VAR: Pointer to the RAM data block                         */
/* Return      :                                                              */
/* Contents    : Read current position data from NV memory                    */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_ReadCurrentPosition( P2VAR(AUTOSAR_uint16, AUTOMATIC, RTE_APPL_DATA) NvM_DstPtr ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    NvM_ReadBlock(NvMBlock0, (uint16*)NvM_DstPtr)
    return ret_val;
}


/******************************************************************************/
/* Name        : Rte_Call_RP_MemorySeat_NvM_ReadMode                          */
/* Param       : P2VAR: Pointer to the RAM data block                         */
/* Return      :                                                              */
/* Contents    : Read mode position data from NV memory                       */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_ReadMode( P2VAR(AUTOSAR_uint32, AUTOMATIC, RTE_APPL_DATA) NvM_DstPtr ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    NvM_ReadBlock(NvMBlock1, (uint32*)NvM_DstPtr)
    return ret_val;
}


/******************************************************************************/
/* Name        : Rte_Call_RP_MemorySeat_NvM_WriteCurrentPosition              */
/* Param       : P2VAR: Pointer to the RAM data block                         */
/* Return      :                                                              */
/* Contents    : Write current position data to NV memory                     */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_WriteCurruntPosition( P2VAR(AUTOSAR_uint16, AUTOMATIC, RTE_APPL_DATA) NvM_SrcPtr ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    NvM_WriteBlock(NvMBlock0, (uint16*) NvM_SrcPtr)
    return ret_val;
}

/******************************************************************************/
/* Name        : Rte_Call_RP_MemorySeat_NvM_WriteMode                         */
/* Param       : P2VAR: Pointer to the RAM data block                         */
/* Return      :                                                              */
/* Contents    : Write mode position data to NV memory                        */
/* Note        :                                                              */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) Rte_Call_RP_MemorySeat_NvM_WriteMode( P2VAR(AUTOSAR_uint32, AUTOMATIC, RTE_APPL_DATA) NvM_SrcPtr ) {
    VAR(Std_ReturnType, AUTOMATIC) ret_val = RTE_E_OK;

    NvM_WriteBlock(NvMBlock1, (uint32*) NvM_SrcPtr)
    return ret_val;
}


extern FUNC(void, ElectricSeatControl_CODE) ProcessCommand_10ms( VAR(void, AUTOMATIC) );
/******************************************************************************/
/* Name        : Rte_ProcessCommand_10ms                                      */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Runnable Process Command                                     */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE) Rte_ProcessCommand_10ms( VAR(void, AUTOMATIC) ) {

    ProcessCommand_10ms();

}


extern FUNC(void, ElectricSeatControl_CODE) InitElectricSeatControl( VAR(void, AUTOMATIC) );
/******************************************************************************/
/* Name        : Rte_InitElectricSeatControl                                  */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Runnable Init Electric Seat Control                          */
/* Note        :                                                              */
/******************************************************************************/
FUNC(void, RTE_CODE) Rte_InitElectricSeatControl( VAR(void, AUTOMATIC) ) {

    InitElectricSeatControl();

}



