/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSequenceNumberManager.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes: DalSequenceNumberManager
*/


#pragma once

#include "stdafx.h"

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalSequenceNumberManager
			* @brief Handles all Sequence number related tasks
			*/
			private ref class DalSequenceNumberManager sealed
			{
				private:
					static const unsigned char _packetSequenceMaxValue = 0x0F; //Min value for the sequence number
					static const unsigned char _packetSequenceMinValue = 0x00; //Max value for sequence number
					static const unsigned char _reservedNumberInvalidIndicator = 0xFF; //to make the reservedCommandSequenceNumber "invalid"
					
					static bool reserveSequenceNumberForCapture; //indicator to indicate that a number has been reserved for capture
					static unsigned char _nextCommandSequenceNumber; //stores the internal value of the command sequence numer 
					static unsigned char reservedCommandSequenceNumber ; //stores the sequence number of the comand that cannot be used when a capture is in progress
					static unsigned char _nextStreamingPacketSequnceNumber; //the next expected sequnce number of a streaming packet.

					DalSequenceNumberManager(); //make constructor private so that it cannot be called

					/**
					* Checks if streaming packet number is in the correct sequence 
					* @param	streamingPacketSequenceNumber	The extracted sequence number of the packet being validated.
					*											This number must be right shifted first using ExtractStreamingSequenceNumber()
					* @return	false if this sequence number was not the expected number
					*
					* @see ExtractStreamingSequenceNumber()
					*/
					static bool CheckStreamingSequenceNumber(const unsigned char streamingPacketSequenceNumber);

					/**
					* Converts the sequence number by removing the comand code and right shifting the EM4's niblle
					* @param	streamingPacketSequenceNumber	The sequence number of the packet being validated.
					* @return	The extracted sequence number
					*
					* @see ExtractStreamingSequenceNumber()
					*/
					static unsigned char ExtractStreamingSequenceNumber(const unsigned char streamingPacketSequenceNumber);

					//static void IncrementWithRollover(unsigned char ^%numberToIncrement);

				internal:
					
					/**
					* Property to obtain the a sequence number for the EM4 command 
					* Starts from 0x00 to 0x0F and rolls over.
					*/
					static property unsigned char NextCommandSequenceNumber
					{
						/**
						* Returns the sequence number that is used to initialize the next Em4 command
						*
						* @return sequence number.
						*/
						unsigned char get();
						
					};

					/**
					* Checks if command and response sequence numbers are identical
					*
					* @param	commandSequenceNumber	Sequence number of the EM4 command sent.
					* @param	responseSequenceNumber	Sequence number of the EM4 repsonse recived by DAL.
					*
					* @return	false if the sequence numbers dont match
					*/
					static bool ValidateCommandResponseSequenceNumber( const unsigned char commandSequenceNumber, const unsigned char responseSequenceNumber);

					/**
					* Checks if streaming packet sequence number is correct
					*
					* @param	streamingPacketSequenceNumber	Sequence number of the EM4 command sent.
					*
					* @return	false if the sequence numbers dont match
					*/
					static bool ValidateStreamingSequenceNumber(const unsigned char streamingPacketSequenceNumber);
					
					/**
					* Resets the next command sequence number to min.
					*/
					static void ResetCommandSequenceNumber();

					/**
					* Resets the next streaming packet expected sequence number to min.
					*/
					static void ResetStreamingSequenceNumber();

					/**
					* Blocks a sequence number for command comands 
					* This should be called after a Start streaming operation is successful so that this seqeunce
					* Number will not be used again until the capture is completed.
					*
					* @param	captureCommandSequenceNumber	Sequence number of the successful Start Streaming command
					*
					*/
					static void ReserveCommandNumberDuringStreaming(unsigned char captureCommandSequenceNumber);

					/**
					* Frees up the number resperved for capture by ReserveCommandNumberDuringStreaming().
					*/
					static void ReleaseReservedCommandNumber();
			};


					} //End Namespace DataAccess
	}
}
