/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
      Copyright (C) PWV MEDICAL PTY LTD, 1998

	    Filename 	  	:  TBuffer.H
      Author        :  Sergei Eremenko
      Revision      :  1.00
      Date          :  21 Dec 98

  	  Description 	:	DECLARATION of TBuffer Class
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
//---------------------------------------------------------------------------
#ifndef TBufferH
#define TBufferH
//#include <vcl\db.hpp>
#include <stdio.h>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Base TBuffer class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class TBuffer
{
  private:
    FILE *FStream;
    String FFileName;
  public:
    // Constructors, destructors
    TBuffer(const String pFileName);
    TBuffer();
    ~TBuffer();
    // Member functions:
    //---------------------------------------------------------------------------
    bool OpenFile(const String pFileName);
    //---------------------------------------------------------------------------
    void CloseFile();
    //---------------------------------------------------------------------------
    bool GetNextValueFromFile(short int *pValue1, short int *pValue2 = NULL);
};
#endif
