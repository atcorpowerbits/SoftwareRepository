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
#include "DalStatusHandler.h"

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
					 static bool firstReadAfterCaptureStarted = false;

					static DalDataBuffer ^dataBufferObj; //to hold pointer to object

					//Making these two variables static. They need to be accessed from static member functions.
					static DalSimulationFile^ _tonometerSimulationFile; //Pointer to first simulation file
					static DalSimulationFile^ _cuffTimerSimulationFile; //pointer to second simulation file (for other cuff related measurements)
					Timers::Timer ^captureTimer;  //Timer to fire simulated data events
					//static void OnTimerGetValuesAndRaiseEvents(Object^ sender, ElapsedEventArgs^ args); //Method to raise events at a specific time imterval //Obsolete
					static void OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args); //read multiple events in each interval
					//static void ReadMultipleEventsInLoop(); //making non static in order to raise events. static members cannot have this pointer
					static void ReadMultipleEventsInLoop(Object^ sender);
					
					static DalSimulationHandler^ _instance = gcnew DalSimulationHandler();

					/**
					 * Overloaded assignment Operator. @n
					 * Returns this pointer to implement singleton.
					 */
					DalSimulationHandler^ operator=(DalSimulationHandler^) 
					{
						return this;
					}  

					DalSimulationHandler(); //Constructor , made private to implement singleton
					
				public:
					//virtual bool StartCapture(); //Start the simulation capture //Non parameterized method is obsolete

					virtual bool StartCapture(int captureTime, int samplingRate); //new parametrized method
					virtual bool StopCapture(); //Stop the simulation capture
					virtual bool GetConnectionStatus(); //Dummy method to return connection status
					virtual bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^%deviceConfigInfo );//Dummy method to return configuration info.

					/**
					* Checks if the device is connected on the port specified in conifg
					* @return	Always @c true for simulation
					*/
					virtual bool CheckIfDeviceIsConnected();
					
					/**
					* Sets the pressure value
					* @return	Will always return @c true for simulation
					*/
					virtual bool SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard);	

					/**
					*Function is to open the selecetd Simulation file from the Config.
					*
					* @return The status of the operation
					*/
					bool GetFileNameFromConfgAndOpen();


					//function is being moved to DalStatusHandler for unification
					///*
					//* Checks the status flag and raises events if necessary
					//*
					//* @param[in] statusBytes The status flag for validation
					//* @param[out] cuffIsInflated Indicates if the status flags had a cuff inflated status.
					//*
					//* @return The status of the operation
					//*/
					//static bool CheckStatusFlag(unsigned long statusBytes, bool %cuffIsInflated);

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


					/**
					* Sets the EM4 mode to Idle mode
					*
					* @return @c true
					* @warning This is a stub method for simulationa and will always return @c true
					*/
					virtual bool SetIdleMode();

			};
		}
	}
}