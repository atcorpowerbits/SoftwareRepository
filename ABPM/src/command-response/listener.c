/**
 * \file 
 *
 * \brief Listen a command from BP and take action
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 22/04/2013 9:45:03 AM
 * \author victora
 */ 

//_____ I N C L U D E S ____________________________________________________
#include <compiler.h>
#include "listener.h"
#include "cmd_idle_state.h"
#include "usart/usart_rxtx.h"
#include "pwa/pwa.h"
#include "config/conf_abpm.h"
#include "sender.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________
// A flag to inform when a packet from BP is received
bool flag_packet_received = false;

// A flag to inform when pwa calculation is finished
bool flag_finished_pwa = false;

// Keep time stamp data from BP
bp_timestamp_t bp_timestamp;

// Keep BP calibration data from BP
bp_calibration_t bp_calibration;

//uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0}; // to be filled in after a good packet is received and CRC checked.
uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x01, 0x38, 0x22, 0x0C, 0x0B, 0x0C, 0x0D, 0x00, 0x88}; // simulate START_CBP command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x02, 0x88}; // simulate ABORT_CBP command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x03, 0x88}; // simulate GET_CBP_STATUS command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x04, 0x88}; // simulate GET_CBP_RESULTS command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x05, 0x88}; // simulate GET_CBP_UP_STATUS command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x06, 0, 0, 0, 0, 0x88}; // simulate SET_CBP_CONFIG command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x07, 0x88}; // simulate GET_CBP_CONFIG command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x08, 0x88}; // simulate GET_CBP_ADC_DATA command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x09, 0x88}; // simulate SET_SLEEP_MODE command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x0A, 0xA5, 0x88}; // simulate WRITE_DATA_FLASH command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0x0B, 0x7B, 0, 0x59, 0, 0x88}; // simulate GET_CBP_PRESSURE command packet
//va:UT uint8_t packet_received_buffer[MAX_CMD_PACKET_SIZE] = {0x2A, 0xFF, 0x88}; // simulate undefined command packet

/**
 * \brief Singleton instance of the command state machine
 */
cbp_command_ptr cbp_command_instance;

//struct command_state_t * saved_command_state;

//_____ P R O T O T Y P E S ________________________________________________
cbp_command_ptr listener_create_command (void);
void listener_init(void);
void listener_task(void);

/**
 * \brief Convert LSB and MSB bytes to 16-bit unsigned integer value
 * param[in] lsb LSB
 * param[in] msb MSB
 * \return 16-bit unsigned integer value
 */
static uint16_t bytes_to_uint16 (uint8_t lsb, uint8_t msb)
{
	uint16_t value = msb;
	
	value = (value << 8) | lsb;
	return value;
}

/**
 * \brief Create a command state machine singleton
 * \return Pointer to cbp command
 */
cbp_command_ptr listener_create_command (void)
{
	cbp_command_ptr instance = malloc (sizeof *instance);

	if (NULL != instance)
	{
		transition_to_idle(&instance->current_state);
	}
	return instance;
}

/**
 * \brief Take action wrt command received from BP
 */
static void command_action(void)
{
	uint8_t cmd = packet_received_buffer[1]; // 2nd byte in the received packet is a command byte
	
	switch (cmd)
	{
		case CMD_START_CBP:
		{
			// Extract timestamp data from BP
			bp_timestamp.second = packet_received_buffer[2];
			bp_timestamp.minute = packet_received_buffer[3];
			bp_timestamp.hour   = packet_received_buffer[4];
			bp_timestamp.day    = packet_received_buffer[5];
			bp_timestamp.month  = packet_received_buffer[6];
			bp_timestamp.year   = packet_received_buffer[7];

			cbp_command_instance->current_state.start_cbp(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_ABORT_CBP:
		{
			cbp_command_instance->current_state.abort_cbp(&cbp_command_instance->current_state, cmd);

			// Acknowledge BP that CBP has aborted
			send_aborted(cmd);
			break;
		}
		case CMD_GET_CBP_STATUS:
		{
			cbp_command_instance->current_state.get_cbp_status(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_GET_CBP_RESULTS:
		{
			cbp_command_instance->current_state.get_cbp_results(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_GET_CBP_UP_STATUS:
		{
			cbp_command_instance->current_state.get_cbp_up_status(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_SET_CBP_CONFIG:
		{
			cbp_command_instance->current_state.set_cbp_config(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_GET_CBP_CONFIG:
		{
			cbp_command_instance->current_state.get_cbp_config(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_GET_CBP_ADC_DATA:
		{
			cbp_command_instance->current_state.get_cbp_adc_data(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_SET_SLEEP_MODE:
		{
			cbp_command_instance->current_state.set_sleep_mode(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_WRITE_DATA_FLASH:
		{
			cbp_command_instance->current_state.write_data_flash(&cbp_command_instance->current_state, cmd);
			break;
		}
		case CMD_GET_CBP_PRESSURE:
		{
			// Extract brachial calibration data from BP
			bp_calibration.sys = bytes_to_uint16(packet_received_buffer[2], packet_received_buffer[3]);
			bp_calibration.dia = bytes_to_uint16(packet_received_buffer[4], packet_received_buffer[5]);

			cbp_command_instance->current_state.get_cbp_pressure(&cbp_command_instance->current_state, cmd);
			break;
		}
		default:
		{
			respond_undefined(&cbp_command_instance->current_state, cmd);
			cmd_resp_error_code = CMD_UNDEFINED;
			print_debug("Error(%d): Undefined command %02X received\n", cmd_resp_error_code, cmd);
			break;
		}
	}
}

/**
 * \brief Initialise command listener
 */
void listener_init(void)
{
	flag_packet_received = true; //va:UT Set true to simulate packet received. Restore false;
	flag_start_pwa = false;
	flag_finished_pwa = false;
	flag_abort = false;
	
	cbp_command_instance = listener_create_command();
//	saved_command_state = malloc (sizeof *saved_command_state);
	
	bp_calibration.sys = 9999;
	bp_calibration.dia = 9999;
}

/**
 * \brief Main task for the command listener to take further action if a good (ie CRC checked) packet is received
 */
void listener_task(void)
{
	if (flag_packet_received)
	{
		command_action();
		
		// Recycle received packet after taking a command action
		flag_packet_received = false;
	}
	
	// Also listen to internal pwa calculation finished event to take further action, i.e. to send <K> packet
	if (flag_finished_pwa)
	{
		cbp_command_instance->current_state.finish_cbp(&cbp_command_instance->current_state, CMD_START_CBP);
		flag_finished_pwa = false;
	}
}