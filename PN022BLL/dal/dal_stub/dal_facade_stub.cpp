// This is the main DLL file.

#include "stdafx.h"

#include "dal_facade_stub.h"
#include "dal_meter_cmd_stub.h"

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
		meter = gcnew DalMeter;
	}
	DalTonoData^ DalFacade::FindTonoData() 
	{ 
		return meter->tonoDataRaw; 
	}
	bool DalFacade::StartPWV(void)
	{
		return true; //stub
	}
	void DalFacade::DispatchCaptureData()
	{
		meter->tonoDataRaw->Notify(1234);
	}
}