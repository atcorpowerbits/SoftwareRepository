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
					DalCommandInterface^ _commandInterface;
					//CrxLogger ^logObj;
					CrxMessagingManager ^ messagingMgr;
					DalDataBuffer ^dataBufferObj; //to hold pointer to object
					static DalDeviceHandler^ _instance = gcnew DalDeviceHandler();

					/**
					* Overloaded assignment Operator. @n
					* Returns this pointer to implement singleton.
					*/
					DalDeviceHandler^ operator=( DalDeviceHandler^) 
					{
						return this;
					}  
					
				public:
					/**
					* Constructor for the class.
					*/
					DalDeviceHandler(); 


					///*
					//* Start the data capture fromt the device.
					//*
					//* @warning This is a stub only. It is not meant to be used and is only retained for compatibility with stub.
					//*/
					//virtual bool StartCapture(); //obsolete

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
					virtual String^ GetAlarmSource() new; 

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
					
					//No need to chjeck tonometer status 
					//It wont be returned correctly by EM4
					///*
					//* Checks if the tonometer is connected
					//* @return @c true if the tonometer is connected properly
					//*/
					//bool CheckIfTonometerIsConnected();

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
					* Sets the EM4 mode to Idle mode
					*
					* @return The result of the operation
					*/
					virtual bool SetIdleMode();


			};
		}
	}
}