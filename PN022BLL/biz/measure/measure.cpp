/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Measurement Classes
*/

#include "StdAfx.h"
#include "Measure.h"

namespace Biz {
	/**
	Initialise

	DESCRIPTION

		Initialise for ???
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	void BizMeasure::Initialise()
	{
	}
	/**
	ValidateBeforeStore

	DESCRIPTION

		Validate before store ???
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	bool BizMeasure::ValidateBeforeStore()
	{
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

		xyz

	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
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

		xyz

	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
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

		xyz

	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
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

		xyz

	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
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

		xyz

	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
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
		} else if (!((SP->Reading - DP->Reading) < MEA_SP2DP_DIFF_MIN))
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

		xyz

	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
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
		} else if (!((MP->Reading - DP->Reading) < MEA_MP2DP_DIFF_MIN))
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

		xyz

	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
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
		} else if (!((SP->Reading - MP->Reading) < MEA_SP2MP_DIFF_MIN))
		{
			//TBD: Inform user "Diff bet SP and MP should be ... mmHg"
			isValid = false;
		} else 
		{
			isValid = true;
		}
		return isValid;
	}
}