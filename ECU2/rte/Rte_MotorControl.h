#ifndef RTE_MOTORCONTROL_H
#define RTE_MOTORCONTROL_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_MotorControl_Type.h"

/*----------------------------------------------------------------------------*/
/* RTE API Declaration                                                        */
/*----------------------------------------------------------------------------*/

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MotorControl_IoHwAb_SeatMoveForward( void );
#define Rte_Call_RP_MotorControl_IoHwAb_SeatMoveForward Rte_Call_IoHwAb_SeatMoveForward

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MotorControl_IoHwAb_SeatMoveBack( void );
#define Rte_Call_RP_MotorControl_IoHwAb_SeatMoveBack    Rte_Call_IoHwAb_SeatMoveBack
extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MotorControl_IoHwAb_BackSeatFold( void );
#define Rte_Call_RP_MotorControl_IoHwAb_BackSeatFold    Rte_Call_IoHwAb_BackSeatFold

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Call_RP_MotorControl_IoHwAb_BackSeatUnfold( void );
#define Rte_Call_RP_MotorControl_IoHwAb_BackSeatUnfold  Rte_Call_IoHwAb_BackSeatUnfold

extern FUNC(Std_ReturnType, RTE_CODE_EcucPartition_0) Rte_Read_RP_PositionCommand_Command( P2VAR(AUTOSAR_uint8, AUTOMATIC, RTE_APPL_DATA) command );
#define Rte_Read_RP_PositionCommand_ReceiveCommand      Rte_Read_ReceiveCommand

extern FUNC(void, RTE_CODE_EcucPartition_0) Rte_HandlePositionCommand_10ms( VAR(void, AUTOMATIC) );

Rte_COMCbk_ComIPdu_SeatBsw_CAN_HS_CAN_CommandReq( void );

#endif /* RTE_MOTORCONTROL_H */

/* End of Rte_MotorControl.h */
