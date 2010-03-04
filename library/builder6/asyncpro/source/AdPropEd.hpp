// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Adproped.pas' rev: 5.00

#ifndef AdpropedHPP
#define AdpropedHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdAbout.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <DsgnIntf.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adproped
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdPacketStringProperty;
class PASCALIMPLEMENTATION TApdPacketStringProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual AnsiString __fastcall GetValue(void);
	virtual void __fastcall SetValue(const AnsiString Value);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdPacketStringProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdPacketStringProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdPacketEditor;
class PASCALIMPLEMENTATION TApdPacketEditor : public Dsgnintf::TDefaultEditor 
{
	typedef Dsgnintf::TDefaultEditor inherited;
	
public:
	virtual void __fastcall ExecuteVerb(int Index);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TApdPacketEditor(Classes::TComponent* AComponent
		, Dsgnintf::_di_IFormDesigner ADesigner) : Dsgnintf::TDefaultEditor(AComponent, ADesigner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdPacketEditor(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdVoipAudioVideoEditor;
class PASCALIMPLEMENTATION TApdVoipAudioVideoEditor : public Dsgnintf::TDefaultEditor 
{
	typedef Dsgnintf::TDefaultEditor inherited;
	
public:
	virtual void __fastcall ExecuteVerb(int Index);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TApdVoipAudioVideoEditor(Classes::TComponent* 
		AComponent, Dsgnintf::_di_IFormDesigner ADesigner) : Dsgnintf::TDefaultEditor(AComponent, ADesigner
		) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdVoipAudioVideoEditor(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdVersionProperty;
class PASCALIMPLEMENTATION TApdVersionProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall Edit(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdVersionProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdVersionProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdValidEnumProperty;
class PASCALIMPLEMENTATION TApdValidEnumProperty : public Dsgnintf::TEnumProperty 
{
	typedef Dsgnintf::TEnumProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdValidEnumProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TEnumProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdValidEnumProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdStateEditor;
class PASCALIMPLEMENTATION TApdStateEditor : public Dsgnintf::TDefaultEditor 
{
	typedef Dsgnintf::TDefaultEditor inherited;
	
public:
	virtual void __fastcall ExecuteVerb(int Index);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TApdStateEditor(Classes::TComponent* AComponent
		, Dsgnintf::_di_IFormDesigner ADesigner) : Dsgnintf::TDefaultEditor(AComponent, ADesigner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TApdStateEditor(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdGenericFileNameProperty;
class PASCALIMPLEMENTATION TApdGenericFileNameProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall Edit(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdGenericFileNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdGenericFileNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdAPFFileNameProperty;
class PASCALIMPLEMENTATION TApdAPFFileNameProperty : public TApdGenericFileNameProperty 
{
	typedef TApdGenericFileNameProperty inherited;
	
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdAPFFileNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : TApdGenericFileNameProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdAPFFileNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdConverterNameProperty;
class PASCALIMPLEMENTATION TApdConverterNameProperty : public TApdGenericFileNameProperty 
{
	typedef TApdGenericFileNameProperty inherited;
	
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdConverterNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : TApdGenericFileNameProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdConverterNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdLogNameProperty;
class PASCALIMPLEMENTATION TApdLogNameProperty : public TApdGenericFileNameProperty 
{
	typedef TApdGenericFileNameProperty inherited;
	
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdLogNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : TApdGenericFileNameProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdLogNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdTraceNameProperty;
class PASCALIMPLEMENTATION TApdTraceNameProperty : public TApdGenericFileNameProperty 
{
	typedef TApdGenericFileNameProperty inherited;
	
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdTraceNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : TApdGenericFileNameProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdTraceNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdHistoryNameProperty;
class PASCALIMPLEMENTATION TApdHistoryNameProperty : public TApdGenericFileNameProperty 
{
	typedef TApdGenericFileNameProperty inherited;
	
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdHistoryNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : TApdGenericFileNameProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdHistoryNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdCaptureNameProperty;
class PASCALIMPLEMENTATION TApdCaptureNameProperty : public TApdGenericFileNameProperty 
{
	typedef TApdGenericFileNameProperty inherited;
	
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdCaptureNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : TApdGenericFileNameProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdCaptureNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdAPJNameProperty;
class PASCALIMPLEMENTATION TApdAPJNameProperty : public TApdGenericFileNameProperty 
{
	typedef TApdGenericFileNameProperty inherited;
	
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdAPJNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : TApdGenericFileNameProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdAPJNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdFaxCoverNameProperty;
class PASCALIMPLEMENTATION TApdFaxCoverNameProperty : public TApdGenericFileNameProperty 
{
	typedef TApdGenericFileNameProperty inherited;
	
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdFaxCoverNameProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : TApdGenericFileNameProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdFaxCoverNameProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdDirectoryProperty;
class PASCALIMPLEMENTATION TApdDirectoryProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall Edit(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdDirectoryProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdDirectoryProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TApdVoipAudioVideoProperty;
class PASCALIMPLEMENTATION TApdVoipAudioVideoProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall Edit(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TApdVoipAudioVideoProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TApdVoipAudioVideoProperty(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Adproped */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adproped;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Adproped
