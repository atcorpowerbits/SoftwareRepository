// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwAbsPcl.pas' rev: 6.00

#ifndef AwAbsPclHPP
#define AwAbsPclHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdPort.hpp>	// Pascal unit
#include <AwUser.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <AwTPcl.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awabspcl
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
static const Shortint awpDefAbsStatusInterval = 0xa;
extern PACKAGE Byte DQFull[8];
extern PACKAGE Byte DQDefault[8];
extern PACKAGE int UnixDaysBase;
static const int SecsPerDay = 0x15180;
static const Shortint ProtocolDataPtr = 0x1;
extern PACKAGE unsigned Crc32Table[256];
extern PACKAGE unsigned Crc32TableOfs;
extern PACKAGE unsigned CrcTable[256];
extern PACKAGE int __fastcall apInitProtocolData(Awtpcl::PProtocolData &P, Adport::TApdCustomComPort* H, unsigned Options);
extern PACKAGE void __fastcall apDoneProtocol(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall apResetReadWriteHooks(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall apSetProtocolWindow(Awtpcl::PProtocolData P, int HW);
extern PACKAGE void __fastcall apSetFileList(Awtpcl::PProtocolData P, Oomisc::PFileList FL);
extern PACKAGE int __fastcall apMakeFileList(Awtpcl::PProtocolData P, Oomisc::PFileList &FL, unsigned Size);
extern PACKAGE void __fastcall apDisposeFileList(Awtpcl::PProtocolData P, Oomisc::PFileList FL, unsigned Size);
extern PACKAGE int __fastcall apAddFileToList(Awtpcl::PProtocolData P, Oomisc::PFileList FL, char * PName);
extern PACKAGE BOOL __fastcall apNextFileMask(Awtpcl::PProtocolData P, char * FName);
extern PACKAGE BOOL __fastcall apNextFileList(Awtpcl::PProtocolData P, char * FName);
extern PACKAGE int __fastcall apGetBytesTransferred(Awtpcl::PProtocolData P);
extern PACKAGE int __fastcall apGetBytesRemaining(Awtpcl::PProtocolData P);
extern PACKAGE BOOL __fastcall apSupportsBatch(Awtpcl::PProtocolData P);
extern PACKAGE int __fastcall apGetInitialFilePos(Awtpcl::PProtocolData P);
extern PACKAGE int __fastcall apEstimateTransferSecs(Awtpcl::PProtocolData P, int Size);
extern PACKAGE void __fastcall apGetProtocolInfo(Awtpcl::PProtocolData P, Oomisc::TProtocolInfo &Info);
extern PACKAGE void __fastcall apSetFileMask(Awtpcl::PProtocolData P, char * NewMask);
extern PACKAGE void __fastcall apSetReceiveFilename(Awtpcl::PProtocolData P, char * FName);
extern PACKAGE void __fastcall apSetDestinationDirectory(Awtpcl::PProtocolData P, char * Dir);
extern PACKAGE void __fastcall apSetHandshakeWait(Awtpcl::PProtocolData P, unsigned NewHandshake, unsigned NewRetry);
extern PACKAGE void __fastcall apSetEfficiencyParms(Awtpcl::PProtocolData P, unsigned BlockOverhead, unsigned TurnAroundDelay);
extern PACKAGE void __fastcall apSetProtocolPort(Awtpcl::PProtocolData P, Adport::TApdCustomComPort* H);
extern PACKAGE void __fastcall apSetOverwriteOption(Awtpcl::PProtocolData P, unsigned Opt);
extern PACKAGE void __fastcall apSetActualBPS(Awtpcl::PProtocolData P, int BPS);
extern PACKAGE void __fastcall apSetStatusInterval(Awtpcl::PProtocolData P, unsigned NewInterval);
extern PACKAGE void __fastcall apOptionsOn(Awtpcl::PProtocolData P, unsigned OptionFlags);
extern PACKAGE void __fastcall apOptionsOff(Awtpcl::PProtocolData P, unsigned OptionFlags);
extern PACKAGE BOOL __fastcall apOptionsAreOn(Awtpcl::PProtocolData P, unsigned OptionFlags);
extern PACKAGE void __fastcall apStartProtocol(Awtpcl::PProtocolData P, Byte Protocol, BOOL Transmit, Awtpcl::TPrepareProc StartProc, Awtpcl::TProtocolFunc ProtFunc);
extern PACKAGE void __fastcall apStopProtocol(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall apResetStatus(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall apShowFirstStatus(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall apShowLastStatus(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall apSignalFinish(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall aapPrepareReading(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall aapFinishReading(Awtpcl::PProtocolData P);
extern PACKAGE BOOL __fastcall aapReadProtocolBlock(Awtpcl::PProtocolData P, char * Block, unsigned &BlockSize);
extern PACKAGE void __fastcall aapPrepareWriting(Awtpcl::PProtocolData P);
extern PACKAGE void __fastcall aapFinishWriting(Awtpcl::PProtocolData P);
extern PACKAGE BOOL __fastcall aapWriteProtocolBlock(Awtpcl::PProtocolData P, char * Block, unsigned BlockSize);
extern PACKAGE void __fastcall apProtocolError(Awtpcl::PProtocolData P, int ErrorCode);
extern PACKAGE AnsiString __fastcall apTrimZeros(AnsiString S);
extern PACKAGE AnsiString __fastcall apOctalStr(int L);
extern PACKAGE int __fastcall apOctalStr2Long(AnsiString S);
extern PACKAGE int __fastcall apPackToYMTimeStamp(int RawTime);
extern PACKAGE int __fastcall apYMTimeStampToPack(int YMTime);
extern PACKAGE int __fastcall apCurrentTimeStamp(void);
extern PACKAGE int __fastcall apCrc32OfFile(Awtpcl::PProtocolData P, char * FName, int Len);
extern PACKAGE void __fastcall apMsgStatus(Awtpcl::PProtocolData P, unsigned Options);
extern PACKAGE BOOL __fastcall apMsgNextFile(Awtpcl::PProtocolData P, char * FName);
extern PACKAGE void __fastcall apMsgLog(Awtpcl::PProtocolData P, unsigned Log);
extern PACKAGE BOOL __fastcall apMsgAcceptFile(Awtpcl::PProtocolData P, char * FName);
extern PACKAGE unsigned __fastcall apUpdateChecksum(Byte CurByte, unsigned CheckSum);
extern PACKAGE unsigned __fastcall apUpdateCrc(Byte CurByte, unsigned CurCrc);
extern PACKAGE unsigned __fastcall apUpdateCrcKermit(Byte CurByte, unsigned CurCrc);
extern PACKAGE char * __fastcall apStatusMsg(char * P, unsigned Status);
extern PACKAGE void __fastcall apSetProtocolMsgBase(unsigned NewBase);
extern PACKAGE int __fastcall apUpdateCrc32(Byte CurByte, int CurCrc);

}	/* namespace Awabspcl */
using namespace Awabspcl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwAbsPcl
