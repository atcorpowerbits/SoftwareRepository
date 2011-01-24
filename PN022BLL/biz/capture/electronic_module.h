/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	electronic_module.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Electronic Module class
*/

#pragma once

#include <biz_namespace.h>
#include <data_events.h>

using namespace System;
using namespace DAL_NAMESPACE;

START_BIZ_NAMESPACE

ref class BizElectronicModuleState; // needed for forward declaration

public ref class BizElectronicModule
{
public:
	void ChangeState(BizElectronicModuleState^ state);

	// Dispatch information / warning / error message to be handled by an observer
	//e.g. Presentation Layer
	void Dispatch();

	property BizElectronicModuleState^ currentState;
	property BizElectronicModuleState^ previousState;
	property BizElectronicModuleState^ dispatchedState;

	// Constructor
	BizElectronicModule(void);

private:
//	unsigned short prevErrorAlarmStatus; // TBD: move it to DAL to filter it earlier in DAL
	DataAccess::DalErrorAlarmStatusFlag prevErrorAlarmStatus; // TBD: move it to DAL to filter it earlier in DAL
	String^ source;

//	void Update(Object^ sender, DalModuleErrorAlarmEventArgs^ e);
	void Update_ORI(Object^ sender, DalModuleErrorAlarmEventArgs_ORI^ e); // _ORI prefix'es were introduced in DAL by TM during Sprint-5
};
END_BIZ_NAMESPACE
