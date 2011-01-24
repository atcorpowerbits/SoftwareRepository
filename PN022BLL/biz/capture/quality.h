/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	quality.h
	
	Author       :  Paul McBryde

    Description  :	DECLARATION of Business Logic Layer Quality classes.
*/

#pragma once

#include <data_events.h>
#include <buffer.h>
#include <biz_namespace.h>

using namespace System;

START_BIZ_NAMESPACE
public ref class BizQuality abstract
{
public:
	virtual void Reset() {};
	virtual void Update() {};

protected:
	BizQuality() {};
	property BizBuffer^ buffer;							// A buffer strategy to buffer the captured data
	property unsigned short sampleRate;					// The timing of the captured data
};

public ref class BizCarotidQuality : BizQuality
{
public:
	BizCarotidQuality(BizBuffer^ buffer, unsigned short sampleRate);
	virtual void Reset() override;
	virtual void Update() override;
	//property BizCarotidQualityEvent^ carotidQualityBiz; // Quality data to be dispatched

private:
	void Update(Object^ sender, BizTonometerDataEventArgs^ e);
	//property BizTonometerDataEvent^ carotidData;		// To observe tonometer data from Biz
	property unsigned short counter;					// To keep track of when to dispatch quality data
};

// A class to monitor femoral cuff data quality
public ref class BizFemoralQuality : BizQuality
{
public:
	BizFemoralQuality(BizBuffer^ buffer, unsigned short sampleRate);
	virtual void Reset() override;
	virtual void Update() override;

private:
	void Update(Object^ sender, BizCuffPulseEventArgs^ e);
	property unsigned short counter;					// To keep track of when to dispatch quality data
};
END_BIZ_NAMESPACE
