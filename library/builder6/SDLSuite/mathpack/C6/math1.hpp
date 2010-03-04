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
class DELPHICLASS TRandGen;
class PASCALIMPLEMENTATION TRandGen : public System::TObject 
{
	typedef System::TObject inherited;
	
private:
	double FLowBorder;
	double FHighBorder;
	int FResolution;
	void *FDistVec;
	void __fastcall SetResolution(int res);
	double __fastcall GetProbability(int Idx);
	double __fastcall GetRandNum(void);
	double __fastcall GetLambda(int ix);
	void __fastcall SetProbability(int Idx, double Value);
	
public:
	__fastcall TRandGen(void);
	__fastcall virtual ~TRandGen(void);
	__property double HighBorder = {read=FHighBorder, write=FHighBorder};
	__property double Lambda[int ix] = {read=GetLambda};
	__property double LowBorder = {read=FLowBorder, write=FLowBorder};
	void __fastcall Normalize(void);
	void __fastcall NormalDistri(double m, double s);
	__property double Probability[int ix] = {read=GetProbability, write=SetProbability};
	__property double Random = {read=GetRandNum};
	int __fastcall IndexOfLambda(double Lambda);
	__property int Resolution = {read=FResolution, write=SetResolution, nodefault};
	void __fastcall UniformDistri(void);
	void __fastcall WeibullDistri(double alpha, double beta);
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE bool AbortMathProc;
extern PACKAGE AnsiString __fastcall Decimal(int innum, Byte places);
extern PACKAGE void __fastcall CalcScalePars(int Ntick, double LowVal, double HighVal, double &LowTick, double &Distance, Word &Divi);
extern PACKAGE int __fastcall ScanBin(AnsiString Instring, int &Idx);
extern PACKAGE int __fastcall ScanHex(AnsiString Instring, int &Idx);
extern PACKAGE int __fastcall ScanOctal(AnsiString Instring, int &Idx);
extern PACKAGE int __fastcall ScanDecimal(AnsiString Instring, int &Idx);
extern PACKAGE double __fastcall ScanFPNum(AnsiString Instring, bool AllowExp, int DecPChar, int &Idx);
extern PACKAGE AnsiString __fastcall Hex(int innum, Byte places);
extern PACKAGE AnsiString __fastcall Octal(int innum, Byte places);
extern PACKAGE AnsiString __fastcall Bin(int innum, Byte places);
extern PACKAGE void __fastcall SortArray(void * ArrayAdr, int LengArray, Sdlbase::VarType TypArray, bool Ascending);
extern PACKAGE void __fastcall ExChange(void *x, void *y, Word size);
extern PACKAGE System::TDateTime __fastcall ScanDateTime(AnsiString InString, AnsiString Format, Sdlbase::TLanguage Language, int &error);
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
extern PACKAGE int __fastcall SortIntoArray(void * ArrayAdr, int LengArray, Sdlbase::VarType TypArray, void * value, bool Ascending, bool Dublicates);
extern PACKAGE void __fastcall InsertIntoArray(void * ArrayAdr, int LengArray, Sdlbase::VarType TypArray, void * value, int index);
extern PACKAGE double __fastcall Min(double a, double b);
extern PACKAGE double __fastcall Max(double a, double b);
extern PACKAGE int __fastcall Sign(double a);
extern PACKAGE bool __fastcall BRandom(double p);
extern PACKAGE double __fastcall GRandom(void);
extern PACKAGE double __fastcall LongRand(int seed);
extern PACKAGE bool __fastcall WithinBounds(double Inval, double Boundary1, double Boundary2);
extern PACKAGE int __fastcall IntPos(double InNum);
extern PACKAGE int __fastcall IntNeg(double InNum);
extern PACKAGE Word __fastcall GrayCode(Word InNum);
extern PACKAGE int __fastcall StrToIntDefault(AnsiString InStr, int Def);

}	/* namespace Math1 */
using namespace Math1;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// math1
