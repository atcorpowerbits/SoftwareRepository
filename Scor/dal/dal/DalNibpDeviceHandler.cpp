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
	/*if (CrxSytemParameters::Instance->GetStringTagValue("NibpDal.CuffPressureMeasurementThreadEnable") == "Y")
	{
	cuffPressurePlottingThread = gcnew Thread(gcnew ThreadStart(this, &DalNibpDeviceHandler::CuffPressurePlottingThreadMethod ));
	}*/
	signalNibpAbortCaller = gcnew SignalNibpAbortedAsyncCaller(this, &DalNibpDeviceHandler::SignalNibpAborted);

	obtainBpMeasurementAsynCaller =  gcnew ObtainBpMeasurementAsyncCaller(this, &DalNibpDeviceHandler::GetBpDataAndRaiseEvent);

	//nibpModuleConnected = false; //set to false so that we know for sure that the session has not started

	_instance = this;
}

bool DalNibpDeviceHandler::StartBpProcess(DalNIBPMode nibpMode, unsigned short initialPressure, bool initialInflate)
{

	bool boolRetValue;

	if (!nibpModuleConnected) 
	{
	//First connect to NibpModule
	boolRetValue = ConnectToNibpModule();

	if (!boolRetValue)
	{
		return false;
	}

		nibpModuleConnected = true; //set to tru so that for subsequent assesments we dont do it all over again

	if (initialInflate)
	{
		int waitTime = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.DalNibpIntialInflateCommandWaitTime");
		
		//since this has an initial pressure we must first set the initial value
		DalNibpIntialInflateCommand^ initialInflateCommand = gcnew DalNibpIntialInflateCommand(initialPressure, waitTime);
		boolRetValue = initialInflateCommand->SetInitialInflate();
	}
	if (!boolRetValue)
	{
		return false;
	}
	}

	//First check if the pressure is within an acceptible limit
	if (!IsCuffDeflated())
	{
		return false; 
	}

	int numberOfTries = 0;

	do
	{

		int sleepTimeBeforeStartBp = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.SendNibpConnectCommand.WaitTimeBetweenConnectAndStartBP");
		CrxLogger::Instance->Write("DalNibpDeviceHandler::StartBpProcess  Sleeping for " + sleepTimeBeforeStartBp + " ms before sending StartBP command " ,ErrorSeverity::Debug);

		//sleep for 7 seconds before trying becuase the NIBP module needs time to get ready

		//WaitTimeBetweenConnectAndStartBP: The time to wait after NIBP_CONNECT command has been sent and the Start_BP
		// command will be sent. Can be zero but usuall results in the command being NACKED
		Thread::Sleep(sleepTimeBeforeStartBp);

		//Thread::Sleep(7000); 
		//Dont create the object of a particular type
		//call the method which will return the specifc type
		//DalNibpStartBpCommand^ startBpCommand = gcnew DalNibpStartBpCommand(200000);

		if (startBpCommand)
		{
			delete startBpCommand;
		}

		startBpCommand = GetNewStartBpCommandObject(nibpMode);


	//Send the start BP command
	boolRetValue = startBpCommand->SendStartBpCommand();

		
		numberOfTries++; //increment the counter
	}
	while((numberOfTries <=2) && (!boolRetValue));

	//for testing and developemnt only
	////use without retries
	//startBpCommand = GetNewStartBpCommandObject(nibpMode);
	////Send the start BP command
	//boolRetValue = startBpCommand->SendStartBpCommand();

	if (!boolRetValue)
	{
		CrxLogger::Instance->Write("DalNibpDeviceHandler::StartBpProcess Failed to send the StartBp command. Deleting object", ErrorSeverity::Debug);
		
		//delete the startBpCommand Object
		delete startBpCommand;

		return false;
	}
	
	//if response was successful start the thread to put cuff pressure in Data buffer
	CreateDataBuffer();//create an array to transfer the data
	
	try
	{
		if (CrxSytemParameters::Instance->GetStringTagValue("NibpDal.CuffPressureMeasurementThreadEnable") == "Y")
		{
			
			if (!cuffPressurePlottingThread)
			{
				CrxLogger::Instance->Write("DalNibpDeviceHandler::StartBpProcess Starting cuff meaurement thread", ErrorSeverity::Debug);
	
				cuffPressurePlottingThread = gcnew Thread(gcnew ThreadStart(this, &DalNibpDeviceHandler::CuffPressurePlottingThreadMethod ));
		
			cuffPressurePlottingThread->Start();   //Start the cuff pressure plooting
		}
	}
	}
	catch(ThreadStateException^ exObj)
	{
		CrxLogger::Instance->Write("DalNibpDeviceHandler::StartBpProcess  cuff meaurement thread exception", ErrorSeverity::Debug);
		
		//Do not Suppress this exception
		throw exObj;
	}

	//set the marker that says that a measurement is in progress
	DalNibpEnvironmentVariables::bpMeasurementInProgress = true;



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
	CrxLogger::Instance->Write("DalNibpDeviceHandler::FinishBP started" , ErrorSeverity::Debug);
	//Send the AbortBP command

	bool boolRetValue;

	//Wait untill the cuff has deflated below the acceptable level.
	boolRetValue =  IsCuffDeflated();

	if (boolRetValue)
	{
		//Stop the cuff pressure measurement thread
		StopCuffPressurePlotting();

		//call disconnect
		SendNibpDisconnectCommand();
	}
	else
	{
		return false;
	}

	CrxLogger::Instance->Write("DalNibpDeviceHandler::FinishBP returning " + boolRetValue , ErrorSeverity::Debug);

	return boolRetValue;
}

bool DalNibpDeviceHandler::AbortBP()
{
	CrxLogger::Instance->Write("DalNibpDeviceHandler::AbortBP started" , ErrorSeverity::Debug);
	bool boolRetValue;

	int waitTime = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.DalNibpAbortBpCommandWaitTime");
	DalNibpAbortBpCommand ^ abortBpCommand = gcnew DalNibpAbortBpCommand(waitTime);
	boolRetValue =abortBpCommand->AbortBp();

	if (!boolRetValue)
	{
		CrxLogger::Instance->Write("DalNibpDeviceHandler::AbortBP Abort command Failed" , ErrorSeverity::Debug);
		//return false; Even if the command fails we still need to continue on and close the remaining processes
	}
	//else

	boolRetValue = FinishBP();

	CrxLogger::Instance->Write("DalNibpDeviceHandler::AbortBP returning " + boolRetValue , ErrorSeverity::Debug);


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
			//Thread::Sleep(1000); //this is user decided 
			Thread::Sleep(CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.SendNibpConnectCommand.BusyWaitPeriod")); //this is user decided 
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

		nibpModuleConnected = true; //set the flag to true

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
	DalReturnValue returnValue ;
		returnValue =  SendNibpConnectDisconnectCommand(false);

	if (DalReturnValue::Ack == returnValue )
	{
		//set the flag to false so that the next time we start with NIBP cycle we send connect command again.
		nibpModuleConnected = false; 
	}

	return returnValue;
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
						//CrxLogger::Instance->Write("DalNibpDeviceHandler::SendNibpConnectDisconnectCommand returing Ack", ErrorSeverity::Debug);

			//specifically return ack instead of Success so we can use it in a look
			return DalReturnValue::Ack;

		}
		else
		{
			CrxLogger::Instance->Write("DalNibpDeviceHandler::SendNibpConnectDisconnectCommand returing Nack", ErrorSeverity::Debug);

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
	CrxLogger::Instance->Write("DalNibpDeviceHandler::GetCuffPressure boolReturnValue: " + boolReturnValue.ToString() + " cuffPressure: " + cuffPressure, ErrorSeverity::Debug);

	return boolReturnValue;


}

//Deepak: no need to check using a sepearate thread. Use the existing cuff pressure measurement thread
//bool DalNibpDeviceHandler::CheckIfCuffHasDeflated()
//{
//
//	bool retValue;
//	unsigned int cuffPressureValue;
//
//	try{
//
//
//		do
//		{
//			cuffPressureValue = 0 ;//clear it
//			retValue = GetCuffPressure(cuffPressureValue);
//			//Get the cuff pressure. There is no need to stop it.
//			Thread::Sleep(200); //5 times per sec
//		}
//		while(cuffPressureValue > 15 && retValue);//once it is 14 we will stop
//
//		if (!retValue)
//		{
//			return false;
//		}
//	}
//	catch(ThreadInterruptedException^ threadEx)
//	{
//		delete threadEx;
//
//	}
//
//	return true;
//}

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
//			Thread::Sleep(200); //5 times per sec
			Thread::Sleep(CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.GetCuffPressureCommandRetryInterval")); //5 times per sec
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
	if (CrxSytemParameters::Instance->GetStringTagValue("NibpDal.CuffPressureMeasurementThreadEnable") == "Y")
	{
	this->cuffPressurePlottingThread->Abort();

		delete cuffPressurePlottingThread;
		cuffPressurePlottingThread = nullptr;
	}
}


bool DalNibpDeviceHandler::GetBpDataAndRaiseEvent()
{
	bool retValue;

	CrxLogger::Instance->Write("DalNibpDeviceHandler::GetBpDataAndRaiseEvent started",  ErrorSeverity::Debug);
	DalNibpGetBpDataCommand ^ getBpDataCommandObject = gcnew DalNibpGetBpDataCommand();

	retValue = getBpDataCommandObject->GetBpDataAndRaiseEvent();


	//Delete the original StartBPData command 
	//delete startBpCommand;
	CrxLogger::Instance->Write("DalNibpDeviceHandler::GetBpDataAndRaiseEvent returning" + retValue,  ErrorSeverity::Debug);
	return retValue;
}

DalNibpStartBpCommand^ DalNibpDeviceHandler::GetNewStartBpCommandObject(DalNIBPMode nibpMode)
{
	if (DalNIBPMode::Adult == nibpMode)
	{

		return gcnew DalNibpStartBpCommand();
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

void DalNibpDeviceHandler::SignalNibpAborted()
{
	try
	{
	//This method is called when an EM4 Abort signal is recieved.
	//We should check if there is a K response thread waiting for StartBP and

		//if (startBpCommand)
		//{

		//	//startBpCommand->kPacketListenerThread->Abort(); //object reference not found error

		//	//delete startBpCommand; //TODO: see if this works

		//	bool returnValue;

		//	//Now send a disconnect command
		//	returnValue = FinishBP();
		//}
		//else
		//{
		//	return ;
		//}

		AbortBP();
	}
	catch( Exception ^ excepObj)
	{
		throw gcnew ScorException(excepObj);
	}
}



bool DalNibpDeviceHandler::IsCuffDeflated()
{
	try{
		while(CurrentCuffPressure > 15 )//once it is 14 we will stop
	{
			
			//Get the cuff pressure. There is no need to stop it.
			//Thread::Sleep(200); //5 times per sec
			Thread::Sleep(CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.GetCuffPressureCommandRetryInterval")); //5 times per sec

		}

	}
	catch(ThreadInterruptedException^ threadEx)
	{
		delete threadEx;

	}

	return true;
}


void DalNibpDeviceHandler::AbortBpOnStopButtonPress()
{
	//DalNibpDeviceHandler::Instance->signalNibpAbortCaller->Invoke(); 
		//raise the necessary signal. Passing the data is irrelvant.
		DalNibpDeviceHandler::Instance->signalNibpAbortCaller->BeginInvoke(nullptr, nullptr); 

	//SignalNibpAborted();
	//AbortBP(); //TODO: 
}
