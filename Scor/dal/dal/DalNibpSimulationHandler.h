/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpSimulationHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalNibpSimulationHandler class.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "IDalNibpHandler.h"
#include "DalSimulationFile.h"
#include "DalDataBuffer.h"

using namespace System;
using namespace System::IO;
using namespace System::Timers;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalNibpSimulationHandler 
			* @brief Class to operate in NIBP simulation mode.  
			*/
			
			private ref class DalNibpSimulationHandler : public IDalNibpHandler
			{
				private:
					static DalSimulationFile^ _nibpSimulationFile; //pointer to NIBP simulation file
					static Timers::Timer ^_nibpTimer = nullptr;  //Timer to fire simulated NIBP data event
					static bool _nibpConnected ;
					static unsigned short _nibpStatus;
					static unsigned short _nibpErrorCode;
					static unsigned short _nibpSP;
					static unsigned short _nibpDP;
					static unsigned short _nibpMP;
					static unsigned short _nibpHR;

					//Sets the Initial Inflate value
					bool SetBPInitialInflate(unsigned short initialPressure); //TS Stub
					
					//Singleton instance
					static DalNibpSimulationHandler^ _instance = gcnew DalNibpSimulationHandler();

					static DalDataBuffer ^dataBufferObj; //to hold pointer to object
				public:
					
					/**
					* Returns the current singleton instance.
					*/
					static property DalNibpSimulationHandler^ Instance
					{
						DalNibpSimulationHandler^ get()
						{
							return DalNibpSimulationHandler::_instance;
						};
					};

					/**
					* Starts a BP measurement process with the specified initial pressure.
					* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
					* @param[in]	initialPressure	The inital pressure to set for this capture instance
					* @return	A boolean value indicating the success or failure of this process
					*/
					virtual bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure);

					/**
					* Starts a BP measurement process.
					* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
					* @return	A boolean value indicating the success or failure of this process
					*/
					virtual bool StartBP(DalNIBPMode nibpMode);

					/**
					* Stops a BP measurement and disconnects the NIBP module
					* @return	A boolean value indicating the success or failure of this process
					*/
					virtual bool FinishBP();

					/**
					* Aborts an ongoing BP measurement.
					* @return	A boolean value indicating the success or failure of this process
					*/
					virtual bool AbortBP();

					/**
					* Handler for the internal timer. Reads an NIBP event data from the file and raises an event.
					* @param[in]	sender	The raiser of this event
					* @param[in]	args	Arguments for this event
					*/
					static void OnTimerDalNIBPDataEvent(Object^ sender, ElapsedEventArgs^ args);
			};
		}
	}
}