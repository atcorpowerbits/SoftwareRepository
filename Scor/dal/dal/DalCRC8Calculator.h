/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCRC8Calculator.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  CRC8Calculator
*/
#pragma once

#include "stdafx.h"
#include "DalCommon.h"

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{




			/**
			* @class CRC8Calculator
			* @brief Class to calculate 8 bit CRC value 
			*/
			private ref class CRC8Calculator
			{
				private:
					static array<unsigned char>^ crc8Table = gcnew array<unsigned char>(DalConstants::CRCTableSize ); // Default size of array
					static bool TableReady = false;
					static CRC8Calculator^ _instance = gcnew CRC8Calculator();
					/*CRC8Calculator^ operator= (const CRC8Calculator);*/ //fxCop
					
					/**
					* Constructor for the class. @n
					* Initializes the CRC8 table
					*/
					CRC8Calculator();

				public:
					

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

					/**
					* Returns the current singleton instance.
					*/
					static property CRC8Calculator^ Instance
					{
						CRC8Calculator^ get()
						{
							return CRC8Calculator::_instance;
						};
					};
			};


						
		}//End namespace DataAccess
	}
}

