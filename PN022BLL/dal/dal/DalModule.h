/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalModule.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalModule class.
*/

#pragma once


#include "stdafx.h"
#include "DalCommon.h"
#include "IDalHandler.h"
#include "DalDeviceHandler.h"
#include "DalEventContainer.h"
#include "DalSimulationFile.h"
#include "DalSimulationHandler.h"

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
                // constant declarations
                static const unsigned int DAL_NULLCOMMPORT_ERR      = 303;  //TODO:STUB
                static const unsigned int DAL_SIMULATION            = 10056;  //TODO:STUB

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
				void StartCapture(); //TODO:STUB
				void StartCapture(int captureTime, int samplingRate);

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
				bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											DalDeviceConfigUsageStruct ^deviceConfigInfo ); 

				/**
				* Stub method. Returns the name of the first comm port on which the EM4 device is connected. @n
				* Should only be used for DalDeviceHandler
				*
				* @return	The name of the first comm port where the electronic device is connected.
				* 
				* @warning	This method has not been implemented. It is a stub.
				*/
				String^ FindModule();

				// Returns the PWV measurement counter stored in the firmware
				bool GetPWVMeasurementCounter( unsigned short% count); //TODO:STUB

				// Sets the PWV measurement counter stored in the firmware
				bool SetPWVMeasurementCounter( unsigned short count); //TODO:STUB

				property bool measurementCounterTest;

				String^ GetErrorAlarmSource(); 
			};
		}
	}
}