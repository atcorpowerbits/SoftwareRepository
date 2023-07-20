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
protected:
	BizQuality() {};
	property BizBuffer^% buffer;
};

public ref class BizCarotidQuality : BizQuality
{
public:
	BizCarotidQuality(BizBuffer^ buffer);

	property BizCarotidQualityEvent^ carotidQualityBiz; //tonometer data to be dispatched

private:
	void Update(Object^ sender, BizTonometerDataEventArgs^ e);
};

END_BIZ_NAMESPACE
