// This is the main DLL file.

#include "stdafx.h"

#include "dal_stub.h"
#include "dal_facade_stub.h"
//#include "dal_meter_stub.h"
#include "DalEventContainer.h"
#include "DalEventContainerStub.h"
//#include "dal_module_cmd_stub.h"

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
#if 0
DalTonometerDataEvent^ DalFacade::FindTonometerDataEvent() 
{ 
	return DalMeter::Instance()->tonometerDataEvent; 
}
DalCuffPulseEvent^ DalFacade::FindCuffPulseEvent() 
{ 
	return DalMeter::Instance()->cuffPulseEvent; 
}
DalCuffPressureEvent^ DalFacade::FindCuffPressureEvent() 
{ 
	return DalMeter::Instance()->cuffPressureEvent; 
}
DalCountdownTimerEvent^ DalFacade::FindCountdownTimerEvent() 
{ 
	return DalMeter::Instance()->countdownTimerEvent; 
}
DalCuffStatusEvent^ DalFacade::FindCuffStatusEvent() 
{ 
	return DalMeter::Instance()->cuffStatusEvent; 
}
bool DalFacade::StartCapture(unsigned int captureDataType)
{
	this->captureDataType = captureDataType;

	return true; 
}
bool DalFacade::StopCapture()
{
	_module->StopCapture();
	return true; 
}
DalModuleInfo^ DalFacade::FindModuleInfo()
{
	return DalModuleInfo::Instance();
}
String^ DalFacade::GetFWConfig(unsigned int configType)
{
	switch (configType)
	{
	case DalConstants::CONFIG_MODULE_TYPE:
			return L"EM4 (stub)"; 
		case DalConstants::CONFIG_MODULE_CAPABILITY:
			return L"xxx (stub)"; 
		case DalConstants::CONFIG_MODULE_SN:
			return L"1234567890 (stub)"; 
		case DalConstants::CONFIG_MODULE_MAIN_FW_VERSION:
			return L"0.1 (stub)"; 
		case DalConstants::CONFIG_MODULE_CALIBRATION_DATE:
			return L"(stub)"; 
		default:
			return L"cannot get undefined config"; 
	}
}
#endif

void DalFacade::SimulateCaptureOneShot() 
{
#if 0
	DalMeter::Instance()->tonometerDataEvent->Notify(1234); 
	DalMeter::Instance()->cuffPulseEvent->Notify(5678); 
	DalMeter::Instance()->cuffStatusEvent->Notify(DalConstants::CUFF_DEFLATED_STATUS_BITS);
	DalMeter::Instance()->cuffPressureEvent->Notify(70);
#endif
	DalEventContainer::Instance->OnDalTonometerDataEvent(this, gcnew DalTonometerDataEventArgs(1234));
	DalEventContainer::Instance->OnDalCuffPulseEvent(this, gcnew DalCuffPulseEventArgs(5678));
	DalEventContainerStub::Instance->OnDalCountdownTimerEvent(this, gcnew DalCountdownTimerEventArgs(9000));
	DalEventContainerStub::Instance->OnDalCuffStatusEvent(this, gcnew DalCuffStatusEventArgs(0x0100));
	DalEventContainerStub::Instance->OnDalModuleErrorAlarmEvent(DalEventContainerStub::Instance, 
		gcnew DalModuleErrorAlarmEventArgs(0x0008, 0x0001));
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
	int newPressure;
	int newStatus;
	int newCountdown;
	int newSource;

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
#if 0
	DalMeter::Instance()->tonometerDataEvent->Notify(tonometerData);
	DalMeter::Instance()->cuffPulseEvent->Notify(cuffPulse);
	DalMeter::Instance()->countdownTimerEvent->Notify(DalModule::Instance()->countDown);
	DalMeter::Instance()->cuffStatusEvent->Notify(DalModule::Instance()->status & 0x2F);
	DalMeter::Instance()->cuffPressureEvent->Notify(DalModule::Instance()->cuffPressure);
#endif
	DalEventContainer::Instance->OnDalTonometerDataEvent(DalEventContainer::Instance, gcnew DalTonometerDataEventArgs(tonometerData));
	DalEventContainer::Instance->OnDalCuffPulseEvent(DalEventContainer::Instance, gcnew DalCuffPulseEventArgs(cuffPulse));
	DalEventContainerStub::Instance->OnDalCountdownTimerEvent(DalEventContainerStub::Instance, gcnew DalCountdownTimerEventArgs(DalFacade::Instance()->countDown));
	DalEventContainerStub::Instance->OnDalCuffStatusEvent(DalEventContainerStub::Instance, 
		gcnew DalCuffStatusEventArgs(DalFacade::Instance()->status & 0x2F00));
//	DalEventContainer::Instance->OnDalCuffPressureEvent(DalEventContainer::Instance, gcnew DalCuffPressureEventArgs(newPressure));
	DalEventContainerStub::Instance->OnDalModuleErrorAlarmEvent(DalEventContainerStub::Instance, 
		gcnew DalModuleErrorAlarmEventArgs((DalFacade::Instance()->status & 0x0028), DalFacade::Instance()->source));

	// Countdown the timer by the amount of simulation interval
	DalFacade::Instance()->countDown -= DalConstants::SimulationTimerInterval;
}

void DalFacade::StopCaptureSimulation() 
{
	captureTimer->Enabled = false; // stop simulation
	dataFile->CloseFile();
	timerFile->CloseFile();
}
