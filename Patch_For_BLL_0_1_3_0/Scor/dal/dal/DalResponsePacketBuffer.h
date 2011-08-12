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

			public ref class DalResponsePacketBuffer: public IDalPacketQueue 
			{
				private:

					array<unsigned char>^ waitingResponse;
					static Mutex^ _mutex = gcnew Mutex();

					DalResponsePacketBuffer();
					~DalResponsePacketBuffer();
					DalResponsePacketBuffer^ operator = (DalResponsePacketBuffer^); //privatized for singleton
					DalResponsePacketBuffer(DalResponsePacketBuffer^); //privatized for singleton


					static DalResponsePacketBuffer ^ _instance  = gcnew DalResponsePacketBuffer();

				public:
					static property DalResponsePacketBuffer^ Instance
					{
						DalResponsePacketBuffer^ get();
					}

					virtual array<unsigned char>^ Dequeue();
					virtual void Enqueue(array<unsigned char>^ packet);

					virtual void Clear();
			};

		}
	}
}
