/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	info.h
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Information Class
*/

#include "stdafx.h"
#include "info.h"

using namespace DataAccess;

namespace Biz {
	/**
	Instance

	DESCRIPTION

		Get the BizInfo singleton instance.
	
	INPUT
	
		none.
	
	OUTPUT
	
		None.
	
	RETURN
	
		BizInfo^ - Handle to BizInfo object
	
	*/
	BizInfo^ BizInfo::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew BizInfo;
		}
		return _instance;
	}
	/**
	GetCompanyName

	DESCRIPTION

		Get the company name.
	
	INPUT
	
		len - Company name string buffer limit.
	
	OUTPUT
	
		coName - Company name string.
	
	RETURN
	
		None.
	
	*/
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

	/**
	GetVersion

	DESCRIPTION

		Get the application version.
	
	INPUT
	
		len - Application version string buffer limit.
	
	OUTPUT
	
		appVersion - Application version string.
	
	RETURN
	
		None.
	
	*/
	void BizInfo::GetVersion(String^ %appVersion, int len)
	{
		if (this->appVersion->Length > len) 
		{
			appVersion = this->appVersion->Substring(0,len);
		} else 
		{
			appVersion = this->appVersion;
		}
	}

	/**
	GetModuleType

	DESCRIPTION

		Get the electronic module type.
	
	INPUT
	
		len - Module type string buffer limit.
	
	OUTPUT
	
		moduleType - Module type string.
	
	RETURN
	
		None.
	
	*/
	void BizInfo::GetModuleType(String^ %moduleType, int len)
	{
		this->moduleType = DalFacade::Instance()->GetFWConfig(DalConstants::CONFIG_MODULE_TYPE);

		if (this->moduleType->Length > len) 
		{
			moduleType = this->moduleType->Substring(0,len);
		} else 
		{
			moduleType = this->moduleType;
		}
	}

	/**
	GetModuleType

	DESCRIPTION

		Get the electronic module type.
	
	INPUT
	
		len - Module type string buffer limit.
	
	OUTPUT
	
		moduleType - Module type string.
	
	RETURN
	
		None.
	
	*/
	void BizInfo::GetModuleCapability(String^ %moduleCapability, int len)
	{
		this->moduleCapability = DalFacade::Instance()->GetFWConfig(DalConstants::CONFIG_MODULE_CAPABILITY);

		if (this->moduleCapability->Length > len) 
		{
			moduleCapability = this->moduleCapability->Substring(0,len);
		} else 
		{
			moduleCapability = this->moduleCapability;
		}
	}

	void BizInfo::GetModuleSN(String^ %moduleSN, int len)
	{
		this->moduleSN = DalFacade::Instance()->GetFWConfig(DalConstants::CONFIG_MODULE_SN);

		if (this->moduleSN->Length > len) 
		{
			moduleSN = this->moduleSN->Substring(0,len);
		} else 
		{
			moduleSN = this->moduleSN;
		}
	}

	void BizInfo::GetModuleVersion(String^ %moduleVersion, int len)
	{
		this->moduleVersion = DalFacade::Instance()->GetFWConfig(DalConstants::CONFIG_MAIN_FW_VERSION);

		if (this->moduleVersion->Length > len) 
		{
			moduleVersion = this->moduleVersion->Substring(0,len);
		} else 
		{
			moduleVersion = this->moduleVersion;
		}
	}

	BizInfo::BizInfo(void)
	{
		company = STR_BIZ_CO_NAME;
		appVersion = STR_BIZ_VERSION;
		moduleType = STR_BIZ_MODULE_VERSION;
		moduleCapability = STR_BIZ_MODULE_CAPABILITY;
		moduleSN = STR_BIZ_MODULE_SN;
		moduleVersion = STR_BIZ_MODULE_VERSION;
	}
}