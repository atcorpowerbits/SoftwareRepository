/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalStreamingPacketQueue.h

     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalStreamingPacketQueue class.
*/

#pragma once

#include "stdafx.h"
#include "IDalPacketQueue.h"

using namespace System::Collections::Generic;
using namespace System::Threading; 


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class	DalStreamingPacketQueue
			* @brief	Implements a queue for streaming packets.
			*/
			public ref class DalStreamingPacketQueue: public IDalPacketQueue
			{
				private:
					DalStreamingPacketQueue(); //constructor
					~DalStreamingPacketQueue(); //destructor
					DalStreamingPacketQueue(DalStreamingPacketQueue^);//copyt constructor
					DalStreamingPacketQueue^ operator = (DalStreamingPacketQueue^); //overloaded assignment operator

					static DalStreamingPacketQueue^ _instance = gcnew DalStreamingPacketQueue(); //internal instance variable
 
					Queue<array<unsigned char>^> ^streamingPacketQueue; //A queue of pointers that point to the streaming packets
					
						
					//Removing mutex becuase it clashes with the [Synchronization] attribute of DalStagingQueue class
					//TODO: recheck effects of this
					//static Mutex^ _mutex = gcnew Mutex(); //mutex for access synchronization


				public:

					/**
					* Instance propoerty that returns a pointer to the singleton instance.
					*/
					static property DalStreamingPacketQueue^ Instance
					{
						/**
						* Returns a pointer the current instance.
						* @return Pointer to the singleton instance.
						*/
						DalStreamingPacketQueue^ get();
					};

					/**
					* Gets the topmost pakcet from the queue and removes it from the queue.
					*
					* @return	A byte array containing the data packet
					*/
					virtual array<unsigned char>^ Dequeue();
					
					
					/**
					* Adds the specified packet to the end of the queue
					*
					* @param[in]	packet	The packet to enqueue
					*/
					virtual void Enqueue(array<unsigned char>^ packet);

					/**
					* Empties the buffer and deletes all the contents.
					*/
					virtual void Clear();

					/**
					* Gets the number of packtes available in this array
					*
					* @return	The number of elements
					*/
					int Count();

			};


		}
	}
}