/*
 * pressure.h
 *
 * Created: 12/10/2012 1:44:56 PM
 *  Author: yoonl
 */ 


#ifndef PRESSURE_H_
#define PRESSURE_H_

#include "asf.h"
#include "pwa_data.h"

typedef struct
{
	int16_t Index;
	int16_t Start;
	int16_t End;
	int16_t FLength;
	int16_t FSize;
	float Profile[PRESSURE_PULSE_MAXLENGTH];
}Pulse;

Pulse *Pulses;
Pulse *AvPulse;
uint8_t NofPulses;

bool Pulses_init(void);
void Pulses_final(void);
bool AvPulse_init(void);
void AvPulse_final(void);
bool CalcPulses(const bool pRejectExtraPulses, const int8_t pTail, const uint16_t onsetsLength, const float *floatSignal, const int16_t *TrigPts);
bool Validate(Pulse *pPulse);
bool AveragePulse(const int16_t pLength, const int8_t pTail, const int16_t pSignalSampleRate);

#endif /* PRESSURE_H_ */