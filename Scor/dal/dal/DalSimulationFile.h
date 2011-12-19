/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalSimulationFile.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header file for DalSimulationFile class
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"

using namespace System;
using namespace System::IO;

namespace AtCor{ 
	namespace Scor{ 
		namespace DataAccess{

								/**
								* @class DalSimulationFile
								* @brief Proivdes methods to read from the Simulation file.
								*/
								private ref class DalSimulationFile
								{
								private:
									// constant declarations
                                    static const unsigned int DAL_FILENOTSET_ERR      = 301;  //TODO:STUB
                                    static const unsigned int DAL_FILENOTFOUND_ERR    = 302; //TODO:STUB
                                    static const unsigned int DAL_FAILTOCREATE_ERR    = 303; //TODO:STUB
                                    static const unsigned int DAL_FAILTOWRITE_ERR     = 304; //TODO:STUB

									StreamReader ^reader; //variable to store the File stream reader
									StreamWriter ^writer; //variable to store the File stream writer 

								internal:
									String^ filePath;	//path of the file on the disk

								public:
									/**
									* Opens the file specified by @c DalSimulationFile::filePath.
									*
									* @return The status of the operation
									*/
									bool OpenFile();

									/**
									* Closes an open file.
									*
									* @return The status of the operation
									*/
									bool CloseFile();

									/**
									* Constructor for the class. @n
									* Opens a file if specified in @c DalSimulationFile::filePath
									*/
									DalSimulationFile(); 

									/**
									* Parametrized constructor. Sets @c filePath to the specified file and opens it.
									*
									* @param[in] sourceFilePath The path of the simulation file
									*/
									DalSimulationFile(String ^sourceFilePath); //Overloaded Constructor
									
									/**
									* Destructor for the class. @n
									* Closes open filereaders and relaes files.
									*/
									~DalSimulationFile(); //Destructor

									/**
									* Reads a line from the simlation file and returns a single integer value.
									* @param[out] value1 Unsigned integer value from the first column in the file.
									*
									* @return the status of the operation: true if successful
									*/
									bool GetNextValues(unsigned short *value1);
									
									/**
									* Reads a line from the simlation file and returns two integer values.
									* @param[out] value1 Unsigned integer value from the first column in the file.
									* @param[out] value2 Unsigned integer value from the second column in the file.
									*
									* @return the status of the operation: true if successful
									*/
									bool GetNextValues(unsigned short *value1, unsigned short *value2);
																		
									/**
									* Reads a line from the simlation file and returns four values.
									* @param[out] value1 Unsigned integer value from the first column in the file.
									* @param[out] value2 Unsigned short value from the second column in the file.
									* @param[out] value3 Unsigned short value from the third column in the file.
									* @param[out] value4 Unsigned short value from the fourth column in the file.
									*
									* @return the status of the operation: true if successful
									*
									* @see GetNextValues(signed int *value1, signed int *value2);
									*/									
									bool GetNextValues(unsigned long  *value1, unsigned short *value2, unsigned short *value3, unsigned short *value4 );
									
									/**
									* Reads a line from the simlation file and returns four values.
									* @param[out] value1 Unsigned integer value from the first column in the file.
									* @param[out] value2 Unsigned integer value from the second column in the file.
									* @param[out] value3 Unsigned long value from the third column in the file.
									* @param[out] value4 Unsigned long value from the fourth column in the file.
									* @param[out] value5 Unsigned long value from the fifth column in the file.
									* @param[out] value6 Unsigned long value from the sixth column in the file.
									* @param[out] value7 Unsigned long value from the seventh column in the file.
									*
									* @return the status of the operation: true if successful
									*
									* @see GetNextValues(signed int *value1, signed int *value2);
									*/
									bool GetNextValues(unsigned short  *value1, unsigned short *value2, unsigned short *value3, unsigned short *value4, unsigned short *value5, unsigned short *value6, unsigned short *value7 );

									/**
									* Resets the simulation source file to point to begining of file.
									*
									* @return  true if the operation was successful.
									*/
									bool ResetFileStreamPosition();


									/**
									* Creates a new file to dump data on a crash
									*
									* @param[in] outputFilePath	The name of the file created. @n
									*							It is created according to the date and time
									* @return  true if the operation was successful.
									*/
									bool CreateFile(String^ outputFilePath);
									
									/**
									* Writes the values passed to the dump file
									*
									* @param[in] tonometerData	Tonometer value
									* @param[in] cuffPulse	Cuff Pulse value
									* @return  @c true if the operation was successful.
									*/
									bool SaveCurrentValues(unsigned short tonometerData, unsigned short cuffPulse); 
									
									/**
									* Writes the values passed to the dump file
									*
									* @param[in] cuffPulse	Cuff Pulse value
									* @return  @c true if the operation was successful.
									*/
									bool DalSimulationFile::SaveCurrentValues(unsigned short cuffPulse);								
									
									/**
									* Writes the values passed to the dump file
									*
									* @param[in] time	time value
									* @param[in] status	status value
									* @param[in] errorCode	errorcode value
									* @param[in] sp	sp value
									* @param[in] dp dp value
									* @param[in] map map value
									* @param[in] hr hr value
									* @return  @c true if the operation was successful.
									*/
									bool DalSimulationFile::SaveCurrentValues(unsigned short time, unsigned short status, unsigned short errorCode, unsigned short sp, unsigned short dp, unsigned short map, unsigned short hr);
	
									/**
									* Removes special characters from the string
									*
									* @param[in] str	String value
									* @return  @c modified string  if the operation was successful.
									*/
									String^ RemoveSpecialCharacters(String^ str);
			};
		}
	}
}
