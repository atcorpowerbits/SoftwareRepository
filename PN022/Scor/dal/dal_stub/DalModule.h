#include "stdafx.h"
#include "DalCommon.h"
#include "IDalHandler.h"

using namespace System;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalModule
			* @brief	Exposes main functionality for the DAL module. Singleton class.
			*/
			public ref class DalModule
			{
			private:
				static DalModule^ _instance = gcnew DalModule();
				DalModule();
				DalModule(const DalModule^);
				DalModule^ operator= (const DalModule);
				IDalHandler^ _currentDevice;
				CaptureType _captureDataType;
			public:
				/**
				* Returns the current singleton instance.
				*/
				static property DalModule^ Instance
				{
					DalModule^ get()
					{
						return DalModule::_instance;
					};
				};

				/**
				* Obtains the current com port settig from Configuration and sets the current strategy.
				*/
				void SetDeviceStrategy();

				/**
				* Obtains the current com port settig from Configuration and sets the current strategy.
				* @param[in] commPort The Comm port setting.
				*/
				void SetDeviceStrategy(String^ commPort);

				/**
				* Starts the data capture from the selected device.
				*/
				void StartCapture();

				/**
				* Stops the data capture from the active device.
				*/
				void StopCapture();

				/**
				* Returns the status for the current device.
				*/
				bool GetConnectionStatus();

				/**
				* Gets the configuration info for the specifed configruation item .
				* @param[in]	deviceConfigItem	The configuration item to be obtained
				* @param[in,out]	deviceConfigInfo	The structure to return the configuration info into.
				*/
				bool GetConfigurationInfo(DalDeviceConfigUseageEnum deviceConfigItem, 
											DalDeviceConfigUsageStruct ^deviceConfigInfo ); 

				String^ FindModule();
			};
		}
	}
}