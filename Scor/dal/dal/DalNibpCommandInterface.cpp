/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpCommandInterface.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Source file for DalNibpCommandInterface class
*/

#include "stdafx.h"

#include "DalNibpCommandInterface.h"

using namespace AtCor::Scor::DataAccess;

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


