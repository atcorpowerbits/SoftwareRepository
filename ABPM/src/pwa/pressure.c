/*
 * pressure.c
 *
 * Created: 12/10/2012 1:45:07 PM
 *  Author: yoonl
 */ 

#include "pressure.h"
#include "usart/usart_rxtx.h"
#include "math_pwa.h"

#define PWA_MIN_VALID_PULSELENGTH_PERCENT	(float)0.60
#define PWA_MAX_VALID_PULSELENGTH_PERCENT	(float)1.50
#define PWA_MIN_SIGNAL_LENGTH				(int16_t)300
#define PWA_MIN_SIGNAL_HEIGHT				(int16_t)30
#define PRESSURE_PULSE_MINLENGTH			(float)(60.0 * (MEAS_DEFAULT_SAMPLE_RATE) / MAX_HR)

/* ###########################################################################
 ** Pulses_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise Pulses properties
 */
bool Pulses_init(void)
{
	NofPulses = 0;
	
	Pulses = malloc(sizeof(Pulse)*PRESSURE_MAX_PULSES);
	if (Pulses == NULL)
	{
		return false;
	}
	
	for (int16_t i = 0; i < PRESSURE_MAX_PULSES; i++)
	{
		Pulses[i].Index = -1;
		Pulses[i].Start = 0;
		Pulses[i].End = 0;
		Pulses[i].FLength = 0;
		Pulses[i].FSize = 0;
		memset(Pulses[i].Profile, 0, sizeof(Pulses[i].Profile[0]) * PRESSURE_PULSE_MAXLENGTH);
	}
	
	return true;
}

/* ###########################################################################
 ** Pulses_final()
 **
 ** DESCRIPTION
 **  Free Pulses properties
*/
void Pulses_final(void)
{
	if (Pulses != NULL)
	{
		free(Pulses);
		Pulses = NULL;
	}
}

/* ###########################################################################
 ** AvPulse_init()
 **
 ** DESCRIPTION
 **  Initailise AvPulse properties
 */
bool AvPulse_init(void)
{
	AvPulse = malloc(sizeof(Pulse));
	if (AvPulse == NULL)
	{
		return false;
	}
	
	AvPulse->Index = -1;
	AvPulse->Start = 0;
	AvPulse->End = 0;
	AvPulse->FLength = 0;
	AvPulse->FSize = 0;
	memset(AvPulse->Profile, 0, sizeof(AvPulse->Profile[0]) * PRESSURE_PULSE_MAXLENGTH);
	
	return true;
}

/* ###########################################################################
 ** AvPulse_final()
 **
 ** DESCRIPTION
 **  Finalise AvPulse properties
*/
void AvPulse_final(void)
{
	if (AvPulse != NULL)
	{
		free(AvPulse);
		AvPulse = NULL;
	}
}

/* ###########################################################################
 ** CalcPulses ()
 **
 ** DESCRIPTION
 **  Calculate Pulses using trigger points
 ** INPUT
 **  BizPressure class (source)
 ** OUTPUT
 **  boolean success or not
*/
bool CalcPulses(const bool pRejectExtraPulses, const int8_t pTail, const uint16_t onsetsLength, const float *floatSignal, const int16_t *TrigPts)
{
	if (pRejectExtraPulses == false)
	{
		// Calculate pulses without rejecting extra short and long pulses
		NofPulses = 0;
		for (uint16_t i=0; i < onsetsLength - 1; i++)
		{
			short int lLength = (short int)(TrigPts[i+1] - TrigPts[i] + 1);
			// Reject extralarge pulses
			if (lLength > PRESSURE_PULSE_MAXLENGTH  || lLength < PRESSURE_PULSE_MINLENGTH)
				continue;
			int16_t index = TrigPts[i] - pTail;
			if (index < 0) // Miss first trigger point if it is too close to the start
				continue;
			memcpy(&Pulses[NofPulses].Profile[0], &floatSignal[index], sizeof(float)*(lLength + pTail));
			Pulses[NofPulses].Start = pTail;
			Pulses[NofPulses].Index = TrigPts[i];
			Pulses[NofPulses].End = (int16_t) (pTail + lLength - 1);
			Pulses[NofPulses].FLength = lLength;
			Pulses[NofPulses].FSize = lLength + 1*pTail;
			NofPulses++;
		}
		return (NofPulses > 1);
	}
	else
	{
		if (onsetsLength <= 1)
		{
			return false;
		}
		// Calculate average length
		float lAvLength = 0.;
		int16_t NofAv = 0;
		for (int16_t i=0; i < onsetsLength - 1; i++)
		{
			int16_t lLength = (TrigPts[i+1] - TrigPts[i] + 1);
			if (lLength < PRESSURE_PULSE_MAXLENGTH && lLength > PRESSURE_PULSE_MINLENGTH)
			{
				lAvLength += lLength;
				NofAv++;
			}
		}
		if (NofAv <= 0)
			return false;

		lAvLength /= NofAv;
		// Calculate pulses rejecting extra short and long pulses
		NofPulses = 0;
		for (uint16_t i=0; i < onsetsLength - 1; i++)
		{
			short int lLength = (short int)(TrigPts[i+1] - TrigPts[i] + 1);
			if (lLength > PRESSURE_PULSE_MAXLENGTH || lLength < PRESSURE_PULSE_MINLENGTH)
				continue;
			if ((lLength >= lAvLength*PWA_MIN_VALID_PULSELENGTH_PERCENT) &&
				(lLength <= lAvLength*PWA_MAX_VALID_PULSELENGTH_PERCENT))
			{
				int16_t index = TrigPts[i] - pTail/* * ExpandFactor*/;
				if (index < 0) // Miss first trigger point if it is too close to the start
					continue;
				memcpy(&Pulses[NofPulses].Profile[0], &floatSignal[index], sizeof(float)*(lLength + pTail));
				Pulses[NofPulses].Start = pTail;
				Pulses[NofPulses].Index = TrigPts[i];
				Pulses[NofPulses].End = (int16_t) (pTail + lLength - 1);
				Pulses[NofPulses].FLength = lLength;
				Pulses[NofPulses].FSize = lLength + 1*pTail;
				NofPulses++;
			}
		}
		return (NofPulses > 1);
	}
}

/* ###########################################################################
 ** Validate ()
 **
 ** DESCRIPTION
 **  Validate pulse
 ** INPUT
 **  Pulse class
 ** OUTPUT
 **  boolean valid pulse or not
*/
bool Validate(Pulse *pPulse)
{
	// Pulse Validation
	if ((!pPulse) || (pPulse->FLength < 1) || (pPulse->Start < 0) || (pPulse->Start > pPulse->End) ||
		(pPulse->FSize < pPulse->FLength) || (pPulse->FSize > PRESSURE_PULSE_MAXLENGTH) || (pPulse->End - pPulse->Start + 1 != pPulse->FLength))
	{
		print_debug("Error: wrong pulse.\r\n");
		return false;
	}
	return true;
}

/* ###########################################################################
 ** AveragePulse (...)
 **
 ** DESCRIPTION
 **  Find Average Pulse from Pulses
 ** INPUT
 **  pLength - predefined pulse Length (0 for periph, >0 for central)
 **  Pulses[NofPulses] - all pulses
 ** OUTPUT
 **  AvPulse - average pulse structure
 ** RETURN
 **  boolean success or not
*/
bool AveragePulse(const int16_t pLength, const int8_t pTail, const int16_t pSignalSampleRate)
{
	if (NofPulses <= 0)
	{
		return false;
	}
	// Calculate Size of Average Pulse averaging all pulses
	// if the length is unknown
	int16_t LengthAvPulse = 0;
	if (pLength > 0)
	{
		LengthAvPulse = pLength;
	}
	else
	{
		for (int16_t i = 0; i < NofPulses; i++)
		{
			// Break if wrong pulse
			if (Validate(&Pulses[i])==false)
			{
				return false;
			}
			LengthAvPulse += Pulses[i].FLength;
		}
		Math_Round((float)LengthAvPulse/NofPulses, &LengthAvPulse);
	}

	// Validation
	if (LengthAvPulse < PRESSURE_PULSE_MINLENGTH || LengthAvPulse > PRESSURE_PULSE_MAXLENGTH)
	{
		return false;
	}

	// Create AvPulse
	AvPulse->Start = (int16_t)(pTail);
	AvPulse->End = (int16_t)(pTail + LengthAvPulse - 1);
	AvPulse->FLength = LengthAvPulse;
	AvPulse->FSize = LengthAvPulse + 1*pTail;
	if (!Validate(AvPulse))
	{
		return false;
	}
	// Initialisation of AvPulse for summarisation
	for (int16_t i = 0; i < AvPulse->FSize; i++)
	{
		double lsum = 0;
		int16_t lCountPulses = 0;
		for (int16_t np = 0; np < NofPulses; np++)
		{
			if (i < Pulses[np].FSize)
			{
				// Shift Up Pulse[np] from Pulse[0]
				float lUpStep = Pulses[np].Profile[Pulses[np].Start] - Pulses[0].Profile[Pulses[0].Start];
				lsum += Pulses[np].Profile[i] - lUpStep;
				lCountPulses++;
			}
		}
		if (lCountPulses < 1)
		{
			return false;
		}
		AvPulse->Profile[i] = (float)(lsum/lCountPulses);
	}
	AvPulse->Index = 0;

	if (AvPulse->FLength < PRESSURE_PULSE_MINLENGTH || AvPulse->FLength > PRESSURE_PULSE_MAXLENGTH/**ExpandFactor*/)
	{
		return false;
	}
	return true;
}