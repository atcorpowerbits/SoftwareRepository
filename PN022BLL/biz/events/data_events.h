/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	data_events.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of business data event classes.
*/

#pragma once

#include <biz_namespace.h>

using namespace System;

START_BIZ_NAMESPACE

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
// BizCountdownTimerEventArgs: a custom event inherited from EventArgs.
public ref class BizCountdownTimerEventArgs: public EventArgs
{
public:
   BizCountdownTimerEventArgs( unsigned short data )
   {
	  this->data = data;
   }
   property unsigned short data;
};

// Class with a function that creates the eventargs and initiates the event
public ref class BizCountdownTimerEvent
{
public:
   // Events are handled with delegates, so we must establish a handler
   // as a delegate:
   delegate void BizCountdownTimerEventHandler(Object^ sender, BizCountdownTimerEventArgs^ e );

   // Now, create a public event whose type is our handler delegate. 
   event BizCountdownTimerEventHandler^ CountdownTimerEvent;

   // This will be the starting point of our event-- it will create data args,
   // and then raise the event, passing the args. 
   void Notify( unsigned int data );

};
// BizCuffStateEventArgs: a custom event inherited from EventArgs.
public ref class BizCuffStateEventArgs: public EventArgs
{
public:
   BizCuffStateEventArgs( String^ data )
   {
	  this->data = data;
   }
   property String^ data;
};

// Class with a function that creates the eventargs and initiates the event
public ref class BizCuffStateEvent
{
public:
   // Events are handled with delegates, so we must establish a handler
   // as a delegate:
   delegate void BizCuffStateEventHandler(Object^ sender, BizCuffStateEventArgs^ e );

   // Now, create a public event whose type is our handler delegate. 
   event BizCuffStateEventHandler^ CuffStateEvent;

   // This will be the starting point of our event-- it will create data args,
   // and then raise the event, passing the args. 
   // Possible cuff states are:
   // -Disconnected
   // -Deflated
   // -Inflating
   // -Inflated
   // -Deflating
   // -Resting
   void Notify( String^ data );

};

END_BIZ_NAMESPACE
