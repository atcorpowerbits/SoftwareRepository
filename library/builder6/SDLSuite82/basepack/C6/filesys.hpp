// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'filesys.pas' rev: 6.00

#ifndef filesysHPP
#define filesysHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
#include <streams.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Filesys
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLFileSysError;
class PASCALIMPLEMENTATION ESDLFileSysError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLFileSysError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLFileSysError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLFileSysError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLFileSysError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLFileSysError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLFileSysError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLFileSysError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLFileSysError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLFileSysError(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TNumericFeedback)(System::TObject* Sender, const double num);

typedef void __fastcall (__closure *TStringFeedback)(System::TObject* Sender, const AnsiString msg);

typedef void __fastcall (*TScanFilesFeedback)(AnsiString CurrentDir, int Count);

typedef void __fastcall (*TFileCopyFeedBack)(int BytesCopied, int SizeOfFile);

typedef void __fastcall (*TTreeCopyFeedBack)(int BytesCopied, int SizeOfCurrentFile, AnsiString NameOfCurrentFile, int NrOfFilesCopiedSoFar);

typedef void __fastcall (__closure *TOnFileSelectEvent)(System::TObject* Sender, AnsiString Parameters, Controls::TModalResult &UserAction, AnsiString &SelectedFileName);

typedef void __fastcall (__closure *TOnFileCheckEvent)(System::TObject* Sender, AnsiString FileName, bool &FileDoesExist);

typedef void __fastcall (__closure *TOnOverwriteEvent)(System::TObject* Sender, AnsiString FileName, Controls::TModalResult &OverwriteReply);

class DELPHICLASS TUnivSaveDialog;
class PASCALIMPLEMENTATION TUnivSaveDialog : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	AnsiString FParams;
	AnsiString FFileName;
	TOnFileSelectEvent FOnFileSelect;
	TOnFileCheckEvent FOnFileCheck;
	TOnOverwriteEvent FOnOverwrite;
	bool FUseStdDiag;
	
public:
	__fastcall virtual TUnivSaveDialog(Classes::TComponent* AOwner);
	__fastcall virtual ~TUnivSaveDialog(void);
	bool __fastcall Execute(void);
	__property AnsiString FileName = {read=FFileName, write=FFileName};
	int __fastcall ExtractParamAsInt(AnsiString ParName);
	double __fastcall ExtractParamAsDouble(AnsiString ParName);
	AnsiString __fastcall ExtractParamAsString(AnsiString ParName);
	
__published:
	__property AnsiString Parameters = {read=FParams, write=FParams};
	__property TOnFileSelectEvent OnFileSelect = {read=FOnFileSelect, write=FOnFileSelect};
	__property TOnFileCheckEvent OnFileCheck = {read=FOnFileCheck, write=FOnFileCheck};
	__property TOnOverwriteEvent OnOverwrite = {read=FOnOverwrite, write=FOnOverwrite};
	__property bool UseStandardDialog = {read=FUseStdDiag, write=FUseStdDiag, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "filesys_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
extern PACKAGE AnsiString __fastcall StripExtension(AnsiString FName);
extern PACKAGE void __fastcall AbortAnyFileCopying(void);
extern PACKAGE int __fastcall FileCopyFeedBk(AnsiString SourceName, AnsiString DestName, bool RemoveReadOnly, TFileCopyFeedBack FeedbackProc);
extern PACKAGE void __fastcall CopyFileTree(AnsiString source, AnsiString dest, bool RemoveReadOnly, TTreeCopyFeedBack FeedBack);
extern PACKAGE int __fastcall GetFileSize(AnsiString FileName);
extern PACKAGE int __fastcall MoveToRecycleBin(AnsiString FileMask);
extern PACKAGE AnsiString __fastcall DelDirTree(AnsiString path);
extern PACKAGE bool __fastcall DirIsReadOnly(AnsiString Dir);
extern PACKAGE bool __fastcall DiskIsReadOnly(Byte Drive);
extern PACKAGE int __fastcall GetDiskDriveType(Byte Drive);
extern PACKAGE bool __fastcall IsRootDir(AnsiString path);
extern PACKAGE AnsiString __fastcall StripPath(AnsiString FName);
extern PACKAGE int __fastcall DeleteFiles(AnsiString FileMask);
extern PACKAGE AnsiString __fastcall InventPassword(int NrChars);
extern PACKAGE AnsiString __fastcall FileDetect(AnsiString FileMask);
extern PACKAGE AnsiString __fastcall DOSToWinPath(AnsiString DOSPath);
extern PACKAGE bool __fastcall IsDOS83Path(AnsiString Path);
extern PACKAGE int __fastcall ExtractDrive(AnsiString Path);
extern PACKAGE System::Comp __fastcall DiskFreeExtended(Byte Drive);
extern PACKAGE void __fastcall SetAllFilenameCase(AnsiString FileMask, bool Upc);
extern PACKAGE bool __fastcall DirEmpty(AnsiString DirName);
extern PACKAGE bool __fastcall DirExists(AnsiString DirName);
extern PACKAGE void __fastcall ScanFilesToStrList(AnsiString FileMask, bool SubDirs, Classes::TStringList* SL, TScanFilesFeedback Feedback);
extern PACKAGE AnsiString __fastcall GetSystemDir();
extern PACKAGE AnsiString __fastcall GetTempDir();
extern PACKAGE AnsiString __fastcall GetEnviroVar(AnsiString VarName);
extern PACKAGE AnsiString __fastcall GetWindowsDir();
extern PACKAGE void __fastcall AppendToTextFile(AnsiString FName, AnsiString Text)/* overload */;
extern PACKAGE void __fastcall AppendToTextFile(AnsiString FName, Classes::TStringList* SL)/* overload */;
extern PACKAGE int __fastcall CountLinesInTextFile(const TextFile &FVar)/* overload */;
extern PACKAGE int __fastcall CountLinesInTextFile(const AnsiString FName)/* overload */;
extern PACKAGE int __fastcall ReadHeaderOfASC(AnsiString FName, AnsiString &Comment, int &NFeat, int &NObj, bool &ClInf, bool &NamFeat, bool &NamObj)/* overload */;
extern PACKAGE int __fastcall ReadHeaderOfASC(Classes::TStream* InStream, AnsiString &Comment, int &NFeat, int &NObj, bool &ClInf, bool &NamFeat, bool &NamObj)/* overload */;
extern PACKAGE void __fastcall Register(void);

}	/* namespace Filesys */
using namespace Filesys;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// filesys
