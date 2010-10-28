#include "stdafx.h"
#include "DalFacade.h"

//using namespace DataAccess;


namespace DataAccess{

	DalFacade::DalFacade()
	{
		//Empty body.
	}
	
	DalFacade::DalFacade(DalFacade^)
	{
		//Empty copy constructor
	}

	DalFacade^ DalFacade::Instance()
	{
	//TODO: Temporary filler returns null
		return nullptr;

	}

}