/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCommandState.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Companion source file for the command state machine.
*/


#include "stdafx.h"
#include "DalCommandState.h"
#include "DalCommandInterface.h"
#include "DalDeviceHandler.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::DataAccess::StateMachines;

using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{
	namespace Scor {
		namespace DataAccess {
			namespace StateMachines{ 

				DalCommandState::DalCommandState()
				{
					//No intialization required
				}

				DalReturnValue DalCommandState::SendCommandAndGetResponse(DalEM4Command ^)
				{
					//return failure by default. child class overrides will do actual processing
					return DalReturnValue::Failure; 
				}

				DalReturnValue DalCommandState::ValidateResponsePacket(DalEM4Command^ serialCommand)
				{
					serialCommand; //Dummy statement to get rid of C4100 warning

					//return failure by default. child class overrides will do actual processing
					return DalReturnValue::Failure; 
				}

				DalReturnValue DalCommandState::ListenForEM4Response(DalEM4Command ^serialCommand)
				{
					serialCommand; //Dummy statement to get rid of C4100 warning

					//return failure by default. child class overrides will do actual processing
					return DalReturnValue::Failure;
				}

				//DalReturnValue DalCommandState::ValidateCommandResult(AtCor::Scor::DataAccess::DalEM4Command ^serialCommand, AtCor::Scor::DataAccess::DalReturnValue responseReturnValue)
				//{
				//	//return failure by default. child class overrides will do actual processing
				//	return DalReturnValue::Failure ; 
				//}



				DalCommandStateReady::DalCommandStateReady()
				{
					//nothing to do
				}

				DalCommandStateReady^ DalCommandStateReady::operator =(DalCommandStateReady ^)
				{
					return this;
				}

				DalReturnValue DalCommandStateReady::SendCommandAndGetResponse(DalEM4Command ^serialCommand)
				{
					DalReturnValue returnValue;
					
					//now callthe actual methoid that sends a command and processes it.
					//Warning calling DalCommandInterface::SendCommandAndGetResponse is fatal 
					//bcause it will cause an internal loop.
					returnValue = DalCommandInterface::Instance->ProcessCommandAndResponse(serialCommand); 
					
					//since the command has been sent and processed we will go back to the ready state.
					DalCommandInterface::Instance->ChangeCommandState(DalCommandStateReady::Instance);

					return returnValue;

				}



				DalCommandStateWaiting::DalCommandStateWaiting()
				{
					//nothing to do
				}

				DalCommandStateWaiting^ DalCommandStateWaiting::operator =(DalCommandStateWaiting ^)
				{
					return this;
				}

				DalReturnValue DalCommandStateWaiting::ListenForEM4Response(DalEM4Command ^serialCommand)
				{
					DalReturnValue returnValue;

					returnValue = DalCommandInterface::Instance->ListenForEM4Response(serialCommand);

					if (DalReturnValue::Success == returnValue)
					{
						DalCommandInterface::Instance->ChangeCommandState(DalCommandStateResponseReceived::Instance);
					}
					else if (DalReturnValue::Timeout == returnValue)
					{
						DalCommandInterface::Instance->ChangeCommandState(DalCommandStateTimeout::Instance);
					}
					return returnValue;
				}

				DalCommandStateTimeout::DalCommandStateTimeout()
				{
					//nothing to do
				}

				DalCommandStateTimeout^ DalCommandStateTimeout::operator =(AtCor::Scor::DataAccess::StateMachines::DalCommandStateTimeout ^)
				{
					return this;
				}
	

				DalCommandStateResponseReceived::DalCommandStateResponseReceived()
				{
					//nothing to do
				}

				DalCommandStateResponseReceived^ DalCommandStateResponseReceived::operator =(DalCommandStateResponseReceived ^)
				{
					return this;
				}

				DalReturnValue DalCommandStateResponseReceived::ValidateResponsePacket(DalEM4Command ^serialCommand)
				{
					DalReturnValue returnValue;

					returnValue = DalCommandInterface::Instance->ValidateResponsePacket(serialCommand);

					DalCommandInterface::Instance->ChangeCommandState(DalCommandStateReady::Instance );

					return returnValue;

				}

			} //namespace StateMachines
		} //namespace DataAccess 
	} //namespace Scor
}//namespace AtCor

