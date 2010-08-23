/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_message_stub.cpp
	
	Author       :  Paul McBryde

    Description  :	Cross Cutting Message Facade Classes
*/

#include "stdafx.h"
#include "crx_message_stub.h"

using namespace CrossCutting;

#pragma hdrstop


/** 
Instance

DESCRIPTION
   Get the singleton instance of Message Facade.

INPUT

   None.

OUTPUT

   None.

RETURN

   Handle to the object instance

*/	
CrxMessageFacade^ CrxMessageFacade::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew CrxMessageFacade;
	}
	return _instance;
}
/** 
Constructor

DESCRIPTION
   Constructor for Message Facade.

INPUT
   None.

OUTPUT
   None.

RETURN
   None.
*/	
CrxMessageFacade::CrxMessageFacade(void)
{
	messageResources = gcnew ResourceManager("crx_stub.messages", Assembly::GetExecutingAssembly());
}

// Display a message to the user
// 
bool CrxMessageFacade::Message(TraceEventType severity, String^ title, 
								String^ userMessage, String^ logMessage)
{
	return true;
}
