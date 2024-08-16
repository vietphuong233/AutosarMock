#ifndef RTE_DATAHANDLE_H
#define RTE_DATAHANDLE_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_Type.h"

/*----------------------------------------------------------------------------*/
/* definitions                                                                */
/*----------------------------------------------------------------------------*/

/* Generic typedef */
#define io_signal       uint8
#define command_signal  uint8

/* Seat position definition */
typedef struct _seat_position
{
    uint8 SEAT_POS;                 /* Position of Seat     */
    uint8 BACKREST_POS;             /* Position of Backrest */

} seat_position_t;

/* Seat control definition */
typedef struct _seat_control
{
    seat_position_t POSITION;       /* Current Positon       */
    sint8           SEAT_MOVE;      /* Seat move needed      */
    sint8           BACKREST_MOVE;  /* Back rest move needed */
    seat_state_t    STATE;          /* Current State         */
} seat_control_t;

/* Setting data on NvM */
typedef struct _setting_data
{
    seat_position_t MODE1_DATA;     /* Data from mode button 1 */
    seat_position_t MODE2_DATA;     /* Data from mode button 2 */
} setting_data_t;

#endif /* RTE_DATAHANDLE_H */

/* End of Rte_DataHandle.h */
