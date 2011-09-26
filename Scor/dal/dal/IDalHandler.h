/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      IDalHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      IDalHandler interface file.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"


using namespace System;
using namespace System::Timers;

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
			
					/**
					* Start the data capture fromt the device. @n
					* Creates a buffer suitable for the specified time and sampling rate.
					* @param[in]	captureTime	the time frame in seconds for the capture window
					* @param[in]	samplingRate	The number of samples per second
					* @return A boolean value indicating succes of the operation
					*
					*/
					bool StartCapture(int captureTime, int samplingRate); //parametrized method
					
					/**
					* Stops an ongoing data capture.
					*
					* @return A boolean value inidcating the status of the operation.
					*/
					bool StopCapture();
					
					/**
					* Returns the connection status. ie if device is connected or not on the given commport.
					*
					* @return A boolean value indicating if the device is connected or not.
					*/
					bool GetConnectionStatus();
					
					/**
					* Gets thhe configuration info of the rdevice.
					*
					* @param[in] deviceConfigItem	The configuration item whose information is requested.
					* @param[in,out]	deviceConfigInfo	The structure to return the configuration item information.
					*/
					bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, DalDeviceConfigUsageStruct ^%deviceConfigInfo );
					
					/**
					* Returns the name of the last error or alarm source
					* @return	A string contianing the name of the source
					*/
					String^ GetAlarmSource(DalAlarmSource% translatedAlarmSource);

					/**
					* Checks if the device is connected on the port specified in conifg
					* @return	@c true if device is present on the same port. @c false otherwise
					*/
					bool CheckIfDeviceIsConnected();
  				    
					/**
					* Dumps the tonometer and cuff data to a backup file @n
					* Obtain the name using @c GetSavedFileName
					* @param[in]	tonometerData	Array with tonometer data values
					* @param[in]	cuffPulse	Array with cuff pulse data values
					* @param[in]	bufferSize	The size of the buffer to be dumped
					* @return	 @c true if the operation was successful
					*/
					bool SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					/**
					* Dumps the tonometer and cuff data to a backup file @n
					* Obtain the name using @c GetSavedFileName
					* @param[in]	cuffPulse	Array with cuff pulse data values
					* @param[in]	bufferSize	The size of the buffer to be dumped
					* @return	 @c true if the operation was successful
					*/
					bool SaveCaptureData(array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					/**
					* Returns the name and filepath of the dump file saved by @c SaveCaptureData
					* @return	The filepath of the saved file
					* @see	SaveCaptureData
					* @warning	This method can only be called once after SaveCaptureData() is called.
					*			Calling it a second time results in a blank string being returned.
					*/
					String^ GetSavedFileName();

					/**
					* Sets the pressure value of the EM4 cuff.
					*
					* @param[in]	newPressure	The pressure to set
					* @param[in]	cuffBoard	The board on which the pressure is set
					*
					* @return	@c true if the operation succeded
					*/
					bool SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard);
					
					
					/**
					* Sets the EM4 mode to Idle mode
					*
					* @return A boolean value indicating the status of the operation
					*/
					bool SetIdleMode();

					//TS Stub
					bool IsCuffDeflated();

					void CloseFiles(); 

					//TS STUB
					bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure);
					bool StartBP(DalNIBPMode nibpMode);
					bool FinishBP();
					bool AbortBP();

			};

		}
	}
}



