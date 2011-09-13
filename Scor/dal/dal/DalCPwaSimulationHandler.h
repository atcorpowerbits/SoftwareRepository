/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCPwaSimulationHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalPwvSimulationHandler class.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "IDalHandler.h"
#include "DalDataBuffer.h"
#include "DalStatusHandler.h"
#include "DalSimulationFile.h"

using namespace System;
using namespace System::IO;
using namespace System::Timers;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalCPwaSimulationHandler 
			* @brief Class to operate in simulation mode. Holds references to simulation file handles. 
			*/
			//Inherit from IDalHandler
			private ref class DalCPwaSimulationHandler : public DalSimulationHandler
			{
				private:
					//static bool firstReadAfterCaptureStarted = false;

					static DalDataBuffer ^dataBufferObj; //to hold pointer to object

					//Making these two variables static. They need to be accessed from static member functions.
					static DalSimulationFile^ _tonometerSimulationFile; //Pointer to first simulation file
					static DalSimulationFile^ _cuffTimerSimulationFile; //pointer to second simulation file (for other cuff related measurements)
					//Timers::Timer ^captureTimer;  //Timer to fire simulated data events
					
					//Added by TS Stub
					//static bool cuffInUse = false; // to indicate cuff is inflating, inflated, or deflating
		
					//
					static void OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args); //read multiple events in each interval
					static void ReadMultipleEventsInLoop(Object^ sender);
					
					static DalCPwaSimulationHandler^ _instance = gcnew DalCPwaSimulationHandler();

					/**
					 * Overloaded assignment Operator. @n
					 * Returns this pointer to implement singleton.
					 */
					DalCPwaSimulationHandler^ operator=(DalCPwaSimulationHandler^) 
					{
						return this;
					}  

					DalCPwaSimulationHandler();//Constructor , made private to implement singleton
					virtual ~DalCPwaSimulationHandler();
					
				public:
					
					/**
					* Start the data capture fromt the device. @n
					* Creates a buffer suitable for the specified time and sampling rate.
					* @param[in]	captureTime	the time frame in seconds for the capture window
					* @param[in]	samplingRate	The number of samples per second
					* @return A boolean value indicating succes of the operation
					*
					*/
					virtual bool StartCapture(int captureTime, int samplingRate) override; //new parametrized method
					
					

					/**
					*Function is to open the selecetd Simulation file from the Config.
					*
					* @return The status of the operation
					*/
					virtual bool GetFileNameFromConfgAndOpen() override;

					/**
					* Property with custom get method to supply instance.@n
					* Used to implement singleton
					*/
					static property DalCPwaSimulationHandler^ Instance
					{

						/**
						* Custom get method. @n
						* Returns a pointer to this singleton instance.
						*
						* @return	Pointer to this instance
						*/
						DalCPwaSimulationHandler^ get()
						{
							return DalCPwaSimulationHandler::_instance;
						};
					};


					/**
					* Closes any opened files
					*/
					virtual void CloseFiles() override;
			};
		}
	}
}