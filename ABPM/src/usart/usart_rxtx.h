/*
 * usart_rxtx.h
 *
 * Created: 10/10/2012 9:27:04 AM
 *  Author: yoonl
 */ 


#ifndef USART_RXTX_H_
#define USART_RXTX_H_

#include "board.h"
#include "usart.h"
#include "gpio.h"
#include "power_clocks_lib.h"

#define PBA_TARGET_PBACLK_FREQ_HZ	FOSC0  // PBA clock target frequency, in Hz

#if BOARD == UC3C_EK
#  define PBA_USART                 (&AVR32_USART2)
#  define PBA_USART_RX_PIN          AVR32_USART2_RXD_0_1_PIN
#  define PBA_USART_RX_FUNCTION     AVR32_USART2_RXD_0_1_FUNCTION
#  define PBA_USART_TX_PIN          AVR32_USART2_TXD_0_1_PIN
#  define PBA_USART_TX_FUNCTION     AVR32_USART2_TXD_0_1_FUNCTION
#  define PBA_USART_CLOCK_MASK      AVR32_USART2_CLK_PBA
#  define PBA_PDCA_CLOCK_HSB        AVR32_PDCA_CLK_HSB
#  if UC3C_REVC
#    define PBA_PDCA_CLOCK_PB       AVR32_PDCA_CLK_PBB
#  else
#    define PBA_PDCA_CLOCK_PB       AVR32_PDCA_CLK_PBC
#  endif
#endif

#if !defined(PBA_USART)             || \
	!defined(PBA_USART_RX_PIN)      || \
	!defined(PBA_USART_RX_FUNCTION) || \
	!defined(PBA_USART_TX_PIN)      || \
	!defined(PBA_USART_TX_FUNCTION)
#  error The USART configuration to use in this PBA is missing.
#endif

static const gpio_map_t USART_GPIO_MAP =
{
	{PBA_USART_RX_PIN, PBA_USART_RX_FUNCTION},
	{PBA_USART_TX_PIN, PBA_USART_TX_FUNCTION}
};

// USART options.
static const usart_options_t USART_OPTIONS =
{
	.baudrate     = 57600,
	.charlength   = 8,
	.paritytype   = USART_NO_PARITY,
	.stopbits     = USART_1_STOPBIT,
	.channelmode  = USART_NORMAL_CHMODE
};

void usart_rs232_mode_init(void);
void print_debug(char *msg, ...);

#endif /* USART_RXTX_H_ */