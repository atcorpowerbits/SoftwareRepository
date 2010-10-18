/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	capture.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Cuff State classes.
*/

#include "StdAfx.h"
#include <cuff_state.h>

using namespace Biz;

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
void BizCuffState::ChangeState(BizCuff^ const client, BizCuffState^ %state)
{
	client->ChangeState(state);
}

/**
BizCuffDisconnected State Instance

DESCRIPTION

	Get the BizCuffDisconnected singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizCuffDisconnected^ - Handle to BizCuffDisconnected singleton object

*/
BizCuffDisconnected^ BizCuffDisconnected::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizCuffDisconnected;
		_instance->internalName = "Disconnected";
	}
	return _instance;
}

/**
Connect

DESCRIPTION

	Cuff is changing state from disconnected to connected state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffDisconnected::Connect(BizCuff^ const client)
{
	ChangeState(client, BizCuffDeflated::Instance());
}

/**
BizCuffDeflated State Instance

DESCRIPTION

	Get the BizCuffDeflated singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizCuffDeflated^ - Handle to BizCuffDeflated singleton object

*/
BizCuffDeflated^ BizCuffDeflated::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizCuffDeflated;
		_instance->internalName = "Deflated";
	}
	return _instance;
}

/**
Disconnect

DESCRIPTION

	Cuff is changing state from connected to disconnected state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffDeflated::Disconnect(BizCuff^ const client)
{
	ChangeState(client, BizCuffDisconnected::Instance());
}

/**
InflateNow

DESCRIPTION

	Cuff is changing state from connected / deflated to inflating state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffDeflated::InflateNow(BizCuff^ const client)
{
	ChangeState(client, BizCuffInflating::Instance());
}

/**
BizCuffInflating State Instance

DESCRIPTION

	Get the BizCuffInflating singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizCuffInflating^ - Handle to BizCuffInflating singleton object

*/
BizCuffInflating^ BizCuffInflating::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizCuffInflating;
		_instance->internalName = "Inflating";
	}
	return _instance;
}

/**
FinishInflating

DESCRIPTION

	Cuff is changing state from inflating to inflated state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffInflating::FinishInflating(BizCuff^ const client)
{
	ChangeState(client, BizCuffInflated::Instance());
}

/**
DeflateNow

DESCRIPTION

	Cuff is changing state from inflating to deflating state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffInflating::DeflateNow(BizCuff^ const client)
{
	ChangeState(client, BizCuffDeflating::Instance());
}

/**
BizCuffInflated State Instance

DESCRIPTION

	Get the BizCuffInflated singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizCuffInflated^ - Handle to BizCuffInflated singleton object

*/
BizCuffInflated^ BizCuffInflated::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizCuffInflated;
		_instance->internalName = "Inflated";
	}
	return _instance;
}

/**
DeflateNow

DESCRIPTION

	Cuff is changing state from inflated to deflating state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffInflated::DeflateNow(BizCuff^ const client)
{
	ChangeState(client, BizCuffDeflating::Instance());
}

/**
BizCuffDeflating State Instance

DESCRIPTION

	Get the BizCuffDeflating singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizCuffDeflating^ - Handle to BizCuffDeflating singleton object

*/
BizCuffDeflating^ BizCuffDeflating::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizCuffDeflating;
		_instance->internalName = "Deflating";
	}
	return _instance;
}

/**
FinishDeflating

DESCRIPTION

	Cuff is changing state from deflating to connected / deflated state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffDeflating::FinishDeflating(BizCuff^ const client)
{
	ChangeState(client, BizCuffResting::Instance());
}

/**
BizCuffResting State Instance

DESCRIPTION

	Get the BizCuffResting singleton instance.

INPUT

	none.

OUTPUT

	None.

RETURN

	BizCuffResting^ - Handle to BizCuffResting singleton object

*/
BizCuffResting^ BizCuffResting::Instance()
{
	if (_instance == nullptr) 
	{
		_instance = gcnew BizCuffResting;
		_instance->internalName = "Resting";
	}
	return _instance;
}

/**
FinishDeflating

DESCRIPTION

	Cuff is changing state from resting to connected / deflated state.

INPUT

	client - A handle to BizMeasure which is the client of BizCuffState

OUTPUT

	None.

RETURN

	None.

*/
void BizCuffResting::Connect(BizCuff^ const client)
{
	ChangeState(client, BizCuffDeflated::Instance());
}

