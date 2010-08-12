/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_meter_data_stub.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of meter data stub classes.
*/

#pragma once

using namespace System;

namespace DataAccess {
	// FireEventArgs: a custom event inherited from EventArgs.
	public ref class DalTonoDataEventArgs: public EventArgs
	{
	public:
	   DalTonoDataEventArgs( unsigned short data )
	   {
		  this->data = data;
	   }
	   unsigned short data;
	};
	// Class with a function that creates the eventargs and initiates the event
	public ref class DalTonoData
	{
	public:
	   // Events are handled with delegates, so we must establish a DalTonoDataHandler
	   // as a delegate:
	   delegate void TonoDataEventHandler(Object^ sender, DalTonoDataEventArgs^ tde );

	   // Now, create a public event "DalTonoDataEvent" whose type is our DalTonoDataEventHandler delegate. 
	   event TonoDataEventHandler^ TonoDataEvent;

	   // This will be the starting point of our event-- it will create DalTonoDataEventArgs,
	   // and then raise the event, passing DalTonoDataEventArgs. 
	   void Notify( unsigned int data );
	};
}
