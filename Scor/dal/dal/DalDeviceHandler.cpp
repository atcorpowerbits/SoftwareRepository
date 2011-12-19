/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalDeviceHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalDeviceHandler class code
*/

#include "stdafx.h"
#include "DalDeviceHandler.h"
#include "DalCommon.h"
#include "DalDataBuffer.h"
#include "IDalHandler.h"
#include "DalStatusHandler.h"
#include "DalActivePort.h"
#include "DalBinaryConversions.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Messaging;


namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalDeviceHandler::DalDeviceHandler()
			{
				try
				{
					//logObj = CrxLogger::Instance;
					messagingMgr = CrxMessagingManager::Instance;
				}
				catch(ScorException^)
				{
					throw;
				}

				//removing all DCI constructors and replacing with instance
				if (nullptr == _commandInterface)
				{
					_commandInterface = DalCommandInterface::Instance;
				}

				//_currentCommandState = DalCommandStateReady::Instance;
			}

			void DalDeviceHandler::CloseFiles()
			{
			}

			bool DalDeviceHandler::StartCapture(int captureTime, int samplingRate)
			{
				//CrxLogger::Instance->Write("DAL>>> DalDeviceHandler::StartCapture Called", ErrorSeverity::Debug);

				//create a buffer of the required size
				try
				{
					dataBufferObj = nullptr;
					dataBufferObj = DalDataBuffer::Instance;
					dataBufferObj->CreateBuffer(captureTime, samplingRate);
				}
				catch(ScorException^)
				{
					throw;
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				//GUI checks if device is connected beofre calling this function . So no
				//need to do it again. This is as per Alistairs mail on4-5th August 20111

				//No need to check if tonometer is connected
				//The result will not be correct from EM4
								
				
				
				//Deepak: 12/Nov-2011 corrected the code for PWVSW-546
				//and spun it off into another function

				//Set Idle mode
				//bool boolReturnValue;
				////
				////boolReturnValue = SetIdleMode();
				//
				//int countRetry;
				//int count = 0;
				//int sleepTime = 0;
				//
				//sleepTime = Convert::ToInt32(CrxSytemParameters::Instance->GetStringTagValue("IdleModeSleepTime"));
				//countRetry = (15000/sleepTime) + 1;
				
				//Object^ obj;
				//do
				//{
				//	ScorException^ check = gcnew ScorException (1001, CrxStructCommonResourceMsg::Dal_DeviceIdling_Message, ErrorSeverity::Information);	
				//	CrxEventContainer::Instance->OnShowStatusEvent(obj, gcnew CrxShowStatusEventArgs(check));
				
				//	boolReturnValue = SetIdleMode();
				//	if(!boolReturnValue)
				//	{
				//		count++;
				//		Threading::Thread::Sleep(sleepTime); //Wait for 3 sec to re-check the idle mode
				//	}
				//}
				//while(!boolReturnValue || count > countRetry);
				////Alok

				//if (false == boolReturnValue )
				//{
				//	ScorException^ check = gcnew ScorException (1002, CrxStructCommonResourceMsg::Dal_DeviceNotReady_Message, ErrorSeverity::Information);	
				//	CrxEventContainer::Instance->OnShowStatusEvent(obj, gcnew CrxShowStatusEventArgs(check));
				//	return false;
				//}

				if(! SetIdleModeProcess())
					{
					//Failed to set IDLE mode within 15 sec.

					//capture cannot continue if IDLE mode was not set
					return false;
				}

				//now issue the command to start capture and see if the response was acknowledgement
				array<unsigned char> ^commandData = gcnew array<unsigned char> (1) {Em4CommandCodes::CaptureCommandDataPWVMode}; //Make this 0x03 into a dynamic thing
				DalEM4Command ^ startCaptureCommand = gcnew DalEM4Command(Em4CommandCodes::StartDataCapture , commandData);
				startCaptureCommand->expectedResponseLength = Em4ResponseRequiredLength::StartDataCapture ;
				
				DalReturnValue returnValue = DalReturnValue::Failure;

				returnValue = _commandInterface->SendCommandAndGetResponse(startCaptureCommand); //renamed oringinal method
				
				//if acknowledged start the handler to listen to the data received.
				if (DalReturnValue::Success == returnValue )
				{
					//Reserve the successful capture commands sequence number durign streaming process
					DalSequenceNumberManager::ReserveCommandNumberDuringStreaming(startCaptureCommand->commandSequenceNumber);

					//start the handler for data capture here
					try
					{
						return _commandInterface->InitiateDataCaptureMode();
					}
					catch(ScorException^)
					{
						throw;
					}
				}
				
				return false;
			}

			bool DalDeviceHandler::StopCapture()
			{
				//CrxLogger::Instance->Write("DAL>>> DalDeviceHandler::StopCapture Called", ErrorSeverity::Debug);
				//CrxLogger::Instance->Write("DAL>>> DalDeviceHandler::StopCapture START", ErrorSeverity::Debug);
					
				//check if  the comand interface isnt already created
				if (nullptr == _commandInterface)
				{
					return false;
				}

				//send command to stop capture
				DalEM4Command ^ stopCaptureCommand = gcnew DalEM4Command(Em4CommandCodes::StopDataCapture , nullptr);
				DalReturnValue returnValue = DalReturnValue::Failure;
				stopCaptureCommand->expectedResponseLength = Em4ResponseRequiredLength::StopDataCapture; 
				//stopCaptureCommand->timeoutPeriod = 1000; //TODO: setting a high timeout to allow the Stop capture command sufficient time
				////It needs extra time because there are many streaming packets in the queue befor it 

				returnValue = _commandInterface->SendCommandAndGetResponse(stopCaptureCommand); //renamed oringinal method

				CrxLogger::Instance->Write("DAL>>> DalDeviceHandler::StopCapture returnValue" + returnValue.ToString(), ErrorSeverity::Debug);

				
				if(!(_commandInterface->StopDataCaptureMode()))
				{
					CrxLogger::Instance->Write("DAL>>> DalDeviceHandler::StopDataCaptureMode returned false", ErrorSeverity::Debug);
				}

				//Free up the reserved sequence number so that it can be reused
				DalSequenceNumberManager::ReleaseReservedCommandNumber();


				if (returnValue == DalReturnValue::Success)
				{
					CrxLogger::Instance->Write("DAL>>> DalDeviceHandler::StopCapture() returning true", ErrorSeverity::Debug);

					return true;
				}
				else
				{
					CrxLogger::Instance->Write("DAL>>> DalDeviceHandler::StopCapture() returning false", ErrorSeverity::Debug);

					return false;
				}
			}

			bool DalDeviceHandler::GetConnectionStatus()
			{
				//call the fucntion which checks the device connection
				return CheckIfDeviceIsConnected();
			}

			bool DalDeviceHandler::GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^%deviceConfigInfo )
			{
				bool returnValue = false;

				//temporarily assign the same values as the EM4 simulation device until the actual code is written.
				switch (deviceConfigItem)
				{
					
					case DalDeviceConfigUsageEnum::ModuleCalibrationDate:
						//Dummy value: returns todays date
						deviceConfigInfo->ModuleConfigDate= System::DateTime::Today;
						break;
					case DalDeviceConfigUsageEnum::ModuleConfigDate:
						//Dummy value: returns todays date
						deviceConfigInfo->ModuleConfigDate= System::DateTime::Today;
						break;
					case DalDeviceConfigUsageEnum::ModuleConfigId:
						//Dummy value
						deviceConfigInfo->ModuleConfigId = 123; //Dummy value . will be retreived from the EM4 device
						break;
					case DalDeviceConfigUsageEnum::ModuleMainFirmwareVersion:
						//Dummy value
						//deviceConfigInfo->ModuleMainFWVersion =CrxMessagingManager::Instance->GetMessage("DAL_CONST_GCI_FIRMWARE_VERSION");
						deviceConfigInfo->ModuleMainFWVersion =CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstGciFirmwareVersion);
						break;
					case DalDeviceConfigUsageEnum::ModuleSerialNumber:
						String ^ tempSerialNumber;
						
						returnValue = GetConfigDeviceSerialMumber(tempSerialNumber);
						deviceConfigInfo->ModuleSerialNumber = tempSerialNumber;
						return returnValue;
					case DalDeviceConfigUsageEnum::ModuleType:
						//Dummy value
						//deviceConfigInfo->ModuleType = CrxMessagingManager::Instance->GetMessage("DAL_CONST_GCI_TYPE"); 
						deviceConfigInfo->ModuleType = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstGciType); 
						break;
					case DalDeviceConfigUsageEnum::PwaCuffMeasurementsCounter:
						String^ tempPwaCuffMeasurementsCounter;

						returnValue = GetConfigPwaCuffMeasurementsCounter(tempPwaCuffMeasurementsCounter);
						deviceConfigInfo->PwaCuffMeasurementsCounter = tempPwaCuffMeasurementsCounter; 
						return returnValue;
					default:
						break;
				}

				//return false until this functionality is implemented
				return false;
			}

			//name changed. see if the functionality needs changing
			String^ DalDeviceHandler::GetAlarmSource(DalAlarmSource% translatedAlarmSource) 
			{
				
				//We need to call a command to get the error alrm source
				DalReturnValue returnedValue;
				DalEM4Command^ serialCommand;
				unsigned long eaSourceFlag;
				//DalAlarmSource translatedAlarmSource;

				try
				{
					serialCommand = gcnew DalEM4Command(Em4CommandCodes::GetAlarmStatus, nullptr);
					serialCommand->expectedResponseLength = Em4ResponseRequiredLength::GetAlarmStatus ;
					returnedValue = _commandInterface->SendCommandAndGetResponse(serialCommand); 
					
					if (returnedValue == DalReturnValue::Success)
					{
						eaSourceFlag = DalBinaryConversions::TranslateFourBytes(serialCommand->em4ResponseData, 0);
						_currentEASourceFlag = eaSourceFlag  ;
						_currentAlarmStatusFlag = (serialCommand->em4StatusFlag) & (unsigned long)DalStatusFlagBitMask::AlarmStatusBitsMask;

						// call parent method
						return DalStatusHandler::GetAlarmSource(translatedAlarmSource);
					}
					else
					{
						return nullptr;
					}

				}
				catch(ScorException^)
				{
					// rethrow the exception
					throw;
				}
			}

			int DalDeviceHandler::FindModule(String^ comPort)
			{
				//get the current com port setting from the Config file
				CrxConfigManager ^configMgr = CrxConfigManager::Instance;
                configMgr->GetGeneralUserSettings();
                configMgr->GetPwvUserSettings();
                String ^ commPort = configMgr->GeneralSettings->CommsPort;

				//First check if some port has been set( i.e. in gui the value shoud not be "Simulation")
				if (String::Compare(commPort->Replace(DalFormatterStrings::SingleSpaceString ,String::Empty), CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::ComportSimulation), false) != 0)
				{
					//then some com port is set. check if this is the actual device connected by calling getconfig info
					if (CheckIfDeviceIsConnected())
					{
						return 1;
					}
					//if not then check all ports for device
				}

				//find all open ports
				array<String^>^ listOfSerialPorts = nullptr;
				
				try
				{
					listOfSerialPorts = SerialPort::GetPortNames();
				}
				catch(Win32Exception^ winExcepObj)
				{
					throw gcnew ScorException(winExcepObj);
				}

				for each (String ^ portName in listOfSerialPorts)
				{
					////CrxLogger::Instance->Write("Ports Listed: " + portName, ErrorSeverity::Debug);
					if (CheckIfDeviceIsConnected(portName))
					{
						//Device is present on another com port
						//update the new port name to the config file.
						configMgr->GeneralSettings->CommsPort = portName;
						configMgr->SetGeneralUserSettings(configMgr->GeneralSettings);
						
						//return the parameter and value;
						comPort = portName;
						return 2; 
					}
				}

				//if we reach here it means the device was not found at all
				//return true and make comPort null to signify that the port is avalaiable
				comPort = nullptr;
				return 0;
			}

			bool DalDeviceHandler::CheckIfDeviceIsConnected()
			{
				//get the current set com port from Config
				CrxConfigManager ^configMgr = CrxConfigManager::Instance;
                configMgr->GetGeneralUserSettings();
                configMgr->GetPwvUserSettings();
                String ^ commPort = configMgr->GeneralSettings->CommsPort;

				if (String::Compare(commPort->Replace(DalFormatterStrings::SingleSpaceString,String::Empty), messagingMgr->GetMessage(CrxStructCommonResourceMsg::ComportSimulation), false) == 0)
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrPortSimulationErrCd, CrxStructCommonResourceMsg::DalErrPortSimulation, ErrorSeverity::Information);
				}
				else
				{
					 return CheckIfDeviceIsConnected(commPort);
				}
				//return false; //unreachable code
			}


			
			bool DalDeviceHandler::CheckIfDeviceIsConnected(String^ comPort)
			{

				bool returnValue;
				
				  
				//String^ searchingPortMessage = "DAL: DalDeviceHandler::CheckIfDeviceIsConnected checking connection on port: " + comPort;
				
				ScorException^ check = gcnew ScorException (CrxStructCommonResourceMsg::DalMsgCheckDevicePortErrCd , CrxStructCommonResourceMsg::DalMsgCheckDevicePort, ErrorSeverity::Information, nullptr, comPort );	
				CrxEventContainer::Instance->OnShowStatusEvent(nullptr, gcnew CrxShowStatusEventArgs(check));
				
			
				if (nullptr == comPort )
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs, ErrorSeverity::Warning );
				}
				
				
				try
				{
					DalDeviceConfigUsageStruct^ configStruct = gcnew DalDeviceConfigUsageStruct();
				
					//first check if this is the port already set in commandInterface
					//if yes then we SHOULD NOT open it again
					
					////if ( (comPort == _commandInterface->ActiveSerialPortName) && (nullptr != _commandInterface))
					//if ( (comPort == DalActivePort::Instance->ActiveSerialPortName) && (nullptr != _commandInterface))
					//{
					//	{
					//		//Deepak 22nd Nov 2011: Sometimes it tries on COM1 which is set as the default port name
					//		//but it may not necessarily be open. So try setting it again

					//		returnValue = DalActivePort::Instance->SetActivePort(comPort);

					//		if (!returnValue)
					//		{
					//			//could not set the port.
					//			//the portname may be illegal or some other problem
					//			return false;
					//		}
					//	}

					//	//this com port has already been set 
					//	//we just need to verify if the device is present there

					//	try
					//	{
					//		return GetConfigurationInfo(DalDeviceConfigUsageEnum::ModuleSerialNumber, configStruct);
					//	}
					//	catch(ScorException ^ excepObj)
					//	{
					//		//Deepak 22 Nov 2011
					//		//returning false is not the besrt thing to do here
					//		//Code has been rearranged to suppress exceptions at their source
					//		//instead of being cascaded and supprassed later
					//		//so now we will rethrow the exception
					//		throw;

					//		//Deepak: commented out
					//		////this port didnt work
					//		////dont throw the exception so that we can try with another port
					//		//return false;
					//	}
					//}
					//else
					//{
						//this comPort is not set in command interface. 
						//We need to first open the port and then check if it is valid
						//then check if the device is present
						
					/*try
					{*/
							//_commandInterface->SetActivePort(comPort);
					returnValue = DalActivePort::Instance->SetActivePort(comPort);
						
					if (!returnValue)
						{
						//could not set the port.
						//the portname may be illegal or some other problem
						returnValue =  false;
						}
					else
					{
				
					returnValue = GetConfigurationInfo(DalDeviceConfigUsageEnum::ModuleSerialNumber, configStruct);
					}
					//}
					//catch(ScorException ^ )
					//{
					//	//Deepak 22 Nov 2011
					//	//returning false is not the besrt thing to do here
					//	//Code has been rearranged to suppress exceptions at their source
					//	//instead of being cascaded and supprassed later
					//	//so now we will rethrow the exception
					//	throw;

					//	//Deepak: commented out
					//	////this port didnt work
					//	////dont throw the exception so that we can try with another port
					//	//return false;
					//}
					///*}*/
					//return false; 
				}
				catch(ScorException^ )
				{
					throw; 
				}
				catch(Exception ^excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
					
				return returnValue;
			}


			bool DalDeviceHandler::SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard)
			{
				CrxLogger::Instance->Write("DAL >>> DalDeviceHandler::SetPressure called with pressure:" + newPressure.ToString() + " Binary: " +  newPressure.ToString("X2") + " as a signed int: " + ((signed int)newPressure).ToString(), ErrorSeverity::Debug);
				
				//Deepak: This code is temporary until the cuff pressure negative problem is solved.
				//TODO: remove after solution 
				if (0 > ((signed int)newPressure))
				{
					CrxLogger::Instance->Write("DAL >>> DalDeviceHandler::SetPressure called with negative pressure value: Binary: " +  newPressure.ToString("X2") + " as a signed int: " + ((signed int)newPressure).ToString() + " . ignoring it an d taking pressure  = 0", ErrorSeverity::Debug);
					
					newPressure = 0;
				
				}
				unsigned short pressureToSet = (unsigned short)newPressure;

				unsigned char pressureMSB, pressureLSB, commandByte;

				pressureLSB = (unsigned char)(pressureToSet & 0x00FF);
				pressureMSB = ((unsigned char)((pressureToSet & 0xFF00) >> 8));
				
				array<unsigned char> ^pressureBytes = gcnew array<unsigned char> {pressureMSB, pressureLSB};

				
				try
				{
					if (cuffBoard == EM4CuffBoard::SuntechBoard)
					{
						commandByte = Em4CommandCodes::SetPressureSuntechBoard;
					}
					else if (cuffBoard == EM4CuffBoard::MainBoard)
					{
						commandByte = Em4CommandCodes::SetPressureMainBoard;
					}
					else 
					{
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs, ErrorSeverity::Exception);
					}

					DalEM4Command ^setPressureCommand = gcnew DalEM4Command(commandByte,pressureBytes);
					setPressureCommand->expectedResponseLength = Em4ResponseRequiredLength::SetPressure;

					//Deepak: TODO: note it. experimenting with a higher timeout 
					//This command is sent when streaming is in progress so it 
					//needs some more time to process
					setPressureCommand->timeoutPeriod = 100; 



					if (_commandInterface->SendCommandAndGetResponse(setPressureCommand) ==DalReturnValue::Success) //renamed oringinal method
					{
						//CrxLogger::Instance->Write("DAL >>> DalDeviceHandler::SetPressure call Successful" , ErrorSeverity::Debug);
				
						return true; 
					}
					else
					{
						//CrxLogger::Instance->Write("DAL >>> DalDeviceHandler::SetPressure call Failed" , ErrorSeverity::Debug);
						return false;
					}
				}
				catch(ScorException^)
				{
					throw;
				}
				 return false;
			}


			//bool DalDeviceHandler::CheckIfTonometerIsConnected()
			//{
			//	unsigned short statusFlag; 

			//	if (nullptr == _commandInterface)
			//	{
			//		throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNoInterfaceErrCd, CrxStructCommonResourceMsg::DalErrNoInterface,ErrorSeverity::Warning );
			//	}
			//	
			//	DalReturnValue returnedValue = DalReturnValue::Failure ;

			//	DalEM4Command^ serialCommand = gcnew DalEM4Command(Em4CommandCodes::GetConfigInfo, gcnew array<unsigned char> (1){Em4CommandCodes::GetConfigInfoDataDeviceSerialNumber});
			//	serialCommand->expectedResponseLength = Em4ResponseRequiredLength::GetConfigInfoDataDeviceSerialNumber;
			//	
			//	returnedValue = _commandInterface->SendCommandAndGetResponse(serialCommand); //renamed oringinal method
			//	
			//	if (returnedValue == DalReturnValue::Success)
			//	{
			//		serialCommand->BreakupEM4Response();
			//		statusFlag = serialCommand->em4StatusFlag ;

			//		DalTonometerState tonoState;
			//		tonoState = (DalTonometerState)(statusFlag & (unsigned short)DalTonometerStatusBitMask::TonometerNotConnectedBits);
			//		if (DalTonometerState::Disconnected == tonoState)
			//		{
			//			return false;
			//		}
			//		else
			//		{
			//			return true;
			//		}
			//	}
			//	else
			//	{
			//		throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommandFailedErrCd, CrxStructCommonResourceMsg::DalErrCommandFailed,ErrorSeverity::Warning );
			//	}
			//}


			bool DalDeviceHandler::GetConfigDeviceSerialMumber(String ^% moduleSerialNumber)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::GetConfigInfoDataDeviceSerialNumber};

				serialCommand = gcnew DalEM4Command(Em4CommandCodes::GetConfigInfo, dataCode);
				serialCommand->expectedResponseLength = Em4ResponseRequiredLength::GetConfigInfoDataDeviceSerialNumber ;
				
				returnedValue = _commandInterface->SendCommandAndGetResponse(serialCommand); ////renamed oringinal method
				
				if (returnedValue == DalReturnValue::Success)
				{
					moduleSerialNumber = DalBinaryConversions::ConvertBytesToString(serialCommand->em4ResponseData); 
					delete serialCommand;
					return true;
				}
				else
				{
					return false;
				}

			}

			bool DalDeviceHandler::GetConfigPwaCuffMeasurementsCounter(String ^% PwaCuffMeasurementsCounter)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::GetConfigInfoDataPwaCuffMeasurementsCounter};

				serialCommand = gcnew DalEM4Command(Em4CommandCodes::GetConfigInfo, dataCode);
				serialCommand->expectedResponseLength = Em4ResponseRequiredLength::GetConfigInfoDataPwaCuffMeasurementsCounter ;
				
				returnedValue = _commandInterface->SendCommandAndGetResponse(serialCommand); ////renamed oringinal method
				
				if (returnedValue == DalReturnValue::Success)
				{
					PwaCuffMeasurementsCounter = DalBinaryConversions::ConvertBytesToString(serialCommand->em4ResponseData); 
					delete serialCommand;
					return true;
				}
				else
				{
					return false;
				}

			}

			bool DalDeviceHandler::SetIdleMode()
			{

				////Deepak: 12/Nov/2011
				////TODO: for testing only!!!!!!!!!!!!!!!!!
				//return false;
				////REVERT UPPER LINE WHEN DONE


				try
				{
					//bool returnValue;

					//Dont check device connection within this function.
					//Check before calling it.

					////first check if device is connected
					//returnValue = CheckIfDeviceIsConnected();

					////if device is not connected we cannot set the mode
					//if (false == returnValue)
					//{
					//	return false;
					//}
					////else create a command and send it

					//create a command object
					DalEM4Command^ setIdleCommand;

					setIdleCommand = gcnew DalEM4Command(Em4CommandCodes::SetIdleMode, nullptr);
					
					//this command can only be sent once
					setIdleCommand->retriesAllowed = 1;
					//set timeout to 15 seconds
					//setIdleCommand->timeoutPeriod = 15000; //miliseconds (Default is 50 ms)

					setIdleCommand->expectedResponseLength = 5;

					//send it
					DalReturnValue commandReturnValue;
					commandReturnValue = _commandInterface->SendCommandAndGetResponse(setIdleCommand);

					if (DalReturnValue::Success == commandReturnValue)
					//---if (DalReturnValue::Ack == commandReturnValue)
					{
						return true;
					}
					else
					{
						return false;
					}
				}
				catch(ScorException^)
				{
					throw;
				}
				catch(Exception ^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
			}

			//TS Stub
			bool DalDeviceHandler::IsCuffDeflated()
			{
				//Use the same command that is required to get the alarm source
				DalReturnValue returnedValue;
				DalEM4Command^ serialCommand;
				//unsigned long eaSourceFlag;

				try
				{
					serialCommand = gcnew DalEM4Command(Em4CommandCodes::GetAlarmStatus, nullptr);
					serialCommand->expectedResponseLength = Em4ResponseRequiredLength::GetAlarmStatus ;
					returnedValue = _commandInterface->SendCommandAndGetResponse(serialCommand); 
					
					if (returnedValue == DalReturnValue::Success)
					{
						
						//the status flag will be checked and any eventt raised
						//now we need to obtain the status flag and extract the cuff state
						return (DalCuffStateFlags::CUFF_STATE_DEFLATED == currentCuffState);
					}
					else
					{
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommandFailedErrCd, CrxStructCommonResourceMsg::DalErrCommandFailed, ErrorSeverity::Information );
					}

				}
				catch(ScorException^)
				{
					// rethrow the exception
					throw;
				}
	
			}

			
						
			DalReturnValue DalDeviceHandler::DalEm4Communication(unsigned char cmdCode, array<unsigned char> ^%data, unsigned int em4ResponseReqLen)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				serialCommand = gcnew DalEM4Command(cmdCode, data);
				serialCommand->expectedResponseLength = em4ResponseReqLen;
				
				returnedValue = _commandInterface->SendCommandAndGetResponse(serialCommand); ////renamed oringinal method
				
				data = serialCommand->em4ResponseData;

				return returnedValue;
			}

			//Set ConfigurationAndUsages Methods
			//----------------------------------
			String^ DalDeviceHandler::SerialNumberMpb()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::SerialNumberMpb};
				String^ moduleSerialNumber = String::Empty;
				
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::SerialNumberMpb);

				if (returnedValue == DalReturnValue::Success)
				{
					moduleSerialNumber = DalBinaryConversions::ConvertArrayToString(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommdPacketCreateFailErrCd, CrxStructCommonResourceMsg::DalErrCommdPacketCreateFail, ErrorSeverity::Exception);
				}
				return moduleSerialNumber;
			}			
			String^ DalDeviceHandler::ProcessorFirmwareVersionMpb()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::ProcessorFirmwareVersionMpb};
				String^ processorFirmwareVersionMpb = String::Empty;

				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::ProcessorFirmwareVersionMpb);
								
				if (returnedValue == DalReturnValue::Success)
				{
					processorFirmwareVersionMpb = DalBinaryConversions::ConvertArrayToString(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommdPacketCreateFailErrCd, CrxStructCommonResourceMsg::DalErrCommdPacketCreateFail, ErrorSeverity::Exception);
				}
				return processorFirmwareVersionMpb;
			}

			String^ DalDeviceHandler::PldSafetyFirmwareVersionMpb()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::PldSafetyFirmwareVersionMpb};
				String^ pldSafetyFirmwareVersionMpb = String::Empty;

				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::PldSafetyFirmwareVersionMpb);
								
				if (returnedValue == DalReturnValue::Success)
				{
					pldSafetyFirmwareVersionMpb = DalBinaryConversions::ConvertArrayToString(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommdPacketCreateFailErrCd, CrxStructCommonResourceMsg::DalErrCommdPacketCreateFail, ErrorSeverity::Exception);
				}
				return pldSafetyFirmwareVersionMpb;
			}

			String^ DalDeviceHandler::SerialNumberSuntechPcb()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::SerialNumberSuntechPcb};
				String^ serialNumberSuntechPcb = String::Empty;

				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::SerialNumberSuntechPcb);
				
				if (returnedValue == DalReturnValue::Success)
				{
					serialNumberSuntechPcb = DalBinaryConversions::ConvertArrayToString(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommdPacketCreateFailErrCd, CrxStructCommonResourceMsg::DalErrCommdPacketCreateFail, ErrorSeverity::Exception);
				}
				return serialNumberSuntechPcb;
			}

			String^ DalDeviceHandler::BPFirmwareVersionSuntech()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::BPFirmwareVersionSuntech};
				String^ bpFirmwareVersionSuntech = String::Empty;
				
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::BPFirmwareVersionSuntech);
				
				if (returnedValue == DalReturnValue::Success)
				{
					bpFirmwareVersionSuntech = DalBinaryConversions::ConvertArrayToString(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommdPacketCreateFailErrCd, CrxStructCommonResourceMsg::DalErrCommdPacketCreateFail, ErrorSeverity::Exception);
				}
				return bpFirmwareVersionSuntech;
			}

			String^ DalDeviceHandler::SafetyFirmwareVersionSuntech()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::SafetyFirmwareVersionSuntech};
				String^ safetyFirmwareVersionSuntech = String::Empty;

				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::SafetyFirmwareVersionSuntech);
				
				if (returnedValue == DalReturnValue::Success)
				{
					safetyFirmwareVersionSuntech = DalBinaryConversions::ConvertArrayToString(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommdPacketCreateFailErrCd, CrxStructCommonResourceMsg::DalErrCommdPacketCreateFail, ErrorSeverity::Exception);
				}
				return safetyFirmwareVersionSuntech;
			}

			String^ DalDeviceHandler::SerialNumberEm4()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::SerialNumberEm4};
				String^ moduleSerialNumber;

				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::SerialNumberEm4);
								
				if (returnedValue == DalReturnValue::Success)
				{
					moduleSerialNumber = DalBinaryConversions::ConvertArrayToString(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);
				}
				return moduleSerialNumber;
			}
		
			unsigned short DalDeviceHandler::HWConfigurationMpb()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::HWConfigurationMpb};

				unsigned short hwConfigurationMpb = 0;
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::HWConfigurationMpb);
				
				if (returnedValue == DalReturnValue::Success)
				{
					hwConfigurationMpb = (unsigned short) dataCode[0]; 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);
				}
			
				return hwConfigurationMpb;
			}

			unsigned short DalDeviceHandler::SystemConfigurationId()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::SystemConfigurationId};

				unsigned short SystemConfigurationId = 0;
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::SystemConfigurationId);
				
				if (returnedValue == DalReturnValue::Success)
				{
					SystemConfigurationId = (unsigned short) dataCode[0]; 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				}
			
				return SystemConfigurationId;
			}

			unsigned int DalDeviceHandler::NumberofPWVmeasurements()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array <unsigned char>^ dataCode = gcnew array <unsigned char> (1) {Em4CommandCodes::NumberofPWVmeasurements};

				unsigned int numberofPWVmeasurements = 0;
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::NumberofPWVmeasurements);

				if (returnedValue == DalReturnValue::Success)
				{
					numberofPWVmeasurements = DalBinaryConversions::TranslateThreeBytes(dataCode, 0); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			
				return numberofPWVmeasurements;
			}

			unsigned int DalDeviceHandler::NumberofPWAtonometermeasurements()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::NumberofPWAtonometermeasurements};

				unsigned int numberofPWAtonomeasurements = 0;
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::NumberofPWAtonometermeasurements);
				
				if (returnedValue == DalReturnValue::Success)
				{
					numberofPWAtonomeasurements = DalBinaryConversions::TranslateThreeBytes(dataCode, 0); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
				
				return numberofPWAtonomeasurements;
			}
			unsigned int DalDeviceHandler::NumberofPWAcuffmeasurements()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::NumberofPWAcuffmeasurements};

				unsigned int pwaCuffMeasurementsCounter = 0;
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::NumberofPWAcuffmeasurements);

				if (returnedValue == DalReturnValue::Success)
				{
					pwaCuffMeasurementsCounter = DalBinaryConversions::TranslateThreeBytes(dataCode, 0); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
				
				return pwaCuffMeasurementsCounter;
			}

			unsigned int DalDeviceHandler::NumberOfNibpMeasurements()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::NumberOfNibpMeasurements};
				unsigned int numberOfNibpMeasurements = 0;
				
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::NumberOfNibpMeasurements);

				if (returnedValue == DalReturnValue::Success)
				{
					numberOfNibpMeasurements = DalBinaryConversions::TranslateThreeBytes(dataCode, 0); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
				
				return numberOfNibpMeasurements;
			}

			DateTime DalDeviceHandler::CalibrationDateMpb()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::CalibrationDateMpb};
				DateTime dtCalibrationDateMpb ;
				
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::CalibrationDateMpb);

				if (returnedValue == DalReturnValue::Success)
				{
					dtCalibrationDateMpb = DalBinaryConversions::ConvertArrayIntoDate(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
				
				return dtCalibrationDateMpb;
			}
			DateTime DalDeviceHandler::CalibrationDateSuntech()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::CalibrationDateSuntech};
				DateTime dtCalibrationDateSuntech ;
				
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::CalibrationDateSuntech);

				if (returnedValue == DalReturnValue::Success)
				{
					dtCalibrationDateSuntech = DalBinaryConversions::ConvertArrayIntoDate(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
				
				return dtCalibrationDateSuntech;
			}			

			DateTime DalDeviceHandler::TestDate()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::TestDate};
				DateTime dtTestDate ;
				
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::TestDate);

				if (returnedValue == DalReturnValue::Success)
				{
					dtTestDate = DalBinaryConversions::ConvertArrayIntoDate(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
				
				return dtTestDate;
			}

			DateTime DalDeviceHandler::SystemConfigurationChangeDate()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::SystemConfigurationChangeDate};
				DateTime dtSystemConfigurationChangeDate ;
				
				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::SystemConfigurationChangeDate);

				if (returnedValue == DalReturnValue::Success)
				{
					dtSystemConfigurationChangeDate = DalBinaryConversions::ConvertArrayIntoDate(dataCode); 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
				
				return dtSystemConfigurationChangeDate;
			}

			unsigned short DalDeviceHandler::NotchFilterEnable()
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::NotchFilterEnable};

				unsigned short NotchFilterEnable = 0;

				returnedValue = DalEm4Communication(Em4CommandCodes::GetConfigInfo, dataCode, Em4ResponseRequiredLength::SystemConfigurationId);
				
				if (returnedValue == DalReturnValue::Success)
				{
					NotchFilterEnable = (unsigned short) dataCode[0]; 
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
				return NotchFilterEnable;
			}

			
			//Set ConfigurationAndUsages Methods
			//----------------------------------
			void DalDeviceHandler::SerialNumberMpb(String^ data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = DalBinaryConversions::ConvertStringToBytes(data);
				
				if(byteData->Length == Em4ConfigurationFieldLength::SerialNumberMpb)
				{
					//Convert string into bytes
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::SerialNumberMpb+1) {Em4CommandCodes::SerialNumberMpb};
					byteData->CopyTo(dataCode,1);
					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);
				}

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::ProcessorFirmwareVersionMpb(String^ data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				if(data->Length == Em4ConfigurationFieldLength::ProcessorFirmwareVersionMpb)
				{
					//Convert string into bytes
					array<unsigned char>^ byteData = DalBinaryConversions::ConvertStringToBytes(data);
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::ProcessorFirmwareVersionMpb+1) {Em4CommandCodes::ProcessorFirmwareVersionMpb};
					
					byteData->CopyTo(dataCode,1);
					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);
				}

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::PldSafetyFirmwareVersionMpb(String^ data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				if(data->Length == Em4ConfigurationFieldLength::PldSafetyFirmwareVersionMpb)
				{
					array<unsigned char>^ byteData = DalBinaryConversions::ConvertStringToBytes(data);
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::PldSafetyFirmwareVersionMpb+1) {Em4CommandCodes::PldSafetyFirmwareVersionMpb};
					
					byteData->CopyTo(dataCode,1);
					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);
				}

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::SerialNumberSuntechPcb(String^ data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				if(data->Length == Em4ConfigurationFieldLength::SerialNumberSuntechPcb)
				{
					array<unsigned char>^ byteData = DalBinaryConversions::ConvertStringToBytes(data);
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::SerialNumberSuntechPcb+1) {Em4CommandCodes::SerialNumberSuntechPcb};
					
					byteData->CopyTo(dataCode,1);
					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);
				}

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::BPFirmwareVersionSuntech(String^ data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				if(data->Length == Em4ConfigurationFieldLength::BPFirmwareVersionSuntech)
				{
					array<unsigned char>^ byteData = DalBinaryConversions::ConvertStringToBytes(data);
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::BPFirmwareVersionSuntech+1) {Em4CommandCodes::BPFirmwareVersionSuntech};
					
					byteData->CopyTo(dataCode,1);
					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);
				}

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::SafetyFirmwareVersionSuntech(String^ data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				if(data->Length == Em4ConfigurationFieldLength::SafetyFirmwareVersionSuntech)
				{
					array<unsigned char>^ byteData = DalBinaryConversions::ConvertStringToBytes(data);
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::SafetyFirmwareVersionSuntech+1) {Em4CommandCodes::SafetyFirmwareVersionSuntech};
					
					byteData->CopyTo(dataCode,1);
					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);
				}

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::SerialNumberEm4(String^ data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				if(data->Length == Em4ConfigurationFieldLength::SerialNumberEm4)
				{
					array<unsigned char>^ byteData = DalBinaryConversions::ConvertStringToBytes(data);
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::SerialNumberEm4+1) {Em4CommandCodes::SerialNumberEm4};
					
					byteData->CopyTo(dataCode,1);
					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);
				}

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}
			
			void DalDeviceHandler::HWConfigurationMpb(unsigned short data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::HWConfigurationMpb);
				byteData[0] = (unsigned char)(data & 0x00FF);
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::HWConfigurationMpb+1) {Em4CommandCodes::HWConfigurationMpb};
				
				byteData->CopyTo(dataCode,1);
				returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::SystemConfigurationId(unsigned short data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::SystemConfigurationId);
				byteData[0] = (unsigned char)(data & 0x00FF);
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::SystemConfigurationId+1) {Em4CommandCodes::SystemConfigurationId};
				
				byteData->CopyTo(dataCode,1);
				returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::NumberofPWVmeasurements(unsigned int data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NumberofPWVmeasurements);
				byteData = DalBinaryConversions::ConvertThreeBytesIntoArray(data);
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NumberofPWVmeasurements+1) {Em4CommandCodes::NumberofPWVmeasurements};
				
				byteData->CopyTo(dataCode,1);
				returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::NumberofPWAtonometermeasurements(unsigned int data)	
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NumberofPWAtonometermeasurements);
			
				byteData = DalBinaryConversions::ConvertThreeBytesIntoArray(data);
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NumberofPWAtonometermeasurements+1) {Em4CommandCodes::NumberofPWAtonometermeasurements};
				byteData->CopyTo(dataCode,1);

				returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::NumberofPWAcuffmeasurements(unsigned int data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NumberofPWAcuffmeasurements);
				
				byteData = DalBinaryConversions::ConvertThreeBytesIntoArray(data);
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NumberofPWAcuffmeasurements+1) {Em4CommandCodes::NumberofPWAcuffmeasurements};
				byteData->CopyTo(dataCode,1);

				returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}

			void DalDeviceHandler::NumberOfNibpMeasurements(unsigned int data)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NumberOfNibpMeasurements);
				
				byteData = DalBinaryConversions::ConvertThreeBytesIntoArray(data);
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NumberOfNibpMeasurements+1) {Em4CommandCodes::NumberOfNibpMeasurements};
				byteData->CopyTo(dataCode,1);

				returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			}
			void DalDeviceHandler::CalibrationDateMpb(DateTime data)	
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::CalibrationDateMpb);
				
				////need to check the data
				byteData[5] = (unsigned char)((unsigned int)data.Minute & 0x00FF);
				byteData[4] = (unsigned char)((unsigned int)data.Hour & 0x00FF);
				byteData[3] = (unsigned char)((unsigned int)data.Day & 0x00FF);
				byteData[2] = (unsigned char)((unsigned int)data.Month & 0x00FF);
				byteData[0] = (unsigned char)((unsigned int)data.Year & 0x00FF);
				byteData[1] = ((unsigned char)(((unsigned int)data.Year & 0xFF00) >> 8));
				
				byteData = DalBinaryConversions::ConvertDateIntoArray(data);

				if ( byteData[0] != 0x0000  || byteData[1] != 0x0000)
				{
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::CalibrationDateMpb+1) {Em4CommandCodes::CalibrationDateMpb};
					byteData->CopyTo(dataCode,1);

					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

					if (returnedValue == DalReturnValue::Success)
					{
						delete serialCommand;	
					}
					else
					{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
					}
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalInvallidDateTimeErrCd, CrxStructCommonResourceMsg::DalInvallidDateTime, ErrorSeverity::Exception);				
				}
			}
			void DalDeviceHandler::CalibrationDateSuntech(DateTime data)	
			{ 
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::CalibrationDateSuntech);
				
				////need to check the data
				byteData[5] = (unsigned char)((unsigned int)data.Minute & 0x00FF);
				byteData[4] = (unsigned char)((unsigned int)data.Hour & 0x00FF);
				byteData[3] = (unsigned char)((unsigned int)data.Day & 0x00FF);
				byteData[2] = (unsigned char)((unsigned int)data.Month & 0x00FF);
				byteData[0] = (unsigned char)((unsigned int)data.Year & 0x00FF);
				byteData[1] = ((unsigned char)(((unsigned int)data.Year & 0xFF00) >> 8));
				
				byteData = DalBinaryConversions::ConvertDateIntoArray(data);

				if ( byteData[0] != 0x0000  || byteData[1] != 0x0000)
				{
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::CalibrationDateSuntech+1) {Em4CommandCodes::CalibrationDateSuntech};
					byteData->CopyTo(dataCode,1);

					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

					if (returnedValue == DalReturnValue::Success)
					{
						delete serialCommand;	
					}
					else
					{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
					}
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalInvallidDateTimeErrCd, CrxStructCommonResourceMsg::DalInvallidDateTime, ErrorSeverity::Exception);				
				}
			}
			void DalDeviceHandler::TestDate(DateTime data)	
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::TestDate);
				
				////need to check the data
				byteData[5] = (unsigned char)((unsigned int)data.Minute & 0x00FF);
				byteData[4] = (unsigned char)((unsigned int)data.Hour & 0x00FF);
				byteData[3] = (unsigned char)((unsigned int)data.Day & 0x00FF);
				byteData[2] = (unsigned char)((unsigned int)data.Month & 0x00FF);
				byteData[0] = (unsigned char)((unsigned int)data.Year & 0x00FF);
				byteData[1] = ((unsigned char)(((unsigned int)data.Year & 0xFF00) >> 8));
				
				byteData = DalBinaryConversions::ConvertDateIntoArray(data);

				if ( byteData[0] != 0x0000  || byteData[1] != 0x0000)
				{
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::TestDate+1) {Em4CommandCodes::TestDate};
					byteData->CopyTo(dataCode,1);

					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

					if (returnedValue == DalReturnValue::Success)
					{
						delete serialCommand;	
					}
					else
					{
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
					}
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalInvallidDateTimeErrCd, CrxStructCommonResourceMsg::DalInvallidDateTime, ErrorSeverity::Exception);				
				}
			}
			void DalDeviceHandler::SystemConfigurationChangeDate(DateTime data)	
			{ 
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::SystemConfigurationChangeDate);
				
				////need to check the data
				byteData[5] = (unsigned char)((unsigned int)data.Minute & 0x00FF);
				byteData[4] = (unsigned char)((unsigned int)data.Hour & 0x00FF);
				byteData[3] = (unsigned char)((unsigned int)data.Day & 0x00FF);
				byteData[2] = (unsigned char)((unsigned int)data.Month & 0x00FF);
				byteData[0] = (unsigned char)((unsigned int)data.Year & 0x00FF);
				byteData[1] = ((unsigned char)(((unsigned int)data.Year & 0xFF00) >> 8));
				
				byteData = DalBinaryConversions::ConvertDateIntoArray(data);

				if ( byteData[0] != 0x0000  || byteData[1] != 0x0000)
				{
					array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::SystemConfigurationChangeDate+1) {Em4CommandCodes::SystemConfigurationChangeDate};
					byteData->CopyTo(dataCode,1);

					returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

					if (returnedValue == DalReturnValue::Success)
					{
						delete serialCommand;	
					}
					else
					{
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
					}
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalInvallidDateTimeErrCd, CrxStructCommonResourceMsg::DalInvallidDateTime, ErrorSeverity::Exception);				
				}
			}
			
			void DalDeviceHandler::NotchFilterEnable(unsigned short data) 
			{ 
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;

				array<unsigned char>^ byteData = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NotchFilterEnable);
				
				byteData[0] = (unsigned char)(data & 0x00FF);
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (Em4ConfigurationFieldLength::NotchFilterEnable+1) {Em4CommandCodes::NotchFilterEnable};
				byteData->CopyTo(dataCode,1);
				returnedValue = DalEm4Communication(Em4CommandCodes::SetConfigInfo, dataCode, Em4ResponseRequiredLength::ZeroDataResponsePacket);

				if (returnedValue == DalReturnValue::Success)
				{
					delete serialCommand;	
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalFailedGetSetConfigParaErrCd, CrxStructCommonResourceMsg::DalFailedGetSetConfigPara, ErrorSeverity::Exception);				
				}
			};


			bool DalDeviceHandler::SetIdleModeProcess()
			{
				//Set Idle mode
				bool boolReturnValue;

				//boolReturnValue = SetIdleMode();
				int countRetry;
				int count = 0;
				int sleepTime = 3000;

				sleepTime = Convert::ToInt32(CrxSytemParameters::Instance->GetStringTagValue("IdleModeSleepTime"));
				countRetry = (15000/sleepTime) + 1;
				Object^ obj;
				do
				{
						
					ScorException^ check = gcnew ScorException (CrxStructCommonResourceMsg::Dal_DeviceIdling_MessageErrCd, CrxStructCommonResourceMsg::Dal_DeviceIdling_Message, ErrorSeverity::Information);	
					CrxEventContainer::Instance->OnShowStatusEvent(obj, gcnew CrxShowStatusEventArgs(check));

					boolReturnValue = SetIdleMode();
					if(!boolReturnValue)
					{
						count++;
						Threading::Thread::Sleep(sleepTime); //Wait for 3 sec to re-check the idle mode
					}
				}
				while((!boolReturnValue) && (count < countRetry));

				if (false == boolReturnValue )
				{
					ScorException^ scorExObj = gcnew ScorException (1002, CrxStructCommonResourceMsg::Dal_DeviceNotReady_Message, ErrorSeverity::Information);	
					//CrxEventContainer::Instance->OnShowStatusEvent(obj, gcnew CrxShowStatusEventArgs(check));
					//throw scorExObj;
					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException , scorExObj);

					return false;
				}
				else
				{
					return true;
				}
			}



			
		}// end namespaces
	}
}