/**
 * \file
 *
 * \brief Encrypt/Decrypt CBP image.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 4/04/2014 4:08:48 PM
 * \author yoonl
 */

#include "decrypt_program.h"
#include "enc_dec.h"
#include "states.h"
#include "usart_if.h"
#include "boot.h"
#include <string.h>
#include "dataflash_if.h"

// The demo cbp image size used in this unit test is slightly higher than AVR32_FLASHC_PAGE_SIZE(512bytes) to
// make the last page is partial in MCU Flash block.
// It is designed to work with a specific MCU Flash block size.
const unsigned char cbxDemoContents[] =
{
	0x00, 0x00, 0x01, 0x00, 0x20, 0x02, 0x00, 0x00,
	0xA8, 0x34, 0x31, 0x9D, 0x61, 0x62, 0x70, 0x6D,
	0x43, 0x42, 0x50, 0xBE, 0x73, 0xF6, 0x1C, 0x7A,
	0x0E, 0xE4, 0x70, 0x22, 0x5D, 0xD3, 0x2C, 0x48,
	0x48, 0xDB, 0xC4, 0x78, 0xF6, 0x74, 0x3F, 0x29,
	0x4D, 0x65, 0xEE, 0x4B, 0xFA, 0x55, 0xC1, 0x0D,
	0xF2, 0x17, 0xA5, 0xEA, 0x7A, 0xF8, 0x04, 0xED,
	0xB0, 0x4E, 0x77, 0xD8, 0xC2, 0x61, 0x10, 0x58,
	0x0F, 0xD2, 0x1F, 0x73, 0x3F, 0xA3, 0xFB, 0xC6,
	0xC1, 0xCC, 0xB0, 0xD7, 0x38, 0xF1, 0xC2, 0xE4,
	0x07, 0x11, 0xB1, 0xA1, 0xF0, 0x4D, 0x9A, 0x3B,
	0x21, 0xC1, 0x69, 0xC5, 0xB0, 0xD4, 0xF5, 0x45,
	0xB9, 0xFF, 0x8A, 0xDE, 0x5D, 0x1C, 0xDF, 0x41,
	0x7E, 0x33, 0x95, 0xCC, 0xD1, 0x73, 0xCB, 0x61,
	0x25, 0x11, 0xC5, 0x87, 0xFB, 0x45, 0x81, 0x6A,
	0x78, 0x86, 0x83, 0xB7, 0xB5, 0x5D, 0x02, 0x28,
	0x44, 0x69, 0x46, 0xF5, 0x4D, 0x4D, 0xC7, 0xD6,
	0x06, 0x9A, 0x8D, 0x52, 0x10, 0x6D, 0xB3, 0x22,
	0xA2, 0x2B, 0xFC, 0x1D, 0xDA, 0x9C, 0x69, 0x4F,
	0x89, 0x32, 0x7E, 0xDD, 0xFD, 0x34, 0x65, 0x1B,
	0xC8, 0x5F, 0x57, 0x7C, 0x90, 0xFC, 0xE7, 0xC4,
	0xE5, 0x98, 0x80, 0xBE, 0x31, 0xD7, 0x1E, 0xC4,
	0x7B, 0xAA, 0x2E, 0x25, 0xC0, 0x7B, 0xD3, 0x1B,
	0xA2, 0x79, 0x4F, 0x74, 0x17, 0x57, 0xDB, 0xD9,
	0xFB, 0x8C, 0x1B, 0x80, 0x14, 0x60, 0x55, 0xEA,
	0x3C, 0xE5, 0x0F, 0x5C, 0x47, 0x3F, 0xBA, 0x7E,
	0x89, 0x9B, 0x4B, 0x3E, 0x33, 0xD9, 0xD2, 0x95,
	0x61, 0xB4, 0x00, 0x95, 0x9C, 0xC4, 0xF0, 0xEF,
	0x21, 0xD2, 0x21, 0x3D, 0xA6, 0xDB, 0x7C, 0x6B,
	0x27, 0x63, 0xA7, 0xA7, 0x2A, 0x28, 0x08, 0xB4,
	0xE0, 0x40, 0xEA, 0x66, 0x2F, 0x6F, 0x78, 0x00,
	0xDA, 0x13, 0xA4, 0x8B, 0x5C, 0x11, 0xD3, 0xA8,
	0xCC, 0xEB, 0xB6, 0x12, 0xDD, 0x13, 0x2A, 0xE7,
	0x6E, 0xA8, 0x47, 0xF6, 0xC7, 0x0D, 0xE8, 0x33,
	0xD2, 0x0E, 0x89, 0xA8, 0x6B, 0xD1, 0x35, 0x56,
	0x00, 0x47, 0xAA, 0xB1, 0xD3, 0xA8, 0xE1, 0xB4,
	0xB4, 0xC4, 0xC5, 0x50, 0x4B, 0x0E, 0xB7, 0x3F,
	0x5E, 0x49, 0x14, 0x0A, 0x05, 0x66, 0xE2, 0x77,
	0xCB, 0x67, 0xED, 0x8D, 0xA6, 0x86, 0xC2, 0x72,
	0x90, 0xA2, 0xEB, 0x4A, 0x3C, 0x43, 0x25, 0x16,
	0x97, 0xF0, 0x2C, 0x87, 0xE2, 0x25, 0x84, 0x0D,
	0xEF, 0x58, 0x49, 0xFA, 0x3C, 0x8A, 0xD1, 0x8A,
	0x56, 0x06, 0x2B, 0x3E, 0x82, 0xF1, 0xF1, 0xBB,
	0x67, 0xD4, 0x79, 0x65, 0xE0, 0x75, 0xC0, 0xF7,
	0x6A, 0x53, 0x4C, 0xF2, 0xEA, 0x43, 0x98, 0x70,
	0x77, 0xFC, 0xFD, 0x1C, 0x61, 0xD5, 0x4F, 0x2F,
	0x41, 0xAE, 0xF0, 0x30, 0xAE, 0x06, 0x55, 0xF8,
	0xCE, 0x51, 0x81, 0xD3, 0xF8, 0x95, 0xF1, 0x8D,
	0xB9, 0xBA, 0x07, 0x53, 0x99, 0xB6, 0xE9, 0xEE,
	0x81, 0x1F, 0x63, 0x63, 0x4F, 0xC1, 0x9E, 0x77,
	0xF3, 0x2A, 0x6F, 0x32, 0x8E, 0x59, 0x6E, 0xD5,
	0x9C, 0x8D, 0x9C, 0x11, 0xC2, 0x00, 0x3F, 0x15,
	0x30, 0x27, 0xDC, 0x1A, 0xE9, 0xB7, 0x46, 0x94,
	0xE0, 0x90, 0x74, 0x90, 0x7D, 0x96, 0x0C, 0xA2,
	0x49, 0xE9, 0xE1, 0x71, 0x42, 0x48, 0xF9, 0x75,
	0x8B, 0x2C, 0x5D, 0x49, 0x79, 0xEE, 0x0F, 0x51,
	0x82, 0xAD, 0x77, 0x66, 0x1C, 0xBD, 0xFE, 0x93,
	0x84, 0x81, 0x4F, 0x8B, 0x51, 0xA5, 0x08, 0x85,
	0xC3, 0x75, 0xA1, 0xA4, 0x48, 0x1A, 0x49, 0x3A,
	0xD7, 0x11, 0x4C, 0x62, 0x50, 0x9D, 0xD5, 0x86,
	0x03, 0x41, 0xBA, 0x55, 0x5D, 0xD0, 0x50, 0x94,
	0xB3, 0xA3, 0x30, 0xD9, 0xA3, 0xB6, 0x1A, 0x63,
	0x20, 0x8D, 0xBE, 0x09, 0xA9, 0xD4, 0xD1, 0x65,
	0x14, 0xFF, 0x52, 0x8F, 0x26, 0x3D, 0x2C, 0x8B,
	0x91, 0x9E, 0xAF, 0x71, 0xD5, 0xDC, 0xE3, 0xB7,
	0x55, 0xA0, 0xFE, 0x29, 0x84, 0xC8, 0x23, 0x87,
	0x41, 0x7C, 0x9C, 0x7D, 0xB7, 0xEC, 0x31, 0x93,
	0x38, 0x5C, 0x9D, 0xB4, 0x2A, 0x57, 0x21, 0xDA,
	0x88, 0x97, 0x8E, 0x20, 0x51, 0x49, 0xE6, 0xFC,
	0x9F, 0xB6, 0x4A, 0x02, 0x7A, 0x3D, 0xAB, 0xF6,
	0x72, 0x69, 0x8D, 0x2D,
};

/**
 * \brief General setup for each test case.
 * \param[in] test - structure test_case
 */
void general_setup(const struct test_case *test)
{
	print_debug_append("\r\n");
}

/**
 * \brief General cleanup for each test case.
 * \param[in] test - structure test_case
 */
void general_cleanup(const struct test_case *test)
{
	print_debug_append("\r\n");
}

/**
 * \brief Check CBP binary image from DataFlash.
 * \param[in] test - structure test_case
 */
void run_CheckCbpBinaryImage_test(const struct test_case *test)
{
	bool actual = false;
	cbxHeader_t *cbxHeader;
	
	init_enc_dec_with_key();
	actual = ReadCbxHeader();
	test_assert_true(test, actual, "Failed to read CBX header from DataFlash.\r\n");
	
	actual = CheckCbpBinaryImage();
	test_assert_true(test, actual, "Failed to check CBP binary image from DataFlash.\r\n");
	
	cbxHeader = GetCbxHeader();
	cbxHeader->eSize.u32 -= 1;
	actual = CheckCbpBinaryImage();
	test_assert_false(test, actual, "Failed to validate negative test for checking CBP binary image from DataFlash.\r\n");
}

/**
 * \brief Program and verify CBP binary image test.
 * \param[in] test - structure test_case
 */
void run_ProgramAndVerifyMCU_test(const struct test_case *test)
{
	bool actual = false;
	cbxHeader_t *cbxHeader;
	
	init_enc_dec_with_key();
	cbxHeader = GetCbxHeader();
	
	actual = ReadCbxHeader();
	test_assert_true(test, actual, "Failed to read CBX header from DataFlash.\r\n");
	
	actual = CheckCbpBinaryImage();
	test_assert_true(test, actual, "Failed to check CBP binary image from DataFlash.\r\n");
	
	actual = ProgramAndVerifyMCU();
	test_assert_true(test, actual, "Failed to program CBP image.\r\n");
	
	memset(cbxHeader, 0, sizeof(cbxHeader_t));
	actual = ProgramAndVerifyMCU();
	test_assert_false(test, actual, "Failed to validate negative test for programing CBP image.\r\n");
}

/**
 * \brief Erase MCU Flash test.
 * \param[in] test - structure test_case
 */
void run_EraseMcuFlash_test(const struct test_case *test)
{
	bool actual = false;
	
	actual = EraseMcuFlash();
	test_assert_true(test, actual, "Failed to erase MCU Flash.\r\n");
	
	// Negative test for erasing MCU page.
	SetMcuLastPage(flashc_get_page_count() + 1);
	actual = EraseMcuFlash();
	test_assert_false(test, actual, "Failed to validate negative test to erase MCU Flash.\r\n");
}

/**
 * \brief Write data to MCU Flash test.
 * \param[in] test - structure test_case
 */
void run_WriteToMcuFlash_test(const struct test_case *test)
{
	const uint32_t dummy_data = 0x01020304;
	volatile uint32_t *offset;
	uint8_t data[MCU_READ_WRITE_SIZE] = {0};
	uint8_t buf[MCU_READ_WRITE_SIZE] = {0};
	bool actual = false;
	
	offset = (uint32_t *)(PROGRAM_START_ADDRESS);
	SetCbpStartAddress(PROGRAM_START_ADDRESS);
	memcpy(data, &dummy_data, MCU_READ_WRITE_SIZE);
	flashc_clear_page_buffer();
	for (uint16_t i = 0; i < AVR32_FLASHC_PAGE_SIZE; i += MCU_READ_WRITE_SIZE)
	{
		WriteToMcuFlash(data, MCU_READ_WRITE_SIZE, i);
	}
	memcpy(buf, (void *)offset, MCU_READ_WRITE_SIZE);
	actual = (memcmp(buf, data, MCU_READ_WRITE_SIZE) == 0);
	test_assert_true(test, actual, "Failed to write data to MCU flash.\r\n");
}

/**
 * \brief Write partial last page to MCU Flash test.
 * \param[in] test - structure test_case
 */
void run_WriteToMcuFlash_PartialLastPage_test(const struct test_case *test)
{
	uint32_t cbxContentSize; // including Header_2
	uint32_t contentIndex;
	uint8_t pageBuffer[DF_PAGE_SIZE];
	uint16_t pageNumber;
	uint16_t sizeToWrite;
	df_error_code_t df_status;
	transition_t expectedTransition;
	bool actual = false;
	bin_image_header_t *binHeader;
	
	// Write the entire CBX contents, including Header_2 to DataFlash
	cbxContentSize = sizeof(cbxDemoContents);
	contentIndex = 0;
	pageNumber = CBX_START_PAGE;
	while (contentIndex < cbxContentSize)
	{
		// See one full page or less to write
		sizeToWrite = (contentIndex + DF_PAGE_SIZE) > cbxContentSize ? (cbxContentSize - contentIndex) : DF_PAGE_SIZE;
		memset(pageBuffer, 0, DF_PAGE_SIZE);
		memcpy(pageBuffer, &cbxDemoContents[contentIndex], sizeToWrite);
		
		test_assert_true(test, pageNumber < DF_MAX_PAGES, "Page overflow detected during writing contents to DataFlash\r\n");
		df_status = df_write_page(pageNumber, pageBuffer, sizeToWrite);
		test_assert_true(test, df_status == DF_RW_SUCCESS, "Failed to write content page %d to DataFlash\r\n", pageNumber);
		contentIndex += sizeToWrite;
		pageNumber++;
	}

	// Verify the CBX contents just written to DataFlash
	expectedTransition = CheckDownloadedImage();
	test_assert_true(test, expectedTransition == TRANSITION_VALID_IMAGE, "Failed to validate CBX image written to DataFlash\r\n");
	
	init_enc_dec_with_key();
	actual = ReadCbxHeader();
	test_assert_true(test, actual, "Failed to read CBX header from DataFlash.\r\n");
	
	actual = CheckCbpBinaryImage();
	test_assert_true(test, actual, "Failed to check CBP binary image from DataFlash.\r\n");
	
	// The ProgramAndVerifyMCU() calls WriteToMcuFlash() to program cbp image part.
	// The demo cbp image size used in this unit test is slightly higher than AVR32_FLASHC_PAGE_SIZE(512bytes) to
	// make the last page is partial in MCU Flash block.
	binHeader = GetCbpBinHeader();
	print_debug_append("CBP image size = %d\r\n", binHeader->bSize.u32);
	actual = ProgramAndVerifyMCU();
	test_assert_true(test, actual, "Failed to program CBP binary image to MCU Flash.\r\n");
}

/**
 * \brief Check MCU Flash after program CBP image.
 * \param[in] test - structure test_case
 */
void run_CheckMcuFlash_test(const struct test_case *test)
{
	bin_image_header_t *bin_header;
	bool actual = false;
	uint32_t start_address = 0;
	
	init_enc_dec_with_key();
	actual = ReadCbxHeader();
	test_assert_true(test, actual, "Failed to read CBX header from DataFlash.\r\n");
	
	actual = CheckCbpBinaryImage();
	bin_header = GetCbpBinHeader();
	test_assert_true(test, actual, "Failed to validate CBP binary image from DataFlash.\r\n");
	
	actual = ProgramAndVerifyMCU();
	test_assert_true(test, actual, "Failed to program CBP binary image to MCU Flash.\r\n");
	print_debug_append("\r\n");
	
	// Positive test for checking MCU Flash.
	start_address = bin_header->Start_Offset.u32;
	SetCbpStartAddress(start_address);
	actual = CheckMcuFlash();
	test_assert_true(test, actual, "Failed to validate checking MCU Flash.\r\n");
	
	// Negative test for checking MCU Flash.
	start_address = bin_header->Start_Offset.u32 + MCU_READ_WRITE_SIZE;
	SetCbpStartAddress(start_address);
	actual = CheckMcuFlash();
	test_assert_false(test, actual, "Failed to validate negative test for checking MCU Flash.\r\n");
}

/**
 * \brief Decrypt test.
 * \param[in] test - structure test_case
 */
void run_Decrypt_test(const struct test_case *test)
{
	bool actual = false;
	uint8_t dummy_enc_buffer[ENC_DEC_BLOCK_SIZE] = {0x73, 0xf6, 0x1c, 0x7a, 0x0e, 0xe4, 0x70, 0x22};
	uint8_t dummy_dec_buffer[ENC_DEC_BLOCK_SIZE] = {0};
	uint8_t dummy_exp_dec_buffer[ENC_DEC_BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80};
	
	init_enc_dec_with_key();
	actual = decrypt(NULL, NULL, true);
	test_assert_false(test, actual, "Failed to validate negative test for decrypt.\r\n");
	
	actual = decrypt(dummy_enc_buffer, dummy_dec_buffer, true);
	test_assert_true(test, actual, "Failed to check decrypt().\r\n");
	
	actual = (memcmp(dummy_dec_buffer, dummy_exp_dec_buffer, ENC_DEC_BLOCK_SIZE) == 0);
	test_assert_true(test, actual, "Failed to validate decrypted data with expected data.\r\n");
}
