/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCRC8Calculator.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      CRC8Calculator class code
*/

#include "stdafx.h"
#include "DalCRC8Calculator.h"


using namespace System;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			CRC8Calculator::CRC8Calculator()
			{
				int j;
				unsigned char i;
				unsigned char crc;

				try
				{
					//these consttants are used only in ths method 
					//so we are not moving it to an enum
					for (i=0; i < DalConstants::CRCTableSize; i++) 
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
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCrcTableFailedErrCd, CrxStructCommonResourceMsg::DalErrCrcTableFailed, ErrorSeverity::Exception);
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
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrCrcCalcFailedErrCd, CrxStructCommonResourceMsg::DalErrCrcCalcFailed, ErrorSeverity::Exception);
				}

				*crc8ForArray = crcValue;

				return true;
			}

		}//ENd DataAccess
	}
}
