//---------------------------------------------------------------------------
#ifndef form_selectH
#define form_selectH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include <meas\pubtype.h>
//---------------------------------------------------------------------------
class Tfrm_select : public TForm
{
__published:	// IDE-managed Components
  TPanel *Panel1;
  TPanel *Panel2;
  TPanel *pnl_main;
  TPanel *pnl_med_notes;
  TLabel *Label5;
  TLabel *Label6;
  TLabel *lbl_artery;
  TMemo *mm_medication;
  TMemo *mm_notes;
  TComboBox *lst_artery;
  TPanel *pnl_graphed;
  TLabel *Label2;
  TListBox *lst_out;
  TPanel *pnl_centre;
  TPanel *pnl_not_graphed;
  TLabel *Label1;
  TListBox *lst_in;
  TLabel *lbl_pat_title;
  TLabel *lbl_pat;
  TSpeedButton *btn_add;
  TSpeedButton *btn_add_all;
  TSpeedButton *btn_delete;
  TSpeedButton *btn_delete_all;
  TLabel *lblAv;
  TLabel *lblSel;
  TLabel *Label4;
  TLabel *lblMax;
   TLabel *lbl_pwa_artery_title;
   TLabel *lbl_pwa_artery;
   TSpeedButton *btnOk;
   TSpeedButton *btnCancel;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall lst_inClick(TObject *Sender);
  
  void __fastcall btn_add_allClick(TObject *Sender);
  void __fastcall btn_delete_allClick(TObject *Sender);
  void __fastcall btn_addClick(TObject *Sender);
  void __fastcall btn_deleteClick(TObject *Sender);
  void __fastcall lst_outClick(TObject *Sender);
  void __fastcall btnOkClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall EnableButtons();

  void __fastcall lst_arteryChange(TObject *Sender);
   void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
  int FMaxNofMeasurements;
  MEAS_ID_TYPE FMeasMode;
  String *FArtery;
  TStringList* input_list;
  TStringList* result_list;
  TStringList* FFullList;
  TDataSet *qry_select;
  void  __fastcall SortList(TStrings* pList);
public:		// User declarations
  // __fastcall Tfrm_select(TComponent* Owner);
  __fastcall Tfrm_select(TComponent* Owner, String pPatientName,
             TDataSet *pQuery, TStringList* pFullList, TStringList* pInputList, TStringList* pResultList,
             MEAS_ID_TYPE pMeasMode, int pMaxNofMeasurements,
             String *pPWAArtery = NULL);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_select *frm_select;
//---------------------------------------------------------------------------
#endif
