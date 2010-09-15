//---------------------------------------------------------------------------
#ifndef rot3dataH
#define rot3dataH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "Rot3D.hpp"
#include "NumLab.hpp"
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Dialogs.hpp>
#include "numlab.hpp"
#include "rot3d.hpp"
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
        TRot3D *Rot3D1;
        TScrollBar *ScrollBar4;
        TScrollBar *SBAngX;
        TScrollBar *SBAngY;
        TScrollBar *SBAngZ;
        TNumLab *NLabGamma;
        TNumLab *NLabBeta;
        TNumLab *NLabAlpha;
        TSpeedButton *SBAutoRot;
        TBitBtn *BButExit;
        TNumLab *NumLab4;
        TRadioGroup *RadioGroup1;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TScrollBar *SBBBSize;
        TScrollBar *SBAxSize;
        TCheckBox *CheckBox1;
        TPopupMenu *PopupMenu1;
        TMenuItem *Rotate1;
        TMenuItem *Zoom1;
        TMenuItem *Pan1;
        TMenuItem *copy1;
        TMenuItem *ToClipboard1;
        TMenuItem *ToBMPFile1;
        TSaveDialog *SaveDialog1;
        TCheckBox *CBIsoMetric;
        TBitBtn *BButPrintit;
        TRadioGroup *RGCoordSystem;
        void __fastcall SBAngXChange(TObject *Sender);
        void __fastcall SBAngYChange(TObject *Sender);
        void __fastcall SBAngZChange(TObject *Sender);
        void __fastcall ScrollBar4Change(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall Rot3D1MouseMove(TObject *Sender, TShiftState Shift, int X,
        int Y);
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall RadioButton1Click(TObject *Sender);
        void __fastcall RadioButton2Click(TObject *Sender);
        void __fastcall RadioButton3Click(TObject *Sender);
        void __fastcall CheckBox1Click(TObject *Sender);
        void __fastcall SBAxSizeChange(TObject *Sender);
        void __fastcall Rotate1Click(TObject *Sender);
        void __fastcall Zoom1Click(TObject *Sender);
        void __fastcall Pan1Click(TObject *Sender);

        void __fastcall ToClipboard1Click(TObject *Sender);
        void __fastcall ToBMPFile1Click(TObject *Sender);
        void __fastcall SBBBSizeChange(TObject *Sender);
        void __fastcall SBAutoRotClick(TObject *Sender);
        void __fastcall CBIsoMetricClick(TObject *Sender);
        void __fastcall BButPrintitClick(TObject *Sender);
        void __fastcall Rot3D1MouseDown(TObject *Sender, TMouseButton Button,
        TShiftState Shift, int X, int Y);
        void __fastcall Rot3D1MouseUp(TObject *Sender, TMouseButton Button,
        TShiftState Shift, int X, int Y);
        void __fastcall RGCoordSystemClick(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
