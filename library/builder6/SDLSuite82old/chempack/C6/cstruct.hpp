// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'cstruct.pas' rev: 6.00

#ifndef cstructHPP
#define cstructHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <matrix.hpp>	// Pascal unit
#include <cform.hpp>	// Pascal unit
#include <cdata.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cstruct
{
//-- type declarations -------------------------------------------------------
struct TPropRec
{
	System::SmallString<15>  ID;
	double Par;
} ;

typedef TPropRec TProps[20];

#pragma option push -b-
enum SSSMode { smSkeleton, smAtoms, smBonds, smAtomAndBonds };
#pragma option pop

#pragma option push -b-
enum FrgType { NSglBnd, NCCSgl, NDblBnd, NCCDbl, NTrplBnd, NCCTrpl, NAroBnd, NBranch, XCnt, COOH, COO, NO2, AnyCO, AroCl, AroBr, AnyOH, PhOH, NH2, NHR, NR2, NCON, CN, CONR2, CHO, COX, AnySO, OCH3, NO, NNH2 };
#pragma option pop

#pragma pack(push, 4)
struct AtListType
{
	int NrAtoms;
	int AtList[63];
} ;
#pragma pack(pop)

typedef Byte AtFlagType[63];

typedef Byte BondListType[10];

#pragma pack(push, 1)
struct RingType
{
	Byte RingSize;
	Byte AtList[64];
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct RingListType
{
	int NrOfRings;
	RingType RList[100];
} ;
#pragma pack(pop)

#pragma option push -b-
enum CoordUnitType { cuUnknown, cuPixel, cuNanoM, cuPicoM, cuAngstrom };
#pragma option pop

#pragma pack(push, 4)
struct CTElem
{
	Byte AtNum;
	Byte AtWeight;
	Byte AtFlag;
	Byte Attrib;
	Shortint Charge;
	Byte ConnTo[10];
	Byte TypConn[10];
	float Coords[3];
	int AtDispAtb;
} ;
#pragma pack(pop)

class DELPHICLASS TCTab;
class PASCALIMPLEMENTATION TCTab : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Classes::TNotifyEvent FOnChange;
	int __fastcall GetNBonds(int AtIx);
	Byte __fastcall GetAtNum(int AtIx);
	void __fastcall SetAtNum(int AtIx, Byte AtNum);
	Byte __fastcall GetAtWeight(int AtIx);
	void __fastcall SetAtWeight(int AtIx, Byte AtWeight);
	Shortint __fastcall GetCharge(int AtIx);
	void __fastcall SetCharge(int AtIx, Shortint Charge);
	CTElem __fastcall GetAtomEntries(int AtIx);
	void __fastcall SetAtomEntries(int AtIx, const CTElem &AE);
	Byte __fastcall GetAtFlag(int AtIx);
	void __fastcall SetAtFlag(int AtIx, Byte AtFlag);
	Byte __fastcall GetAttrib(int AtIx);
	void __fastcall SetAttrib(int AtIx, Byte Attrib);
	float __fastcall GetCoords(int AtIx, int DimIx);
	void __fastcall SetCoords(int AtIx, int DimIx, float Coord);
	bool __fastcall GetCoordsPresent(void);
	void __fastcall SetCoordsPresent(bool value);
	Byte __fastcall GetConnTo(int AtIx, int ConnIx);
	void __fastcall SetConnTo(int AtIx, int ConnIx, Byte ConnTo);
	Byte __fastcall GetTypConn(int AtIx, int ConnIx);
	void __fastcall SetTypConn(int AtIx, int ConnIx, Byte Typ);
	AnsiString __fastcall GetCASNr();
	void __fastcall SetCASNr(AnsiString InString);
	bool __fastcall CheckCASNr(int CASNum);
	
protected:
	int FNumValidAtoms;
	AnsiString FStrucName;
	int FCASNr;
	CoordUnitType FCoordUnit;
	CTElem FAtomEntries[63];
	
public:
	__fastcall virtual TCTab(Classes::TComponent* AOwner);
	__fastcall virtual ~TCTab(void);
	bool __fastcall AddAtom(const CTElem &AtomRec);
	int __fastcall AtomCount(Byte AtNum);
	int __fastcall CalcAttributes(void);
	int __fastcall CalcMissingH(void);
	double __fastcall CalcMolExtents(double &MinX, double &MinY, double &MaxX, double &MAxY, double &CentX, double &CentY);
	void __fastcall CalcMolCenter(double &spx, double &spy, double &spz);
	bool __fastcall CalcMolecularFormula(Cform::TFormulaRec &BForm);
	double __fastcall CalcChemMolWeight(void);
	void __fastcall Changed(void);
	Byte __fastcall CheckConnect(int At1, int At2);
	void __fastcall ClearAttributes(void);
	void __fastcall Clear(void);
	Word __fastcall CompareWith(TCTab* CTabSource);
	void __fastcall CopyFrom(TCTab* CTabSource);
	void __fastcall DeleteAtom(int AtomNr);
	int __fastcall FindAtomInBox(double x, double y, double z, double XRange, double YRange, double ZRange);
	void __fastcall FindClosestAtom(double x, double y, double z, int &ClosestAtom, double &Dist);
	bool __fastcall ContainsUnconnectedAtom(void);
	void __fastcall EnterConn(int AtIx, int Connto, int TypConn);
	int __fastcall FindNextEndAtom(int AtIx);
	int __fastcall FindShortestRings(Word AtomIx, RingListType &RingList);
	int __fastcall FindSSSR(RingListType &RingList);
	int __fastcall FragmentCount(FrgType FrgCode);
	int __fastcall FragmentCode(int AtIx, int &NOuterBonds);
	void __fastcall JoinFragment(TCTab* CTabSource);
	void __fastcall LinkFragment(TCTab* CtabSource);
	bool __fastcall MakeConnection(int At1, int At2, Byte CType);
	void __fastcall MakeSymmetricConnections(void);
	int __fastcall MaxNBonds(int &AtIx);
	void __fastcall MatchAtomTemplate(Shortint An, Shortint Nb, const Byte * TypB, AtListType &AtomsMatched);
	int __fastcall NrHAtoms(int AtIx);
	bool __fastcall ReadFromClearTextFile(TextFile &AFile);
	bool __fastcall ReadFromClearTextFileCTABG(TextFile &AFile);
	bool __fastcall ReadFromMDLCTabFile(TextFile &AFile);
	bool __fastcall ReadFromMDLCTabStream(Classes::TStream* InStream);
	bool __fastcall ReadFromMDLMolStream(Classes::TStream* InStream);
	bool __fastcall ReadFromMDLMolFile(TextFile &AFile);
	bool __fastcall ReadFromMDLSDFile(TextFile &AFile, TPropRec * Props);
	bool __fastcall ReadConnTabBody(TextFile &AFile);
	void __fastcall RemoveHydrogen(void);
	int __fastcall RingsInMolecule(void);
	void __fastcall RotateWithPCA(void);
	bool __fastcall SearchSubStruc(TCTab* CTabSmall, Byte * MatchedAtoms, bool CompareBonds);
	int __fastcall StripfromChains(void);
	bool __fastcall SumForContained(TCTab* CTabSmall);
	void __fastcall WriteToClearTextFile(TextFile &AFile);
	void __fastcall WriteToMDLCTabFile(TextFile &TFile);
	void __fastcall WriteToMDLCTabStream(Classes::TStream* OutStream);
	void __fastcall WriteToMDLMolFile(TextFile &TFile,  System::ShortString &User, AnsiString ProgName, int Regnum, AnsiString comment);
	void __fastcall WriteToMDLMolStream(Classes::TStream* OutStream,  System::ShortString &User, AnsiString ProgName, int Regnum, AnsiString comment);
	void __fastcall WriteToMolConnXFile(int IdNum, TextFile &AFile);
	__property Byte AtAttrib[int AtIx] = {read=GetAttrib, write=SetAttrib};
	__property Shortint AtCharge[int AtIx] = {read=GetCharge, write=SetCharge};
	__property float AtCoords[int AtIx][int DimIx] = {read=GetCoords, write=SetCoords};
	__property Byte AtConnTo[int AtIx][int ConnIx] = {read=GetConnTo, write=SetConnTo};
	__property Byte AtTypConn[int AtIx][int ConnIx] = {read=GetTypConn, write=SetTypConn};
	__property Byte AtFlag[int AtIx] = {read=GetAtFlag, write=SetAtFlag};
	__property Byte AtNum[int AtIx] = {read=GetAtNum, write=SetAtNum};
	__property Byte AtWeight[int AtIx] = {read=GetAtWeight, write=SetAtWeight};
	__property CTElem AtomEntries[int AtIx] = {read=GetAtomEntries, write=SetAtomEntries};
	__property int BinCASNr = {read=FCASNr, write=FCASNr, nodefault};
	__property bool CoordinatesPresent = {read=GetCoordsPresent, write=SetCoordsPresent, nodefault};
	__property int NAtoms = {read=FNumValidAtoms, write=FNumValidAtoms, nodefault};
	__property int NBonds[int AtIx] = {read=GetNBonds};
	__property CoordUnitType CoordUnits = {read=FCoordUnit, write=FCoordUnit, nodefault};
	
__published:
	__property AnsiString CASNr = {read=GetCASNr, write=SetCASNr};
	__property AnsiString StrucName = {read=FStrucName, write=FStrucName};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "cstruct_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
static const Shortint MaxLengCTab = 0x3f;
static const Shortint MaxConn = 0xa;
static const Shortint MaxConnOld = 0x8;
static const Shortint MaxRings = 0x64;
static const Shortint MaxRingSize = 0x40;
static const Shortint MaxDim = 0x3;
static const Shortint AttribLin = 0x1;
static const Shortint Attrib347R = 0x2;
static const Shortint Attrib5R = 0x4;
static const Shortint Attrib6R = 0x8;
static const Shortint AttribBranch = 0x10;
static const Shortint AttribAnyR = 0x20;
static const Shortint AttribTerm = 0x40;
static const Byte AttribCondR = 0x80;
static const Shortint AttribNone = 0x0;
static const Shortint btNoBond = 0x0;
static const Shortint btSingle = 0x1;
static const Shortint btDouble = 0x2;
static const Shortint btTriple = 0x3;
static const Shortint btAromatic = 0x4;
static const Shortint MaxProps = 0x14;
extern PACKAGE AnsiString __fastcall FragmentStr(int InCode);
extern PACKAGE void __fastcall ClearCTElem(CTElem &AtomRec);
extern PACKAGE bool __fastcall RingInRingList(const RingType &Ring, const RingListType &RingList);
extern PACKAGE void __fastcall Register(void);

}	/* namespace Cstruct */
using namespace Cstruct;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// cstruct
