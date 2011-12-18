/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalPwvDeviceHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalPwvDeviceHandler class defintition
*/

#pragma once

#include "stdafx.h"
#include "DalDeviceHandler.h"

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class DalPwvDeviceHandler
			* @brief	The class that handles the EM4 device for PwvMode
			*/
			private ref class DalPwvDeviceHandler: public DalDeviceHandler
			{
				internal:
					
					/**
					* Constructor for this class.
					*/
					DalPwvDeviceHandler();

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