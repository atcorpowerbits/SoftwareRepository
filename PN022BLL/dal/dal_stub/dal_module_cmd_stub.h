/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	cmd_states.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Meter Command States
*/

#pragma once

#include "dal_meter_stub.h"
#include "dal_simulation_file.h"

using namespace System;
using namespace System::Collections::Generic;

namespace DataAccess {
	ref class DalModuleCommand; // needed for forward declaration
	ref class DalModuleCommandState; // needed for forward declaration

	public ref class DalModule
	{
	public:
		DalModule(void);
		int StartCapture();
		bool StopCapture();
//???	private:
//???		friend class DalModuleCommandState;
		void ChangeState(DalModuleCommandState^ s);
//?		DalModuleCommand^ command;

		static System::Timers::Timer^ captureTimer;
		static System::Timers::Timer^ countdownTimer;

		void SimulateCaptureData(unsigned int captureDataType);
		void StopCaptureSimulation();
		void SimulateDeflationTimer();
		void StopDeflationTimerSimulation();

		static DalModule^ Instance();
		static DalSimulationFile^ dataFile;

		static const unsigned short DAL_SIM_COUNTDOWN_DEFLATION = 180; // 3 min in sec
		static const unsigned short DAL_SIM_COUNTDOWN_REST = 30; // in sec
		static const unsigned short DAL_SIM_COUNTDOWN_STATE_DEFLATION = 1;
		static const unsigned short DAL_SIM_COUNTDOWN_STATE_REST = 2;
	private:
		static DalModule^ _instance;
		DalModuleCommandState^ _state;
//?		DalModuleCommand^ _command;
		Queue<int>^ captureQueue;
		static unsigned int countdownSecLeft;
		static unsigned int countdownState;

		// Specify what you want to happen when the Elapsed event is 
		// raised.
		static void OnCaptureTimedEvent( Object^ source, ElapsedEventArgs^ e );
		static void OnCountdownTimedEvent( Object^ source, ElapsedEventArgs^ e );
	};

	public ref class DalModuleCommand abstract
	{
	protected:
		DalModuleCommand() {};
	public:
		virtual void Execute() = 0;
	};
	public ref class DalStartPWVCommand : DalModuleCommand 
	{
	public:
		virtual void Execute() override {};
	};

	public ref class DalModuleCommandState abstract
	{
	protected:
		void ChangeState(DalModule^ const m, DalModuleCommandState^ %s);
	public:
		virtual int ConfirmCommand(DalModule^ const m) { return false; };
		virtual bool StartCapture(DalModule^ const m) { return false; };
		virtual bool StopCapture(DalModule^ const m) { return false; };
		virtual void ReceiveResponse(DalModule^ const m) {};
//?		virtual void ReceiveStream(DalModule^ m) {};
	};
	ref class DalMeterIdle : DalModuleCommandState
	{
	private:
		static DalMeterIdle^ _instance;
	public:
		static DalMeterIdle^ Instance();
		virtual bool StartCapture(DalModule^ const m) override;
	};
	ref class DalMeterWaitConfirmation : DalModuleCommandState
	{
	private:
		static DalMeterWaitConfirmation^ _instance;
	public:
		static DalMeterWaitConfirmation^ Instance();
		virtual int ConfirmCommand(DalModule^ const m) override;
	};
	ref class DalMeterCapturing : DalModuleCommandState
	{
	private:
		static DalMeterCapturing^ _instance;
	public:
		static DalMeterCapturing^ Instance();
	};
	ref class DalMeterWaitResponse : DalModuleCommandState
	{
	private:
		static DalMeterWaitResponse^ _instance;
	public:
		static DalMeterWaitResponse^ Instance();
		virtual void ReceiveResponse(DalModule^ const m) override;
	};

}
