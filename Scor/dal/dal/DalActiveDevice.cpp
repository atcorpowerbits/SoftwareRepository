/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalActiveDevice.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Code file for DalActiveDevice class
*/

#include "stdafx.h"
#include "DalCommon.h"
#include "DalActiveDevice.h"
#include "DalPwvSimulationHandler.h"
#include "DalCPwaSimulationHandler.h"
//#include "DalMeasurementMode.h"
//#include "DalPwvMode.h"
#include "DalModule.h"
#include "DalPwvDeviceHandler.h"
#include "DalCPwaDeviceHandler.h"

using namespace System::ComponentModel;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			DalActiveDevice::DalActiveDevice()
			{
				//Set the current capture data type to cuff pulse and tonometer by default.
				DalActiveDevice::_currentDevice = nullptr;
				
				//Call method to set the current device
				//SetDeviceStrategy();
				
				//register the event handler that will run when the config setting's comm port is changed.
				CrxEventContainer::Instance->OnCommsPortEvent += gcnew CommsPortEventHandler(&DalActiveDevice::ConfigCommsPortSettingChangeHandler);
			}

			DalActiveDevice::DalActiveDevice(DalActiveDevice ^)
			{
				//overloaded copy constructor.
				//Does nothing
			}

			bool DalActiveDevice::SetDeviceStrategy()
			{
				try
				{
					String ^ comPortInConfig; 
					DalStreamingMode currStreamingMode;
					
					//obtain the setting from config manager.
					CrxConfigManager ^configMgr = CrxConfigManager::Instance;
					configMgr->GetGeneralUserSettings();
					configMgr->GetPwvUserSettings();
					//Get the simulation type as set in configuration.
					comPortInConfig = configMgr->GeneralSettings->CommsPort->ToUpper();

					currStreamingMode = DalModule::Instance->StreamingMode;
					
					//if (currStreamingMode  == DalStreamingMode::None)
					//{
					//	currMode == configMgr->GeneralSettings->StartupMode;
					//}
					//else if(currStreamingMode  == DalStreamingMode::Pwv)
					//{
					//	currMode == oMsg->GetMessage(CrxStructCommonResourceMsg::DocPwvSettings);
					//}
					//else if(currStreamingMode  == DalStreamingMode::cPwa)
					//{
					//	currMode == oMsg->GetMessage(CrxStructCommonResourceMsg::DocPwaSettings);
					//}
					//else
					//{
					//	currMode = String::Empty;
					//}
					
					if (String::IsNullOrEmpty(comPortInConfig))
					{
						//make it simualtion by default Dont throw exception
						//comPortInConfig = CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::ComportSimulation);
						comPortInConfig = CrxStructCommonResourceMsg::Simulation;

						//set the com port as simulation in Config file
						configMgr->GeneralSettings->CommsPort = comPortInConfig->ToUpper();
						configMgr->SetGeneralUserSettings(configMgr->GeneralSettings);
						//CrxLogger::Instance->Write(CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::DalMsgDefaultModeSelectedSim), ErrorSeverity::Debug);
					}

					//SetDeviceStrategy(comPortInConfig); 
					SetDeviceStrategy(comPortInConfig, currStreamingMode);
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

//			//TODO: This method will be removed in future as new over loaded method is created, which takes 
//			//		two arguments
//			bool DalActiveDevice::SetDeviceStrategy(String ^commPort)
//			{
//				try
//				{
//					CrxMessagingManager ^oMsg = CrxMessagingManager::Instance;
//
//					if (commPort == nullptr)
//					{
//						//A null string was passed when a comm port was expected.
//						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrComportNotSetErrCd, CrxStructCommonResourceMsg::DalErrComportNotSet, ErrorSeverity::Exception);
//					}
//	                
//					//Compare with the "simulation" string CrxMessaging
//					if (String::Compare(commPort->Replace(DalFormatterStrings::SingleSpaceString,String::Empty), CrxStructCommonResourceMsg::Simulation, true) == 0)
//					{
//						//if config manager returns "simulation" initialize the DalSimulationHander
//						//create a new simulation handler
////						if (DalStreamingMode::Pwv == DalModule::Instance->StreamingMode)
//						{
//							_currentDevice = DalPwvSimulationHandler::Instance;
//						}
////						else if(DalStreamingMode::cPwa == DalModule::Instance->StreamingMode)
//						{
//							//To Do: Change to cPwa
//							//_currentDevice = DalPwvSimulationHandler::Instance;
//						}
////						else
//						{
//							//_currentDevice = nullptr;
//						}
//
//					}
//					else
//					{
//						if (DalStreamingMode::Pwv == DalModule::Instance->StreamingMode)
//						{
//							_currentDevice = gcnew DalPwvDeviceHandler();
//						}
//						else if (DalStreamingMode::Pwv == DalModule::Instance->StreamingMode)
//						{
//							_currentDevice = gcnew DalCPwaDeviceHandler();
//						}
//						else
//						{
//							_currentDevice = nullptr;
//							throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNoInterfaceErrCd, CrxStructCommonResourceMsg::DalErrNoInterface, ErrorSeverity::Exception);
//							
//						}
//					}
//				}
//				catch(ScorException ^)
//				{
//					throw;
//				}
//				catch(Exception ^ excepObj)
//				{
//					throw gcnew ScorException(excepObj);
//				}
//
//				return true;
//			}

			bool DalActiveDevice::SetDeviceStrategy(String ^commPort, DalStreamingMode mode)
			{
				try
				{
					//CrxMessagingManager ^oMsg = CrxMessagingManager::Instance;
					
					if (commPort == nullptr)
					{
						//A null string was passed when a comm port was expected.
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrComportNotSetErrCd, CrxStructCommonResourceMsg::DalErrComportNotSet, ErrorSeverity::Exception);
					}
	                
					//Compare with the "simulation" string CrxMessaging
					if (String::Compare(commPort->Replace(DalFormatterStrings::SingleSpaceString,String::Empty), CrxStructCommonResourceMsg::Simulation, true) == 0)
					{
						SetSimulationAsCurrent(mode);
						//if(_currentDevice != nullptr)
						//{
						//	_currentDevice->CloseFiles();
						//}
						////if config manager returns "simulation" initialize the DalSimulationHander
						////create a new simulation handler
						//if (DalStreamingMode::Pwv == mode)
						//{
						//	_currentDevice = DalPwvSimulationHandler::Instance;
						//}
						//else if(DalStreamingMode::cPwa == mode)
						//{
						//	_currentDevice = DalCPwaSimulationHandler::Instance;
						//}
						//else if(DalStreamingMode::tPwa == mode)
						//{
						//	//To Do: Change to tPwa
						//	_currentDevice = nullptr;
						//}
						//else
						//{
						//	_currentDevice = nullptr;
						//	throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNoInterfaceErrCd, CrxStructCommonResourceMsg::DalErrNoInterface, ErrorSeverity::Exception);	
						//}
					}
					else //This is an EM4 device port
					{

						SetDeviceAsCurrent(mode);
						/*if (DalStreamingMode::Pwv == mode)
						{
							_currentDevice = gcnew DalPwvDeviceHandler();
						}
							else if (DalStreamingMode::cPwa == mode)
						{
							_currentDevice = gcnew DalCPwaDeviceHandler();
						}
						else
						{
							_currentDevice = nullptr;
							throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNoInterfaceErrCd, CrxStructCommonResourceMsg::DalErrNoInterface, ErrorSeverity::Exception);
							
						}*/
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

			void DalActiveDevice::SetSimulationAsCurrent(DalStreamingMode mode)
			{
						if(_currentDevice != nullptr)
						{
							_currentDevice->CloseFiles();
						}
						//if config manager returns "simulation" initialize the DalSimulationHander
						//create a new simulation handler
						if (DalStreamingMode::Pwv == mode)
						{
							_currentDevice = DalPwvSimulationHandler::Instance;
						}
						else if(DalStreamingMode::cPwa == mode)
						{
							_currentDevice = DalCPwaSimulationHandler::Instance;
						}
						else if(DalStreamingMode::tPwa == mode)
						{
							//To Do: Change to tPwa
							_currentDevice = nullptr;
						}
						else
						{
							_currentDevice = nullptr;
							throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNoInterfaceErrCd, CrxStructCommonResourceMsg::DalErrNoInterface, ErrorSeverity::Exception);	
						}
					}

			void DalActiveDevice::SetDeviceAsCurrent(DalStreamingMode mode)
					{
							if (DalStreamingMode::Pwv == mode)
						{
							_currentDevice = gcnew DalPwvDeviceHandler();
						}
							else if (DalStreamingMode::cPwa == mode)
						{
							_currentDevice = gcnew DalCPwaDeviceHandler();
						}
						else
						{
							_currentDevice = nullptr;
							throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNoInterfaceErrCd, CrxStructCommonResourceMsg::DalErrNoInterface, ErrorSeverity::Exception);
							
						}
			}

			DalActiveDevice^ DalActiveDevice::operator =(DalActiveDevice)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}

			//bool DalActiveDevice::GetConnectionStatus()
			//{
			//	if (_currentDevice)
			//	{
			//		//call the active device method
			//		return _currentDevice->GetConnectionStatus();
			//	}
			//	return false;
			//}

			//bool DalActiveDevice::GetConfigurationInfo(DalDeviceConfigUsageEnum deviceConfigItem, 
			//								DalDeviceConfigUsageStruct ^deviceConfigInfo )
			//{
			//	if (_currentDevice)
			//	{
			//		//call the active device method
			//		return _currentDevice->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
			//	}
			//	return false;
			//}

			DalFindModuleResult DalActiveDevice::FindModule(String ^%deviceFoundPort)
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
				//use true to ignore the case
				if (0 == String::Compare(configPort->Replace(DalFormatterStrings::SingleSpaceString,String::Empty), CrxStructCommonResourceMsg::Simulation, true) )
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
						//SetDeviceStrategy(deviceFoundPort);
						SetDeviceStrategy(deviceFoundPort, DalModule::Instance->StreamingMode);

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
					//SetDeviceStrategy(deviceFoundPort);
					SetDeviceStrategy(deviceFoundPort, DalModule::Instance->StreamingMode);

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

			//String^ DalActiveDevice::GetErrorAlarmSource()
			//{
			//	if (_currentDevice)
			//	{
			//		//call the active device method
			//		return _currentDevice->GetAlarmSource();
			//	}
			//	return nullptr;

			//}

			//	/**
			//GetPWVMeasurementCounter()

			//DESCRIPTION:	Returns the PWV measurement counter stored in the firmware.

			//INPUT:	None.

			//OUTPUT:		count.

			//RETURN:		boolean success or not.
			//*/
			//bool DalActiveDevice::GetPWVMeasurementCounter( unsigned short% count)
			//{
			//	// If the module is not connected return false, otherwise retrieve the count -
			//	// value and return true

			//	count = 0;

			//	return measurementCounterTest;
			//}

			///**
			//SetPWVMeasurementCounter()

			//DESCRIPTION

			//	Sets the PWV measurement counter stored in the firmware.

			//INPUT

			//	count.

			//OUTPUT

			//	None.

			//RETURN

			//	boolean success or not.
			//*/
			//bool DalActiveDevice::SetPWVMeasurementCounter( unsigned short count)
			//{
			//	count; //Dummy statement to get rid of C4100 warning

			//	// If the module is not connected return false, otherwise set the count -
			//	// value and return true

			//	return measurementCounterTest;
			//}


			/*String^ DalActiveDevice::GetSavedFilePath()
			{
				return _currentDevice->GetSavedFileName();
			}*/

			void DalActiveDevice::ConfigCommsPortSettingChangeHandler(Object^ , CommsPortEventArgs^ args)
			{
				//sender; //Dummy statement to get rid of C4100 warning

				CrxLogger::Instance->Write("DAl received Comms port change event: " + args->commsPortSetting, ErrorSeverity::Debug);
				//SetDeviceStrategy(args->commsPortSetting);
				SetDeviceStrategy(args->commsPortSetting, DalModule::Instance->StreamingMode);

			}

			bool DalActiveDevice::SearchAllPortsforDevice(String ^%foundPortName, String ^excludePort )
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
					////CrxLogger::Instance->Write("Ports Listed: " + portName, ErrorSeverity::Debug);
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

			//bool DalActiveDevice::CheckIfDeviceIsConnected()
			//{
			//	if (_currentDevice)
			//	{
			//		//call the active device method
			//		return _currentDevice->CheckIfDeviceIsConnected();
			//	}
			//	else
			//	{
			//		return false;
			//	}
			//}

			/*bool DalActiveDevice::SetPressure(unsigned int newPressure, EM4CuffBoard cuffBoard)
			{
				if (_currentDevice)
				{
					return _currentDevice->SetPressure(newPressure, cuffBoard);
				}
				else
				{
					return false;
				}
			}*/

			//bool DalActiveDevice::SetIdleMode()
			//{
			//	//call the actual method
			//	if (_currentDevice)
			//	{
			//		return _currentDevice->SetIdleMode();
			//	}
			//	else
			//	{
			//		return false;
			//	}
	
			//}

			//Fxcop reccommends that reference parameters should not be used
			//bool DalModule::IsAnnualCalibrationDue(System::DateTime ^%lastCalibrationDate)
			//{
			//	//Stub method. will be replaced by actual code later
			//	lastCalibrationDate = gcnew DateTime(2010, 5, 9);

			//	return true;

			//}

			//DateTime DalActiveDevice::GetLastCalibrationDate()
			//{
			//	//Stub method. will be replaced by actual code later
			//	return DateTime(2010, 5, 9);
			//}

			//void DalActiveDevice::SetStreamingMode(DalStreamingMode newMode)
			//{
			//	//Set the current mode
			//	_currentStreamingMode = newMode;
			//}

			////TS Stub
			//bool DalActiveDevice::IsCuffDeflated()
			//{
			//	if (_currentDevice)
			//	{
			//		//call the active device method
			//		return _currentDevice->IsCuffDeflated();
			//	}
			//	else
			//	{
			//		return true;
			//	}
			//}

			//TS Stub
			// Unit testing purpose only to force StartCapture to fail when 
			void DalActiveDevice::SetDeviceNull()
			{
				_currentDevice = nullptr;
			}



		}
	}
}