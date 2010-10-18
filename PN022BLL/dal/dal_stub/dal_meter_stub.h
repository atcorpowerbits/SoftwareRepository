/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_meter_data_stub.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of meter data stub classes.
*/

#pragma once

using namespace System;
using namespace System::Timers;

namespace DataAccess {

	// DalTonometerDataEventArgs: a custom event inherited from EventArgs.
	public ref class DalTonometerDataEventArgs: public EventArgs
	{
	public:
	   DalTonometerDataEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};

	// Class with a function that creates the eventargs and initiates the event
	public ref class DalTonometerDataEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a DalTonometerDataHandler
	   // as a delegate:
	   delegate void DalTonometerDataEventHandler(Object^ sender, DalTonometerDataEventArgs^ args );

	   // Now, create a public event "TonometerDataEvent" whose type is our DalTonometerDataEventHandler delegate. 
	   event DalTonometerDataEventHandler^ TonometerDataEvent;

	   // This will be the starting point of our event-- it will create DalTonometerDataEventArgs,
	   // and then raise the event, passing DalTonometerDataEventArgs. 
	   void Notify( unsigned int data );
	};

	// DalCuffPulseArgs: a custom event inherited from EventArgs.
	public ref class DalCuffPulseEventArgs: public EventArgs
	{
	public:
	   DalCuffPulseEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalCuffPulseEvent
	{
	public:
	   delegate void DalCuffPulseEventHandler(Object^ sender, DalCuffPulseEventArgs^ args );

	   // Now, create a public event "CuffPulseEvent" whose type is our DalCuffPulseEventHandler delegate. 
	   event DalCuffPulseEventHandler^ CuffPulseEvent;

	   // This will be the starting point of our event-- it will create DalCuffPulseArgs,
	   // and then raise the event, passing DalCuffPulseArgs. 
	   void Notify( unsigned short data );
	};

	// DalCuffPressureArgs: a custom event inherited from EventArgs.
	public ref class DalCuffPressureEventArgs: public EventArgs
	{
	public:
	   DalCuffPressureEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalCuffPressureEvent
	{
	public:
	   delegate void DalCuffPressureEventHandler(Object^ sender, DalCuffPressureEventArgs^ args );

	   // Now, create a public event "CuffPressureEvent" whose type is our DalCuffPressureEventHandler delegate. 
	   event DalCuffPressureEventHandler^ CuffPressureEvent;

	   // This will be the starting point of our event-- it will create DalCuffPressureArgs,
	   // and then raise the event, passing DalCuffPressureArgs. 
	   void Notify( unsigned short data );
	};

	// DalCountdownTimerArgs: a custom event inherited from EventArgs.
	public ref class DalCountdownTimerEventArgs: public EventArgs
	{
	public:
	   DalCountdownTimerEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalCountdownTimerEvent
	{
	public:
	   delegate void DalCountdownTimerEventHandler(Object^ sender, DalCountdownTimerEventArgs^ args );

	   // Now, create a public event "CountdownTimerEvent" whose type is our DalCountdownTimerEventHandler delegate. 
	   event DalCountdownTimerEventHandler^ CountdownTimerEvent;

	   // This will be the starting point of our event-- it will create DalCountdownTimerArgs,
	   // and then raise the event, passing DalCountdownTimerArgs. 
	   void Notify( unsigned short data );
	};

	// DalCuffStatusArgs: a custom event inherited from EventArgs.
	public ref class DalCuffStatusEventArgs: public EventArgs
	{
	public:
	   DalCuffStatusEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalCuffStatusEvent
	{
	public:
	   delegate void DalCuffStatusEventHandler(Object^ sender, DalCuffStatusEventArgs^ args );

	   // Now, create a public event "CuffStatusEvent" whose type is our DalCuffStatusEventHandler delegate. 
	   event DalCuffStatusEventHandler^ CuffStatusEvent;

	   // This will be the starting point of our event-- it will create DalCuffStatusArgs,
	   // and then raise the event, passing DalCuffStatusArgs. 
	   void Notify( unsigned short data );
	private:
		unsigned short previousStatus;
	};

	public ref class DalMeter
	{
	public:
		static DalMeter^ Instance();
		property DalTonometerDataEvent^ tonometerDataEvent;
		property DalCuffPulseEvent^ cuffPulseEvent;
		property DalCuffPressureEvent^ cuffPressureEvent;
		property DalCountdownTimerEvent^ countdownTimerEvent;
		property DalCuffStatusEvent^ cuffStatusEvent;
	protected:
		DalMeter();
	private: 
		static DalMeter^ _instance;
	};
}
