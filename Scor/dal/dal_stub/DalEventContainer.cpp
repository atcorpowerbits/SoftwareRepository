#include "Stdafx.h"
#include "DalEventContainer.h"

using namespace AtCor::Scor::DataAccess;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalTonometerDataEventArgs::DalTonometerDataEventArgs(unsigned short data)
			{
				//assign the parameter to class member
				this->data = data;
			}

			DalCuffPulseEventArgs::DalCuffPulseEventArgs(unsigned short data) 
			{
				//assign the parameter to class member
				this->data = data;
			}

			DalEventContainer::DalEventContainer()
			{
				//Empty code block to implement singleton
			}

			//Overloaded copy contructor. 
			DalEventContainer::DalEventContainer(const DalEventContainer^)
			{
				//Does nothing. Made private to implement singleton.
			}

			//overloaded assignment operator. Private to implement singleton.
			DalEventContainer^ DalEventContainer::operator = (const DalEventContainer)
			{
				//return the  current instance itself.
				return this;
			}

		}
	}
}
