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


using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace System::Diagnostics; //for stopwatch

using namespace AtCor::Scor::DataAccess;

DalNibpDeviceHandler::DalNibpDeviceHandler()
{
	SetCommandInterface(gcnew DalNibpCommandInterface());
}

bool DalNibpDeviceHandler::StartBP(DalNIBPMode nibpMode, unsigned short initialPressure)
{
	nibpMode;
	initialPressure;

	//TODO: code this

	return false; //temp
}

bool DalNibpDeviceHandler::StartBP(DalNIBPMode nibpMode)
{
	nibpMode;

	//TODO: code this

	return false; //temp
}

bool DalNibpDeviceHandler::FinishBP()
{
	//TODO: code this

	return false; //temp
}

bool DalNibpDeviceHandler::AbortBP()
{
	//TODO: code this

	return false; //temp
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

	}
	while((returnValue != DalReturnValue::Ack) && (milisecondsExpired<= maximumProcessTimeAllowed));

	if (DalReturnValue::Ack == returnValue )
	{
		return true;
	}
	
	return false; //default
}

DalReturnValue DalNibpDeviceHandler::SendNibpConnectCommand()
{
	DalReturnValue returnValue = DalReturnValue::Failure;
	array<unsigned char> ^commandData = gcnew array<unsigned char> (1) {0x00}; //0 for connect
	DalEM4Command ^ nibpConnectCommand = gcnew DalEM4Command(Em4CommandCodes::NibpConnectDisconnect, commandData);
	nibpConnectCommand->expectedResponseLength =  5; //no data expected

	returnValue = _commandInterface->SendCommandAndGetResponse(nibpConnectCommand);

	if (DalReturnValue::Success == returnValue)
	{
		
		//if (nibpConnectCommand->em4ResponseAckNackByte == ((unsigned char)Em4CommandCodes::NibpConnectDisconnect & (unsigned char)DalAckNackByteMask::AckNackStatusBitMask))
		if ((unsigned char) DalAckNackByteMask::AckNackStatusBitMask == (nibpConnectCommand->em4ResponseAckNackByte & (unsigned char)DalAckNackByteMask::AckNackStatusBitMask))
		{
			//specifically return ack instead of Success so we can use it in a look
			return DalReturnValue::Ack;
		}
		else
		{
			return DalReturnValue::NoAck;
		}
	}
	return returnValue; //default
}

void DalNibpDeviceHandler::SetCommandInterface(DalCommandInterface^ interfaceObj)
{
	this->_commandInterface = interfaceObj;
}

