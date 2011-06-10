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
 * @namespace	AtCor::Scor::CrossCutting::Configuration
 * @brief		This namespace implements configuration related functionality.
 * 
 */
namespace AtCor { namespace Scor { namespace CrossCutting { namespace Configuration
{	

	// Declaring global static numbers for structure variables
	/**
	* @enum CrxGenPwvValue
	 * @brief Container for General Pwv setting Value. 
	 */
	public enum class CrxGenPwvValue
	{
		CrxGenHeightWeightMetric		= 0,
		CrxGenHeightWeightImperial		= 1,
		CrxGenBPOptSPandDP				= 0,
		CrxGenBPOptSPandMP				= 1,
		CrxGenBPOptMPandDP				= 2,		
		CrxPwvDistDistUnitsMM			= 0,
		CrxPwvDistDistUnitsCM			= 1,		
		CrxPwvDistMethodSubtract		= 0,
		CrxPwvDistMethodDirect			= 1,		
		CrxPwvCapture5Seconds			= 5,
		CrxPwvCapture10Seconds			= 10,
		CrxPwvCapture20Seconds			= 20,
		
	};	

	/**
	 * @struct CrxConfigStructInternal
	 * @brief Container for internal string. 	
	 */
	private ref struct CrxConfigStructInternal
	{
		static String^ ConfigFilePath = ".\\system\\config\\scor.config";
		static String^ DefaultEnvironment = "Clinical";


	};

	/**
	 * @struct CrxConfigXmlTag
	 * @brief Container for config file tags. 	
	 */
	private ref struct CrxConfigXmlTag
	{
		static String^ General = "GENERAL";
		static String^ Default = "DEFAULT";
		static String^ User = "USER";
		static String^ Pwv = "PWV";
		static String^ ConfigXmlElementsList = "'CONFIGURATION', 'SYSTEMSETTING', 'GENERAL', 'USER', 'PATIENTPRIVACY', 'HEIGHTANDWEIGHTUNITS', 'BLOODPRESSUREENTRYOPTIONS', 'COMMSPORT', 'REPORTTITLE', 'REPORTLOGOPATH', 'DEFAULT', 'PWV', 'PWVDISTANCEMETHOD', 'FEMORALTOCUFF', 'PWVDISTANCEUNITS', 'CAPTURETIME', 'EUROPEANGENERALPOPULATION', 'SIMULATIONTYPE', 'SERVERNAME', 'SOURCEDATA', 'CULTUREINFO', 'MACHINENAME', 'STARTUPMODE', 'STARTUPSCREEN', 'PRINTERNAME' , 'DEFAULTREPORT' , 'HEALTHYPOPULATION'";
		static String^ TagSeparator	=	"'";
		static String^ CheckYesNoValue = "'NO', 'YES'";
		static String^ StartUpScreenValue = "'SETUP'";
		static String^ UpperYES = "YES";
		//Commented to reduce FxCop warning. Uncomment it to use when neccessary
		//static String^ UpperNO = "NO";
		static String^ LowerYes = "Yes";
		static String^ LowerNo = "No";
		static String^ Blank = " ";

		static String^ PatientPrivacy = "PATIENTPRIVACY";
		static String^ HeightAndWeightUnits = "HEIGHTANDWEIGHTUNITS";
		static String^ BloodPressureEntryOptions = "BLOODPRESSUREENTRYOPTIONS";
		static String^ CommsPort = "COMMSPORT";
		static String^ ReportTitle = "REPORTTITLE";
		static String^ ReportLogoPath = "REPORTLOGOPATH";
		static String^ ServerName = "SERVERNAME";
		static String^ SourceData = "SOURCEDATA";
		static String^ CultureInfo = "CULTUREINFO";
		static String^ MachineName = "MACHINENAME";
		static String^ StartupMode = "STARTUPMODE";
		static String^ StartupScreen = "STARTUPSCREEN";
		static String^ PrinterName = "PRINTERNAME";

		static String^ PwvDistanceMethod = "PWVDISTANCEMETHOD";
		static String^ FemoralToCuff = "FEMORALTOCUFF";
		static String^ PwvDistanceUnits = "PWVDISTANCEUNITS";
		static String^ CaptureTime = "CAPTURETIME";
		static String^ ReferenceRange = "EUROPEANGENERALPOPULATION";
		static String^ NormalRange = "HEALTHYPOPULATION";
		static String^ SimulationType = "SIMULATIONTYPE";
		static String^ DefaultReport  = "DEFAULTREPORT";
	};

	/**
	 * @struct CrxConfigHeightandWeightUnits
	 * @brief Container for CrxConfigHeightandWeightUnits. 	
	 */
	private ref struct CrxConfigHeightandWeightUnits
	{
		static String^ Metric = "METRIC";
		//Commented to reduce FxCop warning. Uncomment it to use when neccessary
		//static String^ Imperial = "IMPERIAL";

		static String^ MetricSetValue = "Metric";
		static String^ ImperialSetValue = "Imperial";

		static String^ CompareStr = "'METRIC', 'IMPERIAL'";
	};

	/**
	 * @struct CrxConfigBloodPressureOption
	 * @brief Container for BloodPressureOption. 	
	 */
	private ref struct CrxConfigBloodPressureOption
	{
		static String^ SPandDP = "SPANDDP";
		static String^ SPandMP = "SPANDMP";
		static String^ MPandDP = "MPANDDP";

		static String^ SPandDPSetValue = "SP and DP";
		static String^ SPandMPSetValue = "SP and MP";
		static String^ MPandDPSetValue = "MP and DP";

	};

	/**
	 * @struct CrxConfigPwvDistanceUnits
	 * @brief Container for PwvDistanceUnits. 	
	 */
	private ref struct CrxConfigPwvDistanceUnits
	{
		static String^ MM = "MM";	
		static String^ CompareStr = "'MM', 'CM'";

		static String^ MMSetValue = "mm";
		static String^ CMSetValue = "cm";		
	};

	/**
	 * @struct CrxConfigPwvDistanceMethods
	 * @brief Container for PwvDistanceMethods. 	
	 */
	private ref struct CrxConfigPwvDistanceMethods
	{		
		static String^ Subtracting = "SUBTRACTING";

		static String^ SubtractingSetValue = "Subtracting";
		static String^ DirectSetValue = "Direct";

		static String^ CompareStr = "'SUBTRACTING', 'DIRECT'";
	};

	/**
	 * @struct CrxConfigCaptureTime
	 * @brief Container for CaptureTime. 	
	 */
	private ref struct CrxConfigCaptureTime
	{
		static String^ FiveSeconds		= "5SECONDS";
		static String^ TenSeconds		= "10SECONDS";
		static String^ TwentySeconds	= "20SECONDS";

		static String^ FiveSecondsSetValue		= "5 seconds";
		static String^ TenSecondsSetValue		= "10 seconds";
		static String^ TwentySecondsSetValue	= "20 seconds";		
	};

	// Declaring global static numbers for structure variables
	/**
	* @enum UnitsType
	 * @brief Container for Units Type Value. 
	 */
	public enum class UnitsType
	{
		UNITS_METRIC,
		UNITS_IMPERIAL,
		UNITS_INVALID
	};          

	
	//Declaring enum for Metric Distance Units
	/**
	* @enum MetricDistanceUnits
	 * @brief Container for Metric Distance Units. 
	 */
	
	public enum class MetricDistanceUnits
	{
		METRIC_DISTANCE_MM,
		METRIC_DISTANCE_CM,
		METRIC_DISTANCE_INVALID
	};          
	
	//Declaring enum for BizMode
	/**
	* @enum BizMode
	 * @brief Container for Biz Mode. 
	 */
	public enum class BizMode
	{
		PWV,
		PWA,
		NIBP
	};      


	// Creating CrxStructSetting Structure and variables
	/**
	* @struct CrxStructGeneralSetting
	 * @brief Container for general configuration settings. 
	 */
	public ref struct CrxStructGeneralSetting
	{
		bool PatientPrivacy;			/**< true: if patient privacy is selected, false: if not selcted */
		int HeightandWeightUnit;		/**<0 : if metric is selcted, 1: If immperial is selected */
		int BloodPressureEntryOptions;	/**<0 : if SP and DP is selected 1:SP and MP is selected 2:MP and DP is selected */
		String^ CommsPort;				/**< Shows the string selected */
		String^ ReportTitle;			/**< Shows the report title */
		String^ ReportLogoPath;			/**< Shows the report logo path */
		String^ ServerName;				/**< Shows the server name selected */
		String^ SourceData;				/**< Shows the source data selected */
		String^ CultureInfo;			/**< Shows the culture info */
		String^ MachineName;			/**< Shows the machine name */
		String^ StartupMode;			/**< Shows the Startup Mode */
		String^ StartupScreen;			/**< Shows the Startup Screen */
		String^ EnvironmentSettings;	/**< Shows the environment Settings  */
		String^ PrinterName;			/**< Shows the printer settings */


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
			ServerName					= nullptr;
			SourceData					= nullptr;
			CultureInfo					= nullptr;
			MachineName					= nullptr;
			StartupMode					= nullptr;
			StartupScreen				= nullptr;
			EnvironmentSettings			= nullptr;
			PrinterName					= nullptr;
		}
	};

	/**
	 * @struct CrxStructPwvSetting
	 * @brief Container for PWV configuration settings. 
	 */
	public ref struct CrxStructPwvSetting
	{
		
		bool FemoralToCuff;		/**< true: if Femoral to Cuff is selected, false: if not selcted */		
		bool ReferenceRange;	/**< true: if Reference Range is selected, false: if not selcted */
		bool NormalRange;		/**< true: if Normal Range is selected, false: if not selcted */
		int PWVDistanceUnits;	/**<0 : if mm is selected, 1: If cm is selected */
		int PWVDistanceMethod;	/**<0 : if substracting is selected, 1: if direct is selected */
		int CaptureTime;		/**<5 : if 5 seconds is selected 10:10 seconds is selected 20:20 seconds is selected */
		String^ SimulationType;	/**< Shows the String Selected*/
		String^ DefaultReport;	/**< Shows the default report string selected*/
		
		/**
		* Default constructor to initialize the structure members
		*/
		CrxStructPwvSetting()
		{
			FemoralToCuff		= false;
			ReferenceRange		= false;
			NormalRange			= false;
			PWVDistanceUnits	= 0;
			PWVDistanceMethod	= 0;
			CaptureTime			= Convert::ToInt32(CrxGenPwvValue::CrxPwvCapture5Seconds); 
			SimulationType		= nullptr;
			DefaultReport		= nullptr;
		}
	};

	/**
	* @class CrxConfigManager
	* @brief Class to manage configuration related functions. @n
	* This Class is mainly responsible for maintaining scor.config file located in \“system\\config\” folder. @n
	* It has methods that enable read and write in to specific sections of configuration file.
	*/
	public ref class CrxConfigManager
	{
		private:
						
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
                //set path of the configuration file, this is hard coded as it will always point to system\config folder.
				_nameOfFile = CrxConfigStructInternal::ConfigFilePath;

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
			CrxConfigManager(CrxConfigManager^)
			{
				
			}
			
			/**
			* Assignment Operator
			*/
			CrxConfigManager^ operator=(CrxConfigManager^) 
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
			//Get Server Name from config file
			void GetServerName(String^ SubSection, String^ ReaderValue);
			//Get Source Data from config file
			void GetSourceData(String^ SubSection, String^ ReaderValue);
			//Get CultureInfo from config file
			void GetCultureInfo(String^ SubSection, String^ ReaderValue);
			//Get Machine Name from config file
			void GetMachineName(String^ SubSection, String^ ReaderValue);
			//Get Startup Mode from config file
			void GetStartupMode(String^ SubSection, String^ ReaderValue);
			//Get Startup Screen from config file
			void GetStartupScreen(String^ SubSection, String^ ReaderValue);
			//Get Config Printer from config file
			void GetConfigPrinter(String^ SubSection, String^ ReaderValue);
	
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
			//Set Server Name in config file
			void SetServerName(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set Source Data in config file
			void SetSourceData(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set CultureInfo in config file
			void SetCultureInfo(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set Machine Name in config file
			void SetMachineName(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//Set Printer Name in config file
			void SetPrinterName(CrxStructGeneralSetting^ gs, XmlNode^ node);

			//-------------------Get PWV Setting Values-------------------
			//Get Femoral Cuff value from config file
			void GetFemoralToCuff(String^ SubSection , String^ ReaderValue);
			//Get Reference Range value from config file
			void GetReferenceRange(String^ SubSection, String^ ReaderValue);
			//Get Normal Range value from config file
			void GetNormalRange(String^ SubSection, String^ ReaderValue);
			//Get PWV Distance Units value from config file
			void GetPwvDistanceUnits(String^ SubSection, String^ ReaderValue);
			//Get PWV Distance Methods value from config file
			void GetPwvDistanceMethods(String^ SubSection, String^ ReaderValue);
			//Get Capture Time value from config file
			void GetCaptureTime(String^ SubSection, String^ ReaderValue);
			//Get Simulation Type value from config file
			void GetSimulationType(String^ SubSection, String^ ReaderValue);
			//Get Default Report value from config file
			void GetDefaultReport(String^ SubSection, String^ ReaderValue);
	
			//-------------------Set PWV Setting User Values-------------------
			//Set Femoral Cuff in config file
			void SetFemoralToCuff(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set Reference Range value in config file
			void SetReferenceRange(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set Normal Range value in config file
			void SetNormalRange(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set PWV Distance Units value in config file
			void SetPwvDistanceUnits(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set PWV Distance Methods value in config file
			void SetPwvDistanceMethods(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set Capture Time value in config file
			void SetCaptureTime(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set Simulation Type value in config file
			void SetSimulationType(CrxStructPwvSetting^ ps, XmlNode^ node);
			//Set Default Report value from config file
			void SetDefaultReport(CrxStructPwvSetting^ ps, XmlNode^ node);

			

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
		* @param[out] objGenSettings CrxStructGeneralSetting handle to General Settings structure
		*/
		void GetGeneralDefaultSettings(CrxStructGeneralSetting^ objGenSettings);
		
		/**
		* To get General User Settings from the file
		*/
		void GetGeneralUserSettings();	
		
		/**
		* To Set General User Setting 
		* @param[in] gs CrxStructGeneralSetting Handle to the general setting structure
		*/
		void SetGeneralUserSettings(CrxStructGeneralSetting^ gs);	
		
		/**
		* To get PWV Default Settings from file
		* @param[out] objPwvSettings CrxStructPwvSetting handle to PWV Settings structure
		*/
		void GetPwvDefaultSettings(CrxStructPwvSetting^ objPwvSettings);
		
		/**
		* To get PWV User Settings from the file
		*/
		void GetPwvUserSettings();	
		
		/**
		* To Set PWV User Setting 
		* @param[in] ps CrxStructPwvSetting Handle to the PWV setting structure
		*/
		void SetPwvUserSettings(CrxStructPwvSetting^ ps);	
	};

	/**
	 * @struct CrxSystemParameterInfo
	 * @brief Stores strings needed for system	
	 */
	private ref struct CrxSystemParameterInfo
	{
		private:
			CrxSystemParameterInfo()
			{
				//empty private constructor . Recommended by FXCop
			}
		public:
			static String^ FilePath = ".\\system\\config\\ScorSystemParameters.xml";

	};
}}}} // End Namespace tags
