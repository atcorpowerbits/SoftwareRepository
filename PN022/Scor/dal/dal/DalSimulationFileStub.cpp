#include "stdafx.h"
#include "DalSimulationFile.h"
//#include "AtCor.h"

using namespace AtCor::Scor::DataAccess;

bool DalSimulationFile::GetNextValues(unsigned int *value1, unsigned int *value2, unsigned int *value3, unsigned long *value4  )
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
	DataStrings = singleLine->Split('\t', 4); //three substrings
	*value1 = Int16::Parse(DataStrings[0]);
	*value2 = Int16::Parse(DataStrings[1]);
	*value3 = Int16::Parse(DataStrings[2], System::Globalization::NumberStyles::AllowHexSpecifier);
	*value4 = Int32::Parse(DataStrings[3], System::Globalization::NumberStyles::AllowHexSpecifier);
//	*value4 = Int32::Parse(DataStrings[3]);

	return false;
}

