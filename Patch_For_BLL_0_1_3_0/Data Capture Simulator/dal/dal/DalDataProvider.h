#pragma once

#include "stdafx.h"
#include "DalSimulationFile.h"
#include "DalCommandInterface.h"
#include "DalDataBuffer.h"

#include "DalCommon.h"

using namespace System;
using namespace System::IO;

namespace AtCor{ 
	namespace Scor{ 
		namespace DataAccess{

			public ref class DalDataProvider
			{

				private:
					static DalCommandInterface ^ dci ; 
					static bool firstReadAfterCaptureStarted = false;

					
					
					static DalSimulationFile^ _tonometerSimulationFile; //Pointer to first simulation file
					static DalSimulationFile^ _cuffTimerSimulationFile; //pointer to second simulation file (for other cuff related measurements)
					static Timers::Timer ^captureTimer;  //Timer to fire simulated data events
					static void OnTimerGetValuesAndSendData(Object^ sender, ElapsedEventArgs^ args); //Method to raise events at a specific time imterval //TODO:STUB
					static void ReadAndSendSerialData(Object^ sender);

					static void PcCommandResolver(Object^ sender, PCCommandRecievedEventArgs ^args);

				public:
					
					DalDataProvider(); //Constructor
					static bool StartSendingData(); //Start the simulation capture 
					static bool StopSendingData(); //Stop the simulation capture

					bool StartListeningToPCCommands(); //Start the slistening
					bool StopListeningToPCCommands(); //Stop the simulation capture
					static DalEM4Command ^ GenerateNackPacket(DalEM4Command ^commandSource);

					static bool ReplyToPCRequest(unsigned char inCommandCode, array<unsigned char> ^% outReplyData);

			};

		}//end namespace DataAccess
	}// end namespace Scor
}//end namespace AtCor




