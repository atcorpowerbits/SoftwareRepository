/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalPwvDeviceHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalPwvDeviceHandler class code file
*/


#include "stdafx.h"
#include "DalPwvDeviceHandler.h"
#include "DalPwvCommandInterface.h"

using namespace System::Threading;

using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;

DalPwvDeviceHandler::DalPwvDeviceHandler()
{
	//Create a new object to the specific command interface
	_commandInterface = gcnew DalPwvCommandInterface();
}



bool DalPwvDeviceHandler::StartCapture(int captureTime, int samplingRate)
{
	CrxLogger::Instance->Write("DAL>>> DalPwvDeviceHandler::StartCapture Called", ErrorSeverity::Debug);

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
					
	//Deepak: 12/Nov-2011 corrected the code for PWVSW-546
				//and spun it off into another function
	////Set Idle mode
	//bool boolReturnValue;

	////boolReturnValue = SetIdleMode();
	//int countRetry;
	//int count = 0;
	//int sleepTime = 3000;

	//sleepTime = Convert::ToInt32(CrxSytemParameters::Instance->GetStringTagValue("IdleModeSleepTime"));
	//countRetry = (15000/sleepTime) + 1;
	//Object^ obj;
	//do
	//{
	//	
	//	ScorException^ check = gcnew ScorException (1001, CrxStructCommonResourceMsg::Dal_DeviceIdling_Message, ErrorSeverity::Information);	
	//	CrxEventContainer::Instance->OnShowStatusEvent(obj, gcnew CrxShowStatusEventArgs(check));

	//	boolReturnValue = SetIdleMode();
	//	if(!boolReturnValue)
	//	{
	//		count++;
	//		Threading::Thread::Sleep(sleepTime); //Wait for 3 sec to re-check the idle mode
	//	}
	//}
	//while((!boolReturnValue) && (count < countRetry));

	//if (false == boolReturnValue )
	//{
	//	ScorException^ check = gcnew ScorException (1002, CrxStructCommonResourceMsg::Dal_DeviceNotReady_Message, ErrorSeverity::Information);	
	//	CrxEventContainer::Instance->OnShowStatusEvent(obj, gcnew CrxShowStatusEventArgs(check));

	//	return false;
	//}

	if(! SetIdleModeProcess())
	{
		//Failed to set IDLE mode within 15 sec.

		//capture cannot continue if IDLE mode was not set
		return false;
	}

	//now issue the command to start capture and see if the response was acknowledgement
	array<unsigned char> ^commandData = gcnew array<unsigned char> (1) {Em4CommandCodes::CaptureCommandDataPWVMode}; //Make this 0x03 into a dynamic thing
	DalEM4Command ^ startCaptureCommand = gcnew DalEM4Command(Em4CommandCodes::StartDataCapture , commandData);
	startCaptureCommand->expectedResponseLength = Em4ResponseRequiredLength::StartDataCapture ;
	
	DalReturnValue returnValue = DalReturnValue::Failure;

	returnValue = _commandInterface->SendCommandAndGetResponse(startCaptureCommand); //renamed oringinal method
	
	CrxLogger::Instance->Write("DAL>>> DalPwvDeviceHandler::StartCapture command sent and returned: " + returnValue.ToString(), ErrorSeverity::Debug);

	
	//if acknowledged start the handler to listen to the data received.
	if (DalReturnValue::Success == returnValue )
	{
		//Reserve the successful capture commands sequence number durign streaming process
		DalSequenceNumberManager::ReserveCommandNumberDuringStreaming(startCaptureCommand->commandSequenceNumber);

		//start the handler for data capture here
		try
		{
			bool returnValue;
			returnValue =  _commandInterface->InitiateDataCaptureMode();
			CrxLogger::Instance->Write("DAL>>> DalPwvDeviceHandler::StartCapture InitiateDataCaptureMode() returned: " + returnValue.ToString(), ErrorSeverity::Debug);

			return returnValue;
		}
		catch(ScorException^)
		{
			throw;
		}
	}
	
	return false;
}