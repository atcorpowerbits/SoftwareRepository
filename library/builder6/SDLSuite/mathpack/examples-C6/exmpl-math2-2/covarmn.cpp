//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "covarmn.h"
#include "matrix.hpp"
#include "math1.hpp"
#include "math2.hpp"
#include "stdlib.h"
#include "stdio.h"
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
#pragma link "Grids"
#pragma link "Matrix"
#pragma link "Math1"
#pragma link "Math2"
#pragma link "matrix"
#pragma resource "*.dfm"
TForm1 *Form1;
const int InMatCols=4;
const int InMatRows=31;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SButExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButClearClick(TObject *Sender)
{
InMat->Fill(0);
CalcOutMatrix();
LoadStringGrids();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButFillClick(TObject *Sender)
{
int  i,j;

for (i=1; i<=SGInMat->ColCount; i++)
  {
  for (j=1; j<=SGInMat->RowCount; j++)
    {
    InMat->Elem[i][j] = 0.01*random(100);
    }
  }
CalcOutMatrix();
LoadStringGrids();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBScatterClick(TObject *Sender)
{
CalcOutMatrix();
LoadStringGrids();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBCovarClick(TObject *Sender)
{
CalcOutMatrix();
LoadStringGrids();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RBCorrelClick(TObject *Sender)
{
CalcOutMatrix();
LoadStringGrids();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SGInMatKeyPress(TObject *Sender, char &Key)
{
int ix, iy;
double ddummy1;
AnsiString AuxStr;

if (Key == 0x0d)
  {
  ix = SGInMat->Selection.Left;
  iy = SGInMat->Selection.Top;
  AuxStr = SGInMat->Cells[ix][iy];
  if (AuxStr != "")
    {
    ddummy1 = AuxStr.ToDouble();
    InMat->Elem[ix][iy] = ddummy1;
    }
  CalcOutMatrix();
  LoadStringGrids();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
int  i,j;

OutMat->Resize (InMatCols,InMatCols);
InMat->Resize (InMatCols,InMatRows);

for (i=1; i<=SGInMat->ColCount; i++)
  {
  for (j=1; j<=SGInMat->RowCount; j++)
    {
    InMat->Elem[i][j] = 0.01*random(100);
    }
  }
CalcOutMatrix();
LoadStringGrids();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadStringGrids()
{
int i,j;
char astr[20];

for (i=1; i<=SGInMat->ColCount; i++)
  {
  sprintf (astr, "C%1d", i);
  SGInMat->Cells[i][0] = astr;
  }
for (i=1; i<=SGInMat->RowCount; i++)
  {
  sprintf (astr, "R%1d", i);
  SGInMat->Cells [0][i] = astr;
  }
for (i=1; i<=SGInMat->ColCount; i++)
  {
  for (j=1; j<=SGInMat->RowCount; j++)
    {
    sprintf (astr, "%1.3f", InMat->Elem[i][j]);
    SGInMat->Cells [i][j] = astr;
    }
  }
for (i=1; i<=SGOutMat->ColCount; i++)
  {
  sprintf (astr, "C%1d", i);
  SGOutMat->Cells [i][0] = astr;
  }
for (i=1; i<=SGOutMat->RowCount; i++)
  {
  sprintf (astr, "R%1d", i);
  SGOutMat->Cells [0][i] = astr;
  }
for (i=1; i<=SGOutMat->ColCount; i++)
  {
  for (j=1; j<=SGOutMat->RowCount; j++)
    {
    sprintf (astr, "%1.3f", OutMat->Elem[i][j]);
    SGOutMat->Cells [i][j] = astr;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CalcOutMatrix()
{
if (RBScatter->Checked == TRUE)
  {
  CalcCovar (InMat, OutMat, 1, InMat->NrOfColumns, 1, InMat->NrOfRows, 0);
  }
if (RBCovar->Checked == TRUE)
  {
  CalcCovar (InMat, OutMat, 1, InMat->NrOfColumns, 1, InMat->NrOfRows, 1);
  }
if (RBCorrel->Checked ==TRUE)
  {
  CalcCovar (InMat, OutMat, 1, InMat->NrOfColumns, 1, InMat->NrOfRows, 2);
  }
}
