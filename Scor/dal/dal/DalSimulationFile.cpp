/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSimulationFile.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalSimulationFile class
*/

#include "stdafx.h"
#include "DalSimulationFile.h"
//#include "AtCor.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting::Logging;


	bool DalSimulationFile::OpenFile()
	{

		FileStream ^ openFileStream;

		//check if the filePath varaible has been entered
		if (filePath == nullptr)
		{
			throw gcnew DalException("DAL_ERR_FILE_NOT_SET"); //File not specified
		}

		try
		{
			openFileStream = File::Open(filePath, FileMode::Open);
		}
		catch(Exception^ )
		{
			throw gcnew DalException("CRX_ERR_FILE_NOT_EXIST"); //File does not exist or could not open file.
			
		}
		if(openFileStream->Length  == 0)
		{
			throw gcnew DalException("DAL_ERR_EMPT_SIMULATION_FILE"); //"The selected simulation file is empty. Please select another simulation file."
			
		}
		else
		{
			//Open the file and pass it to new streamreader.
			reader = gcnew StreamReader(openFileStream);
			return true;
		}
	}

	
	bool DalSimulationFile::CloseFile()
	{
		if (reader != nullptr)
		{
			//close streamreader
			reader->Close();
			reader = nullptr;
			return true;
		}
		if (writer != nullptr) //TODO:STUB
		{
			//close streamreader
			writer->Close();
			writer = nullptr;
			return true;
		}
		//false if there was some problem
		return false;
	}
	
	DalSimulationFile::DalSimulationFile()//Constructor
	{
		//Initialize all pointers as null
		reader = nullptr;
		filePath = nullptr;
	}
	
	DalSimulationFile::DalSimulationFile(String ^sourceFilePath)//Overloaded Constructor
	{
		//asign the source path to filePAth and open file
		filePath = sourceFilePath;
		//Open the source file.
		OpenFile();
	}
	
	DalSimulationFile::~DalSimulationFile()//Destructor
	{
		//Close the reader
		reader->Close();
	}
	
	bool DalSimulationFile::GetNextValues(unsigned long *value1, unsigned long *value2)
	{
		String ^singleLine; //temporary variable to store string
		array<String^> ^DataStrings; //string array to store the returned numbers

		if (reader == nullptr)
		{
			throw gcnew DalException("CRX_ERR_FILE_CANNOT_ACC"); //Simulation file has not been opened before attempting to read
			
		}
		
		//Check if we have reached end of file and reset pointer to the start.
		if ( reader->EndOfStream)
		{
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
		}
		singleLine = reader->ReadLine();
		DataStrings = singleLine->Split('\t', 2); //Parse only first two numbers
		
		//return values to calling function
		*value1 = (short)Single::Parse(DataStrings[0]);
		*value2 = (short)Single::Parse(DataStrings[1]);
		//TODO: these variables must be bigger to accomodate any other changes
		//successful
		return true;
	}


	bool DalSimulationFile::GetNextValues(unsigned long *value1, unsigned long *value2, unsigned long *value3, unsigned long *value4) 
	{
		String ^singleLine; //temporary variable to store string
		array<String^> ^DataStrings; //string array to store the returned numbers

		if (reader == nullptr)
		{
			throw gcnew DalException("CRX_ERR_FILE_CANNOT_ACC"); //Simulation file has not been opened before attempting to read
		
		}
		
		//Check if we have reached end of file and reset pointer to the start
		if ( reader->EndOfStream)
		{
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
		}

		//read a line from the file
		singleLine = reader->ReadLine();

		//extract three substrings from this file
		DataStrings = singleLine->Split('\t', 4); //four substrings

		//parse individual values 
		*value1 = (short)Single::Parse(DataStrings[0]);
		*value2 = (short)Single::Parse(DataStrings[1]);
		*value3 = Int32::Parse(DataStrings[2], System::Globalization::NumberStyles::AllowHexSpecifier);
		*value4 = Int32::Parse(DataStrings[3], System::Globalization::NumberStyles::AllowHexSpecifier);
				
		return true;
	}

	bool DalSimulationFile::ResetFileStreamPosition()
	{
		if (reader)
		{
			//clear the buffered data
			reader->DiscardBufferedData();

			//reposition the pointer of the filestream.
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
			reader->BaseStream->Position = 0;
		}

		return true;
	}
