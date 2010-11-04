/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	electronic_module.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Electronic Module class
*/

#pragma once

#include <biz_namespace.h>

using namespace System;
using namespace DAL_NAMESPACE;

START_BIZ_NAMESPACE

ref class BizElectronicModuleState; // needed for forward declaration

public ref class BizElectronicModule
{
public:
	void ChangeState(BizElectronicModuleState^ state);

	property BizElectronicModuleState^ currentState;

	// Constructor
	BizElectronicModule(void);

private:
	unsigned short oldDalModuleState;

	void Update(Object^ sender, DalModuleErrorAlarmEventArgs^ e);
//	DalElectronicModuleStatusEvent^ cuffStatusSubject; // to observe cuff state event from DAL
};
END_BIZ_NAMESPACE
