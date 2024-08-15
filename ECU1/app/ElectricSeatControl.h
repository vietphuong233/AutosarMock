#ifndef ELECTRIC_SEAT_CONTROL_SWC_H
#define ELECTRIC_SEAT_CONTROL_SWC_H

/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/

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

/* Check command type macros */
#define MOVE_MASK                     0x0Fu
#define MOVE_COMMAND_SHIFT            4u
#define CHECK_MOVE_COMMAND(x)         (((uint8_t)(((uint8_t)(x))>>MOVE_COMMAND_SHIFT))&MOVE_MASK)
#define MEM_MASK                      0x03u
#define MEM_COMMAND_SHIFT             2u
#define CHECK_MEMORY_COMMAND(x)       (((uint8_t)(((uint8_t)(x))>>MEM_COMMAND_SHIFT))&MEM_MASK)

/* Block ID definitions */
#define BLOCKID1    0x01U/* Simulate NvMBlock ID for setting 1             */
#define BLOCKID2    0x02U/* Simulate NvMBlock ID for setting 2             */
#define BLOCKIDOLD  0x03U/* Simulate NvMBlock ID for latest saved position */

/*----------------------------------------------------------------------------*/
/* runnables                                                                  */
/*----------------------------------------------------------------------------*/

FUNC(void, SeatAdjuster_CODE) InitElectricSeatControl( VAR(void, AUTOMATIC) );

FUNC(void, SeatAdjuster_CODE) ProcessCommand_10ms( VAR(void, AUTOMATIC) );

/*----------------------------------------------------------------------------*/
/* private functions prototypes                                               */
/*----------------------------------------------------------------------------*/
command_type_t GetCommandType( command_signal command );
void StartAdjusting(seat_positon_t new_positon);
uint32_t GetMemoryId(command_signal command)

#endif /* ELECTRIC_SEAT_CONTROL_SWC_H */

/* End of Electric_Seat_Control.h */
