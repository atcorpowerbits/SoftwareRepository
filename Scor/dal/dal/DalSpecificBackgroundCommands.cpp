

#include "stdafx.h"
#include "DalSpecificBackgroundCommands.h"
#include "DalBinaryConversions.h"

using namespace AtCor::Scor::DataAccess;

DalCuffPressureCommand::DalCuffPressureCommand()
{
	this->nibpCommandPacket = gcnew array<unsigned char>  {0x3A, 0x79, 0x05, 0x00, 0x48};
	this->responseWaitingTimeMax = 100;
	
}

bool DalCuffPressureCommand::ProcessNibpResponse()
{

	return true;
}

bool DalCuffPressureCommand::GetCuffPressure(unsigned int & cuffPressure)
{
	DalReturnValue returnValue; 
	returnValue = this->SendCommandAndGetResponse();

	if ( DalReturnValue::Success  == returnValue)
	{
		//extract the nibp response and return it

		cuffPressure = DalBinaryConversions::TranslateTwoBytesLsbFirst(this->nibpResponsePacket, 2);

		return true;
	}
	else
	{
		cuffPressure = 0; 

		return false;
	}
}



DalNibpGetBpDataCommand::DalNibpGetBpDataCommand()
{
	this->nibpCommandPacket = gcnew array<unsigned char> {0x3A, 0x79, 0x03, 0x00, 0x4A};
	this->responseWaitingTimeMax = 100;
}

bool DalNibpGetBpDataCommand::ProcessNibpResponse()
{

	return true;
}

bool DalNibpGetBpDataCommand::GetBpDataAndRaiseEvent()
{
	DalReturnValue returnValue; 
	returnValue = this->SendCommandAndGetResponse();

	if ( DalReturnValue::Success  == returnValue)
	{
		//extract the nibp response and return it
		ExtractDataParts();

		//TODO
		if (CheckRecievedData())
		{
			DalNIBPDataEventArgs ^ eventArgs = gcnew DalNIBPDataEventArgs(
																			_nibpDataObject->Ec , 
																		   (unsigned short)_nibpDataObject->Sss, 
																		   (unsigned short)_nibpDataObject->Ddd, 
																		   (unsigned short)_nibpDataObject->Map, 
																		   (unsigned short)_nibpDataObject->Rate
																		   );

			DalEventContainer::Instance->OnDalNIBPDataEvent(this, eventArgs);

		}
		else
		{
			return false;
		}

		return true;
	}
	else
	{

		return false;
	}

	//return false; //unreachable
}

bool DalNibpGetBpDataCommand::CheckRecievedData()
{

	if ( this->_nibpDataObject->Ec != 0)
	{
		return false;
	}
	
	if(this->_nibpDataObject->Bps != 0x01)
	{
		return false;
	}

	return true;
}

void DalNibpGetBpDataCommand::ExtractDataParts()
{
	this->_nibpDataObject = gcnew DalNibpData();

	//DalBinaryConversions::TranslateTwoBytes(this->nibpResponsePacket, 2);

	//_nibpDataObject->Ec = (unsigned char) this->nibpResponsePacket[20];

	
	//TODO: validate these two

	_nibpDataObject->Sss = DalBinaryConversions::TranslateTwoBytes(this->nibpResponsePacket, 2);
	_nibpDataObject->Ddd = DalBinaryConversions::TranslateTwoBytes(this->nibpResponsePacket, 4);
	//_nibpDataObject->Btc = (unsigned char) this->nibpResponsePacket[6]; //unused for now
	_nibpDataObject->Bps = (unsigned char) this->nibpResponsePacket[7];
	_nibpDataObject->Rate = DalBinaryConversions::TranslateTwoBytes(this->nibpResponsePacket, 16);
	_nibpDataObject->Map = DalBinaryConversions::TranslateTwoBytes(this->nibpResponsePacket, 18);
	_nibpDataObject->Ec = (unsigned char) this->nibpResponsePacket[20];


}
