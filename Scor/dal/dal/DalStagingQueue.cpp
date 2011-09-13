/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalStagingQueue.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Source file for DalStagingQue class
*/

#include "stdafx.h"

#include "DalStagingQueue.h"
#include "DalResponsePacketBuffer.h"
#include "DalStreamingPacketQueue.h"
#include "DalActivePort.h"
#include "DalBinaryConversions.h"
#include "DalStatusHandler.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;


DalStagingQueue::DalStagingQueue()
{
	this->stagingQueue = gcnew  List<unsigned char> ;
	_nackPacketStandardLength = DalConstants::EM4ZeroDataResponsePacketSize + DalConstants::EM4NackPacketDataLength ;
	//TODO: _streamingPacketSize  should change based on PWV/PWA mode
	_streamingPacketSize = DalConstants::PWVCaptureDataSize + DalConstants::EM4ZeroDataResponsePacketSize;

	//_processQueueAsyncCaller = gcnew ProcessQueueAsyncCaller(this, &DalStagingQueue::ProcessQueue);

	this->dataProcessingThread = gcnew Thread(gcnew ThreadStart(this, &DalStagingQueue::ProcessingThreadMethod));

	this->dataProcessingThread->Start();

	//_attemptUnderFlowReadCaller = gcnew AttemptUnderFlowReadCaller(DalActivePort::Instance, &DalActivePort::ReadDataFromPort);
}

DalStagingQueue^ DalStagingQueue::operator= (DalStagingQueue^)
{
	return this;
}

DalPacketType DalStagingQueue::DeterminePacketType(unsigned char commandCodeByte)
{
	if ((unsigned char)DalAckNackByteMask::DataCaptureCodeAckedByte == commandCodeByte)
	{
		//this is a streaming packet
		return DalPacketType::StreamingDataPacket ;
	}
	else
	{
		//check if a command is being looked for
		if (true == checkForCommand)
		{
			//YES: validate for command ACK or NACK

			//First check if the command byte is the same
			if (commandCodeToLocate == ( commandCodeByte & (unsigned char)DalAckNackByteMask::CommandCodeBitsMask  ))
			{
				//the command byte is validated againt the desired command
				//now find the type is ACK or NACK

				if ( (unsigned char) DalAckNackByteMask::AckNackStatusBitMask == ( commandCodeByte & (unsigned char) DalAckNackByteMask::AckNackStatusBitMask)) 
				{
					return DalPacketType::AckedResponsePakcet;
				}
				else
				{
					return DalPacketType::NackedResponsePacket;
				}
			}
		}
	}

	return DalPacketType::Unknown;
}

array <unsigned char>^  DalStagingQueue::ExtractAckedResponsePakcet()
{
	//this is dependant on the checkFlag 
	//Assuming that this method will only be called after the flag is set
	//////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ExtractAckedResponsePakcet Start");

	array<unsigned char>^ tempArray = nullptr;

	tempArray = DequeueArray(expectedResponseLengthToLocate + 1) ; //1 for CRC

	
	if (nullptr!= tempArray)
	{
//		//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ExtractAckedResponsePakcet AckedResponsePacket:  " +  AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(tempArray));
	
		this->checkForCommand = false; //make a note that the command has been sent to the handler

		//call the method which will upload it to the required array
		DalResponsePacketBuffer::Instance->Enqueue(tempArray);
	}
	return tempArray;
}

array <unsigned char>^ DalStagingQueue::ExtractNackedResponsePacket()
{
	//////CrxLogger::Instance->Write("Deepak>>>  DalStagingQueue::ExtractNackedResponsePacket Start");
	array<unsigned char>^ tempArray;

	tempArray = DequeueArray(_nackPacketStandardLength + 1) ; //1 for CRC
	
	
	if (nullptr!= tempArray)
	{
//		//CrxLogger::Instance->Write("Deepak>>>  DalStagingQueue::ExtractNackedResponsePacket Nacked Response Packet:  " +  AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(tempArray));
	

		this->checkForCommand = false; //make a note that the command has been sent to the handler

		//call the method which will upload it to the required array
		DalResponsePacketBuffer::Instance->Enqueue(tempArray);
	}
	return tempArray;
}

array <unsigned char>^ DalStagingQueue::ExtractStreamingDataPacket()
{
//	//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ExtractStreamingDataPacket  Start");
	array<unsigned char>^ tempArray = nullptr;

	tempArray = DequeueArray(_streamingPacketSize + 1) ; //1 for CRC

	if (nullptr!= tempArray)
	{

//		//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ExtractStreamingDataPacket StreamingPacket:  " +  AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(tempArray));

		DalStreamingPacketQueue::Instance->Enqueue(tempArray);
	}

	return tempArray;
}

void DalStagingQueue::LookForResponseToCommand(
												unsigned char commandCodeToLocate, 
												unsigned char expectedResponseLengthToLocate, 
												unsigned char 
												)
{
	//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::LookForResponseToCommand:  " + commandCodeToLocate.ToString(DalFormatterStrings::PrintByte) + "Sequence No: " + expectedSequenceNumberToLocate.ToString(DalFormatterStrings::PrintByte) );
	
	//set the flag to true
	this->checkForCommand = true;

	//store the vvalues which we want to look for
	this->commandCodeToLocate = commandCodeToLocate;
	this->expectedResponseLengthToLocate  = expectedResponseLengthToLocate;
	//this->expectedSequenceNumberToLocate = expectedSequenceNumberToLocate;
}

void DalStagingQueue::StopLookingForResponse()
{
	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::StopLookingForResponse: ");

	this->checkForCommand = false;

}

void  DalStagingQueue::ProcessQueue()
{
	
	bool returnValue = true; //set to true so that we can do processig once
	//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessQueue Start queue length :  " +  this->stagingQueue->Count );

	
	do
	{
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessQueue Calling ProcessSinglePacket");
				
		returnValue = ProcessSinglePacket();
	}
	while(returnValue);

	//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessQueue End queue length :  " +  this->stagingQueue->Count );


	//return returnValue; //changed to voud
}

void DalStagingQueue::EnqueueArray(array<unsigned char,1> ^sourceArray)
{
	if (nullptr == sourceArray)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrorNullParamErrCd, CrxStructCommonResourceMsg::DalErrorNullParam, ErrorSeverity::Warning);
	}

	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::EnqueueArray stagingMutex LOCK");
	//lock the resource
	stagingMutex->WaitOne();

	try
	{
	//add the array at the end of the staging queue
	this->stagingQueue->AddRange(sourceArray);
	}
	finally
	{
		//rlease the mutex
		stagingMutex->ReleaseMutex();
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::EnqueueArray stagingMutex RELEASE");
	}

	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::EnqueueArray Added:  " +  AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(sourceArray));
	//////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::EnqueueArray stagingQueue:  " +  AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(this->stagingQueue->ToArray()));

	//Now that the data has been added, call the processing method asynchronously
	//We do not have any mehtod to call back so both parameters are null
	//_processQueueAsyncCaller->BeginInvoke(nullptr, nullptr); \
	//TODO: we will no call this method in a thread instead of directly
	//Calling will be done by the DalActivePort whcih pushes the data onto the que or the class which wants more data

}

DalStagingQueue^ DalStagingQueue::Instance::get()
{
	return DalStagingQueue::_instance;
}

array<unsigned char>^ DalStagingQueue::DequeueArray(int numberOfBytes)
{
	array <unsigned char>^ returnValueArray;
	
	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::DequeueArray stagingMutex LOCK");
	//take a lock AT THE VERY BEGINING DONT WANT COUNT TO CHANGE DURING EXECUTION
	stagingMutex->WaitOne();
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::DequeueArray stagingMutex LOCK TAKEN");

	if (numberOfBytes > (this->stagingQueue->Count))
	{
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::DequeueArray : UNDERFLOW" + "Number of Bytes Requested " + numberOfBytes + " Available" +  (this->stagingQueue->Count));
		//instead of throwing an exception we should return false to let the processing start gain
		
		//Deepak: using this invoke here may cause a problem. Need to search this posible scenario more carefully
		//TODO: recheck this scenario
		//invoke the read method over here so that it can try and fill the missin data
		//	_attemptUnderFlowReadCaller->BeginInvoke(nullptr, nullptr);

		//release the lock
		stagingMutex->ReleaseMutex();

		return nullptr;
	}

	try
	{
		//First return the required contents
		returnValueArray = this->stagingQueue->GetRange(0, numberOfBytes)->ToArray();
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::DequeueArray returnValueArray = " + AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(returnValueArray));
		
		//remove the content from the array
		this->stagingQueue->RemoveRange(0, numberOfBytes);
	}
	catch(Exception^ excepObj)
	{
		//////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::DequeueArray Exception: " + excepObj->Message+ " :" + excepObj->StackTrace);
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::DequeueArray Exception: numberOfBytes: " +  numberOfBytes + " Array Available" + this->stagingQueue->Count);
		
		//deleting exception and returning a nullptr
		delete excepObj;
		return nullptr;
	}
	finally
	{
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::DequeueArray Inside finally block.");

		//release the lock
		stagingMutex->ReleaseMutex();
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::DequeueArray stagingMutex RELEASE");
	}
	return returnValueArray;
}

bool DalStagingQueue::ProcessSinglePacket()
{
	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessSinglePacket Start with queue:  " +  AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(this->stagingQueue->ToArray()));
	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessSinglePacket Start with queue length :  " +  this->stagingQueue->Count );

 
	stagingMutex->WaitOne();
	if (0 == this->stagingQueue->Count )
	{
		//////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessSinglePacket ZERO Data");
		stagingMutex->ReleaseMutex();
		return false;
	}
	//else
	
	//get the first element from the queue and find it's type
	unsigned char firstByteinQueue = this->stagingQueue[0];
	DalPacketType packetType =  DeterminePacketType(firstByteinQueue);
	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessSinglePacket Type determined = " + packetType.ToString(DalFormatterStrings::PrintEnumName)+ " firstByteinQueue " +firstByteinQueue.ToString(DalFormatterStrings::PrintByte));

	//TEst Code only: TODO
	if (DalPacketType::Unknown == packetType)
	{
		CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessSinglePacket Buffer: " + DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray()));
	}
	
	stagingMutex->ReleaseMutex();

	array<unsigned char>^ extractedPacket; 
	
	

	//take action based on type
	if (DalPacketType::StreamingDataPacket  == packetType)
	{
		extractedPacket = ExtractStreamingDataPacket();
	}
	else if (DalPacketType::AckedResponsePakcet  == packetType)
	{
		extractedPacket = ExtractAckedResponsePakcet();
	}
	else if (DalPacketType::NackedResponsePacket == packetType)
	{
		extractedPacket = ExtractNackedResponsePacket();
	}
	else
	{
		//Cannot determine type of packet in queue
		
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessSinglePacket ERROR condition: firstByteinQueue "  + firstByteinQueue.ToString(DalFormatterStrings::PrintByte));
		
		//clear the buffer as required
		PartiallyClearBuffer();
	}

	//////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessSinglePacket ENDING queue:  " +  AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(this->stagingQueue->ToArray()));
	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessSinglePacket ENDING " );
	Thread::Sleep(0);


	if (nullptr == extractedPacket)
	{
		//if we havent extracted any data return false to signify that there is nothing left to process
		return false;
	}
	else
	{
		return true;
	}
}

DalStagingQueue::~DalStagingQueue()
{
	this->dataProcessingThread->Abort();


	delete this->stagingQueue;
	delete this->stagingMutex;

	this->stagingQueue = nullptr;
	this->stagingMutex =  nullptr;

}

void DalStagingQueue::CaptureMode::set(bool mode)
{
	_captureMode = mode;
}

void DalStagingQueue::PartiallyClearBuffer()
{
	if (_captureMode)
	{
		//We are in capture mode . need to only clear till the next straming packet in the array
		//TODO: code this
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::PartiallyClearBuffer Noty implemented for streaming:  " );

		int nextStreamingPacketIndex = GetIndexOfNextStreamingPacketHead();
		
		if (-1 == nextStreamingPacketIndex)
		{
			//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::PartiallyClearBuffer clearing entire buffer in Capture Mode:  " +  DalBinaryConversions::ConvertBytesToString(stagingQueue->ToArray()));
			
			//there are no more packets clear entire buffer
			EmptyBuffer();
		}
		else
		{
			stagingMutex->WaitOne();

			//TODO: this line is for debugging only. Delete when not required
			//array<unsigned char> ^ returnValueArray = this->stagingQueue->GetRange(0, nextStreamingPacketIndex)->ToArray();

			//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::PartiallyClearBuffer Partial remove length:  "+ nextStreamingPacketIndex + " Bytes : " +  DalBinaryConversions::ConvertBytesToString(returnValueArray));

			//clear from 0 to (nextStreamingPacketIndex-1)
			this->stagingQueue->RemoveRange(0, nextStreamingPacketIndex);

			stagingMutex->ReleaseMutex();

		}
	}
	else
	{
		//CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::PartiallyClearBuffer clearing entire buffer:  " +  DalBinaryConversions::ConvertBytesToString(stagingQueue->ToArray()));
	
		//command response mode clear the entire buffer.
		EmptyBuffer();
	}
}

void DalStagingQueue::ProcessingThreadMethod()
{
	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessingThreadMethod Enter");
	try
	{

		do
		{
			try
			{
				if(this->stagingQueue->Count)
				{
					////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessingThreadMethod Calling ProcessQueue()");
					ProcessQueue();

				}

				Thread::Sleep(Timeout::Infinite ); 	//sleep until woken again
			}
			catch(ThreadInterruptedException^ ex)
			{
				//This exception is raised wne thread->Interrupt is called. 
				//It is not a real expception
				delete ex;
				////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessingThreadMethod ThreadInterruptedException raised");
				continue;
			}


		}
		while(true);
	}
	catch(ScorException^ scorExObj)
	{
		//throw; //dont throw an excpetion from a thread . convert it to an event

		DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException, scorExObj);
	}
	catch(Exception^ excepObj)
	{
		
		//throw gcnew ScorException(excepObj);//dont throw an excpetion from a thread . convert it to an event

		DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException, gcnew ScorException(excepObj));
	}



	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::ProcessingThreadMethod Exit");
}

void DalStagingQueue::SignalDataAvailable()
{
	dataProcessingThread->Interrupt();
}

int DalStagingQueue::GetIndexOfNextStreamingPacketHead()
{
	//look for  0x87 ox0D pattern and return index

	bool found  = false;

	int indexToSearchFrom = 0;

	int indexFound;

	try
	{
		do 
		{
			//First look for 87H
			indexFound = stagingQueue->IndexOf(0x87, indexToSearchFrom);
			if (-1 == indexFound)
			{
				return -1; //tell caller we didnt find it
			}
			else
			{
				//TODO: THis will change for PWA mode
				//then check if the next element is 0DH
				if(stagingQueue[indexFound + 1] == 0x0D)
				{
					found = true;
					return indexFound;
				}
				else
				{
					//THis index is not the start of the header
					indexToSearchFrom = indexFound+1;
				}
			}
		}while(!found);
	}
	catch(ArgumentOutOfRangeException^ ex)
	{
		delete ex;
		return -1;
	}

	return -1;
}


void DalStagingQueue::EmptyBuffer()
{
	////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::PartiallyClearBuffer stagingMutex LOCK");
		stagingMutex->WaitOne();
	
		//clear the entire buffer.
		stagingQueue->Clear();

		stagingMutex->ReleaseMutex();
		////CrxLogger::Instance->Write("Deepak>>> DalStagingQueue::PartiallyClearBuffer stagingMutex RELEASE");
}
