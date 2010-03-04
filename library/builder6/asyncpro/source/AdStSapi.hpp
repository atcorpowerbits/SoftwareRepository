// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStSapi.pas' rev: 5.00

#ifndef AdStSapiHPP
#define AdStSapiHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Controls.hpp>	// Pascal unit
#include <AdStMach.hpp>	// Pascal unit
#include <AdSapiEn.hpp>	// Pascal unit
#include <AdStSt.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adstsapi
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TApdOnSetupSpeakString)(System::TObject* Sender, AnsiString &AString
	);

class DELPHICLASS TApdSAPISpeakState;
class PASCALIMPLEMENTATION TApdSAPISpeakState : public Adstst::TApdCustomActionState 
{
	typedef Adstst::TApdCustomActionState inherited;
	
private:
	AnsiString FStringToSpeak;
	Adsapien::TApdSapiEngine* FSapiEngine;
	TApdOnSetupSpeakString FOnSetupSpeakString;
	
protected:
	void __fastcall SetSapiEngine(const Adsapien::TApdSapiEngine* v);
	void __fastcall SetStringToSpeak(const AnsiString v);
	
public:
	__fastcall virtual TApdSAPISpeakState(Classes::TComponent* AOwner);
	virtual void __fastcall Activate(void);
	
__published:
	__property Adsapien::TApdSapiEngine* SapiEngine = {read=FSapiEngine, write=SetSapiEngine};
	__property AnsiString StringToSpeak = {read=FStringToSpeak, write=SetStringToSpeak};
	__property OnGetData ;
	__property OnGetDataString ;
	__property TApdOnSetupSpeakString OnSetupSpeakString = {read=FOnSetupSpeakString, write=FOnSetupSpeakString
		};
	__property ActiveColor ;
	__property Caption ;
	__property Conditions ;
	__property Font ;
	__property Glyph ;
	__property GlyphCells ;
	__property InactiveColor ;
	__property Movable ;
	__property OutputOnActivate ;
	__property OnStateActivate ;
	__property OnStateFinish ;
	__property OnSelectNextState ;
public:
	#pragma option push -w-inl
	/* TApdCustomActionState.Destroy */ inline __fastcall virtual ~TApdSAPISpeakState(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adstsapi */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adstsapi;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStSapi
