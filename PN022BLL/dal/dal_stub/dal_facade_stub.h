// dal_stub.h

#pragma once

#include "dal_info_stub.h"
#include "dal_namespace.h"

using namespace System;

START_DAL_NAMESPACE

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

END_DAL_NAMESPACE
