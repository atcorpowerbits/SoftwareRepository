/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxEventContainer.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      code file to contain all event handling related code for Cross cutting layer.
*/

#pragma once

#include "Stdafx.h"
#include "CrxEventContainer.h"


namespace AtCor{
	namespace Scor{
		namespace CrossCutting{

			CommsPortEventArgs::CommsPortEventArgs(String^ commsPortSetting)
			{
				//assign the parameter to class member
				this->commsPortSetting = commsPortSetting;
			}

			CrxEventContainer::CrxEventContainer()
			{
				//Empty code block to implement singleton
			}

			//Overloaded copy contructor. 
			CrxEventContainer::CrxEventContainer(CrxEventContainer^)
			{
				//Does nothing. Made private to implement singleton.
			}

			//overloaded assignment operator. Private to implement singleton.
			CrxEventContainer^ CrxEventContainer::operator = (CrxEventContainer)
			{
				//return the  current instance itself.
				return this;
			}

			//Show Status Event constructor
			CrxShowStatusEventArgs::CrxShowStatusEventArgs(ScorException^ objScorException)
			{
				//assign the parameter to class member
				this->ObjScorException = objScorException;
			}			

		}
	}
}
