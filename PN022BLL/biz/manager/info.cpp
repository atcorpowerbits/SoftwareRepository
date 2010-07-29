/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	info.h
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Information Class
*/

#include "stdafx.h"
#include "info.h"

namespace Biz {
	BizInfo^ BizInfo::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew BizInfo;
		}
		return _instance;
	}
	void BizInfo::GetCompanyName(String^ %coName, int len)
	{
		if (company->Length > len) 
		{
			coName = company->Substring(0,len);
		} else 
		{
			coName = company;
		}
	}

	void BizInfo::GetVersion(String^ %appVersion, int len)
	{
		if (company->Length > len) 
		{
			appVersion = version->Substring(0,len);
		} else 
		{
			appVersion = version;
		}
	}

	BizInfo::BizInfo(void)
	{
		company = STR_BIZ_CO_NAME;
		version = STR_BIZ_VERSION;
	}
}