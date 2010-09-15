//---------------------------------------------------------------------------
#ifndef form_importH
#define form_importH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
//---------------------------------------------------------------------------
class Tfrm_import : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TBitBtn *btnImport;
  TBitBtn *btnClose;
  TPanel *Panel2;
  TPanel *Panel3;
  TLabel *Label1;
  TBitBtn *btnSelect;
  TEdit *edtDir;
  TOpenDialog *OpenDialog1;
  TPanel *Panel5;
  TPanel *Panel4;
  TCheckBox *chkShowMsg;
  TGroupBox *GroupBox1;
  TLabel *lblPatTitle;
  TLabel *lblMeasTitle;
  TLabel *lblPWVTitle;
  TGroupBox *grpMsg;
  TMemo *memMsg;
  TProgressBar *ProgressBar1;
  TBitBtn *btnCancel;
  TSplitter *Splitter1;
  TLabel *lblProg;
  TPanel *Panel6;
  TGroupBox *GroupBox3;
  TEdit *edtCap;
  TUpDown *UpDownCap;
  TBitBtn *btnClear;
  TBitBtn *btnSave;
  TSaveDialog *SaveDialogMsg;
        TADOTable *tblPatDbase;
        TADOTable *tblMeasDbase;
        TADOTable *tblPWVDbase;
  void __fastcall btnImportClick(TObject *Sender);

  void __fastcall btnCloseClick(TObject *Sender);
  void __fastcall btnSelectClick(TObject *Sender);
  void __fastcall btnClearClick(TObject *Sender);

  void __fastcall chkShowMsgClick(TObject *Sender);
  void __fastcall memMsgChange(TObject *Sender);

  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall btnCancelClick(TObject *Sender);
  
  void __fastcall FormShow(TObject *Sender);
  
  void __fastcall btnSaveClick(TObject *Sender);
private:	// User declarations
  bool RestorePat(TDataSet* pTable1, TDataSet* pTable2);
  bool RestoreMeas(TDataSet* pTable1, TDataSet* pTable2, bool pCalculate);
  bool RestorePWV(TDataSet* pTable1, TDataSet* pTable2, bool pCalculate);
  String FormatName(String pName);
public:		// User declarations
  // __fastcall TfrmImport(TComponent* Owner);
  __fastcall Tfrm_import(TComponent* Owner, String DbaseDir,
             TADOTable *pTblPatAccess, TADOTable *pTblMeasAccess,
             TADOTable *pPWVAccess, bool pCalculate = true);
  TADOTable *tblPatAccess, *tblMeasAccess, *tblPWVAccess;
  bool Calculate;
  bool Success;
  bool CloseApp;
  String PatTitle, MeasTitle, PWVTitle;
  String MsgStr;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_import *frm_import;
//---------------------------------------------------------------------------
#endif
