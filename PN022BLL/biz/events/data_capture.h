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
		virtual void Dispatch() {};

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

		property BizTonoDataEvent^ tonoDataBiz; //tonometer data to be dispatched
		virtual void Dispatch() override;

	private:
		DalTonoDataEvent^ tonoDataRaw; // to observe tonometer raw data from DAL
		void Update(Object^ sender, DalTonoDataArgs^ e);
	};

	public ref class BizCuffPulseCapture : BizCapture
	{
	public:
		BizCuffPulseCapture(BizBuffer^ buffer);

		property BizCuffPulseEvent^ cuffPulseBiz; //cuff pulse data to be dispatched
		virtual void Dispatch() override;

	private:
		DalCuffPulseEvent^ cuffPulseRaw; // to observe cuff pulse raw data from DAL
		void Update(Object^ sender, DalCuffPulseArgs^ e);
	};
}

