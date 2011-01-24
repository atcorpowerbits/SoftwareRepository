/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	electronic_module.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Electronic Module Class
*/

#include <StdAfx.h>
#include <electronic_module.h>
#include <electronic_module_state.h>

using namespace BIZ_NAMESPACE;
using namespace CRX_LOG_NAMESPACE;

BizElectronicModule::BizElectronicModule(void) 
{
	currentState = BizElectronicModuleNormal::Instance();
//	prevErrorAlarmStatus = DalConstantsStub::ActiveStatus;
	prevErrorAlarmStatus = DataAccess::DalErrorAlarmStatusFlag::ActiveStatus;

	// Attach the handler to observe state event from DAL
//	DalEventContainerStub::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(this, &BizElectronicModule::Update);
	DalEventContainer::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler_ORI(this, &BizElectronicModule::Update_ORI);
};

/**
ChangeState

DESCRIPTION

	Change electronic module to a given state

INPUT

	state - Destination electronic module state

OUTPUT

	None.

RETURN

	None.

*/		
void BizElectronicModule::ChangeState(BizElectronicModuleState^ state)
{
	previousState = currentState;
	currentState = state;
}

/**
Update

DESCRIPTION

	Process update from the electronic module state subject.
	Note that it shouldn't display the data as the update is not called from a GUI thread.

INPUT

	sender - Subject which is sending the update event.

	e - Event arguments where a electronic module state is passed.

OUTPUT

	None.

RETURN

	None.

*/		
#if 0
void BizElectronicModule::Update( Object^ sender, DalModuleErrorAlarmEventArgs^ e )
{
	// No need to change state if it's the same as before.
	// In real DAL, DAL should not delegate this event if EM4 is in the same state.
	if (e->errorAlarmStatus != prevErrorAlarmStatus)
	{
		currentState->ReceiveNewStatus(this, e->errorAlarmStatus);		
		prevErrorAlarmStatus = e->errorAlarmStatus;
	}
}
#endif

/**
Update_ORI

DESCRIPTION

	Process update from the electronic module state (subject of this observer).
	Note that it shouldn't display the data as the update is not called from a GUI thread.

INPUT

	sender - Subject which is sending the update event.

	e - Event arguments where a electronic module state is passed from DAL as a new (ORI?) args.

OUTPUT

	None.

RETURN

	None.

*/	void BizElectronicModule::Update_ORI( Object^ sender, DalModuleErrorAlarmEventArgs_ORI^ e )
{
	// No need to change state if it's the same as before.
	// In real DAL, DAL should not delegate this event if EM4 is in the same state.
	if (e->ErrorAlarmStatus != prevErrorAlarmStatus)
	{
		currentState->ReceiveNewStatus(this, e->ErrorAlarmStatus);		
		prevErrorAlarmStatus = e->ErrorAlarmStatus;
	}
}

/**
Dispatch

DESCRIPTION

	Dispatch the current state of the electronic module.
	Let individual state to dispatch its own state.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizElectronicModule::Dispatch()
{
	// Dispatch only once when there's a change of state
	if (currentState != previousState && currentState != dispatchedState)
	{
//TBD:DAL not ready for it 		source = DalModule::Instance->GetErrorAlarmSource();
		source = "error alarm source not avaialble yet"; // stub
		// Comment out logging before running UT BizElectronicModuleDispatchTest
		CrossCutting::Logging::CrxLogger::Instance->Write(source);
		currentState->Dispatch(source);
		dispatchedState = currentState;
	}
}
