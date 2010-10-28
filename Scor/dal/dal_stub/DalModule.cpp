#include "stdafx.h"
#include "DalModule.h"


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			DalModule::DalModule()
			{
				DalModule::_captureDataType = TonometerAndCuffPulseCombination;
				DalModule::_currentDevice = nullptr;
				SetDeviceStrategy();
			}

			DalModule::DalModule(const AtCor::Scor::DataAccess::DalModule ^)
			{

			}

			void DalModule::SetDeviceStrategy()
			{
			}

			void DalModule::SetDeviceStrategy(System::String ^commPort)
			{
			}

			DalModule^ DalModule::operator =(const DalModule)
			{
				return this;
			}

			void DalModule::StartCapture()
			{
			}

			void DalModule::StopCapture()
			{
			}

			bool DalModule::GetConnectionStatus()
			{
				return false;
			}

			bool DalModule::GetConfigurationInfo(DalDeviceConfigUseageEnum deviceConfigItem, 
											DalDeviceConfigUsageStruct ^deviceConfigInfo )
			{
				return false;
			}

			String^ DalModule::FindModule()
			{
				return nullptr;
			}

		}
	}
}