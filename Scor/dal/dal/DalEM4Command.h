/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4Command.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  DalEM4Command, EM4DataCapturePacket, CRC8Calculator
*/
#pragma once

#include "stdafx.h"

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

					static unsigned char _sentPacketSequenceNumber;

				public:
					/**
					* Property to obtain the a sequence number for the EM4 command 
					* Starts from 0x00 to 0x0F and rolls over.
					*/
					property unsigned char SentPacketSequenceNumber
					{
						unsigned char get()
						{
							unsigned char returnValue;
							
							returnValue = _sentPacketSequenceNumber++;
							if (_sentPacketSequenceNumber >0x0F)
							{
								_sentPacketSequenceNumber = 0x00;
							}
							
							return returnValue;
						};
					};
					
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
			};

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
			};

			
			/**
			* @class CRC8Calculator
			* @brief Class to calculate 8 bit CRC value 
			*/
			private ref class CRC8Calculator
			{
				private:
					static array<unsigned char>^ crc8Table = gcnew array<unsigned char>(256); // Default size of array
					static bool TableReady = false;

				public:
					/**
					* Constructor for the class. @n
					* Initializes the CRC8 table
					*/
					CRC8Calculator();

					/**
					* Computes the CRC value for the byte and adds it to the existing CRC value for the array
					* @param[in,out] currentCrc	The crc value of the array. Will beupdated with the addition of the neext byte.
					* @param[in]	nextByte	The next byte in the array to add the crc value for
					*/
					void inline Crc8forNextByte(unsigned char* currentCrc, const unsigned char nextByte);

					/**
					* Computes the CRC value for the array
					* @param[in] commandArray	The array for whcioh CRC8 is to be calculated
					* @param[in]	arrayLength	Length of the array
					* @param[out]	crc8ForArray	The computed CRC8 value for the array
					* @return		boolean value indicating the status of the operation.
					*/
					bool ComputeCrc8ForArray( array<unsigned char>^ commandArray, const unsigned int arrayLength, unsigned char* crc8ForArray); 
			};
		}
	}
}
