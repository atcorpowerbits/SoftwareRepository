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
#include "DalCommandState.h"
#include "DalCaptureState.h"
#include "DalSequenceNumberManager.h"
#include "DalActivePort.h"
#include "DalStreamingPacketQueue.h"


using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;
using namespace System::Timers;

using namespace AtCor::Scor::DataAccess::StateMachines;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			/**
			* @class DalCommandInterface
			* @brief Communicates with the EM4 device via the serial port interface and exposes methods @n
			*		to send/recieve and valide the packets
			*/
			private ref class DalCommandInterface: public DalStatusHandler
			{
				private:
					
					/*static unsigned char _sentPacketSequenceNumber;
					static unsigned char _packetSequenceMaxValue = 0x0F;
					static unsigned char _packetSequenceMinValue = 0x00;*/
					static int _tonometerDataIndex = 0;
					static int _cuffPulseDataIndex = 2;
					static int _cuffPressureDataIndex = 4;
					static int _countdownTimerDataIndex = 6; 

					static DalCommandInterface^ _instance = gcnew DalCommandInterface();
					DalCommandInterface^ operator= ( DalCommandInterface);
					
					bool ValidateCommand(DalEM4Command^ serialCommand);
					DalReturnValue ValidateCommandResult(DalEM4Command^ serialCommand, DalReturnValue responseReturnValue);

					Timers::Timer^ streamingStoppedCheckTimer;  //A timer to check whether the serial port data streaming has stopped.

					
					static DalCommandState^ _currentCommandState; //pointer to the current state object of the command state machine

					static DalCaptureState^ _currentCaptureState;  //pointer to the current state object of the capture state machine

					DalReturnValue SendCommandPacketWithRetries(DalEM4Command^ serialCommand);  

					Thread^ listenerThread;


					
				internal:
					Timers::Timer^ streamingPacketProcessingTimer; //Timer to start the method that will process x packets in each tick
					
					
					
			
					//Renamed the older SendCommand method to SendCommandAndGetResponse.
					//This is more descriptive. SendCommand does not give the real meaning.
					
					/**
					* Send the command specifed in the parameter and processes the response from EM4
					* @warning This command was previously known as SendCommand() 
					* but has been renamed to make it more meaningful. It is now a facade for ProcessCommandAndResponse()
					*
					* @param[in,out] serialCommand	A DalEM4Command object which has been initialized  with a valid command.
					* @return The status of the operation: succeded/ failed/ timout/ nack
					*/
					DalReturnValue SendCommandAndGetResponse(DalEM4Command^ serialCommand); 

					///**
					//* Send the command specifed in the parameter and processes the response from EM4
					//* @warning This command was previously known as SendCommand() 
					//* but has been renamed to make it more meaningful. It is now a facade for ProcessCommandAndResponse()
					//*
					//* @param[in,out] serialCommand	A DalEM4Command object which has been initialized  with a valid command.
					//* @return The status of the operation: succeded/ failed/ timout/ nack
					//*/
					//DalReturnValue SendPacketWithRetries(DalEM4Command^ serialCommand); 

					/**
					* Sends a command and gets the response from the EM4 @n
					* @warning This function is the same code as SendCommandAndGetResponse(previously SendCommand()) 
					*			It will do the actual code while SendCommandAndGetResponse is the facade for this method.
					* @param[in,out] serialCommand	A DalEM4Command object which has been initialized  with a valid command.
					* @return The status of the operation: succeded/ failed/ timout/ nack
					*/
					DalReturnValue ProcessCommandAndResponse(DalEM4Command^ serialCommand); 

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
					* @param[in]	serialCommand	The succesful sent & received data packet
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
					* @param[in]	serialCommand	The succesful sent & received data packet
					* @return	DalReturnValue value indiciating status of the operation
					*/
					static DalReturnValue ValidateResponsePacket(DalEM4Command^ serialCommand);

					/**
					* Validates EM4 DataCapture packet received by DataCaptureSinglePacketHandler().
					* @param[in]	capturePacket	The EM4DataCapturePacket recived from the EM4 
					* @return	DalReturnValue value indiciating status of the operation
					*/
					static DalReturnValue ValidateResponsePacket(EM4DataCapturePacket ^ capturePacket);

					//function is being moved to DalStatusHandler for unification
					///*
					//* Checks the status flag parameter and raises events on cuff or error_alarm status change
					//* @param[in] statusBytes	The status flag to check
					//* @return	status of the operation
					//*/
					//static bool CheckStatusFlag(unsigned long statusBytes);

					//moved to a different class
					/*
					* Property to obtain the a sequence number for the EM4 command 
					* Starts from 0x00 to 0x0F and rolls over.
					*/
					/*static property unsigned char SentPacketSequenceNumber
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
					};*/

					/**
					* Sets the current state of the command State machine
					*
					* @param[in]	newCommandState	The new state of the command state machine
					*/
					void ChangeCommandState(DalCommandState^ newCommandState);

					/**
					* Sets the current state of the Capture State machine
					*
					* @param[in]	newCaptureState	The new state of the capture state machine
					*/
					static void ChangeCaptureState(DalCaptureState^ newCaptureState);

					/**
					* Registers the DataCaptureSinglePacketHandler to listen to data caputre packets
					* @return	status of the operation
					*/
					virtual bool InitiateDataCaptureModeInternal();

					/**
					* De-registers the DataCaptureSinglePacketHandler to listen to data caputre packets
					* @return	status of the operation
					*/
					bool StopDataCaptureModeInternal();

					/**
					* Sets the internal instance variable to the specified object
					*
					* @param newObject	Pointer to the new object which should be acccesed when DalCommandINterface::Instance is called
					*/
					static void SetInstanceObject(DalCommandInterface^ newObject);
					
				public:

					/**
					* Constructor for the DalCommandInterface class
					* Initializes the DalCommanInterface but does not set the port
					*/
					DalCommandInterface();
					
					///*
					//* Handler for the events raised during data capture. @n
					//* Reads multiple events in a loop
					//* @param[in]	sender	Event sender. 
					//* @param[in]	e	Event arguments
					//*/
					//static void DataCaptureMultiplePacketHandler(Object^ sender, SerialDataReceivedEventArgs^ e);
			

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

					/*
					* Sets the current SerialPort Object to the specified port name
					* @param  serialPortName The serial port to set
					* @return	status of the operation
					*/
					//bool SetActivePort( String^ serialPortName);

					/*
					* Sets the port name for the current serial port object.
					* @param  serialPortName The serial port to set
					* @return	status of the operation
					* @warning Check if the serialport instance is not null before calling.
					*/
					//bool SetActivePortInstance(String^ serialPortName);

					/*
					* Sets the properties of the internal serialPort object
					* @return	status of the operation
					*/
					//bool SetSerialPortProperties();

					//bool CreateAndOpenNewSerialPort(String^ newPortName);

					//bool CloseActivePort();

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

					///*
					//* Returns the name of the currently active serial port.
					//* @warning Will return @c null if the current serial port object is not set.
					//*/
					//property String^ ActiveSerialPortName
					//{
					//	String^ get()
					//	{
					//		if (_serialPort)
					//		{
					//			return _serialPort->PortName;
					//		}
					//		else
					//		{
					//			//we will return a null string to indicate that the serialPort object hasnt been initialized.
					//			return nullptr;
					//		}
					//	};
					//}

					

					///*
					//* Cleans the input buffer and dumps the unread packets into the log file.
					//* Called when there an illegal data packet is received @n
					//* cleans the input buffer and dumps the remaining values into the logfile.
					//* @param[in]	serialPort	The serial port object
					//* @param[in]	currentDataPacket	The data packet to be dumped. 
					//*/
					//static bool DumpInputBufferOnFailure(SerialPort^ serialPort, array<unsigned char> ^currentDataPacket);


					///*
					//* Processes the input buffer for data packets. @n
					//* Reads multiple data packets in a loop and writes them to the circula buffer.
					//* @param[in]	sender	Event sender. 
					//* @param[in]	e	Event arguments
					//* @see DataCaptureMultiplePacketHandler
					//*/
					//static void ReadFromPortAndWriteToBuffer(Object^ sender, SerialDataReceivedEventArgs^ e);

					///*
					//* Searches for the response to a particulr serial command in a large array. @n
					//* @param[in]	serialCommand	The command whose response we need to search in the array. 
					//* @param[in]	sourceArray		The array in which the search is conducted
					//* @return		A boolan value indicating the status of the operation: @n
					//*				@c true if a valid response to the command was found( can be an Ack or nack)
					//*				@c false if no response was found.
					//*/
					//bool ExtractRequiredResponseFromArray(DalEM4Command^ serialCommand, array <unsigned char> ^ sourceArray);


					/**
					* Public exposed member that is called via the state machine.
					* Internally calls CheckIfTimeoutHasOccurredInternal in the correct state.
					*
					* @param[in]	sender	The object that raised this event.
					* @param[out]	args	The timer event arguments.
					*
					*/
					static void CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args);

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
					static void CheckIfTimeoutHasOccurredInternal(Object^ sender, ElapsedEventArgs^ args);

					/**
					* Processes a single packet from the streamign packet buffer.
					* @param[in]	streamingPacket A byte array to be processed
					* @return	The status of the operaton
					*/
					virtual bool ProcessSingleStreamingPacket(array<unsigned char> ^ streamingPacket);

					/**
					* Loops throug all available streaming packets and processes them
					*
					* @return	The status of the operaton
					*/
					bool ProcessStreamingPackets();

					/**
					* TImer event handler which processes all available packets when raised
					*
					* @param[in]	sender	The object which raised the event
					* @param[in]	e	The ElapsedEventArgs for this timer 
					*/
					void StreamingPacketReadHandler(Object ^sender, ElapsedEventArgs^ e);

					/**
					*	Asynchronous listener that waits for a response to arrive in the response buffer
					*	Times out if no data is recieved within the expected time as specifed in the repsonsePacket
					*
					*	@param[in,out]	responsePacket	The EM4 command-repsonse object in which the response is copied 
					*/
					void ResponseListenerThreadMethod(Object^ responsePacket);

					/**
					* Lets the processing thread know that there are streaming packets witing for processing in the queue
					*
					*/
					void SignalResponsePacketAvailable();

				
			};
		}
	}
}