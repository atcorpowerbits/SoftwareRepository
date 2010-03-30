// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'vector.pas' rev: 6.00

#ifndef vectorHPP
#define vectorHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Vector
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLVectorError;
class PASCALIMPLEMENTATION ESDLVectorError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLVectorError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLVectorError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLVectorError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLVectorError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLVectorError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLVectorError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLVectorError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLVectorError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLVectorError(void) { }
	#pragma option pop
	
};


typedef DynamicArray<double >  vector__3;

class DELPHICLASS TVector;
class DELPHICLASS TIntVector;
class PASCALIMPLEMENTATION TVector : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
public:
	double operator[](int ix) { return Elem[ix]; }
	
private:
	int FNElem;
	DynamicArray<double >  FVec;
	Classes::TNotifyEvent FOnChange;
	Sdlbase::TSortExchgEvent FOnSortExchange;
	double __fastcall GetVal(int Elem);
	void __fastcall SetVal(int Elem, double Value);
	double __fastcall CalcVecLeng(void);
	void __fastcall SetVecLeng(double Value);
	void __fastcall SetVecSize(int sz);
	void __fastcall SkewKurtIntern(int LowElem, int HighElem, double &Skewness, double &Kurtosis, int &NumData);
	
protected:
	void __fastcall SortExchange(Byte ExchgWhat, int index1, int index2, int first, int last);
	
public:
	__fastcall virtual TVector(Classes::TComponent* AOwner);
	__fastcall virtual ~TVector(void);
	void __fastcall Add(TVector* OtherVec);
	void __fastcall Clear(void);
	void __fastcall Changed(void);
	void __fastcall Clone(TVector* VecSource);
	void __fastcall CopyFrom(TVector* VecSource, int SourceElemLo, int SourceElemHi, int DestElem);
	double __fastcall Correlate(TVector* OtherVec, int ElemShift);
	double __fastcall DotProduct(TVector* OtherVec);
	void __fastcall Fill(double value);
	double __fastcall GeometricMean(int LowElem, int HighElem);
	double __fastcall HarmonicMean(int LowElem, int HighElem);
	bool __fastcall Histogram(int FirstElem, int LastElem, double FirstBin, double LastBin, double BinWidth, TIntVector* Histo, int &Underflow, int &Overflow, int &MaxCnt);
	__property double Leng = {read=CalcVecLeng, write=SetVecLeng};
	void __fastcall MeanVar(int LowElem, int HighElem, double &Mean, double &Variance);
	void __fastcall MinMax(int LowElem, int HighElem, double &Minimum, double &Maximum);
	double __fastcall Percentile(double prob, int LowElem, int HighElem);
	bool __fastcall Quartiles(int LowElem, int HighElem, double &Q1, double &Q2, double &Q3);
	bool __fastcall Resize(int NE);
	void __fastcall SkewKurt(int LowElem, int HighElem, double &Skewness, double &Kurtosis);
	void __fastcall SkewKurtSample(int LowElem, int HighElem, double &Skewness, double &Kurtosis);
	void __fastcall ShuffleElems(void);
	void __fastcall SMult(double scalar);
	void __fastcall SortElems(bool Ascending, int RangeFirst, int RangeLast);
	void __fastcall Subtract(TVector* OtherVec);
	double __fastcall Sum(int LowElem, int HighElem);
	__property double Elem[int ix] = {read=GetVal, write=SetVal/*, default*/};
	
__published:
	__property int NrOfElem = {read=FNElem, write=SetVecSize, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Sdlbase::TSortExchgEvent OnSortExchange = {read=FOnSortExchange, write=FOnSortExchange};
};


typedef DynamicArray<int >  vector__5;

class PASCALIMPLEMENTATION TIntVector : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
public:
	int operator[](int ix) { return Elem[ix]; }
	
private:
	int FNElem;
	DynamicArray<int >  FVec;
	Classes::TNotifyEvent FOnChange;
	Sdlbase::TSortExchgEvent FOnSortExchange;
	int __fastcall GetVal(int Elem);
	void __fastcall SetVal(int Elem, int Value);
	double __fastcall CalcVecLeng(void);
	void __fastcall SetIntVecSize(int sz);
	void __fastcall SkewKurtIntern(int LowElem, int HighElem, double &Skewness, double &Kurtosis, int &NumData);
	
protected:
	void __fastcall SortExchange(Byte ExchgWhat, int index1, int index2, int first, int last);
	
public:
	__fastcall virtual TIntVector(Classes::TComponent* AOwner);
	__fastcall virtual ~TIntVector(void);
	void __fastcall Add(TIntVector* OtherVec);
	void __fastcall Changed(void);
	void __fastcall Clear(void);
	void __fastcall Clone(TIntVector* VecSource);
	void __fastcall CopyFrom(TIntVector* VecSource, int SourceElemLo, int SourceElemHi, int DestElem);
	int __fastcall Correlate(TIntVector* OtherVec, int ElemShift);
	int __fastcall DotProduct(TIntVector* OtherVec);
	void __fastcall Fill(int value);
	double __fastcall GeometricMean(int LowElem, int HighElem);
	double __fastcall HarmonicMean(int LowElem, int HighElem);
	__property double Leng = {read=CalcVecLeng};
	void __fastcall MeanVar(int LowElem, int HighElem, double &Mean, double &Variance);
	void __fastcall MinMax(int LowElem, int HighElem, int &Minimum, int &Maximum);
	double __fastcall Percentile(double prob, int LowElem, int HighElem);
	bool __fastcall Quartiles(int LowElem, int HighElem, double &Q1, double &Q2, double &Q3);
	bool __fastcall Resize(int NE);
	void __fastcall SkewKurt(int LowElem, int HighElem, double &Skewness, double &Kurtosis);
	void __fastcall SkewKurtSample(int LowElem, int HighElem, double &Skewness, double &Kurtosis);
	void __fastcall SortElems(bool Ascending, int RangeFirst, int RangeLast);
	void __fastcall ShuffleElems(void);
	void __fastcall SMult(int scalar);
	void __fastcall Subtract(TIntVector* OtherVec);
	int __fastcall Sum(int LowElem, int HighElem);
	__property int Elem[int ix] = {read=GetVal, write=SetVal/*, default*/};
	
__published:
	__property int NrOfElem = {read=FNElem, write=SetIntVecSize, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Sdlbase::TSortExchgEvent OnSortExchange = {read=FOnSortExchange, write=FOnSortExchange};
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "vector_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Vector */
using namespace Vector;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// vector
