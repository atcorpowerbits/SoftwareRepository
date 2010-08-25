// dal_stub.h

#pragma once

using namespace System;

namespace DataAccess {
	// Some forward declarations
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
		void SimulateCaptureData();
		void StopSimulation();
		void SimulateCaptureOneShot();

		DalTonoDataEvent^ FindTonoData();
		DalCuffPulseEvent^ FindCuffPulse();

	protected:
		DalFacade(void);
	private:
		static DalFacade^ _instance;
		DalModule^ _module;
		unsigned int captureDataType;
	};
}
