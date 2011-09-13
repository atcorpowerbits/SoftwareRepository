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
			private ref class DalSimulationHandler abstract: public IDalHandler , public DalStatusHandler 
			{
				private:
					 
					static DalDataBuffer ^dataBufferObj; //to hold pointer to object

					//Making these two variables static. They need to be accessed from static member functions.
					static DalSimulationFile^ _tonometerSimulationFile; //Pointer to first simulation file
					static DalSimulationFile^ _cuffTimerSimulationFile; //pointer to second simulation file (for other cuff related measurements)
					
		
					
					//static void OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args); //read multiple events in each interval
					static void ReadMultipleEventsInLoop(Object^ sender);
					
					//static DalSimulationHandler^ _instance = gcnew DalSimulationHandler();

					/**
					 * Overloaded assignment Operator. @n
					 * Returns this pointer to implement singleton.
					 */
					DalSimulationHandler^ operator=(DalSimulationHandler^) 
					{
						//return this;
						return nullptr;
					}  
			protected:
					static bool firstReadAfterCaptureStarted ;

					//Added by TS Stub
					static bool cuffInUse = false; // to indicate cuff is inflating, inflated, or deflating
		
					DalSimulationHandler(); //Constructor , made private to implement singleton
					static void OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args); //read multiple events in each interval
					//static void ReadMultipleEventsInLoop(Object^ sender);
					virtual ~DalSimulationHandler();
					Timers::Timer ^captureTimer;  //Timer to fire simulated data events
				public:
					
					/**
					* Start the data capture fromt the device. @n
					* Creates a buffer suitable for the specified time and sampling rate.
					* @param[in]	captureTime	the time frame in seconds for the capture window
					* @param[in]	samplingRate	The number of samples per second
					* @return A boolean value indicating succes of the operation
					*
					*/
					virtual bool StartCapture(int captureTime, int samplingRate); //new parametrized method
					
					/**
					* Stops an ongoing data capture.
					*
					* @return A boolean value inidcating the status of the operation.
					*/
					virtual bool StopCapture(); //Stop the simulation capture
					
					/**
					* Returns the connection status. ie if device is connected or not on the given commport.
					*
					* @return A boolean value indicating if the device is connected or not.
					*/
					virtual bool GetConnectionStatus(); //Dummy method to return connection status
					
					/**
					* Gets thhe configuration info of the rdevice.
					*
					* @param[in] deviceConfigItem	The configuration item whose information is requested.
					* @param[in,out]	deviceConfigInfo	The structure to return the configuration item information.
					* @warning This is a stub only. Not yet implemented.
					*/
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
					virtual bool GetFileNameFromConfgAndOpen();


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
					//static property DalSimulationHandler^ Instance
					//{

					//	/**
					//	* Custom get method. @n
					//	* Returns a pointer to this singleton instance.
					//	*
					//	* @return	Pointer to this instance
					//	*/
					//	DalSimulationHandler^ get()
					//	{
					//		//return DalSimulationHandler::_instance;
					//	};
					//};


					/**
					* Sets the EM4 mode to Idle mode
					*
					* @return @c true
					* @warning This is a stub method for simulationa and will always return @c true
					*/
					virtual bool SetIdleMode();

					virtual bool IsCuffDeflated();

					virtual void CloseFiles();

			};
		}
	}
}