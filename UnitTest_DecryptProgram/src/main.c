/**
 * \file
 *
 * \brief Unit Test for decrypt and program project.
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
#include "power_clocks_lib.h" // for pcl_switch_to_osc
#include "print_funcs.h" // for init_dbg_rs232
#include "sysclk.h" // for sysclk_init
#include "usart_if.h" // for print_debug_append
#include "dataflash_if.h"
#include "decrypt_program.h"

int main (void)
{
	board_init();

	// Switch main clock to external oscillator 0 (crystal).
	sysclk_init();
	pcl_switch_to_osc(PCL_OSC0, FOSC0, OSC0_STARTUP);

	// Initialize the debug USART module.
	init_dbg_rs232(FOSC0);

	df_interface_init();
	
	// WARNING: This Unit Test project requires the CBX image in DataFlash.
	// WriteToMcuFlash_PartialLastPage_test writes dummy CBX image to DataFlash, this test should be called in the beginning.
	// Put test case addresses in an array.
	DEFINE_TEST_ARRAY(DecryptProgram) =
	{
		&WriteToMcuFlash_PartialLastPage_test,
		&CheckCbpBinaryImage_test,
		&EraseMcuFlash_test,
		&WriteToMcuFlash_test,
		&ProgramAndVerifyMCU_test,
		&CheckMcuFlash_test,
		&Decrypt_test,
		&EraseCbpConfigRec_test,
	};

	// Define the test suite.
	DEFINE_TEST_SUITE(DecryptProgram_suite, DecryptProgram, "Decrypt and program CBP image unit tests suite");
	
	// Run all tests in the test suite.
	test_suite_run(&DecryptProgram_suite);
	
	while (true)
	{
		// no operation, delay one machine cycle.
		__asm__("nop");
	};
}
