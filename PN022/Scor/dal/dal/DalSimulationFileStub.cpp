#include "stdafx.h"
#include "DalSimulationFile.h"
//#include "AtCor.h"

using namespace AtCor::Scor::DataAccess;

//bool DalSimulationFile::GetNextValues(unsigned long *value1, unsigned long *value2, unsigned long *value3, unsigned long *value4  )
//{
//	String ^singleLine;
//	array<String^> ^DataStrings;
//
//	if (reader == nullptr)
//	{
//		throw gcnew DalException(302); //Simulation file has not been opened before attempting to read
//		return false;
//	}
//	
//	if ( reader->EndOfStream)
//	{
//		reader->BaseStream->Seek(0, SeekOrigin::Begin);
//	}
//	singleLine = reader->ReadLine();
//	DataStrings = singleLine->Split('\t', 4); //three substrings
//	*value1 = Int16::Parse(DataStrings[0]);
//	*value2 = Int16::Parse(DataStrings[1]);
//	*value3 = Int16::Parse(DataStrings[2], System::Globalization::NumberStyles::AllowHexSpecifier);
//	*value4 = Int32::Parse(DataStrings[3], System::Globalization::NumberStyles::AllowHexSpecifier);
////	*value4 = Int32::Parse(DataStrings[3]);
//
//	return false;
//}

bool DalSimulationFile::CreateFile(String^ outputFilePath)
{
	filePath = outputFilePath;
	String^ currentDir = Directory::GetCurrentDirectory();

	try
	{
		//Create the file and pass it to new streamwiter.
		writer = File::CreateText(filePath);
//		writer = gcnew StreamWriter(File::CreateText(filePath));
//		writer = gcnew StreamWriter(filePath);
		return true;
	}
	catch(Exception^)
	{
		throw gcnew DalException(DAL_FAILTOCREATE_ERR); //File could not be created.
	}
}

bool DalSimulationFile::SaveCurrentValues(unsigned short tonometerData, unsigned short cuffPulse)
{
	String ^singleLine = tonometerData.ToString() + "\t" + cuffPulse.ToString();

	try
	{
		writer->WriteLine(singleLine);
		return true;
	}
	catch(System::Exception^)
	{
		throw gcnew DalException(DAL_FAILTOWRITE_ERR); //File could not be written.
	}
}
