/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpBackgroundCommand.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Code file for classes:  DalNibpBackgroundCommand
*/

#include "stdafx.h"
#include "DalNibpBackgroundCommand.h"

using namespace AtCor::Scor::DataAccess;


DalReturnValue DalNibpBackgroundCommand::ListenForEM4Response()
{
	bool threadHasBeenTerminated = false;
	DalReturnValue customReturnValue = DalReturnValue::Failure;
	//Start the thread that will process the events to arrive
	if (nullptr != responseListenerThread)
	{
		//CrxLogger::Instance->Write("DalNibpBackgroundCommand::ListenForEM4Response deleting old responseListenerThread", ErrorSeverity::Debug);
		delete responseListenerThread;
	}
	responseListenerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &DalNibpBackgroundCommand::ResponseListenerThreadMethod));

	
	//register the event handler to listen for async data arrived events
	DalEventContainer::Instance->OnDalNibpPacketEvent += gcnew NibPPacketArrivedEventHandler(this, &DalNibpBackgroundCommand::PacketArrivedProcessingMethod);

	this->currentBackGroundState = DalNibpBackGroundCommandState::WaitingForResponse;

	responseListenerThread->Start();

	//wait for the time specified. 
	//if it does not return in the specied time go back

	
	threadHasBeenTerminated = responseListenerThread->Join(this->responseWaitingTimeMax); 

	//CrxLogger::Instance->Write("DalNibpBackgroundCommand::ListenForEM4Response threadHasBeenTerminated:" + threadHasBeenTerminated+ " after waiting " + this->responseWaitingTimeMax +" ms.", ErrorSeverity::Debug);


	this->currentBackGroundState = DalNibpBackGroundCommandState::ResponseRecieved;


	if (false == threadHasBeenTerminated)
	{
		//the thread did not receive a signal within the expected time
		

		//return failure
		customReturnValue =  DalReturnValue::Timeout ;
	}
	else
	{
		//this thread was signaled that valid data is available
		if (DalNibpBackGroundCommandState::ResponseRecieved == this->currentBackGroundState )
		{

		//process this data (let the child do it. just put the placeholder method
		ProcessNibpResponse();

		//deregister this thread
		StopListeningForEM4response();

		customReturnValue =  DalReturnValue::Success;
		}
		else
		{
			customReturnValue =  DalReturnValue::Failure ;

		}

	}
	//do some dereigstering and inform that this object needs to be closed
	StopListeningForEM4response();

	return customReturnValue;

}

bool DalNibpBackgroundCommand::StopListeningForEM4response()
{
	delete responseListenerThread;

	DalEventContainer::Instance->OnDalNibpPacketEvent -= gcnew NibPPacketArrivedEventHandler(this, &DalNibpBackgroundCommand::PacketArrivedProcessingMethod);


	return false;
}


DalNibpBackgroundCommand::DalNibpBackgroundCommand():DalEM4HostToNibpCommand()
{
}

//DalNibpBackgroundCommand::DalNibpBackgroundCommand(array<unsigned char> ^ nibpPacket, unsigned int responseWaitTime):
//	DalEM4HostToNibpCommand(DalNibpCommandType::BackgroundCommand , nibpPacket, responseWaitTime)
//{
//	this->currentBackGroundState = DalNibpBackGroundCommandState::NotSent;
//}


bool DalNibpBackgroundCommand::ActOnPacket(array <unsigned char> ^ nibpToHostResponse)
{
	//check the length of the packet. It should not be 4
	if (4 != nibpToHostResponse[1]) 
	{
		//this is a background packet response
		
		//attach it to the current object
		this->nibpResponsePacket = nibpToHostResponse;
		//change the state
		this->currentBackGroundState = DalNibpBackGroundCommandState::ResponseRecieved;


		
		//take some action


		//then signal the waiting thread that it has something for it
		this->responseListenerThread->Interrupt();

		return true;
	}

	return false;
}

void DalNibpBackgroundCommand::ResponseListenerThreadMethod(System::Object ^)
{
	try
	{
		//TODO: see if this timout should be infinite
		//sleep until timeout expires or the thread is woken up
		Thread::Sleep(this->responseWaitingTimeMax); 

		//Thread::Sleep(this->responseWaitingTimeMax);
	}
	catch (ThreadAbortException^ )
	{
		//dont abort the thread
		Thread::ResetAbort();

	}
	catch(ThreadInterruptedException^ threadInterruptEx)
	{
		//this means that the data has arrived. 
		//We need to  process it or take some action

		delete threadInterruptEx;
		////CrxLogger::Instance->Write("Deepak>>> DalCommandInterface::ResponseListenerThreadMethod ThreadInterruptedException raised", ErrorSeverity::Debug);
	}


}

bool DalNibpBackgroundCommand::ProcessNibpResponse()
{
	//let child objects decide what they want to do with the result
	//we dont want to do anythin here
	return false;
}
