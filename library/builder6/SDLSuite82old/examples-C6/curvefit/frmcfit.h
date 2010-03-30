//---------------------------------------------------------------------------
#ifndef frmcfitH
#define frmcfitH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "NumLab.hpp"
#include "RChart.hpp"
#include "cspin.h"
#include "CSPIN.h"
#include "rchart.hpp"
#include "math2.hpp"
#include "numlab.hpp"
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
        TSpeedButton *SBNewPnts;
        TNumLab *NLabFitQual;
        TSpeedButton *SBClear;
        TLabel *LblFormula;
        TLabel *LblParams;
        TPanel *Panel2;
        TSpeedButton *BButParabolFit;
        TSpeedButton *BButCalcReciprLine;
        TSpeedButton *BButHyper;
        TSpeedButton *BButLogFit;
        TSpeedButton *BButGaussFit;
        TSpeedButton *BButLinFit;
        TBitBtn *BButExit;
        TRChart *RChart1;
        TLabel *LblPolyOrder;
        TSpeedButton *BButPolynomial;
        TCSpinEdit *SEPolyOrder;
        TCurveFit *Stats1;
        TSpeedButton *BButSpline;
        TLabel *LblSmoothSpline;
        TScrollBar *SBarSmoothSpline;
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall SBClearClick(TObject *Sender);
        void __fastcall RChart1MouseDown(TObject *Sender, TMouseButton Button,
        TShiftState Shift, int X, int Y);
        void __fastcall SBNewPntsClick(TObject *Sender);
        void __fastcall BButParabolFitClick(TObject *Sender);
        void __fastcall BButCalcReciprLineClick(TObject *Sender);
        void __fastcall BButHyperClick(TObject *Sender);
        void __fastcall BButLogFitClick(TObject *Sender);
        void __fastcall BButGaussFitClick(TObject *Sender);
        void __fastcall BButLinFitClick(TObject *Sender);
        void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
        void __fastcall BButPolynomialClick(TObject *Sender);
        void __fastcall SEPolyOrderChange(TObject *Sender);
        void __fastcall BButSplineClick(TObject *Sender);
        void __fastcall SBarSmoothSplineChange(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
private:        // User declarations
        void __fastcall DisableElements();
        void __fastcall ShowSpline();
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
