/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_config_stub.h
	
	Author       :  Victor Aung

    Description  :	Cross Cutting Configuration Facade Classes
*/
#include "stdafx.h"
#include "crx_config_stub.h"

#
namespace CrossCutting {
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
		return (MeasureUnit == MEASUREMENT_UNIT_METRICS);
	}
}