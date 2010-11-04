/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	electronic_module_state.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Electronic Module State.
*/

#pragma once

#include <electronic_module.h>
#include <biz_namespace.h>

using namespace System;

START_BIZ_NAMESPACE

public ref class BizElectronicModuleState abstract
{
public:
	virtual void ReceiveNormal(BizElectronicModule^ const client) {};
	virtual void ReceiveError(BizElectronicModule^ const client) {};
	virtual void ReceiveAlarm(BizElectronicModule^ const client) {};

protected:
	BizElectronicModuleState() {};
	static void ChangeState(BizElectronicModule^ const client, BizElectronicModuleState^ state);
};

// Electronic Module nomral state
public ref class BizElectronicModuleNormal : BizElectronicModuleState
{
public:
	static BizElectronicModuleNormal^ BizElectronicModuleNormal::Instance();
	virtual void ReceiveError(BizElectronicModule^ const client) override;
	virtual void ReceiveAlarm(BizElectronicModule^ const client) override;

private:
	static BizElectronicModuleNormal^ _instance;
};

// Electronic Module abnomral state
public ref class BizElectronicModuleAbnormal : BizElectronicModuleState
{
public:
	static BizElectronicModuleAbnormal^ BizElectronicModuleAbnormal::Instance();
	virtual void ReceiveNormal(BizElectronicModule^ const client) override;

private:
	static BizElectronicModuleAbnormal^ _instance;
};

END_BIZ_NAMESPACE
