//---------------------------------------------------------------------------
#ifndef frmmeterH
#define frmmeterH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include "NumLab.hpp"
#include "Meter.hpp"
#include "Colsel.hpp"
#include <vcl\Dialogs.hpp>
#include "colsel.hpp"
#include "meter.hpp"
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
        TSpeedButton *SBExit;
        TNumLab *NumLab1;
        TLabel *Label8;
        TScrollBar *SBValue;
        TMeter *Meter1;
        TMeter *Meter3;
        TMeter *Meter2;
        TLabel *Label3;
        TColSel *CSMeterBkgnd;
        TLabel *Label4;
        TColSel *CSColorCover;
        TLabel *Label1;
        TColSel *CSColorScale;
        TLabel *Label2;
        TColSel *CSColorText;
        TSpeedButton *SBColBak;
        TGroupBox *GroupBox2;
        TLabel *Label6;
        TLabel *Label7;
        TScrollBar *SBMaxVal;
        TScrollBar *SBMinVal;
        TGroupBox *GroupBox1;
        TRadioButton *RBRaised;
        TRadioButton *RBLowered;
        TRadioButton *RbEmbossed;
        TRadioButton *RBEngraved;
        TRadioButton *RBSimple;
        TRadioButton *RBNone;
        TLabel *Label5;
        TEdit *EdCaption;
        TCheckBox *CBShortTicks;
        TCheckBox *CBScaleLine;
        TCheckBox *CBLimHigh;
        TCheckBox *CBLimLow;
        TBitBtn *BButNeedleLayout;
        TColorDialog *ColorDialog1;
        TGroupBox *GroupBox3;
        TLabel *Label9;
        TLabel *Label10;
        TScrollBar *SBThreshHigh;
        TScrollBar *SBThreshLow;
        TCheckBox *CBVisThresh;
        TRadioGroup *RGLayout;
        TBitBtn *BButNeedle2Layout;
        TScrollBar *SBAnchorSize;
        TCheckBox *CBAnchorOn;
        TScrollBar *SBarValue2;
        TLabel *Label11;
        TLabel *LblSecNeedle;
        void __fastcall SBExitClick(TObject *Sender);
        void __fastcall SBValueChange(TObject *Sender);
        void __fastcall CSMeterBkgndChange(TObject *Sender);
        void __fastcall CSColorCoverChange(TObject *Sender);
        void __fastcall CSColorScaleChange(TObject *Sender);
        void __fastcall CSColorTextChange(TObject *Sender);
        void __fastcall RBRaisedClick(TObject *Sender);
        void __fastcall RBLoweredClick(TObject *Sender);
        void __fastcall RbEmbossedClick(TObject *Sender);
        void __fastcall RBEngravedClick(TObject *Sender);
        void __fastcall RBSimpleClick(TObject *Sender);
        void __fastcall RBNoneClick(TObject *Sender);
        void __fastcall SBColBakClick(TObject *Sender);
        void __fastcall SBMinValChange(TObject *Sender);
        void __fastcall SBMaxValChange(TObject *Sender);
        void __fastcall EdCaptionChange(TObject *Sender);
        void __fastcall CBShortTicksClick(TObject *Sender);
        void __fastcall CBScaleLineClick(TObject *Sender);
        void __fastcall CBLimHighClick(TObject *Sender);
        void __fastcall CBLimLowClick(TObject *Sender);
        void __fastcall BButNeedleLayoutClick(TObject *Sender);
        void __fastcall RGLayoutClick(TObject *Sender);
        void __fastcall SBThreshLowChange(TObject *Sender);
        void __fastcall SBThreshHighChange(TObject *Sender);
        void __fastcall CBVisThreshClick(TObject *Sender);
        void __fastcall SBarValue2Change(TObject *Sender);
        void __fastcall SBAnchorSizeChange(TObject *Sender);
        void __fastcall CBAnchorOnClick(TObject *Sender);
        void __fastcall BButNeedle2LayoutClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
