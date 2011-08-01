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
			//Thread^ readerThread;
			//static bool dataAvaliable = false;

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

			bool CreateAndOpenNewSerialPort(String^ newPortName);

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
			property SerialPort^ CurrentPort
			{
				SerialPort^ get()
				{
					return _serialPort;
				}
			}

			void SendPacket(array<unsigned char>^ dataToSend);
			
			void DataReceviedHandler(
											Object^ sender,
											SerialDataReceivedEventArgs^ e);

			void ReadDataFromPort();

			//void ThreadMethod();



	};

		}
	}
}
