// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'math1.pas' rev: 6.00

#ifndef math1HPP
#define math1HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Math1
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLMath1Error;
class PASCALIMPLEMENTATION ESDLMath1Error : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLMath1Error(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLMath1Error(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLMath1Error(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLMath1Error(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLMath1Error(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLMath1Error(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLMath1Error(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLMath1Error(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLMath1Error(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TDegreeFormat { dfDeg, dfDegMin, dfDegMinSec };
#pragma option pop

//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "math1_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE bool AbortMathProc;
extern PACKAGE AnsiString __fastcall Decimal(int innum, Byte places);
extern PACKAGE Byte __fastcall BitReversal(Byte InByte);
extern PACKAGE AnsiString __fastcall strf(double r, int FieldWidth, int DecP);
extern PACKAGE bool __fastcall IsPrime(int number);
extern PACKAGE void __fastcall CancelFraction(int &numer, int &denom);
extern PACKAGE Byte __fastcall DecodeBit(int ix);
extern PACKAGE int __fastcall DecodeLong(int ix);
extern PACKAGE int __fastcall EncodeLong(int value);
extern PACKAGE int __fastcall CountBits(Byte InByte);
extern PACKAGE double __fastcall lg(double x);
extern PACKAGE double __fastcall ld(double x);
extern PACKAGE double __fastcall sinh(double x);
extern PACKAGE double __fastcall cosh(double x);
extern PACKAGE double __fastcall tgh(double x);
extern PACKAGE double __fastcall tg(double x);
extern PACKAGE double __fastcall cot(double x);
extern PACKAGE AnsiString __fastcall MakeEFormat(double x, int w, int d);
extern PACKAGE int __fastcall SortIntoArray(void * ArrayAdr, int LengArray, Sdlbase::TVarKind TypArray, void * value, bool Ascending, bool Duplicates)/* overload */;
extern PACKAGE int __fastcall SortIntoArray(double * SArray, const int SArray_Size, double value, bool Ascending, bool Duplicates)/* overload */;
extern PACKAGE int __fastcall SortIntoArray(float * SArray, const int SArray_Size, float value, bool Ascending, bool Duplicates)/* overload */;
extern PACKAGE int __fastcall SortIntoArray(int * SArray, const int SArray_Size, int value, bool Ascending, bool Duplicates)/* overload */;
extern PACKAGE void __fastcall InsertIntoArray(void * ArrayAdr, int LengArray, Sdlbase::TVarKind TypArray, void * value, int index)/* overload */;
extern PACKAGE void __fastcall InsertIntoArray(double * SArray, const int SArray_Size, double value, int index)/* overload */;
extern PACKAGE void __fastcall InsertIntoArray(float * SArray, const int SArray_Size, float value, int index)/* overload */;
extern PACKAGE void __fastcall InsertIntoArray(int * SArray, const int SArray_Size, int value, int index)/* overload */;
extern PACKAGE void __fastcall SortArray(void * ArrayAdr, int LengArray, Sdlbase::TVarKind TypArray, bool Ascending)/* overload */;
extern PACKAGE void __fastcall SortArray(double * SArray, const int SArray_Size, bool Ascending)/* overload */;
extern PACKAGE void __fastcall SortArray(int * SArray, const int SArray_Size, bool Ascending)/* overload */;
extern PACKAGE void __fastcall SortArray(float * SArray, const int SArray_Size, bool Ascending)/* overload */;
extern PACKAGE double __fastcall Min(double a, double b);
extern PACKAGE double __fastcall Max(double a, double b);
extern PACKAGE int __fastcall Signum(double a);
extern PACKAGE bool __fastcall BRandom(double p);
extern PACKAGE double __fastcall GRandom(void);
extern PACKAGE double __fastcall LongRand(int seed);
extern PACKAGE bool __fastcall WithinBounds(double Inval, double Boundary1, double Boundary2);
extern PACKAGE int __fastcall IntPos(double InNum);
extern PACKAGE int __fastcall IntNeg(double InNum);
extern PACKAGE double __fastcall Round125(double InNum);
extern PACKAGE Word __fastcall GrayCode(Word InNum);
extern PACKAGE int __fastcall StrToIntDefault(AnsiString InStr, int Def);
extern PACKAGE AnsiString __fastcall DegreeToStr(double innum, TDegreeFormat format, int precision);
extern PACKAGE void __fastcall ConvertDegrees(double &deg, double &min, double &sec, TDegreeFormat InFormat, TDegreeFormat OutFormat);
extern PACKAGE double __fastcall AngleToXAxis(double x, double y);
extern PACKAGE double __fastcall EuclideanDistance(double x1, double y1, double x2, double y2);
extern PACKAGE Extended __fastcall Factorial(int argument);
extern PACKAGE AnsiString __fastcall Roman(int InNum);
extern PACKAGE void __fastcall CalcScalePars(int Ntick, Extended LowVal, Extended HighVal, Extended &LowTick, Extended &Distance, Word &Divi);
extern PACKAGE AnsiString __fastcall Hex(int innum, Byte places);
extern PACKAGE AnsiString __fastcall Octal(int innum, Byte places);
extern PACKAGE AnsiString __fastcall Bin(int innum, Byte places);
extern PACKAGE void __fastcall ExChange(void *x, void *y, Word size)/* overload */;
extern PACKAGE void __fastcall ExChange(int &x, int &y)/* overload */;
extern PACKAGE void __fastcall ExChange(Byte &x, Byte &y)/* overload */;
extern PACKAGE void __fastcall ExChange(float &x, float &y)/* overload */;
extern PACKAGE void __fastcall ExChange(double &x, double &y)/* overload */;
extern PACKAGE void __fastcall ExChange(Extended &x, Extended &y)/* overload */;
extern PACKAGE void __fastcall ExChange(AnsiString &x, AnsiString &y)/* overload */;
extern PACKAGE void __fastcall ExChange(bool &x, bool &y)/* overload */;
extern PACKAGE void __fastcall ExChange(char &x, char &y)/* overload */;
extern PACKAGE void __fastcall ExChange(Word &x, Word &y)/* overload */;
extern PACKAGE void __fastcall ExChange(Shortint &x, Shortint &y)/* overload */;
extern PACKAGE void __fastcall ExChange(unsigned &x, unsigned &y)/* overload */;
extern PACKAGE void __fastcall ExChange(__int64 &x, __int64 &y)/* overload */;
extern PACKAGE int __fastcall ScanHex(AnsiString Instring, int &Idx);
extern PACKAGE int __fastcall ScanOctal(AnsiString Instring, int &Idx);
extern PACKAGE int __fastcall ScanBin(AnsiString Instring, int &Idx);
extern PACKAGE double __fastcall ScanDegrees(AnsiString InString, int &Idx, bool ExpectGeo, int &Error);
extern PACKAGE System::TDateTime __fastcall ScanDateTime(AnsiString InString, AnsiString Format, Sdlbase::TLanguage Language, int &error);
extern PACKAGE int __fastcall ScanDecimal(AnsiString Instring, int &Idx);
extern PACKAGE double __fastcall ScanFPNum(AnsiString Instring, bool AllowExp, int DecPChar, int &Idx);
extern PACKAGE bool __fastcall IsValidDouble(AnsiString InString, bool AllowExp, int DecPChar);

}	/* namespace Math1 */
using namespace Math1;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// math1
