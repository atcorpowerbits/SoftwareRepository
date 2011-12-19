/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpForegroundCommand.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Code file for classes:  DalNibpForegroundCommand
*/

#include "stdafx.h"
#include "DalNibpForegroundCommand.h"


using namespace AtCor::Scor::DataAccess;
using namespace System::Diagnostics;
using namespace AtCor::Scor::CrossCutting::Messaging;

DalNibpForegroundCommand::DalNibpForegroundCommand():DalEM4HostToNibpCommand()
{
}

//DalNibpForegroundCommand::DalNibpForegroundCommand( array<unsigned char> ^ nibpPacket, unsigned int responseWaitTime):
//	DalEM4HostToNibpCommand(DalNibpCommandType::ForeGroundCommand , nibpPacket, responseWaitTime)
//{
//	this->currentForegroundState = DalNibpForegroundCommandState::NotSent;
//}


bool DalNibpForegroundCommand::ActOnPacket(array <unsigned char> ^ nibpToHostResponse)
{
	//check the length of the packet
	if (4 == nibpToHostResponse[1]) 
	{
		//this is a foreground packet response
			//take some action

		//attach it to the current object
		this->nibpResponsePacket = nibpToHostResponse;

		//chech the response data
		if (0x4F == nibpToHostResponse[2]) 
		{
			//O recieved
			this->currentForegroundState = DalNibpForegroundCommandState::RecievedO;
		}
		else if (0x4B == nibpToHostResponse[2])
		{
			//K recieved
			this->currentForegroundState = DalNibpForegroundCommandState::RecievedK;
		} 
		else if (0x41 == nibpToHostResponse[2])
		{
			//A (Abort) recieved
			this->currentForegroundState = DalNibpForegroundCommandState::RecievedA;
		}
		else if (0x42 == nibpToHostResponse[2])
		{
			//B (Busy) recieved
			this->currentForegroundState = DalNibpForegroundCommandState::Busy;
		}
		else if (0x45 == nibpToHostResponse[2])
		{
			//E (Error) packet recieved
			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNibpPacketEErrCd, CrxStructCommonResourceMsg::DalErrNibpPacketE, ErrorSeverity::Exception );
			/*
				Message: "DAL_ERR_NIBP_PACKET_E" :NIBP module indicated that it recieved a valid command but 
						it may be malformed.*/

		}
		else if (0x4E == nibpToHostResponse[2])
		{
			//N (No such command)
			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNibpPacketNErrCd,CrxStructCommonResourceMsg::DalErrNibpPacketN, ErrorSeverity::Exception );
			/*
				Message:"DAL_ERR_NIBP_PACKET_N": NIBP module recieved an unidentified command.*/

		}
		else if (0x44 == nibpToHostResponse[2])
		{
			//D (No such  121 (0x79) command)
			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNibpPacketDErrCd, CrxStructCommonResourceMsg::DalErrNibpPacketD, ErrorSeverity::Exception );
			/*
				Message: NIBP module recieved a '121' command with unrecognizable data.*/

		}
		else if (0x54 == nibpToHostResponse[2])
		{
			//T (Timeout)
			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrNibpPacketTErrCd, CrxStructCommonResourceMsg::DalErrNibpPacketT, ErrorSeverity::Exception );
			/*
				Message:  "DAL_ERR_NIBP_PACKET_T" A Timeout occured while the BP module was recieving a command.
			*/

		}
		//any more to add

		


		//then signal the waiting thread that it has something for it
		this->responseListenerThread->Interrupt();

		return true; //return true so that the calling event handler knows that this event has been consumed

	}
	//else simply ignore it it is of no use to us.

	return false;
}


DalReturnValue DalNibpForegroundCommand ::ListenForEM4Response()
{
	bool threadHasBeenTerminated = false;

	Stopwatch ^ responseTimeChecker = gcnew Stopwatch();
	responseTimeChecker->Start();

	if (responseListenerThread)
	{
		//CrxLogger::Instance->Write("DalNibpForegroundCommand ::ListenForEM4Response deleting old thread before creating new one:" +  (this->responseListenerThread)->GetHashCode() , ErrorSeverity::Debug);
		delete responseListenerThread;
	}
	//Start the thread that will process the events to arrive
	responseListenerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &DalNibpForegroundCommand::ResponseListenerThreadMethod));
	
	//register the event handler to listen for async data arrived events
	DalEventContainer::Instance->OnDalNibpPacketEvent += gcnew NibPPacketArrivedEventHandler(this, &DalNibpForegroundCommand::PacketArrivedProcessingMethod);

	responseListenerThread->Start();
	//wait for the time specified. 
	//if it does not return in the specied time go back
	//CrxLogger::Instance->Write("DalNibpForegroundCommand::ListenForEM4Response >> After Start(): responseListenerThread state: "+ this->responseListenerThread->ThreadState.ToString() + " Object type:"+ this->GetType() +  " thread Object iD" + (this->responseListenerThread)->GetHashCode() , ErrorSeverity::Debug );
	
	try
	{
	threadHasBeenTerminated = responseListenerThread->Join(this->responseWaitingTimeMax);
	}
	catch( ThreadInterruptedException ^ threadInterruptEx)
	{
		delete threadInterruptEx;

	}

	//CrxLogger::Instance->Write("DalNibpForegroundCommand::ListenForEM4Response >> After Join: responseListenerThread state: "+ this->responseListenerThread->ThreadState.ToString() + " Object type:"+ this->GetType() +  " thread Object iD" + (this->responseListenerThread)->GetHashCode()  , ErrorSeverity::Debug );
	responseTimeChecker->Stop(); 
	CrxLogger::Instance->Write("DalNibpForegroundCommand ::ListenForEM4Response waited for "+responseTimeChecker->ElapsedMilliseconds+" ms and threadHasBeenTerminated: " +  threadHasBeenTerminated.ToString(), ErrorSeverity::Debug);

	if (false == threadHasBeenTerminated)
	{
		//the thread did not recieve a signal within the expected time
		//do some dereigstering and inform that this object needs to be closed
		StopListeningForEM4response();

		//return failure
		return DalReturnValue::Failure;
	}
	else
	{
		//this thread was signaled that valid data is available

		//process this data

		//some commands will need to wait for both O & K before this thread returns
		//others will need to wait for only O to return and then launch a sepearate thread for K packet
		//Let the child class take action as appropriate
		DalReturnValue  returnValue;
		 returnValue = ProcessNibpResponse();

		 return  returnValue;

	}

	//return DalReturnValue::Failure; //unreachable
}


bool DalNibpForegroundCommand::StopListeningForEM4response()
{
	CrxLogger::Instance->Write("DalNibpForegroundCommand::StopListeningForEM4response responseListenerThread state: "+ responseListenerThread->ThreadState.ToString()+ " Aborting and deleting thread " + " thread Object iD" + (Thread::CurrentThread)->GetHashCode() , ErrorSeverity::Debug);
	responseListenerThread->Abort();
	delete responseListenerThread;

	DalEventContainer::Instance->OnDalNibpPacketEvent -= gcnew NibPPacketArrivedEventHandler(this, &DalNibpForegroundCommand::PacketArrivedProcessingMethod);


	return false;
}

void DalNibpForegroundCommand::ResponseListenerThreadMethod(System::Object ^)
{
	try
	{
		//sleep until timeout expires or the thread is woken up
		Thread::Sleep(this->responseWaitingTimeMax ); 
		CrxLogger::Instance->Write("DalNibpForegroundCommand::ResponseListenerThreadMethod woke up from sleep " + " thread Object iD" + (Thread::CurrentThread)->GetHashCode() , ErrorSeverity::Debug); 
	}
	catch(ThreadInterruptedException^ threadInterruptEx)
	{
		CrxLogger::Instance->Write("DalNibpForegroundCommand::ResponseListenerThreadMethod Interruped for " + this->GetType() + " threadState: " + this->responseListenerThread->ThreadState.ToString() + " thread Object iD" + (Thread::CurrentThread)->GetHashCode(), ErrorSeverity::Debug); 
	
		//this means that the data has arrived. 
		//We need to  process it or take some action

		delete threadInterruptEx;
	}
	catch(ThreadAbortException ^ )
	{
		CrxLogger::Instance->Write("DalNibpForegroundCommand::ResponseListenerThreadMethod Aborted!!!!! for " + this->GetType() + " threadState: " + this->responseListenerThread->ThreadState.ToString() + " thread Object iD" + (Thread::CurrentThread)->GetHashCode() , ErrorSeverity::Debug); 

	}
	//CrxLogger::Instance->Write("DalNibpForegroundCommand::ResponseListenerThreadMethod exiting for " + this->GetType() + " threadState: " + this->responseListenerThread->ThreadState.ToString() + " thread Object iD" + (Thread::CurrentThread)->GetHashCode(), ErrorSeverity::Debug); 
	
}

DalReturnValue  DalNibpForegroundCommand::ProcessNibpResponse()
{
	//let child objects decide what they want to do with the result
	//we dont want to do anythin here
	//return false;

	CrxLogger::Instance->Write("DalNibpForegroundCommand::ProcessNibpResponse returning DalReturnValue::Failure! This method should not be called. Child method should be called instead.", ErrorSeverity::Debug);
	return DalReturnValue::Failure;
}


DalNibpForegroundCommand::~DalNibpForegroundCommand()
{
	//CrxLogger::Instance->Write("DalNibpForegroundCommand::~DalNibpForegroundCommand called for object" + this->GetType() + " Hash Code: " + this->GetHashCode(), ErrorSeverity::Debug);
	
}