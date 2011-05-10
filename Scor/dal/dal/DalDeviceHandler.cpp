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
					logObj = CrxLogger::Instance;
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
			}


			bool DalDeviceHandler::StartCapture()
			{
				// this code has been left for compatibility with the DAL stub
				//no parameters recieved. assume capture time and sampling rate
				//since this function will be done away with , we are not moving the constants
				return StartCapture( 10, 256);
			}

			bool DalDeviceHandler::StartCapture(int captureTime, int samplingRate)
			{
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

				//first check if the device is connected on the comm port mention in Config.
				if(!CheckIfDeviceIsConnected())
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrConfigPortNotConnectedErrCd, CrxStructCommonResourceMsg::DalErrConfigPortNotConnected, ErrorSeverity::Information);
				}

				//check if tonometer is connected. Capture cannot proceed if it is disconnectd
				if(!CheckIfTonometerIsConnected())
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrTonoNotConnectedErrCd, CrxStructCommonResourceMsg::DalErrTonoNotConnected, ErrorSeverity::Information);
				}

				//now issue the command to start capture and see if the response was acknowledgement
				array<unsigned char> ^commandData = gcnew array<unsigned char> (1) {Em4CommandCodes::CaptureCommandDataPWVMode}; //Make this 0x03 into a dynamic thing
				DalEM4Command ^ startCaptureCommand = gcnew DalEM4Command(Em4CommandCodes::StartDataCapture , commandData);
				startCaptureCommand->expectedResponseLength = Em4ResponseRequiredLength::StartDataCapture ;
				
				DalReturnValue returnValue = DalReturnValue::Failure;

				returnValue = _commandInterface->SendCommand(startCaptureCommand);


				//if acknowledged start the handler to listen to the data received.
				if (DalReturnValue::Success == returnValue )
				{
					//start the handler for data capture here
					try
					{
						_commandInterface->InitiateDataCaptureMode();
						return true;
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
				//check if  the comand interface isnt already created
				if (nullptr == _commandInterface)
				{
					return false;
				}

				//deregister the data capture handler first
				if(!(_commandInterface->StopDataCaptureMode()))
				{
					//failed to deregister the data capture handler
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommandFailedErrCd, CrxStructCommonResourceMsg::DalErrCommandFailed, ErrorSeverity::Information); 
				}

				//send command to stop capture
				DalEM4Command ^ startCaptureCommand = gcnew DalEM4Command(Em4CommandCodes::StopDataCapture , nullptr);
				DalReturnValue returnValue = DalReturnValue::Failure;
				startCaptureCommand->expectedResponseLength = Em4ResponseRequiredLength::StopDataCapture; 

				returnValue = _commandInterface->SendCommand(startCaptureCommand);
				if (returnValue == DalReturnValue::Success)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool DalDeviceHandler::GetConnectionStatus()
			{
				//TODO
				//Stub method, needs to be implemented with state machine
				//will return false to show that it is disconnected until the functionality is implemented.
				return false;
			}

			bool DalDeviceHandler::GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct ^%deviceConfigInfo )
			{

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
						return GetConfigDeviceSerialMumber(deviceConfigInfo->ModuleSerialNumber);
					case DalDeviceConfigUsageEnum::ModuleType:
						//Dummy value
						//deviceConfigInfo->ModuleType = CrxMessagingManager::Instance->GetMessage("DAL_CONST_GCI_TYPE"); 
						deviceConfigInfo->ModuleType = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalConstGciType); 
						break;
					default:
						break;
				}

				//return false until this functionality is implemented
				return false;
			}

			String^ DalDeviceHandler::GetErrorAlarmSource() 
			{
				
				//We need to call a command to get the error alrm source
				DalReturnValue returnedValue;
				DalEM4Command^ serialCommand;
				unsigned long eaSourceFlag;

				try
				{
					serialCommand = gcnew DalEM4Command(Em4CommandCodes::GetAlarmStatus, nullptr);
					serialCommand->expectedResponseLength = Em4ResponseRequiredLength::GetAlarmStatus ;
					returnedValue = _commandInterface->SendCommand(serialCommand);

					if (returnedValue == DalReturnValue::Success)
					{
						eaSourceFlag = DalCommandInterface::TranslateFourBytes(serialCommand->em4ResponseData, 0);
						_currentEASourceFlag = eaSourceFlag  ;
						_currentEAStatusFlag = (serialCommand->em4StatusFlag) & (unsigned long)DalStatusFlagBitMask::ErrorAlarmStatusBitsMask;

						// call parent method
						return DalStatusHandler::GetErrorAlarmSource();
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
					//CrxLogger::Instance->Write("Ports Listed: " + portName);
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
				return false;
			}


			
			bool DalDeviceHandler::CheckIfDeviceIsConnected(String^ comPort)
			{
				if (nullptr == comPort )
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs, ErrorSeverity::Warning );
				}
				
				try
				{
					bool returnValue = false;
					DalDeviceConfigUsageStruct^ configStruct = gcnew DalDeviceConfigUsageStruct();
				
					//first check if this is the port already set in commandInterface
					//if yes then we SHOULD NOT open it again
					if ( (comPort == _commandInterface->ActiveSerialPortName) && (nullptr != _commandInterface))
					{
						//this com port has already been set 
						//we just need to verify if the device is present there
						return GetConfigurationInfo(DalDeviceConfigUsageEnum::ModuleSerialNumber, configStruct);
					}
					else
					{
						//this comPort is not set in command interface. 
						//We need to first open the port and then check if it is valid
						//then check if the device is present
						
						try
						{
							_commandInterface->SetActivePort(comPort);
						
							returnValue = GetConfigurationInfo(DalDeviceConfigUsageEnum::ModuleSerialNumber, configStruct);
							return returnValue;
						}
						catch(ScorException ^)
						{
							//this port didnt work
							//dont throw the exception so that we can try with another port
							return false;
						}
					}
					return false; 
				}
				catch(ScorException ^)
				{
					throw; 
				}
				catch(Exception ^excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
			}


			bool DalDeviceHandler::SetPressure(int newPressure, EM4CuffBoard cuffBoard)
			{
				unsigned short pressureToSet = (unsigned short)newPressure;

				unsigned char pressureMSB, pressureLSB, commandByte;

				pressureLSB = (unsigned char)(pressureToSet & 0x00FF);
				pressureMSB = ((unsigned char)((pressureToSet &0xFF00) >> 8));
				
				array<unsigned char> ^pressureBytes = gcnew array<unsigned char> {pressureMSB, pressureLSB};

				if (cuffBoard == EM4CuffBoard::SuntechBoard)
				{
					commandByte = Em4CommandCodes::SetPressureSuntechBoard;
					
				}
				else if (cuffBoard == EM4CuffBoard::MainBoard)
				{
					commandByte = Em4CommandCodes::SetPressureMainBoard;
				}

				try
				{
					DalEM4Command ^setPressureCommand = gcnew DalEM4Command(commandByte,pressureBytes);
					setPressureCommand->expectedResponseLength = Em4ResponseRequiredLength::SetPressure;
					
					if (_commandInterface->SendCommand(setPressureCommand) ==DalReturnValue::Success)
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
				 return false;
			}


			bool DalDeviceHandler::CheckIfTonometerIsConnected()
			{
				unsigned short statusFlag; 

				if (nullptr == _commandInterface)
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNoInterfaceErrCd, CrxStructCommonResourceMsg::DalErrNoInterface,ErrorSeverity::Warning );
				}
				
				DalReturnValue returnedValue = DalReturnValue::Failure ;

				DalEM4Command^ serialCommand = gcnew DalEM4Command(Em4CommandCodes::GetConfigInfo, gcnew array<unsigned char> (1){Em4CommandCodes::GetConfigInfoDataDeviceSerialNumber});
				serialCommand->expectedResponseLength = Em4ResponseRequiredLength::GetConfigInfoDataDeviceSerialNumber;
				returnedValue = _commandInterface->SendCommand(serialCommand);

				if (returnedValue == DalReturnValue::Success)
				{
					serialCommand->BreakupEM4Response();
					statusFlag = serialCommand->em4StatusFlag ;

					DalTonometerState tonoState;
					tonoState = (DalTonometerState)(statusFlag & (unsigned short)DalTonometerStatusBitMask::TonometerNotConnectedBits);
					if (DalTonometerState::Disconnected == tonoState)
					{
						return false;
					}
					else
					{
						return true;
					}
				}
				else
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCommandFailedErrCd, CrxStructCommonResourceMsg::DalErrCommandFailed,ErrorSeverity::Warning );
				}
			}


			/*String^ DalDeviceHandler::GetSavedFileName()
			{
				return _savedDataFilePath;
			}*/

			bool DalDeviceHandler::GetConfigDeviceSerialMumber(String ^% moduleSerialNumber)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {Em4CommandCodes::GetConfigInfoDataDeviceSerialNumber};

				serialCommand = gcnew DalEM4Command(Em4CommandCodes::GetConfigInfo, dataCode);
				serialCommand->expectedResponseLength = Em4ResponseRequiredLength::GetConfigInfoDataDeviceSerialNumber ;
				returnedValue = _commandInterface->SendCommand(serialCommand);
				if (returnedValue == DalReturnValue::Success)
				{
					moduleSerialNumber = ConvertBytesToString(serialCommand->em4ResponseData); 
					delete serialCommand;
					return true;
				}
				else
				{
					return false;
				}

			}
			
		}
	}
}