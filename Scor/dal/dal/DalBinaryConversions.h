/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalBinaryConversions.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalBinaryConversions class header file.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"


using namespace System;
using namespace System::IO;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalBinaryConversions
			* @brief Provides methods for translating binary data to and from other native data types
			*/
			private ref class DalBinaryConversions sealed
			{
				private:
					DalBinaryConversions(); //make constructor private to ensure that the class is not instantiated.

				public:

				/**
				* Converts the input array into a hexadecimal string representation.
				* @param[in]	inputArray	The input array
				* @return	A string representation of the input array
				*/
				static String^ ConvertBytesToString(array<unsigned char>^ inputArray);

				/**
				* Converts the specifed byte array into an unsigned short integer @n
				* Converts two bytes to an unsigned short integer
				* @param[in]	sourceArray	The byte array from which the integer is to be extracted
				* @param[in]	startPostion	Start index for the bytes
				* @return	An  unsigned short integer containing the translated bytes
				*/
				static unsigned short TranslateTwoBytes( array <unsigned char>^ sourceArray, int startPostion);
				
				/**
				* Converts the specifed byte array into a signed short integer by taking the 1st byte as LSB@n
				* @param[in]	sourceArray	The byte array from which the integer is to be extracted
				* @param[in]	startPostion	Start index for the bytes
				* @return	A signed short integer containing the translated bytes
				*/
				static signed short TranslateTwoBytesLsbFirst( array <unsigned char>^ sourceArray, int startPostion);
	
				/**
				* Converts the specifed byte array into an unsigned integer @n
				* Converts two bytes to an unsigned short integer
				* @param[in]	sourceArray	The byte array from which the integer is to be extracted
				* @param[in]	startPostion	Start index for the bytes
				* @return	An  unsigned short integer containing the translated bytes
				*/
				static unsigned int TranslateThreeBytes( array <unsigned char>^ sourceArray, int startPostion);

				/**
				* Converts the specifed byte array into an unsigned long integer
				* Converts four bytes to an unsigned long integer
				* @param[in]	sourceArray	The byte array from which the integer is to be extracted
				* @param[in]	startPostion	Start index for the bytes
				* @return	An  unsigned long integer containing the translated bytes
				*/
				static unsigned long TranslateFourBytes( array <unsigned char>^ sourceArray, int startPostion);

				/**
				* Converts the parameter to a DalAlarmSource alarm type
				* @param	alarmType	The soource enum type
				* @return	The corresponding  DalAlarmSource alarm type
				*/
				static DalAlarmSource ConvertAlarmType(DalAlarmFlagBitPosition alarmType);

				/**
				* Converts the parameter to a DalAlarmSource alarm type
				* @param	alarmType	The soource enum type
				* @return	The corresponding  DalAlarmSource alarm type
				*/
				static DalAlarmSource ConvertAlarmType(DalAlarmSupplyRailFlag alarmType);

				/**
				* Converts the parameter to a DalAlarmSource alarm type
				* @param	alarmType	The soource enum type
				* @return	The corresponding  DalAlarmSource alarm type
				*/
				static DalAlarmSource ConvertAlarmType(DalErrorAlarmStatusFlag alarmType);

				/**
				* Converts the parameter to a DalAlarmSource alarm type
				* @param	alarmName	The soource enum type
				* @return	The corresponding  DalAlarmSource alarm type
				*/
				static DalAlarmSource ConvertAlarmType(String^ alarmName);

				/**
				* Generates a Modulo256 checksum for NIBP packet
				* @param[in]	sourceArray	The array on which the checksum is to be generated
				* @param[in]	length The lenght of the array for which calculation should be done
				* @return	The hexadecimal value of the checksum
				*/
				static unsigned char GenerateModulo256Checksum(array<unsigned char>^ sourceArray, unsigned int length);

				/**
					* Converts the input string into bytes array.
					* @param[in]	strData	The input string
					* @return	A byte array representation of the string
				*/
				static array<unsigned char>^ ConvertStringToBytes(String^ strData);
				
				/**
					* Converts the input bytes into bytes array.
					* @param[in]	data	The input unsigned int
					* @return	A byte array representation of the int
				*/
				static array<unsigned char>^ ConvertThreeBytesIntoArray( unsigned int data);
				
				/**
					* Converts the input date into bytes array.
					* @param[in] data	The input dateTime
					* @return	A byte array representation of the DateTime
				*/
				static array<unsigned char>^ ConvertDateIntoArray(DateTime data);
				
				/**
					* Converts the input bytes array into DateTime .
					* @param[in] data	The input ByteArray
					* @return	A DateTime representation of the byte array
				*/
				static DateTime ConvertArrayIntoDate(array<unsigned char>^ data);

				/**
				* Converts the input bytes array.
				* @param[in] inputArray	The input ByteArray
				* @return	A String representation of the byte array
				*/
				static String^ ConvertArrayToString(array<unsigned char>^ inputArray);

			};

			
			
		} //End Namespace DataAccess
	}
}
