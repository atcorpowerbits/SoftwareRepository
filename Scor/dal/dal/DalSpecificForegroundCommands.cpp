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
using namespace AtCor::Scor::CrossCutting::Configuration;

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

DalReturnValue DalNibpIntialInflateCommand::ProcessNibpResponse()
{

	//if this is O packet then wait for K packet
	if(DalNibpForegroundCommandState::RecievedO == this->currentForegroundState )
	{
		//relaunc the thread to listen for K response
		ListenForEM4Response();

		//return true;
		return DalReturnValue::Success;
	}
	else if (DalNibpForegroundCommandState::RecievedK  == this->currentForegroundState )
	{
		//no need to wait any more
		StopListeningForEM4response();

		//return true;
		return DalReturnValue::Success;
	}
	else if (DalNibpForegroundCommandState::RecievedA  == this->currentForegroundState )
	{
		StopListeningForEM4response();

		//return false;
		return DalReturnValue::Failure ;
	}

	//return false;//default
	return DalReturnValue::Failure;

}



DalNibpStartBpCommand::DalNibpStartBpCommand():DalNibpForegroundCommand()
{
	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x20, 0xA6};
	//this->responseWaitingTimeMax = 1000;//this is for the first O response to arrive
	this->responseWaitingTimeMax = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.StartBP.WatitForO");//this is for the first O response to arrive
	
	//this->kPacketWaitTime = 140*1000; //time for the process to complete(K packet arrival)
	this->kPacketWaitTime = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.StartBP.WatitForK"); //time for the process to complete(K packet arrival)

}

//FxCop
//DalNibpStartBpCommand::DalNibpStartBpCommand(int responseWaitTime)
//{
//
//	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x20, 0xA6};
//	//this->responseWaitingTimeMax = 1000;//this is for the first O response to arrive
//	this->responseWaitingTimeMax = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.StartBP.WatitForO");//this is for the first O response to arrive
//	
//	this->kPacketWaitTime = responseWaitTime; //time for the process to complete(K packet arrival)
//
//
//}


bool DalNibpStartBpCommand::SendStartBpCommand()
{
	DalReturnValue retValue;
	int numberOfRetries = 0;

	//Send the command. IF the response is Busy we have to retry 5 times

	do
	{
	retValue = this->SendCommandAndGetResponse();
	CrxLogger::Instance->Write("DalNibpStartBpCommand::SendStartBpCommand SendCommand returned " + retValue.ToString(), ErrorSeverity::Debug);

		numberOfRetries++;

		//wait for 1 second and then retry
		Thread::Sleep(1000);


	}
	while(( DalReturnValue::Busy == retValue)  && (numberOfRetries <= 6));

	
	if (DalReturnValue::Success == retValue)
	{
		return true;
	}
	else
	{
		return false;
	}
}

DalReturnValue DalNibpStartBpCommand::ProcessNibpResponse()
{
	CrxLogger::Instance->Write("DalNibpStartBpCommand::ProcessNibpResponse called. State= " + this->currentForegroundState.ToString(), ErrorSeverity::Debug);
	//if this is O packet then return true 
	//before that launch a seperate thread that will wait for the K packet
	if(DalNibpForegroundCommandState::RecievedO == this->currentForegroundState )
	{
		//relaunch another thread to listen for K response
		if(responseListenerThread)
		{
			//CrxLogger::Instance->Write("DalNibpStartBpCommand::ProcessNibpResponse  deleting older thread and creating new one on recieving O packet", ErrorSeverity::Debug);
			delete responseListenerThread;
		}
		
		//create the thread
			this->responseListenerThread = gcnew Thread(gcnew ParameterizedThreadStart(this, &DalNibpStartBpCommand::ListenerForKPacketThreadMethod));

		////start the thread. We wont join it anywhere. 
		////If the K packet doesnt arrive we will let it wither
			this->responseListenerThread ->Start();

		//return true;
		return DalReturnValue::Success;
		
	}
	else if (DalNibpForegroundCommandState::RecievedK == this->currentForegroundState )
	{

		//signal the thread that is waiting for a K packet arrival.
		this->responseListenerThread ->Interrupt();

		//no need to wait any more
		StopListeningForEM4response();

		//return true;
		return DalReturnValue::Failure;

	}
	else if (DalNibpForegroundCommandState::RecievedA  == this->currentForegroundState )
	{
		StopListeningForEM4response();

		//return false;
		return DalReturnValue::Failure;
	}
	else if (DalNibpForegroundCommandState::Busy   == this->currentForegroundState )
	{

		//EM4 is busy need to retry after 1 second
		
		return DalReturnValue::Busy;
	}

	//return false;
	return DalReturnValue::Failure;
}


void DalNibpStartBpCommand::ListenerForKPacketThreadMethod(System::Object ^)
{
	try
	{
		//CrxLogger::Instance->Write("DalNibpStartBpCommand::ListenerForKPacketThreadMethod sleeping for signal with wait time: "+ this->kPacketWaitTime , ErrorSeverity::Debug);
		
		//sleep for a longer period of timeuntil timeout expires or the thread is woken up
		Thread::Sleep(this->kPacketWaitTime ); 

		//NIBP Case 5: Host and NIBP module sychronization.
		//If we reach here it means that we waited for the designated K Packet waiting time...
		//but no response whatsoever came 
		//In this case we still have to try and get the BP data. 
		//If (BPS = New ) it means we have a valid measurement
		CrxLogger::Instance->Write("DalNibpStartBpCommand::ListenerForKPacketThreadMethod timeed out without recieving K signal. Attempting to get BP data." , ErrorSeverity::Debug);

	}
	catch(ThreadInterruptedException^ threadInterruptEx)
	{
		CrxLogger::Instance->Write("DalNibpStartBpCommand::ListenerForKPacketThreadMethod Interrupted" + threadInterruptEx->StackTrace, ErrorSeverity::Debug);
		
		//this will signify that the K packet  has arrived.

		delete threadInterruptEx;

		//DeepaK: moved to {finally} block. See reason above
		////call the method that will get the BP data
		//DalNibpDeviceHandler::Instance->GetBpDataAndRaiseEvent();
		

		//DalEventContainer::Instance->OnDalNibpPacketEvent -= gcnew NibPPacketArrivedEventHandler(this, &DalNibpForegroundCommand::PacketArrivedProcessingMethod);

		
	}
	catch(ThreadAbortException ^ abortEx)
	{
		abortEx;
		CrxLogger::Instance->Write("DalNibpStartBpCommand::ListenerForKPacketThreadMethod Aborted!", ErrorSeverity::Debug);
	}
	finally
	{
		//Regardless of whether we get a K packet or a timout occurs while waiting for a K packet
		//We must try to get the BP data (as per Case 5)
		//So we will do it in finally block.

		//call the method that will get the BP data
		DalNibpDeviceHandler::Instance->GetBpDataAndRaiseEvent();
	
	}
	delete kPacketListenerThread;
	CrxLogger::Instance->Write("DalNibpStartBpCommand::ListenerForKPacketThreadMethod exiting", ErrorSeverity::Debug);
	delete this; //Deepak: attempting to delete the object. Lets see if this works
		
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

DalReturnValue DalNibpAbortBpCommand::ProcessNibpResponse()
{

	//Abort command will recieve A and then K
	if(DalNibpForegroundCommandState::RecievedA  == this->currentForegroundState )
	{
		if (true == DalNibpEnvironmentVariables::bpMeasurementInProgress)
		{
			DalNibpEnvironmentVariables::bpMeasurementInProgress = false;

			//Launch the thread to listen for K response
		ListenForEM4Response();

		}
		else
		{
			StopListeningForEM4response();
			//no need to wait for a K in case there was no measurement in progress
		}

		//return true;
		return DalReturnValue::Success ; //in either case return true to tell that the response was processed
	}
	else if (DalNibpForegroundCommandState::RecievedK  == this->currentForegroundState )
	{
		//no need to wait any more
		StopListeningForEM4response();

		//return true;
		return  DalReturnValue::Success;

	}

	//return false;
	return DalReturnValue::Failure;

}

DalNibpStartPediatricBpCommand::DalNibpStartPediatricBpCommand():DalNibpStartBpCommand()
{
	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x87, 0x3F}; //START_PEDS_BP
	//this->responseWaitingTimeMax = 100; //this is for the first O response to arrive
	this->responseWaitingTimeMax = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.StartBP.WatitForO"); //this is for the first O response to arrive
	
	//this->kPacketWaitTime = 100* 1000; //time for the process to complete(K packet arrival) for neonate
	this->kPacketWaitTime = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.StartBP.StartPediatricBpWaitForK"); //time for the process to complete(K packet arrival) for neonate
}

DalNibpStartNeonateBpCommand::DalNibpStartNeonateBpCommand():DalNibpStartBpCommand()
{
	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x28, 0x9E}; //START_NEONATE_BP
	//this->responseWaitingTimeMax = 100; //this is for the first O response to arrive
	this->responseWaitingTimeMax = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.StartBP.WatitForO"); //this is for the first O response to arrive
	
	//this->kPacketWaitTime = 85* 1000; //time for the process to complete(K packet arrival) for neonate
	this->kPacketWaitTime = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.StartBP.StartNeonateBpWaitForK"); //time for the process to complete(K packet arrival) for neonate
}
