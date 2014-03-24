/*
 * \file
 *
 * \brief Unit Tests to check downloaded image
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 13/03/2014 2:18:32 PM
 * \author victora
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

/**
 * \brief Negative Tests to check downloaded CBP Firmware image header in DataFlash
 * \param[in] test - structure test_case
 */
void run_check_invalid_image_header (const struct test_case *test)
{
	uint8_t pageBuffer[DF_PAGE_SIZE];
	df_error_code_t df_status;
	transition_t nextTransition;
	bool expected;
	cbxHeader_t * testHeader;

	// Change the CBX header checksum for negative unit test
	df_status = df_read_page(CBX_START_PAGE, pageBuffer, DF_PAGE_SIZE);
	test_assert_true(test, DF_RW_SUCCESS == df_status, "Failed to read CBX header from DataFlash\r\n");
	testHeader = (cbxHeader_t *)pageBuffer;
	testHeader->crc8 = ~testHeader->crc8;
	df_status = df_write_page(CBX_START_PAGE, pageBuffer, DF_PAGE_SIZE);
	test_assert_true(test, DF_RW_SUCCESS == df_status, "Failed to change CBX header in DataFlash\r\n");

	// Read and check the corrupted CBX header from the downloaded image in the DataFlash
	nextTransition = CheckDownloadedImage();
	test_assert_true(test, nextTransition == TRANSITION_INVALID_IMAGE, "Failed to detect the corrupted CBX header in DataFlash\r\n");

	// Restore the original CBX header checksum in DataFlash
	testHeader->crc8 = ~testHeader->crc8;
	df_status = df_write_page(CBX_START_PAGE, pageBuffer, DF_PAGE_SIZE);
	test_assert_true(test, DF_RW_SUCCESS == df_status, "Failed to change CBX header in DataFlash\r\n");

	// Make sure the downloaded image is intact in DataFlash
	nextTransition = CheckDownloadedImage();
	test_assert_true(test, nextTransition == TRANSITION_VALID_IMAGE, "Failed to restore downloaded image in DataFlash\r\n");
}

/**
 * \brief Negative Tests to check downloaded CBP Firmware image payload in DataFlash
 * \param[in] test - structure test_case
 */
void run_check_invalid_image_payload (const struct test_case *test)
{
	uint8_t pageBuffer[DF_PAGE_SIZE];
	df_error_code_t df_status;
	transition_t nextTransition;
	bool expected;
	cbxHeader_t * theHeader = GetCbxHeader();

	// Change the CBX payload CRC32 in RAM for negative unit test
	expected = ReadCbxHeader();
	test_assert_true(test, expected, "Failed to read CBX header page from DataFlash\r\n");
	
	theHeader->eCRC32.u32 = ~theHeader->eCRC32.u32;

	// Check the CBX payload in the DataFlash with the corrupted header 
	nextTransition = CheckEncyptedPayloadCRC();
	test_assert_true(test, nextTransition == TRANSITION_INVALID_IMAGE, "Failed to detect the corrupted CBX payload in DataFlash\r\n");
}
