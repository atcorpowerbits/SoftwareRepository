// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'kohonen.pas' rev: 6.00

#ifndef kohonenHPP
#define kohonenHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <matrix.hpp>	// Pascal unit
#include <vector.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Kohonen
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TKohonenXMLTag { xmlSizeX, xmlSizeY, xmlComment, xmlNrInsens, xmlMaxNeighb, xmlMaxSteps, xmlMaxAlpha, xmlCurStep, xmlCyclic, xmlCell, xmlMeanStdDev, xmlEndKohonen, xmlInvalid };
#pragma option pop

class DELPHICLASS TKohonen;
class PASCALIMPLEMENTATION TKohonen : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FMaxNeighb;
	AnsiString FComment;
	int FCurNeighb;
	int FMaxSteps;
	int FCurStep;
	double FMaxAlpha;
	double FCurAlpha;
	Matrix::TMat3D* FKohMat;
	int FSizeX;
	int FSizeY;
	int FNrInSens;
	int FNrTrnObj;
	Vector::TVector* MeanVec;
	Vector::TVector* StdDevVec;
	bool FCyclic;
	bool FAbort;
	bool FReserved;
	Sdlbase::TOnPercentDoneEvent FOnFeedback;
	Matrix::TMatrix* FDataMat;
	bool FMatsAdj;
	int __fastcall ProcessXmlTag(TKohonenXMLTag xmlTag, AnsiString attr, AnsiString cont);
	double __fastcall GetWeight(int ix, int iy, int wi);
	void __fastcall SetNumInsens(int nl);
	void __fastcall SetSizeX(int x);
	void __fastcall SetSizeY(int y);
	void __fastcall SetWeigtsToRandom(void);
	void __fastcall SetDataMat(Matrix::TMatrix* x);
	
protected:
	void __fastcall DoFeedback(int PercentDone);
	
public:
	__fastcall virtual TKohonen(Classes::TComponent* AOwner);
	__fastcall virtual ~TKohonen(void);
	void __fastcall ApplyIt(Vector::TVector* InData, int &BestIx, int &BestIy, double &Distance);
	void __fastcall AbortTraining(void);
	void __fastcall ContinueTraining(void);
	bool __fastcall LoadFromXMLFile(AnsiString FName, AnsiString DataID);
	bool __fastcall ReadFromXMLStream(Classes::TStream* InStream, AnsiString DataID);
	bool __fastcall ReadFromOpenXMLFile(TextFile &InFile, AnsiString DataID);
	void __fastcall SaveAsXMLFile(AnsiString FName, AnsiString DataID);
	void __fastcall StandardizeData(void);
	__property Matrix::TMatrix* TrainData = {read=FDataMat, write=SetDataMat};
	void __fastcall Trainit(void);
	__property double Weights[int ix][int iy][int wi] = {read=GetWeight};
	void __fastcall WriteToXMLStream(Classes::TStream* OutStream, bool CreateHeader, AnsiString DataID);
	void __fastcall WriteToOpenXMLFile(TextFile &OutFile, bool CreateHeader, AnsiString DataID);
	
__published:
	__property AnsiString Comment = {read=FComment, write=FComment};
	__property bool Cyclic = {read=FCyclic, write=FCyclic, nodefault};
	__property double InitialAlpha = {read=FMaxAlpha, write=FMaxAlpha};
	__property int InitialNeighbors = {read=FMaxNeighb, write=FMaxNeighb, nodefault};
	__property int NrOfInSens = {read=FNrInSens, write=SetNumInsens, nodefault};
	__property int NrOfTrnSteps = {read=FMaxSteps, write=FMaxSteps, nodefault};
	__property int SizeX = {read=FSizeX, write=SetSizeX, nodefault};
	__property int SizeY = {read=FSizeY, write=SetSizeY, nodefault};
	__property Sdlbase::TOnPercentDoneEvent OnFeedback = {read=FOnFeedback, write=FOnFeedback};
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "kohonen_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Kohonen */
using namespace Kohonen;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// kohonen
