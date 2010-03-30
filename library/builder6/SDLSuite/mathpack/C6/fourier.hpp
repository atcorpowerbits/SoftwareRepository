// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'fourier.pas' rev: 6.00

#ifndef fourierHPP
#define fourierHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Fourier
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TFastFourierWgtWin { fwRectangle, fwTriangle, fwCos2, fwGauss, fwHamming, fwBlackman };
#pragma option pop

class DELPHICLASS TFastFourier;
class PASCALIMPLEMENTATION TFastFourier : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FNumData;
	void *FData;
	TFastFourierWgtWin FWgtWin;
	bool MaxValuesValid;
	double FMaxReal;
	double FMaxImag;
	double FMinReal;
	double FMinImag;
	double FMaxPower;
	double FMaxMagni;
	double __fastcall GetRealVal(int ix);
	void __fastcall SetRealVal(int ix, double v);
	double __fastcall GetImagVal(int ix);
	void __fastcall SetImagVal(int ix, double v);
	void __fastcall SetNumData(int ndata);
	void __fastcall SetWgtWin(TFastFourierWgtWin ww);
	double __fastcall GetPowerSpec(int ix);
	double __fastcall GetMagnitude(int ix);
	double __fastcall GetFSerSin(int n);
	double __fastcall GetFSerCos(int n);
	double __fastcall GetPhase(int ix);
	double __fastcall GetMaxPower(void);
	double __fastcall GetMaxMagni(void);
	double __fastcall GetMaxReal(void);
	double __fastcall GetMaxImag(void);
	double __fastcall GetMinReal(void);
	double __fastcall GetMinImag(void);
	void __fastcall DoFFT(int isign);
	void __fastcall CalcMaxValues(void);
	
public:
	__fastcall virtual TFastFourier(Classes::TComponent* AOwner);
	__fastcall virtual ~TFastFourier(void);
	__property double RealSpec[int ix] = {read=GetRealVal, write=SetRealVal};
	__property double ImagSpec[int ix] = {read=GetImagVal, write=SetImagVal};
	void __fastcall Clear(void);
	void __fastcall ClearImag(void);
	void __fastcall ClearReal(void);
	void __fastcall Transform(void);
	double __fastcall FreqOfLine(int ix, double SampleTime);
	void __fastcall InverseTransform(void);
	__property double PowerSpec[int ix] = {read=GetPowerSpec};
	double __fastcall RMS(int FirstIx, int LastIx);
	__property double Magnitude[int ix] = {read=GetMagnitude};
	__property double FourSerSinCoeff[int n] = {read=GetFSerSin};
	__property double FourSerCosCoeff[int n] = {read=GetFSerCos};
	__property double Phase[int ix] = {read=GetPhase};
	__property double PowerMax = {read=GetMaxPower};
	__property double MagniMax = {read=GetMaxMagni};
	__property double RealMax = {read=GetMaxReal};
	__property double ImagMax = {read=GetMaxImag};
	__property double RealMin = {read=GetMinReal};
	__property double ImagMin = {read=GetMinImag};
	__property void * DataBuffer = {read=FData};
	
__published:
	__property int SpectrumSize = {read=FNumData, write=SetNumData, nodefault};
	__property TFastFourierWgtWin WeightingWindow = {read=FWgtWin, write=SetWgtWin, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Fourier */
using namespace Fourier;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// fourier
