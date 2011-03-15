/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4DataCapturePacket.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  EM4DataCapturePacket
*/
#pragma once

#include "stdafx.h"
#include "DalCRC8Calculator.h"

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class EM4DataCapturePacket
			* @brief Class to recive EM4 capture data.
			*/
			private ref class EM4DataCapturePacket
			{
				internal:
					array<unsigned char>^ em4Response;	/**< array to store EM4 command packe*/
					unsigned int em4ResponsePacketLength; /**< EM4 response packet length. This may not be the same as em4ResponseLengthByte */
					unsigned int em4ResponseDataLength; /**< Response data part length*/
					unsigned char em4ResponseSequenceNumber; /**< response sequence byte */

					unsigned short em4StatusFlag; /**< status flag recieved*/
					unsigned char em4ResponseCRCByte; /**< CRC value recived from EM4*/
					unsigned char em4ResponseAckNackByte; /**< Ack.Nack byte*/
					unsigned char em4ResponseLengthByte; /**< EM4 response length as recieved within the packet*/
					array<unsigned char>^ em4ResponseData; /**< data packet recieved from the response packet */

				private:
					~EM4DataCapturePacket();

				public:
					/**
					* Breaks the EM4 response into its individual components and stores it in the EM4DataCapturePacket structure
					* @return @c true if the command was succesful
					*/
					bool BreakupEM4Response();

					/**
					* Constructor to create a capture packet of variable data length
					* @param[in]	dataLength	The length of the data expected from EM4. can be zero for no data
					*/
					EM4DataCapturePacket(unsigned int dataLength);

					/**
					* Breaks the EM4 response packet and extracts the data part.
					* @return @c true if the command was succesful
					*/
					bool BreakResponseDataPart();

			};
			
		}
	}
}
