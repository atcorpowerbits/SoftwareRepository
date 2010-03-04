//---------------------------------------------------------------------------
#ifndef mainfrmH
#define mainfrmH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Buttons.hpp>
#include "RChart.hpp"
#include "Fourier.hpp"
#include "rchart.hpp"
#include "fourier.hpp"
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
class TForm1 : public TForm
{
__published:    // IDE-managed Components
        TScrollBar *ScrollBar1;
        TScrollBar *ScrollBar2;
        TScrollBar *ScrollBar3;
        TScrollBar *ScrollBar4;
        TScrollBar *ScrollBar5;
        TScrollBar *ScrollBar6;
        TScrollBar *ScrollBar7;
        TScrollBar *ScrollBar8;
        TScrollBar *ScrollBar10;
        TScrollBar *ScrollBar11;
        TScrollBar *ScrollBar12;
        TScrollBar *ScrollBar13;
        TScrollBar *ScrollBar14;
        TScrollBar *ScrollBar15;
        TScrollBar *ScrollBar16;
        TLabel *Label1;
        TBitBtn *BButSquare;
        TBitBtn *BButHalfSine;
        TBitBtn *BButTriangle;
        TBitBtn *BButSaw;
        TBitBtn *BButExit;
        TBitBtn *BButReset;
        TRChart *RChart1;
        TFastFourier *FastFourier1;
        void __fastcall ScrollBar1Change(TObject *Sender);
        void __fastcall BButResetClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BButSquareClick(TObject *Sender);
        void __fastcall BButSawClick(TObject *Sender);
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall BButHalfSineClick(TObject *Sender);
        void __fastcall BButTriangleClick(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
