/*
 * pwa.c
 *
 * Created: 10/10/2012 11:29:11 AM
 *  Author: yoonl
 */ 

#include "pwa.h"
#include "buffer.h"
#include "usart/usart_rxtx.h"
#include "pwa_data.h"
#include "pwa_signal.h"
#include "pressure.h"
#include "pulse.h"

#include "math_pwa.h"

#define PWA_ED_TOP_PERCENT					(float)0.75  // ED cannot be more then 65% of Length
#define PWA_EFFECTIVE_PULSE_LENGTH_PERCENT	(float)0.75 // percent to calculate min value for calibration
#define PWA_NOF_DELAY_SAMPLES				(int8_t)8
#define PWA_CUFF_INFLATE_PRESSURE_SUBTRACT	(int8_t)10


/* ###########################################################################
 ** FloatSignal_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise floatSignal properties
 */
bool FloatSignal_init(void)
{
	floatSignal = malloc(sizeof(float)*PRESSURE_MAX_PPOINTS);
	if (floatSignal == NULL)
	{
		return false;
	}
	
	memset(floatSignal, 0, sizeof(float)*PRESSURE_MAX_PPOINTS);
	return true;
}

/* ###########################################################################
 ** FloatSignal_final()
 **
 ** DESCRIPTION
 **  Free floatSignal properties
*/
void FloatSignal_final(void)
{
	if (floatSignal != NULL)
	{
		free(floatSignal);
		floatSignal = NULL;
	}
}

/* ###########################################################################
 ** IntegerOnsets_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise integerOnsets properties
 */
bool IntegerOnsets_init(void)
{
	integerOnsets = malloc(sizeof(int16_t)*PRESSURE_MAX_TPOINTS);
	if (integerOnsets == NULL)
	{
		return false;
	}
	
	memset(integerOnsets, -1, sizeof(int16_t)*PRESSURE_MAX_TPOINTS);
	return true;
}

/* ###########################################################################
 ** IntegerOnsets_final()
 **
 ** DESCRIPTION
 **  Free integerOnsets properties
*/
void IntegerOnsets_final(void)
{
	if (integerOnsets != NULL)
	{
		free(integerOnsets);
		integerOnsets = NULL;
	}
}

/* ###########################################################################
 ** Finalise()
 **
 ** DESCRIPTION
 **  Free all allocated memories
*/
void Finalise(void)
{
	FloatSignal_final();
	IntegerOnsets_final();
	Pulses_final();
	Derivatives_final();
	AvPulse_final();
}

/* ###########################################################################
 ** InitialDownSample()
 **
 ** DESCRIPTION
 **  Down sample from DEFAULT_SAMPLE_RATE to MEAS_DEFAULT_SAMPLE_RATE
 **  Only Tonometer signal is required to check the minimum acceptable digital unit threshold.
 ** INPUT
 **  pDownSampleRate: DEFAULT_SAMPLE_RATE/MEAS_DEFAULT_SAMPLE_RATE
 **  rawSignalLength: total points of raw signal
 ** OUTPUT
 **  BizPWASignal::floatSignal
*/
bool InitialDownSample(const uint8_t pDownSampleRate, const uint16_t rawSignalLength)
{
	if (pDownSampleRate <= 0 || rawSignalLength <= 0)
	{
		return false;
	}

	uint16_t lSize = (rawSignalLength - 1)/pDownSampleRate + 1;
	rawSignals = (uint16_t*)malloc(sizeof(uint16_t)*lSize);
	if (rawSignals == NULL)
	{
		print_debug("Error: failed to allocate memory rawSignals.\r\n");
		return false;
	}
	memset(rawSignals, 0, sizeof(uint16_t)*lSize);
	
	for (int i=0; i < lSize; i++)
	{
		rawSignals[i] = adc_buffer[i*pDownSampleRate];
		floatSignal[i] = (float)adc_buffer[i*pDownSampleRate];
		if (floatSignal[i] < PWA_ACCEPTABLE_DATA_THRESHOLD_TONOMETER)
		{
			print_debug("Error: capture signal is too low.\r\n");
			return false;
		}
	}
	signalLength = lSize;
	
	// Once we get down samples, we don't need circular adc_buffer.
	ADCBuffer_final();
	
	return true;
}

/* ###########################################################################
 ** ValidateBeforeCalculate()
 **
 ** DESCRIPTION
 **  Validate PWA properties before Calculation routine
 ** INPUT
 **  PWA properties
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
bool ValidateBeforeCalculate(void)
{
	if (signalLength < PRESSURE_PULSE_MAXLENGTH)
	{
		print_debug("Error: signal too short.\r\n");
		return false;
	}
	if (signalLength > PRESSURE_MAX_PPOINTS)
	{
		signalLength = PRESSURE_MAX_PPOINTS;
		print_debug("Warning: signal too long.\r\n");
	}
	
	return true;
}

/* ###########################################################################
 ** CalculateBrachial
 **
 ** DESCRIPTION
 **  Do all mathematics for Cuff measurement
 ** INPUT
 **  PWA class (source)
 ** OUTPUT
 **  boolean success or not
*/
bool CalculateBrachial(void)
{
	signalLength = 0;
	onsetsLength = 0;
	if (!FloatSignal_init())
	{
		print_debug("Error: failed to allocate memory for floatSignal.\r\n");
		return false;
	}
	if (!IntegerOnsets_init())
	{
		print_debug("Error: failed to allocate memory for integerOnsets.\r\n");
		return false;
	}
	
	if (!InitialDownSample(DEFAULT_SAMPLE_RATE/MEAS_DEFAULT_SAMPLE_RATE, PRESSURE_MAX_PPOINTS))
	{
		print_debug("Error: failed InitialDownSample().\r\n");
		return false;
	}
	
	if (!ValidateBeforeCalculate())
	{
		return false;
	}
	
	if (!Derivatives_init())
	{
		print_debug("Error: failed to allocate memory for Derivatives.\r\n");
		return false;
	}	
	if (!FindOnsets(PWA_DER2_ALGORITHM, PWA_NOF_DELAY_SAMPLES + 2, floatSignal, signalLength, &onsetsLength, integerOnsets, Derivatives1, Derivatives2))
	{
		print_debug("Error: failed FindOnsets().\r\n");
		return false;
	}
	Derivatives_final();
	
	if (!Pulses_init())
	{
		print_debug("Error: failed to allocate memory for Pulses.\r\n");
		return false;
	}	
	if (!CalcPulses(true, PWA_NOF_DELAY_SAMPLES, onsetsLength, floatSignal, integerOnsets))
	{
		print_debug("Error: failed CalcPulses().\r\n");
		return false;
	}
	IntegerOnsets_final();
	
	if (!AvPulse_init())
	{
		print_debug("Error: failed to allocate memory for AvPulse.\r\n");
		return false;
	}
	if (!AveragePulse(0, PWA_NOF_DELAY_SAMPLES, MEAS_DEFAULT_SAMPLE_RATE))
	{
		print_debug("Error: failed AveragePulse().\r\n");
		return false;
	}
	Pulses_final();
	
	if (!Smooth(AvPulse->Profile, AvPulse->FSize))
	{
		print_debug("Error: failed Brachial AvPulse Smooth().\r\n");
		return false;
	}
	
	if (!Validate(AvPulse))
	{
		print_debug("Error: failed Validate AvPulse after Smooth.\r\n");
		return false;
	}
	
	float *tmpSignal = malloc(sizeof(float)*PRESSURE_MAX_PPOINTS);
	if (tmpSignal == NULL)
	{
		print_debug("Error: failed to allocate memory for tmpSignal.\r\n");
		return false;
	}
	memset(tmpSignal, 0, sizeof(float)*PRESSURE_MAX_PPOINTS);
	int16_t x = 0;
	do
	{
		for (int16_t j = AvPulse->Start; j <= AvPulse->End; j++)
		{
			tmpSignal[x] = AvPulse->Profile[j];
			++x;
			if (x >= PRESSURE_MAX_PPOINTS)
			{
				break;
			}
		}
	} while (x <= PRESSURE_MAX_PPOINTS-1);
	
	Finalise();
	
	// Prepare floatSignal for Radial calculation before Brachial convolution.
	if (!FloatSignal_init())
	{
		print_debug("Error: failed to allocate memory for floatSignal.\r\n");
		return false;
	}
	
	Convolution_Brachial(tmpSignal);
	
	free(tmpSignal);
	tmpSignal = NULL;
	
	print_debug("Done CalculateBrachial().\r\n");
	
	return true;
}

/* ###########################################################################
 ** Convolution_Radial()
 **
 ** DESCRIPTION
 **  Convert Peripheral Signal To Central using convolution
 ** INPUT
 **  none.
 ** OUTPUT
 **  Central[0 : signalLength-NofTFC] - shifted central pressure signal
 **  Central[signalLength-NofTFC : signalLength] = 0 - tail of central pressure signal
 ** RETURN
 **  boolean success or not
*/
void Convolution_Radial(const float *pPulses)
{
	// Transformation coefficients for Radial type of measurement
	static const double coeff_radial[NOF_TF_COEFF] =
	{
		0.009862,			-0.000095,			-0.005618,			-0.003233,
		0.006131,			0.017503,			0.024616,			0.023522,
		0.014987,			0.004218,			-0.002010,			0.000762,
		0.012045,			0.026615,			0.037516,			0.040147,
		0.034989,			0.027256,			0.023525,			0.027286,
		0.036144,			0.042628,			0.038530,			0.020530,
		-0.006188,			-0.028806,			-0.032427,			-0.007839,
		0.042468,			0.103461,			0.152893,			0.170668,
		0.147910
	};
	
	double ld = 0.0;
	// calculate central (aortic) data
	for(int i = 0; i < signalLength; i++)
	{
		// Do not calculate Central for tail of a signal
		if (i > signalLength - NOF_TF_COEFF)
		{
			floatSignal[i] = 0.;
			continue;
		}
		// Calculate Central for actual signal
		ld = 0.0;
		for(int j = 0; j < NOF_TF_COEFF; j++ )
		{
			ld += coeff_radial[j] * pPulses[i+j];
		}
		floatSignal[i] = (float)ld;
	}
}

/* ###########################################################################
 ** Convolution_Brachial()
 **
 ** DESCRIPTION
 **  Convert PeriphBrachial's AvPulses to Peripheral Signal using convolution
 ** INPUT
 **  averagePulses - PeriphBrachial's AvPulses
 ** OUTPUT
 **  Periph->floatSignal
 ** RETURN
 **  boolean success or not
*/
void Convolution_Brachial(const float *averagePulses)
{
	// Transformation coefficients for Brachial type of measurement
	static const double coeff_brachial[NOF_TF_COEFF] =
	{
		0.0041491,		0.0022707,		0.0017829,		0.0039123,
		0.012659,		0.012573,		0.013907,		0.007776,
		0.0027408,		0.0062829,		0.018101,		0.038431,
		0.012004,		0.019161,		-0.020699,		-0.032209,
		-0.0027947,		0.023223,		0.035068,		-0.090998,
		0.0086391,		-0.20452,		-0.072118,		0.11899,
		0.099651,		0.11002,		-0.15731,		0.38602,
		-0.70907,		0.76256,		0.71102,		-0.24762,
		0.10266
	};
	
	double ld = 0.0;
	for (int16_t i = 0; i < signalLength; i++)
	{
		ld = 0.0;
		for (int16_t j = 0; j < NOF_TF_COEFF; j++)
		{
			ld += coeff_brachial[j] * averagePulses[i+j];
		}
		floatSignal[i] = (float)ld;
	}
}

/* ###########################################################################
 ** Calculate ()
 **
 ** DESCRIPTION
 **  Do all mathematics for this measurement
 ** INPUT
 **  PWA class (source)
 ** OUTPUT
 **  boolean success or not
*/
bool CalculateRadial(float pCalibrationFactor)
{
	onsetsLength = 0;
	if (!IntegerOnsets_init())
	{
		print_debug("Error: failed to allocate memory for integerOnsets.\r\n");
		return false;
	}
	
	if (!ValidateBeforeCalculate())
	{
		return false;
	}
	
	// Convolution_Radial will change floatSignal, let's use tmpSignal to store floatSignal.
	float *tmpSignalBrachialAverage = malloc(sizeof(float)*PRESSURE_MAX_PPOINTS);
	if (tmpSignalBrachialAverage == NULL)
	{
		print_debug("Error: failed to allocate memory for tmpSignalBrachialAverage.\r\n");
		return false;
	}
	memset(tmpSignalBrachialAverage, 0, sizeof(float)*PRESSURE_MAX_PPOINTS);
	memcpy(tmpSignalBrachialAverage, floatSignal, sizeof(float)*PRESSURE_MAX_PPOINTS);
	memset(floatSignal, 0, sizeof(float)*PRESSURE_MAX_PPOINTS);
	Convolution_Radial(tmpSignalBrachialAverage);
	free(tmpSignalBrachialAverage);
	tmpSignalBrachialAverage = NULL;
	
	print_debug("Done CalculateRadial().\r\n");
	
	return true;
}