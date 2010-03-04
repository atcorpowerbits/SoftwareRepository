// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwZmodem.pas' rev: 6.00

#ifndef AwZmodemHPP
#define AwZmodemHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <AwAbsPcl.hpp>	// Pascal unit
#include <AwTPcl.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awzmodem
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const Shortint MaxAttentionLen = 0x20;
static const Word MaxHandshakeWait = 0x444;
static const Shortint MaxBadBlocks = 0x14;
static const Word DefReceiveTimeout = 0x16c;
static const Shortint DrainingStatusInterval = 0x12;
static const Word DefFinishWaitZM = 0x16c;
static const Shortint DefFinishRetry = 0x3;
static const Shortint ZmodemTurnDelay = 0x0;
static const Shortint ZmodemOverHead = 0x14;
extern PACKAGE unsigned ZMaxBlock[2];
extern PACKAGE unsigned ZMaxWork[2];
static const char ZPad = '\x2a';
static const char ZDle = '\x18';
static const char ZBin = '\x41';
static const char ZHex = '\x42';
static const char ZBin32 = '\x43';
static const char ZrQinit = '\x0';
static const char ZrInit = '\x1';
static const char ZsInit = '\x2';
static const char ZAck = '\x3';
static const char ZFile = '\x4';
static const char ZSkip = '\x5';
static const char ZNak = '\x6';
static const char ZAbort = '\x7';
static const char ZFin = '\x8';
static const char ZRpos = '\x9';
static const char ZData = '\xa';
static const char ZEof = '\xb';
static const char ZFerr = '\xc';
static const char ZCrc = '\xd';
static const char ZChallenge = '\xe';
static const char ZCompl = '\xf';
static const char ZCan = '\x10';
static const char ZFreeCnt = '\x11';
static const char ZCommand = '\x12';
extern PACKAGE int __fastcall zpInit(Awtpcl::PProtocolData &P, Adport::TApdCustomComPort* H, unsigned Options);
extern PACKAGE int __fastcall zpReinit(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall zpDone(Awtpcl::PProtocolData &P);
extern PACKAGE void __fastcall zpDonePart(Awtpcl::PProtocolData P);
extern PACKAGE int __fastcall zpSetFileMgmtOptions(Awtpcl::PProtocolData P, BOOL Override, BOOL SkipNoFile, Byte FOpt);
extern PACKAGE int __fastcall zpSetRecoverOption(Awtpcl::PProtocolData P, BOOL OnOff);
extern PACKAGE int __fastcall zpSetBigSubpacketOption(Awtpcl::PProtocolData P, BOOL UseBig);
extern PACKAGE int __fastcall zpSetZmodemFinishWait(Awtpcl::PProtocolData P, unsigned NewWait, Byte NewRetry);
extern PACKAGE void __fastcall zpPrepareReceive(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall zpReceive(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE void __fastcall zpPrepareTransmit(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall zpTransmit(unsigned Msg, unsigned wParam, int lParam);

}	/* namespace Awzmodem */
using namespace Awzmodem;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwZmodem
