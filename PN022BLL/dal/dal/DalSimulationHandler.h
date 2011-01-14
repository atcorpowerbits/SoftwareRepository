
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
			private ref class DalSimulationHandler : public IDalHandler 
			{
				private:
					 static unsigned long _currentStatusFlags;
					 static unsigned long _currentErrorAlarmFlags;

					static DalDataBuffer ^dataBufferObj; //to hold pointer to object

					static String^ dalErrorAlarmSourceName; //used for 2-3 static functions
					
					//Making these two variables static. They need to be accessed from static member functions.
					static DalSimulationFile^ _tonometerSimulationFile; //Pointer to first simulation file
					static DalSimulationFile^ _cuffTimerSimulationFile; //pointer to second simulation file (for other cuff related measurements)
					Timers::Timer ^captureTimer;  //Timer to fire simulated data events
					static void OnTimerGetValuesAndRaiseEvents(Object^ sender, ElapsedEventArgs^ args); //Method to raise events at a specific time imterval //TODO:STUB
					static void OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args); //read multiple events in each interval
					//static void ReadMultipleEventsInLoop(); //making non static in order to raise events. static members cannot have this pointer
					static void ReadMultipleEventsInLoop(Object^ sender);


				public:
					static property unsigned long currentStatusFlags 
					{
						unsigned long get()
						{
							return _currentStatusFlags;
						}

						void set(unsigned long value)
						{
							_currentStatusFlags= value;
						}
					};

					static property unsigned long currentErrorAlarmFlags 
					{
						unsigned long get()
						{
							return _currentErrorAlarmFlags;
						}

						void set(unsigned long value)
						{
							_currentErrorAlarmFlags= value;
						}
					};
					
				public:
					DalSimulationHandler(); //Constructor
					virtual void StartCapture(); //Start the simulation capture //TODO:STUB
					virtual void StartCapture(int captureTime, int samplingRate); //new parametrized method
					virtual void StopCapture(); //Stop the simulation capture
					virtual bool GetConnectionStatus(); //Dummy method to return connection status
					virtual bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^deviceConfigInfo );//Dummy method to return configuration info.

					static bool CheckStatusFlagsChanged(const unsigned long newStatusFlags); 
					static bool CheckErrorAlarmFlagsChanged(unsigned long newErrorAlarmFlags); 
					static String^ MapErrorSourceToString(unsigned long sourceFlags); 
					static String^ MapAlarmSourceToString(unsigned long sourceFlags); 
					virtual String^ GetErrorAlarmSource(); 
					static DalCuffStateFlags TranslateCuffStatusBits(unsigned long statusFlags); 
					static DalErrorAlarmStatusFlag TranslateErrorAlarmStatusBits(unsigned long statusFlags); 


			};
		}
	}
}