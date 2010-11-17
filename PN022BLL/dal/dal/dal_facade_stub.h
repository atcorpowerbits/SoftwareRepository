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

public ref class DalFacade
{
public:
	static System::Timers::Timer^ captureTimer;

	static DalFacade^ DalFacade::Instance();
	void SimulateCaptureData();
	void StopCaptureSimulation();
	void SimulateCaptureOneShot();
	String^ DalFacade::GetErrorAlarmSource();
	String^ MapErrorSourceToString(unsigned short errorSource);
	String^ MapAlarmSourceToString(unsigned short alarmSource);
	// needs status & source as publicfor unit testing BizElectronicModule
	static unsigned short status;
	static unsigned long source; // need 4 butes: alarm (2) & error (2)
protected:
	DalFacade(void);
private:
	static DalSimulationFile^ dataFile;
	static DalSimulationFile^ timerFile;
	static short countDown;
	static short cuffPressure;

	static DalFacade^ _instance;

	// Specify what you want to happen when the Elapsed event is 
	// raised.
	static void OnCaptureTimedEvent( Object^ source, ElapsedEventArgs^ e );
};

}}}

