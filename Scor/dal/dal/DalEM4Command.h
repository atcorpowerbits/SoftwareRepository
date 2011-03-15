/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4Command.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  DalEM4Command, EM4DataCapturePacket
*/
#pragma once

#include "stdafx.h"
#include "DalCRC8Calculator.h"

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			/**
			* @class DalEM4Command
			* @brief Class to send EM4 command and recieve its response.
			*/
			private ref class DalEM4Command
			{
				// attirbutes which are visible inside DAL dll only
				internal:
					
					unsigned char commandSequenceNumber; /**< Sequence number of the command */
					unsigned char commandCRCByte; /**< CRC value*/
					unsigned int retryNumber;/**< retry attempt number*/

					array<unsigned char>^ em4Response; /**< array to store EM4 response packet*/
				
					array<unsigned char>^ em4Command; /**< array to store EM4 command packe*/
					unsigned int commandLength;	/**< length of the command excluding CRC*/
					
				public:
					unsigned char		commandCode; /**< Command code byte*/
					array<unsigned char>^ commandData; /**< command data*/

					unsigned int em4ResponsePacketLength; /**< EM4 response packet length. This may not be the same as em4ResponseLengthByte */
					unsigned int em4ResponseDataLength; /**< Response data part length*/
					unsigned char em4ResponseSequenceNumber; /**< response sequence byte */
					unsigned char em4ResponseCRCByte; /**< CRC value recived from EM4*/
					unsigned char em4ResponseAckNackByte; /**< Ack.Nack byte*/
					unsigned char em4ResponseLengthByte; /**< EM4 response length as recieved within the packet*/
					unsigned short em4StatusFlag; /**< status flag */
					array<unsigned char>^ em4ResponseData; /**< data packet recieved from the response packet */

					unsigned int timeoutPeriod; /**< timout period to wait for response. Default value is 50 ms*/
					unsigned int retriesAllowed; /**< Number of retries . Set to 3 by default*/

				private:
					DalEM4Command(); // Default C'tor

					~DalEM4Command(); // Default D'tor

					bool ConstuctCommand();

					//static unsigned char _sentPacketSequenceNumber;

				public:
					
					
					/**
					* Parametrised constructor to create an EM4 command
					* @param[in] inCommandCode	The command code byte. Cannot be null
					* @param[in] inCommandData	Additional data if necessary for the command. Can be null.
					*/
					DalEM4Command(Byte inCommandCode, array<Byte>^ inCommandData);

					/**
					* Breaks the EM4 response into various parts
					* @return @c true if the command was succesful
					*/
					bool BreakupEM4Response();

					/**
					* Extracts the data part of the EM4 response packet.
					* @return @c true if the command was succesful
					*/
					bool BreakResponseDataPart();
			};


			
		}
	}
}
