
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
			private ref class DalSimulationHandler : public IDalHandler 
			{
				private:

					static DalDataBuffer ^dataBufferObj; //to hold pointer to object

					//Making these two variables static. They need to be accessed from static member functions.
					static DalSimulationFile^ _simulationFile1; //Pointer to first simulation file
					static DalSimulationFile^ _simulationFile2; //pointer to second simulation file (for other cuff related measurements)
					Timers::Timer ^captureTimer;  //Timer to fire simulated data events
					static void OnTimerGetValuesAndRaiseEvents(Object^ sender, ElapsedEventArgs^ args); //Method to raise events at a specific time imterval
					static void OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args); //read multiple events in each interval
					static void ReadMultipleEventsInLoop();
					
				public:
					DalSimulationHandler(); //Constructor
					//virtual void StartCapture(); //Start the simulation capture
					virtual void StartCapture(int captureTime, int samplingRate); //new parametrized method
					virtual void StopCapture(); //Stop the simulation capture
					virtual bool GetConnectionStatus(); //Dummy method to return connection status
					virtual bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^deviceConfigInfo );//Dummy method to return configuration info.

			};
		}
	}
}