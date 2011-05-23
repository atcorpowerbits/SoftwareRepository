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
			
					bool StartCapture(int captureTime, int samplingRate); //parametrized method
					
					//bool StartCapture();//TODO:STUB Non parametrized method removed from Dal Module
					bool StopCapture();
					bool GetConnectionStatus();
					bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, DalDeviceConfigUsageStruct ^%deviceConfigInfo );
					//String^ GetErrorAlarmSource();
					String^ GetAlarmSource();

					bool CheckIfDeviceIsConnected();
  				    bool SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					bool SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard);
					String^ GetSavedFileName();

					/**
					* Sets the EM4 mode to Idle mode
					*
					* @return A boolean value indicating the status of the operation
					*/
					bool SetIdleMode();
			};

		}
	}
}



