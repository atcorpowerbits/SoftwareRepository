/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Measurement Classes
*/

#include "StdAfx.h"
#include <measure.h>
#include <math_library.h>
#include <patient.h>

using namespace CRX_CONFIG_NAMESPACE;
using namespace BIZ_NAMESPACE;

/**
 ** Constructor()
 **
 ** DESCRIPTION:
 **  Constructor for measure class.

 ** INPUT:
 **	 none.

 ** OUTPUT:
 **  none.

 ** RETURN:
 **  none.
*/
BizMeasure::BizMeasure()
{
	Initialise();
}

/**
 ** Initialise()
 **
 ** DESCRIPTION:
 **  Initialse the members of the measure class.

 ** INPUT:
 **	 none.

 ** OUTPUT:
 **  dataRevision,
 **  sampleRate,
 **  measurementDateTime,
 **  auditDateTime.

 ** RETURN:
 **  none.
*/
void BizMeasure::Initialise()
{
	systemId = BizPatient::Instance()->systemId;
	patientNumber = BizPatient::Instance()->patientNumber;                          
	groupStudyId = BizPatient::Instance()->groupStudyId;
	measurementDateTime = DateTime::Now;     
	patientAge = 0;
	
	dataRevision = DATA_REVISION;           

	medication = "";    
	notes = "";          
	operatorId = "";       
	interpretation = ""; 

	heightAndWeight = gcnew BizHeightAndWeight;
	
	if (CrxConfigManager::Instance->
		GeneralSettings->BloodPressureEntryOptions == CrxConfigConstants::GENERAL_BP_ENTRY_MPDP)
	{
		bloodPressureEntryOption = CrxConfigConstants::GENERAL_BP_ENTRY_MPDP;
		bloodPressure = gcnew BizMPAndDP;
	} 
	else if (CrxConfigManager::Instance->
		GeneralSettings->BloodPressureEntryOptions == CrxConfigConstants::GENERAL_BP_ENTRY_SPDP)
	
	{
		bloodPressureEntryOption = CrxConfigConstants::GENERAL_BP_ENTRY_SPDP;
		bloodPressure = gcnew BizSPAndDP;
	}
	else if (CrxConfigManager::Instance->
		GeneralSettings->BloodPressureEntryOptions == CrxConfigConstants::GENERAL_BP_ENTRY_SPMP)
	
	{
		bloodPressureEntryOption = CrxConfigConstants::GENERAL_BP_ENTRY_SPMP;
		bloodPressure = gcnew BizSPAndMP;
	}	
	
	captureTime = CrxConfigManager::Instance->PwvSettings->CaptureTime; //TBD: Why is capture time from PWV setting needed in generic measure class? -
	sampleRate = 1024 / DalConstants::DataSamplingInterval; //DEFAULT_SAMPLE_RATE;  
	
	simulation = false;

	/*reasonForChange = "";
	auditChange = AUDIT_ORIGINAL;
	auditDateTime = DateTime::Now;	
	*/
}

/**
Validate

DESCRIPTION

	Validate the measurement before calculation that:
		height and weight are within the range (if entered),
		blood pressures are within the range (if entered),
	    system ID is not null or empty,
		internal patient number is not zero or negative,
		measurement date time is not in the future,
		data revision matches math revision,
		sample rate is within the range,
		capture time is within the range.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - measurement is valid.

	false - measurement is not valid.

*/
bool BizMeasure::Validate()
{	
	// Validate height and weight (if entered) and calculate metric or imperial equivalents -
	// and the BMI
	if (!heightAndWeight->ValidateAndCalculate())
	{
		return false;
	}

	// Validate blood pressures (if entered)
	if (!bloodPressure->Validate())
	{
		return false;
	}

	// GroupStudyID can be blank, so no need to validate
	// Validate Customer System ID
	if ( systemId <=0 )
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_NO_SYSTEMID", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(sampleRate, CultureInfo::CurrentUICulture), 
			"");*/
		return false;
	}

	// Validate internal patient number
	if (patientNumber <= 0)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_NO_PATIENT_NUMBER", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(sampleRate, CultureInfo::CurrentUICulture), 
			"");*/
		return false;
	}
	
	// Validate datetime
	if (measurementDateTime > DateTime::Now)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_DATETIME", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(measurementDateTime, CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_DATETIME", CultureInfo::InvariantCulture) 
			+ Convert::ToString(measurementDateTime, CultureInfo::InvariantCulture));*/
		return false;
	}

	// Validate data revision
	if (dataRevision != DATA_REVISION)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_DATA_REVISION", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(dataRevision, CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_DATA_REVISION", CultureInfo::InvariantCulture) 
			+ Convert::ToString(dataRevision, CultureInfo::InvariantCulture));*/
		return false;
	}

	// Validate sample rate
	if (sampleRate < MIN_SAMPLE_RATE || sampleRate > MAX_SAMPLE_RATE)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_SAMPLERATE", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(sampleRate, CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_SAMPLERATE", CultureInfo::InvariantCulture) 
			+ Convert::ToString(sampleRate, CultureInfo::InvariantCulture));*/
		return false;
	}

	// Validate capture time
	if (captureTime < MIN_CAPTURE_TIME || captureTime > MAX_CAPTURE_TIME)
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_CAPTURE_TIME", CultureInfo::CurrentUICulture) 
			+ Convert::ToString(captureTime, CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_CAPTURE_TIME", CultureInfo::InvariantCulture) 
			+ Convert::ToString(captureTime, CultureInfo::InvariantCulture));*/
		return false;
	}

	return true;
}
/**
CalculateAge()

DESCRIPTION

	Calculate the patient's age on the date of the measurement.

INPUT

	measurementDateTime,
	BizPatient->dateOfBirth.

OUTPUT

	patientAge.

RETURN

	boolean success or not.
*/
bool BizMeasure::CalculateAge()
{
	// Check if the user has entered a date of birth
	if ( BizPatient::Instance()->dateOfBirth <= BizConstants::PATIENT_INITIAL_DATE )
	{
	   /* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_NO_DATE_OF_BIRTH", CultureInfo::CurrentUICulture), 
			"");*/
	   return false;
	}

	// Check if the age will be greater than 0
	if ( measurementDateTime.Year <= BizPatient::Instance()->dateOfBirth.Year )
	{
		/* TBD: CrxMessageFacade::Instance()->Message(TraceEventType::Error,
			CrxMessageFacade::Instance()->messageResources->GetString(L"VALIDATION_ERROR", CultureInfo::CurrentUICulture), 
			GetCurrentMeasureDetails() +
			CrxMessageFacade::Instance()->messageResources->GetString(L"MEASURE_INVALID_DATE_OF_BIRTH", CultureInfo::CurrentUICulture), 
			"");*/
		patientAge = 0;
		return false;
	}	

	// Calculate age
	patientAge = measurementDateTime.Year - BizPatient::Instance()->dateOfBirth.Year;
   
	// If the patient's birthday hasn't occured this year, then deduct 1 year
	if ( BizPatient::Instance()->dateOfBirth.DayOfYear > measurementDateTime.DayOfYear )
	{
		patientAge--;
	}
	
	return true;
}

/**
CalculateBloodPressureRange()

DESCRIPTION

	Calculate the blood pressure range.

INPUT

	bloodPressure->SP->Reading.

OUTPUT

	bloodPressureRange,
	bloodPressureRangeTitle.

RETURN

	boolean success or not.
*/
bool BizMeasure::CalculateBloodPressureRange()
{	
	// Blood Pressure range can only be calculated if SP has been entered
	if ( bloodPressure->SP->Reading == BizConstants::DEFAULT_VALUE )
	{
		// TBD: Display status bar message of the form "SP is required to display the reference range"
		return false;
	}

	// Calculate the blood pressure range
	if ( bloodPressure->SP->Reading < BLOOD_PRESSURE_OPTIMAL_LIMIT )
	{
		bloodPressureRange = BLOOD_PRESSURE_OPTIMAL;
	}
	else if ( bloodPressure->SP->Reading < BLOOD_PRESSURE_NORMAL_LIMIT )
	{
		bloodPressureRange = BLOOD_PRESSURE_NORMAL;
	}
	else if ( bloodPressure->SP->Reading < BLOOD_PRESSURE_HIGH_NORMAL_LIMIT )
	{
		bloodPressureRange = BLOOD_PRESSURE_HIGH_NORMAL;
	}
	else if ( bloodPressure->SP->Reading < BLOOD_PRESSURE_GRADE_I_LIMIT )
	{
		bloodPressureRange = BLOOD_PRESSURE_GRADE_I;
	}
	else
	{
		bloodPressureRange = BLOOD_PRESSURE_GRADE_II_III;
	}

	bloodPressureRangeTitle = _bloodPressureRangeTitles[bloodPressureRange];

	// Blood pressure range was calculated successfully
	return true;
}

/**
 ** Constructor()
 **
 ** DESCRIPTION:

 **  Constructor for height and weight class.

 ** INPUT:

 **	 none.

 ** OUTPUT:

 **  none.

 ** RETURN:

 **  none.
*/
BizHeightAndWeight::BizHeightAndWeight()
{
	Initialise();
}

/**
 ** Initialise()
 **
 ** DESCRIPTION:

 **  Initialse the members of the height and weight class.

 ** INPUT:

 **	 none.

 ** OUTPUT:

 **  none.

 ** RETURN:

 **  none.
*/
void BizHeightAndWeight::Initialise()
{
	heightInCentimetres = BizConstants::DEFAULT_VALUE;
	heightInInches = BizConstants::DEFAULT_VALUE;
	weightInKilograms = BizConstants::DEFAULT_VALUE;
	weightInPounds = BizConstants::DEFAULT_VALUE;
	bodyMassIndex = BizConstants::DEFAULT_VALUE;	
}

/**
ValidateAndCalculate

DESCRIPTION

	Validate and calculate the height and weight before calculation.

INPUT

	None.

OUTPUT

	None.

RETURN

	true  - height and weight is valid.

	false - height and weight is not valid.

*/
bool BizHeightAndWeight::ValidateAndCalculate()
{
	short output;

	// Ignore previous BMI calculation
	bodyMassIndex = BizConstants::DEFAULT_VALUE;
	
	if (CrxConfigManager::Instance->
		GeneralSettings->HeightandWeightUnit == CrxConfigConstants::GENERAL_UNIT_METRIC)
	{
		// Ignore previous imperial values
		heightInInches = BizConstants::DEFAULT_VALUE;
		weightInPounds = BizConstants::DEFAULT_VALUE;
		
		// Check if the user has entered a value
		if ( heightInCentimetres != BizConstants::DEFAULT_VALUE )
		{
			if (heightInCentimetres < MEA_HEIGHT_CM_MIN || heightInCentimetres > MEA_HEIGHT_CM_MAX)
			{
				//TBD: Inform user "Height is not within the valid range between ... cm and ... cm"
				return false;
			}
			// Calculate heightInInches. 
			// Cannot return false as heightInCentimetres has already been validated
			BizMath::Round( heightInCentimetres / CONVERT_INCH_TO_CM, output );
			heightInInches = output;
		}
		
		// Check if the user has entered a value
		if ( weightInKilograms != BizConstants::DEFAULT_VALUE )
		{
			if (weightInKilograms < MEA_WEIGHT_KG_MIN || weightInKilograms > MEA_WEIGHT_KG_MAX)
			{
				//TBD: Inform user "Weight is not within the valid range between ... kg and ... kg"
				return false;
			}
			// Calculate weightInPounds. 
			// Cannot return false as weightInKilograms has already been validated
			BizMath::Round( weightInKilograms / CONVERT_POUND_TO_KILO, output );
			weightInPounds = output;
		}
	}
	else if (CrxConfigManager::Instance->
		GeneralSettings->HeightandWeightUnit == CrxConfigConstants::GENERAL_UNIT_IMPERIAL)
	{
		// Ignore previous metric values
		heightInCentimetres = BizConstants::DEFAULT_VALUE;
		weightInKilograms = BizConstants::DEFAULT_VALUE;
		
		// Check if the user has entered a value
		if ( heightInInches != BizConstants::DEFAULT_VALUE )
		{
			if (heightInInches < MEA_HEIGHT_INCH_MIN || heightInInches > MEA_HEIGHT_INCH_MAX)
			{
				//TBD: Inform user "Height is not within the valid range between ... in and ... in"
				return false;
			}
			// Calculate heightInCentimetres. 
			// Cannot return false as heightInInches has already been validated
			BizMath::Round( heightInInches * CONVERT_INCH_TO_CM, output );
			heightInCentimetres = output;
		}
		
		// Check if the user has entered a value
		if ( weightInPounds != BizConstants::DEFAULT_VALUE )
		{
			if (weightInPounds < MEA_WEIGHT_LB_MIN || weightInPounds > MEA_WEIGHT_LB_MAX)
			{
				//TBD: Inform user "Weight is not within the valid range between ... lb and ... lb"
				return false;
			}
			// Calculate weightInKilograms. 
			// Cannot return false as weightInPounds has already been validated
			BizMath::Round( weightInPounds * CONVERT_POUND_TO_KILO, output );
			weightInKilograms = output;
		}
	}

	// Calculate BMI (kg/m^2) if the user entered height and weight
	if ( heightInCentimetres != BizConstants::DEFAULT_VALUE 
		&& weightInKilograms != BizConstants::DEFAULT_VALUE )
	{
		bodyMassIndex = 100 * 100 * (float) weightInKilograms / 
			((float) heightInCentimetres * (float) heightInCentimetres);
	}
	return true;
}

/**
Validate

DESCRIPTION

	Validate the height object is within the valid range in centimeters.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - Height is valid.

	false - Height is not valid.

*/		
bool BizHeightCM::Validate()
{
	bool isValid;
	if (Height >= MEA_HEIGHT_CM_MIN && Height <= MEA_HEIGHT_CM_MAX)
	{
		isValid = true;
	} else 
	{
		//TBD: Inform user "Height is not within the valid range between ... cm and ... cm"
		isValid = false;
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate the height object is within the valid range in inches.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - Height is valid.

	false - Height is not valid.

*/		
bool BizHeightInch::Validate()
{
	bool isValid;
	if (Height >= MEA_HEIGHT_INCH_MIN && Height <= MEA_HEIGHT_INCH_MAX)
	{
		isValid = true;
	} else 
	{
		//TBD: Inform user "Height is not within the valid range between ... and ... feet"
		// Don't forget to convert internal range in inches to feet for user information!
		isValid = false;
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate the weight object is within the valid range in kilograms.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - Weight is valid.

	false - Weight is not valid.

*/		
bool BizWeightKG::Validate()
{
	bool isValid;
	if (Weight >= MEA_WEIGHT_KG_MIN && Weight <= MEA_WEIGHT_KG_MAX)
	{
		isValid = true;
	} else 
	{
		//TBD: Inform user "Weight is not within the valid range between ... and ... kg"
		isValid = false;
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate the weight object is within the valid range in pounds.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - Weight is valid.

	false - Weight is not valid.

*/		
bool BizWeightLB::Validate()
{
	bool isValid;
	if (Weight >= MEA_WEIGHT_LB_MIN && Weight <= MEA_WEIGHT_LB_MAX)
	{
		isValid = true;
	} else 
	{
		//TBD: Inform user "Weight is not within the valid range between ... and ... lb"
		isValid = false;
	}
	return isValid;
}
/**
 ** Constructor()
 **
 ** DESCRIPTION:
 **  Constructor for pressure reading class.

 ** INPUT:
 **	 none.

 ** OUTPUT:
 **  none.

 ** RETURN:
 **  none.
*/
BizPressureReading::BizPressureReading()
{
	Initialise();
}

/**
 ** Initialise()
 **
 ** DESCRIPTION:
 **  Initialse the members of the pressure reading class.

 ** INPUT:
 **	 none.

 ** OUTPUT:
 **  none.

 ** RETURN:
 **  none.
*/
void BizPressureReading::Initialise()
{
	Reading = BizConstants::DEFAULT_VALUE;	
}
/**
Validate

DESCRIPTION

	Validate pressure reading.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - valid

	false - invalid

*/		
bool BizPressureReading::Validate()
{
	// Check if the user has entered a value
	if ( Reading != BizConstants::DEFAULT_VALUE)
	{
		if (Reading < MEA_BP_MIN || Reading > MEA_BP_MAX)
		{
			return false;
		}
	}
	return true;
}
/**
Validate

DESCRIPTION

	Validate SP.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - valid

	false - invalid

*/		
bool BizSP::Validate()
{
	bool isValid;
	if (BizPressureReading::Validate())
	{
		isValid = true;
	} else {
		//TBD: Inform user "SP is not within the valid range between ... and ... mmHg"
		isValid = false;
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate DP.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - valid

	false - invalid

*/		
bool BizDP::Validate()
{
	bool isValid;
	if (BizPressureReading::Validate())
	{
		isValid = true;
	} else {
		//TBD: Inform user "DP is not within the valid range between ... and ... mmHg"
		isValid = false;
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate MP.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - valid

	false - invalid

*/		
bool BizMP::Validate()
{
	bool isValid;
	if (BizPressureReading::Validate())
	{
		isValid = true;
	} else {
		//TBD: Inform user "MP is not within the valid range between ... and ... mmHg"
		isValid = false;
	}
	return isValid;
}
/**
Validate

DESCRIPTION

	Validate SP and DP blood pressure.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - valid

	false - invalid

*/		
bool BizSPAndDP::Validate()
{
	if (!SP->Validate())
	{
		return false;
	} 

	if (!DP->Validate())
	{
		return false;
	} 
	
	// Check if the user has entered both values
	if ( SP->Reading != BizConstants::DEFAULT_VALUE
		&& DP->Reading != BizConstants::DEFAULT_VALUE)
	{ 
		if (SP->Reading < (DP->Reading + MEA_SP2DP_DIFF_MIN))
		{
			//TBD: Inform user "Diff bet SP and DP should be ... mmHg"
			return false;
		} 
	}
	return true;
}
/**
Validate

DESCRIPTION

	Validate MP and DP blood pressure.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - valid

	false - invalid

*/		
bool BizMPAndDP::Validate()
{
	if (!MP->Validate())
	{
		return false;
	} 

	if (!DP->Validate())
	{
		return false;
	} 
	
	// Check if the user has entered both values
	if ( MP->Reading != BizConstants::DEFAULT_VALUE
		&& DP->Reading != BizConstants::DEFAULT_VALUE)
	{ 
		if (MP->Reading < (DP->Reading + MEA_MP2DP_DIFF_MIN))
		{
			//TBD: Inform user "Diff bet MP and DP should be ... mmHg"
			return false;
		} 
	}
	return true;
}
/**
Validate

DESCRIPTION

	Validate SP and MP blood pressure.

INPUT

	None.

OUTPUT

	None.

RETURN

	true - valid

	false - invalid

*/		
bool BizSPAndMP::Validate()
{
	if (!SP->Validate())
	{
		return false;
	} 

	if (!MP->Validate())
	{
		return false;
	} 
	
	// Check if the user has entered both values
	if ( SP->Reading != BizConstants::DEFAULT_VALUE
		&& MP->Reading != BizConstants::DEFAULT_VALUE)
	{ 
		if (SP->Reading < (MP->Reading + MEA_SP2MP_DIFF_MIN))
		{
			//TBD: Inform user "Diff bet SP and MP should be ... mmHg"
			return false;
		} 
	}
	return true;
}

/**
Populate()

DESCRIPTION

	Populate the BizMeasure class from a database structure.

INPUT

	CrxStructPWVMeasurementData.

OUTPUT
	
	BizMeasure class members.

RETURN

	Boolean success or not.
*/
bool BizMeasure::Populate( CrxStructPWVMeasurementData^ record )
{
	// Validate
	if ( record == nullptr )
	{
		return false;
	}
	
	// Populate the Measure class properties
	// Cannot return false because the record has already been validated
	bloodPressure->Populate( record );
	bloodPressureEntryOption = record->BloodPressureEntryOption;
	bloodPressureRangeTitle = record->BloodPressureRange;

	// Cannot return false because the record has already been validated
	heightAndWeight->Populate( record );

	systemId = record->SystemIdentifier;
	groupStudyId = record->GroupIdentifier;
	patientNumber = record->PatientNumberInternal;

	measurementDateTime = record->StudyDateTime;
	dataRevision = record->DataRevision;
	patientAge = record->Age;

	notes = record->Notes;
	operatorId = record->Operator;
	
	captureTime = record->CaptureTime;
	sampleRate = record->SampleRate;
	simulation = record->Simulation;

	return true;
}

/**
Store()

DESCRIPTION

	Store the BizMeasure class into a database structure.

INPUT

	BizMeasure class members.

OUTPUT
	
	CrxStructPWVMeasurementData.

RETURN

	Boolean success or not.
*/
bool BizMeasure::Store( CrxStructPWVMeasurementData^ record )
{
	// Validate
	if ( record == nullptr )
	{
		return false;
	}
	
	// Cannot return false because the record has already been validated
	bloodPressure->Store( record );
	record->BloodPressureEntryOption = bloodPressureEntryOption;
	record->BloodPressureRange = bloodPressureRangeTitle;

	// Cannot return false because the record has already been validated
	heightAndWeight->Store( record );

	record->SystemIdentifier = systemId;
	record->GroupIdentifier = groupStudyId;
	record->PatientNumberInternal = patientNumber;

	record->StudyDateTime = measurementDateTime;
	record->DataRevision = dataRevision;
	record->Age = patientAge;

	record->Notes = notes;
	record->Operator = operatorId;
	
	record->CaptureTime = captureTime;
	record->SampleRate = sampleRate;
	record->Simulation = simulation;

	return true;
}
/**
Populate()

DESCRIPTION

	Populate the BizBloodPressure class from a database structure.

INPUT

	CrxStructPWVMeasurementData.

OUTPUT
	
	BizBloodPressure class members.

RETURN

	Boolean success or not.
*/
bool BizBloodPressure::Populate( CrxStructPWVMeasurementData^ record )
{
	// Validate
	if ( record == nullptr )
	{
		return false;
	}
	
	SP->Reading = record->SP;
	DP->Reading = record->DP;
	MP->Reading = record->MP;

	return true;
}

/**
Store()

DESCRIPTION

	Store the BizBloodPressure class into a database structure.

INPUT

	BizBloodPressure class members.

OUTPUT
	
	CrxStructPWVMeasurementData.

RETURN

	Boolean success or not.
*/
bool BizBloodPressure::Store( CrxStructPWVMeasurementData^ record )
{
	// Validate
	if ( record == nullptr )
	{
		return false;
	}
	
	record->SP = SP->Reading;
	record->DP = DP->Reading;
	record->MP = MP->Reading;

	return true;
}
/**
Populate()

DESCRIPTION

	Populate the BizHeightAndWeight class from a database structure.

INPUT

	CrxStructPWVMeasurementData.

OUTPUT
	
	BizHeightAndWeight class members.

RETURN

	Boolean success or not.
*/
bool BizHeightAndWeight::Populate( CrxStructPWVMeasurementData^ record )
{
	// Validate
	if ( record == nullptr )
	{
		return false;
	}
	
	heightInCentimetres = record->HeightInCentimetres;
	heightInInches = record->HeightInInches;
	weightInKilograms = record->WeightInKilograms;
	weightInPounds = record->WeightInPounds;
	bodyMassIndex = record->BodyMassIndex;

	return true;
}

/**
Store()

DESCRIPTION

	Store the BizHeightAndWeight class into a database structure.

INPUT

	BizHeightAndWeight class members.

OUTPUT
	
	CrxStructPWVMeasurementData.

RETURN

	Boolean success or not.
*/
bool BizHeightAndWeight::Store( CrxStructPWVMeasurementData^ record )
{
	// Validate
	if ( record == nullptr )
	{
		return false;
	}
	
	record->HeightInCentimetres = heightInCentimetres;
	record->HeightInInches = heightInInches;
	record->WeightInKilograms = weightInKilograms;
	record->WeightInPounds = weightInPounds;
	record->BodyMassIndex = bodyMassIndex;

	return true;
}