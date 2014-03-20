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
#include "usart_if.h"
#include "dataflash_if.h"
#include "print_funcs.h"
#include "crc8.h"
#include "crc32.h"

// Copy of CBX file header
static cbxHeader_t theHeader;

// Commence ISP
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
				//nextTransition = DecryptAndProgramImage();
			    break;
			case TRANSITION_PROGRAMMING_PASSED:
			    //nextTransition = PrepareNormalReboot();
				break;
			case TRANSITION_REBOOT:
			    //nextTransition = RebootNow();
				break;
			case TRANSITION_INVALID_IMAGE:
			case TRANSITION_PROGRAMMING_FAILED:
				BootloadingError();
				// Not supposed to return from error state but fall through if it did
			default:
				nextTransition = TRANSITION_EXIT;
				break;
		}
	}
}

// Check the downloaded CBX contents in DataFlash
transition_t CheckDownloadedImage (void)
{
	uint8_t recalculatedChecksum;
	uint8_t pageBuffer[DF_PAGE_SIZE];
	uint8_t signature[CBX_ESIGNATURE_LEN + 1];
	df_error_code_t df_status;

	print_dbg("Checking downloaded image in DataFlash\r\n");

	// Get the CBX header
	df_status = df_read_page(CBX_START_PAGE, pageBuffer, DF_PAGE_SIZE);
	if (DF_RW_SUCCESS != df_status)
	{
		print_debug_append("Failed to read CBX header from page %d in DataFlash\r\n", CBX_START_PAGE);
		return TRANSITION_INVALID_IMAGE;
	}
	print_dbg("Copy the header\r\n");
	memcpy(&theHeader, pageBuffer, sizeof(theHeader));

	// Correct any endianess of the header fields
	print_dbg("Endianess of header\r\n");
	theHeader.eSize.u32 = swap32(theHeader.eSize.u32);
	theHeader.eCRC32.u32 = swap32(theHeader.eCRC32.u32);

	// Check the Header_2 checksum
	print_dbg("Recalc header checksum\r\n");
	recalculatedChecksum = calculate_crc(&theHeader, sizeof(theHeader) - 1);
	if (recalculatedChecksum != theHeader.crc8)
	{
		print_dbg("Failed to verify Header_2 checksum\r\n");
		return TRANSITION_INVALID_IMAGE;
	}
	
	// Read and print the header
	print_dbg("Clear signature\r\n");
	memset(signature, 0, sizeof(signature));
	print_dbg("Copy signature\r\n");
	memcpy(signature, theHeader.eSignature, sizeof(theHeader.eSignature));
	print_dbg("Version=");
	print_dbg_ulong(theHeader.majorVer);
	print_dbg_char('.');
	print_dbg_ulong(theHeader.minorVer);
	print_dbg("; Encrypted size=");
	print_dbg_ulong(theHeader.eSize.u32);
	print_dbg("; CRC32=0x");
	print_dbg_hex(theHeader.eCRC32.u32);
	print_dbg("; App Signature=");
	print_dbg(signature);
	print_dbg("\r\n");
	
	return CheckEncyptedPayloadCRC();
}

// Verify the encrypted CBX payload in DataFlash
transition_t CheckEncyptedPayloadCRC (void)
{
	uint32_t contentIndex;
	uint32_t cbxContentSize; // including Header_2
	uint16_t pageNumber;
	uint8_t pageBuffer[DF_PAGE_SIZE];
	uint16_t sizeToRead;
	uint16_t sizeToRecalcCRC32;
	uint32_t recalculatedCRC32;
	df_error_code_t df_status;
	uint32_t pageOffset;

	cbxContentSize = theHeader.eSize.u32 + sizeof(cbxHeader_t);
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
			print_debug_append("Failed to read content page %d from DataFlash\r\n", pageNumber);
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
	if (recalculatedCRC32 == theHeader.eCRC32.u32)
	{
		print_dbg("Valid encrypted payload in DataFlash\r\n");
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
	while (true) {
		gpio_tgl_gpio_pin(AVR32_PIN_PA02);
		cpu_delay_ms(20, sysclk_get_cpu_hz());
		gpio_tgl_gpio_pin(AVR32_PIN_PA02);
		cpu_delay_ms(980, sysclk_get_cpu_hz());
	}
}
