#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalSimulationFile.h"

using namespace System;
using namespace System::IO;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{
			/**
			* @interface IDalHandler
			* @brief Interface class to implement managers for EM4 and simulation devices.
			*
			* @see DalSimulationHanlder, DalDeviceHandler
			*/
			private interface class IDalHandler 
			{
				public:
					void StartCapture();
					void StopCapture();
					bool GetConnectionStatus();
					bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^deviceConfigInfo );
			};



		}
	}
}