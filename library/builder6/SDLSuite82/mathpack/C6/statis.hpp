// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'statis.pas' rev: 6.00

#ifndef statisHPP
#define statisHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <math2.hpp>	// Pascal unit
#include <vector.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Statis
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLStatisError;
class PASCALIMPLEMENTATION ESDLStatisError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLStatisError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLStatisError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLStatisError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLStatisError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLStatisError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLStatisError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLStatisError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLStatisError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLStatisError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TSignifLevel { Dot20, Dot15, Dot10, Dot05, Dot01 };
#pragma option pop

#pragma option push -b-
enum TtTestVersion { ttPaired, ttHomoScedastic, ttHeteroScedastic };
#pragma option pop

typedef DynamicArray<double >  statis__3;

class DELPHICLASS TRandGen;
class PASCALIMPLEMENTATION TRandGen : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	double FLowBorder;
	double FHighBorder;
	int FResolution;
	DynamicArray<double >  FDistVec;
	void __fastcall SetResolution(int res);
	double __fastcall GetProbability(int Idx);
	double __fastcall GetRandNum(void);
	double __fastcall GetLambda(int ix);
	void __fastcall SetProbability(int Idx, double Value);
	
public:
	__fastcall virtual TRandGen(Classes::TComponent* AOwner);
	__fastcall virtual ~TRandGen(void);
	__property double Lambda[int ix] = {read=GetLambda};
	void __fastcall Normalize(void);
	void __fastcall NormalDistri(double m, double s);
	__property double Probability[int ix] = {read=GetProbability, write=SetProbability};
	__property double Random = {read=GetRandNum};
	int __fastcall IndexOfLambda(double Lambda);
	void __fastcall UniformDistri(void);
	void __fastcall WeibullDistri(double alpha, double beta);
	
__published:
	__property double HighBorder = {read=FHighBorder, write=FHighBorder};
	__property double LowBorder = {read=FLowBorder, write=FLowBorder};
	__property int Resolution = {read=FResolution, write=SetResolution, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "statis_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
extern PACKAGE double __fastcall KolmogSmir1SampleTestStat(int SampleSize, TSignifLevel alpha);
extern PACKAGE double __fastcall nDistriQuantile(double p);
extern PACKAGE double __fastcall WeibullDensity(double x, double alpha, double beta);
extern PACKAGE double __fastcall IncompleteGamma(double x, double a);
extern PACKAGE double __fastcall Erf(double x);
extern PACKAGE double __fastcall ErfApprox(double x);
extern PACKAGE double __fastcall nDistriDensity(double u);
extern PACKAGE double __fastcall nDistriIntegral(double u);
extern PACKAGE double __fastcall LnGamma(double x);
extern PACKAGE double __fastcall CalcFishQ(double m1, double m2, double s1, double s2);
extern PACKAGE int __fastcall BinomCoeff(int n, int k);
extern PACKAGE double __fastcall LnBinomCoeff(int n, int k);
extern PACKAGE double __fastcall LnBeta(double z, double w);
extern PACKAGE double __fastcall IncompleteBeta(double x, double a, double b);
extern PACKAGE double __fastcall FisherTransform(double x);
extern PACKAGE double __fastcall FisherTransformInv(double x);
extern PACKAGE double __fastcall ConfidenceInterval(double alpha, double StdDev, int NumData);
extern PACKAGE double __fastcall chi2DistriIntegral(double chi2, int df);
extern PACKAGE double __fastcall Chi2DistriDensity(double chi2, int df);
extern PACKAGE double __fastcall FDistriDensity(double F, int df1, int df2);
extern PACKAGE double __fastcall tDistriIntegral(double t, int df);
extern PACKAGE double __fastcall tDistriDensity(double t, int df);
extern PACKAGE double __fastcall FDistriIntegral(double F, int df1, int df2);
extern PACKAGE double __fastcall FDistriQuantile(double p, int df1, int df2);
extern PACKAGE double __fastcall tDistriQuantile(double p, int df);
extern PACKAGE double __fastcall chi2DistriQuantile(double p, int df);
extern PACKAGE double __fastcall Perform2SampleTTest(Vector::TVector* Data1, Vector::TVector* Data2, TtTestVersion TestType, bool OneSided, double &Mean1, double &Mean2, double &Stdv1, double &Stdv2, double &MeanDiff, double &StdDiff, double &tStatistic, int &df)/* overload */;
extern PACKAGE double __fastcall Perform2SampleTTest(Vector::TVector* Data1, Vector::TVector* Data2, TtTestVersion TestType, bool OneSided)/* overload */;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Statis */
using namespace Statis;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// statis
