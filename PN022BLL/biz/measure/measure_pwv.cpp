/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer PWV Measurement Class
*/

#include "StdAfx.h"
#include <measure_pwv.h>
#include <patient.h>
#include <session.h>
#include <biz.h>

using namespace System::Globalization;
using namespace CRX_CONFIG_NAMESPACE;
using namespace CRX_LOG_NAMESPACE;
using namespace DAL_NAMESPACE;
using namespace BIZ_NAMESPACE;

/**
ValidateFemoral2CuffDistance

DESCRIPTION

	Validate Femoral to Cuff Distance which should be between min and max.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - Femoral to Cuff Distanceis valid.

	false - Femoral to Cuff Distance not valid.

*/		
bool BizFemoral2CuffDistance::Validate()
{
	bool isValid = false;

	if (distance >= PWV_FEMORAL_TO_CUFF_DISTANCE_MIN && distance <= PWV_FEMORAL_TO_CUFF_DISTANCE_MAX)
	{
		isValid = true;
	} else
	{
		//TBD: Inform user "Femoral to Cuff distance not within the valid range between ... cm and ... cm"
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate PWV Carotid Distance.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - PWV Carotid Distance is valid.

	false - PWV Carotid Distance is not valid.

*/
bool BizCarotidDistance::Validate()
{
	bool isValid = false;

	if (distance >= PWV_DISTANCE_MIN && distance <= PWV_DISTANCE_MAX)
	{
		isValid = true;
	} else
	{
		//TBD: Inform user "Carotid distance is not within the valid range between ... cm and ... cm"
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate PWV Cuff Distance.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - PWV Cuff Distance is valid.

	false - PWV Cuff Distance is not valid.

*/
bool BizCuffDistance::Validate()
{
	bool isValid = false;

	if (distance >= PWV_DISTANCE_MIN && distance <= PWV_DISTANCE_MAX)
	{
		isValid = true;
	} else
	{
		//TBD: Inform user "Cuff distance is not within the valid range between ... cm and ... cm"
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate PWV Direct Distance.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - PWV Direct Distance is valid.

	false - PWV Direct Distance is not valid.

*/
bool BizPWVDirectDistance::Validate()
{
	bool isValid = false;

	if (distance >= PWV_DISTANCE_MIN && distance <= PWV_DISTANCE_MAX)
	{
		isValid = true;
	} else
	{
		//TBD: Inform user "PWV direct distance is not within the valid range between ... cm and ... cm"
	}
	return isValid;
}
/**
BizPWV

DESCRIPTION

	Constructor where distance and signal objects are aggregated.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/	
BizPWV::BizPWV(void)
{
	// Instantiate some PWV distance objects
	myCarotidDistance = gcnew BizCarotidDistance;
	myCuffDistance = gcnew BizCuffDistance;
	myPWVDirectDistance = gcnew BizPWVDirectDistance;
	myFemoral2CuffDistance = gcnew BizFemoral2CuffDistance;

	// Initialise other properties
	carotidSignal = gcnew BizSignal;
	femoralSignal = gcnew BizSignal;

	pulseWaveVelocity = gcnew array<BizDelta^>(MAX_ONSETS);
	for (int i = 0; i < MAX_ONSETS; i++)
	{
		pulseWaveVelocity[i] = gcnew BizDelta;
	}
	
	// Allocate Signals
	carotidSignal->Allocate(MAX_SIGNAL_LENGTH, MAX_ONSETS);
	femoralSignal->Allocate(MAX_SIGNAL_LENGTH, MAX_ONSETS);

	// Initialise
	Initialise();
}
/**
ValidatePWVDistance

DESCRIPTION

	Validate PWV distance with respect to calculation method used.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - PWV distance is valid for the selected method.

	false - PWV distance is not valid for the selected method.
	
*/	
bool BizPWV::ValidatePWVDistance()
{
	bool isValid = false;
	CrxStructPwvSetting^ pwvSetting = CrxConfigManager::Instance->PwvSettings;

	if (pwvSetting->PWVDistanceMethod == 0) // TBD: replace magic number for subtracting method
	{
		isValid = myCarotidDistance->Validate() && myCuffDistance->Validate();
	}
	else if (pwvSetting->PWVDistanceMethod == 1) // TBD: replace magic number for direct method
	{
		isValid = myPWVDirectDistance->Validate();
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate the PWV measurement before calculation including:
	    Basic measurement parameters in BizMeasure
		PWV Distance
		Femoral to Cuff Distance
		Calculated Distance

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - PWV measurement is valid.

	false - PWV measurement is not valid.

*/
bool BizPWV::Validate()
{
	if (!BizMeasure::Validate())
	{
		return false;
	} 
	
	if (!myFemoral2CuffDistance->Validate())
	{
		return false;
	} 
	
	if (!ValidatePWVDistance())
	{
		return false;
	} 
	
	if (!CalculateAndValidateDistance())
	{
		return false;
	} 

	return true;
}
/**
StartCapture

DESCRIPTION

	Start capturing PWV measurement data.
	Data buffers are reset before capturing starts.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - PWV capture started successfully.

	false - PWV capture failed to start.

*/		
bool BizPWV::StartCapture()
{
	CrxLogger::Instance->Write("Start PWV capture");
	tonometerDataObserver->Reset();
	cuffPulseObserver->Reset();
	carotidQualityObserver->Reset();
//	return DalFacade::Instance()->StartCapture(DalConstants::DATA_TONOMETER_AND_CUFF_PULSE_COMBO);
	LogSetupData(); // TBD: remove after TM Sprint-3 integration?

	try {
		DalModule::Instance->StartCapture();
		return true;
	}
	catch (Exception^) {
//		throw gcnew BizException(???); //Failed to start PWV capture
		return true;
	}
}
/**
StopCapture

DESCRIPTION

	Stop capturing PWV measurement data.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - PWV capture stopped successfully.

	false - PWV capture failed to stop.

*/		
bool BizPWV::StopCapture()
{
	CrxLogger::Instance->Write("Stop PWV capture");
//	return DalFacade::Instance()->StopCapture();
	try {
		DalModule::Instance->StopCapture();
		return true;
	}
	catch (Exception^) {
//		throw gcnew BizException(???); //Failed to stop PWV capture
		return false;
	}
}
/**
DispatchCaptureData

DESCRIPTION

	Dispatch PWV measurement data which may have been observed (captured).
	PWV measurement data inclucde:
	-Tonometer data
	-Cuff pulse data
	-Cuff pressure data (future)
	-Count down timer
	-Cuff state

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizPWV::DispatchCaptureData()
{
	tonometerDataObserver->Dispatch();
	cuffPulseObserver->Dispatch();
	countdownTimerObserver->Dispatch();
	cuffObserver->Dispatch();
}
/**
 ** Initialise()
 **
 ** DESCRIPTION:
 **
 **  Initialse the members of the PWV class.

 ** INPUT:
 **
 **	 SampleRate.

 ** OUTPUT:
 **
 **  none.

 ** RETURN:
 **
 **  none.
*/
void BizPWV::Initialise()
{
	unsigned int bufferSize = (captureTime + BusinessLogic::BizConstants::CAPTURE_EXTRA_FOR_HANDSHAKE) * sampleRate;

	BizMeasure::Initialise();
	
	tonometerBuffer = gcnew BizCircularBuffer(bufferSize);
	cuffBuffer = gcnew BizCircularBuffer(bufferSize);

	// Tonometer and cuff pulse data from DAL are captured here for PWV measurement.
	tonometerDataObserver = gcnew BizTonometerDataCapture( tonometerBuffer );
	tonometerDataObserver->Reset();

	cuffPulseObserver = gcnew BizCuffPulseCapture( cuffBuffer );
	cuffPulseObserver->Reset();

	// Carotid quality is calculated from the captured tonometer data
	carotidQualityObserver = gcnew BizCarotidQuality( tonometerBuffer, sampleRate );

	// Femoral quality is calculated from the captured cuff pulse data
	femoralQualityObserver = gcnew BizFemoralQuality( cuffBuffer, sampleRate );

	// Countdown data from DAL are captured here for PWV measurement.
	// Only one last countdown data is needed to be captured.
	countdownTimerObserver = gcnew BizCountdownTimerCapture(gcnew BizCircularBuffer(1));
	countdownTimerObserver->Reset();

	cuffObserver = gcnew BizCuff;
		
	myCarotidDistance->distance = BizConstants::DEFAULT_VALUE;
	myCuffDistance->distance = BizConstants::DEFAULT_VALUE;
	myFemoral2CuffDistance->distance = DEFAULT_FEMORAL_TO_CUFF_DISTANCE;
	myPWVDirectDistance->distance = BizConstants::DEFAULT_VALUE;
	calculatedDistance = BizConstants::DEFAULT_VALUE;
	correctionTime = DEFAULT_CORRECTION_TIME;					
	
	// Initialise cannot return false because sampleRate is hard-coded
	carotidSignal->Initialise(sampleRate);
	femoralSignal->Initialise(sampleRate);

	SetDefaults();
}
/**
 ** SetDefaults()
 **
 ** DESCRIPTION:
 **
 **  Set default values for calculated variables.

 ** INPUT:
 **
 **  none.

 ** OUTPUT:
 **
 **  none.

 ** RETURN:
 **
 **  none.
*/
void BizPWV::SetDefaults()
{
	meanDeltaTime = BizConstants::DEFAULT_VALUE;					
	meanCorrectedTime = BizConstants::DEFAULT_VALUE;
	meanPulseWaveVelocity = BizConstants::DEFAULT_VALUE;			
	standardDeviation = BizConstants::DEFAULT_VALUE;
	
	numberOfDeltas = 0;
	numberOfValidDeltas = 0;
    
	isCarotidSignalValid = false;
	isFemoralSignalValid = false;
	isStandardDeviationValid = false;
	meanHeartRate = BizConstants::DEFAULT_VALUE;

    carotidSignal->SetDefaults();
    femoralSignal->SetDefaults();
    
    for (int i = 0; i < MAX_ONSETS; i++)
    {
		pulseWaveVelocity[i]->SetDefaults();
    }
}
void BizDelta::SetDefaults()
{
	heartRate = BizConstants::DEFAULT_FLOAT_VALUE;
	deltaTime = BizConstants::DEFAULT_FLOAT_VALUE;
	correctedTime = BizConstants::DEFAULT_FLOAT_VALUE;
	pulseWaveVelocity = BizConstants::DEFAULT_FLOAT_VALUE;
	isValid = false;
}

/**
ValidateBeforeStore

DESCRIPTION

	Validate the PWV measurement before storing including:
		meanPulseWaveVelocity,
		standardDeviation.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - PWV measurement is valid.

	false - PWV measurement is not valid.

*/
bool BizPWV::ValidateBeforeStore()
{
	// Validate input parameters
	if (!Validate())
	{
		return false;
	}

	// Validate PWV against the adult range
	if (meanPulseWaveVelocity < MIN_ADULT_PWV)
	{
		// PWV's in the children range are allowed after confirmation
		/* TBD: 
			if (CrxMessageFacade::Instance()->Message(TraceEventType::Confirmation,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails()\n\n +
			CrxMessageFacade::Instance()->messageResources->GetString(L"PWV_INVALID_ADULT", CultureInfo::CurrentUICulture)
			+ Convert::ToString(meanPulseWaveVelocity, CultureInfo::CurrentUICulture)
			+ Convert::ToString(MAX_PWV, CultureInfo::CurrentUICulture)
			+ Convert::ToString(MIN_ADULT_PWV, CultureInfo::CurrentUICulture),
			"") == ID_NO)
		 {*/
			return false;
		 //}
	}
	
	// Display a warning if the standard deviation is high
	if (standardDeviation > HIGH_STANDARD_DEVIATION * meanPulseWaveVelocity)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Warning,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails()\n\n +
			CrxMessageFacade::Instance()->messageResources->GetString(L"PWV_DEVIATION_HIGH", CultureInfo::CurrentUICulture)
			+ Convert::ToString(standardDeviation, CultureInfo::CurrentUICulture)
			+ Convert::ToString(meanPulseWaveVelocity, CultureInfo::CurrentUICulture),
			"");*/
	}

	return true;
}
/**
Calculate()

DESCRIPTION

	Calculate all members of this class.

INPUT

	User input distances,
	correctionTime,
	carotidSignal->signal,
	femoralSignal->signal.

OUTPUT

	calculatedDistance,
	carotidSignal->floatOnsets,
	femoralSignal->floatOnsets,
	QualityControl - TBD,
	meanHeartRate,
	pulseWaveVelocity array,
	numberOfDeltas,
	numberOfValidDeltas,
	meanDeltaTime,
	meanCorrectedTime,
	meanPulseWaveVelocity,
	standardDeviation,
	isCarotidSignalValid,
	isFemoralSignalValid,
	isStandardDeviationValid.

RETURN

	boolean success or not.
*/
bool BizPWV::Calculate()
{
	// Default values for calculated members
    SetDefaults();
    
	// Validate input members and calculate distance
    if (!Validate())
    {
       return false;
    }

    // Check whether enough points have been captured
    if (!ValidateSignals())
    {
      return false;
    }

	// Find the onsets for both signals
	if (!carotidSignal->FindOnsets())
	{
		return false;
	}
	if (!femoralSignal->FindOnsets())
	{
		return false;
	}

	// Calculate quality control information -
	// Cannot return false if FindOnsets returns true
	CalculateQualityControls();

	/* Calculate heart rate
	if (!CalculateHeartRate())
	{
		return false;
	}*/

	// Calculate the array of heart rates and pulse wave velocities
	if (!CalculateBizDeltaArray())
	{
		return false;
	}

	// Calculate means and standardDeviation
	if (!CalculateFeatures())
	{
		return false;
	}

	return true;
}
/**
CalculateAndValidateDistance

DESCRIPTION

	Calculate and Validate PWV Distance.

INPUT

	CrxConfigFacade::Instance()->isSubtractingMethod(),
	myCuffDistance->distance,
	myCarotidDistance->distance,
	myFemoral2CuffDistance->distance,
	myPWVDirectDistance->distance.

OUTPUT

	calculatedDistance.

RETURN

	true  - PWV Calculated Distance is valid.

	false - PWV Calculated Distance is not valid.

*/
bool BizPWV::CalculateAndValidateDistance()
{
	short distance;
	bool isValid = false;
	
	CrxStructPwvSetting^ pwvSetting = CrxConfigManager::Instance->PwvSettings;

	if (pwvSetting->PWVDistanceMethod == 0) // TBD: replace magic number for subtracting method
	{
		distance = myCuffDistance->distance - myCarotidDistance->distance - myFemoral2CuffDistance->distance;
	} 
	else
	{
		distance = myPWVDirectDistance->distance - myFemoral2CuffDistance->distance;
	}

	// Validate the distance first as it may be negative and -
	// calculatedDistance is unsigned
	if (distance < PWV_DISTANCE_MIN || distance > PWV_DISTANCE_MAX)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Notification,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			CrxMessageFacade::Instance()->messageResources->GetString(L"PWV_INVALID_DISTANCE", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(distance, CultureInfo::CurrentUICulture), 
			"");*/
	}
	else
	{
		calculatedDistance = distance;
		isValid = true;
	}

	return isValid;
}

/**
 ** PrepareToCaptureSignal()
 **
 ** DESCRIPTION
 **
 **  Prepares the PWV class to store new signals.

 ** INPUT
 **
 **  none.

 ** OUTPUT
 **
 **  none.

 ** RETURN
 **
 **  none.
*/
void BizPWV::PrepareToCaptureSignal()
{
  // Reset calculated members
  SetDefaults();
  
  // Set up ready flags for Signals
  carotidSignal->PrepareToCapture();
  femoralSignal->PrepareToCapture();
}

bool BizPWV::SaveToFile()
{
  /*PATIENT_RECORD_TYPE  pat;
  if (patient_get(&pat))
  {
    String lFileName = ExtractFilePath(Application->ExeName) + EXPORT_SUBDIR + "pwv_session_" +
                        pat.surname + "_" + DateTime.FormatString("ddmmmyyyy") + ".txt";

    DeleteFile(lFileName);
    int lFileHandle = FileCreate(lFileName);

    // Validation
    if (lFileHandle <= 0)
    {
        MsgBox(LoadStr(MSG_COMMS_NO_FILE) + lFileName + "\n\n" +
                LoadStr(MSG_COMMS_CHECK_FILENAME), SWARNING, MB_ICONSTOP);
        return false;
    }
    // Printing arrays
    if (ExportArrays(lFileHandle) == false)
    {
        return false;
    }

    FileClose(lFileHandle);
    return true;
  }*/
  return false;
}

/**
 ** ValidateSignals()
 **
 ** DESCRIPTION
 **
 **  Validate the properties of the PWV class signals.

 ** INPUT
 **
 **  Signal class members.

 ** OUTPUT
 **
 **   none.

 ** RETURN
 **
 **  boolean success or not.
*/
bool BizPWV::ValidateSignals()
{
	bool ret1 = carotidSignal->ValidateSignal(MIN_SIGNAL_LENGTH, TONOMETER_MIN_SIGNAL_HEIGHT);
	bool ret2 = femoralSignal->ValidateSignal(MIN_SIGNAL_LENGTH, CUFF_MIN_SIGNAL_HEIGHT);
	bool ret = ret1 & ret2;
	return ret;
}

/**
 ** CalculateHeartRate()
 **
 ** DESCRIPTION
 **
 **  Calculate heart rate from the Femoral Cuff Onsets.

 ** INPUT
 **
 **  Signal class members,
 **  sampleRate.

 ** OUTPUT
 **
 **  none.

 ** RETURN
 **
 **  boolean success or not
*/
/*bool BizPWV::CalculateHeartRate()
{
	// Initialisation
	unsigned short index;
	unsigned short numberOfPulses = femoralSignal->onsetsLength - 1;
	float averagePulseLength = 0;
	unsigned short numberOfValidPulses = 0;
	float sum = 0;
	
	// Calculate AveragePulseLength
	for (index = 0; index < numberOfPulses; index++)
	{
		averagePulseLength += femoralSignal->floatOnsets[index + 1] - femoralSignal->floatOnsets[index];
		numberOfValidPulses++;
	}
	averagePulseLength /= numberOfValidPulses;

	// Reject extra short and long pulses
	numberOfValidPulses = 0;
	for (index = 0; index < numberOfPulses; index++)
	{
		float pulseLength = femoralSignal->floatOnsets[index + 1] - femoralSignal->floatOnsets[index];
		if ((pulseLength > averagePulseLength * MIN_VALID_PULSELENGTH_PERCENT) &&
		  (pulseLength < averagePulseLength * MAX_VALID_PULSELENGTH_PERCENT))
		{
			sum += pulseLength;
			numberOfValidPulses++;
		}
	}
	
	// Validate numberOfValidPulses
	if (numberOfValidPulses <= 0)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails()\n\n +
			CrxMessageFacade::Instance()->messageResources->GetString(L"PWV_SIGNAL_TOO_BAD", CultureInfo::CurrentUICulture), 
			"");
		return false;
	}

	// Calculate heartRate
	meanHeartRate = (60 * sampleRate) / (sum / numberOfValidPulses);

	// Validate meanHeartRate
	if (meanHeartRate < MIN_HEART_RATE || meanHeartRate > MAX_HEART_RATE)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails()\n\n +
			CrxMessageFacade::Instance()->messageResources->GetString(L"PWV_INVALID_HEART_RATE", CultureInfo::CurrentUICulture)
			+ Convert::ToString(meanHeartRate, CultureInfo::CurrentUICulture), 
			"");
		meanHeartRate = BizConstants::DEFAULT_VALUE;
		return false;
	}

	// Success
	return true;
}*/
/**
CalculateBizDeltaArray()

DESCRIPTION

	Calculate the BizDelta array between the femoral and carotid signals

INPUT

	sampleRate,
	calculatedDistance,
	correctionTime,
	carotidSignal,
	femoralSignal.

OUTPUT

	array<BizDelta^>^ pulseWaveVelocity,
	numberOfDeltas,
	numberOfValidDeltas.

RETURN

	boolean success or not
*/
bool BizPWV::CalculateBizDeltaArray()
{
	// Initialisation
	unsigned short index;
	unsigned short carotidIndex = 0;
	unsigned short femoralIndex = 0;
	unsigned short previousFemoralIndex = 0;
	unsigned short previousCarotidIndex = 0;
	
	// Mark all onsets as negatives, which indicates an invalid onset
	for (index = 0; index < carotidSignal->onsetsLength; index++)
	{
		carotidSignal->floatOnsets[index] = -carotidSignal->floatOnsets[index];
	}
	for (index = 0; index < femoralSignal->onsetsLength; index++)
	{
		femoralSignal->floatOnsets[index] = -femoralSignal->floatOnsets[index];
	}
	
	// Calculate the time differences and pulse wave velocities between the 2 signals -
	// until the boundaries are reached
	while (femoralIndex < femoralSignal->onsetsLength && carotidIndex < carotidSignal->onsetsLength)
	{
		// Get current onsets
		float carotidOnset = Math::Abs(carotidSignal->floatOnsets[carotidIndex]);
		float femoralOnset = Math::Abs(femoralSignal->floatOnsets[femoralIndex]);
		
		// The pulse takes longer to travel to the femoral artery than the carotid artery
		if (femoralOnset > carotidOnset)
		{
			// Check additional carotidOnset before femoralOnset
			if (carotidIndex == carotidSignal->onsetsLength - 1 || femoralOnset < Math::Abs(carotidSignal->floatOnsets[carotidIndex + 1]))
			{
				// Calculate heart rate of the previous delta once the next delta is found.
				// Ignored onsets can only be noise and so are not considered when calculating -
				// heart rate.
				if ( numberOfDeltas > 0 )
				{
					pulseWaveVelocity[numberOfDeltas - 1]->heartRate = (60 * sampleRate) / 
						(femoralOnset - Math::Abs(femoralSignal->floatOnsets[previousFemoralIndex]));
					
					// Validate the heart rate if the delta was considered valid
					if (pulseWaveVelocity[numberOfDeltas - 1]->isValid &&
						(pulseWaveVelocity[numberOfDeltas - 1]->heartRate > MAX_HEART_RATE ||
						pulseWaveVelocity[numberOfDeltas - 1]->heartRate < MIN_HEART_RATE))
					{
						// Mark the delta and onsets as invalid
						pulseWaveVelocity[numberOfDeltas - 1]->isValid = false;
						femoralSignal->floatOnsets[previousFemoralIndex] = -Math::Abs(femoralSignal->floatOnsets[previousFemoralIndex]);
						carotidSignal->floatOnsets[previousCarotidIndex] = -Math::Abs(carotidSignal->floatOnsets[previousCarotidIndex]);
						numberOfValidDeltas--;
					}
				}
					
				// Ignore the last delta as we cannot verify the heart rate
				if (carotidIndex != carotidSignal->onsetsLength - 1 && femoralIndex != femoralSignal->onsetsLength - 1)
				{
					pulseWaveVelocity[numberOfDeltas]->deltaTime = (femoralOnset - carotidOnset) * 1000 / sampleRate;
					pulseWaveVelocity[numberOfDeltas]->correctedTime = pulseWaveVelocity[numberOfDeltas]->deltaTime - correctionTime;

					// Validate the corrected time
					if (pulseWaveVelocity[numberOfDeltas]->correctedTime > 0)
					{
						// Calculate and validate the pulse wave velocity
						pulseWaveVelocity[numberOfDeltas]->pulseWaveVelocity = (float) calculatedDistance / pulseWaveVelocity[numberOfDeltas]->correctedTime;
						if (pulseWaveVelocity[numberOfDeltas]->pulseWaveVelocity <= MAX_PWV &&
							pulseWaveVelocity[numberOfDeltas]->pulseWaveVelocity >= MIN_PWV)
						{
							// Add valid deltas
							pulseWaveVelocity[numberOfDeltas]->isValid = true;
							femoralSignal->floatOnsets[femoralIndex] = femoralOnset;
							carotidSignal->floatOnsets[carotidIndex] = carotidOnset;
							numberOfValidDeltas++;
						}
					}
					// Ignore invalid deltas
					numberOfDeltas++;
					previousFemoralIndex = femoralIndex;
					previousCarotidIndex = carotidIndex;
				}
				femoralIndex++;
				carotidIndex++;
			}
			// Ignore additional carotid onsets
			else
			{
				carotidIndex++;
			}
		}
		// Ignore additional femoral onsets
		else
		{
			femoralIndex++;
		}
	}

	// Check if enough time differences were found
	if (numberOfDeltas < MIN_NUMBER_OF_DELTAS)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"MATH_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails()\n\n +
			CrxMessageFacade::Instance()->messageResources->GetString(L"PWV_NOT_ENOUGH_DELTAS", CultureInfo::CurrentUICulture), 
			"");*/
		return false;
	}
	// Check if enough pulse wave velocities were found
	if (numberOfValidDeltas < MIN_NUMBER_OF_DELTAS)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"MATH_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails()\n\n +
			CrxMessageFacade::Instance()->messageResources->GetString(L"PWV_INVALID", CultureInfo::CurrentUICulture), 
			"");*/
		return false;
	}

	// Success
	return true;
}
/**
CalculateFeatures()

DESCRIPTION

	Calculate average heart rate, average pulseWaveVelocity and its standard deviation.

INPUT

	numberOfDeltas,
	numberOfValidDeltas,
	pulseWaveVelocity array.

OUTPUT
	
	meanHeartRate,
	meanDeltaTime,
	meanCorrectedTime,
	meanPulseWaveVelocity,
	standardDeviation,
	isStandardDeviationValid.

RETURN

	boolean success or not.
*/
bool BizPWV::CalculateFeatures()
{	
	// Initialisation
	unsigned short index;
	float sumHeartRate = 0;
	float sumDeltaTime = 0;
	float sumCorrectedTime = 0;
	float sumPulseWaveVelocity = 0;
	float sumStandardDeviation = 0;
	
	// Calculate mean values for valid deltas
	for (index = 0; index < numberOfDeltas; index++)
	{
		if (pulseWaveVelocity[index]->isValid)
		{
			sumHeartRate += pulseWaveVelocity[index]->heartRate;
			sumDeltaTime += pulseWaveVelocity[index]->deltaTime;
			sumCorrectedTime += pulseWaveVelocity[index]->correctedTime;
			sumPulseWaveVelocity += pulseWaveVelocity[index]->pulseWaveVelocity;
		}
	}

	// Averaging
	meanHeartRate = sumHeartRate / numberOfValidDeltas;
	meanDeltaTime = sumDeltaTime / numberOfValidDeltas;
	meanCorrectedTime = sumCorrectedTime / numberOfValidDeltas;
	meanPulseWaveVelocity = sumPulseWaveVelocity / numberOfValidDeltas;

	// Calculate standardDeviation
	for (index = 0; index < numberOfDeltas; index++)
	{
		if (pulseWaveVelocity[index]->isValid)
		{
			sumStandardDeviation += (float) Math::Pow(pulseWaveVelocity[index]->pulseWaveVelocity - meanPulseWaveVelocity, 2);
		}
	}
	standardDeviation = (float) Math::Sqrt(sumStandardDeviation / numberOfValidDeltas);

	// Validate standard deviation
	if (standardDeviation <= (VALID_STANDARD_DEVIATION * meanPulseWaveVelocity))
	{
		isStandardDeviationValid = true;
	}

	// Unacceptable standard deviation
	if (standardDeviation >= meanPulseWaveVelocity)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails()\n\n +
			CrxMessageFacade::Instance()->messageResources->GetString(L"PWV_DEVIATION_TOO_BIG", CultureInfo::CurrentUICulture)
			+ Convert::ToString(standardDeviation, CultureInfo::CurrentUICulture)
			+ Convert::ToString(meanPulseWaveVelocity, CultureInfo::CurrentUICulture),
			"");*/
		return false;
	}

	return true;
}

/**
CalculateQualityControls()

DESCRIPTION

	Calculate quality control for the carotid and femoral signals.

INPUT

	carotidSignal,
	femoralSignal.

OUTPUT
	isCarotidSignalValid,
	isFemoralSignalValid.

RETURN

	boolean success or not.
*/
bool BizPWV::CalculateQualityControls()
{	
	// Calculate quality control information
	if (!carotidSignal->CalculateQualityControls())
	{
		return false;
	}
	if (!femoralSignal->CalculateQualityControls())
	{
		return false;
	}

	// Validate quality control information
	if (carotidSignal->pulseHeight >= VALID_CAROTID_PULSE_HEIGHT &&
		carotidSignal->pulseHeightVariation <= VALID_CAROTID_PULSE_HEIGHT_VARIATION)
	{
		isCarotidSignalValid = true;
	}
	if (femoralSignal->pulseHeight >= VALID_FEMORAL_PULSE_HEIGHT)
	{
		isFemoralSignalValid = true;
	}

	return true;
}

// Log current patient and measurement data
void BizPWV::LogSetupData()
{
	String^ logMesasge;
	array<String^> ^dateString;

	// Collect and log current patient data
	logMesasge = "PWV current patient:";
	logMesasge += "\npatientId=" + BizPatient::Instance()->patientId;
	logMesasge += " firstName=" + BizPatient::Instance()->firstName;
	logMesasge += " lastName=" + BizPatient::Instance()->lastName;
	logMesasge += " groupStudyId=" + BizPatient::Instance()->groupStudyId;
	// TBD: find out why dateOfBirth.Date is also returning the time
	dateString = BizPatient::Instance()->dateOfBirth.Date.ToString()->Split();
	logMesasge += " dob=" + dateString[0];
	logMesasge += " gender=" + BizPatient::Instance()->gender;
	CrxLogger::Instance->Write(logMesasge);

	// Collect and log PWV measurement data
	logMesasge = "PWV measurement data:";
	logMesasge += "\nh(cm)=" + heightAndWeight->heightInCentimetres;
	logMesasge += " w(kg)=" + heightAndWeight->weightInKilograms;
	logMesasge += " h(in)=" + heightAndWeight->heightInInches;
	logMesasge += " w(lb)=" + heightAndWeight->weightInPounds;
	logMesasge += " op=" + BizSession::Instance()->measurement->operatorId;
	logMesasge += " notes=" + BizSession::Instance()->measurement->notes;
	if (BizSession::Instance()->measurement->bloodPressure->SP) 
	{
		logMesasge += " SP=" + BizSession::Instance()->measurement->bloodPressure->SP->Reading.ToString();
	}
	if (BizSession::Instance()->measurement->bloodPressure->DP) 
	{
		logMesasge += " DP=" + BizSession::Instance()->measurement->bloodPressure->DP->Reading.ToString();
	}
	if (BizSession::Instance()->measurement->bloodPressure->MP) 
	{
		logMesasge += " MP=" + BizSession::Instance()->measurement->bloodPressure->MP->Reading.ToString();
	}
	logMesasge += " carotid=" + myCarotidDistance->distance;
	logMesasge += " cuff=" + myCuffDistance->distance;
	logMesasge += " femoral2cuff=" + myFemoral2CuffDistance->distance;
	logMesasge += " pwv distance=" + myPWVDirectDistance->distance;
	CrxLogger::Instance->Write(logMesasge);
}

/**
SaveCaptureData()

DESCRIPTION

	Save the captured carotid tonometer and femoral cuff data in the simulation file format:
	<carotid tonometer data>TAB<femoral cuff data>

	It's assumed that same amount of data had been captured in parallel 
	in carotid tonometer and femoral cuff data buffers.

INPUT

	carotidSignal,
	femoralSignal.

OUTPUT
	isCarotidSignalValid,
	isFemoralSignalValid.

RETURN

	boolean success or not.
*/
bool BizPWV::SaveCaptureData()
{
	array< unsigned short >^ tonometerData;
	array< unsigned short >^ cuffPulse;
	unsigned short startIndex; 
	unsigned short endIndex; 
	unsigned int bufferSize;

	tonometerData = tonometerBuffer->ReadBuffer(bufferSize, startIndex, endIndex);
	cuffPulse = cuffBuffer->ReadBuffer(bufferSize, startIndex, endIndex);

	// If the buffer is not full, calculate up to the last sample
	if ( startIndex != endIndex )
	{
		bufferSize = endIndex;
	}
	
	return DalFacade::Instance()->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
}
