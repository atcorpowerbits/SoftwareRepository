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

			public ref class DalStreamingPacketQueue: public IDalPacketQueue
			{
				private:
					DalStreamingPacketQueue();
					~DalStreamingPacketQueue();
					DalStreamingPacketQueue(DalStreamingPacketQueue^);
					DalStreamingPacketQueue^ operator = (DalStreamingPacketQueue^);

					static DalStreamingPacketQueue^ _instance = gcnew DalStreamingPacketQueue();

					Queue<array<unsigned char>^> ^streamingPacketQueue;
					static Mutex^ _mutex = gcnew Mutex();


				public:

					static property DalStreamingPacketQueue^ Instance
					{
						DalStreamingPacketQueue^ get();
					};

					virtual array<unsigned char>^ Dequeue();
					virtual void Enqueue(array<unsigned char>^ packet);

					virtual void Clear();
					int Count();

			};


		}
	}
}