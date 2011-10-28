/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpCommandInterface.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Source file for DalNibpCommandInterface class
*/

#include "stdafx.h"

#include "DalNibpCommandInterface.h"
#include "DalEventContainer.h"


using namespace AtCor::Scor::DataAccess;

DalNibpCommandInterface::DalNibpCommandInterface()
{

	//NibPPacketArrivedEventHandler += gcnew NibPPacketArrivedEventHandler(PacketProcessingMethod);
	//DalEventContainer::Instance->OnDalNibpPacketEvent += gcnew NibPPacketArrivedEventHandler(PacketProcessingMethod);
	
}

bool DalNibpCommandInterface::SendCommandToNibpModule(array<unsigned char>^ nibpCommandByteArray)
{
	
	try
	{
		//insert it into the send NIBP Command
		DalEM4Command^ send_Nibp_command = gcnew DalEM4Command(0x14, nibpCommandByteArray); //14 for em4 COMMAND
		send_Nibp_command->expectedResponseLength = 9;
		

		//send it. //dont wait for response
		 DalActivePort::Instance->SendPacket(send_Nibp_command->em4Command);
	}
	catch(ScorException^)
	{
		return false;
	}
	catch(Exception^ )
	{
		return false;
	}

	return true; 
}

//void DalNibpCommandInterface::PacketProcessingMethod(Object^ source, NibPacketArrivedEventArgs^ args)
//{
//	
//	//first get the binary array 
//	array<unsigned char>^ rawEm4Packet = args->nibpPacket;
//	array<unsigned char>^ nibpSpecificData;
//
//	//convert it to an Em4 packet and validate it
//	
//	DalEM4NibpToHostPacket ^ nibpHostPacket = gcnew DalEM4NibpToHostPacket(rawEm4Packet);
//	DalReturnValue returnValue = nibpHostPacket->ValidatePacket();
//
//	if (DalReturnValue::Success != returnValue)
//	{
//		//todo: see if you need to throw an excpetion
//		return ;
//	} //else
//
//	nibpSpecificData = nibpHostPacket->em4ResponseData ;
//
//}



void DalNibpCommandInterface::ProcessNibpToHostPacket(array<unsigned char> ^ nibpToHostPacket)
{
	
	//first get the binary array 
	//array<unsigned char>^ rawEm4Packet = args->nibpPacket;
	array<unsigned char>^ nibpSpecificData;

	//convert it to an Em4 packet and validate it
	
	DalEM4NibpToHostPacket ^ nibpHostPacket = gcnew DalEM4NibpToHostPacket(nibpToHostPacket);
	DalReturnValue returnValue = nibpHostPacket->ValidatePacket();

	if (DalReturnValue::Success != returnValue)
	{
		//todo: see if you need to throw an excpetion
		return ;
	} //else

	nibpSpecificData = nibpHostPacket->em4ResponseData ;

	//Raise an event and let any interested party handle it
	DalEventContainer::Instance->OnDalNibpPacketEvent(nullptr, gcnew NibPacketArrivedEventArgs(nibpSpecificData));

}

DalNibpCommandInterface^ DalNibpCommandInterface::operator= (DalNibpCommandInterface^ )
{
	//overloaded assignment operator.
				//used to implement singleton.
				return this;
}


