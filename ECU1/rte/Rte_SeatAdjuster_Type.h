#ifndef RTE_SEATADJUSTER_TYPE_H
#define RTE_SEATADJUSTER_TYPE_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_Type.h"

/*----------------------------------------------------------------------------*/
/* definitions                                                                */
/*----------------------------------------------------------------------------*/

/* IO Hardware Signal Bit Macros */
#define CHECK_MASK          0x01u
#define FORWARD_SHIFT       6u
#define FORWARD_CHECK(x)    (((uint8)(((uint8)(x))>>FORWARD_SHIFT))&CHECK_MASK)
#define BACKWARD_SHIFT      5u
#define BACKWARD_CHECK(x)   (((uint8)(((uint8)(x))>>BACKWARD_SHIFT))&CHECK_MASK)
#define FOLD_SHIFT          4u
#define FOLD_CHECK(x)       (((uint8)(((uint8)(x))>>FOLD_SHIFT))&CHECK_MASK)
#define UNFOLD_SHIFT        3u
#define UNFOLD_CHECK(x)     (((uint8)(((uint8)(x))>>UNFOLD_SHIFT))&CHECK_MASK)
#define SET_SHIFT           2u
#define SET_CHECK(x)        (((uint8)(((uint8)(x))>>SET_SHIFT))&CHECK_MASK)
#define MODE1_SHIFT         1u
#define MODE1_CHECK(x)      (((uint8)(((uint8)(x))>>FOLD_SHIFT))&CHECK_MASK)
#define MODE2_SHIFT         0u
#define MODE2_CHECK(x)      (((uint8)(((uint8)(x))>>UNFOLD_SHIFT))&CHECK_MASK)

/* Command Signal Definitions */
#define MOVE_FORWARD_SIGNAL     0x40U
#define MOVE_BACKWARD_SIGNAL    0x80U
#define FOLD_SIGNAL             0x10U
#define UNFOLD_SIGNAL           0x20U
#define SET_MODE_SIGNAL         0x04U
#define MODE1_SIGNAL            0x08U
#define MODE2_SIGNAL            0x0CU

#endif /* RTE_SEATADJUSTER_TYPE_H */

/* End of Rte_SeatAdjuster_Type.h */
