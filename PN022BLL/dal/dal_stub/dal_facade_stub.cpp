// This is the main DLL file.

#include "stdafx.h"

#include "dal.h"
#include "dal_facade_stub.h"
#include "dal_meter_stub.h"
#include "dal_module_cmd_stub.h"

using namespace DAL_NAMESPACE;

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
void DalFacade::SimulateCaptureOneShot() 
{
	DalMeter::Instance()->tonometerDataEvent->Notify(1234); 
	DalMeter::Instance()->cuffPulseEvent->Notify(5678); 
	DalMeter::Instance()->cuffStatusEvent->Notify(DalConstants::CUFF_DEFLATED_STATUS_BITS);
	DalMeter::Instance()->cuffPressureEvent->Notify(70);
}
void DalFacade::SimulateCaptureData() 
{
	_module->SimulateCaptureData(captureDataType);
}
void DalFacade::StopCaptureSimulation() 
{
	_module->StopCaptureSimulation();
}
