/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalStagingQueue.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalStagingQue class
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"

using namespace System; //general
using namespace System::Collections::Generic; //For Queue<T>
using namespace System::Threading; //For mutex

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalStagingQueue
			{

			private:
				
				//Queue<unsigned char>^ stagingQueue;
				List<unsigned char>^ stagingQueue;
				
				static Mutex ^stagingMutex = gcnew Mutex; 

				//int stagingQueueLength; //To set the length of the queue
				 unsigned char commandCodeToLocate;
				unsigned char expectedResponseLengthToLocate; 
				//unsigned char expectedSequenceNumberToLocate; //TODO: may be needed later
				static bool checkForCommand;//default false
				unsigned int _nackPacketStandardLength; //Excluding CRC
				unsigned int  _streamingPacketSize; 

				static DalStagingQueue^ _instance = gcnew DalStagingQueue();

				bool _captureMode; //a flag to know wheter we are in capture mode or command-response mode

				Thread^ dataProcessingThread; //thread to process the data in the queue


				/**
				* Determines the type of packet of the specifed firstbyte
				* @param[in]	commandCodeByte	The first byte in a byte array whose type is to be determined
				*
				* @returns	The type of packet as a DalPacketType value.
				*/
				DalPacketType DeterminePacketType(unsigned char commandCodeByte);

				/**
				* Dequeues a complete streaming packet from the head of the list.
				*
				* @return	A Streaming packet from the head of the array
				*/
				array <unsigned char>^ ExtractStreamingDataPacket();

				/**
				* Dequeues a complete Acked response packet from the head of the list.
				*
				* @return	An Acked packet from the head of the array
				*
				* @warning First determine the packet type using DeterminePacketType. If the type and code are 
				*			not corret then the funtion will throw an error.
				*/
				array <unsigned char>^ ExtractAckedResponsePakcet();

				/**
				* Dequeues a complete Acked response packet from the head of the list.
				*
				* @return	An Acked packet from the head of the array
				*
				* @warning First determine the packet type using DeterminePacketType. If the type and code are 
				*			not corret then the funtion will throw an error.
				*/
				array <unsigned char>^ ExtractNackedResponsePacket();
				
				/**
				* Loops through all the bytes in the queue and classifies each accordign to the type
				* It then calls the respective methods which extract the packet based on the type.
				* Does this untill there is a complete packet left to pick.
				*/
				void ProcessQueue();

				DalStagingQueue(); //constructor
				~DalStagingQueue(); //Destructor
				DalStagingQueue^ operator= (DalStagingQueue^); //assignment operator

				/**
				* Gets an array from the que with the specified length 
				*/
				array <unsigned char>^ DequeueArray(int numberOfBytes);

				/**
				* Determines the type of the first packet in the queue and extracts it to its respective buffer
				*/
				bool ProcessSinglePacket();

				//A delegate to call using begininvoke. Should have the same signature as the method being called
				//Since we are using it within this class itself it has been defined as a class member and not outside.
				 delegate void ProcessQueueAsyncCaller();

				 //Delegate to call the read method in case of an underflow
				 delegate void AttemptUnderFlowReadCaller();

				 //Clears the buffer partially.
				 //If it is in streming mode it clears the array till the next streaming pacet.
				 //In command response mode it clears the entire buffer
				 void PartiallyClearBuffer();

				 //This thread processes the entire queue as long as there are valid packets left.
				 //Once it finishes it goes to sleep until woken up.
				 void ProcessingThreadMethod();

				 //Locates the next streaming packet and returns its index.
				int GetIndexOfNextStreamingPacketHead();

				
				
				
			internal:

				/**
				* Property with custom get method to supply instance.@n
				* Used to implement singleton
				*/
				static property DalStagingQueue^ Instance
				{

					/**
					* Custom get method. @n
					* Returns a pointer to this singleton instance.
					*
					* @return	Pointer to this instance
					*/
					DalStagingQueue^ get();
				};

				/**
				* Adds the specified byte array to the end of the queue.
				*
				* @param[in]	sourceArray	THe byte array to enqueue	
				*/
				void EnqueueArray(array <unsigned char>^ sourceArray);

				/**
				* Tells the processing thread that it should watch out for a response to an EM4 command
				* whihc has the specified code, length and sequence mumber
				*
				* @param[in]	commandCodeToLocate	The command code of the sent command.	
				* @param[in]	expectedResponseLengthToLocate	The expected length of the acked response.	
				* @param[in]	expectedSequenceNumberToLocate	The sequence number that should be echoed.	
				*/
				void LookForResponseToCommand( 
												unsigned char commandCodeToLocate,
												unsigned char expectedResponseLengthToLocate, //should be same as Em4ResponseRequiredLength enum
												unsigned char expectedSequenceNumberToLocate
												);

				/**
				* Tells the processign thread to not expect the command -response that was last notified by LookForResponseToCommand
				*
				* @see LookForResponseToCommand
				*/
				void StopLookingForResponse();


				/**
				* Informs toe processing que whether the DAL is in command-response mode or in capture mode.
				*/
				property bool CaptureMode
				{
					void set(bool mode);
				};

				/**
				*	Tells the processing thread that the data is available.
				* If the thread is sleeping it will wake the thread
				*/
				void SignalDataAvailable();

				/**
				* Clears the buffer.
				*/
				void EmptyBuffer();

			};

			


		}//namespace AtCor
	}//namespace Scor
}//namespace DataAccess