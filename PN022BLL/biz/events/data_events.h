/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	data_events.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of business data event classes.
*/

#pragma once

using namespace System;

namespace Biz {

	// BizTonometerDataEventArgs: a custom event inherited from EventArgs.
	public ref class BizTonometerDataEventArgs: public EventArgs
	{
	public:
	   BizTonometerDataEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   property unsigned short data;
	};

	// Class with a function that creates the eventargs and initiates the event
	public ref class BizTonometerDataEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a handler
	   // as a delegate. FxCop suggested to use EventHandler<T> to eliminate
	   // custom delegate like this but unit test couldn't be compiled.
	   delegate void BizTonometerDataEventHandler(Object^ sender, BizTonometerDataEventArgs^ e );

	   // Now, create a public event whose type is our handler delegate. 
	   event BizTonometerDataEventHandler^ TonometerDataEvent;
	   /* FxCop suggested to use EventHandler<T> to replace above above but it didn't comiple as explained above.
	   event EventHandler<BizTonometerDataEventArgs^>^ TonometerDataEvent;
	   */

	   // This will be the starting point of our event-- it will create data args,
	   // and then raise the event, passing the args. 
	   void Notify( unsigned int data );

	};

	// BizCuffPulseEventArgs: a custom event inherited from EventArgs.
	public ref class BizCuffPulseEventArgs: public EventArgs
	{
	public:
	   BizCuffPulseEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   property unsigned short data;
	};

	// Class with a function that creates the eventargs and initiates the event
	public ref class BizCuffPulseEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a handler
	   // as a delegate:
	   delegate void BizCuffPulseEventHandler(Object^ sender, BizCuffPulseEventArgs^ e );

	   // Now, create a public event whose type is our handler delegate. 
	   event BizCuffPulseEventHandler^ CuffPulseEvent;

	   // This will be the starting point of our event-- it will create data args,
	   // and then raise the event, passing the args. 
	   void Notify( unsigned int data );

	};
	// BizCountdownArgs: a custom event inherited from EventArgs.
	public ref class BizCountdownEventArgs: public EventArgs
	{
	public:
	   BizCountdownEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   property unsigned short data;
	};

	// Class with a function that creates the eventargs and initiates the event
	public ref class BizCountdownEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a handler
	   // as a delegate:
	   delegate void BizCountdownEventHandler(Object^ sender, BizCountdownEventArgs^ e );

	   // Now, create a public event whose type is our handler delegate. 
	   event BizCountdownEventHandler^ CountdownEvent;

	   // This will be the starting point of our event-- it will create data args,
	   // and then raise the event, passing the args. 
	   void Notify( unsigned int data );

	};
}
