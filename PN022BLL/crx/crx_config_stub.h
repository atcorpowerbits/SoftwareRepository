/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_config_stub.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Cross Cutting Configuration Facade
*/

#pragma once

using namespace System;

namespace CrossCutting {
	typedef enum {
		MEASUREMENT_UNIT_METRICS = 0,
		MEASUREMENT_UNIT_IMPERIAL = 1,
	} measurement_unit;
	// Cross-Cutting Configuration Facade Singleton Class
	public ref class CrxConfigFacade
	{
	public:
		static CrxConfigFacade^ CrxConfigFacade::Instance();
		property bool PWVSubtractingMethod;
		bool isMetricsUnit();
	protected:
		CrxConfigFacade(void);
	private:
		static CrxConfigFacade^ _instance;
		property measurement_unit MeasureUnit;
	};
}
