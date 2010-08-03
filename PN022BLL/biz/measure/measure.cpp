/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Measurement Classes
*/

#include "StdAfx.h"
#include "Measure.h"

namespace Biz {
	BizMeasure::BizMeasure(void)
	{
	}
	bool BizHeightCm::Validate()
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
	bool BizWeightKg::Validate()
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