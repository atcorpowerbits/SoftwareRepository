// This is the main DLL file.

#include "stdafx.h"

#include "dal_stub.h"
#include "dal_facade_stub.h"
#include "DalEventContainer.h"
#include "DalEventContainerStub.h"

using namespace AtCor::Scor::DataAccess;

DalFacade^ DalFacade::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew DalFacade;
	}
	return _instance;
}
DalFacade::DalFacade(void)
{
}

void DalFacade::SimulateCaptureOneShot() 
{
	DalEventContainer::Instance->OnDalTonometerDataEvent(this, gcnew DalTonometerDataEventArgs(1234));
	DalEventContainer::Instance->OnDalCuffPulseEvent(this, gcnew DalCuffPulseEventArgs(5678));
	DalEventContainerStub::Instance->OnDalCountdownTimerEvent(this, gcnew DalCountdownTimerEventArgs(9000));
	DalEventContainerStub::Instance->OnDalCuffStatusEvent(this, gcnew DalCuffStatusEventArgs(0x0100));

	status = ErrorStatus; //AlarmStatus;   // simulate alarm or error
	source = DualSensor; //OverPressure; // source to be read interpretted when GetErrorAlarmSource is called
	DalEventContainerStub::Instance->OnDalModuleErrorAlarmEvent(
		DalEventContainerStub::Instance, 
		gcnew DalModuleErrorAlarmEventArgs(status));
}
void DalFacade::SimulateCaptureData() 
{
	int captureDataType = TonometerAndCuffPulseCombination;

	// Normally, the timer is declared at the class level,
	// so that it stays in scope as long as it is needed.
	// If the timer is declared in a long-running method,  
	// KeepAlive must be used to prevent the JIT compiler 
	// from allowing aggressive garbage collection to occur 
	// before the method ends. (See end of method.)
	//System::Timers::Timer^ captureTimer;

	// Create a new Timer with Interval set in milliseconds.
	// e.g. ~4 ms for 256 samples/sec
	captureTimer = gcnew Timer(DalConstants::SimulationTimerInterval);

	// Hook up the Elapsed event for the timer.
	switch (captureDataType) // TBD: get DalModule::Instance->_captureDataType
	{
	case TonometerAndCuffPulseCombination:
		captureTimer->Elapsed += gcnew ElapsedEventHandler( &DalFacade::OnCaptureTimedEvent );
		dataFile = gcnew DalSimulationFile("./simulation/pwv/Default.dat");
		timerFile = gcnew DalSimulationFile("./cuff_timer.dat");
		break;
	default:
		return; // nothing to simulate
	}
//	dataFile->OpenFile();
//	timerFile->OpenFile();
	countDown = 0;
	captureTimer->Enabled = true;

	// If the timer is declared in a long-running method, use
	// KeepAlive to prevent garbage collection from occurring
	// before the method ends.
	//GC::KeepAlive(captureTimer);
}
void DalFacade::OnCaptureTimedEvent( Object^ source, ElapsedEventArgs^ e )
{
	int tonometerData;
	int cuffPulse;
	unsigned int newPressure;
	unsigned int newStatus;
	unsigned int newCountdown;
	unsigned long newSource;

	// Read new timer data if it's counted down to zero
	if (DalFacade::Instance()->countDown <= 0) 
	{
		DalFacade::Instance()->timerFile->GetNextValues(
			&newCountdown,
			&newPressure,
			&newStatus, 
			&newSource);
		DalFacade::Instance()->countDown = newCountdown;
		DalFacade::Instance()->cuffPressure = newPressure;
		DalFacade::Instance()->status = newStatus;
		DalFacade::Instance()->source = newSource;
	}
	// Read PWV simulation data
	DalFacade::Instance()->dataFile->GetNextValues(
		&tonometerData, 
		&cuffPulse);

	// Notify observers to generate corresponding events
	DalEventContainer::Instance->OnDalTonometerDataEvent(DalEventContainer::Instance, gcnew DalTonometerDataEventArgs(tonometerData));
	DalEventContainer::Instance->OnDalCuffPulseEvent(DalEventContainer::Instance, gcnew DalCuffPulseEventArgs(cuffPulse));
	DalEventContainerStub::Instance->OnDalCountdownTimerEvent(DalEventContainerStub::Instance, gcnew DalCountdownTimerEventArgs(DalFacade::Instance()->countDown));
	DalEventContainerStub::Instance->OnDalCuffStatusEvent(DalEventContainerStub::Instance, 
		gcnew DalCuffStatusEventArgs(DalFacade::Instance()->status & 0x2F00));
//	DalEventContainer::Instance->OnDalCuffPressureEvent(DalEventContainer::Instance, gcnew DalCuffPressureEventArgs(newPressure));
	DalEventContainerStub::Instance->OnDalModuleErrorAlarmEvent(
		DalEventContainerStub::Instance, 
		gcnew DalModuleErrorAlarmEventArgs(DalFacade::Instance()->status & 0x0028));
	// Countdown the timer by the amount of simulation interval
	DalFacade::Instance()->countDown -= DalConstants::SimulationTimerInterval;
}

void DalFacade::StopCaptureSimulation() 
{
	captureTimer->Enabled = false; // stop simulation
	dataFile->CloseFile();
	timerFile->CloseFile();
}

// Return the error & alarm source 
String^ DalFacade::GetErrorAlarmSource()
{
	String^ sourceText;

	switch (status & 0x0028)
	{
	case DataAccess::NoErrorAlarm:
		sourceText = "Module active"; // TBD: get the string from crx string resource
		break;
	case DataAccess::ErrorStatus:
		sourceText = MapErrorSourceToString(source & 0x0000FFFF);
		break;
	case DataAccess::AlarmStatus:
		sourceText = MapAlarmSourceToString((source >> 16) & 0x0000FFFF);
		break;
	default:
		sourceText = "Unknown module status " + status.ToString(); // TBD: get the string from crx string resource
		break;
	}
	return sourceText;
}

String^ DalFacade::MapErrorSourceToString(unsigned short errorSource)
{
	String^ sourceText;

	// TBD: map to real errors using string resource
	switch (errorSource)
	{
	case DualSensor:
		sourceText = "Dual sensors error"; // TBD: get the string from crx string resource
		break;
	case CuffLeak:
		sourceText = "Cuff leak error"; // TBD: get the string from crx string resource
		break;
	default:
		sourceText = "Unknown error" + errorSource.ToString(); // TBD: get the string from crx string resource
		break;
	}
	return sourceText;
}

String^ DalFacade::MapAlarmSourceToString(unsigned short alarmSource)
{
	String^ sourceText;

	// TBD: map to real alarms using string resource
	switch (alarmSource)
	{
	case OverPressure:
		sourceText = "Over pressure alarm"; // TBD: get the string from crx string resource
		break;
	case InflatedOverTime:
		sourceText = "Inflated over time alarm"; // TBD: get the string from crx string resource
		break;
	default:
		sourceText = "Unknown alarm " + alarmSource.ToString(); // TBD: get the string from crx string resource
		break;
	}
	return sourceText;
}

