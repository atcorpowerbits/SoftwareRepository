/**
 * \file 
 *
 * \brief Command Idle State
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 22/04/2013 12:33:10 PM
 * \author victora
 */ 

//_____ I N C L U D E S ____________________________________________________
#include <compiler.h>
#include "cmd_idle_state.h"
#include "cmd_busy_state.h"
#include "cmd_instant_state.h"
#include "usart/usart_rxtx.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________

/**
 * \brief No transition; Nothing to abort for cbp while in idle state
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void abort_cbp (command_state_ptr state, int cmd)
{
	print_debug("Nothing to abort_cbp while in %s state\n", state->name);
}

/**
 * \brief Transition into this idle state
 * \param[in] state Current command state
 */
void transition_to_idle (command_state_ptr state)
{
	print_debug("Transition: %s ===> IDLE\n", state->name);
	default_command_init(state);
	state->name = "IDLE";
	update_cbp_system_status(CBP_SYSTEM_STATUS_IDLE);

	// prepare to handle foreground CBP commands
	state->start_cbp = transition_to_busy;
	state->set_cbp_config = transition_to_busy;
	state->write_data_flash = transition_to_busy;
	state->set_sleep_mode = transition_to_busy;

	// prepare to handle background CBP commands
	state->abort_cbp = abort_cbp;
	state->get_cbp_status = transition_to_instant_response;
	state->get_cbp_results = transition_to_instant_response;
	state->get_cbp_up_status = transition_to_instant_response;
	state->get_cbp_config = transition_to_instant_response;
	state->get_cbp_adc_data = transition_to_instant_response;
	state->get_cbp_pressure = transition_to_instant_response;
}