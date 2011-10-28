/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSpecificBackgroundCommands.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for all DalNibpBackgroundCommand derived classes
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"
#include "DalNibpBackgroundCommand.h"


using namespace System;
using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalCuffPressureCommand: public DalNibpBackgroundCommand
			{
				public:
					DalCuffPressureCommand();

			protected:
				virtual bool ProcessNibpResponse() override;
			internal:
				bool GetCuffPressure(unsigned int& cuffPressure);

			};

			private ref class DalNibpGetBpDataCommand: public DalNibpBackgroundCommand
			{
				public:
					DalNibpGetBpDataCommand();
				protected:
					virtual bool ProcessNibpResponse() override;

				internal:
					bool GetBpDataAndRaiseEvent();
				private:
					DalNibpData^  _nibpDataObject;
					bool CheckRecievedData();
					void ExtractDataParts();


			};



		} //End namespace DataAccess
	}
}
