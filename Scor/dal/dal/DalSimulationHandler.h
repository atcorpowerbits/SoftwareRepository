/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSimulationHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalSimulationHandler class.
*/

#pragma once

#include "stdafx.h"
#include "IDalHandler.h"
#include "DalSimulationFile.h"
#include "DalDataBuffer.h"
#include "DalCommon.h"

using namespace System;
using namespace System::IO;
using namespace System::Timers;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalSimulationHandler
			* @brief Class to operate in simulation mode. Holds references to simulation file handles. 
			*/
			//Inherit from IDalHandler
			private ref class DalSimulationHandler : public IDalHandler , public DalStatusHandler 
			{
				private:
					 /*static unsigned long _currentCuffStatusFlag;
					 static unsigned long _currentEAStatusFlag;
					 static unsigned long _currentEASourceFlag;*/

					 static bool firstReadAfterCaptureStarted = false;

					static DalDataBuffer ^dataBufferObj; //to hold pointer to object

					//static String^ dalErrorAlarmSourceName; //used for 2-3 static functions
					
					//Making these two variables static. They need to be accessed from static member functions.
					static DalSimulationFile^ _tonometerSimulationFile; //Pointer to first simulation file
					static DalSimulationFile^ _cuffTimerSimulationFile; //pointer to second simulation file (for other cuff related measurements)
					Timers::Timer ^captureTimer;  //Timer to fire simulated data events
					static void OnTimerGetValuesAndRaiseEvents(Object^ sender, ElapsedEventArgs^ args); //Method to raise events at a specific time imterval //TODO:STUB
					static void OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args); //read multiple events in each interval
					//static void ReadMultipleEventsInLoop(); //making non static in order to raise events. static members cannot have this pointer
					static void ReadMultipleEventsInLoop(Object^ sender);
					
					static DalSimulationHandler^ _instance = gcnew DalSimulationHandler();

					/**
					 * Overloaded assignment Operator. @n
					 * Returns this pointer to implement singleton.
					 */
					DalSimulationHandler^ operator=(const DalSimulationHandler^) 
					{
						return this;
					}  

					DalSimulationHandler(); //Constructor , made private to implement singleton
					
				public:
					virtual bool StartCapture(); //Start the simulation capture //TODO:STUB
					virtual bool StartCapture(int captureTime, int samplingRate); //new parametrized method
					virtual bool StopCapture(); //Stop the simulation capture
					virtual bool GetConnectionStatus(); //Dummy method to return connection status
					virtual bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^deviceConfigInfo );//Dummy method to return configuration info.

					/**
					* Checks if the device is connected on the port specified in conifg
					* @return	Always @c true for simulation
					*/
					virtual bool CheckIfDeviceIsConnected();
					
					/**
					* Sets the pressure value
					* @return	Will always return @c true for simulation
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
					*Function is to open the selecetd Simulation file from the Config.
					*
					* @return The status of the operation
					*/
					bool GetFileNameFromConfgAndOpen();


					static bool CheckStatusFlag(unsigned long statusBytes, bool %cuffIsInflated);

					/**
					* Property with custom get method to supply instance.@n
					* Used to implement singleton
					*/
					static property DalSimulationHandler^ Instance
					{

						/**
						* Custom get method. @n
						* Returns a pointer to this singleton instance.
						*
						* @return	Pointer to this instance
						*/
						DalSimulationHandler^ get()
						{
							return DalSimulationHandler::_instance;
						};
					};

			};
		}
	}
}