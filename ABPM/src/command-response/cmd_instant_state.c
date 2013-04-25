/**
 * \file 
 *
 * \brief Command Instant Response State to execute a background command
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 22/04/2013 5:09:15 PM
 * \author victora
 */ 

//_____ I N C L U D E S ____________________________________________________
#include <compiler.h>
#include "cmd_idle_state.h"
#include "cmd_busy_state.h"
#include "cmd_instant_state.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________

/**
 * \brief Respond with instant data
 * \param[in] cmd Background command to be responded instantly
 * \param[in] cmd Command received
 */
static void respond_intant_data (int cmd)
{
	switch (cmd)
	{
		case CMD_GET_CBP_STATUS:
		{
			print_debug("Under construction: background command %02X\n", cmd);
			break;
		}
		case CMD_GET_CBP_RESULTS:
		{
			print_debug("Under construction: background command %02X\n", cmd);
			break;
		}
		case CMD_GET_CBP_UP_STATUS:
		{
			print_debug("Under construction: background command %02X\n", cmd);
			break;
		}
		case CMD_GET_CBP_CONFIG:
		{
			print_debug("Under construction: background command %02X\n", cmd);
			break;
		}
		case CMD_GET_CBP_ADC_DATA:
		{
			print_debug("Under construction: background command %02X\n", cmd);
			break;
		}
		case CMD_GET_CBP_PRESSURE:
		{
			print_debug("Under construction: background command %02X\n", cmd);
			break;
		}
		default:
		{
			print_debug("Error(%d): Unable to execute unsupported background command %02X\n", cmd);
			break;
		}
	}	
}

/**
 * \brief Transition into this instant response state
 * \param[in] state Current command state
 * \param[in] cmd Background command to be responded instantly
 */
void transition_to_instant_response (command_state_ptr state, int cmd)
{
	// Keep the caller state to return to
	push_command_state(state);
	
	default_command_init(state);
	state->name = "INSTANT_RESPONSE";
	
	respond_intant_data(cmd);
	
	// Return to caller state
	pop_command_state(state);
}
