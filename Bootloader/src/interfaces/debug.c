/*
 * \file
 *
 * \brief Debugging interface
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 6/03/2014 5:20:49 PM
 * \author victora
 */ 

#include <asf.h>
#include "debug.h"

void debug_msg (const char *str)
{
	// Redirect to print debugging message
	print_dbg(str);
//va:POC	// Invoke the USART driver to transmit the input string with the given USART.
//va:POC	usart_write_line(DBG_USART, str);
}

