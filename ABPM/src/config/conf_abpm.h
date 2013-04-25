/**
 * \file
 *
 * \brief Configuration for Central BP
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2012
 *
 * \date Created: 12/11/2012 2:16:12 PM
 * \author victora
 */

#ifndef CONF_ABPM_H_
#define CONF_ABPM_H_

#include "asf.h"

#define PWA_MAX_CAPTURE_TIME	(uint8_t)5								// in seconds
#define DEFAULT_SAMPLE_RATE		(uint8_t)128							// samples per sec

#define ADC_BUF_SIZE			(uint16_t)DEFAULT_SAMPLE_RATE*PWA_MAX_CAPTURE_TIME

#define SAMPLING_PERIOD			((float)(1.0 / DEFAULT_SAMPLE_RATE))	// in sec

#define MAIN_CLOCK				BOARD_OSC0_HZ							// in Hz
#define GCLOCK					SAMPLING_RATE							// Generic clock to generate PEVC trigger used for DAC
#define OSC32_DIVISOR			((32000 / GCLOCK / 2) - 1)				// Divisor for 32kHz clock where div = (1/2 * (f of src) / (f of gclk)) - 1

#define PBA_PBSEL				(CONFIG_SYSCLK_PBA_DIV - 1)				// Divisor compensated for +1 which added below to get the actually divisor
#define MAIN_DIVISOR			(1 << (PBA_PBSEL + 1))					// Get divisor from PBxSEL:PBSEL, ie 2 ** (PBSEL + 1)
#define CLOCK_DACIFB			(float)(MAIN_CLOCK / MAIN_DIVISOR)		// where fPBx = fMain / divisor
#define DACIFB_DIVISOR			128										// Use the highest divisor wrt hardware limitation to scale down PBA for CLK_DACIFB clock
#define DAC_PRESCALER_CLOCK		(float)(CLOCK_DACIFB / DACIFB_DIVISOR)	// PBB clock divided with max divisor
#define CLOCK_ADC_INTERVAL		3905									// PBC clock @ 1MHz makes ADC to sample every 1/(interval+1) usec, e.g 3905+1 for ~256 Hz; 7812+1 for ~128 Hz

//! ADC Task Configuration Parameters
// Number of conversions per sequence
#define ADC_NUMBER_OF_CONV_SEQ0	1
// Connection of the external analog input
#define ADC_EXT_INPUT_INP		AVR32_ADCIFA_INP_ADCIN2
#define ADC_EXT_INPUT_INN		AVR32_ADCIFA_INN_GNDANA
#define ADC_EXT_INPUT_PIN		AVR32_ADCIN2_PIN						// Connected to external analog cuff signal from SunTech
#define ADC_EXT_INPUT_FUNCTION	AVR32_ADCIN2_FUNCTION					// Input function for external analog signal
// PDCA Channel for ADC SEQ0
#define ADC_PDCA_CHANNEL_SEQ0	0

// Abort flag to stop calculation.
static volatile bool flag_abort = false;

// Common error codes for 1 byte max.
static volatile uint8_t Common_Error_Code = 0;
typedef enum
{
	PWA_CALCULATION_FAILED = 1,
	COMMON_ERROR_CODE_END = 255 // Make sure common error code less than 255.
}common_error_code_t;

#endif /* CONF_ABPM_H_ */