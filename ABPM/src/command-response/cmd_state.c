/**
 * \file 
 *
 * \brief Command Default State
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 22/04/2013 10:27:52 AM
 * \author victora
 */ 

//_____ I N C L U D E S ____________________________________________________
#include <compiler.h>
#include "cmd_state.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________
extern struct command_state_t * saved_command_state;

/**
 * \brief Respond to BP that CBP is busy
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
void respond_busy (command_state_ptr state, int cmd)
{
	print_debug("Unable to execute command %02X while CBP in %s state\n", cmd, state->name);
	// send busy packet <TBD>
}

/**
 * \brief Respond to BP that CBP command is undefined
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
void respond_undefined (command_state_ptr state, int cmd)
{
	print_debug("CBP command %02X is in error while CBP in %s state\n", cmd, state->name);
	// send error packet <TBD>
}

/**
 * \brief Respond to BP that CBP command is in error
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
void respond_error (command_state_ptr state, int cmd)
{
	print_debug("CBP command %02X is in error while CBP in %s state\n", cmd, state->name);
	// send error packet <TBD>
}

/**
 * \brief Default start cbp command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_start_cbp (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported start_cbp command in %s state\n", state->name);
}

/**
 * \brief Default abort cbp command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_abort_cbp (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported abort_cbp command in %s state\n", state->name);
}

/**
 * \brief Default get cbp status command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_get_cbp_status (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported get_cbp_status command in %s state\n", state->name);
}

/**
 * \brief Default get cbp results command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_get_cbp_results (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported get_cbp_results command in %s state\n", state->name);
}

/**
 * \brief Default get cbp microprocessor status command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_get_cbp_up_status (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported get_cbp_up_status command in %s state\n", state->name);
}

/**
 * \brief Default set cbp config command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_set_cbp_config (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported set_cbp_config command in %s state\n", state->name);
}

/**
 * \brief Default get cbp config command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_get_cbp_config (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported get_cbp_config command in %s state\n", state->name);
}

/**
 * \brief Default get cbp adc data command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_get_cbp_adc_data (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported get_cbp_adc_data command in %s state\n", state->name);
}

/**
 * \brief Default set sleep mode command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_set_sleep_mode (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported set_sleep_mode command in %s state\n", state->name);
}

/**
 * \brief Default write data flash command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_write_data_flash (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported write_data_flash command in %s state\n", state->name);
}

/**
 * \brief Default get cbp pressure data command to assist debugging command state machine
 * \param[in] state Current command state
 * \param[in] cmd Command received
 */
static void default_get_cbp_pressure (command_state_ptr state, int cmd)
{
	// Unsupported action
	print_debug("Unsupported get_cbp_pressure command in %s state\n", state->name);
}

/**
 * \brief Save current command state and actions
 * \param[in] state Current command state
 */
void push_command_state (command_state_ptr state)
{
	saved_command_state->name = state->name;
	saved_command_state->start_cbp = state->start_cbp;
	saved_command_state->abort_cbp = state->abort_cbp;
	saved_command_state->get_cbp_status = state->get_cbp_status;
	saved_command_state->get_cbp_results = state->get_cbp_results;
	saved_command_state->get_cbp_up_status = state->get_cbp_up_status;
	saved_command_state->set_cbp_config = state->set_cbp_config;
	saved_command_state->get_cbp_config = state->get_cbp_config;
	saved_command_state->get_cbp_adc_data = state->get_cbp_adc_data;
	saved_command_state->set_sleep_mode = state->set_sleep_mode;
	saved_command_state->write_data_flash = state->write_data_flash;
	saved_command_state->get_cbp_pressure = state->get_cbp_pressure;
}

/**
 * \brief Restore previous command state and actions
 */
void pop_command_state (command_state_ptr state)
{
	state->name = saved_command_state->name;
	state->start_cbp = saved_command_state->start_cbp;
	state->abort_cbp = saved_command_state->abort_cbp;
	state->get_cbp_status = saved_command_state->get_cbp_status;
	state->get_cbp_results = saved_command_state->get_cbp_results;
	state->get_cbp_up_status = saved_command_state->get_cbp_up_status;
	state->set_cbp_config = saved_command_state->set_cbp_config;
	state->get_cbp_config = saved_command_state->get_cbp_config;
	state->get_cbp_adc_data = saved_command_state->get_cbp_adc_data;
	state->set_sleep_mode = saved_command_state->set_sleep_mode;
	state->write_data_flash = saved_command_state->write_data_flash;
	state->get_cbp_pressure = saved_command_state->get_cbp_pressure;
}

/**
 * \brief Initialise default cbp command actions to assist debugging command state machine
 * \param[in] state Current command state
 */
void default_command_init (command_state_ptr state)
{
	state->name = "DEFAULT";
	state->start_cbp = default_start_cbp;
	state->abort_cbp = default_abort_cbp;
	state->get_cbp_status = default_get_cbp_status;
	state->get_cbp_results = default_get_cbp_results;
	state->get_cbp_up_status = default_get_cbp_up_status;
	state->set_cbp_config = default_set_cbp_config;
	state->get_cbp_config = default_get_cbp_config;
	state->get_cbp_adc_data = default_get_cbp_adc_data;
	state->set_sleep_mode = default_set_sleep_mode;
	state->write_data_flash = default_write_data_flash;
	state->get_cbp_pressure = default_get_cbp_pressure;
}
