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



using namespace System;
using namespace System::IO::Ports;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{
			DalCommandInterface::DalCommandInterface()
			{
				//Empty constructor does nothing
			}

			DalCommandInterface::DalCommandInterface(String^ em4DevicePortName)
			{
				if (nullptr == em4DevicePortName)
				{
					throw gcnew ScorException(1011, "DAL_ERR_NO_COMMPORT_NAME", ErrorSeverity::Exception);
				}

				// if serial port if not open
				if (!_serialPort)
				{
					try
					{
						_serialPort = gcnew SerialPort(em4DevicePortName);
					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
					}
				}

				////Code to close the port if already open
				//try
				//{
				//	_serialPort->Close();
				//}
				//catch(Exception^ excepObj)
				//{
				//	throw gcnew ScorException(excepObj);
				//}

				//set the serial port properties to match the EM4 device
				_serialPort->BaudRate = DalConstants::EM4SerialPortBaudRate ;
				_serialPort->Parity = Parity::None;
				_serialPort->StopBits = StopBits::One;
				_serialPort->DataBits = DalConstants::EM4SerialPortBits;
				_serialPort->Handshake  = Handshake::None;

				if (!(_serialPort->IsOpen))
				{
					try
					{
						_serialPort->Open();
					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
					}
				}

			}

			bool DalCommandInterface::ValidateCommand(DalEM4Command^ serialCommand)
			{
				if (nullptr == serialCommand )
				{
					throw gcnew ScorException(1012, "DAL_ERR_EMPTY_COMMAND", ErrorSeverity::Exception);
				}

				if (0x00 == serialCommand->commandCode )  //Defect fixed
				{
					throw gcnew ScorException(1012, "DAL_ERR_EMPTY_COMMAND", ErrorSeverity::Exception);
				}

				if (!_serialPort->IsOpen)
				{
					//pport is not open
					throw gcnew ScorException(1013, "DAL_ERR_PORT_NOT_OPEN", ErrorSeverity::Exception);
				}

				return true;
			}

			
			DalReturnValue DalCommandInterface::SendCommand(DalEM4Command^ serialCommand)
			{
				DalReturnValue responseReturnValue = DalReturnValue::Failure; //initialize to failure
				
				if (!ValidateCommand(serialCommand))
				{
					return DalReturnValue::Failure;
				}
				
				//set the timeout period
				_serialPort->ReadTimeout = serialCommand->timeoutPeriod;

				//Retry as many times as specified for the command 
				do 
				{
					try
					{
						_serialPort->Write(serialCommand->em4Command,0, serialCommand->commandLength +1); //1 for CRC byte
					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
					}

					//wait to allow the response to arrive
					Thread::Sleep(1);

					//check here for response 
					responseReturnValue = ListenForEM4Response(serialCommand);

				} while((serialCommand->retryNumber < serialCommand->retriesAllowed ) && (responseReturnValue != DalReturnValue::Success ));

				return ValidateCommandResult(serialCommand, responseReturnValue);
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

			
			void DalCommandInterface::DataCaptureHandler(Object^ sender, SerialDataReceivedEventArgs^ e)
			{
				DalPwvDataStruct pwvDataObject ;
				EM4DataCapturePacket^ capturePacket = gcnew EM4DataCapturePacket(DalConstants::PWVCaptureDataSize); 
			
				SerialPort^ locSerialPort = (SerialPort^)sender;

				DalDataBuffer^ dataBufferObj = DalDataBuffer::Instance;

				int dataWaiting = locSerialPort->BytesToRead;
			
				try
				{
					int bytesRead = locSerialPort->Read(capturePacket->em4Response, 0, dataWaiting);
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				
				if(!capturePacket->BreakupEM4Response())
				{
					throw gcnew ScorException(1014, "DAL_ERR_RESPONSE_RESOLVE_FAILURE", ErrorSeverity::Exception );
				}

				//everything is fine now get the data. and write it to the variables
				pwvDataObject.tonometerData = TranslateTwoBytes(capturePacket->em4ResponseData, 0);
				pwvDataObject.cuffPulseData = TranslateTwoBytes(capturePacket->em4ResponseData, 2);
				pwvDataObject.cuffPressure  = TranslateTwoBytes(capturePacket->em4ResponseData, 4);
				pwvDataObject.countdownTimer = TranslateTwoBytes(capturePacket->em4ResponseData, 6);

				if(!dataBufferObj->WriteDataToBuffer(pwvDataObject))
				{
					throw gcnew ScorException(1015, "DAL_ERR_BUFFER_WRITE_FAILED", ErrorSeverity::Exception);
				}
				
				//validate flags only after the data has been written to the buffer that way the data will be available in the buffer.
				if (ValidateResponsePacket(capturePacket)!= DalReturnValue::Success)
				{
					throw gcnew ScorException(1016, "DAL_ERR_RESPONSE_INVALID", ErrorSeverity::Exception );
				}

			}

			DalReturnValue DalCommandInterface::ListenForEM4Response(DalEM4Command^ serialCommand)
			{
				serialCommand->em4Response = nullptr;
				
				int dataWaiting = _serialPort->BytesToRead;
				if (dataWaiting == 0)
				{
					serialCommand->retryNumber++;
					return DalReturnValue::Timeout;
				}

				serialCommand->em4Response  = gcnew array<unsigned char>(dataWaiting);
				int bytesRead = 0;

				try
				{
					bytesRead = _serialPort->Read(serialCommand->em4Response, 0, dataWaiting);
				}
				catch(TimeoutException^)
				{
					serialCommand->retryNumber++;
					return DalReturnValue::Timeout;
				}

				if (bytesRead<dataWaiting)
				{
					serialCommand->retryNumber++;
					return DalReturnValue::Failure ;
				}
				else
				{
					serialCommand->em4ResponsePacketLength = bytesRead - 1; //excluding CRC
				}

				//if everthing is fine and the data is recoeved 
				//validate the packet
				return ValidateResponsePacket(serialCommand);
			}

			bool DalCommandInterface::ValidateResponseCRC (DalEM4Command^ serialCommand)
			{
				bool returnValue;

				if (serialCommand->em4Response == nullptr)
				{
					return false;
				}

				//generate the CRC
				CRC8Calculator ^ crcCalculator =CRC8Calculator::Instance;
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
				CRC8Calculator ^ crcCalculator = CRC8Calculator::Instance;
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
					throw gcnew ScorException(1017, "DAL_ERR_EMPTY_RESPONSE_VALIDATION", ErrorSeverity::Exception);
				}

				//Call the method to break the response into individual partes;
				if (!serialCommand->BreakupEM4Response())
				{
					return DalReturnValue::Failure;
				}

				unsigned char responseCode = serialCommand->em4Response[0];

				if ((responseCode & 0x7F) != serialCommand->commandCode )
				{
					//the reply is for another command incorrect
					return DalReturnValue::Failure;
				}

				if (!(responseCode & 0x80))
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
				CheckStatusFlag(statusBytes);
				
				//validate sequence number
				if (serialCommand->commandSequenceNumber != serialCommand->em4ResponseSequenceNumber)
				{
					return DalReturnValue::Failure;
				}

				return DalReturnValue::Success ;
			}

			bool DalCommandInterface::CheckStatusFlag(unsigned long statusBytes)
			{
				unsigned long cuffStatusBytes, eaStatusBytes; 

				//First break the status flag down into its two important sets
				//cuff status related bits
				cuffStatusBytes = statusBytes &0x2F00;

				//and Error-Alarm event related bits
				eaStatusBytes =statusBytes & 0x0028;

				//CrxLogger::Instance->Write("statusBytes:" + statusBytes.ToString("X4") +" cuffStatusBytes:" + cuffStatusBytes.ToString("X4") + " errorAlarmStatusBytes:"+eaStatusBytes.ToString("X4") ); //debugging only
				
				try
				{
					 if (CheckCuffStatusFlagsChanged(cuffStatusBytes) ==  true)
					 {
						DalCuffStateFlags currentCuffState = TranslateCuffStatusBits(cuffStatusBytes);

						 //map the status bytes to a state flag
						 //	raise a staus change event and update the new flag.
						DalEventContainer::Instance->OnDalCuffStatusEvent(nullptr, gcnew DalCuffStatusEventArgs_ORI(currentCuffState)); //cant pass the sender since this is a static method
						
					 }

					 if (CheckEAStatusFlagChanged(eaStatusBytes) == true)
					 {
						 //if a change has occured in the error/alarm bits first raise an event 
						 DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, gcnew DalModuleErrorAlarmEventArgs_ORI(TranslateErrorAlarmStatusBits(eaStatusBytes)));//cant pass the sender since this is a static method
						 //CrxLogger::Instance->Write("CheckEAStatusFlagChanged>>>OnDalModuleErrorAlarmEvent event raised");
					 }
				}
				catch(ScorException^)
				{
					throw;
				}

				return true;
			}

			DalReturnValue DalCommandInterface::ValidateResponsePacket(EM4DataCapturePacket ^capturePacket)
			{

				unsigned long statusBytes ;
				unsigned long cuffStatusBytes, eaStatusBytes; 

				if (capturePacket->em4Response == nullptr)
				{
					throw gcnew ScorException(1017, "DAL_ERR_EMPTY_RESPONSE_VALIDATION", ErrorSeverity::Exception);
				}

				//Call the method to break the response into individual partes;
				if (!capturePacket->BreakupEM4Response())
				{
					return DalReturnValue::Failure;
				}

				//the reply value should be for 07
				if (capturePacket->em4ResponseAckNackByte != 0x87 ) //UT fix
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
				
				//First break the status flag down into its two important sets
				//cuff status related bits
				cuffStatusBytes = statusBytes &0x2F00;

				//and Error-Alarm event related bits
				eaStatusBytes =statusBytes & 0x0028;

				//CrxLogger::Instance->Write("statusBytes:" + statusBytes.ToString("X4") +" cuffStatusBytes:" + cuffStatusBytes.ToString("X4") + " errorAlarmStatusBytes:"+eaStatusBytes.ToString("X4") ); // debugging only
				
				 if (CheckCuffStatusFlagsChanged(cuffStatusBytes) ==  true)
				 {
					DalCuffStateFlags currentCuffState = TranslateCuffStatusBits(cuffStatusBytes);
					 //map the status bytes to a state flag
					 //	raise a staus change event and update the new flag.
					DalEventContainer::Instance->OnDalCuffStatusEvent(nullptr, gcnew DalCuffStatusEventArgs_ORI(currentCuffState)); //sender
				 }

				 if (CheckEAStatusFlagChanged(eaStatusBytes) == true)
				 {
					 //if a change has occured in the error/alarm bits first raise an event 
					 DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, gcnew DalModuleErrorAlarmEventArgs_ORI(TranslateErrorAlarmStatusBits(eaStatusBytes))); //cant pass the sender since this is a static method					 //CrxLogger::Instance->Write("CheckEAStatusFlagChanged>>>OnDalModuleErrorAlarmEvent event raised");
				 }

				return DalReturnValue::Success ;
			}

			bool DalCommandInterface::InitiateDataCaptureMode()
			{
				if (_serialPort)
				{
					try
					{
						//This will vary as per mode.
						_serialPort->ReceivedBytesThreshold = DalConstants::PWVCaptureDataSize+ 1; //packet size + CRC byte

						//_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DataCaptureHandler); remmoved to run sim
					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
					}

					return true;
				}
				else
				{
					return false;
				}
			}

			bool DalCommandInterface::StopDataCaptureMode()
			{
				if (_serialPort)
				{
					try
					{
						//_serialPort->DataReceived -= gcnew SerialDataReceivedEventHandler(DataCaptureHandler); //to run sim
					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
					}

					return true;
				}
				else
				{
					return false;
				}
			}

			unsigned short DalCommandInterface::TranslateTwoBytes( array <unsigned char>^ sourceArray, int startPostion)
			{
				//get the status flag
				EM44StatusFlag flagUn;

				flagUn.ucStatusBytes[1] = sourceArray[startPostion]; //UT fix
				flagUn.ucStatusBytes[0] = sourceArray[startPostion + 1];

				return flagUn.ulStatusFlag ;
			}


			unsigned long DalCommandInterface::TranslateFourBytes( array <unsigned char>^ sourceArray, int startPostion)
			{
				//get the status flag
				EM44ErrorAlarmSourceFlag flagUn;
				//UT fix
				flagUn.ucStatusBytes[3] = sourceArray[startPostion];
				flagUn.ucStatusBytes[2] = sourceArray[startPostion + 1];
				flagUn.ucStatusBytes[1] = sourceArray[startPostion + 2];
				flagUn.ucStatusBytes[0] = sourceArray[startPostion + 3];

				return flagUn.ulStatusFlag ;
			}


			bool DalCommandInterface::TranslateUnsignedShort( array <unsigned char>^ destinationArray, int startPostion, unsigned short sourceUS)
			{
				//get the status flag
				EM44StatusFlag flagUn;

				try
				{

					flagUn.ulStatusFlag = sourceUS;
					destinationArray[startPostion] = flagUn.ucStatusBytes[1]; 
					destinationArray[startPostion + 1] = flagUn.ucStatusBytes[0];
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				return true; 
			}

			bool DalCommandInterface::TranslateUnsignedLong(array <unsigned char>^ destinationArray, int startPostion, unsigned long sourceUL )
			{
				//get the status flag
				EM44ErrorAlarmSourceFlag flagUn;
				
				try
				{
					flagUn.ulStatusFlag = sourceUL;

					destinationArray[startPostion] = flagUn.ucStatusBytes[3] ;
					destinationArray[startPostion + 1] = flagUn.ucStatusBytes[2];
					destinationArray[startPostion + 2] = flagUn.ucStatusBytes[1];
					destinationArray[startPostion + 3] = flagUn.ucStatusBytes[0] ;
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return true;
			}


			DalReturnValue DalCommandInterface::SendDataCapturePacket(DalEM4Command^ serialCommand)
			{
				int retryCount;
				DalReturnValue responseReturnValue = DalReturnValue::Failure; //initialize to failure
				
				if (!ValidateCommand(serialCommand))
				{
					return DalReturnValue::Failure;
				}
				
				//set the timeout period
				_serialPort->ReadTimeout = serialCommand->timeoutPeriod;

				//Retry as many times as specified for the command 
					try
					{
						_serialPort->Write(serialCommand->em4Command,0, serialCommand->commandLength +1); //1 for CRC byte
					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
						retryCount++;
					}

					//wait to allow the response to arrive
					Thread::Sleep(1);

					return DalReturnValue::Success;
			}




			void DalCommandInterface::PCCommandHandler(Object^ sender, SerialDataReceivedEventArgs^ e)
			{
				SerialPort^ locSerialPort = (SerialPort^)sender;

				//get the command packet from the serial port
				int dataWaiting = locSerialPort->BytesToRead;
				array<unsigned char> ^pcCommandArray = gcnew array<unsigned char> (dataWaiting);
				try
				{
					int bytesRead = locSerialPort->Read(pcCommandArray, 0, dataWaiting);
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				
				//re-create an EM4 command packet out of this and send it to data provider.
				DalEM4Command^ commandRecievedfromPC = gcnew DalEM4Command(pcCommandArray);
				//send this command to DalDataProvider to validate and send a response //TODO.
				DalEventContainer::Instance->OnPcCommandRecievedEvent( nullptr , gcnew  PCCommandRecievedEventArgs(commandRecievedfromPC));

				
			}
			

		}//End Data Access
	}
}