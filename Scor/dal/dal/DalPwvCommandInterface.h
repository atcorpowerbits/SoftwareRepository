/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalPWVCommandInterface.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for DalPwvCommandInterface class
*/
#pragma once

#include "stdafx.h"
#include "DalCommandInterface.h"

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalPwvCommandInterface
			* @brief	This class controls the device interface for PWV mode
			*/
			private ref class DalPwvCommandInterface: public DalCommandInterface
			{
				private:
					static int _tonometerDataIndex = 0;
					static int _cuffPulseDataIndex = 2;
					static int _cuffPressureDataIndex = 4;
					static int _countdownTimerDataIndex = 6; 
				internal:
					/**
					* Constructor for this class
					*/
					DalPwvCommandInterface();
				public:

					/**
					* Processes a single packet from the streamign packet buffer.
					* @param[in]	streamingPacket A byte array to be processed
					* @return	The status of the operaton
					*/
					virtual bool ProcessSingleStreamingPacket(array<unsigned char> ^ streamingPacket) override;
			};


		}//end namespaces
	}
}
