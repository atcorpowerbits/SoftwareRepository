//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "ureplist.h"
#include "stdlib.h"
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
#pragma link "replist"
#pragma link "Grids"
#pragma link "Colsel"
#pragma link "colsel"
#pragma resource "*.dfm"
TForm1 *Form1;

const
  System::ShortString FirstNames[20] =
                  {"John","Jack","Jill","Pat","Morgan",
                   "Robert","Hugh","Thomas","Alex","Dave",
                   "Jeffrey","Mark","Buddy","Vince","Cliff",
                   "Claudia","Sally","Elizabeth","Gail","Michael"};
  AnsiString LastNames [20] =
                  {"Hayek","Braaten","Lohninger","Arsenna","Mortensen",
                   "Miller","Stewart","Collaud","Bergh","Wiles",
                   "Bock","Stefferson","Nilsson","Johansson","Horvath",
                   "Christiansen","Maltese","Wilson","Churchill","Clinton"};
  AnsiString Addresses [20] =
                  {"Bollene, France","Vienna, Austria","Amsterdam, The Netherlands","Austin, Texas","Milton, Australia",
                   "Ikast, Denmark","Heidenheim, Germany","Richmond, California","Vail, Colorado","Cape Town, RSA",
                   "Berlin, Germany","Rio, Brazil","Takasaki, Japan","Stockholm, Sweden","Budapest, Hungary",
                   "Barcelona, Spain","Taipei, Taiwan","New Orleans, USA","Moscow, Russia","Auckland, New Zealand"};

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
void __fastcall TForm1::BButAddRowClick(TObject *Sender)
{
int i;
int ix;

if (Replist::IsLightEd && (RL1->NrOfRows >= 300))
  {
  BButAddRow->Enabled = false;
  }
else
  {
  RL1->SuppressPaint=true;
  for (i=1;i<100;i++)
    {
    ix=RL1->AddRow();
    RL1->Elem[1][ix] = IntToStr(ix);
    RL1->Elem[2][ix] = FirstNames[random(20)];
    RL1->Elem[3][ix] = LastNames[random(20)];
    RL1->Elem[4][ix] = Addresses[random(20)];
    }
  RL1->SuppressPaint = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButUnsortClick(TObject *Sender)
{
RL1->UnSort();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSTextChange(TObject *Sender)
{
RL1->ColorText = CSText->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSBkg1Change(TObject *Sender)
{
RL1->ColorBkgdNormal = CSBkg1->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CSBkg2Change(TObject *Sender)
{
RL1->ColorBkgdShaded = CSBkg2->SelColor;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
if (ColorDialog1->Execute())
  {
  CSBkg1->SelColor = ColorDialog1->Color;
  RL1->ColorBkgdNormal = ColorDialog1->Color;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
if (ColorDialog1->Execute())
  {
  CSBkg2->SelColor = ColorDialog1->Color;
  RL1->ColorBkgdShaded = ColorDialog1->Color;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SBarRowPatChange(TObject *Sender)
{
RL1->RowColPattern = SBarRowPat->Position;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBVertLinesClick(TObject *Sender)
{
if (CBVertLines->Checked)
  {
  RL1->Options = RL1->Options << goVertLine;
  }
  else
  {
  RL1->Options = RL1->Options >> goVertLine;
  }
RL1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::CBHorzLinesClick(TObject *Sender)
{
if (CBHorzLines->Checked)
  {
  RL1->Options = RL1->Options << goHorzLine;
  }
  else
  {
  RL1->Options = RL1->Options >> goHorzLine;
  }
RL1->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormShow(TObject *Sender)
{
int i;

RL1->SuppressPaint = true;
RL1->Header[1] = "Cust.No.";
RL1->Header[2] = "First Name";
RL1->Header[3] = "Last Name";
RL1->Header[4] = "Address";
for (i=1; i<RL1->NrOfRows; i++)
  {
  RL1->Elem[1][i] = IntToStr(i);
  RL1->Elem[2][i] = FirstNames[random(20)];
  RL1->Elem[3][i] = LastNames[random(20)];
  RL1->Elem[4][i] = Addresses[random(20)];
  }
RL1->SuppressPaint = false;
CSText->SelColor = RL1->ColorText;
CSBkg1->SelColor = RL1->ColorBkgdNormal;
CSBkg2->SelColor = RL1->ColorBkgdShaded;
}
//---------------------------------------------------------------------------
