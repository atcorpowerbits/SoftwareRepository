/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalCaptureState.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for the async timeout machine.
*/



#pragma once

#include "stdafx.h"

using namespace System;
using namespace System::IO::Ports;
using namespace System::Timers;


namespace AtCor{
	namespace Scor {
		namespace DataAccess {
			namespace StateMachines{


	/**
	* @class DalCaptureState
	* @brief Abstract base class for the capture state machine. @n
	*		Contains default behaviour for the various functions handled by this state machine.
	* @warning Default behaviour for all methods is to return a flase or to do nothing. 
	*			Child state classes must override this behaviour as appropriate to implement them.
	*/
	private ref class DalCaptureState
	{
		public:
			/**
			* Registers the DataCaptureSinglePacketHandler to listen to data caputre packets
			* @return	status of the operation
			*/
			virtual bool InitiateDataCaptureMode();

	
			/**
			* De-registers the DataCaptureSinglePacketHandler to listen to data caputre packets
			* @return	status of the operation
			*/
			virtual bool StopDataCaptureMode();

			///*
			//* Processes the input buffer for data packets. @n
			//* Reads multiple data packets in a loop and writes them to the circula buffer.
			//* @param[in]	sender	Event sender. 
			//* @param[in]	e	Event arguments
			//* @see DataCaptureMultiplePacketHandler
			//*/
			//virtual void ReadFromPortAndWriteToBuffer(Object^ sender, SerialDataReceivedEventArgs^ e);

			virtual bool ProcessStreamingPackets();

			/**
			* Event handler to check if data buffer is empty.
			* Increments a counter if the buffer is empty and resets it to zero
			* if it is not. If the counter reaches @ref DalConstants::MaxStreamingTimeoutOccurrences 
			* then it raises an OnDalModuleErrorAlarmEvent
			*
			* @param[in]	sender	The object that raised this event.
			* @param[out]	args	The timer event arguments.
			*
			*/
			virtual void CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args);
	};


	/**
	* @class DalCaptureStateNotListening
	* @brief Child class that represents the EM4 when it is not measuring data. @n
	*		The only valid command for this state is InitiateDataCaptureMode.
	*/
	private ref class DalCaptureStateNotListening : public DalCaptureState
	{
		private:
			static DalCaptureStateNotListening^ _instance = gcnew DalCaptureStateNotListening();
			
			DalCaptureStateNotListening();
			DalCaptureStateNotListening^ operator = (DalCaptureStateNotListening^);

		public:
			/**
			* Singleton instnace for this class.
			*/
			static property DalCaptureStateNotListening^ Instance
			{
				DalCaptureStateNotListening^ get()
				{
					return DalCaptureStateNotListening::_instance; 
				};
			};

			/**
			* Starts the data capture mode. 
			* Calls the DalCommandInterface::InitiateDataCaptureModeInternal() method.
			*/
			virtual bool InitiateDataCaptureMode()override;
	};

	/**
	* @class DalCaptureStateWaiting
	* @brief The state in which EM4 is ready to recieve data from the serial port. @n
	*		In this state, the only valid commands are to stop capture and to check timout.
	*/
	private ref class DalCaptureStateWaiting : public DalCaptureState
	{
		private:
			static DalCaptureStateWaiting^ _instance = gcnew DalCaptureStateWaiting();
			
			DalCaptureStateWaiting();
			DalCaptureStateWaiting^ operator = (DalCaptureStateWaiting^);

		public:
			/**
			* Singleton instnace for this class.
			*/
			static property DalCaptureStateWaiting^ Instance
			{
				DalCaptureStateWaiting^ get()
				{
					return DalCaptureStateWaiting::_instance; 
				};
			};

			/**
			* Stops the data capture process
			*/
			virtual bool StopDataCaptureMode() override;
			virtual void CheckIfTimeoutHasOccurred(Object^ sender, ElapsedEventArgs^ args) override;
	};

	/**
	* @class DalCaptureStateDataReceived
	* @brief The state in which the SWCI has received data from the serial port. @n
	*		In this state, the only valid command are to stop capture and to check timout.
	*/
	private ref class DalCaptureStateDataReceived : public DalCaptureState
	{
		private:
			static DalCaptureStateDataReceived^ _instance = gcnew DalCaptureStateDataReceived();
			
			DalCaptureStateDataReceived();
			DalCaptureStateDataReceived^ operator = ( DalCaptureStateDataReceived^);

		public:
			/**
			* Singleton instnace for this class.
			*/
			static property DalCaptureStateDataReceived^ Instance
			{
				DalCaptureStateDataReceived^ get()
				{
					return DalCaptureStateDataReceived::_instance; 
				};
			};

			/**
			* Calls the method which will process serial port capture packets.
			*/
			//virtual void ReadFromPortAndWriteToBuffer(Object^ sender, SerialDataReceivedEventArgs^ e) override;

			virtual bool ProcessStreamingPackets() override;

	};


	/**
	* @class DalCaptureStateTimeout
	* @brief The state in which the data capture process has timed out. @n
	*		This state does not have any valid commands and is only representative.
	*/
	private ref class DalCaptureStateTimeout : public DalCaptureState
	{
		private:
			static DalCaptureStateTimeout^ _instance = gcnew DalCaptureStateTimeout();
			
			DalCaptureStateTimeout();
			DalCaptureStateTimeout^ operator = (DalCaptureStateTimeout^);

		public:
			/**
			* Singleton instnace for this class.
			*/
			static property DalCaptureStateTimeout^ Instance
			{
				DalCaptureStateTimeout^ get()
				{
					return DalCaptureStateTimeout::_instance; 
				};
			};
	};




			} //namespace StateMachines
		} //namespace DataAccess 
	} //namespace Scor
}//namespace AtCor
