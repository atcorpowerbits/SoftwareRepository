/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	cmd_states.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of Meter Command States
*/

#pragma once

#include "dal_namespace.h"
#include "dal_meter_stub.h"
#include "dal_simulation_file.h"

using namespace System;
using namespace System::Collections::Generic;

START_DAL_NAMESPACE

public ref class DalModule
{
public:
	DalModule(void);
	bool StartCapture();
	bool StopCapture();

	static System::Timers::Timer^ captureTimer;

	void SimulateCaptureData(unsigned int captureDataType);
	void StopCaptureSimulation();

	static DalModule^ Instance();
	static DalSimulationFile^ dataFile;
	static DalSimulationFile^ timerFile;

	static const unsigned short DAL_SIM_COUNTDOWN_DEFLATION = 180; // 3 min in sec
	static const unsigned short DAL_SIM_COUNTDOWN_REST = 30; // in sec
	static const unsigned short DAL_SIM_COUNTDOWN_STATE_DEFLATION = 1;
	static const unsigned short DAL_SIM_COUNTDOWN_STATE_REST = 2;
private:
	static DalModule^ _instance;
	static short countDown;
	static short cuffPressure;
	static short status;

	// Specify what you want to happen when the Elapsed event is 
	// raised.
	static void OnCaptureTimedEvent( Object^ source, ElapsedEventArgs^ e );
};
END_DAL_NAMESPACE
