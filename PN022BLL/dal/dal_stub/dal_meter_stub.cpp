/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_meter_data_stub.cpp
	
	Author       :  Victor Aung

    Description  :	Meter Data stub classes
*/

#include "StdAfx.h"
#include "dal_meter_stub.h"

namespace DataAccess {

	void DalTonometerDataEvent::Notify( unsigned int data )
	{
		DalTonometerDataEventArgs^ tonometerArgs = gcnew DalTonometerDataEventArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as event args. 
		// The call must match the signature of the corresponding event handler.
		TonometerDataEvent( this, tonometerArgs );
	}
	void DalCuffPulseEvent::Notify( unsigned short data )
	{
		DalCuffPulseEventArgs^ cuffPulseArgs = gcnew DalCuffPulseEventArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as event args. 
		// The call must match the signature of the corresponding event handler.
		CuffPulseEvent( this, cuffPulseArgs );
	}
	void DalCountdownEvent::Notify( unsigned short data )
	{
		DalCountdownEventArgs^ countdownArgs = gcnew DalCountdownEventArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as event args. 
		// The call must match the signature of the corresponding event handler.
		CountdownEvent( this, countdownArgs );
	}

	DalTonometerStub::DalTonometerStub()
	{
		tonometerDataRaw = gcnew DalTonometerDataEvent;
//?		tonometerDataValue = 0;
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

	DalCountdownStub::DalCountdownStub()
	{
		countdownRaw = gcnew DalCountdownEvent;
	}

	DalCountdownStub^ DalCountdownStub::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalCountdownStub;
		}
		return _instance;
	}
}
