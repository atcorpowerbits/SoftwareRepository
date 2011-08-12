/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalBinaryConversions.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalBinaryConversions class header file.
*/

#pragma once

#include "stdafx.h"


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
					* @param	inputArray	The input array
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
				* Converts the specifed byte array into an unsigned long integer
				* Converts four bytes to an unsigned long integer
				* @param[in]	sourceArray	The byte array from which the integer is to be extracted
				* @param[in]	startPostion	Start index for the bytes
				* @return	An  unsigned long integer containing the translated bytes
				*/
				static unsigned long TranslateFourBytes( array <unsigned char>^ sourceArray, int startPostion);
			};

			
		} //End Namespace DataAccess
	}
}
