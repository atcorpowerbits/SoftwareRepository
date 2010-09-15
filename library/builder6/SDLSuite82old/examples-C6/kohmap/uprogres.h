//---------------------------------------------------------------------------

#ifndef uprogresH
#define uprogresH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "meter.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFrmProgress : public TForm
{
__published:	// IDE-managed Components
        TMeter *Meter;
        TBitBtn *BButAbort;
        TCheckBox *CBShowTraining;
        void __fastcall BButAbortClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFrmProgress(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmProgress *FrmProgress;
//---------------------------------------------------------------------------
#endif
