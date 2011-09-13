/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalModule.h
        
     Author       :		 Deepak D'Souza/Alok Sahu
 
     Description  :      Header file for DalStreamingMode class.
*/

#include "stdafx.h"
#include "DalCommandInterface.h"
#include "DalDeviceHandler.h"
#include "DalCommon.h"
#include "DalEventContainer.h"
#include "DalCaptureState.h"
#include "DalStagingQueue.h"
#include "DalSequenceNumberManager.h"
#include "DalResponsePacketBuffer.h"
#include "DalBinaryConversions.h"

using namespace System;
using namespace System::IO::Ports;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::DataAccess::StateMachines;
using namespace AtCor::Scor::CrossCutting::Configuration;


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{
			DalStreamingMode::DalStreamingMode()
			{

			}


		}
	}
}