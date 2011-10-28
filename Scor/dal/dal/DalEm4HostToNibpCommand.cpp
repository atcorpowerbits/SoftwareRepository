/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4HostToNibpCommand.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Code file for classes:  DalEM4HostToNibpCommand
*/

#include "stdafx.h"
#include "DalEM4HostToNibpCommand.h"


using namespace AtCor::Scor::DataAccess;


DalEM4HostToNibpCommand::DalEM4HostToNibpCommand()
{
	SetCommandInterface(DalNibpCommandInterface::Instance);
}


//DalEM4HostToNibpCommand::DalEM4HostToNibpCommand(DalNibpCommandType type, array<unsigned char> ^ nibpPacket, unsigned int responseWaitTime)
//{
//	//first set the interface
//	SetCommandInterface(DalNibpCommandInterface::Instance);
//
//	//copy the parameters
//	//this->commandType = type;
//	this->nibpCommandPacket = nibpPacket;
//	this->responseWaitingTimeMax = responseWaitTime;
//}

DalEM4HostToNibpCommand::~DalEM4HostToNibpCommand()
{
}

DalReturnValue DalEM4HostToNibpCommand::SendCommandAndGetResponse()
{

	bool returnValue;
	DalReturnValue dalRetValue;

	//send a command to the interace object
	returnValue = _commandInterface->SendCommandToNibpModule(this->nibpCommandPacket);
	Thread::Sleep(0);

	if (!returnValue)
	{
		return DalReturnValue::Failure;
	}

	//successfull now launch listener for the response
	dalRetValue = ListenForEM4Response();

	/*if ( DalReturnValue::Success == dalRetValue)
	{
	}*/



	return dalRetValue;
}

void DalEM4HostToNibpCommand::PacketArrivedProcessingMethod(Object^ , NibPacketArrivedEventArgs^ args)
{
	//first get the nibpPacket
	array <unsigned char> ^ nibpToHostResponse  = args->nibpPacket;
	
	//then interpret it 
	ActOnPacket(nibpToHostResponse);

}

bool DalEM4HostToNibpCommand::ActOnPacket(array <unsigned char> ^)
{

	//Unnecessary. Child classes will take appropriate action	
	////check the length of the packet
	//if (4 == nibpToHostResponse[1]) 
	//{
	//	//this is a foreground packet response
	//	if (DalNibpCommandType::ForeGroundCommand  == this->commandType  )
	//	{
	//		//take some action
	//	}
	//}
	//else
	//{

	//	//background packet response
	//	if (DalNibpCommandType::BackgroundCommand == this->commandType  )
	//	{
	//		//take some action
	//	}
	
	//}

	return false; //default
}

void DalEM4HostToNibpCommand::ResponseListenerThreadMethod(Object ^)
{
	//do nothing overriden methods will take care
}




DalReturnValue DalEM4HostToNibpCommand::ListenForEM4Response()
{
	//Start the thread that will process the events to arrive
	/*responseListenerThread = gcnew Thread(ParameterizedThreadStart(this, ResponseListenerThreadMethod));

		listenerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &DalCommandInterface::ResponseListenerThreadMethod));
*/


	//register the event handler to listen for async data arrived events
	//DalEventContainer::Instance->OnDalNibpPacketEvent += gcnew NibPPacketArrivedEventHandler(this, &DalEM4HostToNibpCommand::PacketArrivedProcessingMethod);

	return DalReturnValue::Failure;
}





bool DalEM4HostToNibpCommand::StopListeningForEM4response()
{

	DalEventContainer::Instance->OnDalNibpPacketEvent -= gcnew NibPPacketArrivedEventHandler(this, &DalEM4HostToNibpCommand::PacketArrivedProcessingMethod);


	return false;
}





void DalEM4HostToNibpCommand::SetCommandInterface(DalNibpCommandInterface^ newInterface)
{
	this->_commandInterface = newInterface;
}




















