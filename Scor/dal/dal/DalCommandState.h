/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCommandState.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for the command state machine.
*/


#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalEM4Command.h"

using namespace System;


namespace AtCor{
	namespace Scor {
		namespace DataAccess {
			/**
			* @namespace AtCor::Scor::DataAccess::StateMachines
			* @brief	Namepsace to contain state machine related code.
			*/
			namespace StateMachines{ 
	

	/**
	* @class DalCommandState
	* @brief Abstract base class for the command state machine. @n
	*		Contains default behaviour for the various functions handled by this state machine.
	* @warning Default behaviour for all methods is to return a flase or to do nothing. 
	*			Child state classes must override this behaviour as appropriate to implement them.
	*/
	private ref class DalCommandState
	{
		protected:
			DalCommandState();

		public:
		    
			/**
			* Send the command specifed in the parameter and processes the response from EM4
			* @warning This command was previously known as SendCommand() 
			* but has been renamed to make it more meaningful. It is now a facade for ProcessCommandAndResponse()
			*
			* @param[in,out] serialCommand	A DalEM4Command object which has been initialized  with a valid command.
			* @return The status of the operation: succeded/ failed/ timout/ nack
			*/
			virtual DalReturnValue SendCommandAndGetResponse(DalEM4Command^ serialCommand); 

			/**
			* Validates the CRC of the EM4 response for a succesfully sent command
			* @param[in]	serialCommand	The succesful sent & received data packet
			* @return	boolean value indiciating status of the operation
			*/
			virtual DalReturnValue ValidateResponsePacket(DalEM4Command^ serialCommand);

			/**
			* Obtains the response from the port for the command sent by SendCommand
			* @param[in,out] serialCommand	A DalEM4Command object which has been initialized  with a valid command.
			*								This method  will write the EM4 response to the same structure.
			* @return The status of the operation: succeded/ failed/ timout/ nack
			*/
			virtual DalReturnValue ListenForEM4Response(DalEM4Command^ serialCommand);
	};

	/**
	* @class DalCommandStateReady
	* @brief Represents the State in which the  DAL is not processing any command and is ready to send commands to EM4@n
	*		The only valid command for this state is SendCommandAndGetResponse.
	*/
	private ref class DalCommandStateReady : public DalCommandState
	{
		private : 
			static DalCommandStateReady^ _instance = gcnew DalCommandStateReady();

			DalCommandStateReady();
			DalCommandStateReady^ operator = (const DalCommandStateReady^);

		public:
			/**
			* Singleton instnace for this class.
			*/
			static property DalCommandStateReady^ Instance
			{
				DalCommandStateReady^ get()
				{
					return DalCommandStateReady::_instance; 
				};
			};

			/**
			* Sends a command and gets a response from EM4.
			*/
			virtual DalReturnValue SendCommandAndGetResponse(DalEM4Command^ serialCommand) override; 
	};


	/**
	* @class DalCommandStateWaiting
	* @brief Represents the State in which the DAL is has sent a command and is waiting for a response from EM4.@n
	*		The only valid command for this state is ListenForEM4Response.
	*/
	private ref class DalCommandStateWaiting : public DalCommandState
	{
		private : 
			static DalCommandStateWaiting^ _instance = gcnew DalCommandStateWaiting();

			DalCommandStateWaiting();
			DalCommandStateWaiting^ operator = (const DalCommandStateWaiting^);

		public:
			/**
			* Singleton instnace for this class.
			*/
			static property DalCommandStateWaiting^ Instance
			{
				DalCommandStateWaiting^ get()
				{
					return DalCommandStateWaiting::_instance; 
				};
			};

			/**
			* Listens for a reply from the EM4 for a sent command
			*/
			virtual DalReturnValue ListenForEM4Response(DalEM4Command^ serialCommand) override;
	};

	/**
	* @class DalCommandStateTimeout
	* @brief Represents the State in which the DAL has not recieved a response from EM4 within a specified time.@n
	*		This state is only representative and does not have any valid commands.
	*/
	private ref class DalCommandStateTimeout : public DalCommandState
	{
		private : 
			static DalCommandStateTimeout^ _instance = gcnew DalCommandStateTimeout();

			DalCommandStateTimeout();
			DalCommandStateTimeout^ operator = (const DalCommandStateTimeout^);

		public:
			/**
			* Singleton instnace for this class.
			*/
			static property DalCommandStateTimeout^ Instance
			{
				DalCommandStateTimeout^ get()
				{
					return DalCommandStateTimeout::_instance; 
				};
			};
	};

	/**
	* @class DalCommandStateResponseReceived
	* @brief Represents the State in which the DAL has recieved a response from EM4 .@n
	*		The only valid command in this state is ValidateResponsePacket.
	*/
	private ref class DalCommandStateResponseReceived : public DalCommandState
	{
		private : 
			static DalCommandStateResponseReceived^ _instance = gcnew DalCommandStateResponseReceived();

			DalCommandStateResponseReceived();
			DalCommandStateResponseReceived^ operator = (const DalCommandStateResponseReceived^);

		public:
			/**
			* Singleton instnace for this class.
			*/
			static property DalCommandStateResponseReceived^ Instance
			{
				DalCommandStateResponseReceived^ get()
				{
					return DalCommandStateResponseReceived::_instance; 
				};
			};

			/**
			* Validates a recieved response packet.
			*/
			virtual DalReturnValue ValidateResponsePacket(DalEM4Command^ serialCommand) override ;
	};


			} //namespace StateMachines
		} //namespace DataAccess 
	} //namespace Scor
}//namespace AtCor
