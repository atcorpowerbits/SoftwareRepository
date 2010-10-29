/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	capture.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Capture classes.
*/

#pragma once

#include <data_events.h>
#include <buffer.h>
#include <biz_namespace.h>

using namespace System;
using namespace DAL_NAMESPACE;

START_BIZ_NAMESPACE
public ref class BizCapture abstract
{
public:
	virtual void Reset() { buffer->Reset(); };
	virtual void Dispatch() = 0;

protected:
	BizCapture() {};
	property BizBuffer^ buffer;
};

public ref class BizTonometerDataCapture : BizCapture
{
public:
	BizTonometerDataCapture(BizBuffer^ buffer);

//	property BizTonometerDataEvent^ tonometerDataBiz; //tonometer data to be dispatched
	virtual void Dispatch() override;

private:
	void Update(Object^ sender, DalTonometerDataEventArgs^ e);
};

public ref class BizCuffPulseCapture : BizCapture
{
public:
	BizCuffPulseCapture(BizBuffer^ buffer);

	property BizCuffPulseEvent^ cuffPulseBiz; //cuff pulse data to be dispatched
	virtual void Dispatch() override;

private:
	void Update(Object^ sender, DalCuffPulseEventArgs^ e);
};

public ref class BizCountdownTimerCapture : BizCapture
{
public:
	BizCountdownTimerCapture(BizBuffer^ buffer);

	 property BizCountdownTimerEvent^ countdownTimerBiz; //countdown data to be dispatched
	virtual void Dispatch() override;

private:
	void Update(Object^ sender, DalCountdownTimerEventArgs^ e);
};

END_BIZ_NAMESPACE
