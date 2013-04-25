/**
 * \file
 *
 * \brief ADC Task
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2012
 *
 * \date Created: 12/11/2012 3:23:27 PM
 * \author victora
 */

#include "board.h"
#include "gpio.h"
#include "adcifa.h"
#include "pdca.h"
#include "sysclk.h"
#include "conf_abpm.h"
#include "pwa\buffer.h"
#include "adc_task.h"

// Trigger process state
#define ADC_TRIGGER_SYNC_NONE             0
#define ADC_TRIGGER_SYNC_MIN              1
#define ADC_TRIGGER_SYNC_ORDER            2

// Prototypes
void pdca_init(void);

// ADCIFA IP registers address
volatile avr32_adcifa_t *adcifa = &AVR32_ADCIFA;

// Boolean to trigger end of PDCA transfer
volatile bool flag_end_of_acquisition = false;

// Boolean to start acquisition trigger
volatile int32_t trigger_process_state = ADC_TRIGGER_SYNC_NONE;

// ADC Configuration
adcifa_opt_t adc_config_t = {
	.frequency                  = 1000000,            // ADC frequency (Hz)
	.reference_source           = ADCIFA_REF06VDD,    // Reference source
	.sample_and_hold_disable    = false,              // Sample and Hold enabled
	.single_sequencer_mode      = false,              // Dual sequencer mode
	.free_running_mode_enable   = false,              // Free running not used
	.sleep_mode_enable          = false               // Sleep mode not used
};

// Sequencer 0 Configuration
adcifa_sequencer_opt_t adc_sequencer0_config_t = {
	.convnb                     = ADC_NUMBER_OF_CONV_SEQ0,  // nb channel conv.
	.resolution                 = ADCIFA_SRES_12B,          // 12-bit cuff signal data resolution
	.trigger_selection          = ADCIFA_TRGSEL_ITIMER,     // Timer Trigger
	.start_of_conversion        = ADCIFA_SOCB_ALLSEQ,       // All Conv. in seq
	.sh_mode                    = ADCIFA_SH_MODE_STANDARD,  // No Oversampling
	.half_word_adjustment       = ADCIFA_HWLA_NOADJ,        // Right Alignment
	.software_acknowledge       = ADCIFA_SA_NO_EOS_SOFTACK  // No Soft. Ack.
};

// Conversions in the sequencer configuration
// sequencer 0 conversion channels
adcifa_sequencer_conversion_opt_t
adc_conversion_sequencer0_t[ADC_NUMBER_OF_CONV_SEQ0] = {
	{ // 1st conversion
		.channel_p = ADC_EXT_INPUT_INP,             // Positive Channel
		.channel_n = ADC_EXT_INPUT_INN,             // Negative Channel
		.gain      = ADCIFA_SHG_1                   // No Gain (x1)
	}
};

// Initialize the PDCA transfer channel structure
static pdca_channel_options_t pdca_channel0_config_t = {
	.addr = (void *)NULL,                           // Buffer address to be assigned at run time
	.pid = AVR32_ADCIFA_PDCA_ID_RX_CH0,             // Data from ADC SEQ0
	.size = ADC_BUF_SIZE,                           // Transfer counter
	.r_addr = NULL,                                 // No reload address
	.r_size = 0,                                    // No reload counter
	.transfer_size = PDCA_TRANSFER_SIZE_HALF_WORD   // 16-bit transfer
};

// Initialize the ADCIFA Window Monitor Structure
volatile adcifa_window_monitor_opt_t adc_window_config_t = {
	.mode = ADCIFA_WINDOW_MODE_ABOVE,               // Default init mode
	.low_threshold = 0,                             // Default LT
	.high_threshold = 0,                            // Default HT
	.source_index = ADC_NUMBER_OF_CONV_SEQ0-1       // Index
};

/*! \brief The ADCIFA window monitor interrupt handler.
*
*/
#if !defined(AVR32_ADCIFA_IRQ_GROUP)
#define AVR32_ADCIFA_IRQ_GROUP          36
#else
#warning "Duplicate define(s) to remove from the ASF"
#endif
ISR(adc_int_window_handler, AVR32_ADCIFA_IRQ_GROUP, 0)
{
	// Here only sequencer 0 is enabled so the interrupt source is not checked
	switch (trigger_process_state) {
		case ADC_TRIGGER_SYNC_MIN: // Min level found
		if (adc_window_config_t.high_threshold > 0) {
			// Start order synchronization step only if
			// trig > min signal value
			trigger_process_state = ADC_TRIGGER_SYNC_ORDER;
			adc_window_config_t.low_threshold = 0;
			// Trig when sample > LT
			adc_window_config_t.mode = ADCIFA_WINDOW_MODE_ABOVE;
			adcifa_configure_window_monitor(adcifa, ADCIFA_SEQ0,
			(adcifa_window_monitor_opt_t *)&adc_window_config_t);
		}
		else {
			// Restart min level search
			adc_window_config_t.high_threshold = 0; // Stay in sync process
			adcifa_configure_window_monitor(adcifa, ADCIFA_SEQ0,
			(adcifa_window_monitor_opt_t *)&adc_window_config_t);
		}
		break;
		case ADC_TRIGGER_SYNC_ORDER:        // Order level found
		// Launch acquisition now
		pdca_enable(ADC_PDCA_CHANNEL_SEQ0);
		gpio_clr_gpio_pin(LED0_GPIO); // Let's switch on LED0 when sampling
		adcifa_disable_interrupt(adcifa, AVR32_ADCIFA_WM0_MASK);
		break;
		default:
		break;
	}
	// Clear any pending interrupt
	adcifa_clear_interrupt(adcifa, AVR32_ADCIFA_WM0_MASK);
}

/*! \brief The PDCA interrupt handler.
 *
 * The handler disables the PDCA transfer.
 * The interrupt will happen each time the transfer is completed.
 */
ISR(pdca_int_handler_seq0, AVR32_PDCA_IRQ_GROUP0, 0)
{
	gpio_set_gpio_pin(LED0_GPIO); // switch off LED0
	// Re-initialize the PDCA channel for next acquisition
	pdca_disable(ADC_PDCA_CHANNEL_SEQ0);
	pdca_init_channel(ADC_PDCA_CHANNEL_SEQ0, &pdca_channel0_config_t);
	pdca_enable_interrupt_transfer_complete(ADC_PDCA_CHANNEL_SEQ0);
	flag_end_of_acquisition = true;
}

/*!
 * \brief Configure the PDCA and register its interrupt pdca_int_handler
 */
void pdca_init(void)
{
	// Initialize PDCA channel with the pdca_options
	pdca_channel0_config_t.addr = (void *)adc_buffer;
	pdca_init_channel(ADC_PDCA_CHANNEL_SEQ0, &pdca_channel0_config_t);

	// register Register pdca_int_handler_seq0 interrupt on level 0
	irqflags_t flags = cpu_irq_save();
	irq_register_handler(pdca_int_handler_seq0,
					AVR32_PDCA_IRQ_0, 0);
	cpu_irq_restore(flags);

	// Enable the PDCA interrupt each time the transfer is complete,
	// i.e. each time a data buffer is ready
	pdca_enable_interrupt_transfer_complete(ADC_PDCA_CHANNEL_SEQ0);
}

/*!
 * \brief main function : initialization and loop to display ADC values
 */
void adc_task_init( void )
{
	// GPIO pin/adc-function map.
	static const gpio_map_t adc_io_map_t = {
		{AVR32_ADCREF0_PIN,AVR32_ADCREF0_FUNCTION},
		{AVR32_ADCREFP_PIN,AVR32_ADCREFP_FUNCTION},
		{AVR32_ADCREFN_PIN,AVR32_ADCREFN_FUNCTION},
		{ADC_EXT_INPUT_PIN, ADC_EXT_INPUT_FUNCTION}
	};

	AVR32_HMATRIXB.mcfg[AVR32_HMATRIXB_MASTER_CPU_INSN] = 0x1; //what is this for?

	// Assign and enable GPIO pins to the ADC function.
	gpio_enable_module(adc_io_map_t, sizeof(adc_io_map_t) / sizeof(adc_io_map_t[0]));

	// Get ADCIFA factory Configuration
	adcifa_get_calibration_data(adcifa, &adc_config_t);

	// Configure ADCIFA core
	adcifa_configure(adcifa, &adc_config_t, sysclk_get_pbc_hz());

	// Configure ADCIFA sequencer 0 & 1
	adcifa_configure_sequencer(adcifa, ADCIFA_SEQ0, &adc_sequencer0_config_t,
			adc_conversion_sequencer0_t);

	// Configure the trigger monitor
	trigger_process_state = ADC_TRIGGER_SYNC_MIN;           // Start sync search
	adc_window_config_t.mode = ADCIFA_WINDOW_MODE_BELOW;// Trig when sample < HT
	adc_window_config_t.high_threshold = 0;             // Sweep threshold
	adcifa_configure_window_monitor(adcifa, ADCIFA_SEQ0,
	(adcifa_window_monitor_opt_t *)&adc_window_config_t);

	// register Register adc_int_window_handler interrupt on level 0
	irqflags_t flags = cpu_irq_save();
	irq_register_handler(adc_int_window_handler,
			AVR32_ADCIFA_WINDOW_IRQ, 0);
	cpu_irq_restore(flags);

	// Clear any pending interrupt
	adcifa_clear_interrupt(adcifa, AVR32_ADCIFA_WM0_MASK);
	adcifa_enable_interrupt(adcifa, AVR32_ADCIFA_WM0_MASK);

	// Start the internal timer to count interval set to trigger conv.
	adcifa_start_itimer(adcifa, CLOCK_ADC_INTERVAL);
	
	// Initialize the PDCA
	pdca_init();

	// Start a first acquisition now
	pdca_enable(ADC_PDCA_CHANNEL_SEQ0);
}

