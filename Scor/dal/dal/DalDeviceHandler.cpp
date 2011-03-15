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

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::DataAccess;


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

				//since we do not have a com port we will create a commandInterface without one
				/*if (_commandInterface)
				{
					_commandInterface = nullptr;
				}

				try
				{
					_commandInterface = gcnew DalCommandInterface();
				}*/

				//removing all DCI constructors and replacing with instance
				if (nullptr == _commandInterface)
				{
					_commandInterface = DalCommandInterface::Instance;
				}
			}

			//Deepak: Redundant due to change of design. Uncalled as of now. May need later - FxCop
			//DalDeviceHandler::DalDeviceHandler(String ^commPort)
			//{
			//	try
			//	{
			//		logObj = CrxLogger::Instance;
			//		messagingMgr = CrxMessagingManager::Instance;
			//	}
			//	catch(ScorException^)
			//	{
			//		throw;
			//	}

			//	//inititalize the comm coprt using the provided parameter.
			//	if (nullptr == commPort )
			//	{
			//		//A null string was passed when a comm port was expected.
			//		throw gcnew ScorException(1002, "DAL_ERR_COMPORT_NOT_SET", ErrorSeverity::Exception);
			//	}

			//	//if the parameters are fine set the current port
			//	_commPort = commPort;

			//	/*if (_commandInterface)
			//	{
			//		_commandInterface = nullptr;
			//	}

			//	try
			//	{
			//		_commandInterface = gcnew DalCommandInterface(_commPort);
			//	}
			//	catch(ScorException^)
			//	{
			//		_commandInterface = nullptr;
			//		throw;
			//	}*/
			//	
			//	//removing all DCI constructors and replacing with instance
			//	//if command interface hasnt already been provided , add a pointer to the singleton instance
			//	if (nullptr == _commandInterface)
			//	{
			//		_commandInterface = DalCommandInterface::Instance;
			//	}

			//	//now set the DCI instacne serial port
			//	try
			//	{
			//		_commandInterface->SetActivePort(commPort);
			//	}
			//	catch(ScorException^)
			//	{
			//		throw;
			//	}


			//	//if the port does open send a command on it to check if the device actually responds 
			//	//if it does not then the com port set by user in Settings does not have a device. Inform them.
			//	if (false == CheckIfDeviceIsConnected(_commandInterface))
			//	{
			//		throw gcnew ScorException(1019, "DAL_ERR_CONFIG_PORT_NOT_CONNECTED", ErrorSeverity::Information);
			//	}
			//}

			bool DalDeviceHandler::StartCapture()
			{
				// this code has been left for compatibility with the DAL stub
				//no parameters recieved. assume capture time and sampling rate
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

				////create the comand interface if it isnt already created
				//if (nullptr == _commandInterface)
				//{
				//	
				//	_commandInterface = DalCommandInterface::Instance ;
				//	if (!_commandInterface)
				//	{
				//		throw gcnew ScorException(1028, "DAL_ERR_DEV_INTERFACE_FATAL_ERROR", ErrorSeverity::Exception);
				//	}
				//}

				//first check if the device is connected on the comm port mention in Config.
				if(!CheckIfDeviceIsConnected())
				{
					throw gcnew ScorException(1019, "DAL_ERR_CONFIG_PORT_NOT_CONNECTED", ErrorSeverity::Information);
				}

				//check if tonometer is connected. Capture cannot proceed if it is disconnectd
				if(!CheckIfTonometerIsConnected())
				{
					throw gcnew ScorException(1020, "DAL_ERR_TONO_NOT_CONNECTED", ErrorSeverity::Information);
				}

				//now issue the command to start capture and see if the response was acknowledgement
				array<unsigned char> ^commandData = gcnew array<unsigned char> (1) {0x03}; //Make this 0x03 into a dynamic thing
				DalEM4Command ^ startCaptureCommand = gcnew DalEM4Command(0x06, commandData);
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

				//send command to stop capture
				DalEM4Command ^ startCaptureCommand = gcnew DalEM4Command(0x08, nullptr);
				DalReturnValue returnValue = DalReturnValue::Failure;

				returnValue = _commandInterface->SendCommand(startCaptureCommand);
				if (returnValue == DalReturnValue::Success)
				{
					return true;
				}
				else
				{
					return false;
				}

				if(_commandInterface->StopDataCaptureMode())
				{
					//failed to deregister the data capture handler
					throw gcnew ScorException(1021, "DAL_ERR_COMMAND_FAILED", ErrorSeverity::Information); 
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
											  DalDeviceConfigUsageStruct ^deviceConfigInfo )
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
						deviceConfigInfo->ModuleMainFWVersion = L"0.1 (stub)";
						break;
					case DalDeviceConfigUsageEnum::ModuleSerialNumber:
						return GetConfigDeviceSerialMumber(deviceConfigInfo->ModuleSerialNumber);
					case DalDeviceConfigUsageEnum::ModuleType:
						//Dummy value
						deviceConfigInfo->ModuleType = L"EM4 Device (stub)";
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
					serialCommand = gcnew DalEM4Command(0x11, nullptr);
					returnedValue = _commandInterface->SendCommand(serialCommand);

					if (returnedValue == DalReturnValue::Success)
					{
						eaSourceFlag = DalCommandInterface::TranslateFourBytes(serialCommand->em4ResponseData, 0);
						_currentEASourceFlag = eaSourceFlag  ;
						_currentEAStatusFlag = (serialCommand->em4StatusFlag) & 0x0028;

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
				if (String::Compare(commPort->Replace(" ",""), CrxMessagingManager::Instance->GetMessage("COMPORT_SIMULATION"), false) != 0)
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

				if (String::Compare(commPort->Replace(" ",""), messagingMgr->GetMessage("COMPORT_SIMULATION"), false) == 0)
				{
					throw gcnew ScorException(1018, "DAL_ERR_PORT_SIMULATION", ErrorSeverity::Information);
				}
				else
				{
					 return CheckIfDeviceIsConnected(commPort);
				}
				return false;
			}


			
			bool DalDeviceHandler::CheckIfDeviceIsConnected(String^ comPort)
			{
				bool returnValue = false;
				DalDeviceConfigUsageStruct^ configStruct = gcnew DalDeviceConfigUsageStruct();
				
				if (nullptr == comPort )
				{
					throw gcnew ScorException(1005, "DAL_ERR_INVALID_ARGS", ErrorSeverity::Warning );
				}

				//first check if this is the port already set in commandInterface
				//if yes then we SHOULD NOT open it again
				if ( (comPort == _commandInterface->ActiveSerialPortName) && (nullptr != _commandInterface))
				{
					try
					{
						//this com port has already been set 
						//we just need to verify if the device is present there
						return GetConfigurationInfo(DalDeviceConfigUsageEnum::ModuleSerialNumber, configStruct);
						
					
					}
					catch(ScorException ^)
					{
						throw; 
					}
				}
				else
				//{
				//	DalCommandInterface ^ currentCommandInterfaceInstance = _commandInterface;
				//	//this comPort is not set in command interface. 
				//	//We need to first open the port and then check if it is valid
				//	//then check if the device is present
				//	try
				//	{
				//		DalCommandInterface ^ newCommandInterface = gcnew DalCommandInterface(comPort);
				//	}
				//	catch(ScorException^)
				//	{
				//		return false;
				//	}
				//	//if the new cI object is created succesfull  set it as the current CI
				//	//we need to send a command and validate
				//	_commandInterface = newCommandInterface;
				//	try
				//	{
				//		returnValue = GetConfigurationInfo(DalDeviceConfigUsageEnum::ModuleSerialNumber, configStruct);
				//		if (true == returnValue)
				//		{
				//			_commandInterface = newCommandInterface;
				//		}
				//		else
				//		{
				//			_commandInterface = currentCommandInterfaceInstance;
				//		}
				//		return returnValue;
				//		
				//	}
				//	catch(ScorException ^)
				//	{
				//		//in case of a problem , revert back to the old CI object
				//		_commandInterface = currentCommandInterfaceInstance;
				//	}
				//}
				{
					
					//this comPort is not set in command interface. 
					//We need to first open the port and then check if it is valid
					//then check if the device is present
					
					try
					{
						_commandInterface->SetActivePort(comPort);
					}
					catch(ScorException^)
					{
						//this port didnt work
						//dont throw the exception so that we can try with another port
						return false;
					}
					//we need to send a command and validate
					try
					{
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

			//Deepak: Uncalled as of now. May need later - FxCop
			////this method is used internally only to verify if the com port specified in the DalDevliceHandlerConstructor 
			////has the EM4 device.
			////It should not initialize the port
			//bool DalDeviceHandler::CheckIfDeviceIsConnected(DalCommandInterface^ currentCommandInterface)
			//{

			//	if (nullptr == currentCommandInterface )
			//	{
			//		throw gcnew ScorException(1005, "DAL_ERR_INVALID_ARGS", ErrorSeverity::Warning );
			//	}

			//	bool returnValue = false;

			//	//call getConfigInfo(() and verify if this port responds
			//	DalDeviceConfigUsageStruct^ configStruct = gcnew DalDeviceConfigUsageStruct();

			//	returnValue = GetConfigurationInfo(DalDeviceConfigUsageEnum::ModuleSerialNumber, configStruct);
			//
			//	return returnValue;

			//}

			bool DalDeviceHandler::SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize)
			{
				
				unsigned short index = 0;
				bool saved = false;

			// construct the file path, file contains captured waveform data and of same format
			// as of the simulation file. (capture_DateTime.Dat).
			String^ tempFilePath = ".\\simulation\\pwv\\";
			String^ tempCapture = "capture_";
			String^ tempFileExt = ".dat";

			DateTime currentDateTime;
			currentDateTime = System::DateTime::Now;

			//create the file name using current date time
			String  ^ currentDateTimeStr = currentDateTime.ToString("yyyyMMMddHHmmss");
			currentDateTimeStr = tempFilePath + tempCapture + currentDateTimeStr+ tempFileExt; 
			
			DalSimulationFile^ simulationOutputFile; //Pointer to first simulation file
			simulationOutputFile = gcnew DalSimulationFile();

			if(simulationOutputFile->CreateFile(currentDateTimeStr))
			{
				while (index < bufferSize)
				{
					simulationOutputFile->SaveCurrentValues(tonometerData[index], cuffPulse[index]);
					index++;
				}
			}
			simulationOutputFile->CloseFile();
			return saved;
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
					commandByte = 0x09;
					
				}
				else if (cuffBoard == EM4CuffBoard::MainBoard)
				{
					commandByte = 0x0A;
				}

				try
				{
					DalEM4Command ^setPressureCommand = gcnew DalEM4Command(commandByte,pressureBytes);
					
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
					throw gcnew ScorException(1022, "DAL_ERR_NO_INTERFACE",ErrorSeverity::Warning );
				}
				
				DalReturnValue returnedValue = DalReturnValue::Failure ;

				DalEM4Command^ serialCommand = gcnew DalEM4Command(0x0B, gcnew array<unsigned char> (1){0x08});
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
					throw gcnew ScorException(1021, "DAL_ERR_COMMAND_FAILED",ErrorSeverity::Warning );
				}
			}


			String^ DalDeviceHandler::GetSavedFileName()
			{
				return _savedDataFilePath;
			}

			bool DalDeviceHandler::GetConfigDeviceSerialMumber(String ^% moduleSerialNumber)
			{
				DalReturnValue returnedValue =  DalReturnValue::Failure ;
				DalEM4Command^ serialCommand = nullptr;
				array<unsigned char>^ dataCode = gcnew array<unsigned char> (1) {0x08};

				serialCommand = gcnew DalEM4Command(0x0B, dataCode);
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