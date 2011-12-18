/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalEM4HostToNibpCommand.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  DalEM4HostToNibpCommand
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalNibpCommandInterface.h"
#include "DalEventContainer.h"

using namespace System;
using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			private ref class DalEM4HostToNibpCommand
			{
				protected:
					array<unsigned char> ^ nibpCommandPacket;
					//DalNibpCommandType commandType;
					//bool responseRecievedFlag;
					unsigned int responseWaitingTimeMax;
					DalNibpCommandInterface^ _commandInterface;
					Thread^ responseListenerThread;
					array<unsigned char> ^ nibpResponsePacket;


					DalEM4HostToNibpCommand(); //dont allow user to instantiate this object
					~DalEM4HostToNibpCommand();

					/**
					* Processes an incomming NIBP packet when the event is raised.
					*
					* @param[in]  source	The object that raised this event
					* @param[in]	args	The event arguments
					*/
					void PacketArrivedProcessingMethod(Object^ source, NibPacketArrivedEventArgs^ args);
					
					/**
					* Obtains the response from the port for the command sent by SendCommand
					* @return The status of the operation: succeded/ failed/ timout/ nack
					*/
					virtual DalReturnValue ListenForEM4Response();

					/**
					* Stops all threads and event handlers
					* @return	The status of the operation.
					*/
					virtual bool StopListeningForEM4response();

				
				internal:
					/**
					* Dependency injection method
					* @param[in]	newInterface	The DalNibpCommandInterface to link to.
					*/
					void SetCommandInterface(DalNibpCommandInterface^ newInterface);

					/**
					* Sends a command and waits for a response from NIBP module
					* return	The status of the operation.
					*/
					DalReturnValue SendCommandAndGetResponse();

					/**
					* Processes an EM4 response
					* @param[in]	nibpToHostResponse	The nibp Packet to process
					* @return	The status of the operation.
					*/
					virtual bool ActOnPacket(array <unsigned char> ^ nibpToHostResponse);

					/**
					* Thread method that waits for Em4 response
					* @param[in]	responsePacket	The object for this event
					*/
					virtual void ResponseListenerThreadMethod(Object^ responsePacket);
				

			};


			




		} //End namespace DataAccess
	}
}