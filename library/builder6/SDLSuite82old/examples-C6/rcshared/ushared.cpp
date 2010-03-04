//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "ushared.h"
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
#pragma link "rchart"
#pragma resource "*.dfm"
TForm1 *Form1;
const int MaxData = 2000;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawData()
{
int i;

RChart1->ClearGraf();
RChart1->MoveTo (1, cos(0.041)*sin(0.03)+1/1000.0+SBNoise->Position*0.0001*random(100));
for (i=2;i<=MaxData;i++)
  {
  RChart1->DrawTo (i, cos(i*0.041)*sin(i*0.03)+5*exp(-(0.01*(i-500))*(0.01*(i-500)))+
                     7*exp(-(0.021*(i-1500))*(0.021*(i-1500)))+SBNoise->Position*0.0001*random(100));
  }
RChart1->ShowGraf();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBNoiseChange(TObject *Sender)
{
DrawData();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RChart2ZoomPan(TObject *Sender)
{
RChart1->CrossHair1->PosX = RChart2->Scale1X->RangeLow;
RChart1->CrossHair2->PosX = RChart2->Scale1X->RangeHigh;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RChart3ZoomPan(TObject *Sender)
{
RChart1->CrossHair3->PosX = RChart3->Scale1X->RangeLow;
RChart1->CrossHair4->PosX = RChart3->Scale1X->RangeHigh;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RChart1CrossHairMove(TObject *Sender,
      TCrossHair *WhichCrossHair)
{
RChart2->Scale1X->RangeLow = RChart1->CrossHair1->PosX;
RChart2->Scale1X->RangeHigh = RChart1->CrossHair2->PosX;
RChart3->Scale1X->RangeLow = RChart1->CrossHair3->PosX;
RChart3->Scale1X->RangeHigh = RChart1->CrossHair4->PosX;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
RChart1->SetRange (1, 0,-2, MaxData, 10);
RChart2->UseDataOf = RChart1;
RChart3->UseDataOf = RChart1;
DrawData();
RChart1CrossHairMove (Sender, NULL);
}
//---------------------------------------------------------------------------
