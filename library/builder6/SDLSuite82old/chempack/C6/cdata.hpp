// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'cdata.pas' rev: 6.00

#ifndef cdataHPP
#define cdataHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cdata
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxChemElem = 0x67;
#define SDLVersionInfo "cdata_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE AnsiString __fastcall CompressChemName(AnsiString Instring);
extern PACKAGE AnsiString __fastcall DeCompressChemName(AnsiString InString);
extern PACKAGE void __fastcall PerSysCoord(int AtNr, int &x, int &y);
extern PACKAGE AnsiString __fastcall CElemSymb(int AtNr);
extern PACKAGE AnsiString __fastcall CElemName(int AtNr);
extern PACKAGE int __fastcall AtomicNumber(AnsiString Symbol);
extern PACKAGE int __fastcall IntAtWeight(int AtNr);
extern PACKAGE double __fastcall ExactAtWeight(int AtNr);
extern PACKAGE double __fastcall ChemAtWeight(int AtNr);
extern PACKAGE double __fastcall VDWRadius(int AtNr);
extern PACKAGE bool __fastcall CheckCASNr(int CASNum);
extern PACKAGE AnsiString __fastcall FormatCASNr(int CASNr);
extern PACKAGE bool __fastcall ConvertStrToCASNr(AnsiString InString, int &CASNr);
extern PACKAGE int __fastcall NumOuterElectrons(int AtNr);
extern PACKAGE AnsiString __fastcall ShortElectronConfig(int AtNr);
extern PACKAGE AnsiString __fastcall FullElectronConfig(int AtNr);

}	/* namespace Cdata */
using namespace Cdata;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// cdata
