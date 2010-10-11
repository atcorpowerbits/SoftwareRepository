/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	capture.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Capture classes.
*/

#pragma once

#include <data_events.h>
#include <buffer.h>

using namespace System;

using namespace DataAccess;

namespace Biz {
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

		property BizTonometerDataEvent^ tonometerDataBiz; //tonometer data to be dispatched
		virtual void Dispatch() override;

	private:
		void Update(Object^ sender, DalTonometerDataEventArgs^ e);
		DalTonometerDataEvent^ tonometerDataRaw; // to observe tonometer raw data from DAL
	};

	public ref class BizCuffPulseCapture : BizCapture
	{
	public:
		BizCuffPulseCapture(BizBuffer^ buffer);

		property BizCuffPulseEvent^ cuffPulseBiz; //cuff pulse data to be dispatched
		virtual void Dispatch() override;

	private:
		void Update(Object^ sender, DalCuffPulseEventArgs^ e);
		DalCuffPulseEvent^ cuffPulseRaw; // to observe cuff pulse raw data from DAL
	};

	public ref class BizCountdownCapture : BizCapture
	{
	public:
		BizCountdownCapture(BizBuffer^ buffer);

		property BizCountdownEvent^ countdownBiz; //countdown data to be dispatched
		virtual void Dispatch() override;

	private:
		void Update(Object^ sender, DalCountdownEventArgs^ e);
		DalCountdownEvent^ countdownRaw; // to observe countdown raw data from DAL
	};
}

