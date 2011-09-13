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

DalAlarmSource DalBinaryConversions::ConvertAlarmType(DalAlarmFlagBitPosition alarmType)
{
	//get the integer of the parameter. Convert it to DalAlarmSource and return it 
	return safe_cast<DalAlarmSource>((int)alarmType + 0);
	
}

DalAlarmSource DalBinaryConversions::ConvertAlarmType(DalAlarmSupplyRailFlag alarmType)
{
	//this one requires a physical translation
	switch (alarmType)
	{
		case DalAlarmSupplyRailFlag::Reserved :
				return DalAlarmSource::Reserved;
		case DalAlarmSupplyRailFlag::Source5VA:
				return DalAlarmSource::Source5VA;
		case DalAlarmSupplyRailFlag::Source5VD :
				return DalAlarmSource::Source5VD;
		case DalAlarmSupplyRailFlag::SupplyRailNoAlarm :
				return DalAlarmSource::SupplyRailNoAlarm ;
		case DalAlarmSupplyRailFlag::Vin :
				return DalAlarmSource::Vin;
		case DalAlarmSupplyRailFlag::VPump :
				return DalAlarmSource::VPump ;
		case DalAlarmSupplyRailFlag::VTono :
				return DalAlarmSource::VTono;
		case DalAlarmSupplyRailFlag::VValve :
				return DalAlarmSource::VValve ;
		default:
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