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
					//DalCommandInterface::Instance->ChangeCommandState(DalCommandStateWaiting::Instance);
					ChangeCommandState(DalCommandStateWaiting::Instance); //call directly so that it is applicable for its children too


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

					//DalCommandInterface::Instance->ChangeCommandState(DalCommandStateReady::Instance);
					ChangeCommandState(DalCommandStateReady::Instance); //call directly so that it is applicable for its children too
					
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


			DalReturnValue DalCommandInterface::ListenForEM4Response(DalEM4Command^ serialCommand)
			{
				////CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ListenForEM4Response() : Start" );
				listenerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &DalCommandInterface::ResponseListenerThreadMethod));

				listenerThread->Start(serialCommand); //pass the command object so that we can copy the variable directly

				listenerThread->Join(); //Wait for the data to come 
				if (nullptr == serialCommand->em4Response )
				{
					//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ListenForEM4Response() : No data recieved : timing out");

					//DalCommandInterface::Instance->ChangeCommandState(DalCommandStateTimeout::Instance);
					ChangeCommandState(DalCommandStateTimeout::Instance); //call directly so that it is applicable for its children too
					
					
					//we still recived no data so we are timing out
					serialCommand->retryNumber++; //increment the counter
					return DalReturnValue::Timeout;
				}

				//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ListenForEM4Response() : recievedData:" + DalBinaryConversions::ConvertBytesToString(serialCommand->em4Response));

				//we have recieved data so signify that we have recieved it
				//DalCommandInterface::Instance->ChangeCommandState(DalCommandStateResponseReceived::Instance);
				ChangeCommandState(DalCommandStateResponseReceived::Instance); //call directly so that it is applicable for its children too


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
				CrxLogger::Instance->Write("Deepak>>> ValidateResponsePacket() : " + DalBinaryConversions::ConvertBytesToString(serialCommand->em4Response));

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


			bool DalCommandInterface::InitiateDataCaptureModeInternal()
			{
				try
				{
					ResetAllStaticMembers();

					//Reset the streaming seqence number validation
					DalSequenceNumberManager::ResetStreamingSequenceNumber();
				
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

			bool DalCommandInterface::StopDataCaptureModeInternal()
			{

				try
				{
					//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::StopDataCaptureModeInternal called");

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

			


			DalCommandInterface^ DalCommandInterface::operator =( DalCommandInterface)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}



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

					//DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateWaiting::Instance);
					ChangeCaptureState(DalCaptureStateWaiting::Instance); //call directly so that it is applicable for its children too
					
				}

				if (BufferEmptyCounter >=  DalConstants::MaxStreamingTimeoutOccurrences)
				{
					//DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateTimeout::Instance);
					ChangeCaptureState(DalCaptureStateTimeout::Instance); //call directly so that it is applicable for its children too
					
					//raise event 
					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureTimeout, DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName, DalBinaryConversions::ConvertAlarmType(DalErrorAlarmStatusFlag::DataCaptureTimeout));
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);

					//////CrxLogger::Instance->Write("Timeout Event raised :" + BufferEmptyCounter);

					//DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateNotListening::Instance);
					ChangeCaptureState(DalCaptureStateNotListening::Instance); //call directly so that it is applicable for its children too
				}
			}




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

			bool DalCommandInterface::ProcessSingleStreamingPacket(array<unsigned char> ^streamingPacket)
			{
				CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ProcessSingleStreamingPacket called with parameter: " + DalBinaryConversions::ConvertBytesToString(streamingPacket)+ " End");

				if (nullptr == streamingPacket)
				{
					//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ProcessSingleStreamingPacket returning false" );
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
						// return false; //signal failure
						 throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCaptureInvalidPacketErrCd,CrxStructCommonResourceMsg::DalErrCaptureInvalidPacket, ErrorSeverity::Information);
					 }

					//validate the data.
					if (DalReturnValue::Success != ValidateResponsePacket(capturePacket))
					{
						//return false;// anyways we cannot catch the exception
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCaptureInvalidPacketErrCd,CrxStructCommonResourceMsg::DalErrCaptureInvalidPacket, ErrorSeverity::Information);
					}

					//everything is fine now get the data. and write it to the variables
					pwvDataObject.tonometerData = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _tonometerDataIndex);
					pwvDataObject.cuffPulseData = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _cuffPulseDataIndex);
					pwvDataObject.cuffPressure  = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _cuffPressureDataIndex);
					pwvDataObject.countdownTimer = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _countdownTimerDataIndex);

					if(!dataBufferObj->WriteDataToBuffer(pwvDataObject))
					{
						//return false;
						////////CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> write to buff failed ");
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferWriteFailedErrCd, CrxStructCommonResourceMsg::DalErrBufferWriteFailed, ErrorSeverity::Exception);
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

					//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ProcessSingleStreamingPacket ScorException caught and deleted : " + scorExObj->ErrorMessageKey + " Raising ErrorAlarm Event for packet: " + DalBinaryConversions::ConvertBytesToString(streamingPacket) + " :End");  
					//delete scorExObj ; //do not delete, pass it as an object in the exception event

					//TODO: Change alarm type from InvalidPacket to StreamingException only after TS is aware of it
					DalErrorAlarmStatusFlag alarmType = DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket;
					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, alarmType, DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(alarmType, sourceName, DalBinaryConversions::ConvertAlarmType(alarmType), scorExObj);
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);
				}
				catch(Exception^ excepObj)
				{
					//see note above.
					//CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ProcessSingleStreamingPacket Exception caught and deleted : " + excepObj->StackTrace + ">>>"+ excepObj->Message + "Raising ErrorAlarm Event for packet: " + DalBinaryConversions::ConvertBytesToString(streamingPacket)+ " :End");  
					
					//delete excepObj; //do not delete
					ScorException^ scorExObj = gcnew ScorException(excepObj);

					//TODO: Change alarm type from InvalidPacket to StreamingException only after TS is aware of it
					
					DalErrorAlarmStatusFlag alarmType = DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket;
					String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, alarmType, DalFormatterStrings::PrintEnumName);
					DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(alarmType, sourceName, DalBinaryConversions::ConvertAlarmType(alarmType), scorExObj);
					DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);
				}

				return false;
			}

			bool DalCommandInterface::ProcessStreamingPackets()
			{
				int totalPacketCount = DalStreamingPacketQueue::Instance->Count();
				//CrxLogger::Instance->Write("Deepak>> DalCommandInterface::ProcessStreamingPackets available no. " + totalPacketCount);

				int currentPacketIndex;
				array<unsigned char> ^ currentPacket;
				bool returnValue;

				for (currentPacketIndex=0 ; currentPacketIndex < totalPacketCount; currentPacketIndex++)
				{
					//get the packet
					currentPacket = DalStreamingPacketQueue::Instance->Dequeue();

					if (nullptr == currentPacket)
					{
						return false;
					}

					//process it
					returnValue = ProcessSingleStreamingPacket(currentPacket);

					if (!returnValue)
					{
						return false;
					}
					
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
				////CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ResponseListenerThreadMethod START.");

				try
				{


					DalEM4Command^ commandObject = (DalEM4Command ^) responsePacket;

					//create a sperate array pointer to read the response. 
					array <unsigned char>^ recievedData ;

					try
					{	
						//sleep until timeout expires or the thread is woken up
						Thread::Sleep(commandObject->timeoutPeriod); 
					}
					catch(ThreadInterruptedException^ threadInterruptEx)
					{
						//this exception is not a real exception
						//it is only thrown when a thread->Interrupt() method is called
						delete threadInterruptEx;
						////CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ResponseListenerThreadMethod ThreadInterruptedException raised");
					}
					finally
					{
						//now read from the queue and see if we got a response
						//check if the data is available
						recievedData= DalResponsePacketBuffer::Instance->Dequeue();

						//assign the recieved value to the parameter
						//responsePacket = recievedData;

						commandObject->em4Response  = recievedData; //copy the array to the command response
					
						////CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ResponseListenerThreadMethod EXIT.");
					}
				}
				catch(ScorException^ scorExObj)
				{
					//Raise an event instead of throwing an exception
					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException , scorExObj);
				}
				catch(Exception^ excepObj)
				{
					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException, gcnew ScorException(excepObj));
				}
			}

			void DalCommandInterface::SignalResponsePacketAvailable()
			{
				listenerThread->Interrupt();
			}

			void DalCommandInterface::SetInstanceObject(DalCommandInterface ^newObject)
			{
				if (nullptr == newObject)
				{
					//cannot accept null for this
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs, ErrorSeverity::Exception);
				}

				_instance = newObject;



			}




		}//End Data Access
	}
}