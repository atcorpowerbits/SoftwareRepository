/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	crx_message_stub.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Cross Cutting Message Facade
*/

#pragma once

using namespace System;
using namespace System::Resources;
using namespace System::Diagnostics;
using namespace System::Reflection;

namespace CrossCutting {
	
	public ref class CrxMessageFacade
	{
	public:
		static ResourceManager^ messageResources;

		static CrxMessageFacade^ CrxMessageFacade::Instance();
		
		// Display a message to the user
		bool Message(TraceEventType severity, String^ title, 
					String^ userMessage, String^ logMessage);

	protected:
		CrxMessageFacade(void);
		
	private:
		static CrxMessageFacade^ _instance;
	};
}