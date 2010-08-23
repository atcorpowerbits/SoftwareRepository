/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer PWV Measurement Class
*/

#include "StdAfx.h"
#include "measure_pwv.h"

using namespace CrossCutting;
using namespace DataAccess;

namespace Biz {
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

		// TBD: remove after proof of concept
		// Find the tonometer data in DAL to observe
		myTonoDataObserver = gcnew TonoDataObserverStub(DalFacade::Instance()->FindTonoData());

	}
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
	bool BizPWV::ValidateFemoral2CuffDistance()
	{
		bool isValid;

		if (Femoral2CuffDistance >= PWV_FEM2CUFF_MIN && Femoral2CuffDistance <= PWV_FEM2CUFF_MAX)
		{
			isValid = true;
		} else
		{
			//TBD: Inform user "Femoral to Cuff distance not within the valid range between ... cm and ... cm"
			isValid = false;
		}
		return isValid;
	}
	/**
	ValidatePWVDistance

	DESCRIPTION

		Validate PWV Distance with respect to the Distance Method used.

		For subtracting distance method, validate:

			Carotid Distance

			Cuff Distance

		For direct distance method, validate:

			PWV Distance
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		true  - PWV Distance is valid.
	
		false - PWV Distance is not valid.
	
	*/
	bool BizPWV::ValidatePWVDistance()
	{
		bool isValid = false;

		// TBD: check PWV distance method
		if (CrxConfigFacade::Instance()->PWVSubtractingMethod)
		{
			if (!(CarotidDistance >= PWV_DISTANCE_MIN && CarotidDistance <= PWV_DISTANCE_MAX))
			{
				//TBD: Inform user "Carotid distance is not within the valid range between ... cm and ... cm"
				isValid = false;
			} else if (!(CuffDistance >= PWV_DISTANCE_MIN && CuffDistance <= PWV_DISTANCE_MAX))
			{
				//TBD: Inform user "Cuff distance is not within the valid range between ... cm and ... cm"
				isValid = false;

			} else
			{
				isValid = true;
			}
		} else if (!(PWVDistance >= PWV_DISTANCE_MIN && PWVDistance <= PWV_DISTANCE_MAX))
		{
				//TBD: Inform user "PWV distance is not within the valid range between ... cm and ... cm"
				isValid = false;
		} else
		{
				isValid = true;
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
		} else if (!ValidateFemoral2CuffDistance())
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
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		true  - PWV capture started successful.
	
		false - PWV capture failed to start.
	
	*/		
	bool BizPWV::StartCapture()
	{
		return DalFacade::Instance()->StartCapture(DalConstants::DATA_TONOMETER_AND_CUFF_PULSE_COMBO);
	}
	void BizPWV::DisplayCaptureData()
	{
		myTonoDataObserver->Display();
	}
}