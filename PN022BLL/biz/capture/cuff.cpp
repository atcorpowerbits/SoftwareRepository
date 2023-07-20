/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	measure.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Cuff Class
*/

#include <StdAfx.h>
#include <cuff.h>
#include <cuff_state.h>

using namespace BIZ_NAMESPACE;

BizCuff::BizCuff(void) 
{
	// TBD: Confirm if cuff can be assumed "not connected" first.
	currentState = BizCuffDisconnected::Instance();
	previousState = currentState;

	cuffStatusSubject = DalFacade::Instance()->FindCuffStatusEvent();

	// Attach the handler to observe cuff state event from DAL
	cuffStatusSubject->CuffStatusEvent += 
		gcnew DalCuffStatusEvent::DalCuffStatusEventHandler( this, &BizCuff::Update );

	// Create a cuff state business data subject
	cuffStateBiz = gcnew BizCuffStateEvent;
};

/**
ChangeState

DESCRIPTION

	Change cuff to a given state

INPUT

	state - Destination cuff state

OUTPUT

	None.

RETURN

	None.

*/		
void BizCuff::ChangeState(BizCuffState^ state)
{
	currentState = state;
}

/**
Update

DESCRIPTION

	Process update from the cuff state subject.
	Note that it shouldn't display the data as the update is not called from a GUI thread.

INPUT

	sender - Subject which is sending the update event.

	e - Event arguments where a cuff state is passed.

OUTPUT

	None.

RETURN

	None.

*/		
void BizCuff::Update( Object^ sender, DalCuffStatusEventArgs^ e )
{
	// Map DAL cuff state event into 
	switch (e->data)
	{
	case 1: // TBD: Why can't use DataAccess::DalConstants::CUFF_STATE_DISCONNECTED):
		ChangeState(BizCuffDisconnected::Instance());
		break;
	case 2: // TBD: Why can't use DataAccess::DalConstants::CUFF_STATE_CONNECTED_DEFLATED):
		ChangeState(BizCuffDeflated::Instance());
		break;
	case 3: // TBD: Why can't use DataAccess::DalConstants::CUFF_STATE_INFLATING):
		ChangeState(BizCuffInflating::Instance());
		break;
	case 4: // TBD: Why can't use DataAccess::DalConstants::CUFF_STATE_INFLATED):
		ChangeState(BizCuffInflated::Instance());
		break;
	case 5: // TBD: Why can't use DataAccess::DalConstants::CUFF_STATE_DEFLATING):
		ChangeState(BizCuffDeflating::Instance());
		break;
	default:
		break;
	}
}

/**
Dispatch

DESCRIPTION

	Dispatch cuff state if has chnaged.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/		
void BizCuff::Dispatch()
{
	if (previousState != currentState)
	{
		// Inform observers about the cuff state change
		cuffStateBiz->Notify(currentState->internalName);

		// Remember the current state as a previous state
		previousState = currentState;
	}
}

