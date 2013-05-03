/**
 * \file 
 *
 * \brief Send a response from CBP to BP
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: Created: 26/04/2013 09:47:05 AM
 * \author victora
 */ 

#ifndef SENDER_H_
#define SENDER_H_

#define MAX_RESPONSE_PACKET_SIZE 255 //<TBD> Find the actual biggest response packet length
#define RESPONSE_PACKET_OVERHEAD 4 //including CRC
#define RESPONSE_LENGTH_SINGLE_DATA (RESPONSE_PACKET_OVERHEAD + 1)

#define CMD_START_BYTE		'*' // 0x2A
#define RESPONSE_START_BYTE	'+' // 0x2B
#define ABORT_RESPONSE		'A' // 0x41
#define BUSY_RESPONSE		'B' // 0x42
#define ERROR_RESPONSE		'E' // 0x45
#define K_OK_RESPONSE		'K' // 0x4B
#define UNDEFINED_RESPONSE	'N' // 0x4E
#define O_OK_RESPONSE		'O' // 0x4F
#define SLEEPING_RESPONSE	'S' // 0x53
#define TIMEOUT_RESPONSE	'T' // 0x54

void sender_task (void);
void sender_init (void);
void send_busy (uint8_t cmd);
void send_undefined (uint8_t cmd);
void send_error (uint8_t cmd);
void send_aborted (uint8_t cmd);
void send_o_ok (uint8_t cmd);
void send_k_ok (uint8_t cmd);
void send_timeout (uint8_t cmd);
void send_sleeping (uint8_t cmd);
void send_status (void);
void send_config (void);

#endif /* SENDER_H_ */