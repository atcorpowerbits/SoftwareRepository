/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	dal_simulation_file.cpp
	
	Author       :  Victor Aung

    Description  :	Simulation file class
*/

#include "StdAfx.h"
#include "dal_simulation_file.h"

using namespace System;
using namespace System::Collections;
using namespace System::IO;

namespace DataAccess {

	DalSimulationFile::DalSimulationFile(String^ const fileName)
	{
	  path = fileName;
	}

	DalSimulationFile::~DalSimulationFile()
	{
		CloseFile();
	}

	bool DalSimulationFile::OpenFile()
	{
		reader = File::OpenText(path);
		if (reader == nullptr)
		{
		//TBD: ShowMessage("File " + fileName + " does not exist");
		return false;
		}
		return true;
	}

	void DalSimulationFile::CloseFile()
	{
		if (reader)
		{
		delete (IDisposable^)(reader);
		}
		reader = nullptr;
		path = L"";
	}

	String^ DalSimulationFile::GetLine()
	{
		// Read a line from the file
		String^ line = reader->ReadLine(); 
		if (line == nullptr) 
		{
			reader = File::OpenText(path);
			line = GetLine();
		}
		return line;
	}
	bool DalSimulationFile::GetNextValues(short *value1, short *value2)
	{
/*
		// Read file
		String^ line = reader->ReadLine(); 
		if (line == nullptr) 
		{
			reader = File::OpenText(path);
			return GetNextValueFromFile(value1, value2);
		} else 
*/
		// Read file
		String^ line = GetLine(); 
		{
			array<String^>^split = line->Split();
			IEnumerator^ myEnum = split->GetEnumerator();

			myEnum->MoveNext();
			String^ string1 = safe_cast<String^>(myEnum->Current);
			*value1 = (short)Single::Parse(string1);

			myEnum->MoveNext();
			String^ string2 = safe_cast<String^>(myEnum->Current);
			*value2 = (short)Single::Parse(string2);
		}
		return true;
	}
	bool DalSimulationFile::GetNextValues(
		short *value1, 
		short *value2, 
		short *value3)
	{
		bool check;
		String^ token;
		String^ line = reader->ReadLine(); 
		if (line == nullptr) 
		{
			reader = File::OpenText(path);
			return GetNextValues(value1, value2, value3);
		} else 
		{
			array<String^>^split = line->Split();
			IEnumerator^ myEnum = split->GetEnumerator();

			check = myEnum->MoveNext();
			token = safe_cast<String^>(myEnum->Current);
			*value1 = Convert::ToInt16(Single::Parse(token));

			check = myEnum->MoveNext();
			token = safe_cast<String^>(myEnum->Current);
//?			*value2 = (short)Single::Parse(token);
			*value2 = Convert::ToInt16(Single::Parse(token));

			check = myEnum->MoveNext();
			token = safe_cast<String^>(myEnum->Current);
//?			*value3 = (short)Single::Parse(token);
			*value3 = Convert::ToInt16(Single::Parse(token));
		}
		return true;
	}
}
