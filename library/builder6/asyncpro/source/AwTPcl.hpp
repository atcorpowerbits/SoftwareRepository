// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwTPcl.pas' rev: 6.00

#ifndef AwTPclHPP
#define AwTPclHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AwUser.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awtpcl
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TProcessBlockStart { pbsNone, pbs128, pbs1024, pbsCancel, pbsEOT };
#pragma option pop

#pragma pack(push, 4)
struct TSlotInfo
{
	int Len;
	int Seq;
	BOOL InUse;
	BOOL Acked;
	unsigned Retries;
} ;
#pragma pack(pop)

typedef TSlotInfo TInfoTable[27];

typedef char TDataTable[27648];

typedef char *PDataTable;

#pragma option push -b-
enum TXmodemState { txInitial, txHandshake, txGetBlock, txWaitFreeSpace, txSendBlock, txDraining, txReplyPending, txEndDrain, txFirstEndOfTransmit, txRestEndOfTransmit, txEotReply, txFinished, txDone, rxInitial, rxWaitForHSReply, rxWaitForBlockStart, rxCollectBlock, rxProcessBlock, rxFinishedSkip, rxFinished, rxDone };
#pragma option pop

#pragma option push -b-
enum TYmodemState { tyInitial, tyHandshake, tyGetFileName, tySendFileName, tyDraining, tyReplyPending, tyPrepXmodem, tySendXmodem, tyFinished, tyFinishDrain, tyDone, ryInitial, ryDelay, ryWaitForHSReply, ryWaitForBlockStart, ryCollectBlock, ryProcessBlock, ryOpenFile, ryPrepXmodem, ryReceiveXmodem, ryFinished, ryDone };
#pragma option pop

#pragma option push -b-
enum TZmodemState { tzInitial, tzHandshake, tzGetFile, tzSendFile, tzCheckFile, tzStartData, tzEscapeData, tzSendData, tzWaitAck, tzSendEof, tzDrainEof, tzCheckEof, tzSendFinish, tzCheckFinish, tzError, tzCleanup, tzDone, rzRqstFile, rzDelay, rzWaitFile, rzCollectFile, rzSendInit, rzSendBlockPrep, rzSendBlock, rzSync, rzStartFile, rzStartData, rzCollectData, rzGotData, rzWaitEof, rzEndOfFile, rzSendFinish, rzCollectFinish, rzError, rzWaitCancel, rzCleanup, rzDone };
#pragma option pop

#pragma option push -b-
enum THeaderState { hsNone, hsGotZPad, hsGotZDle, hsGotZBin, hsGotZBin32, hsGotZHex, hsGotHeader };
#pragma option pop

#pragma option push -b-
enum HexHeaderStates { hhFrame, hhPos1, hhPos2, hhPos3, hhPos4, hhCrc1, hhCrc2 };
#pragma option pop

#pragma option push -b-
enum BinaryHeaderStates { bhFrame, bhPos1, bhPos2, bhPos3, bhPos4, bhCrc1, bhCrc2, bhCrc3, bhCrc4 };
#pragma option pop

#pragma option push -b-
enum ReceiveBlockStates { rbData, rbCrc };
#pragma option pop

#pragma option push -b-
enum TKermitState { tkInit, tkInitReply, tkCollectInit, tkOpenFile, tkSendFile, tkFileReply, tkCollectFile, tkCheckTable, tkSendData, tkBlockReply, tkCollectBlock, tkSendEof, tkEofReply, tkCollectEof, tkSendBreak, tkBreakReply, tkCollectBreak, tkComplete, tkWaitCancel, tkError, tkDone, rkInit, rkGetInit, rkCollectInit, rkGetFile, rkCollectFile, rkGetData, rkCollectData, rkComplete, rkWaitCancel, rkError, rkDone };
#pragma option pop

#pragma option push -b-
enum TKermitHeaderState { hskNone, hskGotMark, hskGotLen, hskGotSeq, hskGotType, hskGotLong1, hskGotLong2, hskDone };
#pragma option pop

#pragma option push -b-
enum TKermitDataState { dskData, dskCheck1, dskCheck2, dskCheck3 };
#pragma option pop

typedef char TBPDataBlock[2048];

typedef char *PBPDataBlock;

#pragma pack(push, 4)
struct TSABuffer
{
	unsigned Seq;
	unsigned Num;
	char PType;
	char *Buf;
} ;
#pragma pack(pop)

typedef TSABuffer TSPackets[2];

typedef Byte TQuoteArray[8];

typedef char TQuoteTable[256];

#pragma option push -b-
enum TBPlusState { rbInitial, rbGetDLE, rbGetB, rbCollectPacket, rbProcessPacket, rbFinished, rbSendEnq, rbError, rbWaitErrorAck, rbCleanup, rbDone, tbInitial, tbGetBlock, tbWaitFreeSpace, tbSendData, tbCheckAck, tbEndOfFile, tbEofAck, tbError, tbWaitErrorAck, tbCleanup, tbDone };
#pragma option pop

#pragma option push -b-
enum TPacketState { psGetDLE, psGetB, psGetSeq, psGetType, psGetData, psGetCheck1, psGetCheck2, psCheckCheck, psSendAck, psError, psSuccess };
#pragma option pop

#pragma option push -b-
enum TTermPacketState { tpsWaitB, tpsWaitSeq, tpsWaitType, tpsCollectPlus, tpsCollectAckPlus, tpsCollectT, tpsCollectAckT, tpsError };
#pragma option pop

#pragma option push -b-
enum TAckCollectionState { acGetDLE, acGetNum, acHaveAck, acGetPacket, acCollectPacket, acSkipPacket1, acSkipPacket2, acSkipPacket3, acSkipPacket4, acSkipPacket5, acTimeout, acError, acSendNak, acSendEnq, acResync1, acResync2, acResync3, acResync4, acSendData, acFailed };
#pragma option pop

#pragma option push -b-
enum TDirection { dUpload, dDownload };
#pragma option pop

#pragma pack(push, 1)
struct ParamsRecord
{
	Byte WinSend;
	Byte WinRecv;
	Byte BlkSize;
	Byte ChkType;
	Byte QuoteSet[8];
	Byte DROpt;
	Byte UROpt;
	Byte FIOpt;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TAsciiState { taInitial, taGetBlock, taWaitFreeSpace, taSendBlock, taSendDelay, taFinishDrain, taFinished, taDone, raInitial, raCollectBlock, raProcessBlock, raFinished, raDone };
#pragma option pop

typedef char TDataBlock[1024];

typedef char *PDataBlock;

typedef char TWorkBlock[2048];

typedef char *PWorkBlock;

typedef char TInBuffer[4096];

typedef char *PInBuffer;

typedef Byte TPosFlags[4];

typedef Byte TFileBuffer[8192];

typedef Byte *PFileBuffer;

struct TProtocolData;
typedef TProtocolData *PProtocolData;

typedef void __fastcall (*TPrepareProc)(PProtocolData P);

typedef void __fastcall (*TProtocolFunc)(unsigned Msg, unsigned wParam, int lParam);

typedef void __fastcall (*PrepFinishProc)(PProtocolData P);

typedef BOOL __fastcall (*ReadProtProc)(PProtocolData P, char * Block, unsigned &BlockSize);

typedef BOOL __fastcall (*WriteProtProc)(PProtocolData P, char * Block, unsigned BlockSize);

typedef void __fastcall (*CancelFunc)(PProtocolData P);

typedef void __fastcall (*ShowStatusProc)(PProtocolData P, unsigned Options);

typedef BOOL __fastcall (*NextFileFunc)(PProtocolData P, char * FName);

typedef void __fastcall (*LogFileProc)(PProtocolData P, unsigned LogFileStatus);

typedef BOOL __fastcall (*AcceptFileFunc)(PProtocolData P, char * FName);

#pragma pack(push, 4)
struct TKermitOptions
{
	Byte MaxPacketLen;
	Byte MaxTimeout;
	Byte PadCount;
	char PadChar;
	char Terminator;
	char CtlPrefix;
	char HibitPrefix;
	char Check;
	char RepeatPrefix;
	Byte CapabilitiesMask;
	Byte WindowSize;
	unsigned MaxLongPacketLen;
	unsigned SendInitSize;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TProtocolData
{
	int aStatusTrigger;
	int aTimeoutTrigger;
	int aOutBuffFreeTrigger;
	int aOutBuffUsedTrigger;
	int aNoCarrierTrigger;
	HWND aHWindow;
	Adport::TApdCustomComPort* aHC;
	BOOL aBatchProtocol;
	BOOL aFilesSent;
	BOOL aAbortFlag;
	BOOL aTimerStarted;
	int aCurProtocol;
	unsigned aCheckType;
	unsigned aHandshakeRetry;
	unsigned aHandshakeWait;
	unsigned aHandshakeAttempt;
	unsigned aBlockLen;
	unsigned aBlockNum;
	unsigned aFlags;
	unsigned aTransTimeout;
	unsigned aFinishWait;
	unsigned aRcvTimeout;
	unsigned aProtocolStatus;
	unsigned aLastBlockSize;
	int aProtocolError;
	int aSrcFileLen;
	int aSrcFileDate;
	unsigned aBlockCheck;
	int aInitFilePos;
	Oomisc::EventTimer aReplyTimer;
	char *aDataBlock;
	TProtocolFunc aCurProtFunc;
	_RTL_CRITICAL_SECTION aProtSection;
	BOOL aForceStatus;
	BOOL aTimerPending;
	unsigned aInProgress;
	unsigned aBlockErrors;
	unsigned aTotalErrors;
	unsigned aActCPS;
	unsigned aOverhead;
	unsigned aTurnDelay;
	unsigned aStatusInterval;
	unsigned aSaveStatus;
	int aSaveError;
	int aBytesRemaining;
	int aBytesTransferred;
	int aElapsedTicks;
	Oomisc::EventTimer aStatusTimer;
	Oomisc::EventTimer aTimer;
	BOOL aEndPending;
	BOOL aFileOpen;
	BOOL aNoMoreData;
	BOOL aLastBlock;
	unsigned aBlkIndex;
	int aWriteFailOpt;
	int aStartOfs;
	int aEndOfs;
	int aLastOfs;
	int aFileOfs;
	int aEndOfDataOfs;
	Byte *aFileBuffer;
	unsigned aSaveMode;
	BOOL aUpcaseFileNames;
	BOOL aFindingFirst;
	unsigned aFileListIndex;
	char aPathName[256];
	char aSearchMask[256];
	char *aFileList;
	Sysutils::TSearchRec aCurRec;
	bool aFFOpen;
	Byte aJunk;
	ShowStatusProc apShowStatus;
	LogFileProc apLogFile;
	NextFileFunc apNextFile;
	AcceptFileFunc apAcceptFile;
	PrepFinishProc apPrepareReading;
	ReadProtProc apReadProtocolBlock;
	PrepFinishProc apFinishReading;
	PrepFinishProc apPrepareWriting;
	WriteProtProc apWriteProtocolBlock;
	PrepFinishProc apFinishWriting;
	file aWorkFile;
	char aDestDir[256];
	union
	{
		struct 
		{
			BOOL sCtrlZEncountered;
			unsigned sInterCharDelay;
			unsigned sInterLineDelay;
			unsigned sInterCharTicks;
			unsigned sInterLineTicks;
			unsigned sMaxAccumDelay;
			unsigned sSendIndex;
			unsigned sCRTransMode;
			unsigned sLFTransMode;
			char sEOLChar;
			TAsciiState sAsciiState;
			
		};
		struct 
		{
			char bSaveC;
			char bLastType;
			BOOL bQSP;
			BOOL bQuoted;
			BOOL bResumeFlag;
			BOOL bAborting;
			BOOL bBPlusMode;
			BOOL bQuotePending;
			BOOL bSentENQ;
			BOOL bNAKSent;
			BOOL bFailed;
			unsigned bChecksum;
			unsigned bTimerIndex;
			unsigned bNewChk;
			unsigned bCurTimer;
			int bAbortCount;
			int bNextSeq;
			int bPacketNum;
			int bIdx;
			int bRSize;
			int bSeqNum;
			int bNext2ACK;
			int bNext2Fill;
			int bSAMax;
			int bSAWaiting;
			int bSAErrors;
			int bRPackets;
			char *bRBuffer;
			TSABuffer bSBuffer[2];
			char bQuoteTable[256];
			ParamsRecord bHostParams;
			ParamsRecord bOurParams;
			TDirection bDirection;
			TBPlusState bBPlusState;
			TTermPacketState bTermState;
			TPacketState bPacketState;
			TAckCollectionState bAckState;
			
		};
		struct 
		{
			char kPacketType;
			TKermitState kKermitState;
			TKermitHeaderState kKermitHeaderState;
			TKermitDataState kKermitDataState;
			BOOL kCheckKnown;
			BOOL kLPInUse;
			BOOL kUsingHibit;
			BOOL kUsingRepeat;
			BOOL kReceiveInProgress;
			BOOL kTransmitInProgress;
			unsigned kDataLen;
			unsigned kRecDataLen;
			unsigned kActualDataLen;
			unsigned kMinRepeatCnt;
			unsigned kRecBlockNum;
			unsigned kExpectedAck;
			unsigned kBlockCheck2;
			unsigned kSWCTurnDelay;
			TKermitOptions kKermitOptions;
			TKermitOptions kRmtKermitOptions;
			char *kInBuff;
			unsigned kInBuffHead;
			unsigned kInBuffTail;
			BOOL kWorkEndPending;
			unsigned kWorkLen;
			unsigned kLastWorkIndex;
			char *kWorkBlock;
			unsigned kTableSize;
			unsigned kTableHead;
			unsigned kTableTail;
			unsigned kBlockIndex;
			int kNext2Send;
			char *kDataTable;
			TSlotInfo kInfoTable[27];
			char kTempCheck;
			char kC1;
			char kC2;
			char kC3;
			BOOL kSkipped;
			BOOL kGetLong;
			int kLongCheck;
			unsigned kSaveCheck2;
			int kSaveCheck;
			
		};
		struct 
		{
			char zLastFrame;
			char zTerminator;
			char zHeaderType;
			TZmodemState zZmodemState;
			THeaderState zHeaderState;
			HexHeaderStates zHexHdrState;
			BinaryHeaderStates zBinHdrState;
			ReceiveBlockStates zRcvBlockState;
			bool zFileMgmtOverride;
			bool zReceiverRecover;
			bool zUseCrc32;
			bool zCanCrc32;
			bool zHexPending;
			bool zEscapePending;
			bool zEscapeAll;
			bool zControlCharSkip;
			bool zWasHex;
			unsigned zDiscardCnt;
			unsigned zConvertOpts;
			unsigned zFileMgmtOpts;
			unsigned zTransportOpts;
			unsigned zFinishRetry;
			unsigned zWorkSize;
			unsigned zCanCount;
			unsigned zHexChar;
			unsigned zCrcCnt;
			unsigned zOCnt;
			int zLastFileOfs;
			Byte zAttentionStr[32];
			bool zUse8KBlocks;
			BOOL zTookHit;
			unsigned zGoodAfterBad;
			unsigned zDataBlockLen;
			int zDataInTransit;
			char *zWorkBlock;
			char zRcvFrame;
			Byte zRcvHeader[4];
			unsigned zRcvBuffLen;
			char zLastChar;
			Byte zTransHeader[4];
			int zZRQINITValue;
			
		};
		struct 
		{
			BOOL xCRCMode;
			BOOL x1KMode;
			BOOL xGMode;
			unsigned xMaxBlockErrors;
			unsigned xBlockWait;
			unsigned xEotCheckCount;
			char xStartChar;
			char xHandshake;
			unsigned xNaksReceived;
			unsigned xEotCounter;
			unsigned xCanCounter;
			unsigned xOverheadLen;
			TXmodemState xXmodemState;
			Byte xJunk;
			int ySaveLen;
			int yNewDT;
			char ySaveName[256];
			char *yFileHeader;
			BOOL y128BlockMode;
			TYmodemState yYmodemState;
			
		};
		
	};
} ;
#pragma pack(pop)

//-- var, const, procedure ---------------------------------------------------
static const Word FileBufferSize = 0x2000;
static const Byte awpDefHandshakeWait = 0xb6;
static const Shortint awpDefHandshakeRetry = 0xa;
static const Word awpDefTransTimeout = 0x444;
static const Word apMaxBlockSize = 0x400;
extern PACKAGE char BlockFillChar;
static const Shortint TelixDelay = 0x9;
static const Shortint MaxWindowSlots = 0x1b;
static const Word BPTimeoutMax = 0x222;
static const Shortint BPErrorMax = 0xa;
static const Word BPBufferMax = 0x800;
static const Shortint BPSendAheadMax = 0x2;
static const Word BPDefFinishWait = 0x111;
extern PACKAGE System::SmallString<31>  ESCIResponse;

}	/* namespace Awtpcl */
using namespace Awtpcl;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwTPcl
