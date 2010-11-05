/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_message_stub.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Cross Cutting Message Facade
*/

#pragma once

#include "crx_namespace.h"

using namespace System;
using namespace System::Resources;
using namespace System::Diagnostics;
using namespace System::Reflection;

START_CRX_MSG_NAMESPACE

public ref class CrxMessageFacade
{
public:
	static ResourceManager^ messageResources;

	static CrxMessageFacade^ CrxMessageFacade::Instance();
	
	// Display a message to the user.
	// The user message should be translated by the Resource -
	// Manager, while the log message should be invariant (English)
	bool Message(TraceEventType severity, String^ title, 
				String^ userMessage, String^ logMessage);

protected:
	CrxMessageFacade(void);
	
private:
	static CrxMessageFacade^ _instance;
};

END_CRX_MSG_NAMESPACE
