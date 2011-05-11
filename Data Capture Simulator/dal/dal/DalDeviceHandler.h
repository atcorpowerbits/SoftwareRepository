/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalDeviceHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalDeviceHandler class header file.
*/

#pragma once

#include "stdafx.h"
#include "IDalHandler.h"
#include "DalCommandInterface.h"
#include "DalDataBuffer.h"


using namespace System;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalDeviceHandler
			* @brief Class to handle EM4 device operation.
			*/
			private ref class DalDeviceHandler : public IDalHandler , public DalStatusHandler
			{
				private:
					String^ _commPort; //The current comm port name. Can be a real port or simulation
					DalCommandInterface^ _commandInterface;
					CrxLogger ^logObj;
					CrxMessagingManager ^ messagingMgr;
					DalDataBuffer ^dataBufferObj; //to hold pointer to object
					
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
					* @warning This is a stub only. It is not meant to be used and is only retained for compatibility with stub.
					*/
					virtual bool StartCapture(); //TODO:STUB

					/**
					* Start the data capture fromt the device. @n
					* Creates a buffer suitable for the specified time and sampling rate.
					* @param[in]	captureTime	the time frame in seconds for the capture window
					* @param[in]	samplingRate	The number of samples per second
					* @return A boolean value indicating succes of the operation
					*
					*/
					virtual bool StartCapture(int captureTime, int samplingRate);

					/**
					* Stops an ongoing data capture.
					*
					* @warning This is a stub only. Not yet implemented.
					*/
					virtual bool StopCapture();

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

					/**
					* Returns the name of the last error or alarm source
					* @return	A string contianing the name of the source
					*/
					virtual String^ GetErrorAlarmSource() new; 

					/**
					* Looks for the EM4 module on the serial ports
					* @param[out]	comPort	The name of the port where the device was found. @n
					*				This is returned only if return value is @c 2
					* @return  An interger value indicating the  status @n
					*			@c 0: the device was not found on any port 
					*			@c 1: the device was on the same port as specified in confi
					*			@c 2: the device was found on a different port. Check @c comPort for the anem of the new port.
					*/
					virtual int FindModule(String^ comPort);

					/**
					* Checks if the device is connected on the port specified in conifg
					* @return	@c true if device is present on the same port. @c false otherwise
					*/
					virtual bool CheckIfDeviceIsConnected();

					/**
					* Checks if the device is connected on the port specified as a parameter
					* @return	@c true if device is present on the same port. @c false otherwise
					*/
					virtual bool CheckIfDeviceIsConnected(String^ comPort);
					/**
					* Sets the pressure value
					* @return	@c true if the operation succeded
					*/
					virtual bool SetPressure(int newPressure, EM4CuffBoard cuffBoard);	
					
					/**
					* Dumps the tonometer and cuff data to a backup file @n
					* Obtain the name using @c GetSavedFileName
					* @param[in]	tonometerData	Array with tonometer data values
					* @param[in]	cuffPulse	Array with cuff pulse data values
					* @param[in]	bufferSize	The size of the buffer to be dumped
					* @return	 @c true if the operation was successful
					*/
					virtual bool SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					/**
					* Returns the name and filepath of the dump file saved by @c SaveCaptureData
					* @return	The filepath of the saved file
					* @see	SaveCaptureData
					*/
					virtual String^ GetSavedFileName();
					
					/**
					* Checks if the tonometer is connected
					* @return @c true if the tonometer is connected properly
					*/
					bool CheckIfTonometerIsConnected();
					
			};
		}
	}
}