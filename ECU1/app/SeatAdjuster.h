#ifndef SEAT_ADJUSTER_SWC_H
#define SEAT_ADJUSTER_SWC_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* definitions                                                                */
/*----------------------------------------------------------------------------*/

/* Type definition */
#define io_signal            uint8_t
#define command_signal       uint8_t
#define IO_CHANNEL_GROUP_1   /* Simulate IO channel group */

/* IO Hardware Signal Bit Macros */
#define CHECK_MASK          0x01u
#define FORWARD_SHIFT       6u
#define FORWARD_CHECK(x)    (((uint8_t)(((uint8_t)(x))>>FORWARD_SHIFT))&CHECK_MASK)
#define BACKWARD_SHIFT      5u
#define BACKWARD_CHECK(x)   (((uint8_t)(((uint8_t)(x))>>BACKWARD_SHIFT))&CHECK_MASK)
#define FOLD_SHIFT          4u
#define FOLD_CHECK(x)       (((uint8_t)(((uint8_t)(x))>>FOLD_SHIFT))&CHECK_MASK)
#define UNFOLD_SHIFT        3u
#define UNFOLD_CHECK(x)     (((uint8_t)(((uint8_t)(x))>>UNFOLD_SHIFT))&CHECK_MASK)
#define SET_SHIFT           2u
#define SET_CHECK(x)        (((uint8_t)(((uint8_t)(x))>>SET_SHIFT))&CHECK_MASK)
#define MODE1_SHIFT         1u
#define MODE1_CHECK(x)      (((uint8_t)(((uint8_t)(x))>>FOLD_SHIFT))&CHECK_MASK)
#define MODE2_SHIFT         0u
#define MODE2_CHECK(x)      (((uint8_t)(((uint8_t)(x))>>UNFOLD_SHIFT))&CHECK_MASK)

/* Command Signal Definitions */
#define MOVE_FORWARD_SIGNAL     (command_signal)0x40u
#define MOVE_BACKWARD_SIGNAL    (command_signal)0x80u
#define FOLD_SIGNAL             (command_signal)0x10u
#define UNFOLD_SIGNAL           (command_signal)0x20u
#define SET_MODE_SIGNAL         (command_signal)0x04u
#define MODE1_SIGNAL            (command_signal)0x08u
#define MODE2_SIGNAL            (command_signal)0x0Cu

/*----------------------------------------------------------------------------*/
/* runnables                                                                  */
/*----------------------------------------------------------------------------*/

FUNC(void, HandleAdjusterSignal_CODE) HandleAdjusterSignal_10ms( void );


#endif /* SEAT_ADJUSTER_SWC_H */

/* End of Seat_Adjuster.h */
