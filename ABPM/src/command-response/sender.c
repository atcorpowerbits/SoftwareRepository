/**
 * \file 
 *
 * \brief Send a response from CBP to BP
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 26/04/2013 9:49:03 AM
 * \author victora
 */ 

//_____ I N C L U D E S ____________________________________________________
#include <compiler.h>
#include "cmd_state.h"
#include "sender.h"
#include "crc8.h"
#include "usart/usart_rxtx.h"
#include "config/conf_abpm.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________
uint8_t packet_transmit_buffer[MAX_RESPONSE_PACKET_SIZE] = {0}; // to be filled in after a good packet is received and CRC checked.
uint8_t packet_transmit_len = 0;

// A flag to inform when a packet is ready to send to BP
bool flag_packet_to_send = false;

//_____ P R O T O T Y P E S ________________________________________________

/**
 * \brief Log packet buffer overflow error and send error response
 * param[in] cmd Command from BP which CBP is responding to
 * param[in] len Overflow packet length
 */
static void send_error_buffer_overflow (uint8_t cmd, uint8_t len)
{
	cmd_resp_error_code = RESP_XMIT_PACKET_BUFF_OVERFLOW;
	print_debug("Error(%d): Respond with <E> to command %02X due to transmit packet buffer overflow; length = %d\n", cmd_resp_error_code, cmd, len);
	send_error(cmd);
}

/**
 * \brief Fill in data to the packet buffer by appending data bytes
 * param[in] cmd Command from BP which CBP is responding to
 * param[in] total_len Number of bytes to be transmitted
 */
static bool fill_packet_header (uint8_t cmd, uint8_t total_len)
{
	bool filled = false;
	
	// Make sure there is no outstanding packet to transmit
	if (flag_packet_to_send)
	{
		cmd_resp_error_code = RESP_XMIT_PACKET_OUTSTANDING;
		print_debug("Error(%d): Respond with <E> to command %02X due to transmit packet outstanding\n", cmd_resp_error_code, cmd);
		send_error(cmd);
	}
	// Check if packet transmit buffer is long enough
	else if (total_len < MAX_RESPONSE_PACKET_SIZE)
	{
		packet_transmit_len = 0;
		packet_transmit_buffer[packet_transmit_len++] = RESPONSE_START_BYTE;
		packet_transmit_buffer[packet_transmit_len++] = total_len;
		packet_transmit_buffer[packet_transmit_len++] = cmd;
		filled = true;
	}
	else
	{
		// log and send error packet because CBP cannot respond to a command from BP
		send_error_buffer_overflow(cmd, total_len);
	}
	return filled;
}

/**
 * \brief Fill in data to the packet buffer by appending data bytes
 * param[in] data_buff Data buffer of bytes
 * param[in] data_count Number of data bytes 
 */
static void fill_packet_data_bytes (uint8_t* data_buff, uint8_t data_count)
{
	int i;
	
	// Fill in data bytes in the packet buffer
	for (i = 0; i < data_count; i++)
	{
		packet_transmit_buffer[packet_transmit_len + i] = *(data_buff + i);
	}
	packet_transmit_len += data_count;
}

/**
 * \brief Fill in data to the packet buffer by appending data bytes
 * param[in] data_buff Data buffer of integers
 * param[in] data_count Number of integer data 
 */
static void fill_packet_data_integers (uint16_t* data_buff, uint8_t data_count)
{
	int i;
	
	// Fill in integers in the packet buffer; 2-byte per integer; LSB first
	for (i = 0; i < data_count; i++)
	{
		packet_transmit_buffer[packet_transmit_len + (2 * i)] = *(data_buff + i) & 0x00FF; // LSB
		packet_transmit_buffer[packet_transmit_len + (2 * i) + 1] = (*(data_buff + i) & 0xFF00) >> 8; // MSB
	}
	packet_transmit_len += 2 * data_count;
}

/**
 * \brief Fill in crc at the end of the packet to transmit
 */
static void fill_packet_crc (void)
{
	packet_transmit_buffer[packet_transmit_len] = calculate_crc(packet_transmit_buffer, packet_transmit_len);
	packet_transmit_len++;
}

/**
 * \brief Send a single data response packet to BP
 * param[in] cmd Command from BP which CBP is responding to
 * param[in] data Data to package in the response
 */
void send_response_single_data (uint8_t cmd, uint8_t data)
{
	if (flag_packet_to_send)
	{
		// <TBD> There is an outstanding packet to transmit; Can't call send_error which may cause an endless recursive call to send_response_single_data again?
	}
	else
	{
		packet_transmit_len = 0;
		packet_transmit_buffer[packet_transmit_len++] = RESPONSE_START_BYTE;
		packet_transmit_buffer[packet_transmit_len++] = RESPONSE_LENGTH_SINGLE_DATA;
		packet_transmit_buffer[packet_transmit_len++] = cmd; // responding to this command
		packet_transmit_buffer[packet_transmit_len++] = data; // single data to respond with
		packet_transmit_buffer[packet_transmit_len++] = calculate_crc(packet_transmit_buffer, RESPONSE_LENGTH_SINGLE_DATA - 1);

		// inform to send the packet out
		flag_packet_to_send = true;
	}
}

/**
 * \brief Send current CBP status to BP
 */
void send_status (void)
{
	uint8_t dummy_other_status[CBP_OTHER_STATUS_DATA_LEN] = {0};
	int total_len = CBP_STATUS_DATA_LEN + RESPONSE_PACKET_OVERHEAD; // including crc

	// Fill the packet header which also makes sure there is no outstanding packet to transmit
	if (fill_packet_header(CMD_GET_CBP_STATUS, total_len))
	{
		print_debug("Sending current status to BP\n");
		fill_packet_data_bytes(get_current_cbp_system_status(), CBP_SYSTEM_STATUS_DATA_LEN);
		fill_packet_data_bytes(dummy_other_status, CBP_OTHER_STATUS_DATA_LEN);
		fill_packet_crc();

		// inform to send the packet out now
		flag_packet_to_send = true;
	}
}

/**
 * \brief Send current CBP config parameters to BP
 */
void send_config (void)
{
	int total_len = CBP_CONFIG_DATA_LEN + RESPONSE_PACKET_OVERHEAD; // including crc

	// Fill the packet header which also makes sure there is no outstanding packet to transmit
	if (fill_packet_header(CMD_GET_CBP_CONFIG, total_len))
	{
		print_debug("Sending current config to BP\n");
		fill_packet_data_bytes(get_current_cbp_config(), CBP_CONFIG_DATA_LEN);
		fill_packet_crc();

		// inform to send the packet out now
		flag_packet_to_send = true;
	}
}

/**
 * \brief Send abort packet to BP to acknowledge abort 
 * param[in] cmd Command from BP which CBP is responding to
 */
void send_aborted (uint8_t cmd)
{
	print_debug("Sending ABORT response to command %02X\n", cmd);
	send_response_single_data(cmd, ABORT_RESPONSE);
}

/**
 * \brief Send busy packet to BP
 * param[in] cmd Command from BP which CBP is responding to
 */
void send_busy (uint8_t cmd)
{
	print_debug("Sending BUSY response to command %02X\n", cmd);
	send_response_single_data(cmd, BUSY_RESPONSE);
}

/**
 * \brief Send <O> packet to BP when foreground command is started
 * param[in] cmd Command from BP which CBP is responding to
 */
void send_o_ok (uint8_t cmd)
{
	print_debug("Sending <O> response to command %02X\n", cmd);
	send_response_single_data(cmd, O_OK_RESPONSE);
}

/**
 * \brief Send <K> packet to BP when foreground command is finished
 * param[in] cmd Command from BP which CBP is responding to
 */
void send_k_ok (uint8_t cmd)
{
	print_debug("Sending <K> response to command %02X\n", cmd);
	send_response_single_data(cmd, K_OK_RESPONSE);
}

/**
 * \brief Send error packet to BP
 * param[in] cmd Command from BP which CBP is responding to
 */
void send_error (uint8_t cmd)
{
	print_debug("Sending ERROR <E> response to command %02X\n", cmd);
	send_response_single_data(cmd, ERROR_RESPONSE);
}

/**
 * \brief Send sleeping packet to BP
 * param[in] cmd Command from BP which CBP is responding to
 */
void send_sleeping (uint8_t cmd)
{
	print_debug("Sending SLEEPING <S> response\n");
	send_response_single_data(cmd, SLEEPING_RESPONSE);
}

/**
 * \brief Send timeout packet to BP
 * param[in] cmd Command from BP which CBP is responding to
 */
void send_timeout (uint8_t cmd)
{
	print_debug("Sending TIMEOUT <T> response\n");
	send_response_single_data(cmd, TIMEOUT_RESPONSE);
}

/**
 * \brief Send undefined packet to BP
 * param[in] cmd Command from BP which CBP is responding to
 */
void send_undefined (uint8_t cmd)
{
	print_debug("Sending UNDEFINED <N> response to command %02X\n", cmd);
	send_response_single_data(cmd, UNDEFINED_RESPONSE);
}

/**
 * \brief Initialise response sender
 */
void sender_init (void)
{
	flag_packet_to_send = false;
}

/**
 * \brief Main task for the response sender to send out a response packet when it's ready
 */
void sender_task (void)
{
	if (flag_packet_to_send)
	{
		// send the response packet now <TBD>
		transmit_response(packet_transmit_buffer, packet_transmit_buffer[1]);

		// Recycle packet to send after response is transmitted
		flag_packet_to_send = false;
	}
}
