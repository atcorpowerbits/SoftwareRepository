/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalResponsePacketBuffer.h

     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalResponsePacketBuffer class.
*/

#pragma once

#include "stdafx.h"
#include "IDalPacketQueue.h"

using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalResponsePacketBuffer
			* @brief	Stores the responses to EM4 commands.
			*/
			public ref class DalResponsePacketBuffer: public IDalPacketQueue 
			{
				private:

					array<unsigned char>^ waitingResponse; //a pointer to the currently stored response packet
					static Mutex^ _mutex = gcnew Mutex(); //mutex to sychronize acces to the waitingResponse.

					DalResponsePacketBuffer(); //Constructor
					~DalResponsePacketBuffer(); //Destructor
					DalResponsePacketBuffer^ operator = (DalResponsePacketBuffer^); //privatized for singleton
					DalResponsePacketBuffer(DalResponsePacketBuffer^); //privatized for singleton


					static DalResponsePacketBuffer ^ _instance  = gcnew DalResponsePacketBuffer(); //instance variable for singleton

				public:

					/**
					* Singleton instance of this class.
					* Returns a pointer to this instance
					*/
					static property DalResponsePacketBuffer^ Instance
					{
						/**
						* Returns a pointer to the current instance.
						* @return	The current instance.
						*/
						DalResponsePacketBuffer^ get();
					}

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
			};

		}
	}
}
