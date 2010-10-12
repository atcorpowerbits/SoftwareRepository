// dal_module_info_stub.h

#pragma once

using namespace System;

namespace DataAccess {
	public ref class DalModuleInfo
	{
	public:
		static DalModuleInfo^ DalModuleInfo::Instance();
		property String^ moduleType;
		property String^ moduleSN;
		property String^ moduleMainFWVersion;
		property unsigned short moduleConfigID;
		property DateTime moduleConfigDate;
		property DateTime moduleCalibrationDate;
	protected:
		DalModuleInfo(void);
	private:
		static DalModuleInfo^ _instance;
	};
}