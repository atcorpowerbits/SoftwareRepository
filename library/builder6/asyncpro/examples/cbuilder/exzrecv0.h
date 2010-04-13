// ***** BEGIN LICENSE BLOCK *****
// * Version: MPL 1.1
// *
// * The contents of this file are subject to the Mozilla Public License Version
// * 1.1 (the "License"); you may not use this file except in compliance with
// * the License. You may obtain a copy of the License at
// * http://www.mozilla.org/MPL/
// *
// * Software distributed under the License is distributed on an "AS IS" basis,
// * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// * for the specific language governing rights and limitations under the
// * License.
// *
// * The Original Code is TurboPower Async Professional
// *
// * The Initial Developer of the Original Code is
// * TurboPower Software
// *
// * Portions created by the Initial Developer are Copyright (C) 1991-2002
// * the Initial Developer. All Rights Reserved.
// *
// * Contributor(s):
// *
// * ***** END LICENSE BLOCK *****

/*********************************************************/
/*                      EXZRECV0.H                       */
/*********************************************************/
//---------------------------------------------------------------------------
#ifndef exzrecv0H
#define exzrecv0H
//---------------------------------------------------------------------------
#include <vcl\Classes.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include "AdPort.hpp"
#include "AdProtcl.hpp"
#include "AdPStat.hpp"
#include "OoMisc.hpp"
#include "ADTrmEmu.hpp"
#include "AdTapi.hpp"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *Button1;
	TApdComPort *ApdComPort1;
	TApdProtocol *ApdProtocol1;
	TApdProtocolStatus *ApdProtocolStatus1;
    TAdTerminal *AdTerminal1;
        TApdTapiDevice *ApdTapiDevice1;
	void __fastcall ApdProtocol1ProtocolFinish(TObject *CP, int ErrorCode);
	void __fastcall ApdComPort1TriggerData(TObject *CP, WORD TriggerHandle);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall ApdTapiDevice1TapiPortOpen(TObject *Sender);
private:	// User declarations
	Word ZModemHandle;
public:		// User declarations
	virtual __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern TForm1 *Form1;
//---------------------------------------------------------------------------
#endif