//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#pragma hdrstop

#include "frmmain.h"
#include "math2.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "numlab"
#pragma link "rchart"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButNewPointsClick(TObject *Sender)
{
const double ofs=0.06;

int        i;
double     x,y;
TPDblArray dt;
TPDblArray dt2;

Randomize;
dt.Length = SBarNPoints->Position;
RChart1->ClearGraf();
RChart1->DataColor = clBlue;
for (i=0; i<SBarNPoints->Position; i++)
  {
  x = 0.01*random(1000);
  y = 0.01*random(1000);
  dt[i].X = x;
  dt[i].Y = y;
  RChart1->MarkAt(x, y, 9);
  };

dt2 = Convex2DHull (dt);

RChart1->DataColor = clLime;
RChart1->MoveTo (dt2[0].X, dt2[0].Y);
for (i=0; i<dt2.Length; i++)
  {
  RChart1->DrawTo (dt2[i].X, dt2[i].Y);
  }
RChart1->DrawTo (dt2[0].X, dt2[0].Y);
RChart1->DataColor = clRed;
for (i=0; i<dt2.Length; i++)
  {
  RChart1->Text (dt2[i].X+ofs*(dt2[i].X-5), dt2[i].Y+ofs*(dt2[i].Y-5), 10, IntToStr(i+1));
  }
RChart1->ShowGraf();

NLabArea->Value = fabs(PolygonArea(dt2));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SBarNPointsChange(TObject *Sender)
{
NLabPoints->Value = SBarNPoints->Position;
ButNewPointsClick(NULL);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
ButNewPointsClick(NULL);
}
//---------------------------------------------------------------------------





