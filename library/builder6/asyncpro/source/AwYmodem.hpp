// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwYmodem.pas' rev: 6.00

#ifndef AwYmodemHPP
#define AwYmodemHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <AwXmodem.hpp>	// Pascal unit
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

namespace Awymodem
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE int __fastcall ypInit(Awtpcl::PProtocolData &P, Adport::TApdCustomComPort* H, bool Use1K, bool UseGMode, unsigned Options);
extern PACKAGE int __fastcall ypReinit(Awtpcl::PProtocolData P, bool Use1K, bool UseGMode);
extern PACKAGE void __fastcall ypDone(Awtpcl::PProtocolData &P);
extern PACKAGE void __fastcall ypDonePart(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall ypPrepareTransmit(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall ypTransmit(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE void __fastcall ypPrepareReceive(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall ypReceive(unsigned Msg, unsigned wParam, int lParam);

}	/* namespace Awymodem */
using namespace Awymodem;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwYmodem
