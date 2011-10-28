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

			private ref class DalNibpIntialInflateCommand: public DalNibpForegroundCommand
			{
				private :
					int initialPressure;

				internal:
					DalNibpIntialInflateCommand(int initalInflatePressure, unsigned int responseWaitTime);

					bool SetInitialInflate();
			public:

					virtual bool ProcessNibpResponse() override;

			};



			private ref class DalNibpStartBpCommand: public DalNibpForegroundCommand
			{
				protected:
					DalNibpStartBpCommand();
					unsigned int kPacketWaitTime;

				internal:
					DalNibpStartBpCommand(int responseWaitTime);
					

					bool SendStartBpCommand();
					Thread^ kPacketListenerThread;
				public:

					virtual bool ProcessNibpResponse() override;

					virtual void ListenerForKPacketThreadMethod(Object^ responsePacket) ;


			};

			private ref class DalNibpStartPediatricBpCommand: public DalNibpStartBpCommand
			{
				internal:
					DalNibpStartPediatricBpCommand();

			};

			private ref class DalNibpStartNeonateBpCommand: public DalNibpStartBpCommand
			{
				internal:
					DalNibpStartNeonateBpCommand();

			};


			private ref class DalNibpAbortBpCommand:public DalNibpForegroundCommand
			{
				private:
					DalNibpAbortBpCommand();

				internal:
					DalNibpAbortBpCommand(int responseWaitTime);
					bool AbortBp();
				public:
					virtual bool ProcessNibpResponse() override;

			};


		} //End namespace DataAccess
	}
}
