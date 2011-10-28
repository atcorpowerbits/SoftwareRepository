/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpBackgroundCommand.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for classes:  DalNibpBackgroundCommand
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalEM4HostToNibpCommand.h"


using namespace System;
using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{


			private ref class DalNibpBackgroundCommand: public DalEM4HostToNibpCommand
			{
				protected:
					DalNibpBackgroundCommand();
					DalNibpBackGroundCommandState currentBackGroundState;
				internal:
					//DalNibpBackgroundCommand(array<unsigned char> ^ nibpPacket, unsigned int responseWaitTime);

					virtual bool ActOnPacket(array <unsigned char> ^ nibpToHostResponse) override;
					virtual void ResponseListenerThreadMethod(Object^ responsePacket) override;

				protected:	
					virtual DalReturnValue ListenForEM4Response() override;
					virtual bool StopListeningForEM4response() override;

					//blank method. Let child class decide what processing it wants to do after this.
					virtual bool ProcessNibpResponse();


			};


		} //End namespace DataAccess
	}
}