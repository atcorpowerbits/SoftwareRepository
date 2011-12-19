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
	CrxLogger::Instance->Write("DalEM4HostToNibpCommand::~DalEM4HostToNibpCommand called for object" + this->GetType() + " Hash Code: " + this->GetHashCode(), ErrorSeverity::Debug);
	responseListenerThread->Abort();
	delete responseListenerThread;
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

	//CrxLogger::Instance->Write("DalEM4HostToNibpCommand::SendCommandAndGetResponse calling ListenForEM4Response()" , ErrorSeverity::Debug );
	//successfull now launch listener for the response
	dalRetValue = ListenForEM4Response();

	/*if ( DalReturnValue::Success == dalRetValue)
	{
	}*/



	return dalRetValue;
}

void DalEM4HostToNibpCommand::PacketArrivedProcessingMethod(Object^ , NibPacketArrivedEventArgs^ args)
{

	try
	{
	if (args->Handled)
	{
		//This response has been handled by some other object so ignore it.
		return;
	}

	//first get the nibpPacket
	array <unsigned char> ^ nibpToHostResponse  = args->nibpPacket;
	
	bool retValue;
	
	//then interpret it 
	retValue = ActOnPacket(nibpToHostResponse);
	
	if (retValue)
	{
		//if packet has been acted on then we should set this to true so that it is not handled again
		args->Handled = true;
	}
	}
	catch( ThreadInterruptedException ^ threadInterruptEx)
	{
		delete threadInterruptEx;

	}

}

bool DalEM4HostToNibpCommand::ActOnPacket(array <unsigned char> ^)
{

	//Unnecessary. Child classes will take appropriate action	
	

	return false; //default
}

void DalEM4HostToNibpCommand::ResponseListenerThreadMethod(Object ^)
{
	//do nothing overriden methods will take care
}




DalReturnValue DalEM4HostToNibpCommand::ListenForEM4Response()
{

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




















