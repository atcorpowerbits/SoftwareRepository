// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'chemgrph.pas' rev: 6.00

#ifndef chemgrphHPP
#define chemgrphHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <cstruct.hpp>	// Pascal unit
#include <sdlbase.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Menus.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Chemgrph
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TDirection { diLeft, diTop, diRight, diBottom };
#pragma option pop

#pragma option push -b-
enum TCGDispMode { dmSkeleton, dmHeteroOnly, dmAllAtoms, dmNumbers };
#pragma option pop

typedef void __fastcall (__closure *TMoveOverStructEvent)(System::TObject* Sender, int ClosestAtom, double Dist, Classes::TShiftState Shift, double rMousePosX, double rMousePosY);

class DELPHICLASS TChemGraph;
class PASCALIMPLEMENTATION TChemGraph : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
private:
	Graphics::TColor FColorBakG;
	Graphics::TColor FMolColor;
	Graphics::TColor FColBlackLine;
	Graphics::TColor FColGrayLine;
	Graphics::TColor FColWhiteLine;
	Sdlbase::TColorScheme FColorScheme;
	double FTransForm[3];
	int FMaxBondLeng;
	TMoveOverStructEvent FOnMMvInChart;
	Sdlbase::TFrameStyle FFrameStyle;
	int FClipBounds[4];
	TCGDispMode FDispMode;
	bool FSuppressPaint;
	bool FDrawAsIs;
	int __fastcall ConstructElemSymb(int AtIx, AnsiString &ESymb);
	void __fastcall DrawMolRaw(TCGDispMode DispMode, double TrafoK, double TrafoDx, double TrafoDy, bool Clip, Graphics::TCanvas* CV);
	void __fastcall DrawConnections(int AtIx, bool HighOnly, TCGDispMode DisplayMode, double TrafoK, double TrafoDx, double TrafoDy, bool Clip, Graphics::TCanvas* CV);
	void __fastcall DispElemSymb(int AtIx, TCGDispMode DispMode, double TrafoK, double TrafoDx, double TrafoDy, bool Clip, Graphics::TCanvas* CV);
	int __fastcall GetClipBoundary(TDirection ix);
	Graphics::TColor __fastcall GetAtColor(int AtIx);
	Byte __fastcall GetVisAttrib(int AtIx);
	void __fastcall SetClipBoundary(TDirection ix, int ClipVal);
	void __fastcall SetColorBakG(Graphics::TColor Value);
	void __fastcall SetColorScheme(Sdlbase::TColorScheme Value);
	void __fastcall SetAtColor(int AtIx, Graphics::TColor value);
	void __fastcall SetDispMode(TCGDispMode value);
	void __fastcall SetFrameStyle(Sdlbase::TFrameStyle value);
	void __fastcall SetMaxbondleng(int value);
	void __fastcall SetMolColor(Graphics::TColor value);
	void __fastcall SetSuppressPaint(bool supp);
	void __fastcall SetDrawAsIs(bool x);
	void __fastcall SetVisAttrib(int AtIx, Byte value);
	void __fastcall StructureHasChanged(System::TObject* Sender);
	MESSAGE void __fastcall WMMoveOverStruct(Messages::TWMMouse &Message);
	
protected:
	virtual void __fastcall Paint(void);
	void __fastcall MoveOverStruct(int ClosestAtom, double Dist, Classes::TShiftState Shift, double RMousePosX, double RMousePosY);
	
public:
	Cstruct::TCTab* Structure;
	__fastcall virtual TChemGraph(Classes::TComponent* AOwner);
	__fastcall virtual ~TChemGraph(void);
	__property Graphics::TColor AtColor[int AtIx] = {read=GetAtColor, write=SetAtColor};
	__property Byte AtVisAttrib[int AtIx] = {read=GetVisAttrib, write=SetVisAttrib};
	__property int ClipBoundary[TDirection ix] = {read=GetClipBoundary, write=SetClipBoundary};
	__property bool DrawUnscaled = {read=FDrawAsIs, write=SetDrawAsIs, nodefault};
	int __fastcall FindChainNexttoCursor(float x, float y, Cstruct::AtListType &ChainAtoms);
	void __fastcall FindRingNextToCursor(float x, float y, Cstruct::RingType &Ring);
	void __fastcall OptimizeMolShape(int IdealDist);
	void __fastcall ShowMoleculeInABox(Graphics::TCanvas* Canvas, TCGDispMode DispMode, int llx, int lly, int urx, int ury, int MaxBondLeng);
	__property bool SuppressPaint = {read=FSuppressPaint, write=SetSuppressPaint, nodefault};
	
__published:
	__property Align  = {default=0};
	__property Graphics::TColor ColorBkg = {read=FColorBakG, write=SetColorBakG, nodefault};
	__property Sdlbase::TColorScheme ColorScheme = {read=FColorScheme, write=SetColorScheme, nodefault};
	__property Graphics::TColor ColorStructure = {read=FMolColor, write=SetMolColor, nodefault};
	__property TCGDispMode DisplayMode = {read=FDispMode, write=SetDispMode, nodefault};
	__property Font ;
	__property Sdlbase::TFrameStyle FrameStyle = {read=FFrameStyle, write=SetFrameStyle, nodefault};
	__property int MaxBondLeng = {read=FMaxBondLeng, write=SetMaxbondleng, nodefault};
	__property ParentFont  = {default=1};
	__property ParentShowHint  = {default=1};
	__property PopupMenu ;
	__property ShowHint ;
	__property Visible  = {default=1};
	__property OnClick ;
	__property OnDblClick ;
	__property OnMouseMove ;
	__property OnMouseDown ;
	__property OnMouseUp ;
	__property TMoveOverStructEvent OnMoveOverStruct = {read=FOnMMvInChart, write=FOnMMvInChart};
};


//-- var, const, procedure ---------------------------------------------------
static const Shortint vaNormal = 0x0;
static const Shortint vaBold = 0x1;
static const Shortint vaInvert = 0x2;
static const Shortint vaItalic = 0x4;
#define SDLVersionInfo "chemgrph_r820_lighted"
static const bool IsLightEd = true;
static const Word Release = 0x334;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Chemgrph */
using namespace Chemgrph;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// chemgrph
