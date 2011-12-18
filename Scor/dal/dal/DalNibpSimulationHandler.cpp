/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpSimulationHandler.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Code file for DalNibpSimulationHandler class
*/

#include "stdafx.h"
#include "DalEventContainer.h"
#include "DalNibpSimulationHandler.h"
#include "DalDataBuffer.h"
#include "DalCommon.h"
#include "DalNibpStatusHandler.h"

using namespace System::ComponentModel;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::CrossCutting::Configuration;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			// Equivalent to NIBP CONNECT, START_BP & <O>
			bool DalNibpSimulationHandler::StartBP(DalNIBPMode nibpMode)
			{
				unsigned short locDuration;
				unsigned short locStatus;
				unsigned short locErrorCode;
				unsigned short locSP;
				unsigned short locDP;
				unsigned short locMP;
				unsigned short locHR;

				nibpMode;

				dataBufferObj = DalDataBuffer::Instance;

				//create array
				dataBufferObj->CreateBuffer(5, 4);
				//dataBufferObj->CreateBuffer(3, 3);
				DalPwvDataStruct tempbuff;

				for( unsigned short i=1; i<=15; i++)
				{
					tempbuff.cuffPressure = i*20;
					dataBufferObj->WriteDataToBuffer(tempbuff);
				}
				//Threading::Thread::Sleep(2000);

				for( unsigned short i=15; i>1; i--)
				{
					tempbuff.cuffPressure = i*20;
					dataBufferObj->WriteDataToBuffer(tempbuff);
				}

				if (!_nibpConnected)
				{
					_nibpConnected = true;
					//pick the NIBP sim file from another directory
					_nibpSimulationFile = gcnew DalSimulationFile(".\\simulation\\nibp\\nibp.dat");
				}

				// Read one NIBP record to simulate; local variables (non-static) are needed to pass ref to GetNextValues
				_nibpSimulationFile->GetNextValues(&locDuration, &locStatus, &locErrorCode, &locSP, &locDP, &locMP, &locHR);
				_nibpStatus = locStatus;
				_nibpErrorCode = locErrorCode;
				_nibpSP = locSP;
				_nibpDP = locDP;
				_nibpMP = locMP;
				_nibpHR = locHR;

				if (_nibpTimer == nullptr)
				{
					//specify the event handler to handle timer events
					_nibpTimer = gcnew Timers::Timer();
					_nibpTimer->Elapsed += gcnew ElapsedEventHandler(&DalNibpSimulationHandler::OnTimerDalNIBPDataEvent); 
				}
				//Start the timer.
				_nibpTimer->Interval = locDuration;
				_nibpTimer->Enabled = true;
				return true;
			}

			// Equivalent to NIBP DISCONNECT
			bool DalNibpSimulationHandler::FinishBP()
			{
				_nibpConnected = false;
				if (_nibpTimer)
				{
					_nibpTimer->Enabled = false;
					_nibpTimer->Elapsed -= gcnew ElapsedEventHandler(&DalNibpSimulationHandler::OnTimerDalNIBPDataEvent); 
					_nibpTimer = nullptr;
					delete _nibpSimulationFile;
				}
				return true;
			}

			// Equivalent to NIBP Abort_BP & <A>
			bool DalNibpSimulationHandler::AbortBP()
			{
				if (_nibpTimer)
				{
					_nibpTimer->Enabled = false;
				}
				return true;
			}

			// Simulate NIBP START_BP <K> 
			void DalNibpSimulationHandler::OnTimerDalNIBPDataEvent(Object^ sender, ElapsedEventArgs^ args)
			{
				unsigned short dalError4NIBP;
				String^ errorMessage = String::Empty ;
				NibpMeasurementStatus  resultStatus;

				args;
				_nibpTimer->Enabled = false;

				/* 
				   This is just an example.
				   All SunTech NIBP specific error codes must be translated to DAL NIBP error enum that are visible to BLL.
				*/
				resultStatus = DalNibpStatusHandler::ValidateBpData(_nibpErrorCode, _nibpStatus, errorMessage);
				
				if (resultStatus  == NibpMeasurementStatus::Successful)
				{
					// No error. New NIBP data is ready.
					dalError4NIBP = 0;
				}
				else
				{
					// Donot use NIBP data for other errors
					dalError4NIBP = 12345;
				}
								
				DalEventContainer::Instance->OnDalNIBPDataEvent(sender,
																gcnew DalNIBPDataEventArgs(dalError4NIBP, 
																						   _nibpSP, 
																						   _nibpDP, 
																						   _nibpMP, 
																						   _nibpHR,
																						   resultStatus,
																						   errorMessage));
				/*DalEventContainer::Instance->OnDalNIBPDataEvent(sender, 
																gcnew DalNIBPDataEventArgs(dalError4NIBP, 
																						   _nibpSP, 
																						   _nibpDP, 
																						   _nibpMP, 
																						   _nibpHR));
			*/
			}


			//TS Stub
			// Equivalent to SET_INITIAL_INFLATE & <O> <K>
			bool DalNibpSimulationHandler::SetBPInitialInflate(unsigned short )
			{
				return true;
			}

			//TS Stub
			// Start NIBP using initial inflate pressure
			bool DalNibpSimulationHandler::StartBP(DalNIBPMode nibpMode, unsigned short initialPressure)
			{
				bool startOK = false;

				// Set initial inflate pressure first before starting NIBP
				startOK = SetBPInitialInflate(initialPressure);
				if (startOK)
				{
					startOK = StartBP(nibpMode);
				}
				return startOK;
			}
		}
	}
}