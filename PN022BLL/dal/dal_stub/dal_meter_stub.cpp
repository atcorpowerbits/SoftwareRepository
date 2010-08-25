/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_meter_data_stub.cpp
	
	Author       :  Victor Aung

    Description  :	Meter Data stub classes
*/

#include "StdAfx.h"
#include "dal_meter_stub.h"

namespace DataAccess {

//	DalMeter::DalMeter()
//	{
//	}
	void DalTonoDataEvent::Notify( unsigned int data )
	{
		DalTonoDataArgs^ tonoArgs = gcnew DalTonoDataArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as FireEventArgs. 
		// The call must match the signature of FireEventHandler.
		TonoDataEvent( this, tonoArgs );
	}
	void DalCuffPulseEvent::Notify( unsigned short data )
	{
		DalCuffPulseArgs^ cuffPulseArgs = gcnew DalCuffPulseArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as FireEventArgs. 
		// The call must match the signature of FireEventHandler.
		CuffPulseEvent( this, cuffPulseArgs );
	}
	void DalPayloadDataEvent::Notify( unsigned int dataType, unsigned int len, array<char>^ data )
	{
		DalPayloadDataArgs^ payloadArgs = gcnew DalPayloadDataArgs( dataType, len, data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as arguments. 
		// The call must match the signature of PayloadDataEventHandler.
		PayloadDataEvent( this, payloadArgs );
	}

	DalTonometerStub::DalTonometerStub()
	{
		tonoDataRaw = gcnew DalTonoDataEvent;
//?		tonoDataValue = 0;
	}

	DalTonometerStub^ DalTonometerStub::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalTonometerStub;
		}
		return _instance;
	}
	   
	DalCuffStub::DalCuffStub()
	{
		cuffPulseRaw = gcnew DalCuffPulseEvent;
	}

	DalCuffStub^ DalCuffStub::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalCuffStub;
		}
		return _instance;
	}
}
