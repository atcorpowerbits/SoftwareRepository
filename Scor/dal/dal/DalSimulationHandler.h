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
					/**
					* flag that is used to detect if this is the first time the function has run in a session
					*/
					static bool firstReadAfterCaptureStarted ;

					//Added by TS Stub
					static bool cuffInUse = false; // to indicate cuff is inflating, inflated, or deflating
		
					DalSimulationHandler(); //Constructor , made private to implement singleton
					static void OnTimerReadMultipleEvents(Object^ sender, ElapsedEventArgs^ args); //read multiple events in each interval
					//static void ReadMultipleEventsInLoop(Object^ sender);
					virtual ~DalSimulationHandler();
					Timers::Timer ^captureTimer;  //Timer to fire simulated data events
					static void SetCountDownTimer(DalCuffStateFlags currentCuffState, unsigned long locCountdownTimer, DalPwvDataStruct^ dataVar);

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

					/**
					* Sets the EM4 mode to Idle mode
					*
					* @return @c true
					* @warning This is a stub method for simulationa and will always return @c true
					*/
					virtual bool SetIdleMode();

					/**
					*Checks if the cuff is deflated(below an acceptable min value)
					* @return @c true if the cuff is delfated
					*/
					virtual bool IsCuffDeflated();

					/**
					* Closes any open files.
					*/
					virtual void CloseFiles();

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

					//DalConfigurationAndUsages Methods: Get
					/**
					* Gets the Serial Number main processor board PCB
					*
					* @return The result of the operation
					*/
					virtual String^ SerialNumberMpb();
					
					/**
					* Gets the Processor firmware Version main processor board
					*
					* @return The result of the operation
					*/
					virtual String^ ProcessorFirmwareVersionMpb();

					/**
					* Gets the PLD Safety firmware Version main processor board
					*
					* @return The result of the operation
					*/
					virtual String^ PldSafetyFirmwareVersionMpb();

					/**
					* Gets the Serial number Suntech PCB
					*
					* @return The result of the operation
					*/
					virtual String^ SerialNumberSuntechPcb();

					/**
					* Gets the BP firmware version Suntech
					*
					* @return The result of the operation
					*/
					virtual String^ BPFirmwareVersionSuntech();

					/**
					* Gets the Safety firmware Version Suntech
					*
					* @return The result of the operation
					*/
					virtual String^ SafetyFirmwareVersionSuntech();

					/**
					* Gets the Serial number EM4
					*
					* @return The result of the operation
					*/
					virtual String^ SerialNumberEm4();
	
					/**
					* Gets the HW Configuration main processor board
					*
					* @return The result of the operation
					*/
					virtual unsigned short HWConfigurationMpb();

					/**
					* Gets the System configuration ID
					*
					* @return The result of the operation
					*/
					virtual unsigned short SystemConfigurationId();
					
					/**
					* Gets the Number of PWV measurements
					*
					* @return The result of the operation
					*/
					virtual unsigned int NumberofPWVmeasurements();

					/**
					* Gets the Number of PWA tonometer measurements
					*
					* @return The result of the operation
					*/
					virtual unsigned int NumberofPWAtonometermeasurements();
					/**
					* Gets the Number of PWA cuff measurements
					*
					* @return The result of the operation
					*/
					virtual unsigned int NumberofPWAcuffmeasurements();

					/**
					* Gets the Number of NIBP measurements
					*
					* @return The result of the operation
					*/
					virtual unsigned int NumberOfNibpMeasurements();
					
					/**
					* Gets the calibration date main processor board
					*
					* @return The result of the operation
					*/
					virtual DateTime CalibrationDateMpb();

					/**
					* Gets the calibration date Suntech
					*
					* @return The result of the operation
					*/
					virtual DateTime CalibrationDateSuntech();

					/**
					* Gets the test date
					*
					* @return The result of the operation
					*/
					virtual DateTime TestDate();

					/**
					* Gets the System configuration Change Date
					*
					* @return The result of the operation
					*/
					virtual DateTime SystemConfigurationChangeDate();
					
					/**
					* Gets the Notch Filter Enable
					*
					* @return The result of the operation
					*/
					virtual unsigned short NotchFilterEnable();

					//DalConfigurationAndUsages Methods: Set
					/**
					* Sets the Serial Number main processor board PCB.
					*
					* @param[in]	data	Serial Number main processor board PCB to set
					*
					* @return	void
					*/
					virtual void SerialNumberMpb(String^ data);
					
					/**
					* Sets the Processor firmware Version main processor board
					*
					* @param[in]	data	Processor firmware Version main processor board to set
					*
					* @return	void
					*/
					virtual void ProcessorFirmwareVersionMpb(String^ data);
					
					/**
					* Sets the PLD Safety firmware Version main processor board.
					*
					* @param[in]	data	PLDSafetyfirmwareVersionmainprocessorboard to set
					*
					* @return	void
					*/
					virtual void PldSafetyFirmwareVersionMpb(String^ data);
					
					/**
					* Sets the Serial number Suntech PCB.
					*
					* @param[in]	data	SerialNumberSuntechPcb to set
					*
					* @return	void
					*/
					virtual void SerialNumberSuntechPcb(String^ data);
					
					/**
					* Sets the BP firmware version Suntech.
					*
					* @param[in]	data	BPfirmwareVersionSuntech to set
					*
					* @return	void
					*/
					virtual void BPFirmwareVersionSuntech(String^ data);
					
					/**
					* Sets the Safety firmware Version Suntech.
					*
					* @param[in]	data	SafetyFirmwareVersionSuntech to set
					*
					* @return	void
					*/
					virtual void SafetyFirmwareVersionSuntech(String^ data);
					
					/**
					* Sets the Serial number EM4.
					*
					* @param[in]	data	SerialNumberEm4 to set
					*
					* @return	void
					*/
					virtual void SerialNumberEm4(String^ data);
					
					/**
					* Sets the HW Configuration main processor board.
					*
					* @param[in]	data	HWConfigurationMpb to set
					*
					* @return	void
					*/
					virtual void HWConfigurationMpb(unsigned short data);
					
					/**
					* Sets the System configuration ID.
					*
					* @param[in]	data	SystemConfigurationId to set
					*
					* @return	void
					*/
					virtual void SystemConfigurationId(unsigned short data);

					/**
					* Sets the Number of PWV measurements.
					*
					* @param[in]	data	NumberofPWVmeasurements to set
					*
					* @return	void
					*/
					virtual void NumberofPWVmeasurements(unsigned int data);
					
					/**
					* Sets the Number of PWA tonometer measurements.
					*
					* @param[in]	data	NumberofPWAtonometermeasurements to set
					*
					* @return	void
					*/
					virtual void NumberofPWAtonometermeasurements(unsigned int data);
					
					/**
					* Sets the Number of PWA cuff measurements.
					*
					* @param[in]	data	NumberofPWAcuffmeasurements to set
					*
					* @return	void
					*/
					virtual void NumberofPWAcuffmeasurements(unsigned int data);
					
					/**
					* Sets the Number of NIBP measurements.
					*
					* @param[in]	data	NumberOfNibpMeasurements to set
					*
					* @return	void
					*/
					virtual void NumberOfNibpMeasurements(unsigned int data);

					/**
					* Sets the calibration date main processor board.
					*
					* @param[in]	data	CalibrationDateMpb
					*
					* @return	void
					*/
					virtual void CalibrationDateMpb(DateTime data);
					
					/**
					* Sets the calibration date Suntech.
					*
					* @param[in]	data	CalibrationDateSuntech to set
					*
					* @return	void
					*/
					virtual void CalibrationDateSuntech(DateTime data);
					
					/**
					* Sets the test date.
					*
					* @param[in]	data	test date to set
					*
					* @return	void
					*/
					virtual void TestDate(DateTime data);

					//virtual void SystemConfigurationChangeDate(DateTime data);
					/**
					* Sets the System configuration Change Date.
					*
					* @param[in]	data	SystemConfigurationChangeDate to set
					*
					* @return	void
					*/
					virtual void SystemConfigurationChangeDate(DateTime data);

					/**
					* Sets the Notch Filter Enable.
					*
					* @param[in]	data	NotchFilterEnable to set
					*
					* @return	void
					*/
					virtual void NotchFilterEnable(unsigned short data);
			};
		}
	}
}