#ifndef SEAT_MOTOR_CONTROL_SWC_H
#define SEAT_MOTOR_CONTROL_SWC_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/

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



#endif /* SEAT_MOTOR_CONTROL_SWC_H */

/* End of Seat_Motor_Control.h */
