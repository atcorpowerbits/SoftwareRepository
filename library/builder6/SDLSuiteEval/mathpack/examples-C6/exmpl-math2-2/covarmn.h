//---------------------------------------------------------------------------
#ifndef covarmnH
#define covarmnH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "Grids.hpp"
#include "matrix.hpp"
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
        TPanel *Panel1;
        TSpeedButton *SButExit;
        TStringGrid *SGInMat;
        TLabel *Label2;
        TButton *ButClear;
        TButton *ButFill;
        TGroupBox *GroupBox1;
        TRadioButton *RBScatter;
        TRadioButton *RBCovar;
        TRadioButton *RBCorrel;
        TStringGrid *SGOutMat;
        TMatrix *OutMat;
        TMatrix *InMat;
        void __fastcall SButExitClick(TObject *Sender);
        void __fastcall ButClearClick(TObject *Sender);
        void __fastcall ButFillClick(TObject *Sender);
        void __fastcall RBScatterClick(TObject *Sender);
        void __fastcall RBCovarClick(TObject *Sender);
        void __fastcall RBCorrelClick(TObject *Sender);
        void __fastcall SGInMatKeyPress(TObject *Sender, char &Key);
        void __fastcall FormActivate(TObject *Sender);
private:        // User declarations
        void __fastcall LoadStringGrids();
        void __fastcall CalcOutMatrix();
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
