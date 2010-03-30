//---------------------------------------------------------------------------

#ifndef usharedH
#define usharedH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "rchart.hpp"
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TLabel *Label1;
        TBitBtn *Exit;
        TScrollBar *SBNoise;
        TPanel *Panel2;
        TRChart *RChart1;
        TPanel *Panel3;
        TSplitter *Splitter1;
        TRChart *RChart2;
        TRChart *RChart3;
        void __fastcall ExitClick(TObject *Sender);
        void __fastcall SBNoiseChange(TObject *Sender);
        void __fastcall RChart2ZoomPan(TObject *Sender);
        void __fastcall RChart3ZoomPan(TObject *Sender);
        void __fastcall RChart1CrossHairMove(TObject *Sender,
          TCrossHair *WhichCrossHair);
        void __fastcall FormShow(TObject *Sender);
private:
        void __fastcall DrawData();
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
