/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalStatusHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalStatusHandler class header file.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalSimulationFile.h"

using namespace System;
using namespace System::IO;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{
			
			/**
			* @class DalStatusHandler
			* @brief common functions including status check for EM4 and simulation
			*
			* @see DalSimulationHanlder, DalDeviceHandler
			*/
			private ref class DalStatusHandler
			{
				protected:
					static unsigned long _currentCuffStatusFlag = 0xFFFF;  /**< current cuff status flags*/ //TODO: clear value for all flags?
					static unsigned long _currentAlarmStatusFlag; /**< current error alarm  status flags*/
					static unsigned long _currentEASourceFlag; /**< current error alarm  source flags*/
					static unsigned long _currentUnusedStatusFlag; // use this

					//unused variable
					//static String^ dalErrorAlarmSourceName; //To store the source name
			
					static String^ _savedDataFilePath; /**< the path and filename where the waveform dump has been placed*/

					static unsigned long _newAlarmStatusBytes;  
					static unsigned long  _newTonoStatusBytes = 0xFFFF;  
					static unsigned long _newCuffStatusBytes = 0xFFFF;
					static unsigned long _newPowerUpStatusBytes, _newStopButtonStatusBytes;
					static unsigned long _newUnusedStatusBytes;
					static DalCuffStateFlags currentCuffState; //Stores the current cuffState enum value, needed for simulation

					static unsigned long _currentStatusFlag;  /**< current status flags*/
					static unsigned long _currentTonoStatusFlag = 0xFFFF;  /**< current tonometer status flags*/


					/**
					* Resets all static member variables which represents various 
					* flags to the some initial reference value.
					* Should be called when the measurement process should be started repeatedly
					*/
					static void ResetAllStaticMembers();

					/**
					* Returns a string with the name of the supply rails alarm which triggered the AS flag 
					* Called internally from GetAlarmSource().
					*/
					String^ GetSupplyRailsAlarmSource(DalAlarmSource% translatedAlarmSource);

					/**
					* Returns a string with he name of the supply rails alarm which triggered the AS flag 
					*/
					String^ GetNameofRaisedAlarmFlag(DalAlarmSource% translatedAlarmSource);

				
				public:
					/**
					* Returns the source of alarm
					* @return	The name of the alarm source 
					*/
					virtual String^ GetAlarmSource(DalAlarmSource% translatedAlarmSource); 

					/**
					* Checks if there is a change in cuff status. 
					* @param	newCuffStatusFlags	New cuff status flag to compare with the current value
					* @return	status of the operation
					*/
					static bool CheckCuffStatusFlagsChanged(const unsigned long newCuffStatusFlags); 

					/**
					* Checks if there is a change in error/alarm status. 
					* @param	newAlarmStatusFlag	New error/alarm status flag to compare with the current value
					* @return	status of the operation
					*/
					static bool CheckAlarmStatusFlagChanged(unsigned long newAlarmStatusFlag); 

					/**
					* Translates the cuff status flag bits into a state as listed in DalCuffStateFlags
					* @param	cuffStatusFlags	Cuff status bits source flag
					* @return	The translated cuff state
					*/
					static DalCuffStateFlags TranslateCuffStatusBits(unsigned long cuffStatusFlags);

					/**
					* Translates the tonometer status flag bits into a state as listed in DalTonometerState
					* @param	tonoStatusFlags	Tonometer status bits source flag
					* @return	The translated Tonometer state
					*/
					static DalTonometerState TranslateTonoStatusBits(unsigned long tonoStatusFlags);
					
					/**
					* Translates the error/alarm status flag bits into an error/alarm state as listed in DalErrorAlarmStatusFlag
					* @param	statusFlags	error/alarm status bits source flag
					* @return	The translated state
					*/
					static DalErrorAlarmStatusFlag TranslateAlarmStatusBits(unsigned long statusFlags); 

					

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
					* Dumps the tonometer and cuff data to a backup file @n
					* Obtain the name using @c GetSavedFileName
					* @param[in]	cuffPulse	Array with cuff pulse data values
					* @param[in]	bufferSize	The size of the buffer to be dumped
					* @return	 @c true if the operation was successful
					*/
					virtual bool SaveCaptureData(array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					/**
					* Returns the name and filepath of the dump file saved by @c SaveCaptureData
					* @return	The filepath of the saved file
					* @see	SaveCaptureData
					* @warning	This method can only be called once after SaveCaptureData() is called.
					*			Calling it a second time results in a blank string being returned.
					*/
					virtual String^ GetSavedFileName();

					/**
					* Breaks up the Status flag into its constituent parts and validates them. @n
					* Raises events when necessary	
					*
					* @param	statusBytes	The status flags as an unsigned long integer
					*
					* @returns	A bool value indicating the status of the operation
					*/
					static bool ProcessStatusFlag(unsigned long statusBytes);

					/**
					* Checks if there is a change the entire status flag. 
					* @param	newStatusFlag	New status flag to compare with the current value
					* @return	status of the operation
					*/
					static bool CheckStatusFlagsChanged(const unsigned long newStatusFlag); 

					/**
					* Extracts the values of the status flag parameter and copies them to the various flag members.
					* @param	statusBytes	 The status flag to be split into various components
					*/
					static void SplitStatusFlagComponents(const unsigned long statusBytes);

					/**
					* Checks the cuff status flag and raises an event if changed.
					*/
					static void ProcessCuffStatusFlag();

					/**
					* Checks if the tonometer flag has changed and raises event if needed.
					*/
					static void ProcessTonoStatusFlag();

					/**
					* Checks if the alarm bit of the status flag has changed.
					* Raises event if needed and performs any other action if needed.
					*/
					static void ProcessAlarmStatusFlag();

					/**
					* Checks if the powerup bit of the status flag is raised
					* Raises event if needed and performs any other action on the flag.
					*/
					static void ProcessPowerUpBitMask();

					/**
					* Checks if the set restet button has been hit by the user
					* Raises event if needed and stops the capture process if needed.
					*/
					static void ProcessStopButtonBitMask();

					/**
					* Checks if any of the unused status bits have changed and raises an event
					* @param[in] statusBytes	The status flag to be processed
					*/
					static void ProcessUnusedBitsStatusFlag(const unsigned long statusBytes);

					/**
					* Validates a particular unused bit in the status flag.
					* Raises an event if that bit has changed
					*
					* @param[in,out] oldFlag	The current flag value. Will be set to the new value
					* @param[in]	newFlag	The new value of the flag
					* @param[in]	unusedFlagType	The flag name.
					*/
					static void ProcessUnusedBit( unsigned long & oldFlag , const unsigned long  & newFlag, DalUnusedStatusFlagBit unusedFlagType);


					static void RaiseEventForException(DalErrorAlarmStatusFlag alarmType, ScorException^ excptionObject);



					
			};

		}
	}
}
