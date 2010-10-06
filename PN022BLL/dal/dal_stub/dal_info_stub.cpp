// This is the main DLL file.

#include "stdafx.h"

#include "dal_info_stub.h"

namespace DataAccess {
	DalModuleInfo^ DalModuleInfo::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalModuleInfo;
		}
		return _instance;
	}
	DalModuleInfo::DalModuleInfo(void)
	{
		moduleType = L"EM4 (stub)";
		moduleSN = L"1234567890 (stub)";
		moduleMainFWVersion = L"0.1 (stub)";
		moduleCapability = 99;
		moduleCalibrationDate = DateTime::Today.Date;
	}
}
