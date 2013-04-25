/**
 * \file 
 *
 * \brief Command Busy State while executing a foreground command
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 22/04/2013 12:35:54 PM
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
static int current_foreground_cmd;

/**
 * \brief Transition from this busy state to idle state when cbp is aborted
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void abort_cbp (command_state_ptr state, int cmd)
{
	// do any clean up <TBD>
	switch (current_foreground_cmd)
	{
		case CMD_START_CBP:
		{
			print_debug("Under construction: aborting foreground command %02X\n", current_foreground_cmd);
			break;
		}
		case CMD_SET_CBP_CONFIG:
		{
			print_debug("Under construction: aborting foreground command %02X\n", current_foreground_cmd);
			break;
		}
		case CMD_WRITE_DATA_FLASH:
		{
			print_debug("Under construction: aborting foreground command %02X\n", current_foreground_cmd);
			break;
		}
		case CMD_SET_SLEEP_MODE:
		{
			print_debug("Under construction: aborting foreground command %02X\n", current_foreground_cmd);
			break;
		}
		default:
		{
			cmd_error = 3002; //<Tidy up error numbers TBD>
			print_debug("Error(%d): Unable to abort unsupported foreground command %02X\n", cmd_error, current_foreground_cmd);
			break;
		}
	}
	transition_to_idle(state);
}

/**
 * \brief Transition from this busy state to instant response state to reply cbp status
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void get_cbp_status (command_state_ptr state, int cmd)
{
	transition_to_instant_response(state, cmd);
}

/**
 * \brief Execute the foreground command
 * \param[in] cmd Foreground command to execute now
 */
static void execute_foreground_command (int cmd)
{
	current_foreground_cmd = cmd;
	
	switch (cmd)
	{
		case CMD_START_CBP:
		{
			print_debug("Under construction: foreground command %02X\n", cmd);
			break;
		}
		case CMD_SET_CBP_CONFIG:
		{
			print_debug("Under construction: foreground command %02X\n", cmd);
			break;
		}
		case CMD_WRITE_DATA_FLASH:
		{
			print_debug("Under construction: foreground command %02X\n", cmd);
			break;
		}
		case CMD_SET_SLEEP_MODE:
		{
			print_debug("Under construction: foreground command %02X\n", cmd);
			break;
		}
		default:
		{
			cmd_error = 3002; //<TBD>
			print_debug("Error(%d): Unable to execute unsupported foreground command %02X\n", cmd_error, cmd);
			break;
		}
	}	
}

/**
 * \brief Transition into this busy state
 * \param[in] state Current command state
 * \param[in] cmd Foreground command to execute
 */
void transition_to_busy (command_state_ptr state, int cmd)
{
	current_foreground_cmd = 0;
	default_command_init(state);
	state->name = "BUSY";

	// prepare to handle foreground CBP commands
	state->start_cbp = respond_busy;
	state->set_cbp_config = respond_busy;
	state->write_data_flash = respond_busy;
	state->set_sleep_mode = respond_busy;

	// prepare to handle background CBP commands
	state->abort_cbp = abort_cbp;
	state->get_cbp_status = get_cbp_status;
	state->get_cbp_results = respond_error;
	state->get_cbp_up_status = respond_error;
	state->get_cbp_config = respond_error;
	state->get_cbp_adc_data = respond_error;
	state->get_cbp_pressure = respond_error;
	
	execute_foreground_command(cmd);
}
