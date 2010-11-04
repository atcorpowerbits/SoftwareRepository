/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Measurement Classes
*/

#include "StdAfx.h"
#include <measure.h>

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
	// TBD: need to check the Height & Weight Unit from the config
	// then instantiate the right object, i.e. metric or imperial
	if (AtCor::Scor::CrossCutting::Configuration::CrxConfigManager::Instance->
		GeneralSettings->HeightandWeightUnit == CrxConfigConstants::GENERAL_UNIT_METRIC)
	{
		myHeight = gcnew BizHeightCM;
		myWeight = gcnew BizWeightKG;
	} else 
	{
		myHeight = gcnew BizHeightInch;
		myWeight = gcnew BizWeightLB;
	}
	// Instantiate BP object - default SP+DP
	myBP = gcnew BizSPAndDP;
	
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
	systemId = "";
	patientNumber = 0;                          
	groupStudyId = "";
	measurementDateTime = DateTime::Now;                        
	
	dataRevision = DATA_REVISION;           

	medication = "";    
	notes = "";          
	operatorId = "";       
	interpretation = ""; 

	//myHeight->Height = BizConstants::DEFAULT_VALUE; 
	//myWeight->Weight = BizConstants::DEFAULT_VALUE; 
	bodyMassIndex = BizConstants::DEFAULT_VALUE;    

	//myBP->SP = BizConstants::DEFAULT_VALUE;
	//myBP->MP = BizConstants::DEFAULT_VALUE;
	//myBP->DP = BizConstants::DEFAULT_VALUE;

	captureTime = CrxConfigFacade::Instance()->GetCaptureTime(); // DEFAULT_CAPTURE_TIME
	sampleRate = 1024 / DalConstants::DATA_SAMPLING_INTERVAL; //DEFAULT_SAMPLE_RATE;  
	
	simulation = false;

	reasonForChange = "";
	auditChange = AUDIT_ORIGINAL;
	auditDateTime = DateTime::Now;	
}

/**
Validate

DESCRIPTION

	Validate the measurement before calculation including:
		height,
		weight,
		BP,
		measurementDateTime,
		dataRevision,
		sampleRate,
		captureTime.

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
	/*if (!myHeight->Validate())
	{
		return false;
	} 
	else if (!myWeight->Validate())
	{
		return false;
	} 
	else if (!myBP->Validate())
	{
		return false;
	}*/ 
	
	// GroupStudyID can be blank, so no need to validate
	// Validate Customer System ID
	if (String::IsNullOrEmpty(systemId))
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
xyz

DESCRIPTION

	xyz

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

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
xyz

DESCRIPTION

	xyz

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

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
xyz

DESCRIPTION

	xyz

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

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
xyz

DESCRIPTION

	Validate

INPUT

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
		bool isValid;
		if (Reading >= MEA_BP_MIN && Reading <= MEA_BP_MAX)
		{
			isValid = true;
		} else
		{
			isValid = false;
		}
		return isValid;
	}
	/**
xyz

DESCRIPTION

	Validate

INPUT

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
xyz

DESCRIPTION

	Validate

INPUT

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
xyz

DESCRIPTION

	Validate

INPUT

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
xyz

DESCRIPTION

	Validate

INPUT

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
		bool isValid;
		if (!SP->Validate())
		{
			isValid = false;
		} else if (!DP->Validate())
		{
			isValid = false;
		} else if (SP->Reading < (DP->Reading + MEA_SP2DP_DIFF_MIN))
		{
			//TBD: Inform user "Diff bet SP and DP should be ... mmHg"
			isValid = false;
		} else 
		{
			isValid = true;
		}
		return isValid;
	}
	/**
xyz

DESCRIPTION

	Validate

INPUT

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
		bool isValid;
		if (!MP->Validate())
		{
			isValid = false;
		} else if (!DP->Validate())
		{
			isValid = false;
		} else if (MP->Reading < (DP->Reading + MEA_MP2DP_DIFF_MIN))
		{
			//TBD: Inform user "Diff bet MP and DP should be ... mmHg"
			isValid = false;
		} else 
		{
			isValid = true;
		}
		return isValid;
	}
	/**
xyz

DESCRIPTION

	Validate

INPUT

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
		bool isValid;
		if (!SP->Validate())
		{
			isValid = false;
		} else if (!MP->Validate())
		{
			isValid = false;
		} else if (SP->Reading < (MP->Reading + MEA_SP2MP_DIFF_MIN))
		{
			//TBD: Inform user "Diff bet SP and MP should be ... mmHg"
			isValid = false;
		} else 
		{
			isValid = true;
		}
		return isValid;
	}