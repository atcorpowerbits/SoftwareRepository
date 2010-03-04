// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStatEd.pas' rev: 5.00

#ifndef AdStatEdHPP
#define AdStatEdHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <AdStMach.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Grids.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adstated
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TApdStringGrid;
class PASCALIMPLEMENTATION TApdStringGrid : public Grids::TStringGrid 
{
	typedef Grids::TStringGrid inherited;
	
public:
	virtual void __fastcall DrawCell(int ACol, int ARow, const Windows::TRect &ARect, Grids::TGridDrawState 
		AState);
public:
	#pragma option push -w-inl
	/* TStringGrid.Create */ inline __fastcall virtual TApdStringGrid(Classes::TComponent* AOwner) : Grids::TStringGrid(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TStringGrid.Destroy */ inline __fastcall virtual ~TApdStringGrid(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdStringGrid(HWND ParentWindow) : Grids::TStringGrid(
		ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TfrmStateEdit;
class PASCALIMPLEMENTATION TfrmStateEdit : public Forms::TForm 
{
	typedef Forms::TForm inherited;
	
__published:
	Stdctrls::TGroupBox* GroupBox2;
	Stdctrls::TButton* btnAdd;
	Stdctrls::TButton* btnEdit;
	Stdctrls::TButton* btnDelete;
	Stdctrls::TButton* btnOK;
	Stdctrls::TButton* btnCancel;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall btnAddClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall ConditionGridSelectCell(System::TObject* Sender, int ACol, int ARow, bool &CanSelect
		);
	void __fastcall btnEditClick(System::TObject* Sender);
	void __fastcall btnDeleteClick(System::TObject* Sender);
	void __fastcall FormResize(System::TObject* Sender);
	
private:
	TApdStringGrid* ConditionGrid;
	Adstmach::TApdCustomStateMachine* FStateMachine;
	void __fastcall SetStateMachine(const Adstmach::TApdCustomStateMachine* Value);
	
public:
	Classes::TStringList* Conditions;
	Classes::TStringList* AvailableStates;
	__property Adstmach::TApdCustomStateMachine* StateMachine = {read=FStateMachine, write=SetStateMachine
		};
public:
	#pragma option push -w-inl
	/* TCustomForm.Create */ inline __fastcall virtual TfrmStateEdit(Classes::TComponent* AOwner) : Forms::TForm(
		AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmStateEdit(Classes::TComponent* AOwner, int 
		Dummy) : Forms::TForm(AOwner, Dummy) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmStateEdit(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TfrmStateEdit(HWND ParentWindow) : Forms::TForm(
		ParentWindow) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TfrmStateEdit* frmStateEdit;
extern PACKAGE bool __fastcall EditState(Adstmach::TApdCustomState* State, const AnsiString Name);

}	/* namespace Adstated */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Adstated;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStatEd
