#include "stdafx.h"
#include "DalSimulationFile.h"
//#include "AtCor.h"

using namespace AtCor::Scor::DataAccess;


	bool DalSimulationFile::OpenFile()
	{
		if (filePath == nullptr)
			throw gcnew DalException(301); //File not specified

		try
		{
			reader = gcnew StreamReader(File::Open(filePath, FileMode::Open));
			return true;
		}
		catch(Exception^)
		{
			throw gcnew DalException(302); //File does not exist or could not open file.
			return false;
		}
	}
	
	bool DalSimulationFile::CloseFile()
	{
		if (reader != nullptr)
		{
			reader->Close();
			reader = nullptr;
			return true;
		}
		return false;
	}
	
	DalSimulationFile::DalSimulationFile()//Constructor
	{
		reader = nullptr;
		filePath = nullptr;
	}
	
	DalSimulationFile::DalSimulationFile(String ^sourceFilePath)//Overloaded Constructor
	{
		//TODO
		filePath = sourceFilePath;
		OpenFile();
	
	}
	
	DalSimulationFile::~DalSimulationFile()//Destructor
	{
		//TODO
		reader->Close();
	}
	
	bool DalSimulationFile::GetNextValues(signed int *value1, signed int *value2)
	{
		String ^singleLine;
		array<String^> ^DataStrings;

		if (reader == nullptr)
		{
			throw gcnew DalException(302); //Simulation file has not been opened before attempting to read
			return false;
		}
		
		if ( reader->EndOfStream)
		{
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
		}
		singleLine = reader->ReadLine();
		DataStrings = singleLine->Split('\t', 2);
		*value1 = (short)Single::Parse(DataStrings[0]);
		*value2 = (short)Single::Parse(DataStrings[1]);
		return false;
	}

	bool DalSimulationFile::GetNextValues(signed int *value1, signed int *value2, signed int *value3 )
	{
		String ^singleLine;
		array<String^> ^DataStrings;

		if (reader == nullptr)
		{
			throw gcnew DalException(302); //Simulation file has not been opened before attempting to read
			return false;
		}
		
		if ( reader->EndOfStream)
		{
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
		}
		singleLine = reader->ReadLine();
		DataStrings = singleLine->Split('\t', 3); //three substrings
		*value1 = (short)Single::Parse(DataStrings[0]);
		*value2 = (short)Single::Parse(DataStrings[1]);
		*value3 = (short)Single::Parse(DataStrings[2]);

		return false;
	}

