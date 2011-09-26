/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalnibpCommandInterface.h
        
     Author       :		 Deepak D'Souza
 
     Description  :     Header file for DalNibpCommandInterface class
*/
#pragma once

#include "stdafx.h"
#include "DalCommandInterface.h"


namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			private ref class DalNibpCommandInterface: public DalCommandInterface
			{
				internal:
					bool SendCommandToNibpModule(array<unsigned char>^ nibpCommandByteArray);
			
			};


		} //end namesapces
	}
}