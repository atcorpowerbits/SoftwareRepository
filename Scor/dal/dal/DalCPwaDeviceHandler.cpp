/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCPwaDeviceHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalCPwaDeviceHandler class code file
*/

#include "stdafx.h"
#include "DalCPwaDeviceHandler.h"
#include "DalCPwaCommandInterface.h"

using namespace AtCor::Scor::CrossCutting;

DalCPwaDeviceHandler::DalCPwaDeviceHandler()
{
	//set the command interface object
	_commandInterface = gcnew DalCPwaCommandInterface();
//	_nibpHandler = DalNibpDeviceHandler::Instance;
	_nibpHandler = gcnew DalNibpDeviceHandler();
}

bool DalCPwaDeviceHandler::StartCapture(int captureTime, int samplingRate)
{
	//CrxLogger::Instance->Write("DAL>>> DalCPwaDeviceHandler::StartCapture Called", ErrorSeverity::Debug);

	//create a buffer of the required size
	try
	{
		dataBufferObj = nullptr;
		dataBufferObj = DalDataBuffer::Instance;
		dataBufferObj->CreateBuffer(captureTime, samplingRate);
	}
	catch(ScorException^)
	{
		throw;
	}
	catch(Exception^ excepObj)
	{
		throw gcnew ScorException(excepObj);
	}

	//GUI checks if device is connected beofre calling this function . So no
	//need to do it again. This is as per Alistairs mail on4-5th August 20111

	//No need to check if tonometer is connected
	//The result will not be correct from EM4
					
	//Set Idle mode
	bool boolReturnValue;
	//boolReturnValue = SetIdleMode();
	boolReturnValue = SetIdleModeProcess(); //Replace direct call with function which will send the command in a loop with timeout

	if (false == boolReturnValue )
	{
		return false;
	}

	//TODO: As per Alistair's mail. We are supposed to use the PWV mode command itself to implement CPWA
	//option 0x02 should not be used for CPWA

	//now issue the command to start capture and see if the response was acknowledgement
	//Use the data for CPwa mode
	//array<unsigned char> ^commandData = gcnew array<unsigned char> (1) {Em4CommandCodes::CaptureCommandDataCPWAMode}; 
	
	array<unsigned char> ^commandData = gcnew array<unsigned char> (1) {Em4CommandCodes::CaptureCommandDataPWVMode }; 
	DalEM4Command ^ startCaptureCommand = gcnew DalEM4Command(Em4CommandCodes::StartDataCapture , commandData);
	startCaptureCommand->expectedResponseLength = Em4ResponseRequiredLength::StartDataCapture ;
	
	DalReturnValue returnValue = DalReturnValue::Failure;

	returnValue = _commandInterface->SendCommandAndGetResponse(startCaptureCommand); //renamed oringinal method
	
	//if acknowledged start the handler to listen to the data received.
	if (DalReturnValue::Success == returnValue )
	{
		//Reserve the successful capture commands sequence number durign streaming process
		DalSequenceNumberManager::ReserveCommandNumberDuringStreaming(startCaptureCommand->commandSequenceNumber);

		//start the handler for data capture here
		try
		{
			bool retValu;
			retValu =  _commandInterface->InitiateDataCaptureMode();

			return retValu;
		}
		catch(ScorException^)
		{
			throw;
		}
	}
	
	return false;
}

bool DalCPwaDeviceHandler::StartBP(DalNIBPMode nibpMode, unsigned short initialPressure)
{
	return _nibpHandler->StartBP(nibpMode, initialPressure);
}

bool DalCPwaDeviceHandler::StartBP(DalNIBPMode nibpMode) 
{
	return _nibpHandler->StartBP(nibpMode);
}

bool DalCPwaDeviceHandler::FinishBP()
{
	return _nibpHandler->FinishBP();
}

bool DalCPwaDeviceHandler::AbortBP()
{
	return _nibpHandler->AbortBP();
}