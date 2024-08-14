#ifndef SEAT_MOTOR_CONTROL_SWC_H
#define SEAT_MOTOR_CONTROL_SWC_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* definitions                                                                */
/*----------------------------------------------------------------------------*/

/* Type definition */
#define io_signal       uint8_t
#define command_signal  uint8_t
#define IO_CHANNEL_GROUP_1   /* Simulate IO channel group */

/* Command Signal Definitions */
#define MOVE_FORWARD_COMMAND   (command_signal)0x40u
#define MOVE_BACKWARD_COMMAND  (command_signal)0x80u
#define FOLD_COMMAND           (command_signal)0x10u
#define UNFOLD_COMMAND         (command_signal)0x20u
#define SET_MODE_COMMAND       (command_signal)0x04u
#define MODE1_COMMAND          (command_signal)0x08u
#define MODE2_COMMAND          (command_signal)0x0Cu



#endif /* SEAT_MOTOR_CONTROL_SWC_H */

/* End of Seat_Motor_Control.h */
