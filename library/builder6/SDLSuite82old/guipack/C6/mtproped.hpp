// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'mtproped.pas' rev: 6.00

#ifndef mtpropedHPP
#define mtpropedHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <DesignIntf.hpp>	// Pascal unit
#include <DesignEditors.hpp>	// Pascal unit
#include <Buttons.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <meter.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Mtproped
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TFDFileNameProperty;
class PASCALIMPLEMENTATION TFDFileNameProperty : public Designeditors::TStringProperty 
{
	typedef Designeditors::TStringProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual Designintf::TPropertyAttributes __fastcall GetAttributes(void);
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TFDFileNameProperty(const Designintf::_di_IDesigner ADesigner, int APropCount) : Designeditors::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TFDFileNameProperty(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Mtproped */
using namespace Mtproped;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// mtproped
