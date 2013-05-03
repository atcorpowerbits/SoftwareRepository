/**
 * \file 
 *
 * \brief Listen a command from BP and take action
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: Created: 22/04/2013 10:26:05 AM
 * \author victora
 */ 

#ifndef LISTENER_H_
#define LISTENER_H_

#define MAX_CMD_PACKET_SIZE 11

#include "cmd_state.h"

/**
 * \brief Current command state of the command state machine
 */
typedef struct {
	command_state_t current_state;
} cbp_command_t, *cbp_command_ptr;

void listener_task (void);
void listener_init (void);

#endif /* LISTENER_H_ */