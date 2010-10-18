// dal_stub.h

#pragma once

#include "dal_info_stub.h"

using namespace System;

namespace DataAccess {
	// Some forward declarations
	ref class DalMeter; 
	ref class DalModule; 
	ref class DalTonometerDataEvent;
	ref class DalCuffPulseEvent;
	ref class DalCuffPressureEvent;
	ref class DalCountdownTimerEvent;
	ref class DalCuffStatusEvent;

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
//		void SimulateDeflationTimer();
//		void StopDeflationTimerSimulation();

		DalTonometerDataEvent^ FindTonometerDataEvent();
		DalCuffPulseEvent^ FindCuffPulseEvent();
		DalCuffPressureEvent^ FindCuffPressureEvent();
		DalCountdownTimerEvent^ FindCountdownTimerEvent();
		DalCuffStatusEvent^ FindCuffStatusEvent();

	protected:
		DalFacade(void);
	private:
		static DalFacade^ _instance;
		DalModule^ _module;
		unsigned int captureDataType;
	};
}
