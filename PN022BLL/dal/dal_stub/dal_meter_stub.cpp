/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_meter_data_stub.cpp
	
	Author       :  Victor Aung

    Description  :	Meter Data stub classes
*/

#include <StdAfx.h>
#include <dal.h>
#include <dal_meter_stub.h>

using namespace DAL_NAMESPACE;

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
void DalCuffPressureEvent::Notify( unsigned short data )
{
	DalCuffPressureEventArgs^ cuffPressureArgs = gcnew DalCuffPressureEventArgs( data );

	// Now, raise the event by invoking the delegate. Pass in 
	// the object that initated the event (this) as well as event args. 
	// The call must match the signature of the corresponding event handler.
	CuffPressureEvent( this, cuffPressureArgs );
}
void DalCountdownTimerEvent::Notify( unsigned short data )
{
	// Notify only a round sec 
//		if (!(data % 1000))
//		{
		DalCountdownTimerEventArgs^ countdownTimerArgs = gcnew DalCountdownTimerEventArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as event args. 
		// The call must match the signature of the corresponding event handler.
		CountdownTimerEvent( this, countdownTimerArgs );
//		}
}
void DalCuffStatusEvent::Notify( unsigned short data )
{
	unsigned short cuffState;

	// Map cuff status data to cuff state 
	switch (data & 0xFF)
	{
	case DalConstants::CUFF_DISCONNECTED_STATUS_BITS:
		cuffState = DalConstants::CUFF_STATE_DISCONNECTED;
		break;
	case DalConstants::CUFF_DEFLATED_STATUS_BITS:
		cuffState = DalConstants::CUFF_STATE_DEFLATED;
		break;
	case DalConstants::CUFF_INFLATING_STATUS_BITS:
		cuffState = DalConstants::CUFF_STATE_INFLATING;
		break;
	case DalConstants::CUFF_INFLATED_STATUS_BITS:
		cuffState = DalConstants::CUFF_STATE_INFLATED;
		break;
	case DalConstants::CUFF_DEFLATING_STATUS_BITS:
		cuffState = DalConstants::CUFF_STATE_DEFLATING;
		break;
	default:
		break;
	}
	DalCuffStatusEventArgs^ cuffStatusArgs = gcnew DalCuffStatusEventArgs( cuffState );

	// Now, raise the event by invoking the delegate. Pass in 
	// the object that initated the event (this) as well as event args. 
	// The call must match the signature of the corresponding event handler.
	CuffStatusEvent( this, cuffStatusArgs );
}

DalMeter::DalMeter()
{
	tonometerDataEvent = gcnew DalTonometerDataEvent;
	cuffPulseEvent = gcnew DalCuffPulseEvent;
	cuffPressureEvent = gcnew DalCuffPressureEvent;
	countdownTimerEvent = gcnew DalCountdownTimerEvent;
	cuffStatusEvent = gcnew DalCuffStatusEvent;
}

DalMeter^ DalMeter::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew DalMeter;
	}
	return _instance;
}
