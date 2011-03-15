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
				//Deepak: we should not create the default serial pirt object since it sets to COM1
				//create a serialport object only after we have a definitive port name
				/*try
				{
					CreateAndOpenNewSerialPort(nullptr);
				}
				catch(ScorException^)
				{
					throw;
				}*/
				
				
			}

			//Deepak: Redundant due to change of design. Uncalled as of now. May need later - FxCop
			//DalCommandInterface::DalCommandInterface(String^ em4DevicePortName)
			//{
			//	//first check if the portname is not null
			//	//CreateAndOpenNewSerialPort will create a serialoort object regardless of wheter a name has been provided or not
			//	if (nullptr == em4DevicePortName)
			//	{
			//		throw gcnew ScorException(1011, "DAL_ERR_NO_COMMPORT_NAME", ErrorSeverity::Exception);
			//	}

			//	try
			//	{
			//		CreateAndOpenNewSerialPort(em4DevicePortName);
			//	}
			//	catch(Exception^)
			//	{
			//		throw;
			//	}

			//	
			//	if (false == SetSerialPortProperties())
			//	{
			//		throw gcnew ScorException(1024, "DAL_ERR_COMPORT_PROPERTIES_FAIL", ErrorSeverity::Warning );
			//		//failed to set the propery of theserial port
			//	}
			//}

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
						//clear the input buffer before sending a command 
						//so that any remenant bits dont get prefixed to the response
						_serialPort->DiscardInBuffer();
						_serialPort->Write(serialCommand->em4Command,0, serialCommand->commandLength +1); //1 for CRC byte
					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
					}

					//wait to allow the response to arrive
					Thread::Sleep(DalConstants::EM4LatencyPeriod);

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


			//unused. May be needed later
			//void DalCommandInterface::DataCaptureSinglePacketHandler(Object^ sender, SerialDataReceivedEventArgs^ e)
			//{

			//	DalPwvDataStruct pwvDataObject ;
			//	int bytesRead;
			//	EM4DataCapturePacket^ capturePacket = gcnew EM4DataCapturePacket(DalConstants::PWVCaptureDataSize); 
			//
			//	SerialPort^ locSerialPort = (SerialPort^)sender;

			//	DalDataBuffer^ dataBufferObj = DalDataBuffer::Instance;

			//	int dataToReadLength = DalConstants::PWVCaptureDataSize + DalConstants::EM4ZeroDataResponsePacketSize +1 ;
			//
			//	try
			//	{
			//		if (locSerialPort->BytesToRead < dataToReadLength)
			//		{
			//			//it may be possible that the event has been fired but the actual number of bytes is less.
			//			//return so that the buffer can be filled.
			//			return;
			//		}
			//		bytesRead = locSerialPort->Read(capturePacket->em4Response, 0, dataToReadLength);
			//		
			//		if (bytesRead != dataToReadLength)
			//		{
			//			//CrxLogger::Instance->Write("DalDataHAndler>>>>>less bytesRead= " + bytesRead );
			//			return;

			//		}
			//		//write the number of bytes recieved so that it can be validated against the length recieved from EM4
			//		capturePacket->em4ResponsePacketLength = bytesRead - 1; //excluding CRC
			//	}
			//	catch(Exception^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}
			//	
			//	if(!capturePacket->BreakupEM4Response())
			//	{
			//		throw gcnew ScorException(1014, "DAL_ERR_RESPONSE_RESOLVE_FAILURE", ErrorSeverity::Exception );
			//	}

			//	try
			//	{
			//		//everything is fine now get the data. and write it to the variables
			//		pwvDataObject.tonometerData = TranslateTwoBytes(capturePacket->em4ResponseData, 0);
			//		pwvDataObject.cuffPulseData = TranslateTwoBytes(capturePacket->em4ResponseData, 2);
			//		pwvDataObject.cuffPressure  = TranslateTwoBytes(capturePacket->em4ResponseData, 4);
			//		pwvDataObject.countdownTimer = TranslateTwoBytes(capturePacket->em4ResponseData, 6);
			//	}
			//	catch(Exception ^ excepObj)
			//	{
			//		throw gcnew ScorException(excepObj);
			//	}


			////	CrxLogger::Instance->Write("DalDataHAndler>>> tonometerData : " + pwvDataObject.tonometerData + "    cuffPulseData: " + pwvDataObject.cuffPulseData);

			//	if(!dataBufferObj->WriteDataToBuffer(pwvDataObject))
			//	{
			//		throw gcnew ScorException(1015, "DAL_ERR_BUFFER_WRITE_FAILED", ErrorSeverity::Exception);
			//	}
			//	
			//	//validate flags only after the data has been written to the buffer that way the data will be available in the buffer.
			//	if (ValidateResponsePacket(capturePacket)!= DalReturnValue::Success)
			//	{
			//		throw gcnew ScorException(1016, "DAL_ERR_RESPONSE_INVALID", ErrorSeverity::Exception );
			//	}

			//}



			//this should be called only after the BytesTORead value has been set to a proper multiple
			void DalCommandInterface::DataCaptureMultiplePacketHandler(Object^ sender, SerialDataReceivedEventArgs^ e)
			{

				DalPwvDataStruct pwvDataObject ;
				int bytesRead;
				EM4DataCapturePacket^ capturePacket = gcnew EM4DataCapturePacket(DalConstants::PWVCaptureDataSize); 
			
				SerialPort^ locSerialPort = (SerialPort^)sender;

				DalDataBuffer^ dataBufferObj = DalDataBuffer::Instance;

				int singlePacketSize = DalConstants::PWVCaptureDataSize + DalConstants::EM4ZeroDataResponsePacketSize +1 ;

				int numberofPacketsToRead = DalConstants::DeviceNumberOfReadsPerInterval ;

				
				for (int loopCounter = 0; loopCounter < numberofPacketsToRead; loopCounter++)
				{
					try
					{
						if (locSerialPort->BytesToRead < singlePacketSize)
						{
							//it may be possible that the event has been fired but the actual number of bytes is less.
							//return so that the buffer can be filled.
						//	CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> less bytes to read : "+ locSerialPort->BytesToRead );
							return;
						}
						//else read a single packet from port
						bytesRead = locSerialPort->Read(capturePacket->em4Response, 0, singlePacketSize);
						//This comment is needed to debug EM4 packtes. Will be kept till it is tested on EM4 device. 
						//Remove after development is completed
						//CrxLogger::Instance->Write("Data recieved:" +  ConvertBytesToString(capturePacket->em4Response));
						
						if (bytesRead != singlePacketSize)
						{
							//insufficient data for a single packet
							//CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> less bytes read from port: "+ bytesRead );
							continue;

						}
						//write the number of bytes recieved so that it can be validated against the length recieved from EM4
						capturePacket->em4ResponsePacketLength = bytesRead - 1; //excluding CRC
					
						//split the recieved array into individual components 
						//for valdiation and transfering to buffer.
						if (!(capturePacket->BreakupEM4Response()))
						{
						//	CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> breakup failed "+ ConvertBytesToString(capturePacket->em4Response));
							//call the dump method before returning
							DumpInputBufferOnFailure(locSerialPort, capturePacket->em4Response);
							throw gcnew ScorException(1029,"DAL_ERR_CAPTURE_INVALID_PACKET", ErrorSeverity::Information);
						}

						//validate the data.
						if (ValidateResponsePacket(capturePacket)!= DalReturnValue::Success)
						{
						//	CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> validation failed " + ConvertBytesToString(capturePacket->em4Response));
							//call the dump method before returning
							DumpInputBufferOnFailure(locSerialPort, capturePacket->em4Response);
							throw gcnew ScorException(1029,"DAL_ERR_CAPTURE_INVALID_PACKET", ErrorSeverity::Information);
						}

						//everything is fine now get the data. and write it to the variables
						pwvDataObject.tonometerData = TranslateTwoBytes(capturePacket->em4ResponseData, 0);
						pwvDataObject.cuffPulseData = TranslateTwoBytes(capturePacket->em4ResponseData, 2);
						pwvDataObject.cuffPressure  = TranslateTwoBytes(capturePacket->em4ResponseData, 4);
						pwvDataObject.countdownTimer = TranslateTwoBytes(capturePacket->em4ResponseData, 6);

						CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>>" + " tonometerData: " + pwvDataObject.tonometerData + " cuffPulseData: " + pwvDataObject.cuffPulseData + " countdownTimer: " + pwvDataObject.countdownTimer);

						if(!dataBufferObj->WriteDataToBuffer(pwvDataObject))
						{
							//CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> write to buff failed ");
							throw gcnew ScorException(1015, "DAL_ERR_BUFFER_WRITE_FAILED", ErrorSeverity::Exception);
						}
					
					}
					catch(ScorException^ )
					{
						//CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> scor exception recieved ");
						throw;
					}
					catch(Exception^ excepObj)
					{
						//CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> general exception recieved ");
						throw gcnew ScorException(excepObj);
					}
				}//end for

				Thread::Sleep(DalConstants::EM4LatencyPeriod); 
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
				CRC8Calculator ^ crcCalculator = CRC8Calculator::Instance;
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
						DalEventContainer::Instance->OnDalCuffStatusEvent(nullptr, gcnew DalCuffStatusEventArgs(currentCuffState)); //cant pass the sender since this is a static method
						
					 }

					 if (CheckEAStatusFlagChanged(eaStatusBytes) == true)
					 {
						 //if a change has occured in the error/alarm bits first raise an event 
						 DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, gcnew DalModuleErrorAlarmEventArgs(TranslateErrorAlarmStatusBits(eaStatusBytes)));//cant pass the sender since this is a static method
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
				
				if (!CheckStatusFlag(statusBytes))
				{
					return DalReturnValue::Failure ;
				}
				return DalReturnValue::Success ;
			}

			bool DalCommandInterface::InitiateDataCaptureMode()
			{
				if (_serialPort)
				{
					try
					{
						//Deepak: commented for multiple read event do notdelete. 
						////This will vary as per mode.
						//_serialPort->ReceivedBytesThreshold =DalConstants::EM4ZeroDataResponsePacketSize + DalConstants::PWVCaptureDataSize+ 1; //packet size+ data size + CRC byte

						//_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DataCaptureSinglePacketHandler);

						
						//for mutliple reads we need to set the threshold to to the number of packets being read
						int singlePacketSize =DalConstants::EM4ZeroDataResponsePacketSize + DalConstants::PWVCaptureDataSize+ 1; //packet size+ data size + CRC byte
						int totalBytesTOReadinLoop = singlePacketSize * DalConstants::DeviceNumberOfReadsPerInterval ;
						_serialPort->ReceivedBytesThreshold =totalBytesTOReadinLoop; //total bytes to read in a single swoop

						_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DataCaptureMultiplePacketHandler);


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
						//_serialPort->DataReceived -= gcnew SerialDataReceivedEventHandler(DataCaptureSinglePacketHandler);
						_serialPort->DataReceived -= gcnew SerialDataReceivedEventHandler(DataCaptureMultiplePacketHandler);
						
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

			bool DalCommandInterface::SetSerialPortProperties()
			{
				//first check if the serial port is set . if not then raise an exception
				if (nullptr == _serialPort)
				{
					return false;
				}
				try
				{
					//set the serial port properties to match the EM4 device
					_serialPort->BaudRate = DalConstants::EM4SerialPortBaudRate ;
					_serialPort->Parity = Parity::None;
					_serialPort->StopBits = StopBits::One;
					_serialPort->DataBits = DalConstants::EM4SerialPortBits;
					_serialPort->Handshake  = Handshake::None;
					//set the read and write timeouts to the same value
					_serialPort->WriteTimeout  = DalConstants::EM4ResponseTimeout ; 
					_serialPort->ReadTimeout   = DalConstants::EM4ResponseTimeout ; 

				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return true;
			}

			//Deepak: uncalled as of now. May need later - FxCop
			//bool DalCommandInterface::SetActivePort( SerialPort^ serialPortObject)
			//{
			//	
			//	//close the active port if present
			//	try
			//	{
			//		CloseActivePort();
			//	}
			//	catch(Exception ^)
			//	{
			//		return false;
			//	}

			//	try
			//	{
			//		_serialPort = serialPortObject;
			//		SetSerialPortProperties();
			//	}
			//	catch (Exception ^)
			//	{
			//		return false;
			//	}

			//	return true;
			//}

			bool DalCommandInterface::SetActivePort(String^ serialPortName)
			{
				//if ((String::Empty == serialPortName) ||(nullptr == serialPortName)) //removed by FxCop
				if (String::IsNullOrEmpty(serialPortName))
				{
					throw gcnew ScorException(1005, "DAL_ERR_INVALID_ARGS",ErrorSeverity::Exception);
				}
				//if there is a serial port then set the portname to this 
				if (_serialPort)
				{
					try
					{
						//call the method to set the port name for the current serial port object.
						SetActivePortInstance(serialPortName);
					}
					catch(ScorException ^)
					{
						throw;
					}
				}
				else
				{
					try
					{
						if(false == CreateAndOpenNewSerialPort(serialPortName))
						{
							return false;
						}
						//SetSerialPortProperties(); //not needed as it is set internally in CreateAndOpenNewSerialPort
					}
					catch(ScorException ^ )
					{
						throw;
					}
				}

				return true;
			}



			//made due to Sourcemonitor
			bool DalCommandInterface::SetActivePortInstance(String^ serialPortName)
			{
				try
					{
						//close the serial port if already open
						if (_serialPort->IsOpen)
						{
							_serialPort->Close();
						}

						//assign the name to the curres SP object
						_serialPort->PortName = serialPortName;
						SetSerialPortProperties();
						
						if (!(_serialPort->IsOpen))
						{
							_serialPort->Open();
						}
						return true;
					}
					catch(Exception^  excepObj)
					{
						throw gcnew ScorException(excepObj);
					}
			}

			bool DalCommandInterface::CreateAndOpenNewSerialPort(String^ newPortName)
			{
				//do not accept null or empty string
				//if ((String::Empty == newPortName) ||(nullptr == newPortName)) //removed by FxCop
				if(String::IsNullOrEmpty(newPortName))
				{
					throw gcnew ScorException(1005, "DAL_ERR_INVALID_ARGS",ErrorSeverity::Exception);
				}
				
				//check if the active port is set 
				//close it and delete it
				if (_serialPort)
				{
					if ( false == CloseActivePort())
					{
						//since there is an active port and it could not be closed
						throw gcnew ScorException(1025, "DAL_ERR_ACTIVE_PORT_CLOSE_FAILED", ErrorSeverity::Exception);
					}
				}

				//cannopt allow default port creation
				//if (nullptr == newPortName)
				//{
				//	//if portname is emptry then simply create a serial port but dont open it
				//	try
				//	{
				//		//note the default onstructor always opens to "COM1"
				//		//however it is unlikely that our device will be on a real Serail port
				//		_serialPort = gcnew SerialPort();
				//	}
				//	catch(Exception^ excepObj)
				//	{
				//		throw gcnew ScorException(excepObj);
				//	}
				//}
				/*else
				{*/
				
				//now try to create the serial port object
				try
				{
					_serialPort = gcnew SerialPort(newPortName);
					SetSerialPortProperties();
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				//open it and see if it is avaliable
				//ISOpen will return false even if the port is opened by us 
				//but is in use by another process so handle it
				if (!(_serialPort->IsOpen))
				{
					try
					{
						_serialPort->Open();
					}
					catch(Exception^ )
					{
						//give a distinct message that we could not use the port even if avaliable. 
						//the user may have some other app communicating on the same port
						//they need to shut it
						throw gcnew ScorException(1026, "DAL_ERR_PORT_OPEN_FAILED", ErrorSeverity::Exception );
					}
				}
				/*}*/
				
				return true;
			}

			bool DalCommandInterface::CloseActivePort()
			{
				if (!_serialPort)
				{
					//attempted to close nullptr
					throw gcnew ScorException(1027, "DAL_ERR_INVALID_PORT_CLOSE", ErrorSeverity::Exception);
				}

				//if yes then close the existing
				//and set to the parameter
				try
				{
					_serialPort->Close();
					delete _serialPort ;
					_serialPort = nullptr;
				}
				//catch (Exception ^ ) //FxCop recommneds using a more speicic expcetion here
				catch(IOException^)
				{
					return false;
				}
				
				return true;
			}

			DalCommandInterface^ DalCommandInterface::operator =(const DalCommandInterface)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}


			bool DalCommandInterface::DumpInputBufferOnFailure(SerialPort^ serialPort, array<unsigned char> ^currentDataPacket)
			{
				
				CrxLogger::Instance->Write(CrxMessagingManager::Instance->GetMessage("DAL_MSG_ILLEGAL_PACKET_RCVD") + DalCommandInterface::ConvertBytesToString(currentDataPacket));

				int bytesRemainingInBuffer = serialPort->BytesToRead;
				//now get all the unread bytes from the buffer into an array.
				array <unsigned char>^ inputBuffData = gcnew array<unsigned char> (bytesRemainingInBuffer);
				 serialPort->Read(inputBuffData, 0,bytesRemainingInBuffer) ;

				
				CrxLogger::Instance->Write(CrxMessagingManager::Instance->GetMessage("DAL_MSG_PORT_BUFFER_DUMP"));
				CrxLogger::Instance->Write(ConvertBytesToString( inputBuffData));

				//now clear the buffer before retruning 
				try
				{
					serialPort->DiscardInBuffer();
				}
				catch(Exception ^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return true;
			}

		}//End Data Access
	}
}