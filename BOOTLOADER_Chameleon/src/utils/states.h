/*
 * \file
 *
 * \brief Bootloading state machine header
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2014
 *
 * \date Created: 28/02/2014 12:16:34 PM
 * \author victora
 */ 

#ifndef STATES_H_
#define STATES_H_

#include <gpio.h>
#include "encrypt_decrypt/enc_dec.h"

#define CBX_ESIGNATURE_LEN	7
#define CBX_START_PAGE		20480 // skip the first 1MB in CBP DataFlash to avoid heavy use of the first 1MB in CBP DataFlash

// Use AWO as a heart beat
#define CBP_AWO_PIN	AVR32_PIN_PA02

// Max MCU size for CBP image
#define MAX_MCU_SIZE_FOR_CBP_IMAGE		(AVR32_FLASHC_FLASH_SIZE - PROGRAM_START_OFFSET)

// MCU read/write size
#define MCU_READ_WRITE_SIZE	(uint32_t)(4)

// State tansition triggers
typedef enum
{
	TRANSITION_UNKNOWN = 0,
	TRANSITION_ISP_FORCED,
	TRANSITION_VALID_IMAGE,
	TRANSITION_INVALID_IMAGE,
	TRANSITION_PROGRAMMING_PASSED,
	TRANSITION_PROGRAMMING_FAILED,
	TRANSITION_ERASE_CONFIG_REC_FAILED,
	TRANSITION_REBOOT,
	TRANSITION_REBOOT_PREP_FAILED,
	TRANSITION_EXIT,
} transition_t;
	
// Encrypted CBP Firmware file (CBX) header
typedef struct
{
	uint8_t spares2[2];
	uint8_t majorVer;
	uint8_t minorVer;
	Union32 eSize;
	Union32 eCRC32;
	uint8_t eSignature[CBX_ESIGNATURE_LEN];
	uint8_t crc8;
} cbxHeader_t;

// CBP Firmware (original) binary image header
typedef struct
{
	Union32 Spare1;
	Union32 Start_Offset;
	Union32 bSize;
	Union32 bCRC32;
	uint8_t bSignature[SIGNATURE_LEN_CBP_IMAGE];
}bin_image_header_t;

// Commence ISP
void DoISP (transition_t nextTransition);

// Check the new downloaded CBP Image in DataFlash
transition_t CheckDownloadedImage (void);
transition_t CheckEncyptedPayloadCRC (void);
bool ReadCbxHeader (void);

// Decrypt and Program the new CBP Image in MCU
transition_t DecryptAndProgramImage (void);


// Bootloading error
void BootloadingError (void);

cbxHeader_t * GetCbxHeader (void);
bin_image_header_t *GetCbpBinHeader(void);

bool CheckCbpBinaryImage(void);
bool ProgramAndVerifyMCU(void);
bool EraseMcuFlash(void);
bool WriteToMcuFlash(const unsigned char *data, const uint32_t data_size, const uint32_t mcu_position);
bool CheckMcuFlash(void);
bool EraseCbpConfigRec (void);

void SetCbpStartAddress(const uint32_t address);

#endif /* STATES_H_ */