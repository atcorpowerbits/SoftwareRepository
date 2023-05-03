/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSimulationFile.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      source file for DalSimulationFile class
*/

#include "stdafx.h"
#include "DalSimulationFile.h"
//#include "AtCor.h"

using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::CrossCutting;
using namespace System::Text;


	bool DalSimulationFile::OpenFile()
	{

		FileStream ^ openFileStream;

		//check if the filePath varaible has been entered
		if (filePath == nullptr)
		{
			//throw gcnew DalException("DAL_ERR_FILE_NOT_SET"); 
			//File not specified
			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrFileNotSetErrCd, CrxStructCommonResourceMsg::DalErrFileNotSet, ErrorSeverity::Exception);
		}

		try
		{
			openFileStream = File::Open(filePath, FileMode::Open);
		}
		catch(Exception^ sysExcep)
		{
			//File does not exist or could not open file.
			//throw gcnew DalException("CRX_ERR_FILE_NOT_EXIST"); 
			throw gcnew ScorException(sysExcep);
			
		}
		if(openFileStream->Length  == 0)
		{
			//"The selected simulation file is empty. Please select another simulation file."
			throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrEmptSimulationFileErrCd, CrxStructCommonResourceMsg::DalErrEmptSimulationFile, ErrorSeverity::Exception);
			
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
		if (writer != nullptr) 
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

	bool DalSimulationFile::GetNextValues(unsigned short *value1)
	{
		String ^singleLine; //temporary variable to store string
		try
		{
		if (reader == nullptr)
		{
			 //Simulation file has not been opened before attempting to read
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);
		}
		
		//Check if we have reached end of file and reset pointer to the start.
		if ( reader->EndOfStream)
		{
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
		}
		singleLine = reader->ReadLine();
		
		//Removing special characters from the string
		singleLine = RemoveSpecialCharacters(singleLine);
		
		//return values to calling function
		//CrxLogger::Instance->Write(singleLine, ErrorSeverity::Debug);
		*value1 = UInt16::Parse(singleLine);
		//successful
		return true;
		}
		catch(Exception^ ex)
		{
			throw gcnew ScorException(ex);
		}
	}
	
	String^ DalSimulationFile::RemoveSpecialCharacters(String^ str)
    {

        StringBuilder^ sb = gcnew StringBuilder();
        for (int i = 0; i < str->Length; i++)
        {
            if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'z' || (str[i] == '.' || str[i] == '_')))
                sb->Append(str[i]);
        }

        return sb->ToString();
    }

	bool DalSimulationFile::GetNextValues(unsigned short *value1, unsigned short *value2)
	{
		try
		{
			String ^singleLine; //temporary variable to store string
			array<String^> ^DataStrings; //string array to store the returned numbers

			try
			{
				if (reader == nullptr)
				{
					 //Simulation file has not been opened before attempting to read
					throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);
				}
				
				//Check if we have reached end of file and reset pointer to the start.
				if ( reader->EndOfStream)
				{
					reader->BaseStream->Seek(0, SeekOrigin::Begin);
				}
				singleLine = reader->ReadLine();
				DataStrings = singleLine->Split('\t', 2); //Parse only first two numbers
				
				//return values to calling function
				*value1 = UInt16::Parse(DataStrings[0]);
				*value2 = UInt16::Parse(DataStrings[1]);
			}
			catch(Exception^ exObj)
			{
				delete exObj;//
			}
		//successful
		return true;
	}
		catch(ScorException^ exObj)
		{
			throw gcnew ScorException(exObj);
		}
	}


	bool DalSimulationFile::GetNextValues(unsigned long *value1, unsigned short *value2, unsigned short *value3, unsigned short *value4) 
	{
		try
		{
		String ^singleLine; //temporary variable to store string
		array<String^> ^DataStrings; //string array to store the returned numbers

		if (reader == nullptr)
		{
			//Simulation file has not been opened before attempting to read
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);
		}
		
		//Check if we have reached end of file and reset pointer to the start
		if ( reader->EndOfStream)
		{
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
		}

		//read a line from the file
		singleLine = reader->ReadLine();

		//extract three substrings from this file
		DataStrings = singleLine->Split(DalFormatterStrings::tabSeparator, 4); //four substrings

		//parse individual values 
		*value1 = UInt32::Parse(DataStrings[0]);
		*value2 = UInt16::Parse(DataStrings[1]);
		*value3 = Int16::Parse(DataStrings[2], System::Globalization::NumberStyles::AllowHexSpecifier);
		*value4 = Int16::Parse(DataStrings[3], System::Globalization::NumberStyles::AllowHexSpecifier);
				
		return true;
	}
		catch(Exception^ exObj)
		{
			throw gcnew ScorException(exObj);
		}
	}

	bool DalSimulationFile::GetNextValues(unsigned short *value1, unsigned short *value2, unsigned short *value3, unsigned short *value4, unsigned short *value5, unsigned short *value6, unsigned short *value7 )
	{
		String ^singleLine; //temporary variable to store string
		array<String^> ^DataStrings; //string array to store the returned numbers

		if (reader == nullptr)
		{
			//Simulation file has not been opened before attempting to read
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);
		}
		
		//Check if we have reached end of file and reset pointer to the start
		if ( reader->EndOfStream)
		{
			reader->BaseStream->Seek(0, SeekOrigin::Begin);
		}

		//read a line from the file
		singleLine = reader->ReadLine();

		//extract substrings from this file
	DataStrings = singleLine->Split(DalFormatterStrings::tabSeparator, 7);

		//parse individual values 
		*value1 = (short)Single::Parse(DataStrings[0]);
		*value2 = (short)Single::Parse(DataStrings[1]);
		*value3 = (short)Single::Parse(DataStrings[2]);
		*value4 = (short)Single::Parse(DataStrings[3]);
		*value5 = (short)Single::Parse(DataStrings[4]);
		*value6 = (short)Single::Parse(DataStrings[5]);
		*value7 = (short)Single::Parse(DataStrings[6]);
				
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

	bool DalSimulationFile::SaveCurrentValues(unsigned short tonometerData, unsigned short cuffPulse)
	{
	String ^singleLine = tonometerData.ToString() + DalFormatterStrings::tabSeparatorString + cuffPulse.ToString();

	try
	{
		writer->WriteLine(singleLine);
		return true;
	}
	catch(System::Exception^)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);
	}
	}

	bool DalSimulationFile::SaveCurrentValues(unsigned short cuffPulse)
	{
		try
		{
			writer->WriteLine(cuffPulse.ToString());
			return true;
		}
		catch(System::Exception^)
		{
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);
		}
	}

	bool DalSimulationFile::SaveCurrentValues(unsigned short time, unsigned short status, unsigned short errorCode, unsigned short sp, unsigned short dp, unsigned short map, unsigned short hr)
	{
		String ^singleLine = String::Concat(time.ToString(), DalFormatterStrings::tabSeparatorString, 
											status.ToString(), DalFormatterStrings::tabSeparatorString, 
										    errorCode.ToString(), DalFormatterStrings::tabSeparatorString, 
										    sp.ToString(), DalFormatterStrings::tabSeparatorString,
										    dp.ToString(), DalFormatterStrings::tabSeparatorString, 
										    map.ToString(), DalFormatterStrings::tabSeparatorString, 
										    hr.ToString(), DalFormatterStrings::tabSeparatorString);

		try
		{
			writer->WriteLine(singleLine);
			return true;
		}
		catch(System::Exception^)
		{
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);
		}
	}

	bool DalSimulationFile::CreateFile(String^ outputFilePath)
	{
	filePath = outputFilePath;
	//String^ currentDir = Directory::GetCurrentDirectory();

	try
	{
		//Create the file and pass it to new streamwiter.
		writer = File::CreateText(filePath);
		return true;
	}
	catch(Exception^)
	{
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrFileCannotAccessErrCd, CrxStructCommonResourceMsg::CrxErrFileCannotAccess, ErrorSeverity::Exception);
	}
	}

	String^ SerialNumberMpb()
	{
		return "SerialNumberMpb";
	}