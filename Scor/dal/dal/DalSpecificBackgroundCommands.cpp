

#include "stdafx.h"
#include "DalSpecificBackgroundCommands.h"
#include "DalBinaryConversions.h"
#include "DalNibpDevicehandler.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting::Configuration;

DalCuffPressureCommand::DalCuffPressureCommand()
{
	this->nibpCommandPacket = gcnew array<unsigned char>  {0x3A, 0x79, 0x05, 0x00, 0x48};
	//this->responseWaitingTimeMax = 100;
	this->responseWaitingTimeMax = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.DalCuffPressureCommandWaitTime");
	
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

		//Set the current cuff pressure in DalNibpDeviceHandler so we can retrieve it 
		DalNibpDeviceHandler::CurrentCuffPressure = cuffPressure;

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
	//	this->responseWaitingTimeMax = 100;
	this->responseWaitingTimeMax = CrxSytemParameters::Instance->GetIntegerTagValue("NibpDal.Timeouts.DalNibpGetBpDataCommandWaitTime");
}

bool DalNibpGetBpDataCommand::ProcessNibpResponse()
{

	return true;
}

bool DalNibpGetBpDataCommand::GetBpDataAndRaiseEvent()
{
	DalReturnValue returnValue; 
	bool methodReturnValue;
	returnValue = this->SendCommandAndGetResponse();
	//CrxLogger::Instance->Write("DalNibpGetBpDataCommand::GetBpDataAndRaiseEvent Sent command and response recieved: " + returnValue.ToString(), ErrorSeverity::Debug );

	NibpMeasurementStatus  resultStatus = NibpMeasurementStatus::Unsuccessful; //Default value
	String ^ errorMessage = String::Empty ; //default
	this->_nibpDataObject = gcnew DalNibpData(); //We have to raise the event under any circumstance


	if ( DalReturnValue::Success  == returnValue)
	{
		//extract the nibp response and return it
		ExtractDataParts();

		bool dataCorrect = CheckRecievedData();
		CrxLogger::Instance->Write("DalNibpGetBpDataCommand::GetBpDataAndRaiseEvent CheckRecievedData returned: " + dataCorrect + ". EC andBP ignored. Raising event!." , ErrorSeverity::Debug );
				
		//if(true) //revert this should be for testing only
		if (dataCorrect)
		{
			resultStatus = NibpMeasurementStatus::Successful ;
			
			methodReturnValue =  true;

		}
		else
		{
			resultStatus = NibpMeasurementStatus::Unsuccessful;
			errorMessage = "BP data was extracted but is invalid.";  

			if (88 == _nibpDataObject->Ec)
			{
				errorMessage = "Brachial calibration error: {0}. Please turn EM4 off/on before starting a new measurement. Please refer to user manual for further corrective actions if necessary.";
				//TODO: resource file
			}
			else
			{
				errorMessage = "Brachial calibration error: {0}. Please refer to user manual for further corrective actions if necessary.";
				//TODO: resource file

			}
			methodReturnValue =  false;
		}

	}
	else
	{
		resultStatus = NibpMeasurementStatus::Unsuccessful;
		errorMessage = "Attempted to get BP Data but Failed.";  
		//This will tell the upper layers that the measurement simply failed and there is no technicall issue


		methodReturnValue =  false;
	}

	DalNIBPDataEventArgs ^ eventArgs = gcnew DalNIBPDataEventArgs(
																			_nibpDataObject->Ec , 
																			//0 , //this is for testing only. Do not CHECK IN!
																		   (unsigned short)_nibpDataObject->Sss, 
																		   (unsigned short)_nibpDataObject->Ddd, 
																		   (unsigned short)_nibpDataObject->Map, 
																		   (unsigned short)_nibpDataObject->Rate,
																		   resultStatus,
																		   errorMessage
																		   );

	DalEventContainer::Instance->OnDalNIBPDataEvent(this, eventArgs);

	return methodReturnValue;

	//return false; //unreachable
}

bool DalNibpGetBpDataCommand::CheckRecievedData()
{


	if (CrxSytemParameters::Instance->GetStringTagValue("NibpDal.IngnoreEC1ForTesting") != "Y")
	{
	if ( this->_nibpDataObject->Ec != 0)
	{
		return false;
	}
	
	if(this->_nibpDataObject->Bps != 0x01)
	{
		return false;
	}

		
	}

	if (CrxSytemParameters::Instance->GetStringTagValue("NibpDal.IngnoreEC1ForTesting") == "Y")
	{
		if ( this->_nibpDataObject->Ec == 1)
		{
			CrxLogger::Instance->Write("DalNibpGetBpDataCommand::CheckRecievedData replcing EC = 1 with EC = 0. This is only for development and you should not see this message in real time.",  ErrorSeverity::Warning);
			//Replace -1 with zero to allow for dummy "successful" measurement
			//we will not ignore other valid error codes
			this->_nibpDataObject->Ec = 0; 
		}

	}

	

	return true;
}

void DalNibpGetBpDataCommand::ExtractDataParts()
{
	


	
	_nibpDataObject->Sss = DalBinaryConversions::TranslateTwoBytesLsbFirst (this->nibpResponsePacket, 2);
	_nibpDataObject->Ddd = DalBinaryConversions::TranslateTwoBytesLsbFirst(this->nibpResponsePacket, 4);
	//_nibpDataObject->Btc = (unsigned char) this->nibpResponsePacket[6]; //unused for now
	_nibpDataObject->Bps = (unsigned char) this->nibpResponsePacket[7];
	_nibpDataObject->Rate = DalBinaryConversions::TranslateTwoBytesLsbFirst(this->nibpResponsePacket, 16);
	_nibpDataObject->Map = DalBinaryConversions::TranslateTwoBytesLsbFirst(this->nibpResponsePacket, 18);
	_nibpDataObject->Ec = (unsigned char) this->nibpResponsePacket[20];

	CrxLogger::Instance->Write("DalNibpGetBpDataCommand::ExtractDataParts Bps:" + _nibpDataObject->Bps + " Ec: " +  _nibpDataObject->Ec + " SP: " + _nibpDataObject->Sss + " DP: " + _nibpDataObject->Ddd + " MP: " + _nibpDataObject->Map + " HR: " + _nibpDataObject->Rate , ErrorSeverity::Debug );


}
