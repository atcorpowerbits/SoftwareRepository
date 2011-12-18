/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalActivePort.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for DalActivePort class
*/

#pragma once;

using namespace System;
using namespace System::IO;
using namespace System::IO::Ports;
using namespace System::Threading;

using namespace System::Timers;



namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

	private ref class DalActivePort
	{
		private:
			DalActivePort();
			static DalActivePort^ _instance = gcnew DalActivePort();
			DalActivePort^ operator = (DalActivePort);
			
			static SerialPort ^_serialPort;

			//FxCop
			//static bool serialDataWasRecieved; //flag to check wether data was recieved since the last chek.

			//Removing from this class. We need to have as few timer events 
			//the checking has been moved to dalStreamingpacketQueue
			//Timers::Timer^ timeoutCheckTimer;


		public:

			/**
			* Returns the current singleton instance.
			*/
			static property DalActivePort^ Instance
			{
				DalActivePort^ get()
				{
					return DalActivePort::_instance;
				};
			};

			/**
			* Sets the current SerialPort Object to the specified port name
			* @param  serialPortName The serial port to set
			* @return	status of the operation
			*/
			bool SetActivePort( String^ serialPortName);

			/**
			* Sets the port name for the current serial port object.
			* @param  serialPortName The serial port to set
			* @return	status of the operation
			* @warning Check if the serialport instance is not null before calling.
			*/
			bool SetActivePortInstance(String^ serialPortName);

			/**
			* Sets the properties of the internal serialPort object
			* @return	status of the operation
			*/
			bool SetSerialPortProperties();

			/**
			* Creates a new SerialPort instance and opens it.
			* If any port is already open it will attempt to close it first.
			* 
			* @param[in]	 newPortName	Name of the new port.
			* @return	A boolean value indicating the status of the operation
			*/
			bool CreateAndOpenNewSerialPort(String^ newPortName);

			/**
			* Closes any open port and deletes its instance. 
			* @return	status of the operation
			*/
			bool CloseActivePort();

			/**
			* Returns the name of the currently active serial port.
			* @warning Will return @c null if the current serial port object is not set.
			*/
			property String^ ActiveSerialPortName
			{
				String^ get()
				{
					if (_serialPort)
					{
						return _serialPort->PortName;
					}
					else
					{
						//we will return a null string to indicate that the serialPort object hasnt been initialized.
						return nullptr;
					}
				};
			}

			//TODO: This method needs to be removed. No class should be 
			//allowed to refer to the port directly. Al read writhe must be done within this class 
			/**
			* Returns a pointer to the internal SerialPort instance. 
			*/
			property SerialPort^ CurrentPort
			{
				SerialPort^ get()
				{
					return _serialPort;
				}
			}

			/**
			* Transmits a packet over the serial port interface
			* @param	dataToSend	The command to be sent
			*/
			void SendPacket(array<unsigned char>^ dataToSend);
			
			/**
			* Event handler for the serial port's Data recieved event
			* @param[in]	sender	The object which raised this event
			* @param[in]	e	The arguements for the event.
			*/
			void DataReceviedHandler(
											Object^ sender,
											SerialDataReceivedEventArgs^ e);

			/**
			* Reads all the available data from the port and writes it to a staging queue.
			*/
			void ReadDataFromPort();

			//moved to another class. Reducing timer events
			///*
			//* Timer Event handler whcih checks if th data is avaialabe in the serial port or not.
			//* If there is no data avialable in the specified number of consecutive checks, it raises 
			//* an alarm and stops checking.
			//*
			//* @param[in]	sender	The object which raised this event
			//* @param[in]	args	The arguements for the event.
			//*/
			//void CheckStreamingTimeout(Object^ sender, ElapsedEventArgs^ args);

			//moved to another class. Reducing timer events
			///*
			//* Starts the streaming timout check.
			//*/
			//void StartStreamingTimeoutChecker();

			//moved to another class. Reducing timer events
			///*
			//* Stops the streaming timout check.
			//*/
			//void StopStreamingTimeoutChecker();

	};

		}
	}
}
