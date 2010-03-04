//---------------------------------------------------------------------------

#ifndef frmmainH
#define frmmainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "numlab.hpp"
#include "rchart.hpp"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TNumLab *NLabArea;
        TNumLab *NLabPoints;
        TButton *ButNewPoints;
        TScrollBar *SBarNPoints;
        TRChart *RChart1;
        void __fastcall ButNewPointsClick(TObject *Sender);
        void __fastcall SBarNPointsChange(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
