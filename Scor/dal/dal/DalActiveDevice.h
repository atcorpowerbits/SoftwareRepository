/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalActiveDevice.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalActiveDevice class.
*/

#pragma once


#include "stdafx.h"
#include "DalCommon.h"
#include "IDalHandler.h"
#include "DalDeviceHandler.h"
#include "DalEventContainer.h"
#include "DalSimulationFile.h"
#include "DalSimulationHandler.h"
#include "DalStatusHandler.h"

using namespace System;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			/**
			* @class DalActiveDevice
			* @brief	Exposes main functionality for the DAL Current Device module. Singleton class.
			*/
			private ref class DalActiveDevice
			{
			private:
                static DalActiveDevice^ _instance = gcnew DalActiveDevice();

				DalActiveDevice();
				DalActiveDevice( DalActiveDevice^);
				DalActiveDevice^ operator= ( DalActiveDevice);

				static void ConfigCommsPortSettingChangeHandler(Object^ sender, CommsPortEventArgs^ args);

				/**
				* Searches all available ports  for the EM4 module
				* @param[out]	foundPortName	The name of the port on which the EM4 device was located
				* @param[in]	excludePort	The port to be excluded from the search if it has already been searched.
				*							@n It can be null
				* @return	 @c true if the operation was successful
				*/
				bool SearchAllPortsforDevice(String ^%foundPortName, String ^excludePort);
				static void SetSimulationAsCurrent(DalStreamingMode mode);
				static void SetDeviceAsCurrent(DalStreamingMode mode);


			internal:	
				static IDalHandler^ _currentDevice;  //A pointer to the current device
				
			public:
				
				/**
				* Returns the current singleton instance.
				*/
				static property DalActiveDevice^ Instance
				{
					DalActiveDevice^ get()
					{
						return DalActiveDevice::_instance;
					};
				};

				/**
				* Returns the current device.
				*/
				static property IDalHandler^ CurrentDevice
				{
					IDalHandler^ get()
					{
						//return this->_currentDevice;
						return _currentDevice;
					};
				};

				/**
				* Obtains the current com port settig from Configuration and sets the current strategy.
				*
				* @return	A boolean value specifying the success/failure of the operation.
				*/
				static bool SetDeviceStrategy();

				///**
				//* Obtains the current com port settig from Configuration and sets the current strategy.
				//* @param[in] commPort The Comm port setting.
				//*
				//* @return	A boolean value specifying the success/failure of the operation.
				//*/
				//static bool SetDeviceStrategy(String^ commPort);

				/**
				* Obtains the current com port settig from Configuration and sets the current strategy.
				* @param[in] commPort The Comm port setting.
				* @param[in] mode The streaming mode setting.
				*
				* @return	A boolean value specifying the success/failure of the operation.
				*/
				static bool SetDeviceStrategy(String ^commPort, DalStreamingMode mode);

				/**
				* Returns the name of the first comm port on which the EM4 device is connected. @n
				* Should only be used for DalDeviceHandler
				*
				* @param[out]	deviceFoundPort	The port on which the device was found
				*
				* @return	A DalFindModuleResult value specifying whether the EM4 device was found or not.
				*/
				DalFindModuleResult FindModule(String ^%deviceFoundPort);
				
				// TS stub
				void SetDeviceNull();
			};
		}
	}
}