//---------------------------------------------------------------------------

#ifndef mainfrmH
#define mainfrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "colsel.hpp"
#include "progbar.hpp"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TProgBar *PBar1;
        TProgBar *PBar2;
        TProgBar *PBar3;
        TProgBar *PBar4;
        TProgBar *PBar5;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TScrollBar *ScrollBar1;
        TRadioGroup *RGDirection;
        TCheckBox *CBoxGradient;
        TColSel *ColSelMin;
        TColSel *ColSelMax;
        TRadioGroup *RGGradMode;
        TScrollBar *SBarTextAngle;
        TBitBtn *BButLoadImage;
        TBitBtn *BButSpecialCurtain1;
        TBitBtn *BButNoImage;
        TColSel *CSelBakgnd;
        TRadioGroup *RGOutFrame;
        TRadioGroup *RGInnerFrame;
        TBitBtn *BButSpecialCurtain2;
        TScrollBar *SBarMarginTop;
        TScrollBar *SBarMarginBottom;
        TScrollBar *SBarMarginLeft;
        TScrollBar *SBarMarginRight;
        TOpenDialog *OpenDialog1;
        void __fastcall SBarMarginTopChange(TObject *Sender);
        void __fastcall SBarMarginBottomChange(TObject *Sender);
        void __fastcall SBarMarginLeftChange(TObject *Sender);
        void __fastcall SBarMarginRightChange(TObject *Sender);
        void __fastcall BButSpecialCurtain1Click(TObject *Sender);
        void __fastcall BButSpecialCurtain2Click(TObject *Sender);
        void __fastcall RGOutFrameClick(TObject *Sender);
        void __fastcall RGInnerFrameClick(TObject *Sender);
        void __fastcall CSelBakgndChange(TObject *Sender);
        void __fastcall BButLoadImageClick(TObject *Sender);
        void __fastcall BButNoImageClick(TObject *Sender);
        void __fastcall SBarTextAngleChange(TObject *Sender);
        void __fastcall ScrollBar1Change(TObject *Sender);
        void __fastcall RGDirectionClick(TObject *Sender);
        void __fastcall RGGradModeClick(TObject *Sender);
        void __fastcall ColSelMinChange(TObject *Sender);
        void __fastcall ColSelMaxChange(TObject *Sender);
        void __fastcall CBoxGradientClick(TObject *Sender);
        void __fastcall PBar1ShowValue(TObject *Sender,
          AnsiString &ValueText);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
