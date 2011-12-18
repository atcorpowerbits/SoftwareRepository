/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4NibpToHostPacket.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  DalEM4NibpToHostPacket
*/

#pragma once

#include "stdafx.h"
#include "DalEM4DataCapturePacket.h"
#include "DalNibpStatusHandler.h"

using namespace System;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalEM4NibpToHostPacket
			* @brief	This class defines the basic operations for all NIBP commands
			*/
			private ref class DalEM4NibpToHostPacket: public EM4DataCapturePacket
			{
				private:
					DalEM4NibpToHostPacket(); //private. do not allow default object creation
					DalNibpStatusHandler ^ _statusHandler;
					~DalEM4NibpToHostPacket();

				internal:
					/**
					* Constructor: intializes a command with the specifed array
					* @param[in]	byteArray	The NIBP command
					*/
					DalEM4NibpToHostPacket(array<unsigned char> ^ byteArray);

					/**
					* Validates a recieved EM4 NIBP response
					* @return The validation status
					*/
					DalReturnValue ValidatePacket();

					/**
					* Vlaidates the CRC of the encapsulating EM4 command
					* @return @c true if the CRC is valid.
					*/
					bool ValidateResponseCRC();
					void SetStatusHandler(DalNibpStatusHandler ^ newStatusHandler);




			};


		} //End namespace DataAccess
	}
}

