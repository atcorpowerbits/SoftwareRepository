/*
 * test_image_to_df.h
 *
 * Created: 13/03/2014 2:18:32 PM
 *  Author: victora
 */ 


#ifndef TEST_IMAGE_TO_DF_H_
#define TEST_IMAGE_TO_DF_H_


#include <asf.h>
#include "dataflash_if.h"

void run_write_image_to_df(const struct test_case *test);

// Define all the test cases.
DEFINE_TEST_CASE(write_image_to_dataflash, NULL, run_write_image_to_df, NULL, "Write image(error state) to DataFlash");


#endif /* TEST_IMAGE_TO_DF_H_ */