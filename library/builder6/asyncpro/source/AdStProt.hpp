// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStProt.pas' rev: 5.00

#ifndef AdStProtHPP
#define AdStProtHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Controls.hpp>	// Pascal unit
#include <AdProtcl.hpp>	// Pascal unit
#include <AdStSt.hpp>	// Pascal unit
#include <AdStMach.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adstprot
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TApdOnSetupProtocol)(System::TObject* Sender, Adprotcl::TApdProtocol* 
	AProtocol);

typedef void __fastcall (__closure *TApdOnFileXfrComplete)(System::TObject* Sender, int ErrorCode, int 
	&NextState);

class DELPHICLASS TApdSendFileState;
class PASCALIMPLEMENTATION TApdSendFileState : public Adstst::TApdCustomActionState 
{
	typedef Adstst::TApdCustomActionState inherited;
	
private:
	AnsiString FOutputOnError;
	AnsiString FOutputOnOK;
	Adprotcl::TApdProtocol* FProtocol;
	TApdOnSetupProtocol FOnSetupProtocol;
	TApdOnFileXfrComplete FOnFileXfrComplete;
	
protected:
	virtual void __fastcall Activate(void);
	void __fastcall SetOutputOnError(const AnsiString v);
	void __fastcall SetOutputOnOK(const AnsiString v);
	void __fastcall SetProtocol(Adprotcl::TApdProtocol* v);
	
public:
	__fastcall virtual TApdSendFileState(Classes::TComponent* AOwner);
	
__published:
	__property AnsiString OutputOnError = {read=FOutputOnError, write=SetOutputOnError};
	__property AnsiString OutputOnOK = {read=FOutputOnOK, write=SetOutputOnOK};
	__property Adprotcl::TApdProtocol* Protocol = {read=FProtocol, write=SetProtocol};
	__property TApdOnFileXfrComplete OnFileXfrComplete = {read=FOnFileXfrComplete, write=FOnFileXfrComplete
		};
	__property TApdOnSetupProtocol OnSetupProtocol = {read=FOnSetupProtocol, write=FOnSetupProtocol};
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
	/* TApdCustomActionState.Destroy */ inline __fastcall virtual ~TApdSendFileState(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdReceiveFileState;
class PASCALIMPLEMENTATION TApdReceiveFileState : public Adstst::TApdCustomActionState 
{
	typedef Adstst::TApdCustomActionState inherited;
	
private:
	AnsiString FOutputOnError;
	AnsiString FOutputOnOK;
	Adprotcl::TApdProtocol* FProtocol;
	TApdOnSetupProtocol FOnSetupProtocol;
	TApdOnFileXfrComplete FOnFileXfrComplete;
	
protected:
	virtual void __fastcall Activate(void);
	void __fastcall SetOutputOnError(const AnsiString v);
	void __fastcall SetOutputOnOK(const AnsiString v);
	void __fastcall SetProtocol(Adprotcl::TApdProtocol* v);
	
public:
	__fastcall virtual TApdReceiveFileState(Classes::TComponent* AOwner);
	
__published:
	__property AnsiString OutputOnError = {read=FOutputOnError, write=SetOutputOnError};
	__property AnsiString OutputOnOK = {read=FOutputOnOK, write=SetOutputOnOK};
	__property Adprotcl::TApdProtocol* Protocol = {read=FProtocol, write=SetProtocol};
	__property TApdOnFileXfrComplete OnFileXfrComplete = {read=FOnFileXfrComplete, write=FOnFileXfrComplete
		};
	__property TApdOnSetupProtocol OnSetupProtocol = {read=FOnSetupProtocol, write=FOnSetupProtocol};
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
	/* TApdCustomActionState.Destroy */ inline __fastcall virtual ~TApdReceiveFileState(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adstprot */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adstprot;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStProt
