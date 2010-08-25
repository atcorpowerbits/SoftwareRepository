/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	cmd_states.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Elec. Module's Command State Classes
*/

#include "StdAfx.h"
#include <dal.h>
#include <dal_module_cmd_stub.h>

namespace DataAccess {
	void DalModuleCommandState::ChangeState(DalModule^ const m, DalModuleCommandState^ %s)
	{
		m->ChangeState(s);
	}
	DalMeterIdle^ DalMeterIdle::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalMeterIdle;
		}
		return _instance;
	}
	bool DalMeterIdle::StartCapture(DalModule^ const m)
	{
		bool isSent = false;

		//TBD: send start capture command here
		isSent = true;

		ChangeState(m, DalMeterWaitConfirmation::Instance());
		return isSent;
	}
	DalMeterWaitConfirmation^ DalMeterWaitConfirmation::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalMeterWaitConfirmation;
		}
		return _instance;
	}
	int DalMeterWaitConfirmation::ConfirmCommand(DalModule^ const m)
	{
		int confirmation;

		// wait for ACK or NACK or timeout
		confirmation = 1;

		// change state to wait for response data if necessary

		// just done
		ChangeState(m, DalMeterIdle::Instance());
		return confirmation;
	}
	DalMeterCapturing^ DalMeterCapturing::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalMeterCapturing;
		}
		return _instance;
	}
	DalMeterWaitResponse^ DalMeterWaitResponse::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalMeterWaitResponse;
		}
		return _instance;
	}
	void DalMeterWaitResponse::ReceiveResponse(DalModule^ const m)
	{
		//TBD: notify data subjects when response data is received
//???		TonoData^ data = gcnew TonoData;
//?		m->tonoDataRaw->Notify(1234);
		ChangeState(m, DalMeterIdle::Instance());
	}

	DalModule::DalModule(void) 
	{
		_state = DalMeterIdle::Instance();
	}
	DalModule^ DalModule::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalModule;
		}
		return _instance;
	}
	void DalModule::ChangeState(DalModuleCommandState^ s)
	{
		_state = s;
	}
	int DalModule::StartCapture()
	{
		int startOK = 0;
		if (!_state->StartCapture(this))
		{
			;
		} else if (!_state->ConfirmCommand(this))
		{
			;
		} else
		{
			startOK = 1;
		}
		return startOK;
	}
	bool DalModule::StopCapture()
	{
		bool stopOK = false;
/*		if (_state->StopCapture(this))
		{
			stopOK = true;
		}
*/
		stopOK = true; // stub
		return stopOK;
	}
	void DalModule::Simulate(unsigned int captureDataType)
	{
		// Normally, the timer is declared at the class level,
		// so that it stays in scope as long as it is needed.
		// If the timer is declared in a long-running method,  
		// KeepAlive must be used to prevent the JIT compiler 
		// from allowing aggressive garbage collection to occur 
		// before the method ends. (See end of method.)
		//System::Timers::Timer^ simulateTimer;

		// Create a new Timer with Interval set in milliseconds.
		// e.g. ~4 ms for 256 samples/sec
		simulateTimer = gcnew Timer (4);

		// Hook up the Elapsed event for the timer.
		switch (captureDataType)
		{
		case DalConstants::DATA_TONOMETER_AND_CUFF_PULSE_COMBO:
			simulateTimer->Elapsed += gcnew ElapsedEventHandler( &DalModule::OnPWVTimedEvent );
			dataFile = gcnew DalSimulationFile("c:\\projects\\pn022bll\\dal\\dal_stub\\pwv.dat");
			break;
		default:
			return; // nothing to simulate
		}
		dataFile->OpenFile();

		simulateTimer->Enabled = true;

		// If the timer is declared in a long-running method, use
		// KeepAlive to prevent garbage collection from occurring
		// before the method ends.
		//GC::KeepAlive(simulateTimer);
	}
	void DalModule::OnPWVTimedEvent( Object^ source, ElapsedEventArgs^ e )
	{
		short tonoData;
		short cuffData;

		DalModule::Instance()->dataFile->GetNextValueFromFile(&tonoData, &cuffData);
		DalTonometerStub::Instance()->tonoDataRaw->Notify(tonoData);
		DalCuffStub::Instance()->cuffPulseRaw->Notify(cuffData);
	}
	void DalModule::StopSimulation()
	{
		simulateTimer->Enabled = false; // stop simulation
		dataFile->CloseFile();
	}
}