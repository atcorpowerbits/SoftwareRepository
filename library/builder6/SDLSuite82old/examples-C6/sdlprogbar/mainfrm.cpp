//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>8
#pragma hdrstop

#include "mainfrm.h"
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
#pragma link "progbar"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarMarginTopChange(TObject *Sender)
{
PBar1->MarginTop = SBarMarginTop->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarMarginBottomChange(TObject *Sender)
{
PBar1->MarginBottom = SBarMarginBottom->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarMarginLeftChange(TObject *Sender)
{
PBar1->MarginLeft = SBarMarginLeft->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarMarginRightChange(TObject *Sender)
{
PBar1->MarginRight = SBarMarginRight->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButSpecialCurtain1Click(TObject *Sender)
{
int  i;

PBar1->ColorMapMode = cgmMove;
PBar1->BarColors[1023] = clBlack;
for (i=1022; i>=0; i--)
  {
  PBar1->BarColors[i] = TColor(int(fmod(i, 256)) +0X003F00+256*int(fmod(i, 128)) + 0X8F0000);
  }
CBoxGradient->Checked = true;
RGGradMode->ItemIndex = 2;
PBar1->Invalidate();
ColSelMin->SelColor = PBar1->ColorMin;
ColSelMax->SelColor = PBar1->ColorMax;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButSpecialCurtain2Click(TObject *Sender)
{
int  i;

PBar1->ColorMapMode = cgmMove;
PBar1->BarColors[1023] = clBlue;
for (i=1022; i>0; i--)
  {
  PBar1->BarColors[i] = TColor(128+int(0.5+127*sin(i/60.0)) + 256*(128+int(0.5+127*cos(i/81.0))));
  }
CBoxGradient->Checked = true;
RGGradMode->ItemIndex = 2;
PBar1->Invalidate();
ColSelMin->SelColor = PBar1->ColorMin;
ColSelMax->SelColor = PBar1->ColorMax;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGOutFrameClick(TObject *Sender)
{
PBar1->FrameStyleOuter = TFrameStyle(RGOutFrame->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGInnerFrameClick(TObject *Sender)
{
PBar1->FrameStyleInner = TFrameStyle(RGInnerFrame->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSelBakgndChange(TObject *Sender)
{
PBar1->ColorBackGnd = CSelBakgnd->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButLoadImageClick(TObject *Sender)
{
if (OpenDialog1->Execute())
  {
  PBar1->BackGroundImg = OpenDialog1->FileName;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButNoImageClick(TObject *Sender)
{
PBar1->BackGroundImg = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarTextAngleChange(TObject *Sender)
{
PBar1->TextAngle = SBarTextAngle->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
PBar1->Value = ScrollBar1->Position/5;
PBar2->Value = ScrollBar1->Position;
PBar3->Value = ScrollBar1->Position;
PBar4->Value = ScrollBar1->Position;
PBar5->Value = ScrollBar1->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGDirectionClick(TObject *Sender)
{
PBar1->Direction = TDirection(RGDirection->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGGradModeClick(TObject *Sender)
{
PBar1->ColorMapMode = TColorMapping(RGGradMode->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColSelMinChange(TObject *Sender)
{
PBar1->ColorMin = ColSelMin->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ColSelMaxChange(TObject *Sender)
{
PBar1->ColorMax = ColSelMax->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBoxGradientClick(TObject *Sender)
{
PBar1->ShowColorGradient = CBoxGradient->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PBar1ShowValue(TObject *Sender,
      AnsiString &ValueText)
{
ValueText = ValueText+" %";
}
//---------------------------------------------------------------------------
