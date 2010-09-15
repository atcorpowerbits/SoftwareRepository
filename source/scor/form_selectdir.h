//---------------------------------------------------------------------------
#ifndef form_selectdirH
#define form_selectdirH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <FileCtrl.hpp>
//---------------------------------------------------------------------------
class Tfrm_select_dir : public TForm
{
__published:	// IDE-managed Components
  TPanel *pnl_form;
  TPanel *pnl_drive;
  TLabel *lbl_path_title;
  TLabel *lbl_path;
  TDriveComboBox *cmbx_drive;
  TDirectoryListBox *lstbx_dir;
   TSpeedButton *bbtn_select;
   TSpeedButton *bbtn_close;
  void __fastcall bbtn_selectClick(TObject *Sender);
  void __fastcall bbtn_closeClick(TObject *Sender);
  
  void __fastcall FormActivate(TObject *Sender);
  void __fastcall cmbx_driveChange(TObject *Sender);
  void __fastcall cmbx_driveClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   AnsiString  selected_dir;
  __fastcall Tfrm_select_dir(TComponent* Owner, String title);
};

bool emma_select_dir(TComponent *owner,
                     String select_title,
                     String &dir);

#endif
