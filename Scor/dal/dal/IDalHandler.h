/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      IDalHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      IDalHandler interface file.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"


using namespace System;
using namespace System::Timers;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{
			/**
			* @interface IDalHandler
			* @brief Interface class to implement managers for EM4 and simulation devices.
			*
			* @see DalSimulationHanlder, DalDeviceHandler
			*/
			private interface class IDalHandler 
			{
				public:
			
					/**
					* Start the data capture fromt the device. @n
					* Creates a buffer suitable for the specified time and sampling rate.
					* @param[in]	captureTime	the time frame in seconds for the capture window
					* @param[in]	samplingRate	The number of samples per second
					* @return A boolean value indicating succes of the operation
					*
					*/
					bool StartCapture(int captureTime, int samplingRate); //parametrized method
					
					/**
					* Stops an ongoing data capture.
					*
					* @return A boolean value inidcating the status of the operation.
					*/
					bool StopCapture();
					
					/**
					* Returns the connection status. ie if device is connected or not on the given commport.
					*
					* @return A boolean value indicating if the device is connected or not.
					*/
					bool GetConnectionStatus();
					
					/**
					* Gets thhe configuration info of the rdevice.
					*
					* @param[in] deviceConfigItem	The configuration item whose information is requested.
					* @param[in,out]	deviceConfigInfo	The structure to return the configuration item information.
					*/
					bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, DalDeviceConfigUsageStruct ^%deviceConfigInfo );
					
					/**
					* Returns the name of the last error or alarm source
					* @return	A string contianing the name of the source
					*/
					String^ GetAlarmSource(DalAlarmSource% translatedAlarmSource);

					/**
					* Checks if the device is connected on the port specified in conifg
					* @return	@c true if device is present on the same port. @c false otherwise
					*/
					bool CheckIfDeviceIsConnected();
  				    
					/**
					* Dumps the tonometer and cuff data to a backup file @n
					* Obtain the name using @c GetSavedFileName
					* @param[in]	tonometerData	Array with tonometer data values
					* @param[in]	cuffPulse	Array with cuff pulse data values
					* @param[in]	bufferSize	The size of the buffer to be dumped
					* @return	 @c true if the operation was successful
					*/
					bool SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					/**
					* Dumps the tonometer and cuff data to a backup file @n
					* Obtain the name using @c GetSavedFileName
					* @param[in]	cuffPulse	Array with cuff pulse data values
					* @param[in]	bufferSize	The size of the buffer to be dumped
					* @return	 @c true if the operation was successful
					*/
					bool SaveCaptureData(array< unsigned short >^ cuffPulse, unsigned short bufferSize);

					/**
					* Returns the name and filepath of the dump file saved by @c SaveNibpData
					* @param[in]	time		Array with time data values
					* @param[in]	status		Array with stats data values
					* @param[in]	errorCode	Array with errorCode values
					* @param[in]	sp			Array with sp data values
					* @param[in]	dp			Array with dp data values
					* @param[in]	map			Array with map data values
					* @param[in]	hr			Array with hr data values
					* @param[in]	bufferSize	The size of the buffer to be dumped
					*
					* @return	The filepath of the saved file
					*/

					bool SaveNibpData(array< unsigned short >^ time, array< unsigned short >^ status, array< unsigned short >^ errorCode, array< unsigned short >^ sp, array< unsigned short >^ dp, array< unsigned short >^ map, array< unsigned short >^ hr, unsigned short bufferSize);
					bool SaveNibpData(unsigned short time, unsigned short status, unsigned short errorCode, unsigned short sp, unsigned short dp, short map, unsigned short hr);

					/**
					* Returns the name and filepath of the dump file saved by @c SaveCaptureData
					* @return	The filepath of the saved file
					* @see	SaveCaptureData
					* @warning	This method can only be called once after SaveCaptureData() is called.
					*			Calling it a second time results in a blank string being returned.
					*/
					String^ GetSavedFileName();

					/**
					* Returns the name and filepath of the dump file saved by @c SaveNibpData
					* @return	The filepath of the saved file
					* @see	SaveCaptureData
					* @warning	This method can only be called once after SaveNibpData() is called.
					*			Calling it a second time results in a blank string being returned.
					*/
					String^ GetSavedFileNameNibp();

					/**
					* Sets the pressure value of the EM4 cuff.
					*
					* @param[in]	newPressure	The pressure to set
					* @param[in]	cuffBoard	The board on which the pressure is set
					*
					* @return	@c true if the operation succeded
					*/
					bool SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard);
					
					
					/**
					* Sets the EM4 mode to Idle mode
					*
					* @return A boolean value indicating the status of the operation
					*/
					bool SetIdleMode();

					//TS Stub
					bool IsCuffDeflated();

					/**
					* Closes any open files or other resources.
					*/
					void CloseFiles(); 

					/**
					* Starts a BP measurement process with the specified initial pressure.
					* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
					* @param[in]	initialPressure	The inital pressure to set for this capture instance
					* @return	A boolean value indicating the success or failure of this process
					*/
					bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure);

					/**
					* Starts a BP measurement process.
					* @param[in]	nibpMode	The age group for which measurement is to be taken as an enum
					* @return	A boolean value indicating the success or failure of this process
					*/
					bool StartBP(DalNIBPMode nibpMode);

					/**
					* Stops a BP measurement and disconnects the NIBP module
					* @return	A boolean value indicating the success or failure of this process
					*/
					bool FinishBP();

					/**
					* Aborts an ongoing BP measurement.
					* @return	A boolean value indicating the success or failure of this process
					*/
					bool AbortBP();


					
					/**
					* Gets the Serial Number main processor board PCB
					*
					* @return The result of the operation
					*/
					 String^ SerialNumberMpb();
					
					/**
					* Gets the Processor firmware Version main processor board
					*
					* @return The result of the operation
					*/
					 String^ ProcessorFirmwareVersionMpb();

					/**
					* Gets the PLD Safety firmware Version main processor board
					*
					* @return The result of the operation
					*/
					 String^ PldSafetyFirmwareVersionMpb();

					/**
					* Gets the Serial number Suntech PCB
					*
					* @return The result of the operation
					*/
					 String^ SerialNumberSuntechPcb();

					/**
					* Gets the BP firmware version Suntech
					*
					* @return The result of the operation
					*/
					 String^ BPFirmwareVersionSuntech();

					/**
					* Gets the Safety firmware Version Suntech
					*
					* @return The result of the operation
					*/
					 String^ SafetyFirmwareVersionSuntech();

					/**
					* Gets the Serial number EM4
					*
					* @return The result of the operation
					*/
					 String^ SerialNumberEm4();
	
					/**
					* Gets the HW Configuration main processor board
					*
					* @return The result of the operation
					*/
					 unsigned short HWConfigurationMpb();

					/**
					* Gets the System configuration ID
					*
					* @return The result of the operation
					*/
					 unsigned short SystemConfigurationId();
					
					/**
					* Gets the Number of PWV measurements
					*
					* @return The result of the operation
					*/
					 unsigned int NumberofPWVmeasurements();

					/**
					* Gets the Number of PWA tonometer measurements
					*
					* @return The result of the operation
					*/
					 unsigned int NumberofPWAtonometermeasurements();
					/**
					* Gets the Number of PWA cuff measurements
					*
					* @return The result of the operation
					*/
					 unsigned int NumberofPWAcuffmeasurements();

					/**
					* Gets the Number of NIBP measurements
					*
					* @return The result of the operation
					*/
					 unsigned int NumberOfNibpMeasurements();
					
					/**
					* Gets the calibration date main processor board
					*
					* @return The result of the operation
					*/
					 DateTime CalibrationDateMpb();

					/**
					* Gets the calibration date Suntech
					*
					* @return The result of the operation
					*/
					 DateTime CalibrationDateSuntech();

					/**
					* Gets the test date
					*
					* @return The result of the operation
					*/
					 DateTime TestDate();

					/**
					* Gets the System configuration Change Date
					*
					* @return The result of the operation
					*/
					 DateTime SystemConfigurationChangeDate();

					/**
					* Gets the Notch Filter Enable
					*
					* @return The result of the operation
					*/
					unsigned short NotchFilterEnable();
					
					////DalConfigurationAndUsages Methods : Set
					/**
					* Sets the Serial Number main processor board PCB.
					*
					* @param[in]	data	Serial Number main processor board PCB to set
					*
					* @return	void
					*/
					void SerialNumberMpb(String^ data);
					
					/**
					* Sets the Processor firmware Version main processor board
					*
					* @param[in]	data	Processor firmware Version main processor board to set
					*
					* @return	void
					*/
					void ProcessorFirmwareVersionMpb(String^ data);
					
					/**
					* Sets the PLD Safety firmware Version main processor board.
					*
					* @param[in]	data	PLDSafetyfirmwareVersionmainprocessorboard to set
					*
					* @return	void
					*/
					void PldSafetyFirmwareVersionMpb(String^ data);
					
					/**
					* Sets the Serial number Suntech PCB.
					*
					* @param[in]	data	SerialNumberSuntechPcb to set
					*
					* @return	void
					*/
					void SerialNumberSuntechPcb(String^ data);
					
					/**
					* Sets the BP firmware version Suntech.
					*
					* @param[in]	data	BPfirmwareVersionSuntech to set
					*
					* @return	void
					*/
					void BPFirmwareVersionSuntech(String^ data);
					
					/**
					* Sets the Safety firmware Version Suntech.
					*
					* @param[in]	data	SafetyFirmwareVersionSuntech to set
					*
					* @return	void
					*/
					void SafetyFirmwareVersionSuntech(String^ data);
					
					/**
					* Sets the Serial number EM4.
					*
					* @param[in]	data	SerialNumberEm4 to set
					*
					* @return	void
					*/
					void SerialNumberEm4(String^ data);
					
					/**
					* Sets the HW Configuration main processor board.
					*
					* @param[in]	data	HWConfigurationMpb to set
					*
					* @return	void
					*/
					void HWConfigurationMpb(unsigned short data);
					
					/**
					* Sets the System configuration ID.
					*
					* @param[in]	data	SystemConfigurationId to set
					*
					* @return	void
					*/
					void SystemConfigurationId(unsigned short data);

					/**
					* Sets the Number of PWV measurements.
					*
					* @param[in]	data	NumberofPWVmeasurements to set
					*
					* @return	void
					*/
					void NumberofPWVmeasurements(unsigned int data);
					
					/**
					* Sets the Number of PWA tonometer measurements.
					*
					* @param[in]	data	NumberofPWAtonometermeasurements to set
					*
					* @return	void
					*/
					void NumberofPWAtonometermeasurements(unsigned int data);
					
					/**
					* Sets the Number of PWA cuff measurements.
					*
					* @param[in]	data	NumberofPWAcuffmeasurements to set
					*
					* @return	void
					*/
					void NumberofPWAcuffmeasurements(unsigned int data);
					
					/**
					* Sets the Number of NIBP measurements.
					*
					* @param[in]	data	NumberOfNibpMeasurements to set
					*
					* @return	void
					*/
					void NumberOfNibpMeasurements(unsigned int data);

					/**
					* Sets the calibration date main processor board.
					*
					* @param[in]	data	CalibrationDateMpb
					*
					* @return	void
					*/
					void CalibrationDateMpb(DateTime data);
					
					/**
					* Sets the calibration date Suntech.
					*
					* @param[in]	data	CalibrationDateSuntech to set
					*
					* @return	void
					*/
					void CalibrationDateSuntech(DateTime data);
					
					/**
					* Sets the test date.
					*
					* @param[in]	data	test date to set
					*
					* @return	void
					*/
					void TestDate(DateTime data);
					
					/**
					* Sets the System configuration Change Date.
					*
					* @param[in]	data	SystemConfigurationChangeDate to set
					*
					* @return	void
					*/
					void SystemConfigurationChangeDate(DateTime data);

					/**
					* Sets the Notch Filter Enable.
					*
					* @param[in]	data	NotchFilterEnable to set
					*
					* @return	void
					*/
					void NotchFilterEnable(unsigned short data);
			};

		}
	}
}



