/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	cmd_states.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Elec. Module's Command State Classes
*/

#include "StdAfx.h"
#include "dal_meter_cmd_stub.h"
#include "dal_meter_data_stub.h"

namespace DataAccess {
	void DalMeterState::ChangeState(DalMeter^ const m, DalMeterState^ %s)
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
	bool DalMeterIdle::StartCapture(DalMeter^ const m)
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
	int DalMeterWaitConfirmation::ConfirmCommand(DalMeter^ const m)
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
	void DalMeterWaitResponse::ReceiveResponse(DalMeter^ const m)
	{
		//TBD: notify data subjects when response data is received
//???		TonoData^ data = gcnew TonoData;
		m->tonoDataRaw->Notify(1234);
		ChangeState(m, DalMeterIdle::Instance());
	}
	DalMeter::DalMeter(void) 
	{
		_state = DalMeterIdle::Instance();

		tonoDataRaw = gcnew DalTonoData;
	}
	void DalMeter::ChangeState(DalMeterState^ s)
	{
		_state = s;
	}
	int DalMeter::StartCapture()
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
	bool DalMeter::StopCapture()
	{
		bool stopOK = false;
		if (_state->StopCapture(this))
		{
			stopOK = true;
		}
		return stopOK;
	}
}