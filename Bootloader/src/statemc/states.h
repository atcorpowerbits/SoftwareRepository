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


// Check the new downloaded CBP Image in DataFlash
int8_t CheckDownloadedImage (void);

// Decrypt and Program the new CBP Image in MCU
int8_t DecryptAndProgramImage (void);

// Prepare for noraml reboot
void PrepareNormalReboot (void);

// Reboot now
void RebootNow (void);

// Bootloading error
void BootloadingError (void);



#endif /* STATES_H_ */