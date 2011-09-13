/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalPwvDeviceHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalPwvDeviceHandler class code file
*/


#include "stdafx.h"
#include "DalPwvDeviceHandler.h"
#include "DalPwvCommandInterface.h"

using namespace AtCor::Scor::CrossCutting;

DalPwvDeviceHandler::DalPwvDeviceHandler()
{
	//Create a new object to the specific command interface
	_commandInterface = gcnew DalPwvCommandInterface();
}



bool DalPwvDeviceHandler::StartCapture(int captureTime, int samplingRate)
{
	//CrxLogger::Instance->Write("Deepak>>> DalPwvDeviceHandler::StartCapture Called");

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
	boolReturnValue = SetIdleMode();
	if (false == boolReturnValue )
	{
		return false;
	}

	//now issue the command to start capture and see if the response was acknowledgement
	array<unsigned char> ^commandData = gcnew array<unsigned char> (1) {Em4CommandCodes::CaptureCommandDataPWVMode}; //Make this 0x03 into a dynamic thing
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
			return _commandInterface->InitiateDataCaptureMode();
		}
		catch(ScorException^)
		{
			throw;
		}
	}
	
	return false;
}