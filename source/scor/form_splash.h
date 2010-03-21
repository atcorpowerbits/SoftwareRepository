#ifndef form_splashH
#define form_splashH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrm_splash : public TForm
{
__published:	// IDE-managed Components
    TPanel *pnl_bottom;
    TLabel *lbl_loading;
    TBevel *Bevel1;
    TLabel *lbl_copyright;
    TLabel *lbl_version;
    TLabel *lbl_model;
    TPanel *pnl_image;
    TImage *img_splash;
   TImage *Image1;
   TImage *Image2;
private:	// User declarations
public:		// User declarations
    __fastcall Tfrm_splash(TComponent* Owner);
};

extern PACKAGE Tfrm_splash *frm_splash;
#endif
