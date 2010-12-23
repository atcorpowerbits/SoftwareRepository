#include "stdafx.h"
#include "DalModule.h"

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
				// TBD: This method fails
				//SetDeviceStrategy();

				// For testing only
				measurementCounterTest = true;
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
					throw gcnew DalException(DAL_NULLCOMMPORT_ERR); //A null string was passed when a comm port was expected
				}
                
                CrxMessagingManager ^oMsg = CrxMessagingManager::Instance;

				//Compare with the "simulation" string CrxMessaging
                if (commPort->Replace(" ","")->ToUpper() == oMsg->GetMessage(DAL_SIMULATION)->ToUpper())
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

			void DalModule::StartCapture()
			{
				if (_currentDevice)
				{
					//call the active device method
					_currentDevice->StartCapture();
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
				// If the module is not connected return false, otherwise set the count -
				// value and return true

				return measurementCounterTest;
			}
		}
	}
}