/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalStreamingPacketQueue.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalStreamingPacketQueue class
*/

#include "stdafx.h"
#include "DalStreamingPacketQueue.h"
#include "DalStatusHandler.h" //TODO: remove

using namespace AtCor::Scor::DataAccess;

using namespace AtCor::Scor::CrossCutting::Logging;

DalStreamingPacketQueue::DalStreamingPacketQueue()
{
	this->streamingPacketQueue = gcnew Queue<array<unsigned char>^>();
}

DalStreamingPacketQueue::~DalStreamingPacketQueue()
{
	this->Clear();
	delete this->streamingPacketQueue;
	this->streamingPacketQueue = nullptr;

	//release the mutex in case it is held
	_mutex->ReleaseMutex();
	delete this->_mutex;
}

DalStreamingPacketQueue::DalStreamingPacketQueue(DalStreamingPacketQueue^)
{
	//Do nothing
}

DalStreamingPacketQueue^ DalStreamingPacketQueue::operator =(DalStreamingPacketQueue^)
{
	return this;
}

DalStreamingPacketQueue^ DalStreamingPacketQueue::Instance::get()
{
	return _instance;
}

array<unsigned char>^ DalStreamingPacketQueue::Dequeue()
{
	array<unsigned char>^ returnValue;
	
	_mutex->WaitOne();
	
	if (this->streamingPacketQueue->Count != 0)
	{
		returnValue=  this->streamingPacketQueue->Dequeue();
		//CrxLogger::Instance->Write("Deepak>>> DalStreamingPacketQueue::Dequeue Total : "+ this->streamingPacketQueue->Count + " Dequeued " + AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(returnValue) );
		CrxLogger::Instance->Write("Deepak>>> DalStreamingPacketQueue::Dequeue Total : "+ this->streamingPacketQueue->Count );
	}
	else
	{
		returnValue = nullptr; 
		//CrxLogger::Instance->Write("Deepak>>> DalStreamingPacketQueue::Dequeue Total : "+ this->streamingPacketQueue->Count + " UNDERFLOW" );
	}
	
	_mutex->ReleaseMutex();

	return returnValue;
}

void DalStreamingPacketQueue::Enqueue(array<unsigned char> ^packet)
{
	_mutex->WaitOne();

	this->streamingPacketQueue->Enqueue(packet);
	//CrxLogger::Instance->Write("Deepak>>> DalStreamingPacketQueue::Enqueue Total : "+ this->streamingPacketQueue->Count + " Added new packet: " + AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(packet) );
	CrxLogger::Instance->Write("Deepak>>> DalStreamingPacketQueue::Enqueue Total : "+ this->streamingPacketQueue->Count );
	
	
	_mutex->ReleaseMutex();
}

void DalStreamingPacketQueue::Clear()
{
	_mutex->WaitOne();

	this->streamingPacketQueue->Clear();
	
	_mutex->ReleaseMutex();

}

int DalStreamingPacketQueue::Count()
{
	return this->streamingPacketQueue->Count;
}