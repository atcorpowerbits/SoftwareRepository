/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxConfiguration.h
        
     Author       :		 Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting Configuration namespace
*/

#pragma once

using namespace System;
using namespace System::Xml;


/**
 * @namespace	CrxConfiguration
 * @brief		This namespace implements configuration related functionality.
 * 
 */
namespace AtCor { namespace Scor { namespace CrossCutting { namespace Configuration
{	
//public:
	//Declaring global static numbers for structure variables
	static const int CRX_GEN_HEIGHTWEIGHT_METRIC	= 0;
	static const int CRX_GEN_HEIGHTWEIGHT_IMPERIAL	= 1;
	static const int CRX_GEN_BP_OPT_SPANDDP			= 0;
	static const int CRX_GEN_BP_OPT_SPANDMP			= 1;
	static const int CRX_GEN_BP_OPT_MPANDDP			= 2;

	static const int CRX_PWV_DIST_UNITS_MM			= 0;
	static const int CRX_PWV_DIST_UNITS_CM			= 1;
	static const int CRX_PWV_DIST_METHOD_SUBSTRACT	= 0;
	static const int CRX_PWV_DIST_METHOD_DIRECT		= 1;
	static const int CRX_PWV_CAPTURE_5SECONDS		= 0;
	static const int CRX_PWV_CAPTURE_10SECONDS		= 1;
	static const int CRX_PWV_CAPTURE_20SECONDS		= 2;	

	// Creating CrxStructSetting Structure and variables
	/**
	 * Container for general configuration settings. 
	 */
	public ref struct CrxStructGeneralSetting
	{
		bool PatientPrivacy; /**< true: if patient privacy is selected, false: if not selcted */
		int HeightandWeightUnit; /**<0 : if metric is selcted, 1: If immperial is selected */
		int BloodPressureEntryOptions; /**<0 : if SP and DP is selected 1:SP and MP is selected 2:MP and DP is selected */
		String^ CommsPort; /**< Shows the string selected */
		String^ ReportTitle;	/**< Shows the report title */
		String^ ReportLogoPath; /**< Shows the report logo path */

		/**
		* Default constructor to initialize the structure members
		*/
		CrxStructGeneralSetting()
		{
			PatientPrivacy				= false;
			HeightandWeightUnit			= 0;
			BloodPressureEntryOptions	= 0;
			CommsPort					= nullptr;
			ReportTitle					= nullptr;
			ReportLogoPath				= nullptr;
		}
	};

	/**
	 * Container for PWV configuration settings. 
	 */
	public ref struct CrxStructPwvSetting
	{
		
		bool FemoralToCuff;/**< true: if Femoral to Cuff is selected, false: if not selcted */		
		bool ReferenceRange;/**< true: if Reference Range is selected, false: if not selcted */
		int PWVDistanceUnits;/**<0 : if mm is selected, 1: If cm is selected */
		int PWVDistanceMethod;/**<0 : if substracting is selected, 1: if direct is selected */
		int CaptureTime;/**<0 : if 5 seconds is selected 1:10 seconds is selected 2:20 seconds is selected */
		String^ SimulationType;/**< Shows the String Selected*/
		
		/**
		* Default constructor to initialize the structure members
		*/
		CrxStructPwvSetting()
		{
			FemoralToCuff		= false;
			ReferenceRange		= false;
			PWVDistanceUnits	= 0;
			PWVDistanceMethod	= 0;
			CaptureTime			= 0;
			SimulationType		= nullptr;			
		}
	};

	/**
	* @class CrxConfigManager
	* @brief Class to manage configuration related functions. @n
	* This Class is mainly responsible for maintaining scor.config file located in �system\config� folder. @n
	* It has methods that enable read and write in to specific sections of configuration file.
	*/
	public ref class CrxConfigManager
	{
		private:
			
			//Declaring Static variables names for exception numbers
			static const int CRXERR_FILE_NOT_EXIST = 100;
			static const int CRXERR_CORRUPT_FILE = 101;
			static const int CRXERR_FILE_NOT_ACCESS = 102;

			//singleton instance
			static CrxConfigManager^ _instance = gcnew CrxConfigManager();
			
			//structure instance to hold general settings
			CrxStructGeneralSetting^ _generalSettings;

			//structure instance to hold PWV settings
			CrxStructPwvSetting^ _pwvSettings;

			//structure instance to hold general settings for internal use
			CrxStructGeneralSetting^ _gSetInternal;

			//structure instance to hold PWV settings for internal use
			CrxStructPwvSetting^ _pSetInternal;

			// holds the location of the configuration file
            String^ _nameOfFile;

			//Default Constructor, sets the path of the configuration file, also initializes all the 
			//structure references.
			CrxConfigManager()
			{
                //set path of the configuration file, this is hard coded.
                _nameOfFile = L".\\system\\config\\scor.config";

				//Create instance General Settings Structure
				_generalSettings = gcnew CrxStructGeneralSetting();
				
				//Create instance PWV Settings Structure
				_pwvSettings = gcnew CrxStructPwvSetting();

				//Create internal instance General Settings Structure
				_gSetInternal = gcnew CrxStructGeneralSetting();

				//Create internal instance PWV Settings Structure
				_pSetInternal = gcnew CrxStructPwvSetting();
			}

			/**
			* Copy Constructor
			*/
			CrxConfigManager(const CrxConfigManager^)
			{
				
			}
			
			/**
			* Assignment Operator
			*/
			CrxConfigManager^ operator=(const CrxConfigManager^) 
			{
				 return this;
			}     

			// -------------Internal Function / Methods.-------------------
			//Get data from the file as per Section and Subsection
			void GetSettings(String^ Section, String^ SubSection);

			//Set data in the file as per Section and Subsection
			void SetSettings(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs , CrxStructPwvSetting^ ps);

			//Set data in the file as per Section, Subsection and node
			void SetSettingsNode(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs, CrxStructPwvSetting^ ps, XmlNode^ node);
		
			//Get data from the XML file as per Subsection node
			void SetGeneralSettingsNode(CrxStructGeneralSetting^ gs, XmlNode^ node);

			//Get data from the XML file as per Subsection node
			void SetPwvSettingsNode(CrxStructPwvSetting^ gs, XmlNode^ node);

			//Get data from the XML file as per Subsection node
			void GetSettingsNode(String^ Section, String^ SubSection, String^ SubSectionNode , String^ ReaderValue);

			//Get data from the XML file as per Subsection node
			void GetGeneralSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue);

			//Get data from the XML file as per Subsection node
			void GetPwvSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue);

			//-------------------Get General Setting Values-------------------
			//Get Patient Privacy value form config file
			void GetPatientPrivacy(String^ SubSection, String^ ReaderValue);
			//Get Height and weight value from config file
			void GetHeightWeight(String^ SubSection, String^ ReaderValue);
			//Get Blood Pressure Option from config file
			void GetBloodPressureOption(String^ SubSection, String^ ReaderValue);
			//Get Comms Port from config file
			void GetCommsPort(String^ SubSection, String^ ReaderValue);
			//Get Report Title from config file
			void GetReportTitle(String^ SubSection, String^ ReaderValue);
			//Get Report Logo Path from config file
			void GetReportLogoPath(String^ SubSection, String^ ReaderValue);
	
			//-------------------Set General Setting User Values-------------------
			//Set Patient Privacy value in config file
			void SetPatientPrivacy(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set Height and weight value in config file
			void SetHeightWeight(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set Blood Pressure Option in config file
			void SetBloodPressureOption(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set Comms Port in config file
			void SetCommsPort(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set Report Title in config file
			void SetReportTitle(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set Report Logo Path in config file
			void SetReportLogoPath(CrxStructGeneralSetting^ gs, XmlNode^ node);

			//-------------------Get PWV Setting Values-------------------
			//Get Femoral Cuff value from config file
			void GetFemoralToCuff(String^ SubSection , String^ ReaderValue);
			//Get Reference Range value from config file
			void GetReferenceRange(String^ SubSection, String^ ReaderValue);
			//Get PWV Distance Units value from config file
			void GetPwvDistanceUnits(String^ SubSection, String^ ReaderValue);
			//Get PWV Distance Methods value from config file
			void GetPwvDistanceMethods(String^ SubSection, String^ ReaderValue);
			//Get Capture Time value from config file
			void GetCaptureTime(String^ SubSection, String^ ReaderValue);
			//Get Simulation Type value from config file
			void GetSimulationType(String^ SubSection, String^ ReaderValue);
	
			//-------------------Set PWV Setting User Values-------------------
			//Set Femoral Cuff in config file
			void SetFemoralToCuff(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set Reference Range value in config file
			void SetReferenceRange(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set PWV Distance Units value in config file
			void SetPwvDistanceUnits(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set PWV Distance Methods value in config file
			void SetPwvDistanceMethods(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set Capture Time value in config file
			void SetCaptureTime(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set Simulation Type value in config file
			void SetSimulationType(CrxStructPwvSetting^ ps, XmlNode^ node);
			

	public:
			
			
			/**
			* Singleton Instance property with Only Get accessor
			*/
			static property CrxConfigManager^ Instance
			{
				CrxConfigManager^ get()
				{
					return CrxConfigManager::_instance;
				};
			};
		
			/** 
			* Structure GeneralSetting instance property with Get & Set accessor
			*/
			property CrxStructGeneralSetting^ GeneralSettings
			{
				CrxStructGeneralSetting^ get()
				{
					return CrxConfigManager::_generalSettings;
				};

				void set(CrxStructGeneralSetting^ gs)
				{
					_generalSettings = gs;
				}
			};

			/** 
			* Structure PWVSetting instance property with Get & Set accessor
			*/
			property CrxStructPwvSetting^ PwvSettings
			{
				CrxStructPwvSetting^ get()
				{
					return CrxConfigManager::_pwvSettings;
				};

				void set(CrxStructPwvSetting^ ps)
				{
					_pwvSettings = ps;
				}
			};			

		/**
		* To get General Default Settings from file
		* @param[out] CrxStructGeneralSetting handle to General Settings structure
		*/
		void GetGeneralDefaultSettings(CrxStructGeneralSetting^ objGenSettings);
		
		/**
		* To get General User Settings from the file
		*/
		void GetGeneralUserSettings();	
		
		/**
		* To Set General User Setting 
		* @param[in] CrxStructGeneralSetting Handle to the general setting structure
		*/
		void SetGeneralUserSettings(CrxStructGeneralSetting^ gs);	
		
		/**
		* To get PWV Default Settings from file
		* @param[out] CrxStructPwvSetting handle to PWV Settings structure
		*/
		void GetPwvDefaultSettings(CrxStructPwvSetting^ objPwvSettings);
		
		/**
		* To get PWV User Settings from the file
		*/
		void GetPwvUserSettings();	
		
		/**
		* To Set PWV User Setting 
		* @param[in] CrxStructPwvSetting Handle to the PWV setting structure
		*/
		void SetPwvUserSettings(CrxStructPwvSetting^ ps);	
		
	};
}}}} // End Namespace tags