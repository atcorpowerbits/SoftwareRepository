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

using namespace AtCor::Scor::CrossCutting::Printer;

void CrxPrintManager::AtCorPrintAboutBox(String^ strPrn, Image^ imgPrn)
{
	try
	{
		CrxConfigManager^ objCrx = CrxConfigManager::Instance;

		PrintDocument^ printDocument = gcnew PrintDocument();
		CrxStructGeneralSetting^ gs = gcnew CrxStructGeneralSetting();
	    
		CrxPrintManager::_printString = strPrn;
		CrxPrintManager::_imgPrint = imgPrn;	

		objCrx->GetGeneralUserSettings();
		gs = objCrx->GeneralSettings;
		printDocument->PrinterSettings->PrinterName = gs->PrinterName; 

	
		printDocument->PrintPage += gcnew PrintPageEventHandler(this, &CrxPrintManager::AtCorPrintAboutBoxFormat);             
		 
		printDocument->Print();   		
	}
	catch(Exception^ eObj)
	{		
		throw gcnew ScorException(eObj);
	}
}

void CrxPrintManager::AtCorPrintAboutBoxFormat(Object^ , PrintPageEventArgs^ e)
{
	int start				=	0;
	int top					=	0;
	int lineHeight			=	0;
	int lineCount			=	0;
	float lineTop			=	0; 
	float lineLeft			=	0;		
	Brush^ brush			=	nullptr;    
	String^ prnStr			=	nullptr;
	Font^ prnFont			=	nullptr;
	Image^ imgPrint			=	nullptr;

	try
	{
		//Setting the color as Black.
		brush = Brushes::Black;    

		//Using default font as Arial, size 10
		//Setting the font and size as Arial(10).
		prnFont = gcnew Font(CrxPrinterSetting::FontType,Convert::ToSingle(CrxPrinterSetting::FontSize,CrxCommon::gCI));
		
		//Assigning actual string into variable
		prnStr = CrxPrintManager::_printString;
		imgPrint = CrxPrintManager::_imgPrint;

		//Initializing the varibales
		lineHeight = Convert::ToInt32(CrxPrinterSetting::LineHeight,CrxCommon::gCI);
		lineCount = Convert::ToInt32(CrxPrinterSetting::LineCount,CrxCommon::gCI);
		lineTop = Convert::ToSingle(e->MarginBounds.Top);        
		lineLeft = Convert::ToSingle(e->MarginBounds.Left);
		
		while ((start = prnStr->IndexOf('\n', start)) != -1)
		{
			lineCount++;
			start++;
		}

		top = e->MarginBounds.Top + (lineCount * lineHeight);	
	
		e->Graphics->DrawString(prnStr, prnFont, brush, lineLeft, lineTop);        
		e->Graphics->DrawImage(imgPrint,int(lineLeft),top);
	}
	catch(Exception^ eObj)
	{		
		throw gcnew ScorException(eObj);
	}
}
