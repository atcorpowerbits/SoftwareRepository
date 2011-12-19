/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalPWVCommandInterface.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Code file for DalPwvCommandInterface class
*/
#pragma once

#include "stdafx.h"
#include "DalPwvCommandInterface.h"

#include "DalDeviceHandler.h"
#include "DalCommon.h"
#include "DalEventContainer.h"
#include "DalCaptureState.h"
#include "DalStagingQueue.h"
#include "DalSequenceNumberManager.h"
#include "DalResponsePacketBuffer.h"
#include "DalBinaryConversions.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;

//bool DalPwvCommandInterface::InitiateDataCaptureModeInternal()
//{
//	try
//	{
//		ResetAllStaticMembers();
//
//		//Reset the streaming seqence number validation
//		DalSequenceNumberManager::ResetStreamingSequenceNumber();
//	
//		//clear the streaming buffer before we start
//		DalStreamingPacketQueue::Instance->Clear();
//
//		//Inform the Staging que of the mode
//		//this has an impact on how it deals with unrecognized packets
//		DalStagingQueue::Instance->CaptureMode = true;
//
//		//TODO: change this method
//
//		//register and start the timer which will read the data
//		streamingPacketProcessingTimer = gcnew Timers::Timer(DalConstants::StreamingPacketReadInterval); 
//		streamingPacketProcessingTimer->Elapsed += gcnew ElapsedEventHandler(this, create new method and add here); 
//		streamingPacketProcessingTimer->Enabled = true;
//
//		//Initialize the timeout checker.
//		DalActivePort::Instance->StartStreamingTimeoutChecker();
//		
//	}
//	catch(Exception^ excepObj)
//	{
//		throw gcnew ScorException(excepObj);
//	}
//	return true;
//}

DalPwvCommandInterface::DalPwvCommandInterface()
{
	DalCommandInterface::SetInstanceObject(this);
}


bool DalPwvCommandInterface::ProcessSingleStreamingPacket(array<unsigned char> ^streamingPacket)
{
	CrxLogger::Instance->Write("DAL>>> DalPwvCommandInterface::ProcessSingleStreamingPacket called with parameter: " + DalBinaryConversions::ConvertBytesToString(streamingPacket)+ " End", ErrorSeverity::Debug);

	if (nullptr == streamingPacket)
	{
		//CrxLogger::Instance->Write("DAL>>> DalPwvCommandInterface::ProcessSingleStreamingPacket returning false" , ErrorSeverity::Debug);
		return false;
	}
	try
	{

		EM4DataCapturePacket^ capturePacket = gcnew EM4DataCapturePacket(DalConstants::PWVCaptureDataSize);
		DalPwvDataStruct pwvDataObject ;
		DalDataBuffer^ dataBufferObj = DalDataBuffer::Instance; //maybe we can move it out of the looper so that this will save one operation? TODO

		//copy the array to the capture packet
		capturePacket->em4Response = streamingPacket;

		//set the length to the size received from the port -1 9for CRC)
		capturePacket->em4ResponsePacketLength = streamingPacket->Length - 1;

		//breakup the byte array into the individual components
		 if (! capturePacket->BreakupEM4Response())
		 {
			// return false; //signal failure
			 throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCaptureInvalidPacketErrCd,CrxStructCommonResourceMsg::DalErrCaptureInvalidPacket, ErrorSeverity::Information);
		 }

		//validate the data.
		if (DalReturnValue::Success != ValidateResponsePacket(capturePacket))
		{
			//return false;// anyways we cannot catch the exception
			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCaptureInvalidPacketErrCd,CrxStructCommonResourceMsg::DalErrCaptureInvalidPacket, ErrorSeverity::Information);
		}

		//everything is fine now get the data. and write it to the variables
		pwvDataObject.tonometerData = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _tonometerDataIndex);
		pwvDataObject.cuffPulseData = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _cuffPulseDataIndex);
		pwvDataObject.cuffPressure  = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _cuffPressureDataIndex);
		pwvDataObject.countdownTimer = DalBinaryConversions::TranslateTwoBytes(capturePacket->em4ResponseData, _countdownTimerDataIndex);

		if(!dataBufferObj->WriteDataToBuffer(pwvDataObject))
		{
			//return false;
			////////CrxLogger::Instance->Write("DataCaptureMultiplePacketHandler>> write to buff failed ", ErrorSeverity::Debug);
			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferWriteFailedErrCd, CrxStructCommonResourceMsg::DalErrBufferWriteFailed, ErrorSeverity::Exception);
		}
		return true; //everything fine
	}
	catch(ScorException^ scorExObj)
	{
		//if we rethrow this exception , it will be unhandled. 
		//This is because this exception is raised in a 
		//method which has no caller and operates on its own thread.
		//THos causes the application to crash due to unhandled exception even though there is an exception handler in GUI.
		//So we are deleting this exception instead of rethrowing it.
		//To inform the upper layers, we are raising an OnDalModuleErrorAlarmEvent event.
		//This particular type (DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket) needs to be handled by
		//upper layers which need to decide what to do in this case.

		//Attempting to deregister the serial port DataRecieved event handler is useless because
		//serial port cannot be modified in a static method. 
		//we also tried calling Stop capture in GUI but that needs the method to be static.
		//It would result in  a lot of code refactoring.
		
		//CrxLogger::Instance->Write("DAL>>> DalCommandInterface::ProcessSingleStreamingPacket ScorException caught and deleted : " + scorExObj->ErrorMessageKey + " Raising ErrorAlarm Event for packet: " + DalBinaryConversions::ConvertBytesToString(streamingPacket) + " :End", ErrorSeverity::Debug);  
		delete scorExObj ;
		String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, DalFormatterStrings::PrintEnumName);
		DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName, DalBinaryConversions::ConvertAlarmType(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket));
		DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);
	}
	catch(Exception^ excepObj)
	{
		//see note above.
		//`CrxLogger::Instance->Write("DAL>>> DalCommandInterface::ProcessSingleStreamingPacket Exception caught and deleted : " + excepObj->StackTrace + ">>>"+ excepObj->Message + "Raising ErrorAlarm Event for packet: " + DalBinaryConversions::ConvertBytesToString(streamingPacket)+ " :End", ErrorSeverity::Debug);  
		
		delete excepObj;
		String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, DalFormatterStrings::PrintEnumName);
		DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket, sourceName, DalBinaryConversions::ConvertAlarmType(DalErrorAlarmStatusFlag::DataCaptureErrorInvalidPacket));
		DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);

	}

	return false;
}