/*
 * \file
 *
 * \brief Unit Tests Header to check downloaded image
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 13/03/2014 2:18:32 PM
 * \author victora
 */ 


#ifndef TEST_CHECKDOWNLOADEDIMAGE_H_
#define TEST_CHECKDOWNLOADEDIMAGE_H_


#include <asf.h>
#include "dataflash_if.h"

void run_check_valid_image(const struct test_case *test);
void run_check_invalid_image_header(const struct test_case *test);
void run_check_invalid_image_payload(const struct test_case *test);

// Define all the test cases.
DEFINE_TEST_CASE(check_valid_image, NULL, run_check_valid_image, NULL, "Check valid image in DataFlash");
DEFINE_TEST_CASE(check_invalid_image_header, NULL, run_check_invalid_image_header, NULL, "Check invalid image header in DataFlash");
DEFINE_TEST_CASE(check_invalid_image_payload, NULL, run_check_invalid_image_payload, NULL, "Check invalid image payload in DataFlash");


#endif /* TEST_CHECKDOWNLOADEDIMAGE_H_ */