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

	// DalTonoDataEventArgs: a custom event inherited from EventArgs.
	public ref class DalTonoDataArgs: public EventArgs
	{
	public:
	   DalTonoDataArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};

	// Class with a function that creates the eventargs and initiates the event
	public ref class DalTonoDataEvent
	{
	public:
	   // Events are handled with delegates, so we must establish a DalTonoDataHandler
	   // as a delegate:
	   delegate void DalTonoDataEventHandler(Object^ sender, DalTonoDataArgs^ args );

	   // Now, create a public event "TonoDataEvent" whose type is our DalTonoDataEventHandler delegate. 
	   event DalTonoDataEventHandler^ TonoDataEvent;

	   // This will be the starting point of our event-- it will create DalTonoDataEventArgs,
	   // and then raise the event, passing DalTonoDataEventArgs. 
	   void Notify( unsigned int data );
	};

	// DalCuffPulseArgs: a custom event inherited from EventArgs.
	public ref class DalCuffPulseArgs: public EventArgs
	{
	public:
	   DalCuffPulseArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalCuffPulseEvent
	{
	public:
	   delegate void DalCuffPulseEventHandler(Object^ sender, DalCuffPulseArgs^ args );

	   // Now, create a public event "CuffPulseEvent" whose type is our DalCuffPulseEventHandler delegate. 
	   event DalCuffPulseEventHandler^ CuffPulseEvent;

	   // This will be the starting point of our event-- it will create DalCuffPulseArgs,
	   // and then raise the event, passing DalCuffPulseArgs. 
	   void Notify( unsigned short data );
	};

	// DalCountdownArgs: a custom event inherited from EventArgs.
	public ref class DalCountdownArgs: public EventArgs
	{
	public:
	   DalCountdownArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalCountdownEvent
	{
	public:
	   delegate void DalCountdownEventHandler(Object^ sender, DalCountdownArgs^ args );

	   // Now, create a public event "CountdownEvent" whose type is our DalCountdownEventHandler delegate. 
	   event DalCountdownEventHandler^ CountdownEvent;

	   // This will be the starting point of our event-- it will create DalCountdownArgs,
	   // and then raise the event, passing DalCountdownArgs. 
	   void Notify( unsigned short data );
	};

	// PayloadDataEventArgs: a custom event inherited from EventArgs.
	public ref class DalPayloadDataArgs: public EventArgs
	{
	public:
	   DalPayloadDataArgs( unsigned int dataType, unsigned short len, array<char>^ data )
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
	   delegate void PayloadDataEventHandler(Object^ sender, DalPayloadDataArgs^ tde );

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
		property DalTonoDataEvent^ tonoDataRaw;
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
