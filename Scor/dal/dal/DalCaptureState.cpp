/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCaptureState.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Companion source file for the capture state machine.
*/


#include "stdafx.h"
#include "DalCaptureState.h"
#include "DalCommandInterface.h"

using namespace AtCor::Scor::CrossCutting::Logging;


namespace AtCor{
	namespace Scor {
		namespace DataAccess {
			namespace StateMachines{ 

	bool DalCaptureState::InitiateDataCaptureMode()
	{

		////CrxLogger::Instance->Write("DalCaptureState::InitiateDataCaptureMode returns false", ErrorSeverity::Debug);
		//return false;
		////default


		bool returnValue;

		returnValue = DalCommandInterface::Instance->InitiateDataCaptureModeInternal();

		if (true == returnValue )
		{
			//change to the waiting state
			DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateWaiting::Instance);
		}
		//if false then dont change state

		CrxLogger::Instance->Write("DalCaptureState::InitiateDataCaptureMode  called in default state. returns: "+ returnValue.ToString(), ErrorSeverity::Debug);
		
		return returnValue;
	}

	bool DalCaptureState::StopDataCaptureMode()
	{
		//ca// should be routed to actual method regardless of current state
		bool returnValue ;
		returnValue  = DalCommandInterface::Instance->StopDataCaptureModeInternal();
		if (true == returnValue)
		{
			DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateNotListening::Instance);
	}

		return returnValue;
	}

	//void DalCaptureState::ReadFromPortAndWriteToBuffer(Object ^sender, SerialDataReceivedEventArgs ^e)
	//{
	//	sender; //Dummy statement to get rid of C4100 warning
	//	e; //Dummy statement to get rid of C4100 warning

	//	//do nothing
	//}

	bool DalCaptureState::ProcessStreamingPackets()
	{
		return false;
		//Do nothing
	}

	//void DalCaptureState::CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args)
	//{
	//	sender; //Dummy statement to get rid of C4100 warning
	//	args; //Dummy statement to get rid of C4100 warning

	//	//do nothing
	//}



	DalCaptureStateNotListening::DalCaptureStateNotListening()
	{
	}

	DalCaptureStateNotListening^ DalCaptureStateNotListening::operator =(DalCaptureStateNotListening ^)
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
		
		//CrxLogger::Instance->Write("DalCaptureStateNotListening::InitiateDataCaptureMode returns: "+ returnValue.ToString(), ErrorSeverity::Debug);
		
		return returnValue;
	}
	


	DalCaptureStateWaiting::DalCaptureStateWaiting()
	{
		//do nothing
	}

	DalCaptureStateWaiting^ DalCaptureStateWaiting::operator =(DalCaptureStateWaiting^)
	{
		return this;
	}


	//function has been removed
	/*bool DalCaptureStateWaiting::StopDataCaptureMode()
	{
		bool returnValue ;
		returnValue  = DalCommandInterface::Instance->StopDataCaptureModeInternal();
		if (true == returnValue)
		{
			DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateNotListening::Instance);
		}

		return returnValue;
	}*/

	//void DalCaptureStateWaiting::CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args)
	//{
	//	//The state change is done in the method itself
	//	DalCommandInterface::Instance->CheckIfTimeoutHasOccurredInternal (sender, args);
	//	
	//}



	DalCaptureStateDataReceived::DalCaptureStateDataReceived()
	{
		//empty constructor
	}

	DalCaptureStateDataReceived^ DalCaptureStateDataReceived::operator =(DalCaptureStateDataReceived^)
	{
		return this;
	}

	/*void DalCaptureStateDataReceived::ReadFromPortAndWriteToBuffer(Object ^sender, SerialDataReceivedEventArgs ^e)
	{
		DalCommandInterface::Instance->ReadFromPortAndWriteToBuffer(sender, e);
		DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateWaiting::Instance);
	}*/

	bool DalCaptureStateDataReceived::ProcessStreamingPackets()
	{
		bool returnValue ;
		returnValue = DalCommandInterface::Instance->ProcessStreamingPackets();
		DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateWaiting::Instance);

		return returnValue;

	}




	DalCaptureStateTimeout::DalCaptureStateTimeout()
	{
	}

	DalCaptureStateTimeout^ DalCaptureStateTimeout::operator =(DalCaptureStateTimeout^)
	{
		return this;
	}



	

			} //namespace StateMachines
		} //namespace DataAccess 
	} //namespace Scor
}//namespace AtCor