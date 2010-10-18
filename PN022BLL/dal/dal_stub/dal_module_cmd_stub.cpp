/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	cmd_states.cpp
	
	Author       :  Victor Aung

    Description  :	Business Logic Layer Elec. Module's Command State Classes
*/

#include "StdAfx.h"
#include <dal.h>
#include <dal_module_cmd_stub.h>

namespace DataAccess {
	DalModule::DalModule(void) 
	{
	}
	DalModule^ DalModule::Instance()
	{
		if (_instance == nullptr) 
		{
			_instance = gcnew DalModule;
		}
		return _instance;
	}
	bool DalModule::StartCapture()
	{
		bool startOK = false;
		return startOK;
	}
	bool DalModule::StopCapture()
	{
		bool stopOK = false;
		stopOK = true; // stub
		return stopOK;
	}
	void DalModule::SimulateCaptureData(unsigned int captureDataType)
	{
		// Normally, the timer is declared at the class level,
		// so that it stays in scope as long as it is needed.
		// If the timer is declared in a long-running method,  
		// KeepAlive must be used to prevent the JIT compiler 
		// from allowing aggressive garbage collection to occur 
		// before the method ends. (See end of method.)
		//System::Timers::Timer^ captureTimer;

		// Create a new Timer with Interval set in milliseconds.
		// e.g. ~4 ms for 256 samples/sec
		captureTimer = gcnew Timer(DalConstants::SIMULATION_TIMER_INTERVAL);

		// Hook up the Elapsed event for the timer.
		switch (captureDataType)
		{
		case DalConstants::DATA_TONOMETER_AND_CUFF_PULSE_COMBO:
			captureTimer->Elapsed += gcnew ElapsedEventHandler( &DalModule::OnCaptureTimedEvent );
			dataFile = gcnew DalSimulationFile("./pwv_default.dat");
			timerFile = gcnew DalSimulationFile("./cuff_timer.dat");
			break;
		default:
			return; // nothing to simulate
		}
		dataFile->OpenFile();
		timerFile->OpenFile();
		countDown = 0;
		captureTimer->Enabled = true;

		// If the timer is declared in a long-running method, use
		// KeepAlive to prevent garbage collection from occurring
		// before the method ends.
		//GC::KeepAlive(captureTimer);
	}
	void DalModule::OnCaptureTimedEvent( Object^ source, ElapsedEventArgs^ e )
	{
		short tonometerData;
		short cuffPulse;
		short newPressure;
		short newStatus;
		short newCountdown;

		// Read new timer data if it's counted down to zero
		if (DalModule::Instance()->countDown <= 0) 
		{
			DalModule::Instance()->timerFile->GetNextValues(
				&newCountdown,
				&newPressure,
				&newStatus);
			DalModule::Instance()->countDown = newCountdown * 1000;
			DalModule::Instance()->cuffPressure = newPressure;
			DalModule::Instance()->status = newStatus;
		}
		// Read PWV simulation data
		DalModule::Instance()->dataFile->GetNextValues(
			&tonometerData, 
			&cuffPulse);

		// Notify observers to generate corresponding events
		DalMeter::Instance()->tonometerDataEvent->Notify(tonometerData);
		DalMeter::Instance()->cuffPulseEvent->Notify(cuffPulse);
		DalMeter::Instance()->countdownTimerEvent->Notify(DalModule::Instance()->countDown);
		DalMeter::Instance()->cuffStatusEvent->Notify(DalModule::Instance()->status & 0x2F);
		DalMeter::Instance()->cuffPressureEvent->Notify(DalModule::Instance()->cuffPressure);

		// Countdown the timer by the amount of simulation interval
		DalModule::Instance()->countDown -= DalConstants::SIMULATION_TIMER_INTERVAL;
	}

	void DalModule::StopCaptureSimulation()
	{
		captureTimer->Enabled = false; // stop simulation
		dataFile->CloseFile();
		timerFile->CloseFile();
	}
/*	void DalModule::SimulateDeflationTimer()
	{
		// Start to count down for deflation
		countdownSecLeft = DAL_SIM_COUNTDOWN_DEFLATION;
		countdownState = DAL_SIM_COUNTDOWN_STATE_DEFLATION;

		// Create a new Timer with Interval set in milliseconds.
		countdownTimer = gcnew Timer (1000);
		countdownTimer->Elapsed += gcnew ElapsedEventHandler( &DalModule::OnCountdownTimedEvent );
		countdownTimer->Enabled = true;
	}
	void DalModule::StopDeflationTimerSimulation()
	{
		countdownTimer->Enabled = false; // stop simulation
	}
	void DalModule::OnCountdownTimedEvent( Object^ source, ElapsedEventArgs^ e )
	{
		countdownSecLeft--;
		DalCountdownStub::Instance()->countdownRaw->Notify(countdownSecLeft);
		if (countdownSecLeft == 0) 
		{
			switch (countdownState)
			{
			case DAL_SIM_COUNTDOWN_STATE_DEFLATION:
				countdownSecLeft = DAL_SIM_COUNTDOWN_REST;
				countdownState = DAL_SIM_COUNTDOWN_STATE_REST;
				break;
			case DAL_SIM_COUNTDOWN_STATE_REST:
				countdownSecLeft = DAL_SIM_COUNTDOWN_DEFLATION;
				countdownState = DAL_SIM_COUNTDOWN_STATE_DEFLATION;
				break;
			default:
				break;
			}
		}
	}
*/
}