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

			
			private ref class DalNibpCommandInterface: public DalCommandInterface
			{
				private:
					static DalNibpCommandInterface^ _instance = gcnew DalNibpCommandInterface();
					DalNibpCommandInterface^ operator= (DalNibpCommandInterface^);

				internal:
					static property DalNibpCommandInterface^ Instance
					{
						DalNibpCommandInterface^ get()
						{
							return _instance;
						}
					};

					
					DalNibpCommandInterface(); //constructor

					bool SendCommandToNibpModule(array<unsigned char>^ nibpCommandByteArray);
			
					//event EventHandler<NibPacketArrivedEventArgs^>^ NibPPacketArrivedEventHandler;

					/*void DemoEvent(array<unsigned char>^ demoData)
					{
						EventHandler<NibPacketArrivedEventArgs^> ^temp = NibPPacketArrivedEventHandler;
						temp(this, gcnew NibPacketArrivedEventArgs(demoData) );
					}*/

					//not needed
					//static void PacketProcessingMethod(Object^ source, NibPacketArrivedEventArgs^ args);

					static void ProcessNibpToHostPacket(array<unsigned char> ^ nibpToHostPacket);

					//delegate for ProcessNibpToHostPacket
					delegate void ProcessNibpToHostPacketAsyncCaller(array<unsigned char> ^ nibpToHostPacket);
					
			
			};

			


		} //end namesapces
	}
}