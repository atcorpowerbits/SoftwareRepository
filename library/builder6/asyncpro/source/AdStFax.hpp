// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStFax.pas' rev: 5.00

#ifndef AdStFaxHPP
#define AdStFaxHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Controls.hpp>	// Pascal unit
#include <AdStMach.hpp>	// Pascal unit
#include <AdFax.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AdStSt.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adstfax
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdSendFaxState;
typedef void __fastcall (__closure *TApdOnSetupSendFax)(TApdSendFaxState* Sender, Adfax::TApdSendFax* 
	AFax);

class DELPHICLASS TApdReceiveFaxState;
typedef void __fastcall (__closure *TApdOnSetupReceiveFax)(TApdReceiveFaxState* Sender, Adfax::TApdReceiveFax* 
	AFax);

typedef void __fastcall (__closure *TApdOnFaxXfrComplete)(Adstst::TApdCustomActionState* Sender, int 
	ErrorCode, int &NextState);

class PASCALIMPLEMENTATION TApdSendFaxState : public Adstst::TApdCustomActionState 
{
	typedef Adstst::TApdCustomActionState inherited;
	
private:
	bool FManualTransmit;
	AnsiString FOutputOnError;
	AnsiString FOutputOnOK;
	Adfax::TApdSendFax* FSendFax;
	TApdOnSetupSendFax FOnSetupFax;
	TApdOnFaxXfrComplete FOnFaxXfrComplete;
	
protected:
	virtual void __fastcall Activate(void);
	void __fastcall SetManualTransmit(const bool v);
	void __fastcall SetOutputOnError(const AnsiString v);
	void __fastcall SetOutputOnOK(const AnsiString v);
	void __fastcall SetSendFax(Adfax::TApdSendFax* v);
	
public:
	__fastcall virtual TApdSendFaxState(Classes::TComponent* AOwner);
	
__published:
	__property bool ManualTransmit = {read=FManualTransmit, write=SetManualTransmit, default=0};
	__property AnsiString OutputOnError = {read=FOutputOnError, write=SetOutputOnError};
	__property AnsiString OutputOnOK = {read=FOutputOnOK, write=SetOutputOnOK};
	__property Adfax::TApdSendFax* SendFax = {read=FSendFax, write=SetSendFax};
	__property TApdOnFaxXfrComplete OnFaxXfrComplete = {read=FOnFaxXfrComplete, write=FOnFaxXfrComplete
		};
	__property TApdOnSetupSendFax OnSetupFax = {read=FOnSetupFax, write=FOnSetupFax};
	__property ActiveColor ;
	__property Caption ;
	__property Font ;
	__property Glyph ;
	__property GlyphCells ;
	__property InactiveColor ;
	__property Movable ;
	__property OutputOnActivate ;
	__property OnGetData ;
	__property OnGetDataString ;
	__property OnStateActivate ;
	__property OnStateFinish ;
public:
	#pragma option push -w-inl
	/* TApdCustomActionState.Destroy */ inline __fastcall virtual ~TApdSendFaxState(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdReceiveFaxState : public Adstst::TApdCustomActionState 
{
	typedef Adstst::TApdCustomActionState inherited;
	
private:
	bool FManualReceive;
	AnsiString FOutputOnError;
	AnsiString FOutputOnOK;
	bool FSendATAToModem;
	Adfax::TApdReceiveFax* FReceiveFax;
	TApdOnFaxXfrComplete FOnFaxXfrComplete;
	TApdOnSetupReceiveFax FOnSetupFax;
	
protected:
	virtual void __fastcall Activate(void);
	void __fastcall SetManualReceive(const bool v);
	void __fastcall SetOutputOnError(const AnsiString v);
	void __fastcall SetOutputOnOK(const AnsiString v);
	void __fastcall SetReceiveFax(Adfax::TApdReceiveFax* v);
	void __fastcall SetSendATAToModem(const bool v);
	
public:
	__fastcall virtual TApdReceiveFaxState(Classes::TComponent* AOwner);
	
__published:
	__property bool ManualReceive = {read=FManualReceive, write=SetManualReceive, default=0};
	__property AnsiString OutputOnError = {read=FOutputOnError, write=SetOutputOnError};
	__property AnsiString OutputOnOK = {read=FOutputOnOK, write=SetOutputOnOK};
	__property Adfax::TApdReceiveFax* ReceiveFax = {read=FReceiveFax, write=SetReceiveFax};
	__property bool SendATAToModem = {read=FSendATAToModem, write=SetSendATAToModem, default=0};
	__property TApdOnFaxXfrComplete OnFaxXfrComplete = {read=FOnFaxXfrComplete, write=FOnFaxXfrComplete
		};
	__property TApdOnSetupReceiveFax OnSetupFax = {read=FOnSetupFax, write=FOnSetupFax};
	__property ActiveColor ;
	__property Caption ;
	__property Font ;
	__property Glyph ;
	__property GlyphCells ;
	__property InactiveColor ;
	__property Movable ;
	__property OutputOnActivate ;
	__property OnGetData ;
	__property OnGetDataString ;
	__property OnStateActivate ;
	__property OnStateFinish ;
public:
	#pragma option push -w-inl
	/* TApdCustomActionState.Destroy */ inline __fastcall virtual ~TApdReceiveFaxState(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adstfax */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adstfax;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStFax
