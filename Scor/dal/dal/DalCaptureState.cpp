/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCaptureState.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Companion source file for the capture state machine.
*/


#include "stdafx.h"
#include "DalCaptureState.h"
#include "DalCommandInterface.h"


namespace AtCor{
	namespace Scor {
		namespace DataAccess {
			namespace StateMachines{ 

	bool DalCaptureState::InitiateDataCaptureMode()
	{
		return false;
		//default
	}

	bool DalCaptureState::StopDataCaptureMode()
	{
		return false;
	}

	void DalCaptureState::ReadFromPortAndWriteToBuffer(Object ^sender, SerialDataReceivedEventArgs ^e)
	{
		//do nothing
	}

	void DalCaptureState::CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args)
	{
		//do nothing
	}



	DalCaptureStateNotListening::DalCaptureStateNotListening()
	{
	}

	DalCaptureStateNotListening^ DalCaptureStateNotListening::operator =(const DalCaptureStateNotListening ^)
	{
		return this;
	}

	bool DalCaptureStateNotListening::InitiateDataCaptureMode()
	{
		bool returnValue;

		returnValue = DalCommandInterface::Instance->InitiateDataCaptureModeInternal();

		if (true == returnValue )
		{
			//change to the waiting state
			DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateWaiting::Instance);
		}
		//if false then dont change state
		
		return returnValue;
	}
	


	DalCaptureStateWaiting::DalCaptureStateWaiting()
	{
		//do nothing
	}

	DalCaptureStateWaiting^ DalCaptureStateWaiting::operator =(const DalCaptureStateWaiting^)
	{
		return this;
	}


	bool DalCaptureStateWaiting::StopDataCaptureMode()
	{
		bool returnValue ;
		returnValue  = DalCommandInterface::Instance->StopDataCaptureModeInternal();
		if (true == returnValue)
		{
			DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateNotListening::Instance);
		}

		return returnValue;
	}

	void DalCaptureStateWaiting::CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args)
	{
		//The state change is done in the method itself
		DalCommandInterface::Instance->CheckIfTimeoutHasOccurredInternal (sender, args);
		
	}



	DalCaptureStateDataReceived::DalCaptureStateDataReceived()
	{
		//empty constructor
	}

	DalCaptureStateDataReceived^ DalCaptureStateDataReceived::operator =(const DalCaptureStateDataReceived^)
	{
		return this;
	}

	void DalCaptureStateDataReceived::ReadFromPortAndWriteToBuffer(Object ^sender, SerialDataReceivedEventArgs ^e)
	{
		DalCommandInterface::Instance->ReadFromPortAndWriteToBuffer(sender, e);
		DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateWaiting::Instance);
	}




	DalCaptureStateTimeout::DalCaptureStateTimeout()
	{
	}

	DalCaptureStateTimeout^ DalCaptureStateTimeout::operator =(const DalCaptureStateTimeout^)
	{
		return this;
	}



	

			} //namespace StateMachines
		} //namespace DataAccess 
	} //namespace Scor
}//namespace AtCor