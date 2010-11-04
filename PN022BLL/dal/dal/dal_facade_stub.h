// dal_stub.h

#pragma once

//#include "dal_info_stub.h"
//#include "dal_namespace.h"
#include "DalSimulationFile.h"

using namespace System;
using namespace System::Timers;

namespace AtCor{ 
namespace Scor { 
namespace DataAccess{

// Some forward declarations
#if 0
ref class DalMeter; 
ref class DalModule; 
ref class DalTonometerDataEvent;
ref class DalCuffPulseEvent;
ref class DalCuffPressureEvent;
ref class DalCountdownTimerEvent;
ref class DalCuffStatusEvent;
#endif

public ref class DalFacade
{
public:
	static System::Timers::Timer^ captureTimer;

	static DalFacade^ DalFacade::Instance();
//	bool StartCapture(unsigned int dataType);
//	bool StopCapture();
//	String^ GetFWConfig(unsigned int configType);
//	DalModuleInfo^ FindModuleInfo();
	void SimulateCaptureData();
	void StopCaptureSimulation();
	void SimulateCaptureOneShot();

//	DalTonometerDataEvent^ FindTonometerDataEvent();
//	DalCuffPulseEvent^ FindCuffPulseEvent();
//	DalCuffPressureEvent^ FindCuffPressureEvent();
//	DalCountdownTimerEvent^ FindCountdownTimerEvent();
//	DalCuffStatusEvent^ FindCuffStatusEvent();

protected:
	DalFacade(void);
private:
	static DalSimulationFile^ dataFile;
	static DalSimulationFile^ timerFile;
	static short countDown;
	static short cuffPressure;
	static short status;
	static short source;

	static DalFacade^ _instance;
//	DalModuleStub^ _module;
//	unsigned int captureDataType;

	// Specify what you want to happen when the Elapsed event is 
	// raised.
	static void OnCaptureTimedEvent( Object^ source, ElapsedEventArgs^ e );
};

}}}

