/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_meter_data_stub.cpp
	
	Author       :  Victor Aung

    Description  :	Meter Data stub classes
*/

#include "StdAfx.h"
#include "dal_meter_data_stub.h"

namespace DataAccess {
	void DalTonoData::Notify( unsigned int data )
	{
		DalTonoDataEventArgs^ tonoArgs = gcnew DalTonoDataEventArgs( data );

		// Now, raise the event by invoking the delegate. Pass in 
		// the object that initated the event (this) as well as FireEventArgs. 
		// The call must match the signature of FireEventHandler.
		TonoDataEvent( this, tonoArgs );
	}
}
