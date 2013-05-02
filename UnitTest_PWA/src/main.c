/**
 * \file
 *
 * \brief main method
 * \author Author: yoonl
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include "../../ABPM/src/usart/usart_rxtx.h"
#include "test_buffer.h"
uint16_t PWA_Error_Code = 0;

int main (void)
{
	board_init();
	usart_rs232_mode_init();
	
	// Put test case addresses in an array.
	DEFINE_TEST_ARRAY(PWA_tests) =
	{
		&ADCBuffer_init_test,
		&ADCBuffer_final_test,
	};

	// Define the test suite.
	DEFINE_TEST_SUITE(PWA_suite, PWA_tests, "PWA unit test suite");
	
	// Run all tests in the test suite.
	test_suite_run(&PWA_suite);
	
	while (true)
	{
		// no operation, delay one machine cycle.
		__asm__("nop");
	};
}
