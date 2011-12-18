/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4NibpToHostPacket.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Code file for classes:  DalEM4NibpToHostPacket
*/

#pragma once

#include "stdafx.h"
#include "DalEM4NibpToHostPacket.h"
#include "DalStatusHandler.h"

using namespace System;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::DataAccess;

DalEM4NibpToHostPacket::DalEM4NibpToHostPacket():EM4DataCapturePacket(0)
{
	//Do nothing this is a blank constructor

	//Call EM4DataCapturePacket constuctor with dataSize = 0
	//This way we can control the size of the response packet which will be variable for DalEM4NibpToHostPacket
	SetStatusHandler(gcnew DalNibpStatusHandler());
}

DalEM4NibpToHostPacket::DalEM4NibpToHostPacket(array<unsigned char> ^byteArray):EM4DataCapturePacket(0)
{
	//Call EM4DataCapturePacket constuctor with dataSize = 0
	//This way we can control the size of the response packet which will be variable for DalEM4NibpToHostPacket

	SetStatusHandler(gcnew DalNibpStatusHandler());

	//copy the response from the parameter
	em4Response = byteArray;

	em4ResponsePacketLength= byteArray->Length -1; //subtract 1 for CRC

	//call the function that will break the packet into individual bits
	BreakupEM4Response();
}


DalReturnValue DalEM4NibpToHostPacket::ValidatePacket()
{

	unsigned long statusBytes ;

	//the reply value should be for 0x93
	if (em4ResponseAckNackByte != (unsigned char)DalAckNackByteMask::Em4NibpToHostCommandCode ) 
	{
		//the reply is for another command incorrect
		return DalReturnValue::Failure;
	}

	//now validate the CRC
	if (!(ValidateResponseCRC()))
	{
		return DalReturnValue::Failure ;
	}

	//assign the status flag to a variable
	statusBytes = (unsigned long) em4StatusFlag ;
	
	//no need to return value based on the status flag. ACK/NACK is enough 
	_statusHandler->ProcessStatusFlag(statusBytes);


	//Not sure if sequence number will be valid here TODO: Please check
	//if (CrxSytemParameters::Instance->GetStringTagValue("ProcessSequenceNumber.StreamingPackets") == "Y")
	//{
	//	//validate the sequecne number
	//	if (!DalSequenceNumberManager::ValidateStreamingSequenceNumber(capturePacket->em4ResponseSequenceNumber))
	//	{
	//		return DalReturnValue::Failure;
	//	}
	//}	

	return DalReturnValue::Success ;
}

bool DalEM4NibpToHostPacket::ValidateResponseCRC()
{
	bool returnValue;

	if (em4Response == nullptr)
	{
		return false;
	}

	//generate the CRC
	DalCRC8Calculator ^ crcCalculator = DalCRC8Calculator::Instance;
	unsigned char generatedCRCValue = 0x00;
	unsigned char recivedCRCValue = em4ResponseCRCByte;
	returnValue= crcCalculator->ComputeCrc8ForArray(em4Response, em4ResponsePacketLength, &generatedCRCValue);

	 if (false == returnValue)
	 {
		 return false;
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

void DalEM4NibpToHostPacket::SetStatusHandler(DalNibpStatusHandler ^ newStatusHandler)
{
	this->_statusHandler = newStatusHandler;
}

DalEM4NibpToHostPacket::~DalEM4NibpToHostPacket()
{
	CrxLogger::Instance->Write("DalEM4NibpToHostPacket::~DalEM4NibpToHostPacket called for object:" + this->GetType());
	
	//TODO
}





