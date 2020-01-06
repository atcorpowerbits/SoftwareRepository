/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "test_image_to_df.h"
#include "power_clocks_lib.h" // for pcl_switch_to_osc
#include "print_funcs.h" // for init_dbg_rs232
#include "sysclk.h" // for sysclk_init
#include "usart_if.h" // for print_debug_append

int main (void)
{
	board_init();

	// Switch main clock to external oscillator 0 (crystal).
	sysclk_init();
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);

	// Initialize the debug USART module.
	init_dbg_rs232(FOSC0);

	df_interface_init();
	
	//print_debug_append("***** Unit Test Write to DF *****\r\n");

	// Put test case addresses in an array.
	DEFINE_TEST_ARRAY(image_to_df_tests) =
	{
		&write_image_to_dataflash,
	};

	// Define the test suite.
	DEFINE_TEST_SUITE(image_to_df_tests_suite, image_to_df_tests, "Write image(error state) to DataFlash unit tests suite");
	
	// Run all tests in the test suite.
	test_suite_run(&image_to_df_tests_suite);
	
	while (true)
	{
		// no operation, delay one machine cycle.
		__asm__("nop");
	};
}