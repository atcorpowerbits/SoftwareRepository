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
					*	Asynchronous listener that waits for a response to arrive in the response buffer
					*	Times out if no data is recieved within the expected time as specifed in the repsonsePacket
					*
					*	@param[in,out]	responsePacket	The EM4 command-repsonse object in which the response is copied 
					*/
					void PacketArrivedProcessingMethod(Object^ source, NibPacketArrivedEventArgs^ args);
					
					/**
					* Obtains the response from the port for the command sent by SendCommand
					* @param[in,out] serialCommand	A DalEM4Command object which has been initialized  with a valid command.
					*								This method  will write the EM4 response to the same structure.
					* @return The status of the operation: succeded/ failed/ timout/ nack
					* @warning Do not use for data capture.
					*/
					virtual DalReturnValue ListenForEM4Response();

					virtual bool StopListeningForEM4response();

				
				internal:
					void SetCommandInterface(DalNibpCommandInterface^ newInterface);

					//DalEM4HostToNibpCommand(DalNibpCommandType type, array<unsigned char> ^ nibpPacket, unsigned int responseWaitTime);

					DalReturnValue SendCommandAndGetResponse();

					virtual bool ActOnPacket(array <unsigned char> ^ nibpToHostResponse);

					virtual void ResponseListenerThreadMethod(Object^ responsePacket);
				

			};


			




		} //End namespace DataAccess
	}
}