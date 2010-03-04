// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwKermit.pas' rev: 6.00

#ifndef AwKermitHPP
#define AwKermitHPP

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

namespace Awkermit
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const Shortint DefMinRepeatCnt = 0x4;
static const bool FastAbort = false;
static const char DefHibitPrefix = '\x26';
static const Byte CancelWait = 0xb6;
static const char DiscardChar = '\x44';
static const Shortint MaxWindowSlots = 0x1b;
static const Shortint KermitOverhead = 0x14;
static const Word KermitTurnDelay = 0x3e8;
static const Shortint SWCKermitTurnDelay = 0x0;
static const char KBreak = '\x42';
static const char KData = '\x44';
static const char KError = '\x45';
static const char KFile = '\x46';
static const char KNak = '\x4e';
static const char KSendInit = '\x53';
static const char KDisplay = '\x58';
static const char KAck = '\x59';
static const char KEndOfFile = '\x5a';
extern PACKAGE Awtpcl::TKermitOptions DefKermitOptions;
extern PACKAGE Awtpcl::TKermitOptions MissingKermitOptions;
extern PACKAGE int __fastcall kpInit(Awtpcl::PProtocolData &P, Adport::TApdCustomComPort* H, unsigned Options);
extern PACKAGE int __fastcall kpReinit(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall kpDonePart(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall kpDone(Awtpcl::PProtocolData &P);
extern PACKAGE int __fastcall kpSetKermitOptions(Awtpcl::PProtocolData P, const Awtpcl::TKermitOptions &KOptions);
extern PACKAGE int __fastcall kpSetMaxPacketLen(Awtpcl::PProtocolData P, Byte MaxLen);
extern PACKAGE int __fastcall kpSetMaxLongPacketLen(Awtpcl::PProtocolData P, unsigned MaxLen);
extern PACKAGE int __fastcall kpSetMaxWindows(Awtpcl::PProtocolData P, Byte MaxNum);
extern PACKAGE int __fastcall kpSetSWCTurnDelay(Awtpcl::PProtocolData P, unsigned TrnDelay);
extern PACKAGE Byte __fastcall kpGetSWCSize(Awtpcl::PProtocolData P);
extern PACKAGE int __fastcall kpGetLPStatus(Awtpcl::PProtocolData P, BOOL &InUse, unsigned &PacketSize);
extern PACKAGE int __fastcall kpSetMaxTimeoutSecs(Awtpcl::PProtocolData P, Byte MaxTimeout);
extern PACKAGE int __fastcall kpSetPacketPadding(Awtpcl::PProtocolData P, char C, Byte Count);
extern PACKAGE int __fastcall kpSetTerminator(Awtpcl::PProtocolData P, char C);
extern PACKAGE int __fastcall kpSetCtlPrefix(Awtpcl::PProtocolData P, char C);
extern PACKAGE int __fastcall kpSetHibitPrefix(Awtpcl::PProtocolData P, char C);
extern PACKAGE int __fastcall kpSetRepeatPrefix(Awtpcl::PProtocolData P, char C);
extern PACKAGE int __fastcall kpSetKermitCheck(Awtpcl::PProtocolData P, Byte CType);
extern PACKAGE Byte __fastcall kpWindowsUsed(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall kpPrepareReceive(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall kpReceive(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE void __fastcall kpPrepareTransmit(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall kpTransmit(unsigned Msg, unsigned wParam, int lParam);

}	/* namespace Awkermit */
using namespace Awkermit;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwKermit
