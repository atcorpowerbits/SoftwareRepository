// dal_stub.h

#pragma once

using namespace System;

namespace DataAccess {
	ref class DalMeter; // needed for forward declaration
	ref class DalTonoData; // needed for forward declaration

	public ref class DalFacade
	{
	public:
		static DalFacade^ DalFacade::Instance();
		bool StartPWV();
		void DispatchCaptureData();

//?		DalMeter^ GetMeter() { return meter; };
		DalTonoData^ FindTonoData();

	protected:
		DalFacade(void);
	private:
		static DalFacade^ _instance;
		DalMeter^ meter;
	};
}
