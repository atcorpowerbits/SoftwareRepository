/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	info.h
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Information Class
*/

#include "stdafx.h"
#include "info.h"

using namespace System::Globalization;
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
	GetCopyright

	DESCRIPTION

		Get the application copyright.
	
	INPUT
	
		len - Application copyright string buffer limit.
	
	OUTPUT
	
		copyRight - Application copyright string.
	
	RETURN
	
		None.
	
	*/
	void BizInfo::GetCopyright(String^ %copyRight, int len)
	{
		if (this->copyRight->Length > len) 
		{
			copyRight = this->copyRight->Substring(0,len);
		} else 
		{
			copyRight = this->copyRight;
		}
	}

	/**
	GetModuleType

	DESCRIPTION

		Get the electronic module type.
	
	INPUT
	
		len - Module type string buffer limit.
	
	OUTPUT
	
		info - Module type string.
	
	RETURN
	
		None.
	
	*/
	void BizInfo::GetModuleType(String^ %info, int len)
	{
		moduleType = DalFacade::Instance()->FindModuleInfo()->moduleType;

		if (moduleType->Length > len) 
		{
			info = moduleType->Substring(0,len);
		} else 
		{
			info = moduleType;
		}
	}

	/**
	GetModuleCapability

	DESCRIPTION

		Get the electronic module capability.
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		Electronic module capability integer value.
	
	*/
	unsigned short BizInfo::GetModuleCapability()
	{
		moduleCapability = DalFacade::Instance()->FindModuleInfo()->moduleCapability;
		return moduleCapability;
	}

	/**
	GetModuleSN

	DESCRIPTION

		Get the electronic module serial number.
	
	INPUT
	
		len - Module serial number string buffer limit.
	
	OUTPUT
	
		info - Module serial number string.
	
	RETURN
	
		None.
	
	*/
	void BizInfo::GetModuleSN(String^ %info, int len)
	{
		moduleSN = DalFacade::Instance()->FindModuleInfo()->moduleSN;

		if (moduleSN->Length > len) 
		{
			info = moduleSN->Substring(0,len);
		} else 
		{
			info = moduleSN;
		}
	}

	/**
	GetModuleVersion

	DESCRIPTION

		Get the electronic module version.
	
	INPUT
	
		len - Module version string buffer limit.
	
	OUTPUT
	
		info - Module version string.
	
	RETURN
	
		None.
	
	*/
	void BizInfo::GetModuleVersion(String^ %info, int len)
	{
		moduleVersion = DalFacade::Instance()->FindModuleInfo()->moduleMainFWVersion;

		if (moduleVersion->Length > len) 
		{
			info = moduleVersion->Substring(0,len);
		} else 
		{
			info = moduleVersion;
		}
	}
	/**
	GetModuleCalibrationDate

	DESCRIPTION

		Get the electronic module calibration date.
	
	INPUT
	
		len - Module calibration date string buffer limit.
	
	OUTPUT
	
		info - Module calibration date.
	
	RETURN
	
		None.
	
	*/
	void BizInfo::GetModuleCalibrationDate(String^ %info, int len)
	{
		// Use CultureInfo as IFormatProvider interface to format date to string
		// to meet a FxCop rule.
		CultureInfo^ culture = gcnew CultureInfo(CultureInfo::CurrentUICulture->ToString());

		moduleCalibrationDate = DalFacade::Instance()->FindModuleInfo()->moduleCalibrationDate;

		if (moduleCalibrationDate->ToString(culture)->Length > len) 
		{
			info = moduleCalibrationDate->ToString(culture)->Substring(0,len);
		} else 
		{
			info = moduleCalibrationDate->ToString(culture);
		}
	}
	/**
	BizInfo

	DESCRIPTION

		Contruct and set information regarding Business Layer and Electronic Module.
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	BizInfo::BizInfo(void)
	{
		company = STR_BIZ_CO_NAME;
		appVersion = STR_BIZ_VERSION;
		copyRight = STR_BIZ_COPYRIGHT;
	}
}