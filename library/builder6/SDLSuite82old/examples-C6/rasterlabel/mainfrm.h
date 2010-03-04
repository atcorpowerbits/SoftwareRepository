//---------------------------------------------------------------------------

#ifndef mainfrmH
#define mainfrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "rasterlab.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmMain : public TForm
{
__published:	// IDE-managed Components
        TRasterLab *RLab1;
        TTimer *Timer1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall RLab1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall RLab1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
private:	// User declarations
public:		// User declarations
        __fastcall TFrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmMain *FrmMain;
//---------------------------------------------------------------------------
#endif
