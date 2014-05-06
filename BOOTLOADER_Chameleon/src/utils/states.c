/*
 * \file
 *
 * \brief Bootloading state machine 
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 28/02/2014 12:11:51 PM
 * \author victora
 */ 

#include <compiler.h>
#include <string.h>
#include <cycle_counter.h>
#include <sysclk.h>
#include "states.h"
#include "state_reboot.h"
#include "usart_if.h"
#include "dataflash_if.h"
#include "print_funcs.h"
#include "crc8.h"
#include "crc32.h"
#include <boot.h>

#define PROGRAM_START_PAGE  (PROGRAM_START_OFFSET / AVR32_FLASHC_PAGE_SIZE)

// Copy of CBX file header
static cbxHeader_t cbxHeader;

// CBP binary image header
static bin_image_header_t bin_header;

volatile uint32_t *flashc_ptr;
volatile uint32_t cbp_image_start_address = 0;
volatile uint32_t mcu_written_count = 0;
volatile uint32_t mcu_page_count = 0;
volatile uint32_t mcu_last_page_for_cbp_image = 0;
volatile uint32_t mcu_last_page_partial_data_size = 0;
volatile uint32_t mcu_max_rw_count = 0;

/**
 * \brief Get access to CBX header (Header-2)
 * \return Pointer to the CBX header
 */
cbxHeader_t * GetCbxHeader (void) 
{ 
	return &cbxHeader; 
}

/**
 * \brief Get access to the original binary image header (Header-1)
 * \return Pointer to the original binary image header
 */
bin_image_header_t *GetCbpBinHeader(void)
{
	return &bin_header;
}

/**
 * \brief State machine for ISP process.
 * \param[in] nextTransition Transition event to trigger a state change.
 */
void DoISP (transition_t nextTransition)
{
	while (TRANSITION_EXIT != nextTransition)
	{
		switch (nextTransition)
		{
			case TRANSITION_ISP_FORCED:
				nextTransition = CheckDownloadedImage();
				break;
			case TRANSITION_VALID_IMAGE:
				nextTransition = DecryptAndProgramImage();
			    break;
			case TRANSITION_PROGRAMMING_PASSED:
				// Fall through to start the new CBP Operational firmware after it's been programmed successfully
			case TRANSITION_INVALID_IMAGE:
				// Fall through to restart the existing CBP Operational firmware when there is no valid image to upgrade
			case TRANSITION_ERASE_CONFIG_REC_FAILED:
				// If it is here, a CBP Operational firmware is available in MCU Flash to be started normally, i.e. in non-IPS mode
			    nextTransition = PrepareNormalReboot();
				break;
			case TRANSITION_REBOOT:
			    nextTransition = RebootNow();
				break;
			case TRANSITION_PROGRAMMING_FAILED:
			case TRANSITION_REBOOT_PREP_FAILED:
				BootloadingError();
				break;
			default:
				print_dbg("???Unknown transition\r\n");
				// Stop here with the LED on
				gpio_set_gpio_pin(LED0_GPIO);
				while (1) ;
				break;
		}
	}
}

/**
 * \brief Read the CBX header of the downloaded image in the DataFlash.
 * \return boolean Successfully read or not
 */
bool ReadCbxHeader (void)
{
	// The memcpy method is not friendly in bootloader and gives unexpected operation if the data type is different.
	// It is better to match the same data type(static) with cbxHeader.
	static uint8_t pageBuffer[DF_PAGE_SIZE];
	df_error_code_t df_status;

	df_status = df_read_page(CBX_START_PAGE, pageBuffer, DF_PAGE_SIZE);
	if (DF_RW_SUCCESS != df_status)
	{
		print_dbg("Failed to read CBX header from DataFlash page ");
		print_dbg_ulong(CBX_START_PAGE);
		print_dbg("\r\n");
		return false;
	}
	memcpy(&cbxHeader, pageBuffer, sizeof(cbxHeader));

	// Correct any endianess of the header fields
	cbxHeader.eSize.u32 = swap32(cbxHeader.eSize.u32);
	cbxHeader.eCRC32.u32 = swap32(cbxHeader.eCRC32.u32);

	return true;
}

/**
 * \brief Check the downloaded CBX contents in DataFlash.
 * \return Transition event.
 */
transition_t CheckDownloadedImage (void)
{
	uint8_t recalculatedChecksum;
	uint8_t pageBuffer[DF_PAGE_SIZE];
	uint8_t signature[CBX_ESIGNATURE_LEN + 1];
	df_error_code_t df_status;
	int32_t cbp_image_size = 0;

	print_dbg("Checking downloaded image in DataFlash\r\n");

	// Load the CBX header
	if (!ReadCbxHeader())
	{
		return TRANSITION_INVALID_IMAGE;
	}
	
	// Check the Header_2 checksum
	recalculatedChecksum = calculate_crc(&cbxHeader, sizeof(cbxHeader) - 1);
	if (recalculatedChecksum != cbxHeader.crc8)
	{
		print_dbg("Failed to verify CBX header checksum. Download a valid CBX image in DataFlash >>>");
		print_dbg("\r\n");
		return TRANSITION_INVALID_IMAGE;
	}
	
	// Check CBP image size.
	cbp_image_size = cbxHeader.eSize.u32 - sizeof(cbxHeader_t) - sizeof(bin_image_header_t);
	if (cbp_image_size <= 0 || cbp_image_size > MAX_MCU_SIZE_FOR_CBP_IMAGE)
	{
		print_dbg("Failed to verify CBP image size to fit in MCU Flash. CBP image size = ");
		print_dbg_ulong(cbp_image_size);
		print_dbg("\r\n");
		return TRANSITION_INVALID_IMAGE;
	}
	
	// Check signature in CBX header.
	if (memcmp(&cbxHeader.eSignature, SIGNATURE_CBX_IMAGE, CBX_ESIGNATURE_LEN) != 0)
	{
		print_dbg("Failed to verify the signature of CBX header. Signature = ");
		for (int16_t i = 0; i < CBX_ESIGNATURE_LEN; i ++)
		{
			print_dbg_char(cbxHeader.eSignature[i]);
		}
		print_dbg("\r\n");
		return TRANSITION_INVALID_IMAGE;
	}

	// Print only when image is valid
	memset(signature, 0, sizeof(signature));
	memcpy(signature, cbxHeader.eSignature, sizeof(cbxHeader.eSignature));
	print_dbg("\r\n");
	print_dbg("CBX Version=");
	print_dbg_ulong(cbxHeader.majorVer);
	print_dbg_char('.');
	print_dbg_ulong(cbxHeader.minorVer);
	print_dbg("; Encrypted size=");
	print_dbg_ulong(cbxHeader.eSize.u32);
	print_dbg("; CRC32=0x");
	print_dbg_hex(cbxHeader.eCRC32.u32);
	print_dbg("; App Signature=");
	print_dbg(signature);
	print_dbg("\r\n");
	
	return CheckEncyptedPayloadCRC();
}

/**
 * \brief Verify the encrypted CBX payload in DataFlash.
 * \return Transition event.
 */
transition_t CheckEncyptedPayloadCRC (void)
{
	uint32_t contentIndex;
	uint32_t cbxContentSize; // including Header_2
	uint16_t pageNumber;
	uint8_t pageBuffer[DF_PAGE_SIZE];
	uint16_t sizeToRead;
	uint16_t sizeToRecalcCRC32;
	uint32_t recalculatedCRC32 = 0;
	df_error_code_t df_status;
	uint32_t pageOffset;

	cbxContentSize = cbxHeader.eSize.u32 + sizeof(cbxHeader_t);
	contentIndex = 0;
	pageNumber = CBX_START_PAGE;
	while (contentIndex < cbxContentSize)
	{
		// See one full page or less to read
		sizeToRead = (contentIndex + DF_PAGE_SIZE) > cbxContentSize ? (cbxContentSize - contentIndex) : DF_PAGE_SIZE;
		memset(pageBuffer, 0, DF_PAGE_SIZE);
		
		if (pageNumber >= DF_MAX_PAGES)
		{
			print_dbg("Page overflow detected during reading contents from DataFlash\r\n");
			return TRANSITION_INVALID_IMAGE;
		}
		df_status = df_read_page(pageNumber, pageBuffer, sizeToRead);
		if (DF_RW_SUCCESS != df_status)
		{
			print_dbg("Failed to read contents from DataFlash page ");
			print_dbg_ulong(pageNumber);
			print_dbg("\r\n");
			return TRANSITION_INVALID_IMAGE;
		}

		// header_2 in the first page must be skipped before recalculating CRC32 of the encrypted payload
		sizeToRecalcCRC32 = sizeToRead;
		if (contentIndex == 0)
		{
			pageOffset = sizeof(cbxHeader_t);
			sizeToRecalcCRC32 -= pageOffset;
		}
		else
		{
			pageOffset = 0;
		}
		recalculatedCRC32 = crc32(recalculatedCRC32, &pageBuffer[pageOffset], sizeToRecalcCRC32);
		contentIndex += sizeToRead;
		pageNumber++;
	}
	print_dbg("\r\n");
	if (recalculatedCRC32 == cbxHeader.eCRC32.u32)
	{
		print_dbg("Verified encrypted payload in DataFlash\r\n");
		return TRANSITION_VALID_IMAGE;
	}
	else
	{
		print_dbg("Failed to verify CRC of encrypted payload in DataFlash. CBX content size=");
		print_dbg_ulong(cbxContentSize);
		print_dbg("; recalculatedCRC32=0x");
		print_dbg_hex(recalculatedCRC32);
		print_dbg("\r\n");
		return TRANSITION_INVALID_IMAGE;
	}
}

// Bootloading error
void BootloadingError (void)
{
	print_dbg("???Bootloader in error state");
	while (true) {
		gpio_tgl_gpio_pin(AVR32_PIN_PA02);
		cpu_delay_ms(25, sysclk_get_cpu_hz());
		gpio_tgl_gpio_pin(AVR32_PIN_PA02);
		cpu_delay_ms(25, sysclk_get_cpu_hz());
	}
}

/**
 * \brief Decrypt and program image.
 * \return Transition event.
 */
transition_t DecryptAndProgramImage (void)
{
	init_enc_dec_with_key();
	
	if (!CheckCbpBinaryImage())
	{
		print_dbg("Error: CBP binary image is invalid.\r\n");
		return TRANSITION_INVALID_IMAGE;
	}
	
	// Erase the old Configuration record, i.e. the last page in DataFlash
	// used by previous CBP Operational firmware, before the existing
	// CBP Operational firmware is erased. In case it failed to erase the old Configuration record,
	// current CBP Operational firmware is still there to be rebooted.
	if (!EraseCbpConfigRec())
	{
		print_dbg("Error: Failed to erase CBP Configuration page in DataFlash.\r\n");
		return TRANSITION_ERASE_CONFIG_REC_FAILED;
	}

	if (!ProgramAndVerifyMCU())
	{
		print_dbg("Error: Failed to program CBP binary image to MCU Flash.\r\n");
		return TRANSITION_PROGRAMMING_FAILED;
	}
	
	return TRANSITION_PROGRAMMING_PASSED;
}

/**
 * \brief Decrypt CBP binary image from DataFlash and validate image.
 * \return boolean successful or not.
 */
bool CheckCbpBinaryImage(void)
{
	uint8_t enc_buffer[ENC_DEC_BLOCK_SIZE];
	uint8_t dec_buffer[ENC_DEC_BLOCK_SIZE];
	uint8_t pageBuffer[DF_PAGE_SIZE];
	uint32_t contentIndex;
	uint32_t cbxContentSize; // including Header_2
	volatile uint16_t pageIndex;
	uint16_t blockIndex;
	uint16_t pageNumber;
	uint16_t sizeToRead;
	df_error_code_t df_status;
	uint32_t recalculatedCRC32 = 0;
	volatile uint32_t paddingSize = 0;
	
	cbxContentSize = cbxHeader.eSize.u32 + sizeof(cbxHeader_t);
	contentIndex = 0;
	pageNumber = CBX_START_PAGE;
	memset(enc_buffer, 0, ENC_DEC_BLOCK_SIZE);
	memset(dec_buffer, 0, ENC_DEC_BLOCK_SIZE);
	memset(&bin_header, 0, sizeof(bin_image_header_t));
	blockIndex = 0;
	
	while (contentIndex < cbxContentSize)
	{
		pageIndex = 0;
		
		// See one full page or less to read
		sizeToRead = (contentIndex + DF_PAGE_SIZE) > cbxContentSize ? (cbxContentSize - contentIndex) : DF_PAGE_SIZE;
		memset(pageBuffer, 0, DF_PAGE_SIZE);
		
		if (pageNumber >= DF_MAX_PAGES)
		{
			print_dbg("Page overflow detected during reading contents from DataFlash\r\n");
			return false;
		}
		df_status = df_read_page(pageNumber, pageBuffer, sizeToRead);
		if (DF_RW_SUCCESS != df_status)
		{
			print_dbg("Failed to read contents from DataFlash page ");
			print_dbg_ulong(pageNumber);
			print_dbg("\r\n");
			return false;
		}
		
		// Check header information first.
		if (pageNumber == CBX_START_PAGE)
		{
			// Skip CBX header.
			pageIndex = sizeof(cbxHeader_t);
			
			// Decrypt Spare1, Start_Offset in header.
			memcpy(enc_buffer, &pageBuffer[pageIndex], ENC_DEC_BLOCK_SIZE);
			if (!decrypt(enc_buffer, dec_buffer, true))
			{
				print_dbg("Failed to decrypt CBP binary image header for Spare1, Start_Offset.\r\n");
				return false;
			}
			memcpy(&bin_header.Spare1.u32, &dec_buffer[0], sizeof(bin_header.Spare1.u32));
			memcpy(&bin_header.Start_Offset.u32, &dec_buffer[sizeof(bin_header.Spare1.u32)], sizeof(bin_header.Start_Offset.u32));
			
			// Decrypt bSize, bCRC32 in header.
			pageIndex += ENC_DEC_BLOCK_SIZE;
			memcpy(enc_buffer, &pageBuffer[pageIndex], ENC_DEC_BLOCK_SIZE);
			if (!decrypt(enc_buffer, dec_buffer, false))
			{
				print_dbg("Failed to decrypt CBP binary image header for bSize, bCRC32.\r\n");
				return false;
			}
			memcpy(&bin_header.bSize.u32, &dec_buffer[0], sizeof(bin_header.bSize.u32));
			memcpy(&bin_header.bCRC32.u32, &dec_buffer[sizeof(bin_header.bSize.u32)], sizeof(bin_header.bCRC32.u32));
			
			bin_header.Spare1.u32 = swap32(bin_header.Spare1.u32);
			bin_header.Start_Offset.u32 = swap32(bin_header.Start_Offset.u32);
			bin_header.bSize.u32 = swap32(bin_header.bSize.u32);
			bin_header.bCRC32.u32 = swap32(bin_header.bCRC32.u32);
			cbp_image_start_address = bin_header.Start_Offset.u32;
			
			mcu_max_rw_count = bin_header.bSize.u32 % MCU_READ_WRITE_SIZE;
			paddingSize = bin_header.bSize.u32 % ENC_DEC_BLOCK_SIZE;
			if (mcu_max_rw_count > 0 || paddingSize > 0)
			{
				mcu_max_rw_count = (bin_header.bSize.u32 / MCU_READ_WRITE_SIZE) + 1;
			}
			else
			{
				mcu_max_rw_count = bin_header.bSize.u32 / MCU_READ_WRITE_SIZE;
			}
			
			mcu_last_page_partial_data_size = bin_header.bSize.u32 % AVR32_FLASHC_PAGE_SIZE;
			if (mcu_last_page_partial_data_size > 0)
			{
				mcu_last_page_for_cbp_image = (bin_header.bSize.u32 / AVR32_FLASHC_PAGE_SIZE) + 1;
			}
			else
			{
				mcu_last_page_for_cbp_image = bin_header.bSize.u32 / AVR32_FLASHC_PAGE_SIZE;
			}
			
			// Decrypt bSignature in header.
			pageIndex += ENC_DEC_BLOCK_SIZE;
			memcpy(enc_buffer, &pageBuffer[pageIndex], ENC_DEC_BLOCK_SIZE);
			if (!decrypt(enc_buffer, dec_buffer, false))
			{
				print_dbg("Failed to decrypt CBP binary image header for bSignature.\r\n");
				return false;
			}
			memcpy(&bin_header.bSignature, dec_buffer, sizeof(bin_header.bSignature));
			if (memcmp(&bin_header.bSignature, SIGNATURE_CBP_IMAGE, SIGNATURE_LEN_CBP_IMAGE) != 0)
			{
				print_dbg("Failed to verify the signature of CBP binary image.\r\n");
				return false;
			}
	
			pageIndex += ENC_DEC_BLOCK_SIZE;
		}
		
		for (uint16_t i = pageIndex; i < sizeToRead; i++)
		{
			enc_buffer[blockIndex] = pageBuffer[i];
			blockIndex++;
			if (blockIndex == ENC_DEC_BLOCK_SIZE)
			{
				if (!decrypt(enc_buffer, dec_buffer, false))
				{
					print_dbg("Failed to decrypt CBP binary image.\r\n");
					return false;
				}
				recalculatedCRC32 = crc32(recalculatedCRC32, dec_buffer, ENC_DEC_BLOCK_SIZE);
				blockIndex = 0;
				memset(enc_buffer, 0, ENC_DEC_BLOCK_SIZE);
			}
		}

		pageNumber++;
		contentIndex += sizeToRead;
	}
	
	if (recalculatedCRC32 != bin_header.bCRC32.u32)
	{
		print_dbg("Failed to verify CBP binary image CRC from DataFlash.\r\n");
		return false;
	}
	
	return true;
}

/**
 * \brief Decrypt CBP binary image from DataFlash, program to MCU Flash and verify it.
 * \return boolean successful or not.
 */
bool ProgramAndVerifyMCU(void)
{
	uint8_t enc_buffer[ENC_DEC_BLOCK_SIZE];
	uint8_t dec_buffer[ENC_DEC_BLOCK_SIZE];
	uint8_t pageBuffer[DF_PAGE_SIZE];
	uint32_t contentIndex;
	uint32_t cbxContentSize; // including Header_2
	uint16_t pageIndex;
	uint16_t blockIndex;
	uint16_t pageNumber;
	uint16_t sizeToRead;
	df_error_code_t df_status;
	uint32_t mcuPos = 0;
	uint16_t total_header_size = 0;
	uint32_t mcu_rw_size = 0;
	uint32_t mcu_rw_size_by_dec_block = 0;
	uint32_t dec_buffer_index = 0;
	
	print_dbg("\r\nStart erasing MCU application flash.\r\n");
	if (!EraseMcuFlash())
	{
		print_dbg("Failed to erase MCU application flash.\r\n");
		return false;
	}
	// There's no CBP Operational firmware beyond this point to be rebooted until the new one is programmed
	print_dbg("Erased MCU application flash.\r\n");
	
	total_header_size = sizeof(cbxHeader_t) + sizeof(bin_image_header_t);
	cbxContentSize = cbxHeader.eSize.u32 + sizeof(cbxHeader_t);
	contentIndex = 0;
	pageNumber = CBX_START_PAGE;
	memset(enc_buffer, 0, sizeof(enc_buffer));
	memset(dec_buffer, 0, sizeof(dec_buffer));
	blockIndex = 0;
	mcu_written_count = 0;
	mcu_page_count = 0;
	
	// Clean up page buffer before start any writing to MCU.
	flashc_clear_page_buffer();
	
	print_dbg("Start writing to MCU application flash.\r\n");
	while (contentIndex < cbxContentSize)
	{
		pageIndex = 0;
		
		// See one full page or less to read
		sizeToRead = (contentIndex + DF_PAGE_SIZE) > cbxContentSize ? (cbxContentSize - contentIndex) : DF_PAGE_SIZE;
		memset(pageBuffer, 0, DF_PAGE_SIZE);
		
		if (pageNumber >= DF_MAX_PAGES)
		{
			print_dbg("Page overflow detected during reading contents from DataFlash\r\n");
			return false;
		}
		df_status = df_read_page(pageNumber, pageBuffer, sizeToRead);
		if (DF_RW_SUCCESS != df_status)
		{
			print_dbg("Failed to read contents from DataFlash page ");
			print_dbg_ulong(pageNumber);
			print_dbg("\r\n");
			return false;
		}
		
		if (pageNumber == CBX_START_PAGE)
		{
			// Skip CBX header.
			pageIndex = sizeof(cbxHeader_t);
			
			for (uint16_t i = pageIndex; i < total_header_size; i += sizeof(enc_buffer))
			{
				memcpy(enc_buffer, &pageBuffer[pageIndex], sizeof(enc_buffer));
				if (!decrypt(enc_buffer, dec_buffer, (i == sizeof(cbxHeader_t))))
				{
					print_dbg("Failed to decrypt CBP binary image header.\r\n");
					return false;
				}
				pageIndex += sizeof(enc_buffer);
			}
		}
		
		for (uint16_t i = pageIndex; i < sizeToRead; i++)
		{
			enc_buffer[blockIndex] = pageBuffer[i];
			blockIndex++;
			if (blockIndex == sizeof(enc_buffer))
			{
				memset(dec_buffer, 0, sizeof(dec_buffer));
				if (!decrypt(enc_buffer, dec_buffer, false))
				{
					print_dbg("Failed to decrypt CBP binary image.\r\n");
					return false;
				}
				blockIndex = 0;
				memset(enc_buffer, 0, sizeof(enc_buffer));
				
				if (sizeof(dec_buffer) - MCU_READ_WRITE_SIZE <= 0)
				{
					if (!WriteToMcuFlash(dec_buffer, sizeof(dec_buffer), mcuPos))
					{
						print_dbg("Failed to write CBP binary image to MCU Flash.\r\n");
						return false;
					}
					mcuPos += sizeof(dec_buffer);
				}
				else
				{
					dec_buffer_index = 0;
					mcu_rw_size = 0;
					mcu_rw_size_by_dec_block = sizeof(dec_buffer);
					while(mcu_rw_size_by_dec_block > 0)
					{
						if (mcu_rw_size_by_dec_block >= MCU_READ_WRITE_SIZE)
						{
							mcu_rw_size = MCU_READ_WRITE_SIZE;
						}
						else
						{
							mcu_rw_size = mcu_rw_size_by_dec_block;
						}
						
						if (!WriteToMcuFlash(&dec_buffer[dec_buffer_index], mcu_rw_size, mcuPos))
						{
							print_dbg("Failed to write CBP binary image to MCU Flash.\r\n");
							return false;
						}
						mcuPos += mcu_rw_size;
						dec_buffer_index += mcu_rw_size;
						mcu_rw_size_by_dec_block -= mcu_rw_size;
					}
				}
			}
		}

		pageNumber++;
		contentIndex += sizeToRead;
	}
	
	// If we are here, all writing CBP image to MCU flash is done.
	// Read written data from MCU flash and validate by recalculating crc32.
	if (!CheckMcuFlash())
	{
		print_dbg("Failed to verify CBP binary image CRC from MCU Flash.\r\n");
		return false;
	}
	
	return true;
}

/**
 * \brief Erase and verify MCU application flash.
 * \return boolean successful or not.
 */
bool EraseMcuFlash(void)
{
	// Erase and verify MCU application flash.
	for (unsigned int i = flashc_get_page_count() - 1; i >= PROGRAM_START_PAGE; i--)
	{
		if (!flashc_erase_page(i, true))
		{
			print_dbg("Erase failed at i=0x");
			print_dbg_hex(i);
			print_dbg("\r\n");
			return false;
		}
	}
	
	return true;
}

/**
 * \brief Write data(4bytes) to MCU application flash.
 * \return boolean successful or not.
 */
bool WriteToMcuFlash(const unsigned char *data, const uint32_t data_size, const uint32_t mcu_position)
{
	// Note: This method is very sensitive in somehow, try to avoid using any complex calculation or printing any in this method.
	
	bool flashc_no_error = true;
	flashc_ptr = (uint32_t *)(cbp_image_start_address + mcu_position);
	
	*flashc_ptr = *((uint32_t *)data);
	mcu_written_count += data_size;
	// If the written data to page buffer is 512 bytes, call write page.
	if (mcu_written_count == AVR32_FLASHC_PAGE_SIZE)
	{
		mcu_written_count = 0;
		mcu_page_count++;
		flashc_write_page(-1);
		if (flashc_is_lock_error() || flashc_is_programming_error())
		{
			flashc_no_error = false;
		}
		flashc_clear_page_buffer();
		if (flashc_is_lock_error() || flashc_is_programming_error())
		{
			flashc_no_error = false;
		}
	}
	// If the last page is partial and it meets the last page, it should write partial data of the last page.
	else if ((mcu_last_page_partial_data_size > 0) && (mcu_page_count == mcu_last_page_for_cbp_image - 1) && (mcu_written_count >= mcu_last_page_partial_data_size))
	{
		flashc_write_page(-1);
		if (flashc_is_lock_error() || flashc_is_programming_error())
		{
			flashc_no_error = false;
		}
	}
	
	return flashc_no_error;
}

/**
 * \brief Read data(4bytes) from MCU application flash, calculate crc32 and check it with header bCRC32 value.
 * \return boolean successful or not.
 */
bool CheckMcuFlash(void)
{
	// Note: This method is very sensitive in somehow, try to avoid using any complex calculation or printing any in this method.
	
	uint8_t buffer[MCU_READ_WRITE_SIZE] = {0};
	uint32_t recalculatedCRC32 = 0;
	uint32_t mcuPos = 0;

	for (uint32_t i = 0; i < mcu_max_rw_count; i++)
	{
		memset(buffer, 0, MCU_READ_WRITE_SIZE);
		flashc_ptr = (uint32_t *)(cbp_image_start_address + mcuPos);
		memcpy(buffer, flashc_ptr, MCU_READ_WRITE_SIZE);
		recalculatedCRC32 = crc32(recalculatedCRC32, buffer, MCU_READ_WRITE_SIZE);
		mcuPos += MCU_READ_WRITE_SIZE;
	}
	
	if (recalculatedCRC32 == bin_header.bCRC32.u32)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * \brief Set CBP image start address in MCU Flash.
 * This method is for UnitTest_DecryptProgram.
 */
void SetCbpStartAddress(const uint32_t address)
{
	cbp_image_start_address = address;
}

/**
 * \brief Erase configuration record of the CBP Operational firmware.
 * \return boolean successful or not.
 */
bool EraseCbpConfigRec (void)
{
	df_error_code_t df_status = df_erase_page(CBP_CONFIG_PAGE);
	
	return (DF_RW_SUCCESS == df_status);
}
