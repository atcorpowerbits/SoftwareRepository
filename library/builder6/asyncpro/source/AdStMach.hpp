// Borland C++ Builder
// Copyright (c) 1995, 2002 by Borland Software Corporation
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdStMach.pas' rev: 6.00

#ifndef AdStMachHPP
#define AdStMachHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <TypInfo.hpp>	// Pascal unit
#include <AdStrMap.hpp>	// Pascal unit
#include <AdExcept.hpp>	// Pascal unit
#include <AdPort.hpp>	// Pascal unit
#include <AdPacket.hpp>	// Pascal unit
#include <OoMisc.hpp>	// Pascal unit
#include <StdCtrls.hpp>	// Pascal unit
#include <Dialogs.hpp>	// Pascal unit
#include <Forms.hpp>	// Pascal unit
#include <Graphics.hpp>	// Pascal unit
#include <ExtCtrls.hpp>	// Pascal unit
#include <Controls.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <SysUtils.hpp>	// Pascal unit
#include <Messages.hpp>	// Pascal unit
#include <Windows.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Adstmach
{
//-- type declarations -------------------------------------------------------
#pragma option push -b-
enum TApdConnectAddType { atAdd, atSub, atNone };
#pragma option pop

#pragma option push -b-
enum TAdConnectoidClickStyle { ccsHighlight, ccsHint, ccsDashedLine };
#pragma option pop

typedef Set<TAdConnectoidClickStyle, ccsHighlight, ccsDashedLine>  TAdConnectoidClickStyles;

class DELPHICLASS TApdStateConnectoid;
typedef void __fastcall (__closure *TApdOnConnectoidClickEvent)(System::TObject* Sender, TApdStateConnectoid* Connectoid);

typedef void __fastcall (__closure *TApdOnDataSourceGetData)(System::TObject* Sender, void * Data, int DataSize);

typedef void __fastcall (__closure *TApdOnDataSourceGetDataString)(System::TObject* Sender, AnsiString DataString);

typedef void __fastcall (__closure *TApdOnStateGetData)(System::TObject* Sender, void * Data, int DataSize);

typedef void __fastcall (__closure *TApdOnStateGetDataString)(System::TObject* Sender, AnsiString DataString);

class DELPHICLASS TApdStateCustomDataSource;
class DELPHICLASS TApdCustomStateMachine;
class DELPHICLASS TApdCustomState;
class DELPHICLASS TApdStateConditions;
class DELPHICLASS TApdStateCondition;
class PASCALIMPLEMENTATION TApdStateConditions : public Classes::TCollection 
{
	typedef Classes::TCollection inherited;
	
public:
	TApdStateCondition* operator[](int Index) { return Items[Index]; }
	
private:
	HIDESBASE TApdStateCondition* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, const TApdStateCondition* Value);
	
protected:
	TApdCustomState* FState;
	DYNAMIC Classes::TPersistent* __fastcall GetOwner(void);
	
public:
	__fastcall TApdStateConditions(TApdCustomState* State, TMetaClass* ItemClass);
	virtual void __fastcall Update(Classes::TCollectionItem* Item);
	HIDESBASE TApdStateCondition* __fastcall Add(void);
	__property TApdStateCondition* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	#pragma option push -w-inl
	/* TCollection.Destroy */ inline __fastcall virtual ~TApdStateConditions(void) { }
	#pragma option pop
	
};


typedef void __fastcall (__closure *TApdStateNotifyEvent)(TApdCustomState* State);

typedef void __fastcall (__closure *TApdStateFinishEvent)(TApdCustomState* State, TApdStateCondition* Condition, TApdCustomState* &NextState);

class PASCALIMPLEMENTATION TApdCustomState : public Oomisc::TApdBaseGraphicControl 
{
	typedef Oomisc::TApdBaseGraphicControl inherited;
	
private:
	bool FActive;
	bool FCompleted;
	Graphics::TBitmap* FGlyph;
	AnsiString FOutputOnActivate;
	TApdStateConditions* FConditions;
	int FGlyphCells;
	Graphics::TColor FActiveColor;
	Graphics::TColor FInactiveColor;
	TApdStateNotifyEvent FOnStateActivate;
	TApdStateFinishEvent FOnStateFinish;
	AnsiString FCaption;
	bool FMovable;
	int FOldX;
	int FOldY;
	bool FMoving;
	bool FActionState;
	TApdOnStateGetData FOnGetData;
	TApdOnStateGetDataString FOnGetDataString;
	void __fastcall SetActiveColor(const Graphics::TColor NewColor);
	void __fastcall SetActionState(const bool v);
	void __fastcall SetInactiveColor(const Graphics::TColor NewColor);
	void __fastcall SetConditions(const TApdStateConditions* Value);
	void __fastcall SetGlyph(const Graphics::TBitmap* Value);
	void __fastcall SetGlyphCells(const int Value);
	void __fastcall SetCaption(const AnsiString Value);
	void __fastcall SetMovable(const bool v);
	
protected:
	bool HaveGlyph;
	TApdCustomStateMachine* FStateMachine;
	bool FUseLeftBorder;
	int FLeftBorderWidth;
	Graphics::TColor FLeftBorderFill;
	virtual void __fastcall Activate(void);
	virtual void __fastcall Deactivate(void);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	virtual void __fastcall SetParent(Controls::TWinControl* AParent);
	TApdCustomStateMachine* __fastcall FindStateMachine(void);
	void __fastcall WMEraseBackground(Messages::TWMEraseBkgnd &Msg);
	__property bool ActionState = {read=FActionState, write=SetActionState, nodefault};
	__property TApdOnStateGetData OnGetData = {read=FOnGetData, write=FOnGetData};
	__property TApdOnStateGetDataString OnGetDataString = {read=FOnGetDataString, write=FOnGetDataString};
	
public:
	__fastcall virtual TApdCustomState(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomState(void);
	int __fastcall FindDefaultError(void);
	int __fastcall FindDefaultNext(void);
	virtual void __fastcall Loaded(void);
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	virtual void __fastcall Paint(void);
	virtual void __fastcall Terminate(int ErrorCode);
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
	__property bool Active = {read=FActive, nodefault};
	__property bool Completed = {read=FCompleted, nodefault};
	__property Graphics::TColor ActiveColor = {read=FActiveColor, write=SetActiveColor, nodefault};
	__property Graphics::TColor InactiveColor = {read=FInactiveColor, write=SetInactiveColor, nodefault};
	__property TApdStateConditions* Conditions = {read=FConditions, write=SetConditions};
	__property Graphics::TBitmap* Glyph = {read=FGlyph, write=SetGlyph};
	__property int GlyphCells = {read=FGlyphCells, write=SetGlyphCells, nodefault};
	__property bool Movable = {read=FMovable, write=SetMovable, default=0};
	__property AnsiString OutputOnActivate = {read=FOutputOnActivate, write=FOutputOnActivate};
	__property TApdStateNotifyEvent OnStateActivate = {read=FOnStateActivate, write=FOnStateActivate};
	__property TApdStateFinishEvent OnStateFinish = {read=FOnStateFinish, write=FOnStateFinish};
};


class DELPHICLASS TApdStateComPortSource;
class PASCALIMPLEMENTATION TApdStateCustomDataSource : public Oomisc::TApdBaseComponent 
{
	typedef Oomisc::TApdBaseComponent inherited;
	
private:
	TApdCustomStateMachine* FStateMachine;
	int FPauseDepth;
	TApdOnDataSourceGetData FOnGetData;
	TApdOnDataSourceGetDataString FOnGetDataString;
	
protected:
	bool __fastcall GetPaused(void);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	TApdCustomStateMachine* __fastcall SearchStateMachine(const Classes::TComponent* C);
	__property TApdCustomStateMachine* StateMachine = {read=FStateMachine};
	__property TApdOnDataSourceGetData OnGetData = {read=FOnGetData, write=FOnGetData};
	__property TApdOnDataSourceGetDataString OnGetDataString = {read=FOnGetDataString, write=FOnGetDataString};
	
public:
	__fastcall virtual TApdStateCustomDataSource(Classes::TComponent* AOwner);
	virtual void __fastcall Output(AnsiString AString) = 0 ;
	virtual void __fastcall OutputBlock(void * ABlock, int ASize) = 0 ;
	virtual void __fastcall Pause(void);
	virtual void __fastcall Resume(void);
	virtual void __fastcall StateActivate(TApdCustomState* State) = 0 ;
	virtual void __fastcall StateChange(TApdCustomState* OldState, TApdCustomState* NewState) = 0 ;
	virtual void __fastcall StateDeactivate(TApdCustomState* State) = 0 ;
	virtual void __fastcall StateMachineActivate(TApdCustomState* State, TApdStateCondition* Condition, int Index) = 0 ;
	virtual void __fastcall StateMachineDeactivate(TApdCustomState* State) = 0 ;
	virtual void __fastcall StateMachineStart(TApdCustomStateMachine* AOwner);
	virtual void __fastcall StateMachineStop(void);
	__property bool Paused = {read=GetPaused, nodefault};
public:
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TApdStateCustomDataSource(void) { }
	#pragma option pop
	
};


class PASCALIMPLEMENTATION TApdStateComPortSource : public TApdStateCustomDataSource 
{
	typedef TApdStateCustomDataSource inherited;
	
private:
	Classes::TList* PacketList;
	Adport::TApdCustomComPort* FComPort;
	void *FBuffer;
	int FBufferSize;
	
protected:
	void __fastcall SetComPort(const Adport::TApdCustomComPort* Value);
	void __fastcall PacketEvent(System::TObject* Sender, void * Data, int Size);
	void __fastcall PacketTimeout(System::TObject* Sender);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall TriggerHandler(unsigned Msg, unsigned wParam, int lParam);
	
public:
	__fastcall virtual TApdStateComPortSource(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdStateComPortSource(void);
	virtual void __fastcall Output(AnsiString AString);
	virtual void __fastcall OutputBlock(void * ABlock, int ASize);
	virtual void __fastcall Pause(void);
	virtual void __fastcall Resume(void);
	virtual void __fastcall StateActivate(TApdCustomState* State);
	virtual void __fastcall StateDeactivate(TApdCustomState* State);
	virtual void __fastcall StateMachineActivate(TApdCustomState* State, TApdStateCondition* Condition, int Index);
	virtual void __fastcall StateMachineDeactivate(TApdCustomState* State);
	virtual void __fastcall StateChange(TApdCustomState* OldState, TApdCustomState* NewState);
	virtual void __fastcall StateMachineStart(TApdCustomStateMachine* AOwner);
	virtual void __fastcall StateMachineStop(void);
	
__published:
	__property Adport::TApdCustomComPort* ComPort = {read=FComPort, write=SetComPort};
	__property OnGetData ;
	__property OnGetDataString ;
};


typedef void __fastcall (__closure *TApdStateMachineFinishEvent)(TApdCustomStateMachine* StateMachine, int ErrorCode);

typedef void __fastcall (__closure *TApdStateMachineStateChangeEvent)(TApdCustomStateMachine* StateMachine, TApdCustomState* FromState, TApdCustomState* ToState);

class PASCALIMPLEMENTATION TApdCustomStateMachine : public Oomisc::TApdBaseScrollingWinControl 
{
	typedef Oomisc::TApdBaseScrollingWinControl inherited;
	
private:
	TApdCustomState* FStartState;
	TApdCustomState* FTerminalState;
	TApdCustomState* FCurrentState;
	Graphics::TCanvas* FCanvas;
	TApdStateComPortSource* FDefaultDataSource;
	TApdStateMachineFinishEvent FOnStateMachineFinish;
	TApdStateMachineStateChangeEvent FOnStateChange;
	Forms::TFormBorderStyle FBorderStyle;
	void *FData;
	int FDataSize;
	AnsiString FDataString;
	int FLastErrorCode;
	AnsiString FCaption;
	bool FActive;
	TApdStateCustomDataSource* FDataSource;
	TApdOnConnectoidClickEvent FConnectoidClickEvent;
	bool FMovableStates;
	TAdConnectoidClickStyles FConnectoidClickStyle;
	Adport::TApdCustomComPort* __fastcall GetComPort(void);
	TApdStateCustomDataSource* __fastcall GetDataSource(void);
	TApdStateCustomDataSource* __fastcall GetLiveDataSource(void);
	void __fastcall SetStartState(const TApdCustomState* Value);
	void __fastcall SetTerminalState(const TApdCustomState* Value);
	void __fastcall SetComPort(const Adport::TApdCustomComPort* Value);
	void __fastcall SetBorderStyle(const Forms::TBorderStyle Value);
	void __fastcall SetMovableStates(const bool v);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMCtl3DChanged(Messages::TMessage &Message);
	void * __fastcall GetData(void);
	int __fastcall GetDataSize(void);
	AnsiString __fastcall GetDataString();
	Classes::TStringList* __fastcall GetStateNames(void);
	void __fastcall SetCaption(const AnsiString Value);
	void __fastcall SetConnectoidClickStyle(const TAdConnectoidClickStyles v);
	
protected:
	HIDESBASE MESSAGE void __fastcall CMDesignHitTest(Messages::TWMMouse &Msg);
	void __fastcall ConnectoidAtPoint(TApdConnectAddType AddType, const Types::TPoint &Point);
	virtual void __fastcall CreateParams(Controls::TCreateParams &Params);
	virtual void __fastcall PaintWindow(HDC DC);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	void __fastcall DoActivate(TApdCustomState* NewState);
	void __fastcall DoDeactivate(void);
	MESSAGE void __fastcall DoStateChange(Messages::TMessage &M);
	bool __fastcall GetPaused(void);
	void __fastcall RenderConnectoid(TApdStateConnectoid* Connectoid, TApdCustomState* State, TApdCustomState* DestState);
	void __fastcall SetData(void * NewData, AnsiString NewDataString, int NewDataSize);
	void __fastcall SetDataSource(const TApdStateCustomDataSource* v);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	void __fastcall WMEraseBackground(Messages::TWMEraseBkgnd &Msg);
	__property TApdStateCustomDataSource* LiveDataSource = {read=GetLiveDataSource, write=SetDataSource};
	
public:
	__fastcall virtual TApdCustomStateMachine(Classes::TComponent* AOwner);
	__fastcall virtual ~TApdCustomStateMachine(void);
	virtual void __fastcall Loaded(void);
	void __fastcall StateMachinePaint(void);
	void __fastcall ChangeState(int ConditionIndex);
	void __fastcall Pause(void);
	void __fastcall Resume(void);
	void __fastcall Start(void);
	void __fastcall Cancel(void);
	__property void * Data = {read=GetData};
	__property int DataSize = {read=GetDataSize, nodefault};
	__property AnsiString DataString = {read=GetDataString};
	__property bool Active = {read=FActive, default=0};
	__property Forms::TBorderStyle BorderStyle = {read=FBorderStyle, write=SetBorderStyle, default=1};
	__property Graphics::TCanvas* Canvas = {read=FCanvas};
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
	__property TAdConnectoidClickStyles ConnectoidClickStyle = {read=FConnectoidClickStyle, write=SetConnectoidClickStyle, default=0};
	__property Adport::TApdCustomComPort* ComPort = {read=GetComPort, write=SetComPort};
	__property TApdCustomState* CurrentState = {read=FCurrentState};
	__property TApdStateCustomDataSource* DataSource = {read=GetDataSource, write=SetDataSource};
	__property bool Paused = {read=GetPaused, nodefault};
	__property Classes::TStringList* StateNames = {read=GetStateNames};
	__property TApdCustomState* StartState = {read=FStartState, write=SetStartState};
	__property TApdCustomState* TerminalState = {read=FTerminalState, write=SetTerminalState};
	__property int LastErrorCode = {read=FLastErrorCode, nodefault};
	__property bool MovableStates = {read=FMovableStates, write=SetMovableStates, default=0};
	__property TApdStateMachineStateChangeEvent OnStateChange = {read=FOnStateChange, write=FOnStateChange};
	__property TApdStateMachineFinishEvent OnStateMachineFinish = {read=FOnStateMachineFinish, write=FOnStateMachineFinish};
	__property TApdOnConnectoidClickEvent OnConnectoidClick = {read=FConnectoidClickEvent, write=FConnectoidClickEvent};
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdCustomStateMachine(HWND ParentWindow) : Oomisc::TApdBaseScrollingWinControl(ParentWindow) { }
	#pragma option pop
	
};



class PASCALIMPLEMENTATION TApdStateConnectoid : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FWidth;
	AnsiString FCaption;
	Graphics::TColor FColor;
	TApdStateCondition* FCondition;
	bool FSelected;
	Graphics::TFont* FFont;
	void __fastcall SetCaption(const AnsiString Value);
	void __fastcall SetColor(const Graphics::TColor Value);
	void __fastcall SetFont(const Graphics::TFont* Value);
	void __fastcall SetWidth(const int Value);
	
protected:
	virtual void __fastcall DefineProperties(Classes::TFiler* Filer);
	bool __fastcall IsCaptionStored(void);
	void __fastcall ReadCaption(Classes::TReader* Reader);
	void __fastcall WriteCaption(Classes::TWriter* Writer);
	
public:
	__fastcall TApdStateConnectoid(TApdStateCondition* AOwner);
	__fastcall virtual ~TApdStateConnectoid(void);
	void __fastcall Changed(void);
	
__published:
	__property AnsiString Caption = {read=FCaption, write=SetCaption};
	__property Graphics::TColor Color = {read=FColor, write=SetColor, nodefault};
	__property int Width = {read=FWidth, write=SetWidth, nodefault};
	__property Graphics::TFont* Font = {read=FFont, write=SetFont};
};


class PASCALIMPLEMENTATION TApdStateCondition : public Classes::TCollectionItem 
{
	typedef Classes::TCollectionItem inherited;
	
protected:
	virtual AnsiString __fastcall GetDisplayName();
	
private:
	int FPacketSize;
	int FTimeout;
	int FErrorCode;
	TApdCustomState* FNextState;
	AnsiString FEndString;
	AnsiString FStartString;
	TApdStateConnectoid* FConnectoid;
	bool FIgnoreCase;
	bool FDefaultError;
	bool FDefaultNext;
	AnsiString FOutputOnActivate;
	void __fastcall SetNextState(const TApdCustomState* Value);
	void __fastcall SetConnectoid(const TApdStateConnectoid* Value);
	
protected:
	AnsiString __fastcall GetCaption();
	Graphics::TColor __fastcall GetColor(void);
	Graphics::TFont* __fastcall GetFont(void);
	void __fastcall SetCaption(const AnsiString v);
	void __fastcall SetColor(const Graphics::TColor v);
	void __fastcall SetDefaultError(const bool v);
	void __fastcall SetDefaultNext(const bool v);
	void __fastcall SetFont(const Graphics::TFont* v);
	void __fastcall SetOutputOnActivate(const AnsiString v);
	
public:
	__fastcall virtual TApdStateCondition(Classes::TCollection* Collection);
	__fastcall virtual ~TApdStateCondition(void);
	HIDESBASE void __fastcall Changed(void);
	
__published:
	__property bool DefaultError = {read=FDefaultError, write=SetDefaultError, nodefault};
	__property bool DefaultNext = {read=FDefaultNext, write=SetDefaultNext, nodefault};
	__property AnsiString StartString = {read=FStartString, write=FStartString};
	__property AnsiString EndString = {read=FEndString, write=FEndString};
	__property AnsiString OutputOnActivate = {read=FOutputOnActivate, write=SetOutputOnActivate};
	__property int PacketSize = {read=FPacketSize, write=FPacketSize, nodefault};
	__property int Timeout = {read=FTimeout, write=FTimeout, nodefault};
	__property TApdCustomState* NextState = {read=FNextState, write=SetNextState};
	__property int ErrorCode = {read=FErrorCode, write=FErrorCode, nodefault};
	__property bool IgnoreCase = {read=FIgnoreCase, write=FIgnoreCase, nodefault};
	__property TApdStateConnectoid* Connectoid = {read=FConnectoid, write=SetConnectoid};
	__property AnsiString Caption = {read=GetCaption, write=SetCaption};
	__property Graphics::TColor Color = {read=GetColor, write=SetColor, nodefault};
	__property Graphics::TFont* Font = {read=GetFont, write=SetFont};
};


class DELPHICLASS TApdStateMachine;
class PASCALIMPLEMENTATION TApdStateMachine : public TApdCustomStateMachine 
{
	typedef TApdCustomStateMachine inherited;
	
__published:
	__property Caption ;
	__property ConnectoidClickStyle  = {default=0};
	__property DataSource ;
	__property ComPort ;
	__property MovableStates  = {default=0};
	__property StartState ;
	__property TerminalState ;
	__property OnConnectoidClick ;
	__property OnStateChange ;
	__property OnStateMachineFinish ;
	__property Align  = {default=0};
	__property Anchors  = {default=3};
	__property AutoSize  = {default=0};
	__property BevelEdges  = {default=15};
	__property BevelInner  = {index=0, default=2};
	__property BevelOuter  = {index=1, default=1};
	__property BevelKind  = {default=0};
	__property BevelWidth  = {default=1};
	__property BiDiMode ;
	__property Constraints ;
	__property ParentBiDiMode  = {default=1};
	__property OnContextPopup ;
	__property OnMouseWheel ;
	__property OnMouseWheelDown ;
	__property OnMouseWheelUp ;
	__property OnResize ;
	__property Color  = {default=-2147483643};
	__property AutoScroll  = {default=1};
	__property Ctl3D ;
	__property Font ;
	__property PopupMenu ;
	__property ShowHint ;
	__property TabOrder  = {default=-1};
	__property TabStop  = {default=0};
	__property OnClick ;
	__property OnDblClick ;
	__property OnEnter ;
	__property OnExit ;
	__property OnMouseDown ;
	__property OnMouseMove ;
	__property OnMouseUp ;
public:
	#pragma option push -w-inl
	/* TApdCustomStateMachine.Create */ inline __fastcall virtual TApdStateMachine(Classes::TComponent* AOwner) : TApdCustomStateMachine(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomStateMachine.Destroy */ inline __fastcall virtual ~TApdStateMachine(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TApdStateMachine(HWND ParentWindow) : TApdCustomStateMachine(ParentWindow) { }
	#pragma option pop
	
};


class DELPHICLASS TApdState;
class PASCALIMPLEMENTATION TApdState : public TApdCustomState 
{
	typedef TApdCustomState inherited;
	
__published:
	__property ActiveColor ;
	__property Caption ;
	__property Conditions ;
	__property Font ;
	__property Glyph ;
	__property GlyphCells ;
	__property InactiveColor ;
	__property Movable  = {default=0};
	__property OutputOnActivate ;
	__property OnGetData ;
	__property OnGetDataString ;
	__property OnStateActivate ;
	__property OnStateFinish ;
public:
	#pragma option push -w-inl
	/* TApdCustomState.Create */ inline __fastcall virtual TApdState(Classes::TComponent* AOwner) : TApdCustomState(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TApdCustomState.Destroy */ inline __fastcall virtual ~TApdState(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------

}	/* namespace Adstmach */
using namespace Adstmach;
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// AdStMach
