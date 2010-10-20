/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_config_stub.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Cross Cutting Configuration Facade
*/

#pragma once

using namespace System;

namespace CrossCutting {
	// Cross-Cutting Configuration Facade Singleton Class
	public ref class CrxConfigFacade
	{
	public:
		static const short MEASUREMENT_UNIT_METRICS = 0;
		static const short MEASUREMENT_UNIT_IMPERIAL = 1;
	
		static CrxConfigFacade^ CrxConfigFacade::Instance();
		bool isMetricsUnit();
		bool isSubtractingMethod();
		unsigned short GetCaptureTime();
		/**<0 : if SP and DP is selected 1:SP and MP is selected 2:MP and DP is selected */
		unsigned short GetBPCombination();

		// For unit testing PWV
		void SetMeasurementUnit(unsigned short);
		void SetDistanceMethod(bool);
		void SetCaptureTime(unsigned short);
		void SetBPCombination(unsigned short);

	protected:
		CrxConfigFacade(void);
		property unsigned short PWVMeasureUnit;
		property bool PWVSubtractingMethod;
		property unsigned short PWVCaptureTime;
		property unsigned short PWVBPCombination;
	private:
		static CrxConfigFacade^ _instance;
	};
}
