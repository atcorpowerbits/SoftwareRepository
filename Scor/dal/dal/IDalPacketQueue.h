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


			private interface class IDalPacketQueue
			{
				public:
					array<unsigned char>^ Dequeue();
					void Enqueue(array<unsigned char>^ packet);
					void Clear();
			};

		}
	}
}