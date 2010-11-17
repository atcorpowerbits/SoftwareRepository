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
using namespace DAL_NAMESPACE;

START_BIZ_NAMESPACE

public ref class BizElectronicModuleState abstract
{
public:
	virtual void Dispatch(String^ source) {};
	virtual void ReceiveNewStatus(BizElectronicModule^ const client, unsigned short newStatus) {};

protected:
	BizElectronicModuleState() {};
	static void ChangeState(BizElectronicModule^ const client, BizElectronicModuleState^ state);
};

// Electronic Module normal state
public ref class BizElectronicModuleNormal : BizElectronicModuleState
{
public:
	static BizElectronicModuleNormal^ Instance();
	virtual void Dispatch(String^ source) override;
	virtual void ReceiveNewStatus(BizElectronicModule^ const client, unsigned short newStatus) override;

private:
	static BizElectronicModuleNormal^ _instance;
};

// Electronic Module warning state
public ref class BizElectronicModuleWarning : BizElectronicModuleState
{
public:
	static BizElectronicModuleWarning^ Instance();
	virtual void Dispatch(String^ source) override;
	virtual void ReceiveNewStatus(BizElectronicModule^ const client, unsigned short newStatus) override;

private:
	static BizElectronicModuleWarning^ _instance;
};

// Electronic Module error state
public ref class BizElectronicModuleError : BizElectronicModuleState
{
public:
	static BizElectronicModuleError^ Instance();
	virtual void Dispatch(String^ source) override;
	virtual void ReceiveNewStatus(BizElectronicModule^ const client, unsigned short newStatus) override;

private:
	static BizElectronicModuleError^ _instance;
};

END_BIZ_NAMESPACE
