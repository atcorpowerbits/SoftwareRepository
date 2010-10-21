// This is the main DLL file.

#include "stdafx.h"

#include "dal_info_stub.h"

using namespace DAL_NAMESPACE;

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
	moduleConfigID = 99;
	moduleConfigDate = DateTime::Today.Date;
	moduleCalibrationDate = DateTime::Today.Date;
}
