/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCPwaDeviceHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalCPwaDeviceHandler class defintition
*/

#pragma once

#include "stdafx.h"
#include "DalDevicehandler.h"


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalCPwaDeviceHandler: public DalDeviceHandler
			{	
			internal:
				DalCPwaDeviceHandler();
			public:

				/**
				* Start the data capture fromt the device. @n
				* Creates a buffer suitable for the specified time and sampling rate.
				* @param[in]	captureTime	the time frame in seconds for the capture window
				* @param[in]	samplingRate	The number of samples per second
				* @return A boolean value indicating succes of the operation
				*
				*/
				virtual bool StartCapture(int captureTime, int samplingRate) override;
			};

		} //End namespaces
	}
}