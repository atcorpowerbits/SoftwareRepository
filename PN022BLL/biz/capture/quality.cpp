/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	quality.cpp
	
	Author       :  Paul McBryde

    Description  :	Business Logic Layer Quality classes.
*/

#include "StdAfx.h"
#include "quality.h"
#include <biz_namespace.h>
#include <math_library.h>

using namespace System::Threading;
using namespace BIZ_NAMESPACE;

/**
BizCarotidQuality

DESCRIPTION

	Constructor

INPUT

	buffer - incoming carotid data buffer,
	sampleRate - timing of the carotid data. 

OUTPUT

	None.

RETURN

	None.

*/		
BizCarotidQuality::BizCarotidQuality(BizBuffer^ buffer, unsigned short sampleRate)
{
	this->buffer = buffer;
	//this->carotidData = carotidData;
	this->sampleRate = sampleRate;

	// Create a tonometer business data subject
	//carotidQualityBiz = gcnew BizCarotidQualityEvent;

	// Attach the handler to observe tonometer data event from Biz
	//carotidData->TonometerDataEvent += gcnew BizTonometerDataEvent::BizTonometerDataEventHandler( this, &BizCarotidQuality::Update);  
	BizEventContainer::Instance->OnBizTonometerDataEvent += gcnew BizTonometerDataEventHandler(this, &BizCarotidQuality::Update);

	BizCarotidQuality::Reset();
}
/**
Update

DESCRIPTION

	Process the carotid quality update,
	Notify the carotid quality event when the quality changes.

INPUT

	sender - Subject which is sending the update event,
	e - Event arguments where tonometer data is passed,
	BizCarotidQuality::buffer - incoming carotid data buffer,
	BizCarotidQuality::sampleRate - timing of the carotid data.

OUTPUT

	BizCarotidQualityEventHandler::signalMinimum - signal maximum, used to calculate signal strength and scale the display
	BizCarotidQualityEventHandler::signalMaximum - signal minimum, used to calculate signal strength and scale the display
	BizCarotidQualityEventHandler::signalStrengthColor - colour to be displayed on the quality indicator
	BizCarotidQualityEventHandler::enableOkayButton - can the user calculate a report or not.

RETURN

	None.

*/		
void BizCarotidQuality::Update( Object^ sender, BizTonometerDataEventArgs^ e )
{
	unsigned int bufferSize;
	array< unsigned short >^ signal;
	unsigned short startIndex; 
	unsigned short endIndex; 
	unsigned short signalMinimum;
	unsigned short signalMaximum;
	unsigned short signalHeight;		
	
	Color signalStrengthColor = Color( Color::Red );
	bool enableOkayButton = false;
	
	// Update the counter first so we ignore the first interval and send the -
	// first notification once we have meaningful information to send
	counter++;
	
	// Calculate the quality every second. There's no need to update every sample
	counter %= QUALITY_UPDATE_INTERVAL * sampleRate;
	if ( counter == 0 )
	{
		// Read the carotid signal buffer 
		signal = buffer->ReadBuffer( bufferSize, startIndex, endIndex );
		
		// If the buffer is not full, calculate up to the last sample
		if ( startIndex != endIndex )
		{
			bufferSize = endIndex;
		}
		
		// Calculate the range
		BizMath::MinimumMaximumInArray( signal, bufferSize, signalMinimum, signalMaximum );
		signalHeight = signalMaximum - signalMinimum;
		
		// If the minimum is below the baseline, the signal is not valid (the tonometer may -
		// have been disconnected) so the Okay button shall remain disabled and the quality -
		// indicator Red
		if ( signalMinimum > MINIMUM_TONOMETER_BASELINE )
		{
			// Determine the quality indicator colour
			if ( signalHeight >= TONOMETER_SIGNAL_STRENGTH_GOOD )
			{
				signalStrengthColor = Color( Color::Green );
			}
			else if ( signalHeight >= TONOMETER_SIGNAL_STRENGTH_POOR )
			{
				signalStrengthColor = Color( Color::Yellow );
			}
			
			// Enable the Okay button if the buffer is full and the range is above the minimum
			if ( startIndex == endIndex && 
				signalHeight > MINIMUM_TONOMETER_SIGNAL_STRENGTH )
			{
				enableOkayButton = true;
			}
		}
		//carotidQualityBiz->Notify( signalMinimum, signalMaximum, signalStrengthColor, enableOkayButton );
		BizEventContainer::Instance->OnBizCarotidQualityEvent(this, gcnew BizCarotidQualityEventArgs( signalMinimum, signalMaximum, signalStrengthColor, enableOkayButton ));
	}
}

/**
Reset

DESCRIPTION

	Reset the quality data.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizCarotidQuality::Reset()
{
	counter = 0;
}
