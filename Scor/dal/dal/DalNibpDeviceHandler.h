/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalNibpDeviceHandler.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header page for DalNibpDeviceHandler class.
*/

#pragma once


#include "stdafx.h"
#include "DalCommon.h"
#include "IDalNibpHandler.h"
#include "DalCommandInterface.h"
#include "DalEM4Command.h"


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalNibpDeviceHandler: public IDalNibpHandler
			{
				private:
					static DalNibpDeviceHandler^ _instance = gcnew DalNibpDeviceHandler();

					DalCommandInterface^ _commandInterface;

					bool ConnectToNibpModule();
					
					DalReturnValue SendNibpConnectCommand();
					void SetCommandInterface(DalCommandInterface^); 
					DalNibpDeviceHandler(); //Constructor

							

				public:
					
					/**
					* Returns the current singleton instance.
					*/
					static property DalNibpDeviceHandler^ Instance
					{
						DalNibpDeviceHandler^ get()
						{
							return DalNibpDeviceHandler::_instance;
						};
					};

					virtual bool StartBP(DalNIBPMode nibpMode, unsigned short initialPressure);

					virtual bool StartBP(DalNIBPMode nibpMode);

					virtual bool FinishBP();

					virtual bool AbortBP();
			};


		}// end namespaces
	}
}
