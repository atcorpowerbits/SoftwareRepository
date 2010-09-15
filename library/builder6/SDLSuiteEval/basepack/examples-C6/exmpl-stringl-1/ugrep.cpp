//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop

#include "ugrep.h"
#include "stringl.hpp"
#include "fstream.h"
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
#pragma link "stringl"
#pragma resource "*.dfm"
TForm1 *Form1;
TGrep *SearchStr = new TGrep();
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
void __fastcall TForm1::CBIgnoreCaseClick(TObject *Sender)
{
if (CBIgnoreCase->Checked)
  {
  SearchStr->IgnoreCase = true;
  }
else
  {
  SearchStr->IgnoreCase = false;
  }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::BButStartSearchClick(TObject *Sender)
{
ifstream   InFile;
char       astr[2000];
int        ix;
int        linecnt;

SearchStr->RegExp = EdRegexp->Text;
MMResult->Clear();
if (OpenDialog1->Execute())
  {
  InFile.open (OpenDialog1->FileName.c_str());
  linecnt = 0;
  MMResult->Visible = false;
  while (!InFile.eof())
    {
    InFile.getline (astr, 2000);
    linecnt++;
    if (SearchStr->MatchString (astr, ix))
      {
      MMResult->Lines->Add (IntToStr(linecnt)+": "+astr);
      }
    }
  MMResult->Visible = true;
  InFile.close();
  };
}
//---------------------------------------------------------------------------
