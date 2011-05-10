/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4DataCapturePacket.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      EM4DataCapturePacket class code
*/

#include "stdafx.h"
#include "DalEM4DataCapturePacket.h"
#include "DalCommon.h"
#include "DalCommandInterface.h"


using namespace System;
using namespace AtCor::Scor::CrossCutting;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{



			EM4DataCapturePacket::~EM4DataCapturePacket()
			{
				em4Response = nullptr;
				em4ResponseData = nullptr;
			}


			bool EM4DataCapturePacket::BreakupEM4Response()
			{
				try
				{
					if (nullptr == em4Response )
					{
						return false;
					}
					
					em4ResponseLengthByte = em4Response[(int)Em4ResponseByteIndex::ResponseLengthByte];

					if (em4ResponsePacketLength != em4ResponseLengthByte)
					{
						//there is a mismatch between the length as mentioned in the packet and as recieved.
						//Cannot continue any further
						return false;
					}

					em4ResponseAckNackByte = em4Response[(int)Em4ResponseByteIndex::AckNackByte ];
					
					em4ResponseSequenceNumber = em4Response[(int)Em4ResponseByteIndex::ResponseLengthByte]>>4;
					em4ResponseCRCByte = em4Response[(int)em4ResponseLengthByte];

					//get the status flag
					EM4StatusFlag flagUn;
					flagUn.ucStatusBytes[0] = em4Response[em4ResponseLengthByte - 1];
					flagUn.ucStatusBytes[1] = em4Response[em4ResponseLengthByte - 2];

					em4StatusFlag =  flagUn.ulStatusFlag ;

					//em4StatusFlag = DalCommandInterface::TranslateTwoBytes(em4Response, em4ResponseLengthByte - 2);

					return BreakResponseDataPart();

					
				}
				catch(ScorException ^ )
				{
					throw;
				}
				catch(Exception ^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
			}


			EM4DataCapturePacket::EM4DataCapturePacket(unsigned int dataLength)
			{
				try
				{
					//empty constructor does noting
					em4Response = gcnew array<unsigned char> (DalConstants::EM4ZeroDataResponsePacketSize + dataLength + 1); //+1 for CRC byte 
					
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
					//em4ResponseAckNackByte = 0x00; //FxCop
					em4ResponseLengthByte = 0x00;
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
			}

			bool EM4DataCapturePacket::BreakResponseDataPart()
			{
				try
				{
					//sepearte the data packet and also its length
					if (em4ResponsePacketLength == DalConstants::EM4ZeroDataResponsePacketSize)
					{
						// packet is valid but does not contain data
						em4ResponseDataLength = 0;
						em4ResponseData = nullptr;
					}
					else if (em4ResponsePacketLength < DalConstants::EM4ZeroDataResponsePacketSize)
					{
						// invalid packet from EM4
						return false;
					}
					else 
					{
						// packet len greater than 5, means valid packet with data
						em4ResponseDataLength = em4ResponsePacketLength - DalConstants::EM4ZeroDataResponsePacketSize;
						em4ResponseData = gcnew array<unsigned char> (em4ResponseDataLength);
						em4Response->Copy(em4Response, (int)Em4ResponseByteIndex::DataChunkFirstByte , em4ResponseData, 0,  em4ResponseDataLength);
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