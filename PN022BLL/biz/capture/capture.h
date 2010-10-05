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
		virtual void Reset() { _buffer->Reset(); };
		virtual void Dispatch() = 0;

	protected:
/*		bool gotData;
		Mutex lockData;
		unsigned short dataCaptured;
		unsigned short bufferLength;
		unsigned short startBuffer;
		unsigned short endBuffer;
		unsigned short nextToDispatch;
*/
		BizBuffer^ _buffer;
	};

	public ref class BizTonoDataCapture : BizCapture
	{
	public:
		BizTonoDataCapture(BizBuffer^ buffer);

		void Update(Object^ sender, DalTonoDataArgs^ e);
		property BizTonoDataEvent^ tonoDataBiz; //tonometer data to be dispatched
		virtual void Dispatch() override;

	private:
		DalTonoDataEvent^ tonoDataRaw; // to observe tonometer raw data from DAL
	};

	public ref class BizCuffPulseCapture : BizCapture
	{
	public:
		BizCuffPulseCapture(BizBuffer^ buffer);

		void Update(Object^ sender, DalCuffPulseArgs^ e);
		property BizCuffPulseEvent^ cuffPulseBiz; //cuff pulse data to be dispatched
		virtual void Dispatch() override;

	private:
		DalCuffPulseEvent^ cuffPulseRaw; // to observe cuff pulse raw data from DAL
	};

	public ref class BizCountdownCapture : BizCapture
	{
	public:
		BizCountdownCapture(BizBuffer^ buffer);

		void Update(Object^ sender, DalCountdownArgs^ e);
		property BizCountdownEvent^ countdownBiz; //countdown data to be dispatched
		virtual void Dispatch() override;

	private:
		DalCountdownEvent^ countdownRaw; // to observe countdown raw data from DAL
	};
}

