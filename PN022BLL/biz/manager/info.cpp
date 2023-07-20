/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	info.h
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Information Class
*/

#include "stdafx.h"
#include <biz.h>
#include <info.h>

using namespace System::Globalization;
using namespace BIZ_NAMESPACE;
//using namespace CRX_CONFIG_NAMESPACE;
using namespace CRX_MSG_NAMESPACE;
using namespace DAL_NAMESPACE;

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

	length - Company name string buffer limit.

OUTPUT

	coName - Company name string.

RETURN

	None.

*/
void BizInfo::GetCompanyName(String^ %coName, unsigned short length)
{
	if (company->Length > length) 
	{
		coName = company->Substring(0,length);
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

	length - Application version string buffer limit.

OUTPUT

	appVersion - Application version string.

RETURN

	None.

*/
void BizInfo::GetVersion(String^ %appVersion, unsigned short length)
{
	if (this->appVersion->Length > length) 
	{
		appVersion = this->appVersion->Substring(0,length);
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

	length - Application copyright string buffer limit.

OUTPUT

	copyRight - Application copyright string.

RETURN

	None.

*/
void BizInfo::GetCopyright(String^ %copyRight, unsigned short length)
{
	if (this->copyRight->Length > length) 
	{
		copyRight = this->copyRight->Substring(0,length);
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

	length - Module type string buffer limit.

OUTPUT

	info - Module type string.

RETURN

	None.

*/
void BizInfo::GetModuleType(String^ %info, unsigned short length)
{
	moduleType = DalFacade::Instance()->FindModuleInfo()->moduleType;

	if (moduleType->Length > length) 
	{
		info = moduleType->Substring(0,length);
	} else 
	{
		info = moduleType;
	}
}

/**
GetModuleConfigID

DESCRIPTION

	Get the electronic module config ID.

INPUT

	None.

OUTPUT

	None.

RETURN

	Electronic module config ID integer value.

*/
unsigned short BizInfo::GetModuleConfigID()
{
	moduleConfigID = DalFacade::Instance()->FindModuleInfo()->moduleConfigID;
	return moduleConfigID;
}

/**
GetModuleSN

DESCRIPTION

	Get the electronic module serial number.

INPUT

	length - Module serial number string buffer limit.

OUTPUT

	info - Module serial number string.

RETURN

	None.

*/
void BizInfo::GetModuleSN(String^ %info, unsigned short length)
{
	moduleSN = DalFacade::Instance()->FindModuleInfo()->moduleSN;

	if (moduleSN->Length > length) 
	{
		info = moduleSN->Substring(0,length);
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

	length - Module version string buffer limit.

OUTPUT

	info - Module version string.

RETURN

	None.

*/
void BizInfo::GetModuleVersion(String^ %info, unsigned short length)
{
	moduleVersion = DalFacade::Instance()->FindModuleInfo()->moduleMainFWVersion;

	if (moduleVersion->Length > length) 
	{
		info = moduleVersion->Substring(0,length);
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

	length - Module calibration date string buffer limit.

OUTPUT

	info - Module calibration date.

RETURN

	None.

*/
void BizInfo::GetModuleCalibrationDate(String^ %info, unsigned short length)
{
	String^ dateString;

	moduleCalibrationDate = DalFacade::Instance()->FindModuleInfo()->moduleCalibrationDate;

	// Convert date to culturally correct string suggested by FxCop
	dateString = Convert::ToString(moduleCalibrationDate, CultureInfo::CurrentUICulture);

	if (dateString->Length > length) 
	{
		info = dateString->Substring(0,length);
	} else 
	{
		info = dateString;
	}
}
/**
GetModuleConfigName

DESCRIPTION

	Get the electronic module config name.

INPUT

	length - Module config name string buffer limit.

OUTPUT

	info - Module config name.

RETURN

	None.

*/
void BizInfo::GetModuleConfigName(String^ %info, unsigned short length)
{
	String^ configName;
	unsigned short configValue = GetModuleConfigID();

	switch (configValue)
	{
	case CONFIG_ID_PWV:
		configName = CrxMessageFacade::Instance()->messageResources->
			GetString(L"CONFIG_NAME_PWV", CultureInfo::CurrentUICulture);
		break;
	default:
		configName = CrxMessageFacade::Instance()->messageResources->
			GetString(L"CONFIG_NAME_INVALID", CultureInfo::CurrentUICulture);
		break;
	}
	if (configName->Length > length) 
	{
		info = configName->Substring(0,length);
	} else 
	{
		info = configName;
	}
}
/**
GetConfigDate

DESCRIPTION

	Get the electronic module configuration date.

INPUT

	length - Module configuration date string buffer limit.

OUTPUT

	info - Module configuration date.

RETURN

	None.

*/
void BizInfo::GetModuleConfigDate(String^ %info, unsigned short length)
{
	String^ dateString;

	moduleConfigDate = DalFacade::Instance()->FindModuleInfo()->moduleConfigDate;

	// Convert date to culturally correct string suggested by FxCop
	dateString = Convert::ToString(moduleConfigDate, CultureInfo::CurrentUICulture);

	if (dateString->Length > length) 
	{
		info = dateString->Substring(0,length);
	} else 
	{
		info = dateString;
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
	company = CrxMessageFacade::Instance()->messageResources->
		GetString(L"COMPANY_NAME", CultureInfo::CurrentUICulture);
	appVersion = CrxMessageFacade::Instance()->messageResources->
		GetString(L"APP_VERSION", CultureInfo::CurrentUICulture);
	copyRight = CrxMessageFacade::Instance()->messageResources->
		GetString(L"COMPANY_COPYRIGHT", CultureInfo::CurrentUICulture);
}
