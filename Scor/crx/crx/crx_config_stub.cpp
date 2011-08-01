/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_config_stub.h
	
	Author       :  Victor Aung

    Description  :	Cross Cutting Configuration Facade Classes
*/
#include "stdafx.h"
#include "crx_namespace.h"
#include "crx_config_stub.h"
#include "CrxMessaging.h"

using namespace CRX_CONFIG_NAMESPACE;
using namespace CRX_MSG_NAMESPACE;

/** 
Instance

DESCRIPTION
   Get the singleton instance of Config Facade.

INPUT

   None.

OUTPUT

   None.

RETURN

   Handle to the object instance

*/	
CrxConfigFacade^ CrxConfigFacade::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew CrxConfigFacade;
	}
	return _instance;
}
/** 
Instance

DESCRIPTION
   Constructor for Config Facade.
INPUT
   None.
OUTPUT
   None.
RETURN
   None.
*/	
CrxConfigFacade::CrxConfigFacade(void)
{
	PWVSubtractingMethod = true;
	PWVCaptureTime = 20; // stub to 20 sec
}
/** 
isPWVSubtractingMethod

DESCRIPTION

   Check PWV Distance Subtracting Method is used.

INPUT

   None.

OUTPUT

   None.

RETURN

   true  - PWV Distance Subtracting Method is used

   false - PWV Distance Subtracting Method is not used

*/
bool CrxConfigFacade::isSubtractingMethod()
{
	return (PWVSubtractingMethod);
}
unsigned short CrxConfigFacade::GetCaptureTime()
{
	return PWVCaptureTime;
}
void CrxConfigFacade::SetDistanceMethod(bool subtracting)
{
	PWVSubtractingMethod = subtracting;
}
void CrxConfigFacade::SetCaptureTime(unsigned short captureTime)
{
	PWVCaptureTime = captureTime;
}

bool CrxConfigFacade::IsPressurePeriphCuff()
{
	return false; // true: Cuff, false: Tonometer
}

bool CrxConfigFacade::IsPwaMode()
{
	return false; // true: PWA mode, false: PWV mode
}

String^ CrxConfigFacade::GetDistanceUnitName()
{
	String^ unitName;
	if (CrxConfigManager::Instance->PwvSettings->PWVDistanceUnits == (int)CrxGenPwvValue::CrxPwvDistDistUnitsCM)
	{
		unitName = CrxMessagingManager::Instance->GetMessage("CM");
	}
	else
	{
		unitName = CrxMessagingManager::Instance->GetMessage("MM");
	}
	return unitName;
}

unsigned int CrxConfigFacade::GetDistanceUnitDivisor()
{
	unsigned int unitDivisor;
	if (CrxConfigManager::Instance->PwvSettings->PWVDistanceUnits == (int)CrxGenPwvValue::CrxPwvDistDistUnitsCM)
	{
		// Internal distance in mm to be converted to cm
		unitDivisor = 10;
	}
	else
	{
		// Internal distance in mm to be used as is
		unitDivisor = 1;
	}
	return unitDivisor;
}

