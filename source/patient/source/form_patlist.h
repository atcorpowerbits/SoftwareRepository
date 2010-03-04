//---------------------------------------------------------------------------
#ifndef form_patlistH
#define form_patlistH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Qrctrls.hpp>
#include <quickrpt.hpp>
#include <QuickRpt.hpp>
#include <QRCtrls.hpp>
//---------------------------------------------------------------------------
class Tfrm_patlist : public TForm
{
__published:	// IDE-managed Components
    TQuickRep *qckrp_pat_list;
    TQRBand *DetailBand1;
    TQRBand *PageFooterBand1;
    TQRBand *PageHeaderBand1;
    TQRBand *TitleBand1;
    TQRDBText *qrdb_surname;
    TQRDBText *qrdb_firstname;
    TQRLabel *QRLabel1;
    TQRDBText *qrdb_dob;
    TQRLabel *qrlbl_records;
    TQRBand *ColumnHeaderBand1;
    TQRLabel *QRLabel2;
    TQRLabel *QRLabel3;
    TQRLabel *QRLabel4;
    TQRLabel *QRLabel5;
    TQRLabel *qrlbl_db_details;
    TQRSysData *QRSysData1;
    TQRLabel *qrlbl_totals;
    TQRLabel *qrlbl_first_title;
    TQRLabel *qrlbl_first;
    TQRLabel *qrlbl_last;
    TQRLabel *qrlbl_last_title;
    void __fastcall qrbnd_sdetail_measuresBeforePrint(
          TQRCustomBand *Sender, bool &PrintBand);
    
    
    
    void __fastcall qckrp_pat_listPreview(TObject *Sender);
private:	// User declarations

public:		// User declarations
    __fastcall Tfrm_patlist(TComponent* Owner);
    __fastcall bool report_patlist_setup(void);
    __fastcall void report_patlist_cleanup(void);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_patlist *frm_patlist;

//---------------------------------------------------------------------------
#endif
