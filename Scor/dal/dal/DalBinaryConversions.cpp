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
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace System::Text;
using namespace System;
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

String^ DalBinaryConversions::ConvertArrayToString(array<unsigned char>^ inputArray)
{
	if (nullptr == inputArray)
	{
		return String::Empty;
	}

	StringBuilder ^ packetData = gcnew StringBuilder((inputArray->Length))  ;
	//Each byte is printed as two characters + 1 whitespace

	//UnicodeEncoding^ unicode = gcnew UnicodeEncoding(); //unused

	//String^ myInput = Convert::ToString(Convert::ToChar(710)); unused

	for each (unsigned char singleByte in inputArray)
	{
		/*packetData = packetData->Append(singleByte.ToString(DalFormatterStrings::PrintByte));
		packetData = packetData->Append(DalFormatterStrings::SingleSpaceString );*/

		packetData->Append( Convert::ToString(Convert::ToChar(singleByte))) ;
	}
	return packetData->ToString();
}

array<unsigned char>^ DalBinaryConversions::ConvertStringToBytes(String^ chars)
{
    ASCIIEncoding^ ascii = gcnew ASCIIEncoding();
    
    int byteCount = ascii->GetByteCount(chars->ToCharArray());
	array<unsigned char>^ bytes = gcnew array<unsigned char> (byteCount) {0};
	
	 ascii->GetBytes(chars, 0, byteCount, bytes, 0);
	return bytes;
}

unsigned short DalBinaryConversions::TranslateTwoBytes( array <unsigned char>^ sourceArray, int startPostion)
{
	//get the status flag
	TwoBytesUnsignedShort flagUn;

	flagUn.ucStatusBytes[1] = sourceArray[startPostion];
	flagUn.ucStatusBytes[0] = sourceArray[startPostion + 1];

	return flagUn.ulStatusFlag ;
}

unsigned int DalBinaryConversions::TranslateThreeBytes( array <unsigned char>^ sourceArray, int startPostion)
{
	//get the status flag
	ThreeBytesUnsignedInt flagUn;

	flagUn.ucStatusBytes[3] = 0;
	flagUn.ucStatusBytes[2] = sourceArray[startPostion];
	flagUn.ucStatusBytes[1] = sourceArray[startPostion + 1];
	flagUn.ucStatusBytes[0] = sourceArray[startPostion + 2];

	return flagUn.uiStatusFlag;
}
signed short DalBinaryConversions::TranslateTwoBytesLsbFirst( array <unsigned char>^ sourceArray, int startPostion)
{
	//similar to TranslateTwoBytes() but the LSB is the first byte instead of second
	//get the status flag
	TwoBytesSignedShort  flagUn;

	flagUn.ucStatusBytes[1] = sourceArray[startPostion +1];
	flagUn.ucStatusBytes[0] = sourceArray[startPostion];

	return flagUn.ssStatusFlag ;
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

array<unsigned char>^ DalBinaryConversions::ConvertThreeBytesIntoArray( unsigned int data)
{
	array<unsigned char>^ byteData = gcnew array<unsigned char> (3);

	//need to check the data
	byteData[2] = (unsigned char)(data & 0x00FF);
	byteData[1] = ((unsigned char)((data & 0xFF00) >> 8));
	byteData[0] = ((unsigned char)((data & 0xFF00) >> 16));

	return byteData;

}

array<unsigned char>^ DalBinaryConversions::ConvertDateIntoArray(DateTime data)
{
		array<unsigned char>^ byteData = gcnew array<unsigned char> (6);

		byteData[5] = (unsigned char)((unsigned int)data.Minute & 0x00FF);
		byteData[4] = (unsigned char)((unsigned int)data.Hour & 0x00FF);
		byteData[3] = (unsigned char)((unsigned int)data.Day & 0x00FF);
		byteData[2] = (unsigned char)((unsigned int)data.Month & 0x00FF);
		byteData[0] = (unsigned char)((unsigned int)data.Year & 0x00FF);
		byteData[1] = ((unsigned char)(((unsigned int)data.Year & 0xFF00) >> 8));

		return byteData;
}

DateTime DalBinaryConversions::ConvertArrayIntoDate(array<unsigned char>^ data)
{
		DateTime dt ;//= gcnew DateTime;

		dt.AddMinutes( (double) ((unsigned int)data[5]));
		dt.AddHours((double) ((unsigned int)data[4]));
		dt.AddDays((double) ((unsigned int)data[3]));
		dt.AddMonths((int) ((unsigned int)data[2]));
		dt.AddYears((int) ((unsigned int)data[0] & ((unsigned int)data[1] << 8)));
		
		return dt;
}

DalAlarmSource DalBinaryConversions::ConvertAlarmType(DalAlarmFlagBitPosition alarmType)
{
	//get the integer of the parameter. Convert it to DalAlarmSource and return it 
	return safe_cast<DalAlarmSource>((int)alarmType + 0);
	
}

//DalAlarmSource DalBinaryConversions::ConvertAlarmType(DalAlarmSupplyRailFlag alarmType)
//{
//	//this one requires a physical translation
//	switch (alarmType)
//	{
//		case DalAlarmSupplyRailFlag::Reserved :
//				return DalAlarmSource::Reserved;
//		case DalAlarmSupplyRailFlag::Source5VA:
//				return DalAlarmSource::Source5VA;
//		case DalAlarmSupplyRailFlag::Source5VD :
//				return DalAlarmSource::Source5VD;
//		case DalAlarmSupplyRailFlag::SupplyRailNoAlarm :
//				return DalAlarmSource::SupplyRailNoAlarm ;
//		case DalAlarmSupplyRailFlag::Vin :
//				return DalAlarmSource::Vin;
//		case DalAlarmSupplyRailFlag::VPump :
//				return DalAlarmSource::VPump ;
//		case DalAlarmSupplyRailFlag::VTono :
//				return DalAlarmSource::VTono;
//		case DalAlarmSupplyRailFlag::VValve :
//				return DalAlarmSource::VValve ;
//		default:
//			return DalAlarmSource::NoAlarmDefined;
//	}
//}

DalAlarmSource DalBinaryConversions::ConvertAlarmType(DalAlarmSupplyRailFlag alarmType)
{
	try
	{
		String ^alarmName;
		//first get the alarm name as a string from the source enum
		alarmName = alarmType.ToString();

		//then try to convert it to another type
		return safe_cast<DalAlarmSource>(Enum::Parse(DalAlarmSource::typeid, alarmName));
	}
	catch(Exception ^)
	{
		//on exception return with a false type to signify that this type was not found.
			return DalAlarmSource::NoAlarmDefined;
	}

	
}

DalAlarmSource DalBinaryConversions::ConvertAlarmType(DalErrorAlarmStatusFlag alarmType)
{
	//get the integer of the parameter. 
	//Add an offset and convert it to DalAlarmSource and return it 
	return safe_cast<DalAlarmSource>((int)alarmType + 200);
}

DalAlarmSource  DalBinaryConversions::ConvertAlarmType(String ^alarmName)
{
	try
	{
		return safe_cast<DalAlarmSource>(Enum::Parse(DalAlarmSource::typeid, alarmName));
	}
	catch(Exception ^)
	{
		//on exception return with a false type to signify that this type was not found.
		return DalAlarmSource::NoAlarmDefined;
	}
	
}

unsigned char DalBinaryConversions::GenerateModulo256Checksum(cli::array<unsigned char,1> ^sourceArray, unsigned int length)
{
	//throw an excpetion in case of a problem
	if ((nullptr == sourceArray) || (0 == sourceArray->Length) || (0 == length))
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrorNullParamErrCd, CrxStructCommonResourceMsg::DalErrorNullParam, ErrorSeverity::Exception);
	}

	//if not do the actual processing
	unsigned int current = 0;
	unsigned char moduloSum = 0x00;

	while (current < length)
	{
		moduloSum +=sourceArray[current++];
	}
	
	moduloSum = unsigned char((unsigned int)0x100 - (unsigned int)moduloSum);



	return moduloSum; 
}