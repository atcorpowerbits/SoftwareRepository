/*
 * pwa.c
 *
 * Major functions for PWA calculation, Peripheral/Central output parameters.
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
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
#include "command-response/sender.h"
#include "command-response/cmd_state.h"

#define PWA_ED_TOP_PERCENT					(float)0.75
#define PWA_EFFECTIVE_PULSE_LENGTH_PERCENT	(float)0.75 // percent to calculate min value for calibration
#define PWA_NOF_DELAY_SAMPLES				(int8_t)8
#define PWA_CUFF_INFLATE_PRESSURE_SUBTRACT	(int8_t)10
uint16_t PWA_Error_Code = 0;

/* ###########################################################################
 ** FloatSignal_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise floatSignal, Central_floatSignal properties
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if out of memory.
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
 **  Free floatSignal, Central_floatSignal properties
 ** INPUT
 ** OUTPUT
 ** RETURN
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
 **  Allocate memory, initailise integerOnsets, Central_integerOnsets properties
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if out of memory.
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
 **  Free integerOnsets, Central_integerOnsets properties
 ** INPUT
 ** OUTPUT
 ** RETURN
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
 ** Derivatives_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise Derivatives properties
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if out of memory.
 */
bool Derivatives_init(void)
{
	Derivatives1 = malloc(sizeof(float)*PRESSURE_MAX_PPOINTS);
	Derivatives2 = malloc(sizeof(float)*PRESSURE_MAX_PPOINTS);
	
	if (Derivatives1 == NULL || Derivatives2 == NULL)
	{
		return false;
	}
	
	memset(Derivatives1, 0, sizeof(float)*PRESSURE_MAX_PPOINTS);
	memset(Derivatives2, 0, sizeof(float)*PRESSURE_MAX_PPOINTS);
	return true;
}

/* ###########################################################################
 ** Derivatives_final()
 **
 ** DESCRIPTION
 **  Free Derivatives properties
 ** INPUT
 ** OUTPUT
 ** RETURN
*/
void Derivatives_final(void)
{
	if (Derivatives1 != NULL)
	{
		free(Derivatives1);
		Derivatives1 = NULL;
	}
	if (Derivatives2 != NULL)
	{
		free(Derivatives2);
		Derivatives2 = NULL;
	}
}

/* ###########################################################################
 ** PeriphParams_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise PeriphParams properties
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if out of memory.
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
	PeriphParams->QualityT1 = DEFAULT_VALUE;
	PeriphParams->OperatorIndex = DEFAULT_VALUE;
	
	return true;
}

/* ###########################################################################
 ** PeriphParams_final()
 **
 ** DESCRIPTION
 **  Free PeriphParams properties
 ** INPUT
 ** OUTPUT
 ** RETURN
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
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if out of memory.
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
	CentralParams->PP = DEFAULT_VALUE;
	CentralParams->MeanP = DEFAULT_VALUE;
	CentralParams->AGPH = DEFAULT_VALUE;
	CentralParams->AGPH_HR75 = DEFAULT_VALUE;
	CentralParams->AP = DEFAULT_VALUE;
	CentralParams->HR = DEFAULT_VALUE;
	
	return true;
}

/* ###########################################################################
 ** CentralParams_final()
 **
 ** DESCRIPTION
 **  Free CentralParams properties
 ** INPUT
 ** OUTPUT
 ** RETURN
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
 ** QCParams_init()
 **
 ** DESCRIPTION
 **  Allocate memory, initailise QCParams properties
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if out of memory.
 */
bool QCParams_init(void)
{
	QCParams = (QC_Parameters *)malloc(sizeof(QC_Parameters));
	if (QCParams == NULL)
	{
		return false;
	}
	
	QCParams->QC_DiastolicVariation = DEFAULT_VALUE;
	QCParams->QC_PulseHeight = DEFAULT_VALUE;
	QCParams->QC_PulseHeightVariation = DEFAULT_VALUE;
	QCParams->QC_PulseLengthVariation = DEFAULT_VALUE;
	QCParams->QC_ShapeDeviation = DEFAULT_VALUE;
	
	return true;
}
/* ###########################################################################
 ** QCParams_final()
 **
 ** DESCRIPTION
 **  Free QCParams properties
 ** INPUT
 ** OUTPUT
 ** RETURN
*/
void QCParams_final(void)
{
	if (QCParams != NULL)
	{
		free(QCParams);
		QCParams = NULL;
	}
}

/* ###########################################################################
 ** Initialise()
 **
 ** DESCRIPTION
 **  Initialise all single tone parameters.
 ** INPUT
 ** OUTPUT
 ** RETURN
*/
void Initialise(void)
{
	signalLength = 0;
	onsetsLength = 0;
	Central_onsetsLength = 0;
	PWA_Error_Code = 0;
}

/* ###########################################################################
 ** DisplayMemoryUsage()
 **
 ** DESCRIPTION
 **  Display memory usage on heap when compiled with _DEBUG symbol.
 ** INPUT
 **  msg - parsed comment string.
 ** OUTPUT
 ** RETURN
*/
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
 **  Free all allocated heap memories
 ** INPUT
 ** OUTPUT
 ** RETURN
*/
void Finalise(void)
{
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
	QCParams_final();
}

/* ###########################################################################
 ** CheckSamples()
 **
 ** DESCRIPTION
 **  Check each sample is greater or equal than PWA_ACCEPTABLE_DATA_THRESHOLD,
 **  otherwise, do not call any PWA calculation. Because PWA algorithm requires
 **  certain higher value than threshold.
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if adc_buffer is null or any sample is less than PWA_ACCEPTABLE_DATA_THRESHOLD.
*/
bool CheckSamples(void)
{
	if (adc_buffer == NULL)
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): CheckSamples() - adc_buffer is null.\r\n", PWA_Error_Code);
		return false;
	}

	for (uint16_t i=0; i < ADC_BUF_SIZE; i++)
	{
		floatSignal[i] = (float)adc_buffer[i];
		if (floatSignal[i] < PWA_ACCEPTABLE_DATA_THRESHOLD)
		{
			PWA_Error_Code = PWA_MSG_CAPTURE_SIGNAL_TOO_LOW;
			print_debug("Error(%d): capture signal is too low.\r\n", PWA_Error_Code);
			return false;
		}
	}
	signalLength = ADC_BUF_SIZE;
	
	return true;
}

/* ###########################################################################
 ** ValidateBeforeCalculate()
 **
 ** DESCRIPTION
 **  Validate signalLength, Brachial Sp/Dp before Calculation routine.
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if validation failed.
*/
bool ValidateBeforeCalculate(void)
{
	if (signalLength < PRESSURE_PULSE_MAXLENGTH)
	{
		PWA_Error_Code = PWA_MSG_SIGNAL_TOO_SHORT;
		print_debug("Error(%d): The Signal length is too short to proceed with the calculation.\r\n", PWA_Error_Code);
		return false;
	}
	if (signalLength > PRESSURE_MAX_PPOINTS)
	{
		signalLength = PRESSURE_MAX_PPOINTS;
		print_debug("Warning: The Signal length is too long and has been truncated.\r\n");
	}
	
	// Validate Brachial SP and DP.
	if (Brachial_SP < Brachial_DP + MEA_SP2DP_DIFF_MIN)
	{
		PWA_Error_Code = PWA_SP_DP_TOO_CLOSE;
		print_debug("Error(%d): SYS should be higher than DIA by %d mmHg.\r\n", PWA_Error_Code, MEA_SP2DP_DIFF_MIN);
		return false;
	}
	if (Brachial_SP < NIBP_ADULT_MIN_SP || Brachial_SP > NIBP_ADULT_MAX_SP)
	{
		PWA_Error_Code = PWA_SP_OUT_OF_RANGE;
		print_debug("Error(%d): Systolic Pressure(%d) is out of range.\r\n", PWA_Error_Code, Brachial_SP);
		return false;
	}
	if (Brachial_DP < NIBP_ADULT_MIN_DP || Brachial_DP > NIBP_ADULT_MAX_DP)
	{
		PWA_Error_Code = PWA_DP_OUT_OF_RANGE;
		print_debug("Error(%d): Diastolic Pressure(%d) is out of range.\r\n", PWA_Error_Code, Brachial_DP);
		return false;
	}
	
	return true;
}

/* ###########################################################################
 ** CalculateBrachial()
 **
 ** DESCRIPTION
 **  Do all mathematics for Brachial Cuff measurement
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if any calculation failed.
*/
bool CalculateBrachial(void)
{
	print_debug("Start CalculateBrachial().\r\n");
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	
	if (!FloatSignal_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for floatSignal.\r\n", PWA_Error_Code);
		return false;
	}
	
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!CheckSamples())
	{
		print_debug("Error: failed CheckSamples().\r\n"); // CheckSamples() has detailed error code.
		return false;
	}
	
	if (!ValidateBeforeCalculate())
	{
		print_debug("Error: failed ValidateBeforeCalculate().\r\n"); // ValidateBeforeCalculate() has detailed error code.
		return false;
	}
	
	if (!IntegerOnsets_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for integerOnsets.\r\n", PWA_Error_Code);
		return false;
	}
	if (!Derivatives_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Derivatives.\r\n", PWA_Error_Code);
		return false;
	}
	// Trigger Points and Pulses
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!FindOnsets(PWA_DER2_ALGORITHM, PWA_NOF_DELAY_SAMPLES + 2, floatSignal, signalLength, &onsetsLength, integerOnsets, Derivatives1, Derivatives2))
	{
		PWA_Error_Code = PWA_MSG_TRIGGER_ERR;
		print_debug("Error(%d): failed FindOnsets() - error calculating Trigger Points.\r\n", PWA_Error_Code);
		return false;
	}
	Derivatives_final();
	
	if (!Pulses_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!CalcPulses(PWA_NOF_DELAY_SAMPLES, onsetsLength, floatSignal, integerOnsets))
	{
		PWA_Error_Code = PWA_MSG_CALCPULSES_ERR;
		print_debug("Error(%d): failed CalcPulses() - error calculating Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	IntegerOnsets_final();
	
	if (!AvPulse_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for AvPulse.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!AveragePulse(0, PWA_NOF_DELAY_SAMPLES, MEAS_DEFAULT_SAMPLE_RATE))
	{
		PWA_Error_Code = PWA_MSG_CALCPULSES_ERR;
		print_debug("Error(%d): failed AveragePulse() - error calculating Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	
	// Calculate Quality Control parameters.
	if (!QCParams_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for QCParams.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!QualityControl())
	{
		PWA_Error_Code = PWA_MSG_TOO_BAD_SIGNAL;
		print_debug("Error(%d): failed QualityControl().\r\n", PWA_MSG_TOO_BAD_SIGNAL);
		return false;
	}
	
	Pulses_final();
	FloatSignal_final();
	
	if (!Validate(AvPulse))
	{
		print_debug("Error: failed Validate(AvPulse).\r\n"); // Validate() has detailed error code.
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!Smooth(AvPulse->Profile, AvPulse->FSize))
	{
		PWA_Error_Code = PWA_MSG_SMOOTH_ERR;
		print_debug("Error(%d): failed Brachial AvPulse Smooth().\r\n", PWA_Error_Code);
		return false;
	}
	
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	// Fill AvPulse into tmpSignal fully for convolution.
	float *tmpSignal = malloc(sizeof(float)*PRESSURE_MAX_PPOINTS);
	if (tmpSignal == NULL)
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for tmpSignal.\r\n", PWA_Error_Code);
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
	
	// Here, tmpSignal has repeated AvPulse and ready for Convolution. So, we don't need AvPulse in Brachial.
	AvPulse_final();
	
	// Convolution_Brachial() will change Periph floatSignal, let's prepare floatSignal for Radial calculation before Brachial convolution.
	// floatSignal would be Periph raw signal after Convolution.
	if (!FloatSignal_init())
	{
		free(tmpSignal);
		tmpSignal = NULL;
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for floatSignal.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		free(tmpSignal);
		tmpSignal = NULL;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	Convolution_Brachial(tmpSignal);
	
	free(tmpSignal);
	tmpSignal = NULL;
	
	print_debug("End CalculateBrachial().\r\n");
	
	return true;
}

/* ###########################################################################
 ** CalculateRadial()
 **
 ** DESCRIPTION
 **  Find onsets for Periph and Central, apply radial convolution, and compare Periph and Central trigger points.
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if any calculation failed.
*/
bool CalculateRadial(void)
{
	print_debug("Start CalculateRadial().\r\n");
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	
	onsetsLength = 0;
	if (!IntegerOnsets_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for integerOnsets.\r\n", PWA_Error_Code);
		return false;
	}
	if (!Derivatives_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Derivatives.\r\n", PWA_Error_Code);
		return false;
	}
	// Trigger Points and Pulses
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!FindOnsets(PWA_DER2_ALGORITHM, PWA_NOF_DELAY_SAMPLES + 2, floatSignal, signalLength, &onsetsLength, integerOnsets, Derivatives1, Derivatives2))
	{
		PWA_Error_Code = PWA_MSG_TRIGGER_ERR;
		print_debug("Error(%d): failed FindOnsets() - error calculating Periph Trigger Points.\r\n", PWA_Error_Code);
		return false;
	}
	Derivatives_final();
	
	if (!Central_FloatSignal_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Central_floatSignal.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	Convolution_Radial(floatSignal);
	
	Central_onsetsLength = 0;
	if (!Central_IntegerOnsets_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Central integerOnsets.\r\n", PWA_Error_Code);
		return false;
	}
	if (!Derivatives_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Derivatives.\r\n", PWA_Error_Code);
		return false;
	}
	// Trigger Points and Pulses
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!FindOnsets(PWA_DER2_ALGORITHM, PWA_NOF_DELAY_SAMPLES + 2, Central_floatSignal, signalLength, &Central_onsetsLength, Central_integerOnsets, Derivatives1, Derivatives2))
	{
		PWA_Error_Code = PWA_MSG_TRIGGER_ERR;
		print_debug("Error(%d): failed FindOnsets() - error calculating Central Trigger Points.\r\n", PWA_Error_Code);
		return false;
	}
	Derivatives_final();
	
	// Compare Periph and Central trigger points used by Periph/Central onsets and Reject irregulars
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!RejectIrregularTrigPts())
	{
		PWA_Error_Code = PWA_MSG_IRREGULAR_TRIGPTS;
		print_debug("Error(%d): failed RejectIrregularTrigPts().\r\n", PWA_Error_Code);
		return false;
	}
	
	// Calculating CalAvPulse for Periph and Central is the next step, part of Radial calculation.
	// But they are separated in 2 methods: CalculatePeriph_CalAvPulse(), CalculateCentral_CalAvPulse()
	// because the steps of calculating each algorithms are too big.
		
	print_debug("End CalculateRadial().\r\n");
	
	return true;
}

/* ###########################################################################
 ** CalculatePeriph_CalAvPulse()
 **
 ** DESCRIPTION
 **  Calculate Periph_CalAvPulse and Peripheral parameters
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if any calculation failed.
*/
bool CalculatePeriph_CalAvPulse(void)
{
	print_debug("Start CalculatePeriph_CalAvPulse().\r\n");
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	
	if (!Pulses_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!CalcPulses(PWA_NOF_DELAY_SAMPLES, onsetsLength, floatSignal, integerOnsets))
	{
		PWA_Error_Code = PWA_MSG_CALCPULSES_ERR;
		print_debug("Error(%d): failed CalcPulses() - error calculating Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	IntegerOnsets_final();
	
	if (!AvPulse_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for AvPulse.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!AveragePulse(0, PWA_NOF_DELAY_SAMPLES, MEAS_DEFAULT_SAMPLE_RATE))
	{
		PWA_Error_Code = PWA_MSG_CALCPULSES_ERR;
		print_debug("Error(%d): failed AveragePulse() - error calculating Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	Pulses_final();
	
	if (!Validate(AvPulse))
	{
		print_debug("Error: failed Validate(AvPulse).\r\n"); // Validate() has detailed error code.
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!Smooth(AvPulse->Profile, AvPulse->FSize))
	{
		PWA_Error_Code = PWA_MSG_SMOOTH_ERR;
		print_debug("Error(%d): failed Radial AvPulse Smooth().\r\n", PWA_Error_Code);
		return false;
	}
	
	if (!ExpPulses_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for ExpPulses.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!ExpandPulse(AvPulse, EXPPULSE_MAX_EXPAND_FACTOR))
	{
		PWA_Error_Code = PWA_MSG_EXPANDPULSE_ERR;
		print_debug("Error(%d): failed ExpandPulse().\r\n", PWA_Error_Code);
		return false;
	}

	// After expand AvPulse, find systolic onset of AvPulse and cut pulse tale.
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!SystolicOnset(PWA_TANGENT_DER2_ALGORITHM, 0, MEAS_DEFAULT_SAMPLE_RATE*EXPPULSE_MAX_EXPAND_FACTOR, ExpPulse, Der1ExpPulse, Der2ExpPulse, Der3ExpPulse))
	{
		PWA_Error_Code = PWA_MSG_CALCSYSTONSET_ERR;
		print_debug("Error(%d): failed SystolicOnset().\r\n", PWA_Error_Code);
		return false;
	}
	
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!DownSample(ExpPulse, EXPPULSE_MAX_EXPAND_FACTOR, AvPulse))
	{
		PWA_Error_Code = PWA_MSG_DOWNSAMPLE_ERR;
		print_debug("Error(%d): failed DownSample().\r\n", PWA_Error_Code);
		return false;
	}
	// After DownSample(), ExpPulses are not required anymore. We got the final AvPulse here.
	ExpPulses_final();
	
	if (!PeriphParams_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for PeriphParams.\r\n", PWA_Error_Code);
		return false;
	}
	if (!Periph_CalAvPulse_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Periph_CalAvPulse.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!CalibrateAvPulse_Periph())
	{
		PWA_Error_Code = PWA_MSG_CALIBRATE_AVPULSE_PERIPH_ERR;
		print_debug("Error(%d): failed CalibrateAvPulse_Periph().\r\n", PWA_Error_Code);
		return false;
	}
	// We don't need AvPulse, once we got Periph_CalAvPulse.
	AvPulse_final();

	print_debug("End CalculatePeriph_CalAvPulse().\r\n");
	return true;
}

/* ###########################################################################
 ** CalculateCentral_CalAvPulse()
 **
 ** DESCRIPTION
 **  Calculate Central_CalAvPulse and Central parameters
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if any calculation failed.
*/
bool CalculateCentral_CalAvPulse(void)
{
	print_debug("Start CalculateCentral_CalAvPulse().\r\n");
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	
	if (!Pulses_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!CalcPulses(PWA_NOF_DELAY_SAMPLES, Central_onsetsLength, Central_floatSignal, Central_integerOnsets))
	{
		PWA_Error_Code = PWA_MSG_CALCPULSES_ERR;
		print_debug("Error(%d): failed CalcPulses() - error calculating Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	Central_IntegerOnsets_final();
	
	if (!AvPulse_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for AvPulse.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!AveragePulse(0, PWA_NOF_DELAY_SAMPLES, MEAS_DEFAULT_SAMPLE_RATE))
	{
		PWA_Error_Code = PWA_MSG_CALCPULSES_ERR;
		print_debug("Error(%d): failed AveragePulse() - error calculating Pulses.\r\n", PWA_Error_Code);
		return false;
	}
	Pulses_final();
	Central_FloatSignal_final();
	
	if (!Validate(AvPulse))
	{
		print_debug("Error: failed Validate(AvPulse).\r\n"); // Validate() has detailed error code.
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!Smooth(AvPulse->Profile, AvPulse->FSize))
	{
		PWA_Error_Code = PWA_MSG_SMOOTH_ERR;
		print_debug("Error(%d): failed Radial AvPulse Smooth().\r\n", PWA_Error_Code);
		return false;
	}
	
	if (!ExpPulses_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for ExpPulses.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!ExpandPulse(AvPulse, EXPPULSE_MAX_EXPAND_FACTOR))
	{
		PWA_Error_Code = PWA_MSG_EXPANDPULSE_ERR;
		print_debug("Error(%d): failed ExpandPulse().\r\n", PWA_Error_Code);
		return false;
	}

	// After expand AvPulse, find systolic onset of AvPulse and cut pulse tale.
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!SystolicOnset(PWA_TANGENT_DER2_ALGORITHM, 0, MEAS_DEFAULT_SAMPLE_RATE*EXPPULSE_MAX_EXPAND_FACTOR, ExpPulse, Der1ExpPulse, Der2ExpPulse, Der3ExpPulse))
	{
		PWA_Error_Code = PWA_MSG_CALCSYSTONSET_ERR;
		print_debug("Error(%d): failed SystolicOnset().\r\n", PWA_Error_Code);
		return false;
	}
	
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!DownSample(ExpPulse, EXPPULSE_MAX_EXPAND_FACTOR, AvPulse))
	{
		PWA_Error_Code = PWA_MSG_DOWNSAMPLE_ERR;
		print_debug("Error(%d): failed DownSample().\r\n", PWA_Error_Code);
		return false;
	}
	// After DownSample(), ExpPulses are not required anymore. We got the final AvPulse here.
	ExpPulses_final();
	
	if (!CentralParams_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for CentralParams.\r\n", PWA_Error_Code);
		return false;
	}
	if (!Central_CalAvPulse_init())
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Central_CalAvPulse.\r\n", PWA_Error_Code);
		return false;
	}
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	if (!CalibrateAvPulse_Central())
	{
		PWA_Error_Code = PWA_MSG_CALIBRATE_AVPULSE_CENTRAL_ERR;
		print_debug("Error(%d): failed CalibrateAvPulse_Central().\r\n", PWA_Error_Code);
		return false;
	}
	// We don't need AvPulse, once we got Central_CalAvPulse.
	AvPulse_final();
	
	// Set the length of Central calibrated average pulse.
	if (Central_CalAvPulse->FSize - Central_CalAvPulse->Start < Periph_CalAvPulse->FLength)
	{
		PWA_Error_Code = PWA_MSG_CALCPULSES_ERR;
		print_debug("Error(%d): Central_CalAvPulse size is wrong.\r\n", PWA_Error_Code);
		return false;
	}
	Central_CalAvPulse->End = Central_CalAvPulse->Start + Periph_CalAvPulse->FLength - 1;
	Central_CalAvPulse->FLength = Periph_CalAvPulse->FLength;
	if (Central_CalAvPulse->FLength > Central_CalAvPulse->FSize)
	{
		Central_CalAvPulse->FSize = Central_CalAvPulse->FLength;
	}

	print_debug("End CalculateCentral_CalAvPulse().\r\n");
	return true;
}

/* ###########################################################################
 ** Convolution_Radial()
 **
 ** DESCRIPTION
 **  Convert Peripheral Signal To Central using convolution
 ** INPUT
 **  pPulses - floatSignal
 ** OUTPUT
 **  Central_floatSignal[0 : signalLength - NOF_TF_COEFF] - shifted central pressure signal
 **  Central_floatSignal[signalLength - NOF_TF_COEFF : signalLength] = 0 - tail of central pressure signal
 ** RETURN
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
	for (uint16_t i = 0; i < signalLength; i++)
	{
		ld = 0.0;
		for (uint16_t j = 0; j < NOF_TF_COEFF; j++)
		{
			ld += coeff_brachial[j] * averagePulses[i+j];
		}
		floatSignal[i] = (float)ld;
	}
}

/* ###########################################################################
 ** CalibrateAvPulse_Periph()
 **
 ** DESCRIPTION
 **  Calibrate AvPulse for Peripheral pressures
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if lAver is out of range.
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
 **  boolean - return false if Central Sp/Dp is DEFAULT_VALUE.
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
	if (CentralParams->SP == -DEFAULT_VALUE || CentralParams->DP == DEFAULT_VALUE)
	{
		return false;
	}
	
	return true;
}

/* ###########################################################################
 ** ExtractFeatures()
 **
 ** DESCRIPTION
 **  Find T1, T2, ED for Periph and Central, extract Central parameters used by PeriphParams->ExpPulse_ED.
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - if out of memory in any reason, cannot continue extracting features and return false.
*/
bool ExtractFeatures(void)
{
	print_debug("Start ExtractFeatures().\r\n");
	if (flag_abort)
	{
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		return false;
	}
	
	bool result = true;
	int16_t lCentralMainPeak = 0, lPeriphMainPeak = 0;
	Pulse *Periph_ExpPulse = NULL, *Central_ExpPulse = NULL;
	float *tmpCentralDer1ExpPulseProfile = NULL;
	
	Periph_ExpPulse = (Pulse *)malloc(sizeof(Pulse));
	if (Periph_ExpPulse == NULL)
	{
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Periph_ExpPulse.\r\n", PWA_Error_Code);
		return false;
	}
	Periph_ExpPulse->Profile = malloc(sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	if (Periph_ExpPulse->Profile == NULL)
	{
		result = false;
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Periph_ExpPulse->Profile.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	Periph_ExpPulse->Index = -1;
	Periph_ExpPulse->Start = 0;
	Periph_ExpPulse->End = 0;
	Periph_ExpPulse->FLength = 0;
	Periph_ExpPulse->FSize = 0;
	memset(Periph_ExpPulse->Profile, 0, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	
	Central_ExpPulse = (Pulse *)malloc(sizeof(Pulse));
	if (Central_ExpPulse == NULL)
	{
		result = false;
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Central_ExpPulse.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	Central_ExpPulse->Profile = malloc(sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	if (Central_ExpPulse->Profile == NULL)
	{
		result = false;
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for Central_ExpPulse->Profile.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	Central_ExpPulse->Index = -1;
	Central_ExpPulse->Start = 0;
	Central_ExpPulse->End = 0;
	Central_ExpPulse->FLength = 0;
	Central_ExpPulse->FSize = 0;
	memset(Central_ExpPulse->Profile, 0, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	
	
	// Find  T1, T2, ED for Periph
	if (!ExpPulses_init())
	{
		result = false;
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for ExpPulses.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	// For Periph FindT1T2ED() requires Central Der1ExpPulse Profile and lCentralMainPeak.
	// Let's expand Central_CalAvPulse here to get whatever we need for Periph calculation.
	if (flag_abort)
	{
		result = false;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		goto FreeLocalArrays;
	}
	if (!ExpandPulse(Central_CalAvPulse, EXPPULSE_MAX_EXPAND_FACTOR))
	{
		result = false;
		PWA_Error_Code = PWA_MSG_EXPANDPULSE_ERR;
		print_debug("Error(%d): failed ExpandPulse() with Central_CalAvPulse.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	if (flag_abort)
	{
		result = false;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		goto FreeLocalArrays;
	}
	lCentralMainPeak = IndexOfExtremum(ExpPulse, MAX, GLOBAL, 1, ExpPulse->FLength/2, 0, LESS, DEFAULT_VALUE, NULL,
		NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0);
	if (lCentralMainPeak < 0)
	{
		print_debug("Info: lCentralMainPeak for ExpPulse not found.\r\n");
	}
	
	tmpCentralDer1ExpPulseProfile = malloc(sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	if (tmpCentralDer1ExpPulseProfile == NULL)
	{
		result = false;
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for tmpCentralDer1ExpPulseProfile.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	memset(tmpCentralDer1ExpPulseProfile, 0, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	memcpy(tmpCentralDer1ExpPulseProfile, Der1ExpPulse->Profile, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	Central_ExpPulse->Index = ExpPulse->Index;
	Central_ExpPulse->Start = ExpPulse->Start;
	Central_ExpPulse->End = ExpPulse->End;
	Central_ExpPulse->FLength = ExpPulse->FLength;
	Central_ExpPulse->FSize = ExpPulse->FSize;
	memcpy(Central_ExpPulse->Profile, ExpPulse->Profile, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	ExpPulses_final();
	
	// We need to calculate Periph FindT1T2ED() first, because Central FindT1T2ED() requires PeriphParams->ExpPulse_ED and lPeriphMainPeak.
	if (!ExpPulses_init())
	{
		result = false;
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for ExpPulses.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	if (flag_abort)
	{
		result = false;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		goto FreeLocalArrays;
	}
	if (!ExpandPulse(Periph_CalAvPulse, EXPPULSE_MAX_EXPAND_FACTOR))
	{
		result = false;
		PWA_Error_Code = PWA_MSG_EXPANDPULSE_ERR;
		print_debug("Error(%d): failed ExpandPulse() with Periph_CalAvPulse.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	if (flag_abort)
	{
		result = false;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		goto FreeLocalArrays;
	}
	lPeriphMainPeak = IndexOfExtremum(ExpPulse, MAX, GLOBAL, 1, ExpPulse->FLength/2, 0, LESS, DEFAULT_VALUE, NULL,
		NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0, NULL, LESS, DEFAULT_VALUE, 0);
	if (lPeriphMainPeak < 0)
	{
		print_debug("Info: lPeriphMainPeak for ExpPulse not found.\r\n");
	}
	Periph_ExpPulse->Index = ExpPulse->Index;
	Periph_ExpPulse->Start = ExpPulse->Start;
	Periph_ExpPulse->End = ExpPulse->End;
	Periph_ExpPulse->FLength = ExpPulse->FLength;
	Periph_ExpPulse->FSize = ExpPulse->FSize;
	memcpy(Periph_ExpPulse->Profile, ExpPulse->Profile, sizeof(float)*PRESSURE_EXPPULSE_MAXLENGTH);
	
	// We are finding Periph T1,T2,ED here, pCentralParams should be NULL.
	if (flag_abort)
	{
		result = false;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		goto FreeLocalArrays;
	}
	FindT1T2ED(ExpPulse, Der1ExpPulse, Der2ExpPulse, Der3ExpPulse,
		EXPPULSE_MAX_EXPAND_FACTOR, MEAS_DEFAULT_SAMPLE_RATE, -1, lCentralMainPeak, -1, -1, tmpCentralDer1ExpPulseProfile, PeriphParams, NULL);
	ExpPulses_final();
	
	// Calculate Operator Index here, because it needs PeriphParams->QualityT1.
	PeriphParams->OperatorIndex = CalculateOperatorIndex();
	QCParams_final();
	
	
	// Find  T1, T2, ED for Central
	// Set the limitation for Central->ExpPulse_T2 on the base of Periph->ExpPulse_T2
	int16_t lLimitT1T2 = (PeriphParams->ExpPulse_T2 != DEFAULT_VALUE ? PeriphParams->ExpPulse_T2 : -1);
	if (lLimitT1T2 > 0 && PeriphParams->ExpPulse_T2m > 0 && PeriphParams->ExpPulse_ShoulderAfterPeak > PeriphParams->ExpPulse_T2m)
	{
		lLimitT1T2 = PeriphParams->ExpPulse_ShoulderAfterPeak;
	}
	if (!ExpPulses_init())
	{
		result = false;
		PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
		print_debug("Error(%d): failed to allocate memory for ExpPulses.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	if (flag_abort)
	{
		result = false;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		goto FreeLocalArrays;
	}
	if (!ExpandPulse(Central_CalAvPulse, EXPPULSE_MAX_EXPAND_FACTOR))
	{
		result = false;
		PWA_Error_Code = PWA_MSG_EXPANDPULSE_ERR;
		print_debug("Error(%d): failed ExpandPulse() with Central_CalAvPulse.\r\n", PWA_Error_Code);
		goto FreeLocalArrays;
	}
	
	// We are finding Central T1,T2,ED here, pPeriphParams should be NULL.
	if (flag_abort)
	{
		result = false;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		goto FreeLocalArrays;
	}
	FindT1T2ED(ExpPulse, Der1ExpPulse, Der2ExpPulse, Der3ExpPulse,
		EXPPULSE_MAX_EXPAND_FACTOR, MEAS_DEFAULT_SAMPLE_RATE, PeriphParams->ExpPulse_ED, -1, lPeriphMainPeak, lLimitT1T2, NULL, NULL, CentralParams);
	ExpPulses_final();
	
	
	// Extract other features dependant on T1, T2, ED.
	if (flag_abort)
	{
		result = false;
		print_debug("Warning: PWA calculation has been requested the runtime to abort it in a safety way.\r\n");
		goto FreeLocalArrays;
	}
	CentralExtractFeatures(PeriphParams->ExpPulse_ED, Central_ExpPulse);
	
	Periph_CalAvPulse_final();

	
FreeLocalArrays:
	if (tmpCentralDer1ExpPulseProfile != NULL)
	{
		free(tmpCentralDer1ExpPulseProfile);
		tmpCentralDer1ExpPulseProfile = NULL;
	}
	if (Periph_ExpPulse != NULL)
	{
		if (Periph_ExpPulse->Profile != NULL)
		{
			free(Periph_ExpPulse->Profile);
			Periph_ExpPulse->Profile = NULL;
		}
		free(Periph_ExpPulse);
		Periph_ExpPulse = NULL;
	}
	if (Central_ExpPulse != NULL)
	{
		if (Central_ExpPulse->Profile != NULL)
		{
			free(Central_ExpPulse->Profile);
			Central_ExpPulse->Profile = NULL;
		}
		free(Central_ExpPulse);
		Central_ExpPulse = NULL;
	}
	ExpPulses_final();
	
	print_debug("End ExtractFeatures().\r\n");
	return result;
}

/* ###########################################################################
 ** RejectIrregularTrigPts()
 **
 ** DESCRIPTION
 **  Compare Periph and Central trigger points and Reject irregulars
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if NofValidTrigs <= 1 or out of memory.
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

/* ###########################################################################
 ** ValidateBeforeStore()
 **
 ** DESCRIPTION
 **  Validate Central heart rate before Store in disk.
 **  As discussed with Ahmad, lots of checking parameters in XCEL are redundant,
 **  but we can add here anything major concerned validation further.
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if validation failed.
*/
bool ValidateBeforeStore(void)
{
	if ((CentralParams->HR != DEFAULT_VALUE) && (CentralParams->HR < MIN_HR || CentralParams->HR > MAX_HR))
	{
		PWA_Error_Code = PWA_MSG_HR_OUT;
		print_debug("Error(%d): The value for Heart Rate is out of range. HR = %f\r\n", PWA_Error_Code, CentralParams->HR);
		CentralParams->HR = DEFAULT_VALUE;
		return false;
	}
	
	return true;
}

/* ###########################################################################
 ** CalculatePWA()
 **
 ** DESCRIPTION
 **  Do all mathematics for this measurement - calculations of Brachial and Radial.
 ** INPUT
 ** OUTPUT
 ** RETURN
 **  boolean - return false if any calculation failed or validation of output parameters is failed.
*/
bool CalculatePWA(void)
{
	Initialise();
	
	// The below calculating methods have each own detailed error codes handling.
	if (!CalculateBrachial())
	{
		print_debug("Error: failed CalculateBrachial().\r\n");
		return false;
	}

	if (!CalculateRadial())
	{
		print_debug("Error: failed CalculateRadial().\r\n");
		return false;
	}

	if (!CalculatePeriph_CalAvPulse())
	{
		print_debug("Error: failed CalculatePeriph_CalAvPulse().\r\n");
		return false;
	}

	if (!CalculateCentral_CalAvPulse())
	{
		print_debug("Error: failed CalculateCentral_CalAvPulse().\r\n");
		return false;
	}

	if (!ExtractFeatures())
	{
		print_debug("Error: failed ExtractFeatures().\r\n");
		return false;
	}

	if (!ValidateBeforeStore())
	{
		print_debug("Error: failed ValidateBeforeStore().\r\n");
		return false;
	}
	
	return true;
}


//----------------------------------------------------------------------
// For porting to C only, will be removed after done porting to C.
void TestCallPWA(void)
{
	Brachial_SP = 120;
	Brachial_DP = 80;
	
	if (!CalculatePWA())
	{
		Common_Error_Code = PWA_CALCULATION_FAILED;
		print_debug("Common_Error_Code=%d, PWA_Error_Code=%d.\r\n", Common_Error_Code, PWA_Error_Code);
		Finalise();
		return;
	}
	
	// Save all required parameters to disk here ...
	
	if (PeriphParams->OperatorIndex >= QUALITY_THRESHOLD)
	{
		print_debug("Report quality: tick.\r\n");
	}
	else
	{
		print_debug("Report quality: cross.\r\n");
	}
	
	Finalise();
	
	print_debug("Common_Error_Code=%d, PWA_Error_Code=%d.\r\n", Common_Error_Code, PWA_Error_Code);
	print_debug("Done TestCallPWA().\r\n");
}

// For porting to C only, will be removed after done porting to C.
void TestSetRawSignal(void)
{
#ifdef _DEBUG
	for (uint16_t i=0; i<ADC_BUF_SIZE; i++)
	{
		AddSignal(wave_table[i]);
	}
	TestCallPWA();
#endif
}

void pwa_calculation_task (void)
{
	if (flag_start_pwa)
	{
		// Don't let another pwa to be started
		flag_start_pwa = false;
		update_cbp_system_status(CBP_SYSTEM_STATUS_CALCULATING);
		
		Finalise();
		if (!ADCBuffer_init())
		{
			PWA_Error_Code = PWA_MSG_OUT_OF_MEMORY;
			print_debug("Error(%d): failed to allocate memory adc_buffer.\r\n", PWA_Error_Code);
		}
		else
		{
			TestSetRawSignal();
		}

		// Flag when pwa calculation is finished regardless of the result, even if the calculation was aborted.
		flag_finished_pwa = true;
	}
}

//----------------------------------------------------------------------------