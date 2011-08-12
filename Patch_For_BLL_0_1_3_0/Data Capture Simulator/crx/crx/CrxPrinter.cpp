/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxPrinter.h
        
     Author       :		 Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting Printer namespace
*/

#include "stdafx.h"
#include "CrxCrossCutting.h"
#include "ScorException.h"
#include "CrxPrinter.h"

using namespace System;
using namespace System::Text;
using namespace System::Data;
using namespace System::Windows;
using namespace System::Windows::Forms;

using namespace System::Data::Common;
using namespace System::Data::SqlClient;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::ComponentModel;
using namespace System::Data::OleDb;
using namespace System::Drawing;
using namespace System::Drawing::Printing;
using namespace System::Resources;

using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Printer;
using namespace AtCor::Scor::CrossCutting::Configuration; 


void CrxPrintManager::AtCorPrintDocument(String^ strPrn)
{
	CrxConfigManager^ objCrx = CrxConfigManager::Instance;

	PrintDocument^ printDocument = gcnew PrintDocument();
	PrintDialog^ printDialog	= gcnew PrintDialog();
	CrxStructGeneralSetting^ gs = gcnew CrxStructGeneralSetting();
    
	CrxPrintManager::printString = strPrn;
	
	//Setting print dialog properties
	printDialog->ShowNetwork = false;         
	printDialog->Document = printDocument;         
	printDialog->AllowPrintToFile = true;       

	//Disabling advanced options, as printing simple text
	printDialog->AllowCurrentPage = false;         
	printDialog->AllowSelection = false;         
	printDialog->AllowSomePages = false; 
	
	//Display XP Style Print Dialog         
	printDialog->UseEXDialog = true; 
	try
	{
		if (printDialog->ShowDialog() == DialogResult::OK)         
		 {            
			printDocument->PrintPage += gcnew PrintPageEventHandler(this, &CrxPrintManager::AtCorPrintStatus);             
			 
			//Print method call. 
			printDocument->Print();             
		 } 

		//Assigning the Printer settings to the Document.             
		printDocument->PrinterSettings = printDialog->PrinterSettings; 
		
		objCrx->GetGeneralUserSettings();
		gs = objCrx->GeneralSettings;

		//Getting selected printer name into gs
		gs->PrinterName = printDocument->PrinterSettings->PrinterName;

		//Setting printer name in to config file
		objCrx->SetGeneralUserSettings(gs);
	}
	catch(Exception^ eObj)
	{		
		throw gcnew ScorException(eObj);
	}
}

void CrxPrintManager::AtCorPrintStatus(Object^ sender, PrintPageEventArgs^ e)
{
	float lineTop = 0; 
	float lineLeft =0;
	Brush^ brush = nullptr;    
	String^ prnStr = nullptr;
	Font^ prnFont = nullptr;
	Image^ imgPrint = nullptr;

	//Setting the color as Black.
	brush = Brushes::Black;    

	//Using default font as Arial, size 10
	//Setting the font and size as Arial(10).
	prnFont = gcnew Font("Arial",10);
	
	//Assigning actual string into variable
	prnStr = CrxPrintManager::printString;
	
	lineTop = e->MarginBounds.Top ;         
	lineLeft = e->MarginBounds.Left;
	
	try
	{
		e->Graphics->DrawString(prnStr, prnFont, brush, lineLeft, lineTop);        
		
	}
	catch(Exception^ eObj)
	{		
		throw gcnew ScorException(eObj);
	}
}