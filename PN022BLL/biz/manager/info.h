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

namespace Biz {
	public ref class BizInfo {
	public:
		static BizInfo^ BizInfo::Instance();
		void GetCompanyName(String^ %coName, int len);
		void GetVersion(String^ %appVersion, int len);
	protected:
		BizInfo(void);
	private:
		property String^ company;
		property String^ version;
		static BizInfo^ _instance;
	};
}