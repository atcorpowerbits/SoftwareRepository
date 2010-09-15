//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "FMatrix.h"
#include "matrix.hpp"
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
#pragma link "matrix"
#pragma resource "*.dfm"
const int MatSize=6;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButDoneClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButClearClick(TObject *Sender)
{
Mat1->Fill(0.0);
LoadStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButFillClick(TObject *Sender)
{
int i,j;

for (i=1; i<=MatSize; i++)
  {
  for (j=1; j<=MatSize; j++)
    {
    Mat1->Elem[i][j] = 0.1*random(100) - 5;
    }
  }
LoadStringGrid();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButInvertClick(TObject *Sender)
{
if (Mat1->Invert() == TRUE)
  {
  LoadStringGrid();
  }
else
  {
  char buffer[80];
  sprintf (buffer,"ERROR during inversion of matrix");
  MessageDlg (buffer, mtInformation, TMsgDlgButtons() << mbOK, 0);
  Mat1->Fill (0.0);
  LoadStringGrid();
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
int        i,j;
double     AuxVal;
char       astr[20];

Mat1->Resize(MatSize,MatSize);
SGMat->DefaultColWidth = 64;
for (i=1; i<=MatSize; i++)
  {
  for (j=1; j<=MatSize; j++)
    {
    AuxVal = 0.1*random(100) - 5;
    sprintf (astr, "%1.2f", AuxVal);
    SGMat->Cells[i-1][j-1] = astr;
    Mat1->Elem[i][j] = AuxVal;
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::LoadStringGrid()
{
int  i,j;
char astr[20];

for (i=1; i<=MatSize; i++)
  {
  for (j=1; j<=MatSize; j++)
    {
    sprintf (astr, "%1.2f", Mat1->Elem[i][j]);
    SGMat->Cells[i-1][j-1] = astr;
    }
  }
}
//---------------------------------------------------------------------------