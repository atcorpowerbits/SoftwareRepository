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

const unsigned char cbxContents[] =
{
	0x00, 0x00, 0x01, 0x00, 0x20, 0x02, 0x00, 0x00,
	0x6C, 0xE6, 0xF8, 0x96, 0x61, 0x62, 0x70, 0x6D,
	0x43, 0x42, 0x50, 0x88, 0x31, 0x02, 0xF2, 0x96,
	0x7E, 0x62, 0x76, 0xCE, 0x5B, 0x57, 0xAF, 0x7D,
	0x5C, 0x9C, 0x5C, 0x08, 0x86, 0xF7, 0x19, 0xED,
	0x01, 0x74, 0x88, 0xF6, 0x83, 0xD6, 0x15, 0xC3,
	0xFA, 0x4D, 0x86, 0xF2, 0xC5, 0x4C, 0x07, 0x18,
	0x3C, 0x97, 0xB1, 0x01, 0x80, 0xAC, 0x77, 0x93,
	0xD6, 0xE9, 0xD9, 0xAA, 0xD1, 0x78, 0xD7, 0xCF,
	0xE8, 0x8A, 0xE1, 0x3C, 0x1E, 0xB7, 0x89, 0x29,
	0xD8, 0x00, 0xE1, 0xB1, 0x21, 0x62, 0x75, 0xB3,
	0xFC, 0x6A, 0x60, 0x96, 0xD3, 0x63, 0x0B, 0x96,
	0xA6, 0xA2, 0xB6, 0x93, 0x8A, 0x4F, 0x62, 0x62,
	0xC2, 0x9B, 0xA2, 0xB4, 0x0D, 0xF5, 0x61, 0xCD,
	0x21, 0x7B, 0xAA, 0x1E, 0x00, 0x32, 0x2E, 0xC4,
	0x95, 0x2D, 0x45, 0x22, 0x30, 0xA7, 0xC6, 0xCD,
	0xE3, 0x47, 0x64, 0x96, 0xBA, 0x18, 0xCD, 0xDF,
	0x58, 0xEE, 0x0B, 0xEE, 0x18, 0x52, 0xE1, 0xA1,
	0xC0, 0xB8, 0x42, 0xA3, 0x26, 0xD5, 0x3A, 0x76,
	0x4A, 0x5B, 0x07, 0x6E, 0x02, 0x0D, 0x69, 0x2A,
	0x6A, 0xCE, 0x73, 0x77, 0xF9, 0x1F, 0xB7, 0x9F,
	0x8F, 0xFF, 0xE6, 0x50, 0x93, 0xEE, 0xD9, 0x5C,
	0xBF, 0x2A, 0xB6, 0x12, 0x3C, 0x85, 0x45, 0xA0,
	0x69, 0x22, 0x00, 0x1B, 0x4E, 0x20, 0x69, 0x5E,
	0x86, 0x83, 0x7D, 0x8D, 0x15, 0x89, 0x37, 0x40,
	0x4F, 0x2B, 0xD6, 0xE1, 0x8D, 0x3A, 0x95, 0xBD,
	0x94, 0x97, 0x24, 0xA4, 0x1A, 0x7C, 0xFF, 0xAD,
	0xD3, 0x54, 0x63, 0x10, 0xC5, 0xD9, 0xA2, 0xE9,
	0xFE, 0x42, 0x54, 0xD7, 0xD1, 0x54, 0x0D, 0xAC,
	0x93, 0xB5, 0x00, 0x47, 0xA1, 0x66, 0xAB, 0x25,
	0x6C, 0xE0, 0xFC, 0x35, 0xC1, 0xD4, 0xAB, 0x9C,
	0x24, 0x66, 0x9A, 0x35, 0x61, 0x15, 0xC5, 0x74,
	0xA0, 0x6C, 0xC8, 0x9A, 0xBE, 0xAA, 0x93, 0xC9,
	0xD5, 0xCD, 0x88, 0x4B, 0x28, 0x4D, 0x9D, 0x05,
	0xE7, 0xC8, 0x27, 0xD9, 0x9F, 0xF1, 0x22, 0x66,
	0xBE, 0x00, 0xC3, 0xAE, 0xED, 0x8F, 0x43, 0xD5,
	0xCD, 0x0D, 0xDA, 0xA6, 0x6F, 0xDC, 0x9A, 0x97,
	0x9B, 0x94, 0x6D, 0x2C, 0x68, 0x24, 0x28, 0xBE,
	0x3E, 0x24, 0x7E, 0x0F, 0x36, 0x34, 0xFD, 0xFB,
	0x99, 0xCB, 0x1D, 0x92, 0x16, 0x3B, 0xCD, 0x80,
	0x12, 0x1F, 0x2B, 0x37, 0xBC, 0xE8, 0x07, 0x2E,
	0x0D, 0xAE, 0xDE, 0xE3, 0x47, 0xFD, 0x58, 0x0D,
	0x41, 0x36, 0x39, 0x97, 0x60, 0x1E, 0x83, 0x6D,
	0x6B, 0x67, 0x66, 0xD9, 0x3E, 0x21, 0x46, 0x5E,
	0x2C, 0xDE, 0x34, 0x47, 0x06, 0xA3, 0xFD, 0x86,
	0x4E, 0x39, 0x73, 0xF9, 0x5C, 0xD2, 0x47, 0xDA,
	0x8E, 0x5B, 0xFD, 0xA5, 0xDA, 0xF3, 0xD6, 0x1D,
	0xA8, 0x1A, 0x78, 0x4B, 0x88, 0xC5, 0xEA, 0x65,
	0x6E, 0x0B, 0xF9, 0xCB, 0x60, 0xC7, 0x73, 0x84,
	0x75, 0xC0, 0x5E, 0xC0, 0xF0, 0x2D, 0x14, 0x20,
	0x35, 0xA3, 0x0F, 0xD6, 0x67, 0xC5, 0xB5, 0x0B,
	0x54, 0x99, 0xD9, 0x88, 0xFF, 0x37, 0xAD, 0x72,
	0x7C, 0xA5, 0x6A, 0x95, 0x19, 0x0F, 0xCD, 0x5C,
	0xB0, 0xDC, 0x4C, 0x61, 0xC7, 0xDF, 0x19, 0x6A,
	0xBF, 0x68, 0xE8, 0x26, 0x18, 0x85, 0xA2, 0xA3,
	0xC7, 0x52, 0x3B, 0x68, 0x53, 0xBA, 0x24, 0x9C,
	0xA3, 0xDD, 0x69, 0x2A, 0x13, 0x1D, 0x32, 0xE6,
	0xD3, 0xF7, 0x8B, 0xF2, 0xBE, 0xD8, 0x89, 0x14,
	0x04, 0xFF, 0x4B, 0xB6, 0x2F, 0x60, 0x7F, 0x0D,
	0xF2, 0xF0, 0x9E, 0xB9, 0x6A, 0x6A, 0xC9, 0x20,
	0x43, 0x20, 0xFF, 0x6C, 0x34, 0x50, 0x5F, 0xF9,
	0xE4, 0x71, 0x3B, 0xC8, 0xB1, 0x2F, 0x14, 0x34,
	0x43, 0xAF, 0x7A, 0x1C, 0xCF, 0xD6, 0x74, 0x40,
	0xCC, 0x68, 0x28, 0xA9, 0x01, 0xA2, 0x05, 0x84,
	0xC6, 0x4C, 0xCB, 0x8D, 0x6D, 0x42, 0x1A, 0xB5,
	0xC2, 0x03, 0x28, 0x4D, 0x58, 0x74, 0xAE, 0x2C,
	0xB7, 0xAD, 0xBF, 0x03, 0x28, 0xBB, 0x85, 0xC2,
	0x30, 0x68, 0x06, 0xFE, 0x58, 0xD9, 0x84, 0xEC,
	0x71, 0x6F, 0x27, 0x90, 0x9A, 0x31, 0x6B, 0x3A,
	0xD5, 0xC7, 0xC3, 0x5F, 0xE5, 0x68, 0xD8, 0xF6,
	0xB1, 0xD6, 0x91, 0xE8,
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
	cbxHeader = GetCbxHeader();
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
	memset(cbxHeader, 0, sizeof(cbxHeader_t));
	
	actual = ProgramAndVerifyMCU();
	test_assert_false(test, actual, "Failed to validate negative test for programing CBP image.\r\n");
	
	actual = ReadCbxHeader();
	test_assert_true(test, actual, "Failed to read CBX header from DataFlash.\r\n");
	
	actual = ProgramAndVerifyMCU();
	test_assert_true(test, actual, "Failed to program CBP image.\r\n");
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
	memcpy(buf, offset, MCU_READ_WRITE_SIZE);
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
	cbxHeader_t *cbxHeader;
	bin_image_header_t *binHeader;
	
	// Write the entire CBX contents, including Header_2 to DataFlash
	cbxContentSize = sizeof(cbxContents);
	contentIndex = 0;
	pageNumber = CBX_START_PAGE;
	while (contentIndex < cbxContentSize)
	{
		// See one full page or less to write
		sizeToWrite = (contentIndex + DF_PAGE_SIZE) > cbxContentSize ? (cbxContentSize - contentIndex) : DF_PAGE_SIZE;
		memset(pageBuffer, 0, DF_PAGE_SIZE);
		memcpy(pageBuffer, &cbxContents[contentIndex], sizeToWrite);
		
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
	uint8_t dummy_enc_buffer[ENC_DEC_BLOCK_SIZE] = {0x31, 0x02, 0xf2, 0x96, 0x7e, 0x62, 0x76, 0xce};
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

/**
 * \brief Erase CBP Config Record test.
 * \param[in] test - structure test_case
 */
void run_EraseCbpConfigRec_test (const struct test_case *test)
{
	bool actual = false;
	df_error_code_t df_status;
	uint8_t buffer[DF_PAGE_SIZE];
	
	actual = EraseCbpConfigRec();
	test_assert_true(test, actual, "Failed to erase CBP Config Record.\r\n");
	
	// Check if Config Record is actually erased with 0xFF's
	memset(buffer, 0, DF_PAGE_SIZE);
	df_status = df_read_page(CBP_CONFIG_PAGE, buffer, DF_PAGE_SIZE);
	test_assert_true(test, DF_RW_SUCCESS == df_status, "Failed to read CBP Config Record for unit test verification\r\n");
	for (int i = 0; i < DF_PAGE_SIZE; i++)
	{
		test_assert_true(test, buffer[i] == 0xFF, "Failed to verify CBP Config Record is erased\r\n");
	}
	
	// Temporarily stop SPI peripheral clock to disable DataFlash interface for negative unit test on the target function.
	df_interface_disable();
	actual = EraseCbpConfigRec();
	test_assert_false(test, actual, "Unable to detect failure to erase CBP Config Record.\r\n");
	
	// Enable DataFlash interface again
	df_interface_enable();
}
