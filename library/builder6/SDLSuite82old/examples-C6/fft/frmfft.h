//---------------------------------------------------------------------------
#ifndef frmfftH
#define frmfftH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "Fourier.hpp"
#include <vcl\Buttons.hpp>
#include "RChart.hpp"
#include <ExtCtrls.hpp>
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
        TLabel *Label1;
        TLabel *Label2;
        TScrollBar *SBFreq1;
        TScrollBar *ScrollBar1;
        TFastFourier *FFT1;
        TLabel *Label3;
        TComboBox *CBoxWind;
        TCheckBox *CBLogY;
        TBitBtn *BButExit;
        TRChart *RChart2;
        TRChart *RChart1;
        TRadioGroup *RGSpecType;
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall CBoxWindChange(TObject *Sender);
        void __fastcall ScrollBar1Change(TObject *Sender);
        void __fastcall SBFreq1Change(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall CBLogYClick(TObject *Sender);
        void __fastcall RGSpecTypeClick(TObject *Sender);
private:        // User declarations
        void __fastcall StartFFT();
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
