//---------------------------------------------------------------------------
#ifndef frmneedlH
#define frmneedlH
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "Meter.hpp"
#include <vcl\Buttons.hpp>
#include "Colsel.hpp"
#include "colsel.hpp"
#include "meter.hpp"
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
class TFrmNeedLayout : public TForm
{
__published:    // IDE-managed Components
        TMeter *Meter1;
        TBitBtn *BButOK;
        TLabel *Label3;
        TScrollBar *SBThickness;
        TLabel *Label4;
        TScrollBar *SBNHeadAngle;
        TLabel *Label6;
        TScrollBar *SBNHeadMidLeng;
        TLabel *Label5;
        TScrollBar *SBNHeadSize;
        TLabel *Label1;
        TColSel *CSNeedleBody;
        TLabel *Label2;
        TColSel *CSNeedleOutline;
        TBitBtn *BitBtn1;
        void __fastcall SBThicknessChange(TObject *Sender);
        void __fastcall SBNHeadAngleChange(TObject *Sender);
        void __fastcall SBNHeadMidLengChange(TObject *Sender);
        void __fastcall SBNHeadSizeChange(TObject *Sender);

        void __fastcall CSNeedleBodyChange(TObject *Sender);
        void __fastcall CSNeedleOutlineChange(TObject *Sender);
private:        // User declarations
public:         // User declarations
        __fastcall TFrmNeedLayout(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TFrmNeedLayout *FrmNeedLayout;
//---------------------------------------------------------------------------
#endif
