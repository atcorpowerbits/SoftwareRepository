//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "vector1.h"
#include "vector.hpp"
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
#pragma link "Vector"
#pragma link "vector"
#pragma resource "*.dfm"

const int VecLeng = 20;
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButDVClick(TObject *Sender)
{
Vec1->Free();
Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormActivate(TObject *Sender)
{
int  i;
char buf1[20];

Randomize;
Vec1->NrOfElem = VecLeng;
SG1->RowCount = VecLeng;
SG1->ColCount = 1;
for (i=1; i<=VecLeng; i++)
  Vec1->Elem[i] = i;
for (i=1; i<=VecLeng; i++)
  {
  sprintf (buf1, "%5.2f",Vec1->Elem[i]);
  SG1->Cells[0][i-1] = buf1;
  }
SG1SetEditText (Sender, 0,0,"1.00");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SG1SetEditText(TObject *Sender, int ACol, int ARow,
        const AnsiString Value)
{
double ddummy1;
double ddummy2;
double ddummy3;
AnsiString AuxStr;
char buf1[20];
char buf2[20];

DecimalSeparator = '.';
AuxStr = SG1->Cells[ACol][ARow];
if (AuxStr != "")
  {
  ddummy1 = AuxStr.ToDouble();
  Vec1->Elem[ARow+1] = ddummy1;
  }
sprintf (buf1, "Leng = %1.3f", Vec1->Leng);
LblLeng->Caption = buf1;

Vec1->MeanVar (1, VecLeng, ddummy1, ddummy2);
sprintf (buf1, "Mean = %1.3f", ddummy1);
sprintf (buf2, "Var = %1.3f", ddummy2);
LblMean->Caption = buf1;
LblVar->Caption = buf2;

Vec1->MinMax (1, VecLeng, ddummy1, ddummy2);
sprintf (buf1, "Min = %1.3f", ddummy1);
sprintf (buf2, "Max = %1.3f", ddummy2);
LblMin->Caption = buf1;
LblMax->Caption = buf2;

Vec1->Quartiles (1, VecLeng, ddummy1, ddummy2, ddummy3);
sprintf (buf1, "Q123 = %1.3f   %1.3f   %1.3f", ddummy1, ddummy2, ddummy3);
LblQuart->Caption = buf1;

}
//---------------------------------------------------------------------------
