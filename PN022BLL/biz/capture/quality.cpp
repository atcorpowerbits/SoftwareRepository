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

	buffer,
	carotidData,
	sampleRate. 

OUTPUT

	None.

RETURN

	None.

*/		
BizCarotidQuality::BizCarotidQuality(BizBuffer^ buffer, BizTonometerDataEvent^ carotidData, unsigned short sampleRate)
{
	this->buffer = buffer;
	this->carotidData = carotidData;
	this->sampleRate = sampleRate;

	// Create a tonometer business data subject
	carotidQualityBiz = gcnew BizCarotidQualityEvent;

	// Attach the handler to observe tonometer data event from Biz
	carotidData->TonometerDataEvent += gcnew BizTonometerDataEvent::BizTonometerDataEventHandler( this, &BizCarotidQuality::Update);  

	Reset();
}
/**
Update

DESCRIPTION

	Process the carotid quality update,
	Notify the carotid quality event when the quality changes.

INPUT

	sender - Subject which is sending the update event,
	e - Event arguments where tonometer data is passed,
	buffer,
	bufferSize,
	startIndex,
	endIndex,
	sampleRate.

OUTPUT

	signalMinimum,
	signalMaximum,
	signalStrengthColor,
	enableOkayButton.

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
	
	counter++;
	counter %= QUALITY_UPDATE_INTERVAL * sampleRate;
	if ( counter == 0 )
	{
		buffer->ReadBuffer( signal, bufferSize, startIndex, endIndex );
		if ( startIndex != endIndex )
		{
			bufferSize = endIndex;
		}
		BizMath::MinimumMaximumInArray( signal, bufferSize, signalMinimum, signalMaximum );
		signalHeight = signalMaximum - signalMinimum;
		if ( signalMinimum > MINIMUM_TONOMETER_BASELINE )
		{
			if ( signalHeight >= TONOMETER_SIGNAL_STRENGTH_GOOD )
			{
				signalStrengthColor = Color( Color::Green );
			}
			else if ( signalHeight >= TONOMETER_SIGNAL_STRENGTH_POOR )
			{
				signalStrengthColor = Color( Color::Yellow );
			}
			if ( startIndex == endIndex && 
				signalHeight > MINIMUM_TONOMETER_SIGNAL_STRENGTH )
			{
				enableOkayButton = true;
			}
		}
		carotidQualityBiz->Notify( signalMinimum, signalMaximum, signalStrengthColor, enableOkayButton );
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
