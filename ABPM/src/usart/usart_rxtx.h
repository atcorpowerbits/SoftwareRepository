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
#define PBC_TARGET_PBCCLK_FREQ_HZ	FOSC0  // PBC clock target frequency, in Hz for USART4

#if BOARD == UC3C_EK || BOARD == USER_BOARD
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

// for BP-CBP command/response serial comms
#if BOARD == UC3C_EK

#  define CMD_USART                 (&AVR32_USART4)
#  define CMD_USART_RX_PIN          AVR32_USART4_RXD_PIN
#  define CMD_USART_RX_FUNCTION     AVR32_USART4_RXD_FUNCTION
#  define CMD_USART_TX_PIN          AVR32_USART4_TXD_PIN
#  define CMD_USART_TX_FUNCTION     AVR32_USART4_TXD_FUNCTION
#  define CMD_USART_CLOCK_MASK      AVR32_USART4_CLK_PBC
#  define CMD_PDCA_CLOCK_HSB        AVR32_PDCA_CLK_HSB
#  define CMD_USART_PBx_FREQ_HZ     PBC_TARGET_PBCCLK_FREQ_HZ // USART0 runs on PBC clock
#  if UC3C_REVC
#    define CMD_PDCA_CLOCK_PB       AVR32_PDCA_CLK_PBB
#  else
#    define CMD_PDCA_CLOCK_PB       AVR32_PDCA_CLK_PBC
#  endif

#elif BOARD == USER_BOARD

#  define CMD_USART                 (&AVR32_USART0)
#  define CMD_USART_RX_PIN          AVR32_USART0_RXD_PIN
#  define CMD_USART_RX_FUNCTION     AVR32_USART0_RXD_FUNCTION
#  define CMD_USART_TX_PIN          AVR32_USART0_TXD_PIN
#  define CMD_USART_TX_FUNCTION     AVR32_USART0_TXD_FUNCTION
#  define CMD_USART_CLOCK_MASK      AVR32_USART0_CLK_PBA
#  define CMD_PDCA_CLOCK_HSB        AVR32_PDCA_CLK_HSB
#  define CMD_USART_PBx_FREQ_HZ     PBA_TARGET_PBACLK_FREQ_HZ // USART0 runs on PBA clock
#  if UC3C_REVC
#    define CMD_PDCA_CLOCK_PB       AVR32_PDCA_CLK_PBB
#  else
#    define CMD_PDCA_CLOCK_PB       AVR32_PDCA_CLK_PBC
#  endif

#endif

#if !defined(PBA_USART)             || \
	!defined(PBA_USART_RX_PIN)      || \
	!defined(PBA_USART_RX_FUNCTION) || \
	!defined(PBA_USART_TX_PIN)      || \
	!defined(PBA_USART_TX_FUNCTION)
#  error The USART configuration to use in this PBA is missing.
#endif

#if !defined(CMD_USART)             || \
!defined(CMD_USART_RX_PIN)      || \
!defined(CMD_USART_RX_FUNCTION) || \
!defined(CMD_USART_TX_PIN)      || \
!defined(CMD_USART_TX_FUNCTION)
#  error The CMD_USART configuration to use in this PBC is missing.
#endif

static const gpio_map_t USART_GPIO_MAP =
{
	{PBA_USART_RX_PIN, PBA_USART_RX_FUNCTION},
	{PBA_USART_TX_PIN, PBA_USART_TX_FUNCTION},
	{CMD_USART_RX_PIN, CMD_USART_RX_FUNCTION},
	{CMD_USART_TX_PIN, CMD_USART_TX_FUNCTION}
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

// USART options for BP-CBP command/response serial comms
static const usart_options_t CMD_USART_OPTIONS =
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