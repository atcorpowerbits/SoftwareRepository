/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	cmd_states.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Meter Command States
*/

#pragma once

#include "dal_meter_data_stub.h"

namespace DataAccess {
	ref class DalMeter; // needed for forward declaration

	public ref class DalMeterCommand abstract
	{
	protected:
		DalMeterCommand() {};
	public:
		virtual void Execute() = 0;
	};
	public ref class DalStartPWVCommand : DalMeterCommand 
	{
	public:
		virtual void Execute() override {};
	};
	public ref class DalMeterState abstract
	{
	protected:
		void ChangeState(DalMeter^ const m, DalMeterState^ %s);
	public:
		virtual int ConfirmCommand(DalMeter^ const m) { return false; };
		virtual bool StartCapture(DalMeter^ const m) { return false; };
		virtual bool StopCapture(DalMeter^ const m) { return false; };
		virtual void ReceiveResponse(DalMeter^ const m) {};
		virtual void ReceiveStream(DalMeter^ m) {};
	};
	ref class DalMeterIdle : DalMeterState
	{
	private:
		static DalMeterIdle^ _instance;
	public:
		static DalMeterIdle^ Instance();
		virtual bool StartCapture(DalMeter^ const m) override;
	};
	ref class DalMeterWaitConfirmation : DalMeterState
	{
	private:
		static DalMeterWaitConfirmation^ _instance;
	public:
		static DalMeterWaitConfirmation^ Instance();
		virtual int ConfirmCommand(DalMeter^ const m) override;
	};
	ref class DalMeterCapturing : DalMeterState
	{
	private:
		static DalMeterCapturing^ _instance;
	public:
		static DalMeterCapturing^ Instance();
	};
	ref class DalMeterWaitResponse : DalMeterState
	{
	private:
		static DalMeterWaitResponse^ _instance;
	public:
		static DalMeterWaitResponse^ Instance();
		virtual void ReceiveResponse(DalMeter^ const m) override;
	};
	public ref class DalMeter
	{
	public:
		DalMeter(void);
		DalTonoData^ tonoDataRaw;
		int StartCapture();
		bool StopCapture();
//???	private:
//???		friend class DalMeterState;
		void ChangeState(DalMeterState^ s);
		DalMeterCommand^ command;
	private:
		DalMeterState^ _state;
		DalMeterCommand^ _command;
	};
}

