// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'filesys.pas' rev: 6.00

#ifndef filesysHPP
#define filesysHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Filesys
{
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TNumericFeedback)(System::TObject* Sender, const double num);

typedef void __fastcall (__closure *TStringFeedback)(System::TObject* Sender, const AnsiString msg);

typedef void __fastcall (*TScanFilesFeedback)(AnsiString CurrentDir, int Count);

typedef void __fastcall (*TFileCopyFeedBack)(int BytesCopied, int SizeOfFile);

typedef void __fastcall (*TTreeCopyFeedBack)(int BytesCopied, int SizeOfCurrentFile, AnsiString NameOfCurrentFile, int NrOfFilesCopiedSoFar);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE AnsiString __fastcall StripExtension(AnsiString FName);
extern PACKAGE void __fastcall AbortAnyFileCopying(void);
extern PACKAGE int __fastcall FileCopyFeedBk(AnsiString SourceName, AnsiString DestName, bool RemoveReadOnly, TFileCopyFeedBack FeedbackProc);
extern PACKAGE void __fastcall CopyFileTree(AnsiString source, AnsiString dest, bool RemoveReadOnly, TTreeCopyFeedBack FeedBack);
extern PACKAGE int __fastcall GetFileSize(AnsiString FileName);
extern PACKAGE int __fastcall MoveToRecycleBin(AnsiString FileMask);
extern PACKAGE AnsiString __fastcall DelDirTree(AnsiString path);
extern PACKAGE bool __fastcall DiskIsReadOnly(Byte Drive);
extern PACKAGE bool __fastcall DirIsReadOnly(AnsiString Dir);
extern PACKAGE int __fastcall GetDiskDriveType(Byte Drive);
extern PACKAGE bool __fastcall IsRootDir(AnsiString path);
extern PACKAGE AnsiString __fastcall StripPath(AnsiString FName);
extern PACKAGE int __fastcall DeleteFiles(AnsiString FileMask);
extern PACKAGE AnsiString __fastcall InventPassword(int NrChars);
extern PACKAGE AnsiString __fastcall FileDetect(AnsiString FileMask);
extern PACKAGE AnsiString __fastcall DOSToWinPath(AnsiString DOSPath);
extern PACKAGE int __fastcall ExtractDrive(AnsiString Path);
extern PACKAGE System::Comp __fastcall DiskFreeExtended(Byte Drive);
extern PACKAGE void __fastcall SetAllFilenameCase(AnsiString FileMask, bool Upc);
extern PACKAGE bool __fastcall DirEmpty(AnsiString DirName);
extern PACKAGE bool __fastcall DirExists(AnsiString DirName);
extern PACKAGE void __fastcall ScanFilesToStrList(AnsiString FileMask, bool SubDirs, Classes::TStringList* SL, TScanFilesFeedback Feedback);
extern PACKAGE AnsiString __fastcall GetTempDir();
extern PACKAGE AnsiString __fastcall GetWindowsDir();
extern PACKAGE AnsiString __fastcall GetSystemDir();
extern PACKAGE AnsiString __fastcall GetEnviroVar(AnsiString VarName);

}	/* namespace Filesys */
using namespace Filesys;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// filesys
