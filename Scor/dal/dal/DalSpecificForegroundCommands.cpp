/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSpecificForegroundCommands.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     code file for all DalNibpForegroundCommand derived classes
*/

#include "stdafx.h"
#include "DalSpecificForegroundCommands.h"
#include "DalBinaryConversions.h"
#include "DalNibpDeviceHandler.h"

using namespace AtCor::Scor::DataAccess;

DalNibpIntialInflateCommand::DalNibpIntialInflateCommand(int initalInflatePressure, unsigned int responseWaitTime)
{
	this->initialPressure = initalInflatePressure;
	this->responseWaitingTimeMax = responseWaitTime;


	unsigned char pressureMSB, pressureLSB, checkSum;

	pressureLSB = (unsigned char)(this->initialPressure & 0x00FF);
	pressureMSB = ((unsigned char)((this->initialPressure & 0xFF00) >> 8));
	
	//create an array and insert the pressure values
	array<unsigned char> ^pressureBytes = gcnew array<unsigned char> (5) {0x3A, 0x17, pressureMSB, pressureLSB, 0x00};
	
	//now calculate the modulo-256 checksum
	checkSum = DalBinaryConversions::GenerateModulo256Checksum(pressureBytes, pressureBytes->Length -1);
	//set it to the last byte
	pressureBytes[pressureBytes->Length -1] = checkSum;

	this->nibpCommandPacket = pressureBytes;
}


bool DalNibpIntialInflateCommand::SetInitialInflate()
{
	DalReturnValue retValue;

	retValue = this->SendCommandAndGetResponse();

	if (DalReturnValue::Success == retValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DalNibpIntialInflateCommand::ProcessNibpResponse()
{

	//if this is O packet then wait for K packet
	if(DalNibpForegroundCommandState::RecievedO == this->currentForegroundState )
	{
		//relaunc the thread to listen for K response
		ListenForEM4Response();

		return true;
	}
	else if (DalNibpForegroundCommandState::RecievedK  == this->currentForegroundState )
	{
		//no need to wait any more
		StopListeningForEM4response();

		return true;

	}
	else if (DalNibpForegroundCommandState::RecievedA  == this->currentForegroundState )
	{
		StopListeningForEM4response();

		//return false;
		return false;
	}

	return false;//default

}



DalNibpStartBpCommand::DalNibpStartBpCommand():DalNibpForegroundCommand()
{

}

DalNibpStartBpCommand::DalNibpStartBpCommand(int responseWaitTime)
{

	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x20, 0xA6};
	this->responseWaitingTimeMax = 100; //this is for the first O response to arrive
	this->kPacketWaitTime = responseWaitTime; //time for the process to complete(K packet arrival)


}


bool DalNibpStartBpCommand::SendStartBpCommand()
{
	DalReturnValue retValue;

	retValue = this->SendCommandAndGetResponse();
	CrxLogger::Instance->Write("DalNibpStartBpCommand::SendStartBpCommand SendCommand returned " + retValue.ToString(), ErrorSeverity::Debug);

	if (DalReturnValue::Success == retValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DalNibpStartBpCommand::ProcessNibpResponse()
{
	CrxLogger::Instance->Write("DalNibpStartBpCommand::ProcessNibpResponse called. State= " + this->currentForegroundState.ToString(), ErrorSeverity::Debug);
	//if this is O packet then return true 
	//before that launch a seperate thread that will wait for the K packet
	if(DalNibpForegroundCommandState::RecievedO == this->currentForegroundState )
	{
		//relaunch another thread to listen for K response
		
		//StopListeningForEM4response();
		
		//create the thread
		kPacketListenerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &DalNibpStartBpCommand::ListenerForKPacketThreadMethod));

		//start the thread. We wont join it anywhere. 
		//If the K packet doesnt arrive we will let it wither
		kPacketListenerThread->Start();

		return true;
		
	}
	else if (DalNibpForegroundCommandState::RecievedK == this->currentForegroundState )
	{

		//signal the thread that is waiting for a K packet arrival.
		kPacketListenerThread->Interrupt();

		//no need to wait any more
		StopListeningForEM4response();

		return true;

	}
	else if (DalNibpForegroundCommandState::RecievedA  == this->currentForegroundState )
	{
		StopListeningForEM4response();

		//return false;
		return false;
	}

	return false;
}


void DalNibpStartBpCommand::ListenerForKPacketThreadMethod(System::Object ^)
{
	try
	{
		CrxLogger::Instance->Write("DalNibpStartBpCommand::ListenerForKPacketThreadMethod sleeping for signal", ErrorSeverity::Debug);
		
		//sleep for a longer period of timeuntil timeout expires or the thread is woken up
		Thread::Sleep(this->kPacketWaitTime ); 
	}
	catch(ThreadInterruptedException^ threadInterruptEx)
	{
		CrxLogger::Instance->Write("DalNibpStartBpCommand::ListenerForKPacketThreadMethod Interrupted", ErrorSeverity::Debug);
		
		//this will signify that the K packet  has arrived.

		delete threadInterruptEx;


		//call the method that will get the BP data
		DalNibpDeviceHandler::Instance->GetBpDataAndRaiseEvent();
		

		//DalEventContainer::Instance->OnDalNibpPacketEvent -= gcnew NibPPacketArrivedEventHandler(this, &DalNibpForegroundCommand::PacketArrivedProcessingMethod);

		delete kPacketListenerThread;
	}
	finally
	{
		//stop the cuffPloting thread
		DalNibpDeviceHandler::Instance->StopCuffPressurePlotting();

	
	}
	CrxLogger::Instance->Write("DalNibpStartBpCommand::ListenerForKPacketThreadMethod exiting", ErrorSeverity::Debug);
		
}

DalNibpAbortBpCommand::DalNibpAbortBpCommand()
{
}

DalNibpAbortBpCommand::DalNibpAbortBpCommand(int responseWaitTime)
{
	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x79, 0x01, 0x00, 0x4C};
	this->responseWaitingTimeMax = responseWaitTime;
}


bool DalNibpAbortBpCommand::AbortBp()
{
	DalReturnValue retValue;

	retValue = this->SendCommandAndGetResponse();

	if (DalReturnValue::Success == retValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DalNibpAbortBpCommand::ProcessNibpResponse()
{

	//Abort command will recieve A and then K
	if(DalNibpForegroundCommandState::RecievedA  == this->currentForegroundState )
	{
		//relaunc the thread to listen for K response
		ListenForEM4Response();

		return true;
	}
	else if (DalNibpForegroundCommandState::RecievedK  == this->currentForegroundState )
	{
		//no need to wait any more
		StopListeningForEM4response();

		return true;

	}

	return false;

}

DalNibpStartPediatricBpCommand::DalNibpStartPediatricBpCommand():DalNibpStartBpCommand()
{
	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x87, 0x3F}; //START_PEDS_BP
	this->responseWaitingTimeMax = 100; //this is for the first O response to arrive
	this->kPacketWaitTime = 100000; //time for the process to complete(K packet arrival) for neonate
}

DalNibpStartNeonateBpCommand::DalNibpStartNeonateBpCommand():DalNibpStartBpCommand()
{
	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x28, 0x9E}; //START_NEONATE_BP
	this->responseWaitingTimeMax = 100; //this is for the first O response to arrive
	this->kPacketWaitTime = 85; //time for the process to complete(K packet arrival) for neonate
}
