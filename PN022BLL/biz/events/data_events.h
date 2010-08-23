/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	data_events.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of business data event classes.
*/

#pragma once

using namespace System;

namespace Biz {

	// BizTonoDataArgs: a custom event inherited from EventArgs.
	public ref class BizTonoDataArgs: public EventArgs
	{
	public:
	   BizTonoDataArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};

	// Class with a function that creates the eventargs and initiates the event
	public ref class BizTonoDataEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a DalTonoDataHandler
	   // as a delegate:
	   delegate void BizTonoDataEventHandler(Object^ sender, BizTonoDataArgs^ args );

	   // Now, create a public event whose type is our TonoDataEventHandler delegate. 
	   event BizTonoDataEventHandler^ TonoDataEvent;

	   // This will be the starting point of our event-- it will create BizTonoDataArgs,
	   // and then raise the event, passing BizTonoDataArgs. 
	   void Notify( unsigned int data );
	};
}
