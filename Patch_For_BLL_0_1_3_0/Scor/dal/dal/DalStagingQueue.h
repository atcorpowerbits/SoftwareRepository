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

				DalPacketType DeterminePacketType(unsigned char commandCodeByte);

				array <unsigned char>^ ExtractStreamingDataPacket();
				array <unsigned char>^ ExtractAckedResponsePakcet();
				array <unsigned char>^ ExtractNackedResponsePacket();
				
				
				void ProcessQueue();

				DalStagingQueue();
				~DalStagingQueue();
				DalStagingQueue^ operator= (DalStagingQueue^);
				array <unsigned char>^ DequeueArray(int numberOfBytes);

				bool ProcessSinglePacket();

				//A delegate to call using begininvoke. Should have the same signature as the method being called
				//Since we are using it within this class itself it has been defined as a class member and not outside.
				 delegate void ProcessQueueAsyncCaller();

				 //Delegate to call the read method in case of an underflow
				 delegate void AttemptUnderFlowReadCaller();

				//ProcessQueueAsyncCaller^ _processQueueAsyncCaller;

				//AttemptUnderFlowReadCaller^ _attemptUnderFlowReadCaller;

				bool _captureMode;

				void PartiallyClearBuffer();

				Thread^ dataProcessingThread;

				void ProcessingThreadMethod();
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

				void EnqueueArray(array <unsigned char>^ sourceArray);

				void LookForResponseToCommand( 
												unsigned char commandCodeToLocate,
												unsigned char expectedResponseLengthToLocate, //should be same as Em4ResponseRequiredLength enum
												unsigned char expectedSequenceNumberToLocate
												);

				void StopLookingForResponse();


				property bool CaptureMode
				{
					void set(bool mode);
				};

				void SignalDataAvailable();

				void EmptyBuffer();

			};

			


		}//namespace AtCor
	}//namespace Scor
}//namespace DataAccess