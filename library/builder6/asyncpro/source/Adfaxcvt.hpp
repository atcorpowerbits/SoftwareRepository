// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdFaxCvt.pas' rev: 6.00

#ifndef AdFaxCvtHPP
#define AdFaxCvtHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdExcept.hpp>	// Pascal unit
#include <AwFaxCvt.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <IniFiles.hpp>	// Pascal unit
#include <Registry.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <ShellAPI.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Printers.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adfaxcvt
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TFaxInputDocumentType { idNone, idText, idTextEx, idTiff, idPcx, idDcx, idBmp, idBitmap, idUser, idShell };
#pragma option pop

#pragma option push -b-
enum TFaxCvtOptions { coDoubleWidth, coHalfHeight, coCenterImage, coYield, coYieldOften };
#pragma option pop

typedef Set<TFaxCvtOptions, coDoubleWidth, coYieldOften>  TFaxCvtOptionsSet;

#pragma option push -b-
enum TFaxResolution { frNormal, frHigh };
#pragma option pop

#pragma option push -b-
enum TFaxWidth { fwNormal, fwWide };
#pragma option pop

#pragma option push -b-
enum TFaxFont { ffStandard, ffSmall };
#pragma option pop

typedef void __fastcall (__closure *TFaxStatusEvent)(System::TObject* F, bool Starting, bool Ending, int PagesConverted, int LinesConverted, int BytesConverted, int BytesToConvert, bool &Abort);

typedef void __fastcall (__closure *TFaxOutputLineEvent)(System::TObject* F, Sysutils::PByteArray Data, int Len, bool EndOfPage, bool MorePages);

typedef void __fastcall (__closure *TFaxOpenFileEvent)(System::TObject* F, AnsiString FName);

typedef void __fastcall (__closure *TFaxCloseFileEvent)(System::TObject* F);

typedef void __fastcall (__closure *TFaxReadLineEvent)(System::TObject* F, Sysutils::PByteArray Data, int &Len, bool &EndOfPage, bool &MorePages);

class DELPHICLASS TApdCustomFaxConverter;
class PASCALIMPLEMENTATION TApdCustomFaxConverter : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	TFaxInputDocumentType FInputDocumentType;
	TFaxCvtOptionsSet FOptions;
	TFaxResolution FResolution;
	TFaxWidth FWidth;
	unsigned FTopMargin;
	unsigned FLeftMargin;
	unsigned FLinesPerPage;
	unsigned FTabStop;
	Graphics::TFont* FEnhFont;
	TFaxFont FFontType;
	AnsiString FFontFile;
	AnsiString FDocumentFile;
	AnsiString FOutFileName;
	AnsiString FDefUserExtension;
	AnsiString FStationID;
	TFaxStatusEvent FStatus;
	TFaxOutputLineEvent FOutputLine;
	TFaxOpenFileEvent FOpenUserFile;
	TFaxCloseFileEvent FCloseUserFile;
	TFaxReadLineEvent FReadUserLine;
	TFaxInputDocumentType LastDocType;
	Oomisc::TAbsFaxCvt *Data;
	bool FileOpen;
	HWND PrnCallbackHandle;
	bool FWaitingForShell;
	bool FResetShellTimer;
	int FShellPageCount;
	bool FPadPage;
	void __fastcall CreateData(void);
	void __fastcall DestroyData(void);
	void __fastcall SetCvtOptions(const TFaxCvtOptionsSet NewOpts);
	void __fastcall SetDocumentFile(const AnsiString NewFile);
	void __fastcall SetEnhFont(Graphics::TFont* Value);
	void __fastcall ConvertToResolution(const AnsiString FileName, TFaxResolution NewRes);
	void __fastcall ChangeDefPrinter(bool UseFax);
	void __fastcall ConvertShell(const AnsiString FileName);
	void __fastcall PrnCallback(Messages::TMessage &Msg);
	void __fastcall SetPadPage(const bool Value);
	
public:
	__fastcall virtual TApdCustomFaxConverter(Classes::TComponent* Owner);
	__fastcall virtual ~TApdCustomFaxConverter(void);
	__property TFaxInputDocumentType InputDocumentType = {read=FInputDocumentType, write=FInputDocumentType, default=0};
	__property TFaxCvtOptionsSet Options = {read=FOptions, write=SetCvtOptions, default=13};
	__property TFaxResolution Resolution = {read=FResolution, write=FResolution, default=0};
	__property TFaxWidth Width = {read=FWidth, write=FWidth, default=0};
	__property unsigned TopMargin = {read=FTopMargin, write=FTopMargin, default=0};
	__property unsigned LeftMargin = {read=FLeftMargin, write=FLeftMargin, default=50};
	__property unsigned LinesPerPage = {read=FLinesPerPage, write=FLinesPerPage, default=60};
	__property unsigned TabStop = {read=FTabStop, write=FTabStop, default=4};
	__property AnsiString FontFile = {read=FFontFile, write=FFontFile};
	__property TFaxFont FontType = {read=FFontType, write=FFontType, nodefault};
	__property Graphics::TFont* EnhFont = {read=FEnhFont, write=SetEnhFont};
	__property AnsiString DocumentFile = {read=FDocumentFile, write=SetDocumentFile};
	__property AnsiString OutFileName = {read=FOutFileName, write=FOutFileName};
	__property AnsiString DefUserExtension = {read=FDefUserExtension, write=FDefUserExtension};
	__property AnsiString StationID = {read=FStationID, write=FStationID};
	__property bool PadPage = {read=FPadPage, write=SetPadPage, nodefault};
	__property TFaxStatusEvent OnStatus = {read=FStatus, write=FStatus};
	__property TFaxOutputLineEvent OnOutputLine = {read=FOutputLine, write=FOutputLine};
	__property TFaxOpenFileEvent OnOpenUserFile = {read=FOpenUserFile, write=FOpenUserFile};
	__property TFaxCloseFileEvent OnCloseUserFile = {read=FCloseUserFile, write=FCloseUserFile};
	__property TFaxReadLineEvent OnReadUserLine = {read=FReadUserLine, write=FReadUserLine};
	void __fastcall ConvertToFile(void);
	void __fastcall Convert(void);
	void __fastcall ConvertBitmapToFile(const Graphics::TBitmap* Bmp);
	void __fastcall ConvertToHighRes(const AnsiString FileName);
	void __fastcall ConvertToLowRes(const AnsiString FileName);
	void __fastcall OpenFile(void);
	void __fastcall CloseFile(void);
	void __fastcall GetRasterLine(void *Buffer, int &BufLen, bool &EndOfPage, bool &MorePages);
	void __fastcall CompressRasterLine(void *Buffer, void *OutputData, int &OutLen);
	void __fastcall MakeEndOfPage(void *Buffer, int &BufLen);
	virtual void __fastcall Status(const bool Starting, const bool Ending, const int PagesConverted, const int LinesConverted, const int BytesToRead, const int BytesRead, bool &Abort);
	virtual void __fastcall OutputLine(void *Data, int Len, bool EndOfPage, bool MorePages);
	virtual void __fastcall OpenUserFile(const AnsiString FName);
	virtual void __fastcall CloseUserFile(void);
	void __fastcall ReadUserLine(void *Data, int &Len, bool &EndOfPage, bool &MorePages);
};


class DELPHICLASS TApdFaxConverter;
class PASCALIMPLEMENTATION TApdFaxConverter : public TApdCustomFaxConverter 
{
	typedef TApdCustomFaxConverter inherited;
	
__published:
	__property InputDocumentType  = {default=0};
	__property Options  = {default=13};
	__property Resolution  = {default=0};
	__property Width  = {default=0};
	__property TopMargin  = {default=0};
	__property LeftMargin  = {default=50};
	__property LinesPerPage  = {default=60};
	__property TabStop  = {default=4};
	__property EnhFont ;
	__property FontFile ;
	__property FontType ;
	__property DocumentFile ;
	__property OutFileName ;
	__property DefUserExtension ;
	__property OnStatus ;
	__property OnOutputLine ;
	__property OnOpenUserFile ;
	__property OnCloseUserFile ;
	__property OnReadUserLine ;
public:
	#pragma option push -w-inl
	/* TApdCustomFaxConverter.Create */ inline __fastcall virtual TApdFaxConverter(Classes::TComponent* Owner) : TApdCustomFaxConverter(Owner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomFaxConverter.Destroy */ inline __fastcall virtual ~TApdFaxConverter(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TUnpackerOptions { uoYield, uoAbort };
#pragma option pop

typedef Set<TUnpackerOptions, uoYield, uoAbort>  TUnpackerOptionsSet;

#pragma option push -b-
enum TAutoScaleMode { asNone, asDoubleHeight, asHalfWidth };
#pragma option pop

typedef void __fastcall (__closure *TUnpackOutputLineEvent)(System::TObject* Sender, bool Starting, bool Ending, Sysutils::PByteArray Data, int Len, int PageNum);

typedef void __fastcall (__closure *TUnpackStatusEvent)(System::TObject* Sender, AnsiString FName, int PageNum, int BytesUnpacked, int BytesToUnpack);

class DELPHICLASS TApdCustomFaxUnpacker;
class PASCALIMPLEMENTATION TApdCustomFaxUnpacker : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
protected:
	TUnpackerOptionsSet FOptions;
	bool FWhitespaceCompression;
	unsigned FWhitespaceFrom;
	unsigned FWhitespaceTo;
	bool FScaling;
	unsigned FHorizMult;
	unsigned FHorizDiv;
	unsigned FVertMult;
	unsigned FVertDiv;
	TAutoScaleMode FAutoScaleMode;
	AnsiString FInFileName;
	AnsiString FOutFileName;
	TUnpackOutputLineEvent FOutputLine;
	TUnpackStatusEvent FStatus;
	Oomisc::TUnpackFax *Data;
	char InFileZ[256];
	char OutFileZ[256];
	void __fastcall CreateData(void);
	void __fastcall DestroyData(void);
	virtual void __fastcall OutputLine(const bool Starting, const bool Ending, const Sysutils::PByteArray Data, const unsigned Len, const unsigned PageNum);
	virtual void __fastcall Status(const AnsiString FName, const unsigned PageNum, const int BytesUnpacked, const int BytesToUnpack);
	void __fastcall SetHorizMult(const unsigned NewHorizMult);
	void __fastcall SetHorizDiv(const unsigned NewHorizDiv);
	void __fastcall SetVertMult(const unsigned NewVertMult);
	void __fastcall SetVertDiv(const unsigned NewVertDiv);
	unsigned __fastcall GetNumPages(void);
	TFaxResolution __fastcall GetFaxResolution(void);
	TFaxWidth __fastcall GetFaxWidth(void);
	void __fastcall SetInFileName(const AnsiString NewName);
	void __fastcall SetUnpackerOptions(const TUnpackerOptionsSet NewUnpackerOptions);
	char * __fastcall InFNameZ(void);
	char * __fastcall OutFNameZ(void);
	
public:
	__fastcall virtual TApdCustomFaxUnpacker(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomFaxUnpacker(void);
	void __fastcall UnpackPage(const unsigned Page);
	void __fastcall UnpackFile(void);
	Graphics::TBitmap* __fastcall UnpackPageToBitmap(const unsigned Page);
	Graphics::TBitmap* __fastcall UnpackFileToBitmap(void);
	void __fastcall UnpackPageToPcx(const unsigned Page);
	void __fastcall UnpackFileToPcx(void);
	void __fastcall UnpackPageToDcx(const unsigned Page);
	void __fastcall UnpackFileToDcx(void);
	void __fastcall UnpackPageToTiff(const unsigned Page);
	void __fastcall UnpackFileToTiff(void);
	void __fastcall UnpackPageToBmp(const unsigned Page);
	void __fastcall UnpackFileToBmp(void);
	void __fastcall ExtractPage(const unsigned Page);
	__property TUnpackerOptionsSet Options = {read=FOptions, write=SetUnpackerOptions, default=1};
	__property bool WhitespaceCompression = {read=FWhitespaceCompression, write=FWhitespaceCompression, default=0};
	__property unsigned WhitespaceFrom = {read=FWhitespaceFrom, write=FWhitespaceFrom, default=0};
	__property unsigned WhitespaceTo = {read=FWhitespaceTo, write=FWhitespaceTo, default=0};
	__property bool Scaling = {read=FScaling, write=FScaling, default=0};
	__property unsigned HorizMult = {read=FHorizMult, write=SetHorizMult, default=1};
	__property unsigned HorizDiv = {read=FHorizDiv, write=SetHorizDiv, default=1};
	__property unsigned VertMult = {read=FVertMult, write=SetVertMult, default=1};
	__property unsigned VertDiv = {read=FVertDiv, write=SetVertDiv, default=1};
	__property TAutoScaleMode AutoScaleMode = {read=FAutoScaleMode, write=FAutoScaleMode, nodefault};
	__property AnsiString InFileName = {read=FInFileName, write=SetInFileName};
	__property AnsiString OutFileName = {read=FOutFileName, write=FOutFileName};
	__property unsigned NumPages = {read=GetNumPages, nodefault};
	__property TFaxResolution FaxResolution = {read=GetFaxResolution, nodefault};
	__property TFaxWidth FaxWidth = {read=GetFaxWidth, nodefault};
	__property TUnpackOutputLineEvent OnOutputLine = {read=FOutputLine, write=FOutputLine};
	__property TUnpackStatusEvent OnStatus = {read=FStatus, write=FStatus};
	/*         class method */ static bool __fastcall IsAnAPFFile(TMetaClass* vmt, const AnsiString FName);
};


class DELPHICLASS TApdFaxUnpacker;
class PASCALIMPLEMENTATION TApdFaxUnpacker : public TApdCustomFaxUnpacker 
{
	typedef TApdCustomFaxUnpacker inherited;
	
__published:
	__property Options  = {default=1};
	__property WhitespaceCompression  = {default=0};
	__property WhitespaceFrom  = {default=0};
	__property WhitespaceTo  = {default=0};
	__property Scaling  = {default=0};
	__property HorizMult  = {default=1};
	__property HorizDiv  = {default=1};
	__property VertMult  = {default=1};
	__property VertDiv  = {default=1};
	__property AutoScaleMode ;
	__property InFileName ;
	__property OutFileName ;
	__property OnOutputLine ;
	__property OnStatus ;
public:
	#pragma option push -w-inl
	/* TApdCustomFaxUnpacker.Create */ inline __fastcall virtual TApdFaxUnpacker(Classes::TComponent* AOwner) : TApdCustomFaxUnpacker(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomFaxUnpacker.Destroy */ inline __fastcall virtual ~TApdFaxUnpacker(void) { }
	#pragma option pop
	
};


class DELPHICLASS EApdAPFGraphicError;
class PASCALIMPLEMENTATION EApdAPFGraphicError : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall EApdAPFGraphicError(const AnsiString Msg) : Sysutils::Exception(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EApdAPFGraphicError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EApdAPFGraphicError(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EApdAPFGraphicError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EApdAPFGraphicError(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EApdAPFGraphicError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EApdAPFGraphicError(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EApdAPFGraphicError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EApdAPFGraphicError(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdAPFGraphic;
class PASCALIMPLEMENTATION TApdAPFGraphic : public Graphics::TGraphic 
{
	typedef Graphics::TGraphic inherited;
	
private:
	int FCurrentPage;
	Classes::TList* FPages;
	TApdCustomFaxUnpacker* FFromAPF;
	TApdCustomFaxConverter* FToAPF;
	
protected:
	virtual void __fastcall Draw(Graphics::TCanvas* ACanvas, const Types::TRect &Rect);
	void __fastcall FreeImages(void);
	virtual bool __fastcall GetEmpty(void);
	virtual int __fastcall GetHeight(void);
	int __fastcall GetNumPages(void);
	Graphics::TBitmap* __fastcall GetPage(int x);
	virtual int __fastcall GetWidth(void);
	void __fastcall SetCurrentPage(int v);
	virtual void __fastcall SetHeight(int v);
	void __fastcall SetPage(int x, Graphics::TBitmap* v);
	virtual void __fastcall SetWidth(int v);
	
public:
	__fastcall virtual TApdAPFGraphic(void);
	__fastcall virtual ~TApdAPFGraphic(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	virtual void __fastcall AssignTo(Classes::TPersistent* Dest);
	virtual void __fastcall LoadFromClipboardFormat(Word AFormat, unsigned AData, HPALETTE APalette);
	virtual void __fastcall LoadFromFile(const AnsiString Filename);
	virtual void __fastcall LoadFromStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToClipboardFormat(Word &AFormat, unsigned &AData, HPALETTE &APalette);
	virtual void __fastcall SaveToStream(Classes::TStream* Stream);
	virtual void __fastcall SaveToFile(const AnsiString Filename);
	__property Graphics::TBitmap* Page[int x] = {read=GetPage, write=SetPage};
	
__published:
	__property int CurrentPage = {read=FCurrentPage, write=SetCurrentPage, nodefault};
	__property int NumPages = {read=GetNumPages, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::ResourceString _ApdEcStrNoClipboard;
#define Adfaxcvt_ApdEcStrNoClipboard System::LoadResourceString(&Adfaxcvt::_ApdEcStrNoClipboard)
extern PACKAGE System::ResourceString _ApdEcStrBadFaxFmt;
#define Adfaxcvt_ApdEcStrBadFaxFmt System::LoadResourceString(&Adfaxcvt::_ApdEcStrBadFaxFmt)
extern PACKAGE System::ResourceString _ApdEcStrInvalidPage;
#define Adfaxcvt_ApdEcStrInvalidPage System::LoadResourceString(&Adfaxcvt::_ApdEcStrInvalidPage)
#define afcDefInputDocumentType (TFaxInputDocumentType)(0)
#define afcDefFaxCvtOptions (System::Set<TFaxCvtOptions, coDoubleWidth, coYieldOften> () << TFaxCvtOptions(0) << TFaxCvtOptions(2) << TFaxCvtOptions(3) )
#define afcDefResolution (TFaxResolution)(0)
#define afcDefFaxCvtWidth (TFaxWidth)(0)
static const Shortint afcDefTopMargin = 0x0;
static const Shortint afcDefLeftMargin = 0x32;
static const Shortint afcDefLinesPerPage = 0x3c;
static const Shortint afcDefFaxTabStop = 0x4;
#define afcDefFontFile "APFAX.FNT"
#define afcDefFontType (TFaxFont)(0)
extern PACKAGE int afcDefPrintTimeout;
#define afcDefFaxUnpackOptions (System::Set<TUnpackerOptions, uoYield, uoAbort> () << TUnpackerOptions(0) )
static const bool afcDefWhitespaceCompression = false;
static const Shortint afcDefWhitespaceFrom = 0x0;
static const Shortint afcDefWhitespaceTo = 0x0;
static const bool afcDefScaling = false;
static const Shortint afcDefHorizMult = 0x1;
static const Shortint afcDefHorizDiv = 0x1;
static const Shortint afcDefVertMult = 0x1;
static const Shortint afcDefVertDiv = 0x1;
#define afcDefAutoScaleMode (TAutoScaleMode)(1)

}	/* namespace Adfaxcvt */
using namespace Adfaxcvt;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdFaxCvt
