// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AwFaxCvt.pas' rev: 6.00

#ifndef AwFaxCvtHPP
#define AwFaxCvtHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Awfaxcvt
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern PACKAGE BOOL __fastcall awIsAnAPFFile(char * FName);
extern PACKAGE void __fastcall acInitDataLine(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE void __fastcall acInitFaxConverter(Oomisc::PAbsFaxCvt &Cvt, void * Data, Oomisc::TGetLineCallback CB, Oomisc::TOpenFileCallback OpenFile, Oomisc::TCloseFileCallback CloseFile, char * DefaultExt);
extern PACKAGE void __fastcall acDoneFaxConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall acSetOtherData(Oomisc::PAbsFaxCvt Cvt, void * OtherData);
extern PACKAGE void __fastcall acOptionsOn(Oomisc::PAbsFaxCvt Cvt, Word OptionFlags);
extern PACKAGE void __fastcall acOptionsOff(Oomisc::PAbsFaxCvt Cvt, Word OptionFlags);
extern PACKAGE BOOL __fastcall acOptionsAreOn(Oomisc::PAbsFaxCvt Cvt, Word OptionFlags);
extern PACKAGE void __fastcall acSetMargins(Oomisc::PAbsFaxCvt Cvt, unsigned Left, unsigned Top);
extern PACKAGE void __fastcall acSetResolutionMode(Oomisc::PAbsFaxCvt Cvt, BOOL HiRes);
extern PACKAGE void __fastcall acSetResolutionWidth(Oomisc::PAbsFaxCvt Cvt, unsigned RW);
extern PACKAGE void __fastcall acSetStationID(Oomisc::PAbsFaxCvt Cvt, char * ID);
extern PACKAGE void __fastcall acSetStatusCallback(Oomisc::PAbsFaxCvt Cvt, Oomisc::TCvtStatusCallback CB);
extern PACKAGE void __fastcall acSetStatusWnd(Oomisc::PAbsFaxCvt Cvt, int HWindow);
extern PACKAGE void __fastcall acCompressRasterLine(Oomisc::PAbsFaxCvt Cvt, void *Buffer);
extern PACKAGE int __fastcall acOpenFile(Oomisc::PAbsFaxCvt Cvt, char * FileName);
extern PACKAGE void __fastcall acCloseFile(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE int __fastcall acGetRasterLine(Oomisc::PAbsFaxCvt Cvt, void *Data, int &Len, BOOL &EndOfPage, BOOL &MorePages);
extern PACKAGE int __fastcall acAddData(Oomisc::PAbsFaxCvt Cvt, void *Buffer, unsigned Len, BOOL DoInc);
extern PACKAGE int __fastcall acAddLine(Oomisc::PAbsFaxCvt Cvt, void *Buffer, unsigned Len);
extern PACKAGE void __fastcall acMakeEndOfPage(Oomisc::PAbsFaxCvt Cvt, void *Buffer, int &Len);
extern PACKAGE int __fastcall acOutToFileCallback(Oomisc::PAbsFaxCvt Cvt, void *Data, int Len, BOOL EndOfPage, BOOL MorePages);
extern PACKAGE int __fastcall acCreateOutputFile(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE int __fastcall acCloseOutputFile(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE int __fastcall acConvertToFile(Oomisc::PAbsFaxCvt Cvt, char * FileName, char * DestFile);
extern PACKAGE int __fastcall acConvert(Oomisc::PAbsFaxCvt Cvt, char * FileName, Oomisc::TPutLineCallback OutCallback);
extern PACKAGE void __fastcall fcInitTextConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall fcInitTextExConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall fcDoneTextConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall fcDoneTextExConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall fcSetTabStop(Oomisc::PAbsFaxCvt Cvt, unsigned TabStop);
extern PACKAGE int __fastcall fcLoadFont(Oomisc::PAbsFaxCvt Cvt, char * FileName, unsigned FontHandle, BOOL HiRes);
extern PACKAGE int __fastcall fcSetFont(Oomisc::PAbsFaxCvt Cvt, Graphics::TFont* Font, bool HiRes);
extern PACKAGE int __fastcall fcOpenFile(Oomisc::PAbsFaxCvt Cvt, char * FileName);
extern PACKAGE void __fastcall fcCloseFile(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE void __fastcall fcSetLinesPerPage(Oomisc::PAbsFaxCvt Cvt, unsigned LineCount);
extern PACKAGE void __fastcall fcRasterizeText(Oomisc::PAbsFaxCvt Cvt, char * St, unsigned Row, void *Data);
extern PACKAGE int __fastcall fcGetTextRasterLine(Oomisc::PAbsFaxCvt Cvt, void *Data, int &Len, BOOL &EndOfPage, BOOL &MorePages);
extern PACKAGE void __fastcall tcInitTiffConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall tcDoneTiffConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE int __fastcall tcOpenFile(Oomisc::PAbsFaxCvt Cvt, char * FileName);
extern PACKAGE void __fastcall tcCloseFile(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE int __fastcall tcGetTiffRasterLine(Oomisc::PAbsFaxCvt Cvt, void *Data, int &Len, BOOL &EndOfPage, BOOL &MorePages);
extern PACKAGE void __fastcall pcInitPcxConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall pcDonePcxConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE int __fastcall pcOpenFile(Oomisc::PAbsFaxCvt Cvt, char * FileName);
extern PACKAGE void __fastcall pcCloseFile(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE int __fastcall pcGetPcxRasterLine(Oomisc::PAbsFaxCvt Cvt, void *Data, int &Len, BOOL &EndOfPage, BOOL &MorePages);
extern PACKAGE void __fastcall dcInitDcxConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall dcDoneDcxConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE int __fastcall dcOpenFile(Oomisc::PAbsFaxCvt Cvt, char * FileName);
extern PACKAGE void __fastcall dcCloseFile(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE int __fastcall dcGetDcxRasterLine(Oomisc::PAbsFaxCvt Cvt, void *Data, int &Len, BOOL &EndOfPage, BOOL &MorePages);
extern PACKAGE void __fastcall bcInitBmpConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall bcDoneBmpConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE int __fastcall bcOpenFile(Oomisc::PAbsFaxCvt Cvt, char * FileName);
extern PACKAGE void __fastcall bcCloseFile(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE int __fastcall bcGetBmpRasterLine(Oomisc::PAbsFaxCvt Cvt, void *Data, int &Len, BOOL &EndOfPage, BOOL &MorePages);
extern PACKAGE void __fastcall bcInitBitmapConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE void __fastcall bcDoneBitmapConverter(Oomisc::PAbsFaxCvt &Cvt);
extern PACKAGE int __fastcall bcSetInputBitmap(Oomisc::PAbsFaxCvt &Cvt, HBITMAP Bitmap);
extern PACKAGE int __fastcall bcOpenBitmap(Oomisc::PAbsFaxCvt Cvt, char * FileName);
extern PACKAGE void __fastcall bcCloseBitmap(Oomisc::PAbsFaxCvt Cvt);
extern PACKAGE int __fastcall bcGetBitmapRasterLine(Oomisc::PAbsFaxCvt Cvt, void *Data, int &Len, BOOL &EndOfPage, BOOL &MorePages);
extern PACKAGE int __fastcall upInitFaxUnpacker(Oomisc::PUnpackFax &Unpack, void * Data, Oomisc::TUnpackLineCallback CB);
extern PACKAGE void __fastcall upDoneFaxUnpacker(Oomisc::PUnpackFax &Unpack);
extern PACKAGE void __fastcall upOptionsOn(Oomisc::PUnpackFax Unpack, Word OptionFlags);
extern PACKAGE void __fastcall upOptionsOff(Oomisc::PUnpackFax Unpack, Word OptionFlags);
extern PACKAGE BOOL __fastcall upOptionsAreOn(Oomisc::PUnpackFax Unpack, Word OptionFlags);
extern PACKAGE void __fastcall upSetStatusCallback(Oomisc::PUnpackFax Unpack, Oomisc::TUnpackStatusCallback Callback);
extern PACKAGE int __fastcall upSetWhitespaceCompression(Oomisc::PUnpackFax Unpack, unsigned FromLines, unsigned ToLines);
extern PACKAGE void __fastcall upSetScaling(Oomisc::PUnpackFax Unpack, unsigned HMult, unsigned HDiv, unsigned VMult, unsigned VDiv);
extern PACKAGE int __fastcall upGetFaxHeader(Oomisc::PUnpackFax Unpack, char * FName, Oomisc::TFaxHeaderRec &FH);
extern PACKAGE int __fastcall upGetPageHeader(Oomisc::PUnpackFax Unpack, char * FName, unsigned Page, Oomisc::TPageHeaderRec &PH);
extern PACKAGE int __fastcall upUnpackPage(Oomisc::PUnpackFax Unpack, char * FName, unsigned Page);
extern PACKAGE int __fastcall upUnpackFile(Oomisc::PUnpackFax Unpack, char * FName);
extern PACKAGE int __fastcall upUnpackPageToBitmap(Oomisc::PUnpackFax Unpack, char * FName, unsigned Page, Oomisc::TMemoryBitmapDesc &Bmp, BOOL Invert);
extern PACKAGE int __fastcall upUnpackFileToBitmap(Oomisc::PUnpackFax Unpack, char * FName, Oomisc::TMemoryBitmapDesc &Bmp, BOOL Invert);
extern PACKAGE int __fastcall upPutMemoryBitmapLine(Oomisc::PUnpackFax Unpack, Word plFlags, void *Data, unsigned Len, unsigned PageNum);
extern PACKAGE int __fastcall upUnpackPageToBuffer(Oomisc::PUnpackFax Unpack, char * FName, unsigned Page, bool UnpackingFile);
extern PACKAGE int __fastcall upUnpackFileToBuffer(Oomisc::PUnpackFax Unpack, char * FName);
extern PACKAGE int __fastcall upUnpackPageToPcx(Oomisc::PUnpackFax Unpack, char * FName, char * OutName, unsigned Page);
extern PACKAGE int __fastcall upUnpackFileToPcx(Oomisc::PUnpackFax Unpack, char * FName, char * OutName);
extern PACKAGE int __fastcall upUnpackPageToDcx(Oomisc::PUnpackFax Unpack, char * FName, char * OutName, unsigned Page);
extern PACKAGE int __fastcall upUnpackFileToDcx(Oomisc::PUnpackFax Unpack, char * FName, char * OutName);
extern PACKAGE int __fastcall upUnpackPageToTiff(Oomisc::PUnpackFax Unpack, char * FName, char * OutName, unsigned Page);
extern PACKAGE int __fastcall upUnpackFileToTiff(Oomisc::PUnpackFax Unpack, char * FName, char * OutName);
extern PACKAGE int __fastcall upUnpackPageToBmp(Oomisc::PUnpackFax Unpack, char * FName, char * OutName, unsigned Page);
extern PACKAGE int __fastcall upUnpackFileToBmp(Oomisc::PUnpackFax Unpack, char * FName, char * OutName);

}	/* namespace Awfaxcvt */
using namespace Awfaxcvt;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AwFaxCvt
