// This is the main DLL file.

#include "stdafx.h"

#include "dal.h"
#include "dal_facade_stub.h"
#include "dal_meter_stub.h"
#include "dal_module_cmd_stub.h"

namespace DataAccess {
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
//?		meter = (DalTonometerStub^)gcnew DalTonometerStub;
	}
	DalTonoDataEvent^ DalFacade::FindTonoData() 
	{ 
		return DalTonometerStub::Instance()->tonoDataRaw; 
	}
	DalCuffPulseEvent^ DalFacade::FindCuffPulse() 
	{ 
		return DalCuffStub::Instance()->cuffPulseRaw; 
	}
	bool DalFacade::StartCapture(unsigned int captureDataType)
	{
		this->captureDataType = captureDataType;

		return true; //stub
	}
	bool DalFacade::StopCapture()
	{
		_module->StopCapture();
		return true; //stub
	}
	String^ DalFacade::GetFWConfig(unsigned int configType)
	{
		switch (configType)
		{
		case DalConstants::CONFIG_MODULE_TYPE:
				return "EM4 (stub)"; //stub
			case DalConstants::CONFIG_MODULE_CAPABILITY:
				return "xxx (stub)"; //stub
			case DalConstants::CONFIG_MODULE_SN:
				return "1234567890 (stub)"; //stub
			case DalConstants::CONFIG_MAIN_FW_VERSION:
				return "0.1 (stub)"; //stub
			default:
				return "cannot get undefined config"; //stub
		}
	}
	void DalFacade::DispatchCaptureOneShot() // stub?
	{
		DalTonometerStub::Instance()->tonoDataRaw->Notify(1234); // stub
	}
	void DalFacade::DispatchCaptureData() // stub?
	{
//?		DalTonometerStub::Instance()->tonoDataRaw->Notify(1234); // stub
//?		_meter->mainFWVersion->Notify("0.1");; //stub
//?		DalTonometerStub::Instance()->Simulate();
		_module->Simulate(captureDataType);
	}
}