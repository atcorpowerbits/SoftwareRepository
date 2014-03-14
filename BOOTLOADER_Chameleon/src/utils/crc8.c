/**
 * \file
 *
 * \brief Calculate CRC-8
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 26/04/2013 10:59:03 AM
 * \author victora
 */ 

//_____ I N C L U D E S ____________________________________________________
#include "crc8.h"

//_____ M A C R O S ________________________________________________________

//_____ D E F I N I T I O N S ______________________________________________

//_____ D E C L A R A T I O N S ____________________________________________

/**
 * \brief Calculate crc using (0x100 - modulo 256)
 * param[in] buffer Buffer contents for crc calculation
 * param[in] len Length of the buffer for crc calculation
 * \return Calculated crc for the given buffer contents
 */
uint8_t calculate_crc (uint8_t * buffer, int len)
{
	uint8_t modulo256;
	uint16_t sum = 0;
	
	for (int i = 0; i < len; i++)
	{
		sum += buffer[i];
	}
	modulo256 = sum % 256;
	return (0x100 - modulo256);
}
