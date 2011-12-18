/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSpecificForegroundCommands.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for all DalNibpForegroundCommand derived classes
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalNibpForegroundCommand.h"


using namespace System;
using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			/**
			* @class	DalNibpIntialInflateCommand
			* @brief	Class to send the SET_INITIAL_INFLATE Nibp command
			*/
			private ref class DalNibpIntialInflateCommand: public DalNibpForegroundCommand
			{
				private :
					//the pressure value to be used as initial for the measurement
					int initialPressure;

				internal:
					/**
					* Constructor 
					* @param[in]	initalInflatePressure	The initial pressure to set for the BP measurement
					* @param[in]	responseWaitTime	The time in MS to wait for an O & K packet for this command
					*/
					DalNibpIntialInflateCommand(int initalInflatePressure, unsigned int responseWaitTime);

					/**
					* Sends the Initial Inflate command to the NIBP module
					* @return The result of the operation.
					*/
					bool SetInitialInflate();
			public:

					/**
					* Overriden child method which processes an NIBP response packet
					* @return The result of the operation.
					*/
					virtual DalReturnValue ProcessNibpResponse() override;

			};



			/**
			* @class	DalNibpStartBpCommand
			* @brief	Class to send the START_BP Nibp command
			*/
			private ref class DalNibpStartBpCommand: public DalNibpForegroundCommand
			{
				protected:
					
					
					unsigned int kPacketWaitTime;// the wait time between the O & K packets

				internal:
					DalNibpStartBpCommand(); //Constructor for the  
					//FxCop
					///*
					//* Constructors: sets the specified wait time as the time for K packet
					//* @param[in]	responseWaitTime	The k Packet waiting time
					//*/
					//DalNibpStartBpCommand(int responseWaitTime);
					

					/**
					* Sends the StartBP command and retirves the response@n
					* This method returns after the O packet is recieved or a timeout occurs
					* while waiting for A
					* @return The status of the operation
					*/
					bool SendStartBpCommand();

					Thread^ kPacketListenerThread; //A thread to wait for the k packet 
				public:

					/**
					* Overriden child method which processes an NIBP response packet@n
					* Waits for an O packet and then launches a separate listener for the K packet
					* @return The result of the operation.
					*/
					virtual DalReturnValue  ProcessNibpResponse() override;

					/**
					* Thread method that waits for a K packet.
					* @param[in]	responsePacket	THe object for the event
					*/
					virtual void ListenerForKPacketThreadMethod(Object^ responsePacket) ;
			};

			/**
			* @class	DalNibpStartPediatricBpCommand
			* @brief	Class to send the START_PEDIATRIC_BP Nibp command
			*/
			private ref class DalNibpStartPediatricBpCommand: public DalNibpStartBpCommand
			{
				internal:
					/**
					* Default constructor for the class.
					*/
					DalNibpStartPediatricBpCommand();

			};

			/**
			* @class	DalNibpStartNeonateBpCommand
			* @brief	Class to send the START_Neonate_BP Nibp command
			*/
			private ref class DalNibpStartNeonateBpCommand: public DalNibpStartBpCommand
			{
				internal:
					/**
					* Default constructor for the class.
					*/
					DalNibpStartNeonateBpCommand();

			};


			/**
			* @class	DalNibpAbortBpCommand
			* @brief	Class to send the ABORT_BP Nibp command
			*/
			private ref class DalNibpAbortBpCommand:public DalNibpForegroundCommand
			{
				private:
					//Default constructor for the class
					DalNibpAbortBpCommand();

				internal:
					/**
					* Constructor which initializes the class with the specified response time
					* @param[in]	responseWaitTime	The time to wait for a valid response
					*/
					DalNibpAbortBpCommand(int responseWaitTime);

					/**
					* Sends the ABort BP command to NIBP module and waits for a response.
					* @return	The status of the operation
					*/
					bool AbortBp();

				public:
					/**
					* Overriden child method which processes an NIBP response packet@n
					* @return The result of the operation.
					*/
					virtual DalReturnValue ProcessNibpResponse() override;

			};


		} //End namespace DataAccess
	}
}
