/*
 * test_CheckDownloadedImage.h
 *
 * Created: 13/03/2014 2:18:32 PM
 *  Author: victora
 */ 


#ifndef TEST_CHECKDOWNLOADEDIMAGE_H_
#define TEST_CHECKDOWNLOADEDIMAGE_H_


#include <asf.h>
#include "dataflash_if.h"

void run_check_valid_image(const struct test_case *test);

// Define all the test cases.
DEFINE_TEST_CASE(check_valid_image, NULL, run_check_valid_image, NULL, "Check valid image in DataFlash");


#endif /* TEST_CHECKDOWNLOADEDIMAGE_H_ */