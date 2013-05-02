/**
 * \file
 * \brief Unit Test buffer.c
 * \date Created: 24/04/2013 11:08:50 AM
 * \author Author: yoonl
 */

#include "test_buffer.h"
#include "../../ABPM/src/pwa/buffer.h"

/**
 * \brief Clean up memory for adc_buffer after all tests
 * \param[in] test - structure test_case
 */
void cleanup_adc_buffer(const struct test_case *test)
{
	ADCBuffer_final();
}

/**
 * \brief Testing ADCBuffer_init()
 * \param[in] test - structure test_case
 */
void run_ADCBuffer_init_test(const struct test_case *test)
{
	bool status;
	
	status = ADCBuffer_init();
	test_assert_true(test, status, "Not enough memory for adc_buffer. Clean up memory and then test again.\r\n");
	
	// Testing out of memory scenario.
	unsigned char *dummy = NULL;
	int x = 0;
	ADCBuffer_final();
	x = GetAvailableMemory();
	// Add more bytes here because optimization will give little more available memory.
	x += 300;
	dummy = malloc(x);
	if (dummy != NULL)
	{
		status = ADCBuffer_init();
		test_assert_false(test, status, "Negative test failed, comsume more memory and then test again. Current used: %d bytes.\r\n", x);
		free(dummy);
	}
}

/**
 * \brief Testing ADCBuffer_final()
 * \param[in] test - structure test_case
 */
void run_ADCBuffer_final_test(const struct test_case *test)
{
	bool status;
	
	ADCBuffer_init();
	ADCBuffer_final();
	status = (adc_buffer == NULL);
	test_assert_true(test, status, "Failed to free memory.\r\n");
}

/**
 * \brief Get available memory in general
 * \return Available memory size
 */
unsigned int GetAvailableMemory(void)
{
	unsigned int size = 65535;
	unsigned char *buf = NULL;

	while (--size > 0 && (buf = (unsigned char *)malloc(size)) == NULL);
	if (buf)
	{
		free(buf);
		buf = NULL;
	}
	return size;
}
