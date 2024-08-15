#ifndef RTE_MOTOR_CONTROL_TYPE_H
#define RTE_MOTOR_CONTROL_TYPE_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Std_Type.h"

/*----------------------------------------------------------------------------*/
/* definitions                                                                */
/*----------------------------------------------------------------------------*/

/* Command signal definition */
#define command_signal       uint8_t

/* Command Signal Definitions */
#define MOVE_FORWARD_COMMAND   0x40u
#define MOVE_BACKWARD_COMMAND  0x80u
#define FOLD_COMMAND           0x10u
#define UNFOLD_COMMAND         0x20u
#define SET_MODE_COMMAND       0x04u
#define MODE1_COMMAND          0x08u
#define MODE2_COMMAND          0x0Cu

#endif /* RTE_MOTOR_CONTROL_TYPE_H */

/* End of Rte_MotorControl_Type.h */
