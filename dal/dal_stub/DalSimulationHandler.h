#include "stdafx.h"
#include "IDalHandler.h"

using namespace System;
using namespace System::IO;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

/**
			* @class DalSimulationHandler
			* @brief Class to operate in simulation mode. Holds references to simulation file handles. 
			*/
			private ref class DalSimulationHandler : public IDalHandler 
			{
				private:
					DalSimulationFile^ _simulationFile1;
					DalSimulationFile^ _simulationFile2;
					Timers::Timer ^captureTimer;
					void OnTimerGetValuesAndRaiseEvents();
				public:
					DalSimulationHandler();
					virtual void StartCapture();
					virtual void StopCapture();
					virtual bool GetConnectionStatus();
					virtual bool GetConfigurationInfo(DalDeviceConfigUseageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct deviceConfigInfo );

			};
		}
	}
}