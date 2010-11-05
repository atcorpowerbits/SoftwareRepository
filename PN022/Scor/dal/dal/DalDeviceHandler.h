#pragma once

#include "stdafx.h"
#include "IDalHandler.h"

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalDeviceHandler
			* @brief Class to handle EM4 device operation.
			*/
			private ref class DalDeviceHandler : public IDalHandler 
			{
				private:
					String ^_commPort; //The current comm port name. Can be a real port or simulation
				public:
					/**
					* Constructor for the class.
					*/
					DalDeviceHandler(); 

					/**
					* Parametrized constructor for the class. @n
					* Initializes the class using the specified comm port.
					*
					* @param[in] commPort	The com port for the EM4 device
					*/
					DalDeviceHandler(String^ commPort);

					/**
					* Start the data capture fromt the device.
					*
					* @warning This is a stub only. Not yet implemented.
					*/
					virtual void StartCapture();

					/**
					* Stops an ongoing data capture.
					*
					* @warning This is a stub only. Not yet implemented.
					*/
					virtual void StopCapture();

					/**
					* Returns the connection status. ie if device is connected or not on the given commport.
					*
					* @warning This is a stub only. Not yet implemented.
					*/
					virtual bool GetConnectionStatus();

					/**
					* Gets thhe configuration info of the rdevice.
					*
					* @param[in] deviceConfigItem	The configuration item whose information is requested.
					* @param[in,out]	deviceConfigInfo	The structure to return the configuration item information.
					* @warning This is a stub only. Not yet implemented.
					*/
					virtual bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^deviceConfigInfo );
			};
		}
	}
}