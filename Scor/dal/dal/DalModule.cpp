/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalModule.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Code file for DalModule class
*/

#include "stdafx.h"
#include "DalModule.h"


using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;

using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			DalModule::DalModule()
			{
				//Set the current capture data type to cuff pulse and tonometer by default.				
				DalModule::_captureDataType = TonometerAndCuffPulseCombination;
				DalModule::_currentDevice = nullptr;
				
				//Call method to set the current device
				SetDeviceStrategy();
			}

			DalModule::DalModule(const AtCor::Scor::DataAccess::DalModule ^)
			{
				//overloaded copy constructor.
				//Does nothing
			}

			void DalModule::SetDeviceStrategy()
			{
				//obtain the setting from config manager.
				CrxConfigManager ^configMgr = CrxConfigManager::Instance;
                configMgr->GetGeneralUserSettings();
				//Get the simulation type as set in configuration.
                SetDeviceStrategy(configMgr->GeneralSettings->CommsPort);
				
			}

			void DalModule::SetDeviceStrategy(System::String ^commPort)
			{
				if (commPort == nullptr)
				{
					throw gcnew DalException("DAL_ERR_COMPORT_NOT_SET"); //A null string was passed when a comm port was expected.
				}
                
                CrxMessagingManager ^oMsg = CrxMessagingManager::Instance;

				//Compare with the "simulation" string CrxMessaging
               // if (commPort->Replace(" ","")->ToUpper() == oMsg->GetMessage("COMPORT_SIMULATION")->ToUpper()) //as per FxCop
				if (String::Compare(commPort->Replace(" ",""), oMsg->GetMessage("COMPORT_SIMULATION"), false) == 0)
				{
					//if config manager returns "simulation" initialize the DalSimulationHander
					_currentDevice = nullptr;
					_currentDevice = gcnew DalSimulationHandler();
				}
				else
				{
					//if the config manager retursn a comm port name call DalDeviceHandler
					_currentDevice = nullptr;
					_currentDevice = gcnew DalDeviceHandler();
				}
			}

			DalModule^ DalModule::operator =(const DalModule)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}

			void DalModule::StartCapture(int captureTime, int samplingRate)
			{
				if (_currentDevice)
				{
					//call the active device method
					_currentDevice->StartCapture(captureTime, samplingRate);
				}
			}

			void DalModule::StopCapture()
			{
				if (_currentDevice)
				{
					//call the active device method
					_currentDevice->StopCapture();
				}
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

			String^ DalModule::FindModule()
			{
				//This is a stub method.
				//It is only needed for EM4 device
				//For the present we will simply return null
				return nullptr;
			}

		}
	}
}