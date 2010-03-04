//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include <stdio.h>

#include "frmmain.h"
#include "sdlcolors.hpp"
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
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SBarIntensChange(TObject *Sender)
{
int r,g,b;
TColor  col1;

HSItoRGB (SBarHue->Position, 0.01*SBarSat->Position, 0.01*SBarIntens->Position, r, g, b);
PnlColor->Color = RGB(r,g,b);
LblHue->Caption = IntToStr (SBarHue->Position);
LblSat->Caption = IntToStr (SBarSat->Position);
LblIntens->Caption = IntToStr (SBarIntens->Position);
LblRed->Caption = IntToStr (r);
LblGreen->Caption = IntToStr (g);
LblBlue->Caption = IntToStr (b);
PnlRed->Color = r;
PnlGreen->Color = 256*g;
PnlBlue->Color = 65536*b;
EdHTML->Text = "#"+Sysutils::IntToHex((int) RGB(b,g,r), 6);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::FormShow(TObject *Sender)
{
SBarIntensChange(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButInvertClick(TObject *Sender)
{
  int     r,g,b;
  double  h,s,i;

HSItoRGB (SBarHue->Position, 0.01*SBarSat->Position, 0.01*SBarIntens->Position, r, g, b);
r = 255-r;
g = 255-g;
b = 255-b;
RGBtoHSI (r, g, b, h, s, i);
SBarHue->Position = ceil(h);
SBarSat->Position = ceil(s*100);
SBarIntens->Position = ceil(i*100);
}
//---------------------------------------------------------------------------
