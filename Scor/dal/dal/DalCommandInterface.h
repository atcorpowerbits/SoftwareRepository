/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCommandInterface.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for DalCommandInterface class
*/
#pragma once

#include "stdafx.h"
#include "IDalHandler.h"
#include "DalCommon.h"
#include "DalEM4Command.h"



using namespace System;
using namespace System::IO::Ports;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalCommandState
			* @brief Class for command state
			* @warning	Not yet implemented
			*/
			private ref class DalCommandState
			{
				//TODO: add the class definition
			};

			/**
			* @class DalCommandInterface
			* @brief Communicates with the EM4 device via the serial port interface and exposes methods @n
			*		to send/recieve and valide the packets
			*/
			private ref class DalCommandInterface: public DalStatusHandler
			{
				private:
					SerialPort ^_serialPort;
					unsigned char _sentPacketSequenceNumber;

					DalCommandInterface();
					
					bool ValidateCommand(DalEM4Command^ serialCommand);
					DalReturnValue ValidateCommandResult(DalEM4Command^ serialCommand, DalReturnValue responseReturnValue);
					
				internal:
					DalCommandState _currentState; /**< Current state of the interface. Unused */
					
					/**
					* Converts the specifed byte array into an unsigned short integer @n
					* Converts two bytes to an unsigned short integer
					* @param[in]	sourceArray	The byte array from which the integer is to be extracted
					* @param[in]	startPostion	Start index for the bytes
					* @return	An  unsigned short integer containing the translated bytes
					*/
					static unsigned short TranslateTwoBytes( array <unsigned char>^ sourceArray, int startPostion);
					
					/**
					* Converts the specifed byte array into an unsigned long integer
					* Converts four bytes to an unsigned long integer
					* @param[in]	sourceArray	The byte array from which the integer is to be extracted
					* @param[in]	startPostion	Start index for the bytes
					* @return	An  unsigned long integer containing the translated bytes
					*/
					static unsigned long TranslateFourBytes( array <unsigned char>^ sourceArray, int startPostion);
			
					/**
					* Send the command specifed in the parameter and evaluate the response
					* @param[in,out] serialCommand	A DalEM4Command object which has been initialized  with a valid command.
					* @return The status of the operation: succeded/ failed/ timout/ nack
					*/
					DalReturnValue SendCommand(DalEM4Command^ serialCommand); 

					/**
					* Obtains the response from the port for the command sent by SendCommand
					* @param[in,out] serialCommand	A DalEM4Command object which has been initialized  with a valid command.
					*								This method  will write the EM4 response to the same structure.
					* @return The status of the operation: succeded/ failed/ timout/ nack
					* @warning Do not use for data capture.
					*/
					DalReturnValue ListenForEM4Response(DalEM4Command^ serialCommand);

					/**
					* Validates the CRC of the EM4 response for a succesfully sent command
					* @param[in]	serialCommand	The succesful sent & recieved data packet
					* @return	boolean value indiciating status of the operation
					*/
					static bool ValidateResponseCRC(DalEM4Command^ serialCommand);

					/**
					* Validates the CRC of the EM4 DataCapture packet
					* @param[in]	capturePacket	The EM4DataCapturePacket recived from the EM4 
					* @return	boolean value indiciating status of the operation
					*/
					static bool ValidateResponseCRC(EM4DataCapturePacket ^ capturePacket);

					/**
					* Validates the EM4 response for a succesfully sent command
					* @param[in]	serialCommand	The succesful sent & recieved data packet
					* @return	DalReturnValue value indiciating status of the operation
					*/
					static DalReturnValue ValidateResponsePacket(DalEM4Command^ serialCommand);

					/**
					* Validates EM4 DataCapture packet recieved by DataCaptureHandler().
					* @param[in]	capturePacket	The EM4DataCapturePacket recived from the EM4 
					* @return	DalReturnValue value indiciating status of the operation
					*/
					static DalReturnValue ValidateResponsePacket(EM4DataCapturePacket ^ capturePacket);

					/**
					* Checks the status flag parameter and raises events on cuff or error_alarm status change
					* @param[in] statusBytes	The status flag to check
					* @return	status of the operation
					*/
					static bool CheckStatusFlag(unsigned long statusBytes);
					
				public:
					/**
					* Constructor for the DalCommandInterface class
					* Initializes the object using the specifed port name
					* @param[in]	em4DevicePortName	The port anme to initilize this instance
					*/
					DalCommandInterface(String^ em4DevicePortName);

					/**
					* Handler for the events raised during data capture
					* @param[in]	sender	Event sender. 
					* @param[in]	e	Event arguments
					*/
					static void DataCaptureHandler(Object^ sender, SerialDataReceivedEventArgs^ e);

					/**
					* Registers the DataCaptureHandler to listen to data caputre packets
					* @return	status of the operation
					*/
					bool InitiateDataCaptureMode();

					/**
					* De-registers the DataCaptureHandler to listen to data caputre packets
					* @return	status of the operation
					*/
					bool StopDataCaptureMode();
			};
		}
	}
}