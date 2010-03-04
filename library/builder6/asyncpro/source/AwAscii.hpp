// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwAscii.pas' rev: 6.00

#ifndef AwAsciiHPP
#define AwAsciiHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <AwAbsPcl.hpp>	// Pascal unit
#include <AwTPcl.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awascii
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall spInit(Awtpcl::PProtocolData &P, Adport::TApdCustomComPort* H, unsigned Options);
extern PACKAGE int __fastcall spReinit(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall spDonePart(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall spDone(Awtpcl::PProtocolData &P);
extern PACKAGE int __fastcall spSetDelays(Awtpcl::PProtocolData P, unsigned CharDelay, unsigned LineDelay);
extern PACKAGE int __fastcall spSetEOLChar(Awtpcl::PProtocolData P, char C);
extern PACKAGE int __fastcall spGetLineNumber(Awtpcl::PProtocolData P);
extern PACKAGE int __fastcall spSetEOLTranslation(Awtpcl::PProtocolData P, unsigned CR, unsigned LF);
extern PACKAGE int __fastcall spSetEOFTimeout(Awtpcl::PProtocolData P, int NewTimeout);
extern PACKAGE void __fastcall spPrepareTransmit(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall spTransmit(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE void __fastcall spPrepareReceive(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall spReceive(unsigned Msg, unsigned wParam, int lParam);

}	/* namespace Awascii */
using namespace Awascii;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwAscii
