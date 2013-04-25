/**
 * \file 
 *
 * \brief Command Busy State while executing a foreground command
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date 22/04/2013 12:36:03 PM
 * \author victora
 */ 


#ifndef CMD_BUSY_STATE_H_
#define CMD_BUSY_STATE_H_

#include "cmd_state.h"

void transition_to_busy (command_state_ptr state, int cmd);

#endif /* CMD_BUSY_STATE_H_ */