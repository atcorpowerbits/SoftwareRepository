//----------------------------------------------------------------------------
#ifndef form_aboutH
#define form_aboutH
//----------------------------------------------------------------------------
#include <System.hpp>
#include <Windows.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//----------------------------------------------------------------------------
class Tfrm_aboutbox : public TForm
{
__published:
  TPanel *pnl_header;
  TLabel *lbl_pwvmed;
    TLabel *lbl_copyright;
  TLabel *lbl_url;
  TLabel *lbl_email;
  TLabel *lbl_sysid_title;
  TLabel *lbl_sysid;
  TLabel *lbl_version;
    TPanel *pnl_options;
    TLabel *lbl_install_options;
   TLabel *lbl_hardware;
   TLabel *lbl_data_mode;
   TLabel *lbl_pwa;
   TLabel *lbl_pwv;
   TLabel *lbl_pwm;
   TLabel *lbl_hrv;
   TSpeedButton *btn_print;
   TSpeedButton *btn_ok;
  void __fastcall btn_okClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
   void __fastcall btn_printClick(TObject *Sender);
  
    
private:
public:
	virtual __fastcall Tfrm_aboutbox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE Tfrm_aboutbox *frm_aboutbox;
//----------------------------------------------------------------------------
#endif
