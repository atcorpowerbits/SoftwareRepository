/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      IDalPacketQueue.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Interface file header for IDalPacketQueue class.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @interface IDalPacketQueue
			* @brief Interface specification for classes which implement an EM4 packet queue.
			*
			* @see DalStreamingPacketQueue, DalResponsePacketBuffer
			*/
			private interface class IDalPacketQueue
			{
				public:
					/**
					* Gets the topmost pakcet from the queue and removes it from the queue.
					*
					* @return	A byte array containing the data packet
					*/
					array<unsigned char>^ Dequeue();

					/**
					* Adds the specified packet to the end of the queue
					*
					* @param[in]	packet	The packet to enqueue
					*/
					void Enqueue(array<unsigned char>^ packet);

					/**
					* Empties the buffer and deletes all the contents.
					*/
					void Clear();
			};

		}
	}
}