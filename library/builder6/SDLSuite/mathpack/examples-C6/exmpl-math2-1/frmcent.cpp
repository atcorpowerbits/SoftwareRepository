
//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include <stdlib.h>
#include "frmcent.h"
#include "Matrix.hpp"
#include "Math2.hpp"
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
#pragma link "RChart"
#pragma link "Matrix"
#pragma link "Math2"
#pragma link "rchart"
#pragma link "matrix"
#pragma resource "*.dfm"

TForm1 *Form1;
const int NData = 200;                    // number of data points
const int NCenters = 10;                  // number of centers

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
void __fastcall TForm1::BButCreateDClick(TObject *Sender)
{
int i;

RChart1->ClearGraf();
RChart1->DataColor = clBlack;
for (i=1; i<= NData/2; i++)
  {
  Data->Elem[1][i] = 0.05*RChart1->RangeHiX+0.0009*RChart1->RangeHiX*random(1000);
  Data->Elem[2][i] = 0.05*RChart1->RangeHiY+0.0009*RChart1->RangeHiY*random(1000);
  RChart1->MarkAt (Data->Elem[1][i],Data->Elem[2][i],7);
  }
for (i=NData/2; i<=NData-20; i++)
  {
  Data->Elem[1][i] = 0.15*RChart1->RangeHiX+0.0004*RChart1->RangeHiX*random(1000);
  Data->Elem[2][i] = 0.15*RChart1->RangeHiY+0.0004*RChart1->RangeHiY*random(1000);
  RChart1->MarkAt (Data->Elem[1][i],Data->Elem[2][i],7);
  }
for (i=NData-20; i<=NData; i++)
  {
  Data->Elem[1][i] = 0.25*RChart1->RangeHiX+0.0002*RChart1->RangeHiX*random(1000);
  Data->Elem[2][i] = 0.25*RChart1->RangeHiY+0.0002*RChart1->RangeHiY*random(1000);
  RChart1->MarkAt (Data->Elem[1][i],Data->Elem[2][i],7);
  }
RChart1->ShowGraf();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
Data->Resize (2,NData);
Centers->Resize  (2,NCenters);
Data->Fill (0);
Centers->Fill (0);
}
//---------------------------------------------------------------------------
void __fastcall ShowProgress (int cnt)
{
Form1->NLabProcCnt->Value = 100.0*cnt/NData;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButCalcCentClick(TObject *Sender)
{
double MeanDist;
int i;

ProcStat = 0;
MathFeedBackProc = ShowProgress;
NLabProcCnt->Visible = true;
NLabProcCnt->LeftText = "... calculating";
NLabProcCnt->RightText = "% done";
FindCenters (Data, 1, Data->NrOfRows, NCenters, Centers, MeanDist); // mean distance
RChart1->DataColor = clRed;
for (i=1; i<=NCenters; i++)
  RChart1->MarkAt (Centers->Elem[1][i],Centers->Elem[2][i],12);
RChart1->ShowGraf();
MathFeedBackProc = NULL;
NLabProcCnt->Visible = false;
}
//---------------------------------------------------------------------------