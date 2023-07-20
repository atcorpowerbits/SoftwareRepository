/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_simulation_file.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of simulation file class
*/

#pragma once

#include "dal_namespace.h"

using namespace System;
using namespace System::IO;

START_DAL_NAMESPACE

public ref class DalSimulationFile
{
private:
	StreamReader^ reader; 
	String^ path;
	String^ GetLine();
public:
	// Constructors, destructors
	DalSimulationFile(String^ const fileName);
	~DalSimulationFile();
	bool OpenFile();
	void CloseFile();
	bool GetNextValues(short *value1, short *value2);
	bool GetNextValues(short *value1, short *value2, short *value3);
};

END_DAL_NAMESPACE
