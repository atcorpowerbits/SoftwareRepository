// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwXmodem.pas' rev: 6.00

#ifndef AwXmodemHPP
#define AwXmodemHPP

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

namespace Awxmodem
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const Word DrainWait = 0x444;
static const Shortint XmodemOverhead = 0x5;
static const Word XmodemTurnDelay = 0x3e8;
static const char GReq = '\x47';
static const char CrcReq = '\x43';
static const char ChkReq = '\x15';
extern PACKAGE int __fastcall xpInit(Awtpcl::PProtocolData &P, Adport::TApdCustomComPort* H, bool UseCRC, bool Use1K, bool UseGMode, unsigned Options);
extern PACKAGE void __fastcall xpReinit(Awtpcl::PProtocolData P, bool UseCRC, bool Use1K, bool UseGMode);
extern PACKAGE void __fastcall xpDone(Awtpcl::PProtocolData &P);
extern PACKAGE int __fastcall xpSetCRCMode(Awtpcl::PProtocolData P, bool Enable);
extern PACKAGE int __fastcall xpSet1KMode(Awtpcl::PProtocolData P, bool Enable);
extern PACKAGE int __fastcall xpSetGMode(Awtpcl::PProtocolData P, bool Enable);
extern PACKAGE int __fastcall xpSetBlockWait(Awtpcl::PProtocolData P, unsigned NewBlockWait);
extern PACKAGE int __fastcall xpSetXmodemFinishWait(Awtpcl::PProtocolData P, unsigned NewFinishWait);
extern PACKAGE bool __fastcall xpPrepHandshake(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall xpCancel(Awtpcl::PProtocolData P);
extern PACKAGE char __fastcall xpGetHandshakeChar(Awtpcl::PProtocolData P);
extern PACKAGE bool __fastcall xpProcessHandshake(Awtpcl::PProtocolData P);
extern PACKAGE bool __fastcall xpProcessBlockReply(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall xpTransmitBlock(Awtpcl::PProtocolData P, char * Block, unsigned BLen, char BType);
extern PACKAGE void __fastcall xpSendHandshakeChar(Awtpcl::PProtocolData P, char Handshake);
extern PACKAGE bool __fastcall xpCheckForBlockStart(Awtpcl::PProtocolData P, char &C);
extern PACKAGE Awtpcl::TProcessBlockStart __fastcall xpProcessBlockStart(Awtpcl::PProtocolData P, char C);
extern PACKAGE bool __fastcall xpCollectBlock(Awtpcl::PProtocolData P, char * Block);
extern PACKAGE void __fastcall xpReceiveBlock(Awtpcl::PProtocolData P, char * Block, unsigned &BlockSize, char &HandShake);
extern PACKAGE void __fastcall xpPrepareTransmit(Awtpcl::PProtocolData P);
extern PACKAGE int __fastcall xpTransmitPrim(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE void __fastcall xpTransmit(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE void __fastcall xpPrepareReceive(Awtpcl::PProtocolData P);
extern PACKAGE int __fastcall xpReceivePrim(unsigned Msg, unsigned wParam, int lParam);
extern PACKAGE void __fastcall xpReceive(unsigned Msg, unsigned wParam, int lParam);

}	/* namespace Awxmodem */
using namespace Awxmodem;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwXmodem
