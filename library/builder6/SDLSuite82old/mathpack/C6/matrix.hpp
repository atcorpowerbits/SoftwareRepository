// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'matrix.pas' rev: 6.00

#ifndef matrixHPP
#define matrixHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <vector.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Matrix
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLMatrixError;
class PASCALIMPLEMENTATION ESDLMatrixError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLMatrixError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLMatrixError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLMatrixError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLMatrixError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLMatrixError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLMatrixError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLMatrixError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLMatrixError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLMatrixError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TMatXmlTag { xmlMatNumCols, xmlMatNumRows, xmlMatNumPlanes, xmlMatCell, xmlMatBegin, xmlMatEnd, xmlInvalid };
#pragma option pop

#pragma option push -b-
enum TDistMode { dmJaccard, dmManhattan, dmEuclid, dmEuclidSqr, dmDice, dmUserDef };
#pragma option pop

typedef void __fastcall (__closure *TOnCalcDistanceEvent)(System::TObject* Sender, int Row1, int Row2, double &Distance);

#pragma pack(push, 4)
struct TSpMatElemInt
{
	int colidx;
	int rowidx;
	int value;
} ;
#pragma pack(pop)

typedef AnsiString matrix__2[6];

typedef DynamicArray<double >  matrix__4;

typedef DynamicArray<DynamicArray<double > >  matrix__5;

class DELPHICLASS TMatrix;
class PASCALIMPLEMENTATION TMatrix : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FNCol;
	int FNRow;
	AnsiString FDataID;
	DynamicArray<DynamicArray<double > >  Mat;
	int FPrecis[2];
	Classes::TNotifyEvent FOnChange;
	Sdlbase::TSortExchgEvent FOnSortExchange;
	TOnCalcDistanceEvent FOnCalcDist;
	double __fastcall GetVal(int Nc, int Nr);
	void __fastcall SetVal(int Nc, int Nr, double Value);
	int __fastcall GetFPrecis(int ix);
	void __fastcall SetFPrecis(int ix, int value);
	void __fastcall SetNCols(int value);
	void __fastcall SetNRows(int value);
	void __fastcall SkewKurtIntern(int LowCol, int LowRow, int HighCol, int HighRow, double &Skewness, double &Kurtosis, int &NumData);
	
protected:
	void __fastcall SortExchange(Byte ExchgWhat, int index1, int index2, int first, int last);
	
public:
	__fastcall virtual TMatrix(Classes::TComponent* AOwner);
	__fastcall virtual ~TMatrix(void);
	__property double Elem[int ix][int iy] = {read=GetVal, write=SetVal/*, default*/};
	bool __fastcall Add(TMatrix* MatB);
	int __fastcall CalcDistMat(TDistMode Mode, TMatrix* DMat);
	void __fastcall Changed(void);
	void __fastcall CopyColToVec(Vector::TVector* DestVec, int Col, int FirstRow, int LastRow);
	void __fastcall CopyFrom(TMatrix* MatSource, int SourceColLo, int SourceRowLo, int SourceColHi, int SourceRowHi, int DestCol, int DestRow);
	void __fastcall Clone(TMatrix* MatSource);
	void __fastcall CopyFromVec(Vector::TVector* VecSource, int Source1stElem, int SourceLastElem, int DestCol, int DestRow);
	void __fastcall CopyRowToVec(Vector::TVector* DestVec, int Row, int FirstCol, int LastCol);
	double __fastcall Determinant(void);
	void __fastcall Fill(double value);
	HIDESBASE void __fastcall Free(void);
	double __fastcall GeometricMean(int LowCol, int LowRow, int HighCol, int HighRow);
	double __fastcall HarmonicMean(int LowCol, int LowRow, int HighCol, int HighRow);
	bool __fastcall Histogram(int LoX, int LoY, int HiX, int HiY, double FirstBin, double LastBin, double BinWidth, Vector::TIntVector* Histo, int &Underflow, int &Overflow, int &MaxCnt);
	bool __fastcall Invert(void);
	bool __fastcall LoadFromFile(AnsiString FileName, bool AdjustMatrixSize);
	bool __fastcall LoadFromStream(Classes::TMemoryStream* InStream, bool AdjustMatrixSize);
	bool __fastcall LoadFromXMLFile(AnsiString FName, AnsiString DataID);
	bool __fastcall LUdecomposition(TMatrix* &MatL, TMatrix* &MatU);
	void __fastcall MeanVar(int LowCol, int LowRow, int HighCol, int HighRow, double &Mean, double &Variance);
	void __fastcall MinMax(int LowCol, int LowRow, int HighCol, int HighRow, double &Minimum, double &Maximum);
	bool __fastcall Multiply(TMatrix* MatB, TMatrix* MatRes);
	double __fastcall Percentile(double prob, int LowCol, int LowRow, int HighCol, int HighRow);
	__property int Precision[int Index] = {read=GetFPrecis, write=SetFPrecis};
	bool __fastcall Quartiles(int LowCol, int LowRow, int HighCol, int HighRow, double &Q1, double &Q2, double &Q3);
	bool __fastcall ReadFromXMLStream(Classes::TStream* InStream, AnsiString DataID);
	bool __fastcall ReadFromOpenXMLFile(TextFile &InFile, AnsiString DataID);
	bool __fastcall Resize(int Nc, int Nr);
	void __fastcall SaveAsXMLFile(AnsiString FName, AnsiString DataID);
	void __fastcall SaveToStream(Classes::TMemoryStream* &OutStream, int LoC, int LoR, int HiC, int HiR);
	void __fastcall SkewKurt(int LowCol, int LowRow, int HighCol, int HighRow, double &Skewness, double &Kurtosis);
	void __fastcall SkewKurtSample(int LowCol, int LowRow, int HighCol, int HighRow, double &Skewness, double &Kurtosis);
	void __fastcall SMult(double Scalar);
	void __fastcall SortCols(int SortRowIx, bool Ascending, int LowCol, int LowRow, int HighCol, int HighRow);
	void __fastcall SortRows(int SortColIx, bool Ascending, int LowCol, int LowRow, int HighCol, int HighRow);
	void __fastcall StandardizeColumns(Vector::TVector* Means, Vector::TVector* StdDevs);
	void __fastcall StandardizeRows(Vector::TVector* Means, Vector::TVector* StdDevs);
	bool __fastcall StoreOnFile(int LoC, int LoR, int HiC, int HiR, AnsiString FileName);
	bool __fastcall Subtract(TMatrix* MatB);
	double __fastcall Sum(int LoC, int LoR, int HiC, int HiR);
	bool __fastcall Transpose(void);
	double __fastcall Trace(void);
	void __fastcall WriteToOpenXMLFile(TextFile &OutFile, bool CreateHeader, AnsiString DataID);
	void __fastcall WriteToXMLStream(Classes::TStream* OutStream, bool CreateHeader, AnsiString DataID);
	
__published:
	__property int NrOfColumns = {read=FNCol, write=SetNCols, nodefault};
	__property int NrOfRows = {read=FNRow, write=SetNRows, nodefault};
	__property AnsiString DataID = {read=FDataID, write=FDataID};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Sdlbase::TSortExchgEvent OnSortExchange = {read=FOnSortExchange, write=FOnSortExchange};
	__property TOnCalcDistanceEvent OnCalcDistance = {read=FOnCalcDist, write=FOnCalcDist};
};


typedef DynamicArray<TSpMatElemInt >  matrix__7;

typedef DynamicArray<int >  matrix__8;

typedef DynamicArray<DynamicArray<int > >  matrix__9;

class DELPHICLASS TIntMatrix;
class PASCALIMPLEMENTATION TIntMatrix : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FNCol;
	int FNRow;
	AnsiString FDataID;
	bool FIsSparse;
	int FNumAllocated;
	int FAllocBy;
	int FSparseNumElem;
	int FSparseLowCol;
	int FSparseHighCol;
	int FSparseLowRow;
	int FSparseHighRow;
	DynamicArray<TSpMatElemInt >  SpMat;
	DynamicArray<DynamicArray<int > >  Mat;
	Classes::TNotifyEvent FOnChange;
	Sdlbase::TSortExchgEvent FOnSortExchange;
	int __fastcall GetVal(int Nc, int Nr);
	void __fastcall SetVal(int Nc, int Nr, int Value);
	void __fastcall SetNCols(int value);
	void __fastcall SetNRows(int value);
	void __fastcall SkewKurtIntern(int LowCol, int LowRow, int HighCol, int HighRow, double &Skewness, double &Kurtosis, int &NumData);
	
protected:
	void __fastcall SortExchange(Byte ExchgWhat, int index1, int index2, int first, int last);
	
public:
	__fastcall virtual TIntMatrix(Classes::TComponent* AOwner);
	__fastcall TIntMatrix(Classes::TComponent* AOwner, int AllocBy);
	__fastcall virtual ~TIntMatrix(void);
	__property int Elem[int ix][int iy] = {read=GetVal, write=SetVal/*, default*/};
	bool __fastcall Add(TIntMatrix* MatB);
	void __fastcall ArrayToSparse(int AllocBy);
	void __fastcall Changed(void);
	void __fastcall Clone(TIntMatrix* MatSource);
	void __fastcall CopyColToVec(Vector::TIntVector* DestVec, int Col, int FirstRow, int LastRow);
	void __fastcall CopyFrom(TIntMatrix* MatSource, int SourceColLo, int SourceRowLo, int SourceColHi, int SourceRowHi, int DestCol, int DestRow);
	void __fastcall CopyRowToVec(Vector::TIntVector* DestVec, int Row, int FirstCol, int LastCol);
	void __fastcall Fill(int value);
	double __fastcall GeometricMean(int LowCol, int LowRow, int HighCol, int HighRow);
	double __fastcall HarmonicMean(int LowCol, int LowRow, int HighCol, int HighRow);
	bool __fastcall LoadFromFile(AnsiString FileName, bool AdjustMatrixSize);
	bool __fastcall LoadFromStream(Classes::TMemoryStream* InStream, bool AdjustMatrixSize);
	bool __fastcall LoadFromXMLFile(AnsiString FName, AnsiString DataID);
	bool __fastcall LoadSparseMat(AnsiString FileName);
	void __fastcall MeanVar(int LowCol, int LowRow, int HighCol, int HighRow, double &Mean, double &Variance);
	void __fastcall MinMax(int LowCol, int LowRow, int HighCol, int HighRow, int &Minimum, int &Maximum);
	bool __fastcall Multiply(TIntMatrix* MatB, TIntMatrix* MatRes);
	double __fastcall Percentile(double prob, int LowCol, int LowRow, int HighCol, int HighRow);
	bool __fastcall Quartiles(int LowCol, int LowRow, int HighCol, int HighRow, double &Q1, double &Q2, double &Q3);
	bool __fastcall ReadFromOpenXMLFile(TextFile &InFile, AnsiString DataID);
	bool __fastcall ReadFromXMLStream(Classes::TStream* InStream, AnsiString DataID);
	bool __fastcall Resize(int Nc, int Nr);
	void __fastcall SaveAsXMLFile(AnsiString FName, AnsiString DataID);
	void __fastcall SaveToStream(Classes::TMemoryStream* &OutStream, int LoC, int LoR, int HiC, int HiR);
	void __fastcall SkewKurt(int LowCol, int LowRow, int HighCol, int HighRow, double &Skewness, double &Kurtosis);
	void __fastcall SkewKurtSample(int LowCol, int LowRow, int HighCol, int HighRow, double &Skewness, double &Kurtosis);
	void __fastcall SMult(int Scalar);
	void __fastcall SortCols(int SortRowIx, bool Ascending, int LowCol, int LowRow, int HighCol, int HighRow);
	void __fastcall SortRows(int SortColIx, bool Ascending, int LowCol, int LowRow, int HighCol, int HighRow);
	void __fastcall SparseToArray(void);
	bool __fastcall StoreOnFile(int LoC, int LoR, int HiC, int HiR, AnsiString FileName);
	bool __fastcall StoreSparseMat(AnsiString FileName);
	bool __fastcall Subtract(TIntMatrix* MatB);
	int __fastcall Sum(int LoC, int LoR, int HiC, int HiR);
	int __fastcall Trace(void);
	bool __fastcall Transpose(void);
	void __fastcall WriteToOpenXMLFile(TextFile &OutFile, bool CreateHeader, AnsiString DataID);
	void __fastcall WriteToXMLStream(Classes::TStream* OutStream, bool CreateHeader, AnsiString DataID);
	
__published:
	__property AnsiString DataID = {read=FDataID, write=FDataID};
	__property int NrOfColumns = {read=FNCol, write=SetNCols, nodefault};
	__property int NrOfRows = {read=FNRow, write=SetNRows, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property Sdlbase::TSortExchgEvent OnSortExchange = {read=FOnSortExchange, write=FOnSortExchange};
};


typedef DynamicArray<double >  matrix__11;

typedef DynamicArray<DynamicArray<double > >  matrix__21;

typedef DynamicArray<DynamicArray<DynamicArray<double > > >  matrix__31;

class DELPHICLASS TMat3D;
class PASCALIMPLEMENTATION TMat3D : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	int FNumX;
	int FNumY;
	int FNumZ;
	AnsiString FDataID;
	DynamicArray<DynamicArray<DynamicArray<double > > >  Mat;
	Classes::TNotifyEvent FOnChange;
	double __fastcall GetVal(int Nx, int Ny, int Nz);
	void __fastcall SetVal(int Nx, int Ny, int Nz, double Value);
	void __fastcall SetNCols(int value);
	void __fastcall SetNRows(int value);
	void __fastcall SetNLayers(int value);
	
public:
	__fastcall virtual TMat3D(Classes::TComponent* AOwner);
	__fastcall virtual ~TMat3D(void);
	void __fastcall Changed(void);
	__property double Elem[int ix][int iy][int iz] = {read=GetVal, write=SetVal/*, default*/};
	void __fastcall Fill(double value);
	bool __fastcall LoadFromXMLFile(AnsiString FName, AnsiString DataID);
	bool __fastcall ReadFromOpenXMLFile(TextFile &InFile, AnsiString DataID);
	bool __fastcall ReadFromXMLStream(Classes::TStream* InStream, AnsiString DataID);
	bool __fastcall Resize(int Nc, int Nr, int Nl);
	void __fastcall SaveAsXMLFile(AnsiString FName, AnsiString DataID);
	void __fastcall WriteToOpenXMLFile(TextFile &OutFile, bool CreateHeader, AnsiString DataID);
	void __fastcall WriteToXMLStream(Classes::TStream* OutStream, bool CreateHeader, AnsiString DataID);
	
__published:
	__property AnsiString DataID = {read=FDataID, write=FDataID};
	__property int NrOfColumns = {read=FNumX, write=SetNCols, nodefault};
	__property int NrOfRows = {read=FNumY, write=SetNRows, nodefault};
	__property int NrOfLayers = {read=FNumZ, write=SetNLayers, nodefault};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "matrix_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE AnsiString DistModeId[6];
extern PACKAGE void __fastcall Register(void);

}	/* namespace Matrix */
using namespace Matrix;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// matrix
