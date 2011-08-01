/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalModule.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Code file for DalModule class
*/

#include "stdafx.h"
#include "DalModule.h"

using namespace System::ComponentModel;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;

using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			DalModule::DalModule()
			{
				//Set the current capture data type to cuff pulse and tonometer by default.
				DalModule::_currentDevice = nullptr;
				
				//Call method to set the current device
				SetDeviceStrategy();
				
				// For testing only
				measurementCounterTest = true; //TODO:STUB
				
				//register the event handler that will run when the config setting's comm port is changed.
				CrxEventContainer::Instance->OnCommsPortEvent += gcnew CommsPortEventHandler(&DalModule::ConfigCommsPortSettingChangeHandler);
			}

			DalModule::DalModule(DalModule ^)
			{
				//overloaded copy constructor.
				//Does nothing
			}

			bool DalModule::SetDeviceStrategy()
			{
				try
				{
					String ^ comPortInConfig; 
					//obtain the setting from config manager.
					CrxConfigManager ^configMgr = CrxConfigManager::Instance;
					configMgr->GetGeneralUserSettings();
					configMgr->GetPwvUserSettings();
					//Get the simulation type as set in configuration.
					comPortInConfig = configMgr->GeneralSettings->CommsPort;

					if (String::IsNullOrEmpty(comPortInConfig))
					{
						//make it simualtion by default Dont throw exception
						comPortInConfig = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::ComportSimulation);

						//set the com port as simulation in Config file
						configMgr->GeneralSettings->CommsPort = comPortInConfig;
						configMgr->SetGeneralUserSettings(configMgr->GeneralSettings);
						CrxLogger::Instance->Write(CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalMsgDefaultModeSelectedSim));
					}

					SetDeviceStrategy(comPortInConfig); 
				}
				catch(ScorException ^)
				{
					throw;
				}
				catch(Exception ^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return true;
			}

			bool DalModule::SetDeviceStrategy(System::String ^commPort)
			{
				try
				{
					CrxMessagingManager ^oMsg = CrxMessagingManager::Instance;

					if (commPort == nullptr)
					{
						//A null string was passed when a comm port was expected.
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrComportNotSetErrCd, CrxStructCommonResourceMsg::DalErrComportNotSet, ErrorSeverity::Exception);
					}
	                
					//Compare with the "simulation" string CrxMessaging
              		if (String::Compare(commPort->Replace(DalFormatterStrings::SingleSpaceString,String::Empty), oMsg->GetMessage(CrxStructCommonResourceMsg::ComportSimulation), false) == 0)
					{
						//if config manager returns "simulation" initialize the DalSimulationHander
						//create a new simulation handler
						_currentDevice = DalSimulationHandler::Instance;
					}
					else
					{
						//since DAlDeviceHandler is implemented as a singleton we cannot use gcnew
						_currentDevice = DalDeviceHandler::Instance;
					}
				}
				catch(ScorException ^)
				{
					throw;
				}
				catch(Exception ^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return true;
			}

			DalModule^ DalModule::operator =(DalModule)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}

			//older method. was retained for compatilbilty, removed now
			//void DalModule::StartCapture()
			//{
			//	if (_currentDevice)
			//	{
			//		//call the active device method
			//		_currentDevice->StartCapture();
			//	}
			//}

			bool DalModule::StartMeasurement(int captureTime, int samplingRate)
			{
				if (_currentDevice)
				{
					//call the active device method
					return _currentDevice->StartCapture(captureTime, samplingRate);
				}

				return false;
			}

			bool DalModule::StopMeasurement()
			{
				if (_currentDevice)
				{
					//call the active device method
					return _currentDevice->StopCapture();
				}

				return false;
			}

			bool DalModule::GetConnectionStatus()
			{
				if (_currentDevice)
				{
					//call the active device method
					return _currentDevice->GetConnectionStatus();
				}
				return false;
			}

			bool DalModule::GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
											DalDeviceConfigUsageStruct ^deviceConfigInfo )
			{
				if (_currentDevice)
				{
					//call the active device method
					return _currentDevice->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
				}
				return false;
			}

			DalFindModuleResult DalModule::FindModule(String ^%deviceFoundPort)
			{
				//find module should search all ports regardless of whether 
				//it is in Simulation mode or Device mode

				String ^ configPort; //to store the COM port setting received from CONFIG
				String ^ commsPortInConfig; //This will store config comPort name only if it is a non-simulation
				
				
				//get the current com port setting from the Config file
				CrxConfigManager ^configMgr = CrxConfigManager::Instance;
                configMgr->GetGeneralUserSettings();
                configMgr->GetPwvUserSettings();
                configPort = configMgr->GeneralSettings->CommsPort;

				//first check if the current device is simulation
				//save it to a flag 
				//if find module fails to locate a real device we will need to go back to simulation.
				if (0 == String::Compare(configPort->Replace(DalFormatterStrings::SingleSpaceString,String::Empty), CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::ComportSimulation), false) )
				{
					//there was no real comms port in COnfig file
					commsPortInConfig = nullptr;
					
				}
				else
				{
					//it means that FindModule was called when a com port was selected 
					//save this comport present in config so that we dont end up searching it twice
					commsPortInConfig = configPort;
				}

				//if a valid COMMPort is specified in config first  check if the device is present there
				if (nullptr != commsPortInConfig)
				{
					if ((DalDeviceHandler::Instance->CheckIfDeviceIsConnected(commsPortInConfig))  )
					{
						//this is the correct port
						deviceFoundPort = commsPortInConfig;

						//This port is already set in config
						//so no need to update in config

						//set the current device to this port
						SetDeviceStrategy(deviceFoundPort);

						return DalFindModuleResult::ModuleFoundOnConfigPort; 
						//TO specify that the device was found on the 
						//same port as mentioned in COnfig file
					}
				}

				//if theConfig CommPort is simulation,
				//or if the port specified in config does not have the device check all other ports

				String^ foundPortName = nullptr; //String to recieve the found serial port name
				bool searchPortValue ; 
				searchPortValue = SearchAllPortsforDevice(foundPortName,commsPortInConfig);
				if (true == searchPortValue)
				{
					//return the found port name into the out parameter;
					deviceFoundPort = foundPortName;

					//set the current device to this instance
					SetDeviceStrategy(deviceFoundPort);

					//update the config setting
					configMgr->GeneralSettings->CommsPort = foundPortName;
					configMgr->SetGeneralUserSettings(configMgr->GeneralSettings);
					//return 2; 
					//this means that the device was found on a different port as specifed in config
					return DalFindModuleResult::ModuleFoundOnDifferentPort;
				}
				else
				{
					//device was not found
					//if device was simulation let it be 
					//if device was com port  let it be at the same port
					SetDeviceStrategy();
					//return 0;
					return DalFindModuleResult::ModuleNotFound;
				}
			
			}

			String^ DalModule::GetErrorAlarmSource()
			{
				if (_currentDevice)
				{
					//call the active device method
					return _currentDevice->GetAlarmSource();
				}
				return nullptr;

			}

				/**
			GetPWVMeasurementCounter()

			DESCRIPTION

				Returns the PWV measurement counter stored in the firmware.

			INPUT

				None.

			OUTPUT

				count.

			RETURN

				boolean success or not.
			*/
			bool DalModule::GetPWVMeasurementCounter( unsigned short% count)
			{
				// If the module is not connected return false, otherwise retrieve the count -
				// value and return true

				count = 0;

				return measurementCounterTest;
			}

			/**
			SetPWVMeasurementCounter()

			DESCRIPTION

				Sets the PWV measurement counter stored in the firmware.

			INPUT

				count.

			OUTPUT

				None.

			RETURN

				boolean success or not.
			*/
			bool DalModule::SetPWVMeasurementCounter( unsigned short count)
			{
				count; //Dummy statement to get rid of C4100 warning

				// If the module is not connected return false, otherwise set the count -
				// value and return true

				return measurementCounterTest;
			}

			bool DalModule::SaveCaptureData(array< unsigned short >^ tonometerData, array< unsigned short >^ cuffPulse, unsigned short bufferSize)
			{
				return _currentDevice->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
			}

			String^ DalModule::GetSavedFilePath()
			{
				return _currentDevice->GetSavedFileName();
			}

			void DalModule::ConfigCommsPortSettingChangeHandler(Object^ , CommsPortEventArgs^ args)
			{
				//sender; //Dummy statement to get rid of C4100 warning

				//CrxLogger::Instance->Write("DAl received Comms port change event: " + args->commsPortSetting );
				SetDeviceStrategy(args->commsPortSetting);

			}

			bool DalModule::SearchAllPortsforDevice(String ^%foundPortName, String ^excludePort )
			{

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
					//check if this port is excluded
					if ((portName == excludePort ) && (excludePort != nullptr) )
					{
						continue;
					}
					//CrxLogger::Instance->Write("Ports Listed: " + portName);
					if (DalDeviceHandler::Instance->CheckIfDeviceIsConnected(portName)) 
					{

						//found the port with the device
						//return the parameter and value;
						foundPortName = portName;
						return true; 
					}
				}

				return false; 
			}

			bool DalModule::CheckIfDeviceIsConnected()
			{
				if (_currentDevice)
				{
					//call the active device method
					return _currentDevice->CheckIfDeviceIsConnected();
				}
				else
				{
					return false;
				}
			}

			bool DalModule::SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard)
			{
				if (_currentDevice)
				{
					return _currentDevice->SetPressure(newPressure, cuffBoard);
				}
				else
				{
					return false;
				}
			}

			bool DalModule::SetIdleMode()
			{
				//call the actual method
				if (_currentDevice)
				{
					return _currentDevice->SetIdleMode();
				}
				else
				{
					return false;
				}
	
			}

			//Fxcop reccommends that reference parameters should not be used
			//bool DalModule::IsAnnualCalibrationDue(System::DateTime ^%lastCalibrationDate)
			//{
			//	//Stub method. will be replaced by actual code later
			//	lastCalibrationDate = gcnew DateTime(2010, 5, 9);

			//	return true;

			//}

			DateTime DalModule::GetLastCalibrationDate()
			{
				//Stub method. will be replaced by actual code later
				return DateTime(2010, 5, 9);
			}



		}
	}
}