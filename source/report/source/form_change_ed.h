//---------------------------------------------------------------------------
#ifndef form_change_edH
#define form_change_edH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class Tfrm_pwa_change_ed : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnl_form;
  TToolBar *ToolBar1;
  TToolButton *btn_move_ed_left;
  TToolButton *btn_move_ed_right;
  TToolButton *ToolButton8;
  TToolButton *btn_move_ed_accept;
  TToolButton *btn_move_ed_cancel;
  TImageList *ImageListEnabled;
  TImageList *ImageListDisable;
  void __fastcall btn_move_ed_leftClick(TObject *Sender);
  void __fastcall btn_move_ed_rightClick(TObject *Sender);
  void __fastcall btn_move_ed_cancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
  __fastcall Tfrm_pwa_change_ed(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_pwa_change_ed *frm_pwa_change_ed;
//---------------------------------------------------------------------------
#endif
