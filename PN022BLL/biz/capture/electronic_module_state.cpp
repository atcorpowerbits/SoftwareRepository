/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	electronic_module_state.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Cuff State classes.
*/

#include "StdAfx.h"
#include <electronic_module_state.h>

using namespace System;
using namespace BIZ_NAMESPACE;

/**
ChangeState

DESCRIPTION

	Change cuff state.

INPUT

	client - A handle to BizElectronicModule which is the client of BizElectronicModuleState
	state - A handle to BizElectronicModuleState to change to

OUTPUT

	None.

RETURN

	None.

*/		
void BizElectronicModuleState::ChangeState(BizElectronicModule^ const client, BizElectronicModuleState^ state)
{
	if (client != nullptr)
	{
		client->ChangeState(state);
	}
}

/**
BizElectronicModuleNormal State Instance

DESCRIPTION

	Get the BizElectronicModuleNormal singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizElectronicModuleNormal^ - Handle to BizElectronicModuleNormal singleton object

*/
BizElectronicModuleNormal^ BizElectronicModuleNormal::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizElectronicModuleNormal;
	}
	return _instance;
}

/**
Dispatch

DESCRIPTION

	Dispatch a message to tell observers that electronic module is now in normal state.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleNormal::Dispatch(String^ source)
{
	BizEventContainer::Instance->OnBizInformationEvent(this, gcnew BizInformationEventArgs(source));	
}

/**
ReceiveNewStatus

DESCRIPTION

	Electronic Module receives a new status while in normal state.

INPUT

	client - A handle to BizElectronicModule which is the client of BizElectronicModuleState

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleNormal::ReceiveNewStatus(BizElectronicModule^ const client, unsigned short newStatus)
{
	if (newStatus == DalConstantsStub::RecoverableStatus)
	{
		ChangeState(client, BizElectronicModuleWarning::Instance());
	}
	else if (newStatus == DalConstantsStub::UnrecoverableStatus)
	{
		ChangeState(client, BizElectronicModuleError::Instance());
	}
}

/**
BizElectronicModuleWarning State Instance

DESCRIPTION

	Get the BizElectronicModuleWarning singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizElectronicModuleWarning^ - Handle to BizElectronicModuleWarning singleton object

*/
BizElectronicModuleWarning^ BizElectronicModuleWarning::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizElectronicModuleWarning;
	}
	return _instance;
}

/**
Dispatch

DESCRIPTION

	Ask source of abnormal condition form the electroic module before dispatch 
	an abnormal message to tell observers that electronic module is in abnormal state.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleWarning::Dispatch(String^ source)
{
	BizEventContainer::Instance->OnBizWarningEvent(this, gcnew BizWarningEventArgs(source));	
}

/**
ReceiveNewStatus

DESCRIPTION

	Electronic Module receives a new status while in warning state.

INPUT

	client - A handle to BizElectronicModule which is the client of BizElectronicModuleState

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleWarning::ReceiveNewStatus(BizElectronicModule^ const client, unsigned short newStatus)
{
	if (newStatus == DalConstantsStub::ActiveStatus)
	{
		ChangeState(client, BizElectronicModuleNormal::Instance());
	}
	else if (newStatus == DalConstantsStub::UnrecoverableStatus)
	{
		ChangeState(client, BizElectronicModuleError::Instance());
	}
}

/**
BizElectronicModuleError State Instance

DESCRIPTION

	Get the BizElectronicModuleError singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizElectronicModuleError^ - Handle to BizElectronicModuleError singleton object

*/
BizElectronicModuleError^ BizElectronicModuleError::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizElectronicModuleError;
	}
	return _instance;
}

/**
Dispatch

DESCRIPTION

	Dispatch an error message to tell observers that electronic module is in error state.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleError::Dispatch(String^ source)
{
	BizEventContainer::Instance->OnBizErrorEvent(this, gcnew BizErrorEventArgs(source));	
}

/**
ReceiveNewStatus

DESCRIPTION

	Electronic Module receives a new status while in error state.

INPUT

	client - A handle to BizElectronicModule which is the client of BizElectronicModuleState

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleError::ReceiveNewStatus(BizElectronicModule^ const client, unsigned short newStatus)
{
	if (newStatus == DalConstantsStub::ActiveStatus)
	{
		ChangeState(client, BizElectronicModuleNormal::Instance());
	}
	else if (newStatus == DalConstantsStub::RecoverableStatus)
	{
		ChangeState(client, BizElectronicModuleWarning::Instance());
	}
}

