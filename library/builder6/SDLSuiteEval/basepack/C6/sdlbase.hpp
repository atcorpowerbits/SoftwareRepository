// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'sdlbase.pas' rev: 6.00

#ifndef sdlbaseHPP
#define sdlbaseHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Sdlbase
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TBkgFill { bfSimple, bfStretch, bfTile };
#pragma option pop

#pragma option push -b-
enum TBoundingBox { bbNone, bbFrame, bbFaces };
#pragma option pop

#pragma option push -b-
enum TColorScheme { csBWG, csSystem };
#pragma option pop

#pragma option push -b-
enum TFrameStyle { fsNone, fsSimple, fsLowered, fsRaised, fsEmbossed, fsEngraved };
#pragma option pop

struct TPointDouble
{
	double X;
	double Y;
} ;

typedef void __fastcall (__closure *TSortExchgEvent)(System::TObject* Sender, Byte ExchgWhat, int index1, int index2, int first, int last);

#pragma option push -b-
enum TLanguage { lgEnglish, lgGerman, lgFrench, lgSpanish };
#pragma option pop

typedef Types::TPoint TQuad[4];

struct TRectDouble
{
	
	union
	{
		struct 
		{
			TPointDouble TopLeft;
			TPointDouble BottomRight;
			
		};
		struct 
		{
			double Left;
			double Top;
			double Right;
			double Bottom;
			
		};
		
	};
} ;

#pragma option push -b-
enum VarType { rnum, dnum, snum, inum, lnum, Bool, strg };
#pragma option pop

typedef void __fastcall (*FeedBackProcType)(int StateCnt);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::SmallString<4>  MonthShort[4][12];
extern PACKAGE System::SmallString<10>  MonthLong[4][12];
extern PACKAGE System::SmallString<3>  WeekDayShort[4][7];
extern PACKAGE System::SmallString<10>  WeekDayLong[4][7];
extern PACKAGE System::SmallString<6>  NumWords[4][13];
extern PACKAGE int ProcStat;
extern PACKAGE FeedBackProcType MathFeedBackProc;

}	/* namespace Sdlbase */
using namespace Sdlbase;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// sdlbase
