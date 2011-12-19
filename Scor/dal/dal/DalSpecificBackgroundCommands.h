/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSpecificBackgroundCommands.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for all DalNibpBackgroundCommand derived classes
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalNibpBackgroundCommand.h"


using namespace System;
using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class	DalCuffPressureCommand
			* @brief	Class to get a cuff pressure reading.
			*/
			private ref class DalCuffPressureCommand: public DalNibpBackgroundCommand
			{
				public:
					/**
					* Constructor for this command.
					*/
					DalCuffPressureCommand();

			protected:
				/**
				* Overriden member that processes the NIBP response object
				* @return The result of the operation
				*/
				virtual bool ProcessNibpResponse() override;
			internal:
				/**
				* Sends a command to the NIBP module and gets the cuff pressure
				* @param[out]	cuffPressure	The result of this measurement
				* @return The status of this operation.
				*/
				bool GetCuffPressure(unsigned int& cuffPressure);

			};

			/**
			* @class	DalNibpGetBpDataCommand
			* @brief	Class to get BP data after a BP measurement session is completed.
			*/
			private ref class DalNibpGetBpDataCommand: public DalNibpBackgroundCommand
			{
				public:
					//Constructor
					DalNibpGetBpDataCommand();
				protected:
					/**
					* Overriden member that processes the NIBP response object
					* @return The result of the operation
					*/
					virtual bool ProcessNibpResponse() override;

				internal:
					/**
					* Sends a command to NIBP module to Get BP Data and raises an event if succesful
					* @return The status of the operation
					*/
					bool GetBpDataAndRaiseEvent();

					/**
					* Processes an EM4 response
					* @param[in]	nibpToHostResponse	The nibp Packet to process
					* @return	The status of the operation.
					*/
					virtual bool ActOnPacket(array <unsigned char> ^ nibpToHostResponse) override;

				private:
					DalNibpData^  _nibpDataObject; //Pointer to the recieved NIBP data
					bool CheckRecievedData(); //Validates the recieved NIBP response
					void ExtractDataParts(); //Splits the array into its constituent parts.


			};



		} //End namespace DataAccess
	}
}
