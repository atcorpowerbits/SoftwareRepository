/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	facade.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Facade
*/

#pragma once
#include <string.h>
#include "..\manager\info.h"
#include "..\measure\measure_pwv.h" // temp for UT

namespace Biz {
	// A singleton to interface Business Logic Layer
	public ref class BizFacade {
	public:
		static BizFacade^ BizFacade::Instance();
		BizInfo^ FindBizInfo();
		bool StartCapture();
		bool StopCapture();
		void SimulateCaptureData();
		void SimulateCaptureOneShot();
		void DisplayCaptureData();
		bool CalculateReport();
		BizTonoDataEvent^ FindTonoData();

	protected:
		BizFacade(void);

	private:
		static BizFacade^ _instance;
	};
}