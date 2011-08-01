/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalResponsePacketQueue.h

     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalResponsePacketQueue class.
*/

#pragma once

#include "stdafx.h"
#include "IDalPacketQueue.h"

using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			public ref class DalResponsePacketQueue: public IDalPacketQueue 
			{
				private:

					array<unsigned char>^ waitingResponse;
					static Mutex^ _mutex = gcnew Mutex();

					DalResponsePacketQueue();
					~DalResponsePacketQueue();
					DalResponsePacketQueue^ operator = (DalResponsePacketQueue^); //privatized for singleton
					DalResponsePacketQueue(DalResponsePacketQueue^); //privatized for singleton


					static DalResponsePacketQueue ^ _instance  = gcnew DalResponsePacketQueue();

				public:
					static property DalResponsePacketQueue^ Instance
					{
						DalResponsePacketQueue^ get();
					}

					virtual array<unsigned char>^ Dequeue();
					virtual void Enqueue(array<unsigned char>^ packet);

					virtual void Clear();
			};

		}
	}
}
