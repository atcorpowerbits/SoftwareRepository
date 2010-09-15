// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdExcept.pas' rev: 6.00

#ifndef AdExceptHPP
#define AdExceptHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <OoMisc.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adexcept
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS EAPDException;
class PASCALIMPLEMENTATION EAPDException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
private:
	int FErrorCode;
	
public:
	__fastcall EAPDException(const int EC, bool PassThru);
	__fastcall EAPDException(const AnsiString Msg, Byte Dummy);
	/*         class method */ static Word __fastcall MapCodeToStringID(TMetaClass* vmt, const int Code);
	__property int ErrorCode = {read=FErrorCode, write=FErrorCode, nodefault};
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAPDException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAPDException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAPDException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAPDException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAPDException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAPDException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAPDException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAPDException(void) { }
	#pragma option pop
	
};


class DELPHICLASS EGeneral;
class PASCALIMPLEMENTATION EGeneral : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EGeneral(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EGeneral(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EGeneral(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EGeneral(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EGeneral(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EGeneral(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EGeneral(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EGeneral(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EGeneral(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EGeneral(void) { }
	#pragma option pop
	
};


class DELPHICLASS EOpenComm;
class PASCALIMPLEMENTATION EOpenComm : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EOpenComm(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EOpenComm(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EOpenComm(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EOpenComm(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EOpenComm(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EOpenComm(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EOpenComm(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EOpenComm(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EOpenComm(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EOpenComm(void) { }
	#pragma option pop
	
};


class DELPHICLASS ESerialIO;
class PASCALIMPLEMENTATION ESerialIO : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ESerialIO(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ESerialIO(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESerialIO(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESerialIO(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESerialIO(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESerialIO(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESerialIO(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESerialIO(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESerialIO(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESerialIO(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModem;
class PASCALIMPLEMENTATION EModem : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModem(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModem(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModem(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModem(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModem(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModem(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModem(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModem(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModem(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModem(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETrigger;
class PASCALIMPLEMENTATION ETrigger : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETrigger(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETrigger(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETrigger(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETrigger(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETrigger(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETrigger(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETrigger(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETrigger(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETrigger(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETrigger(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPacket;
class PASCALIMPLEMENTATION EPacket : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EPacket(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EPacket(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPacket(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPacket(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPacket(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPacket(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPacket(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPacket(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPacket(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPacket(void) { }
	#pragma option pop
	
};


class DELPHICLASS EProtocol;
class PASCALIMPLEMENTATION EProtocol : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EProtocol(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EProtocol(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EProtocol(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EProtocol(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EProtocol(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EProtocol(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EProtocol(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EProtocol(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EProtocol(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EProtocol(void) { }
	#pragma option pop
	
};


class DELPHICLASS EINI;
class PASCALIMPLEMENTATION EINI : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EINI(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EINI(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EINI(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EINI(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EINI(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EINI(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EINI(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EINI(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EINI(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EINI(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFax;
class PASCALIMPLEMENTATION EFax : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFax(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFax(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFax(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFax(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFax(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFax(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFax(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFax(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFax(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFax(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapi;
class PASCALIMPLEMENTATION ETapi : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapi(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapi(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapi(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapi(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapi(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapi(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapi(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapi(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapi(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapi(void) { }
	#pragma option pop
	
};


class DELPHICLASS ERas;
class PASCALIMPLEMENTATION ERas : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ERas(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ERas(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ERas(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ERas(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ERas(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ERas(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ERas(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ERas(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ERas(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ERas(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAdTerminal;
class PASCALIMPLEMENTATION EAdTerminal : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAdTerminal(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAdTerminal(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAdTerminal(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAdTerminal(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAdTerminal(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAdTerminal(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAdTerminal(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAdTerminal(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdTerminal(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAdTerminal(void) { }
	#pragma option pop
	
};


class DELPHICLASS EXML;
class PASCALIMPLEMENTATION EXML : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EXML(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EXML(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EXML(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EXML(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EXML(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EXML(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EXML(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EXML(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EXML(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EXML(void) { }
	#pragma option pop
	
};


class DELPHICLASS EStateMachine;
class PASCALIMPLEMENTATION EStateMachine : public EAPDException 
{
	typedef EAPDException inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EStateMachine(const int EC, bool PassThru) : EAPDException(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EStateMachine(const AnsiString Msg, Byte Dummy) : EAPDException(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EStateMachine(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAPDException(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EStateMachine(int Ident)/* overload */ : EAPDException(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EStateMachine(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAPDException(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EStateMachine(const AnsiString Msg, int AHelpContext) : EAPDException(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EStateMachine(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAPDException(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EStateMachine(int Ident, int AHelpContext)/* overload */ : EAPDException(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EStateMachine(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAPDException(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EStateMachine(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBadArgument;
class PASCALIMPLEMENTATION EBadArgument : public EGeneral 
{
	typedef EGeneral inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBadArgument(const int EC, bool PassThru) : EGeneral(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBadArgument(const AnsiString Msg, Byte Dummy) : EGeneral(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBadArgument(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EGeneral(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBadArgument(int Ident)/* overload */ : EGeneral(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBadArgument(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EGeneral(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBadArgument(const AnsiString Msg, int AHelpContext) : EGeneral(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBadArgument(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EGeneral(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBadArgument(int Ident, int AHelpContext)/* overload */ : EGeneral(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBadArgument(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EGeneral(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBadArgument(void) { }
	#pragma option pop
	
};


class DELPHICLASS EGotQuitMsg;
class PASCALIMPLEMENTATION EGotQuitMsg : public EGeneral 
{
	typedef EGeneral inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EGotQuitMsg(const int EC, bool PassThru) : EGeneral(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EGotQuitMsg(const AnsiString Msg, Byte Dummy) : EGeneral(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EGotQuitMsg(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EGeneral(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EGotQuitMsg(int Ident)/* overload */ : EGeneral(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EGotQuitMsg(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EGeneral(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EGotQuitMsg(const AnsiString Msg, int AHelpContext) : EGeneral(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EGotQuitMsg(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EGeneral(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EGotQuitMsg(int Ident, int AHelpContext)/* overload */ : EGeneral(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EGotQuitMsg(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EGeneral(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EGotQuitMsg(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBufferTooBig;
class PASCALIMPLEMENTATION EBufferTooBig : public EGeneral 
{
	typedef EGeneral inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBufferTooBig(const int EC, bool PassThru) : EGeneral(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBufferTooBig(const AnsiString Msg, Byte Dummy) : EGeneral(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBufferTooBig(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EGeneral(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBufferTooBig(int Ident)/* overload */ : EGeneral(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBufferTooBig(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EGeneral(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBufferTooBig(const AnsiString Msg, int AHelpContext) : EGeneral(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBufferTooBig(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EGeneral(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBufferTooBig(int Ident, int AHelpContext)/* overload */ : EGeneral(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBufferTooBig(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EGeneral(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBufferTooBig(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPortNotAssigned;
class PASCALIMPLEMENTATION EPortNotAssigned : public EGeneral 
{
	typedef EGeneral inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EPortNotAssigned(const int EC, bool PassThru) : EGeneral(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EPortNotAssigned(const AnsiString Msg, Byte Dummy) : EGeneral(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPortNotAssigned(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EGeneral(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPortNotAssigned(int Ident)/* overload */ : EGeneral(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPortNotAssigned(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EGeneral(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPortNotAssigned(const AnsiString Msg, int AHelpContext) : EGeneral(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPortNotAssigned(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EGeneral(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPortNotAssigned(int Ident, int AHelpContext)/* overload */ : EGeneral(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPortNotAssigned(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EGeneral(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPortNotAssigned(void) { }
	#pragma option pop
	
};


class DELPHICLASS EInternal;
class PASCALIMPLEMENTATION EInternal : public EGeneral 
{
	typedef EGeneral inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EInternal(const int EC, bool PassThru) : EGeneral(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EInternal(const AnsiString Msg, Byte Dummy) : EGeneral(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EInternal(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EGeneral(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EInternal(int Ident)/* overload */ : EGeneral(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EInternal(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EGeneral(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EInternal(const AnsiString Msg, int AHelpContext) : EGeneral(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EInternal(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EGeneral(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EInternal(int Ident, int AHelpContext)/* overload */ : EGeneral(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EInternal(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EGeneral(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EInternal(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModemNotAssigned;
class PASCALIMPLEMENTATION EModemNotAssigned : public EGeneral 
{
	typedef EGeneral inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModemNotAssigned(const int EC, bool PassThru) : EGeneral(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModemNotAssigned(const AnsiString Msg, Byte Dummy) : EGeneral(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModemNotAssigned(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EGeneral(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModemNotAssigned(int Ident)/* overload */ : EGeneral(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModemNotAssigned(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EGeneral(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModemNotAssigned(const AnsiString Msg, int AHelpContext) : EGeneral(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModemNotAssigned(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EGeneral(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModemNotAssigned(int Ident, int AHelpContext)/* overload */ : EGeneral(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModemNotAssigned(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EGeneral(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModemNotAssigned(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPhonebookNotAssigned;
class PASCALIMPLEMENTATION EPhonebookNotAssigned : public EGeneral 
{
	typedef EGeneral inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EPhonebookNotAssigned(const int EC, bool PassThru) : EGeneral(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EPhonebookNotAssigned(const AnsiString Msg, Byte Dummy) : EGeneral(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPhonebookNotAssigned(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EGeneral(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPhonebookNotAssigned(int Ident)/* overload */ : EGeneral(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPhonebookNotAssigned(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EGeneral(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPhonebookNotAssigned(const AnsiString Msg, int AHelpContext) : EGeneral(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPhonebookNotAssigned(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EGeneral(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPhonebookNotAssigned(int Ident, int AHelpContext)/* overload */ : EGeneral(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPhonebookNotAssigned(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EGeneral(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPhonebookNotAssigned(void) { }
	#pragma option pop
	
};


class DELPHICLASS ECannotUseWithWinSock;
class PASCALIMPLEMENTATION ECannotUseWithWinSock : public EGeneral 
{
	typedef EGeneral inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ECannotUseWithWinSock(const int EC, bool PassThru) : EGeneral(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ECannotUseWithWinSock(const AnsiString Msg, Byte Dummy) : EGeneral(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ECannotUseWithWinSock(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EGeneral(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ECannotUseWithWinSock(int Ident)/* overload */ : EGeneral(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ECannotUseWithWinSock(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EGeneral(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ECannotUseWithWinSock(const AnsiString Msg, int AHelpContext) : EGeneral(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ECannotUseWithWinSock(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EGeneral(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ECannotUseWithWinSock(int Ident, int AHelpContext)/* overload */ : EGeneral(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ECannotUseWithWinSock(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EGeneral(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ECannotUseWithWinSock(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBadId;
class PASCALIMPLEMENTATION EBadId : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBadId(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBadId(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBadId(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBadId(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBadId(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBadId(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBadId(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBadId(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBadId(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBadId(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBaudRate;
class PASCALIMPLEMENTATION EBaudRate : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBaudRate(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBaudRate(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBaudRate(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBaudRate(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBaudRate(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBaudRate(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBaudRate(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBaudRate(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBaudRate(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBaudRate(void) { }
	#pragma option pop
	
};


class DELPHICLASS EByteSize;
class PASCALIMPLEMENTATION EByteSize : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EByteSize(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EByteSize(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EByteSize(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EByteSize(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EByteSize(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EByteSize(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EByteSize(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EByteSize(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EByteSize(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EByteSize(void) { }
	#pragma option pop
	
};


class DELPHICLASS EDefault;
class PASCALIMPLEMENTATION EDefault : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EDefault(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EDefault(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDefault(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDefault(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDefault(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDefault(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDefault(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDefault(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDefault(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDefault(void) { }
	#pragma option pop
	
};


class DELPHICLASS EHardware;
class PASCALIMPLEMENTATION EHardware : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EHardware(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EHardware(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EHardware(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EHardware(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EHardware(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EHardware(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EHardware(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EHardware(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EHardware(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EHardware(void) { }
	#pragma option pop
	
};


class DELPHICLASS EMemory;
class PASCALIMPLEMENTATION EMemory : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EMemory(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EMemory(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EMemory(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EMemory(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EMemory(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EMemory(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EMemory(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EMemory(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EMemory(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EMemory(void) { }
	#pragma option pop
	
};


class DELPHICLASS ECommNotOpen;
class PASCALIMPLEMENTATION ECommNotOpen : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ECommNotOpen(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ECommNotOpen(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ECommNotOpen(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ECommNotOpen(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ECommNotOpen(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ECommNotOpen(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ECommNotOpen(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ECommNotOpen(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ECommNotOpen(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ECommNotOpen(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAlreadyOpen;
class PASCALIMPLEMENTATION EAlreadyOpen : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAlreadyOpen(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAlreadyOpen(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAlreadyOpen(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAlreadyOpen(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAlreadyOpen(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAlreadyOpen(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAlreadyOpen(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAlreadyOpen(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAlreadyOpen(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAlreadyOpen(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoHandles;
class PASCALIMPLEMENTATION ENoHandles : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoHandles(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoHandles(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoHandles(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoHandles(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoHandles(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoHandles(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoHandles(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoHandles(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoHandles(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoHandles(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoTimers;
class PASCALIMPLEMENTATION ENoTimers : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoTimers(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoTimers(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoTimers(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoTimers(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoTimers(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoTimers(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoTimers(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoTimers(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoTimers(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoTimers(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoPortSelected;
class PASCALIMPLEMENTATION ENoPortSelected : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoPortSelected(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoPortSelected(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoPortSelected(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoPortSelected(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoPortSelected(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoPortSelected(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoPortSelected(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoPortSelected(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoPortSelected(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoPortSelected(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENotOpenedByTapi;
class PASCALIMPLEMENTATION ENotOpenedByTapi : public EOpenComm 
{
	typedef EOpenComm inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENotOpenedByTapi(const int EC, bool PassThru) : EOpenComm(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENotOpenedByTapi(const AnsiString Msg, Byte Dummy) : EOpenComm(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENotOpenedByTapi(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EOpenComm(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENotOpenedByTapi(int Ident)/* overload */ : EOpenComm(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENotOpenedByTapi(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EOpenComm(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENotOpenedByTapi(const AnsiString Msg, int AHelpContext) : EOpenComm(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENotOpenedByTapi(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EOpenComm(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENotOpenedByTapi(int Ident, int AHelpContext)/* overload */ : EOpenComm(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENotOpenedByTapi(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EOpenComm(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENotOpenedByTapi(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENullApi;
class PASCALIMPLEMENTATION ENullApi : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENullApi(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENullApi(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENullApi(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENullApi(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENullApi(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENullApi(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENullApi(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENullApi(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENullApi(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENullApi(void) { }
	#pragma option pop
	
};


class DELPHICLASS ERegisterHandlerFailed;
class PASCALIMPLEMENTATION ERegisterHandlerFailed : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ERegisterHandlerFailed(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ERegisterHandlerFailed(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ERegisterHandlerFailed(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ERegisterHandlerFailed(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ERegisterHandlerFailed(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ERegisterHandlerFailed(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ERegisterHandlerFailed(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ERegisterHandlerFailed(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ERegisterHandlerFailed(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ERegisterHandlerFailed(void) { }
	#pragma option pop
	
};


class DELPHICLASS EPutBlockFail;
class PASCALIMPLEMENTATION EPutBlockFail : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EPutBlockFail(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EPutBlockFail(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EPutBlockFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EPutBlockFail(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EPutBlockFail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EPutBlockFail(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EPutBlockFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EPutBlockFail(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EPutBlockFail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EPutBlockFail(void) { }
	#pragma option pop
	
};


class DELPHICLASS EGetBlockFail;
class PASCALIMPLEMENTATION EGetBlockFail : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EGetBlockFail(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EGetBlockFail(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EGetBlockFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EGetBlockFail(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EGetBlockFail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EGetBlockFail(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EGetBlockFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EGetBlockFail(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EGetBlockFail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EGetBlockFail(void) { }
	#pragma option pop
	
};


class DELPHICLASS EOutputBufferTooSmall;
class PASCALIMPLEMENTATION EOutputBufferTooSmall : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EOutputBufferTooSmall(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EOutputBufferTooSmall(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EOutputBufferTooSmall(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EOutputBufferTooSmall(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EOutputBufferTooSmall(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EOutputBufferTooSmall(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EOutputBufferTooSmall(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EOutputBufferTooSmall(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EOutputBufferTooSmall(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EOutputBufferTooSmall(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBufferIsEmpty;
class PASCALIMPLEMENTATION EBufferIsEmpty : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBufferIsEmpty(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBufferIsEmpty(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBufferIsEmpty(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBufferIsEmpty(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBufferIsEmpty(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBufferIsEmpty(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBufferIsEmpty(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBufferIsEmpty(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBufferIsEmpty(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBufferIsEmpty(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETracingNotEnabled;
class PASCALIMPLEMENTATION ETracingNotEnabled : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETracingNotEnabled(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETracingNotEnabled(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETracingNotEnabled(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETracingNotEnabled(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETracingNotEnabled(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETracingNotEnabled(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETracingNotEnabled(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETracingNotEnabled(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETracingNotEnabled(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETracingNotEnabled(void) { }
	#pragma option pop
	
};


class DELPHICLASS ELoggingNotEnabled;
class PASCALIMPLEMENTATION ELoggingNotEnabled : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ELoggingNotEnabled(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ELoggingNotEnabled(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ELoggingNotEnabled(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ELoggingNotEnabled(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ELoggingNotEnabled(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ELoggingNotEnabled(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ELoggingNotEnabled(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ELoggingNotEnabled(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ELoggingNotEnabled(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ELoggingNotEnabled(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBaseAddressNotSet;
class PASCALIMPLEMENTATION EBaseAddressNotSet : public ESerialIO 
{
	typedef ESerialIO inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBaseAddressNotSet(const int EC, bool PassThru) : ESerialIO(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBaseAddressNotSet(const AnsiString Msg, Byte Dummy) : ESerialIO(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBaseAddressNotSet(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ESerialIO(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBaseAddressNotSet(int Ident)/* overload */ : ESerialIO(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBaseAddressNotSet(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ESerialIO(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBaseAddressNotSet(const AnsiString Msg, int AHelpContext) : ESerialIO(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBaseAddressNotSet(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ESerialIO(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBaseAddressNotSet(int Ident, int AHelpContext)/* overload */ : ESerialIO(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBaseAddressNotSet(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ESerialIO(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBaseAddressNotSet(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModemNotStarted;
class PASCALIMPLEMENTATION EModemNotStarted : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModemNotStarted(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModemNotStarted(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModemNotStarted(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModemNotStarted(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModemNotStarted(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModemNotStarted(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModemNotStarted(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModemNotStarted(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModemNotStarted(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModemNotStarted(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModemBusy;
class PASCALIMPLEMENTATION EModemBusy : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModemBusy(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModemBusy(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModemBusy(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModemBusy(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModemBusy(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModemBusy(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModemBusy(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModemBusy(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModemBusy(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModemBusy(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModemNotDialing;
class PASCALIMPLEMENTATION EModemNotDialing : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModemNotDialing(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModemNotDialing(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModemNotDialing(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModemNotDialing(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModemNotDialing(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModemNotDialing(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModemNotDialing(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModemNotDialing(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModemNotDialing(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModemNotDialing(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModemNotResponding;
class PASCALIMPLEMENTATION EModemNotResponding : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModemNotResponding(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModemNotResponding(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModemNotResponding(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModemNotResponding(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModemNotResponding(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModemNotResponding(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModemNotResponding(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModemNotResponding(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModemNotResponding(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModemNotResponding(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModemRejectedCommand;
class PASCALIMPLEMENTATION EModemRejectedCommand : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModemRejectedCommand(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModemRejectedCommand(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModemRejectedCommand(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModemRejectedCommand(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModemRejectedCommand(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModemRejectedCommand(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModemRejectedCommand(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModemRejectedCommand(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModemRejectedCommand(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModemRejectedCommand(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModemStatusMismatch;
class PASCALIMPLEMENTATION EModemStatusMismatch : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModemStatusMismatch(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModemStatusMismatch(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModemStatusMismatch(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModemStatusMismatch(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModemStatusMismatch(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModemStatusMismatch(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModemStatusMismatch(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModemStatusMismatch(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModemStatusMismatch(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModemStatusMismatch(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAlreadyDialing;
class PASCALIMPLEMENTATION EAlreadyDialing : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAlreadyDialing(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAlreadyDialing(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAlreadyDialing(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAlreadyDialing(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAlreadyDialing(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAlreadyDialing(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAlreadyDialing(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAlreadyDialing(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAlreadyDialing(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAlreadyDialing(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENotDialing;
class PASCALIMPLEMENTATION ENotDialing : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENotDialing(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENotDialing(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENotDialing(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENotDialing(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENotDialing(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENotDialing(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENotDialing(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENotDialing(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENotDialing(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENotDialing(void) { }
	#pragma option pop
	
};


class DELPHICLASS EDeviceNotSelected;
class PASCALIMPLEMENTATION EDeviceNotSelected : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EDeviceNotSelected(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EDeviceNotSelected(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDeviceNotSelected(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDeviceNotSelected(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDeviceNotSelected(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDeviceNotSelected(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDeviceNotSelected(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDeviceNotSelected(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDeviceNotSelected(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDeviceNotSelected(void) { }
	#pragma option pop
	
};


class DELPHICLASS EModemDetectedBusy;
class PASCALIMPLEMENTATION EModemDetectedBusy : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EModemDetectedBusy(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EModemDetectedBusy(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EModemDetectedBusy(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EModemDetectedBusy(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EModemDetectedBusy(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EModemDetectedBusy(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EModemDetectedBusy(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EModemDetectedBusy(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EModemDetectedBusy(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EModemDetectedBusy(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoDialtone;
class PASCALIMPLEMENTATION ENoDialtone : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoDialtone(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoDialtone(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoDialtone(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoDialtone(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoDialtone(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoDialtone(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoDialtone(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoDialtone(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoDialtone(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoDialtone(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoCarrier;
class PASCALIMPLEMENTATION ENoCarrier : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoCarrier(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoCarrier(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoCarrier(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoCarrier(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoCarrier(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoCarrier(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoCarrier(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoCarrier(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoCarrier(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoCarrier(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoAnswer;
class PASCALIMPLEMENTATION ENoAnswer : public EModem 
{
	typedef EModem inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoAnswer(const int EC, bool PassThru) : EModem(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoAnswer(const AnsiString Msg, Byte Dummy) : EModem(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoAnswer(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EModem(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoAnswer(int Ident)/* overload */ : EModem(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoAnswer(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EModem(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoAnswer(const AnsiString Msg, int AHelpContext) : EModem(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoAnswer(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EModem(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoAnswer(int Ident, int AHelpContext)/* overload */ : EModem(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoAnswer(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EModem(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoAnswer(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoMoreTriggers;
class PASCALIMPLEMENTATION ENoMoreTriggers : public ETrigger 
{
	typedef ETrigger inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoMoreTriggers(const int EC, bool PassThru) : ETrigger(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoMoreTriggers(const AnsiString Msg, Byte Dummy) : ETrigger(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoMoreTriggers(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETrigger(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoMoreTriggers(int Ident)/* overload */ : ETrigger(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoMoreTriggers(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETrigger(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoMoreTriggers(const AnsiString Msg, int AHelpContext) : ETrigger(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoMoreTriggers(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETrigger(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoMoreTriggers(int Ident, int AHelpContext)/* overload */ : ETrigger(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoMoreTriggers(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETrigger(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoMoreTriggers(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETriggerTooLong;
class PASCALIMPLEMENTATION ETriggerTooLong : public ETrigger 
{
	typedef ETrigger inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETriggerTooLong(const int EC, bool PassThru) : ETrigger(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETriggerTooLong(const AnsiString Msg, Byte Dummy) : ETrigger(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETriggerTooLong(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETrigger(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETriggerTooLong(int Ident)/* overload */ : ETrigger(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETriggerTooLong(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETrigger(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETriggerTooLong(const AnsiString Msg, int AHelpContext) : ETrigger(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETriggerTooLong(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETrigger(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETriggerTooLong(int Ident, int AHelpContext)/* overload */ : ETrigger(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETriggerTooLong(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETrigger(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETriggerTooLong(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBadTriggerHandle;
class PASCALIMPLEMENTATION EBadTriggerHandle : public ETrigger 
{
	typedef ETrigger inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBadTriggerHandle(const int EC, bool PassThru) : ETrigger(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBadTriggerHandle(const AnsiString Msg, Byte Dummy) : ETrigger(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBadTriggerHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETrigger(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBadTriggerHandle(int Ident)/* overload */ : ETrigger(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBadTriggerHandle(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETrigger(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBadTriggerHandle(const AnsiString Msg, int AHelpContext) : ETrigger(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBadTriggerHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETrigger(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBadTriggerHandle(int Ident, int AHelpContext)/* overload */ : ETrigger(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBadTriggerHandle(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETrigger(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBadTriggerHandle(void) { }
	#pragma option pop
	
};


class DELPHICLASS EInvalidProperty;
class PASCALIMPLEMENTATION EInvalidProperty : public EPacket 
{
	typedef EPacket inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EInvalidProperty(const int EC, bool PassThru) : EPacket(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EInvalidProperty(const AnsiString Msg, Byte Dummy) : EPacket(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EInvalidProperty(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EPacket(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EInvalidProperty(int Ident)/* overload */ : EPacket(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EInvalidProperty(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EPacket(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EInvalidProperty(const AnsiString Msg, int AHelpContext) : EPacket(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EInvalidProperty(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EPacket(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EInvalidProperty(int Ident, int AHelpContext)/* overload */ : EPacket(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalidProperty(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EPacket(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EInvalidProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS EStringSizeError;
class PASCALIMPLEMENTATION EStringSizeError : public EPacket 
{
	typedef EPacket inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EStringSizeError(const int EC, bool PassThru) : EPacket(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EStringSizeError(const AnsiString Msg, Byte Dummy) : EPacket(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EStringSizeError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EPacket(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EStringSizeError(int Ident)/* overload */ : EPacket(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EStringSizeError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EPacket(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EStringSizeError(const AnsiString Msg, int AHelpContext) : EPacket(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EStringSizeError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EPacket(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EStringSizeError(int Ident, int AHelpContext)/* overload */ : EPacket(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EStringSizeError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EPacket(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EStringSizeError(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETimeout;
class PASCALIMPLEMENTATION ETimeout : public EProtocol 
{
	typedef EProtocol inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETimeout(const int EC, bool PassThru) : EProtocol(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETimeout(const AnsiString Msg, Byte Dummy) : EProtocol(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETimeout(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EProtocol(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETimeout(int Ident)/* overload */ : EProtocol(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETimeout(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EProtocol(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETimeout(const AnsiString Msg, int AHelpContext) : EProtocol(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETimeout(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EProtocol(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETimeout(int Ident, int AHelpContext)/* overload */ : EProtocol(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETimeout(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EProtocol(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETimeout(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETooManyErrors;
class PASCALIMPLEMENTATION ETooManyErrors : public EProtocol 
{
	typedef EProtocol inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETooManyErrors(const int EC, bool PassThru) : EProtocol(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETooManyErrors(const AnsiString Msg, Byte Dummy) : EProtocol(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETooManyErrors(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EProtocol(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETooManyErrors(int Ident)/* overload */ : EProtocol(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETooManyErrors(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EProtocol(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETooManyErrors(const AnsiString Msg, int AHelpContext) : EProtocol(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETooManyErrors(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EProtocol(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETooManyErrors(int Ident, int AHelpContext)/* overload */ : EProtocol(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETooManyErrors(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EProtocol(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETooManyErrors(void) { }
	#pragma option pop
	
};


class DELPHICLASS ESequenceError;
class PASCALIMPLEMENTATION ESequenceError : public EProtocol 
{
	typedef EProtocol inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ESequenceError(const int EC, bool PassThru) : EProtocol(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ESequenceError(const AnsiString Msg, Byte Dummy) : EProtocol(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESequenceError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EProtocol(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESequenceError(int Ident)/* overload */ : EProtocol(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESequenceError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EProtocol(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESequenceError(const AnsiString Msg, int AHelpContext) : EProtocol(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESequenceError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EProtocol(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESequenceError(int Ident, int AHelpContext)/* overload */ : EProtocol(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESequenceError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EProtocol(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESequenceError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EKeyTooLong;
class PASCALIMPLEMENTATION EKeyTooLong : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EKeyTooLong(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EKeyTooLong(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EKeyTooLong(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EKeyTooLong(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EKeyTooLong(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EKeyTooLong(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EKeyTooLong(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EKeyTooLong(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EKeyTooLong(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EKeyTooLong(void) { }
	#pragma option pop
	
};


class DELPHICLASS EDataTooLarge;
class PASCALIMPLEMENTATION EDataTooLarge : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EDataTooLarge(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EDataTooLarge(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDataTooLarge(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDataTooLarge(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDataTooLarge(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDataTooLarge(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDataTooLarge(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDataTooLarge(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDataTooLarge(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDataTooLarge(void) { }
	#pragma option pop
	
};


class DELPHICLASS EIniWrite;
class PASCALIMPLEMENTATION EIniWrite : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EIniWrite(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EIniWrite(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EIniWrite(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EIniWrite(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EIniWrite(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EIniWrite(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EIniWrite(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EIniWrite(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EIniWrite(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EIniWrite(void) { }
	#pragma option pop
	
};


class DELPHICLASS EIniRead;
class PASCALIMPLEMENTATION EIniRead : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EIniRead(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EIniRead(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EIniRead(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EIniRead(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EIniRead(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EIniRead(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EIniRead(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EIniRead(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EIniRead(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EIniRead(void) { }
	#pragma option pop
	
};


class DELPHICLASS ERecordExists;
class PASCALIMPLEMENTATION ERecordExists : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ERecordExists(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ERecordExists(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ERecordExists(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ERecordExists(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ERecordExists(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ERecordExists(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ERecordExists(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ERecordExists(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ERecordExists(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ERecordExists(void) { }
	#pragma option pop
	
};


class DELPHICLASS ERecordNotFound;
class PASCALIMPLEMENTATION ERecordNotFound : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ERecordNotFound(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ERecordNotFound(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ERecordNotFound(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ERecordNotFound(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ERecordNotFound(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ERecordNotFound(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ERecordNotFound(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ERecordNotFound(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ERecordNotFound(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ERecordNotFound(void) { }
	#pragma option pop
	
};


class DELPHICLASS EDatabaseFull;
class PASCALIMPLEMENTATION EDatabaseFull : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EDatabaseFull(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EDatabaseFull(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDatabaseFull(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDatabaseFull(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDatabaseFull(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDatabaseFull(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDatabaseFull(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDatabaseFull(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDatabaseFull(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDatabaseFull(void) { }
	#pragma option pop
	
};


class DELPHICLASS EDatabaseEmpty;
class PASCALIMPLEMENTATION EDatabaseEmpty : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EDatabaseEmpty(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EDatabaseEmpty(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EDatabaseEmpty(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EDatabaseEmpty(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EDatabaseEmpty(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EDatabaseEmpty(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EDatabaseEmpty(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EDatabaseEmpty(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EDatabaseEmpty(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EDatabaseEmpty(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBadFieldList;
class PASCALIMPLEMENTATION EBadFieldList : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBadFieldList(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBadFieldList(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBadFieldList(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBadFieldList(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBadFieldList(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBadFieldList(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBadFieldList(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBadFieldList(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBadFieldList(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBadFieldList(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBadFieldForIndex;
class PASCALIMPLEMENTATION EBadFieldForIndex : public EINI 
{
	typedef EINI inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBadFieldForIndex(const int EC, bool PassThru) : EINI(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBadFieldForIndex(const AnsiString Msg, Byte Dummy) : EINI(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBadFieldForIndex(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EINI(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBadFieldForIndex(int Ident)/* overload */ : EINI(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBadFieldForIndex(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EINI(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBadFieldForIndex(const AnsiString Msg, int AHelpContext) : EINI(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBadFieldForIndex(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EINI(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBadFieldForIndex(int Ident, int AHelpContext)/* overload */ : EINI(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBadFieldForIndex(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EINI(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBadFieldForIndex(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxBadFormat;
class PASCALIMPLEMENTATION EFaxBadFormat : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxBadFormat(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxBadFormat(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxBadFormat(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxBadFormat(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxBadFormat(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxBadFormat(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxBadFormat(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxBadFormat(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxBadFormat(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxBadFormat(void) { }
	#pragma option pop
	
};


class DELPHICLASS EBadGraphicsFormat;
class PASCALIMPLEMENTATION EBadGraphicsFormat : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EBadGraphicsFormat(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EBadGraphicsFormat(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EBadGraphicsFormat(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EBadGraphicsFormat(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EBadGraphicsFormat(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EBadGraphicsFormat(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EBadGraphicsFormat(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EBadGraphicsFormat(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EBadGraphicsFormat(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EBadGraphicsFormat(void) { }
	#pragma option pop
	
};


class DELPHICLASS EConvertAbort;
class PASCALIMPLEMENTATION EConvertAbort : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EConvertAbort(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EConvertAbort(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EConvertAbort(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EConvertAbort(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EConvertAbort(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EConvertAbort(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EConvertAbort(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EConvertAbort(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EConvertAbort(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EConvertAbort(void) { }
	#pragma option pop
	
};


class DELPHICLASS EUnpackAbort;
class PASCALIMPLEMENTATION EUnpackAbort : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EUnpackAbort(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EUnpackAbort(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EUnpackAbort(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EUnpackAbort(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EUnpackAbort(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EUnpackAbort(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EUnpackAbort(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EUnpackAbort(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EUnpackAbort(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EUnpackAbort(void) { }
	#pragma option pop
	
};


class DELPHICLASS ECantMakeBitmap;
class PASCALIMPLEMENTATION ECantMakeBitmap : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ECantMakeBitmap(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ECantMakeBitmap(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ECantMakeBitmap(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ECantMakeBitmap(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ECantMakeBitmap(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ECantMakeBitmap(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ECantMakeBitmap(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ECantMakeBitmap(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ECantMakeBitmap(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ECantMakeBitmap(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoImageLoaded;
class PASCALIMPLEMENTATION ENoImageLoaded : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoImageLoaded(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoImageLoaded(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoImageLoaded(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoImageLoaded(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoImageLoaded(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoImageLoaded(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoImageLoaded(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoImageLoaded(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoImageLoaded(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoImageLoaded(void) { }
	#pragma option pop
	
};


class DELPHICLASS ENoImageBlockMarked;
class PASCALIMPLEMENTATION ENoImageBlockMarked : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ENoImageBlockMarked(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ENoImageBlockMarked(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ENoImageBlockMarked(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ENoImageBlockMarked(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ENoImageBlockMarked(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ENoImageBlockMarked(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ENoImageBlockMarked(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ENoImageBlockMarked(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ENoImageBlockMarked(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ENoImageBlockMarked(void) { }
	#pragma option pop
	
};


class DELPHICLASS EInvalidPageNumber;
class PASCALIMPLEMENTATION EInvalidPageNumber : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EInvalidPageNumber(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EInvalidPageNumber(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EInvalidPageNumber(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EInvalidPageNumber(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EInvalidPageNumber(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EInvalidPageNumber(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EInvalidPageNumber(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EInvalidPageNumber(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalidPageNumber(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EInvalidPageNumber(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxBadMachine;
class PASCALIMPLEMENTATION EFaxBadMachine : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxBadMachine(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxBadMachine(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxBadMachine(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxBadMachine(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxBadMachine(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxBadMachine(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxBadMachine(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxBadMachine(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxBadMachine(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxBadMachine(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxBadModemResult;
class PASCALIMPLEMENTATION EFaxBadModemResult : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxBadModemResult(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxBadModemResult(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxBadModemResult(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxBadModemResult(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxBadModemResult(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxBadModemResult(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxBadModemResult(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxBadModemResult(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxBadModemResult(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxBadModemResult(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxTrainError;
class PASCALIMPLEMENTATION EFaxTrainError : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxTrainError(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxTrainError(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxTrainError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxTrainError(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxTrainError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxTrainError(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxTrainError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxTrainError(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxTrainError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxTrainError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxInitError;
class PASCALIMPLEMENTATION EFaxInitError : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxInitError(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxInitError(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxInitError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxInitError(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxInitError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxInitError(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxInitError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxInitError(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxInitError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxInitError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxBusy;
class PASCALIMPLEMENTATION EFaxBusy : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxBusy(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxBusy(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxBusy(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxBusy(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxBusy(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxBusy(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxBusy(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxBusy(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxBusy(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxBusy(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxVoiceCall;
class PASCALIMPLEMENTATION EFaxVoiceCall : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxVoiceCall(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxVoiceCall(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxVoiceCall(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxVoiceCall(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxVoiceCall(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxVoiceCall(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxVoiceCall(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxVoiceCall(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxVoiceCall(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxVoiceCall(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxDataCall;
class PASCALIMPLEMENTATION EFaxDataCall : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxDataCall(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxDataCall(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxDataCall(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxDataCall(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxDataCall(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxDataCall(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxDataCall(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxDataCall(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxDataCall(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxDataCall(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxNoDialTone;
class PASCALIMPLEMENTATION EFaxNoDialTone : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxNoDialTone(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxNoDialTone(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxNoDialTone(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxNoDialTone(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxNoDialTone(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxNoDialTone(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxNoDialTone(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxNoDialTone(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxNoDialTone(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxNoDialTone(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxNoCarrier;
class PASCALIMPLEMENTATION EFaxNoCarrier : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxNoCarrier(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxNoCarrier(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxNoCarrier(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxNoCarrier(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxNoCarrier(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxNoCarrier(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxNoCarrier(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxNoCarrier(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxNoCarrier(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxNoCarrier(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxSessionError;
class PASCALIMPLEMENTATION EFaxSessionError : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxSessionError(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxSessionError(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxSessionError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxSessionError(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxSessionError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxSessionError(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxSessionError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxSessionError(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxSessionError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxSessionError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EFaxPageError;
class PASCALIMPLEMENTATION EFaxPageError : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EFaxPageError(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EFaxPageError(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EFaxPageError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EFaxPageError(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EFaxPageError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EFaxPageError(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EFaxPageError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EFaxPageError(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EFaxPageError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EFaxPageError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAlreadyMonitored;
class PASCALIMPLEMENTATION EAlreadyMonitored : public EFax 
{
	typedef EFax inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAlreadyMonitored(const int EC, bool PassThru) : EFax(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAlreadyMonitored(const AnsiString Msg, Byte Dummy) : EFax(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAlreadyMonitored(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EFax(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAlreadyMonitored(int Ident)/* overload */ : EFax(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAlreadyMonitored(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EFax(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAlreadyMonitored(const AnsiString Msg, int AHelpContext) : EFax(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAlreadyMonitored(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EFax(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAlreadyMonitored(int Ident, int AHelpContext)/* overload */ : EFax(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAlreadyMonitored(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EFax(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAlreadyMonitored(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiAllocated;
class PASCALIMPLEMENTATION ETapiAllocated : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiAllocated(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiAllocated(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiAllocated(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiAllocated(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiAllocated(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiAllocated(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiAllocated(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiAllocated(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiAllocated(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiAllocated(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiBadDeviceID;
class PASCALIMPLEMENTATION ETapiBadDeviceID : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiBadDeviceID(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiBadDeviceID(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiBadDeviceID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiBadDeviceID(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiBadDeviceID(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiBadDeviceID(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiBadDeviceID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiBadDeviceID(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiBadDeviceID(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiBadDeviceID(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiBearerModeUnavail;
class PASCALIMPLEMENTATION ETapiBearerModeUnavail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiBearerModeUnavail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiBearerModeUnavail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiBearerModeUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiBearerModeUnavail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiBearerModeUnavail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiBearerModeUnavail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiBearerModeUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiBearerModeUnavail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiBearerModeUnavail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiBearerModeUnavail(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiCallUnavail;
class PASCALIMPLEMENTATION ETapiCallUnavail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiCallUnavail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiCallUnavail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiCallUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiCallUnavail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiCallUnavail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiCallUnavail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiCallUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiCallUnavail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiCallUnavail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiCallUnavail(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiCompletionOverrun;
class PASCALIMPLEMENTATION ETapiCompletionOverrun : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiCompletionOverrun(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiCompletionOverrun(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiCompletionOverrun(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiCompletionOverrun(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiCompletionOverrun(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiCompletionOverrun(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiCompletionOverrun(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiCompletionOverrun(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiCompletionOverrun(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiCompletionOverrun(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiConferenceFull;
class PASCALIMPLEMENTATION ETapiConferenceFull : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiConferenceFull(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiConferenceFull(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiConferenceFull(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiConferenceFull(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiConferenceFull(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiConferenceFull(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiConferenceFull(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiConferenceFull(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiConferenceFull(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiConferenceFull(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiDialBilling;
class PASCALIMPLEMENTATION ETapiDialBilling : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiDialBilling(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiDialBilling(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiDialBilling(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiDialBilling(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiDialBilling(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiDialBilling(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiDialBilling(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiDialBilling(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiDialBilling(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiDialBilling(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiDialDialtone;
class PASCALIMPLEMENTATION ETapiDialDialtone : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiDialDialtone(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiDialDialtone(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiDialDialtone(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiDialDialtone(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiDialDialtone(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiDialDialtone(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiDialDialtone(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiDialDialtone(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiDialDialtone(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiDialDialtone(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiDialPrompt;
class PASCALIMPLEMENTATION ETapiDialPrompt : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiDialPrompt(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiDialPrompt(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiDialPrompt(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiDialPrompt(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiDialPrompt(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiDialPrompt(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiDialPrompt(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiDialPrompt(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiDialPrompt(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiDialPrompt(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiDialQuiet;
class PASCALIMPLEMENTATION ETapiDialQuiet : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiDialQuiet(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiDialQuiet(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiDialQuiet(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiDialQuiet(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiDialQuiet(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiDialQuiet(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiDialQuiet(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiDialQuiet(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiDialQuiet(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiDialQuiet(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiIncompatibleApiVersion;
class PASCALIMPLEMENTATION ETapiIncompatibleApiVersion : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiIncompatibleApiVersion(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiIncompatibleApiVersion(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiIncompatibleApiVersion(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiIncompatibleApiVersion(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiIncompatibleApiVersion(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiIncompatibleApiVersion(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiIncompatibleApiVersion(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiIncompatibleApiVersion(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiIncompatibleApiVersion(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiIncompatibleApiVersion(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiIncompatibleExtVersion;
class PASCALIMPLEMENTATION ETapiIncompatibleExtVersion : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiIncompatibleExtVersion(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiIncompatibleExtVersion(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiIncompatibleExtVersion(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiIncompatibleExtVersion(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiIncompatibleExtVersion(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiIncompatibleExtVersion(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiIncompatibleExtVersion(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiIncompatibleExtVersion(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiIncompatibleExtVersion(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiIncompatibleExtVersion(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiIniFileCorrupt;
class PASCALIMPLEMENTATION ETapiIniFileCorrupt : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiIniFileCorrupt(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiIniFileCorrupt(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiIniFileCorrupt(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiIniFileCorrupt(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiIniFileCorrupt(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiIniFileCorrupt(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiIniFileCorrupt(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiIniFileCorrupt(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiIniFileCorrupt(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiIniFileCorrupt(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInUse;
class PASCALIMPLEMENTATION ETapiInUse : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInUse(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInUse(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInUse(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInUse(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInUse(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInUse(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInUse(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInUse(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInUse(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInUse(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalAddress;
class PASCALIMPLEMENTATION ETapiInvalAddress : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalAddress(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalAddress(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalAddress(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalAddress(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalAddress(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalAddress(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalAddress(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalAddress(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalAddress(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalAddress(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalAddressID;
class PASCALIMPLEMENTATION ETapiInvalAddressID : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalAddressID(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalAddressID(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalAddressID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalAddressID(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalAddressID(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalAddressID(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalAddressID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalAddressID(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalAddressID(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalAddressID(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalAddressMode;
class PASCALIMPLEMENTATION ETapiInvalAddressMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalAddressMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalAddressMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalAddressMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalAddressMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalAddressMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalAddressMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalAddressMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalAddressMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalAddressMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalAddressMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalAddressState;
class PASCALIMPLEMENTATION ETapiInvalAddressState : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalAddressState(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalAddressState(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalAddressState(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalAddressState(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalAddressState(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalAddressState(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalAddressState(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalAddressState(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalAddressState(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalAddressState(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalAppHandle;
class PASCALIMPLEMENTATION ETapiInvalAppHandle : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalAppHandle(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalAppHandle(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalAppHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalAppHandle(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalAppHandle(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalAppHandle(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalAppHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalAppHandle(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalAppHandle(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalAppHandle(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalAppName;
class PASCALIMPLEMENTATION ETapiInvalAppName : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalAppName(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalAppName(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalAppName(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalAppName(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalAppName(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalAppName(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalAppName(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalAppName(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalAppName(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalAppName(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalBearerMode;
class PASCALIMPLEMENTATION ETapiInvalBearerMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalBearerMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalBearerMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalBearerMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalBearerMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalBearerMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalBearerMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalBearerMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalBearerMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalBearerMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalBearerMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCallComplMode;
class PASCALIMPLEMENTATION ETapiInvalCallComplMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCallComplMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCallComplMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCallComplMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCallComplMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCallComplMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCallComplMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCallComplMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCallComplMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCallComplMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCallComplMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCallHandle;
class PASCALIMPLEMENTATION ETapiInvalCallHandle : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCallHandle(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCallHandle(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCallHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCallHandle(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCallHandle(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCallHandle(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCallHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCallHandle(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCallHandle(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCallHandle(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCallParams;
class PASCALIMPLEMENTATION ETapiInvalCallParams : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCallParams(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCallParams(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCallParams(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCallParams(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCallParams(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCallParams(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCallParams(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCallParams(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCallParams(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCallParams(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCallPrivilege;
class PASCALIMPLEMENTATION ETapiInvalCallPrivilege : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCallPrivilege(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCallPrivilege(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCallPrivilege(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCallPrivilege(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCallPrivilege(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCallPrivilege(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCallPrivilege(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCallPrivilege(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCallPrivilege(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCallPrivilege(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCallSelect;
class PASCALIMPLEMENTATION ETapiInvalCallSelect : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCallSelect(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCallSelect(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCallSelect(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCallSelect(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCallSelect(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCallSelect(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCallSelect(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCallSelect(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCallSelect(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCallSelect(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCallState;
class PASCALIMPLEMENTATION ETapiInvalCallState : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCallState(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCallState(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCallState(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCallState(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCallState(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCallState(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCallState(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCallState(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCallState(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCallState(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCallStatelist;
class PASCALIMPLEMENTATION ETapiInvalCallStatelist : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCallStatelist(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCallStatelist(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCallStatelist(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCallStatelist(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCallStatelist(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCallStatelist(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCallStatelist(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCallStatelist(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCallStatelist(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCallStatelist(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCard;
class PASCALIMPLEMENTATION ETapiInvalCard : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCard(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCard(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCard(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCard(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCard(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCard(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCard(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCard(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCard(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCard(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCompletionID;
class PASCALIMPLEMENTATION ETapiInvalCompletionID : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCompletionID(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCompletionID(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCompletionID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCompletionID(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCompletionID(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCompletionID(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCompletionID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCompletionID(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCompletionID(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCompletionID(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalConfCallHandle;
class PASCALIMPLEMENTATION ETapiInvalConfCallHandle : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalConfCallHandle(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalConfCallHandle(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalConfCallHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalConfCallHandle(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalConfCallHandle(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalConfCallHandle(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalConfCallHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalConfCallHandle(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalConfCallHandle(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalConfCallHandle(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalConsultCallHandle;
class PASCALIMPLEMENTATION ETapiInvalConsultCallHandle : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalConsultCallHandle(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalConsultCallHandle(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalConsultCallHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalConsultCallHandle(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalConsultCallHandle(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalConsultCallHandle(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalConsultCallHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalConsultCallHandle(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalConsultCallHandle(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalConsultCallHandle(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalCountryCode;
class PASCALIMPLEMENTATION ETapiInvalCountryCode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalCountryCode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalCountryCode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalCountryCode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalCountryCode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalCountryCode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalCountryCode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalCountryCode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalCountryCode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalCountryCode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalCountryCode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalDeviceClass;
class PASCALIMPLEMENTATION ETapiInvalDeviceClass : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalDeviceClass(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalDeviceClass(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalDeviceClass(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalDeviceClass(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalDeviceClass(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalDeviceClass(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalDeviceClass(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalDeviceClass(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalDeviceClass(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalDeviceClass(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalDeviceHandle;
class PASCALIMPLEMENTATION ETapiInvalDeviceHandle : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalDeviceHandle(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalDeviceHandle(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalDeviceHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalDeviceHandle(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalDeviceHandle(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalDeviceHandle(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalDeviceHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalDeviceHandle(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalDeviceHandle(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalDeviceHandle(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalDialParams;
class PASCALIMPLEMENTATION ETapiInvalDialParams : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalDialParams(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalDialParams(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalDialParams(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalDialParams(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalDialParams(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalDialParams(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalDialParams(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalDialParams(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalDialParams(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalDialParams(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalDigitList;
class PASCALIMPLEMENTATION ETapiInvalDigitList : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalDigitList(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalDigitList(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalDigitList(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalDigitList(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalDigitList(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalDigitList(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalDigitList(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalDigitList(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalDigitList(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalDigitList(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalDigitMode;
class PASCALIMPLEMENTATION ETapiInvalDigitMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalDigitMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalDigitMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalDigitMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalDigitMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalDigitMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalDigitMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalDigitMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalDigitMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalDigitMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalDigitMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalDigits;
class PASCALIMPLEMENTATION ETapiInvalDigits : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalDigits(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalDigits(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalDigits(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalDigits(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalDigits(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalDigits(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalDigits(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalDigits(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalDigits(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalDigits(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalExtVersion;
class PASCALIMPLEMENTATION ETapiInvalExtVersion : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalExtVersion(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalExtVersion(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalExtVersion(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalExtVersion(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalExtVersion(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalExtVersion(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalExtVersion(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalExtVersion(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalExtVersion(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalExtVersion(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalGroupID;
class PASCALIMPLEMENTATION ETapiInvalGroupID : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalGroupID(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalGroupID(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalGroupID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalGroupID(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalGroupID(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalGroupID(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalGroupID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalGroupID(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalGroupID(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalGroupID(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalLineHandle;
class PASCALIMPLEMENTATION ETapiInvalLineHandle : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalLineHandle(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalLineHandle(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalLineHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalLineHandle(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalLineHandle(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalLineHandle(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalLineHandle(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalLineHandle(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalLineHandle(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalLineHandle(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalLineState;
class PASCALIMPLEMENTATION ETapiInvalLineState : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalLineState(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalLineState(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalLineState(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalLineState(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalLineState(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalLineState(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalLineState(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalLineState(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalLineState(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalLineState(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalLocation;
class PASCALIMPLEMENTATION ETapiInvalLocation : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalLocation(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalLocation(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalLocation(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalLocation(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalLocation(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalLocation(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalLocation(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalLocation(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalLocation(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalLocation(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalMediaList;
class PASCALIMPLEMENTATION ETapiInvalMediaList : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalMediaList(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalMediaList(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalMediaList(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalMediaList(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalMediaList(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalMediaList(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalMediaList(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalMediaList(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalMediaList(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalMediaList(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalMediaMode;
class PASCALIMPLEMENTATION ETapiInvalMediaMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalMediaMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalMediaMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalMediaMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalMediaMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalMediaMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalMediaMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalMediaMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalMediaMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalMediaMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalMediaMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalMessageID;
class PASCALIMPLEMENTATION ETapiInvalMessageID : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalMessageID(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalMessageID(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalMessageID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalMessageID(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalMessageID(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalMessageID(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalMessageID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalMessageID(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalMessageID(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalMessageID(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalParam;
class PASCALIMPLEMENTATION ETapiInvalParam : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalParam(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalParam(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalParam(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalParam(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalParam(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalParam(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalParam(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalParam(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalParam(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalParam(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalParkID;
class PASCALIMPLEMENTATION ETapiInvalParkID : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalParkID(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalParkID(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalParkID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalParkID(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalParkID(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalParkID(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalParkID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalParkID(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalParkID(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalParkID(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalParkMode;
class PASCALIMPLEMENTATION ETapiInvalParkMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalParkMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalParkMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalParkMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalParkMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalParkMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalParkMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalParkMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalParkMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalParkMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalParkMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalPointer;
class PASCALIMPLEMENTATION ETapiInvalPointer : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalPointer(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalPointer(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalPointer(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalPointer(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalPointer(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalPointer(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalPointer(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalPointer(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalPointer(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalPointer(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalPrivSelect;
class PASCALIMPLEMENTATION ETapiInvalPrivSelect : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalPrivSelect(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalPrivSelect(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalPrivSelect(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalPrivSelect(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalPrivSelect(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalPrivSelect(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalPrivSelect(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalPrivSelect(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalPrivSelect(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalPrivSelect(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalRate;
class PASCALIMPLEMENTATION ETapiInvalRate : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalRate(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalRate(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalRate(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalRate(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalRate(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalRate(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalRate(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalRate(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalRate(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalRate(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalRequestMode;
class PASCALIMPLEMENTATION ETapiInvalRequestMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalRequestMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalRequestMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalRequestMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalRequestMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalRequestMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalRequestMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalRequestMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalRequestMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalRequestMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalRequestMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalTerminalID;
class PASCALIMPLEMENTATION ETapiInvalTerminalID : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalTerminalID(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalTerminalID(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalTerminalID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalTerminalID(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalTerminalID(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalTerminalID(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalTerminalID(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalTerminalID(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalTerminalID(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalTerminalID(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalTerminalMode;
class PASCALIMPLEMENTATION ETapiInvalTerminalMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalTerminalMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalTerminalMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalTerminalMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalTerminalMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalTerminalMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalTerminalMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalTerminalMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalTerminalMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalTerminalMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalTerminalMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalTimeout;
class PASCALIMPLEMENTATION ETapiInvalTimeout : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalTimeout(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalTimeout(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalTimeout(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalTimeout(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalTimeout(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalTimeout(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalTimeout(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalTimeout(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalTimeout(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalTimeout(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalTone;
class PASCALIMPLEMENTATION ETapiInvalTone : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalTone(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalTone(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalTone(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalTone(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalTone(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalTone(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalTone(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalTone(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalTone(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalTone(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalToneList;
class PASCALIMPLEMENTATION ETapiInvalToneList : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalToneList(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalToneList(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalToneList(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalToneList(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalToneList(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalToneList(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalToneList(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalToneList(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalToneList(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalToneList(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalToneMode;
class PASCALIMPLEMENTATION ETapiInvalToneMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalToneMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalToneMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalToneMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalToneMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalToneMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalToneMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalToneMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalToneMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalToneMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalToneMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalTransferMode;
class PASCALIMPLEMENTATION ETapiInvalTransferMode : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalTransferMode(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalTransferMode(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalTransferMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalTransferMode(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalTransferMode(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalTransferMode(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalTransferMode(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalTransferMode(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalTransferMode(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalTransferMode(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiLineMapperFailed;
class PASCALIMPLEMENTATION ETapiLineMapperFailed : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiLineMapperFailed(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiLineMapperFailed(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiLineMapperFailed(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiLineMapperFailed(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiLineMapperFailed(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiLineMapperFailed(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiLineMapperFailed(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiLineMapperFailed(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiLineMapperFailed(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiLineMapperFailed(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNoConference;
class PASCALIMPLEMENTATION ETapiNoConference : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNoConference(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNoConference(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNoConference(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNoConference(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNoConference(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNoConference(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNoConference(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNoConference(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNoConference(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNoConference(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNoDevice;
class PASCALIMPLEMENTATION ETapiNoDevice : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNoDevice(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNoDevice(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNoDevice(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNoDevice(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNoDevice(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNoDevice(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNoDevice(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNoDevice(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNoDevice(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNoDevice(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNoDriver;
class PASCALIMPLEMENTATION ETapiNoDriver : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNoDriver(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNoDriver(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNoDriver(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNoDriver(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNoDriver(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNoDriver(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNoDriver(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNoDriver(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNoDriver(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNoDriver(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNoMem;
class PASCALIMPLEMENTATION ETapiNoMem : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNoMem(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNoMem(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNoMem(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNoMem(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNoMem(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNoMem(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNoMem(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNoMem(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNoMem(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNoMem(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNoRequest;
class PASCALIMPLEMENTATION ETapiNoRequest : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNoRequest(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNoRequest(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNoRequest(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNoRequest(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNoRequest(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNoRequest(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNoRequest(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNoRequest(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNoRequest(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNoRequest(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNotOwner;
class PASCALIMPLEMENTATION ETapiNotOwner : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNotOwner(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNotOwner(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNotOwner(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNotOwner(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNotOwner(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNotOwner(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNotOwner(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNotOwner(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNotOwner(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNotOwner(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNotRegistered;
class PASCALIMPLEMENTATION ETapiNotRegistered : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNotRegistered(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNotRegistered(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNotRegistered(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNotRegistered(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNotRegistered(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNotRegistered(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNotRegistered(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNotRegistered(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNotRegistered(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNotRegistered(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiOperationFailed;
class PASCALIMPLEMENTATION ETapiOperationFailed : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiOperationFailed(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiOperationFailed(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiOperationFailed(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiOperationFailed(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiOperationFailed(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiOperationFailed(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiOperationFailed(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiOperationFailed(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiOperationFailed(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiOperationFailed(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiOperationUnavail;
class PASCALIMPLEMENTATION ETapiOperationUnavail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiOperationUnavail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiOperationUnavail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiOperationUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiOperationUnavail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiOperationUnavail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiOperationUnavail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiOperationUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiOperationUnavail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiOperationUnavail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiOperationUnavail(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiRateUnavail;
class PASCALIMPLEMENTATION ETapiRateUnavail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiRateUnavail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiRateUnavail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiRateUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiRateUnavail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiRateUnavail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiRateUnavail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiRateUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiRateUnavail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiRateUnavail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiRateUnavail(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiResourceUnavail;
class PASCALIMPLEMENTATION ETapiResourceUnavail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiResourceUnavail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiResourceUnavail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiResourceUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiResourceUnavail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiResourceUnavail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiResourceUnavail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiResourceUnavail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiResourceUnavail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiResourceUnavail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiResourceUnavail(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiRequestOverrun;
class PASCALIMPLEMENTATION ETapiRequestOverrun : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiRequestOverrun(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiRequestOverrun(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiRequestOverrun(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiRequestOverrun(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiRequestOverrun(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiRequestOverrun(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiRequestOverrun(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiRequestOverrun(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiRequestOverrun(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiRequestOverrun(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiStructureTooSmall;
class PASCALIMPLEMENTATION ETapiStructureTooSmall : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiStructureTooSmall(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiStructureTooSmall(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiStructureTooSmall(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiStructureTooSmall(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiStructureTooSmall(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiStructureTooSmall(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiStructureTooSmall(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiStructureTooSmall(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiStructureTooSmall(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiStructureTooSmall(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiTargetNotFound;
class PASCALIMPLEMENTATION ETapiTargetNotFound : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiTargetNotFound(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiTargetNotFound(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiTargetNotFound(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiTargetNotFound(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiTargetNotFound(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiTargetNotFound(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiTargetNotFound(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiTargetNotFound(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiTargetNotFound(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiTargetNotFound(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiTargetSelf;
class PASCALIMPLEMENTATION ETapiTargetSelf : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiTargetSelf(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiTargetSelf(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiTargetSelf(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiTargetSelf(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiTargetSelf(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiTargetSelf(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiTargetSelf(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiTargetSelf(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiTargetSelf(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiTargetSelf(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiUninitialized;
class PASCALIMPLEMENTATION ETapiUninitialized : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiUninitialized(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiUninitialized(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiUninitialized(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiUninitialized(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiUninitialized(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiUninitialized(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiUninitialized(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiUninitialized(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiUninitialized(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiUninitialized(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiUserUserInfoTooBig;
class PASCALIMPLEMENTATION ETapiUserUserInfoTooBig : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiUserUserInfoTooBig(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiUserUserInfoTooBig(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiUserUserInfoTooBig(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiUserUserInfoTooBig(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiUserUserInfoTooBig(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiUserUserInfoTooBig(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiUserUserInfoTooBig(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiUserUserInfoTooBig(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiUserUserInfoTooBig(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiUserUserInfoTooBig(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiReinit;
class PASCALIMPLEMENTATION ETapiReinit : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiReinit(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiReinit(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiReinit(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiReinit(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiReinit(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiReinit(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiReinit(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiReinit(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiReinit(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiReinit(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiAddressBlocked;
class PASCALIMPLEMENTATION ETapiAddressBlocked : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiAddressBlocked(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiAddressBlocked(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiAddressBlocked(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiAddressBlocked(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiAddressBlocked(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiAddressBlocked(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiAddressBlocked(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiAddressBlocked(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiAddressBlocked(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiAddressBlocked(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiBillingRejected;
class PASCALIMPLEMENTATION ETapiBillingRejected : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiBillingRejected(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiBillingRejected(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiBillingRejected(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiBillingRejected(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiBillingRejected(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiBillingRejected(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiBillingRejected(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiBillingRejected(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiBillingRejected(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiBillingRejected(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiInvalFeature;
class PASCALIMPLEMENTATION ETapiInvalFeature : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiInvalFeature(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiInvalFeature(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiInvalFeature(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiInvalFeature(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiInvalFeature(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiInvalFeature(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiInvalFeature(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiInvalFeature(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiInvalFeature(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiInvalFeature(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNoMultipleInstance;
class PASCALIMPLEMENTATION ETapiNoMultipleInstance : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNoMultipleInstance(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNoMultipleInstance(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNoMultipleInstance(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNoMultipleInstance(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNoMultipleInstance(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNoMultipleInstance(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNoMultipleInstance(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNoMultipleInstance(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNoMultipleInstance(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNoMultipleInstance(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiBusy;
class PASCALIMPLEMENTATION ETapiBusy : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiBusy(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiBusy(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiBusy(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiBusy(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiBusy(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiBusy(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiBusy(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiBusy(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiBusy(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiBusy(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNotSet;
class PASCALIMPLEMENTATION ETapiNotSet : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNotSet(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNotSet(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNotSet(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNotSet(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNotSet(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNotSet(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNotSet(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNotSet(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNotSet(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNotSet(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiNoSelect;
class PASCALIMPLEMENTATION ETapiNoSelect : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiNoSelect(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiNoSelect(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiNoSelect(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiNoSelect(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiNoSelect(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiNoSelect(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiNoSelect(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiNoSelect(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiNoSelect(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiNoSelect(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiLoadFail;
class PASCALIMPLEMENTATION ETapiLoadFail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiLoadFail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiLoadFail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiLoadFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiLoadFail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiLoadFail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiLoadFail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiLoadFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiLoadFail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiLoadFail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiLoadFail(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiGetAddrFail;
class PASCALIMPLEMENTATION ETapiGetAddrFail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiGetAddrFail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiGetAddrFail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiGetAddrFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiGetAddrFail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiGetAddrFail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiGetAddrFail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiGetAddrFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiGetAddrFail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiGetAddrFail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiGetAddrFail(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiUnexpected;
class PASCALIMPLEMENTATION ETapiUnexpected : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiUnexpected(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiUnexpected(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiUnexpected(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiUnexpected(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiUnexpected(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiUnexpected(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiUnexpected(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiUnexpected(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiUnexpected(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiUnexpected(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiVoiceNotSupported;
class PASCALIMPLEMENTATION ETapiVoiceNotSupported : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiVoiceNotSupported(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiVoiceNotSupported(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiVoiceNotSupported(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiVoiceNotSupported(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiVoiceNotSupported(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiVoiceNotSupported(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiVoiceNotSupported(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiVoiceNotSupported(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiVoiceNotSupported(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiVoiceNotSupported(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiWaveFail;
class PASCALIMPLEMENTATION ETapiWaveFail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiWaveFail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiWaveFail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiWaveFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiWaveFail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiWaveFail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiWaveFail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiWaveFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiWaveFail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiWaveFail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiWaveFail(void) { }
	#pragma option pop
	
};


class DELPHICLASS ETapiTranslateFail;
class PASCALIMPLEMENTATION ETapiTranslateFail : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ETapiTranslateFail(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ETapiTranslateFail(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ETapiTranslateFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ETapiTranslateFail(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ETapiTranslateFail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ETapiTranslateFail(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ETapiTranslateFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ETapiTranslateFail(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ETapiTranslateFail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ETapiTranslateFail(void) { }
	#pragma option pop
	
};


class DELPHICLASS EVoIPNotSupported;
class PASCALIMPLEMENTATION EVoIPNotSupported : public ETapi 
{
	typedef ETapi inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EVoIPNotSupported(const int EC, bool PassThru) : ETapi(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EVoIPNotSupported(const AnsiString Msg, Byte Dummy) : ETapi(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EVoIPNotSupported(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ETapi(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EVoIPNotSupported(int Ident)/* overload */ : ETapi(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EVoIPNotSupported(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ETapi(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EVoIPNotSupported(const AnsiString Msg, int AHelpContext) : ETapi(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EVoIPNotSupported(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ETapi(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EVoIPNotSupported(int Ident, int AHelpContext)/* overload */ : ETapi(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EVoIPNotSupported(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ETapi(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EVoIPNotSupported(void) { }
	#pragma option pop
	
};


class DELPHICLASS ERasLoadFail;
class PASCALIMPLEMENTATION ERasLoadFail : public ERas 
{
	typedef ERas inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall ERasLoadFail(const int EC, bool PassThru) : ERas(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall ERasLoadFail(const AnsiString Msg, Byte Dummy) : ERas(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ERasLoadFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : ERas(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ERasLoadFail(int Ident)/* overload */ : ERas(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ERasLoadFail(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : ERas(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ERasLoadFail(const AnsiString Msg, int AHelpContext) : ERas(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ERasLoadFail(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : ERas(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ERasLoadFail(int Ident, int AHelpContext)/* overload */ : ERas(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ERasLoadFail(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : ERas(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ERasLoadFail(void) { }
	#pragma option pop
	
};


typedef TMetaClass*EAdTerminalClass;

class DELPHICLASS EAdTermRangeError;
class PASCALIMPLEMENTATION EAdTermRangeError : public EAdTerminal 
{
	typedef EAdTerminal inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAdTermRangeError(const int EC, bool PassThru) : EAdTerminal(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAdTermRangeError(const AnsiString Msg, Byte Dummy) : EAdTerminal(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAdTermRangeError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAdTerminal(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAdTermRangeError(int Ident)/* overload */ : EAdTerminal(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAdTermRangeError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAdTerminal(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAdTermRangeError(const AnsiString Msg, int AHelpContext) : EAdTerminal(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAdTermRangeError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAdTerminal(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAdTermRangeError(int Ident, int AHelpContext)/* overload */ : EAdTerminal(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdTermRangeError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAdTerminal(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAdTermRangeError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAdTermInvalidParameter;
class PASCALIMPLEMENTATION EAdTermInvalidParameter : public EAdTerminal 
{
	typedef EAdTerminal inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAdTermInvalidParameter(const int EC, bool PassThru) : EAdTerminal(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAdTermInvalidParameter(const AnsiString Msg, Byte Dummy) : EAdTerminal(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAdTermInvalidParameter(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAdTerminal(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAdTermInvalidParameter(int Ident)/* overload */ : EAdTerminal(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAdTermInvalidParameter(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAdTerminal(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAdTermInvalidParameter(const AnsiString Msg, int AHelpContext) : EAdTerminal(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAdTermInvalidParameter(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAdTerminal(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAdTermInvalidParameter(int Ident, int AHelpContext)/* overload */ : EAdTerminal(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdTermInvalidParameter(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAdTerminal(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAdTermInvalidParameter(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAdTermTooLarge;
class PASCALIMPLEMENTATION EAdTermTooLarge : public EAdTerminal 
{
	typedef EAdTerminal inherited;
	
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAdTermTooLarge(const int EC, bool PassThru) : EAdTerminal(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAdTermTooLarge(const AnsiString Msg, Byte Dummy) : EAdTerminal(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAdTermTooLarge(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAdTerminal(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAdTermTooLarge(int Ident)/* overload */ : EAdTerminal(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAdTermTooLarge(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAdTerminal(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAdTermTooLarge(const AnsiString Msg, int AHelpContext) : EAdTerminal(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAdTermTooLarge(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAdTerminal(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAdTermTooLarge(int Ident, int AHelpContext)/* overload */ : EAdTerminal(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdTermTooLarge(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAdTerminal(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAdTermTooLarge(void) { }
	#pragma option pop
	
};


class DELPHICLASS EApdPagerException;
class PASCALIMPLEMENTATION EApdPagerException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
private:
	int FErrorCode;
	
public:
	__fastcall EApdPagerException(const int ErrCode, const AnsiString Msg);
	
__published:
	__property int ErrorCode = {read=FErrorCode, nodefault};
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EApdPagerException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EApdPagerException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EApdPagerException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EApdPagerException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EApdPagerException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EApdPagerException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EApdPagerException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EApdPagerException(void) { }
	#pragma option pop
	
};


class DELPHICLASS EApdGSMPhoneException;
class PASCALIMPLEMENTATION EApdGSMPhoneException : public Sysutils::Exception 
{
	typedef Sysutils::Exception inherited;
	
private:
	int FErrorCode;
	
public:
	__fastcall EApdGSMPhoneException(const int ErrCode, const AnsiString Msg);
	
__published:
	__property int ErrorCode = {read=FErrorCode, nodefault};
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EApdGSMPhoneException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sysutils::Exception(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EApdGSMPhoneException(int Ident)/* overload */ : Sysutils::Exception(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EApdGSMPhoneException(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sysutils::Exception(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EApdGSMPhoneException(const AnsiString Msg, int AHelpContext) : Sysutils::Exception(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EApdGSMPhoneException(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sysutils::Exception(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EApdGSMPhoneException(int Ident, int AHelpContext)/* overload */ : Sysutils::Exception(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EApdGSMPhoneException(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sysutils::Exception(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EApdGSMPhoneException(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAdStreamError;
class PASCALIMPLEMENTATION EAdStreamError : public EXML 
{
	typedef EXML inherited;
	
private:
	int seFilePos;
	
public:
	__fastcall EAdStreamError(const int FilePos, const WideString Reason);
	__property int FilePos = {read=seFilePos, nodefault};
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAdStreamError(const int EC, bool PassThru) : EXML(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAdStreamError(const AnsiString Msg, Byte Dummy) : EXML(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAdStreamError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EXML(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAdStreamError(int Ident)/* overload */ : EXML(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAdStreamError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EXML(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAdStreamError(const AnsiString Msg, int AHelpContext) : EXML(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAdStreamError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EXML(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAdStreamError(int Ident, int AHelpContext)/* overload */ : EXML(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdStreamError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EXML(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAdStreamError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAdFilterError;
class PASCALIMPLEMENTATION EAdFilterError : public EAdStreamError 
{
	typedef EAdStreamError inherited;
	
private:
	WideString feReason;
	int feLine;
	int feLinePos;
	
public:
	__fastcall EAdFilterError(const int FilePos, const int Line, const int LinePos, const WideString Reason);
	__property WideString Reason = {read=feReason};
	__property int Line = {read=feLine, nodefault};
	__property int LinePos = {read=feLinePos, nodefault};
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAdFilterError(const int EC, bool PassThru) : EAdStreamError(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAdFilterError(const AnsiString Msg, Byte Dummy) : EAdStreamError(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAdFilterError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAdStreamError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAdFilterError(int Ident)/* overload */ : EAdStreamError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAdFilterError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAdStreamError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAdFilterError(const AnsiString Msg, int AHelpContext) : EAdStreamError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAdFilterError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAdStreamError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAdFilterError(int Ident, int AHelpContext)/* overload */ : EAdStreamError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdFilterError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAdStreamError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAdFilterError(void) { }
	#pragma option pop
	
};


class DELPHICLASS EAdParserError;
class PASCALIMPLEMENTATION EAdParserError : public EAdFilterError 
{
	typedef EAdFilterError inherited;
	
public:
	__fastcall EAdParserError(int Line, int LinePos, const WideString Reason);
public:
	#pragma option push -w-inl
	/* EAPDException.Create */ inline __fastcall EAdParserError(const int EC, bool PassThru) : EAdFilterError(EC, PassThru) { }
	#pragma option pop
	#pragma option push -w-inl
	/* EAPDException.CreateUnknown */ inline __fastcall EAdParserError(const AnsiString Msg, Byte Dummy) : EAdFilterError(Msg, Dummy) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall EAdParserError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : EAdFilterError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall EAdParserError(int Ident)/* overload */ : EAdFilterError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall EAdParserError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : EAdFilterError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall EAdParserError(const AnsiString Msg, int AHelpContext) : EAdFilterError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall EAdParserError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : EAdFilterError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall EAdParserError(int Ident, int AHelpContext)/* overload */ : EAdFilterError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdParserError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : EAdFilterError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~EAdParserError(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::ResourceString _secOK;
#define Adexcept_secOK System::LoadResourceString(&Adexcept::_secOK)
extern PACKAGE System::ResourceString _secFileNotFound;
#define Adexcept_secFileNotFound System::LoadResourceString(&Adexcept::_secFileNotFound)
extern PACKAGE System::ResourceString _secPathNotFound;
#define Adexcept_secPathNotFound System::LoadResourceString(&Adexcept::_secPathNotFound)
extern PACKAGE System::ResourceString _secTooManyFiles;
#define Adexcept_secTooManyFiles System::LoadResourceString(&Adexcept::_secTooManyFiles)
extern PACKAGE System::ResourceString _secAccessDenied;
#define Adexcept_secAccessDenied System::LoadResourceString(&Adexcept::_secAccessDenied)
extern PACKAGE System::ResourceString _secInvalidHandle;
#define Adexcept_secInvalidHandle System::LoadResourceString(&Adexcept::_secInvalidHandle)
extern PACKAGE System::ResourceString _secOutOfMemory;
#define Adexcept_secOutOfMemory System::LoadResourceString(&Adexcept::_secOutOfMemory)
extern PACKAGE System::ResourceString _secInvalidDrive;
#define Adexcept_secInvalidDrive System::LoadResourceString(&Adexcept::_secInvalidDrive)
extern PACKAGE System::ResourceString _secNoMoreFiles;
#define Adexcept_secNoMoreFiles System::LoadResourceString(&Adexcept::_secNoMoreFiles)
extern PACKAGE System::ResourceString _secDiskRead;
#define Adexcept_secDiskRead System::LoadResourceString(&Adexcept::_secDiskRead)
extern PACKAGE System::ResourceString _secDiskFull;
#define Adexcept_secDiskFull System::LoadResourceString(&Adexcept::_secDiskFull)
extern PACKAGE System::ResourceString _secNotAssigned;
#define Adexcept_secNotAssigned System::LoadResourceString(&Adexcept::_secNotAssigned)
extern PACKAGE System::ResourceString _secNotOpen;
#define Adexcept_secNotOpen System::LoadResourceString(&Adexcept::_secNotOpen)
extern PACKAGE System::ResourceString _secNotOpenInput;
#define Adexcept_secNotOpenInput System::LoadResourceString(&Adexcept::_secNotOpenInput)
extern PACKAGE System::ResourceString _secNotOpenOutput;
#define Adexcept_secNotOpenOutput System::LoadResourceString(&Adexcept::_secNotOpenOutput)
extern PACKAGE System::ResourceString _secWriteProtected;
#define Adexcept_secWriteProtected System::LoadResourceString(&Adexcept::_secWriteProtected)
extern PACKAGE System::ResourceString _secUnknownUnit;
#define Adexcept_secUnknownUnit System::LoadResourceString(&Adexcept::_secUnknownUnit)
extern PACKAGE System::ResourceString _secDriveNotReady;
#define Adexcept_secDriveNotReady System::LoadResourceString(&Adexcept::_secDriveNotReady)
extern PACKAGE System::ResourceString _secUnknownCommand;
#define Adexcept_secUnknownCommand System::LoadResourceString(&Adexcept::_secUnknownCommand)
extern PACKAGE System::ResourceString _secCrcError;
#define Adexcept_secCrcError System::LoadResourceString(&Adexcept::_secCrcError)
extern PACKAGE System::ResourceString _secBadStructLen;
#define Adexcept_secBadStructLen System::LoadResourceString(&Adexcept::_secBadStructLen)
extern PACKAGE System::ResourceString _secSeekError;
#define Adexcept_secSeekError System::LoadResourceString(&Adexcept::_secSeekError)
extern PACKAGE System::ResourceString _secUnknownMedia;
#define Adexcept_secUnknownMedia System::LoadResourceString(&Adexcept::_secUnknownMedia)
extern PACKAGE System::ResourceString _secSectorNotFound;
#define Adexcept_secSectorNotFound System::LoadResourceString(&Adexcept::_secSectorNotFound)
extern PACKAGE System::ResourceString _secOutOfPaper;
#define Adexcept_secOutOfPaper System::LoadResourceString(&Adexcept::_secOutOfPaper)
extern PACKAGE System::ResourceString _secDeviceWrite;
#define Adexcept_secDeviceWrite System::LoadResourceString(&Adexcept::_secDeviceWrite)
extern PACKAGE System::ResourceString _secDeviceRead;
#define Adexcept_secDeviceRead System::LoadResourceString(&Adexcept::_secDeviceRead)
extern PACKAGE System::ResourceString _secHardwareFailure;
#define Adexcept_secHardwareFailure System::LoadResourceString(&Adexcept::_secHardwareFailure)
extern PACKAGE System::ResourceString _secBadHandle;
#define Adexcept_secBadHandle System::LoadResourceString(&Adexcept::_secBadHandle)
extern PACKAGE System::ResourceString _secBadArgument;
#define Adexcept_secBadArgument System::LoadResourceString(&Adexcept::_secBadArgument)
extern PACKAGE System::ResourceString _secGotQuitMsg;
#define Adexcept_secGotQuitMsg System::LoadResourceString(&Adexcept::_secGotQuitMsg)
extern PACKAGE System::ResourceString _secBufferTooBig;
#define Adexcept_secBufferTooBig System::LoadResourceString(&Adexcept::_secBufferTooBig)
extern PACKAGE System::ResourceString _secPortNotAssigned;
#define Adexcept_secPortNotAssigned System::LoadResourceString(&Adexcept::_secPortNotAssigned)
extern PACKAGE System::ResourceString _secInternal;
#define Adexcept_secInternal System::LoadResourceString(&Adexcept::_secInternal)
extern PACKAGE System::ResourceString _secModemNotAssigned;
#define Adexcept_secModemNotAssigned System::LoadResourceString(&Adexcept::_secModemNotAssigned)
extern PACKAGE System::ResourceString _secPhonebookNotAssigned;
#define Adexcept_secPhonebookNotAssigned System::LoadResourceString(&Adexcept::_secPhonebookNotAssigned)
extern PACKAGE System::ResourceString _secCannotUseWithWinSock;
#define Adexcept_secCannotUseWithWinSock System::LoadResourceString(&Adexcept::_secCannotUseWithWinSock)
extern PACKAGE System::ResourceString _secBadId;
#define Adexcept_secBadId System::LoadResourceString(&Adexcept::_secBadId)
extern PACKAGE System::ResourceString _secBaudRate;
#define Adexcept_secBaudRate System::LoadResourceString(&Adexcept::_secBaudRate)
extern PACKAGE System::ResourceString _secByteSize;
#define Adexcept_secByteSize System::LoadResourceString(&Adexcept::_secByteSize)
extern PACKAGE System::ResourceString _secDefault;
#define Adexcept_secDefault System::LoadResourceString(&Adexcept::_secDefault)
extern PACKAGE System::ResourceString _secHardware;
#define Adexcept_secHardware System::LoadResourceString(&Adexcept::_secHardware)
extern PACKAGE System::ResourceString _secMemory;
#define Adexcept_secMemory System::LoadResourceString(&Adexcept::_secMemory)
extern PACKAGE System::ResourceString _secCommNotOpen;
#define Adexcept_secCommNotOpen System::LoadResourceString(&Adexcept::_secCommNotOpen)
extern PACKAGE System::ResourceString _secAlreadyOpen;
#define Adexcept_secAlreadyOpen System::LoadResourceString(&Adexcept::_secAlreadyOpen)
extern PACKAGE System::ResourceString _secNoHandles;
#define Adexcept_secNoHandles System::LoadResourceString(&Adexcept::_secNoHandles)
extern PACKAGE System::ResourceString _secNoTimers;
#define Adexcept_secNoTimers System::LoadResourceString(&Adexcept::_secNoTimers)
extern PACKAGE System::ResourceString _secNoPortSelected;
#define Adexcept_secNoPortSelected System::LoadResourceString(&Adexcept::_secNoPortSelected)
extern PACKAGE System::ResourceString _secNotOpenedByTapi;
#define Adexcept_secNotOpenedByTapi System::LoadResourceString(&Adexcept::_secNotOpenedByTapi)
extern PACKAGE System::ResourceString _secNullApi;
#define Adexcept_secNullApi System::LoadResourceString(&Adexcept::_secNullApi)
extern PACKAGE System::ResourceString _secNotSupported;
#define Adexcept_secNotSupported System::LoadResourceString(&Adexcept::_secNotSupported)
extern PACKAGE System::ResourceString _secRegisterHandlerFailed;
#define Adexcept_secRegisterHandlerFailed System::LoadResourceString(&Adexcept::_secRegisterHandlerFailed)
extern PACKAGE System::ResourceString _secPutBlockFail;
#define Adexcept_secPutBlockFail System::LoadResourceString(&Adexcept::_secPutBlockFail)
extern PACKAGE System::ResourceString _secGetBlockFail;
#define Adexcept_secGetBlockFail System::LoadResourceString(&Adexcept::_secGetBlockFail)
extern PACKAGE System::ResourceString _secOutputBufferTooSmall;
#define Adexcept_secOutputBufferTooSmall System::LoadResourceString(&Adexcept::_secOutputBufferTooSmall)
extern PACKAGE System::ResourceString _secBufferIsEmpty;
#define Adexcept_secBufferIsEmpty System::LoadResourceString(&Adexcept::_secBufferIsEmpty)
extern PACKAGE System::ResourceString _secTracingNotEnabled;
#define Adexcept_secTracingNotEnabled System::LoadResourceString(&Adexcept::_secTracingNotEnabled)
extern PACKAGE System::ResourceString _secLoggingNotEnabled;
#define Adexcept_secLoggingNotEnabled System::LoadResourceString(&Adexcept::_secLoggingNotEnabled)
extern PACKAGE System::ResourceString _secBaseAddressNotSet;
#define Adexcept_secBaseAddressNotSet System::LoadResourceString(&Adexcept::_secBaseAddressNotSet)
extern PACKAGE System::ResourceString _secModemNotStarted;
#define Adexcept_secModemNotStarted System::LoadResourceString(&Adexcept::_secModemNotStarted)
extern PACKAGE System::ResourceString _secModemBusy;
#define Adexcept_secModemBusy System::LoadResourceString(&Adexcept::_secModemBusy)
extern PACKAGE System::ResourceString _secModemNotDialing;
#define Adexcept_secModemNotDialing System::LoadResourceString(&Adexcept::_secModemNotDialing)
extern PACKAGE System::ResourceString _secNotDialing;
#define Adexcept_secNotDialing System::LoadResourceString(&Adexcept::_secNotDialing)
extern PACKAGE System::ResourceString _secAlreadyDialing;
#define Adexcept_secAlreadyDialing System::LoadResourceString(&Adexcept::_secAlreadyDialing)
extern PACKAGE System::ResourceString _secModemNotResponding;
#define Adexcept_secModemNotResponding System::LoadResourceString(&Adexcept::_secModemNotResponding)
extern PACKAGE System::ResourceString _secModemRejectedCommand;
#define Adexcept_secModemRejectedCommand System::LoadResourceString(&Adexcept::_secModemRejectedCommand)
extern PACKAGE System::ResourceString _secModemStatusMismatch;
#define Adexcept_secModemStatusMismatch System::LoadResourceString(&Adexcept::_secModemStatusMismatch)
extern PACKAGE System::ResourceString _secDeviceNotSelected;
#define Adexcept_secDeviceNotSelected System::LoadResourceString(&Adexcept::_secDeviceNotSelected)
extern PACKAGE System::ResourceString _secModemDetectedBusy;
#define Adexcept_secModemDetectedBusy System::LoadResourceString(&Adexcept::_secModemDetectedBusy)
extern PACKAGE System::ResourceString _secModemNoDialtone;
#define Adexcept_secModemNoDialtone System::LoadResourceString(&Adexcept::_secModemNoDialtone)
extern PACKAGE System::ResourceString _secModemNoCarrier;
#define Adexcept_secModemNoCarrier System::LoadResourceString(&Adexcept::_secModemNoCarrier)
extern PACKAGE System::ResourceString _secModemNoAnswer;
#define Adexcept_secModemNoAnswer System::LoadResourceString(&Adexcept::_secModemNoAnswer)
extern PACKAGE System::ResourceString _secInitFail;
#define Adexcept_secInitFail System::LoadResourceString(&Adexcept::_secInitFail)
extern PACKAGE System::ResourceString _secLoginFail;
#define Adexcept_secLoginFail System::LoadResourceString(&Adexcept::_secLoginFail)
extern PACKAGE System::ResourceString _secMinorSrvErr;
#define Adexcept_secMinorSrvErr System::LoadResourceString(&Adexcept::_secMinorSrvErr)
extern PACKAGE System::ResourceString _secFatalSrvErr;
#define Adexcept_secFatalSrvErr System::LoadResourceString(&Adexcept::_secFatalSrvErr)
extern PACKAGE System::ResourceString _secModemNotFound;
#define Adexcept_secModemNotFound System::LoadResourceString(&Adexcept::_secModemNotFound)
extern PACKAGE System::ResourceString _secInvalidFile;
#define Adexcept_secInvalidFile System::LoadResourceString(&Adexcept::_secInvalidFile)
extern PACKAGE System::ResourceString _spbeDeleteQuery;
#define Adexcept_spbeDeleteQuery System::LoadResourceString(&Adexcept::_spbeDeleteQuery)
extern PACKAGE System::ResourceString _sdsmMsgBase;
#define Adexcept_sdsmMsgBase System::LoadResourceString(&Adexcept::_sdsmMsgBase)
extern PACKAGE System::ResourceString _sdsmMsgReady;
#define Adexcept_sdsmMsgReady System::LoadResourceString(&Adexcept::_sdsmMsgReady)
extern PACKAGE System::ResourceString _sdsmMsgInitialize;
#define Adexcept_sdsmMsgInitialize System::LoadResourceString(&Adexcept::_sdsmMsgInitialize)
extern PACKAGE System::ResourceString _sdsmMsgInitializeTimeout;
#define Adexcept_sdsmMsgInitializeTimeout System::LoadResourceString(&Adexcept::_sdsmMsgInitializeTimeout)
extern PACKAGE System::ResourceString _sdsmMsgAutoAnswerBackground;
#define Adexcept_sdsmMsgAutoAnswerBackground System::LoadResourceString(&Adexcept::_sdsmMsgAutoAnswerBackground)
extern PACKAGE System::ResourceString _sdsmMsgAutoAnswerWait;
#define Adexcept_sdsmMsgAutoAnswerWait System::LoadResourceString(&Adexcept::_sdsmMsgAutoAnswerWait)
extern PACKAGE System::ResourceString _sdsmMsgAnswerWait;
#define Adexcept_sdsmMsgAnswerWait System::LoadResourceString(&Adexcept::_sdsmMsgAnswerWait)
extern PACKAGE System::ResourceString _sdsmMsgDialWait;
#define Adexcept_sdsmMsgDialWait System::LoadResourceString(&Adexcept::_sdsmMsgDialWait)
extern PACKAGE System::ResourceString _sdsmMsgDialCycle;
#define Adexcept_sdsmMsgDialCycle System::LoadResourceString(&Adexcept::_sdsmMsgDialCycle)
extern PACKAGE System::ResourceString _sdsmMsgNoDialtone;
#define Adexcept_sdsmMsgNoDialtone System::LoadResourceString(&Adexcept::_sdsmMsgNoDialtone)
extern PACKAGE System::ResourceString _sdsmMsgConnectWait;
#define Adexcept_sdsmMsgConnectWait System::LoadResourceString(&Adexcept::_sdsmMsgConnectWait)
extern PACKAGE System::ResourceString _sdsmMsgConnected;
#define Adexcept_sdsmMsgConnected System::LoadResourceString(&Adexcept::_sdsmMsgConnected)
extern PACKAGE System::ResourceString _sdsmMsgHangup;
#define Adexcept_sdsmMsgHangup System::LoadResourceString(&Adexcept::_sdsmMsgHangup)
extern PACKAGE System::ResourceString _sdsmMsgCancel;
#define Adexcept_sdsmMsgCancel System::LoadResourceString(&Adexcept::_sdsmMsgCancel)
extern PACKAGE System::ResourceString _sdddCycling;
#define Adexcept_sdddCycling System::LoadResourceString(&Adexcept::_sdddCycling)
extern PACKAGE System::ResourceString _sdddRetryWaiting;
#define Adexcept_sdddRetryWaiting System::LoadResourceString(&Adexcept::_sdddRetryWaiting)
extern PACKAGE System::ResourceString _sdddRetryWaitOver;
#define Adexcept_sdddRetryWaitOver System::LoadResourceString(&Adexcept::_sdddRetryWaitOver)
extern PACKAGE System::ResourceString _sdddDialing;
#define Adexcept_sdddDialing System::LoadResourceString(&Adexcept::_sdddDialing)
extern PACKAGE System::ResourceString _sdddModemConnect;
#define Adexcept_sdddModemConnect System::LoadResourceString(&Adexcept::_sdddModemConnect)
extern PACKAGE System::ResourceString _sdddModemConnectAt;
#define Adexcept_sdddModemConnectAt System::LoadResourceString(&Adexcept::_sdddModemConnectAt)
extern PACKAGE System::ResourceString _sdddModemVoice;
#define Adexcept_sdddModemVoice System::LoadResourceString(&Adexcept::_sdddModemVoice)
extern PACKAGE System::ResourceString _sdddModemError;
#define Adexcept_sdddModemError System::LoadResourceString(&Adexcept::_sdddModemError)
extern PACKAGE System::ResourceString _sdddModemNoCarrier;
#define Adexcept_sdddModemNoCarrier System::LoadResourceString(&Adexcept::_sdddModemNoCarrier)
extern PACKAGE System::ResourceString _sdddModemBusy;
#define Adexcept_sdddModemBusy System::LoadResourceString(&Adexcept::_sdddModemBusy)
extern PACKAGE System::ResourceString _sdddModemNoDialTone;
#define Adexcept_sdddModemNoDialTone System::LoadResourceString(&Adexcept::_sdddModemNoDialTone)
extern PACKAGE System::ResourceString _sdddDialTimedOut;
#define Adexcept_sdddDialTimedOut System::LoadResourceString(&Adexcept::_sdddDialTimedOut)
extern PACKAGE System::ResourceString _sdpeMustEnterName;
#define Adexcept_sdpeMustEnterName System::LoadResourceString(&Adexcept::_sdpeMustEnterName)
extern PACKAGE System::ResourceString _sdpeMustEnterNumber;
#define Adexcept_sdpeMustEnterNumber System::LoadResourceString(&Adexcept::_sdpeMustEnterNumber)
extern PACKAGE System::ResourceString _sdpeNameExists;
#define Adexcept_sdpeNameExists System::LoadResourceString(&Adexcept::_sdpeNameExists)
extern PACKAGE System::ResourceString _scsOpenPort;
#define Adexcept_scsOpenPort System::LoadResourceString(&Adexcept::_scsOpenPort)
extern PACKAGE System::ResourceString _scsPortOpened;
#define Adexcept_scsPortOpened System::LoadResourceString(&Adexcept::_scsPortOpened)
extern PACKAGE System::ResourceString _scsConnectDevice;
#define Adexcept_scsConnectDevice System::LoadResourceString(&Adexcept::_scsConnectDevice)
extern PACKAGE System::ResourceString _scsDeviceConnected;
#define Adexcept_scsDeviceConnected System::LoadResourceString(&Adexcept::_scsDeviceConnected)
extern PACKAGE System::ResourceString _scsAllDevicesConnected;
#define Adexcept_scsAllDevicesConnected System::LoadResourceString(&Adexcept::_scsAllDevicesConnected)
extern PACKAGE System::ResourceString _scsAuthenticate;
#define Adexcept_scsAuthenticate System::LoadResourceString(&Adexcept::_scsAuthenticate)
extern PACKAGE System::ResourceString _scsAuthNotify;
#define Adexcept_scsAuthNotify System::LoadResourceString(&Adexcept::_scsAuthNotify)
extern PACKAGE System::ResourceString _scsAuthRetry;
#define Adexcept_scsAuthRetry System::LoadResourceString(&Adexcept::_scsAuthRetry)
extern PACKAGE System::ResourceString _scsAuthCallback;
#define Adexcept_scsAuthCallback System::LoadResourceString(&Adexcept::_scsAuthCallback)
extern PACKAGE System::ResourceString _scsAuthChangePassword;
#define Adexcept_scsAuthChangePassword System::LoadResourceString(&Adexcept::_scsAuthChangePassword)
extern PACKAGE System::ResourceString _scsAuthProject;
#define Adexcept_scsAuthProject System::LoadResourceString(&Adexcept::_scsAuthProject)
extern PACKAGE System::ResourceString _scsAuthLinkSpeed;
#define Adexcept_scsAuthLinkSpeed System::LoadResourceString(&Adexcept::_scsAuthLinkSpeed)
extern PACKAGE System::ResourceString _scsAuthAck;
#define Adexcept_scsAuthAck System::LoadResourceString(&Adexcept::_scsAuthAck)
extern PACKAGE System::ResourceString _scsReAuthenticate;
#define Adexcept_scsReAuthenticate System::LoadResourceString(&Adexcept::_scsReAuthenticate)
extern PACKAGE System::ResourceString _scsAuthenticated;
#define Adexcept_scsAuthenticated System::LoadResourceString(&Adexcept::_scsAuthenticated)
extern PACKAGE System::ResourceString _scsPrepareForCallback;
#define Adexcept_scsPrepareForCallback System::LoadResourceString(&Adexcept::_scsPrepareForCallback)
extern PACKAGE System::ResourceString _scsWaitForModemReset;
#define Adexcept_scsWaitForModemReset System::LoadResourceString(&Adexcept::_scsWaitForModemReset)
extern PACKAGE System::ResourceString _scsWaitForCallback;
#define Adexcept_scsWaitForCallback System::LoadResourceString(&Adexcept::_scsWaitForCallback)
extern PACKAGE System::ResourceString _scsProjected;
#define Adexcept_scsProjected System::LoadResourceString(&Adexcept::_scsProjected)
extern PACKAGE System::ResourceString _scsStartAuthentication;
#define Adexcept_scsStartAuthentication System::LoadResourceString(&Adexcept::_scsStartAuthentication)
extern PACKAGE System::ResourceString _scsCallbackComplete;
#define Adexcept_scsCallbackComplete System::LoadResourceString(&Adexcept::_scsCallbackComplete)
extern PACKAGE System::ResourceString _scsLogonNetwork;
#define Adexcept_scsLogonNetwork System::LoadResourceString(&Adexcept::_scsLogonNetwork)
extern PACKAGE System::ResourceString _scsSubEntryConnected;
#define Adexcept_scsSubEntryConnected System::LoadResourceString(&Adexcept::_scsSubEntryConnected)
extern PACKAGE System::ResourceString _scsSubEntryDisconnected;
#define Adexcept_scsSubEntryDisconnected System::LoadResourceString(&Adexcept::_scsSubEntryDisconnected)
extern PACKAGE System::ResourceString _scsRasInteractive;
#define Adexcept_scsRasInteractive System::LoadResourceString(&Adexcept::_scsRasInteractive)
extern PACKAGE System::ResourceString _scsRasRetryAuthentication;
#define Adexcept_scsRasRetryAuthentication System::LoadResourceString(&Adexcept::_scsRasRetryAuthentication)
extern PACKAGE System::ResourceString _scsRasCallbackSetByCaller;
#define Adexcept_scsRasCallbackSetByCaller System::LoadResourceString(&Adexcept::_scsRasCallbackSetByCaller)
extern PACKAGE System::ResourceString _scsRasPasswordExpired;
#define Adexcept_scsRasPasswordExpired System::LoadResourceString(&Adexcept::_scsRasPasswordExpired)
extern PACKAGE System::ResourceString _scsRasDeviceConnected;
#define Adexcept_scsRasDeviceConnected System::LoadResourceString(&Adexcept::_scsRasDeviceConnected)
extern PACKAGE System::ResourceString _sPDS_NONE;
#define Adexcept_sPDS_NONE System::LoadResourceString(&Adexcept::_sPDS_NONE)
extern PACKAGE System::ResourceString _sPDS_OFFHOOK;
#define Adexcept_sPDS_OFFHOOK System::LoadResourceString(&Adexcept::_sPDS_OFFHOOK)
extern PACKAGE System::ResourceString _sPDS_DIALING;
#define Adexcept_sPDS_DIALING System::LoadResourceString(&Adexcept::_sPDS_DIALING)
extern PACKAGE System::ResourceString _sPDS_RINGING;
#define Adexcept_sPDS_RINGING System::LoadResourceString(&Adexcept::_sPDS_RINGING)
extern PACKAGE System::ResourceString _sPDS_WAITFORCONNECT;
#define Adexcept_sPDS_WAITFORCONNECT System::LoadResourceString(&Adexcept::_sPDS_WAITFORCONNECT)
extern PACKAGE System::ResourceString _sPDS_CONNECTED;
#define Adexcept_sPDS_CONNECTED System::LoadResourceString(&Adexcept::_sPDS_CONNECTED)
extern PACKAGE System::ResourceString _sPDS_WAITINGTOREDIAL;
#define Adexcept_sPDS_WAITINGTOREDIAL System::LoadResourceString(&Adexcept::_sPDS_WAITINGTOREDIAL)
extern PACKAGE System::ResourceString _sPDS_REDIALING;
#define Adexcept_sPDS_REDIALING System::LoadResourceString(&Adexcept::_sPDS_REDIALING)
extern PACKAGE System::ResourceString _sPDS_MSGNOTSENT;
#define Adexcept_sPDS_MSGNOTSENT System::LoadResourceString(&Adexcept::_sPDS_MSGNOTSENT)
extern PACKAGE System::ResourceString _sPDS_CANCELLING;
#define Adexcept_sPDS_CANCELLING System::LoadResourceString(&Adexcept::_sPDS_CANCELLING)
extern PACKAGE System::ResourceString _sPDS_DISCONNECT;
#define Adexcept_sPDS_DISCONNECT System::LoadResourceString(&Adexcept::_sPDS_DISCONNECT)
extern PACKAGE System::ResourceString _sPDS_CLEANUP;
#define Adexcept_sPDS_CLEANUP System::LoadResourceString(&Adexcept::_sPDS_CLEANUP)
extern PACKAGE System::ResourceString _sPDE_NONE;
#define Adexcept_sPDE_NONE System::LoadResourceString(&Adexcept::_sPDE_NONE)
extern PACKAGE System::ResourceString _sPDE_NODIALTONE;
#define Adexcept_sPDE_NODIALTONE System::LoadResourceString(&Adexcept::_sPDE_NODIALTONE)
extern PACKAGE System::ResourceString _sPDE_LINEBUSY;
#define Adexcept_sPDE_LINEBUSY System::LoadResourceString(&Adexcept::_sPDE_LINEBUSY)
extern PACKAGE System::ResourceString _sPDE_NOCONNECTION;
#define Adexcept_sPDE_NOCONNECTION System::LoadResourceString(&Adexcept::_sPDE_NOCONNECTION)
extern PACKAGE System::ResourceString _sTAPS_NONE;
#define Adexcept_sTAPS_NONE System::LoadResourceString(&Adexcept::_sTAPS_NONE)
extern PACKAGE System::ResourceString _sTAPS_LOGINPROMPT;
#define Adexcept_sTAPS_LOGINPROMPT System::LoadResourceString(&Adexcept::_sTAPS_LOGINPROMPT)
extern PACKAGE System::ResourceString _sTAPS_LOGGEDIN;
#define Adexcept_sTAPS_LOGGEDIN System::LoadResourceString(&Adexcept::_sTAPS_LOGGEDIN)
extern PACKAGE System::ResourceString _sTAPS_LOGINERR;
#define Adexcept_sTAPS_LOGINERR System::LoadResourceString(&Adexcept::_sTAPS_LOGINERR)
extern PACKAGE System::ResourceString _sTAPS_LOGINFAIL;
#define Adexcept_sTAPS_LOGINFAIL System::LoadResourceString(&Adexcept::_sTAPS_LOGINFAIL)
extern PACKAGE System::ResourceString _sTAPS_MSGOKTOSEND;
#define Adexcept_sTAPS_MSGOKTOSEND System::LoadResourceString(&Adexcept::_sTAPS_MSGOKTOSEND)
extern PACKAGE System::ResourceString _sTAPS_SENDINGMSG;
#define Adexcept_sTAPS_SENDINGMSG System::LoadResourceString(&Adexcept::_sTAPS_SENDINGMSG)
extern PACKAGE System::ResourceString _sTAPS_MSGACK;
#define Adexcept_sTAPS_MSGACK System::LoadResourceString(&Adexcept::_sTAPS_MSGACK)
extern PACKAGE System::ResourceString _sTAPS_MSGNAK;
#define Adexcept_sTAPS_MSGNAK System::LoadResourceString(&Adexcept::_sTAPS_MSGNAK)
extern PACKAGE System::ResourceString _sTAPS_MSGRS;
#define Adexcept_sTAPS_MSGRS System::LoadResourceString(&Adexcept::_sTAPS_MSGRS)
extern PACKAGE System::ResourceString _sTAPS_MSGCOMPLETED;
#define Adexcept_sTAPS_MSGCOMPLETED System::LoadResourceString(&Adexcept::_sTAPS_MSGCOMPLETED)
extern PACKAGE System::ResourceString _sTAPS_DONE;
#define Adexcept_sTAPS_DONE System::LoadResourceString(&Adexcept::_sTAPS_DONE)
extern PACKAGE System::ResourceString _spsOK;
#define Adexcept_spsOK System::LoadResourceString(&Adexcept::_spsOK)
extern PACKAGE System::ResourceString _spsProtocolHandshake;
#define Adexcept_spsProtocolHandshake System::LoadResourceString(&Adexcept::_spsProtocolHandshake)
extern PACKAGE System::ResourceString _spsInvalidDate;
#define Adexcept_spsInvalidDate System::LoadResourceString(&Adexcept::_spsInvalidDate)
extern PACKAGE System::ResourceString _spsFileRejected;
#define Adexcept_spsFileRejected System::LoadResourceString(&Adexcept::_spsFileRejected)
extern PACKAGE System::ResourceString _spsFileRenamed;
#define Adexcept_spsFileRenamed System::LoadResourceString(&Adexcept::_spsFileRenamed)
extern PACKAGE System::ResourceString _spsSkipFile;
#define Adexcept_spsSkipFile System::LoadResourceString(&Adexcept::_spsSkipFile)
extern PACKAGE System::ResourceString _spsFileDoesntExist;
#define Adexcept_spsFileDoesntExist System::LoadResourceString(&Adexcept::_spsFileDoesntExist)
extern PACKAGE System::ResourceString _spsCantWriteFile;
#define Adexcept_spsCantWriteFile System::LoadResourceString(&Adexcept::_spsCantWriteFile)
extern PACKAGE System::ResourceString _spsTimeout;
#define Adexcept_spsTimeout System::LoadResourceString(&Adexcept::_spsTimeout)
extern PACKAGE System::ResourceString _spsBlockCheckError;
#define Adexcept_spsBlockCheckError System::LoadResourceString(&Adexcept::_spsBlockCheckError)
extern PACKAGE System::ResourceString _spsLongPacket;
#define Adexcept_spsLongPacket System::LoadResourceString(&Adexcept::_spsLongPacket)
extern PACKAGE System::ResourceString _spsDuplicateBlock;
#define Adexcept_spsDuplicateBlock System::LoadResourceString(&Adexcept::_spsDuplicateBlock)
extern PACKAGE System::ResourceString _spsProtocolError;
#define Adexcept_spsProtocolError System::LoadResourceString(&Adexcept::_spsProtocolError)
extern PACKAGE System::ResourceString _spsCancelRequested;
#define Adexcept_spsCancelRequested System::LoadResourceString(&Adexcept::_spsCancelRequested)
extern PACKAGE System::ResourceString _spsEndFile;
#define Adexcept_spsEndFile System::LoadResourceString(&Adexcept::_spsEndFile)
extern PACKAGE System::ResourceString _spsResumeBad;
#define Adexcept_spsResumeBad System::LoadResourceString(&Adexcept::_spsResumeBad)
extern PACKAGE System::ResourceString _spsSequenceError;
#define Adexcept_spsSequenceError System::LoadResourceString(&Adexcept::_spsSequenceError)
extern PACKAGE System::ResourceString _spsAbortNoCarrier;
#define Adexcept_spsAbortNoCarrier System::LoadResourceString(&Adexcept::_spsAbortNoCarrier)
extern PACKAGE System::ResourceString _spsGotCrcE;
#define Adexcept_spsGotCrcE System::LoadResourceString(&Adexcept::_spsGotCrcE)
extern PACKAGE System::ResourceString _spsGotCrcG;
#define Adexcept_spsGotCrcG System::LoadResourceString(&Adexcept::_spsGotCrcG)
extern PACKAGE System::ResourceString _spsGotCrcW;
#define Adexcept_spsGotCrcW System::LoadResourceString(&Adexcept::_spsGotCrcW)
extern PACKAGE System::ResourceString _spsGotCrcQ;
#define Adexcept_spsGotCrcQ System::LoadResourceString(&Adexcept::_spsGotCrcQ)
extern PACKAGE System::ResourceString _spsTryResume;
#define Adexcept_spsTryResume System::LoadResourceString(&Adexcept::_spsTryResume)
extern PACKAGE System::ResourceString _spsHostResume;
#define Adexcept_spsHostResume System::LoadResourceString(&Adexcept::_spsHostResume)
extern PACKAGE System::ResourceString _spsWaitAck;
#define Adexcept_spsWaitAck System::LoadResourceString(&Adexcept::_spsWaitAck)
extern PACKAGE System::ResourceString _spsNoHeader;
#define Adexcept_spsNoHeader System::LoadResourceString(&Adexcept::_spsNoHeader)
extern PACKAGE System::ResourceString _spsGotHeader;
#define Adexcept_spsGotHeader System::LoadResourceString(&Adexcept::_spsGotHeader)
extern PACKAGE System::ResourceString _spsGotData;
#define Adexcept_spsGotData System::LoadResourceString(&Adexcept::_spsGotData)
extern PACKAGE System::ResourceString _spsNoData;
#define Adexcept_spsNoData System::LoadResourceString(&Adexcept::_spsNoData)
extern PACKAGE System::ResourceString _spsAbort;
#define Adexcept_spsAbort System::LoadResourceString(&Adexcept::_spsAbort)
extern PACKAGE System::ResourceString _sfpInitModem;
#define Adexcept_sfpInitModem System::LoadResourceString(&Adexcept::_sfpInitModem)
extern PACKAGE System::ResourceString _sfpDialing;
#define Adexcept_sfpDialing System::LoadResourceString(&Adexcept::_sfpDialing)
extern PACKAGE System::ResourceString _sfpBusyWait;
#define Adexcept_sfpBusyWait System::LoadResourceString(&Adexcept::_sfpBusyWait)
extern PACKAGE System::ResourceString _sfpSendPage;
#define Adexcept_sfpSendPage System::LoadResourceString(&Adexcept::_sfpSendPage)
extern PACKAGE System::ResourceString _sfpSendPageStatus;
#define Adexcept_sfpSendPageStatus System::LoadResourceString(&Adexcept::_sfpSendPageStatus)
extern PACKAGE System::ResourceString _sfpPageError;
#define Adexcept_sfpPageError System::LoadResourceString(&Adexcept::_sfpPageError)
extern PACKAGE System::ResourceString _sfpPageOK;
#define Adexcept_sfpPageOK System::LoadResourceString(&Adexcept::_sfpPageOK)
extern PACKAGE System::ResourceString _sfpConnecting;
#define Adexcept_sfpConnecting System::LoadResourceString(&Adexcept::_sfpConnecting)
extern PACKAGE System::ResourceString _sfpWaiting;
#define Adexcept_sfpWaiting System::LoadResourceString(&Adexcept::_sfpWaiting)
extern PACKAGE System::ResourceString _sfpNoConnect;
#define Adexcept_sfpNoConnect System::LoadResourceString(&Adexcept::_sfpNoConnect)
extern PACKAGE System::ResourceString _sfpAnswer;
#define Adexcept_sfpAnswer System::LoadResourceString(&Adexcept::_sfpAnswer)
extern PACKAGE System::ResourceString _sfpIncoming;
#define Adexcept_sfpIncoming System::LoadResourceString(&Adexcept::_sfpIncoming)
extern PACKAGE System::ResourceString _sfpGetPage;
#define Adexcept_sfpGetPage System::LoadResourceString(&Adexcept::_sfpGetPage)
extern PACKAGE System::ResourceString _sfpGetPageResult;
#define Adexcept_sfpGetPageResult System::LoadResourceString(&Adexcept::_sfpGetPageResult)
extern PACKAGE System::ResourceString _sfpCheckMorePages;
#define Adexcept_sfpCheckMorePages System::LoadResourceString(&Adexcept::_sfpCheckMorePages)
extern PACKAGE System::ResourceString _sfpGetHangup;
#define Adexcept_sfpGetHangup System::LoadResourceString(&Adexcept::_sfpGetHangup)
extern PACKAGE System::ResourceString _sfpGotHangup;
#define Adexcept_sfpGotHangup System::LoadResourceString(&Adexcept::_sfpGotHangup)
extern PACKAGE System::ResourceString _sfpSwitchModes;
#define Adexcept_sfpSwitchModes System::LoadResourceString(&Adexcept::_sfpSwitchModes)
extern PACKAGE System::ResourceString _sfpMonitorEnabled;
#define Adexcept_sfpMonitorEnabled System::LoadResourceString(&Adexcept::_sfpMonitorEnabled)
extern PACKAGE System::ResourceString _sfpMonitorDisabled;
#define Adexcept_sfpMonitorDisabled System::LoadResourceString(&Adexcept::_sfpMonitorDisabled)
extern PACKAGE System::ResourceString _sfpSessionParams;
#define Adexcept_sfpSessionParams System::LoadResourceString(&Adexcept::_sfpSessionParams)
extern PACKAGE System::ResourceString _sfpGotRemoteID;
#define Adexcept_sfpGotRemoteID System::LoadResourceString(&Adexcept::_sfpGotRemoteID)
extern PACKAGE System::ResourceString _sfpCancel;
#define Adexcept_sfpCancel System::LoadResourceString(&Adexcept::_sfpCancel)
extern PACKAGE System::ResourceString _sfpFinished;
#define Adexcept_sfpFinished System::LoadResourceString(&Adexcept::_sfpFinished)
extern PACKAGE System::ResourceString _secNoMoreTriggers;
#define Adexcept_secNoMoreTriggers System::LoadResourceString(&Adexcept::_secNoMoreTriggers)
extern PACKAGE System::ResourceString _secTriggerTooLong;
#define Adexcept_secTriggerTooLong System::LoadResourceString(&Adexcept::_secTriggerTooLong)
extern PACKAGE System::ResourceString _secBadTriggerHandle;
#define Adexcept_secBadTriggerHandle System::LoadResourceString(&Adexcept::_secBadTriggerHandle)
extern PACKAGE System::ResourceString _secStartStringEmpty;
#define Adexcept_secStartStringEmpty System::LoadResourceString(&Adexcept::_secStartStringEmpty)
extern PACKAGE System::ResourceString _secPacketTooSmall;
#define Adexcept_secPacketTooSmall System::LoadResourceString(&Adexcept::_secPacketTooSmall)
extern PACKAGE System::ResourceString _secNoEndCharCount;
#define Adexcept_secNoEndCharCount System::LoadResourceString(&Adexcept::_secNoEndCharCount)
extern PACKAGE System::ResourceString _secEmptyEndString;
#define Adexcept_secEmptyEndString System::LoadResourceString(&Adexcept::_secEmptyEndString)
extern PACKAGE System::ResourceString _secZeroSizePacket;
#define Adexcept_secZeroSizePacket System::LoadResourceString(&Adexcept::_secZeroSizePacket)
extern PACKAGE System::ResourceString _secPacketTooLong;
#define Adexcept_secPacketTooLong System::LoadResourceString(&Adexcept::_secPacketTooLong)
extern PACKAGE System::ResourceString _secBadFileList;
#define Adexcept_secBadFileList System::LoadResourceString(&Adexcept::_secBadFileList)
extern PACKAGE System::ResourceString _secNoSearchMask;
#define Adexcept_secNoSearchMask System::LoadResourceString(&Adexcept::_secNoSearchMask)
extern PACKAGE System::ResourceString _secNoMatchingFiles;
#define Adexcept_secNoMatchingFiles System::LoadResourceString(&Adexcept::_secNoMatchingFiles)
extern PACKAGE System::ResourceString _secDirNotFound;
#define Adexcept_secDirNotFound System::LoadResourceString(&Adexcept::_secDirNotFound)
extern PACKAGE System::ResourceString _secCancelRequested;
#define Adexcept_secCancelRequested System::LoadResourceString(&Adexcept::_secCancelRequested)
extern PACKAGE System::ResourceString _secTimeout;
#define Adexcept_secTimeout System::LoadResourceString(&Adexcept::_secTimeout)
extern PACKAGE System::ResourceString _secProtocolError;
#define Adexcept_secProtocolError System::LoadResourceString(&Adexcept::_secProtocolError)
extern PACKAGE System::ResourceString _secTooManyErrors;
#define Adexcept_secTooManyErrors System::LoadResourceString(&Adexcept::_secTooManyErrors)
extern PACKAGE System::ResourceString _secSequenceError;
#define Adexcept_secSequenceError System::LoadResourceString(&Adexcept::_secSequenceError)
extern PACKAGE System::ResourceString _secNoFilename;
#define Adexcept_secNoFilename System::LoadResourceString(&Adexcept::_secNoFilename)
extern PACKAGE System::ResourceString _secFileRejected;
#define Adexcept_secFileRejected System::LoadResourceString(&Adexcept::_secFileRejected)
extern PACKAGE System::ResourceString _secCantWriteFile;
#define Adexcept_secCantWriteFile System::LoadResourceString(&Adexcept::_secCantWriteFile)
extern PACKAGE System::ResourceString _secTableFull;
#define Adexcept_secTableFull System::LoadResourceString(&Adexcept::_secTableFull)
extern PACKAGE System::ResourceString _secAbortNoCarrier;
#define Adexcept_secAbortNoCarrier System::LoadResourceString(&Adexcept::_secAbortNoCarrier)
extern PACKAGE System::ResourceString _secBadProtocolFunction;
#define Adexcept_secBadProtocolFunction System::LoadResourceString(&Adexcept::_secBadProtocolFunction)
extern PACKAGE System::ResourceString _secProtocolAbort;
#define Adexcept_secProtocolAbort System::LoadResourceString(&Adexcept::_secProtocolAbort)
extern PACKAGE System::ResourceString _secKeyTooLong;
#define Adexcept_secKeyTooLong System::LoadResourceString(&Adexcept::_secKeyTooLong)
extern PACKAGE System::ResourceString _secDataTooLarge;
#define Adexcept_secDataTooLarge System::LoadResourceString(&Adexcept::_secDataTooLarge)
extern PACKAGE System::ResourceString _secNoFieldsDefined;
#define Adexcept_secNoFieldsDefined System::LoadResourceString(&Adexcept::_secNoFieldsDefined)
extern PACKAGE System::ResourceString _secIniWrite;
#define Adexcept_secIniWrite System::LoadResourceString(&Adexcept::_secIniWrite)
extern PACKAGE System::ResourceString _secIniRead;
#define Adexcept_secIniRead System::LoadResourceString(&Adexcept::_secIniRead)
extern PACKAGE System::ResourceString _secNoIndexKey;
#define Adexcept_secNoIndexKey System::LoadResourceString(&Adexcept::_secNoIndexKey)
extern PACKAGE System::ResourceString _secRecordExists;
#define Adexcept_secRecordExists System::LoadResourceString(&Adexcept::_secRecordExists)
extern PACKAGE System::ResourceString _secRecordNotFound;
#define Adexcept_secRecordNotFound System::LoadResourceString(&Adexcept::_secRecordNotFound)
extern PACKAGE System::ResourceString _secMustHaveIdxVal;
#define Adexcept_secMustHaveIdxVal System::LoadResourceString(&Adexcept::_secMustHaveIdxVal)
extern PACKAGE System::ResourceString _secDatabaseFull;
#define Adexcept_secDatabaseFull System::LoadResourceString(&Adexcept::_secDatabaseFull)
extern PACKAGE System::ResourceString _secDatabaseEmpty;
#define Adexcept_secDatabaseEmpty System::LoadResourceString(&Adexcept::_secDatabaseEmpty)
extern PACKAGE System::ResourceString _secDatabaseNotPrepared;
#define Adexcept_secDatabaseNotPrepared System::LoadResourceString(&Adexcept::_secDatabaseNotPrepared)
extern PACKAGE System::ResourceString _secBadFieldList;
#define Adexcept_secBadFieldList System::LoadResourceString(&Adexcept::_secBadFieldList)
extern PACKAGE System::ResourceString _secBadFieldForIndex;
#define Adexcept_secBadFieldForIndex System::LoadResourceString(&Adexcept::_secBadFieldForIndex)
extern PACKAGE System::ResourceString _secNoStateMachine;
#define Adexcept_secNoStateMachine System::LoadResourceString(&Adexcept::_secNoStateMachine)
extern PACKAGE System::ResourceString _secNoStartState;
#define Adexcept_secNoStartState System::LoadResourceString(&Adexcept::_secNoStartState)
extern PACKAGE System::ResourceString _secNoSapiEngine;
#define Adexcept_secNoSapiEngine System::LoadResourceString(&Adexcept::_secNoSapiEngine)
extern PACKAGE System::ResourceString _secFaxBadFormat;
#define Adexcept_secFaxBadFormat System::LoadResourceString(&Adexcept::_secFaxBadFormat)
extern PACKAGE System::ResourceString _secBadGraphicsFormat;
#define Adexcept_secBadGraphicsFormat System::LoadResourceString(&Adexcept::_secBadGraphicsFormat)
extern PACKAGE System::ResourceString _secConvertAbort;
#define Adexcept_secConvertAbort System::LoadResourceString(&Adexcept::_secConvertAbort)
extern PACKAGE System::ResourceString _secUnpackAbort;
#define Adexcept_secUnpackAbort System::LoadResourceString(&Adexcept::_secUnpackAbort)
extern PACKAGE System::ResourceString _secCantMakeBitmap;
#define Adexcept_secCantMakeBitmap System::LoadResourceString(&Adexcept::_secCantMakeBitmap)
extern PACKAGE System::ResourceString _secNoImageLoaded;
#define Adexcept_secNoImageLoaded System::LoadResourceString(&Adexcept::_secNoImageLoaded)
extern PACKAGE System::ResourceString _secNoImageBlockMarked;
#define Adexcept_secNoImageBlockMarked System::LoadResourceString(&Adexcept::_secNoImageBlockMarked)
extern PACKAGE System::ResourceString _secFontFileNotFound;
#define Adexcept_secFontFileNotFound System::LoadResourceString(&Adexcept::_secFontFileNotFound)
extern PACKAGE System::ResourceString _secInvalidPageNumber;
#define Adexcept_secInvalidPageNumber System::LoadResourceString(&Adexcept::_secInvalidPageNumber)
extern PACKAGE System::ResourceString _secBmpTooBig;
#define Adexcept_secBmpTooBig System::LoadResourceString(&Adexcept::_secBmpTooBig)
extern PACKAGE System::ResourceString _secEnhFontTooBig;
#define Adexcept_secEnhFontTooBig System::LoadResourceString(&Adexcept::_secEnhFontTooBig)
extern PACKAGE System::ResourceString _secFaxBadMachine;
#define Adexcept_secFaxBadMachine System::LoadResourceString(&Adexcept::_secFaxBadMachine)
extern PACKAGE System::ResourceString _secFaxBadModemResult;
#define Adexcept_secFaxBadModemResult System::LoadResourceString(&Adexcept::_secFaxBadModemResult)
extern PACKAGE System::ResourceString _secFaxTrainError;
#define Adexcept_secFaxTrainError System::LoadResourceString(&Adexcept::_secFaxTrainError)
extern PACKAGE System::ResourceString _secFaxInitError;
#define Adexcept_secFaxInitError System::LoadResourceString(&Adexcept::_secFaxInitError)
extern PACKAGE System::ResourceString _secFaxBusy;
#define Adexcept_secFaxBusy System::LoadResourceString(&Adexcept::_secFaxBusy)
extern PACKAGE System::ResourceString _secFaxVoiceCall;
#define Adexcept_secFaxVoiceCall System::LoadResourceString(&Adexcept::_secFaxVoiceCall)
extern PACKAGE System::ResourceString _secFaxDataCall;
#define Adexcept_secFaxDataCall System::LoadResourceString(&Adexcept::_secFaxDataCall)
extern PACKAGE System::ResourceString _secFaxNoDialTone;
#define Adexcept_secFaxNoDialTone System::LoadResourceString(&Adexcept::_secFaxNoDialTone)
extern PACKAGE System::ResourceString _secFaxNoCarrier;
#define Adexcept_secFaxNoCarrier System::LoadResourceString(&Adexcept::_secFaxNoCarrier)
extern PACKAGE System::ResourceString _secFaxSessionError;
#define Adexcept_secFaxSessionError System::LoadResourceString(&Adexcept::_secFaxSessionError)
extern PACKAGE System::ResourceString _secFaxPageError;
#define Adexcept_secFaxPageError System::LoadResourceString(&Adexcept::_secFaxPageError)
extern PACKAGE System::ResourceString _secFaxGDIPrintError;
#define Adexcept_secFaxGDIPrintError System::LoadResourceString(&Adexcept::_secFaxGDIPrintError)
extern PACKAGE System::ResourceString _secFaxMixedResolution;
#define Adexcept_secFaxMixedResolution System::LoadResourceString(&Adexcept::_secFaxMixedResolution)
extern PACKAGE System::ResourceString _secFaxConverterInitFail;
#define Adexcept_secFaxConverterInitFail System::LoadResourceString(&Adexcept::_secFaxConverterInitFail)
extern PACKAGE System::ResourceString _secNoAnswer;
#define Adexcept_secNoAnswer System::LoadResourceString(&Adexcept::_secNoAnswer)
extern PACKAGE System::ResourceString _secAlreadyMonitored;
#define Adexcept_secAlreadyMonitored System::LoadResourceString(&Adexcept::_secAlreadyMonitored)
extern PACKAGE System::ResourceString _secUniAlreadyInstalled;
#define Adexcept_secUniAlreadyInstalled System::LoadResourceString(&Adexcept::_secUniAlreadyInstalled)
extern PACKAGE System::ResourceString _secUniCannotGetSysDir;
#define Adexcept_secUniCannotGetSysDir System::LoadResourceString(&Adexcept::_secUniCannotGetSysDir)
extern PACKAGE System::ResourceString _secUniCannotGetWinDir;
#define Adexcept_secUniCannotGetWinDir System::LoadResourceString(&Adexcept::_secUniCannotGetWinDir)
extern PACKAGE System::ResourceString _secUniUnknownLayout;
#define Adexcept_secUniUnknownLayout System::LoadResourceString(&Adexcept::_secUniUnknownLayout)
extern PACKAGE System::ResourceString _secUniCannotInstallFile;
#define Adexcept_secUniCannotInstallFile System::LoadResourceString(&Adexcept::_secUniCannotInstallFile)
extern PACKAGE System::ResourceString _secDrvCopyError;
#define Adexcept_secDrvCopyError System::LoadResourceString(&Adexcept::_secDrvCopyError)
extern PACKAGE System::ResourceString _secCannotAddPrinter;
#define Adexcept_secCannotAddPrinter System::LoadResourceString(&Adexcept::_secCannotAddPrinter)
extern PACKAGE System::ResourceString _secDrvBadResources;
#define Adexcept_secDrvBadResources System::LoadResourceString(&Adexcept::_secDrvBadResources)
extern PACKAGE System::ResourceString _secDrvDriverNotFound;
#define Adexcept_secDrvDriverNotFound System::LoadResourceString(&Adexcept::_secDrvDriverNotFound)
extern PACKAGE System::ResourceString _secUniCannotGetPrinterDriverDir;
#define Adexcept_secUniCannotGetPrinterDriverDir System::LoadResourceString(&Adexcept::_secUniCannotGetPrinterDriverDir)
extern PACKAGE System::ResourceString _secInstallDriverFailed;
#define Adexcept_secInstallDriverFailed System::LoadResourceString(&Adexcept::_secInstallDriverFailed)
extern PACKAGE System::ResourceString _secSMSBusy;
#define Adexcept_secSMSBusy System::LoadResourceString(&Adexcept::_secSMSBusy)
extern PACKAGE System::ResourceString _secSMSTimedOut;
#define Adexcept_secSMSTimedOut System::LoadResourceString(&Adexcept::_secSMSTimedOut)
extern PACKAGE System::ResourceString _secSMSTooLong;
#define Adexcept_secSMSTooLong System::LoadResourceString(&Adexcept::_secSMSTooLong)
extern PACKAGE System::ResourceString _secSMSUnknownStatus;
#define Adexcept_secSMSUnknownStatus System::LoadResourceString(&Adexcept::_secSMSUnknownStatus)
extern PACKAGE System::ResourceString _secSMSInvalidNumber;
#define Adexcept_secSMSInvalidNumber System::LoadResourceString(&Adexcept::_secSMSInvalidNumber)
extern PACKAGE System::ResourceString _secMEFailure;
#define Adexcept_secMEFailure System::LoadResourceString(&Adexcept::_secMEFailure)
extern PACKAGE System::ResourceString _secServiceRes;
#define Adexcept_secServiceRes System::LoadResourceString(&Adexcept::_secServiceRes)
extern PACKAGE System::ResourceString _secBadOperation;
#define Adexcept_secBadOperation System::LoadResourceString(&Adexcept::_secBadOperation)
extern PACKAGE System::ResourceString _secUnsupported;
#define Adexcept_secUnsupported System::LoadResourceString(&Adexcept::_secUnsupported)
extern PACKAGE System::ResourceString _secInvalidPDU;
#define Adexcept_secInvalidPDU System::LoadResourceString(&Adexcept::_secInvalidPDU)
extern PACKAGE System::ResourceString _secInvalidText;
#define Adexcept_secInvalidText System::LoadResourceString(&Adexcept::_secInvalidText)
extern PACKAGE System::ResourceString _secSIMInsert;
#define Adexcept_secSIMInsert System::LoadResourceString(&Adexcept::_secSIMInsert)
extern PACKAGE System::ResourceString _secSIMPin;
#define Adexcept_secSIMPin System::LoadResourceString(&Adexcept::_secSIMPin)
extern PACKAGE System::ResourceString _secSIMPH;
#define Adexcept_secSIMPH System::LoadResourceString(&Adexcept::_secSIMPH)
extern PACKAGE System::ResourceString _secSIMFailure;
#define Adexcept_secSIMFailure System::LoadResourceString(&Adexcept::_secSIMFailure)
extern PACKAGE System::ResourceString _secSIMBusy;
#define Adexcept_secSIMBusy System::LoadResourceString(&Adexcept::_secSIMBusy)
extern PACKAGE System::ResourceString _secSIMWrong;
#define Adexcept_secSIMWrong System::LoadResourceString(&Adexcept::_secSIMWrong)
extern PACKAGE System::ResourceString _secSIMPUK;
#define Adexcept_secSIMPUK System::LoadResourceString(&Adexcept::_secSIMPUK)
extern PACKAGE System::ResourceString _secSIMPIN2;
#define Adexcept_secSIMPIN2 System::LoadResourceString(&Adexcept::_secSIMPIN2)
extern PACKAGE System::ResourceString _secSIMPUK2;
#define Adexcept_secSIMPUK2 System::LoadResourceString(&Adexcept::_secSIMPUK2)
extern PACKAGE System::ResourceString _secMemFail;
#define Adexcept_secMemFail System::LoadResourceString(&Adexcept::_secMemFail)
extern PACKAGE System::ResourceString _secInvalidMemIndex;
#define Adexcept_secInvalidMemIndex System::LoadResourceString(&Adexcept::_secInvalidMemIndex)
extern PACKAGE System::ResourceString _secMemFull;
#define Adexcept_secMemFull System::LoadResourceString(&Adexcept::_secMemFull)
extern PACKAGE System::ResourceString _secSMSCAddUnknown;
#define Adexcept_secSMSCAddUnknown System::LoadResourceString(&Adexcept::_secSMSCAddUnknown)
extern PACKAGE System::ResourceString _secNoNetwork;
#define Adexcept_secNoNetwork System::LoadResourceString(&Adexcept::_secNoNetwork)
extern PACKAGE System::ResourceString _secNetworkTimeout;
#define Adexcept_secNetworkTimeout System::LoadResourceString(&Adexcept::_secNetworkTimeout)
extern PACKAGE System::ResourceString _secCNMAAck;
#define Adexcept_secCNMAAck System::LoadResourceString(&Adexcept::_secCNMAAck)
extern PACKAGE System::ResourceString _secUnknown;
#define Adexcept_secUnknown System::LoadResourceString(&Adexcept::_secUnknown)
extern PACKAGE System::ResourceString _secADWSERROR;
#define Adexcept_secADWSERROR System::LoadResourceString(&Adexcept::_secADWSERROR)
extern PACKAGE System::ResourceString _secADWSLOADERROR;
#define Adexcept_secADWSLOADERROR System::LoadResourceString(&Adexcept::_secADWSLOADERROR)
extern PACKAGE System::ResourceString _secADWSVERSIONERROR;
#define Adexcept_secADWSVERSIONERROR System::LoadResourceString(&Adexcept::_secADWSVERSIONERROR)
extern PACKAGE System::ResourceString _secADWSNOTINIT;
#define Adexcept_secADWSNOTINIT System::LoadResourceString(&Adexcept::_secADWSNOTINIT)
extern PACKAGE System::ResourceString _secADWSINVPORT;
#define Adexcept_secADWSINVPORT System::LoadResourceString(&Adexcept::_secADWSINVPORT)
extern PACKAGE System::ResourceString _secADWSCANTCHANGE;
#define Adexcept_secADWSCANTCHANGE System::LoadResourceString(&Adexcept::_secADWSCANTCHANGE)
extern PACKAGE System::ResourceString _secADWSCANTRESOLVE;
#define Adexcept_secADWSCANTRESOLVE System::LoadResourceString(&Adexcept::_secADWSCANTRESOLVE)
extern PACKAGE System::ResourceString _swsaBaseErr;
#define Adexcept_swsaBaseErr System::LoadResourceString(&Adexcept::_swsaBaseErr)
extern PACKAGE System::ResourceString _swsaEIntr;
#define Adexcept_swsaEIntr System::LoadResourceString(&Adexcept::_swsaEIntr)
extern PACKAGE System::ResourceString _swsaEBadF;
#define Adexcept_swsaEBadF System::LoadResourceString(&Adexcept::_swsaEBadF)
extern PACKAGE System::ResourceString _swsaEAcces;
#define Adexcept_swsaEAcces System::LoadResourceString(&Adexcept::_swsaEAcces)
extern PACKAGE System::ResourceString _swsaEFault;
#define Adexcept_swsaEFault System::LoadResourceString(&Adexcept::_swsaEFault)
extern PACKAGE System::ResourceString _swsaEInVal;
#define Adexcept_swsaEInVal System::LoadResourceString(&Adexcept::_swsaEInVal)
extern PACKAGE System::ResourceString _swsaEMFile;
#define Adexcept_swsaEMFile System::LoadResourceString(&Adexcept::_swsaEMFile)
extern PACKAGE System::ResourceString _swsaEWouldBlock;
#define Adexcept_swsaEWouldBlock System::LoadResourceString(&Adexcept::_swsaEWouldBlock)
extern PACKAGE System::ResourceString _swsaEInProgress;
#define Adexcept_swsaEInProgress System::LoadResourceString(&Adexcept::_swsaEInProgress)
extern PACKAGE System::ResourceString _swsaEAlReady;
#define Adexcept_swsaEAlReady System::LoadResourceString(&Adexcept::_swsaEAlReady)
extern PACKAGE System::ResourceString _swsaENotSock;
#define Adexcept_swsaENotSock System::LoadResourceString(&Adexcept::_swsaENotSock)
extern PACKAGE System::ResourceString _swsaEDestAddrReq;
#define Adexcept_swsaEDestAddrReq System::LoadResourceString(&Adexcept::_swsaEDestAddrReq)
extern PACKAGE System::ResourceString _swsaEMsgSize;
#define Adexcept_swsaEMsgSize System::LoadResourceString(&Adexcept::_swsaEMsgSize)
extern PACKAGE System::ResourceString _swsaEPrototype;
#define Adexcept_swsaEPrototype System::LoadResourceString(&Adexcept::_swsaEPrototype)
extern PACKAGE System::ResourceString _swsaENoProtoOpt;
#define Adexcept_swsaENoProtoOpt System::LoadResourceString(&Adexcept::_swsaENoProtoOpt)
extern PACKAGE System::ResourceString _swsaEProtoNoSupport;
#define Adexcept_swsaEProtoNoSupport System::LoadResourceString(&Adexcept::_swsaEProtoNoSupport)
extern PACKAGE System::ResourceString _swsaESocktNoSupport;
#define Adexcept_swsaESocktNoSupport System::LoadResourceString(&Adexcept::_swsaESocktNoSupport)
extern PACKAGE System::ResourceString _swsaEOpNotSupp;
#define Adexcept_swsaEOpNotSupp System::LoadResourceString(&Adexcept::_swsaEOpNotSupp)
extern PACKAGE System::ResourceString _swsaEPfNoSupport;
#define Adexcept_swsaEPfNoSupport System::LoadResourceString(&Adexcept::_swsaEPfNoSupport)
extern PACKAGE System::ResourceString _swsaEAfNoSupport;
#define Adexcept_swsaEAfNoSupport System::LoadResourceString(&Adexcept::_swsaEAfNoSupport)
extern PACKAGE System::ResourceString _swsaEAddrInUse;
#define Adexcept_swsaEAddrInUse System::LoadResourceString(&Adexcept::_swsaEAddrInUse)
extern PACKAGE System::ResourceString _swsaEAddrNotAvail;
#define Adexcept_swsaEAddrNotAvail System::LoadResourceString(&Adexcept::_swsaEAddrNotAvail)
extern PACKAGE System::ResourceString _swsaENetDown;
#define Adexcept_swsaENetDown System::LoadResourceString(&Adexcept::_swsaENetDown)
extern PACKAGE System::ResourceString _swsaENetUnreach;
#define Adexcept_swsaENetUnreach System::LoadResourceString(&Adexcept::_swsaENetUnreach)
extern PACKAGE System::ResourceString _swsaENetReset;
#define Adexcept_swsaENetReset System::LoadResourceString(&Adexcept::_swsaENetReset)
extern PACKAGE System::ResourceString _swsaEConnAborted;
#define Adexcept_swsaEConnAborted System::LoadResourceString(&Adexcept::_swsaEConnAborted)
extern PACKAGE System::ResourceString _swsaEConnReset;
#define Adexcept_swsaEConnReset System::LoadResourceString(&Adexcept::_swsaEConnReset)
extern PACKAGE System::ResourceString _swsaENoBufs;
#define Adexcept_swsaENoBufs System::LoadResourceString(&Adexcept::_swsaENoBufs)
extern PACKAGE System::ResourceString _swsaEIsConn;
#define Adexcept_swsaEIsConn System::LoadResourceString(&Adexcept::_swsaEIsConn)
extern PACKAGE System::ResourceString _swsaENotConn;
#define Adexcept_swsaENotConn System::LoadResourceString(&Adexcept::_swsaENotConn)
extern PACKAGE System::ResourceString _swsaEShutDown;
#define Adexcept_swsaEShutDown System::LoadResourceString(&Adexcept::_swsaEShutDown)
extern PACKAGE System::ResourceString _swsaETooManyRefs;
#define Adexcept_swsaETooManyRefs System::LoadResourceString(&Adexcept::_swsaETooManyRefs)
extern PACKAGE System::ResourceString _swsaETimedOut;
#define Adexcept_swsaETimedOut System::LoadResourceString(&Adexcept::_swsaETimedOut)
extern PACKAGE System::ResourceString _swsaEConnRefused;
#define Adexcept_swsaEConnRefused System::LoadResourceString(&Adexcept::_swsaEConnRefused)
extern PACKAGE System::ResourceString _swsaELoop;
#define Adexcept_swsaELoop System::LoadResourceString(&Adexcept::_swsaELoop)
extern PACKAGE System::ResourceString _swsaENameTooLong;
#define Adexcept_swsaENameTooLong System::LoadResourceString(&Adexcept::_swsaENameTooLong)
extern PACKAGE System::ResourceString _swsaEHostDown;
#define Adexcept_swsaEHostDown System::LoadResourceString(&Adexcept::_swsaEHostDown)
extern PACKAGE System::ResourceString _swsaEHostUnreach;
#define Adexcept_swsaEHostUnreach System::LoadResourceString(&Adexcept::_swsaEHostUnreach)
extern PACKAGE System::ResourceString _swsaENotEmpty;
#define Adexcept_swsaENotEmpty System::LoadResourceString(&Adexcept::_swsaENotEmpty)
extern PACKAGE System::ResourceString _swsaEProcLim;
#define Adexcept_swsaEProcLim System::LoadResourceString(&Adexcept::_swsaEProcLim)
extern PACKAGE System::ResourceString _swsaEUsers;
#define Adexcept_swsaEUsers System::LoadResourceString(&Adexcept::_swsaEUsers)
extern PACKAGE System::ResourceString _swsaEDQuot;
#define Adexcept_swsaEDQuot System::LoadResourceString(&Adexcept::_swsaEDQuot)
extern PACKAGE System::ResourceString _swsaEStale;
#define Adexcept_swsaEStale System::LoadResourceString(&Adexcept::_swsaEStale)
extern PACKAGE System::ResourceString _swsaERemote;
#define Adexcept_swsaERemote System::LoadResourceString(&Adexcept::_swsaERemote)
extern PACKAGE System::ResourceString _swsaSysNotReady;
#define Adexcept_swsaSysNotReady System::LoadResourceString(&Adexcept::_swsaSysNotReady)
extern PACKAGE System::ResourceString _swsaVerNotSupported;
#define Adexcept_swsaVerNotSupported System::LoadResourceString(&Adexcept::_swsaVerNotSupported)
extern PACKAGE System::ResourceString _swsaNotInitialised;
#define Adexcept_swsaNotInitialised System::LoadResourceString(&Adexcept::_swsaNotInitialised)
extern PACKAGE System::ResourceString _swsaEDiscOn;
#define Adexcept_swsaEDiscOn System::LoadResourceString(&Adexcept::_swsaEDiscOn)
extern PACKAGE System::ResourceString _swsaHost_Not_Found;
#define Adexcept_swsaHost_Not_Found System::LoadResourceString(&Adexcept::_swsaHost_Not_Found)
extern PACKAGE System::ResourceString _swsaTry_Again;
#define Adexcept_swsaTry_Again System::LoadResourceString(&Adexcept::_swsaTry_Again)
extern PACKAGE System::ResourceString _swsaNo_Recovery;
#define Adexcept_swsaNo_Recovery System::LoadResourceString(&Adexcept::_swsaNo_Recovery)
extern PACKAGE System::ResourceString _swsaNo_Data;
#define Adexcept_swsaNo_Data System::LoadResourceString(&Adexcept::_swsaNo_Data)
extern PACKAGE System::ResourceString _stcs_Idle;
#define Adexcept_stcs_Idle System::LoadResourceString(&Adexcept::_stcs_Idle)
extern PACKAGE System::ResourceString _stcs_Offering;
#define Adexcept_stcs_Offering System::LoadResourceString(&Adexcept::_stcs_Offering)
extern PACKAGE System::ResourceString _stcs_Accepted;
#define Adexcept_stcs_Accepted System::LoadResourceString(&Adexcept::_stcs_Accepted)
extern PACKAGE System::ResourceString _stcs_Dialtone;
#define Adexcept_stcs_Dialtone System::LoadResourceString(&Adexcept::_stcs_Dialtone)
extern PACKAGE System::ResourceString _stcs_Dialing;
#define Adexcept_stcs_Dialing System::LoadResourceString(&Adexcept::_stcs_Dialing)
extern PACKAGE System::ResourceString _stcs_Ringback;
#define Adexcept_stcs_Ringback System::LoadResourceString(&Adexcept::_stcs_Ringback)
extern PACKAGE System::ResourceString _stcs_Busy;
#define Adexcept_stcs_Busy System::LoadResourceString(&Adexcept::_stcs_Busy)
extern PACKAGE System::ResourceString _stcs_SpecialInfo;
#define Adexcept_stcs_SpecialInfo System::LoadResourceString(&Adexcept::_stcs_SpecialInfo)
extern PACKAGE System::ResourceString _stcs_Connected;
#define Adexcept_stcs_Connected System::LoadResourceString(&Adexcept::_stcs_Connected)
extern PACKAGE System::ResourceString _stcs_Proceeding;
#define Adexcept_stcs_Proceeding System::LoadResourceString(&Adexcept::_stcs_Proceeding)
extern PACKAGE System::ResourceString _stcs_OnHold;
#define Adexcept_stcs_OnHold System::LoadResourceString(&Adexcept::_stcs_OnHold)
extern PACKAGE System::ResourceString _stcs_Conferenced;
#define Adexcept_stcs_Conferenced System::LoadResourceString(&Adexcept::_stcs_Conferenced)
extern PACKAGE System::ResourceString _stcs_OnHoldPendConf;
#define Adexcept_stcs_OnHoldPendConf System::LoadResourceString(&Adexcept::_stcs_OnHoldPendConf)
extern PACKAGE System::ResourceString _stcs_OnHoldPendTransfer;
#define Adexcept_stcs_OnHoldPendTransfer System::LoadResourceString(&Adexcept::_stcs_OnHoldPendTransfer)
extern PACKAGE System::ResourceString _stcs_Disconnected;
#define Adexcept_stcs_Disconnected System::LoadResourceString(&Adexcept::_stcs_Disconnected)
extern PACKAGE System::ResourceString _stcs_Unknown;
#define Adexcept_stcs_Unknown System::LoadResourceString(&Adexcept::_stcs_Unknown)
extern PACKAGE System::ResourceString _stds_Other;
#define Adexcept_stds_Other System::LoadResourceString(&Adexcept::_stds_Other)
extern PACKAGE System::ResourceString _stds_Ringing;
#define Adexcept_stds_Ringing System::LoadResourceString(&Adexcept::_stds_Ringing)
extern PACKAGE System::ResourceString _stds_Connected;
#define Adexcept_stds_Connected System::LoadResourceString(&Adexcept::_stds_Connected)
extern PACKAGE System::ResourceString _stds_Disconnected;
#define Adexcept_stds_Disconnected System::LoadResourceString(&Adexcept::_stds_Disconnected)
extern PACKAGE System::ResourceString _stds_MsgWaitOn;
#define Adexcept_stds_MsgWaitOn System::LoadResourceString(&Adexcept::_stds_MsgWaitOn)
extern PACKAGE System::ResourceString _stds_MsgWaitOff;
#define Adexcept_stds_MsgWaitOff System::LoadResourceString(&Adexcept::_stds_MsgWaitOff)
extern PACKAGE System::ResourceString _stds_InService;
#define Adexcept_stds_InService System::LoadResourceString(&Adexcept::_stds_InService)
extern PACKAGE System::ResourceString _stds_OutOfService;
#define Adexcept_stds_OutOfService System::LoadResourceString(&Adexcept::_stds_OutOfService)
extern PACKAGE System::ResourceString _stds_Maintenance;
#define Adexcept_stds_Maintenance System::LoadResourceString(&Adexcept::_stds_Maintenance)
extern PACKAGE System::ResourceString _stds_Open;
#define Adexcept_stds_Open System::LoadResourceString(&Adexcept::_stds_Open)
extern PACKAGE System::ResourceString _stds_Close;
#define Adexcept_stds_Close System::LoadResourceString(&Adexcept::_stds_Close)
extern PACKAGE System::ResourceString _stds_NumCalls;
#define Adexcept_stds_NumCalls System::LoadResourceString(&Adexcept::_stds_NumCalls)
extern PACKAGE System::ResourceString _stds_NumCompletions;
#define Adexcept_stds_NumCompletions System::LoadResourceString(&Adexcept::_stds_NumCompletions)
extern PACKAGE System::ResourceString _stds_Terminals;
#define Adexcept_stds_Terminals System::LoadResourceString(&Adexcept::_stds_Terminals)
extern PACKAGE System::ResourceString _stds_RoamMode;
#define Adexcept_stds_RoamMode System::LoadResourceString(&Adexcept::_stds_RoamMode)
extern PACKAGE System::ResourceString _stds_Battery;
#define Adexcept_stds_Battery System::LoadResourceString(&Adexcept::_stds_Battery)
extern PACKAGE System::ResourceString _stds_Signal;
#define Adexcept_stds_Signal System::LoadResourceString(&Adexcept::_stds_Signal)
extern PACKAGE System::ResourceString _stds_DevSpecific;
#define Adexcept_stds_DevSpecific System::LoadResourceString(&Adexcept::_stds_DevSpecific)
extern PACKAGE System::ResourceString _stds_ReInit;
#define Adexcept_stds_ReInit System::LoadResourceString(&Adexcept::_stds_ReInit)
extern PACKAGE System::ResourceString _stds_Lock;
#define Adexcept_stds_Lock System::LoadResourceString(&Adexcept::_stds_Lock)
extern PACKAGE System::ResourceString _stds_CapsChange;
#define Adexcept_stds_CapsChange System::LoadResourceString(&Adexcept::_stds_CapsChange)
extern PACKAGE System::ResourceString _stds_ConfigChange;
#define Adexcept_stds_ConfigChange System::LoadResourceString(&Adexcept::_stds_ConfigChange)
extern PACKAGE System::ResourceString _stds_TranslateChange;
#define Adexcept_stds_TranslateChange System::LoadResourceString(&Adexcept::_stds_TranslateChange)
extern PACKAGE System::ResourceString _stds_ComplCancel;
#define Adexcept_stds_ComplCancel System::LoadResourceString(&Adexcept::_stds_ComplCancel)
extern PACKAGE System::ResourceString _stds_Removed;
#define Adexcept_stds_Removed System::LoadResourceString(&Adexcept::_stds_Removed)
extern PACKAGE System::ResourceString _sTAPILineReply;
#define Adexcept_sTAPILineReply System::LoadResourceString(&Adexcept::_sTAPILineReply)
extern PACKAGE System::ResourceString _sTAPIStateChange;
#define Adexcept_sTAPIStateChange System::LoadResourceString(&Adexcept::_sTAPIStateChange)
extern PACKAGE System::ResourceString _sTAPICalledBusy;
#define Adexcept_sTAPICalledBusy System::LoadResourceString(&Adexcept::_sTAPICalledBusy)
extern PACKAGE System::ResourceString _sTAPIDialFail;
#define Adexcept_sTAPIDialFail System::LoadResourceString(&Adexcept::_sTAPIDialFail)
extern PACKAGE System::ResourceString _sTAPIRetryWait;
#define Adexcept_sTAPIRetryWait System::LoadResourceString(&Adexcept::_sTAPIRetryWait)
extern PACKAGE System::ResourceString _sTAPIDeviceInUse;
#define Adexcept_sTAPIDeviceInUse System::LoadResourceString(&Adexcept::_sTAPIDeviceInUse)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Unspecified;
#define Adexcept_sTAPIDisconnect_Unspecified System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Unspecified)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Normal;
#define Adexcept_sTAPIDisconnect_Normal System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Normal)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Unknown;
#define Adexcept_sTAPIDisconnect_Unknown System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Unknown)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Reject;
#define Adexcept_sTAPIDisconnect_Reject System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Reject)
extern PACKAGE System::ResourceString _sTAPIDisconnect_PickUp;
#define Adexcept_sTAPIDisconnect_PickUp System::LoadResourceString(&Adexcept::_sTAPIDisconnect_PickUp)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Forwarded;
#define Adexcept_sTAPIDisconnect_Forwarded System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Forwarded)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Busy;
#define Adexcept_sTAPIDisconnect_Busy System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Busy)
extern PACKAGE System::ResourceString _sTAPIDisconnect_NoAnswer;
#define Adexcept_sTAPIDisconnect_NoAnswer System::LoadResourceString(&Adexcept::_sTAPIDisconnect_NoAnswer)
extern PACKAGE System::ResourceString _sTAPIDisconnect_BadAddress;
#define Adexcept_sTAPIDisconnect_BadAddress System::LoadResourceString(&Adexcept::_sTAPIDisconnect_BadAddress)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Unreachable;
#define Adexcept_sTAPIDisconnect_Unreachable System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Unreachable)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Congestion;
#define Adexcept_sTAPIDisconnect_Congestion System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Congestion)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Incompatible;
#define Adexcept_sTAPIDisconnect_Incompatible System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Incompatible)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Unavail;
#define Adexcept_sTAPIDisconnect_Unavail System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Unavail)
extern PACKAGE System::ResourceString _sTAPIDisconnect_NoDialtone;
#define Adexcept_sTAPIDisconnect_NoDialtone System::LoadResourceString(&Adexcept::_sTAPIDisconnect_NoDialtone)
extern PACKAGE System::ResourceString _sTAPIDisconnect_NumberChanged;
#define Adexcept_sTAPIDisconnect_NumberChanged System::LoadResourceString(&Adexcept::_sTAPIDisconnect_NumberChanged)
extern PACKAGE System::ResourceString _sTAPIDisconnect_OutOfOrder;
#define Adexcept_sTAPIDisconnect_OutOfOrder System::LoadResourceString(&Adexcept::_sTAPIDisconnect_OutOfOrder)
extern PACKAGE System::ResourceString _sTAPIDisconnect_TempFailure;
#define Adexcept_sTAPIDisconnect_TempFailure System::LoadResourceString(&Adexcept::_sTAPIDisconnect_TempFailure)
extern PACKAGE System::ResourceString _sTAPIDisconnect_QOSUnavail;
#define Adexcept_sTAPIDisconnect_QOSUnavail System::LoadResourceString(&Adexcept::_sTAPIDisconnect_QOSUnavail)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Blocked;
#define Adexcept_sTAPIDisconnect_Blocked System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Blocked)
extern PACKAGE System::ResourceString _sTAPIDisconnect_DoNotDisturb;
#define Adexcept_sTAPIDisconnect_DoNotDisturb System::LoadResourceString(&Adexcept::_sTAPIDisconnect_DoNotDisturb)
extern PACKAGE System::ResourceString _sTAPIDisconnect_Cancelled;
#define Adexcept_sTAPIDisconnect_Cancelled System::LoadResourceString(&Adexcept::_sTAPIDisconnect_Cancelled)
extern PACKAGE System::ResourceString _secAllocated;
#define Adexcept_secAllocated System::LoadResourceString(&Adexcept::_secAllocated)
extern PACKAGE System::ResourceString _secBadDeviceID;
#define Adexcept_secBadDeviceID System::LoadResourceString(&Adexcept::_secBadDeviceID)
extern PACKAGE System::ResourceString _secBearerModeUnavail;
#define Adexcept_secBearerModeUnavail System::LoadResourceString(&Adexcept::_secBearerModeUnavail)
extern PACKAGE System::ResourceString _secCallUnavail;
#define Adexcept_secCallUnavail System::LoadResourceString(&Adexcept::_secCallUnavail)
extern PACKAGE System::ResourceString _secCompletionOverrun;
#define Adexcept_secCompletionOverrun System::LoadResourceString(&Adexcept::_secCompletionOverrun)
extern PACKAGE System::ResourceString _secConferenceFull;
#define Adexcept_secConferenceFull System::LoadResourceString(&Adexcept::_secConferenceFull)
extern PACKAGE System::ResourceString _secDialBilling;
#define Adexcept_secDialBilling System::LoadResourceString(&Adexcept::_secDialBilling)
extern PACKAGE System::ResourceString _secDialDialtone;
#define Adexcept_secDialDialtone System::LoadResourceString(&Adexcept::_secDialDialtone)
extern PACKAGE System::ResourceString _secDialPrompt;
#define Adexcept_secDialPrompt System::LoadResourceString(&Adexcept::_secDialPrompt)
extern PACKAGE System::ResourceString _secDialQuiet;
#define Adexcept_secDialQuiet System::LoadResourceString(&Adexcept::_secDialQuiet)
extern PACKAGE System::ResourceString _secIncompatibleApiVersion;
#define Adexcept_secIncompatibleApiVersion System::LoadResourceString(&Adexcept::_secIncompatibleApiVersion)
extern PACKAGE System::ResourceString _secIncompatibleExtVersion;
#define Adexcept_secIncompatibleExtVersion System::LoadResourceString(&Adexcept::_secIncompatibleExtVersion)
extern PACKAGE System::ResourceString _secIniFileCorrupt;
#define Adexcept_secIniFileCorrupt System::LoadResourceString(&Adexcept::_secIniFileCorrupt)
extern PACKAGE System::ResourceString _secInUse;
#define Adexcept_secInUse System::LoadResourceString(&Adexcept::_secInUse)
extern PACKAGE System::ResourceString _secInvalAddress;
#define Adexcept_secInvalAddress System::LoadResourceString(&Adexcept::_secInvalAddress)
extern PACKAGE System::ResourceString _secInvalAddressID;
#define Adexcept_secInvalAddressID System::LoadResourceString(&Adexcept::_secInvalAddressID)
extern PACKAGE System::ResourceString _secInvalAddressMode;
#define Adexcept_secInvalAddressMode System::LoadResourceString(&Adexcept::_secInvalAddressMode)
extern PACKAGE System::ResourceString _secInvalAddressState;
#define Adexcept_secInvalAddressState System::LoadResourceString(&Adexcept::_secInvalAddressState)
extern PACKAGE System::ResourceString _secInvalAppHandle;
#define Adexcept_secInvalAppHandle System::LoadResourceString(&Adexcept::_secInvalAppHandle)
extern PACKAGE System::ResourceString _secInvalAppName;
#define Adexcept_secInvalAppName System::LoadResourceString(&Adexcept::_secInvalAppName)
extern PACKAGE System::ResourceString _secInvalBearerMode;
#define Adexcept_secInvalBearerMode System::LoadResourceString(&Adexcept::_secInvalBearerMode)
extern PACKAGE System::ResourceString _secInvalCallComplMode;
#define Adexcept_secInvalCallComplMode System::LoadResourceString(&Adexcept::_secInvalCallComplMode)
extern PACKAGE System::ResourceString _secInvalCallHandle;
#define Adexcept_secInvalCallHandle System::LoadResourceString(&Adexcept::_secInvalCallHandle)
extern PACKAGE System::ResourceString _secInvalCallParams;
#define Adexcept_secInvalCallParams System::LoadResourceString(&Adexcept::_secInvalCallParams)
extern PACKAGE System::ResourceString _secInvalCallPrivilege;
#define Adexcept_secInvalCallPrivilege System::LoadResourceString(&Adexcept::_secInvalCallPrivilege)
extern PACKAGE System::ResourceString _secInvalCallSelect;
#define Adexcept_secInvalCallSelect System::LoadResourceString(&Adexcept::_secInvalCallSelect)
extern PACKAGE System::ResourceString _secInvalCallState;
#define Adexcept_secInvalCallState System::LoadResourceString(&Adexcept::_secInvalCallState)
extern PACKAGE System::ResourceString _secInvalCallStatelist;
#define Adexcept_secInvalCallStatelist System::LoadResourceString(&Adexcept::_secInvalCallStatelist)
extern PACKAGE System::ResourceString _secInvalCard;
#define Adexcept_secInvalCard System::LoadResourceString(&Adexcept::_secInvalCard)
extern PACKAGE System::ResourceString _secInvalCompletionID;
#define Adexcept_secInvalCompletionID System::LoadResourceString(&Adexcept::_secInvalCompletionID)
extern PACKAGE System::ResourceString _secInvalConfCallHandle;
#define Adexcept_secInvalConfCallHandle System::LoadResourceString(&Adexcept::_secInvalConfCallHandle)
extern PACKAGE System::ResourceString _secInvalConsultCallHandle;
#define Adexcept_secInvalConsultCallHandle System::LoadResourceString(&Adexcept::_secInvalConsultCallHandle)
extern PACKAGE System::ResourceString _secInvalCountryCode;
#define Adexcept_secInvalCountryCode System::LoadResourceString(&Adexcept::_secInvalCountryCode)
extern PACKAGE System::ResourceString _secInvalDeviceClass;
#define Adexcept_secInvalDeviceClass System::LoadResourceString(&Adexcept::_secInvalDeviceClass)
extern PACKAGE System::ResourceString _secInvalDeviceHandle;
#define Adexcept_secInvalDeviceHandle System::LoadResourceString(&Adexcept::_secInvalDeviceHandle)
extern PACKAGE System::ResourceString _secInvalDialParams;
#define Adexcept_secInvalDialParams System::LoadResourceString(&Adexcept::_secInvalDialParams)
extern PACKAGE System::ResourceString _secInvalDigitList;
#define Adexcept_secInvalDigitList System::LoadResourceString(&Adexcept::_secInvalDigitList)
extern PACKAGE System::ResourceString _secInvalDigitMode;
#define Adexcept_secInvalDigitMode System::LoadResourceString(&Adexcept::_secInvalDigitMode)
extern PACKAGE System::ResourceString _secInvalDigits;
#define Adexcept_secInvalDigits System::LoadResourceString(&Adexcept::_secInvalDigits)
extern PACKAGE System::ResourceString _secInvalExtVersion;
#define Adexcept_secInvalExtVersion System::LoadResourceString(&Adexcept::_secInvalExtVersion)
extern PACKAGE System::ResourceString _secInvalGroupID;
#define Adexcept_secInvalGroupID System::LoadResourceString(&Adexcept::_secInvalGroupID)
extern PACKAGE System::ResourceString _secInvalLineHandle;
#define Adexcept_secInvalLineHandle System::LoadResourceString(&Adexcept::_secInvalLineHandle)
extern PACKAGE System::ResourceString _secInvalLineState;
#define Adexcept_secInvalLineState System::LoadResourceString(&Adexcept::_secInvalLineState)
extern PACKAGE System::ResourceString _secInvalLocation;
#define Adexcept_secInvalLocation System::LoadResourceString(&Adexcept::_secInvalLocation)
extern PACKAGE System::ResourceString _secInvalMediaList;
#define Adexcept_secInvalMediaList System::LoadResourceString(&Adexcept::_secInvalMediaList)
extern PACKAGE System::ResourceString _secInvalMediaMode;
#define Adexcept_secInvalMediaMode System::LoadResourceString(&Adexcept::_secInvalMediaMode)
extern PACKAGE System::ResourceString _secInvalMessageID;
#define Adexcept_secInvalMessageID System::LoadResourceString(&Adexcept::_secInvalMessageID)
extern PACKAGE System::ResourceString _secInvalParam;
#define Adexcept_secInvalParam System::LoadResourceString(&Adexcept::_secInvalParam)
extern PACKAGE System::ResourceString _secInvalParkID;
#define Adexcept_secInvalParkID System::LoadResourceString(&Adexcept::_secInvalParkID)
extern PACKAGE System::ResourceString _secInvalParkMode;
#define Adexcept_secInvalParkMode System::LoadResourceString(&Adexcept::_secInvalParkMode)
extern PACKAGE System::ResourceString _secInvalPointer;
#define Adexcept_secInvalPointer System::LoadResourceString(&Adexcept::_secInvalPointer)
extern PACKAGE System::ResourceString _secInvalPrivSelect;
#define Adexcept_secInvalPrivSelect System::LoadResourceString(&Adexcept::_secInvalPrivSelect)
extern PACKAGE System::ResourceString _secInvalRate;
#define Adexcept_secInvalRate System::LoadResourceString(&Adexcept::_secInvalRate)
extern PACKAGE System::ResourceString _secInvalRequestMode;
#define Adexcept_secInvalRequestMode System::LoadResourceString(&Adexcept::_secInvalRequestMode)
extern PACKAGE System::ResourceString _secInvalTerminalID;
#define Adexcept_secInvalTerminalID System::LoadResourceString(&Adexcept::_secInvalTerminalID)
extern PACKAGE System::ResourceString _secInvalTerminalMode;
#define Adexcept_secInvalTerminalMode System::LoadResourceString(&Adexcept::_secInvalTerminalMode)
extern PACKAGE System::ResourceString _secInvalTimeout;
#define Adexcept_secInvalTimeout System::LoadResourceString(&Adexcept::_secInvalTimeout)
extern PACKAGE System::ResourceString _secInvalTone;
#define Adexcept_secInvalTone System::LoadResourceString(&Adexcept::_secInvalTone)
extern PACKAGE System::ResourceString _secInvalToneList;
#define Adexcept_secInvalToneList System::LoadResourceString(&Adexcept::_secInvalToneList)
extern PACKAGE System::ResourceString _secInvalToneMode;
#define Adexcept_secInvalToneMode System::LoadResourceString(&Adexcept::_secInvalToneMode)
extern PACKAGE System::ResourceString _secInvalTransferMode;
#define Adexcept_secInvalTransferMode System::LoadResourceString(&Adexcept::_secInvalTransferMode)
extern PACKAGE System::ResourceString _secLineMapperFailed;
#define Adexcept_secLineMapperFailed System::LoadResourceString(&Adexcept::_secLineMapperFailed)
extern PACKAGE System::ResourceString _secNoConference;
#define Adexcept_secNoConference System::LoadResourceString(&Adexcept::_secNoConference)
extern PACKAGE System::ResourceString _secNoDevice;
#define Adexcept_secNoDevice System::LoadResourceString(&Adexcept::_secNoDevice)
extern PACKAGE System::ResourceString _secNoDriver;
#define Adexcept_secNoDriver System::LoadResourceString(&Adexcept::_secNoDriver)
extern PACKAGE System::ResourceString _secNoMem;
#define Adexcept_secNoMem System::LoadResourceString(&Adexcept::_secNoMem)
extern PACKAGE System::ResourceString _secNoRequest;
#define Adexcept_secNoRequest System::LoadResourceString(&Adexcept::_secNoRequest)
extern PACKAGE System::ResourceString _secNotOwner;
#define Adexcept_secNotOwner System::LoadResourceString(&Adexcept::_secNotOwner)
extern PACKAGE System::ResourceString _secNotRegistered;
#define Adexcept_secNotRegistered System::LoadResourceString(&Adexcept::_secNotRegistered)
extern PACKAGE System::ResourceString _secOperationFailed;
#define Adexcept_secOperationFailed System::LoadResourceString(&Adexcept::_secOperationFailed)
extern PACKAGE System::ResourceString _secOperationUnavail;
#define Adexcept_secOperationUnavail System::LoadResourceString(&Adexcept::_secOperationUnavail)
extern PACKAGE System::ResourceString _secRateUnavail;
#define Adexcept_secRateUnavail System::LoadResourceString(&Adexcept::_secRateUnavail)
extern PACKAGE System::ResourceString _secResourceUnavail;
#define Adexcept_secResourceUnavail System::LoadResourceString(&Adexcept::_secResourceUnavail)
extern PACKAGE System::ResourceString _secRequestOverrun;
#define Adexcept_secRequestOverrun System::LoadResourceString(&Adexcept::_secRequestOverrun)
extern PACKAGE System::ResourceString _secStructureTooSmall;
#define Adexcept_secStructureTooSmall System::LoadResourceString(&Adexcept::_secStructureTooSmall)
extern PACKAGE System::ResourceString _secTargetNotFound;
#define Adexcept_secTargetNotFound System::LoadResourceString(&Adexcept::_secTargetNotFound)
extern PACKAGE System::ResourceString _secTargetSelf;
#define Adexcept_secTargetSelf System::LoadResourceString(&Adexcept::_secTargetSelf)
extern PACKAGE System::ResourceString _secUninitialized;
#define Adexcept_secUninitialized System::LoadResourceString(&Adexcept::_secUninitialized)
extern PACKAGE System::ResourceString _secUserUserInfoTooBig;
#define Adexcept_secUserUserInfoTooBig System::LoadResourceString(&Adexcept::_secUserUserInfoTooBig)
extern PACKAGE System::ResourceString _secReinit;
#define Adexcept_secReinit System::LoadResourceString(&Adexcept::_secReinit)
extern PACKAGE System::ResourceString _secAddressBlocked;
#define Adexcept_secAddressBlocked System::LoadResourceString(&Adexcept::_secAddressBlocked)
extern PACKAGE System::ResourceString _secBillingRejected;
#define Adexcept_secBillingRejected System::LoadResourceString(&Adexcept::_secBillingRejected)
extern PACKAGE System::ResourceString _secInvalFeature;
#define Adexcept_secInvalFeature System::LoadResourceString(&Adexcept::_secInvalFeature)
extern PACKAGE System::ResourceString _secNoMultipleInstance;
#define Adexcept_secNoMultipleInstance System::LoadResourceString(&Adexcept::_secNoMultipleInstance)
extern PACKAGE System::ResourceString _secTapiBusy;
#define Adexcept_secTapiBusy System::LoadResourceString(&Adexcept::_secTapiBusy)
extern PACKAGE System::ResourceString _secTapiNotSet;
#define Adexcept_secTapiNotSet System::LoadResourceString(&Adexcept::_secTapiNotSet)
extern PACKAGE System::ResourceString _secTapiNoSelect;
#define Adexcept_secTapiNoSelect System::LoadResourceString(&Adexcept::_secTapiNoSelect)
extern PACKAGE System::ResourceString _secTapiLoadFail;
#define Adexcept_secTapiLoadFail System::LoadResourceString(&Adexcept::_secTapiLoadFail)
extern PACKAGE System::ResourceString _secTapiGetAddrFail;
#define Adexcept_secTapiGetAddrFail System::LoadResourceString(&Adexcept::_secTapiGetAddrFail)
extern PACKAGE System::ResourceString _sTAPIdisabled16bit;
#define Adexcept_sTAPIdisabled16bit System::LoadResourceString(&Adexcept::_sTAPIdisabled16bit)
extern PACKAGE System::ResourceString _secTapiUnexpected;
#define Adexcept_secTapiUnexpected System::LoadResourceString(&Adexcept::_secTapiUnexpected)
extern PACKAGE System::ResourceString _secTapiVoiceNotSupported;
#define Adexcept_secTapiVoiceNotSupported System::LoadResourceString(&Adexcept::_secTapiVoiceNotSupported)
extern PACKAGE System::ResourceString _secTapiWaveFail;
#define Adexcept_secTapiWaveFail System::LoadResourceString(&Adexcept::_secTapiWaveFail)
extern PACKAGE System::ResourceString _secTapiCIDBlocked;
#define Adexcept_secTapiCIDBlocked System::LoadResourceString(&Adexcept::_secTapiCIDBlocked)
extern PACKAGE System::ResourceString _secTapiCIDOutOfArea;
#define Adexcept_secTapiCIDOutOfArea System::LoadResourceString(&Adexcept::_secTapiCIDOutOfArea)
extern PACKAGE System::ResourceString _secTapiWaveFormatError;
#define Adexcept_secTapiWaveFormatError System::LoadResourceString(&Adexcept::_secTapiWaveFormatError)
extern PACKAGE System::ResourceString _secTapiWaveReadError;
#define Adexcept_secTapiWaveReadError System::LoadResourceString(&Adexcept::_secTapiWaveReadError)
extern PACKAGE System::ResourceString _secTapiWaveBadFormat;
#define Adexcept_secTapiWaveBadFormat System::LoadResourceString(&Adexcept::_secTapiWaveBadFormat)
extern PACKAGE System::ResourceString _secTapiTranslateFail;
#define Adexcept_secTapiTranslateFail System::LoadResourceString(&Adexcept::_secTapiTranslateFail)
extern PACKAGE System::ResourceString _secTapiWaveDeviceInUse;
#define Adexcept_secTapiWaveDeviceInUse System::LoadResourceString(&Adexcept::_secTapiWaveDeviceInUse)
extern PACKAGE System::ResourceString _secTapiWaveFileExists;
#define Adexcept_secTapiWaveFileExists System::LoadResourceString(&Adexcept::_secTapiWaveFileExists)
extern PACKAGE System::ResourceString _secTapiWaveNoData;
#define Adexcept_secTapiWaveNoData System::LoadResourceString(&Adexcept::_secTapiWaveNoData)
extern PACKAGE System::ResourceString _secVoIPNotSupported;
#define Adexcept_secVoIPNotSupported System::LoadResourceString(&Adexcept::_secVoIPNotSupported)
extern PACKAGE System::ResourceString _secVoIPCallBusy;
#define Adexcept_secVoIPCallBusy System::LoadResourceString(&Adexcept::_secVoIPCallBusy)
extern PACKAGE System::ResourceString _secVoIPBadAddress;
#define Adexcept_secVoIPBadAddress System::LoadResourceString(&Adexcept::_secVoIPBadAddress)
extern PACKAGE System::ResourceString _secVoIPNoAnswer;
#define Adexcept_secVoIPNoAnswer System::LoadResourceString(&Adexcept::_secVoIPNoAnswer)
extern PACKAGE System::ResourceString _secVoIPCancelled;
#define Adexcept_secVoIPCancelled System::LoadResourceString(&Adexcept::_secVoIPCancelled)
extern PACKAGE System::ResourceString _secVoIPRejected;
#define Adexcept_secVoIPRejected System::LoadResourceString(&Adexcept::_secVoIPRejected)
extern PACKAGE System::ResourceString _secVoIPFailed;
#define Adexcept_secVoIPFailed System::LoadResourceString(&Adexcept::_secVoIPFailed)
extern PACKAGE System::ResourceString _secVoIPTapi3NotInstalled;
#define Adexcept_secVoIPTapi3NotInstalled System::LoadResourceString(&Adexcept::_secVoIPTapi3NotInstalled)
extern PACKAGE System::ResourceString _secVoIPH323NotFound;
#define Adexcept_secVoIPH323NotFound System::LoadResourceString(&Adexcept::_secVoIPH323NotFound)
extern PACKAGE System::ResourceString _secVoIPTapi3EventFailure;
#define Adexcept_secVoIPTapi3EventFailure System::LoadResourceString(&Adexcept::_secVoIPTapi3EventFailure)
extern PACKAGE System::ResourceString _secRasLoadFail;
#define Adexcept_secRasLoadFail System::LoadResourceString(&Adexcept::_secRasLoadFail)
extern PACKAGE System::ResourceString _sdtNone;
#define Adexcept_sdtNone System::LoadResourceString(&Adexcept::_sdtNone)
extern PACKAGE System::ResourceString _sdtDispatch;
#define Adexcept_sdtDispatch System::LoadResourceString(&Adexcept::_sdtDispatch)
extern PACKAGE System::ResourceString _sdtTrigger;
#define Adexcept_sdtTrigger System::LoadResourceString(&Adexcept::_sdtTrigger)
extern PACKAGE System::ResourceString _sdtError;
#define Adexcept_sdtError System::LoadResourceString(&Adexcept::_sdtError)
extern PACKAGE System::ResourceString _sdtThread;
#define Adexcept_sdtThread System::LoadResourceString(&Adexcept::_sdtThread)
extern PACKAGE System::ResourceString _sdtTriggerAlloc;
#define Adexcept_sdtTriggerAlloc System::LoadResourceString(&Adexcept::_sdtTriggerAlloc)
extern PACKAGE System::ResourceString _sdtTriggerDispose;
#define Adexcept_sdtTriggerDispose System::LoadResourceString(&Adexcept::_sdtTriggerDispose)
extern PACKAGE System::ResourceString _sdtTriggerHandlerAlloc;
#define Adexcept_sdtTriggerHandlerAlloc System::LoadResourceString(&Adexcept::_sdtTriggerHandlerAlloc)
extern PACKAGE System::ResourceString _sdtTriggerHandlerDispose;
#define Adexcept_sdtTriggerHandlerDispose System::LoadResourceString(&Adexcept::_sdtTriggerHandlerDispose)
extern PACKAGE System::ResourceString _sdtTriggerDataChange;
#define Adexcept_sdtTriggerDataChange System::LoadResourceString(&Adexcept::_sdtTriggerDataChange)
extern PACKAGE System::ResourceString _sdtTelnet;
#define Adexcept_sdtTelnet System::LoadResourceString(&Adexcept::_sdtTelnet)
extern PACKAGE System::ResourceString _sdtFax;
#define Adexcept_sdtFax System::LoadResourceString(&Adexcept::_sdtFax)
extern PACKAGE System::ResourceString _sdtXModem;
#define Adexcept_sdtXModem System::LoadResourceString(&Adexcept::_sdtXModem)
extern PACKAGE System::ResourceString _sdtYModem;
#define Adexcept_sdtYModem System::LoadResourceString(&Adexcept::_sdtYModem)
extern PACKAGE System::ResourceString _sdtZModem;
#define Adexcept_sdtZModem System::LoadResourceString(&Adexcept::_sdtZModem)
extern PACKAGE System::ResourceString _sdtKermit;
#define Adexcept_sdtKermit System::LoadResourceString(&Adexcept::_sdtKermit)
extern PACKAGE System::ResourceString _sdtAscii;
#define Adexcept_sdtAscii System::LoadResourceString(&Adexcept::_sdtAscii)
extern PACKAGE System::ResourceString _sdtBPlus;
#define Adexcept_sdtBPlus System::LoadResourceString(&Adexcept::_sdtBPlus)
extern PACKAGE System::ResourceString _sdtPacket;
#define Adexcept_sdtPacket System::LoadResourceString(&Adexcept::_sdtPacket)
extern PACKAGE System::ResourceString _sdtUser;
#define Adexcept_sdtUser System::LoadResourceString(&Adexcept::_sdtUser)
extern PACKAGE System::ResourceString _sdtScript;
#define Adexcept_sdtScript System::LoadResourceString(&Adexcept::_sdtScript)
extern PACKAGE System::ResourceString _sdstNone;
#define Adexcept_sdstNone System::LoadResourceString(&Adexcept::_sdstNone)
extern PACKAGE System::ResourceString _sdstReadCom;
#define Adexcept_sdstReadCom System::LoadResourceString(&Adexcept::_sdstReadCom)
extern PACKAGE System::ResourceString _sdstWriteCom;
#define Adexcept_sdstWriteCom System::LoadResourceString(&Adexcept::_sdstWriteCom)
extern PACKAGE System::ResourceString _sdstLineStatus;
#define Adexcept_sdstLineStatus System::LoadResourceString(&Adexcept::_sdstLineStatus)
extern PACKAGE System::ResourceString _sdstModemStatus;
#define Adexcept_sdstModemStatus System::LoadResourceString(&Adexcept::_sdstModemStatus)
extern PACKAGE System::ResourceString _sdstAvail;
#define Adexcept_sdstAvail System::LoadResourceString(&Adexcept::_sdstAvail)
extern PACKAGE System::ResourceString _sdstTimer;
#define Adexcept_sdstTimer System::LoadResourceString(&Adexcept::_sdstTimer)
extern PACKAGE System::ResourceString _sdstData;
#define Adexcept_sdstData System::LoadResourceString(&Adexcept::_sdstData)
extern PACKAGE System::ResourceString _sdstStatus;
#define Adexcept_sdstStatus System::LoadResourceString(&Adexcept::_sdstStatus)
extern PACKAGE System::ResourceString _sdstThreadStart;
#define Adexcept_sdstThreadStart System::LoadResourceString(&Adexcept::_sdstThreadStart)
extern PACKAGE System::ResourceString _sdstThreadExit;
#define Adexcept_sdstThreadExit System::LoadResourceString(&Adexcept::_sdstThreadExit)
extern PACKAGE System::ResourceString _sdstThreadSleep;
#define Adexcept_sdstThreadSleep System::LoadResourceString(&Adexcept::_sdstThreadSleep)
extern PACKAGE System::ResourceString _sdstThreadWake;
#define Adexcept_sdstThreadWake System::LoadResourceString(&Adexcept::_sdstThreadWake)
extern PACKAGE System::ResourceString _sdstDataTrigger;
#define Adexcept_sdstDataTrigger System::LoadResourceString(&Adexcept::_sdstDataTrigger)
extern PACKAGE System::ResourceString _sdstTimerTrigger;
#define Adexcept_sdstTimerTrigger System::LoadResourceString(&Adexcept::_sdstTimerTrigger)
extern PACKAGE System::ResourceString _sdstStatusTrigger;
#define Adexcept_sdstStatusTrigger System::LoadResourceString(&Adexcept::_sdstStatusTrigger)
extern PACKAGE System::ResourceString _sdstAvailTrigger;
#define Adexcept_sdstAvailTrigger System::LoadResourceString(&Adexcept::_sdstAvailTrigger)
extern PACKAGE System::ResourceString _sdstWndHandler;
#define Adexcept_sdstWndHandler System::LoadResourceString(&Adexcept::_sdstWndHandler)
extern PACKAGE System::ResourceString _sdstProcHandler;
#define Adexcept_sdstProcHandler System::LoadResourceString(&Adexcept::_sdstProcHandler)
extern PACKAGE System::ResourceString _sdstEventHandler;
#define Adexcept_sdstEventHandler System::LoadResourceString(&Adexcept::_sdstEventHandler)
extern PACKAGE System::ResourceString _sdstSWill;
#define Adexcept_sdstSWill System::LoadResourceString(&Adexcept::_sdstSWill)
extern PACKAGE System::ResourceString _sdstSWont;
#define Adexcept_sdstSWont System::LoadResourceString(&Adexcept::_sdstSWont)
extern PACKAGE System::ResourceString _sdstSDo;
#define Adexcept_sdstSDo System::LoadResourceString(&Adexcept::_sdstSDo)
extern PACKAGE System::ResourceString _sdstSDont;
#define Adexcept_sdstSDont System::LoadResourceString(&Adexcept::_sdstSDont)
extern PACKAGE System::ResourceString _sdstRWill;
#define Adexcept_sdstRWill System::LoadResourceString(&Adexcept::_sdstRWill)
extern PACKAGE System::ResourceString _sdstRWont;
#define Adexcept_sdstRWont System::LoadResourceString(&Adexcept::_sdstRWont)
extern PACKAGE System::ResourceString _sdstRDo;
#define Adexcept_sdstRDo System::LoadResourceString(&Adexcept::_sdstRDo)
extern PACKAGE System::ResourceString _sdstRDont;
#define Adexcept_sdstRDont System::LoadResourceString(&Adexcept::_sdstRDont)
extern PACKAGE System::ResourceString _sdstCommand;
#define Adexcept_sdstCommand System::LoadResourceString(&Adexcept::_sdstCommand)
extern PACKAGE System::ResourceString _sdstSTerm;
#define Adexcept_sdstSTerm System::LoadResourceString(&Adexcept::_sdstSTerm)
extern PACKAGE System::ResourceString _sdsttfNone;
#define Adexcept_sdsttfNone System::LoadResourceString(&Adexcept::_sdsttfNone)
extern PACKAGE System::ResourceString _sdsttfGetEntry;
#define Adexcept_sdsttfGetEntry System::LoadResourceString(&Adexcept::_sdsttfGetEntry)
extern PACKAGE System::ResourceString _sdsttfInit;
#define Adexcept_sdsttfInit System::LoadResourceString(&Adexcept::_sdsttfInit)
extern PACKAGE System::ResourceString _sdsttf1Init1;
#define Adexcept_sdsttf1Init1 System::LoadResourceString(&Adexcept::_sdsttf1Init1)
extern PACKAGE System::ResourceString _sdsttf2Init1;
#define Adexcept_sdsttf2Init1 System::LoadResourceString(&Adexcept::_sdsttf2Init1)
extern PACKAGE System::ResourceString _sdsttf2Init1A;
#define Adexcept_sdsttf2Init1A System::LoadResourceString(&Adexcept::_sdsttf2Init1A)
extern PACKAGE System::ResourceString _sdsttf2Init1B;
#define Adexcept_sdsttf2Init1B System::LoadResourceString(&Adexcept::_sdsttf2Init1B)
extern PACKAGE System::ResourceString _sdsttf2Init2;
#define Adexcept_sdsttf2Init2 System::LoadResourceString(&Adexcept::_sdsttf2Init2)
extern PACKAGE System::ResourceString _sdsttf2Init3;
#define Adexcept_sdsttf2Init3 System::LoadResourceString(&Adexcept::_sdsttf2Init3)
extern PACKAGE System::ResourceString _sdsttfDial;
#define Adexcept_sdsttfDial System::LoadResourceString(&Adexcept::_sdsttfDial)
extern PACKAGE System::ResourceString _sdsttfRetryWait;
#define Adexcept_sdsttfRetryWait System::LoadResourceString(&Adexcept::_sdsttfRetryWait)
extern PACKAGE System::ResourceString _sdsttf1Connect;
#define Adexcept_sdsttf1Connect System::LoadResourceString(&Adexcept::_sdsttf1Connect)
extern PACKAGE System::ResourceString _sdsttf1SendTSI;
#define Adexcept_sdsttf1SendTSI System::LoadResourceString(&Adexcept::_sdsttf1SendTSI)
extern PACKAGE System::ResourceString _sdsttf1TSIResponse;
#define Adexcept_sdsttf1TSIResponse System::LoadResourceString(&Adexcept::_sdsttf1TSIResponse)
extern PACKAGE System::ResourceString _sdsttf1DCSResponse;
#define Adexcept_sdsttf1DCSResponse System::LoadResourceString(&Adexcept::_sdsttf1DCSResponse)
extern PACKAGE System::ResourceString _sdsttf1TrainStart;
#define Adexcept_sdsttf1TrainStart System::LoadResourceString(&Adexcept::_sdsttf1TrainStart)
extern PACKAGE System::ResourceString _sdsttf1TrainFinish;
#define Adexcept_sdsttf1TrainFinish System::LoadResourceString(&Adexcept::_sdsttf1TrainFinish)
extern PACKAGE System::ResourceString _sdsttf1WaitCFR;
#define Adexcept_sdsttf1WaitCFR System::LoadResourceString(&Adexcept::_sdsttf1WaitCFR)
extern PACKAGE System::ResourceString _sdsttf1WaitPageConnect;
#define Adexcept_sdsttf1WaitPageConnect System::LoadResourceString(&Adexcept::_sdsttf1WaitPageConnect)
extern PACKAGE System::ResourceString _sdsttf2Connect;
#define Adexcept_sdsttf2Connect System::LoadResourceString(&Adexcept::_sdsttf2Connect)
extern PACKAGE System::ResourceString _sdsttf2GetParams;
#define Adexcept_sdsttf2GetParams System::LoadResourceString(&Adexcept::_sdsttf2GetParams)
extern PACKAGE System::ResourceString _sdsttfWaitXon;
#define Adexcept_sdsttfWaitXon System::LoadResourceString(&Adexcept::_sdsttfWaitXon)
extern PACKAGE System::ResourceString _sdsttfWaitFreeHeader;
#define Adexcept_sdsttfWaitFreeHeader System::LoadResourceString(&Adexcept::_sdsttfWaitFreeHeader)
extern PACKAGE System::ResourceString _sdsttfSendPageHeader;
#define Adexcept_sdsttfSendPageHeader System::LoadResourceString(&Adexcept::_sdsttfSendPageHeader)
extern PACKAGE System::ResourceString _sdsttfOpenCover;
#define Adexcept_sdsttfOpenCover System::LoadResourceString(&Adexcept::_sdsttfOpenCover)
extern PACKAGE System::ResourceString _sdsttfSendCover;
#define Adexcept_sdsttfSendCover System::LoadResourceString(&Adexcept::_sdsttfSendCover)
extern PACKAGE System::ResourceString _sdsttfPrepPage;
#define Adexcept_sdsttfPrepPage System::LoadResourceString(&Adexcept::_sdsttfPrepPage)
extern PACKAGE System::ResourceString _sdsttfSendPage;
#define Adexcept_sdsttfSendPage System::LoadResourceString(&Adexcept::_sdsttfSendPage)
extern PACKAGE System::ResourceString _sdsttfDrainPage;
#define Adexcept_sdsttfDrainPage System::LoadResourceString(&Adexcept::_sdsttfDrainPage)
extern PACKAGE System::ResourceString _sdsttf1PageEnd;
#define Adexcept_sdsttf1PageEnd System::LoadResourceString(&Adexcept::_sdsttf1PageEnd)
extern PACKAGE System::ResourceString _sdsttf1PrepareEOP;
#define Adexcept_sdsttf1PrepareEOP System::LoadResourceString(&Adexcept::_sdsttf1PrepareEOP)
extern PACKAGE System::ResourceString _sdsttf1SendEOP;
#define Adexcept_sdsttf1SendEOP System::LoadResourceString(&Adexcept::_sdsttf1SendEOP)
extern PACKAGE System::ResourceString _sdsttf1WaitMPS;
#define Adexcept_sdsttf1WaitMPS System::LoadResourceString(&Adexcept::_sdsttf1WaitMPS)
extern PACKAGE System::ResourceString _sdsttf1WaitEOP;
#define Adexcept_sdsttf1WaitEOP System::LoadResourceString(&Adexcept::_sdsttf1WaitEOP)
extern PACKAGE System::ResourceString _sdsttf1WaitMCF;
#define Adexcept_sdsttf1WaitMCF System::LoadResourceString(&Adexcept::_sdsttf1WaitMCF)
extern PACKAGE System::ResourceString _sdsttf1SendDCN;
#define Adexcept_sdsttf1SendDCN System::LoadResourceString(&Adexcept::_sdsttf1SendDCN)
extern PACKAGE System::ResourceString _sdsttf1Hangup;
#define Adexcept_sdsttf1Hangup System::LoadResourceString(&Adexcept::_sdsttf1Hangup)
extern PACKAGE System::ResourceString _sdsttf1WaitHangup;
#define Adexcept_sdsttf1WaitHangup System::LoadResourceString(&Adexcept::_sdsttf1WaitHangup)
extern PACKAGE System::ResourceString _sdsttf2SendEOP;
#define Adexcept_sdsttf2SendEOP System::LoadResourceString(&Adexcept::_sdsttf2SendEOP)
extern PACKAGE System::ResourceString _sdsttf2WaitFPTS;
#define Adexcept_sdsttf2WaitFPTS System::LoadResourceString(&Adexcept::_sdsttf2WaitFPTS)
extern PACKAGE System::ResourceString _sdsttf2WaitFET;
#define Adexcept_sdsttf2WaitFET System::LoadResourceString(&Adexcept::_sdsttf2WaitFET)
extern PACKAGE System::ResourceString _sdsttf2WaitPageOK;
#define Adexcept_sdsttf2WaitPageOK System::LoadResourceString(&Adexcept::_sdsttf2WaitPageOK)
extern PACKAGE System::ResourceString _sdsttf2SendNewParams;
#define Adexcept_sdsttf2SendNewParams System::LoadResourceString(&Adexcept::_sdsttf2SendNewParams)
extern PACKAGE System::ResourceString _sdsttf2NextPage;
#define Adexcept_sdsttf2NextPage System::LoadResourceString(&Adexcept::_sdsttf2NextPage)
extern PACKAGE System::ResourceString _sdsttf20CheckPage;
#define Adexcept_sdsttf20CheckPage System::LoadResourceString(&Adexcept::_sdsttf20CheckPage)
extern PACKAGE System::ResourceString _sdsttfClose;
#define Adexcept_sdsttfClose System::LoadResourceString(&Adexcept::_sdsttfClose)
extern PACKAGE System::ResourceString _sdsttfCompleteOK;
#define Adexcept_sdsttfCompleteOK System::LoadResourceString(&Adexcept::_sdsttfCompleteOK)
extern PACKAGE System::ResourceString _sdsttfAbort;
#define Adexcept_sdsttfAbort System::LoadResourceString(&Adexcept::_sdsttfAbort)
extern PACKAGE System::ResourceString _sdsttfDone;
#define Adexcept_sdsttfDone System::LoadResourceString(&Adexcept::_sdsttfDone)
extern PACKAGE System::ResourceString _sdstrfNone;
#define Adexcept_sdstrfNone System::LoadResourceString(&Adexcept::_sdstrfNone)
extern PACKAGE System::ResourceString _sdstrfInit;
#define Adexcept_sdstrfInit System::LoadResourceString(&Adexcept::_sdstrfInit)
extern PACKAGE System::ResourceString _sdstrf1Init1;
#define Adexcept_sdstrf1Init1 System::LoadResourceString(&Adexcept::_sdstrf1Init1)
extern PACKAGE System::ResourceString _sdstrf2Init1;
#define Adexcept_sdstrf2Init1 System::LoadResourceString(&Adexcept::_sdstrf2Init1)
extern PACKAGE System::ResourceString _sdstrf2Init1A;
#define Adexcept_sdstrf2Init1A System::LoadResourceString(&Adexcept::_sdstrf2Init1A)
extern PACKAGE System::ResourceString _sdstrf2Init1B;
#define Adexcept_sdstrf2Init1B System::LoadResourceString(&Adexcept::_sdstrf2Init1B)
extern PACKAGE System::ResourceString _sdstrf2Init2;
#define Adexcept_sdstrf2Init2 System::LoadResourceString(&Adexcept::_sdstrf2Init2)
extern PACKAGE System::ResourceString _sdstrf2Init3;
#define Adexcept_sdstrf2Init3 System::LoadResourceString(&Adexcept::_sdstrf2Init3)
extern PACKAGE System::ResourceString _sdstrfWaiting;
#define Adexcept_sdstrfWaiting System::LoadResourceString(&Adexcept::_sdstrfWaiting)
extern PACKAGE System::ResourceString _sdstrfAnswer;
#define Adexcept_sdstrfAnswer System::LoadResourceString(&Adexcept::_sdstrfAnswer)
extern PACKAGE System::ResourceString _sdstrf1SendCSI;
#define Adexcept_sdstrf1SendCSI System::LoadResourceString(&Adexcept::_sdstrf1SendCSI)
extern PACKAGE System::ResourceString _sdstrf1SendDIS;
#define Adexcept_sdstrf1SendDIS System::LoadResourceString(&Adexcept::_sdstrf1SendDIS)
extern PACKAGE System::ResourceString _sdstrf1CollectFrames;
#define Adexcept_sdstrf1CollectFrames System::LoadResourceString(&Adexcept::_sdstrf1CollectFrames)
extern PACKAGE System::ResourceString _sdstrf1CollectRetry1;
#define Adexcept_sdstrf1CollectRetry1 System::LoadResourceString(&Adexcept::_sdstrf1CollectRetry1)
extern PACKAGE System::ResourceString _sdstrf1CollectRetry2;
#define Adexcept_sdstrf1CollectRetry2 System::LoadResourceString(&Adexcept::_sdstrf1CollectRetry2)
extern PACKAGE System::ResourceString _sdstrf1StartTrain;
#define Adexcept_sdstrf1StartTrain System::LoadResourceString(&Adexcept::_sdstrf1StartTrain)
extern PACKAGE System::ResourceString _sdstrf1CollectTrain;
#define Adexcept_sdstrf1CollectTrain System::LoadResourceString(&Adexcept::_sdstrf1CollectTrain)
extern PACKAGE System::ResourceString _sdstrf1Timeout;
#define Adexcept_sdstrf1Timeout System::LoadResourceString(&Adexcept::_sdstrf1Timeout)
extern PACKAGE System::ResourceString _sdstrf1Retrain;
#define Adexcept_sdstrf1Retrain System::LoadResourceString(&Adexcept::_sdstrf1Retrain)
extern PACKAGE System::ResourceString _sdstrf1FinishTrain;
#define Adexcept_sdstrf1FinishTrain System::LoadResourceString(&Adexcept::_sdstrf1FinishTrain)
extern PACKAGE System::ResourceString _sdstrf1SendCFR;
#define Adexcept_sdstrf1SendCFR System::LoadResourceString(&Adexcept::_sdstrf1SendCFR)
extern PACKAGE System::ResourceString _sdstrf1WaitPageConnect;
#define Adexcept_sdstrf1WaitPageConnect System::LoadResourceString(&Adexcept::_sdstrf1WaitPageConnect)
extern PACKAGE System::ResourceString _sdstrf2ValidConnect;
#define Adexcept_sdstrf2ValidConnect System::LoadResourceString(&Adexcept::_sdstrf2ValidConnect)
extern PACKAGE System::ResourceString _sdstrf2GetSenderID;
#define Adexcept_sdstrf2GetSenderID System::LoadResourceString(&Adexcept::_sdstrf2GetSenderID)
extern PACKAGE System::ResourceString _sdstrf2GetConnect;
#define Adexcept_sdstrf2GetConnect System::LoadResourceString(&Adexcept::_sdstrf2GetConnect)
extern PACKAGE System::ResourceString _sdstrfStartPage;
#define Adexcept_sdstrfStartPage System::LoadResourceString(&Adexcept::_sdstrfStartPage)
extern PACKAGE System::ResourceString _sdstrfGetPageData;
#define Adexcept_sdstrfGetPageData System::LoadResourceString(&Adexcept::_sdstrfGetPageData)
extern PACKAGE System::ResourceString _sdstrf1FinishPage;
#define Adexcept_sdstrf1FinishPage System::LoadResourceString(&Adexcept::_sdstrf1FinishPage)
extern PACKAGE System::ResourceString _sdstrf1WaitEOP;
#define Adexcept_sdstrf1WaitEOP System::LoadResourceString(&Adexcept::_sdstrf1WaitEOP)
extern PACKAGE System::ResourceString _sdstrf1WritePage;
#define Adexcept_sdstrf1WritePage System::LoadResourceString(&Adexcept::_sdstrf1WritePage)
extern PACKAGE System::ResourceString _sdstrf1SendMCF;
#define Adexcept_sdstrf1SendMCF System::LoadResourceString(&Adexcept::_sdstrf1SendMCF)
extern PACKAGE System::ResourceString _sdstrf1WaitDCN;
#define Adexcept_sdstrf1WaitDCN System::LoadResourceString(&Adexcept::_sdstrf1WaitDCN)
extern PACKAGE System::ResourceString _sdstrf1WaitHangup;
#define Adexcept_sdstrf1WaitHangup System::LoadResourceString(&Adexcept::_sdstrf1WaitHangup)
extern PACKAGE System::ResourceString _sdstrf2GetPageResult;
#define Adexcept_sdstrf2GetPageResult System::LoadResourceString(&Adexcept::_sdstrf2GetPageResult)
extern PACKAGE System::ResourceString _sdstrf2GetFHNG;
#define Adexcept_sdstrf2GetFHNG System::LoadResourceString(&Adexcept::_sdstrf2GetFHNG)
extern PACKAGE System::ResourceString _sdstrfComplete;
#define Adexcept_sdstrfComplete System::LoadResourceString(&Adexcept::_sdstrfComplete)
extern PACKAGE System::ResourceString _sdstrfAbort;
#define Adexcept_sdstrfAbort System::LoadResourceString(&Adexcept::_sdstrfAbort)
extern PACKAGE System::ResourceString _sdstrfDone;
#define Adexcept_sdstrfDone System::LoadResourceString(&Adexcept::_sdstrfDone)
extern PACKAGE System::ResourceString _sdsttxInitial;
#define Adexcept_sdsttxInitial System::LoadResourceString(&Adexcept::_sdsttxInitial)
extern PACKAGE System::ResourceString _sdsttxHandshake;
#define Adexcept_sdsttxHandshake System::LoadResourceString(&Adexcept::_sdsttxHandshake)
extern PACKAGE System::ResourceString _sdsttxGetBlock;
#define Adexcept_sdsttxGetBlock System::LoadResourceString(&Adexcept::_sdsttxGetBlock)
extern PACKAGE System::ResourceString _sdsttxWaitFreeSpace;
#define Adexcept_sdsttxWaitFreeSpace System::LoadResourceString(&Adexcept::_sdsttxWaitFreeSpace)
extern PACKAGE System::ResourceString _sdsttxSendBlock;
#define Adexcept_sdsttxSendBlock System::LoadResourceString(&Adexcept::_sdsttxSendBlock)
extern PACKAGE System::ResourceString _sdsttxDraining;
#define Adexcept_sdsttxDraining System::LoadResourceString(&Adexcept::_sdsttxDraining)
extern PACKAGE System::ResourceString _sdsttxReplyPending;
#define Adexcept_sdsttxReplyPending System::LoadResourceString(&Adexcept::_sdsttxReplyPending)
extern PACKAGE System::ResourceString _sdsttxEndDrain;
#define Adexcept_sdsttxEndDrain System::LoadResourceString(&Adexcept::_sdsttxEndDrain)
extern PACKAGE System::ResourceString _sdsttxFirstEndOfTransmit;
#define Adexcept_sdsttxFirstEndOfTransmit System::LoadResourceString(&Adexcept::_sdsttxFirstEndOfTransmit)
extern PACKAGE System::ResourceString _sdsttxRestEndOfTransmit;
#define Adexcept_sdsttxRestEndOfTransmit System::LoadResourceString(&Adexcept::_sdsttxRestEndOfTransmit)
extern PACKAGE System::ResourceString _sdsttxEotReply;
#define Adexcept_sdsttxEotReply System::LoadResourceString(&Adexcept::_sdsttxEotReply)
extern PACKAGE System::ResourceString _sdsttxFinished;
#define Adexcept_sdsttxFinished System::LoadResourceString(&Adexcept::_sdsttxFinished)
extern PACKAGE System::ResourceString _sdsttxDone;
#define Adexcept_sdsttxDone System::LoadResourceString(&Adexcept::_sdsttxDone)
extern PACKAGE System::ResourceString _sdstrxInitial;
#define Adexcept_sdstrxInitial System::LoadResourceString(&Adexcept::_sdstrxInitial)
extern PACKAGE System::ResourceString _sdstrxWaitForHSReply;
#define Adexcept_sdstrxWaitForHSReply System::LoadResourceString(&Adexcept::_sdstrxWaitForHSReply)
extern PACKAGE System::ResourceString _sdstrxWaitForBlockStart;
#define Adexcept_sdstrxWaitForBlockStart System::LoadResourceString(&Adexcept::_sdstrxWaitForBlockStart)
extern PACKAGE System::ResourceString _sdstrxCollectBlock;
#define Adexcept_sdstrxCollectBlock System::LoadResourceString(&Adexcept::_sdstrxCollectBlock)
extern PACKAGE System::ResourceString _sdstrxProcessBlock;
#define Adexcept_sdstrxProcessBlock System::LoadResourceString(&Adexcept::_sdstrxProcessBlock)
extern PACKAGE System::ResourceString _sdstrxFinishedSkip;
#define Adexcept_sdstrxFinishedSkip System::LoadResourceString(&Adexcept::_sdstrxFinishedSkip)
extern PACKAGE System::ResourceString _sdstrxFinished;
#define Adexcept_sdstrxFinished System::LoadResourceString(&Adexcept::_sdstrxFinished)
extern PACKAGE System::ResourceString _sdstrxDone;
#define Adexcept_sdstrxDone System::LoadResourceString(&Adexcept::_sdstrxDone)
extern PACKAGE System::ResourceString _sdsttyInitial;
#define Adexcept_sdsttyInitial System::LoadResourceString(&Adexcept::_sdsttyInitial)
extern PACKAGE System::ResourceString _sdsttyHandshake;
#define Adexcept_sdsttyHandshake System::LoadResourceString(&Adexcept::_sdsttyHandshake)
extern PACKAGE System::ResourceString _sdsttyGetFileName;
#define Adexcept_sdsttyGetFileName System::LoadResourceString(&Adexcept::_sdsttyGetFileName)
extern PACKAGE System::ResourceString _sdsttySendFileName;
#define Adexcept_sdsttySendFileName System::LoadResourceString(&Adexcept::_sdsttySendFileName)
extern PACKAGE System::ResourceString _sdsttyDraining;
#define Adexcept_sdsttyDraining System::LoadResourceString(&Adexcept::_sdsttyDraining)
extern PACKAGE System::ResourceString _sdsttyReplyPending;
#define Adexcept_sdsttyReplyPending System::LoadResourceString(&Adexcept::_sdsttyReplyPending)
extern PACKAGE System::ResourceString _sdsttyPrepXmodem;
#define Adexcept_sdsttyPrepXmodem System::LoadResourceString(&Adexcept::_sdsttyPrepXmodem)
extern PACKAGE System::ResourceString _sdsttySendXmodem;
#define Adexcept_sdsttySendXmodem System::LoadResourceString(&Adexcept::_sdsttySendXmodem)
extern PACKAGE System::ResourceString _sdsttyFinished;
#define Adexcept_sdsttyFinished System::LoadResourceString(&Adexcept::_sdsttyFinished)
extern PACKAGE System::ResourceString _sdsttyFinishDrain;
#define Adexcept_sdsttyFinishDrain System::LoadResourceString(&Adexcept::_sdsttyFinishDrain)
extern PACKAGE System::ResourceString _sdsttyDone;
#define Adexcept_sdsttyDone System::LoadResourceString(&Adexcept::_sdsttyDone)
extern PACKAGE System::ResourceString _sdstryInitial;
#define Adexcept_sdstryInitial System::LoadResourceString(&Adexcept::_sdstryInitial)
extern PACKAGE System::ResourceString _sdstryDelay;
#define Adexcept_sdstryDelay System::LoadResourceString(&Adexcept::_sdstryDelay)
extern PACKAGE System::ResourceString _sdstryWaitForHSReply;
#define Adexcept_sdstryWaitForHSReply System::LoadResourceString(&Adexcept::_sdstryWaitForHSReply)
extern PACKAGE System::ResourceString _sdstryWaitForBlockStart;
#define Adexcept_sdstryWaitForBlockStart System::LoadResourceString(&Adexcept::_sdstryWaitForBlockStart)
extern PACKAGE System::ResourceString _sdstryCollectBlock;
#define Adexcept_sdstryCollectBlock System::LoadResourceString(&Adexcept::_sdstryCollectBlock)
extern PACKAGE System::ResourceString _sdstryProcessBlock;
#define Adexcept_sdstryProcessBlock System::LoadResourceString(&Adexcept::_sdstryProcessBlock)
extern PACKAGE System::ResourceString _sdstryOpenFile;
#define Adexcept_sdstryOpenFile System::LoadResourceString(&Adexcept::_sdstryOpenFile)
extern PACKAGE System::ResourceString _sdstryPrepXmodem;
#define Adexcept_sdstryPrepXmodem System::LoadResourceString(&Adexcept::_sdstryPrepXmodem)
extern PACKAGE System::ResourceString _sdstryReceiveXmodem;
#define Adexcept_sdstryReceiveXmodem System::LoadResourceString(&Adexcept::_sdstryReceiveXmodem)
extern PACKAGE System::ResourceString _sdstryFinished;
#define Adexcept_sdstryFinished System::LoadResourceString(&Adexcept::_sdstryFinished)
extern PACKAGE System::ResourceString _sdstryDone;
#define Adexcept_sdstryDone System::LoadResourceString(&Adexcept::_sdstryDone)
extern PACKAGE System::ResourceString _sdsttzInitial;
#define Adexcept_sdsttzInitial System::LoadResourceString(&Adexcept::_sdsttzInitial)
extern PACKAGE System::ResourceString _sdsttzHandshake;
#define Adexcept_sdsttzHandshake System::LoadResourceString(&Adexcept::_sdsttzHandshake)
extern PACKAGE System::ResourceString _sdsttzGetFile;
#define Adexcept_sdsttzGetFile System::LoadResourceString(&Adexcept::_sdsttzGetFile)
extern PACKAGE System::ResourceString _sdsttzSendFile;
#define Adexcept_sdsttzSendFile System::LoadResourceString(&Adexcept::_sdsttzSendFile)
extern PACKAGE System::ResourceString _sdsttzCheckFile;
#define Adexcept_sdsttzCheckFile System::LoadResourceString(&Adexcept::_sdsttzCheckFile)
extern PACKAGE System::ResourceString _sdsttzStartData;
#define Adexcept_sdsttzStartData System::LoadResourceString(&Adexcept::_sdsttzStartData)
extern PACKAGE System::ResourceString _sdsttzEscapeData;
#define Adexcept_sdsttzEscapeData System::LoadResourceString(&Adexcept::_sdsttzEscapeData)
extern PACKAGE System::ResourceString _sdsttzSendData;
#define Adexcept_sdsttzSendData System::LoadResourceString(&Adexcept::_sdsttzSendData)
extern PACKAGE System::ResourceString _sdsttzWaitAck;
#define Adexcept_sdsttzWaitAck System::LoadResourceString(&Adexcept::_sdsttzWaitAck)
extern PACKAGE System::ResourceString _sdsttzSendEof;
#define Adexcept_sdsttzSendEof System::LoadResourceString(&Adexcept::_sdsttzSendEof)
extern PACKAGE System::ResourceString _sdsttzDrainEof;
#define Adexcept_sdsttzDrainEof System::LoadResourceString(&Adexcept::_sdsttzDrainEof)
extern PACKAGE System::ResourceString _sdsttzCheckEof;
#define Adexcept_sdsttzCheckEof System::LoadResourceString(&Adexcept::_sdsttzCheckEof)
extern PACKAGE System::ResourceString _sdsttzSendFinish;
#define Adexcept_sdsttzSendFinish System::LoadResourceString(&Adexcept::_sdsttzSendFinish)
extern PACKAGE System::ResourceString _sdsttzCheckFinish;
#define Adexcept_sdsttzCheckFinish System::LoadResourceString(&Adexcept::_sdsttzCheckFinish)
extern PACKAGE System::ResourceString _sdsttzError;
#define Adexcept_sdsttzError System::LoadResourceString(&Adexcept::_sdsttzError)
extern PACKAGE System::ResourceString _sdsttzCleanup;
#define Adexcept_sdsttzCleanup System::LoadResourceString(&Adexcept::_sdsttzCleanup)
extern PACKAGE System::ResourceString _sdsttzDone;
#define Adexcept_sdsttzDone System::LoadResourceString(&Adexcept::_sdsttzDone)
extern PACKAGE System::ResourceString _sdstrzRqstFile;
#define Adexcept_sdstrzRqstFile System::LoadResourceString(&Adexcept::_sdstrzRqstFile)
extern PACKAGE System::ResourceString _sdstrzDelay;
#define Adexcept_sdstrzDelay System::LoadResourceString(&Adexcept::_sdstrzDelay)
extern PACKAGE System::ResourceString _sdstrzWaitFile;
#define Adexcept_sdstrzWaitFile System::LoadResourceString(&Adexcept::_sdstrzWaitFile)
extern PACKAGE System::ResourceString _sdstrzCollectFile;
#define Adexcept_sdstrzCollectFile System::LoadResourceString(&Adexcept::_sdstrzCollectFile)
extern PACKAGE System::ResourceString _sdstrzSendInit;
#define Adexcept_sdstrzSendInit System::LoadResourceString(&Adexcept::_sdstrzSendInit)
extern PACKAGE System::ResourceString _sdstrzSendBlockPrep;
#define Adexcept_sdstrzSendBlockPrep System::LoadResourceString(&Adexcept::_sdstrzSendBlockPrep)
extern PACKAGE System::ResourceString _sdstrzSendBlock;
#define Adexcept_sdstrzSendBlock System::LoadResourceString(&Adexcept::_sdstrzSendBlock)
extern PACKAGE System::ResourceString _sdstrzSync;
#define Adexcept_sdstrzSync System::LoadResourceString(&Adexcept::_sdstrzSync)
extern PACKAGE System::ResourceString _sdstrzStartFile;
#define Adexcept_sdstrzStartFile System::LoadResourceString(&Adexcept::_sdstrzStartFile)
extern PACKAGE System::ResourceString _sdstrzStartData;
#define Adexcept_sdstrzStartData System::LoadResourceString(&Adexcept::_sdstrzStartData)
extern PACKAGE System::ResourceString _sdstrzCollectData;
#define Adexcept_sdstrzCollectData System::LoadResourceString(&Adexcept::_sdstrzCollectData)
extern PACKAGE System::ResourceString _sdstrzGotData;
#define Adexcept_sdstrzGotData System::LoadResourceString(&Adexcept::_sdstrzGotData)
extern PACKAGE System::ResourceString _sdstrzWaitEof;
#define Adexcept_sdstrzWaitEof System::LoadResourceString(&Adexcept::_sdstrzWaitEof)
extern PACKAGE System::ResourceString _sdstrzEndOfFile;
#define Adexcept_sdstrzEndOfFile System::LoadResourceString(&Adexcept::_sdstrzEndOfFile)
extern PACKAGE System::ResourceString _sdstrzSendFinish;
#define Adexcept_sdstrzSendFinish System::LoadResourceString(&Adexcept::_sdstrzSendFinish)
extern PACKAGE System::ResourceString _sdstrzCollectFinish;
#define Adexcept_sdstrzCollectFinish System::LoadResourceString(&Adexcept::_sdstrzCollectFinish)
extern PACKAGE System::ResourceString _sdstrzError;
#define Adexcept_sdstrzError System::LoadResourceString(&Adexcept::_sdstrzError)
extern PACKAGE System::ResourceString _sdstrzWaitCancel;
#define Adexcept_sdstrzWaitCancel System::LoadResourceString(&Adexcept::_sdstrzWaitCancel)
extern PACKAGE System::ResourceString _sdstrzCleanup;
#define Adexcept_sdstrzCleanup System::LoadResourceString(&Adexcept::_sdstrzCleanup)
extern PACKAGE System::ResourceString _sdstrzDone;
#define Adexcept_sdstrzDone System::LoadResourceString(&Adexcept::_sdstrzDone)
extern PACKAGE System::ResourceString _sdsttkInit;
#define Adexcept_sdsttkInit System::LoadResourceString(&Adexcept::_sdsttkInit)
extern PACKAGE System::ResourceString _sdsttkInitReply;
#define Adexcept_sdsttkInitReply System::LoadResourceString(&Adexcept::_sdsttkInitReply)
extern PACKAGE System::ResourceString _sdsttkCollectInit;
#define Adexcept_sdsttkCollectInit System::LoadResourceString(&Adexcept::_sdsttkCollectInit)
extern PACKAGE System::ResourceString _sdsttkOpenFile;
#define Adexcept_sdsttkOpenFile System::LoadResourceString(&Adexcept::_sdsttkOpenFile)
extern PACKAGE System::ResourceString _sdsttkSendFile;
#define Adexcept_sdsttkSendFile System::LoadResourceString(&Adexcept::_sdsttkSendFile)
extern PACKAGE System::ResourceString _sdsttkFileReply;
#define Adexcept_sdsttkFileReply System::LoadResourceString(&Adexcept::_sdsttkFileReply)
extern PACKAGE System::ResourceString _sdsttkCollectFile;
#define Adexcept_sdsttkCollectFile System::LoadResourceString(&Adexcept::_sdsttkCollectFile)
extern PACKAGE System::ResourceString _sdsttkCheckTable;
#define Adexcept_sdsttkCheckTable System::LoadResourceString(&Adexcept::_sdsttkCheckTable)
extern PACKAGE System::ResourceString _sdsttkSendData;
#define Adexcept_sdsttkSendData System::LoadResourceString(&Adexcept::_sdsttkSendData)
extern PACKAGE System::ResourceString _sdsttkBlockReply;
#define Adexcept_sdsttkBlockReply System::LoadResourceString(&Adexcept::_sdsttkBlockReply)
extern PACKAGE System::ResourceString _sdsttkCollectBlock;
#define Adexcept_sdsttkCollectBlock System::LoadResourceString(&Adexcept::_sdsttkCollectBlock)
extern PACKAGE System::ResourceString _sdsttkSendEof;
#define Adexcept_sdsttkSendEof System::LoadResourceString(&Adexcept::_sdsttkSendEof)
extern PACKAGE System::ResourceString _sdsttkEofReply;
#define Adexcept_sdsttkEofReply System::LoadResourceString(&Adexcept::_sdsttkEofReply)
extern PACKAGE System::ResourceString _sdsttkCollectEof;
#define Adexcept_sdsttkCollectEof System::LoadResourceString(&Adexcept::_sdsttkCollectEof)
extern PACKAGE System::ResourceString _sdsttkSendBreak;
#define Adexcept_sdsttkSendBreak System::LoadResourceString(&Adexcept::_sdsttkSendBreak)
extern PACKAGE System::ResourceString _sdsttkBreakReply;
#define Adexcept_sdsttkBreakReply System::LoadResourceString(&Adexcept::_sdsttkBreakReply)
extern PACKAGE System::ResourceString _sdsttkCollectBreak;
#define Adexcept_sdsttkCollectBreak System::LoadResourceString(&Adexcept::_sdsttkCollectBreak)
extern PACKAGE System::ResourceString _sdsttkComplete;
#define Adexcept_sdsttkComplete System::LoadResourceString(&Adexcept::_sdsttkComplete)
extern PACKAGE System::ResourceString _sdsttkWaitCancel;
#define Adexcept_sdsttkWaitCancel System::LoadResourceString(&Adexcept::_sdsttkWaitCancel)
extern PACKAGE System::ResourceString _sdsttkError;
#define Adexcept_sdsttkError System::LoadResourceString(&Adexcept::_sdsttkError)
extern PACKAGE System::ResourceString _sdsttkDone;
#define Adexcept_sdsttkDone System::LoadResourceString(&Adexcept::_sdsttkDone)
extern PACKAGE System::ResourceString _sdstrkInit;
#define Adexcept_sdstrkInit System::LoadResourceString(&Adexcept::_sdstrkInit)
extern PACKAGE System::ResourceString _sdstrkGetInit;
#define Adexcept_sdstrkGetInit System::LoadResourceString(&Adexcept::_sdstrkGetInit)
extern PACKAGE System::ResourceString _sdstrkCollectInit;
#define Adexcept_sdstrkCollectInit System::LoadResourceString(&Adexcept::_sdstrkCollectInit)
extern PACKAGE System::ResourceString _sdstrkGetFile;
#define Adexcept_sdstrkGetFile System::LoadResourceString(&Adexcept::_sdstrkGetFile)
extern PACKAGE System::ResourceString _sdstrkCollectFile;
#define Adexcept_sdstrkCollectFile System::LoadResourceString(&Adexcept::_sdstrkCollectFile)
extern PACKAGE System::ResourceString _sdstrkGetData;
#define Adexcept_sdstrkGetData System::LoadResourceString(&Adexcept::_sdstrkGetData)
extern PACKAGE System::ResourceString _sdstrkCollectData;
#define Adexcept_sdstrkCollectData System::LoadResourceString(&Adexcept::_sdstrkCollectData)
extern PACKAGE System::ResourceString _sdstrkComplete;
#define Adexcept_sdstrkComplete System::LoadResourceString(&Adexcept::_sdstrkComplete)
extern PACKAGE System::ResourceString _sdstrkWaitCancel;
#define Adexcept_sdstrkWaitCancel System::LoadResourceString(&Adexcept::_sdstrkWaitCancel)
extern PACKAGE System::ResourceString _sdstrkError;
#define Adexcept_sdstrkError System::LoadResourceString(&Adexcept::_sdstrkError)
extern PACKAGE System::ResourceString _sdstrkDone;
#define Adexcept_sdstrkDone System::LoadResourceString(&Adexcept::_sdstrkDone)
extern PACKAGE System::ResourceString _sdsttaInitial;
#define Adexcept_sdsttaInitial System::LoadResourceString(&Adexcept::_sdsttaInitial)
extern PACKAGE System::ResourceString _sdsttaGetBlock;
#define Adexcept_sdsttaGetBlock System::LoadResourceString(&Adexcept::_sdsttaGetBlock)
extern PACKAGE System::ResourceString _sdsttaWaitFreeSpace;
#define Adexcept_sdsttaWaitFreeSpace System::LoadResourceString(&Adexcept::_sdsttaWaitFreeSpace)
extern PACKAGE System::ResourceString _sdsttaSendBlock;
#define Adexcept_sdsttaSendBlock System::LoadResourceString(&Adexcept::_sdsttaSendBlock)
extern PACKAGE System::ResourceString _sdsttaSendDelay;
#define Adexcept_sdsttaSendDelay System::LoadResourceString(&Adexcept::_sdsttaSendDelay)
extern PACKAGE System::ResourceString _sdsttaFinishDrain;
#define Adexcept_sdsttaFinishDrain System::LoadResourceString(&Adexcept::_sdsttaFinishDrain)
extern PACKAGE System::ResourceString _sdsttaFinished;
#define Adexcept_sdsttaFinished System::LoadResourceString(&Adexcept::_sdsttaFinished)
extern PACKAGE System::ResourceString _sdsttaDone;
#define Adexcept_sdsttaDone System::LoadResourceString(&Adexcept::_sdsttaDone)
extern PACKAGE System::ResourceString _sdstraInitial;
#define Adexcept_sdstraInitial System::LoadResourceString(&Adexcept::_sdstraInitial)
extern PACKAGE System::ResourceString _sdstraCollectBlock;
#define Adexcept_sdstraCollectBlock System::LoadResourceString(&Adexcept::_sdstraCollectBlock)
extern PACKAGE System::ResourceString _sdstraProcessBlock;
#define Adexcept_sdstraProcessBlock System::LoadResourceString(&Adexcept::_sdstraProcessBlock)
extern PACKAGE System::ResourceString _sdstraFinished;
#define Adexcept_sdstraFinished System::LoadResourceString(&Adexcept::_sdstraFinished)
extern PACKAGE System::ResourceString _sdstraDone;
#define Adexcept_sdstraDone System::LoadResourceString(&Adexcept::_sdstraDone)
extern PACKAGE System::ResourceString _sdstEnable;
#define Adexcept_sdstEnable System::LoadResourceString(&Adexcept::_sdstEnable)
extern PACKAGE System::ResourceString _sdstDisable;
#define Adexcept_sdstDisable System::LoadResourceString(&Adexcept::_sdstDisable)
extern PACKAGE System::ResourceString _sdstStringPacket;
#define Adexcept_sdstStringPacket System::LoadResourceString(&Adexcept::_sdstStringPacket)
extern PACKAGE System::ResourceString _sdstSizePacket;
#define Adexcept_sdstSizePacket System::LoadResourceString(&Adexcept::_sdstSizePacket)
extern PACKAGE System::ResourceString _sdstPacketTimeout;
#define Adexcept_sdstPacketTimeout System::LoadResourceString(&Adexcept::_sdstPacketTimeout)
extern PACKAGE System::ResourceString _sdstStartStr;
#define Adexcept_sdstStartStr System::LoadResourceString(&Adexcept::_sdstStartStr)
extern PACKAGE System::ResourceString _sdstEndStr;
#define Adexcept_sdstEndStr System::LoadResourceString(&Adexcept::_sdstEndStr)
extern PACKAGE System::ResourceString _sdstIdle;
#define Adexcept_sdstIdle System::LoadResourceString(&Adexcept::_sdstIdle)
extern PACKAGE System::ResourceString _sdstWaiting;
#define Adexcept_sdstWaiting System::LoadResourceString(&Adexcept::_sdstWaiting)
extern PACKAGE System::ResourceString _sdstCollecting;
#define Adexcept_sdstCollecting System::LoadResourceString(&Adexcept::_sdstCollecting)
extern PACKAGE System::ResourceString _sdispHeader;
#define Adexcept_sdispHeader System::LoadResourceString(&Adexcept::_sdispHeader)
extern PACKAGE System::ResourceString _sdispHeaderLine;
#define Adexcept_sdispHeaderLine System::LoadResourceString(&Adexcept::_sdispHeaderLine)
extern PACKAGE System::ResourceString _sdispmdmtagDCTS;
#define Adexcept_sdispmdmtagDCTS System::LoadResourceString(&Adexcept::_sdispmdmtagDCTS)
extern PACKAGE System::ResourceString _sdispmdmtagDDSR;
#define Adexcept_sdispmdmtagDDSR System::LoadResourceString(&Adexcept::_sdispmdmtagDDSR)
extern PACKAGE System::ResourceString _sdispmdmtagTERI;
#define Adexcept_sdispmdmtagTERI System::LoadResourceString(&Adexcept::_sdispmdmtagTERI)
extern PACKAGE System::ResourceString _sdispmdmtagDDCD;
#define Adexcept_sdispmdmtagDDCD System::LoadResourceString(&Adexcept::_sdispmdmtagDDCD)
extern PACKAGE System::ResourceString _sdispmdmtagCTS;
#define Adexcept_sdispmdmtagCTS System::LoadResourceString(&Adexcept::_sdispmdmtagCTS)
extern PACKAGE System::ResourceString _sdispmdmtagDSR;
#define Adexcept_sdispmdmtagDSR System::LoadResourceString(&Adexcept::_sdispmdmtagDSR)
extern PACKAGE System::ResourceString _sdispmdmtagRI;
#define Adexcept_sdispmdmtagRI System::LoadResourceString(&Adexcept::_sdispmdmtagRI)
extern PACKAGE System::ResourceString _sdispmdmtagDCD;
#define Adexcept_sdispmdmtagDCD System::LoadResourceString(&Adexcept::_sdispmdmtagDCD)
extern PACKAGE System::ResourceString _sdispTelnetBinary;
#define Adexcept_sdispTelnetBinary System::LoadResourceString(&Adexcept::_sdispTelnetBinary)
extern PACKAGE System::ResourceString _sdispTelnetEcho;
#define Adexcept_sdispTelnetEcho System::LoadResourceString(&Adexcept::_sdispTelnetEcho)
extern PACKAGE System::ResourceString _sdispTelnetReconnection;
#define Adexcept_sdispTelnetReconnection System::LoadResourceString(&Adexcept::_sdispTelnetReconnection)
extern PACKAGE System::ResourceString _sdispTelnetSupressGoAhead;
#define Adexcept_sdispTelnetSupressGoAhead System::LoadResourceString(&Adexcept::_sdispTelnetSupressGoAhead)
extern PACKAGE System::ResourceString _sdispTelnetApproxMsgSize;
#define Adexcept_sdispTelnetApproxMsgSize System::LoadResourceString(&Adexcept::_sdispTelnetApproxMsgSize)
extern PACKAGE System::ResourceString _sdispTelnetStatus;
#define Adexcept_sdispTelnetStatus System::LoadResourceString(&Adexcept::_sdispTelnetStatus)
extern PACKAGE System::ResourceString _sdispTelnetTimingMark;
#define Adexcept_sdispTelnetTimingMark System::LoadResourceString(&Adexcept::_sdispTelnetTimingMark)
extern PACKAGE System::ResourceString _sdispTelnetRemoteTransEcho;
#define Adexcept_sdispTelnetRemoteTransEcho System::LoadResourceString(&Adexcept::_sdispTelnetRemoteTransEcho)
extern PACKAGE System::ResourceString _sdispTelnetOutputLineWidth;
#define Adexcept_sdispTelnetOutputLineWidth System::LoadResourceString(&Adexcept::_sdispTelnetOutputLineWidth)
extern PACKAGE System::ResourceString _sdispTelnetOutputPageSize;
#define Adexcept_sdispTelnetOutputPageSize System::LoadResourceString(&Adexcept::_sdispTelnetOutputPageSize)
extern PACKAGE System::ResourceString _sdispTelnetOutputCRDisp;
#define Adexcept_sdispTelnetOutputCRDisp System::LoadResourceString(&Adexcept::_sdispTelnetOutputCRDisp)
extern PACKAGE System::ResourceString _sdispTelnetOutputHorzTabs;
#define Adexcept_sdispTelnetOutputHorzTabs System::LoadResourceString(&Adexcept::_sdispTelnetOutputHorzTabs)
extern PACKAGE System::ResourceString _sdispTelnetOutputHorzTabDisp;
#define Adexcept_sdispTelnetOutputHorzTabDisp System::LoadResourceString(&Adexcept::_sdispTelnetOutputHorzTabDisp)
extern PACKAGE System::ResourceString _sdispTelnetOutputFFDisp;
#define Adexcept_sdispTelnetOutputFFDisp System::LoadResourceString(&Adexcept::_sdispTelnetOutputFFDisp)
extern PACKAGE System::ResourceString _sdispTelnetOutputVertTabs;
#define Adexcept_sdispTelnetOutputVertTabs System::LoadResourceString(&Adexcept::_sdispTelnetOutputVertTabs)
extern PACKAGE System::ResourceString _sdispTelnetOutputVertTabDisp;
#define Adexcept_sdispTelnetOutputVertTabDisp System::LoadResourceString(&Adexcept::_sdispTelnetOutputVertTabDisp)
extern PACKAGE System::ResourceString _sdispTelnetOutputLinefeedDisp;
#define Adexcept_sdispTelnetOutputLinefeedDisp System::LoadResourceString(&Adexcept::_sdispTelnetOutputLinefeedDisp)
extern PACKAGE System::ResourceString _sdispTelnetExtendedASCII;
#define Adexcept_sdispTelnetExtendedASCII System::LoadResourceString(&Adexcept::_sdispTelnetExtendedASCII)
extern PACKAGE System::ResourceString _sdispTelnetLogout;
#define Adexcept_sdispTelnetLogout System::LoadResourceString(&Adexcept::_sdispTelnetLogout)
extern PACKAGE System::ResourceString _sdispTelnetByteMacro;
#define Adexcept_sdispTelnetByteMacro System::LoadResourceString(&Adexcept::_sdispTelnetByteMacro)
extern PACKAGE System::ResourceString _sdispTelnetDataEntryTerminal;
#define Adexcept_sdispTelnetDataEntryTerminal System::LoadResourceString(&Adexcept::_sdispTelnetDataEntryTerminal)
extern PACKAGE System::ResourceString _sdispTelnetSUPDUP;
#define Adexcept_sdispTelnetSUPDUP System::LoadResourceString(&Adexcept::_sdispTelnetSUPDUP)
extern PACKAGE System::ResourceString _sdispTelnetSUPDUPOutput;
#define Adexcept_sdispTelnetSUPDUPOutput System::LoadResourceString(&Adexcept::_sdispTelnetSUPDUPOutput)
extern PACKAGE System::ResourceString _sdispTelnetSendLocation;
#define Adexcept_sdispTelnetSendLocation System::LoadResourceString(&Adexcept::_sdispTelnetSendLocation)
extern PACKAGE System::ResourceString _sdispTelnetTerminalType;
#define Adexcept_sdispTelnetTerminalType System::LoadResourceString(&Adexcept::_sdispTelnetTerminalType)
extern PACKAGE System::ResourceString _sdispTelnetEndofRecord;
#define Adexcept_sdispTelnetEndofRecord System::LoadResourceString(&Adexcept::_sdispTelnetEndofRecord)
extern PACKAGE System::ResourceString _sdispTelnetTACACSUserID;
#define Adexcept_sdispTelnetTACACSUserID System::LoadResourceString(&Adexcept::_sdispTelnetTACACSUserID)
extern PACKAGE System::ResourceString _sdispTelnetOutputMarking;
#define Adexcept_sdispTelnetOutputMarking System::LoadResourceString(&Adexcept::_sdispTelnetOutputMarking)
extern PACKAGE System::ResourceString _sdispTelnetTerminalLocNum;
#define Adexcept_sdispTelnetTerminalLocNum System::LoadResourceString(&Adexcept::_sdispTelnetTerminalLocNum)
extern PACKAGE System::ResourceString _sdispTelnetTelnet3270Regime;
#define Adexcept_sdispTelnetTelnet3270Regime System::LoadResourceString(&Adexcept::_sdispTelnetTelnet3270Regime)
extern PACKAGE System::ResourceString _sdispTelnetX3PAD;
#define Adexcept_sdispTelnetX3PAD System::LoadResourceString(&Adexcept::_sdispTelnetX3PAD)
extern PACKAGE System::ResourceString _sdispTelnetNegWindowSize;
#define Adexcept_sdispTelnetNegWindowSize System::LoadResourceString(&Adexcept::_sdispTelnetNegWindowSize)
extern PACKAGE System::ResourceString _sdispTelnetTerminalSpeed;
#define Adexcept_sdispTelnetTerminalSpeed System::LoadResourceString(&Adexcept::_sdispTelnetTerminalSpeed)
extern PACKAGE System::ResourceString _sdispTelnetFlowControl;
#define Adexcept_sdispTelnetFlowControl System::LoadResourceString(&Adexcept::_sdispTelnetFlowControl)
extern PACKAGE System::ResourceString _sdispTelnetLineMode;
#define Adexcept_sdispTelnetLineMode System::LoadResourceString(&Adexcept::_sdispTelnetLineMode)
extern PACKAGE System::ResourceString _sdispTelnetXDisplayLocation;
#define Adexcept_sdispTelnetXDisplayLocation System::LoadResourceString(&Adexcept::_sdispTelnetXDisplayLocation)
extern PACKAGE System::ResourceString _sdispTelnetEnvironment;
#define Adexcept_sdispTelnetEnvironment System::LoadResourceString(&Adexcept::_sdispTelnetEnvironment)
extern PACKAGE System::ResourceString _sdispTelnetAuthentication;
#define Adexcept_sdispTelnetAuthentication System::LoadResourceString(&Adexcept::_sdispTelnetAuthentication)
extern PACKAGE System::ResourceString _sdispTelnetTelnetcode38;
#define Adexcept_sdispTelnetTelnetcode38 System::LoadResourceString(&Adexcept::_sdispTelnetTelnetcode38)
extern PACKAGE System::ResourceString _sdispTelnetNewEnvironment;
#define Adexcept_sdispTelnetNewEnvironment System::LoadResourceString(&Adexcept::_sdispTelnetNewEnvironment)
extern PACKAGE System::ResourceString _sdispTelnetTelnetcode40;
#define Adexcept_sdispTelnetTelnetcode40 System::LoadResourceString(&Adexcept::_sdispTelnetTelnetcode40)
extern PACKAGE System::ResourceString _sdispTelnetTelnetcode41;
#define Adexcept_sdispTelnetTelnetcode41 System::LoadResourceString(&Adexcept::_sdispTelnetTelnetcode41)
extern PACKAGE System::ResourceString _sdispTelnetCharacterSet;
#define Adexcept_sdispTelnetCharacterSet System::LoadResourceString(&Adexcept::_sdispTelnetCharacterSet)
extern PACKAGE System::ResourceString _sIENotInstalled;
#define Adexcept_sIENotInstalled System::LoadResourceString(&Adexcept::_sIENotInstalled)
extern PACKAGE System::ResourceString _sOpenFileFailed;
#define Adexcept_sOpenFileFailed System::LoadResourceString(&Adexcept::_sOpenFileFailed)
extern PACKAGE System::ResourceString _sFileNotFound;
#define Adexcept_sFileNotFound System::LoadResourceString(&Adexcept::_sFileNotFound)
extern PACKAGE System::ResourceString _sAllocSrcMemFailed;
#define Adexcept_sAllocSrcMemFailed System::LoadResourceString(&Adexcept::_sAllocSrcMemFailed)
extern PACKAGE System::ResourceString _sHttpReadReqFailed;
#define Adexcept_sHttpReadReqFailed System::LoadResourceString(&Adexcept::_sHttpReadReqFailed)
extern PACKAGE System::ResourceString _sHttpDataNotAvail;
#define Adexcept_sHttpDataNotAvail System::LoadResourceString(&Adexcept::_sHttpDataNotAvail)
extern PACKAGE System::ResourceString _sHttpReqSendFailed;
#define Adexcept_sHttpReqSendFailed System::LoadResourceString(&Adexcept::_sHttpReqSendFailed)
extern PACKAGE System::ResourceString _sHttpReqOpenFailed;
#define Adexcept_sHttpReqOpenFailed System::LoadResourceString(&Adexcept::_sHttpReqOpenFailed)
extern PACKAGE System::ResourceString _sInetConnectFailed;
#define Adexcept_sInetConnectFailed System::LoadResourceString(&Adexcept::_sInetConnectFailed)
extern PACKAGE System::ResourceString _sInetOpenFailed;
#define Adexcept_sInetOpenFailed System::LoadResourceString(&Adexcept::_sInetOpenFailed)
extern PACKAGE System::ResourceString _sInvalidFtpLoc;
#define Adexcept_sInvalidFtpLoc System::LoadResourceString(&Adexcept::_sInvalidFtpLoc)
extern PACKAGE System::ResourceString _sInvalidFtpDir;
#define Adexcept_sInvalidFtpDir System::LoadResourceString(&Adexcept::_sInvalidFtpDir)
extern PACKAGE System::ResourceString _sFtpReadReqFailed;
#define Adexcept_sFtpReadReqFailed System::LoadResourceString(&Adexcept::_sFtpReadReqFailed)
extern PACKAGE System::ResourceString _sFtpDataNotAvail;
#define Adexcept_sFtpDataNotAvail System::LoadResourceString(&Adexcept::_sFtpDataNotAvail)
extern PACKAGE System::ResourceString _sFtpOpenFileFailed;
#define Adexcept_sFtpOpenFileFailed System::LoadResourceString(&Adexcept::_sFtpOpenFileFailed)
extern PACKAGE System::ResourceString _sFtpPutFileFailed;
#define Adexcept_sFtpPutFileFailed System::LoadResourceString(&Adexcept::_sFtpPutFileFailed)
extern PACKAGE System::ResourceString _sSrcLoadFailed;
#define Adexcept_sSrcLoadFailed System::LoadResourceString(&Adexcept::_sSrcLoadFailed)
extern PACKAGE System::ResourceString _sInvalidMemPtr;
#define Adexcept_sInvalidMemPtr System::LoadResourceString(&Adexcept::_sInvalidMemPtr)
extern PACKAGE System::ResourceString _sFmtErrorMsg;
#define Adexcept_sFmtErrorMsg System::LoadResourceString(&Adexcept::_sFmtErrorMsg)
extern PACKAGE System::ResourceString _sIndexOutOfBounds;
#define Adexcept_sIndexOutOfBounds System::LoadResourceString(&Adexcept::_sIndexOutOfBounds)
extern PACKAGE System::ResourceString _sExpMarkupDecl;
#define Adexcept_sExpMarkupDecl System::LoadResourceString(&Adexcept::_sExpMarkupDecl)
extern PACKAGE System::ResourceString _sIllAttrType;
#define Adexcept_sIllAttrType System::LoadResourceString(&Adexcept::_sIllAttrType)
extern PACKAGE System::ResourceString _sIllAttrDefKeyw;
#define Adexcept_sIllAttrDefKeyw System::LoadResourceString(&Adexcept::_sIllAttrDefKeyw)
extern PACKAGE System::ResourceString _sSysIdMissing;
#define Adexcept_sSysIdMissing System::LoadResourceString(&Adexcept::_sSysIdMissing)
extern PACKAGE System::ResourceString _sExtModifMissing;
#define Adexcept_sExtModifMissing System::LoadResourceString(&Adexcept::_sExtModifMissing)
extern PACKAGE System::ResourceString _sIllCondSectStart;
#define Adexcept_sIllCondSectStart System::LoadResourceString(&Adexcept::_sIllCondSectStart)
extern PACKAGE System::ResourceString _sBadSepInModel;
#define Adexcept_sBadSepInModel System::LoadResourceString(&Adexcept::_sBadSepInModel)
extern PACKAGE System::ResourceString _sExpCommentOrCDATA;
#define Adexcept_sExpCommentOrCDATA System::LoadResourceString(&Adexcept::_sExpCommentOrCDATA)
extern PACKAGE System::ResourceString _sUnexpectedEof;
#define Adexcept_sUnexpectedEof System::LoadResourceString(&Adexcept::_sUnexpectedEof)
extern PACKAGE System::ResourceString _sMismatchEndTag;
#define Adexcept_sMismatchEndTag System::LoadResourceString(&Adexcept::_sMismatchEndTag)
extern PACKAGE System::ResourceString _sIllCharInRef;
#define Adexcept_sIllCharInRef System::LoadResourceString(&Adexcept::_sIllCharInRef)
extern PACKAGE System::ResourceString _sUndeclaredEntity;
#define Adexcept_sUndeclaredEntity System::LoadResourceString(&Adexcept::_sUndeclaredEntity)
extern PACKAGE System::ResourceString _sExpectedString;
#define Adexcept_sExpectedString System::LoadResourceString(&Adexcept::_sExpectedString)
extern PACKAGE System::ResourceString _sSpaceExpectedAt;
#define Adexcept_sSpaceExpectedAt System::LoadResourceString(&Adexcept::_sSpaceExpectedAt)
extern PACKAGE System::ResourceString _sUnexpEndOfInput;
#define Adexcept_sUnexpEndOfInput System::LoadResourceString(&Adexcept::_sUnexpEndOfInput)
extern PACKAGE System::ResourceString _sQuoteExpected;
#define Adexcept_sQuoteExpected System::LoadResourceString(&Adexcept::_sQuoteExpected)
extern PACKAGE System::ResourceString _sInvalidXMLVersion;
#define Adexcept_sInvalidXMLVersion System::LoadResourceString(&Adexcept::_sInvalidXMLVersion)
extern PACKAGE System::ResourceString _sUnableCreateStr;
#define Adexcept_sUnableCreateStr System::LoadResourceString(&Adexcept::_sUnableCreateStr)
extern PACKAGE System::ResourceString _sInvalidName;
#define Adexcept_sInvalidName System::LoadResourceString(&Adexcept::_sInvalidName)
extern PACKAGE System::ResourceString _sInvalidCommentText;
#define Adexcept_sInvalidCommentText System::LoadResourceString(&Adexcept::_sInvalidCommentText)
extern PACKAGE System::ResourceString _sCommentBeforeXMLDecl;
#define Adexcept_sCommentBeforeXMLDecl System::LoadResourceString(&Adexcept::_sCommentBeforeXMLDecl)
extern PACKAGE System::ResourceString _sInvalidCDataSection;
#define Adexcept_sInvalidCDataSection System::LoadResourceString(&Adexcept::_sInvalidCDataSection)
extern PACKAGE System::ResourceString _sRedefinedAttr;
#define Adexcept_sRedefinedAttr System::LoadResourceString(&Adexcept::_sRedefinedAttr)
extern PACKAGE System::ResourceString _sCircularEntRef;
#define Adexcept_sCircularEntRef System::LoadResourceString(&Adexcept::_sCircularEntRef)
extern PACKAGE System::ResourceString _sInvAttrChar;
#define Adexcept_sInvAttrChar System::LoadResourceString(&Adexcept::_sInvAttrChar)
extern PACKAGE System::ResourceString _sInvPCData;
#define Adexcept_sInvPCData System::LoadResourceString(&Adexcept::_sInvPCData)
extern PACKAGE System::ResourceString _sDataAfterValDoc;
#define Adexcept_sDataAfterValDoc System::LoadResourceString(&Adexcept::_sDataAfterValDoc)
extern PACKAGE System::ResourceString _sNoIntConditional;
#define Adexcept_sNoIntConditional System::LoadResourceString(&Adexcept::_sNoIntConditional)
extern PACKAGE System::ResourceString _sNotationNotDeclared;
#define Adexcept_sNotationNotDeclared System::LoadResourceString(&Adexcept::_sNotationNotDeclared)
extern PACKAGE System::ResourceString _sInvPubIDChar;
#define Adexcept_sInvPubIDChar System::LoadResourceString(&Adexcept::_sInvPubIDChar)
extern PACKAGE System::ResourceString _sNoNDATAInPeDecl;
#define Adexcept_sNoNDATAInPeDecl System::LoadResourceString(&Adexcept::_sNoNDATAInPeDecl)
extern PACKAGE System::ResourceString _sInvStandAloneVal;
#define Adexcept_sInvStandAloneVal System::LoadResourceString(&Adexcept::_sInvStandAloneVal)
extern PACKAGE System::ResourceString _sInvEncName;
#define Adexcept_sInvEncName System::LoadResourceString(&Adexcept::_sInvEncName)
extern PACKAGE System::ResourceString _sInvVerNum;
#define Adexcept_sInvVerNum System::LoadResourceString(&Adexcept::_sInvVerNum)
extern PACKAGE System::ResourceString _sInvEntityValue;
#define Adexcept_sInvEntityValue System::LoadResourceString(&Adexcept::_sInvEntityValue)
extern PACKAGE System::ResourceString _sNoCommentInMarkup;
#define Adexcept_sNoCommentInMarkup System::LoadResourceString(&Adexcept::_sNoCommentInMarkup)
extern PACKAGE System::ResourceString _sNoPEInIntDTD;
#define Adexcept_sNoPEInIntDTD System::LoadResourceString(&Adexcept::_sNoPEInIntDTD)
extern PACKAGE System::ResourceString _sXMLDecNotAtBeg;
#define Adexcept_sXMLDecNotAtBeg System::LoadResourceString(&Adexcept::_sXMLDecNotAtBeg)
extern PACKAGE System::ResourceString _sInvalidElementName;
#define Adexcept_sInvalidElementName System::LoadResourceString(&Adexcept::_sInvalidElementName)
extern PACKAGE System::ResourceString _sBadParamEntNesting;
#define Adexcept_sBadParamEntNesting System::LoadResourceString(&Adexcept::_sBadParamEntNesting)
extern PACKAGE System::ResourceString _sInvalidCharEncoding;
#define Adexcept_sInvalidCharEncoding System::LoadResourceString(&Adexcept::_sInvalidCharEncoding)
extern PACKAGE System::ResourceString _sAttrNotNum;
#define Adexcept_sAttrNotNum System::LoadResourceString(&Adexcept::_sAttrNotNum)
extern PACKAGE System::ResourceString _sUnknownAxis;
#define Adexcept_sUnknownAxis System::LoadResourceString(&Adexcept::_sUnknownAxis)
extern PACKAGE System::ResourceString _sInvalidXMLChar;
#define Adexcept_sInvalidXMLChar System::LoadResourceString(&Adexcept::_sInvalidXMLChar)
extern PACKAGE System::ResourceString _sInvalidBEChar;
#define Adexcept_sInvalidBEChar System::LoadResourceString(&Adexcept::_sInvalidBEChar)
extern PACKAGE System::ResourceString _sInvalidLEChar;
#define Adexcept_sInvalidLEChar System::LoadResourceString(&Adexcept::_sInvalidLEChar)
extern PACKAGE System::ResourceString _sBadUTF8Char;
#define Adexcept_sBadUTF8Char System::LoadResourceString(&Adexcept::_sBadUTF8Char)
extern PACKAGE System::ResourceString _sErrEndOfDocument;
#define Adexcept_sErrEndOfDocument System::LoadResourceString(&Adexcept::_sErrEndOfDocument)
extern PACKAGE System::ResourceString _sUCS_ISOConvertErr;
#define Adexcept_sUCS_ISOConvertErr System::LoadResourceString(&Adexcept::_sUCS_ISOConvertErr)
extern PACKAGE System::ResourceString _sUCS_U16ConvertErr;
#define Adexcept_sUCS_U16ConvertErr System::LoadResourceString(&Adexcept::_sUCS_U16ConvertErr)
extern PACKAGE System::ResourceString _sUCS_U8ConverErr;
#define Adexcept_sUCS_U8ConverErr System::LoadResourceString(&Adexcept::_sUCS_U8ConverErr)
extern PACKAGE System::ResourceString _sModemDetectedBusy;
#define Adexcept_sModemDetectedBusy System::LoadResourceString(&Adexcept::_sModemDetectedBusy)
extern PACKAGE System::ResourceString _sModemNoDialtone;
#define Adexcept_sModemNoDialtone System::LoadResourceString(&Adexcept::_sModemNoDialtone)
extern PACKAGE System::ResourceString _sModemNoCarrier;
#define Adexcept_sModemNoCarrier System::LoadResourceString(&Adexcept::_sModemNoCarrier)
extern PACKAGE System::ResourceString _sInitFail;
#define Adexcept_sInitFail System::LoadResourceString(&Adexcept::_sInitFail)
extern PACKAGE System::ResourceString _sLoginFail;
#define Adexcept_sLoginFail System::LoadResourceString(&Adexcept::_sLoginFail)
extern PACKAGE System::ResourceString _sMinorSrvErr;
#define Adexcept_sMinorSrvErr System::LoadResourceString(&Adexcept::_sMinorSrvErr)
extern PACKAGE System::ResourceString _sFatalSrvErr;
#define Adexcept_sFatalSrvErr System::LoadResourceString(&Adexcept::_sFatalSrvErr)
extern PACKAGE System::ResourceString _sConnected;
#define Adexcept_sConnected System::LoadResourceString(&Adexcept::_sConnected)
extern PACKAGE System::ResourceString _sCancelled;
#define Adexcept_sCancelled System::LoadResourceString(&Adexcept::_sCancelled)
extern PACKAGE System::ResourceString _sLineBusy;
#define Adexcept_sLineBusy System::LoadResourceString(&Adexcept::_sLineBusy)
extern PACKAGE System::ResourceString _sDisconnect;
#define Adexcept_sDisconnect System::LoadResourceString(&Adexcept::_sDisconnect)
extern PACKAGE System::ResourceString _sNoDialtone;
#define Adexcept_sNoDialtone System::LoadResourceString(&Adexcept::_sNoDialtone)
extern PACKAGE System::ResourceString _sMsgNotSent;
#define Adexcept_sMsgNotSent System::LoadResourceString(&Adexcept::_sMsgNotSent)
extern PACKAGE System::ResourceString _sWaitingToRedial;
#define Adexcept_sWaitingToRedial System::LoadResourceString(&Adexcept::_sWaitingToRedial)
extern PACKAGE System::ResourceString _sLoginPrompt;
#define Adexcept_sLoginPrompt System::LoadResourceString(&Adexcept::_sLoginPrompt)
extern PACKAGE System::ResourceString _sLoggedIn;
#define Adexcept_sLoggedIn System::LoadResourceString(&Adexcept::_sLoggedIn)
extern PACKAGE System::ResourceString _sDialing;
#define Adexcept_sDialing System::LoadResourceString(&Adexcept::_sDialing)
extern PACKAGE System::ResourceString _sRedialing;
#define Adexcept_sRedialing System::LoadResourceString(&Adexcept::_sRedialing)
extern PACKAGE System::ResourceString _sLoginRetry;
#define Adexcept_sLoginRetry System::LoadResourceString(&Adexcept::_sLoginRetry)
extern PACKAGE System::ResourceString _sMsgOkToSend;
#define Adexcept_sMsgOkToSend System::LoadResourceString(&Adexcept::_sMsgOkToSend)
extern PACKAGE System::ResourceString _sSendingMsg;
#define Adexcept_sSendingMsg System::LoadResourceString(&Adexcept::_sSendingMsg)
extern PACKAGE System::ResourceString _sMsgAck;
#define Adexcept_sMsgAck System::LoadResourceString(&Adexcept::_sMsgAck)
extern PACKAGE System::ResourceString _sMsgNak;
#define Adexcept_sMsgNak System::LoadResourceString(&Adexcept::_sMsgNak)
extern PACKAGE System::ResourceString _sMsgRs;
#define Adexcept_sMsgRs System::LoadResourceString(&Adexcept::_sMsgRs)
extern PACKAGE System::ResourceString _sMsgCompleted;
#define Adexcept_sMsgCompleted System::LoadResourceString(&Adexcept::_sMsgCompleted)
extern PACKAGE System::ResourceString _sSendTimedOut;
#define Adexcept_sSendTimedOut System::LoadResourceString(&Adexcept::_sSendTimedOut)
extern PACKAGE System::ResourceString _sLoggingOut;
#define Adexcept_sLoggingOut System::LoadResourceString(&Adexcept::_sLoggingOut)
extern PACKAGE System::ResourceString _sDone;
#define Adexcept_sDone System::LoadResourceString(&Adexcept::_sDone)
extern PACKAGE System::ResourceString _sVoIPNotAvailable;
#define Adexcept_sVoIPNotAvailable System::LoadResourceString(&Adexcept::_sVoIPNotAvailable)
extern PACKAGE System::ResourceString _slfaxNone;
#define Adexcept_slfaxNone System::LoadResourceString(&Adexcept::_slfaxNone)
extern PACKAGE System::ResourceString _slfaxTransmitStart;
#define Adexcept_slfaxTransmitStart System::LoadResourceString(&Adexcept::_slfaxTransmitStart)
extern PACKAGE System::ResourceString _slfaxTransmitOk;
#define Adexcept_slfaxTransmitOk System::LoadResourceString(&Adexcept::_slfaxTransmitOk)
extern PACKAGE System::ResourceString _slfaxTransmitFail;
#define Adexcept_slfaxTransmitFail System::LoadResourceString(&Adexcept::_slfaxTransmitFail)
extern PACKAGE System::ResourceString _slfaxReceiveStart;
#define Adexcept_slfaxReceiveStart System::LoadResourceString(&Adexcept::_slfaxReceiveStart)
extern PACKAGE System::ResourceString _slfaxReceiveOk;
#define Adexcept_slfaxReceiveOk System::LoadResourceString(&Adexcept::_slfaxReceiveOk)
extern PACKAGE System::ResourceString _slfaxReceiveSkip;
#define Adexcept_slfaxReceiveSkip System::LoadResourceString(&Adexcept::_slfaxReceiveSkip)
extern PACKAGE System::ResourceString _slfaxReceiveFail;
#define Adexcept_slfaxReceiveFail System::LoadResourceString(&Adexcept::_slfaxReceiveFail)
extern PACKAGE char * __fastcall AproLoadZ(char * P, int Code);
extern PACKAGE System::ShortString __fastcall AproLoadStr(const short ErrorCode);
extern PACKAGE System::ShortString __fastcall ErrorMsg(const short ErrorCode);
extern PACKAGE System::ShortString __fastcall MessageNumberToString(short MessageNumber);
extern PACKAGE int __fastcall CheckException(const Classes::TComponent* Ctl, const int Res);
extern PACKAGE int __fastcall XlatException(const Sysutils::Exception* E);

}	/* namespace Adexcept */
using namespace Adexcept;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdExcept
