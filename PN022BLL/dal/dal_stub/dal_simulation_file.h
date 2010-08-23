/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_simulation_file.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of simulation file class
*/

#pragma once

using namespace System;
using namespace System::IO;

namespace DataAccess {
	public ref class DalSimulationFile
	{
	private:
		StreamReader^ reader; 
		String^ path;
	public:
		// Constructors, destructors
		DalSimulationFile(String^ const fileName);
		~DalSimulationFile();
		bool OpenFile();
		void CloseFile();
		bool GetNextValueFromFile(short *value1, short *value2);
	};
}
