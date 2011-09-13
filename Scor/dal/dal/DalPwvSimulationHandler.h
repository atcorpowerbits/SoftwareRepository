/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalPwvSimulationHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalPwvSimulationHandler class.
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
			private ref class DalPwvSimulationHandler : public DalSimulationHandler
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
					//static void ReadMultipleEventsInLoop(Object^ sender) override;
					
					static DalPwvSimulationHandler^ _instance = gcnew DalPwvSimulationHandler();

					/**
					 * Overloaded assignment Operator. @n
					 * Returns this pointer to implement singleton.
					 */
					DalPwvSimulationHandler^ operator=(DalPwvSimulationHandler^) 
					{
						return this;
					}  

					DalPwvSimulationHandler();//Constructor , made private to implement singleton

					static void ReadMultipleEventsInLoop(Object^ sender);
					
					virtual ~DalPwvSimulationHandler();

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
					static property DalPwvSimulationHandler^ Instance
					{

						/**
						* Custom get method. @n
						* Returns a pointer to this singleton instance.
						*
						* @return	Pointer to this instance
						*/
						DalPwvSimulationHandler^ get()
						{
							return DalPwvSimulationHandler::_instance;
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