/**
 * \file
 *
 * \brief Calculate CRC-8
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 26/04/2013 11:00:43 AM
 * \author victora
 */ 

#ifndef CRC8_H_
#define CRC8_H_

#include <compiler.h>

#define CRC_TABLE_SIZE 256

//extern void populate_crc_table (void);
extern uint8_t calculate_crc (uint8_t * buffer, int len);

#endif /* CRC8_H_ */