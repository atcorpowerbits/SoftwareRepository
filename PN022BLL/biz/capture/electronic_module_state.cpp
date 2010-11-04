/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	electronic_module_state.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Cuff State classes.
*/

#include "StdAfx.h"
#include <electronic_module_state.h>

using namespace BIZ_NAMESPACE;

/**
ChangeState

DESCRIPTION

	Change cuff state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState
	state - A handle to BizCuffState to change to

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
ReceiveError

DESCRIPTION

	Electronic Module is changing state from normal to abnormal state.

INPUT

	client - A handle to BizElectronicModule which is the client of BizElectronicModuleState

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleNormal::ReceiveError(BizElectronicModule^ const client)
{
	ChangeState(client, BizElectronicModuleAbnormal::Instance());
}

/**
ReceiveAlarm

DESCRIPTION

	Electronic Module is changing state from normal to abnormal state.

INPUT

	client - A handle to BizElectronicModule which is the client of BizElectronicModuleState

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleNormal::ReceiveAlarm(BizElectronicModule^ const client)
{
	ChangeState(client, BizElectronicModuleAbnormal::Instance());
}

/**
BizElectronicModuleAbnormal State Instance

DESCRIPTION

	Get the BizElectronicModuleAbnormal singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizElectronicModuleAbnormal^ - Handle to BizElectronicModuleAbnormal singleton object

*/
BizElectronicModuleAbnormal^ BizElectronicModuleAbnormal::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizElectronicModuleAbnormal;
	}
	return _instance;
}

/**
ReceiveError

DESCRIPTION

	Electronic Module is changing state from abnormal to normal state.

INPUT

	client - A handle to BizElectronicModule which is the client of BizElectronicModuleState

OUTPUT

	None.

RETURN

	None.

*/
void BizElectronicModuleAbnormal::ReceiveNormal(BizElectronicModule^ const client)
{
	ChangeState(client, BizElectronicModuleNormal::Instance());
}
