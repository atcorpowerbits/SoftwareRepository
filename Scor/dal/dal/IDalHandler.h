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
					/*static property unsigned long currentCuffStatusFlag;
					static property unsigned long currentErrorAlarmFlags;*/
			
					bool StartCapture(int captureTime, int samplingRate); //parametrized method
					
					bool StartCapture();//TODO:STUB
					bool StopCapture();
					bool GetConnectionStatus();
					bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, DalDeviceConfigUsageStruct ^%deviceConfigInfo );
					String^ GetErrorAlarmSource();

					//It should not be called when device is in simulation.
					//so we are removing from the interface	
					//int FindModule(String^ comPort);

					bool CheckIfDeviceIsConnected();
					 bool SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					bool SetPressure(int newPressure, EM4CuffBoard cuffBoard);
					String^ GetSavedFileName();
			};

		}
	}
}



