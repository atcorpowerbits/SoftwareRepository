#include "stdafx.h"
#include "IDalHandler.h"

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalDeviceHandler
			* @brief Class to operate EM4 device.
			*/
			private ref class DalDeviceHandler : public IDalHandler 
			{
				private:
					String ^_commPort;
				public:
					DalDeviceHandler();
					virtual void StartCapture();
					virtual void StopCapture();
					virtual bool GetConnectionStatus();
					virtual bool GetConfigurationInfo(DalDeviceConfigUseageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct deviceConfigInfo );
			};
		}
	}
}