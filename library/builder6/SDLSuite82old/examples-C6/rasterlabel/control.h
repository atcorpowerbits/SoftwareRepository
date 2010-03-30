//---------------------------------------------------------------------------

#ifndef controlH
#define controlH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "colsel.hpp"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmControl : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TRadioGroup *RGDotSize;
        TRadioGroup *RGDotSpacing;
        TRadioGroup *RGScroll;
        TRadioGroup *RGScrollSpeed;
        TRadioGroup *RGScrollStep;
        TColSel *CSelDotFg;
        TColSel *CSelDotBg;
        TColSel *CSelBg;
        TCheckBox *CBoxProportional;
        TRadioGroup *RGFrameStyle;
        TBitBtn *BButFont;
        TComboBox *ComboBlockMode;
        TEdit *EdText;
        TRadioGroup *RGPlaceHolder;
        TBitBtn *BButCloseUI;
        TBitBtn *BButDefaultFont;
        TFontDialog *FontDialog1;
        void __fastcall RGDotSizeClick(TObject *Sender);
        void __fastcall BButDefaultFontClick(TObject *Sender);
        void __fastcall BButCloseUIClick(TObject *Sender);
        void __fastcall BButFontClick(TObject *Sender);
        void __fastcall ComboBlockModeChange(TObject *Sender);
        void __fastcall RGFrameStyleClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall CBoxProportionalClick(TObject *Sender);
        void __fastcall CSelDotFgChange(TObject *Sender);
        void __fastcall CSelDotBgChange(TObject *Sender);
        void __fastcall CSelBgChange(TObject *Sender);
        void __fastcall RGDotSpacingClick(TObject *Sender);
        void __fastcall RGScrollClick(TObject *Sender);
        void __fastcall RGScrollStepClick(TObject *Sender);
        void __fastcall RGScrollSpeedClick(TObject *Sender);
        void __fastcall EdTextChange(TObject *Sender);
private:
public:
        AnsiString __fastcall TFrmControl::FillPlaceholder (AnsiString Instring);
        __fastcall TFrmControl(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmControl *FrmControl;
//---------------------------------------------------------------------------
#endif
