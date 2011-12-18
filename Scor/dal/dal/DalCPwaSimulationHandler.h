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
#include "IDalNibpHandler.h"
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
			private ref class DalCPwaSimulationHandler : public DalSimulationHandler
			{
				private:
					static DalDataBuffer^ dataBufferObj; //to hold pointer to object
					static DalDataBuffer^ nibpBufferObj; //to hold pointer to object

					//Making these two variables static. They need to be accessed from static member functions.
					static DalSimulationFile^ _tonometerSimulationFile; //Pointer to first simulation file
					static DalSimulationFile^ _cuffTimerSimulationFile; //pointer to second simulation file (for other cuff related measurements)
					
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
					
			internal:
					static IDalNibpHandler^ _nibp;  //A pointer to the current device

				public:
					
					/**
					* Returns the NIBP.
					*/
					static property IDalNibpHandler^ NIBP
					{
						IDalNibpHandler^ get()
						{
							return _nibp;
						};
					};

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

					/**
					* Starts a BP measurement process with the specified initial pressure.
					* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
					* @param[in]	initialPressure	The inital pressure to set for this capture instance
					* @return	A boolean value indicating the success or failure of this process
					*/
					virtual bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure) override;
					
					/**
					* Starts a BP measurement process.
					* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
					* @return	A boolean value indicating the success or failure of this process
					*/
					virtual bool StartBP(DalNIBPMode nibpMode) override;
					
					/**
					* Stops a BP measurement and disconnects the NIBP module
					* @return	A boolean value indicating the success or failure of this process
					*/
					virtual bool FinishBP() override;

					/**
					* Aborts an ongoing BP measurement.
					* @return	A boolean value indicating the success or failure of this process
					*/
					virtual bool AbortBP() override;
			};
		}
	}
}