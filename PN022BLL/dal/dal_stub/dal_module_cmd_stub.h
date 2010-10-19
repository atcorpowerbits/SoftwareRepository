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
	public ref class DalModule
	{
	public:
		DalModule(void);
		bool StartCapture();
		bool StopCapture();

		static System::Timers::Timer^ captureTimer;
//		static System::Timers::Timer^ countdownTimer;

		void SimulateCaptureData(unsigned int captureDataType);
		void StopCaptureSimulation();
//		void SimulateDeflationTimer();
//		void StopDeflationTimerSimulation();

		static DalModule^ Instance();
		static DalSimulationFile^ dataFile;
		static DalSimulationFile^ timerFile;

		static const unsigned short DAL_SIM_COUNTDOWN_DEFLATION = 180; // 3 min in sec
		static const unsigned short DAL_SIM_COUNTDOWN_REST = 30; // in sec
		static const unsigned short DAL_SIM_COUNTDOWN_STATE_DEFLATION = 1;
		static const unsigned short DAL_SIM_COUNTDOWN_STATE_REST = 2;
	private:
		static DalModule^ _instance;
//		static unsigned int countdownSecLeft;
//		static unsigned int countdownState;
		static short countDown;
		static short cuffPressure;
		static short status;

		// Specify what you want to happen when the Elapsed event is 
		// raised.
		static void OnCaptureTimedEvent( Object^ source, ElapsedEventArgs^ e );
//		static void OnCountdownTimedEvent( Object^ source, ElapsedEventArgs^ e );
	};
}