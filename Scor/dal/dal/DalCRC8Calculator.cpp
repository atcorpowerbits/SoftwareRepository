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

		}//ENd DataAccess
	}
}
