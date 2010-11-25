/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Cuff class
*/

#pragma once

#include <data_events.h>
#include <biz_namespace.h>

using namespace System;
using namespace DAL_NAMESPACE;

START_BIZ_NAMESPACE

ref class BizCuffState; // needed for forward declaration

public ref class BizCuff
{
public:
	void ChangeState(BizCuffState^ state);
	void Dispatch();

//	property BizCuffStateEvent^ cuffStateBiz; //cuff state event to be passed to obesrserve

	// Keep previous and current cuff states
	property BizCuffState^ previousState;
	property BizCuffState^ currentState;

	// Constructor
	BizCuff(void);

private:
	void Update(Object^ sender, DalCuffStatusEventArgs^ e);
//	DalCuffStatusEvent^ cuffStatusSubject; // to observe cuff state event from DAL
};
END_BIZ_NAMESPACE
