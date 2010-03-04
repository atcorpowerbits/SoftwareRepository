//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "FrmNLab.h"
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
#pragma link "NumLab"
#pragma link "Colsel"
#pragma link "colsel"
#pragma link "numlab"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
NumLab1->Value = 6.221*(ScrollBar1->Position-500);
NumLab1->StateText = "any "+IntToStr(ScrollBar1->Position)+" text";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBRaisedClick(TObject *Sender)
{
NumLab1->FrameStyle = fsRaised;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBLoweredClick(TObject *Sender)
{
NumLab1->FrameStyle = fsLowered;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RbEmbossedClick(TObject *Sender)
{
NumLab1->FrameStyle = fsEmbossed;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBEngravedClick(TObject *Sender)
{
NumLab1->FrameStyle = fsEngraved;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBSimpleClick(TObject *Sender)
{
NumLab1->FrameStyle = fsSimple;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBNoneClick(TObject *Sender)
{
NumLab1->FrameStyle = fsNone;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBFixPClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtFixP;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBFloatClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtFloat;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBIntClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtInt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBZeroIntClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtZeroInt;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBExpClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtExp;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBHexClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtHex;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBCenterClick(TObject *Sender)
{
NumLab1->Alignment = taCenter;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBLeftClick(TObject *Sender)
{
NumLab1->Alignment = taLeftJustify;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBRightClick(TObject *Sender)
{
NumLab1->Alignment = taRightJustify;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColSel1Change(TObject *Sender)
{
NumLab1->ColorLabText = ColSel1->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColSel2Change(TObject *Sender)
{
NumLab1->ColorLabBakG = ColSel2->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColSel3Change(TObject *Sender)
{
NumLab1->ColorOutText = ColSel3->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColSel4Change(TObject *Sender)
{
NumLab1->ColorOutBakG = ColSel4->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBPrecisChange(TObject *Sender)
{
NumLab1->Precision = SBPrecis->Position;
NLabPreci->Value = SBPrecis->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBWidthChange(TObject *Sender)
{
NumLab1->Width = SBWidth->Position;
NLabWidth->Value = NumLab1->Width;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBLeftSpaceChange(TObject *Sender)
{
NumLab1->LeftSpace = SBLeftSpace->Position;
NLabLeftSpace->Value = NumLab1->LeftSpace;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar2Change(TObject *Sender)
{
NumLab1->LabelWidth = ScrollBar2->Position;
NLabLabelWidth->Value = NumLab1->LabelWidth;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBDateTimeClick(TObject *Sender)
{
EdDateTime->Enabled = true;
NumLab1->DTFormat = EdDateTime->Text;
NumLab1->DisplayType = dtDateTime;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBForcePlusSignClick(TObject *Sender)
{
NumLab1->ForcePlusSign = CBForcePlusSign->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EdDateTimeChange(TObject *Sender)
{
NumLab1->DTFormat = EdDateTime->Text;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
NumLab1->LeftTextAlignment = taCenter;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
NumLab1->LeftTextAlignment = taLeftJustify;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
NumLab1->LeftTextAlignment = taRightJustify;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
NumLab1->RightTextAlignment = taCenter;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton5Click(TObject *Sender)
{
NumLab1->RightTextAlignment = taLeftJustify;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioButton6Click(TObject *Sender)
{
NumLab1->RightTextAlignment = taRightJustify;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RBBinClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtBin;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RBOctClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtOct;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RBStateClick(TObject *Sender)
{
EdDateTime->Enabled = false;
NumLab1->DisplayType = dtState;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RBLatDegClick(TObject *Sender)
{
EdDateTime->Enabled = false;
SBPrecis->Position = 4;
NumLab1->DisplayType = dtDeg;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RBLatDegMinClick(TObject *Sender)
{
EdDateTime->Enabled = false;
SBPrecis->Position = 2;
NumLab1->DisplayType = dtDegMin;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RBLatDegMinSecClick(TObject *Sender)
{
EdDateTime->Enabled = false;
SBPrecis->Position = 0;
NumLab1->DisplayType = dtDegMinSec;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
ColSel4->SelColor = NumLab1->ColorOutBakG;
ColSel3->SelColor = NumLab1->ColorOutText;
ColSel1->SelColor = NumLab1->ColorLabText;
ColSel2->SelColor = NumLab1->ColorLabBakG;
if (Numlab::IsLightEd)
  {
  RBBin->Enabled = false;
  RBOct->Enabled = false;
  RBHex->Enabled = false;
  RBZeroInt->Enabled = false;
  RBLatDeg->Enabled = false;
  RBLatDegMin->Enabled = false;
  RBLatDegMinSec->Enabled = false;
  RBState->Enabled = false;
  RBDateTime->Enabled = false;
  }
}
//---------------------------------------------------------------------------

