/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	capture.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Business Logic Layer Cuff State.
*/

#pragma once

#include <cuff.h>
#include <biz_namespace.h>

using namespace System;

START_BIZ_NAMESPACE
	public ref class BizCuffState abstract
	{
	public:
		virtual void Disconnect(BizCuff^ const client) {};
		virtual void InflateNow(BizCuff^ const client) {};
		virtual void FinishInflating(BizCuff^ const client) {};
		virtual void DeflateNow(BizCuff^ const client) {};
		virtual void FinishDeflating(BizCuff^ const client) {};
		virtual void Connect(BizCuff^ const client) {};
		property String^ internalName;

	protected:
		BizCuffState() {};
		static void ChangeState(BizCuff^ const client, BizCuffState^ state);
	};

	// Cuff not connected state
	public ref class BizCuffDisconnected : BizCuffState
	{
	public:
		static BizCuffDisconnected^ BizCuffDisconnected::Instance();
		virtual void Connect(BizCuff^ const client) override;

	private:
		static BizCuffDisconnected^ _instance;
	};

	// Cuff connected / deflated state
	public ref class BizCuffDeflated : BizCuffState
	{
	public:
		static BizCuffDeflated^ BizCuffDeflated::Instance();
		virtual void Disconnect(BizCuff^ const client) override;
		virtual void InflateNow(BizCuff^ const client) override;

	private:
		static BizCuffDeflated^ _instance;
	};

	// Cuff inflating state
	public ref class BizCuffInflating : BizCuffState
	{
	public:
		static BizCuffInflating^ BizCuffInflating::Instance();
		virtual void FinishInflating(BizCuff^ const client) override;
		virtual void DeflateNow(BizCuff^ const client) override;

	private:
		static BizCuffInflating^ _instance;
	};

	// Cuff inflated state
	public ref class BizCuffInflated : BizCuffState
	{
	public:
		static BizCuffInflated^ BizCuffInflated::Instance();
		virtual void DeflateNow(BizCuff^ const client) override;

	private:
		static BizCuffInflated^ _instance;
	};

	// Cuff deflating state
	public ref class BizCuffDeflating : BizCuffState
	{
	public:
		static BizCuffDeflating^ BizCuffDeflating::Instance();
		virtual void FinishDeflating(BizCuff^ const client) override;

	private:
		static BizCuffDeflating^ _instance;
	};

	// Cuff resting state
	public ref class BizCuffResting : BizCuffState
	{
	public:
		static BizCuffResting^ BizCuffResting::Instance();
		virtual void Connect(BizCuff^ const client) override;

	private:
		static BizCuffResting^ _instance;
	};
END_BIZ_NAMESPACE
