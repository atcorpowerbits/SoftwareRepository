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


void CrxPrintManager::AtCorPrintDocument(String^ strPrn, Image^ imgPrn)
{
	try
	{
		CrxConfigManager^ objCrx = CrxConfigManager::Instance;

		PrintDocument^ printDocument = gcnew PrintDocument();
		CrxStructGeneralSetting^ gs = gcnew CrxStructGeneralSetting();
	    
		CrxPrintManager::printString = strPrn;
		CrxPrintManager::imgPrint = imgPrn;	

		objCrx->GetGeneralUserSettings();
		gs = objCrx->GeneralSettings;
		printDocument->PrinterSettings->PrinterName = gs->PrinterName; 

	
		printDocument->PrintPage += gcnew PrintPageEventHandler(this, &CrxPrintManager::AtCorPrintStatus);             
		 
		printDocument->Print();   		
	}
	catch(Exception^ eObj)
	{		
		throw gcnew ScorException(eObj);
	}
}

void CrxPrintManager::AtCorPrintStatus(Object^ sender, PrintPageEventArgs^ e)
{
	int start				=	0;
	int top					=	0;
	int lineHeight			=	14;
	int lineCount			=	1;
	float lineTop			=	0; 
	float lineLeft			=	0;		
	Brush^ brush			=	nullptr;    
	String^ prnStr			=	nullptr;
	Font^ prnFont			=	nullptr;
	Image^ imgPrint			=	nullptr;

	//Setting the color as Black.
	brush = Brushes::Black;    

	//Using default font as Arial, size 10
	//Setting the font and size as Arial(10).
	prnFont = gcnew Font("Arial",10);
	
	//Assigning actual string into variable
	prnStr = CrxPrintManager::printString;
	imgPrint = CrxPrintManager::imgPrint;

	lineTop = Convert::ToSingle(e->MarginBounds.Top) ;        
	lineLeft = Convert::ToSingle(e->MarginBounds.Left);
	
    while ((start = prnStr->IndexOf('\n', start)) != -1)
    {
        lineCount++;
        start++;
    }

	top = e->MarginBounds.Top + (lineCount * lineHeight);
	
	try
	{
		e->Graphics->DrawString(prnStr, prnFont, brush, lineLeft, lineTop);        
		e->Graphics->DrawImage(imgPrint,int(lineLeft),top);
	}
	catch(Exception^ eObj)
	{		
		throw gcnew ScorException(eObj);
	}
}
