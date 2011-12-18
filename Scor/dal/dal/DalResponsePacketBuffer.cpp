/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalResponsePacketBuffer.cpp

     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalResponsePacketBuffer class.
*/

#include "stdafx.h"
#include "DalResponsePacketBuffer.h"
#include "DalCommandInterface.h"
#include "DalBinaryConversions.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting::Logging;

DalResponsePacketBuffer::DalResponsePacketBuffer()
{
	waitingResponse = nullptr;
}

DalResponsePacketBuffer::~DalResponsePacketBuffer()
{
	this->Clear();
//	_mutex->ReleaseMutex();
//	delete this->_mutex;
}

DalResponsePacketBuffer::DalResponsePacketBuffer(DalResponsePacketBuffer^)
{
	//Do nothing
}

DalResponsePacketBuffer^ DalResponsePacketBuffer::operator =(DalResponsePacketBuffer ^)
{
	return this;
}


DalResponsePacketBuffer^ DalResponsePacketBuffer::Instance::get()
{
	return _instance;
}



array<unsigned char> ^ DalResponsePacketBuffer::Dequeue()
{
	//CrxLogger::Instance->Write("Deepak>>> DalResponsePacketBuffer::Dequeue Start ", ErrorSeverity::Debug);
	
	array< unsigned char>^ returnValue; 
//	_mutex->WaitOne();
	//Set the current response
	returnValue =  this->waitingResponse;
	if(nullptr!= returnValue)
	{
		//CrxLogger::Instance->Write("Deepak>>> DalResponsePacketBuffer::Dequeue Start " + DalBinaryConversions::ConvertBytesToString(returnValue), ErrorSeverity::Debug);
	}
	else
	{
		//CrxLogger::Instance->Write("Deepak>>> DalResponsePacketBuffer::Dequeue NULL PACKET RETURNED", ErrorSeverity::Debug);

	}
	

	//clear the response pointer
	//Do not delete the array
	waitingResponse = nullptr;

//	_mutex->ReleaseMutex();

	//now return
	return returnValue;
}

void DalResponsePacketBuffer::Enqueue(array<unsigned char> ^packet)
{
	try
	{

//	_mutex->WaitOne();

	//TODO : This code is for printing the response only //please delete after testing
	if (waitingResponse)
	{
		//CrxLogger::Instance->Write("Deepak>>> DalResponsePacketBuffer::Enqueue deleting the existing resposne: " + DalBinaryConversions::ConvertBytesToString(waitingResponse), ErrorSeverity::Debug);
		delete waitingResponse;
	}

	//CrxLogger::Instance->Write("Deepak>>> DalResponsePacketBuffer::Enqueue Adding new packet: " + DalBinaryConversions::ConvertBytesToString(packet), ErrorSeverity::Debug);
	//now write the new response packet
	waitingResponse = packet;
	
//		_mutex->ReleaseMutex();

	//signal the lstener that the data is available
	DalCommandInterface::Instance->SignalResponsePacketAvailable();
	}
	catch(Exception^ )
	{
		throw;
	}
}

void DalResponsePacketBuffer::Clear()
{
//	_mutex->WaitOne();

	delete waitingResponse;
	waitingResponse = nullptr;

//	_mutex->ReleaseMutex();
}


