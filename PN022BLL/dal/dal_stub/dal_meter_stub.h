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

	// DalCountdownArgs: a custom event inherited from EventArgs.
	public ref class DalCountdownEventArgs: public EventArgs
	{
	public:
	   DalCountdownEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalCountdownEvent
	{
	public:
	   delegate void DalCountdownEventHandler(Object^ sender, DalCountdownEventArgs^ args );

	   // Now, create a public event "CountdownEvent" whose type is our DalCountdownEventHandler delegate. 
	   event DalCountdownEventHandler^ CountdownEvent;

	   // This will be the starting point of our event-- it will create DalCountdownArgs,
	   // and then raise the event, passing DalCountdownArgs. 
	   void Notify( unsigned short data );
	};

	// PayloadDataEventArgs: a custom event inherited from EventArgs.
	public ref class DalPayloadDataEventArgs: public EventArgs
	{
	public:
	   DalPayloadDataEventArgs( unsigned int dataType, unsigned short len, array<char>^ data )
	   {
	      payLoadType = dataType;
		  payloadLength = len;
		  payloadBuffer = data;
	   }
	protected:
	   property unsigned short payLoadType;
	   property unsigned short payloadLength;
	   property array<char>^ payloadBuffer;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalPayloadDataEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a DalPayloadData
	   // as a delegate:
	   delegate void PayloadDataEventHandler(Object^ sender, DalPayloadDataEventArgs^ tde );

	   // Now, create a public event whose type is our PayloadDataEventHandler delegate. 
	   event PayloadDataEventHandler^ PayloadDataEvent;

	   // This will be the starting point of our event-- it will create DalPayloadDataEventArgs,
	   // and then raise the event, passing DalPayloadDataEventArgs. 
	   void Notify( unsigned int dataType, unsigned int len, array<char>^ data );
	};

	public ref class DalMeter abstract
	{
	public:
		virtual void Simulate() {};
		property DalCuffPulseEvent^ cuffPulse;
	};

	public ref class DalTonometerStub : DalMeter
	{
	private: 
		static DalTonometerStub^ _instance;
	protected:
		DalTonometerStub();
	public:
		static DalTonometerStub^ Instance();
		property DalTonometerDataEvent^ tonometerDataRaw;
	};

	public ref class DalCuffStub : DalMeter
	{
	private: 
		static DalCuffStub^ _instance;
	protected:
		DalCuffStub();
	public:
		static DalCuffStub^ Instance();
		property DalCuffPulseEvent^ cuffPulseRaw;
	};

	public ref class DalCountdownStub : DalMeter
	{
	private: 
		static DalCountdownStub^ _instance;
	protected:
		DalCountdownStub();
	public:
		static DalCountdownStub^ Instance();
		property DalCountdownEvent^ countdownRaw;
	};

}
