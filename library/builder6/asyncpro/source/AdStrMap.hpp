// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStrMap.pas' rev: 6.00

#ifndef AdStrMapHPP
#define AdStrMapHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adstrmap
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 4)
struct AdMessageNumberLookupRecord
{
	int MessageNumber;
	AnsiString MessageString;
} ;
#pragma pack(pop)

typedef AdMessageNumberLookupRecord AdStrMap__1[892];

//-- var, const, procedure ---------------------------------------------------
static const Word AdMaxMessages = 0x37b;
extern PACKAGE AdMessageNumberLookupRecord AdMessageNumberLookup[892];

}	/* namespace Adstrmap */
using namespace Adstrmap;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStrMap
