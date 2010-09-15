// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStSt.pas' rev: 5.00

#ifndef AdStStHPP
#define AdStStHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Controls.hpp>	// Pascal unit
#include <AdStMach.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adstst
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TApdOnStartAction)(System::TObject* Sender, Adstmach::TApdStateConditions* 
	StateConditions, bool &ActionCompleted, int &NextState);

typedef void __fastcall (__closure *TApdOnSelectNextState)(System::TObject* Sender, int &NextState);
	

class DELPHICLASS TApdCustomActionState;
class PASCALIMPLEMENTATION TApdCustomActionState : public Adstmach::TApdCustomState 
{
	typedef Adstmach::TApdCustomState inherited;
	
private:
	AnsiString FTitle;
	Graphics::TFont* FTitleFont;
	TApdOnStartAction FOnStartAction;
	TApdOnSelectNextState FOnSelectNextState;
	
protected:
	virtual void __fastcall Activate(void);
	virtual void __fastcall Deactivate(void);
	virtual void __fastcall FinishAction(int NextState);
	Graphics::TColor __fastcall GetTitleColor(void);
	void __fastcall SetTitle(const AnsiString v);
	void __fastcall SetTitleColor(const Graphics::TColor v);
	void __fastcall SetTitleFont(const Graphics::TFont* v);
	virtual void __fastcall StartAction(void) = 0 ;
	
public:
	__fastcall virtual TApdCustomActionState(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomActionState(void);
	void __fastcall AutoSelectNextState(bool Error);
	virtual void __fastcall Paint(void);
	__property AnsiString Title = {read=FTitle, write=SetTitle};
	__property Graphics::TColor TitleColor = {read=GetTitleColor, write=SetTitleColor, nodefault};
	__property Graphics::TFont* TitleFont = {read=FTitleFont, write=SetTitleFont};
	__property TApdOnSelectNextState OnSelectNextState = {read=FOnSelectNextState, write=FOnSelectNextState
		};
	__property TApdOnStartAction OnStartAction = {read=FOnStartAction, write=FOnStartAction};
	
__published:
	__property Conditions ;
};


class DELPHICLASS TApdActionState;
class PASCALIMPLEMENTATION TApdActionState : public TApdCustomActionState 
{
	typedef TApdCustomActionState inherited;
	
public:
	virtual void __fastcall FinishAction(int NextState);
	
__published:
	__property Title ;
	__property TitleColor ;
	__property TitleFont ;
	__property OnGetData ;
	__property OnGetDataString ;
	__property OnStartAction ;
	__property ActiveColor ;
	__property Caption ;
	__property Font ;
	__property Glyph ;
	__property GlyphCells ;
	__property InactiveColor ;
	__property Movable ;
	__property OutputOnActivate ;
public:
	#pragma option push -w-inl
	/* TApdCustomActionState.Create */ inline __fastcall virtual TApdActionState(Classes::TComponent* AOwner
		) : TApdCustomActionState(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomActionState.Destroy */ inline __fastcall virtual ~TApdActionState(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adstst */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adstst;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStSt
