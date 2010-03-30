//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
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
#pragma link "rchart"
#pragma resource "*.dfm"
TForm1 *Form1;
const int MaxP = 10;
const double RealPG[MaxP][2] = {{3,3}, {4,3}, {5,5}, {6,2}, {5,1},
                                {4,-2}, {-2,-4}, {-2,-1}, {-1,2}, {0,1}};

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawPolygon (TCanvas *Canvas, const int Top, const int Left)
{
TPoint Polygon[MaxP];
int    i;
int    x,y;

for (i=0; i<MaxP; i++)
  {
  RChart1->R2M(1, RealPG[i][0], RealPG[i][1], x, y);
  Polygon[i].x = x-Left;
  Polygon[i].y = y-Top;
  }
Canvas->Brush->Color = clYellow;
Canvas->Pen->Color = clBlack;
Canvas->Polygon (Polygon, MaxP-1);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
if (RadioGroup1->ItemIndex == 0)
  {
  RChart1->MouseAction = maPan;
  }
else
  {
  RChart1->MouseAction = maZoomDrag;
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RChart1DataRendered(TObject *Sender,
      TCanvas *&Canvas, int Top, int Left)
{
if (RGzPos->ItemIndex == 1)
  {
  DrawPolygon (Canvas, Top, Left);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RChart1BeforeRenderData(TObject *Sender,
      TCanvas *&Canvas, int Top, int Left)
{
if (RGzPos->ItemIndex == 0)
  {
  DrawPolygon (Canvas, Top, Left);
  }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RGzPosClick(TObject *Sender)
{
RChart1->ShowGraf();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormShow(TObject *Sender)
{
int i;

RChart1->DataColor = clBlue;
RChart1->MoveTo(-10,0);
for (i=1; i<=999; i++)
  {
  RChart1->DrawTo(i/50.0-10, (1000-i)/200.0*sin(i*i/10000.0));
  }
}
//---------------------------------------------------------------------------

