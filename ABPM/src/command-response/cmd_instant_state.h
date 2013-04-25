/**
 * \file 
 *
 * \brief Command Instant Response State to execute a background command
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 22/04/2013 5:04:27 PM
 * \author victora
 */ 

#ifndef CMD_INSTANT_STATE_H_
#define CMD_INSTANT_STATE_H_

#include "cmd_state.h"

void transition_to_instant_response (command_state_ptr state, int cmd);

#endif /* CMD_INSTANT_STATE_H_ */