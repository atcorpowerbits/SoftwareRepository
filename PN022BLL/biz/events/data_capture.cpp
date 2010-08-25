
#include "StdAfx.h"
#include <data_capture.h>

using namespace System::Threading;

namespace Biz {
	/**
	BizTonoDataCapture

	DESCRIPTION

		Constructor

	INPUT
	
		buffer - A buffer strategy to buffer the captured data
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	BizTonoDataCapture::BizTonoDataCapture(BizBuffer^ buffer)
	{
		_buffer = buffer;
		tonoDataRaw = DalFacade::Instance()->FindTonoData();

		// Attach the handler to observe tonometer data event from DAL
		tonoDataRaw->TonoDataEvent += 
			gcnew DalTonoDataEvent::DalTonoDataEventHandler( this, &BizTonoDataCapture::Update );

		// Create a tonometer business data subject
		tonoDataBiz = gcnew BizTonoDataEvent;
	}
	/**
	Update

	DESCRIPTION

		Process the tonometer data update.
		Note that it shouldn't display the data as the update is not called from a GUI thread.
	
	INPUT
	
		sender - Subject which is sending the update event.
	
		e - Event arguments where a tonometer data is passed.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	void BizTonoDataCapture::Update( Object^ sender, DalTonoDataArgs^ e )
	{
		// Keep it in the buffer
		_buffer->Append(e->data);

	}
	/**
	Dispatch

	DESCRIPTION

		Dispatch tonometer data if new data has arrived.
	
	INPUT
	
		None.

	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	void BizTonoDataCapture::Dispatch()
	{
		unsigned short^ readData = gcnew unsigned short;

		// dispatch tonometer data if it's arrived.
		if (_buffer->ReadNext(readData))
		{
			tonoDataBiz->Notify(*readData);
		}
	}

	/**
	BizCuffPulseCapture

	DESCRIPTION

		Constructor

	INPUT
	
		buffer - A buffer strategy to buffer the captured data
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	BizCuffPulseCapture::BizCuffPulseCapture(BizBuffer^ buffer)
	{
		_buffer = buffer;
		cuffPulseRaw = DalFacade::Instance()->FindCuffPulse();

		// Attach the handler to observe tonometer data event from DAL
		cuffPulseRaw->CuffPulseEvent += 
			gcnew DalCuffPulseEvent::DalCuffPulseEventHandler( this, &BizCuffPulseCapture::Update );

		// Create a tonometer business data subject
		cuffPulseBiz = gcnew BizCuffPulseEvent;
	}

	/**
	Update

	DESCRIPTION

		Process the tonometer data update.
		Note that it shouldn't display the data as the update is not called from a GUI thread.
	
	INPUT
	
		sender - Subject which is sending the update event.
	
		e - Event arguments where a tonometer data is passed.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	void BizCuffPulseCapture::Update( Object^ sender, DalCuffPulseArgs^ e )
	{
		// Keep it in the buffer
		_buffer->Append(e->data);

	}

	/**
	Dispatch

	DESCRIPTION

		Dispatch tonometer data if new data has arrived.
	
	INPUT
	
		None.

	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/		
	void BizCuffPulseCapture::Dispatch()
	{
		unsigned short^ readData = gcnew unsigned short;

		// dispatch tonometer data if it's arrived.
		if (_buffer->ReadNext(readData))
		{
			cuffPulseBiz->Notify(*readData);
		}
	}
}