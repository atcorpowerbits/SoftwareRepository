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
#include "DalDataBuffer.h"
#include "DalSpecificForegroundCommands.h"


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalNibpDeviceHandler: public IDalNibpHandler
			{
				private:
					DalDataBuffer^ dataBufferObj; 
					static DalNibpDeviceHandler^ _instance = gcnew DalNibpDeviceHandler();

					DalCommandInterface^ _commandInterface;

					bool ConnectToNibpModule();
					
					DalReturnValue SendNibpConnectCommand();
					DalReturnValue SendNibpDisconnectCommand();
					DalReturnValue SendNibpConnectDisconnectCommand(bool connect);
					void SetCommandInterface(DalCommandInterface^); 
					DalNibpDeviceHandler(); //Constructor
					bool GetCuffPressure(unsigned int& cuffPressure);

					bool StartBpProcess(DalNIBPMode nibpMode, unsigned short initialPressure, bool initialInflate);
							
					bool CheckIfCuffHasDeflated();
					bool CreateDataBuffer();

					Thread^ cuffPressurePlottingThread;
					void CuffPressurePlottingThreadMethod();
					//bool plotCuffPressurePoints;

					DalNibpStartBpCommand^ GetNewStartBpCommandObject(DalNIBPMode nibpMode);

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
					void StopCuffPressurePlotting();

					bool GetBpDataAndRaiseEvent();
			};


		}// end namespaces
	}
}
