/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	capture.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Capture classes.
*/

#include "StdAfx.h"
#include <capture.h>
#include <session.h>
#include <measure_pwv.h>
#include <cuff_state.h>
#include <biz_namespace.h>

using namespace System::Threading;

START_BIZ_NAMESPACE
/**
BizTonometerDataCapture

DESCRIPTION

	Constructor

INPUT

	buffer - A buffer strategy to buffer the captured data

OUTPUT

	None.

RETURN

	None.

*/		
BizTonometerDataCapture::BizTonometerDataCapture(BizBuffer^ buffer)
{
	this->buffer = buffer;

	// Attach the handler to observe tonometer data event from DAL
	DalEventContainer::Instance->OnDalTonometerDataEvent += gcnew DalTonometerDataEventHandler(this, &BizTonometerDataCapture::Update);

	// Create a tonometer business data subject
//	tonometerDataBiz = gcnew BizTonometerDataEvent;
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
void BizTonometerDataCapture::Update( Object^ sender, DalTonometerDataEventArgs^ e )
{
	// Keep it in the buffer
	buffer->Append(e->data);

}
/**
Dispatch

DESCRIPTION

	Dispatch tonometer data as many as arrived.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizTonometerDataCapture::Dispatch()
{
	unsigned short readData;

	// dispatch tonometer data as many as arrived.
	while (buffer->ReadNext(readData))
	{
//		tonometerDataBiz->Notify(readData);
		BizEventContainer::Instance->OnBizTonometerDataEvent(this, gcnew BizTonometerDataEventArgs(readData));	
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
	this->buffer = buffer;

	// Attach the handler to observe cuff pulse data event from DAL
	DalEventContainer::Instance->OnDalCuffPulseEvent += gcnew DalCuffPulseEventHandler(this, &BizCuffPulseCapture::Update);

	// Create a cuff pulse business data subject
	cuffPulseBiz = gcnew BizCuffPulseEvent;
}

/**
Update

DESCRIPTION

	Process the cuff pulse data update.
	Note that it shouldn't display the data as the update is not called from a GUI thread.

INPUT

	sender - Subject which is sending the update event.

	e - Event arguments where a cuff pulse data is passed.

OUTPUT

	None.

RETURN

	None.

*/		
void BizCuffPulseCapture::Update( Object^ sender, DalCuffPulseEventArgs^ e )
{
	// Keep it in the buffer
	buffer->Append(e->data);

}

/**
Dispatch

DESCRIPTION

	Dispatch cuff pulse data as many as arrived.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizCuffPulseCapture::Dispatch()
{
	unsigned short readData;

	// dispatch cuff pulse data as many as arrived.
	while (buffer->ReadNext(readData))
	{
		// TBD:: Revisit design - send zero signal when cuff is not inflated
		BizPWV^ measurePWV = (BizPWV^)BizSession::Instance()->measurement;
		if (measurePWV->cuffObserver->currentState != BizCuffInflated::Instance())
		{
			readData = 0;
		}
		cuffPulseBiz->Notify(readData);
	}
}

/**
BizCountdownCapture

DESCRIPTION

	Constructor

INPUT

	buffer - A buffer strategy to buffer the captured data

OUTPUT

	None.

RETURN

	None.

*/		
BizCountdownTimerCapture::BizCountdownTimerCapture(BizBuffer^ buffer)
{
	this->buffer = buffer;

	// Attach the handler to observe countdown data event from DAL
	DalEventContainerStub::Instance->OnDalCountdownTimerEvent += gcnew DalCountdownTimerEventHandler(this, &BizCountdownTimerCapture::Update);

	// Create a countdown business data subject
	countdownTimerBiz = gcnew BizCountdownTimerEvent;
}

/**
Update

DESCRIPTION

	Process the countdown timer update.
	Note that it shouldn't display the data as the update is not called from a GUI thread.

INPUT

	sender - Subject which is sending the update event.

	e - Event arguments where a countdown timer is passed.

OUTPUT

	None.

RETURN

	None.

*/		
void BizCountdownTimerCapture::Update( Object^ sender, DalCountdownTimerEventArgs^ e )
{
	// Keep it in the buffer
	buffer->Append(e->data);

}

/**
Dispatch

DESCRIPTION

	Dispatch countdown data as many as arrived.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizCountdownTimerCapture::Dispatch()
{
	unsigned short readData;

	// dispatch countdown data as many as arrived.
	while (buffer->ReadNext(readData))
	{
		// round to seconds
		countdownTimerBiz->Notify(readData);
	}
}
END_BIZ_NAMESPACE
