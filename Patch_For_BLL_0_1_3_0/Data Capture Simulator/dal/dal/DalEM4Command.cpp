/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEm4Command.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      CRC8Calculator, DalEM4Command, EM4DataCapturePacket class code
*/

#include "stdafx.h"
#include "DalEM4Command.h"
#include "DalCommon.h"


using namespace System;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			CRC8Calculator::CRC8Calculator()
			{
				int i, j;
				unsigned char crc;

				try
				{

					for (i=0; i<256; i++) 
					{
						crc = i;
						for (j=0; j<8; j++)
						{
							crc = (crc << 1) ^ ((crc & 0x80) ? 0x07 : 0);
						}
						crc8Table[i] = crc & 0xFF;
					}
				}
				catch(Exception^ )
				{
					throw gcnew ScorException(1009, "DAL_ERR_CRC_TABLE_FAILED", ErrorSeverity::Exception);
				}
			}

			void CRC8Calculator::Crc8forNextByte(unsigned char* currentCrc, const unsigned char nextByte)
			{
				*currentCrc = crc8Table[(*currentCrc)^nextByte];
				*currentCrc &= 0xFF;
			}

			bool CRC8Calculator::ComputeCrc8ForArray(array<unsigned char>^ commandArray, const unsigned int arrayLength, unsigned char* crc8ForArray)
			{

				unsigned char crcValue = 0x00;

				try
				{
					for (unsigned int i = 0; i < arrayLength; i++)
					{
						Crc8forNextByte(&crcValue, commandArray[i]);
					}
				}
				catch(Exception^)
				{
					throw gcnew ScorException(1010, "DAL_ERR_CRC_CALC_FAILED", ErrorSeverity::Exception);
				}

				*crc8ForArray = crcValue;

				return true;
			}
					
			CRC8Calculator^ CRC8Calculator::operator= (const CRC8Calculator)
			{
				return this;
			}
					

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
				}
				catch(Exception ^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				
				em4Command[0] = commandCode; //byte1 = command code
				em4Command[1] = commandLength ; //byte 2 length
				//em4Command[2] = SentPacketSequenceNumber; //byte 3 seq#108
				em4Command[2] = DataCapturePacketSequenceNumber ; //byte 3 seq#108 //for data caputre simulation


				// do not copy command is commandData is null
				if (commandData)
				{
						try
						{
							//byte4 onwards copy the data
							commandData->CopyTo(em4Command, 3);
						}
						catch(Exception ^ excepObj)
						{
							throw gcnew ScorException(excepObj);
						}
				}
				
				//generate the CRC
				CRC8Calculator ^ crcCalculator = CRC8Calculator::Instance ;
				
				unsigned char generatedCRCValue = 0x00;

				crcCalculator->ComputeCrc8ForArray(em4Command, commandLength, &generatedCRCValue);
				commandCRCByte = generatedCRCValue;

				//last byte copy crc
				em4Command[commandLength] = commandCRCByte;

				return true; //if everything is fine 
			}

			bool DalEM4Command::BreakupEM4Response()
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
					// packet len greater than 5, means valid packet with data
					em4ResponseDataLength = em4ResponsePacketLength - 5;
					em4ResponseData = gcnew array<unsigned char> (em4ResponseDataLength);
					em4Response->Copy(em4Response, 3 , em4ResponseData, 0,  em4ResponseDataLength);
				}

				return true;
			}


			EM4DataCapturePacket::~EM4DataCapturePacket()
			{
				em4Response = nullptr;
				em4ResponseData = nullptr;
			}


			bool EM4DataCapturePacket::BreakupEM4Response()
			{
				if (nullptr == em4Response )
				{
					return false;
				}
				
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
				if (em4ResponsePacketLength == 5)
				{
					em4ResponseDataLength = 0;
					em4ResponseData = nullptr;
				}
				else if (em4ResponsePacketLength < 5)
				{
					return false;
				}
				else 
				{
					em4ResponseDataLength = em4ResponsePacketLength -5;
					em4ResponseData = gcnew array<unsigned char> (em4ResponseDataLength);
					em4Response->Copy(em4Response, 3 , em4ResponseData, 0,  em4ResponseDataLength);
				}
				return true;
			}

			DalEM4Command::DalEM4Command(array<unsigned char>^ sourcePCCommandArray)
			{

				if (nullptr == sourcePCCommandArray )
				{
					throw gcnew ScorException(111, "DAL_ERR_COMMD_PACKET_CREATE_FAIL", ErrorSeverity::Exception );
				}
				
				int sourceArrayLength  = sourcePCCommandArray->Length;
				if (sourceArrayLength <4)
				{
					throw gcnew ScorException(111, "DAL_ERR_COMMD_PACKET_CREATE_FAIL", ErrorSeverity::Exception );
				}
				
				try
				{

					//get all values except command data
					this->em4Command = (array<unsigned char>^)sourcePCCommandArray->Clone();
					this->commandCode = sourcePCCommandArray[0];
					this->commandLength =  sourcePCCommandArray[1];
					this->commandSequenceNumber = sourcePCCommandArray[2];
					this->commandCRCByte = sourcePCCommandArray[sourcePCCommandArray->Length -1];
					
					
					if (sourceArrayLength >4)
					{
						//there is data
						int dataLength  = sourceArrayLength - 4;
						this->commandData = gcnew array<unsigned char> (dataLength);
						sourcePCCommandArray->Copy(sourcePCCommandArray, 3, this->commandData, 0, dataLength ); 
					}
					else
					{
						this->commandData = nullptr;
					}
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

			}



			EM4DataCapturePacket::EM4DataCapturePacket(unsigned int dataLength)
			{
				//empty constructor does noting
				em4Response = gcnew array<unsigned char> (DalConstants::EM4ZeroDataResponsePacketSize + dataLength); 
				
				if (0 == dataLength)
				{
					em4ResponseData = nullptr; //UT fix
				}
				else
				{
					em4ResponseData = gcnew array<unsigned char> (dataLength);
				}

				em4ResponseDataLength = 0;
				em4ResponseSequenceNumber = 0x00;
				em4StatusFlag = 0x0000;
				em4ResponseCRCByte = 0x00;
				em4ResponseAckNackByte = 0x00;
				em4ResponseLengthByte = 0x00;
			}

			bool DalEM4Command::ValidateCommandCRC()
			{
				bool returnValue;
				//generate the CRC
				CRC8Calculator ^ crcCalculator = CRC8Calculator::Instance;
				unsigned char generatedCRCValue = 0x00;
				unsigned char recivedCRCValue = this->commandCRCByte ;
				returnValue= crcCalculator->ComputeCrc8ForArray(this->em4Command , this->commandLength , &generatedCRCValue);

				 if (false == returnValue)
				 {
					 throw gcnew ScorException(111, "DAL_ERR_CRC_GEN_FAILED", ErrorSeverity::Exception );
				 }
				 else if (generatedCRCValue != recivedCRCValue)
				 {
					return false;
				 }
				 else
				 {
					 return true;
				 }
			}

			DalEM4Command::DalEM4Command(unsigned char inCommandCode, unsigned char seqNo, cli::array<unsigned char,1> ^inCommandData, unsigned short statusBytes)
			{
				this->em4Command = nullptr;
				this->commandCode = inCommandCode;
				this->commandSequenceNumber = seqNo;
				int inCommandDataLength ;
				int totalDataLength ; //2 for satstus bytes;
				
				if (inCommandData)
				{
					inCommandDataLength = inCommandData->Length;
				}
				else
				{
					inCommandDataLength = 0;
				}
				totalDataLength = inCommandDataLength + 2; //2 for satstus bytes;

			
				try
				{
					array<unsigned char>^ dataPlusStatus = gcnew array<unsigned char> (totalDataLength); 

					if (inCommandData)
					{
						//then copy data
						inCommandData->Copy(inCommandData, 0, dataPlusStatus, 0, inCommandDataLength);
					}

					//then copy status bytes
					TranslateUnsignedShort(dataPlusStatus, totalDataLength - 2, (unsigned short)statusBytes);

					this->commandData = (array<unsigned char>^)dataPlusStatus->Clone();
					this->commandLength = totalDataLength + 3;

					commandCRCByte = 0x00;
					em4Response =  nullptr;
					timeoutPeriod = 1000; //in miliseconds . Pick from a global value 
					retriesAllowed = 1; //three times. make this global 

					
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}

				//the rest of the stuff is from constructCommand
				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
				try
				{
					// Additional byte is needed for CRC byte
					em4Command = gcnew array<unsigned char>(commandLength+1);
				}
				catch(Exception ^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				
				em4Command[0] = commandCode; //byte1 = command code
				em4Command[1] = commandLength ; //byte 2 length
				em4Command[2] = this->commandSequenceNumber ; //byte 3 

				// do not copy command is commandData is null
				if (commandData)
				{
						try
						{
							//byte4 onwards copy the data
							commandData->CopyTo(em4Command, 3);
						}
						catch(Exception ^ excepObj)
						{
							throw gcnew ScorException(excepObj);
						}
				}
				
				//generate the CRC
				CRC8Calculator ^ crcCalculator = CRC8Calculator::Instance;
				
				unsigned char generatedCRCValue = 0x00;

				crcCalculator->ComputeCrc8ForArray(em4Command, commandLength, &generatedCRCValue);
				commandCRCByte = generatedCRCValue;

				//last byte copy crc
				em4Command[commandLength] = commandCRCByte;
				
			}


			bool DalEM4Command::TranslateUnsignedShort( array <unsigned char>^ destinationArray, int startPostion, unsigned short sourceUS)
			{
				//get the status flag
				EM44StatusFlag flagUn;

				try
				{

					flagUn.ulStatusFlag = sourceUS;
					destinationArray[startPostion] = flagUn.ucStatusBytes[1]; 
					destinationArray[startPostion + 1] = flagUn.ucStatusBytes[0];
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