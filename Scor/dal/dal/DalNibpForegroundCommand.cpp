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
			//Abort recieved
			this->currentForegroundState = DalNibpForegroundCommandState::RecievedA;
		}
		else if (0x42 == nibpToHostResponse[2])
		{
			//Abort recieved
			this->currentForegroundState = DalNibpForegroundCommandState::Busy;
		}
		
		//TODO: any more to add

		//then signal the waiting thread that it has something for it
		this->responseListenerThread->Interrupt();

	}
	//else simply ignore it it is of no use to us.

	return false;
}


DalReturnValue DalNibpForegroundCommand ::ListenForEM4Response()
{
	bool threadHasBeenTerminated = false;

	Stopwatch ^ responseTimeChecker = gcnew Stopwatch();
	responseTimeChecker->Start();

	//Start the thread that will process the events to arrive
	responseListenerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &DalNibpForegroundCommand::ResponseListenerThreadMethod));
	
	//register the event handler to listen for async data arrived events
	DalEventContainer::Instance->OnDalNibpPacketEvent += gcnew NibPPacketArrivedEventHandler(this, &DalNibpForegroundCommand::PacketArrivedProcessingMethod);

	responseListenerThread->Start();
	//wait for the time specified. 
	//if it does not return in the specied time go back
	threadHasBeenTerminated = responseListenerThread->Join(this->responseWaitingTimeMax);
	responseTimeChecker->Stop(); 
	CrxLogger::Instance->Write("DalNibpForegroundCommand ::ListenForEM4Response waited for "+responseTimeChecker->ElapsedMilliseconds+" ms and returned " +  threadHasBeenTerminated.ToString(), ErrorSeverity::Debug);

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
		ProcessNibpResponse();
		//check the state 

		//deregister this thread
		//StopListeningForEM4response();

		return DalReturnValue::Success;

	}

	//return DalReturnValue::Failure; //unreachable
}


bool DalNibpForegroundCommand::StopListeningForEM4response()
{
	CrxLogger::Instance->Write("DalNibpForegroundCommand::StopListeningForEM4response", ErrorSeverity::Debug);
	delete responseListenerThread;

	DalEventContainer::Instance->OnDalNibpPacketEvent -= gcnew NibPPacketArrivedEventHandler(this, &DalNibpForegroundCommand::PacketArrivedProcessingMethod);


	return false;
}

void DalNibpForegroundCommand::ResponseListenerThreadMethod(System::Object ^)
{
	try
	{
		//TODO: see if this timout should be infinite
		//sleep until timeout expires or the thread is woken up
		Thread::Sleep(Timeout::Infinite); 
	}
	catch(ThreadInterruptedException^ threadInterruptEx)
	{
		//this means that the data has arrived. 
		//We need to  process it or take some action

		delete threadInterruptEx;
		////CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ResponseListenerThreadMethod ThreadInterruptedException raised", ErrorSeverity::Debug);
	}
}

bool DalNibpForegroundCommand::ProcessNibpResponse()
{
	//let child objects decide what they want to do with the result
	//we dont want to do anythin here
	return false;
}