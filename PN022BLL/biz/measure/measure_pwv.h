/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure_pwv.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer PWV Measurement
*/

#pragma once

//#include <string>
#include "measure.h"

using namespace System;

namespace Biz {

	const unsigned short PWV_DISTANCE_MIN = 10;
	const unsigned short PWV_DISTANCE_MAX = 2200;
	const unsigned short PWV_FEM2CUFF_MIN = 10;
	const unsigned short PWV_FEM2CUFF_MAX = 700;

	public ref class BizDistance abstract
	{
	public:
		property unsigned short Distance;
	};
	public ref class BizPWV : BizMeasure
	{
	public:
		property unsigned short CarotidDistance;
		property unsigned short CuffDistance;
		property unsigned short Femoral2CuffDistance;
		property unsigned short PWVDistance;
		bool ValidatePWVDistance();
		bool ValidateFemoral2CuffDistance();
		virtual bool Validate() override;
	public:
		BizPWV(void);
	};
}