/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSequenceNumberManager.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Source file for classes: DalSequenceNumberManager
*/

#include "stdafx.h"
#include "DalSequenceNumberManager.h"
#include "DalCommon.h"

using namespace System;

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting::Logging;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			DalSequenceNumberManager::DalSequenceNumberManager()
			{
				_nextCommandSequenceNumber = _packetSequenceMinValue;
				//reserveSequenceNumberForCapture = false; //FxCop
				reservedCommandSequenceNumber = _reservedNumberInvalidIndicator; //for safety
				_nextStreamingPacketSequnceNumber = _packetSequenceMinValue;

			}

		
			bool DalSequenceNumberManager::ValidateCommandResponseSequenceNumber( const unsigned char commandSequenceNumber, const unsigned char responseSequenceNumber)
			{
				//the two numbers should match
				if (commandSequenceNumber == responseSequenceNumber)
				{
					return true;
				}
				else
				{
					return false;
				}
			}

			bool DalSequenceNumberManager::CheckStreamingSequenceNumber(const unsigned char streamingPacketSequenceNumber)
			{
				//the parameter should match the expected sequence number
				if (streamingPacketSequenceNumber == _nextStreamingPacketSequnceNumber)
				{
					//numbers match
					_nextStreamingPacketSequnceNumber++; //increment for the next expected seqence

					//roll over to 0x00 if the number was 0xFF
					if (_nextStreamingPacketSequnceNumber > _packetSequenceMaxValue)
					{
						_nextStreamingPacketSequnceNumber = _packetSequenceMinValue;
					}
					return true;
				}
				else
				{
					//CrxLogger::Instance->Write("DAL>>> ValidateStreamingSequenceNumber Failed at : " + streamingPacketSequenceNumber.ToString(DalFormatterStrings::PrintByte ), ErrorSeverity::Debug);
					//return false in case of no mathc
					return false;
				}
			}

			void DalSequenceNumberManager::ResetCommandSequenceNumber()
			{
				//clear the value of the expected number and set to 0x00
				_nextCommandSequenceNumber = _packetSequenceMinValue;
			}

			void DalSequenceNumberManager::ResetStreamingSequenceNumber()
			{
				//clear the value of the expected number and set to 0x00
				_nextStreamingPacketSequnceNumber = _packetSequenceMinValue;
			}

			void DalSequenceNumberManager::ReserveCommandNumberDuringStreaming(unsigned char captureCommandSequenceNumber)
			{
				reserveSequenceNumberForCapture = true; //set test flag to true
				//set the reserved number
				reservedCommandSequenceNumber = captureCommandSequenceNumber;
				
			}

			void DalSequenceNumberManager::ReleaseReservedCommandNumber()
			{
				reserveSequenceNumberForCapture = false; //reset indicator
				//set the number to an invalid number to "clear" it
				reservedCommandSequenceNumber = _reservedNumberInvalidIndicator;
			}

			unsigned char DalSequenceNumberManager::NextCommandSequenceNumber::get()
			{
				unsigned char returnValue;

				//first check if a number is reserved
				if ((_nextCommandSequenceNumber == reservedCommandSequenceNumber) && (reserveSequenceNumberForCapture))
				{
					//if yes then send it the next number in order
					_nextCommandSequenceNumber++;
					if (_nextCommandSequenceNumber > _packetSequenceMaxValue)
					{
						//check for rollover
						_nextCommandSequenceNumber = _packetSequenceMinValue;
					}
				}
							
				//set the number to the expected number
				returnValue = _nextCommandSequenceNumber++;
				
				if (_nextCommandSequenceNumber > _packetSequenceMaxValue)
				{
					//check for rollover
					_nextCommandSequenceNumber = _packetSequenceMinValue;
				}
				
				return returnValue;

			}

			unsigned char DalSequenceNumberManager::ExtractStreamingSequenceNumber(const unsigned char streamingPacketSequenceNumber)
			{
				//shift the number to the right by 4 bits this will remove the command code and also set the number between 0 and 0xF

				return streamingPacketSequenceNumber>>DalConstants::RightShiftOneNibble;
			}

			bool DalSequenceNumberManager::ValidateStreamingSequenceNumber(const unsigned char streamingPacketSequenceNumber)
			{
				//CrxLogger::Instance->Write("DAL>>> ValidateStreamingSequenceNumber : " + streamingPacketSequenceNumber.ToString(DalFormatterStrings::PrintByte), ErrorSeverity::Debug);
				//first extract the number
				unsigned char shiftedNumber = ExtractStreamingSequenceNumber(streamingPacketSequenceNumber);

				//next check if it is valid in sequence.
				return CheckStreamingSequenceNumber(shiftedNumber);
			}

			//couldnt get this to work. Keeping for later - Deepak
			//void DalSequenceNumberManager::IncrementWithRollover(unsigned char ^%numberToIncrement)
			//{
			//	(*numberToIncrement)++;

			//	if (*numberToIncrement > _packetSequenceMaxValue)
			//	{
			//		//check for rollover
			//		*numberToIncrement = _packetSequenceMinValue;
			//	}
			//}
					



		} //End Namespace DataAccess
	}
}
