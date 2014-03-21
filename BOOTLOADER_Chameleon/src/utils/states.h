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

#define CBX_ESIGNATURE_LEN	7
#define CBX_START_PAGE		20480 // skip the first 1MB in CBP DataFlash to avoid heavy use of the first 1MB in CBP DataFlash

// Use AWO as a heart beat
#define CBP_AWO_PIN	AVR32_PIN_PA02

// State tansition triggers
typedef enum
{
	TRANSITION_ISP_FORCED = 0,
	TRANSITION_VALID_IMAGE,
	TRANSITION_INVALID_IMAGE,
	TRANSITION_PROGRAMMING_PASSED,
	TRANSITION_PROGRAMMING_FAILED,
	TRANSITION_REBOOT,
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

// Commence ISP
void DoISP (transition_t nextTransition);

// Check the new downloaded CBP Image in DataFlash
transition_t CheckDownloadedImage (void);
transition_t CheckEncyptedPayloadCRC (void);
bool ReadCbxHeader (void);

//// Decrypt and Program the new CBP Image in MCU
//int8_t DecryptAndProgramImage (void);
//
//// Prepare for noraml reboot
//void PrepareNormalReboot (void);
//
//// Reboot now
//void RebootNow (void);

// Bootloading error
void BootloadingError (void);

cbxHeader_t * GetCbxHeader (void);

#endif /* STATES_H_ */