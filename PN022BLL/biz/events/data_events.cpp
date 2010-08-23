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
	BizTonoDataEvent::Notify

	DESCRIPTION

		Creates a tonometer data arguments and notifies the changes as an event to all observers.
	
	INPUT
	
		data - Tonometer data in business context
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	void BizTonoDataEvent::Notify( unsigned int data )
	{
		BizTonoDataArgs^ tonoArgs = gcnew BizTonoDataArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as BizTonoDataArgs. 
		// The call must match the signature of BizTonoDataEventHandler.
		TonoDataEvent( this, tonoArgs );
	}
}