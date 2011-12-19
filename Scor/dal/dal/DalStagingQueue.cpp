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
#include "DalNibpDeviceHandler.h"
#include "DalEventContainer.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;


DalStagingQueue::DalStagingQueue()
{
	this->stagingQueue = gcnew  List<unsigned char> ;
	//not needed any more
	//_nackPacketStandardLength = DalConstants::EM4ZeroDataResponsePacketSize + DalConstants::EM4NackPacketDataLength ;
	//TODO: _streamingPacketSize  should change based on PWV/PWA mode
	//_streamingPacketSize = DalConstants::PWVCaptureDataSize + DalConstants::EM4ZeroDataResponsePacketSize;

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
	else if( 0x93 == commandCodeByte) //determine if this is an NIBP type
	{
		//0x93 is specifically NIBP recieved
		return DalPacketType::NibpPacket;
	}
	else if  (0xA1 == commandCodeByte)
	{
		return DalPacketType::NibpProcessAbortedPacket;

	}
	else
	{

		//Deepak: Determine type solely based on the charachter. Do not loo at what the uper layers are asking

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

//array <unsigned char>^  DalStagingQueue::ExtractAckedResponsePakcet()
//{
//	//Changing the method to reduce dependency on othe rlayers
//	//It does not need to know the length but can find out on its own. -Deepak
//
//	//this is dependant on the checkFlag 
//	//Assuming that this method will only be called after the flag is set
//	//////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ExtractAckedResponsePakcet Start", ErrorSeverity::Debug);
//
//		//First get the length of the packet
//	unsigned int lengthOfThisPacket;
//
//	if ( stagingQueue->Count >=2)
//	{
//		//This conditional check is necessary so that we do not cause an array fault
//		lengthOfThisPacket = this->stagingQueue[1]; //get the length which is stored in the second byte of the packet,
//	}
//	else
//	{
//		//CrxLogger::Instance->Write("DalStagingQueue::ExtractNibpPacket stagingQueue count is less than expected Value: " + stagingQueue->Count, ErrorSeverity::Exception );  
//		return  nullptr;
//
//	}
//
//	array<unsigned char>^ tempArray = nullptr;
//
//	//tempArray = DequeueArray(expectedResponseLengthToLocate + 1) ; //1 for CRC
//	tempArray = DequeueArray(lengthOfThisPacket + 1) ; //1 for CRC
//
//	
//	if (nullptr!= tempArray)
//	{
//		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ExtractAckedResponsePakcet AckedResponsePacket:  " +  DalBinaryConversions::ConvertBytesToString(tempArray), ErrorSeverity::Debug);
//	
//		//this->checkForCommand = false; //make a note that the command has been sent to the handler
//
//		//call the method which will upload it to the required array
//		DalResponsePacketBuffer::Instance->Enqueue(tempArray);
//	}
//	return tempArray;
//}

////TODO: we may not need this if the new loginc works-Deepak
//array <unsigned char>^ DalStagingQueue::ExtractNackedResponsePacket()
//{
//	//////CrxLogger::Instance->Write("DAL>>>  DalStagingQueue::ExtractNackedResponsePacket Start", ErrorSeverity::Debug);
//	array<unsigned char>^ tempArray;
//
//	tempArray = DequeueArray(_nackPacketStandardLength + 1) ; //1 for CRC
//	
//	
//	if (nullptr!= tempArray)
//	{
//		CrxLogger::Instance->Write("DAL>>>  DalStagingQueue::ExtractNackedResponsePacket Nacked Response Packet:  " +  DalBinaryConversions::ConvertBytesToString(tempArray), ErrorSeverity::Debug);
//	
//
//		//this->checkForCommand = false; //make a note that the command has been sent to the handler
//
//		//call the method which will upload it to the required array
//		DalResponsePacketBuffer::Instance->Enqueue(tempArray);
//	}
//	return tempArray;
//}

//array <unsigned char>^ DalStagingQueue::ExtractStreamingDataPacket()
//{
////	//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ExtractStreamingDataPacket  Start", ErrorSeverity::Debug);
//	array<unsigned char>^ tempArray = nullptr;
//
//	tempArray = DequeueArray(_streamingPacketSize + 1) ; //1 for CRC
//
//	if (nullptr!= tempArray)
//	{
//
//		CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ExtractStreamingDataPacket StreamingPacket:  " +  DalBinaryConversions::ConvertBytesToString(tempArray), ErrorSeverity::Debug);
//
//		DalStreamingPacketQueue::Instance->Enqueue(tempArray);
//	}
//
//	return tempArray;
//}


//array <unsigned char>^ DalStagingQueue::ExtractNibpPacket()
//{
//	//////CrxLogger::Instance->Write("DAL>>>  DalStagingQueue::ExtractNibpPacket Start", ErrorSeverity::Debug);
//	array<unsigned char>^ tempArray;
//	unsigned int nibpPacketLength;
//
//	//firs determine the length of the NIBP packet
//
//
//	if ( stagingQueue->Count >=2)
//	{
//		//This conditional check is necessary so that we do not cause an array fault
//
//		nibpPacketLength  = (unsigned int)stagingQueue[1] ; //the packet's length byte is in 1th position
//	}
//	else
//	{
//		CrxLogger::Instance->Write("DalStagingQueue::ExtractNibpPacket stagingQueue count is less than expected Value: " + stagingQueue->Count, ErrorSeverity::Exception );  
//		return  nullptr;
//
//	}
//
//
//	tempArray = DequeueArray(nibpPacketLength + 1) ; //+1 for CRC
//	
//	
//	if (nullptr!= tempArray)
//	{
//		//CrxLogger::Instance->Write("DAL>>>  DalStagingQueue::ExtractNibpPacket Nacked Response Packet:  " +  DalBinaryConversions::ConvertBytesToString(tempArray), ErrorSeverity::Debug);
//	
//		//DalNibpCommandInterface::NibPPacketArrivedEventHandler ^nibpPacketRecievedEvent = gcnew NibPPacketArrivedEventHandler(this, gcnew NibPacketArrivedEventArgs(tempArray) );
//		
//		//EventHandler<NibPacketArrivedEventArgs^> ^nibpPacketRecievedEvent = gcnew EventHandler<NibPacketArrivedEventArgs^>(this, gcnew NibPacketArrivedEventArgs(tempArray));
//		//nibpPacketRecievedEvent(this, gcnew NibPacketArrivedEventArgs(tempArray) );
//
//		//TODO: seewhere we are going to put it.
//		//call the method which will upload it to the required array
//		//DalResponsePacketBuffer::Instance->Enqueue(tempArray);
//
//		////Raise an event and let any interested party handle it
//		//DalEventContainer::Instance->OnDalNibpPacketEvent(this, gcnew NibPacketArrivedEventArgs(tempArray));
//
//		//Call the method which will process the NIBP packet 
//		DalNibpCommandInterface::ProcessNibpToHostPacket(tempArray);
//	}
//	return tempArray;
//}

//array <unsigned char>^ DalStagingQueue::ExtractNibpAbortPacket()
//{
//	//////CrxLogger::Instance->Write("DAL>>>  DalStagingQueue::ExtractNibpAbortPacket Start", ErrorSeverity::Debug);
//	array<unsigned char>^ tempArray;
//
//	//determine the length of the NIBP packet
//	unsigned int nibpPacketLength;
//
//	if ( stagingQueue->Count >=2)
//	{
//
//		nibpPacketLength  = (unsigned int)stagingQueue[1] ; //the packet's length byte is in 1th position
//	}
//	else
//	{
//		//CrxLogger::Instance->Write("DalStagingQueue::ExtractNibpPacket stagingQueue count is less than expected Value: " + stagingQueue->Count, ErrorSeverity::Exception );  
//		return  nullptr;
//
//	}
//
//	tempArray = DequeueArray(nibpPacketLength + 1) ; //+1 for CRC
//	
//	//raise the necessary signal. Passing the data is irrelvant.
//	//TODO
//
//	DalNibpDeviceHandler::Instance->signalNibpAbortCaller->Invoke(); 
//	
//	
//	return tempArray;
//}

//void DalStagingQueue::LookForResponseToCommand(
//												unsigned char commandCodeToLocate, 
//												unsigned char expectedResponseLengthToLocate 
//										
//												)
//{
//	//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::LookForResponseToCommand:  " + commandCodeToLocate.ToString(DalFormatterStrings::PrintByte) + "Sequence No: " + expectedSequenceNumberToLocate.ToString(DalFormatterStrings::PrintByte) , ErrorSeverity::Debug);
//	
//	//set the flag to true
//	//this->checkForCommand = true;
//
//	//store the vvalues which we want to look for
//	this->commandCodeToLocate = commandCodeToLocate;
//	this->expectedResponseLengthToLocate  = expectedResponseLengthToLocate;
//	//this->expectedSequenceNumberToLocate = expectedSequenceNumberToLocate;
//}

//void DalStagingQueue::StopLookingForResponse()
//{
//	////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::StopLookingForResponse: ", ErrorSeverity::Debug);
//
//	//this->checkForCommand = false;
//
//}

void  DalStagingQueue::ProcessQueue()
{
	
	bool returnValue = true; //set to true so that we can do processig once
	//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessQueue Start queue length :  " +  this->stagingQueue->Count , ErrorSeverity::Debug);

	
	do
	{
		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessQueue Calling ProcessSinglePacket", ErrorSeverity::Debug);
				
		returnValue = ProcessSinglePacket();
		Thread::Sleep(0); //zero sleep to let other processes run
	}
	while(returnValue);

	//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessQueue End queue length :  " +  this->stagingQueue->Count , ErrorSeverity::Debug);


	//return returnValue; //changed to voud
}

void DalStagingQueue::EnqueueArray(array<unsigned char,1> ^sourceArray)
{
	if (nullptr == sourceArray)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrorNullParamErrCd, CrxStructCommonResourceMsg::DalErrorNullParam, ErrorSeverity::Warning);
	}

	////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::EnqueueArray stagingMutex LOCK", ErrorSeverity::Debug);
	//lock the resource
	//stagingMutex->WaitOne();

	Monitor::Enter(this->stagingQueue);
	try
	{
	//add the array at the end of the staging queue
	this->stagingQueue->AddRange(sourceArray);
	}
	finally
	{
		Monitor::Exit(this->stagingQueue);
		//rlease the mutex
		//stagingMutex->ReleaseMutex();
		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::EnqueueArray stagingMutex RELEASE", ErrorSeverity::Debug);
	}

	////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::EnqueueArray Added:  " +  AtCor::Scor::DataAccess::DalStatusHandler::ConvertBytesToString(sourceArray), ErrorSeverity::Debug);
	//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::EnqueueArray after adding: " + DalBinaryConversions::ConvertBytesToString(sourceArray)+ ", stagingQueue:  " +  DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray()), ErrorSeverity::Debug);

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
	
	////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray stagingMutex LOCK", ErrorSeverity::Debug);
	//take a lock AT THE VERY BEGINING DONT WANT COUNT TO CHANGE DURING EXECUTION
	//stagingMutex->WaitOne();
		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray stagingMutex LOCK TAKEN", ErrorSeverity::Debug);

	Monitor::Enter(this->stagingQueue);
	if (numberOfBytes > (this->stagingQueue->Count))
	{
		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray : UNDERFLOW" + "Number of Bytes Requested " + numberOfBytes + " Available" +  (this->stagingQueue->Count), ErrorSeverity::Debug);
		//instead of throwing an exception we should return false to let the processing start gain
		
		//release the lock
		//stagingMutex->ReleaseMutex();

		Monitor::Exit(this->stagingQueue);

		return nullptr;
	}

	
	try
	{
		//First return the required contents
		returnValueArray = this->stagingQueue->GetRange(0, numberOfBytes)->ToArray();
		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray returnValueArray = " + DalBinaryConversions::ConvertBytesToString(returnValueArray), ErrorSeverity::Debug);
		
		
		
		//remove the content from the array
		this->stagingQueue->RemoveRange(0, numberOfBytes);

		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray after removing: " + DalBinaryConversions::ConvertBytesToString(returnValueArray)+", stagingQueue:  " +  DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray()), ErrorSeverity::Debug);

	}
	catch(Exception^ excepObj)
	{
		//////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray Exception: " + excepObj->Message+ " :" + excepObj->StackTrace, ErrorSeverity::Debug);
		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray Exception: numberOfBytes: " +  numberOfBytes + " Array Available" + this->stagingQueue->Count, ErrorSeverity::Debug);
		
		//deleting exception and returning a nullptr
		delete excepObj;
		returnValueArray =  nullptr;
	}
	finally
	{
		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray Inside finally block.", ErrorSeverity::Debug);

		//release the lock
		//stagingMutex->ReleaseMutex();
		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::DequeueArray stagingMutex RELEASE", ErrorSeverity::Debug);
		Monitor::Exit(this->stagingQueue);

	}
	return returnValueArray;
}

//bool DalStagingQueue::ProcessSinglePacket()
//{
//	try
//	{
//		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket Start with queue length :  " +  this->stagingQueue->Count + " Queue: " + DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray())   , ErrorSeverity::Debug);
//
//	 
//		//stagingMutex->WaitOne();
//		if (0 == this->stagingQueue->Count )
//		{
//			//////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket ZERO Data", ErrorSeverity::Debug);
//			//stagingMutex->ReleaseMutex();
//			return false;
//		}
//		//else
//		
//		//get the first element from the queue and find it's type
//		unsigned char firstByteinQueue = this->stagingQueue[0];
//		DalPacketType packetType =  DeterminePacketType(firstByteinQueue);
//		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket Type determined = " + packetType.ToString(DalFormatterStrings::PrintEnumName)+ " firstByteinQueue " +firstByteinQueue.ToString(DalFormatterStrings::PrintByte), ErrorSeverity::Debug);
//
//		//TEst Code only: TODO
//		if (DalPacketType::Unknown == packetType)
//		{
//			CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket Buffer Unknown type: " + DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray()), ErrorSeverity::Debug);
//		}
//		
//		//stagingMutex->ReleaseMutex();
//
//		array<unsigned char>^ extractedPacket; 
//		
//		
//		extractedPacket = ExtractPacketByType(packetType);
//
//		//stagingMutex->ReleaseMutex();
//		//Thread::Sleep(0);
//
//		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket ENDING queue:  " +  DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray()), ErrorSeverity::Debug);
//		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket ENDING " , ErrorSeverity::Debug);
//		
//
//
//		if (nullptr == extractedPacket)
//		{
//			//if we havent extracted any data return false to signify that there is nothing left to process
//			return false;
//		}
//		else
//		{
//			return true;
//		}
//	}
//	catch(Exception^ excepObj)
//	{
//		throw gcnew ScorException(excepObj);
//	}
//}


//Implmented using a different logic
bool DalStagingQueue::ProcessSinglePacket()
{
	try
	{
		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket Start with queue length :  " +  this->stagingQueue->Count + " Queue: " + DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray())   , ErrorSeverity::Debug);

 
		//stagingMutex->WaitOne();
	if (0 == this->stagingQueue->Count )
	{
			//////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket ZERO Data", ErrorSeverity::Debug);
			//stagingMutex->ReleaseMutex();
		return false;
	}
	//else
	
		array<unsigned char>^ extractedPacket;
		extractedPacket = GetNextPacket();

		if (nullptr == extractedPacket)
	{
			return false;
	}
		//else we got the array
		//now determine its type and what to be done with it.
		ProcessPacketByType(extractedPacket);

		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket ENDING queue:  " +  DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray()), ErrorSeverity::Debug);
		return true;


	}
	catch(ScorException^)
	{
		throw;
	}
	catch(Exception^ excepObj)
	{
		throw gcnew ScorException(excepObj);
	}
}

//array<unsigned char>^ DalStagingQueue::ExtractPacketByType(DalPacketType packetType)
//{
//	array<unsigned char>^ extractedPacket; 
//
//	//take action based on type
//	if (DalPacketType::StreamingDataPacket  == packetType)
//	{
//		extractedPacket = ExtractStreamingDataPacket();
//	}
//	else if (DalPacketType::AckedResponsePakcet  == packetType)
//	{
//		extractedPacket = ExtractAckedResponsePakcet();
//	}
//	else if (DalPacketType::NackedResponsePacket == packetType)
//	{
//		extractedPacket = ExtractNackedResponsePacket();
//	}
//	else if (DalPacketType::NibpPacket == packetType)
//	{
//		extractedPacket = ExtractNibpPacket();
//
//	}
//	else if (DalPacketType::NibpProcessAbortedPacket == packetType)
//	{
//		extractedPacket = ExtractNibpAbortPacket();
//	}
//	else
//	{
//		//Cannot determine type of packet in queue
//		
//		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessSinglePacket ERROR condition: firstByteinQueue "  + firstByteinQueue.ToString(DalFormatterStrings::PrintByte), ErrorSeverity::Debug);
//		
//		//clear the buffer as required
//		PartiallyClearBuffer();
//		extractedPacket =  nullptr;
//	}
//
//	return extractedPacket;
//
//}

DalStagingQueue::~DalStagingQueue()
{
	this->dataProcessingThread->Abort();


	delete this->stagingQueue;
	//delete this->stagingMutex;

	this->stagingQueue = nullptr;
	//this->stagingMutex =  nullptr;

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

		int nextStreamingPacketIndex = GetIndexOfNextStreamingPacketHead();
		
		if (-1 == nextStreamingPacketIndex)
		{
			CrxLogger::Instance->Write("DAL>>> DalStagingQueue::PartiallyClearBuffer clearing entire buffer in Capture Mode:  " +  DalBinaryConversions::ConvertBytesToString(stagingQueue->ToArray()), ErrorSeverity::Debug);
			
			//there are no more packets clear entire buffer
			EmptyBuffer();
		}
		else
		{
			//stagingMutex->WaitOne();

			//TODO: this line is for debugging only. Delete when not required
			array<unsigned char> ^ returnValueArray = this->stagingQueue->GetRange(0, nextStreamingPacketIndex)->ToArray();

			CrxLogger::Instance->Write("DAL>>> DalStagingQueue::PartiallyClearBuffer Partial remove length:  "+ nextStreamingPacketIndex + " Bytes : " +  DalBinaryConversions::ConvertBytesToString(returnValueArray), ErrorSeverity::Debug);

			//clear from 0 to (nextStreamingPacketIndex-1)
			this->stagingQueue->RemoveRange(0, nextStreamingPacketIndex);

			//stagingMutex->ReleaseMutex();

		}
	}
	else
	{
		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::PartiallyClearBuffer clearing entire buffer:  " +  DalBinaryConversions::ConvertBytesToString(stagingQueue->ToArray()), ErrorSeverity::Debug);
	
		//command response mode clear the entire buffer.
		EmptyBuffer();
	}
}

void DalStagingQueue::ProcessingThreadMethod()
{
	////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessingThreadMethod Enter", ErrorSeverity::Debug);
	try
	{

		do
		{
			try
			{
				if(this->stagingQueue->Count)
				{
					////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessingThreadMethod Calling ProcessQueue()", ErrorSeverity::Debug);
					ProcessQueue();

				}

				Thread::Sleep(Timeout::Infinite ); 	//sleep until woken again
			}
			catch (ThreadAbortException^ )
			{
			
				//dont abort the thread
				Thread::ResetAbort();

			}
			catch(ThreadInterruptedException^ ex)
			{
				//This exception is raised wne thread->Interrupt is called. 
				//It is not a real expception
				delete ex;
				////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessingThreadMethod ThreadInterruptedException raised", ErrorSeverity::Debug);
				continue;
			}


		}
		while(true); //will remain true always
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



	////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessingThreadMethod Exit", ErrorSeverity::Debug);
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
	////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::PartiallyClearBuffer stagingMutex LOCK", ErrorSeverity::Debug);
		//stagingMutex->WaitOne();
	
		CrxLogger::Instance->Write("DAL>>> DalStagingQueue::PartiallyClearBuffer array being cleared:" +DalBinaryConversions::ConvertBytesToString(stagingQueue->ToArray()), ErrorSeverity::Debug);
		//clear the entire buffer.
		stagingQueue->Clear();

		//stagingMutex->ReleaseMutex();
		////CrxLogger::Instance->Write("DAL>>> DalStagingQueue::PartiallyClearBuffer stagingMutex RELEASE", ErrorSeverity::Debug);
}


array<unsigned char>^ DalStagingQueue::GetNextPacket()
{
		//First get the length of the packet
	array<unsigned char>^ tempArray = nullptr;
	unsigned int lengthOfThisPacket;
	unsigned int requiredNuberOfBytes;

	try
	{
		Monitor::Enter(this->stagingQueue);
	
		//We need two bytes to remove a packet from staging queue
		if ( stagingQueue->Count >=2)
		{
			//This conditional check is necessary so that we do not cause an array fault
			lengthOfThisPacket = this->stagingQueue[1]; //get the length which is stored in the second byte of the packet,
			
			//Add 1 for CRC and keep so tht we dont have to calculate repeatedly
			requiredNuberOfBytes = lengthOfThisPacket + 1;

			//next check if the array has as many bytes as we need(lenth +1)
			if ((int)(requiredNuberOfBytes) > (this->stagingQueue->Count))
			{
				//the entire packet is not vaialable
				//return a null pointer
				tempArray = nullptr;
				//CrxLogger::Instance->Write("DalStagingQueue::GetNextPacket stagingQueue count is less than expected Value: " + stagingQueue->Count, ErrorSeverity::Exception );  
			

			}
			else
			{
				//we have as many bytes as we need 
				//deque the required bytes

				tempArray = DequeueArray(requiredNuberOfBytes) ;
			}

			//if yes then go ahead and dequeue
		}
		else
		{
			//not enough bytes to determine packet type and size

			tempArray =   nullptr;

			//CrxLogger::Instance->Write("DalStagingQueue::GetNextPacket stagingQueue count is less than expected Value: " + stagingQueue->Count, ErrorSeverity::Exception );  
			

		}
	}
	catch(ScorException^)
	{
		throw;

	}
	catch(Exception^ excepObj)
	{
		throw gcnew ScorException(excepObj);
	}
	finally
	{
		//rlease lock here
		Monitor::Exit(this->stagingQueue);

		//TODO: remove lock from DequeArray if this lock works

		
	}
	return tempArray;
}

void DalStagingQueue::ProcessPacketByType(array <unsigned char>^ packet)
{
	//TODO: do we need a check for empy arrya inot null.

	//get the first element from the queue and find it's type
	unsigned char firstByteinQueue = packet[0];
	DalPacketType packetType =  DeterminePacketType(firstByteinQueue);
	//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessPacketByType Type determined = " + packetType.ToString(DalFormatterStrings::PrintEnumName)+ " firstByteinQueue " +firstByteinQueue.ToString(DalFormatterStrings::PrintByte), ErrorSeverity::Debug);

	//now perform action based on type
	//TEst Code only: TODO
	if (DalPacketType::Unknown == packetType)
	{
		CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ProcessPacketByType Buffer Unknown type: " + DalBinaryConversions::ConvertBytesToString(this->stagingQueue->ToArray()), ErrorSeverity::Debug);
	}
	else if (DalPacketType::StreamingDataPacket  == packetType)
	{
		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ExtractStreamingDataPacket StreamingPacket:  " +  DalBinaryConversions::ConvertBytesToString(tempArray), ErrorSeverity::Debug);
		DalStreamingPacketQueue::Instance->Enqueue(packet);
	}
	else if (DalPacketType::AckedResponsePakcet  == packetType)
	{
		//CrxLogger::Instance->Write("DAL>>> DalStagingQueue::ExtractAckedResponsePakcet AckedResponsePacket:  " +  DalBinaryConversions::ConvertBytesToString(tempArray), ErrorSeverity::Debug);
	
		//call the method which will upload it to the required array
		DalResponsePacketBuffer::Instance->Enqueue(packet);
	}
	else if (DalPacketType::NackedResponsePacket == packetType)
	{
		//CrxLogger::Instance->Write("DAL>>>  DalStagingQueue::ExtractNackedResponsePacket Nacked Response Packet:  " +  DalBinaryConversions::ConvertBytesToString(tempArray), ErrorSeverity::Debug);
	
		//call the method which will upload it to the required array
		DalResponsePacketBuffer::Instance->Enqueue(packet);
	}
	else if (DalPacketType::NibpPacket == packetType)
	{
		//Call the method which will process the NIBP packet 
		DalNibpCommandInterface::ProcessNibpToHostPacket(packet);

	}
	else if (DalPacketType::NibpProcessAbortedPacket == packetType)
	{
		//raise the necessary signal. Passing the data is irrelvant.
		//DalNibpDeviceHandler::Instance->signalNibpAbortCaller->Invoke(); 
		////TODO: amke this begin invoke
		DalNibpDeviceHandler::Instance->AbortBpOnStopButtonPress();
	}
	
}
