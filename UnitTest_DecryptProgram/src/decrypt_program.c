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

#define MCU_ACCESS_SIZE		4

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
	bin_image_header_t *bin_header;
	bool actual = false;
	uint32_t start_address = 0;
	uint32_t expected_crc32 = 0x08fcea4d;
	uint32_t expected_size = 0x00015304;
	uint32_t expected_offset = PROGRAM_START_ADDRESS;
	uint32_t expected_spare1 = 0x0;
	
	init_enc_dec_with_key();
	actual = ReadCbxHeader();
	test_assert_true(test, actual, "Failed to read CBX header from DataFlash.\r\n");
	
	actual = CheckCbpBinaryImage();
	test_assert_true(test, actual, "Failed to check CBP binary image from DataFlash.\r\n");
	
	bin_header = GetCbpBinHeader();
	test_assert_true(test, (bin_header->bCRC32.u32 == expected_crc32), "Failed to validate bCRC32.\r\n");
	test_assert_true(test, (bin_header->bSize.u32 == expected_size), "Failed to validate bSize.\r\n");
	test_assert_true(test, (bin_header->Start_Offset.u32 == expected_offset), "Failed to validate Start_Offset.\r\n");
	test_assert_true(test, (bin_header->Spare1.u32 == expected_spare1), "Failed to validate Spare1.\r\n");
	actual = (memcmp(bin_header->bSignature, SIGNATURE_CBP_IMAGE, SIGNATURE_LEN_CBP_IMAGE) == 0);
	test_assert_true(test, actual, "Failed to validate bSignature.\r\n");
}

/**
 * \brief Program and verify CBP binary image test.
 * \param[in] test - structure test_case
 */
void run_ProgramAndVerifyMCU_test(const struct test_case *test)
{
	bool actual = false;
	
	init_enc_dec_with_key();
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
	uint8_t data[MCU_ACCESS_SIZE] = {0};
	uint8_t buf[MCU_ACCESS_SIZE] = {0};
	bool actual = false;
	
	offset = (uint32_t *)(PROGRAM_START_ADDRESS);
	SetCbpStartAddress(PROGRAM_START_ADDRESS);
	memcpy(data, &dummy_data, MCU_ACCESS_SIZE);
	flashc_clear_page_buffer();
	for (uint16_t i = 0; i < AVR32_FLASHC_PAGE_SIZE; i += MCU_ACCESS_SIZE)
	{
		WriteToMcuFlash(data, MCU_ACCESS_SIZE, i);
	}
	memcpy(buf, offset, MCU_ACCESS_SIZE);
	actual = (memcmp(buf, data, MCU_ACCESS_SIZE) == 0);
	test_assert_true(test, actual, "Failed to write data to MCU flash.\r\n");
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
	start_address = bin_header->Start_Offset.u32 + MCU_ACCESS_SIZE;
	SetCbpStartAddress(start_address);
	actual = CheckMcuFlash();
	test_assert_false(test, actual, "Failed to validate negative test for checking MCU Flash.\r\n");
}
