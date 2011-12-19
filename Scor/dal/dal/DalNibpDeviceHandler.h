/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpDeviceHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header page for DalNibpDeviceHandler class.
*/

#pragma once


#include "stdafx.h"
#include "DalCommon.h"
#include "IDalNibpHandler.h"
#include "DalCommandInterface.h"
#include "DalEM4Command.h"
#include "DalDataBuffer.h"
#include "DalSpecificForegroundCommands.h"


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalNibpDeviceHandler: public IDalNibpHandler
			{
				private:
					DalDataBuffer^ dataBufferObj;  //pointer to the data buffer
					static DalNibpDeviceHandler^ _instance = gcnew DalNibpDeviceHandler(); //Current instance for Singleton

					DalCommandInterface^ _commandInterface; //pointer to the command interface

					//Connects to the NIBP module by sending the command multiple times in a loop until
					//a positive response arrives or times out.
					bool ConnectToNibpModule();
					
					//Sends an NIBP_Connect command.
					//Internally calls SendNibpConnectDisconnectCommand()
					DalReturnValue SendNibpConnectCommand();

					//Sends an NIBP_Disconnect command.
					//Internally calls SendNibpConnectDisconnectCommand()
					DalReturnValue SendNibpDisconnectCommand();

					//Sends an NIBP connect or disconnect command based on the parameter.
					DalReturnValue SendNibpConnectDisconnectCommand(bool connect);

					void SetCommandInterface(DalCommandInterface^); //Dependency injection mechanism.
					
					bool GetCuffPressure(unsigned int& cuffPressure); //Returns the ciff pressure in an out parameter

					//Starts the BP process by first setting the device in NIBP mode and then sending the inital inflate command
					bool StartBpProcess(DalNIBPMode nibpMode, unsigned short initialPressure, bool initialInflate);
							
					//Deepak: no need to check using a sepearate thread. Use the existing cuff pressure measurement thread
					//bool CheckIfCuffHasDeflated(); //returns true if cuff has deflated

					bool CreateDataBuffer(); //Creates the DAlDataBuffer of appropriate size.

					Thread^ cuffPressurePlottingThread; //thread to read cuff pressure at regular intervals.
					void CuffPressurePlottingThreadMethod(); //Thread method to read cuff pressure and plot it at regular intervals.
					
					DalNibpStartBpCommand^ GetNewStartBpCommandObject(DalNIBPMode nibpMode);//Returns a StartBpCommand object depending on the NIBP mode specified

					DalNibpStartBpCommand^ startBpCommand ; //we need to access the StartBp command objct so that we can abort the process

					bool nibpModuleConnected;
			    
				internal:
					DalNibpDeviceHandler(); //Constructor

				public:
					
					/**
					* Returns the current singleton instance.
					*/
					static property DalNibpDeviceHandler^ Instance
					{
						DalNibpDeviceHandler^ get()
						{
							return DalNibpDeviceHandler::_instance;
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
					* Stops the cuff pressure measurement thread
					*/
					void StopCuffPressurePlotting();

					/**
					* Sends the GET_BP_DATA command, validates the result and raises an event
					* @return The status of the operation.
					*/
					bool GetBpDataAndRaiseEvent();

					void SignalNibpAborted();

					delegate void SignalNibpAbortedAsyncCaller();

					SignalNibpAbortedAsyncCaller^ signalNibpAbortCaller;

					static property unsigned int  CurrentCuffPressure;

					bool IsCuffDeflated(); 

					

					delegate bool ObtainBpMeasurementAsyncCaller();

					ObtainBpMeasurementAsyncCaller^ obtainBpMeasurementAsynCaller;

					void AbortBpOnStopButtonPress();


					
			};


		}// end namespaces
	}
}
