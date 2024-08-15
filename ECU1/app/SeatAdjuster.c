/*----------------------------------------------------------------------------*/
/* include headers                                                            */
/*----------------------------------------------------------------------------*/
#include "Rte_SeatAdjuster.h"

/*----------------------------------------------------------------------------*/
/* private functions                                                          */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* Name        : GetCommand                                                   */
/* Param       : ioData         : io signal from Hardware Abstraction         */
/* Return      : command signal : generated command signal                    */
/* Contents    : Handle IO signal from Hardware Abstraction                   */
/* Author      :                                                              */
/* Note        : This function read io signal from Hardware abstraction then  */
/*               generate corresponding command signal with bit macros        */
/******************************************************************************/
static command_signal GetCommand( const io_signal ioData )
{
    command_signal return_value = 0x00u;

    /* Set Command Move Forward */
    if (0 != FORWARD_CHECK(ioData))
    {
        return_value |= MOVE_FORWARD_SIGNAL;
    }
    /* Set Command Move Backward */
    if (0 != BACKWARD_CHECK(ioData))
    {
        return_value |= MOVE_BACKWARD_SIGNAL;
    }
    /* Set Command Fold */
    if (0 != FOLD_CHECK(ioData))
    {
        return_value |= FOLD_SIGNAL;
    }
    /* Set Command Unfold */
    if (0 != UNFOLD_CHECK(ioData))
    {
        return_value |= UNFOLD_SIGNAL;
    }
    /* Set Command Set Mode */
    if (0 != SET_CHECK(ioData))
    {
        return_value |= SET_MODE_SIGNAL;
    }
    /* Set Command Mode 1 */
    if (0 != MODE1_CHECK(ioData))
    {
        return_value |= MODE1_SIGNAL;
    }
    /* Set Command Mode 2 */
    if (0 != MODE2_CHECK(ioData))
    {
        return_value |= MODE2_SIGNAL;
    }

    return return_value;
}

/*----------------------------------------------------------------------------*/
/* runnables                                                                  */
/*----------------------------------------------------------------------------*/

/******************************************************************************/
/* Name        : HandleAdjusterSignal_10ms                                    */
/* Param       :                                                              */
/* Return      :                                                              */
/* Contents    : Handle IO signal from Hardware Abstraction                   */
/* Author      :                                                              */
/* Note        : This function read io signal from Hardware abstraction:      */
/*               1 byte signal with each bit for each button pins, then create*/
/*               command signal to send to Electric Seat Control SWC          */
/******************************************************************************/
FUNC(void, SeatAdjuster_CODE) HandleAdjusterSignal_10ms( VAR(void, AUTOMATIC) )
{
	static io_signal      ioData  = 0;
    static command_signal command = 0;

    Rte_Call_RP_AdjustData_IoHwAb_DioReadChannelGroup(IO_CHANNEL_GROUP_1, &ioData);

    command = GetCommand( ioData );

    Rte_Write_PP_PositionData_SendPosition(command);

    /* Simulate Watchdog checkpoint */
    Rte_Call_WdgMCheckpointReached(se_id, cp_id);
}

/* End of Seat_Adjuster.c */
