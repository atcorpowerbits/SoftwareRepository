/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEm4Command.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      CRC8Calculator, DalEM4Command, EM4DataCapturePacket class code
*/

#include "stdafx.h"
#include "DalEM4Command.h"
#include "DalCommon.h"
#include "DalCommandInterface.h"


using namespace System;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging ;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

	

					

			DalEM4Command::DalEM4Command()
			{
				em4Command = nullptr;
				commandLength = 0;
				commandSequenceNumber = 0; 
				commandCRCByte = 0x00;
				em4Response =  nullptr;
				timeoutPeriod = DalConstants::EM4ResponseTimeout; //in miliseconds . 
				retriesAllowed = DalConstants::EM4NumberofRetires; //three times.
				retryNumber = 0;
			}

			DalEM4Command::DalEM4Command(Byte inCommandCode, array<Byte>^ inCommandData)
			{
				this->em4Command = nullptr;
				this->commandCode = inCommandCode;
				this->commandSequenceNumber = DalCommandInterface::SentPacketSequenceNumber ; //get the seqence number for the next packet

				if (inCommandData != nullptr)
				{
					try
					{
						this->commandData = (array<unsigned char>^)inCommandData->Clone();
					}
					catch(Exception^ excepObj)
					{
						throw gcnew ScorException(excepObj);
					}
					commandLength = commandData->Length + 3; //code+ length+ sequence = 3 CRC excluded from command length
				}
				else
				{
					commandLength = 3; //code+ length+ sequence = 3 CRC excluded from command length
				}
									
				commandCRCByte = 0x00;
				em4Response =  nullptr;
				timeoutPeriod = DalConstants::EM4ResponseTimeout ; //in miliseconds . Pick from a global value 
				retriesAllowed = DalConstants::EM4NumberofRetires ; //three times. make this global 
				retryNumber = 0;

				if (!this->ConstuctCommand())
				{
					throw gcnew ScorException(1023, "DAL_ERR_COMMD_PACKET_CREATE_FAIL", ErrorSeverity::Exception);
				}
			}

			DalEM4Command::~DalEM4Command()
			{
				em4Command = nullptr;
				commandCode = 0x00;
				commandLength = 0;
				commandSequenceNumber = 0; 
				commandCRCByte = 0x00;
				em4Response =  nullptr;
				timeoutPeriod = 0; 
				retriesAllowed = 0; 
			}

			bool DalEM4Command::ConstuctCommand()
			{
				try
				{
					// Additional byte is needed for CRC byte
					em4Command = gcnew array<unsigned char>(commandLength+1);
				
					em4Command[0] = commandCode; //byte1 = command code
					em4Command[1] = commandLength ; //byte 2 length
					em4Command[2] = this->commandSequenceNumber ; //byte 3 seq#

					// do not copy command is commandData is null
					if (commandData)
					{
						//byte4 onwards copy the data
						commandData->CopyTo(em4Command, 3);
					}
					
					//generate the CRC
					CRC8Calculator ^ crcCalculator = CRC8Calculator::Instance;
					
					unsigned char generatedCRCValue = 0x00;

					crcCalculator->ComputeCrc8ForArray(em4Command, commandLength, &generatedCRCValue);
					commandCRCByte = generatedCRCValue;

					//last byte copy crc
					em4Command[commandLength] = commandCRCByte;

					return true; //if everything is fine 

				}
				catch(Exception ^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
			}

			bool DalEM4Command::BreakupEM4Response()
			{
				try
				{
					if (nullptr == em4Response)
					{
						return false;
					}
					
					// second element is lenght of the response 
					em4ResponseLengthByte = em4Response[1];

					if (em4ResponsePacketLength != em4ResponseLengthByte)
					{
						//there is a mismatch between the length as mentioned in the packet and as recieved.
						//Cannot continue any further
						return false;
					}

					em4ResponseAckNackByte = em4Response[0];
					
					em4ResponseSequenceNumber = em4Response[2]>>4;

					em4ResponseCRCByte = em4Response[(int)em4ResponseLengthByte];

					//get the status flag
					EM44StatusFlag flagUn;
					flagUn.ucStatusBytes[0] = em4Response[em4ResponseLengthByte - 1];
					flagUn.ucStatusBytes[1] = em4Response[em4ResponseLengthByte - 2];

					em4StatusFlag =  flagUn.ulStatusFlag ;

					//sepearte the data packet and also its length
					return BreakResponseDataPart();
				}
				catch(Exception^ excepObj)
				{
					//CrxLogger::Instance->Write("Inside DALEM4Command::BreakupResponse()");
					throw gcnew ScorException(1016, "DAL_ERR_RESPONSE_INVALID", ErrorSeverity::Exception );
				}
			}

			bool DalEM4Command::BreakResponseDataPart()
			{
				try
				{
					//sepearte the data packet and also its length
					if (em4ResponsePacketLength == 5)
					{
						// packet is valid but does not contain data
						em4ResponseDataLength = 0;
						em4ResponseData = nullptr;
					}
					else if (em4ResponsePacketLength < 5)
					{
						// invalid packet from EM4
						return false;
					}
					else 
					{
						// packet length greater than 5, means valid packet with data
						em4ResponseDataLength = em4ResponsePacketLength - 5;
						em4ResponseData = gcnew array<unsigned char> (em4ResponseDataLength);
						em4Response->Copy(em4Response, 3 , em4ResponseData, 0,  em4ResponseDataLength);
					}
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				return true;
			}


		}
	}
}