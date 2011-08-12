/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      IDalHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      IDalHandler interface and DalStatusHandler class header file.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalSimulationFile.h"
#include "DalCuffStateMachine.h"

using namespace System;
using namespace System::IO;

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
					bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, DalDeviceConfigUsageStruct ^deviceConfigInfo );
					String^ GetErrorAlarmSource();

					int FindModule(String^ comPort);
					bool CheckIfDeviceIsConnected();
					virtual bool SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					bool SetPressure(int newPressure, EM4CuffBoard cuffBoard);
					String^ GetSavedFileName();
			};



			/**
			* @class DalStatusHandler
			* @brief common functions including status check for EM4 and simulation
			*
			* @see DalSimulationHanlder, DalDeviceHandler
			*/
			private ref class DalStatusHandler
			{
				protected:
					static unsigned long _currentCuffStatusFlag;  /**< current cuff status flags*/
					 static unsigned long _currentEAStatusFlag; /**< current error alarm  status flags*/
					 static unsigned long _currentEASourceFlag; /**< current error alarm  source flags*/

					 static String^ dalErrorAlarmSourceName; //To store the source name
			
					static String^ _savedDataFilePath; /**< the path and filename where the waveform dump has been placed*/
				
				public:
					/**
					* Returns the source of alarm or error
					* @return	The name of the error/alarm source 
					*/
					virtual String^ GetErrorAlarmSource(); 

					/**
					* Checks if there is a change in cuff status. 
					* @param	newCuffStatusFlags	New cuff status flag to compare with the current value
					* @return	status of the operation
					*/
					static bool CheckCuffStatusFlagsChanged(const unsigned long newCuffStatusFlags); 

					/**
					* Checks if there is a change in error/alarm status. 
					* @param	newEAStatusFlag	New error/alarm status flag to compare with the current value
					* @return	status of the operation
					*/
					static bool CheckEAStatusFlagChanged(unsigned long newEAStatusFlag); 

					/**
					* Returns the error source name  
					* @param	sourceFlags	Error/alarm source flag
					* @return	Name of the error source
					*/
					static String^ MapErrorSourceToString(unsigned long sourceFlags); 

					/**
					* Returns the alarm source name  
					* @param	sourceFlags	Error/alarm source flag
					* @return	Name of the alarm source
					*/
					static String^ MapAlarmSourceToString(unsigned long sourceFlags); 

					/**
					* Translates the cuff status flag bits into a state as listed in DalCuffStateFlags
					* @param	statusFlags	cuff status bits source flag
					* @return	The translated cuff state
					*/
					static DalCuffStateFlags TranslateCuffStatusBits(unsigned long statusFlags);
					/**
					* Translates the error/alarm status flag bits into an error/alarm state as listed in DalErrorAlarmStatusFlag
					* @param	statusFlags	error/alarm status bits source flag
					* @return	The translated state
					*/
					static DalErrorAlarmStatusFlag TranslateErrorAlarmStatusBits(unsigned long statusFlags); 
			};

		}
	}
}



