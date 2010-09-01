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
	   // Events are handled with delegates, so we must establish a handler
	   // as a delegate:
	   delegate void BizTonoDataEventHandler(Object^ sender, BizTonoDataArgs^ args );

	   // Now, create a public event whose type is our handler delegate. 
	   event BizTonoDataEventHandler^ TonoDataEvent;

	   // This will be the starting point of our event-- it will create data args,
	   // and then raise the event, passing the args. 
	   void Notify( unsigned int data );

	};

	// BizCuffPulseArgs: a custom event inherited from EventArgs.
	public ref class BizCuffPulseArgs: public EventArgs
	{
	public:
	   BizCuffPulseArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};

	// Class with a function that creates the eventargs and initiates the event
	public ref class BizCuffPulseEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a handler
	   // as a delegate:
	   delegate void BizCuffPulseEventHandler(Object^ sender, BizCuffPulseArgs^ args );

	   // Now, create a public event whose type is our handler delegate. 
	   event BizCuffPulseEventHandler^ CuffPulseEvent;

	   // This will be the starting point of our event-- it will create data args,
	   // and then raise the event, passing the args. 
	   void Notify( unsigned int data );

	};
	// BizCountdownArgs: a custom event inherited from EventArgs.
	public ref class BizCountdownArgs: public EventArgs
	{
	public:
	   BizCountdownArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};

	// Class with a function that creates the eventargs and initiates the event
	public ref class BizCountdownEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a handler
	   // as a delegate:
	   delegate void BizCountdownEventHandler(Object^ sender, BizCountdownArgs^ args );

	   // Now, create a public event whose type is our handler delegate. 
	   event BizCountdownEventHandler^ CountdownEvent;

	   // This will be the starting point of our event-- it will create data args,
	   // and then raise the event, passing the args. 
	   void Notify( unsigned int data );

	};
}
