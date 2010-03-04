//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "TBuffer.h"
#include <Mathem.h>
//#include <stdio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Constructor and Destructor for TBuffer Class
//---------------------------------------------------------------------------
TBuffer::TBuffer(const String pFileName)
{
  FFileName = "";
  FStream = NULL;
  OpenFile(pFileName);
}
//---------------------------------------------------------------------------
TBuffer::TBuffer()
{
  FFileName = "";
  FStream = NULL;
}
//---------------------------------------------------------------------------
TBuffer::~TBuffer()
{
  CloseFile();
}
//---------------------------------------------------------------------------
bool TBuffer::OpenFile(const String pFileName)
{
  if (FileExists(pFileName)==false)
  {
    ShowMessage("File " + pFileName + " does not exist");
    return false;
  }
  CloseFile();
  // Open file for read
  FStream = fopen(pFileName.c_str(), "r");
  if (FStream==NULL)
  {
    ShowMessage("File " + pFileName + " does not exist or locked");
    return false;
  }
  FFileName = pFileName;
  return true;
}
//---------------------------------------------------------------------------
void TBuffer::CloseFile()
{
  if (FStream != NULL)
    fclose(FStream);
  FStream = NULL;
  FFileName = "";
}

/* ###########################################################################
 ** GetNextValueFromFile()
 **
 ** DESCRIPTION
 **  Getting current value of a signal
 ** INPUT
 **  None
 ** OUTPUT
 **  pValue - current value as integer
 ** RETURN
 **   boolean success or not. If end of Signal, return false
*/
//---------------------------------------------------------------------------
bool TBuffer::GetNextValueFromFile(short int *pValue1, short int *pValue2)
{
  try
  {
    if (FStream == NULL)
    {
      //if (FFileName == "")
      //  return false;
      if (OpenFile(FFileName)==false)
        return false;
      if (FStream == NULL)
        return false;
      //throw Exception("File has not been opened to read");
    }
    // Read file
    float f1, f2;
    bool lEof;
    if (pValue2==NULL)
    {
      lEof = fscanf(FStream, "%f",&f1)!=EOF;
    }
    else
    {
      lEof = fscanf(FStream, "%f %f",&f1, &f2)!=EOF;
    }
    if (lEof == false)
    {
      fseek(FStream, 0L, SEEK_SET);
      return GetNextValueFromFile(pValue1, pValue2);
      //CloseFile();
    }
    else
    {
      *pValue1 = (short int) math_Round(f1);
      if (pValue2!=NULL)
        *pValue2 = (short int) math_Round(f2);
    }
    return lEof;
  }
  catch (Exception &exc)
  {
    Application->ShowException(&exc);
    CloseFile();
    return false;
  }
}

