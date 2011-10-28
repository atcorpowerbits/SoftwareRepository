/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpDeviceHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Code file for DalNibpDeviceHandler class
*/

#include "stdafx.h"
#include "DalEventContainer.h"
#include "DalNibpDeviceHandler.h"
#include "DalEM4Command.h"
#include "DalNibpCommandInterface.h"
#include "DalNibpBackgroundCommand.h"
#include "DalSpecificBackgroundCommands.h"
#include "DalSpecificForegroundCommands.h" 


using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace System::Diagnostics; //for stopwatch

using namespace AtCor::Scor::DataAccess;

DalNibpDeviceHandler::DalNibpDeviceHandler()
{
	SetCommandInterface(gcnew DalNibpCommandInterface());
	cuffPressurePlottingThread = gcnew Thread(gcnew ThreadStart(this, &DalNibpDeviceHandler::CuffPressurePlottingThreadMethod ));
}

bool DalNibpDeviceHandler::StartBpProcess(DalNIBPMode nibpMode, unsigned short initialPressure, bool initialInfalte)
{

	bool boolRetValue;
	//First connect to NibpModule
	boolRetValue = ConnectToNibpModule();

	if (!boolRetValue)
	{
		return false;
	}

	CreateDataBuffer();//create an array to transfer the data
	//plotCuffPressurePoints = true; //tell the cuff thread that you want it to put data into the buffer
	cuffPressurePlottingThread->Start(); 

	
	//TODO: Testing with a 5 second delay before send ing the Set pressure command
	//Noticed that it works only in Debug mode
	//Thread::Sleep(500);

	if (initialInfalte)
	{
		
		//since this has an initial pressure we must first set the initial value
		DalNibpIntialInflateCommand^ initialInflateCommand = gcnew DalNibpIntialInflateCommand(initialPressure, 50);
		boolRetValue = initialInflateCommand->SetInitialInflate();
	}
	if (!boolRetValue)
	{
		return false;
	}

	int numberOfTries = 0;

	do
	{
		Thread::Sleep(7000); //sleep for 7 seconds before trying becuase the NIBP module needs time to get ready

		//Dont create the object of a particular type
		//call the method which will return the specifc type
		//DalNibpStartBpCommand^ startBpCommand = gcnew DalNibpStartBpCommand(200000);

		DalNibpStartBpCommand^ startBpCommand = GetNewStartBpCommandObject(nibpMode);


	//Send the start BP command
	boolRetValue = startBpCommand->SendStartBpCommand();

		
		numberOfTries++; //increment the counter
	}
	while((numberOfTries <=2) && (!boolRetValue));

	if (!boolRetValue)
	{
		return false;
	}
	
	//if resposne was successful start the thread to put cuff pressure in Data buffer
	//TODO: start the process



	return boolRetValue;



}

bool DalNibpDeviceHandler::StartBP(DalNIBPMode nibpMode, unsigned short initialPressure)
{
	CrxLogger::Instance->Write("DalNibpDeviceHandler::StartBpProcess 2 param called initialPressure" + initialPressure + " nibpMode: " + nibpMode.ToString(), ErrorSeverity::Debug);

	bool boolRetValue;

	//Call the private method with the right parameters
	//the called method should do an Initial Inflate
	boolRetValue = StartBpProcess(nibpMode, initialPressure, true);
	

	return boolRetValue;

}

bool DalNibpDeviceHandler::StartBP(DalNIBPMode nibpMode)
{
	CrxLogger::Instance->Write("DalNibpDeviceHandler::StartBpProcess 1 param called  nibpMode: " + nibpMode.ToString(), ErrorSeverity::Debug);
	
	bool boolRetValue;

	//Call the private method with the right parameters
	//No need for inital inflate: set flag to false and pressure to 0.
	boolRetValue = StartBpProcess(nibpMode, 0, false);


	return boolRetValue;
}

bool DalNibpDeviceHandler::FinishBP()
{
	//TODO: start the thread that will measure the pressure before sending the 

	//Send the AbortBP command

	bool boolRetValue;

	boolRetValue =  CheckIfCuffHasDeflated();
	if (boolRetValue)
	{
		//call disconnect
		SendNibpDisconnectCommand();
	}
	else
	{
		return false;
	}



	return boolRetValue;
}

bool DalNibpDeviceHandler::AbortBP()
{
	bool boolRetValue;

	DalNibpAbortBpCommand ^ abortBpCommand = gcnew DalNibpAbortBpCommand(200);
	boolRetValue =abortBpCommand->AbortBp();

	return boolRetValue;
}

bool DalNibpDeviceHandler::ConnectToNibpModule()
{
	long long maximumProcessTimeAllowed = 7500; //in miliseconds
	long long milisecondsExpired; //to measure the expired time after each check
	DalReturnValue returnValue = DalReturnValue::Failure; //default
	unsigned int tryNumber = 0;


	//first start the timer
	Stopwatch^ processStopwatch = Stopwatch::StartNew();

	//now start the loop
	do
	{
		if (0 != tryNumber)
		{
			Thread::Sleep(1000); //this is user decided //TODO
		}

		returnValue = SendNibpConnectCommand(); //send the command
		tryNumber++; //increment the try counter

		//check how much time has expired since the process started.
		milisecondsExpired = processStopwatch->ElapsedMilliseconds ;
		//CrxLogger::Instance->Write("DalNibpDeviceHandler::ConnectToNibpModule inside loop returnValue" +returnValue.ToString() + " milisecondsExpired" + milisecondsExpired, ErrorSeverity::Debug);


	}
	while((returnValue != DalReturnValue::Ack) && (milisecondsExpired<= maximumProcessTimeAllowed));

	if (DalReturnValue::Ack == returnValue )
	{
		CrxLogger::Instance->Write("DalNibpDeviceHandler::ConnectToNibpModule returing True", ErrorSeverity::Debug);

		return true;
	}
	
	CrxLogger::Instance->Write("DalNibpDeviceHandler::ConnectToNibpModule returing False", ErrorSeverity::Debug);

	return false; //default
}

DalReturnValue DalNibpDeviceHandler::SendNibpConnectCommand()
{

	return SendNibpConnectDisconnectCommand(true);
}

DalReturnValue DalNibpDeviceHandler::SendNibpDisconnectCommand()
{
		return SendNibpConnectDisconnectCommand(false);
}

DalReturnValue DalNibpDeviceHandler::SendNibpConnectDisconnectCommand(bool connect)
{
	DalReturnValue returnValue = DalReturnValue::Failure;
	array<unsigned char> ^commandData;

	if (connect)
	{
		commandData = gcnew array<unsigned char> (1) {0x00}; //0 for connect
	}
	else
	{
		commandData = gcnew array<unsigned char> (1) {0x01}; //1 for disconnect
	}

		
		
	DalEM4Command ^ nibpConnectCommand = gcnew DalEM4Command(Em4CommandCodes::NibpConnectDisconnect, commandData);
	nibpConnectCommand->expectedResponseLength =  5; //no data expected

	returnValue = _commandInterface->SendCommandAndGetResponse(nibpConnectCommand);

	if (DalReturnValue::Success == returnValue)
	{
		
		//if (nibpConnectCommand->em4ResponseAckNackByte == ((unsigned char)Em4CommandCodes::NibpConnectDisconnect & (unsigned char)DalAckNackByteMask::AckNackStatusBitMask))
		if ((unsigned char) DalAckNackByteMask::AckNackStatusBitMask == (nibpConnectCommand->em4ResponseAckNackByte & (unsigned char)DalAckNackByteMask::AckNackStatusBitMask))
		{
						CrxLogger::Instance->Write("DalNibpDeviceHandler::SendNibpConnectDisconnectCommand returing Ack", ErrorSeverity::Debug);

			//specifically return ack instead of Success so we can use it in a look
			return DalReturnValue::Ack;

		}
		else
		{
			CrxLogger::Instance->Write("DalNibpDeviceHandler::SendNibpConnectDisconnectCommand returing Ack", ErrorSeverity::Debug);

			return DalReturnValue::NoAck;
		}
	}
	return returnValue; //default
}


void DalNibpDeviceHandler::SetCommandInterface(DalCommandInterface^ interfaceObj)
{
	this->_commandInterface = interfaceObj;
}

//bool DalNibpDeviceHandler::GetCuffPressure()
//{
//	array<unsigned char>^ cuffPressureNibpCommand = gcnew array<unsigned char> {0x3A, 0x79, 0x05, 0x00, 0x48};
//	DalNibpBackgroundCommand^ getCuffPressureCommand = gcnew DalNibpBackgroundCommand(cuffPressureNibpCommand, 100);
//
//	DalReturnValue returnValue; 
//	returnValue = getCuffPressureCommand->SendCommandAndGetResponse();
//
//
//	if (DalReturnValue::Success != returnValue)
//	{
//		return false;
//	}
//	else
//	{
//		return true;
//	}
//}

bool DalNibpDeviceHandler::GetCuffPressure(unsigned int& cuffPressure)
{

	bool boolReturnValue;
	DalCuffPressureCommand^ cuffPressCommand = gcnew  DalCuffPressureCommand();

	boolReturnValue = cuffPressCommand->GetCuffPressure(cuffPressure);

	return boolReturnValue;


}

bool DalNibpDeviceHandler::CheckIfCuffHasDeflated()
{

	bool retValue;
	unsigned int cuffPressureValue;

	try{


		do
		{
			cuffPressureValue = 0 ;//clear it
			retValue = GetCuffPressure(cuffPressureValue);
			//Get the cuff pressure. There is no need to stop it.
			Thread::Sleep(200); //5 times per sec
		}
		while(cuffPressureValue > 15 && retValue);//once it is 14 we will stop

		if (!retValue)
		{
			return false;
		}
	}
	catch(ThreadInterruptedException^ threadEx)
	{
		delete threadEx;

	}

	return true;
}

bool  DalNibpDeviceHandler::CreateDataBuffer()
{
	dataBufferObj = DalDataBuffer::Instance;
	dataBufferObj->CreateBuffer(100, 100);

	return false;
}

void DalNibpDeviceHandler::CuffPressurePlottingThreadMethod()
{
	bool continueMeasurement = true;

	bool retValue;
	unsigned int cuffPressureValue;

	try{


		do
		{
			cuffPressureValue = 0 ;//clear it
			retValue = GetCuffPressure(cuffPressureValue);
			if (retValue)
			{
				//create new buffer object and insert it
				DalPwvDataStruct pwvDataObject ;

				pwvDataObject.cuffPressure = (unsigned short)cuffPressureValue;
				dataBufferObj->WriteDataToBuffer(pwvDataObject);
			}
			Thread::Sleep(200); //5 times per sec
		}
		while(continueMeasurement);
	}
	catch(ThreadInterruptedException^ threadEx)
	{
		delete threadEx;
		continueMeasurement = false;

	}



}

void DalNibpDeviceHandler::StopCuffPressurePlotting()
{
	this->cuffPressurePlottingThread->Abort();
}


bool DalNibpDeviceHandler::GetBpDataAndRaiseEvent()
{
	DalNibpGetBpDataCommand ^ getBpDataCommandObject = gcnew DalNibpGetBpDataCommand();

	getBpDataCommandObject->GetBpDataAndRaiseEvent();



	return true;
}

DalNibpStartBpCommand^ DalNibpDeviceHandler::GetNewStartBpCommandObject(DalNIBPMode nibpMode)
{
	if (DalNIBPMode::Adult == nibpMode)
	{

		return gcnew DalNibpStartBpCommand(140);
	}
	else if (DalNIBPMode::Neonate == nibpMode)
	{
		return gcnew DalNibpStartNeonateBpCommand();
	}
	else if (DalNIBPMode::Pediatric  == nibpMode)
	{
		return gcnew DalNibpStartPediatricBpCommand();
	}
	else
	{
		return nullptr; //default
	}


	
}

