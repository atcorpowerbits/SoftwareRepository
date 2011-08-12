/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalModule.cpp
        
     Author       :		 Victor Aung
 
     Description  :      DalModule class stub methods added by AtCor for unit testing
*/

#include "stdafx.h"
#include "DalModule.h"


using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;

using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			// Unit testing purpose only to force StartCapture to fail when 
			void DalModule::SetDeviceNull()
			{
				_currentDevice = nullptr;
			}
			void DalModule::SimulateActive()
			{
				DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(this, gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::ActiveStatus, "Normal"));
			}
			void DalModule::SimulateWarning()
			{
				DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(this, gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::RecoverableStatus, "Warning"));
			}
			void DalModule::SimulateError()
			{
				DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(this, gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::UnrecoverableStatus, "Error"));
			}
			bool DalModule::IsCuffDeflated()
			{
				if (_currentDevice)
				{
					//call the active device method
					return _currentDevice->IsCuffDeflated();
				}
				else
				{
					return true;
				}
				//if (0 == String::Compare(
				//	"Simulation",
				//	CrxMessagingManager::Instance->GetMessage(CrxStructCommonResourceMsg::ComportSimulation),
				//	false))
				//{
				//	return true;
				//}
				//else
				//{
				//	return false;
				//}
			}
		}
	}
}