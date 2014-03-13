/*
 * usart_if.c
 *
 * Created: 13/03/2014 4:58:55 PM
 *  Author: victora
 */ 

#include <stdarg.h>
#include <usart.h>
#include <stdio.h> // for vsnprintf
#include "usart_if.h"

#define MAX_BUFFER_SIZE		(uint16_t)(1024)

/**
 * \brief Print to debug terminal with the time stamp.
 */
void print_debug_append (char *msg, ...)
{
	va_list args;
	char szBuf[MAX_BUFFER_SIZE] = {0};

	va_start(args, msg);
	// vsnprintf() will not write more than MAX_BUFFER_SIZE including the trailing '\0', it will truncate it automatically if overflow.
	vsnprintf(szBuf, MAX_BUFFER_SIZE, msg, args);
	va_end(args);

	// usart_interface_send_msg_cpy(DEBUG_TERM_PORT, (uint8_t *)szBuf, strlen(szBuf));
	// avoid using usart_interface_send_msg_cpy to transmit via PDCA, until it is made compatible with AST
	usart_write_line(DBG_USART, szBuf);
}

