/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_config_stub.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Cross Cutting Configuration Facade
*/

#pragma once

#include "crx_namespace.h"

using namespace System;

START_CRX_CONFIG_NAMESPACE

// Cross-Cutting Configuration Facade Singleton Class
public ref class CrxConfigFacade
{
public:
	static CrxConfigFacade^ CrxConfigFacade::Instance();
	bool isSubtractingMethod();
	unsigned short GetCaptureTime();

	// For unit testing PWV
	void SetDistanceMethod(bool);
	void SetCaptureTime(unsigned short);

protected:
	CrxConfigFacade(void);
	property bool PWVSubtractingMethod;
	property unsigned short PWVCaptureTime;
private:
	static CrxConfigFacade^ _instance;
};

END_CRX_CONFIG_NAMESPACE
