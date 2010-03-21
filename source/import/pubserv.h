//---------------------------------------------------------------------------
#ifndef ImportPubservH
#define ImportPubservH
#include <vcl\vcl.h>
//#include <vcl\db.hpp>
#include <vcl\dbtables.hpp>
#include <import\pubtype.h>
//---------------------------------------------------------------------------
// object main function to convert Dbase into MSAccess
//---------------------------------------------------------------------------
bool import_sphygmocor_database(String DbaseDir,
     TADOTable *pTblPatAccess = NULL, TADOTable *pTblMeasAccess = NULL,
     TADOTable *pTblPWVAccess = NULL, bool pCalculate = true);
//---------------------------------------------------------------------------
#endif
