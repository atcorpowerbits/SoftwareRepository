#include "stdafx.h"
#include "DalSimulationFile.h"
//#include "AtCor.h"

using namespace AtCor::Scor::DataAccess;


	bool DalSimulationFile::OpenFile()
	{
        //check if the filePath varaible has been entered
		if (filePath == nullptr)
			throw gcnew DalException(DAL_FILENOTSET_ERR); //File not specified

		try
		{
			//Open the file and pass it to new streamreader.
			reader = gcnew StreamReader(File::Open(filePath, FileMode::Open));
			return true;
		}
		catch(System::Exception^)
		{
			throw gcnew DalException(DAL_FILENOTFOUND_ERR); //File does not exist or could not open file.
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
	
	//Todo: The common code needs to be seperated into another inline function
	bool DalSimulationFile::GetNextValues(signed int *value1, signed int *value2)
	{
		String ^singleLine; //temporary variable to store string
		array<String^> ^DataStrings; //string array to store the returned numbers

		if (reader == nullptr)
		{
			throw gcnew DalException(DAL_FILENOTFOUND_ERR); //Simulation file has not been opened before attempting to read
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
		
		//successful
		return true;
	}

	bool DalSimulationFile::GetNextValues(signed int *value1, signed int *value2, signed int *value3 )
	{
		String ^singleLine; //temporary variable to store string
		array<String^> ^DataStrings; //string array to store the returned numbers

		if (reader == nullptr)
		{
			throw gcnew DalException(DAL_FILENOTFOUND_ERR); //Simulation file has not been opened before attempting to read
		}
		
		//Check if we have reached end of file and reset pointer to the start
		if ( reader->EndOfStream)
		{
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
		}

		//read a line from the file
		singleLine = reader->ReadLine();

		//extract three substrings from this file
		DataStrings = singleLine->Split('\t', 3); //three substrings

		//parse individual values 
		*value1 = (short)Single::Parse(DataStrings[0]);
		*value2 = (short)Single::Parse(DataStrings[1]);
		*value3 = (short)Single::Parse(DataStrings[2]);

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

