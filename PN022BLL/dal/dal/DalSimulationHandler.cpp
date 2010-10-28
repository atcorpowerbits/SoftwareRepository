#include "stdafx.h"
#include "DalSimulationHandler.h"


namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalSimulationHandler::DalSimulationHandler()
			{
			}

			void DalSimulationHandler::StartCapture()
			{
			}

			void DalSimulationHandler::StopCapture()
			{
			}

			bool DalSimulationHandler::GetConnectionStatus()
			{
				return false;
			}

			bool DalSimulationHandler::GetConfigurationInfo (DalDeviceConfigUseageEnum deviceConfigItem, 
											  DalDeviceConfigUsageStruct deviceConfigInfo )
			{
				return false;
			}

			void DalSimulationHandler::OnTimerGetValuesAndRaiseEvents()
			{
			}
		
		}
	}
}

