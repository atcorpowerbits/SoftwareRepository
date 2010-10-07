/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	data_events.cpp
	
	Author       :  Victor Aung

    Description  :	Business data event classes
*/

#include "StdAfx.h"
#include "data_events.h"

namespace Biz {
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
		BizCuffPulseArgs^ cuffArgs = gcnew BizCuffPulseArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as data args. 
		// The call must match the signature of the handler.
		CuffPulseEvent( this, cuffArgs );
	}

	/**
	BizCountdownEvent::Notify

	DESCRIPTION

		Creates a count down timer arguments and notifies the changes as an event to all observers.
	
	INPUT
	
		data - Count down timer in business context
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizCountdownEvent::Notify( unsigned int data )
	{
		BizCountdownArgs^ countdownArgs = gcnew BizCountdownArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as data args. 
		// The call must match the signature of the handler.
		CountdownEvent( this, countdownArgs );
	}
}
