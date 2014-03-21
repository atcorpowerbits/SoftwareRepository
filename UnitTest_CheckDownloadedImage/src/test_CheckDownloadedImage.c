/*
 * test_CheckDownloadedImage.c
 *
 * Created: 13/03/2014 2:18:01 PM
 *  Author: victora
 */ 

#include "test_CheckDownloadedImage.h"
#include "states.h"

/**
 * \brief Check downloaded CBP Firmware image in DataFlash
 * \param[in] test - structure test_case
 */
void run_check_valid_image (const struct test_case *test)
{
	transition_t nextTransition;

	nextTransition = CheckDownloadedImage();
	test_assert_true(test, nextTransition == TRANSITION_VALID_IMAGE, "Failed to validate downloaded image in DataFlash\r\n");
}
