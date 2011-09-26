/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpSimulationHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      code page for DalNibpSimulationHandler class.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "IDalNibpHandler.h"
#include "DalSimulationFile.h"

using namespace System;
using namespace System::IO;
using namespace System::Timers;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalNibpSimulationHandler 
			* @brief Class to operate in NIBP simulation mode.  
			*/
			
			private ref class DalNibpSimulationHandler : public IDalNibpHandler
			{
				private:
					//TS STUB
					static DalSimulationFile^ _nibpSimulationFile; //pointer to NIBP simulation file
					static Timers::Timer ^_nibpTimer = nullptr;  //Timer to fire simulated NIBP data event
					static bool _nibpConnected = false;
					static unsigned short _nibpStatus;
					static unsigned short _nibpErrorCode;
					static unsigned short _nibpSP;
					static unsigned short _nibpDP;
					static unsigned short _nibpMP;
					static unsigned short _nibpHR;

					bool SetBPInitialInflate(unsigned short initialPressure); //TS Stub
					
					static DalNibpSimulationHandler^ _instance = gcnew DalNibpSimulationHandler();

				public:
					
					/**
					* Returns the current singleton instance.
					*/
					static property DalNibpSimulationHandler^ Instance
					{
						DalNibpSimulationHandler^ get()
						{
							return DalNibpSimulationHandler::_instance;
						};
					};

					virtual bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure);

					virtual bool StartBP(DalNIBPMode nibpMode);

					virtual bool FinishBP();

					virtual bool AbortBP();

					static void OnTimerDalNIBPDataEvent(Object^ sender, ElapsedEventArgs^ args);
			};
		}
	}
}