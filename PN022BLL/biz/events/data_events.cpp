/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	data_events.cpp
	
	Author       :  Victor Aung

    Description  :	Business data event classes
*/

#include "StdAfx.h"
#include <data_events.h>

using namespace BIZ_NAMESPACE;

/**
BizTonometerDataEvent::Notify

DESCRIPTION

	Creates a tonometer data arguments and notifies the changes as an event to all observers.

INPUT

	data - Tonometermeter data in business context

OUTPUT

	None.

RETURN

	None.

*/
void BizTonometerDataEvent::Notify( unsigned int data )
{
	BizTonometerDataEventArgs^ tonoArgs = gcnew BizTonometerDataEventArgs( data );

	// Now, raise the event by invoking the delegate. Pass in 
	// the object that initated the event (this) as well as data args. 
	// The call must match the signature of the handler.
	TonometerDataEvent( this, tonoArgs );
}

/**
BizCuffPulseEvent::Notify

DESCRIPTION

	Creates a cuff pulse data arguments and notifies the changes as an event to all observers.

INPUT

	data - Cuff pulse data in business context

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffPulseEvent::Notify( unsigned int data )
{
	BizCuffPulseEventArgs^ cuffArgs = gcnew BizCuffPulseEventArgs( data );

	// Now, raise the event by invoking the delegate. Pass in 
	// the object that initated the event (this) as well as data args. 
	// The call must match the signature of the handler.
	CuffPulseEvent( this, cuffArgs );
}

/**
BizCountdownTimerEvent::Notify

DESCRIPTION

	Creates a count down timer arguments and notifies the changes as an event to all observers.

INPUT

	data - Count down timer in business context

OUTPUT

	None.

RETURN

	None.

*/
void BizCountdownTimerEvent::Notify( unsigned int data )
{
	BizCountdownTimerEventArgs^ countdownTimerArgs = gcnew BizCountdownTimerEventArgs( data );

	// Now, raise the event by invoking the delegate. Pass in 
	// the object that initated the event (this) as well as data args. 
	// The call must match the signature of the handler.
	CountdownTimerEvent( this, countdownTimerArgs );
}

/**
BizCuffStateEvent::Notify

DESCRIPTION

	Creates a cuff state argument and notifies the changes as an event to all observers.

INPUT

	data - Cuff state in business context

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffStateEvent::Notify( String^ data )
{
	BizCuffStateEventArgs^ cuffStateEventArgs = gcnew BizCuffStateEventArgs( data );

	// Now, raise the event by invoking the delegate. Pass in 
	// the object that initated the event (this) as well as data args. 
	// The call must match the signature of the handler.
	CuffStateEvent( this, cuffStateEventArgs );
}

/**
BizCarotidQualityEvent::Notify

DESCRIPTION

	Creates carotid quality arguments and notifies the changes as an event to all observers.

INPUT

	data - Tonometermeter data in business context

OUTPUT

	None.

RETURN

	None.

*/
void BizCarotidQualityEvent::Notify( unsigned short signalStrength, Color signalStrengthColor, bool enableOkayButton )
{
	BizCarotidQualityEventArgs^ carotidArgs = gcnew BizCarotidQualityEventArgs( signalStrength, signalStrengthColor, enableOkayButton);

	// Now, raise the event by invoking the delegate. Pass in 
	// the object that initated the event (this) as well as data args. 
	// The call must match the signature of the handler.
	CarotidQualityEvent( this, carotidArgs );
}
