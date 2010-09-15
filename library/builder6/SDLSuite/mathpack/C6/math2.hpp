// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'math2.pas' rev: 6.00

#ifndef math2HPP
#define math2HPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <vector.hpp>	// Pascal unit
#include <matrix.hpp>	// Pascal unit
#include <math1.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Math2
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLMath2Error;
class PASCALIMPLEMENTATION ESDLMath2Error : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLMath2Error(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLMath2Error(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLMath2Error(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLMath2Error(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLMath2Error(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLMath2Error(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLMath2Error(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLMath2Error(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLMath2Error(void) { }
	#pragma option pop
	
};


typedef double __fastcall (*TCalcDistFunc)(int ix);

#pragma option push -b-
enum TClusterMethod { cmSingleLink, cmCompleteLink, cmWard, cmAvgLink, cmFlexLink };
#pragma option pop

#pragma option push -b-
enum TKnnWMode { kwmGauss, kwmAverage, kwmMedian, kwmLinear };
#pragma option pop

class DELPHICLASS TCurveFit;
class PASCALIMPLEMENTATION TCurveFit : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	double sumx;
	double sumy;
	double sumxq;
	double sumyq;
	double sumDiff;
	double SumDiffq;
	double sumxy;
	double sumx2y;
	double sumx3;
	double sumx4;
	double sum1byy;
	double sum1byyq;
	double sumxbyy;
	double sumybyx;
	double sum1byx;
	double sum1byxq;
	double sumlnx;
	double sumlnxq;
	double sumylnx;
	double sumlny;
	double sumlnyq;
	double sumxlny;
	double sumxqlny;
	int FNumData;
	bool FNatural1;
	bool FNaturalN;
	double FY1Dash;
	double FYNDash;
	Vector::TVector* SumXArray;
	Vector::TVector* RHS;
	Vector::TVector* Spl2Deriv;
	Vector::TVector* SplSortedX;
	Vector::TVector* SplSortedY;
	Matrix::TMatrix* FData;
	bool FSplineValid;
	double __fastcall GetMeanX(void);
	double __fastcall GetMeanY(void);
	double __fastcall GetStdDevX(void);
	double __fastcall GetStdDevY(void);
	double __fastcall GetMeanDiff(void);
	double __fastcall GetStdDevDiff(void);
	double __fastcall GetRxy(void);
	double __fastcall GetDataX(int ix);
	double __fastcall GetDataY(int ix);
	void __fastcall ExchangeDuringSort(System::TObject* Sender, Byte ExchgWhat, int index1, int index2, int first, int last);
	void __fastcall PrepareSpline(void);
	void __fastcall SetNatural1(bool value);
	void __fastcall SetNaturalN(bool value);
	void __fastcall SetY1Dash(double value);
	void __fastcall SetYNDash(double value);
	
public:
	__fastcall virtual TCurveFit(Classes::TComponent* AOwner);
	__fastcall virtual ~TCurveFit(void);
	void __fastcall Init(void);
	void __fastcall EnterStatValue(double x, double y);
	void __fastcall RemoveStatValue(int ix);
	void __fastcall CalcStatistics(int &NumData, double &MeanX, double &MeanY, double &StdevX, double &StdevY, double &MeanDiff, double &StdevDiff, double &rxy);
	void __fastcall CalcGaussFit(double &k0, double &k1, double &k2, double &FitQual);
	void __fastcall CalcLinFit(double &k, double &d, double &FitQual);
	void __fastcall CalcLogFit(double &k0, double &k1, double &FitQual);
	void __fastcall CalcParabolFit(double &k0, double &k1, double &k2, double &FitQual);
	bool __fastcall CalcPolyFit(const Byte nOrder, double * kArray, const int kArray_Size, double &FitQual);
	void __fastcall CalcReciLinFit(double &k0, double &k1, double &FitQual);
	void __fastcall CalcHyperbolFit(double &k0, double &k1, double &FitQual);
	double __fastcall CubicSpline(double x);
	__property double DataX[int ix] = {read=GetDataX};
	__property double DataY[int ix] = {read=GetDataY};
	__property int NumData = {read=FNumData, nodefault};
	__property double MeanX = {read=GetMeanX};
	__property double MeanY = {read=GetMeanY};
	__property double StdDevX = {read=GetStdDevX};
	__property double StdDevY = {read=GetStdDevY};
	__property double MeanDiff = {read=GetMeanDiff};
	__property double StdDevDiff = {read=GetStdDevDiff};
	__property double CorrCoeff = {read=GetRxy};
	__property double SplineDerivY1 = {read=FY1Dash, write=SetY1Dash};
	__property double SplineDerivYN = {read=FYNDash, write=SetYNDash};
	__property bool SplineNatural1 = {read=FNatural1, write=SetNatural1, nodefault};
	__property bool SplineNaturalN = {read=FNaturalN, write=SetNaturalN, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxPolyFitOrder = 0x8;
extern PACKAGE void __fastcall PolynomialSmooth(Vector::TVector* SourceVec, int FirstElem, int LastElem, Vector::TVector* DestVec, int WindowSize);
extern PACKAGE void __fastcall FirstDeriv(Vector::TVector* SourceVec, int FirstElem, int LastElem, Vector::TVector* DestVec, int WindowSize);
extern PACKAGE bool __fastcall CalcCovar(Matrix::TMatrix* InData, Matrix::TMatrix* CovarMat, int LoC, int HiC, int LoR, int HiR, int Scaling);
extern PACKAGE bool __fastcall CalcEigVec(Matrix::TMatrix* InMat);
extern PACKAGE double __fastcall GetEigenResult(int EigVecNum, int VecElem);
extern PACKAGE int __fastcall GetEigenSize(void);
extern PACKAGE void __fastcall RemoveEigenMatrix(void);
extern PACKAGE bool __fastcall CalcPrincComp(Matrix::TMatrix* InData, int LoC, int HiC, int LoR, int HiR, int Scaling);
extern PACKAGE double __fastcall CalcFishQ(double m1, double m2, double s1, double s2);
extern PACKAGE void __fastcall MeanDistanceKNN(Matrix::TMatrix* InMat, int kn, int FirstRow, int LastRow, Vector::TVector* &DistVec);
extern PACKAGE void __fastcall FindCenters(Matrix::TMatrix* InMat, int RowLo, int RowHi, int NumCent, Matrix::TMatrix* &Centers, double &MeanDist);
extern PACKAGE void __fastcall FindNearestNeighbors(int k, Matrix::TMatrix* InMat, int FirstObj, int LastObj, Vector::TVector* DatVec, Matrix::TMatrix* KNNList, TCalcDistFunc CalcDist);
extern PACKAGE void __fastcall EstimateByKNN(Matrix::TMatrix* InMat, Vector::TVector* TargetVec, int kn, TKnnWMode WeightingMode, double SmoothFact, Vector::TVector* EstInVar, double &EstTarget, double &EstMeanDist);
extern PACKAGE double __fastcall CalcGaussKernel(Vector::TVector* Probe, Vector::TVector* RefCenter, double Width);
extern PACKAGE double __fastcall CalcGaussKernelMat(Vector::TVector* Probe, Matrix::TMatrix* RefCenterMat, int RefCenterIx, double Width);
extern PACKAGE int __fastcall AgglomClustering(Matrix::TMatrix* InMat, Matrix::TDistMode DistanceMeasure, TClusterMethod ClusterMethod, double alpha, Matrix::TIntMatrix* &ClustResult, Vector::TVector* &ClustDist, Vector::TVector* &DendroCoords);
extern PACKAGE bool __fastcall SingValDecomp(Matrix::TMatrix* MatAU, Matrix::TMatrix* MatV, Vector::TVector* VecW);
extern PACKAGE bool __fastcall SingValEquSolve(Matrix::TMatrix* MatAU, Matrix::TMatrix* MatV, Vector::TVector* VecW, Vector::TVector* VecB, Vector::TVector* VecX, Vector::TVector* VecdX);
extern PACKAGE bool __fastcall MultiLinReg(Matrix::TMatrix* InData, Vector::TVector* OutData, Vector::TVector* Coeff, Vector::TVector* DeltaCoeff);
extern PACKAGE double __fastcall SphereGreatCircleDist(double radius, double Lat1, double Long1, double Lat2, double Long2);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Math2 */
using namespace Math2;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// math2
