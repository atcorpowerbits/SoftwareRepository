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
                                    static const unsigned int DAL_FILENOTSET_ERR      = 301; 
                                    static const unsigned int DAL_FILENOTFOUND_ERR    = 302; 
                                    static const unsigned int DAL_FAILTOCREATE_ERR    = 303; 
                                    static const unsigned int DAL_FAILTOWRITE_ERR     = 304; 

                                    String^ filePath;	//path of the file on the disk
									StreamReader ^reader; //variable to store the File stream reader
									StreamWriter ^writer; //variable to store the File stream writer
								public:
									/**
									* Opens the file specified by @c DalSimulationFile::filePath.
									*/
									bool OpenFile();

									/**
									* Closes an open file.
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
									* Reads a line from the simlation file and returns two integer values.
									* @param[out] value1 Unsigned integer value from the first column in the file.
									* @param[out] value2 Unsigned integer value from the second column in the file.
									*
									* @return the status of the operation: true if successful
									*
									* @see GetNextValues(signed int *value1, signed int *value2, signed int value3)
									*/
									bool GetNextValues(signed int *value1, signed int *value2);
									
									/**
									* Reads a line from the simlation file and returns three integer values.
									* @param[out] value1 Unsigned integer value from the first column in the file.
									* @param[out] value2 Unsigned integer value from the second column in the file.
									* @param[out] value3 Unsigned integer value from the third column in the file.
									*
									* @return the status of the operation: true if successful
									*
									* @see GetNextValues(signed int *value1, signed int *value2);
									*/									
									bool GetNextValues(signed int *value1, signed int *value2, signed int *value3);

									/**
									* Reads a line from the simlation file and returns four integer values.
									* @param[out] value1 Unsigned integer value from the first column in the file.
									* @param[out] value2 Unsigned integer value from the second column in the file.
									* @param[out] value3 Unsigned integer value from the third column in the file.
									* @param[out] value4 Unsigned integer value from the fourth column in the file.
									*
									*/									
									bool GetNextValues(unsigned int *value1, unsigned int *value2, unsigned int *value3, unsigned long *value4);

									/**
									* Resets the simulation source file to point to begining of file.
									*
									* @return  true if the operation was successful.
									*/
									bool ResetFileStreamPosition();

									bool CreateFile(String^ outputFilePath);
									bool SaveCurrentValues(unsigned short tonometerData, unsigned short cuffPulse);
								};
		}
	}
}
