/*
 * pwa.c
 *
 * Created: 10/10/2012 11:29:11 AM
 *  Author: yoonl
 */ 

#include <malloc.h>
#include "pwa.h"
#include "buffer.h"
#include "usart/usart_rxtx.h"
#include "pwa_data.h"
#include "pwa_signal.h"
#include "pressure.h"
#include "pulse.h"
#include "buffer.h"

#define PWA_ED_TOP_PERCENT					(float)0.75
#define PWA_EFFECTIVE_PULSE_LENGTH_PERCENT	(float)0.75 // percent to calculate min value for calibration
#define PWA_NOF_DELAY_SAMPLES				(int8_t)8
#define PWA_CUFF_INFLATE_PRESSURE_SUBTRACT	(int8_t)10

/* ###########################################################################
 ** RawSignal_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise rawSignal properties
 */
bool RawSignal_init(uint16_t pSize)
{
	rawSignal = malloc(sizeof(uint16_t)*pSize);
	if (rawSignal == NULL)
	{
		return false;
	}
	
	memset(rawSignal, 0, sizeof(uint16_t)*pSize);
	return true;
}

/* ###########################################################################
 ** RawSignal_final()
 **
 ** DESCRIPTION
 **  Free rawSignal properties
*/
void RawSignal_final(void)
{
	if (rawSignal != NULL)
	{
		free(rawSignal);
		rawSignal = NULL;
	}
}

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
bool Central_FloatSignal_init(void)
{
	Central_floatSignal = malloc(sizeof(float)*PRESSURE_MAX_PPOINTS);
	if (Central_floatSignal == NULL)
	{
		return false;
	}
	
	memset(Central_floatSignal, 0, sizeof(float)*PRESSURE_MAX_PPOINTS);
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
void Central_FloatSignal_final(void)
{
	if (Central_floatSignal != NULL)
	{
		free(Central_floatSignal);
		Central_floatSignal = NULL;
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
bool Central_IntegerOnsets_init(void)
{
	Central_integerOnsets = malloc(sizeof(int16_t)*PRESSURE_MAX_TPOINTS);
	if (Central_integerOnsets == NULL)
	{
		return false;
	}
	
	memset(Central_integerOnsets, -1, sizeof(int16_t)*PRESSURE_MAX_TPOINTS);
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
void Central_IntegerOnsets_final(void)
{
	if (Central_integerOnsets != NULL)
	{
		free(Central_integerOnsets);
		Central_integerOnsets = NULL;
	}
}

/* ###########################################################################
 ** PeriphParams_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise PeriphParams properties
 */
bool PeriphParams_init(void)
{
	PeriphParams = (Peripheral_Parameters *)malloc(sizeof(Peripheral_Parameters));
	if (PeriphParams == NULL)
	{
		return false;
	}
	
	PeriphParams->Gain = 0;
	PeriphParams->Offset = 0;
	PeriphParams->IntegralAver = 0;
	PeriphParams->PeriphMainPeak = 0;
	PeriphParams->ExpPulse_T1 = DEFAULT_VALUE;
	PeriphParams->ExpPulse_T2 = DEFAULT_VALUE;
	PeriphParams->ExpPulse_T2m = -1;
	PeriphParams->ExpPulse_ShoulderAfterPeak = -1;
	PeriphParams->ExpPulse_ED = DEFAULT_VALUE;
	
	return true;
}

/* ###########################################################################
 ** PeriphParams_final()
 **
 ** DESCRIPTION
 **  Free PeriphParams properties
*/
void PeriphParams_final(void)
{
	if (PeriphParams != NULL)
	{
		free(PeriphParams);
		PeriphParams = NULL;
	}
}

/* ###########################################################################
 ** CentralParams_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise CentralParams properties
 */
bool CentralParams_init(void)
{
	CentralParams = (Central_Parameters *)malloc(sizeof(Central_Parameters));
	if (CentralParams == NULL)
	{
		return false;
	}
	
	CentralParams->ExpPulse_T1 = DEFAULT_VALUE;
	CentralParams->ExpPulse_T2 = DEFAULT_VALUE;
	CentralParams->SP = DEFAULT_VALUE;
	CentralParams->DP = DEFAULT_VALUE;
	CentralParams->MeanP = DEFAULT_VALUE;
	CentralParams->AGPH = DEFAULT_VALUE;
	CentralParams->AP = DEFAULT_VALUE;
	CentralParams->HR = DEFAULT_VALUE;
	CentralParams->SEVR = DEFAULT_VALUE;
	
	return true;
}

/* ###########################################################################
 ** CentralParams_final()
 **
 ** DESCRIPTION
 **  Free CentralParams properties
*/
void CentralParams_final(void)
{
	if (CentralParams != NULL)
	{
		free(CentralParams);
		CentralParams = NULL;
	}
}

/* ###########################################################################
 ** Initialise()
 **
 ** DESCRIPTION
 **  Initialise all parameters
*/
void Initialise(void)
{
	signalLength = 0;
	onsetsLength = 0;
	Central_onsetsLength = 0;
	Brachial_SP = 120;
	Brachial_DP = 80;
	Brachial_MeanP = 0;
}

void DisplayMemoryUsage(char *msg)
{
#ifdef _DEBUG
    struct mallinfo mi;

    mi = mallinfo();

    print_debug("  Heap usage %s\t(peak/in-use/freed) bytes: %d\t%d\t%d\n", 
        msg, mi.arena, mi.uordblks, mi.fordblks);
    //print_debug("Total non-mmapped bytes (arena):       %d\n", mi.arena);
    //print_debug("# of free chunks (ordblks):            %d\n", mi.ordblks);
    //print_debug("# of free fastbin blocks (smblks):     %d\n", mi.smblks);
    //print_debug("# of mapped regions (hblks):           %d\n", mi.hblks);
    //print_debug("Bytes in mapped regions (hblkhd):      %d\n", mi.hblkhd);
    //print_debug("Max. total allocated space (usmblks):  %d\n", mi.usmblks);
    //print_debug("Free bytes held in fastbins (fsmblks): %d\n", mi.fsmblks);
    //print_debug("Total allocated space (uordblks):      %d\n", mi.uordblks);
    //print_debug("Total free space (fordblks):           %d\n", mi.fordblks);
    //print_debug("Topmost releasable block (keepcost):   %d\n", mi.keepcost);
#endif
}


/* ###########################################################################
 ** Finalise()
 **
 ** DESCRIPTION
 **  Free all allocated memories
*/
void Finalise(void)
{
	DisplayMemoryUsage("before finalise");
	IntegerOnsets_final();
	Central_IntegerOnsets_final();
	Pulses_final();
	FloatSignal_final();
	Central_FloatSignal_final();
	Derivatives_final();
	AvPulse_final();
	ADCBuffer_final();
	ExpPulses_final();
	Periph_CalAvPulse_final();
	Central_CalAvPulse_final();
	PeriphParams_final();
	CentralParams_final();
	RawSignal_final();
	DisplayMemoryUsage("after finalise ");
}

/* ###########################################################################
 ** InitialDownSample()
 **
 ** DESCRIPTION
 **  Down sample from DEFAULT_SAMPLE_RATE to MEAS_DEFAULT_SAMPLE_RATE
 ** INPUT
 **  pDownSampleRate: DEFAULT_SAMPLE_RATE/MEAS_DEFAULT_SAMPLE_RATE
 **  rawSignalLength: total points of raw signal
 ** OUTPUT
 **  rawSignal - Original signals as integer value
 **  floatSignal - will be changed for convolution and calculation
*/
bool InitialDownSample(const uint8_t pDownSampleRate, const uint16_t rawSignalLength)
{
	if (pDownSampleRate <= 0 || rawSignalLength <= 0 || floatSignal == NULL)
	{
		return false;
	}

	uint16_t lSize = (rawSignalLength - 1)/pDownSampleRate + 1;
	
	RawSignal_final();
	if (!RawSignal_init(lSize))
	{
		print_debug("Error: failed to allocate memory for rawSignal.\r\n");
		return false;
	}
	
	for (uint16_t i=0; i < lSize; i++)
	{
		rawSignal[i] = adc_buffer[i*pDownSampleRate];
		floatSignal[i] = (float)adc_buffer[i*pDownSampleRate];
		if (floatSignal[i] < PWA_ACCEPTABLE_DATA_THRESHOLD)
		{
			print_debug("Error: capture signal is too low.\r\n");
			return false;
		}
	}
	signalLength = lSize;
	
	// Once we get down samples rawSignal(uint16_t, 128samples, 5seconds), we don't need adc_buffer.
	// We will save this rawSignal to Flash disk if all calculations are successful, and floatSignal will be used for convolution and calculation.
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
 ** CalculateBrachial()
 **
 ** DESCRIPTION
 **  Do all mathematics for Brachial Cuff measurement
 ** INPUT
 **  PWA properties
 ** OUTPUT
 **  boolean success or not
*/
bool CalculateBrachial(void)
{
	print_debug("Start CalculateBrachial().\r\n");
	Initialise();
	if (!FloatSignal_init())
	{
		print_debug("Error: failed to allocate memory for floatSignal.\r\n");
		return false;
	}
	
	if (!InitialDownSample(DEFAULT_SAMPLE_RATE/MEAS_DEFAULT_SAMPLE_RATE, ADC_BUF_SIZE))
	{
		print_debug("Error: failed InitialDownSample().\r\n");
		return false;
	}
	
	if (!ValidateBeforeCalculate())
	{
		return false;
	}
	
	if (!IntegerOnsets_init())
	{
		print_debug("Error: failed to allocate memory for integerOnsets.\r\n");
		return false;
	}
	if (!Derivatives_init())
	{
		print_debug("Error: failed to allocate memory for Derivatives.\r\n");
		return false;
	}
	// Trigger Points and Pulses
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
	if (!CalcPulses(PWA_NOF_DELAY_SAMPLES, onsetsLength, floatSignal, integerOnsets))
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
	FloatSignal_final();
	
	if (!Validate(AvPulse))
	{
		print_debug("Error: failed Validate AvPulse.\r\n");
		return false;
	}
	if (!Smooth(AvPulse->Profile, AvPulse->FSize))
	{
		print_debug("Error: failed Brachial AvPulse Smooth().\r\n");
		return false;
	}
	
	// Fill AvPulse into tmpSignal fully for convolution.
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
	
	// Convolution_Brachial will change Periph floatSignal, let's prepare floatSignal for Radial calculation before Brachial convolution.
	// floatSignal would be Periph raw signal after Convolution.
	if (!FloatSignal_init())
	{
		free(tmpSignal);
		tmpSignal = NULL;
		print_debug("Error: failed to allocate memory for floatSignal.\r\n");
		return false;
	}
	if (!Convolution_Brachial(tmpSignal))
	{
		free(tmpSignal);
		tmpSignal = NULL;
		print_debug("Error: failed Convolution_Brachial().\r\n");
		return false;
	}
	
	free(tmpSignal);
	tmpSignal = NULL;
	
	print_debug("Done CalculateBrachial().\r\n");
	
	return true;
}

/* ###########################################################################
 ** CalculateRadial()
 **
 ** DESCRIPTION
 **  Do all mathematics for this measurement
 ** INPUT
 **  PWA properties
 ** OUTPUT
 **  boolean success or not
*/
bool CalculateRadial(void)
{
	print_debug("Start CalculateRadial().\r\n");
	
	if (!ValidateBeforeCalculate())
	{
		return false;
	}
	
	onsetsLength = 0;
	if (!IntegerOnsets_init())
	{
		print_debug("Error: failed to allocate memory for integerOnsets.\r\n");
		return false;
	}
	if (!Derivatives_init())
	{
		print_debug("Error: failed to allocate memory for Derivatives.\r\n");
		return false;
	}
	// Trigger Points and Pulses
	if (!FindOnsets(PWA_DER2_ALGORITHM, PWA_NOF_DELAY_SAMPLES + 2, floatSignal, signalLength, &onsetsLength, integerOnsets, Derivatives1, Derivatives2))
	{
		print_debug("Error: failed FindOnsets().\r\n");
		return false;
	}
	Derivatives_final();
	
	if (!Central_FloatSignal_init())
	{
		print_debug("Error: failed to allocate memory for Central_floatSignal.\r\n");
		return false;
	}
	if (!Convolution_Radial(floatSignal))
	{
		print_debug("Error: failed Convolution_Radial().\r\n");
		return false;
	}
	
	Central_onsetsLength = 0;
	if (!Central_IntegerOnsets_init())
	{
		print_debug("Error: failed to allocate memory for Central integerOnsets.\r\n");
		return false;
	}
	if (!Derivatives_init())
	{
		print_debug("Error: failed to allocate memory for Derivatives.\r\n");
		return false;
	}
	// Trigger Points and Pulses
	if (!FindOnsets(PWA_DER2_ALGORITHM, PWA_NOF_DELAY_SAMPLES + 2, Central_floatSignal, signalLength, &Central_onsetsLength, Central_integerOnsets, Derivatives1, Derivatives2))
	{
		print_debug("Error: failed FindOnsets().\r\n");
		return false;
	}
	Derivatives_final();
	
	
	if (!RejectIrregularTrigPts())
	{
		print_debug("Error: failed RejectIrregularTrigPts().\r\n");
		return false;
	}
	
	
	/* #### begin Periph_CalAvPulse calculation #### */
	if (!Pulses_init())
	{
		print_debug("Error: failed to allocate memory for Pulses.\r\n");
		return false;
	}
	if (!CalcPulses(PWA_NOF_DELAY_SAMPLES, onsetsLength, floatSignal, integerOnsets))
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
	FloatSignal_final();
	
	if (!Validate(AvPulse))
	{
		print_debug("Error: failed Validate AvPulse.\r\n");
		return false;
	}
	if (!Smooth(AvPulse->Profile, AvPulse->FSize))
	{
		print_debug("Error: failed Brachial AvPulse Smooth().\r\n");
		return false;
	}
	
	if (!ExpPulses_init())
	{
		print_debug("Error: failed to allocate memory for ExpPulses.\r\n");
		return false;
	}
	if (!ExpandPulse(AvPulse, EXPPULSE_MAX_EXPAND_FACTOR))
	{
		print_debug("Error: failed ExpandPulse().\r\n");
		return false;
	}

	// After expand AvPulse, find systolic onset of AvPulse and cut pulse tale.
	if (!SystolicOnset(PWA_TANGENT_DER2_ALGORITHM, 0, MEAS_DEFAULT_SAMPLE_RATE*EXPPULSE_MAX_EXPAND_FACTOR, ExpPulse, Der1ExpPulse, Der2ExpPulse, Der3ExpPulse))
	{
		print_debug("Error: failed SystolicOnset().\r\n");
		return false;
	}
	
	if (!DownSample(ExpPulse, EXPPULSE_MAX_EXPAND_FACTOR, AvPulse))
	{
		print_debug("Error: failed DownSample().\r\n");
		return false;
	}
	// After DownSample(), ExpPulses are not required anymore. We got the final AvPulse here.
	ExpPulses_final();
	
	if (!PeriphParams_init())
	{
		print_debug("Error: failed to allocate memory for PeriphParams.\r\n");
		return false;
	}
	if (!Periph_CalAvPulse_init())
	{
		print_debug("Error: failed to allocate memory for Periph_CalAvPulse.\r\n");
		return false;
	}
	if (!CalibrateAvPulse_Periph())
	{
		print_debug("Error: failed CalibrateAvPulse_Periph().\r\n");
		return false;
	}
	// We don't need AvPulse once we got Periph_CalAvPulse.
	AvPulse_final();
	/* #### end Periph_CalAvPulse calculation #### */
	
	
	/* #### begin Central_CalAvPulse calculation #### */
	if (!Pulses_init())
	{
		print_debug("Error: failed to allocate memory for Pulses.\r\n");
		return false;
	}
	if (!CalcPulses(PWA_NOF_DELAY_SAMPLES, Central_onsetsLength, Central_floatSignal, Central_integerOnsets))
	{
		print_debug("Error: failed CalcPulses().\r\n");
		return false;
	}
	Central_IntegerOnsets_final();
	
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
	Central_FloatSignal_final();
	
	if (!Validate(AvPulse))
	{
		print_debug("Error: failed Validate AvPulse.\r\n");
		return false;
	}
	if (!Smooth(AvPulse->Profile, AvPulse->FSize))
	{
		print_debug("Error: failed Brachial AvPulse Smooth().\r\n");
		return false;
	}
	
	if (!ExpPulses_init())
	{
		print_debug("Error: failed to allocate memory for ExpPulses.\r\n");
		return false;
	}
	if (!ExpandPulse(AvPulse, EXPPULSE_MAX_EXPAND_FACTOR))
	{
		print_debug("Error: failed ExpandPulse().\r\n");
		return false;
	}

	// After expand AvPulse, find systolic onset of AvPulse and cut pulse tale.
	if (!SystolicOnset(PWA_TANGENT_DER2_ALGORITHM, 0, MEAS_DEFAULT_SAMPLE_RATE*EXPPULSE_MAX_EXPAND_FACTOR, ExpPulse, Der1ExpPulse, Der2ExpPulse, Der3ExpPulse))
	{
		print_debug("Error: failed SystolicOnset().\r\n");
		return false;
	}
	
	if (!DownSample(ExpPulse, EXPPULSE_MAX_EXPAND_FACTOR, AvPulse))
	{
		print_debug("Error: failed DownSample().\r\n");
		return false;
	}
	// After DownSample(), ExpPulses are not required anymore. We got the final AvPulse here.
	ExpPulses_final();
	
	if (!CentralParams_init())
	{
		print_debug("Error: failed to allocate memory for CentralParams.\r\n");
		return false;
	}
	if (!Central_CalAvPulse_init())
	{
		print_debug("Error: failed to allocate memory for Central_CalAvPulse.\r\n");
		return false;
	}
	if (!CalibrateAvPulse_Central())
	{
		print_debug("Error: failed CalibrateAvPulse_Central().\r\n");
		return false;
	}
	// We don't need AvPulse once we got Central_CalAvPulse.
	AvPulse_final();
	/* #### end Central_CalAvPulse calculation #### */
	
	
	// Set the length of calibrated average pulse
	if (Central_CalAvPulse->FSize - Central_CalAvPulse->Start < Periph_CalAvPulse->FLength)
	{
		print_debug("Error: Central_CalAvPulse size is wrong.\r\n");
		return false;
	}
	Central_CalAvPulse->End = Central_CalAvPulse->Start + Periph_CalAvPulse->FLength - 1;
	Central_CalAvPulse->FLength = Periph_CalAvPulse->FLength;
	if (Central_CalAvPulse->FLength > Central_CalAvPulse->FSize)
	{
		Central_CalAvPulse->FSize = Central_CalAvPulse->FLength;
	}
	
	// Extract features here ...
	
	print_debug("Done CalculateRadial().\r\n");
	
	return true;
}

/* ###########################################################################
 ** Convolution_Radial()
 **
 ** DESCRIPTION
 **  Convert Peripheral Signal To Central using convolution
 ** INPUT
 **  pPulses
 ** OUTPUT
 **  Central_floatSignal[0 : signalLength-NofTFC] - shifted central pressure signal
 **  Central_floatSignal[signalLength-NofTFC : signalLength] = 0 - tail of central pressure signal
 ** RETURN
 **  boolean success or not
*/
bool Convolution_Radial(const float *pPulses)
{
	if (pPulses == NULL || Central_floatSignal == NULL)
	{
		return false;
	}
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
	for(uint16_t i = 0; i < signalLength; i++)
	{
		// Do not calculate Central for tail of a signal
		if (i > signalLength - NOF_TF_COEFF)
		{
			Central_floatSignal[i] = 0.;
			continue;
		}
		// Calculate Central for actual signal
		ld = 0.0;
		for(uint16_t j = 0; j < NOF_TF_COEFF; j++ )
		{
			ld += coeff_radial[j] * pPulses[i+j];
		}
		Central_floatSignal[i] = (float)ld;
	}
	
	return true;
}

/* ###########################################################################
 ** Convolution_Brachial()
 **
 ** DESCRIPTION
 **  Convert PeriphBrachial's AvPulses to Peripheral Signal using convolution
 ** INPUT
 **  averagePulses - PeriphBrachial's AvPulses
 ** OUTPUT
 **  floatSignal
 ** RETURN
 **  boolean success or not
*/
bool Convolution_Brachial(const float *averagePulses)
{
	if (averagePulses == NULL || floatSignal == NULL)
	{
		return false;
	}
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
	for (uint16_t i = 0; i < signalLength; i++)
	{
		ld = 0.0;
		for (uint16_t j = 0; j < NOF_TF_COEFF; j++)
		{
			ld += coeff_brachial[j] * averagePulses[i+j];
		}
		floatSignal[i] = (float)ld;
	}
	
	return true;
}

/* ###########################################################################
 ** CalibrateAvPulse_Periph()
 **
 ** DESCRIPTION
 **  Calibrate AvPulse for Peripheral pressures
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
bool CalibrateAvPulse_Periph(void)
{
	// Find Min, Max, Gain and Offset for different type of measurement
	// using Sp, Dp, MeanP entered by operator
	float lMin=0, lMax=0, lAver=0;
	lMax = Math_Max(0, AvPulse->End, AvPulse);
	lMin = Math_Min(0, (int16_t)(AvPulse->End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT), AvPulse);
	lAver = Integral(0, AvPulse->End, AvPulse) / (AvPulse->FLength - 1);

	if (lAver <= lMin || lMin >= lMax)
	{
		return false;
	}

	// Find Gain and Offset
	if (Brachial_SP > Brachial_DP)
	{
		PeriphParams->Gain = (Brachial_SP - Brachial_DP) / (lMax - lMin);
		PeriphParams->Offset = Brachial_SP - PeriphParams->Gain*lMax;
	}
	else if (Brachial_MeanP > Brachial_DP)
	{
		PeriphParams->Gain = (Brachial_MeanP - Brachial_DP) / (lAver - lMin);
		PeriphParams->Offset = Brachial_MeanP - PeriphParams->Gain*lAver;
	}

	// Transform using the Gain and Offset for Periph AvPulses
	float pressureMin=0, pressureMax=0, integralAver=0;
	CalibratePulse(PeriphParams->Gain, PeriphParams->Offset, AvPulse, &pressureMin, &pressureMax, Periph_CalAvPulse);
	integralAver = Integral(0, Periph_CalAvPulse->End, Periph_CalAvPulse) / (Periph_CalAvPulse->FLength - 1);
	pressureMax = Math_Max(0, Periph_CalAvPulse->End, Periph_CalAvPulse);
	PeriphParams->IntegralAver = integralAver;
	
	return true;
}

/* ###########################################################################
 ** CalibrateAvPulse_Central()
 **
 ** DESCRIPTION
 **  Calibrate AvPulse for Central pressures and calculate Central SP/DP
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
bool CalibrateAvPulse_Central(void)
{
	// Transform using the same Periph Gain and Offset for Central AvPulses
	float pressureMin=0, pressureMax=0, integralAver=0;
	CalibratePulse(PeriphParams->Gain, PeriphParams->Offset, AvPulse, &pressureMin, &pressureMax, Central_CalAvPulse);
	integralAver = Integral(0, Central_CalAvPulse->End, Central_CalAvPulse) / (Central_CalAvPulse->FLength - 1);
	
	if (PeriphParams->IntegralAver != -DEFAULT_VALUE && PeriphParams->IntegralAver != integralAver)
	{
		for (int16_t i = 0; i < Central_CalAvPulse->FSize; i++)
		{
			Central_CalAvPulse->Profile[i] += PeriphParams->IntegralAver - integralAver;
		}
	}
	
	pressureMax = Math_Max(0, Central_CalAvPulse->End, Central_CalAvPulse);
	pressureMin = Math_Min(0, (int16_t)(Central_CalAvPulse->End * PWA_EFFECTIVE_PULSE_LENGTH_PERCENT), Central_CalAvPulse);
	CentralParams->SP = pressureMax;
	CentralParams->DP = pressureMin;
	
	return true;
}

/* ###########################################################################
 ** ExtractFeatures()
 **
 ** DESCRIPTION
 **  Find T1, T2, ED for Periph and Central, Set Central->ED = Periph->ED
 **  and Extract features
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  none.
*/
void ExtractFeatures(void)
{
	
}

/* ###########################################################################
 ** RejectIrregularTrigPts()
 **
 ** DESCRIPTION
 **  Compare Periph and Central trigger points and Reject irregulars
 ** INPUT
 **  Periph/Central onsets
 ** OUTPUT
 ** RETURN
 **  boolean success or not
*/
bool RejectIrregularTrigPts(void)
{
	// Check Trigger points correspondence
	// Initialisation
	int16_t NofValidTrigs = 0;    // Actual number of valid trigger points
	int16_t PeriphIndex = 0, CentralIndex = 0;
	// Allocate memory for valid Trigger points
	int16_t lMaxNofTr = max(onsetsLength, Central_onsetsLength);
	int16_t *lNewPeriphTrigs = malloc(lMaxNofTr * sizeof(int16_t));
	if (lNewPeriphTrigs == NULL)
	{
		return false;
	}
	int16_t *lNewCentralTrigs = malloc(lMaxNofTr * sizeof(int16_t));
	if (lNewCentralTrigs == NULL)
	{
		free(lNewPeriphTrigs);
		lNewPeriphTrigs = NULL;
		return false;
	}

	for (int16_t ltr = 0; ltr < lMaxNofTr; ltr++)
	{
		// Get current onsets
		int16_t PeriphOnset = integerOnsets[PeriphIndex];
		int16_t CentralOnset = Central_integerOnsets[CentralIndex];
		// Check last trigger point
		if (PeriphIndex >= onsetsLength || CentralIndex >= Central_onsetsLength)
		{
			break;
		}			
		// Comparison
		if (PeriphOnset > CentralOnset)
		{
			// Check additional Central before PeriphOnset
			if (CentralIndex == Central_onsetsLength - 1 || PeriphOnset < Central_integerOnsets[CentralIndex+1])
			{
				lNewPeriphTrigs[NofValidTrigs] = PeriphOnset;
				lNewCentralTrigs[NofValidTrigs] = CentralOnset;
				NofValidTrigs++;
				CentralIndex++;
				PeriphIndex++;
			}
			else
			{
				CentralIndex++;
				continue;
			}
		}
		else // PeriphOnset < CentralOnset
		{
			PeriphIndex++;
			continue;
		}
	}
	// Validation
	if (NofValidTrigs <= 1)
	{
		free(lNewPeriphTrigs);
		lNewPeriphTrigs = NULL;
		free(lNewCentralTrigs);
		lNewCentralTrigs = NULL;
		return false;
	}
	// Copy new trigger points to the places for old
	for (int16_t i=0; i < lMaxNofTr; i++)
	{
		integerOnsets[i] = (i < NofValidTrigs ? lNewPeriphTrigs[i] : (int16_t)-1);
		Central_integerOnsets[i] = (i < NofValidTrigs ? lNewCentralTrigs[i] : (int16_t)-1);
	}
	onsetsLength = NofValidTrigs;
	Central_onsetsLength = NofValidTrigs;
	// Free memory
	free(lNewPeriphTrigs);
	lNewPeriphTrigs = NULL;
	free(lNewCentralTrigs);
	lNewCentralTrigs = NULL;
	// Success
	return true;
}


//----------------------------------------------------------------------
// For porting to C only, will be removed after done porting to C.
void TestCallPWA(void)
{
	if (!CalculateBrachial())
	{
		Finalise();
		print_debug("Error: failed CalculateBrachial().\r\n");
		return;
	}
	
	if (!CalculateRadial())
	{
		Finalise();
		print_debug("Error: failed CalculateRadial().\r\n");
		return;
	}
	
	// Save all required parameters to disk here.
	
	Finalise();
	
	print_debug("Done TestCallPWA().\r\n");
}

// For porting to C only, will be removed after done porting to C.
// +512 is for simulating/validating with xcel, xcel cut off the first 2 seconds.
void TestSetRawSignal(void)
{
#ifdef _DEBUG
	for (uint16_t i=0; i<ADC_BUF_SIZE+512; i++)
	{
		AddSignal(wave_table[i]);
	}
	TestCallPWA();
#endif
}

//----------------------------------------------------------------------------