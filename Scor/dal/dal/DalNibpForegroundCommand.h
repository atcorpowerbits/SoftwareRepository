/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpForegroundCommand.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  DalNibpForegroundCommand
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalEM4HostToNibpCommand.h"


using namespace System;
using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			/**
			* @class DalNibpForegroundCommand
			* @brief	Parent class of all foreground commands.
			*/
			private ref class DalNibpForegroundCommand: public DalEM4HostToNibpCommand
			{
				protected:
					/**
					* Constrcutor for this class
					*/
					DalNibpForegroundCommand();
					DalNibpForegroundCommandState currentForegroundState; //The current state of a command

					/**
					* Destructor for this class.
					*/
					~DalNibpForegroundCommand();
				internal:
					/**
					* Processes the specified packet. Overrides parent behavior
					* @param[in]	nibpToHostResponse	The NIPB response packet from EM4
					* @return	The status of the operation
					*/
					virtual bool ActOnPacket(array <unsigned char> ^ nibpToHostResponse) override;

					/**
					* Listener for a packet arrived event
					* @param[in]	responsePacket	The argument for this event		
					*/
					virtual void ResponseListenerThreadMethod(Object^ responsePacket) override;

				protected:	
					
					/**
					* Launces a thread that waits for a response for a specifed period of time and also
					* launches a listener for NIBP data arrived event
					* @return The status of the operation.
					*/
					virtual DalReturnValue ListenForEM4Response() override;

					/**
					* Stops all threads and de-registers all waiting listeners for this object.
					* @return The status of the operation.
					*/
					virtual bool StopListeningForEM4response() override;

					/**
					* Blank virtual method. Let child class decide what processing it wants to do after this.
					* This method is called when data arrives and is called from ActOnPacket()
					* The child classes will decide what they want to do.
					*
					* @return The status of the operation
					*/
					virtual DalReturnValue ProcessNibpResponse();

			};

		} //End namespace DataAccess
	}
}