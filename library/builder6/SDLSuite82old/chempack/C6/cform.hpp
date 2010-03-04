// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'cform.pas' rev: 6.00

#ifndef cformHPP
#define cformHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <math1.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cform
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TIsotVisib { ivNone, ivSpecial, ivAlways };
#pragma option pop

#pragma pack(push, 4)
struct TFormulaRec
{
	int FLeng;
	Byte AtNum[20];
	Byte AtWgt[20];
	Byte AtCnt[20];
} ;
#pragma pack(pop)

class DELPHICLASS TMolForm;
class PASCALIMPLEMENTATION TMolForm : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	Classes::TAlignment FAlignment;
	Graphics::TColor FColorBkg;
	Graphics::TColor FColorTxt;
	int FBFLeng;
	int FPermutCnt[20];
	double FMassBForm;
	double FTolBForm;
	bool FUseDeuterium;
	bool FShowAsText;
	bool FTransparent;
	AnsiString FFormulStr;
	Byte FAtNum[20];
	Byte FAtWgt[20];
	Byte FAtCnt[20];
	TIsotVisib FIsotVis;
	TFormulaRec FLowBForm;
	TFormulaRec FHighBForm;
	AnsiString __fastcall ChemElem(int AtNr, int AtWt, int AtNum, Byte Format);
	bool __fastcall FindFormulaIntern(bool IntMass, bool CheckPlausibility);
	AnsiString __fastcall GetMolFormula();
	int __fastcall GetAtNum(int idx);
	void __fastcall SetAtNum(int idx, int value);
	int __fastcall GetAtWgt(int idx);
	void __fastcall SetAtWgt(int idx, int value);
	int __fastcall GetAtCnt(int idx);
	void __fastcall SetAtCnt(int idx, int value);
	void __fastcall SetAlignment(Classes::TAlignment value);
	void __fastcall SetColorBkg(Graphics::TColor Value);
	void __fastcall SetColorTxt(Graphics::TColor Value);
	void __fastcall SetNumAtoms(int Value);
	int __fastcall GetNumAtoms(void);
	void __fastcall SetIsotVis(TIsotVisib x);
	void __fastcall SetMolFormula(AnsiString x);
	void __fastcall SetShowAsText(bool x);
	void __fastcall SetTransparent(bool x);
	void __fastcall SetUseDeuter(bool x);
	
protected:
	virtual void __fastcall Paint(void);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	
public:
	__fastcall virtual TMolForm(Classes::TComponent* AOwner);
	__fastcall virtual ~TMolForm(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	AnsiString __fastcall AsString(int fmt);
	double __fastcall ChemMolWgt(void);
	void __fastcall Clear(void);
	double __fastcall ExactMolWgt(void);
	int __fastcall NominalMolWgt(void);
	bool __fastcall ScanNextFormPart(AnsiString Instring, int &index, int &AtNr, int &AtWt, int &AtNum);
	__property int AtNum[int ix] = {read=GetAtNum, write=SetAtNum};
	__property int AtWgt[int ix] = {read=GetAtWgt, write=SetAtWgt};
	__property int AtCnt[int ix] = {read=GetAtCnt, write=SetAtCnt};
	__property int NumAtoms = {read=GetNumAtoms, write=SetNumAtoms, nodefault};
	void __fastcall ShowIt(void);
	void __fastcall ReadFromString(AnsiString Instring);
	int __fastcall CompareTo(TMolForm* OtherFormula);
	bool __fastcall FindFormulaNominalMass(bool CheckPlausibility);
	bool __fastcall FindFormulaExactMass(bool CheckPlausibility);
	bool __fastcall InitFindFormula(double mass, double tol, const TFormulaRec &LowF, const TFormulaRec &HighF);
	void __fastcall ScanMolFormula(AnsiString mform);
	
__published:
	__property Graphics::TColor ColorBkg = {read=FColorBkg, write=SetColorBkg, nodefault};
	__property Graphics::TColor ColorTxt = {read=FColorTxt, write=SetColorTxt, nodefault};
	__property Font ;
	__property TIsotVisib IsotopeVis = {read=FIsotVis, write=SetIsotVis, nodefault};
	__property AnsiString MolFormula = {read=GetMolFormula, write=SetMolFormula};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property bool ShowAsText = {read=FShowAsText, write=SetShowAsText, nodefault};
	__property ShowHint ;
	__property bool Transparent = {read=FTransparent, write=SetTransparent, nodefault};
	__property bool UseDeuterium = {read=FUseDeuterium, write=SetUseDeuter, nodefault};
	__property Visible  = {default=1};
	__property Classes::TAlignment Alignment = {read=FAlignment, write=SetAlignment, nodefault};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint FormMaxEl = 0x14;
#define SDLVersionInfo "cform_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Cform */
using namespace Cform;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// cform
