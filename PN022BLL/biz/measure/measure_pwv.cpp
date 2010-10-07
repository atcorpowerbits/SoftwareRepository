/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer PWV Measurement Class
*/

#include "StdAfx.h"
#include <measure_pwv.h>
#include <biz.h>

using namespace CrossCutting;
using namespace DataAccess;

namespace Biz {
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

		if (distance >= PWV_FEM2CUFF_MIN && distance <= PWV_FEM2CUFF_MAX)
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

		Constructor.
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/	
	BizPWV::BizPWV(void)
	{
		// TBD: need to check the Height & Weight Unit from the config
		// then instantiate the right object, i.e. metric or imperial
		if (CrxConfigFacade::Instance()->isMetricsUnit())
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

		// Instantiate some PWV distance objects
		myCarotidDistance = gcnew BizCarotidDistance;
		myCuffDistance = gcnew BizCuffDistance;
		myPWVDirectDistance = gcnew BizPWVDirectDistance;
		myFemoral2CuffDistance = gcnew BizFemoral2CuffDistance;

		// Tonometer and cuff pulse data from DAL are captured here for PWV measurement.
		myTonometerDataObserver = gcnew BizTonometerDataCapture(
			gcnew BizCircularBuffer(1000 * 
			                        (CrossCutting::CrxConfigFacade::Instance()->PWVCaptureTime + 
									Biz::CAPTURE_EXTRA_FOR_HANDSHAKE) / 
									DalConstants::DATA_SAMPLING_INTERVAL));
		myCuffPulseObserver = gcnew BizCuffPulseCapture(
			gcnew BizCircularBuffer(1000 * 
			                        (CrossCutting::CrxConfigFacade::Instance()->PWVCaptureTime + 
									Biz::CAPTURE_EXTRA_FOR_HANDSHAKE) / 
									DalConstants::DATA_SAMPLING_INTERVAL));

		// Countdown data from DAL are captured here for PWV measurement.
		// Only one last countdown data is needed to be captured.
		myCountdownObserver = gcnew BizCountdownCapture(gcnew BizCircularBuffer(1));

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

		// TBD: check PWV distance method
		if (CrxConfigFacade::Instance()->PWVSubtractingMethod)
		{
			isValid = myCarotidDistance->Validate() && myCuffDistance->Validate();
		} else
		{
			isValid = myPWVDirectDistance->Validate();
		}
		return isValid;
	}
	/**
	Validate

	DESCRIPTION

		Validate the PWV measurement including:
			height
			weight
			BP
			Distance
			Femoral to Cuff Distance
	
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
		bool isValid;

		if (!myHeight->Validate())
		{
			isValid = false;
		} else if (!myWeight->Validate())
		{
			isValid = false;
		} else if (!myBP->Validate())
		{
			isValid = false;
		} else if (!ValidatePWVDistance())
		{
			isValid = false;
		} else if (!myFemoral2CuffDistance->Validate())
		{
			isValid = false;
		} else 
		{
			isValid = true;
		}
		return isValid;
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
		myTonometerDataObserver->Reset();
		myCuffPulseObserver->Reset();
		return DalFacade::Instance()->StartCapture(DalConstants::DATA_TONOMETER_AND_CUFF_PULSE_COMBO);
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
		return DalFacade::Instance()->StopCapture();
	}
	/**
	DispatchCaptureData

	DESCRIPTION

		Dispatch PWV measurement data which may have been observed (captured).
		PWV measurement data inclucde:
		-Tonometer data
		-Cuff pulse data
		-Cuff pressure data
		-Count down timer

	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	void BizPWV::DispatchCaptureData()
	{
		myTonometerDataObserver->Dispatch();
		myCuffPulseObserver->Dispatch();
		myCountdownObserver->Dispatch();
	}
	// Initialise properties
	void BizPWV::Initialise(const int signalSampleRate)
	{
	}

	// Do all mathematics for this measurement
	bool BizPWV::Calculate()
	{
		return true;
	}

	// Prepare PWV class to store signals
	void BizPWV::PrepareToCaptureSignal()
	{
	}
    
	// Validate PWV class properties before Store in database
	bool BizPWV::ValidateBeforeStore()
	{
		return true;
	}

	// Validate PWV class properties before Calculation routine
	bool BizPWV::ValidateBeforeCalculate()
	{
		return true;
	}
    
	// Save arrays if an error occurs while calculating
	bool BizPWV::SaveToFile()
	{
		return true;
	}
    
	// Set default values for calculated variables
	void BizPWV::SetDefaults()
	{
	}

	// Calculate distances
	bool BizPWV::CalculateDistance()
	{
		return true;
	}

	// Calculate PWV, MeanDt, Deviation for this measurement
	bool BizPWV::CalcMainFeatures()
	{
		return true;
	}

	// Calculate time difference between Tonometer and Cuff Onsets
	bool BizPWV::CalcDeltaT(const int sampleRate)
	{
		return true;
	}

	// Calculate Heart rate on the base of ECG Onsets
	bool BizPWV::CalcHeartRate(const int sampleRate)
	{
		return true;
	}

	// Calculate DeltaT average (MeanDt) and its standard deviation
	bool BizPWV::MeanDeviation()
	{
		return true;
	}
}