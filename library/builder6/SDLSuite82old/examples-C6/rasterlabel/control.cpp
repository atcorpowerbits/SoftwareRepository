//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "mainfrm.h"
#include "control.h"
#include "stringl.hpp"
/********************** set-up of include pathes ****************************
Please note: you have to set up the pathes to the include files before
this sample program can be compiled:
Use the command "Project/Options", select the "Directories/Conditional"
tab, and add the required packages to the "include path"

example:
   if you installed the packages into the default directory, the
   include path for the BasePack will be: "C:\SDLSuite\basepack\C6"

More information can be found in the following FAQ article:
   http://forum.sdlsuite.com/read.php?f=2&i=21&t=21
*****************************************************************************/
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "colsel"
#pragma resource "*.dfm"
TFrmControl *FrmControl;
//---------------------------------------------------------------------------
__fastcall TFrmControl::TFrmControl(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
AnsiString __fastcall TFrmControl::FillPlaceholder (AnsiString Instring)
{
  int   ix;
  AnsiString astr;
  AnsiString ResStr;
  double fr;

fr = Now();
fr = fr-int(fr);
switch (RGPlaceHolder->ItemIndex)
  {
  case 1 : {
           astr = strff(100*fr,1,4);
           break;
           }
  case 2 : {
           astr = FormatDateTime ("HH:NN:SS", Now());
           break;
           }
  case 3 : {
           astr = FormatDateTime ("YYYY-MMM-DD  HH:NN:SS", Now());
           break;
           }
  default : astr = "";
  }
ResStr = ReplaceStringInString (Instring, "<dat>", astr, true);
return ResStr;
}
//---------------------------------------------------------------------------
void __fastcall TFrmControl::RGDotSizeClick(TObject *Sender)
{
FrmMain->RLab1->DotSize = RGDotSize->ItemIndex+1;
}
//---------------------------------------------------------------------------
void __fastcall TFrmControl::BButDefaultFontClick(TObject *Sender)
{
FrmMain->RLab1->Font->Name = "default";
}
//---------------------------------------------------------------------------
void __fastcall TFrmControl::BButCloseUIClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrmControl::BButFontClick(TObject *Sender)
{
if (FontDialog1->Execute())
  {
  FrmMain->RLab1->Font = FontDialog1->Font;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmControl::ComboBlockModeChange(TObject *Sender)
{
FrmMain->RLab1->CharBlockMode = TRDBlockMode(ComboBlockMode->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TFrmControl::RGFrameStyleClick(TObject *Sender)
{
FrmMain->RLab1->FrameStyle = TFrameStyle(RGFrameStyle->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TFrmControl::FormShow(TObject *Sender)
{
CSelBg->SetAllColorEditFlags();
CSelDotFg->SetAllColorEditFlags();
CSelDotBg->SetAllColorEditFlags();
}
//---------------------------------------------------------------------------

void __fastcall TFrmControl::CBoxProportionalClick(TObject *Sender)
{
FrmMain->RLab1->Proportional = CBoxProportional->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TFrmControl::CSelDotFgChange(TObject *Sender)
{
FrmMain->RLab1->ColorDotOn = CSelDotFg->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TFrmControl::CSelDotBgChange(TObject *Sender)
{
FrmMain->RLab1->ColorDotOff = CSelDotBg->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TFrmControl::CSelBgChange(TObject *Sender)
{
FrmMain->RLab1->ColorLabBakG = CSelBg->SelColor;
}
//---------------------------------------------------------------------------

void __fastcall TFrmControl::RGDotSpacingClick(TObject *Sender)
{
FrmMain->RLab1->DotSpacing = RGDotSpacing->ItemIndex;
}
//---------------------------------------------------------------------------

void __fastcall TFrmControl::RGScrollClick(TObject *Sender)
{
switch (RGScroll->ItemIndex)
  {
  case 0: {
          FrmMain->RLab1->ScrollMode = rdsmOff;
          FrmMain->RLab1->PosX = 0;
          FrmMain->RLab1->PosY = 0;
          break;
          }
  case 5: {
          FrmMain->RLab1->ScrollMode = rdsmOff;
          FrmMain->RLab1->Height = 100;
          break;
          }
  default: FrmMain->RLab1->ScrollMode = TRDScrollMode(RGScroll->ItemIndex);
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrmControl::RGScrollStepClick(TObject *Sender)
{
const int SInc[7] = {1,2,3,5,7,24,35};

FrmMain->RLab1->ScrollIncrement = SInc[RGScrollStep->ItemIndex];
}
//---------------------------------------------------------------------------

void __fastcall TFrmControl::RGScrollSpeedClick(TObject *Sender)
{
const int SSpd [7] = {10,20,50,100,200,500,1000};

FrmMain->RLab1->ScrollInterval = SSpd[RGScrollSpeed->ItemIndex];
}
//---------------------------------------------------------------------------

void __fastcall TFrmControl::EdTextChange(TObject *Sender)
{
FrmMain->RLab1->Text = FillPlaceholder (EdText->Text);
}
//---------------------------------------------------------------------------

