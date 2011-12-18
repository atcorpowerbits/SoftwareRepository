/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalnibpCommandInterface.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for DalNibpCommandInterface class
*/
#pragma once

#include "stdafx.h"
#include "DalCommandInterface.h"
#include <msclr\lock.h>
#include "DalEventContainer.h"
#include "DalEm4NibpToHostPacket.h"

using namespace System::Runtime::InteropServices; 
using namespace msclr;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			
			/**
			* @class	DalNibpCommandInterface
			* @brief	Interface to send and recieve data from NIBP module
			*/
			private ref class DalNibpCommandInterface: public DalCommandInterface
			{
				private:
					static DalNibpCommandInterface^ _instance = gcnew DalNibpCommandInterface(); //instance for singleton
					DalNibpCommandInterface^ operator= (DalNibpCommandInterface^); //overloaded assignmet operator

				internal:

					/**
					* Pointer to the singleton instance.
					*/
					static property DalNibpCommandInterface^ Instance
					{
						DalNibpCommandInterface^ get()
						{
							return _instance;
						}
					};

					/**
					* Constructor for this class.
					*/
					DalNibpCommandInterface(); //constructor

					/**
					* Sends a commad array to the EM4 device to forwad to NIBP module.
					* @param[in]	nibpCommandByteArray	The NIBP command. It will be encapsulated into an
					*										EM4 command by this function
					* @return	The status of this operation.
					*/
					bool SendCommandToNibpModule(array<unsigned char>^ nibpCommandByteArray);
			
					//event EventHandler<NibPacketArrivedEventArgs^>^ NibPPacketArrivedEventHandler;

					/*void DemoEvent(array<unsigned char>^ demoData)
					{
						EventHandler<NibPacketArrivedEventArgs^> ^temp = NibPPacketArrivedEventHandler;
						temp(this, gcnew NibPacketArrivedEventArgs(demoData) );
					}*/

					//not needed
					//static void PacketProcessingMethod(Object^ source, NibPacketArrivedEventArgs^ args);

					/**
					* Processes the specified packet and extracts the necessary data
					* @param[in]	nibpToHostPacket	The nibp response packet
					*/
					static void ProcessNibpToHostPacket(array<unsigned char> ^ nibpToHostPacket);

					/**
					* Delegate for ProcessNibpToHostPacket() method to implement an asynchronous call
					* @param[in]	nibpToHostPacket	The nibp response packet
					*/
					delegate void ProcessNibpToHostPacketAsyncCaller(array<unsigned char> ^ nibpToHostPacket);
					
			
			};

			


		} //end namesapces
	}
}