/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	info.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Information
*/

#pragma once
#include <string.h>

using namespace System;

#define STR_BIZ_CO_NAME	L"AtCor Medical (stub)"
#define STR_BIZ_VERSION	L"Version 0.1 (stub)"
#define STR_BIZ_MODULE_TYPE	L"Unknown (stub)"
#define STR_BIZ_MODULE_CAPABILITY	L"Unknown (stub)"
#define STR_BIZ_MODULE_SN	L"Unknown (stub)"
#define STR_BIZ_MODULE_VERSION	L"Unknown (stub)"

namespace Biz {
	public ref class BizInfo {
	public:
		static BizInfo^ BizInfo::Instance();
		void GetCompanyName(String^ %coName, int len);
		void GetVersion(String^ %appVersion, int len);
		void GetModuleType(String^ %moduleVersion, int len);
		void GetModuleCapability(String^ %moduleVersion, int len);
		void GetModuleSN(String^ %moduleVersion, int len);
		void GetModuleVersion(String^ %moduleVersion, int len);
	protected:
		BizInfo(void);
	private:
		property String^ company;
		property String^ appVersion;
		property String^ moduleType;
		property String^ moduleCapability;
		property String^ moduleSN;
		property String^ moduleVersion;
		static BizInfo^ _instance;
	};
}