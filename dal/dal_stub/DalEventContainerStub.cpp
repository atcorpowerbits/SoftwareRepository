#include "Stdafx.h"
#include "DalEventContainerStub.h"

using namespace AtCor::Scor::DataAccess;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalCountdownTimerEventArgs::DalCountdownTimerEventArgs(unsigned short data)
			{
				this->data = data;
			}

			DalCuffStatusEventArgs::DalCuffStatusEventArgs(unsigned short data)
			{
				this->data = data;
			}

			DalEventContainerStub::DalEventContainerStub()
			{
			}

			DalEventContainerStub::DalEventContainerStub(const DalEventContainerStub^)
			{
			}

			DalEventContainerStub^ DalEventContainerStub::operator = (const DalEventContainerStub)
			{
				return this;
			}

		}
	}
}
