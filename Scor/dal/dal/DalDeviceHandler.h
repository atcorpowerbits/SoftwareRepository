/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalDeviceHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalDeviceHandler class header file.
*/

#pragma once

#include "stdafx.h"
#include "IDalHandler.h"
#include "DalCommandInterface.h"
#include "DalDataBuffer.h"
#include "DalStatusHandler.h"
#include "DalCommandState.h"


using namespace System;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::DataAccess::StateMachines;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalDeviceHandler
			* @brief Class to handle EM4 device operation.
			*/
			private ref class DalDeviceHandler : public IDalHandler , public DalStatusHandler
			{
				private:
					String^ _commPort; //The current comm port name. Can be a real port or simulation
					
					//CrxLogger ^logObj;
					CrxMessagingManager ^ messagingMgr;
					static DalDeviceHandler^ _instance = gcnew DalDeviceHandler();

					/**
					* Overloaded assignment Operator. @n
					* Returns this pointer to implement singleton.
					*/
					DalDeviceHandler^ operator=( DalDeviceHandler^) 
					{
						return this;
					}  
				protected:
					DalDataBuffer ^dataBufferObj; //to hold pointer to object
					DalCommandInterface^ _commandInterface;
					
					
				public:
					/**
					* Constructor for the class.
					*/
					DalDeviceHandler(); 

					/**
					* Start the data capture fromt the device. @n
					* Creates a buffer suitable for the specified time and sampling rate.
					* @param[in]	captureTime	the time frame in seconds for the capture window
					* @param[in]	samplingRate	The number of samples per second
					* @return A boolean value indicating succes of the operation
					*
					*/
					virtual bool StartCapture(int captureTime, int samplingRate);

					/**
					* Stops an ongoing data capture.
					*
					* @return A boolean value inidcating the status of the operation.
					*/
					virtual bool StopCapture();

					/**
					* Returns the connection status. ie if device is connected or not on the given commport.
					*
					* @return A boolean value indicating if the device is connected or not.
					*/
					virtual bool GetConnectionStatus();

					/**
					* Gets thhe configuration info of the rdevice.
					*
					* @param[in] deviceConfigItem	The configuration item whose information is requested.
					* @param[in,out]	deviceConfigInfo	The structure to return the configuration item information.
					* @warning This is a stub only. Not yet implemented.
					*/
					virtual bool GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^%deviceConfigInfo );

					/**
					* Returns the name of the last error or alarm source
					* @return	A string contianing the name of the source
					*/
					virtual String^ GetAlarmSource(DalAlarmSource% translatedAlarmSource) new; 

					/**
					* Looks for the EM4 module on the serial ports
					* @param[out]	comPort	The name of the port where the device was found. @n
					*				This is returned only if return value is @c 2
					* @return  An interger value indicating the  status @n
					*			@c 0: the device was not found on any port 
					*			@c 1: the device was on the same port as specified in confi
					*			@c 2: the device was found on a different port. Check @c comPort for the anem of the new port.
					*/
					virtual int FindModule(String^ comPort);

					/**
					* Checks if the device is connected on the port specified in conifg
					* @return	@c true if device is present on the same port. @c false otherwise
					*/
					virtual bool CheckIfDeviceIsConnected();

					/**
					* Checks if the device is connected on the port specified as a parameter
					* @return	@c true if device is present on the same port. @c false otherwise
					*/
					virtual bool CheckIfDeviceIsConnected(String^ comPort);

					

					/**
					* Sets the pressure value of the EM4 cuff.
					*
					* @param[in]	newPressure	The pressure to set
					* @param[in]	cuffBoard	The board on which the pressure is set
					*
					* @return	@c true if the operation succeded
					*/
					virtual bool SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard);	
					
					/**
					*  property with custom get method to supply instance.@n
					* Used to implement singleton
					*/
					static property DalDeviceHandler^ Instance
					{

						/**
						* Custom get method. @n
						* Returns a pointer to this singleton instance.
						*
						* @return	Pointer to this instance
						*/
						DalDeviceHandler^ get()
						{
							return DalDeviceHandler::_instance;
						};
					};

					/**
					* Gets the Serial number of the device from config
					* @param[out]	moduleSerialNumber	The serial number obtained from thedevice
					* @return	Status of the operation
					*/
					bool GetConfigDeviceSerialMumber(String ^% moduleSerialNumber);

					/**
					* Gets the Pwa Cuff Measurements Counter of the device from config
					* @param[out]	PwaCuffMeasurementsCounter	The Pwa Cuff Measurements Counter obtained from the device
					* @return	Status of the operation
					*/
					bool GetConfigPwaCuffMeasurementsCounter(String ^% PwaCuffMeasurementsCounter);
					
					/**
					* Sets the EM4 mode to Idle mode
					*
					* @return The result of the operation
					*/
					virtual bool SetIdleMode();

					virtual bool IsCuffDeflated();

					virtual void CloseFiles();

					
					virtual bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure){nibpMode; initialPressure; return true;};
					virtual bool StartBP(DalNIBPMode nibpMode){nibpMode; return true;};
					virtual bool FinishBP(){return true;};
					virtual bool AbortBP(){return true;};
					//static void OnTimerNIBPDataEvent(Object^ sender, ElapsedEventArgs^ args){true;};

					////DalConfigurationAndUsages Methods : Get
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
					
					////DalConfigurationAndUsages Methods : Set
					////---------------------------------------
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
					
					/**
					* Do the call to the EM4 after setting command
					*
					* @param[in]	inCommandCode	CommandCode 
					* @param[in]	data	data to get
					* @param[in]	inEm4ResponseReqLen	Em4 Response Required Length 
					*
					* @return	DalReturnValue
					*/
					DalReturnValue DalEm4Communication(unsigned char inCommandCode, array<unsigned char> ^%data, unsigned int inEm4ResponseReqLen);

					/**
					* Sends the SetIdleMode command in a loop until it returns a NACK 
					* or a timeout of 15 sec occurs. Waits 3 sec between each try.
					*
					* @return @c true if the Idle mode was set within the time period. 
					*			@c flase if the EM4 did not respond at all or returned NACK continuously for 15 sec
					*/
					bool SetIdleModeProcess();

			};
		}
	}
}