// dal_stub.h

#pragma once

using namespace System;

namespace DataAccess {
	// Some forward declaration
	ref class DalMeter; 
	ref class DalModule; 
	ref class DalTonoDataEvent;
	ref class DalCuffPulseEvent;

	public ref class DalFacade
	{
	public:
		static DalFacade^ DalFacade::Instance();
		bool StartCapture(unsigned int dataType);
		bool StopCapture();
		String^ GetFWConfig(unsigned int configType);
		void DispatchCaptureData();
		void DispatchCaptureOneShot();

//?		DalMeter^ GetMeter() { return meter; };
		DalTonoDataEvent^ FindTonoData();
		DalCuffPulseEvent^ FindCuffPulse();

	protected:
		DalFacade(void);
	private:
		static DalFacade^ _instance;
//?		DalMeter^ _meter;
		DalModule^ _module;
		unsigned int captureDataType;
	};
}
