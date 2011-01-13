/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalDeviceHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalDeviceHandler class header file.
*/

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
					unsigned long _currentStatusFlags;
					unsigned long _currentErrorAlarmFlags;
				
			
				public:
					property unsigned long currentStatusFlags 
					{
						virtual unsigned long get()
						{
							return _currentStatusFlags;
						}

						virtual void set(unsigned long value)
						{
							_currentStatusFlags= value;
						}
					};

					property unsigned long currentErrorAlarmFlags 
					{
						virtual unsigned long get()
						{
							return _currentErrorAlarmFlags;
						}

						virtual void set(unsigned long value)
						{
							_currentErrorAlarmFlags= value;
						}
					};

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
					virtual void StartCapture(); //TODO:STUB
					virtual void StartCapture(int captureTime, int samplingRate);

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

					virtual bool CheckStatusFlagsChanged(unsigned long newStatusFlags); 
					virtual bool CheckErrorAlarmFlagsChanged(unsigned long newErrorAlarmFlags); 
					virtual String^ MapErrorSourceToString(unsigned long sourceFlags); 
					virtual String^ MapAlarmSourceToString(unsigned long sourceFlags); 
					virtual String^ GetErrorAlarmSource(); 
					virtual DalCuffStateFlags TranslateCuffStatusBits(unsigned long statusFlags); 
			};
		}
	}
}