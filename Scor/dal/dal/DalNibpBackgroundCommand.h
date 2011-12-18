/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpBackgroundCommand.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  DalNibpBackgroundCommand
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
			* @class DalNibpBackgroundCommand
			* @brief Parent class to impmenet all background command behaviours.
			*/
			private ref class DalNibpBackgroundCommand: public DalEM4HostToNibpCommand
			{
				protected:
					/**
					* Default constructor
					*/
					DalNibpBackgroundCommand();
					DalNibpBackGroundCommandState currentBackGroundState; /**< The current state of the commans */
				internal:
					//DalNibpBackgroundCommand(array<unsigned char> ^ nibpPacket, unsigned int responseWaitTime);

					/**
					* Processes an EM4 response
					* @param[in]	nibpToHostResponse	The nibp Packet to process
					* @return	The status of the operation.
					*/
					virtual bool ActOnPacket(array <unsigned char> ^ nibpToHostResponse) override;
					
					/**
					* Thread method that waits for Em4 response
					* @param[in]	responsePacket	The object for this event
					*/
					virtual void ResponseListenerThreadMethod(Object^ responsePacket) override;

				protected:	
					/**
					* Obtains the response from the port for the command sent by SendCommand
					* @return The status of the operation: succeded/ failed/ timout/ nack
					*/
					virtual DalReturnValue ListenForEM4Response() override;
					
					/**
					* Stops all threads and event handlers
					* @return	The status of the operation.
					*/
					virtual bool StopListeningForEM4response() override;

					/**
					* Process the recieved response packet.
					* THis is an empty method. Let child class decide what processing it wants to do after this.
					* @return The status of the operation.
					*/
					virtual bool ProcessNibpResponse();


			};


		} //End namespace DataAccess
	}
}