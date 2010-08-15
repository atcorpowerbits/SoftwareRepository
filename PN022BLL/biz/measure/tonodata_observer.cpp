
#include "StdAfx.h"
#include "tonodata_observer.h"
#include <iostream> // for cout???

using namespace System;  // for cout???

namespace Biz {
	TonoDataObserver::TonoDataObserver( DalTonoDataEvent^ tonoDataRaw )
	{
		// Attach as an observer to Tonometer data event update
		tonoDataRaw->TonoDataEvent += gcnew DalTonoDataEvent::TonoDataEventHandler( this, &TonoDataObserver::UpdateTonometerData );
	}
	/**
	UpdateTonoData

	DESCRIPTION

		Update for this observer when a raw tonometer data is available.
	
	INPUT
	
		sender - Subject which is sending the update event.
	
		e - Event arguments where a tonometer data is passed.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	void TonoDataObserver::UpdateTonometerData( Object^ sender, DalTonoDataArgs^ e )
	{
		// TBD: Now, act in response to the update event.
		Console::WriteLine( "This tonometer data is {0}", e->data );
	}
}