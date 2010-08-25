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

		return true; 
	}
	bool DalFacade::StopCapture()
	{
		_module->StopCapture();
		return true; 
	}
	String^ DalFacade::GetFWConfig(unsigned int configType)
	{
		switch (configType)
		{
		case DalConstants::CONFIG_MODULE_TYPE:
				return "EM4 (stub)"; 
			case DalConstants::CONFIG_MODULE_CAPABILITY:
				return "xxx (stub)"; 
			case DalConstants::CONFIG_MODULE_SN:
				return "1234567890 (stub)"; 
			case DalConstants::CONFIG_MAIN_FW_VERSION:
				return "0.1 (stub)"; 
			default:
				return "cannot get undefined config"; 
		}
	}
	void DalFacade::SimulateCaptureOneShot() 
	{
		DalTonometerStub::Instance()->tonoDataRaw->Notify(1234); 
		DalCuffStub::Instance()->cuffPulseRaw->Notify(5678); 
	}
	void DalFacade::SimulateCaptureData() 
	{
		_module->Simulate(captureDataType);
	}
	void DalFacade::StopSimulation() 
	{
		_module->StopSimulation();
	}
}