#include "Stdafx.h"
#include "DalEventContainer.h"

using namespace AtCor::Scor::DataAccess;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalTonometerDataEventArgs::DalTonometerDataEventArgs(unsigned short data)
			{
				this->data = data;
			}

			DalCuffPulseEventArgs::DalCuffPulseEventArgs(unsigned short data) 
			{
				this->data = data;
			}

			DalEventContainer::DalEventContainer()
			{
			}

			DalEventContainer::DalEventContainer(const DalEventContainer^)
			{
			}

			DalEventContainer^ DalEventContainer::operator = (const DalEventContainer)
			{
				return this;
			}

		}
	}
}
