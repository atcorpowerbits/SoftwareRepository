// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'cpuid.pas' rev: 6.00

#ifndef cpuidHPP
#define cpuidHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <sdlbase.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cpuid
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS ESDLCpuIdError;
class PASCALIMPLEMENTATION ESDLCpuIdError : public Sdlbase::ESDLError 
{
	typedef Sdlbase::ESDLError inherited;
	
public:
	#pragma option push -w-inl
	/* Exception.Create */ inline __fastcall ESDLCpuIdError(const AnsiString Msg) : Sdlbase::ESDLError(Msg) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmt */ inline __fastcall ESDLCpuIdError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size) : Sdlbase::ESDLError(Msg, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateRes */ inline __fastcall ESDLCpuIdError(int Ident)/* overload */ : Sdlbase::ESDLError(Ident) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmt */ inline __fastcall ESDLCpuIdError(int Ident, const System::TVarRec * Args, const int Args_Size)/* overload */ : Sdlbase::ESDLError(Ident, Args, Args_Size) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateHelp */ inline __fastcall ESDLCpuIdError(const AnsiString Msg, int AHelpContext) : Sdlbase::ESDLError(Msg, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateFmtHelp */ inline __fastcall ESDLCpuIdError(const AnsiString Msg, const System::TVarRec * Args, const int Args_Size, int AHelpContext) : Sdlbase::ESDLError(Msg, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResHelp */ inline __fastcall ESDLCpuIdError(int Ident, int AHelpContext)/* overload */ : Sdlbase::ESDLError(Ident, AHelpContext) { }
	#pragma option pop
	#pragma option push -w-inl
	/* Exception.CreateResFmtHelp */ inline __fastcall ESDLCpuIdError(System::PResStringRec ResStringRec, const System::TVarRec * Args, const int Args_Size, int AHelpContext)/* overload */ : Sdlbase::ESDLError(ResStringRec, Args, Args_Size, AHelpContext) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~ESDLCpuIdError(void) { }
	#pragma option pop
	
};


#pragma option push -b-
enum TCPUFeatures { cpuft_fpu, cpuft_vme, cpuft_de, cpuft_pse, cpuft_tsc, cpuft_msr, cpuft_pae, cpuft_mce, cpuft_cx8, cpuft_apic, cpuft_sepamd, cpuft_sep, cpuft_mtrr, cpuft_pge, cpuft_mca, cpuft_cmov, cpuft_pat, cpuft_pse36, cpuft_serial, cpuft_clflush, cpuft_reserved1, cpuft_dts, cpuft_acpi, cpuft_mmx, cpuft_xsr, cpuft_simd, cpuft_simd2, cpuft_ss, cpuft_reserved2, cpuft_tm, cpuft_ia64, cpuft_3dnow };
#pragma option pop

typedef AnsiString cpuid__2[32];

//-- var, const, procedure ---------------------------------------------------
#define SDLVersionInfo "cpuid_r820_full"
static const bool IsLightEd = false;
static const Word Release = 0x334;
extern PACKAGE AnsiString CPUFeatureNames[32];
extern PACKAGE AnsiString __fastcall GenerateCPUID();
extern PACKAGE bool __fastcall CheckGeneratedCPUID(AnsiString CPUId);
extern PACKAGE int __fastcall CPU_Count(void);
extern PACKAGE bool __fastcall CPU_IDSupport(void);
extern PACKAGE AnsiString __fastcall CPU_VendorString();
extern PACKAGE int __fastcall CPU_Signature(void);
extern PACKAGE int __fastcall CPU_FeatureSet(void);
extern PACKAGE int __fastcall CPU_ExtendedFeatureSet(void);
extern PACKAGE int __fastcall CPU_BrandID(void);
extern PACKAGE int __fastcall CPU_Type(void);
extern PACKAGE bool __fastcall CPU_OverDrive(void);
extern PACKAGE int __fastcall CPU_Family(void);
extern PACKAGE int __fastcall CPU_ExFamily(void);
extern PACKAGE int __fastcall CPU_Model(void);
extern PACKAGE int __fastcall CPU_ExModel(void);
extern PACKAGE int __fastcall CPU_Stepping(void);
extern PACKAGE bool __fastcall CPU_FDIVBugPresent(void);
extern PACKAGE AnsiString __fastcall CPU_SerialNumber();
extern PACKAGE AnsiString __fastcall CPU_MarketName();
extern PACKAGE float __fastcall CPU_Speed(unsigned ADelay);

}	/* namespace Cpuid */
using namespace Cpuid;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// cpuid
