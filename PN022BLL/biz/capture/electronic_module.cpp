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
	oldDalModuleState = DalConstants::NormalState;

	// Attach the handler to observe state event from DAL
	DalEventContainerStub::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(this, &BizElectronicModule::Update);
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
void BizElectronicModule::Update( Object^ sender, DalModuleErrorAlarmEventArgs^ e )
{
	if (e->state == DalConstants::NormalState && oldDalModuleState != e->state)
	{
		CrossCutting::Logging::CrxLogger::Instance->Write(e->source);
		ChangeState(BizElectronicModuleNormal::Instance());
	}
	else if (e->state == DalConstants::RecoverableState ||
	         e->state == DalConstants::UnrecoverableState)
	{
		CrossCutting::Logging::CrxLogger::Instance->Write(e->source);
		ChangeState(BizElectronicModuleAbnormal::Instance());
	}
	oldDalModuleState = e->state;
}
