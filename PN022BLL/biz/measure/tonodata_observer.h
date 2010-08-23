#pragma once

#include "..\events\data_events.h"

using namespace System;
using namespace System::Threading;

using namespace DataAccess;

namespace Biz {
	public ref class TonoDataObserverStub : Object
	{
	public:
		// Create a TonoDataHandler to handle the tonometer data events. 
		TonoDataObserverStub( DalTonoDataEvent^ tonoDataRaw );

		property BizTonoDataEvent^ tonoDataBiz; //forward Tonometer data from Biz
		void Display();

	private:
		DalTonoDataEvent^ tonoDataRaw; // to observe Tonometer raw data
		void Update(Object^ sender, DalTonoDataArgs^ e);
		Mutex lockData;
		unsigned int dataCaptured;
		bool gotData;

	};
}

