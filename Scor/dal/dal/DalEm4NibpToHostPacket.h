/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4NibpToHostPacket.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  DalEM4NibpToHostPacket
*/

#pragma once

#include "stdafx.h"
#include "DalEM4DataCapturePacket.h"

using namespace System;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalEM4NibpToHostPacket: public EM4DataCapturePacket
			{
				private:
					DalEM4NibpToHostPacket(); //private. do not allow default object creation

				public:
					DalEM4NibpToHostPacket(array<unsigned char> ^ byteArray);

					DalReturnValue ValidatePacket();

					bool ValidateResponseCRC();




			};


		} //End namespace DataAccess
	}
}

