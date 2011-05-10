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
#include "DalEM4DataCapturePacket.h"
#include "DalStatusHandler.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;
using namespace System::Timers;

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
					
					static unsigned char _sentPacketSequenceNumber;
					static unsigned char _packetSequenceMaxValue = 0x0F;
					static unsigned char _packetSequenceMinValue = 0x00;
					static int _tonometerDataIndex = 0;
					static int _cuffPulseDataIndex = 2;
					static int _cuffPressureDataIndex = 4;
					static int _countdownTimerDataIndex = 6;

					static DalCommandInterface^ _instance = gcnew DalCommandInterface();
					DalCommandInterface^ operator= (const DalCommandInterface);
					
					bool ValidateCommand(DalEM4Command^ serialCommand);
					DalReturnValue ValidateCommandResult(DalEM4Command^ serialCommand, DalReturnValue responseReturnValue);

					SerialPort ^_serialPort;

					Timers::Timer^ streamingStoppedCheckTimer;  //A timer to check whether the serial port data streaming has stopped.
					

					
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
					* Validates EM4 DataCapture packet recieved by DataCaptureSinglePacketHandler().
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

					/**
					* Property to obtain the a sequence number for the EM4 command 
					* Starts from 0x00 to 0x0F and rolls over.
					*/
					static property unsigned char SentPacketSequenceNumber
					{
						unsigned char get()
						{
							unsigned char returnValue;
							
							returnValue = _sentPacketSequenceNumber++;
							if (_sentPacketSequenceNumber > _packetSequenceMaxValue)
							{
								_sentPacketSequenceNumber = _packetSequenceMinValue;
							}
							
							return returnValue;
						};
					};
					
				public:

					/**
					* Constructor for the DalCommandInterface class
					* Initializes the DalCommanInterface but does not set the port
					*/
					DalCommandInterface();
					
					/**
					* Handler for the events raised during data capture. @n
					* Reads multiple events in a loop
					* @param[in]	sender	Event sender. 
					* @param[in]	e	Event arguments
					*/
					static void DataCaptureMultiplePacketHandler(Object^ sender, SerialDataReceivedEventArgs^ e);
			

					/**
					* Registers the DataCaptureSinglePacketHandler to listen to data caputre packets
					* @return	status of the operation
					*/
					bool InitiateDataCaptureMode();

					/**
					* De-registers the DataCaptureSinglePacketHandler to listen to data caputre packets
					* @return	status of the operation
					*/
					bool StopDataCaptureMode();

					//Deepak: uncalled as of now. May need later - FxCop
					///*
					//* Sets the current SerialPort Object to the specified parameter
					//* @param  serialPortObject The serial port object to specify
					//* @return	status of the operation
					//*/
					//bool SetActivePort( SerialPort^ serialPortObject);

					/**
					* Sets the current SerialPort Object to the specified port name
					* @param  serialPortName The serial port to set
					* @return	status of the operation
					*/
					bool SetActivePort( String^ serialPortName);

					/**
					* Sets the port name for the current serial port object.
					* @param  serialPortName The serial port to set
					* @return	status of the operation
					* @warning Check if the serialport instance is not null before calling.
					*/
					bool SetActivePortInstance(String^ serialPortName);

					/**
					* Sets the properties of the internal serialPort object
					* @return	status of the operation
					*/
					bool SetSerialPortProperties();

					bool CreateAndOpenNewSerialPort(String^ newPortName);

					bool CloseActivePort();

					/**
					* Returns the current singleton instance.
					*/
					static property DalCommandInterface^ Instance
					{
						DalCommandInterface^ get()
						{
							return DalCommandInterface::_instance;
						};
					};

					/**
					* Returns the name of the currently active serial port.
					* @warning Will return @c null if the current serial port object is not set.
					*/
					property String^ ActiveSerialPortName
					{
						String^ get()
						{
							if (_serialPort)
							{
								return _serialPort->PortName;
							}
							else
							{
								//we will return a null string to indicate that the serialPort object hasnt been initialized.
								return nullptr;
							}
						};
					}

					

					/** 
					* Cleans the input buffer and dumps the unread packets into the log file.
					* Called when there an illegal data packet is recieved @n
					* cleans the input buffer and dumps the remaining values into the logfile.
					* @param[in]	serialPort	The serial port object
					* @param[in]	currentDataPacket	The data packet to be dumped. 
					*/
					static bool DumpInputBufferOnFailure(SerialPort^ serialPort, array<unsigned char> ^currentDataPacket);


					/** 
					* Processes the input buffer for data packets. @n
					* Reads multiple data packets in a loop and writes them to the circula buffer.
					* @param[in]	sender	Event sender. 
					* @param[in]	e	Event arguments
					* @see DataCaptureMultiplePacketHandler
					*/
					static void ReadFromPortAndWriteToBuffer(Object^ sender, SerialDataReceivedEventArgs^ e);

					/** 
					* Searches for the response to a particulr serial command in a large array. @n
					* @param[in]	serialCommand	The command whose response we need to search in the array. 
					* @param[in]	sourceArray		The array in which the search is conducted
					* @return		A boolan value indicating the status of the operation: @n
					*				@c true if a valid response to the command was found( can be an Ack or nack)
					*				@c false if no response was found.
					*/
					bool ExtractRequiredResponseFromArray(DalEM4Command^ serialCommand, array <unsigned char> ^ sourceArray);


					/**
					* Event handler to check if data buffer is empty.
					* Increments a counter if the buffer is empty and resets it to zero
					* if it is not . If the counter reaches @ref DalConstants::MaxStreamingTimeoutOccurrences 
					* then it raises an OnDalModuleErrorAlarmEvent
					*
					* @param[in]	sender	The object that raised this event.
					* @param[out]	args	The timer event arguments.
					*
					*/
					static void CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args);
			
			};
		}
	}
}