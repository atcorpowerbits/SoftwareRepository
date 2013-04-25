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

#define MAX_PACKET_SIZE 11

void listener_task (void);
void listener_init (void);

#endif /* LISTENER_H_ */