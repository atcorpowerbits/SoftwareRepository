/**
 * \file
 * \brief Unit Test buffer.c
 * \date Created: 24/04/2013 11:08:50 AM
 * \author Author: yoonl
 */ 


#ifndef TEST_BUFFER_H_
#define TEST_BUFFER_H_

#include <asf.h>
#include "../../ABPM/src/pwa/pwa_data.h"

extern unsigned int GetAvailableMemory(void);
void cleanup_adc_buffer(const struct test_case *test);
void run_ADCBuffer_init_test(const struct test_case *test);
void run_ADCBuffer_final_test(const struct test_case *test);


// Define all the test cases.
DEFINE_TEST_CASE(ADCBuffer_init_test, NULL, run_ADCBuffer_init_test, cleanup_adc_buffer, "ADCBuffer_init_test");
DEFINE_TEST_CASE(ADCBuffer_final_test, NULL, run_ADCBuffer_final_test, NULL, "ADCBuffer_final_test");

#endif /* TEST_BUFFER_H_ */