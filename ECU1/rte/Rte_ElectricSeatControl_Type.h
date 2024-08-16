#ifndef RTE_ELECTRICSEATCONTROL_TYPE_H
#define RTE_ELECTRICSEATCONTROL_TYPE_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_Type.h"

/*----------------------------------------------------------------------------*/
/* definitions                                                                */
/*----------------------------------------------------------------------------*/

/* Command type definition */
typedef enum _command_type
{
    MOVE_COMMAND,          /* Instruct Motor to move      */
    MEMORY_READ_COMMAND,   /* Call NvM to read            */
    MEMORY_WRITE_COMMAND,  /* Call NvM to write           */
} command_type_t;

/* Check position status */
typedef enum _position_status
{
    MOVE_OK,
    MOVE_NOT_OK,
} position_status_t;

/* Seat control state definition */
typedef enum _seat_state
{
    ADJUSTING,    /* Doing adjusting sequence */
    IDLING,       /* Waiting for command      */
} seat_state_t;

/* Setting mode number */
typedef enum _setting_mode
{
    NO_SETTING,       /* No button dectected */
    SETTING_MODE1,    /* Setting from button 1 */
    SETTING_MODE2,    /* Setting from button 2 */
} setting_mode_t;


/* Seat position definition */
typedef struct _seat_position
{
    uint8_t SEAT_POS;        /* Position of Seat */
    uint8_t BACKREST_POS;    /* Position of Backrest */

} seat_position_t;

/* Seat control definition */
typedef struct _seat_control
{
    seat_position_t POSITION;       /* Current Positon */
    int8_t          SEAT_MOVE;      /* Seat move needed */
    int8_t          BACKREST_MOVE;  /* Back rest move needed */
    seat_state_t    STATE;          /* Current State */
} seat_control_t;

/* Setting data on NvM */
typedef struct _setting_data
{
    seat_position_t MODE1_DATA;
    seat_position_t MODE2_DATA;
} setting_data_t;

/* Check command type macros */
#define MOVE_MASK                     0x0Fu
#define MOVE_COMMAND_SHIFT            4u
#define CHECK_MOVE_COMMAND(x)         (((uint8_t)(((uint8_t)(x))>>MOVE_COMMAND_SHIFT))&MOVE_MASK)
#define MEM_MASK                      0x03u
#define MEM_COMMAND_SHIFT             2u
#define CHECK_MEMORY_COMMAND(x)       (((uint8_t)(((uint8_t)(x))>>MEM_COMMAND_SHIFT))&MEM_MASK)

#endif /* ELECTRICSEATCONTROL_TYPE_H */

/* End of Rte_ElectricSeatControl_Type.h */
