
#include "StdAfx.h"
#include "tonodata_observer.h"
//?#include <iostream> // for cout???

//?using namespace System;  // for cout???

using namespace System::Threading;

namespace Biz {
	TonoDataObserverStub::TonoDataObserverStub( DalTonoDataEvent^ tonoDataRaw )
	{
		// Attach as an observer to tonometer raw data event for an update
		tonoDataRaw->TonoDataEvent += gcnew DalTonoDataEvent::DalTonoDataEventHandler( this, &TonoDataObserverStub::Update );

		// Create a tonometer business data subject
		tonoDataBiz = gcnew BizTonoDataEvent;

		gotData = false;
//?		lockData = gcnew Mutex();
	}
	/**
	Update

	DESCRIPTION

		Update this observer when a raw tonometer data is available.
		Note that it cannot display the data since it's not called on GUI thread.
		Must decouple the data from the caller, i.e. interrutpt thread from DAL. 
	
	INPUT
	
		sender - Subject which is sending the update event.
	
		e - Event arguments where a tonometer data is passed.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	void TonoDataObserverStub::Update( Object^ sender, DalTonoDataArgs^ e )
	{
		// TBD: Now, act in response to the update event.
//		Console::WriteLine( "This tonometer data is {0}", e->data );

		// proces on tonometer raw data.
		lockData.WaitOne();
		// Just copy the data for demo and flag its arrival.
		dataCaptured = e->data;
		gotData = true;
		lockData.ReleaseMutex();
	}
	void TonoDataObserverStub::Display()
	{
		// display tonometer data if it's arrived.
		lockData.WaitOne();
		if (gotData)
		{
			// forward the processed tonometer data to the observers
			tonoDataBiz->Notify(dataCaptured);
			gotData = false;
		}
		lockData.ReleaseMutex();
	}
}