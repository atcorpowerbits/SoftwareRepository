/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_config_stub.h
	
	Author       :  Victor Aung

    Description  :	Cross Cutting Configuration Facade Classes
*/
#include "stdafx.h"
#include "crx_namespace.h"
#include "crx_config_stub.h"

using namespace CRX_CONFIG_NAMESPACE;

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
	PWVMeasureUnit = MEASUREMENT_UNIT_METRICS; // stub to metrics
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
bool CrxConfigFacade::isMetricsUnit()
{
	return (PWVMeasureUnit == MEASUREMENT_UNIT_METRICS);
}
bool CrxConfigFacade::isSubtractingMethod()
{
	return (PWVSubtractingMethod);
}
unsigned short CrxConfigFacade::GetCaptureTime()
{
	return PWVCaptureTime;
}
void CrxConfigFacade::SetMeasurementUnit(unsigned short metrics)
{
	PWVMeasureUnit = metrics;
}
void CrxConfigFacade::SetDistanceMethod(bool subtracting)
{
	PWVSubtractingMethod = subtracting;
}
void CrxConfigFacade::SetCaptureTime(unsigned short captureTime)
{
	PWVCaptureTime = captureTime;
}
void CrxConfigFacade::SetBPCombination(unsigned short bp)
{
	PWVBPCombination = bp;
}
unsigned short CrxConfigFacade::GetBPCombination()
{
	return PWVBPCombination;
}
