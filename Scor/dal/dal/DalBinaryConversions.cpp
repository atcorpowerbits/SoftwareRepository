/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalBinaryConversions.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalBinaryConversions class source file.
*/

#pragma once

#include "stdafx.h"
#include "DalBinaryConversions.h"
#include "DalCommon.h"

using namespace AtCor::Scor::DataAccess;
using namespace System::Text;
//using namespace System::Globalization;

DalBinaryConversions::DalBinaryConversions()
{
	//empty constructor for sealed static class
}

/*String^ DalBinaryConversions::ConvertBytesToString(array<unsigned char>^ inputArray)
{
	String ^ packetData = String::Empty ;

	for each (unsigned char singleByte in inputArray)
	{
		packetData += singleByte.ToString(DalFormatterStrings::PrintByte) + DalFormatterStrings::SingleSpaceString ;
	}

	return packetData;
}*/	

String^ DalBinaryConversions::ConvertBytesToString(array<unsigned char>^ inputArray)
{
	if (nullptr == inputArray)
	{
		return String::Empty;
	}

	StringBuilder ^ packetData = gcnew StringBuilder((inputArray->Length)*3)  ;
	//Each byte is printed as two characters + 1 whitespace

	for each (unsigned char singleByte in inputArray)
	{
		/*packetData = packetData->Append(singleByte.ToString(DalFormatterStrings::PrintByte));
		packetData = packetData->Append(DalFormatterStrings::SingleSpaceString );*/

		packetData->Append(singleByte.ToString(DalFormatterStrings::PrintByte))->Append(DalFormatterStrings::SingleSpaceString);
	}
	return packetData->ToString();
}

unsigned short DalBinaryConversions::TranslateTwoBytes( array <unsigned char>^ sourceArray, int startPostion)
{
	//get the status flag
	TwoBytesUnsignedShort flagUn;

	flagUn.ucStatusBytes[1] = sourceArray[startPostion];
	flagUn.ucStatusBytes[0] = sourceArray[startPostion + 1];

	return flagUn.ulStatusFlag ;
}


unsigned long DalBinaryConversions::TranslateFourBytes( array <unsigned char>^ sourceArray, int startPostion)
{
	//get the status flag
	FourBytesUnsignedLong flagUn;
	//UT fix
	flagUn.ucStatusBytes[3] = sourceArray[startPostion];
	flagUn.ucStatusBytes[2] = sourceArray[startPostion + 1];
	flagUn.ucStatusBytes[1] = sourceArray[startPostion + 2];
	flagUn.ucStatusBytes[0] = sourceArray[startPostion + 3];

	return flagUn.ulStatusFlag ;
}