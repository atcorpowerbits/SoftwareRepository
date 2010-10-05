// dal_stub.h

#pragma once

#include "dal_info_stub.h"

using namespace System;

namespace DataAccess {
	// Some forward declarations
	ref class DalMeter; 
	ref class DalModule; 
	ref class DalTonoDataEvent;
	ref class DalCuffPulseEvent;
	ref class DalCountdownEvent;

	public ref class DalFacade
	{
	public:
		static DalFacade^ DalFacade::Instance();
		bool StartCapture(unsigned int dataType);
		bool StopCapture();
		String^ GetFWConfig(unsigned int configType);
		DalModuleInfo^ FindModuleInfo();
		void SimulateCaptureData();
		void StopCaptureSimulation();
		void SimulateCaptureOneShot();
		void SimulateDeflationTimer();
		void StopDeflationTimerSimulation();

		DalTonoDataEvent^ FindTonoDataEvent();
		DalCuffPulseEvent^ FindCuffPulseEvent();
		DalCountdownEvent^ FindCountdownEvent();

	protected:
		DalFacade(void);
	private:
		static DalFacade^ _instance;
		DalModule^ _module;
		unsigned int captureDataType;
	};
}
