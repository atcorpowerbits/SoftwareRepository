// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'OoMisc.pas' rev: 6.00

#ifndef OoMiscHPP
#define OoMiscHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <MMSystem.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <OleCtrls.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Oomisc
{
//-- type declarations -------------------------------------------------------
#pragma pack(push, 1)
struct TPipeEvent
{
	Byte Event;
	System::ShortString Data;
} ;
#pragma pack(pop)

typedef WideString DOMString;

typedef Set<char, 0, 255>  CharSet;

typedef AnsiString TPassString;

typedef int TApdHwnd;

#pragma pack(push, 4)
struct EventTimer
{
	int StartTicks;
	int ExpireTicks;
} ;
#pragma pack(pop)

struct TTapiConfigRec;
typedef TTapiConfigRec *PTapiConfigRec;

#pragma pack(push, 4)
struct TTapiConfigRec
{
	unsigned DataSize;
	Byte Data[1024];
} ;
#pragma pack(pop)

struct TRasIPAddr;
typedef TRasIPAddr *PRasIPAddr;

#pragma pack(push, 1)
struct TRasIPAddr
{
	Byte a;
	Byte b;
	Byte c;
	Byte d;
} ;
#pragma pack(pop)

struct TRasEntry;
typedef TRasEntry *PRasEntry;

#pragma pack(push, 4)
struct TRasEntry
{
	unsigned dwSize;
	unsigned dwfOptions;
	unsigned dwCountryID;
	unsigned dwCountryCode;
	char szAreaCode[11];
	char szLocalPhoneNumber[129];
	unsigned dwAlternateOffset;
	TRasIPAddr IPAddr;
	TRasIPAddr IPAddrDns;
	TRasIPAddr IPAddrDnsAlt;
	TRasIPAddr IPAddrWins;
	TRasIPAddr IPAddrWinsAlt;
	unsigned dwFrameSize;
	unsigned dwfNetProtocols;
	unsigned dwFramingProtocol;
	char szScript[260];
	char szAutodialDll[260];
	char szAutodialFunc[260];
	char szDeviceType[17];
	char szDeviceName[129];
	char szX25PadType[33];
	char szX25Address[201];
	char szX25Facilities[201];
	char szX25UserData[201];
	unsigned dwChannels;
	unsigned dwReserved1;
	unsigned dwReserved2;
} ;
#pragma pack(pop)

struct TRasStatistics;
typedef TRasStatistics *PRasStatistics;

#pragma pack(push, 4)
struct TRasStatistics
{
	unsigned dwSize;
	unsigned dwBytesXmited;
	unsigned dwBytesRcved;
	unsigned dwFramesXmited;
	unsigned dwFramesRcved;
	unsigned dwCrcErr;
	unsigned dwTimeoutErr;
	unsigned dwAlignmentErr;
	unsigned dwHardwareOverrunErr;
	unsigned dwFramingErr;
	unsigned dwBufferOverrunErr;
	unsigned dwCompressionRatioIn;
	unsigned dwCompressionRatioOut;
	unsigned dwBps;
	unsigned dwConnectDuration;
} ;
#pragma pack(pop)

typedef char TNameCharArray[256];

typedef char TExtCharArray[256];

typedef char TPathCharArray[256];

typedef char TDirCharArray[256];

typedef char TChar20Array[21];

typedef char TCharArray[256];

typedef Byte TByteBuffer[65535];

typedef Byte *PByteBuffer;

typedef Shortint TDatabits;

typedef Shortint TStopbits;

typedef void __fastcall (*TApdNotifyProc)(unsigned Msg, unsigned wParam, int lParam);

typedef void __fastcall (__closure *TApdNotifyEvent)(unsigned Msg, unsigned wParam, int lParam);

#pragma pack(push, 4)
struct TProtocolInfo
{
	unsigned piProtocolType;
	unsigned piBlockErrors;
	unsigned piTotalErrors;
	unsigned piBlockSize;
	unsigned piBlockNum;
	int piFileSize;
	int piBytesTransferred;
	int piBytesRemaining;
	int piInitFilePos;
	int piElapsedTicks;
	int piFlags;
	unsigned piBlockCheck;
	char piFileName[256];
	int piError;
	unsigned piStatus;
} ;
#pragma pack(pop)

#pragma option push -b-
enum TAnsiParser { GotNone, GotEscape, GotBracket, GotSemiColon, GotParam, GotCommand, GotControlSeqIntro, GotLeftBrace, GotRightBrace, GotSpace, GotQuestionMark, GotQuestionParam };
#pragma option pop

typedef char TQueue[20];

struct TAnsiEmulator;
typedef TAnsiEmulator *PAnsiEmulator;

#pragma pack(push, 4)
struct TAnsiEmulator
{
	unsigned emuType;
	unsigned emuFlags;
	BOOL emuFirst;
	Byte emuAttr;
	unsigned emuIndex;
	unsigned emuParamIndex;
	char emuQueue[20];
	System::SmallString<5>  emuParamStr[5];
	int emuParamInt[5];
	TAnsiParser emuParserState;
	void *emuOther;
} ;
#pragma pack(pop)

#pragma pack(push, 2)
struct LH
{
	Word L;
	Word H;
} ;
#pragma pack(pop)

struct TIniDatabaseKey;
typedef TIniDatabaseKey *PIniDatabaseKey;

#pragma pack(push, 4)
struct TIniDatabaseKey
{
	char *KeyName;
	unsigned DataSize;
	BOOL StrType;
	BOOL Index;
	TIniDatabaseKey *Next;
} ;
#pragma pack(pop)

struct TIniDatabase;
typedef TIniDatabase *PIniDatabase;

#pragma pack(push, 4)
struct TIniDatabase
{
	char *FName;
	TIniDatabaseKey *DictionaryHead;
	TIniDatabaseKey *DictionaryTail;
	int NumRecords;
	unsigned RecordSize;
	void *DefaultRecord;
	BOOL Prepared;
} ;
#pragma pack(pop)

typedef char TModemNameZ[32];

typedef char TCmdStringZ[42];

typedef char TRspStringZ[22];

typedef char TTagStringZ[22];

typedef char TTagProfStringZ[106];

typedef char TConfigStringZ[256];

typedef char TBoolStrZ[6];

typedef char TBaudStrZ[8];

typedef char TTagArrayZ[5][22];

#pragma pack(push, 1)
struct TModemBaseData
{
	char Name[32];
	char InitCmd[42];
	char DialCmd[42];
	char DialTerm[42];
	char DialCancel[42];
	char HangupCmd[42];
	char ConfigCmd[256];
	char AnswerCmd[42];
	char OkMsg[22];
	char ConnectMsg[22];
	char BusyMsg[22];
	char VoiceMsg[22];
	char NoCarrierMsg[22];
	char NoDialToneMsg[22];
	char ErrorMsg[22];
	char RingMsg[22];
} ;
#pragma pack(pop)

typedef TModemBaseData *PModemBaseData;

struct TModemData;
typedef TModemData *PModemData;

#pragma pack(push, 4)
struct TModemData
{
	TModemBaseData Data;
	unsigned NumErrors;
	char Errors[5][22];
	unsigned NumComps;
	char Compression[5][22];
	BOOL LockDTE;
	int DefBaud;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TModemXFer
{
	TModemBaseData Data;
	char Errors[106];
	char Compress[106];
	char LockDTE[6];
	char DefBaud[8];
} ;
#pragma pack(pop)

typedef TModemXFer *PModemXFer;

#pragma pack(push, 4)
struct TModemDatabase
{
	TIniDatabase *DB;
} ;
#pragma pack(pop)

typedef TModemDatabase *PModemDatabase;

typedef char TKeyMapName[31];

typedef char TKeyMapping[21];

typedef SmallString<20>  TKeyMappingStr;

struct TKeyMapXFerRec;
typedef TKeyMapXFerRec *PKeyMapXFerRec;

#pragma pack(push, 1)
struct TKeyMapXFerRec
{
	char Name[31];
	char Keys[100][21];
} ;
#pragma pack(pop)

struct TVKEyMapRec;
typedef TVKEyMapRec *PVKeyMapRec;

#pragma pack(push, 4)
struct TVKEyMapRec
{
	unsigned KeyCode;
	unsigned ShiftState;
	TKeyMappingStr Mapping;
} ;
#pragma pack(pop)

struct TKeyEmulator;
typedef TKeyEmulator *PKeyEmulator;

#pragma pack(push, 4)
struct TKeyEmulator
{
	char *kbKeyFileName;
	char kbKeyName[31];
	BOOL kbProcessAll;
	BOOL kbProcessExt;
	char kbKeyNameList[121];
	TVKEyMapRec kbKeyMap[100];
	TIniDatabase *kbKeyDataBase;
} ;
#pragma pack(pop)

typedef char TFileList[65535];

typedef char *PFileList;

#pragma pack(push, 2)
struct TCodeRec
{
	Word Code;
	Word Sig;
} ;
#pragma pack(pop)

typedef TCodeRec TTermCodeArray[64];

typedef TCodeRec TMakeUpCodeArray[40];

struct TBufferedOutputFile;
typedef TBufferedOutputFile *PBufferedOutputFile;

#pragma pack(push, 4)
struct TBufferedOutputFile
{
	Word BufPos;
	Byte *Buffer;
	file OutFile;
} ;
#pragma pack(pop)

typedef SmallString<20>  Str20;

#pragma pack(push, 1)
struct TFontRecord
{
	Byte Bytes;
	Byte PWidth;
	Byte Width;
	Byte Height;
} ;
#pragma pack(pop)

typedef char TSigArray[6];

#pragma pack(push, 1)
struct TFaxHeaderRec
{
	char Signature[6];
	int FDateTime;
	Str20 SenderID;
	Byte Filler;
	Word PageCount;
	int PageOfs;
	Byte Padding[26];
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TPageHeaderRec
{
	int ImgLength;
	Word ImgFlags;
	Byte Padding[10];
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TFaxJobHeaderRec
{
	int ID;
	Byte Status;
	Str20 JobName;
	System::SmallString<40>  Sender;
	System::TDateTime SchedDT;
	Byte NumJobs;
	Byte NextJob;
	int CoverOfs;
	int FaxHdrOfs;
	Byte Padding[43];
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct TFaxRecipientRec
{
	Byte Status;
	Byte JobID;
	System::TDateTime SchedDT;
	Byte AttemptNum;
	Word LastResult;
	System::SmallString<50>  PhoneNumber;
	System::SmallString<100>  HeaderLine;
	System::SmallString<30>  HeaderRecipient;
	System::SmallString<30>  HeaderTitle;
	Byte Padding[29];
} ;
#pragma pack(pop)

typedef Byte TPcxPalArray[48];

#pragma pack(push, 1)
struct TPcxHeaderRec
{
	Byte Mfgr;
	Byte Ver;
	Byte Encoding;
	Byte BitsPixel;
	Word XMin;
	Word YMin;
	Word XMax;
	Word YMax;
	Word HRes;
	Word VRes;
	Byte Palette[48];
	Byte Reserved;
	Byte Planes;
	Word BytesLine;
	Word PalType;
	Byte Filler[58];
} ;
#pragma pack(pop)

typedef int TDcxOfsArray[1024];

struct TDcxHeaderRec;
typedef TDcxHeaderRec *PDcxHeaderRec;

#pragma pack(push, 1)
struct TDcxHeaderRec
{
	int ID;
	int Offsets[1024];
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TTreeRec
{
	int Next0;
	int Next1;
} ;
#pragma pack(pop)

typedef TTreeRec TTreeArray[307];

typedef TTreeRec *PTreeArray;

struct TAbsFaxCvt;
typedef TAbsFaxCvt *PAbsFaxCvt;

typedef int __fastcall (*TOpenFileCallback)(PAbsFaxCvt Cvt, char * FileName);

typedef void __fastcall (*TCloseFileCallback)(PAbsFaxCvt Cvt);

typedef int __fastcall (*TGetLineCallback)(PAbsFaxCvt Cvt, void *Data, int &Len, BOOL &EndOfPage, BOOL &MorePages);

typedef int __fastcall (*TPutLineCallback)(PAbsFaxCvt Cvt, void *Data, int Len, BOOL EndOfPage, BOOL MorePages);

typedef BOOL __fastcall (*TCvtStatusCallback)(PAbsFaxCvt Cvt, Word StatFlags, int BytesRead, int BytesToRead);

#pragma pack(push, 4)
struct TAbsFaxCvt
{
	BOOL UseHighRes;
	BOOL DoubleWidth;
	BOOL HalfHeight;
	unsigned Flags;
	unsigned ByteOfs;
	unsigned BitOfs;
	unsigned ResWidth;
	unsigned LeftMargin;
	unsigned TopMargin;
	unsigned CurrPage;
	unsigned CurrLine;
	unsigned LastPage;
	int CurPagePos;
	unsigned CenterOfs;
	void *UserData;
	void *OtherData;
	int BytesRead;
	int BytesToRead;
	Byte *DataLine;
	Byte *TmpBuffer;
	TGetLineCallback GetLine;
	TOpenFileCallback OpenCall;
	TCloseFileCallback CloseCall;
	TCvtStatusCallback StatusFunc;
	HWND StatusWnd;
	char DefExt[4];
	char InFileName[256];
	char OutFileName[256];
	char StationID[21];
	TFaxHeaderRec MainHeader;
	TPageHeaderRec PageHeader;
	TBufferedOutputFile *OutFile;
	BOOL PadPage;
	Graphics::TBitmap* InBitmap;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct SunB
{
	char s_b1;
	char s_b2;
	char s_b3;
	char s_b4;
} ;
#pragma pack(pop)

#pragma pack(push, 1)
struct SunW
{
	Word s_w1;
	Word s_w2;
} ;
#pragma pack(pop)

struct TInAddr;
typedef TInAddr *PInAddr;

#pragma pack(push, 1)
struct TInAddr
{
	
	union
	{
		struct 
		{
			int S_addr;
			
		};
		struct 
		{
			SunW S_un_w;
			
		};
		struct 
		{
			SunB S_un_b;
			
		};
		
	};
} ;
#pragma pack(pop)

class DELPHICLASS TLineReader;
class PASCALIMPLEMENTATION TLineReader : public System::TObject 
{
	typedef System::TObject inherited;
	
protected:
	char Buffer[4097];
	bool fEOLF;
	char *ReadPtr;
	Classes::TStream* fStream;
	int fBytesRead;
	int fFileSize;
	void __fastcall ReadPage(void);
	
public:
	__property int BytesRead = {read=fBytesRead, nodefault};
	__fastcall TLineReader(Classes::TStream* Stream);
	__fastcall virtual ~TLineReader(void);
	__property bool EOLF = {read=fEOLF, nodefault};
	__property int FileSize = {read=fFileSize, nodefault};
	AnsiString __fastcall NextLine();
};


class DELPHICLASS TAdStr;
class PASCALIMPLEMENTATION TAdStr : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	char operator[](unsigned Index) { return Chars[Index]; }
	
private:
	int FMaxLen;
	int FLen;
	char *FString;
	char *FCur;
	
protected:
	void __fastcall SetLen(int NewLen);
	int __fastcall GetLen(void);
	void __fastcall SetMaxLen(int NewMaxLen);
	int __fastcall GetMaxLen(void);
	int __fastcall GetBuffLen(void);
	void __fastcall SetChar(unsigned Index, char Value);
	char __fastcall GetChar(unsigned Index);
	char __fastcall GetCurChar(void);
	
public:
	__fastcall TAdStr(unsigned AMaxLen);
	__fastcall virtual ~TAdStr(void);
	void __fastcall Assign(TAdStr* Source);
	__property int Len = {read=GetLen, write=SetLen, nodefault};
	__property int MaxLen = {read=GetMaxLen, write=SetMaxLen, nodefault};
	__property int BuffLen = {read=GetBuffLen, nodefault};
	__property char Chars[unsigned Index] = {read=GetChar, write=SetChar/*, default*/};
	__property char CurChar = {read=GetCurChar, nodefault};
	__property char * Str = {read=FString};
	__property char * Cur = {read=FCur};
	void __fastcall First(void);
	void __fastcall GotoPos(unsigned Index);
	void __fastcall Last(void);
	void __fastcall MoveBy(int IndexBy);
	void __fastcall Next(void);
	void __fastcall Prev(void);
	void __fastcall Append(const AnsiString Text);
	void __fastcall AppendTAdStr(TAdStr* TS);
	void __fastcall AppendBuff(char * Buff);
	void __fastcall Clear(void);
	AnsiString __fastcall Copy(int Index, int SegLen);
	void __fastcall Delete(int Index, int SegLen);
	void __fastcall Insert(const AnsiString Text, int Index);
	unsigned __fastcall Pos(const AnsiString SubStr);
	unsigned __fastcall PosIdx(const AnsiString SubStr, int Index);
	void __fastcall Prepend(const AnsiString Text);
	void __fastcall Resize(int NewLen);
};


class DELPHICLASS TAdStrCur;
class PASCALIMPLEMENTATION TAdStrCur : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TAdStrCur(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TAdStrCur(void) { }
	#pragma option pop
	
};


struct TTextFaxData;
typedef TTextFaxData *PTextFaxData;

#pragma pack(push, 4)
struct TTextFaxData
{
	bool IsExtended;
	Byte *ReadBuffer;
	unsigned TabStop;
	unsigned LineCount;
	TLineReader* InFile;
	unsigned OnLine;
	unsigned CurRow;
	char CurStr[256];
	AnsiString Pending;
	bool FFPending;
	TFontRecord FontRec;
	union
	{
		struct 
		{
			Graphics::TBitmap* Bitmap;
			unsigned LineBytes;
			unsigned Offset;
			int ImageSize;
			void *ImageData;
			
		};
		struct 
		{
			BOOL FontLoaded;
			Byte *FontPtr;
			
		};
		
	};
} ;
#pragma pack(pop)

struct TStripRecord;
typedef TStripRecord *PStripRecord;

#pragma pack(push, 1)
struct TStripRecord
{
	int Offset;
	int Length;
} ;
#pragma pack(pop)

typedef TStripRecord TStripInfo[8190];

typedef TStripRecord *PStripInfo;

struct TTiffFaxData;
typedef TTiffFaxData *PTiffFaxData;

#pragma pack(push, 4)
struct TTiffFaxData
{
	BOOL Intel;
	Word LastBitMask;
	unsigned CurrRBSize;
	unsigned CurrRBOfs;
	unsigned OnStrip;
	unsigned OnRaster;
	Word Version;
	Word SubFile;
	Word ImgWidth;
	Word ImgLen;
	Word ImgBytes;
	Word NumLines;
	Word CompMethod;
	Word PhotoMet;
	unsigned RowStrip;
	int StripOfs;
	unsigned StripCnt;
	TStripRecord *StripInfo;
	int ByteCntOfs;
	int ImgStart;
	Byte *ReadBuffer;
	file InFile;
} ;
#pragma pack(pop)

struct TDcxFaxData;
typedef TDcxFaxData *PDcxFaxData;

#pragma pack(push, 4)
struct TDcxFaxData
{
	TDcxHeaderRec DcxHeader;
	int DcxPgSz[1024];
	unsigned DcxNumPag;
	unsigned OnPage;
} ;
#pragma pack(pop)

struct TPcxFaxData;
typedef TPcxFaxData *PPcxFaxData;

#pragma pack(push, 4)
struct TPcxFaxData
{
	unsigned CurrRBSize;
	unsigned CurrRBOfs;
	unsigned ActBytesLine;
	Byte *ReadBuffer;
	TPcxHeaderRec PcxHeader;
	unsigned PcxBytes;
	file InFile;
	Word PcxWidth;
	TDcxFaxData *DcxData;
} ;
#pragma pack(pop)

struct TBitmapFaxData;
typedef TBitmapFaxData *PBitmapFaxData;

#pragma pack(push, 4)
struct TBitmapFaxData
{
	HBITMAP BmpHandle;
	Graphics::TBitmap* DataBitmap;
	unsigned BytesPerLine;
	unsigned Width;
	unsigned NumLines;
	unsigned OnLine;
	int Offset;
	unsigned BitmapBufHandle;
	void *BitmapBuf;
	bool NeedsDithering;
	int DM[32][32];
} ;
#pragma pack(pop)

struct TScaleSettings;
typedef TScaleSettings *PScaleSettings;

#pragma pack(push, 4)
struct TScaleSettings
{
	unsigned HMult;
	unsigned HDiv;
	unsigned VMult;
	unsigned VDiv;
} ;
#pragma pack(pop)

struct TUnpackFax;
typedef TUnpackFax *PUnpackFax;

typedef int __fastcall (*TUnpackLineCallback)(PUnpackFax Unpack, Word plFlags, void *Data, unsigned Len, unsigned PageNum);

typedef void __fastcall (*TUnpackStatusCallback)(PUnpackFax Unpack, char * FaxFile, unsigned PageNum, int BytesUnpacked, int BytesToUnpack);

struct TMemoryBitmapDesc;
typedef TMemoryBitmapDesc *PMemoryBitmapDesc;

#pragma pack(push, 4)
struct TMemoryBitmapDesc
{
	unsigned Width;
	unsigned Height;
	HBITMAP Bitmap;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TUnpackFax
{
	unsigned CurCode;
	unsigned CurSig;
	unsigned LineOfs;
	unsigned LineBit;
	unsigned CurrPage;
	unsigned CurrLine;
	unsigned Flags;
	unsigned BadCodes;
	unsigned WSFrom;
	unsigned WSTo;
	unsigned WhiteCount;
	int TreeLast;
	int TreeNext;
	int Match;
	int ImgBytes;
	int ImgRead;
	TTreeRec *WhiteTree;
	TTreeRec *BlackTree;
	Byte *LineBuffer;
	Byte *TmpBuffer;
	Byte *FileBuffer;
	TFaxHeaderRec FaxHeader;
	TPageHeaderRec PageHeader;
	TUnpackLineCallback OutputLine;
	TUnpackStatusCallback Status;
	void *UserData;
	unsigned Height;
	unsigned Width;
	unsigned Handle;
	unsigned Pages;
	unsigned MaxWid;
	void *Lines;
	TScaleSettings Scale;
	TMemoryBitmapDesc MemBmp;
	TUnpackLineCallback SaveHook;
	BOOL ToBuffer;
	BOOL Inverted;
} ;
#pragma pack(pop)

struct TUnpackToPcxData;
typedef TUnpackToPcxData *PUnpackToPcxData;

#pragma pack(push, 4)
struct TUnpackToPcxData
{
	unsigned PBOfs;
	unsigned Lines;
	unsigned LastPage;
	int PCXOfs;
	BOOL FileOpen;
	BOOL DcxUnpack;
	file OutFile;
	char OutName[256];
	Byte PackBuffer[512];
	TDcxHeaderRec DcxHead;
} ;
#pragma pack(pop)

#pragma option push -b-
enum ClassType { ctUnknown, ctDetect, ctClass1, ctClass2, ctClass2_0 };
#pragma option pop

#pragma option push -b-
enum TFaxLogCode { lfaxNone, lfaxTransmitStart, lfaxTransmitOk, lfaxTransmitFail, lfaxReceiveStart, lfaxReceiveOk, lfaxReceiveSkip, lfaxReceiveFail };
#pragma option pop

typedef TFaxLogCode TLogFaxCode;

#pragma option push -b-
enum TFaxServerLogCode { fslNone, fslPollingEnabled, fslPollingDisabled, fslMonitoringEnabled, fslMonitoringDisabled };
#pragma option pop

#pragma option push -b-
enum FaxStateType { faxReady, faxWaiting, faxCritical, faxFinished };
#pragma option pop

typedef SmallString<40>  TFaxNumber;

struct TFaxEntry;
typedef TFaxEntry *PFaxEntry;

#pragma pack(push, 4)
struct TFaxEntry
{
	TFaxNumber fNumber;
	System::ShortString fFName;
	System::ShortString fCover;
	TFaxEntry *fNext;
} ;
#pragma pack(pop)

struct TSendFax;
typedef TSendFax *PSendFax;

#pragma pack(push, 1)
struct TSendFax
{
	char sfNumber[41];
	char sfFName[256];
	char sfCover[256];
} ;
#pragma pack(pop)

#pragma option push -b-
enum TDispatchType { dtNone, dtDispatch, dtTrigger, dtError, dtThread, dtTriggerAlloc, dtTriggerDispose, dtTriggerHandlerAlloc, dtTriggerHandlerDispose, dtTriggerDataChange, dtTelnet, dtFax, dtXModem, dtYModem, dtZModem, dtKermit, dtAscii, dtBPlus, dtPacket, dtUser, dtScript };
#pragma option pop

#pragma option push -b-
enum TDispatchSubType { dstNone, dstReadCom, dstWriteCom, dstLineStatus, dstModemStatus, dstAvail, dstTimer, dstData, dstStatus, dstThreadStart, dstThreadExit, dstThreadSleep, dstThreadWake, dstDataTrigger, dstTimerTrigger, dstStatusTrigger, dstAvailTrigger, dstWndHandler, dstProcHandler, dstEventHandler, dstSWill, dstSWont, dstSDo, dstSDont, dstRWill, dstRWont, dstRDo, dstRDont, dstCommand, dstSTerm, dsttfNone, dsttfGetEntry, dsttfInit, dsttf1Init1, dsttf2Init1, dsttf2Init1A, dsttf2Init1B, dsttf2Init2, dsttf2Init3, dsttfDial, dsttfRetryWait, dsttf1Connect, dsttf1SendTSI, dsttf1TSIResponse, dsttf1DCSResponse, dsttf1TrainStart, dsttf1TrainFinish, dsttf1WaitCFR, dsttf1WaitPageConnect, dsttf2Connect, dsttf2GetParams, dsttfWaitXon, dsttfWaitFreeHeader, dsttfSendPageHeader, dsttfOpenCover, dsttfSendCover, dsttfPrepPage, dsttfSendPage, dsttfDrainPage, dsttf1PageEnd, dsttf1PrepareEOP, dsttf1SendEOP, dsttf1WaitMPS, dsttf1WaitEOP, dsttf1WaitMCF, dsttf1SendDCN, dsttf1Hangup, dsttf1WaitHangup, dsttf2SendEOP
	, dsttf2WaitFPTS, dsttf2WaitFET, dsttf2WaitPageOK, dsttf2SendNewParams, dsttf2NextPage, dsttf20CheckPage, dsttfClose, dsttfCompleteOK, dsttfAbort, dsttfDone, dstrfNone, dstrfInit, dstrf1Init1, dstrf2Init1, dstrf2Init1A, dstrf2Init1B, dstrf2Init2, dstrf2Init3, dstrfWaiting, dstrfAnswer, dstrf1SendCSI, dstrf1SendDIS, dstrf1CollectFrames, dstrf1CollectRetry1, dstrf1CollectRetry2, dstrf1StartTrain, dstrf1CollectTrain, dstrf1Timeout, dstrf1Retrain, dstrf1FinishTrain, dstrf1SendCFR, dstrf1WaitPageConnect, dstrf2ValidConnect, dstrf2GetSenderID, dstrf2GetConnect, dstrfStartPage, dstrfGetPageData, dstrf1FinishPage, dstrf1WaitEOP, dstrf1WritePage, dstrf1SendMCF, dstrf1WaitDCN, dstrf1WaitHangup, dstrf2GetPageResult, dstrf2GetFHNG, dstrfComplete, dstrfAbort, dstrfDone, dsttxInitial, dsttxHandshake, dsttxGetBlock, dsttxWaitFreeSpace, dsttxSendBlock, dsttxDraining, dsttxReplyPending, dsttxEndDrain, dsttxFirstEndOfTransmit, dsttxRestEndOfTransmit, dsttxEotReply, dsttxFinished, dsttxDone, dstrxInitial, dstrxWaitForHSReply
	, dstrxWaitForBlockStart, dstrxCollectBlock, dstrxProcessBlock, dstrxFinishedSkip, dstrxFinished, dstrxDone, dsttyInitial, dsttyHandshake, dsttyGetFileName, dsttySendFileName, dsttyDraining, dsttyReplyPending, dsttyPrepXmodem, dsttySendXmodem, dsttyFinished, dsttyFinishDrain, dsttyDone, dstryInitial, dstryDelay, dstryWaitForHSReply, dstryWaitForBlockStart, dstryCollectBlock, dstryProcessBlock, dstryOpenFile, dstryPrepXmodem, dstryReceiveXmodem, dstryFinished, dstryDone, dsttzInitial, dsttzHandshake, dsttzGetFile, dsttzSendFile, dsttzCheckFile, dsttzStartData, dsttzEscapeData, dsttzSendData, dsttzWaitAck, dsttzSendEof, dsttzDrainEof, dsttzCheckEof, dsttzSendFinish, dsttzCheckFinish, dsttzError, dsttzCleanup, dsttzDone, dstrzRqstFile, dstrzDelay, dstrzWaitFile, dstrzCollectFile, dstrzSendInit, dstrzSendBlockPrep, dstrzSendBlock, dstrzSync, dstrzStartFile, dstrzStartData, dstrzCollectData, dstrzGotData, dstrzWaitEof, dstrzEndOfFile, dstrzSendFinish, dstrzCollectFinish, dstrzError, dstrzWaitCancel, dstrzCleanup, dstrzDone, dsttkInit
	, dsttkInitReply, dsttkCollectInit, dsttkOpenFile, dsttkSendFile, dsttkFileReply, dsttkCollectFile, dsttkCheckTable, dsttkSendData, dsttkBlockReply, dsttkCollectBlock, dsttkSendEof, dsttkEofReply, dsttkCollectEof, dsttkSendBreak, dsttkBreakReply, dsttkCollectBreak, dsttkComplete, dsttkWaitCancel, dsttkError, dsttkDone, dstrkInit, dstrkGetInit, dstrkCollectInit, dstrkGetFile, dstrkCollectFile, dstrkGetData, dstrkCollectData, dstrkComplete, dstrkWaitCancel, dstrkError, dstrkDone, dsttaInitial, dsttaGetBlock, dsttaWaitFreeSpace, dsttaSendBlock, dsttaSendDelay, dsttaFinishDrain, dsttaFinished, dsttaDone, dstraInitial, dstraCollectBlock, dstraProcessBlock, dstraFinished, dstraDone, dstEnable, dstDisable, dstStringPacket, dstSizePacket, dstPacketTimeout, dstStartStr, dstEndStr, dstIdle, dstWaiting, dstCollecting };
#pragma option pop

#pragma pack(push, 1)
struct TTraceRecord
{
	char EventType;
	char C;
} ;
#pragma pack(pop)

typedef TTraceRecord TTraceQueue[4000001];

typedef TTraceRecord *PTraceQueue;

struct TDispatchRecord;
typedef TDispatchRecord *PDispatchRecord;

#pragma pack(push, 4)
struct TDispatchRecord
{
	TDispatchType drType;
	TDispatchSubType drSubType;
	unsigned drTime;
	unsigned drData;
	unsigned drMoreData;
} ;
#pragma pack(pop)

typedef Byte TDispatchQueue[16000001];

typedef Byte *PDispatchQueue;

typedef char TDBuffer[65528];

typedef char *PDBuffer;

typedef char TOBuffer[2147483647];

typedef char *POBuffer;

typedef char TComName[6];

#pragma option push -b-
enum TTriggerType { ttNone, ttAvail, ttTimer, ttData, ttStatus };
#pragma option pop

struct TTimerTrigger;
typedef TTimerTrigger *PTimerTrigger;

#pragma pack(push, 4)
struct TTimerTrigger
{
	unsigned tHandle;
	EventTimer tET;
	int tTicks;
	BOOL tValid;
	BOOL tActive;
} ;
#pragma pack(pop)

typedef unsigned TCheckIndex[22];

struct TDataTrigger;
typedef TDataTrigger *PDataTrigger;

#pragma pack(push, 4)
struct TDataTrigger
{
	unsigned tHandle;
	unsigned tLen;
	unsigned tChkIndex[22];
	BOOL tMatched;
	BOOL tIgnoreCase;
	char tData[22];
} ;
#pragma pack(pop)

struct TStatusTrigger;
typedef TStatusTrigger *PStatusTrigger;

#pragma pack(push, 4)
struct TStatusTrigger
{
	unsigned tHandle;
	unsigned tSType;
	Word tValue;
	bool tSActive;
	bool StatusHit;
} ;
#pragma pack(pop)

#pragma pack(push, 4)
struct TTriggerSave
{
	unsigned tsLenTrigger;
	Classes::TList* tsTimerTriggers;
	Classes::TList* tsDataTriggers;
	Classes::TList* tsStatusTriggers;
} ;
#pragma pack(pop)

struct TWndTriggerHandler;
typedef TWndTriggerHandler *PWndTriggerHandler;

#pragma pack(push, 4)
struct TWndTriggerHandler
{
	int thWnd;
	bool thDeleted;
} ;
#pragma pack(pop)

struct TProcTriggerHandler;
typedef TProcTriggerHandler *PProcTriggerHandler;

#pragma pack(push, 4)
struct TProcTriggerHandler
{
	TApdNotifyProc thNotify;
	bool thDeleted;
} ;
#pragma pack(pop)

struct TEventTriggerHandler;
typedef TEventTriggerHandler *PEventTriggerHandler;

struct TEventTriggerHandler
{
	TApdNotifyEvent thNotify;
	bool thDeleted;
	bool thSync;
} ;

typedef void *TDataPointerArray[3];

#pragma pack(push, 4)
struct QPCCast
{
	unsigned LowPart;
	unsigned HighPart;
} ;
#pragma pack(pop)

class DELPHICLASS TApdBaseComponent;
class PASCALIMPLEMENTATION TApdBaseComponent : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(const AnsiString Value);
	
__published:
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
public:
	#pragma option push -w-inl
	/* TComponent.Create */ inline __fastcall virtual TApdBaseComponent(Classes::TComponent* AOwner) : Classes::TComponent(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdBaseComponent(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdBaseWinControl;
class PASCALIMPLEMENTATION TApdBaseWinControl : public Controls::TWinControl 
{
	typedef Controls::TWinControl inherited;
	
protected:
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(const AnsiString Value);
	
__published:
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
public:
	#pragma option push -w-inl
	/* TWinControl.Create */ inline __fastcall virtual TApdBaseWinControl(Classes::TComponent* AOwner) : Controls::TWinControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdBaseWinControl(HWND ParentWindow) : Controls::TWinControl(ParentWindow) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TWinControl.Destroy */ inline __fastcall virtual ~TApdBaseWinControl(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdBaseOleControl;
class PASCALIMPLEMENTATION TApdBaseOleControl : public Olectrls::TOleControl 
{
	typedef Olectrls::TOleControl inherited;
	
protected:
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(const AnsiString Value);
	
__published:
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
public:
	#pragma option push -w-inl
	/* TOleControl.Create */ inline __fastcall virtual TApdBaseOleControl(Classes::TComponent* AOwner) : Olectrls::TOleControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TOleControl.Destroy */ inline __fastcall virtual ~TApdBaseOleControl(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdBaseOleControl(HWND ParentWindow) : Olectrls::TOleControl(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TApdBaseGraphicControl;
class PASCALIMPLEMENTATION TApdBaseGraphicControl : public Controls::TGraphicControl 
{
	typedef Controls::TGraphicControl inherited;
	
protected:
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(const AnsiString Value);
	
__published:
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
public:
	#pragma option push -w-inl
	/* TGraphicControl.Create */ inline __fastcall virtual TApdBaseGraphicControl(Classes::TComponent* AOwner) : Controls::TGraphicControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TGraphicControl.Destroy */ inline __fastcall virtual ~TApdBaseGraphicControl(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdBaseScrollingWinControl;
class PASCALIMPLEMENTATION TApdBaseScrollingWinControl : public Forms::TScrollingWinControl 
{
	typedef Forms::TScrollingWinControl inherited;
	
protected:
	AnsiString __fastcall GetVersion();
	void __fastcall SetVersion(const AnsiString Value);
	
__published:
	__property AnsiString Version = {read=GetVersion, write=SetVersion, stored=false};
public:
	#pragma option push -w-inl
	/* TScrollingWinControl.Create */ inline __fastcall virtual TApdBaseScrollingWinControl(Classes::TComponent* AOwner) : Forms::TScrollingWinControl(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TApdBaseScrollingWinControl(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdBaseScrollingWinControl(HWND ParentWindow) : Forms::TScrollingWinControl(ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
#define ApVersionStr "v4.06"
#define ApdProductName "Async Professional"
#define ApdShortProductName "APRO"
#define ApdVendor "TurboPower Software Company"
#define ApdVendorURL "http://www.TurboPower.com"
#define ApdXSLImplementation  (0.000000E+00)
#define ApdXMLSpecification "1.0"
static const Byte fsPathName = 0xff;
static const Byte fsDirectory = 0xff;
static const Byte fsFileName = 0xff;
static const Byte fsExtension = 0xff;
static const Byte fsName = 0xff;
static const Shortint ApdShareFileRead = 0x40;
#define ApdDefFileName "C:\\DEFAULT.APF"
static const Word ApdPipeTimeout = 0x1388;
#define ApdPipeName "\\\\.\\pipe\\ApFaxCnv"
#define ApdSemaphoreName "ApFaxCnvSem"
#define ApdRegKey "\\SOFTWARE\\TurboPower\\ApFaxCnv\\Settings"
#define ApdIniFileName "APFPDENG.INI"
#define ApdIniSection "Settings"
#define ApdIniKey "AutoExec"
#define ApdDef32PrinterName "APF Fax Printer"
#define ApdDef16PrinterName "Print To Fax"
#define ApdDefPrinterPort "PRINTFAX"
#define ApdDefaultTerminalName "<default>"
#define ApdNoTerminalName "<none>"
static const Shortint eNull = 0x0;
static const Shortint eStartDoc = 0x1;
static const Shortint eEndDoc = 0x2;
static const Shortint eSetFileName = 0x3;
static const Shortint RasMaxDomain = 0xf;
static const Word RasMaxPassword = 0x100;
static const Word RasMaxUserName = 0x100;
static const Word RasMaxEntryName = 0x100;
static const Word RasMaxPhoneBook = 0x100;
static const Word RasMaxError = 0x100;
static const Shortint RasMaxEntries = 0x40;
static const Byte RasMaxDeviceName = 0x80;
static const Shortint RasMaxDeviceType = 0x10;
static const Byte RasMaxPhoneNumber = 0x80;
static const Byte RasMaxCallBackNum = 0x80;
static const Shortint RasMaxAreaCode = 0xa;
static const Shortint RasMaxPadType = 0x20;
static const Byte RasMaxX25Address = 0xc8;
static const Shortint RasMaxIPAddress = 0xf;
static const Shortint RasMaxIPXAddress = 0x15;
static const Byte RasMaxFacilities = 0xc8;
static const Byte RasMaxUserData = 0xc8;
static const Shortint RASEO_UseCountryAndAreaCodes = 0x1;
static const Shortint RASEO_SpecificIpAddr = 0x2;
static const Shortint RASEO_SpecificNameServers = 0x4;
static const Shortint RASEO_IpHeaderCompression = 0x8;
static const Shortint RASEO_RemoteDefaultGateway = 0x10;
static const Shortint RASEO_DisableLcpExtensions = 0x20;
static const Shortint RASEO_TerminalBeforeDial = 0x40;
static const Byte RASEO_TerminalAfterDial = 0x80;
static const Word RASEO_ModemLights = 0x100;
static const Word RASEO_SwCompression = 0x200;
static const Word RASEO_RequireEncryptedPw = 0x400;
static const Word RASEO_RequireMsEncryptedPw = 0x800;
static const Word RASEO_RequireDataEncryption = 0x1000;
static const Word RASEO_NetworkLogon = 0x2000;
static const Word RASEO_UseLogonCredentials = 0x4000;
static const Word RASEO_PromoteAlternates = 0x8000;
static const int RASEO_SecureLocalFiles = 0x10000;
static const int RASEO_RequireEAP = 0x20000;
static const int RASEO_RequirePAP = 0x40000;
static const int RASEO_RequireSPAP = 0x80000;
static const int RASEO_Custom = 0x100000;
static const int RASEO_PreviewPhoneNumber = 0x200000;
static const int RASEO_SharedPhoneNumbers = 0x800000;
static const int RASEO_PreviewUserPw = 0x1000000;
static const int RASEO_PreviewDomain = 0x2000000;
static const int RASEO_ShowDialingProgress = 0x4000000;
static const int RASEO_RequireCHAP = 0x8000000;
static const int RASEO_RequireMsCHAP = 0x10000000;
static const int RASEO_RequireMsCHAP2 = 0x20000000;
static const int RASEO_RequireW95MSCHAP = 0x40000000;
static const unsigned RASEO_CustomScript = 0x80000000;
static const Shortint RASNP_NetBEUI = 0x1;
static const Shortint RASNP_Ipx = 0x2;
static const Shortint RASNP_Ip = 0x4;
static const Shortint RASFP_Ppp = 0x1;
static const Shortint RASFP_Slip = 0x2;
static const Shortint RASFP_Ras = 0x4;
#define RASDT_Modem "modem"
#define RASDT_Isdn "isdn"
#define RASDT_X25 "x25"
#define RASDT_Vpn "vpn"
#define RASDT_Pad "pad"
#define RASDT_Generic "GENERIC"
#define RASDT_Serial "SERIAL"
#define RASDT_FrameRelay "FRAMERELAY"
#define RASDT_Atm "ATM"
#define RASDT_Sonet "SONET"
#define RASDT_SW56 "SW56"
#define RASDT_Irda "IRDA"
#define RASDT_Parallel "PARALLEL"
static const Shortint MaxComHandles = 0x32;
static const Word DispatchBufferSize = 0x2000;
static const Shortint MaxMessageLen = 0x50;
static const Shortint DontChangeBaud = 0x0;
static const Shortint DontChangeParity = 0x5;
static const Shortint DontChangeDatabits = 0x9;
static const Shortint DontChangeStopbits = 0x3;
static const Shortint msCTSDelta = 0x10;
static const Shortint msDSRDelta = 0x20;
static const Shortint msRingDelta = 0x4;
static const Byte msDCDDelta = 0x80;
static const Shortint lsOverrun = 0x1;
static const Shortint lsParity = 0x2;
static const Shortint lsFraming = 0x4;
static const Shortint lsBreak = 0x8;
static const Shortint leNoError = 0x0;
static const Shortint leBuffer = 0x1;
static const Shortint leOverrun = 0x2;
static const Shortint leParity = 0x3;
static const Shortint leFraming = 0x4;
static const Shortint leCTSTO = 0x5;
static const Shortint leDSRTO = 0x6;
static const Shortint leDCDTO = 0x7;
static const Shortint leTxFull = 0x8;
static const Shortint leBreak = 0x9;
static const Shortint stNotActive = 0x0;
static const Shortint stModem = 0x1;
static const Shortint stLine = 0x2;
static const Shortint stOutBuffFree = 0x3;
static const Shortint stOutBuffUsed = 0x4;
static const Shortint stOutSent = 0x5;
static const Shortint nfNone = 0x0;
static const Shortint nfMask = 0x1;
static const Shortint nfList = 0x2;
static const Shortint wfcWriteNone = 0x0;
static const Shortint wfcWriteFail = 0x1;
static const Shortint wfcWriteRename = 0x2;
static const Shortint wfcWriteAnyway = 0x3;
static const Shortint wfcWriteResume = 0x4;
static const Shortint atNone = 0x0;
static const Shortint atStrip = 0x1;
static const Shortint atAddCRBefore = 0x2;
static const Shortint atAddLFAfter = 0x3;
extern PACKAGE char atEOFMarker;
static const Shortint apFirstCall = 0x1;
static const Shortint apLastCall = 0x2;
static const Shortint lfReceiveStart = 0x0;
static const Shortint lfReceiveOk = 0x1;
static const Shortint lfReceiveFail = 0x2;
static const Shortint lfReceiveSkip = 0x3;
static const Shortint lfTransmitStart = 0x4;
static const Shortint lfTransmitOk = 0x5;
static const Shortint lfTransmitFail = 0x6;
static const Shortint lfTransmitSkip = 0x7;
static const Word ev_CTSS = 0x400;
static const Word ev_DSRS = 0x800;
static const Word ev_RLSDS = 0x1000;
static const Word ev_RingTe = 0x2000;
static const Shortint MsrShadowOfs = 0x23;
static const Shortint DeltaCTSMask = 0x1;
static const Shortint DeltaDSRMask = 0x2;
static const Shortint DeltaRIMask = 0x4;
static const Shortint DeltaDCDMask = 0x8;
static const Shortint CTSMask = 0x10;
static const Shortint DSRMask = 0x20;
static const Shortint RIMask = 0x40;
static const Byte DCDMask = 0x80;
static const Word apw_First = 0x7e00;
static const Word apw_TriggerAvail = 0x7e01;
static const Word apw_TriggerData = 0x7e02;
static const Word apw_TriggerTimer = 0x7e03;
static const Word apw_TriggerStatus = 0x7e04;
static const Word apw_FromYmodem = 0x7e05;
static const Word apw_PortOpen = 0x7e08;
static const Word apw_PortClose = 0x7e09;
static const Word apw_ClosePending = 0x7e0a;
static const Word apw_ProtocolCancel = 0x7e14;
static const Word apw_ProtocolStatus = 0x7e15;
static const Word apw_ProtocolLog = 0x7e16;
static const Word apw_ProtocolNextFile = 0x7e17;
static const Word apw_ProtocolAcceptFile = 0x7e18;
static const Word apw_ProtocolFinish = 0x7e19;
static const Word apw_ProtocolResume = 0x7e1a;
static const Word apw_ProtocolError = 0x7e1b;
static const Word apw_ProtocolAbort = 0x7e1c;
static const Word apw_AutoAnswer = 0x7e28;
static const Word apw_CancelCall = 0x7e29;
static const Word apw_StartDial = 0x7e2a;
static const Word apw_ModemOk = 0x7e28;
static const Word apw_ModemConnect = 0x7e29;
static const Word apw_ModemBusy = 0x7e2a;
static const Word apw_ModemVoice = 0x7e2b;
static const Word apw_ModemNoCarrier = 0x7e2c;
static const Word apw_ModemNoDialTone = 0x7e2d;
static const Word apw_ModemError = 0x7e2e;
static const Word apw_GotLineSpeed = 0x7e2f;
static const Word apw_GotErrCorrection = 0x7e30;
static const Word apw_GotDataCompression = 0x7e31;
static const Word apw_CmdTimeout = 0x7e32;
static const Word apw_DialTimeout = 0x7e33;
static const Word apw_AnswerTimeout = 0x7e34;
static const Word apw_DialCount = 0x7e35;
static const Word apw_AnswerCount = 0x7e36;
static const Word apw_ModemRing = 0x7e37;
static const Word apw_ModemIsConnected = 0x7e38;
static const Word apw_ConnectFailed = 0x7e39;
static const Word apw_CommandProcessed = 0x7e3a;
static const Word apw_TermStart = 0x7e3c;
static const Word apw_TermStop = 0x7e3d;
static const Word apw_TermSetCom = 0x7e3e;
static const Word apw_TermRelCom = 0x7e3f;
static const Word apw_TermSetEmuPtr = 0x7e40;
static const Word apw_TermSetEmuProc = 0x7e41;
static const Word apw_TermClear = 0x7e42;
static const Word apw_TermBuffer = 0x7e43;
static const Word apw_TermColors = 0x7e44;
static const Word apw_TermToggleScroll = 0x7e45;
static const Word apw_TermCapture = 0x7e46;
static const Word apw_TermStuff = 0x7e47;
static const Word apw_TermPaint = 0x7e48;
static const Word apw_TermSetWndProc = 0x7e49;
static const Word apw_TermColorsH = 0x7e4a;
static const Word apw_TermSave = 0x7e4b;
static const Word apw_TermColorMap = 0x7e4c;
static const Word apw_TermForceSize = 0x7e4d;
static const Word apw_TermFontSize = 0x7e4e;
static const Word apw_TermStatus = 0x7e50;
static const Word apw_TermBPlusStart = 0x7e51;
static const Word apw_TermError = 0x7e52;
static const Word apw_CursorPosReport = 0x7e53;
static const Word apw_FaxCvtStatus = 0x7e5a;
static const Word apw_FaxUnpStatus = 0x7e5b;
static const Word apw_FaxOutput = 0x7e5c;
static const Word apw_ViewSetFile = 0x7e64;
static const Word apw_ViewSetFG = 0x7e65;
static const Word apw_ViewSetBG = 0x7e66;
static const Word apw_ViewSetScale = 0x7e67;
static const Word apw_ViewSetScroll = 0x7e68;
static const Word apw_ViewSelectAll = 0x7e69;
static const Word apw_ViewSelect = 0x7e6a;
static const Word apw_ViewCopy = 0x7e6b;
static const Word apw_ViewSetWndProc = 0x7e6c;
static const Word apw_ViewSetWhitespace = 0x7e6d;
static const Word apw_ViewGetBitmap = 0x7e6e;
static const Word apw_ViewGetNumPages = 0x7e6f;
static const Word apw_ViewStartUpdate = 0x7e70;
static const Word apw_ViewEndUpdate = 0x7e71;
static const Word apw_ViewGotoPage = 0x7e72;
static const Word apw_ViewGetCurPage = 0x7e73;
static const Word apw_ViewSetDesignMode = 0x7e74;
static const Word apw_ViewSetRotation = 0x7e75;
static const Word apw_ViewSetAutoScale = 0x7e76;
static const Word apw_ViewNotifyPage = 0x7e77;
static const Word apw_ViewGetPageDim = 0x7e78;
static const Word apw_ViewSetLoadWholeFax = 0x7e79;
static const Word apw_ViewSetBusyCursor = 0x7e7a;
static const Word apw_ViewerError = 0x7e7b;
static const Word apw_ViewGetPageFlags = 0x7e7c;
static const Word apw_ViewGetFileName = 0x7e7d;
static const Word apw_TermBlinkTimeChange = 0x7e82;
static const Word apw_TermPersistentMarkChange = 0x7e83;
static const Word apw_TermSetKeyEmuPtr = 0x7e84;
static const Word apw_TermSetKeyEmuProc = 0x7e85;
static const Word apw_TermSetHalfDuplex = 0x7e86;
static const Word apw_TermGetBuffPtr = 0x7e87;
static const Word apw_TermGetClientLine = 0x7e88;
static const Word apw_TermWaitForPort = 0x7e89;
static const Word apw_TermNeedsUpdate = 0x7e8a;
static const Word apw_PrintDriverJobCreated = 0x7e8c;
static const Word apw_BeginDoc = 0x7e8d;
static const Word apw_EndDoc = 0x7e8e;
static const Word apw_AddPrim = 0x7e8f;
static const Word apw_EndPage = 0x7e90;
static const Word apw_FaxCancel = 0x7ea0;
static const Word apw_FaxNextfile = 0x7ea1;
static const Word apw_FaxStatus = 0x7ea2;
static const Word apw_FaxLog = 0x7ea3;
static const Word apw_FaxName = 0x7ea4;
static const Word apw_FaxAccept = 0x7ea5;
static const Word apw_FaxError = 0x7ea6;
static const Word apw_FaxFinish = 0x7ea7;
static const Word apw_TapiWaveMessage = 0x7eb4;
static const Word apw_TapiEventMessage = 0x7eb5;
static const Word apw_VoIPEventMessage = 0x7eb6;
static const Word apw_VoIPNotifyMessage = 0x7eb7;
static const Word apw_StateDeactivate = 0x7ebe;
static const Word apw_StateChange = 0x7ebf;
static const Word apw_SapiTrain = 0x7ec0;
static const Word apw_SapiPhoneCallBack = 0x7ec1;
static const Word apw_SapiInfoPhrase = 0x7ec2;
static const Word apw_PgrStatusEvent = 0x7ec8;
#define DispatcherClassName "awDispatch"
#define ProtocolClassName "awProtocol"
#define TerminalClassName "awTerminal"
#define MessageHandlerClassName "awMsgHandler"
#define FaxViewerClassName "awViewer"
#define FaxViewerClassNameDesign "dcViewer"
#define TerminalClassNameDesign "dcTerminal"
#define FaxHandlerClassName "awFaxHandler"
static const Shortint egDos = 0x0;
static const Shortint egGeneral = 0xffffffff;
static const Shortint egOpenComm = 0xfffffffe;
static const Shortint egSerialIO = 0xfffffffd;
static const Shortint egModem = 0xfffffffc;
static const Shortint egTrigger = 0xfffffffb;
static const Shortint egProtocol = 0xfffffffa;
static const Shortint egINI = 0xfffffff9;
static const Shortint egFax = 0xfffffff8;
static const Shortint egAdWinsock = 0x9;
static const Shortint egWinsock = 0xa;
static const Shortint egWinsockEx = 0xb;
static const Shortint egTapi = 0xfffffff3;
static const Shortint ecOK = 0x0;
static const Shortint ecFileNotFound = 0xfffffffe;
static const Shortint ecPathNotFound = 0xfffffffd;
static const Shortint ecTooManyFiles = 0xfffffffc;
static const Shortint ecAccessDenied = 0xfffffffb;
static const Shortint ecInvalidHandle = 0xfffffffa;
static const Shortint ecOutOfMemory = 0xfffffff8;
static const Shortint ecInvalidDrive = 0xfffffff1;
static const Shortint ecNoMoreFiles = 0xffffffee;
static const Shortint ecDiskRead = 0xffffff9c;
static const Shortint ecDiskFull = 0xffffff9b;
static const Shortint ecNotAssigned = 0xffffff9a;
static const Shortint ecNotOpen = 0xffffff99;
static const Shortint ecNotOpenInput = 0xffffff98;
static const Shortint ecNotOpenOutput = 0xffffff97;
static const short ecWriteProtected = 0xffffff6a;
static const short ecUnknownUnit = 0xffffff69;
static const short ecDriveNotReady = 0xffffff68;
static const short ecUnknownCommand = 0xffffff67;
static const short ecCrcError = 0xffffff66;
static const short ecBadStructLen = 0xffffff65;
static const short ecSeekError = 0xffffff64;
static const short ecUnknownMedia = 0xffffff63;
static const short ecSectorNotFound = 0xffffff62;
static const short ecOutOfPaper = 0xffffff61;
static const short ecDeviceWrite = 0xffffff60;
static const short ecDeviceRead = 0xffffff5f;
static const short ecHardwareFailure = 0xffffff5e;
static const short ecBadHandle = 0xfffffc17;
static const short ecBadArgument = 0xfffffc16;
static const short ecGotQuitMsg = 0xfffffc15;
static const short ecBufferTooBig = 0xfffffc14;
static const short ecPortNotAssigned = 0xfffffc13;
static const short ecInternal = 0xfffffc12;
static const short ecModemNotAssigned = 0xfffffc11;
static const short ecPhonebookNotAssigned = 0xfffffc10;
static const short ecCannotUseWithWinSock = 0xfffffc0f;
static const short ecBadId = 0xfffff82f;
static const short ecBaudRate = 0xfffff82e;
static const short ecByteSize = 0xfffff82d;
static const short ecDefault = 0xfffff82c;
static const short ecHardware = 0xfffff82b;
static const short ecMemory = 0xfffff82a;
static const short ecCommNotOpen = 0xfffff829;
static const short ecAlreadyOpen = 0xfffff828;
static const short ecNoHandles = 0xfffff827;
static const short ecNoTimers = 0xfffff826;
static const short ecNoPortSelected = 0xfffff825;
static const short ecNotOpenedByTapi = 0xfffff824;
static const short ecNullApi = 0xfffff447;
static const short ecNotSupported = 0xfffff446;
static const short ecRegisterHandlerFailed = 0xfffff445;
static const short ecPutBlockFail = 0xfffff444;
static const short ecGetBlockFail = 0xfffff443;
static const short ecOutputBufferTooSmall = 0xfffff442;
static const short ecBufferIsEmpty = 0xfffff441;
static const short ecTracingNotEnabled = 0xfffff440;
static const short ecLoggingNotEnabled = 0xfffff43f;
static const short ecBaseAddressNotSet = 0xfffff43e;
static const short ecModemNotStarted = 0xfffff05f;
static const short ecModemBusy = 0xfffff05e;
static const short ecModemNotDialing = 0xfffff05d;
static const short ecNotDialing = 0xfffff05c;
static const short ecAlreadyDialing = 0xfffff05b;
static const short ecModemNotResponding = 0xfffff05a;
static const short ecModemRejectedCommand = 0xfffff059;
static const short ecModemStatusMismatch = 0xfffff058;
static const short ecDeviceNotSelected = 0xfffff057;
static const short ecModemDetectedBusy = 0xfffff056;
static const short ecModemNoDialtone = 0xfffff055;
static const short ecModemNoCarrier = 0xfffff054;
static const short ecModemNoAnswer = 0xfffff053;
static const short ecInitFail = 0xfffff052;
static const short ecLoginFail = 0xfffff051;
static const short ecMinorSrvErr = 0xfffff050;
static const short ecFatalSrvErr = 0xfffff04f;
static const short ecModemNotFound = 0xfffff04c;
static const short ecInvalidFile = 0xfffff04b;
static const Word csOpenPort = 0x1194;
static const Word csPortOpened = 0x1195;
static const Word csConnectDevice = 0x1196;
static const Word csDeviceConnected = 0x1197;
static const Word csAllDevicesConnected = 0x1198;
static const Word csAuthenticate = 0x1199;
static const Word csAuthNotify = 0x119a;
static const Word csAuthRetry = 0x119b;
static const Word csAuthCallback = 0x119c;
static const Word csAuthChangePassword = 0x119d;
static const Word csAuthProject = 0x119e;
static const Word csAuthLinkSpeed = 0x119f;
static const Word csAuthAck = 0x11a0;
static const Word csReAuthenticate = 0x11a1;
static const Word csAuthenticated = 0x11a2;
static const Word csPrepareForCallback = 0x11a3;
static const Word csWaitForModemReset = 0x11a4;
static const Word csWaitForCallback = 0x11a5;
static const Word csProjected = 0x11a6;
static const Word csStartAuthentication = 0x11a7;
static const Word csCallbackComplete = 0x11a8;
static const Word csLogonNetwork = 0x11a9;
static const Word csSubEntryConnected = 0x11aa;
static const Word csSubEntryDisconnected = 0x11ab;
static const Word csRasInteractive = 0x11c6;
static const Word csRasRetryAuthentication = 0x11c7;
static const Word csRasCallbackSetByCaller = 0x11c8;
static const Word csRasPasswordExpired = 0x11c9;
static const Word csRasDeviceConnected = 0x11f7;
static const Word csRasBaseEnd = 0x11ab;
static const Word csRasPaused = 0x1000;
static const Word csInteractive = 0x1000;
static const Word csRetryAuthentication = 0x1001;
static const Word csCallbackSetByCaller = 0x1002;
static const Word csPasswordExpired = 0x1003;
static const Word csRasPausedEnd = 0x1003;
static const Word csRasConnected = 0x2000;
static const Word csRasDisconnected = 0x2001;
static const Word psOK = 0x125c;
static const Word psProtocolHandshake = 0x125d;
static const Word psInvalidDate = 0x125e;
static const Word psFileRejected = 0x125f;
static const Word psFileRenamed = 0x1260;
static const Word psSkipFile = 0x1261;
static const Word psFileDoesntExist = 0x1262;
static const Word psCantWriteFile = 0x1263;
static const Word psTimeout = 0x1264;
static const Word psBlockCheckError = 0x1265;
static const Word psLongPacket = 0x1266;
static const Word psDuplicateBlock = 0x1267;
static const Word psProtocolError = 0x1268;
static const Word psCancelRequested = 0x1269;
static const Word psEndFile = 0x126a;
static const Word psResumeBad = 0x126b;
static const Word psSequenceError = 0x126c;
static const Word psAbortNoCarrier = 0x126d;
static const Word psAbort = 0x127a;
static const Word psGotCrcE = 0x126e;
static const Word psGotCrcG = 0x126f;
static const Word psGotCrcW = 0x1270;
static const Word psGotCrcQ = 0x1271;
static const Word psTryResume = 0x1272;
static const Word psHostResume = 0x1273;
static const Word psWaitAck = 0x1274;
static const Word psNoHeader = 0x1275;
static const Word psGotHeader = 0x1276;
static const Word psGotData = 0x1277;
static const Word psNoData = 0x1278;
static const Word fpInitModem = 0x12c1;
static const Word fpDialing = 0x12c2;
static const Word fpBusyWait = 0x12c3;
static const Word fpSendPage = 0x12c4;
static const Word fpSendPageStatus = 0x12c5;
static const Word fpPageError = 0x12c6;
static const Word fpPageOK = 0x12c7;
static const Word fpConnecting = 0x12c8;
static const Word fpWaiting = 0x12d4;
static const Word fpNoConnect = 0x12d5;
static const Word fpAnswer = 0x12d6;
static const Word fpIncoming = 0x12d7;
static const Word fpGetPage = 0x12d8;
static const Word fpGetPageResult = 0x12d9;
static const Word fpCheckMorePages = 0x12da;
static const Word fpGetHangup = 0x12db;
static const Word fpGotHangup = 0x12dc;
static const Word fpSwitchModes = 0x12de;
static const Word fpMonitorEnabled = 0x12df;
static const Word fpMonitorDisabled = 0x12e0;
static const Word fpSessionParams = 0x12e8;
static const Word fpGotRemoteID = 0x12e9;
static const Word fpCancel = 0x12ea;
static const Word fpFinished = 0x12eb;
static const short ecNoMoreTriggers = 0xffffec77;
static const short ecTriggerTooLong = 0xffffec76;
static const short ecBadTriggerHandle = 0xffffec75;
static const short ecStartStringEmpty = 0xffffea83;
static const short ecPacketTooSmall = 0xffffea82;
static const short ecNoEndCharCount = 0xffffea81;
static const short ecEmptyEndString = 0xffffea80;
static const short ecZeroSizePacket = 0xffffea7f;
static const short ecPacketTooLong = 0xffffea7e;
static const short ecBadFileList = 0xffffe88f;
static const short ecNoSearchMask = 0xffffe88e;
static const short ecNoMatchingFiles = 0xffffe88d;
static const short ecDirNotFound = 0xffffe88c;
static const short ecCancelRequested = 0xffffe88b;
static const short ecTimeout = 0xffffe88a;
static const short ecProtocolError = 0xffffe889;
static const short ecTooManyErrors = 0xffffe888;
static const short ecSequenceError = 0xffffe887;
static const short ecNoFilename = 0xffffe886;
static const short ecFileRejected = 0xffffe885;
static const short ecCantWriteFile = 0xffffe884;
static const short ecTableFull = 0xffffe883;
static const short ecAbortNoCarrier = 0xffffe882;
static const short ecBadProtocolFunction = 0xffffe881;
static const short ecProtocolAbort = 0xffffe880;
static const short ecKeyTooLong = 0xffffe4a7;
static const short ecDataTooLarge = 0xffffe4a6;
static const short ecNoFieldsDefined = 0xffffe4a5;
static const short ecIniWrite = 0xffffe4a4;
static const short ecIniRead = 0xffffe4a3;
static const short ecNoIndexKey = 0xffffe4a2;
static const short ecRecordExists = 0xffffe4a1;
static const short ecRecordNotFound = 0xffffe4a0;
static const short ecMustHaveIdxVal = 0xffffe49f;
static const short ecDatabaseFull = 0xffffe49e;
static const short ecDatabaseEmpty = 0xffffe49d;
static const short ecDatabaseNotPrepared = 0xffffe49c;
static const short ecBadFieldList = 0xffffe49b;
static const short ecBadFieldForIndex = 0xffffe49a;
static const short ecNoStateMachine = 0xffffe2b4;
static const short ecNoStartState = 0xffffe2b3;
static const short ecNoSapiEngine = 0xffffe2b2;
static const short ecFaxBadFormat = 0xffffe0bf;
static const short ecBadGraphicsFormat = 0xffffe0be;
static const short ecConvertAbort = 0xffffe0bd;
static const short ecUnpackAbort = 0xffffe0bc;
static const short ecCantMakeBitmap = 0xffffe0bb;
static const short ecNoImageLoaded = 0xffffe08e;
static const short ecNoImageBlockMarked = 0xffffe08d;
static const short ecFontFileNotFound = 0xffffe08c;
static const short ecInvalidPageNumber = 0xffffe08b;
static const short ecBmpTooBig = 0xffffe08a;
static const short ecEnhFontTooBig = 0xffffe089;
static const short ecFaxBadMachine = 0xffffe084;
static const short ecFaxBadModemResult = 0xffffe083;
static const short ecFaxTrainError = 0xffffe082;
static const short ecFaxInitError = 0xffffe081;
static const short ecFaxBusy = 0xffffe080;
static const short ecFaxVoiceCall = 0xffffe07f;
static const short ecFaxDataCall = 0xffffe07e;
static const short ecFaxNoDialTone = 0xffffe07d;
static const short ecFaxNoCarrier = 0xffffe07c;
static const short ecFaxSessionError = 0xffffe07b;
static const short ecFaxPageError = 0xffffe07a;
static const short ecFaxGDIPrintError = 0xffffe079;
static const short ecFaxMixedResolution = 0xffffe078;
static const short ecFaxConverterInitFail = 0xffffe077;
static const short ecNoAnswer = 0xffffe076;
static const short ecAlreadyMonitored = 0xffffe075;
static const short ecFaxMCFNoAnswer = 0xffffe074;
static const short ecUniAlreadyInstalled = 0xffffe070;
static const short ecUniCannotGetSysDir = 0xffffe06f;
static const short ecUniCannotGetWinDir = 0xffffe06e;
static const short ecUniUnknownLayout = 0xffffe06d;
static const short ecUniCannotInstallFile = 0xffffe06b;
static const short ecRasDDNotInstalled = 0xffffe06a;
static const short ecDrvCopyError = 0xffffe069;
static const short ecCannotAddPrinter = 0xffffe068;
static const short ecDrvBadResources = 0xffffe067;
static const short ecDrvDriverNotFound = 0xffffe066;
static const short ecUniCannotGetPrinterDriverDir = 0xffffe065;
static const short ecInstallDriverFailed = 0xffffe064;
static const short ecSMSBusy = 0xffffe05c;
static const short ecSMSTimedOut = 0xffffe05b;
static const short ecSMSTooLong = 0xffffe05a;
static const short ecSMSUnknownStatus = 0xffffe059;
static const short ecSMSInvalidNumber = 0xffffe036;
static const short ecMEFailure = 0xffffdf94;
static const short ecServiceRes = 0xffffdf93;
static const short ecBadOperation = 0xffffdf92;
static const short ecUnsupported = 0xffffdf91;
static const short ecInvalidPDU = 0xffffdf90;
static const short ecInvalidText = 0xffffdf8f;
static const short ecSIMInsert = 0xffffdf8a;
static const short ecSIMPin = 0xffffdf89;
static const short ecSIMPH = 0xffffdf88;
static const short ecSIMFailure = 0xffffdf87;
static const short ecSIMBusy = 0xffffdf86;
static const short ecSIMWrong = 0xffffdf85;
static const short ecSIMPUK = 0xffffdf84;
static const short ecSIMPIN2 = 0xffffdf83;
static const short ecSIMPUK2 = 0xffffdf82;
static const short ecMemFail = 0xffffdf80;
static const short ecInvalidMemIndex = 0xffffdf7f;
static const short ecMemFull = 0xffffdf7e;
static const short ecSMSCAddUnknown = 0xffffdf76;
static const short ecNoNetwork = 0xffffdf75;
static const short ecNetworkTimeout = 0xffffdf74;
static const short ecCNMAAck = 0xffffdf6c;
static const short ecUnknown = 0xffffdecc;
static const Word ecADWSERROR = 0x2329;
static const Word ecADWSLOADERROR = 0x232a;
static const Word ecADWSVERSIONERROR = 0x232b;
static const Word ecADWSNOTINIT = 0x232c;
static const Word ecADWSINVPORT = 0x232d;
static const Word ecADWSCANTCHANGE = 0x232e;
static const Word ecADWSCANTRESOLVE = 0x232f;
static const Word wsaBaseErr = 0x2710;
static const Word wsaEIntr = 0x2714;
static const Word wsaEBadF = 0x2719;
static const Word wsaEAcces = 0x271d;
static const Word wsaEFault = 0x271e;
static const Word wsaEInVal = 0x2726;
static const Word wsaEMFile = 0x2728;
static const Word wsaEWouldBlock = 0x2733;
static const Word wsaEInProgress = 0x2734;
static const Word wsaEAlReady = 0x2735;
static const Word wsaENotSock = 0x2736;
static const Word wsaEDestAddrReq = 0x2737;
static const Word wsaEMsgSize = 0x2738;
static const Word wsaEPrototype = 0x2739;
static const Word wsaENoProtoOpt = 0x273a;
static const Word wsaEProtoNoSupport = 0x273b;
static const Word wsaESocktNoSupport = 0x273c;
static const Word wsaEOpNotSupp = 0x273d;
static const Word wsaEPfNoSupport = 0x273e;
static const Word wsaEAfNoSupport = 0x273f;
static const Word wsaEAddrInUse = 0x2740;
static const Word wsaEAddrNotAvail = 0x2741;
static const Word wsaENetDown = 0x2742;
static const Word wsaENetUnreach = 0x2743;
static const Word wsaENetReset = 0x2744;
static const Word wsaEConnAborted = 0x2745;
static const Word wsaEConnReset = 0x2746;
static const Word wsaENoBufs = 0x2747;
static const Word wsaEIsConn = 0x2748;
static const Word wsaENotConn = 0x2749;
static const Word wsaEShutDown = 0x274a;
static const Word wsaETooManyRefs = 0x274b;
static const Word wsaETimedOut = 0x274c;
static const Word wsaEConnRefused = 0x274d;
static const Word wsaELoop = 0x274e;
static const Word wsaENameTooLong = 0x274f;
static const Word wsaEHostDown = 0x2750;
static const Word wsaEHostUnreach = 0x2751;
static const Word wsaENotEmpty = 0x2752;
static const Word wsaEProcLim = 0x2753;
static const Word wsaEUsers = 0x2754;
static const Word wsaEDQuot = 0x2755;
static const Word wsaEStale = 0x2756;
static const Word wsaERemote = 0x2757;
static const Word wsaEDiscOn = 0x2775;
static const Word wsaSysNotReady = 0x276b;
static const Word wsaVerNotSupported = 0x276c;
static const Word wsaNotInitialised = 0x276d;
static const Word wsaHost_Not_Found = 0x2af9;
static const Word Host_Not_Found = 0x2af9;
static const Word wsaTry_Again = 0x2afa;
static const Word Try_Again = 0x2afa;
static const Word wsaNo_Recovery = 0x2afb;
static const Word No_Recovery = 0x2afb;
static const Word wsaNo_Data = 0x2afc;
static const Word No_Data = 0x2afc;
static const Word wsaNo_Address = 0x2afc;
static const Word No_Address = 0x2afc;
static const short ecAllocated = 0xffffca17;
static const short ecBadDeviceID = 0xffffca16;
static const short ecBearerModeUnavail = 0xffffca15;
static const short ecCallUnavail = 0xffffca13;
static const short ecCompletionOverrun = 0xffffca12;
static const short ecConferenceFull = 0xffffca11;
static const short ecDialBilling = 0xffffca10;
static const short ecDialDialtone = 0xffffca0f;
static const short ecDialPrompt = 0xffffca0e;
static const short ecDialQuiet = 0xffffca0d;
static const short ecIncompatibleApiVersion = 0xffffca0c;
static const short ecIncompatibleExtVersion = 0xffffca0b;
static const short ecIniFileCorrupt = 0xffffca0a;
static const short ecInUse = 0xffffca09;
static const short ecInvalAddress = 0xffffca08;
static const short ecInvalAddressID = 0xffffca07;
static const short ecInvalAddressMode = 0xffffca06;
static const short ecInvalAddressState = 0xffffca05;
static const short ecInvalAppHandle = 0xffffca04;
static const short ecInvalAppName = 0xffffca03;
static const short ecInvalBearerMode = 0xffffca02;
static const short ecInvalCallComplMode = 0xffffca01;
static const short ecInvalCallHandle = 0xffffca00;
static const short ecInvalCallParams = 0xffffc9ff;
static const short ecInvalCallPrivilege = 0xffffc9fe;
static const short ecInvalCallSelect = 0xffffc9fd;
static const short ecInvalCallState = 0xffffc9fc;
static const short ecInvalCallStatelist = 0xffffc9fb;
static const short ecInvalCard = 0xffffc9fa;
static const short ecInvalCompletionID = 0xffffc9f9;
static const short ecInvalConfCallHandle = 0xffffc9f8;
static const short ecInvalConsultCallHandle = 0xffffc9f7;
static const short ecInvalCountryCode = 0xffffc9f6;
static const short ecInvalDeviceClass = 0xffffc9f5;
static const short ecInvalDeviceHandle = 0xffffc9f4;
static const short ecInvalDialParams = 0xffffc9f3;
static const short ecInvalDigitList = 0xffffc9f2;
static const short ecInvalDigitMode = 0xffffc9f1;
static const short ecInvalDigits = 0xffffc9f0;
static const short ecInvalExtVersion = 0xffffc9ef;
static const short ecInvalGroupID = 0xffffc9ee;
static const short ecInvalLineHandle = 0xffffc9ed;
static const short ecInvalLineState = 0xffffc9ec;
static const short ecInvalLocation = 0xffffc9eb;
static const short ecInvalMediaList = 0xffffc9ea;
static const short ecInvalMediaMode = 0xffffc9e9;
static const short ecInvalMessageID = 0xffffc9e8;
static const short ecInvalParam = 0xffffc9e6;
static const short ecInvalParkID = 0xffffc9e5;
static const short ecInvalParkMode = 0xffffc9e4;
static const short ecInvalPointer = 0xffffc9e3;
static const short ecInvalPrivSelect = 0xffffc9e2;
static const short ecInvalRate = 0xffffc9e1;
static const short ecInvalRequestMode = 0xffffc9e0;
static const short ecInvalTerminalID = 0xffffc9df;
static const short ecInvalTerminalMode = 0xffffc9de;
static const short ecInvalTimeout = 0xffffc9dd;
static const short ecInvalTone = 0xffffc9dc;
static const short ecInvalToneList = 0xffffc9db;
static const short ecInvalToneMode = 0xffffc9da;
static const short ecInvalTransferMode = 0xffffc9d9;
static const short ecLineMapperFailed = 0xffffc9d8;
static const short ecNoConference = 0xffffc9d7;
static const short ecNoDevice = 0xffffc9d6;
static const short ecNoDriver = 0xffffc9d5;
static const short ecNoMem = 0xffffc9d4;
static const short ecNoRequest = 0xffffc9d3;
static const short ecNotOwner = 0xffffc9d2;
static const short ecNotRegistered = 0xffffc9d1;
static const short ecOperationFailed = 0xffffc9d0;
static const short ecOperationUnavail = 0xffffc9cf;
static const short ecRateUnavail = 0xffffc9ce;
static const short ecResourceUnavail = 0xffffc9cd;
static const short ecRequestOverrun = 0xffffc9cc;
static const short ecStructureTooSmall = 0xffffc9cb;
static const short ecTargetNotFound = 0xffffc9ca;
static const short ecTargetSelf = 0xffffc9c9;
static const short ecUninitialized = 0xffffc9c8;
static const short ecUserUserInfoTooBig = 0xffffc9c7;
static const short ecReinit = 0xffffc9c6;
static const short ecAddressBlocked = 0xffffc9c5;
static const short ecBillingRejected = 0xffffc9c4;
static const short ecInvalFeature = 0xffffc9c3;
static const short ecNoMultipleInstance = 0xffffc9c2;
static const short ecTapiBusy = 0xffffc998;
static const short ecTapiNotSet = 0xffffc997;
static const short ecTapiNoSelect = 0xffffc996;
static const short ecTapiLoadFail = 0xffffc995;
static const short ecTapiGetAddrFail = 0xffffc994;
static const short ecTapiUnexpected = 0xffffc992;
static const short ecTapiVoiceNotSupported = 0xffffc991;
static const short ecTapiWaveFail = 0xffffc990;
static const short ecTapiCIDBlocked = 0xffffc98f;
static const short ecTapiCIDOutOfArea = 0xffffc98e;
static const short ecTapiWaveFormatError = 0xffffc98d;
static const short ecTapiWaveReadError = 0xffffc98c;
static const short ecTapiWaveBadFormat = 0xffffc98b;
static const short ecTapiTranslateFail = 0xffffc98a;
static const short ecTapiWaveDeviceInUse = 0xffffc989;
static const short ecTapiWaveFileExists = 0xffffc988;
static const short ecTapiWaveNoData = 0xffffc987;
static const short ecVoIPNotSupported = 0xffffc982;
static const short ecVoIPCallBusy = 0xffffc981;
static const short ecVoIPBadAddress = 0xffffc980;
static const short ecVoIPNoAnswer = 0xffffc97f;
static const short ecVoIPCancelled = 0xffffc97e;
static const short ecVoIPRejected = 0xffffc97d;
static const short ecVoIPFailed = 0xffffc97c;
static const short ecVoIPTapi3NotInstalled = 0xffffc97b;
static const short ecVoIPH323NotFound = 0xffffc97a;
static const short ecVoIPTapi3EventFailure = 0xffffc979;
static const short ecRasLoadFail = 0xffffc964;
static const char cNul = '\x0';
static const char cSoh = '\x1';
static const char cStx = '\x2';
static const char cEtx = '\x3';
static const char cEot = '\x4';
static const char cEnq = '\x5';
static const char cAck = '\x6';
static const char cBel = '\x7';
static const char cBS = '\x8';
static const char cTab = '\x9';
static const char cLF = '\xa';
static const char cVT = '\xb';
static const char cFF = '\xc';
static const char cCR = '\xd';
static const char cSO = '\xe';
static const char cSI = '\xf';
static const char cDle = '\x10';
static const char cDC1 = '\x11';
static const char cXon = '\x11';
static const char cDC2 = '\x12';
static const char cDC3 = '\x13';
static const char cXoff = '\x13';
static const char cDC4 = '\x14';
static const char cNak = '\x15';
static const char cSyn = '\x16';
static const char cEtb = '\x17';
static const char cCan = '\x18';
static const char cEM = '\x19';
static const char cSub = '\x1a';
static const char cEsc = '\x1b';
static const char cFS = '\x1c';
static const char cGS = '\x1d';
static const char cRS = '\x1e';
static const char cUS = '\x1f';
static const Shortint poUseEventWord = 0x4;
static const Shortint ipAssertDTR = 0x1;
static const Shortint ipAssertRTS = 0x2;
static const Shortint ipAutoDTR = 0x10;
static const Shortint ipAutoRTS = 0x20;
static const Shortint hfUseDTR = 0x1;
static const Shortint hfUseRTS = 0x2;
static const Shortint hfRequireDSR = 0x4;
static const Shortint hfRequireCTS = 0x8;
static const Shortint sfTransmitFlow = 0x1;
static const Shortint sfReceiveFlow = 0x2;
static const Shortint dcb_Binary = 0x1;
static const Shortint dcb_Parity = 0x2;
static const Shortint dcb_OutxCTSFlow = 0x4;
static const Shortint dcb_OutxDSRFlow = 0x8;
static const Shortint dcb_DTRBit1 = 0x10;
static const Shortint dcb_DTRBit2 = 0x20;
static const Shortint dcb_DsrSensitivity = 0x40;
static const Byte dcb_TxContinueOnXoff = 0x80;
static const Word dcb_OutX = 0x100;
static const Word dcb_InX = 0x200;
static const Word dcb_ErrorChar = 0x400;
static const Word dcb_Null = 0x800;
static const Word dcb_RTSBit1 = 0x1000;
static const Word dcb_RTSBit2 = 0x2000;
static const Word dcb_AbortOnError = 0x4000;
static const Shortint dcb_DTR_CONTROL_ENABLE = 0x10;
static const Shortint dcb_DTR_CONTROL_HANDSHAKE = 0x20;
static const Word dcb_RTS_CONTROL_ENABLE = 0x1000;
static const Word dcb_RTS_CONTROL_HANDSHAKE = 0x2000;
static const Word dcb_RTS_CONTROL_TOGGLE = 0x3000;
static const Shortint fsOff = 0x1;
static const Shortint fsOn = 0x2;
static const Shortint fsDsrHold = 0x3;
static const Shortint fsCtsHold = 0x4;
static const Shortint fsDcdHold = 0x5;
static const Shortint fsXOutHold = 0x6;
static const Shortint fsXInHold = 0x7;
static const Shortint fsXBothHold = 0x8;
static const Shortint eNone = 0x0;
static const Shortint eChar = 0x1;
static const Shortint eGotoXY = 0x2;
static const Shortint eUp = 0x3;
static const Shortint eDown = 0x4;
static const Shortint eRight = 0x5;
static const Shortint eLeft = 0x6;
static const Shortint eClearBelow = 0x7;
static const Shortint eClearAbove = 0x8;
static const Shortint eClearScreen = 0x9;
static const Shortint eClearEndofLine = 0xa;
static const Shortint eClearStartOfLine = 0xb;
static const Shortint eClearLine = 0xc;
static const Shortint eSetMode = 0xd;
static const Shortint eSetBackground = 0xe;
static const Shortint eSetForeground = 0xf;
static const Shortint eSetAttribute = 0x10;
static const Shortint eSaveCursorPos = 0x11;
static const Shortint eRestoreCursorPos = 0x12;
static const Shortint eDeviceStatusReport = 0x13;
static const Shortint eString = 0x14;
static const Shortint eHT = 0x15;
static const Byte eError = 0xff;
static const Shortint eAPC = 0x1e;
static const Shortint eCBT = 0x1f;
static const Shortint eCCH = 0x20;
static const Shortint eCHA = 0x21;
static const Shortint eCHT = 0x22;
static const Shortint eCNL = 0x23;
static const Shortint eCPL = 0x24;
static const Shortint eCPR = 0x25;
static const Shortint eCRM = 0x26;
static const Shortint eCTC = 0x27;
static const Shortint eCUB = 0x6;
static const Shortint eCUD = 0x4;
static const Shortint eCUF = 0x5;
static const Shortint eCUP = 0x2;
static const Shortint eCUU = 0x3;
static const Shortint eCVT = 0x28;
static const Shortint eDA = 0x29;
static const Shortint eDAQ = 0x2a;
static const Shortint eDCH = 0x2b;
static const Shortint eDCS = 0x2c;
static const Shortint eDL = 0x2d;
static const Shortint eDMI = 0x2e;
static const Shortint eDSR = 0x13;
static const Shortint eEA = 0x2f;
static const Shortint eEBM = 0x30;
static const Shortint eECH = 0x31;
static const Shortint eED = 0x32;
static const Shortint eEF = 0x33;
static const Shortint eEL = 0x34;
static const Shortint eEMI = 0x35;
static const Shortint eEPA = 0x36;
static const Shortint eERM = 0x37;
static const Shortint eESA = 0x38;
static const Shortint eFEAM = 0x39;
static const Shortint eFETM = 0x3a;
static const Shortint eFNT = 0x3b;
static const Shortint eGATM = 0x3c;
static const Shortint eGSM = 0x3d;
static const Shortint eGSS = 0x3e;
static const Shortint eHEM = 0x3f;
static const Shortint eHPA = 0x21;
static const Shortint eHPR = 0x5;
static const Shortint eHTJ = 0x40;
static const Shortint eHTS = 0x41;
static const Shortint eHVP = 0x2;
static const Shortint eICH = 0x42;
static const Shortint eIL = 0x43;
static const Shortint eIND = 0x4;
static const Shortint eINT = 0x44;
static const Shortint eIRM = 0x45;
static const Shortint eJFY = 0x46;
static const Shortint eKAM = 0x47;
static const Shortint eLNM = 0x48;
static const Shortint eMATM = 0x49;
static const Shortint eMC = 0x4a;
static const Shortint eMW = 0x4b;
static const Shortint eNEL = 0x4c;
static const Shortint eNP = 0x4d;
static const Shortint eOSC = 0x4e;
static const Shortint ePLD = 0x4f;
static const Shortint ePLU = 0x50;
static const Shortint ePM = 0x51;
static const Shortint ePP = 0x52;
static const Shortint ePU1 = 0x53;
static const Shortint ePU2 = 0x54;
static const Shortint ePUM = 0x55;
static const Shortint eQUAD = 0x56;
static const Shortint eREP = 0x57;
static const Shortint eRI = 0x58;
static const Shortint eRIS = 0x59;
static const Shortint eRM = 0x5a;
static const Shortint eSATM = 0x5b;
static const Shortint eSD = 0x5c;
static const Shortint eSEM = 0x5d;
static const Shortint eSGR = 0x10;
static const Shortint eSL = 0x5e;
static const Shortint eSM = 0xd;
static const Shortint eSPA = 0x5f;
static const Shortint eSPI = 0x60;
static const Shortint eSR = 0x61;
static const Shortint eSRM = 0x62;
static const Shortint eSRTM = 0x63;
static const Shortint eSS2 = 0x64;
static const Shortint eSS3 = 0x65;
static const Shortint eSSA = 0x66;
static const Shortint eST = 0x67;
static const Shortint eSTS = 0x68;
static const Shortint eSU = 0x69;
static const Shortint eTBC = 0x6a;
static const Shortint eTSM = 0x6b;
static const Shortint eTSS = 0x6c;
static const Shortint eTTM = 0x6d;
static const Shortint eVEM = 0x6e;
static const Shortint eVPA = 0x6f;
static const Shortint eVPR = 0x4;
static const Shortint eVTS = 0x70;
static const Shortint eDECSTBM = 0x71;
static const Shortint eENQ = 0x72;
static const Shortint eBEL = 0x73;
static const Shortint eBS = 0x74;
static const Shortint eLF = 0x75;
static const Shortint eCR = 0x76;
static const Shortint eSO = 0x77;
static const Shortint eSI = 0x78;
static const Shortint eIND2 = 0x79;
static const Shortint eDECALN = 0x7a;
static const Shortint eDECDHL = 0x7b;
static const Shortint eDECDWL = 0x7c;
static const Shortint eDECLL = 0x7d;
static const Shortint eDECREQTPARM = 0x7e;
static const Shortint eDECSWL = 0x7f;
static const Byte eDECTST = 0x80;
static const Byte eDECSCS = 0x81;
static const Shortint eattrBlink = 0x1;
static const Shortint eattrInverse = 0x2;
static const Shortint eattrIntense = 0x4;
static const Shortint eattrInvisible = 0x8;
static const Shortint eattrUnderline = 0x10;
static const Shortint emBlack = 0x0;
static const Shortint emRed = 0x1;
static const Shortint emGreen = 0x2;
static const Shortint emYellow = 0x3;
static const Shortint emBlue = 0x4;
static const Shortint emMagenta = 0x5;
static const Shortint emCyan = 0x6;
static const Shortint emWhite = 0x7;
static const Shortint emBlackBold = 0x8;
static const Shortint emRedBold = 0x9;
static const Shortint emGreenBold = 0xa;
static const Shortint emYellowBold = 0xb;
static const Shortint emBlueBold = 0xc;
static const Shortint emMagentaBold = 0xd;
static const Shortint emCyanBold = 0xe;
static const Shortint emWhiteBold = 0xf;
static const Shortint teMapVT100 = 0x1;
static const Shortint MaxParams = 0x5;
static const Shortint MaxQueue = 0x14;
static const Shortint MaxOther = 0xb;
static const Shortint MaxParamLength = 0x5;
static const Shortint KeyMappingLen = 0x14;
static const Shortint gwl_Terminal = 0x0;
static const Shortint tws_WantTab = 0x1;
static const Shortint tws_IntHeight = 0x2;
static const Shortint tws_IntWidth = 0x4;
static const Shortint tws_AutoHScroll = 0x8;
static const Shortint tws_AutoVScroll = 0x10;
static const Word MaxDBRecs = 0x3e7;
static const Shortint MaxNameLen = 0x15;
static const Shortint MaxIndexLen = 0x1f;
static const char NonValue = '\x23';
#define dbIndex "Index"
#define dbDefaults "Defaults"
#define dbNumEntries "_Entries"
#define dbBogus "None"
static const Shortint ApdMaxTags = 0x5;
static const char ApdTagSepChar = '\x2c';
static const Shortint ApdModemNameLen = 0x1f;
static const Shortint ApdCmdLen = 0x29;
static const Shortint ApdRspLen = 0x15;
static const Shortint ApdTagLen = 0x15;
static const Shortint ApdTagProfLen = 0x69;
static const Shortint ApdBoolLen = 0x5;
static const Shortint ApdBaudLen = 0x7;
static const Byte ApdConfigLen = 0xff;
static const Shortint ksControl = 0x2;
static const Shortint ksAlt = 0x4;
static const Shortint ksShift = 0x8;
static const Shortint tsCapital = 0x2;
static const Shortint tsNumlock = 0x4;
static const Shortint tsScroll = 0x8;
static const Shortint ApdKeyMapNameLen = 0x1e;
static const Shortint ApdMaxKeyMaps = 0x64;
#define ApdKeyIndexName "EMULATOR"
static const Shortint ApdKeyIndexMaxLen = 0x78;
static const Shortint apIncludeDirectory = 0x1;
static const Shortint apHonorDirectory = 0x2;
static const Shortint apRTSLowForWrite = 0x4;
static const Shortint apAbortNoCarrier = 0x8;
static const Shortint apKermitLongPackets = 0x10;
static const Shortint apKermitSWC = 0x20;
static const Shortint apZmodem8K = 0x40;
static const Byte apBP2KTransmit = 0x80;
static const Word apAsciiSuppressCtrlZ = 0x100;
static const Shortint DefProtocolOptions = 0x0;
static const Shortint BadProtocolOptions = 0x70;
static const Shortint bcNone = 0x0;
static const Shortint bcChecksum1 = 0x1;
static const Shortint bcChecksum2 = 0x2;
static const Shortint bcCrc16 = 0x3;
static const Shortint bcCrc32 = 0x4;
static const Shortint bcCrcK = 0x5;
#define bcsNone "No check"
#define bcsChecksum1 "Checksum"
#define bcsChecksum2 "Checksum2"
#define bcsCrc16 "Crc16"
#define bcsCrc32 "Crc32"
#define bcsCrck "CrcKermit"
static const Shortint NoProtocol = 0x0;
static const Shortint Xmodem = 0x1;
static const Shortint XmodemCRC = 0x2;
static const Shortint Xmodem1K = 0x3;
static const Shortint Xmodem1KG = 0x4;
static const Shortint Ymodem = 0x5;
static const Shortint YmodemG = 0x6;
static const Shortint Zmodem = 0x7;
static const Shortint Kermit = 0x8;
static const Shortint Ascii = 0x9;
static const Shortint BPlus = 0xa;
static const Shortint MaxAttentionLen = 0x20;
static const Shortint zfWriteNewerLonger = 0x1;
static const Shortint zfWriteCrc = 0x2;
static const Shortint zfWriteAppend = 0x3;
static const Shortint zfWriteClobber = 0x4;
static const Shortint zfWriteNewer = 0x5;
static const Shortint zfWriteDifferent = 0x6;
static const Shortint zfWriteProtect = 0x7;
extern PACKAGE char ProtocolString[11][10];
static const Shortint rw1728 = 0x1;
static const Shortint rw2048 = 0x2;
static const Word StandardWidth = 0x6c0;
static const Word WideWidth = 0x800;
static const Shortint ffHighRes = 0x1;
static const Shortint ffHighWidth = 0x2;
static const Shortint ffLengthWords = 0x4;
static const Shortint fcDoubleWidth = 0x1;
static const Shortint fcHalfHeight = 0x2;
static const Shortint fcCenterImage = 0x4;
static const Shortint fcYield = 0x8;
static const Shortint fcYieldOften = 0x10;
static const Shortint csStarting = 0x1;
static const Shortint csEnding = 0x2;
static const Shortint SmallFont = 0x10;
static const Shortint StandardFont = 0x30;
static const Word MaxTreeRec = 0x132;
static const Word MaxData = 0x1000;
static const Byte MaxLineLen = 0x90;
static const Shortint MaxCodeTable = 0x3f;
static const Shortint MaxMUCodeTable = 0x27;
#define DefTextExt "TXT"
#define DefTiffExt "TIF"
#define DefPcxExt "PCX"
#define DefDcxExt "DCX"
#define DefBmpExt "BMP"
#define DefApfExt "APF"
extern PACKAGE char DefAPFSig[6];
extern PACKAGE int Xpc_BracketAngleLeft[1];
extern PACKAGE int Xpc_BracketAngleRight[1];
extern PACKAGE int Xpc_BracketSquareLeft[1];
extern PACKAGE int Xpc_BracketSquareRight[1];
extern PACKAGE int Xpc_CDATAStart[6];
extern PACKAGE int Xpc_CharacterRef[1];
extern PACKAGE int Xpc_CharacterRefHex[1];
extern PACKAGE int Xpc_CommentEnd[3];
extern PACKAGE int Xpc_CommentStart[4];
extern PACKAGE int Xpc_ConditionalEnd[3];
extern PACKAGE int Xpc_ConditionalIgnore[6];
extern PACKAGE int Xpc_ConditionalInclude[7];
extern PACKAGE int Xpc_ConditionalStart[3];
extern PACKAGE int Xpc_Dash[1];
extern PACKAGE int Xpc_DTDAttFixed[5];
extern PACKAGE int Xpc_DTDAttImplied[7];
extern PACKAGE int Xpc_DTDAttlist[9];
extern PACKAGE int Xpc_DTDAttRequired[8];
extern PACKAGE int Xpc_DTDDocType[9];
extern PACKAGE int Xpc_DTDElement[9];
extern PACKAGE int Xpc_DTDElementAny[3];
extern PACKAGE int Xpc_DTDElementCharData[7];
extern PACKAGE int Xpc_DTDElementEmpty[5];
extern PACKAGE int Xpc_DTDEntity[8];
extern PACKAGE int Xpc_DTDNotation[10];
extern PACKAGE int Xpc_Encoding[8];
extern PACKAGE int Xpc_Equation[1];
extern PACKAGE int Xpc_ExternalPublic[6];
extern PACKAGE int Xpc_ExternalSystem[6];
extern PACKAGE int Xpc_GenParsedEntityEnd[1];
extern PACKAGE int Xpc_ListOperator[1];
extern PACKAGE int Xpc_MixedEnd[2];
extern PACKAGE int Xpc_OneOrMoreOpr[1];
extern PACKAGE int Xpc_ParamEntity[1];
extern PACKAGE int Xpc_ParenLeft[1];
extern PACKAGE int Xpc_ParenRight[1];
extern PACKAGE int Xpc_ProcessInstrEnd[2];
extern PACKAGE int Xpc_ProcessInstrStart[2];
extern PACKAGE int Xpc_QuoteDouble[1];
extern PACKAGE int Xpc_QuoteSingle[1];
extern PACKAGE int Xpc_Standalone[10];
extern PACKAGE int Xpc_UnparsedEntity[5];
extern PACKAGE int Xpc_Version[7];
static const Shortint LIT_CHAR_REF = 0x1;
static const Shortint LIT_ENTITY_REF = 0x2;
static const Shortint LIT_PE_REF = 0x4;
static const Shortint LIT_NORMALIZE = 0x8;
static const Shortint CONTEXT_NONE = 0x0;
static const Shortint CONTEXT_DTD = 0x1;
static const Shortint CONTEXT_ENTITYVALUE = 0x2;
static const Shortint CONTEXT_ATTRIBUTEVALUE = 0x3;
static const Shortint CONTENT_UNDECLARED = 0x0;
static const Shortint CONTENT_ANY = 0x1;
static const Shortint CONTENT_EMPTY = 0x2;
static const Shortint CONTENT_MIXED = 0x3;
static const Shortint CONTENT_ELEMENTS = 0x4;
static const Shortint OCCURS_REQ_NOREPEAT = 0x0;
static const Shortint OCCURS_OPT_NOREPEAT = 0x1;
static const Shortint OCCURS_OPT_REPEAT = 0x2;
static const Shortint OCCURS_REQ_REPEAT = 0x3;
static const Shortint REL_OR = 0x0;
static const Shortint REL_AND = 0x1;
static const Shortint REL_NONE = 0x2;
static const Shortint ATTRIBUTE_UNDECLARED = 0x0;
static const Shortint ATTRIBUTE_CDATA = 0x1;
static const Shortint ATTRIBUTE_ID = 0x2;
static const Shortint ATTRIBUTE_IDREF = 0x3;
static const Shortint ATTRIBUTE_IDREFS = 0x4;
static const Shortint ATTRIBUTE_ENTITY = 0x5;
static const Shortint ATTRIBUTE_ENTITIES = 0x6;
static const Shortint ATTRIBUTE_NMTOKEN = 0x7;
static const Shortint ATTRIBUTE_NMTOKENS = 0x8;
static const Shortint ATTRIBUTE_ENUMERATED = 0x9;
static const Shortint ATTRIBUTE_NOTATION = 0xa;
static const Shortint ATTRIBUTE_DEFAULT_UNDECLARED = 0x0;
static const Shortint ATTRIBUTE_DEFAULT_SPECIFIED = 0x1;
static const Shortint ATTRIBUTE_DEFAULT_IMPLIED = 0x2;
static const Shortint ATTRIBUTE_DEFAULT_REQUIRED = 0x3;
static const Shortint ATTRIBUTE_DEFAULT_FIXED = 0x4;
static const Shortint ENTITY_UNDECLARED = 0x0;
static const Shortint ENTITY_INTERNAL = 0x1;
static const Shortint ENTITY_NDATA = 0x2;
static const Shortint ENTITY_TEXT = 0x3;
static const Shortint CONDITIONAL_INCLUDE = 0x0;
static const Shortint CONDITIONAL_IGNORE = 0x1;
static const Word LineBufferSize = 0x1000;
static const Shortint DMSize = 0x20;
static const Shortint upStarting = 0x1;
static const Shortint upEnding = 0x2;
static const Shortint usStarting = 0x1;
static const Shortint usEnding = 0x2;
static const Shortint ufYield = 0x1;
static const Shortint ufAutoDoubleHeight = 0x2;
static const Shortint ufAutoHalfWidth = 0x4;
static const Shortint ufAbort = 0x8;
static const Shortint DefUnpackOptions = 0x3;
static const unsigned BadUnpackOptions = 0x0;
static const unsigned RasterBufferPageSize = 0x400;
static const int DCXHeaderID = 0x3ade68b1;
static const Shortint gwl_Viewer = 0x0;
static const Shortint vws_DragDrop = 0x1;
static const int DefViewerBG = 0xffffff;
static const Shortint DefViewerFG = 0x0;
static const Shortint DefVScrollInc = 0x8;
static const Shortint DefHScrollInc = 0x8;
extern PACKAGE unsigned DefConnectAttempts;
extern PACKAGE int DefMaxRetries;
extern PACKAGE int DefStatusTimeout;
extern PACKAGE AnsiString DefNormalInit;
extern PACKAGE AnsiString DefBlindInit;
extern PACKAGE AnsiString DefNoDetectBusyInit;
extern PACKAGE AnsiString DefX1Init;
extern PACKAGE AnsiString DefTapiInit;
extern PACKAGE unsigned DefStatusBytes;
extern PACKAGE unsigned MaxBadPercent;
extern PACKAGE unsigned FlushWait;
extern PACKAGE unsigned FrameWait;
static const Shortint afAbortNoConnect = 0x1;
static const Shortint afExitOnError = 0x2;
static const Shortint afCASSubmitUseControl = 0x4;
static const Shortint afSoftwareFlow = 0x8;
extern PACKAGE unsigned DefFaxOptions;
static const unsigned BadFaxOptions = 0x0;
static const Shortint ftNone = 0x0;
static const Shortint ftClass12 = 0x1;
static const Shortint MaxTrigData = 0x15;
static const Shortint MaxDataPointers = 0x3;
static const Shortint TimerFreq = 0x32;
static const Shortint dpProtocol = 0x1;
static const Shortint dpFax = 0x2;
static const Shortint dpModem = 0x3;
static const Shortint MaxTraceCol = 0x4e;
static const int HighestTrace = 0x3d0900;
static const int MaxDLogQueueSize = 0xf42400;
extern PACKAGE unsigned QPFreq;
extern PACKAGE void __fastcall AssignFile(file &F, const AnsiString FileName)/* overload */;
extern PACKAGE void __fastcall AssignFile(TextFile &F, const AnsiString FileName)/* overload */;
extern PACKAGE void __fastcall Assign(file &F, const AnsiString FileName)/* overload */;
extern PACKAGE void __fastcall Assign(TextFile &F, const AnsiString FileName)/* overload */;
extern PACKAGE unsigned __fastcall MinWord(unsigned A, unsigned B);
extern PACKAGE BOOL __fastcall FlagIsSet(unsigned Flags, unsigned FlagMask);
extern PACKAGE void __fastcall ClearFlag(unsigned &Flags, unsigned FlagMask);
extern PACKAGE void __fastcall SetFlag(unsigned &Flags, unsigned FlagMask);
extern PACKAGE BOOL __fastcall ByteFlagIsSet(Byte Flags, Byte FlagMask);
extern PACKAGE void __fastcall ClearByteFlag(Byte &Flags, Byte FlagMask);
extern PACKAGE void __fastcall SetByteFlag(Byte &Flags, Byte FlagMask);
extern PACKAGE void * __fastcall AddWordToPtr(void * P, unsigned W);
extern PACKAGE int __fastcall SafeYield(void);
extern PACKAGE unsigned __fastcall AdTimeGetTime(void);
extern PACKAGE int __fastcall Ticks2Secs(int Ticks);
extern PACKAGE int __fastcall Secs2Ticks(int Secs);
extern PACKAGE int __fastcall MSecs2Ticks(int MSecs);
extern PACKAGE void __fastcall NewTimer(EventTimer &ET, int Ticks);
extern PACKAGE void __fastcall NewTimerSecs(EventTimer &ET, int Secs);
extern PACKAGE BOOL __fastcall TimerExpired(const EventTimer &ET);
extern PACKAGE int __fastcall ElapsedTime(const EventTimer &ET);
extern PACKAGE int __fastcall ElapsedTimeInSecs(const EventTimer &ET);
extern PACKAGE int __fastcall RemainingTime(const EventTimer &ET);
extern PACKAGE int __fastcall RemainingTimeInSecs(const EventTimer &ET);
extern PACKAGE int __fastcall DelayTicks(int Ticks, BOOL Yield);
extern PACKAGE char * __fastcall Long2StrZ(char * Dest, int L);
extern PACKAGE BOOL __fastcall Str2LongZ(char * S, int &I);
extern PACKAGE char * __fastcall JustPathnameZ(char * Dest, char * PathName);
extern PACKAGE char * __fastcall JustFilenameZ(char * Dest, char * PathName);
extern PACKAGE char * __fastcall JustExtensionZ(char * Dest, char * Name);
extern PACKAGE char * __fastcall StrStCopy(char * Dest, char * S, unsigned Pos, unsigned Count);
extern PACKAGE char * __fastcall AddBackSlashZ(char * Dest, char * DirName);
extern PACKAGE BOOL __fastcall ExistFileZ(char * FName);
extern PACKAGE char * __fastcall ForceExtensionZ(char * Dest, char * Name, char * Ext);
extern PACKAGE char * __fastcall DefaultExtensionZ(char * Dest, char * Name, char * Ext);
extern PACKAGE void * __fastcall GetPtr(void * P, int O);
extern PACKAGE void __fastcall NotBuffer(void *Buf, unsigned Len);
extern PACKAGE unsigned __fastcall DelayMS(unsigned MS);
extern PACKAGE AnsiString __fastcall JustName(AnsiString PathName);
extern PACKAGE AnsiString __fastcall AddBackSlash(const AnsiString DirName);
extern PACKAGE bool __fastcall IsWin2000(void);
extern PACKAGE bool __fastcall IsWinNT(void);
extern PACKAGE int __fastcall ApWinExecAndWait32(char * FileName, char * CommandLine, int Visibility);

}	/* namespace Oomisc */
using namespace Oomisc;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// OoMisc
