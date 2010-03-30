// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'statis.pas' rev: 6.00

#ifndef statisHPP
#define statisHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Statis
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TSignifLevel { Dot20, Dot15, Dot10, Dot05, Dot01 };
#pragma option pop

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE double __fastcall WeibullDensity(double x, double alpha, double beta);
extern PACKAGE double __fastcall KolmogSmir1SampleTestStat(int SampleSize, TSignifLevel alpha);
extern PACKAGE double __fastcall nDistriQuantile(double p);
extern PACKAGE double __fastcall nDistriDensity(double u);
extern PACKAGE double __fastcall nDistriIntegral(double u);
extern PACKAGE double __fastcall chi2DistriIntegral(double chi2, int df);
extern PACKAGE double __fastcall Chi2DistriDensity(double chi2, int df);
extern PACKAGE double __fastcall LnGamma(double x);
extern PACKAGE double __fastcall CalcFishQ(double m1, double m2, double s1, double s2);
extern PACKAGE int __fastcall BinomCoeff(int n, int k);
extern PACKAGE double __fastcall LnBinomCoeff(int n, int k);
extern PACKAGE double __fastcall LnBeta(double z, double w);
extern PACKAGE double __fastcall IncompleteBeta(double x, double a, double b);
extern PACKAGE double __fastcall FDistriDensity(double F, int df1, int df2);
extern PACKAGE double __fastcall tDistriIntegral(double t, int df);
extern PACKAGE double __fastcall tDistriDensity(double t, int df);
extern PACKAGE double __fastcall FDistriIntegral(double F, int df1, int df2);
extern PACKAGE double __fastcall FDistriQuantile(double p, int df1, int df2);
extern PACKAGE double __fastcall tDistriQuantile(double p, int df);
extern PACKAGE double __fastcall chi2DistriQuantile(double p, int df);
extern PACKAGE double __fastcall FisherTransform(double x);
extern PACKAGE double __fastcall FisherTransformInv(double x);
extern PACKAGE double __fastcall ConfidenceInterval(double alpha, double StdDev, int NumData);

}	/* namespace Statis */
using namespace Statis;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// statis
