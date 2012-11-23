/*
 * pressure.c
 *
 * Created: 12/10/2012 1:45:07 PM
 *  Author: yoonl
 */ 

#include "pressure.h"
#include "usart/usart_rxtx.h"
#include "math_pwa.h"
#include "pwa_signal.h"
#include "pwa_data.h"
#include "pwa.h"

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
	
	Pulses = (Pulse *)malloc(sizeof(Pulse)*PRESSURE_MAX_PULSES);
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
		Pulses[i].Profile = NULL;
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
	AvPulse = (Pulse *)malloc(sizeof(Pulse));
	if (AvPulse == NULL)
	{
		return false;
	}
	
	AvPulse->Profile = malloc(sizeof(float)*PRESSURE_PULSE_MAXLENGTH);
	if (AvPulse->Profile == NULL)
	{
		return false;
	}
	
	AvPulse->Index = -1;
	AvPulse->Start = 0;
	AvPulse->End = 0;
	AvPulse->FLength = 0;
	AvPulse->FSize = 0;
	memset(AvPulse->Profile, 0, sizeof(float)*PRESSURE_PULSE_MAXLENGTH);
	
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
		if (AvPulse->Profile != NULL)
		{
			free(AvPulse->Profile);
			AvPulse->Profile = NULL;
		}
		free(AvPulse);
		AvPulse = NULL;
	}
}

/* ###########################################################################
 ** Periph_CalAvPulse_init()
 **
 ** DESCRIPTION
 **  Initailise Periph_CalAvPulse properties
 */
bool Periph_CalAvPulse_init(void)
{
	Periph_CalAvPulse = (Pulse *)malloc(sizeof(Pulse));
	if (Periph_CalAvPulse == NULL)
	{
		return false;
	}
	
	Periph_CalAvPulse->Profile = malloc(sizeof(float)*PRESSURE_PULSE_MAXLENGTH);
	if (Periph_CalAvPulse->Profile == NULL)
	{
		return false;
	}
	
	Periph_CalAvPulse->Index = -1;
	Periph_CalAvPulse->Start = 0;
	Periph_CalAvPulse->End = 0;
	Periph_CalAvPulse->FLength = 0;
	Periph_CalAvPulse->FSize = 0;
	memset(Periph_CalAvPulse->Profile, 0, sizeof(float)*PRESSURE_PULSE_MAXLENGTH);
	
	return true;
}

/* ###########################################################################
 ** Periph_CalAvPulse_final()
 **
 ** DESCRIPTION
 **  Finalise Periph_CalAvPulse properties
*/
void Periph_CalAvPulse_final(void)
{
	if (Periph_CalAvPulse != NULL)
	{
		if (Periph_CalAvPulse->Profile != NULL)
		{
			free(Periph_CalAvPulse->Profile);
			Periph_CalAvPulse->Profile = NULL;
		}
		free(Periph_CalAvPulse);
		Periph_CalAvPulse = NULL;
	}
}

/* ###########################################################################
 ** Central_CalAvPulse_init()
 **
 ** DESCRIPTION
 **  Initailise Central_CalAvPulse properties
 */
bool Central_CalAvPulse_init(void)
{
	Central_CalAvPulse = (Pulse *)malloc(sizeof(Pulse));
	if (Central_CalAvPulse == NULL)
	{
		return false;
	}
	
	Central_CalAvPulse->Profile = malloc(sizeof(float)*PRESSURE_PULSE_MAXLENGTH);
	if (Central_CalAvPulse->Profile == NULL)
	{
		return false;
	}
	
	Central_CalAvPulse->Index = -1;
	Central_CalAvPulse->Start = 0;
	Central_CalAvPulse->End = 0;
	Central_CalAvPulse->FLength = 0;
	Central_CalAvPulse->FSize = 0;
	memset(Central_CalAvPulse->Profile, 0, sizeof(float)*PRESSURE_PULSE_MAXLENGTH);
	
	return true;
}

/* ###########################################################################
 ** Central_CalAvPulse_final()
 **
 ** DESCRIPTION
 **  Finalise Central_CalAvPulse properties
*/
void Central_CalAvPulse_final(void)
{
	if (Central_CalAvPulse != NULL)
	{
		if (Central_CalAvPulse->Profile != NULL)
		{
			free(Central_CalAvPulse->Profile);
			Central_CalAvPulse->Profile = NULL;
		}
		free(Central_CalAvPulse);
		Central_CalAvPulse = NULL;
	}
}

/* ###########################################################################
 ** ExpPulses_init()
 **
 ** DESCRIPTION
 **  Initailise ExpPulse,Der1ExpPulse,Der2ExpPulse,Der3ExpPulse properties
 */
bool ExpPulses_init(void)
{
	ExpPulse = (Pulse *)malloc(sizeof(Pulse));
	if (ExpPulse == NULL)
	{
		return false;
	}
	ExpPulse->Profile = malloc(sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	if (ExpPulse->Profile == NULL)
	{
		return false;
	}
	ExpPulse->Index = -1;
	ExpPulse->Start = 0;
	ExpPulse->End = 0;
	ExpPulse->FLength = 0;
	ExpPulse->FSize = 0;
	memset(ExpPulse->Profile, 0, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	
	Der1ExpPulse = (Pulse *)malloc(sizeof(Pulse));
	if (Der1ExpPulse == NULL)
	{
		return false;
	}
	Der1ExpPulse->Profile = malloc(sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	if (Der1ExpPulse->Profile == NULL)
	{
		return false;
	}
	Der1ExpPulse->Index = -1;
	Der1ExpPulse->Start = 0;
	Der1ExpPulse->End = 0;
	Der1ExpPulse->FLength = 0;
	Der1ExpPulse->FSize = 0;
	memset(Der1ExpPulse->Profile, 0, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	
	Der2ExpPulse = (Pulse *)malloc(sizeof(Pulse));
	if (Der2ExpPulse == NULL)
	{
		return false;
	}
	Der2ExpPulse->Profile = malloc(sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	if (Der2ExpPulse->Profile == NULL)
	{
		return false;
	}
	Der2ExpPulse->Index = -1;
	Der2ExpPulse->Start = 0;
	Der2ExpPulse->End = 0;
	Der2ExpPulse->FLength = 0;
	Der2ExpPulse->FSize = 0;
	memset(Der2ExpPulse->Profile, 0, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	
	Der3ExpPulse = (Pulse *)malloc(sizeof(Pulse));
	if (Der3ExpPulse == NULL)
	{
		return false;
	}
	Der3ExpPulse->Profile = malloc(sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	if (Der3ExpPulse->Profile == NULL)
	{
		return false;
	}
	Der3ExpPulse->Index = -1;
	Der3ExpPulse->Start = 0;
	Der3ExpPulse->End = 0;
	Der3ExpPulse->FLength = 0;
	Der3ExpPulse->FSize = 0;
	memset(Der3ExpPulse->Profile, 0, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	
	return true;
}

/* ###########################################################################
 ** ExpPulses_final()
 **
 ** DESCRIPTION
 **  Finalise ExpPulse,Der1ExpPulse,Der2ExpPulse,Der3ExpPulse properties
*/
void ExpPulses_final(void)
{
	if (ExpPulse != NULL)
	{
		if (ExpPulse->Profile != NULL)
		{
			free(ExpPulse->Profile);
			ExpPulse->Profile = NULL;
		}
		free(ExpPulse);
		ExpPulse = NULL;
	}
	
	if (Der1ExpPulse != NULL)
	{
		if (Der1ExpPulse->Profile != NULL)
		{
			free(Der1ExpPulse->Profile);
			Der1ExpPulse->Profile = NULL;
		}
		free(Der1ExpPulse);
		Der1ExpPulse = NULL;
	}
	
	if (Der2ExpPulse != NULL)
	{
		if (Der2ExpPulse->Profile != NULL)
		{
			free(Der2ExpPulse->Profile);
			Der2ExpPulse->Profile = NULL;
		}
		free(Der2ExpPulse);
		Der2ExpPulse = NULL;
	}
	
	if (Der3ExpPulse != NULL)
	{
		if (Der3ExpPulse->Profile != NULL)
		{
			free(Der3ExpPulse->Profile);
			Der3ExpPulse->Profile = NULL;
		}
		free(Der3ExpPulse);
		Der3ExpPulse = NULL;
	}
}

/* ###########################################################################
 ** CalcPulses ()
 **
 ** DESCRIPTION
 **  Calculate Pulses using trigger points
 ** INPUT
 **  pTail, pOnsetsLength, pFloatSignal
 ** OUTPUT
 **  TrigPts - integerOnsets
 ** RETURN
 **  boolean success or not
*/
bool CalcPulses(const int8_t pTail, const uint16_t pOnsetsLength, const float *pFloatSignal, const int16_t *TrigPts)
{
	if (pOnsetsLength <= 1)
	{
		return false;
	}
	// Calculate average length
	float lAvLength = 0.;
	int16_t NofAv = 0;
	for (int16_t i=0; i < pOnsetsLength - 1; i++)
	{
		int16_t lLength = TrigPts[i+1] - TrigPts[i] + 1;
		if (lLength < PRESSURE_PULSE_MAXLENGTH && lLength > PRESSURE_PULSE_MINLENGTH)
		{
			lAvLength += lLength;
			NofAv++;
		}
	}
	if (NofAv <= 0)
	{
		return false;
	}		

	lAvLength /= NofAv;
	// Calculate pulses rejecting extra short and long pulses
	NofPulses = 0;
	for (uint16_t i=0; i < pOnsetsLength - 1; i++)
	{
		int16_t lLength = TrigPts[i+1] - TrigPts[i] + 1;
		if (lLength > PRESSURE_PULSE_MAXLENGTH || lLength < PRESSURE_PULSE_MINLENGTH)
		{
			continue;
		}			
		if ((lLength >= lAvLength*PWA_MIN_VALID_PULSELENGTH_PERCENT) &&
			(lLength <= lAvLength*PWA_MAX_VALID_PULSELENGTH_PERCENT))
		{
			int16_t index = TrigPts[i] - pTail;
			if (index < 0) // Miss first trigger point if it is too close to the start
			{
				continue;
			}				
			Pulses[NofPulses].Profile = (float *)(&pFloatSignal[index]);
			Pulses[NofPulses].Start = pTail;
			Pulses[NofPulses].Index = TrigPts[i];
			Pulses[NofPulses].End = (int16_t)(pTail + lLength - 1);
			Pulses[NofPulses].FLength = lLength;
			Pulses[NofPulses].FSize = lLength + 1*pTail;
			NofPulses++;
		}
	}
	return (NofPulses > 1);
}

/* ###########################################################################
 ** AveragePulse (...)
 **
 ** DESCRIPTION
 **  Find Average Pulse from Pulses
 ** INPUT
 **  pLength - predefined pulse Length (0 for periph, >0 for central)
 **  pTail, pSignalSampleRate
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

	if (AvPulse->FLength < PRESSURE_PULSE_MINLENGTH || AvPulse->FLength > PRESSURE_PULSE_MAXLENGTH)
	{
		return false;
	}
	return true;
}

/* ###########################################################################
 ** CalibratePulse()
 **
 ** DESCRIPTION
 **  Calibrate Pulse using formula:
 **  Cal = Gain*UnCal + Offset
 **  and finding min, max
 ** INPUT
 **  pGain, pOffset - gain and offset
 **  pAvPulse
 ** OUTPUT
 **  pMin, pMax, pCalAvPulse
*/
void CalibratePulse(const float pGain, const float pOffset, const Pulse *pAvPulse, float *pMin, float *pMax, Pulse *pCalAvPulse)
{
	// Transforming
	for (int16_t i = 0; i < pAvPulse->FSize; i++)
	{
		pCalAvPulse->Profile[i] = pGain * pAvPulse->Profile[i] + pOffset;
		// Find Min, Max
		if (i==pAvPulse->Start)
		{
			*pMin = pCalAvPulse->Profile[pCalAvPulse->Start];
			*pMax = pCalAvPulse->Profile[pCalAvPulse->Start];
		}
		else if (i > pAvPulse->Start && i <= pAvPulse->End)
		{
			if (pCalAvPulse->Profile[i] > *pMax)
			{
				*pMax = pCalAvPulse->Profile[i];
			}				
			if (pCalAvPulse->Profile[i] < *pMin)
			{
				*pMin = pCalAvPulse->Profile[i];
			}				
		}
	}
	// Setup length
	pCalAvPulse->Start = pAvPulse->Start;
	pCalAvPulse->Index  = pAvPulse->Index;
	pCalAvPulse->End = pAvPulse->Start + pAvPulse->FLength - 1;
	pCalAvPulse->FLength = pAvPulse->FLength;
	pCalAvPulse->FSize = pAvPulse->FSize;
}

/* ###########################################################################
 ** ExpandPulse ()
 **
 ** DESCRIPTION
 **  Expand pPulse from pPulse->Length to ExpPulse->Length points, 1024 sample rate,
 **  with analitical calculation of expanded profile and its derivatives
 **  using polinomial spline interpolation
 ** INPUT
 **  pPulse - pulse (for example, Calibrated Average pulse)
 **  pExpandFactor
 ** OUTPUT
 **  ExpPulse, Der1ExpPulse, Der2ExpPulse, Der3ExpPulse- expanded pulse and its derivatives
 ** RETURN
 **  boolean success or not
*/
bool ExpandPulse(Pulse *pPulse, const int8_t pExpandFactor)
{
	// Pulse Validation
	if (pPulse == NULL || !Validate(pPulse))
	{
		return false;
	}
	if (pExpandFactor < 1)
	{
		return false;
	}

	ExpPulse->Start = (int16_t)(pPulse->Start * pExpandFactor);
	ExpPulse->End = ExpPulse->Start + ((pPulse->FLength - 1) * pExpandFactor + 1) - 1;
	ExpPulse->FLength = (pPulse->FLength - 1) * pExpandFactor + 1;

	Der1ExpPulse->End = Der1ExpPulse->Start + ExpPulse->FLength - 1;
	Der1ExpPulse->FLength = ExpPulse->FLength;
	Der2ExpPulse->End = Der1ExpPulse->Start + ExpPulse->FLength - 1;
	Der2ExpPulse->FLength = ExpPulse->FLength;
	Der3ExpPulse->End = Der1ExpPulse->Start + ExpPulse->FLength - 1;
	Der3ExpPulse->FLength = ExpPulse->FLength;

	ExpPulse->FSize = (pPulse->FSize - 1) * pExpandFactor + 1;
	Der1ExpPulse->FSize = ExpPulse->FSize;
	Der2ExpPulse->FSize = ExpPulse->FSize;
	Der3ExpPulse->FSize = ExpPulse->FSize;

	float lMaxDer1=0, lMaxDer2=0, lMaxDer3=0;
	float Der1Step = (float)1/10;
	int8_t SplineOrder = 3;  // Cubic splines - optimal
	int8_t SmoothOrder = 3;  // Optimal smooth order formula
	
	// If ExpandFactor = 1 - copy Pulse into ExpPulse and find derivatives
	if (pExpandFactor == 1)
	{
		memcpy(ExpPulse->Profile, pPulse->Profile, pPulse->FSize * sizeof(float));
		Math_SmoothFirstDerivative(pPulse->Profile, pPulse->FSize, SmoothOrder, Der1Step, Der1ExpPulse->Profile, &lMaxDer1);
		Math_SmoothFirstDerivative(Der1ExpPulse->Profile, pPulse->FSize, SmoothOrder, (float)1/5, Der2ExpPulse->Profile, &lMaxDer2);
		Math_SmoothFirstDerivative(Der2ExpPulse->Profile, pPulse->FSize, SmoothOrder, (float)1/5, Der3ExpPulse->Profile, &lMaxDer3);
		return true;
	}

	// Scale coefficient
	float Scale = (float)1 / pExpandFactor;

	// step-by-step polinomial interpolation for function and derivatives
	// ------------------------------------------------------------------

	// First and second derivatives of Raw Pulse
	uint16_t lpSize = pPulse->FSize;
	// Derivatives1 is used in this ExpandPulse() only to expand. Let's temporally use it here.
	float *tmpDerivatives1 = malloc(sizeof(float)*PRESSURE_MAX_PPOINTS);
	if (tmpDerivatives1 == NULL)
	{
		print_debug("Error: failed to allocate memory for tmpDerivatives1.\r\n");
		return false;
	}
	memset(tmpDerivatives1, 0, sizeof(float)*PRESSURE_MAX_PPOINTS);
	
	Math_SmoothFirstDerivative(pPulse->Profile, lpSize, SmoothOrder, Der1Step, tmpDerivatives1, &lMaxDer1);
	Math_SmoothFirstDerivative(tmpDerivatives1, lpSize, SmoothOrder, (float)1/5, &tmpDerivatives1[lpSize], &lMaxDer2);
	Math_SmoothFirstDerivative(&tmpDerivatives1[lpSize], lpSize, SmoothOrder, (float)1/2, &tmpDerivatives1[2*lpSize], &lMaxDer3);
	
	// Interpolation of Raw profile and derivatives
	unsigned short SplineIndex = 0; // Initial spline index
	for (int i = 0; i < ExpPulse->FSize; i++)
	{
		float fj = Scale * i; // fj is an image of ExPulse x-point on pPulse->x-point
	
		// Find SplineIndex - beginning of a spline
		Math_GetSplineIndex(fj, SplineIndex, pPulse->FSize, &SplineIndex);
		// Profile
		Math_Spline (fj - SplineIndex, &pPulse->Profile[SplineIndex], SplineOrder, &(ExpPulse->Profile[i]), NULL, 0);
		// First derivative
		Math_Spline (fj - SplineIndex, &tmpDerivatives1[SplineIndex], SplineOrder, &(Der1ExpPulse->Profile[i]), NULL, 0);
		// Second derivative
		Math_Spline (fj - SplineIndex, &tmpDerivatives1[lpSize + SplineIndex], SplineOrder, &(Der2ExpPulse->Profile[i]), NULL, 0);
		// Third derivative
		Math_Spline (fj - SplineIndex, &tmpDerivatives1[2*lpSize + SplineIndex], SplineOrder, &(Der3ExpPulse->Profile[i]), NULL, 0);
	}
	
	free(tmpDerivatives1);
	tmpDerivatives1 = NULL;

	return true;
}

/* ###########################################################################
 ** SystolicOnset()
 **
 ** DESCRIPTION
 **  Find systolic onset (trigger point) for a pulse,
 **  line up (shift) pulse profile and derivatives to it and cut pulse tale
 ** INPUT
 **  pAlgorithm (PWA_TANGENT_DER2_ALGORITHM) - algorithm type to calculate onset
 **  pLengthOfRadial, pExpPulseSampleRate
 ** OUTPUT
 **  Exapanded pulses
 ** RETURN
 **  boolean success or not
*/
bool SystolicOnset(const int8_t pAlgorithm, const int16_t pLengthOfRadial, const int16_t pExpPulseSampleRate, Pulse *pExpPulse, Pulse *pDer1ExpPulse, Pulse *pDer2ExpPulse, Pulse *pDer3ExpPulse)
{
	int16_t lExpandFactor = pExpPulseSampleRate / MEAS_DEFAULT_SAMPLE_RATE;
	if (lExpandFactor <= 0)
	{
		return false;
	}		
	// Find systolic onset as a peak of der2
	// Find pulse top
	int16_t lTop = IndexOfMax(0, pExpPulse->End/2, pExpPulse);
	if (lTop <= 0)
	{
		return false;
	}		
	// Find peak of der1
	int16_t lPeakOfDer1 = IndexOfExtremum(pDer1ExpPulse, MAX, GLOBAL, 0, lTop - 1, lExpandFactor, LESS, DEFAULT_VALUE, NULL, 
		NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0);
	if (lPeakOfDer1 <= 0)
	{
		return false;
	}		
	// Find peak of der2
	int16_t lPeakOfDer2 = IndexOfExtremum(pDer2ExpPulse, MAX, GLOBAL, 0, lPeakOfDer1 - 1, lExpandFactor, LESS, DEFAULT_VALUE, NULL,
		NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0);
	if (lPeakOfDer2 <= 0)
	{
		return false;
	}		
	// Find the foot
	int16_t lFoot = -1;
	for (int16_t j=lPeakOfDer2; j>=0; j--)
	{
		if ((j == 0) || (pExpPulse->Profile[j] <= pExpPulse->Profile[j-1]))
		{
			lFoot = j;
			break;
		}
	}
	if (lFoot < 0)
	{
		lFoot = 0;
	}		

	// switch between algorithm
	int16_t lSystolicOnset = -1;
	switch (pAlgorithm)
	{
	case PWA_DER1_ALGORITHM:
		lSystolicOnset = lFoot;
		break;
	case PWA_DER2_ALGORITHM:
		lSystolicOnset = lPeakOfDer2;
		break;
	case PWA_TANGENT_DER1_ALGORITHM:
		break;
	case PWA_TANGENT_DER2_ALGORITHM:
		{
			// Calculate tangent
			// tangent is a Der1 value in point maxD2
			double lTangent;
			float Der1Step = (float)1/10;
			float D1F = Der1Step/(float)lExpandFactor;
			lTangent = pDer1ExpPulse->Profile[lPeakOfDer2]*D1F;
			if (lTangent <= 0.)
			{
				return false;
			}				
			// After foot has been found
			// Solve triangle to get time-shift
			float lVertShoulder = pExpPulse->Profile[lPeakOfDer2] - pExpPulse->Profile[lFoot];
			float lHorizShoulder = (float)(lVertShoulder/lTangent);
			// Find onset
			float lFloatOnset = (float)lPeakOfDer2 - lHorizShoulder;
			if (lFloatOnset <= lFoot)
			{
				lFloatOnset = (float)lFoot;
			}				
			Math_Round(lFloatOnset, &lSystolicOnset);
			break;
		}
	}

	if (lSystolicOnset < 0)
	{
		return false;
	}		

	if (lSystolicOnset > pExpPulse->Start)
	{
		lSystolicOnset = pExpPulse->Start;
	}		

	// Shift ExpPulse and derivatives
	int16_t lLength = (pLengthOfRadial <= 0 ? pExpPulse->FLength : pLengthOfRadial);
	for (int16_t i=0; i<lLength; i++)
	{
		pExpPulse->Profile[i] = pExpPulse->Profile[lSystolicOnset + i];
		pDer1ExpPulse->Profile[i] = pDer1ExpPulse->Profile[lSystolicOnset + i];
		pDer2ExpPulse->Profile[i] = pDer2ExpPulse->Profile[lSystolicOnset + i];
		pDer3ExpPulse->Profile[i] = pDer3ExpPulse->Profile[lSystolicOnset + i];
	}
	pExpPulse->Start = 0;
	pExpPulse->End = pExpPulse->Start + lLength - 1;
	pExpPulse->FLength = lLength;
	pDer1ExpPulse->End = pExpPulse->Start + lLength - 1;
	pDer1ExpPulse->FLength = lLength;
	pDer2ExpPulse->End = pExpPulse->Start + lLength - 1;
	pDer2ExpPulse->FLength = lLength;
	pDer3ExpPulse->End = pExpPulse->Start + lLength - 1;
	pDer3ExpPulse->FLength = lLength;

	pExpPulse->FSize = lLength;
	pDer1ExpPulse->FSize = lLength;
	pDer2ExpPulse->FSize = lLength;
	pDer3ExpPulse->FSize = lLength;

	return true;
}

/* ###########################################################################
 ** PeriphExtractFeatures()
 **
 ** DESCRIPTION
 **  Extract specific feature parameters for Periph Pressure
 ** INPUT
 ** OUTPUT
 **  Specific feature parameters for Periph Pressure
 ** RETURN
*/
void PeriphExtractFeatures(void)
{
	if (Brachial_SP > Brachial_DP)
	{
		PeriphParams->PP = Brachial_SP - Brachial_DP;
	}
}

/* ###########################################################################
 ** CentralExtractFeatures()
 **
 ** DESCRIPTION
 **  Extract specific feature parameters (HR, AGPH, ...) for Cenral Pressure
 ** INPUT
 **  pEDIndex, pExpPulse
 ** OUTPUT
 **  Specific feature parameters (HR, AGPH, ...) for Cenral Pressure
 ** RETURN
 **  boolean success or not
*/
bool CentralExtractFeatures(const int16_t pEDIndex, const Pulse *pExpPulse)
{
	float P1 = DEFAULT_VALUE, P2 = DEFAULT_VALUE;
			
	if (Validate(pExpPulse) == false)
	{
		return false;
	}
	
	// Heart rate (bpm) = 60000./Period
	CentralParams->HR = ((float)60 * (MEAS_DEFAULT_SAMPLE_RATE*EXPPULSE_MAX_EXPAND_FACTOR)) / pExpPulse->End;
	
	// Validate whether expanded pulse is shifted properly to systolic onset
	if (pExpPulse->FLength != pExpPulse->FSize || pExpPulse->Start != 0)
	{
		return false;
	}
	// Mean Pressure  mmHg
	if (pExpPulse->FLength > 1)
	{
		CentralParams->MeanP = Integral(pExpPulse->Start, pExpPulse->End, pExpPulse) / (pExpPulse->FLength - 1);
	}
	
	if (pEDIndex == DEFAULT_VALUE || pEDIndex < 0)
	{
		return false;
	}
	if (CentralParams->ExpPulse_T1 != DEFAULT_VALUE)
	{
		P1 = PressureValue((float)CentralParams->ExpPulse_T1, pExpPulse);
	}
	if (CentralParams->ExpPulse_T2 != DEFAULT_VALUE)
	{
		P2 = PressureValue((float)CentralParams->ExpPulse_T2, pExpPulse);
	}
	if ((P1 != DEFAULT_VALUE) && (P2 != DEFAULT_VALUE))
	{
		CentralParams->AP  = P2 - P1;
	}
	
	if (CentralParams->SP != DEFAULT_VALUE && CentralParams->DP != DEFAULT_VALUE)
	{
		if (CentralParams->SP > CentralParams->DP)
		{
			CentralParams->PP  = CentralParams->SP - CentralParams->DP;
		}
	}
	
	// AG/PH in %
	if ((CentralParams->PP != DEFAULT_VALUE) && (CentralParams->AP != DEFAULT_VALUE))
	{
		CentralParams->AGPH = CentralParams->AP/CentralParams->PP * 100;
	}
	if (CentralParams->AGPH != DEFAULT_VALUE && CentralParams->HR != DEFAULT_VALUE)
	{
		if (CentralParams->HR < 40 || CentralParams->HR > 110)
		{
			CentralParams->AGPH_HR75 = DEFAULT_VALUE;
		}
		else
		{
			CentralParams->AGPH_HR75 = (float)(-0.48 * (75 - CentralParams->HR)) + CentralParams->AGPH;
		}
	}
	else
	{
		CentralParams->AGPH_HR75 = DEFAULT_VALUE;
	}
	
	return true;
}