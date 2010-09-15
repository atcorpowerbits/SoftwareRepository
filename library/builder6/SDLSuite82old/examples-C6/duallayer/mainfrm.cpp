//---------------------------------------------------------------------------

#include <vcl.h>
#include <Math.h>
#pragma hdrstop

#include "mainfrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "rchart"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}



//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
int i;

RC1->ClearGraf();
RC1->ActiveLayer = 1;
RC1->DataColor = RC1->Scale1Y->ColorScale;
RC1->MoveTo(0, 0);
for (i=1; i<490; i++)
  {
  RC1->DrawTo(0.2*i, sin(i*0.2)*exp(0.01*i));
  }
RC1->ActiveLayer = 2;
RC1->DataColor = RC1->Scale2Y->ColorScale;
RC1->MoveTo(cos(0), sin(0));
for (i=1; i<490; i++)
  {
  RC1->DrawTo(cos(i*0.058), sin(i*0.02));
  }
RC1->ShowGraf();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBoxMouseAffectsLayer1Click(TObject *Sender)
{
RC1->MouseAffectsLayer[1] = CBoxMouseAffectsLayer1->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBoxMouseAffectsLayer2Click(TObject *Sender)
{
RC1->MouseAffectsLayer[2] = CBoxMouseAffectsLayer2->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGLayoutClick(TObject *Sender)
{
switch (RGLayout->ItemIndex)
  {
  case 0 : {
           RC1->StandardLayout = rcl_X2Bottom_Y2Left;
           break;
           }
  case 1 : {
           RC1->StandardLayout = rcl_X1Bottom_Y2Both;
           break;
           }
  case 2 : {
           RC1->StandardLayout = rcl_X2Both_Y2Both;
           break;
           }
  };

}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGMouseActionClick(TObject *Sender)
{
switch (RGMouseAction->ItemIndex)
  {
  case 0 : {
           RC1->MouseAction = maPan;
           break;
           }
  case 1 : {
           RC1->MouseAction = maZoomWindPos;
           break;
           }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButZoom11Click(TObject *Sender)
{
RC1->AutoRange(1,15);
RC1->AutoRange(2,15);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RGGridClick(TObject *Sender)
{
switch (RGGrid->ItemIndex)
  {
  case 0: {
          RC1->GridStyle = gsNone;
          RC1->ActiveLayer = 0;
          break;
          };
  case 1: {
          RC1->GridStyle = gsDotLines;
          RC1->ActiveLayer = 1;
          break;
          };
  case 2: {
          RC1->GridStyle = gsDotLines;
          RC1->ActiveLayer = 2;
          break;
          };
  }
}
//---------------------------------------------------------------------------
