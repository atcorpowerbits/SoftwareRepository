/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCommandInterface.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      source file for DalCommandInterface class
*/

#include "stdafx.h"
#include "DalCommandInterface.h"
#include "DalDeviceHandler.h"
#include "DalCommon.h"
#include "DalEventContainer.h"
#include "DalCaptureState.h"
#include "DalStagingQueue.h"
#include "DalSequenceNumberManager.h"
#include "DalResponsePacketBuffer.h"
#include "DalBinaryConversions.h"

using namespace System;
using namespace System::IO::Ports;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::DataAccess::StateMachines;
using namespace AtCor::Scor::CrossCutting::Configuration;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{
			DalCommandInterface::DalCommandInterface()
			{
				//We should not create the default serial port object since it sets to COM1
				
				_currentCommandState = DalCommandStateReady::Instance;
				_currentCaptureState = DalCaptureStateNotListening::Instance;
				
			}


			bool DalCommandInterface::ValidateCommand(DalEM4Command^ serialCommand)
			{
				if (nullptr == serialCommand )
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrEmptyCommandErrCd, CrxStructCommonResourceMsg::DalErrEmptyCommand, ErrorSeverity::Exception);
				}

				if (0x00 == serialCommand->commandCode )  
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrEmptyCommandErrCd, CrxStructCommonResourceMsg::DalErrEmptyCommand, ErrorSeverity::Exception);
				}

				//if (!_serialPort->IsOpen)
				if (!DalActivePort::Instance->CurrentPort->IsOpen)
				{
					//pport is not open
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrPortNotOpenErrCd, CrxStructCommonResourceMsg::DalErrPortNotOpen, ErrorSeverity::Exception);
				}

				return true;
			}

			//Renamed to make it more meaningful 
			//SendCommand->SendCommandAndGetResponse->ProcessCommandAndResponse
			DalReturnValue DalCommandInterface::ProcessCommandAndResponse(DalEM4Command^ serialCommand)
			{
				DalReturnValue responseReturnValue = DalReturnValue::Failure; //initialize to failure
				
				if (!ValidateCommand(serialCommand))
				{
					return DalReturnValue::Failure;
				}
				
				////set the timeout period
				////_serialPort->ReadTimeout = serialCommand->timeoutPeriod;
				////DalActivePort::Instance->CurrentPort->ReadTimeout = serialCommand->timeoutPeriod;
				//DalActivePort::Instance->CurrentPort->ReadTimeout = SerialPort::InfiniteTimeout ;

				////Setting to infinite timeout for testing new read/write class
				////The timeout value is still active. see if it can be used or if infinite is fine
				////TODO: attend to this



				////Retry as many times as specified for the command 
				//do 
				//{
				//	try
				//	{
				//		//DO not discard bytes any more
				//		////clear the input buffer before sending a command 
				//		////so that any remenant bits dont get prefixed to the response
				//		////_serialPort->DiscardInBuffer();
				//		//DalActivePort::Instance->CurrentPort->DiscardInBuffer();


				//		////if (0 != _serialPort->BytesToRead )
				//		//if (0 != DalActivePort::Instance->CurrentPort->BytesToRead )
				//		//{
				//		//	//array <unsigned char> ^ dumparray = gcnew array<unsigned char> (_serialPort->BytesToRead);
				//		//	//_serialPort->Read(dumparray, 0, _serialPort->BytesToRead);
				//		//	array <unsigned char> ^ dumparray = gcnew array<unsigned char> (DalActivePort::Instance->CurrentPort->BytesToRead);
				//		//	DalActivePort::Instance->CurrentPort->Read(dumparray, 0, DalActivePort::Instance->CurrentPort->BytesToRead);
				//		//}
				//		//
				//		//DalActivePort::Instance->CurrentPort->DiscardOutBuffer();

				//		//Instead of directly sending command we will call the dallActive port function
				//		//DalActivePort::Instance->CurrentPort->Write(serialCommand->em4Command,0, serialCommand->commandLength +1); //1 for CRC byte
				//		DalActivePort::Instance->SendPacket(serialCommand->em4Command);

				//		//Log it in DalActivePort
				//		////CrxLogger::Instance->Write("Deepak>>> Command sent on port:  " +  ConvertBytesToString(serialCommand->em4Command));
				//	}
				//	catch(Exception^ excepObj)
				//	{
				//		throw gcnew ScorException(excepObj);
				//	}

				//	//change state before the latency wait
				//	DalCommandInterface::Instance->ChangeCommandState(DalCommandStateWaiting::Instance);

				//	//wait to allow the response to arrive
				//	Thread::Sleep(DalConstants::EM4LatencyPeriod);

				//	//check here for response 
				//	//responseReturnValue = ListenForEM4Response(serialCommand);
				//	responseReturnValue = _currentCommandState->ListenForEM4Response(serialCommand);
				//} while((serialCommand->retryNumber < serialCommand->retriesAllowed ) && (responseReturnValue == DalReturnValue::Timeout));
				////} while((serialCommand->retryNumber < serialCommand->retriesAllowed ) && (responseReturnValue != DalReturnValue::Success ));
				//
				
				responseReturnValue = SendCommandPacketWithRetries(serialCommand);

				return ValidateCommandResult(serialCommand, responseReturnValue);
				//return _currentCommandState->ValidateCommandResult(serialCommand, responseReturnValue);

			}

			DalReturnValue DalCommandInterface::SendCommandPacketWithRetries(DalEM4Command^ serialCommand)
			{
				DalReturnValue responseReturnValue = DalReturnValue::Failure; //initialize to failure

				//set the timeout period
				//DalActivePort::Instance->CurrentPort->ReadTimeout = serialCommand->timeoutPeriod;
				//DalActivePort::Instance->CurrentPort->ReadTimeout = SerialPort::InfiniteTimeout ;
			

				//Setting to infinite timeout for testing new read/write class
				//The timeout value is still active. see if it can be used or if infinite is fine
				//TODO: attend to this

				//Retry as many times as specified for the command 
				do 
				{
					try
					{
						//DO not discard bytes from the serial port any more

						//Clear the response buffer so as to avoid any previous "response" from being accepted as correct
						DalResponsePacketBuffer::Instance->Clear();

						//inform the StaqignQueManager that it should look for a response to this command
						DalStagingQueue::Instance->LookForResponseToCommand(serialCommand->commandCode, (unsigned char)(serialCommand->expectedResponseLength), serialCommand->commandSequenceNumber);
						
						//Instead of directly sending command we will call the dallActive port function
						DalActivePort::Instance->SendPacket(serialCommand->em4Command);

					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
					}

					//change state before the latency wait
					DalCommandInterface::Instance->ChangeCommandState(DalCommandStateWaiting::Instance);

					////wait to allow the response to arrive
					//Thread::Sleep(DalConstants::EM4LatencyPeriod); //TODO: rechek if necessary

					//check here for response 
					responseReturnValue = _currentCommandState->ListenForEM4Response(serialCommand);

				} while((serialCommand->retryNumber < serialCommand->retriesAllowed ) && (responseReturnValue == DalReturnValue::Timeout));
				//only retry if a timeout has occured.

				//check if there has been a timeout after three retries
				if( DalReturnValue::Timeout == responseReturnValue)
				{
					//tell the staging que to stop looking for the number
					DalStagingQueue::Instance->StopLookingForResponse();

					//if yes then return immediately singalling a fialure
					return responseReturnValue;
				}
				else
				{
					//if not then process the command
					responseReturnValue =  _currentCommandState->ValidateResponsePacket(serialCommand);

					DalCommandInterface::Instance->ChangeCommandState(DalCommandStateReady::Instance);
					return responseReturnValue;
				}
			}

			DalReturnValue DalCommandInterface::ValidateCommandResult(DalEM4Command^ serialCommand, DalReturnValue responseReturnValue)
			{
				if ((responseReturnValue != DalReturnValue::Success ) && (serialCommand->retryNumber > serialCommand->retriesAllowed ))
				{
					return DalReturnValue::Timeout ;
				}
				else if (responseReturnValue == DalReturnValue::Failure )
				{
					return DalReturnValue::Failure;
				}
				else
				{
					return responseReturnValue;
				}
			}


			//void DalCommandInterface::DataCaptureMultiplePacketHandler(Object^ sender, SerialDataReceivedEventArgs^ e)
			//{
			//	DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateDataReceived::Instance);
			//	//ReadFromPortAndWriteToBuffer(sender, e);
			//	_currentCaptureState->ReadFromPortAndWriteToBuffer(sender, e);
			//}


			//void DalCommandInterface::ReadFromPortAndWriteToBuffer(Object^ sender, SerialDataReceivedEventArgs^ e)
			//{
			//	e; //Dummy statement to get rid of C4100 warning

			//	DalPwvDataStruct pwvDataObject ;
			//	int bytesRead;
			//	EM4DataCapturePacket^ capturePacket = gcnew EM4DataCapturePacket(DalConstants::PWVCaptureDataSize); 
			//
			//	SerialPort^ locSerialPort = (SerialPort^)sender;

			//	DalDataBuffer^ dataBufferObj = DalDataBuffer::Instance;

			//	int singlePacketSize = DalConstants::PWVCaptureDataSize + DalConstants::EM4ZeroDataResponsePacketSize +1 ;

			//	int numberofPacketsToRead = DalConstants::DeviceNumberOfReadsPerInterval ;

			//	//CrxLogger::Instance->Write("Deepak>>> ReadFromPortAndWriteToBuffer() called");

			//	
			//	for (int loopCounter = 0; loopCounter < numberofPacketsToRead; loopCounter++)
			//	{
			//		try
			//		{
			//			if (locSerialPort->BytesToRead < singlePacketSize)
			//			{
			//				//it may be possible that the event has been fired but the actual number of bytes is less.
			//				//return so that the buffer can be filled.
			//			//	//CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> less bytes to read : "+ locSerialPort->BytesToRead );
			//				return;
			//			}
			//			//else read a single packet from port
			//			bytesRead = locSerialPort->Read(capturePacket->em4Response, 0, singlePacketSize);
			//			
			//			//This comment is needed to debug EM4 packtes. Will be kept till it is tested on EM4 device. 
			//			//Remove after development is completed
			//			//CrxLogger::Instance->Write("Deepak>>> ReadFromPortAndWriteToBuffer() Data read from port:  bytes read =  " + bytesRead + " Packet: " +  ConvertBytesToString(capturePacket->em4Response));
			//			
			//			if (bytesRead != singlePacketSize)
			//			{
			//				//insufficient data for a single packet
			//				////CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> less bytes read from port: "+ bytesRead );
			//				continue;

			//			}
			//			//write the number of bytes received so that it can be validated against the length received from EM4
			//			capturePacket->em4ResponsePacketLength = bytesRead - 1; //excluding CRC
			//		
			//			//split the received array into individual components 
			//			//for valdiation and transfering to buffer.
			//			if (!(capturePacket->BreakupEM4Response()))
			//			{
			//			//	//CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> breakup failed "+ ConvertBytesToString(capturePacket->em4Response));
			//				//call the dump method before returning
			//				DumpInputBufferOnFailure(locSerialPort, capturePacket->em4Response);
			//				//throw gcnew ScorException(1029,"DAL_ERR_CAPTURE_INVALID_PACKET", ErrorSeverity::Information);
			//				throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCaptureInvalidPacketErrCd,CrxStructCommonResourceMsg::DalErrCaptureInvalidPacket, ErrorSeverity::Information);
			//			}

			//			//validate the data.
			//			if (ValidateResponsePacket(capturePacket)!= DalReturnValue::Success)
			//			{
			//				throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCaptureInvalidPacketErrCd,CrxStructCommonResourceMsg::DalErrCaptureInvalidPacket, ErrorSeverity::Information);
			//			}

			//			//everything is fine now get the data. and write it to the variables
			//			pwvDataObject.tonometerData = TranslateTwoBytes(capturePacket->em4ResponseData, _tonometerDataIndex);
			//			pwvDataObject.cuffPulseData = TranslateTwoBytes(capturePacket->em4ResponseData, _cuffPulseDataIndex);
			//			pwvDataObject.cuffPressure  = TranslateTwoBytes(capturePacket->em4ResponseData, _cuffPressureDataIndex);
			//			pwvDataObject.countdownTimer = TranslateTwoBytes(capturePacket->em4ResponseData, _countdownTimerDataIndex);

			//			////CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>>" + " tonometerData: " + pwvDataObject.tonometerData + " cuffPulseData: " + pwvDataObject.cuffPulseData + " countdownTimer: " + pwvDataObject.countdownTimer);

			//			if(!dataBufferObj->WriteDataToBuffer(pwvDataObject))
			//			{
			//				////CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> write to buff failed ");
			//				throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferWriteFailedErrCd, CrxStructCommonResourceMsg::DalErrBufferWriteFailed, ErrorSeverity::Exception);
			//			}
			//		
			//		}
			//		catch(ScorException^ scorExObj)
			//		{
			//			//if we rethrow this exception , it will be unhandled. 
			//			//This is because this exception is raised in a 
			//			//method which has no caller and operates on its own thread.
			//			//THos causes the application to crash due to unhandled exception even though there is an exception handler in GUI.
			//			//So we are deleting this exception instead of rethrowing it.
			//			//To inform the upper layers, we are raising an OnDalModuleErrorAlarmEvent event.
			//			//This particular type (DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket) needs to be handled by
			//			//upper layers which need to decide what to do in this case.

			//			//Attempting to deregister the serial port DataRecieved event handler is useless because
			//			//serial port cannot be modified in a static method. 
			//			//we also tried calling Stop capture in GUI but that needs the method to be static.
			//			//It would result in  a lot of code refactoring.
			//			
			//			//TODO: mention this in release note
			//			delete scorExObj ;
			//			String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, DalFormatterStrings::PrintEnumName);
			//			DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName);
			//			DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);
			//		}
			//		catch(Exception^ excepObj)
			//		{
			//			//see note above.
			//			delete excepObj;
			//			String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, DalFormatterStrings::PrintEnumName);
			//			DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName);
			//			DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);

			//		}
			//	}//end for
			//}

			//DalReturnValue DalCommandInterface::ListenForEM4Response(DalEM4Command^ serialCommand)
			//{
			//	serialCommand->em4Response = nullptr;
			//	
			//	int dataWaiting = DalActivePort::Instance->CurrentPort->BytesToRead;
			//	if (dataWaiting == 0)
			//	{
			//		DalCommandInterface::Instance->ChangeCommandState(DalCommandStateTimeout::Instance);
			//		
			//		serialCommand->retryNumber++;
			//		return DalReturnValue::Timeout;
			//	}

			//	//create a sperate array to read the response . it may contain additional bytes if data capture is in place
			//	array <unsigned char>^ recievedData = gcnew array <unsigned char>(dataWaiting);
			//	int bytesRead = 0;

			//	try
			//	{
			//		bytesRead = DalActivePort::Instance->CurrentPort->Read(recievedData, 0, dataWaiting);

			//		//This comment is needed to debug EM4 packtes. Will be kept till it is tested on EM4 device. 
			//		//Remove after development is completed
			//		//CrxLogger::Instance->Write("Deepak>>> ListenForEM4Response() Data read from port:  bytes read =  " + bytesRead + " Packet: " +  ConvertBytesToString(recievedData));
			//			
			//	}
			//	catch(TimeoutException^)
			//	{
			//		DalCommandInterface::Instance->ChangeCommandState(DalCommandStateTimeout::Instance);
			//		serialCommand->retryNumber++;
			//		return DalReturnValue::Timeout;
			//	}

			//	if (bytesRead<dataWaiting)
			//	{
			//		serialCommand->retryNumber++;
			//		return DalReturnValue::Failure ;
			//	}
			//	else if (bytesRead > ((int)(serialCommand->expectedResponseLength )+1))
			//	{
			//		//check if there is some expected length . if yes then it should be validated.

			//		if (!ExtractRequiredResponseFromArray(serialCommand, recievedData))
			//		{
			//			return DalReturnValue::Failure ;
			//		}

			//	}
			//	else
			//	{
			//		//the packet is of the right size.
			//		//copy it directly to serialCommand->em4Response
			//		serialCommand->em4Response  = gcnew array<unsigned char>(recievedData->Length );
			//		recievedData->CopyTo(serialCommand->em4Response, 0);
			//		serialCommand->em4ResponsePacketLength = bytesRead - 1; //excluding CRC
			//	}

			//	//if we have come this far then the data is available
			//	DalCommandInterface::Instance->ChangeCommandState(DalCommandStateResponseReceived::Instance);

			//	//if everthing is fine and the data is recoeved 
			//	//validate the packet

			//	DalReturnValue returnValue;
			//	//returnValue =  ValidateResponsePacket(serialCommand);
			//	returnValue =  _currentCommandState->ValidateResponsePacket(serialCommand);


			//	DalCommandInterface::Instance->ChangeCommandState(DalCommandStateReady::Instance);
			//	
			//	return returnValue;
			//}


			DalReturnValue DalCommandInterface::ListenForEM4Response(DalEM4Command^ serialCommand)
			{
				//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ListenForEM4Response() : Start" );
				listenerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &DalCommandInterface::ResponseListenerThreadMethod));

				listenerThread->Start(serialCommand); //pass the command object so that we can copy the variable directly

				listenerThread->Join(); //Wait for the data to come 
				if (nullptr == serialCommand->em4Response )
				{
					CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ListenForEM4Response() : No data recieved : timing out");

					DalCommandInterface::Instance->ChangeCommandState(DalCommandStateTimeout::Instance);
					
					//we still recived no data so we are timing out
					serialCommand->retryNumber++; //increment the counter
					return DalReturnValue::Timeout;
				}

				CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ListenForEM4Response() : recievedData:" + DalBinaryConversions::ConvertBytesToString(serialCommand->em4Response));

				//we have recieved data so signify that we have recieved it
				DalCommandInterface::Instance->ChangeCommandState(DalCommandStateResponseReceived::Instance);

				//Set the length. The length could either be of the desired size or it could be a NACK lengt.
				serialCommand->em4ResponsePacketLength = serialCommand->em4Response->Length - 1; //excluding CRC

				return DalReturnValue::Success; //signify success to the caller
				//The caller should then validate the resposne
			}

			bool DalCommandInterface::ValidateResponseCRC (DalEM4Command^ serialCommand)
			{
				bool returnValue;

				if (serialCommand->em4Response == nullptr)
				{
					return false;
				}

				//generate the CRC
				DalCRC8Calculator ^ crcCalculator = DalCRC8Calculator::Instance;
				unsigned char generatedCRCValue = 0x00;
				unsigned char recivedCRCValue = serialCommand->em4ResponseCRCByte;
				returnValue= crcCalculator->ComputeCrc8ForArray(serialCommand->em4Response, serialCommand->em4ResponsePacketLength, &generatedCRCValue);

				 if (false == returnValue)
				 {
					 return false;
				 }
				 else if (generatedCRCValue != recivedCRCValue)
				 {
					return false;
				 }
				 else
				 {
					 return true;
				 }
			}

			Boolean DalCommandInterface::ValidateResponseCRC(EM4DataCapturePacket ^ capturePacket)
			{
				bool returnValue;

				if (capturePacket->em4Response == nullptr)
				{
					return false;
				}

				//generate the CRC
				DalCRC8Calculator ^ crcCalculator = DalCRC8Calculator::Instance;
				unsigned char generatedCRCValue = 0x00;
				unsigned char recivedCRCValue = capturePacket->em4ResponseCRCByte;
				returnValue= crcCalculator->ComputeCrc8ForArray(capturePacket->em4Response, capturePacket->em4ResponsePacketLength, &generatedCRCValue);

				 if (false == returnValue)
				 {
					 return false;
				 }
				 else if (generatedCRCValue != recivedCRCValue)
				 {
					return false;
				 }
				 else
				 {
					 return true;
				 }
			}

			DalReturnValue DalCommandInterface::ValidateResponsePacket(DalEM4Command^ serialCommand)
			{

				unsigned long statusBytes ;

				if (serialCommand->em4Response == nullptr)
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrEmptyResponseValidationErrCd, CrxStructCommonResourceMsg::DalErrEmptyResponseValidation, ErrorSeverity::Exception);
				}
				//CrxLogger::Instance->Write("Deepak>>> ValidateResponsePacket() : " + ConvertBytesToString(serialCommand->em4Response));

				//Call the method to break the response into individual partes;
				if (!serialCommand->BreakupEM4Response())
				{
					return DalReturnValue::Failure;
				}

				unsigned char responseCode = serialCommand->em4Response[(int)Em4ResponseByteIndex::AckNackByte ];

				if ((responseCode & (unsigned char)DalAckNackByteMask::CommandCodeBitsMask ) != serialCommand->commandCode )
				{
					//the reply is for another command incorrect
					return DalReturnValue::Failure;
				}

				if (!(responseCode & (unsigned char)DalAckNackByteMask::AckNackStatusBitMask))
				{
					//EM4 returned NACK
					return DalReturnValue::NoAck;
				}

				//now validate the CRC
				if (!(ValidateResponseCRC(serialCommand)))
				{
					return DalReturnValue::Failure ;
				}

				//assign the status flag to a variable
				statusBytes = (unsigned long) serialCommand->em4StatusFlag ;
				ProcessStatusFlag(statusBytes);
				
				//validate sequence number

				if (CrxSytemParameters::Instance->GetStringTagValue("ProcessSequenceNumber.CommandResponse") == "Y")
				{

					//Replacing with another class
					//if (serialCommand->commandSequenceNumber != serialCommand->em4ResponseSequenceNumber)
					if (!(DalSequenceNumberManager::ValidateCommandResponseSequenceNumber(serialCommand->commandSequenceNumber, serialCommand->em4ResponseSequenceNumber)))
					{
						return DalReturnValue::Failure;
					}
				}

				return DalReturnValue::Success ;
			}

			


			DalReturnValue DalCommandInterface::ValidateResponsePacket(EM4DataCapturePacket ^capturePacket)
			{

				unsigned long statusBytes ;

				//Breakup response is called outside the method
	
				//the reply value should be for 07
				if (capturePacket->em4ResponseAckNackByte != (unsigned char)DalAckNackByteMask::DataCaptureCodeAckedByte ) 
				{
					//the reply is for another command incorrect
					return DalReturnValue::Failure;
				}

				//now validate the CRC
				if (!(ValidateResponseCRC(capturePacket)))
				{
					return DalReturnValue::Failure ;
				}

				//assign the status flag to a variable
				statusBytes = (unsigned long) capturePacket->em4StatusFlag ;
				
				//no need to return value based on the status flag. ACK/NACK is enough 
				//In any case ProcessStatusFlag returns true
				/*if (!ProcessStatusFlag(statusBytes))
				{
					return DalReturnValue::Failure ;
				}*/

				ProcessStatusFlag(statusBytes);

				if (CrxSytemParameters::Instance->GetStringTagValue("ProcessSequenceNumber.StreamingPackets") == "Y")
				{
					//validate the sequecne number
					if (!DalSequenceNumberManager::ValidateStreamingSequenceNumber(capturePacket->em4ResponseSequenceNumber))
					{
						return DalReturnValue::Failure;
					}
				}	

				return DalReturnValue::Success ;
			}

			//bool DalCommandInterface::InitiateDataCaptureModeInternal()
			//{
			//	//if (!_serialPort)
			//	if (!(DalActivePort::Instance->CurrentPort))
			//	{
			//		return false;
			//	}
			//	try
			//	{
			//		ResetAllStaticMembers();

			//		//Reset the streaming seqence number validation
			//		DalSequenceNumberManager::ResetStreamingSequenceNumber();
			//	
			//		//for mutliple reads we need to set the threshold to to the number of packets being read
			//		int singlePacketSize =DalConstants::EM4ZeroDataResponsePacketSize + DalConstants::PWVCaptureDataSize+ 1; //packet size+ data size + CRC byte
			//		int totalBytesTOReadinLoop = singlePacketSize * DalConstants::DeviceNumberOfReadsPerInterval ;
			//		//Deepak: disabling this becuase we need a fixed size tresholde for queued reading.
			//		//DalActivePort::Instance->CurrentPort->ReceivedBytesThreshold =totalBytesTOReadinLoop; //total bytes to read in a single swoop

			//		DalActivePort::Instance->CurrentPort->DataReceived += gcnew SerialDataReceivedEventHandler(DataCaptureMultiplePacketHandler);
			//		
			//		//set the timer for data streaming check
			//		streamingStoppedCheckTimer = gcnew Timers::Timer(DalConstants::StreamingTimeoutCheckerInterval);
			//		//streamingStoppedCheckTimer->Elapsed += gcnew ElapsedEventHandler(&DalCommandInterface::CheckIfTimeoutHasOccurred ); 
			//		streamingStoppedCheckTimer->Elapsed += gcnew ElapsedEventHandler(&DalCommandInterface::CheckSerialPortInputBuffer); 
			//		
			//		streamingStoppedCheckTimer->Enabled = true;
			//	}
			//	catch(Exception^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}
			//	return true;
			//}

			bool DalCommandInterface::InitiateDataCaptureModeInternal()
			{
				try
				{
					ResetAllStaticMembers();

					//Reset the streaming seqence number validation
					DalSequenceNumberManager::ResetStreamingSequenceNumber();
				
					//for mutliple reads we need to set the threshold to to the number of packets being read
					//int singlePacketSize =DalConstants::EM4ZeroDataResponsePacketSize + DalConstants::PWVCaptureDataSize+ 1; //packet size+ data size + CRC byte
					//int totalBytesTOReadinLoop = singlePacketSize * DalConstants::DeviceNumberOfReadsPerInterval ;


					//DalActivePort::Instance->CurrentPort->DataReceived += gcnew SerialDataReceivedEventHandler(DataCaptureMultiplePacketHandler);
					
					//TODO: temporarily disabling.
					////set the timer for data streaming check
					//streamingStoppedCheckTimer = gcnew Timers::Timer(DalConstants::StreamingTimeoutCheckerInterval);
					////streamingStoppedCheckTimer->Elapsed += gcnew ElapsedEventHandler(&DalCommandInterface::CheckIfTimeoutHasOccurred ); 
					//streamingStoppedCheckTimer->Elapsed += gcnew ElapsedEventHandler(&DalCommandInterface::CheckSerialPortInputBuffer); 
					//streamingStoppedCheckTimer->Enabled = true;

					//clear the streaming buffer before we start
					DalStreamingPacketQueue::Instance->Clear();

					//Inform the Staging que of the mode
					//this has an impact on how it deals with unrecognized packets
					DalStagingQueue::Instance->CaptureMode = true;

					//register and start the timer which will read the data
					streamingPacketProcessingTimer = gcnew Timers::Timer(DalConstants::StreamingPacketReadInterval); 
					streamingPacketProcessingTimer->Elapsed += gcnew ElapsedEventHandler(this, &DalCommandInterface::StreamingPacketReadHandler ); 
					streamingPacketProcessingTimer->Enabled = true;

					//Initialize the timeout checker.
					DalActivePort::Instance->StartStreamingTimeoutChecker();
					
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				return true;
			}

			//bool DalCommandInterface::StopDataCaptureModeInternal()
			//{
			//	//if (_serialPort)
			//	if (DalActivePort::Instance->CurrentPort)
			//	{
			//		try
			//		{
			//			streamingStoppedCheckTimer->Enabled = false;
			//			//ReadFromPortAndWriteToBuffer(this->_serialPort , nullptr);
			//			ReadFromPortAndWriteToBuffer(DalActivePort::Instance->CurrentPort , nullptr);
			//			//_serialPort->DataReceived -= gcnew SerialDataReceivedEventHandler(DataCaptureSinglePacketHandler);
			//			DalActivePort::Instance->CurrentPort->DataReceived -= gcnew SerialDataReceivedEventHandler(DataCaptureMultiplePacketHandler);
			//			
			//		}
			//		catch(Exception^ excepObj)
			//		{
			//			throw gcnew ScorException(excepObj);
			//		}

			//		return true;
			//	}
			//	else
			//	{
			//		return false;
			//	}
			//}

			bool DalCommandInterface::StopDataCaptureModeInternal()
			{

				try
				{
					CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::StopDataCaptureModeInternal called");
					//streamingStoppedCheckTimer->Enabled = false; //TEMPORARY
					
					////ReadFromPortAndWriteToBuffer(this->_serialPort , nullptr);
					//ReadFromPortAndWriteToBuffer(DalActivePort::Instance->CurrentPort , nullptr);
					////_serialPort->DataReceived -= gcnew SerialDataReceivedEventHandler(DataCaptureSinglePacketHandler);
					//DalActivePort::Instance->CurrentPort->DataReceived -= gcnew SerialDataReceivedEventHandler(DataCaptureMultiplePacketHandler);

					//Stop the timeout checker.
					DalActivePort::Instance->StopStreamingTimeoutChecker();

					streamingPacketProcessingTimer->Enabled = false; //stop the timer

					//Inform the Staging que of the mode
					//this has an impact on how it deals with unrecognized packets
					DalStagingQueue::Instance->CaptureMode = false;

					//clear the buffer since we wont need any more data
					DalStreamingPacketQueue::Instance->Clear();
					//TODO: should we trim the buffere after clearing?
					
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return true;
			}

			

			//bool DalCommandInterface::SetSerialPortProperties()
			//{
			//	//first check if the serial port is set . if not then raise an exception
			//	if (nullptr == _serialPort)
			//	{
			//		return false;
			//	}
			//	try
			//	{
			//		//set the serial port properties to match the EM4 device
			//		_serialPort->BaudRate = DalConstants::EM4SerialPortBaudRate ;
			//		_serialPort->Parity = Parity::None;
			//		_serialPort->StopBits = StopBits::One;
			//		_serialPort->DataBits = DalConstants::EM4SerialPortBits;
			//		_serialPort->Handshake  = Handshake::None;

			//		//set the read and write timeouts to the same value
			//		_serialPort->WriteTimeout  = DalConstants::EM4ResponseTimeout ; 
			//		_serialPort->ReadTimeout   = DalConstants::EM4ResponseTimeout ; 

			//	}
			//	catch(Exception^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}

			//	return true;
			//}

			
			//bool DalCommandInterface::SetActivePort(String^ serialPortName)
			//{
			//	//if ((String::Empty == serialPortName) ||(nullptr == serialPortName)) //removed by FxCop
			//	if (String::IsNullOrEmpty(serialPortName))
			//	{
			//		throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs,ErrorSeverity::Exception);
			//	}
			//	//if there is a serial port then set the portname to this 
			//	if (_serialPort)
			//	{
			//		try
			//		{
			//			//call the method to set the port name for the current serial port object.
			//			SetActivePortInstance(serialPortName);
			//		}
			//		catch(ScorException ^)
			//		{
			//			throw;
			//		}
			//	}
			//	else
			//	{
			//		try
			//		{
			//			if(false == CreateAndOpenNewSerialPort(serialPortName))
			//			{
			//				return false;
			//			}
			//			//SetSerialPortProperties(); //not needed as it is set internally in CreateAndOpenNewSerialPort
			//		}
			//		catch(ScorException ^ )
			//		{
			//			throw;
			//		}
			//	}

			//	return true;
			//}




			//made due to Sourcemonitor
			//bool DalCommandInterface::SetActivePortInstance(String^ serialPortName)
			//{
			//	try
			//		{
			//			//close the serial port if already open
			//			if (_serialPort->IsOpen)
			//			{
			//				_serialPort->Close();
			//			}

			//			//assign the name to the curres SP object
			//			_serialPort->PortName = serialPortName;
			//			SetSerialPortProperties();
			//			
			//			if (!(_serialPort->IsOpen))
			//			{
			//				_serialPort->Open();
			//			}
			//			return true;
			//		}
			//		catch(Exception^  excepObj)
			//		{
			//			throw gcnew ScorException(excepObj);
			//		}
			//}

			//bool DalCommandInterface::CreateAndOpenNewSerialPort(String^ newPortName)
			//{
			//	//do not accept null or empty string
			//	if(String::IsNullOrEmpty(newPortName))
			//	{
			//		throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs,ErrorSeverity::Exception);
			//	}
			//	
			//	//check if the active port is set 
			//	//close it and delete it
			//	if (_serialPort)
			//	{
			//		if ( false == CloseActivePort())
			//		{
			//			//since there is an active port and it could not be closed
			//			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrActivePortCloseFailedErrCd, CrxStructCommonResourceMsg::DalErrActivePortCloseFailed, ErrorSeverity::Exception);
			//		}
			//	}

			//	//cannopt allow default port creation

			//	try
			//	{
			//		_serialPort = gcnew SerialPort(newPortName);
			//		SetSerialPortProperties();
			//	}
			//	catch(Exception^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}

			//	//open it and see if it is avaliable
			//	//ISOpen will return false even if the port is opened by us 
			//	//but is in use by another process so handle it
			//	if (!(_serialPort->IsOpen))
			//	{
			//		try
			//		{
			//			_serialPort->Open();
			//		}
			//		catch(Exception^ )
			//		{
			//			//give a distinct message that we could not use the port even if avaliable. 
			//			//the user may have some other app communicating on the same port
			//			//they need to shut it
			//			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrPortOpenFailedErrCd, CrxStructCommonResourceMsg::DalErrPortOpenFailed, ErrorSeverity::Exception );
			//		}
			//	}
			//
			//	return true;
			//}

			//bool DalCommandInterface::CloseActivePort()
			//{
			//	if (!_serialPort)
			//	{
			//		//attempted to close nullptr
			//		//throw gcnew ScorException(1027, "DAL_ERR_INVALID_PORT_CLOSE", ErrorSeverity::Exception);
			//		throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidPortCloseErrCd, CrxStructCommonResourceMsg::DalErrInvalidPortClose, ErrorSeverity::Exception);
			//	}

			//	//if yes then close the existing
			//	//and set to the parameter
			//	try
			//	{
			//		_serialPort->Close();
			//		delete _serialPort ;
			//		_serialPort = nullptr;
			//	}
			//	catch(IOException^)
			//	{
			//		return false;
			//	}
			//	
			//	return true;
			//}

			DalCommandInterface^ DalCommandInterface::operator =( DalCommandInterface)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}


			//bool DalCommandInterface::DumpInputBufferOnFailure(SerialPort^ serialPort, array<unsigned char> ^)
			//{
			//	
			//	//CrxLogger::Instance->Write(CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalMsgIllegalPacketRcvd) + DalCommandInterface::ConvertBytesToString(currentDataPacket));

			//	int bytesRemainingInBuffer = serialPort->BytesToRead;
			//	//now get all the unread bytes from the buffer into an array.
			//	array <unsigned char>^ inputBuffData = gcnew array<unsigned char> (bytesRemainingInBuffer);
			//	 serialPort->Read(inputBuffData, 0,bytesRemainingInBuffer) ;

			//	
			//	//CrxLogger::Instance->Write(CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalMsgPortBufferDump));
			//	//CrxLogger::Instance->Write(ConvertBytesToString( inputBuffData));

			//	//now clear the buffer before retruning 
			//	try
			//	{
			//		serialPort->DiscardInBuffer();
			//	}
			//	catch(Exception ^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}

			//	return true;
			//}


			//bool DalCommandInterface::ExtractRequiredResponseFromArray(AtCor::Scor::DataAccess::DalEM4Command ^serialCommand, array<unsigned char,1> ^ sourceArray) 
			//{
			//	try
			//	{
			//		unsigned char currentByte;

			//		unsigned char commandCodeAcked, commandCodeNacked;
			//		unsigned char expectedSequenceNumber;
			//		commandCodeAcked = serialCommand->commandCode  | (unsigned char)DalAckNackByteMask::AckNackStatusBitMask;
			//		commandCodeNacked = serialCommand->commandCode;
			//		
			//		//No need to shift the sequence nummber for command-resp
			//		//problem noted by Alistair , mai rcvd on 13 June 2011 -Deepak.

			//		//expectedSequenceNumber = serialCommand->commandSequenceNumber << 4;
			//		expectedSequenceNumber = serialCommand->commandSequenceNumber ;


			//		if ((int)(serialCommand->expectedResponseLength +1 ) < (sourceArray->Length))
			//		{
			//			for (int indexInArray = ((sourceArray->Length) - 1 - (serialCommand->expectedResponseLength)); indexInArray >= 0; indexInArray --)
			//			{
			//				//first check if the byte is an ack or nack of our command code
			//				currentByte = sourceArray[indexInArray];
			//				if ((currentByte != commandCodeAcked ) && (currentByte != commandCodeNacked))
			//				{
			//					//if not then we dont need to process this
			//					continue;
			//				}

			//				//if command code mathces, we need to match the length with the next byte
			//				if ( sourceArray[(indexInArray+1)] != serialCommand->expectedResponseLength )
			//				{
			//					//if the length byte is not as expected then this is a false alarm
			//					continue;
			//				}

			//				//if code and length bytes are correct check if the third byte is the sequence number
			//				//if it is then we have our response within this array starting from indexInArray
			//				if(sourceArray[(indexInArray+2)] != expectedSequenceNumber)
			//				{
			//					continue;
			//				}

			//				//if we arrive here it means that the expected response is present
			//				//copy the required data and return back to caller.

			//				serialCommand->em4Response = gcnew array<unsigned char> (serialCommand->expectedResponseLength +1) ;
			//				sourceArray->Copy(sourceArray, indexInArray, serialCommand->em4Response , 0, (serialCommand->expectedResponseLength +1));
			//				serialCommand->em4ResponsePacketLength = serialCommand->expectedResponseLength; // CRC is excluded
			//				return true;

			//			}

			//			//if we arrive here it means that the expected response is not present
			//			return false;
			//		}
			//		return false;
			//	}
			//	catch(Exception ^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}
			//	
			//}

			void DalCommandInterface::CheckIfTimeoutHasOccurredInternal(System::Object ^sender, System::Timers::ElapsedEventArgs ^args)
			{
				sender; //Dummy statement to get rid of C4100 warning
				args; //Dummy statement to get rid of C4100 warning

				static unsigned int BufferEmptyCounter = 0;

				if (DalDataBuffer::Instance->IsBufferEmpty())
				{
					BufferEmptyCounter++;
				}
				else
				{
					//reset the pointer
					BufferEmptyCounter = 0;

					DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateWaiting::Instance);
					
				}

				if (BufferEmptyCounter >=  DalConstants::MaxStreamingTimeoutOccurrences)
				{
					DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateTimeout::Instance);
					
					//raise event 
					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureTimeout, DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName);
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);

					////CrxLogger::Instance->Write("Timeout Event raised :" + BufferEmptyCounter);

					DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateNotListening::Instance);
				}
			}



			//void DalCommandInterface::CheckSerialPortInputBuffer(Object^ sender, ElapsedEventArgs^ args)
			//{
			//	sender; //Dummy statement to get rid of C4100 warning
			//	args; //Dummy statement to get rid of C4100 warning

			//	static int previousBufferedCount = -1;
			//	int currentBufferedCount;

			//	int singlePacketSize = DalConstants::PWVCaptureDataSize + DalConstants::EM4ZeroDataResponsePacketSize +1 ;

			//	int numberofPacketsToRead = DalConstants::DeviceNumberOfReadsPerInterval ;


			//	currentBufferedCount= DalActivePort::Instance->CurrentPort->BytesToRead;

			//	if (currentBufferedCount < (singlePacketSize * numberofPacketsToRead))
			//	{
			//		if (currentBufferedCount == previousBufferedCount)
			//		{
			//			//raise event
			//			String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureTimeout, DalFormatterStrings::PrintEnumName);
			//			DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName);
			//			DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);
			//			////CrxLogger::Instance->Write("Timeout Event raised :" + BufferEmptyCounter);
			//		}
			//		else
			//		{
			//			previousBufferedCount = currentBufferedCount;
			//		}
			//	}
			//}



			void DalCommandInterface::ChangeCommandState(DalCommandState ^newCommandState)
			{
				if (nullptr == newCommandState)
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrorNullParamErrCd, CrxStructCommonResourceMsg::DalErrorNullParam, ErrorSeverity::Exception);
					//new state cannot be null
				}

				//set the parameter object as the new state
				DalCommandInterface::_currentCommandState = newCommandState;
			}


			//This is a facade for ProcessCommandAndResponse.
			//It will call the ProcessCommandAndResponse thorugh the state machine
			DalReturnValue DalCommandInterface::SendCommandAndGetResponse(DalEM4Command^ serialCommand)
			{
				//call the state machine's method and let the state machine decide
				//if the command is valid for the current state
				return _currentCommandState->SendCommandAndGetResponse(serialCommand);
				
			}


			
			void DalCommandInterface::ChangeCaptureState(DalCaptureState ^newCaptureState)
			{
				if (nullptr == newCaptureState)
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrorNullParamErrCd, CrxStructCommonResourceMsg::DalErrorNullParam, ErrorSeverity::Exception);
					//new state cannot be null
				}

				//set the parameter object as the new state
				DalCommandInterface::_currentCaptureState  = newCaptureState;
			}

			bool DalCommandInterface::InitiateDataCaptureMode()
			{
				return _currentCaptureState->InitiateDataCaptureMode();
			}

			bool DalCommandInterface::StopDataCaptureMode()
			{

				return _currentCaptureState->StopDataCaptureMode();
			}

			void DalCommandInterface::CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args)
			{
				_currentCaptureState->CheckIfTimeoutHasOccurred(sender, args);
			}

			//DalReturnValue DalCommandInterface::SendPacketWithRetries(DalEM4Command ^serialCommand)
			//{

			//	try
			//	{

			//		//set the timeout period
			//		//_serialPort->ReadTimeout = serialCommand->timeoutPeriod;
			//		DalActivePort::Instance->CurrentPort->ReadTimeout = serialCommand->timeoutPeriod;


			//		//Retry as many times as specified for the command 
			//		do 
			//		{
			//			//TODO: remove all code that clears the buffer
			//			
			//				//clear the input buffer before sending a command 
			//				//so that any remenant bits dont get prefixed to the response
			//				//_serialPort->DiscardInBuffer();
			//				DalActivePort::Instance->CurrentPort->DiscardInBuffer();


			//				//if (0 != _serialPort->BytesToRead )
			//				if (0 != DalActivePort::Instance->CurrentPort->BytesToRead )
			//				{
			//					//array <unsigned char> ^ dumparray = gcnew array<unsigned char> (_serialPort->BytesToRead);
			//					//_serialPort->Read(dumparray, 0, _serialPort->BytesToRead);
			//					array <unsigned char> ^ dumparray = gcnew array<unsigned char> (DalActivePort::Instance->CurrentPort->BytesToRead);
			//					DalActivePort::Instance->CurrentPort->Read(dumparray, 0, DalActivePort::Instance->CurrentPort->BytesToRead);
			//				}
			//				
			//				DalActivePort::Instance->CurrentPort->DiscardOutBuffer();
			//				DalActivePort::Instance->CurrentPort->Write(serialCommand->em4Command,0, serialCommand->commandLength +1); //1 for CRC byte

			//				//CrxLogger::Instance->Write("Deepak>>> Command sent on port:  " +  ConvertBytesToString(serialCommand->em4Command));
			//			

			//			//change state before the latency wait
			//			DalCommandInterface::Instance->ChangeCommandState(DalCommandStateWaiting::Instance);

			//			//wait to allow the response to arrive
			//			Thread::Sleep(DalConstants::EM4LatencyPeriod);

			//			//check here for response 
			//			//responseReturnValue = ListenForEM4Response(serialCommand);
			//			responseReturnValue = _currentCommandState->ListenForEM4Response(serialCommand);
			//	}
			//	catch(Exception^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}

			//	
			//	} 
			//}


			bool DalCommandInterface::ProcessSingleStreamingPacket(array<unsigned char> ^streamingPacket)
			{
				CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ProcessSingleStreamingPacket called with parameter: " + DalBinaryConversions::ConvertBytesToString(streamingPacket)+ " End");

				if (nullptr == streamingPacket)
				{
					CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ProcessSingleStreamingPacket returning false" );
					return false;
				}
				try
				{

					EM4DataCapturePacket^ capturePacket = gcnew EM4DataCapturePacket(DalConstants::PWVCaptureDataSize);
					DalPwvDataStruct pwvDataObject ;
					DalDataBuffer^ dataBufferObj = DalDataBuffer::Instance; //maybe we can move it out of the looper so that this will save one operation? TODO

					//copy the array to the capture packet
					capturePacket->em4Response = streamingPacket;

					//set the length to the size received from the port -1 9for CRC)
					capturePacket->em4ResponsePacketLength = streamingPacket->Length - 1;

					//breakup the byte array into the individual components
					 if (! capturePacket->BreakupEM4Response())
					 {
						 return false; //signal failure
					 }

					//validate the data.
					if (DalReturnValue::Success != ValidateResponsePacket(capturePacket))
					{
						return false;// anyways we cannot catch the exception
						//throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCaptureInvalidPacketErrCd,CrxStructCommonResourceMsg::DalErrCaptureInvalidPacket, ErrorSeverity::Information);
					}

					//everything is fine now get the data. and write it to the variables
					pwvDataObject.tonometerData = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _tonometerDataIndex);
					pwvDataObject.cuffPulseData = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _cuffPulseDataIndex);
					pwvDataObject.cuffPressure  = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _cuffPressureDataIndex);
					pwvDataObject.countdownTimer = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _countdownTimerDataIndex);

					if(!dataBufferObj->WriteDataToBuffer(pwvDataObject))
					{
						return false;
						//////CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> write to buff failed ");
						//throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferWriteFailedErrCd, CrxStructCommonResourceMsg::DalErrBufferWriteFailed, ErrorSeverity::Exception);
					}
					return true; //everything fine
				}
				catch(ScorException^ scorExObj)
				{
					//if we rethrow this exception , it will be unhandled. 
					//This is because this exception is raised in a 
					//method which has no caller and operates on its own thread.
					//THos causes the application to crash due to unhandled exception even though there is an exception handler in GUI.
					//So we are deleting this exception instead of rethrowing it.
					//To inform the upper layers, we are raising an OnDalModuleErrorAlarmEvent event.
					//This particular type (DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket) needs to be handled by
					//upper layers which need to decide what to do in this case.

					//Attempting to deregister the serial port DataRecieved event handler is useless because
					//serial port cannot be modified in a static method. 
					//we also tried calling Stop capture in GUI but that needs the method to be static.
					//It would result in  a lot of code refactoring.
					
					//TODO: mention this in release note

					CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ProcessSingleStreamingPacket ScorException caught and deleted : " + scorExObj->ErrorMessageKey + " Raising ErrorAlarm Event for packet: " + DalBinaryConversions::ConvertBytesToString(streamingPacket) + " :End");  
					delete scorExObj ;
					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName);
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);
				}
				catch(Exception^ excepObj)
				{
					//see note above.
					CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ProcessSingleStreamingPacket Exception caught and deleted : " + excepObj->StackTrace + ">>>"+ excepObj->Message + "Raising ErrorAlarm Event for packet: " + DalBinaryConversions::ConvertBytesToString(streamingPacket)+ " :End");  
					
					delete excepObj;
					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName);
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);

				}

				return false;
			}

			bool DalCommandInterface::ProcessStreamingPackets()
			{
				int totalPacketCount = DalStreamingPacketQueue::Instance->Count();
				CrxLogger::Instance->Write("Deepak>> DalCommandInterface::ProcessStreamingPackets available no. " + totalPacketCount);

				int currentPacketIndex;
				array<unsigned char> ^ currentPacket;
				bool returnValue;

				for (currentPacketIndex=0 ; currentPacketIndex < totalPacketCount; currentPacketIndex++)
				{
					//get the packet
					currentPacket = DalStreamingPacketQueue::Instance->Dequeue();

					//process it
					returnValue = ProcessSingleStreamingPacket(currentPacket);

					if (!returnValue)
					{
						return false;
					}
					//TODO: test if zero sleep afect perofrmance
					Thread::Sleep(0);
				}

				return true; 
			}

			void DalCommandInterface::StreamingPacketReadHandler(Object ^, ElapsedEventArgs ^)
			{
				if (0 == DalStreamingPacketQueue::Instance->Count())
				{
					//no data avaliable
					ChangeCaptureState(DalCaptureStateWaiting::Instance);
				}
				else
				{
					ChangeCaptureState(DalCaptureStateDataReceived::Instance);
				}
				
				//let this call be handled by the state machine
				_currentCaptureState->ProcessStreamingPackets();
			}

			void DalCommandInterface::ResponseListenerThreadMethod(Object^ responsePacket)
			{
				//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ResponseListenerThreadMethod START.");

				DalEM4Command^ commandObject = (DalEM4Command ^) responsePacket;

				//create a sperate array pointer to read the response. 
				array <unsigned char>^ recievedData ;

				try
				{
					//TODO: read from common.
					Thread::Sleep(100); //sleep until timeout expires or the thread is woken up
				}
				catch(ThreadInterruptedException^ threadInterruptEx)
				{
					delete threadInterruptEx;
					//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ResponseListenerThreadMethod ThreadInterruptedException raised");
				}
				finally
				{
					//now read from the queue and see if we got a response
					//check if the data is available
					recievedData= DalResponsePacketBuffer::Instance->Dequeue();

					//assign the recieved value to the parameter
					//responsePacket = recievedData;

					commandObject->em4Response  = recievedData; //copy the array to the command response
				
					//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ResponseListenerThreadMethod EXIT.");
				}
			}

			void DalCommandInterface::SignalResponsePacketAvailable()
			{
				listenerThread->Interrupt();
			}




		}//End Data Access
	}
}