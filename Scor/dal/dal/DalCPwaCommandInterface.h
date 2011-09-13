/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCPwaCommandInterface.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for DalCPwaCommandInterface class
*/
#pragma once

#include "stdafx.h"
#include "DalCommandInterface.h"

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalCPwaCommandInterface: public DalCommandInterface
			{
				private:
					//Not overriding the position indexes for CPWA. 
					//As per mail from TS PWV command (0x03) is to be used for CPWA capture)
					/*static int _cuffPulseDataIndex = 0;
					static int _countdownTimerDataIndex = 2; 
					static int _cuffPressureDataIndex = 4;*/
					/*static int _tonometerDataIndex = 0;
					static int _cuffPulseDataIndex = 2;
					static int _cuffPressureDataIndex = 4;
					static int _countdownTimerDataIndex = 6; */


				internal:
					DalCPwaCommandInterface();
					
				public:
					/**
					* Processes a single packet from the streamign packet buffer.
					* @param[in]	streamingPacket A byte array to be processed
					* @return	The status of the operaton
					*/
					//virtual bool ProcessSingleStreamingPacket(array<unsigned char> ^ streamingPacket) override;
			};


		}//end namespaces
	}
}
