/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxPrinter.h
        
     Author       :		 Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting Printer namespace
*/

#pragma once

using namespace System;
using namespace System::Drawing;				
using namespace System::Drawing::Printing;



/**
 * @namespace	AtCor::Scor::CrossCutting::Printer
 * @brief		This namespace implements printer related functionality.
 * 
 */
namespace AtCor { namespace Scor { namespace CrossCutting { namespace Printer
{	

	// Declaring global static numbers for structure variables
	/**
	* @struct CrxPrintValue
	 * @brief Container for Print value to handle enum. 
	 */
	public ref struct CrxPrinterSetting
	{
		
		static const int LineCount		= 1;
		static const int LineHeight		= 14;
		static const int FontSize		= 10;
		static String^ const FontType	= "Arial";

	};

	/**
	* @class CrxPrintManager
	* @brief Class to manage printer related functions. @n
	* This Class is mainly responsible for maintaining printing forms @n
	* It has methods that enable print and set printer in to specific sections of configuration file.
	*/
	public ref class CrxPrintManager
	{

	private:

		//singleton instance
		static CrxPrintManager^ _instance = gcnew CrxPrintManager();
		String^ _printString ;
		Image^ _imgPrint;
		
		/**
		* Default Constructor
		*/
		CrxPrintManager()
		{	
			
		}

		/**
		* Copy Constructor
		*/
		CrxPrintManager(const CrxPrintManager^)
		{
			
		}
		
		/**
		* Assignment Operator
		*/
		CrxPrintManager^ operator=(const CrxPrintManager^) 
		{
			 return this;
		}  

		void AtCorPrintAboutBoxFormat(Object^ sender, PrintPageEventArgs^ e);

	public:

		/**
		* Singleton Instance property with Only Get accessor
		*/
		static property CrxPrintManager^ Instance
		{
			CrxPrintManager^ get()
			{
				return CrxPrintManager::_instance;
			};
		};

		/**
		* To print the about box screen
		*
		* @param[in] prnStr		string to handle the text to be printed
		* @param[in] imgPrint	image object to handle image to be printed.
		*/
		void AtCorPrintAboutBox(String^ prnStr, Image^ imgPrint);
	};
}
}
}
}