#include "stdafx.h"
#include "dal.h"

using namespace System;


namespace DataAccess{
	public ref class DalFacade
	{
		private:
			static DalFacade^ _instance;
			DalModule^ _module;
			unsigned int captureDataType;
			DalFacade(DalFacade^);

		public:
				static DalFacade^ DalFacade::Instance();
				bool StartCapture(unsigned int captureDataType);
				bool StopCapture();
		protected:
			DalFacade(void); //Implemented
	};



}

