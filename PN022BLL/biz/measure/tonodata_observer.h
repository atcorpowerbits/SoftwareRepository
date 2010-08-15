#pragma once

using namespace System;
using namespace DataAccess;

namespace Biz {
	ref class TonoDataObserver : Object
	{
	public:
	   // Create a TonoDataHandler to handle the tonometer data events. 
	   TonoDataObserver( DalTonoDataEvent^ tonoDataRaw );

	private:
		DalTonoDataEvent^ tonoDataRaw; // to observe Tonometer raw data
		void UpdateTonometerData(Object^ sender, DalTonoDataArgs^ e);

	};
}

