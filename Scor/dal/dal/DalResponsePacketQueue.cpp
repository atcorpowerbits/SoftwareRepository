/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalResponsePacketQueue.cpp

     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalResponsePacketQueue class.
*/

#include "stdafx.h"
#include "DalResponsePacketQueue.h"
#include "DalStatusHandler.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting::Logging;

DalResponsePacketQueue::DalResponsePacketQueue()
{
	waitingResponse = nullptr;
}

DalResponsePacketQueue::~DalResponsePacketQueue()
{
	this->Clear();
	delete this->_mutex;
}

DalResponsePacketQueue::DalResponsePacketQueue(DalResponsePacketQueue^)
{
	//Do nothing
}

DalResponsePacketQueue^ DalResponsePacketQueue::operator =(DalResponsePacketQueue ^)
{
	return this;
}

DalResponsePacketQueue^ DalResponsePacketQueue::Instance::get()
{
	return _instance;
}



array<unsigned char> ^ DalResponsePacketQueue::Dequeue()
{
	array< unsigned char>^ returnValue; 
	_mutex->WaitOne();
	//Set the current response
	returnValue =  this->waitingResponse;

	//clear the response pointer
	//Do not delete the array
	waitingResponse = nullptr;

	_mutex->ReleaseMutex();

	//now return
	return returnValue;
}

void DalResponsePacketQueue::Enqueue(array<unsigned char> ^packet)
{
	_mutex->WaitOne();

	//TODO : This code is for printing the response only //please delete after testing
	if (waitingResponse)
	{
		//CrxLogger::Instance->Write("Deepak>>> DalResponsePacketQueue::Enqueue deleting the existing resposne: " + AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(waitingResponse));
		delete waitingResponse;
	}

	//CrxLogger::Instance->Write("Deepak>>> DalResponsePacketQueue::Enqueue Adding new packet: " + AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(packet));
	//now write the new response packet
	waitingResponse = packet;
	
	_mutex->ReleaseMutex();
}

void DalResponsePacketQueue::Clear()
{
	_mutex->WaitOne();

	delete waitingResponse;
	waitingResponse = nullptr;

	_mutex->ReleaseMutex();
}


