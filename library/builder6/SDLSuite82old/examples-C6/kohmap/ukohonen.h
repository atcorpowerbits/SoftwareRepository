//---------------------------------------------------------------------------

#ifndef ukohonenH
#define ukohonenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "kohonen.hpp"
#include "ntabed.hpp"
#include "numio.hpp"
#include "numlab.hpp"
#include "rchart.hpp"
#include "vector.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <Tabnotbk.hpp>
#include <TabNotBk.hpp>
//---------------------------------------------------------------------------
class TFrmSom : public TForm
{
__published:	// IDE-managed Components
        TTabbedNotebook *NoteBk;
        TNTabEd *TEData;
        TRChart *RCKohMap;
        TPanel *Panel1;
        TNumLab *NLAlpha;
        TNumLab *NLSteps;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TBitBtn *BButExit;
        TBitBtn *BButLoad;
        TBitBtn *BButTrainIt;
        TScrollBar *SBAlpha;
        TScrollBar *SBSteps;
        TNumIO *NIOysize;
        TNumIO *NIOxsize;
        TNumIO *NIONeighb;
        TBitBtn *BButStoreNet;
        TBitBtn *BButLoadNet;
        TBitBtn *BButContTrain;
        TOpenDialog *OpenDialog1;
        TKohonen *KohMap1;
        TVector *RowVect;
        TSaveDialog *SaveDialog1;
        void __fastcall BButExitClick(TObject *Sender);
        void __fastcall BButLoadClick(TObject *Sender);
        void __fastcall BButTrainItClick(TObject *Sender);
        void __fastcall SBAlphaChange(TObject *Sender);
        void __fastcall SBStepsChange(TObject *Sender);
        void __fastcall BButStoreNetClick(TObject *Sender);
        void __fastcall BButLoadNetClick(TObject *Sender);
        void __fastcall BButContTrainClick(TObject *Sender);
        void __fastcall KohMap1Feedback(TObject *Sender, int PercentDone);
private:	// User declarations
        void _fastcall ShowCurrentNetResponse();
public:		// User declarations
        __fastcall TFrmSom(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmSom *FrmSom;
//---------------------------------------------------------------------------
#endif
