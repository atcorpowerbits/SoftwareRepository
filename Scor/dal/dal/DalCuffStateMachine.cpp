/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCuffStateMachine.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalCuffStateMachine class
*/

#include "stdafx.h"
#include "DalCuffStateMachine.h"
#include "DalEventContainer.h"
#include "DalModule.h"


using namespace AtCor::Scor::DataAccess;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{
			
			DalCuffState::DalCuffState()
			{
				
			//	_currentDevice  = nullptr;
			//	_currentDevice = DalModule::Instance->_currentDevice ;
			}

			void DalCuffState::StartCapture()
			{
				//TODO
			}

			void DalCuffState::StartCapture(int captureTime, int samplingRate)
			{
				//TODO
			}

			void DalCuffState::StopCapture()
			{
				//TODO
			}

			bool DalCuffState::GetConnectionStatus()
			{
				if (this->GetType() == CuffDisconnected::typeid)
				{
					return false;
				}
				else
				{
					return true;
				}

			}

			String^ DalCuffState::GetErrorAlarmSource()
			{
				return nullptr;
				//TODO
			}

			void DalCuffState::ChangeState(DalCuffState^)
			{
				//todo
			}




			void CuffDeflated::StartCapture()
			{
				if (DalModule::Instance->_currentDevice)
				{
					DalModule::Instance->_currentDevice->StartCapture();
				}

			}

			void CuffDeflated::StartCapture(int captureTime, int samplingRate) 
			{
				
				if (DalModule::Instance->_currentDevice)
				{
					DalModule::Instance->_currentDevice->StartCapture(captureTime, samplingRate);
				}
			}

			
			
			void CuffInflating::StopCapture() 
			{
				if (DalModule::Instance->_currentDevice)
				{
					DalModule::Instance->_currentDevice->StopCapture();
				}
			}

			

			void CuffInflated::StopCapture() 
			{
				if (DalModule::Instance->_currentDevice)
				{
					DalModule::Instance->_currentDevice->StopCapture();
				}
			}


			void CuffDeflating::StartCapture()
			{
				if (DalModule::Instance->_currentDevice)
				{
					DalModule::Instance->_currentDevice->StartCapture();
				}

			}

			void CuffDeflating::StartCapture(int captureTime, int samplingRate)
			{
				if (DalModule::Instance->_currentDevice)
				{
					DalModule::Instance->_currentDevice->StartCapture(captureTime, samplingRate);
				}
			}

			CuffStateMachine::CuffStateMachine()
			{
				//TODO: recheck if below line is necessary
				DalEventContainer::Instance->OnDalCuffStatusEvent += gcnew DalCuffStatusEventHandler(&CuffStateMachine::CuffStateChangeListener);
				DalModule::Instance->_currentCuffState  = CuffDeflated::Instance;

			}

			CuffStateMachine::CuffStateMachine(const CuffStateMachine ^)
			{
				//overloaded copy constructor.
				//Does nothing
			}

			CuffStateMachine^ CuffStateMachine::operator= (const CuffStateMachine)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}

			void CuffStateMachine::ChangeState(AtCor::Scor::DataAccess::DalCuffState ^ newState)
			{
				//handle change of states
				DalModule::Instance->_currentCuffState  = newState;
			}

			void CuffStateMachine::CuffStateChangeListener(Object^ sender, DalCuffStatusEventArgs ^ args)
			{
				switch(args->CuffStateFlag)
				{
					case DalCuffStateFlags::CUFF_STATE_DEFLATED:
						ChangeState(CuffDeflated::Instance);
						break;
					case DalCuffStateFlags::CUFF_STATE_DEFLATING:
						ChangeState(CuffDeflating::Instance);
						break;
					case DalCuffStateFlags::CUFF_STATE_DISCONNECTED :
						ChangeState(CuffDeflated::Instance); //TODO: add disconnected state
						break;
					case DalCuffStateFlags::CUFF_STATE_INFLATED :
						ChangeState(CuffInflated::Instance);
						break;
					case DalCuffStateFlags::CUFF_STATE_INFLATING :
						ChangeState(CuffInflating::Instance);
						break;
					case DalCuffStateFlags::CUFF_STATE_UNKNOWN :
					default:
					//	_currentCuffState = nullptr; //TODO: See if you can get something else for this
						ChangeState(nullptr);
						break;

				}
			}

		}
	}
}

