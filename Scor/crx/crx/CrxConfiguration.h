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

	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
	public enum class CrxGenPwaValue
	{
		CrxPwaCapture5Seconds			= 5,
		CrxPwaCapture10Seconds			= 10,
		CrxPwaCapture20Seconds			= 20,
		
	};	
	//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

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
		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		//static String^ ConfigXmlElementsList = "'CONFIGURATION', 'SYSTEMSETTING', 'GENERAL', 'USER', 'PATIENTPRIVACY', 'HEIGHTANDWEIGHTUNITS', 'BLOODPRESSUREENTRYOPTIONS', 'COMMSPORT', 'REPORTTITLE', 'REPORTLOGOPATH', 'DEFAULT', 'PWV', 'PWVDISTANCEMETHOD', 'FEMORALTOCUFF', 'PWVDISTANCEUNITS', 'CAPTURETIME', 'EUROPEANGENERALPOPULATION', 'SIMULATIONTYPE', 'SERVERNAME', 'SOURCEDATA', 'CULTUREINFO', 'MACHINENAME', 'STARTUPMODE', 'STARTUPSCREEN', 'PRINTERNAME' , 'DEFAULTREPORT' , 'HEALTHYPOPULATION'";
		static String^ ConfigXmlElementsList = "'CONFIGURATION', 'SYSTEMSETTING', 'GENERAL', 'USER', 'PATIENTPRIVACY', 'HEIGHTANDWEIGHTUNITS', 'BLOODPRESSUREENTRYOPTIONS', 'COMMSPORT', 'REPORTTITLE', 'REPORTLOGOPATH', 'DEFAULT', 'PWV', 'PWVDISTANCEMETHOD', 'FEMORALTOCUFF', 'PWVDISTANCEUNITS', 'CAPTURETIME', 'EUROPEANGENERALPOPULATION', 'SIMULATIONTYPE', 'SERVERNAME', 'SOURCEDATA', 'CULTUREINFO', 'MACHINENAME', 'STARTUPMODE', 'STARTUPSCREEN', 'PRINTERNAME' , 'DEFAULTREPORT' , 'HEALTHYPOPULATION' , 'PWA' ,'GUIDANCEBARS','AUTOCAPTURE','MINPULSEHEIGHT','MAXPULSEHEIGHTVARIATION','MAXDIASTOLICVARIATION','AUGMENTATIONINDEX','AUGMENTATIONINDEXATHR75','BLINDSTUDY','CAPTUREINPUT','DEFAULTREPORTSCREEN', 'BP', 'DEVICE' ,'NUMBEROFASSESSMENTS', 'AUTOPWA', 'SPTHRESHOLD', 'PPTHRESHOLD', 'BLOODPRESSURE','SIMULATIONTYPE','KEY' ,'AUTOPWASP','AUTOPWAPP','AUTOPWADP','AUTOPWASPTHRESHOLD','AUTOPWAPPTHRESHOLD','AUTOPWADPTHRESHOLD'";
		//End   : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		
		static String^ TagSeparator	=	"'";
		static String^ CheckYesNoValue = "'NO', 'YES'";
		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		//static String^ StartUpScreenValue = "'SETUP'";
		static String^ StartUpScreenValue = "'SETUP','QUICK START'";
		//End   : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		static String^ StartUpModeValue = "'PWV','PWA'";

		static String^ UpperYES = "YES";
		//Commented to reduce FxCop warning. Uncomment it to use when neccessary
		//static String^ UpperNO = "NO";
		static String^ LowerYes = "Yes";
		static String^ LowerNo = "No";
		static String^ Blank = " ";
		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		static String^ Pwa = "PWA";
		static String^ BP = "BP";
		static String^ DeviceValue = "'SPHYGMOCOR','OTHER'";
		//End   : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011


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
		static String^ SystemKey	=	"KEY";

		////Begin: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
		//static String^ Id = "ID" ;
		//static String^ Sn = "SN";
		//static String^ Verify = "VERIFY";
		//static String^ Cksum = "CKSUM";
		////End   : AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011

		static String^ PwvDistanceMethod = "PWVDISTANCEMETHOD";
		static String^ FemoralToCuff = "FEMORALTOCUFF";
		static String^ PwvDistanceUnits = "PWVDISTANCEUNITS";
		static String^ CaptureTime = "CAPTURETIME";
		static String^ ReferenceRange = "EUROPEANGENERALPOPULATION";
		static String^ NormalRange = "HEALTHYPOPULATION";
		static String^ SimulationType = "SIMULATIONTYPE";
		static String^ DefaultReport  = "DEFAULTREPORT";

		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		static String^ GuidanceBars = "GUIDANCEBARS";
		static String^ AutoCapture = "AUTOCAPTURE";
		static String^ AugmentationIndex = "AUGMENTATIONINDEX";
		static String^ AugmentationIndexAtHR75  = "AUGMENTATIONINDEXATHR75";
		static String^ CaptureInput  = "CAPTUREINPUT";
		//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 6-Jun-2011
		static String^ Device = "DEVICE" ;
		static String^ NumberofAssessments = "NUMBEROFASSESSMENTS";
		static String^ AutoPWA = "AUTOPWA";
		static String^ BloodPressure = "BLOODPRESSURE";
		static String^ AutoPWASP = "AUTOPWASP";
		static String^ AutoPWAPP = "AUTOPWAPP";
		static String^ AutoPWADP = "AUTOPWADP";
		static String^ AutoPWASPThreshold = "AUTOPWASPTHRESHOLD";
		static String^ AutoPWAPPThreshold = "AUTOPWAPPTHRESHOLD";
		static String^ AutoPWADPThreshold = "AUTOPWADPTHRESHOLD";
		//End   : AtCor-Drop2-Sprint1, TM, SWREQ2006, 6-Jun-2011

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
	
	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 6-Jun-2011
	//Declaring enum for Number of Assessments
	/**
	* @enum NumberofAssessments
	 * @brief Container for Number of Assessments. 
	 */
	
	public enum class NumberofAssessments
	{
		Zero = 0,
		One,
		Two,
		Three,
		Four,
		Five
	};     
	
	//Declaring enum for SP PP Threshold Values
	/**
	* @enum ThresholdValues
	 * @brief Container for Threshold Values. 
	 */
	
	public enum class ThresholdValues
	{
		SPThresholdMin = 30,
		SPThresholdMax = 250,
		PPThresholdMin = 10,
		PPThresholdMax = 220
	};     
	//End: AtCor-Drop2-Sprint1, TM, SWREQ2006, 6-Jun-2011

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
		String^	Key;					/**< Shows the application aystem key */
		////Begin: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
		//String^ Id;						/**< Shows the Id from System Key */
		//String^ Sn;						/**< Shows the Sn from System Key */
		//String^ Verify;					/**< Shows the Verify from System Key */
		//String^ Cksum;					/**< Shows the Cksum from System Key */
		////End   : AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011


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
			Key							= nullptr;
			/*Id							= nullptr;
			Sn							= nullptr;
			Verify						= nullptr;
			Cksum						= nullptr;*/
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

	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
	/**
	 * @struct CrxStructPwaSetting
	 * @brief Container for PWA configuration settings. 
	 */
	public ref struct CrxStructPwaSetting
	{
		
		int CaptureTime;
        bool GuidanceBars;
		bool AutoCapture;
		bool AugmentationIndex;
		bool AugmentationIndexAtHR75;
		String^ CaptureInput;
		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
		String^ SimulationType;	/**< Shows the String Selected*/
		//End  : AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
		

		/**
		* Default constructor to initialize the structure members
		*/
		CrxStructPwaSetting()
		{
			CaptureTime				= Convert::ToInt32(CrxGenPwvValue::CrxPwvCapture5Seconds); 
			GuidanceBars			= true;
			AutoCapture				= true;
			AugmentationIndex		= true;
			AugmentationIndexAtHR75	= false;
			CaptureInput			= "Pressure Cuff";
			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
			SimulationType			= nullptr;
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
		}
	};
	//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
	//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 6-Jun-2011
	/**
	 * @struct CrxStructBpSetting
	 * @brief Container for Bp configuration settings. 
	 */
	public ref struct CrxStructBpSetting
	{
		
		String^ Device;
		int NumberofAssessments;
		String^ AutoPWA;
		int BloodPressure;
		bool AutoPWASP;
		bool AutoPWAPP;
		bool AutoPWADP;
		int AutoPWASPThreshold;
		int AutoPWAPPThreshold;
		int AutoPWADPThreshold;
		
		/**
		* Default constructor to initialize the structure members
		*/
		CrxStructBpSetting()
		{
			Device						= nullptr;
			NumberofAssessments			= 1;
			AutoPWA						= nullptr;
			BloodPressure				= 0;
			AutoPWASP					= false;
			AutoPWAPP					= false;
			AutoPWADP					= false;
			AutoPWASPThreshold			= 0;
			AutoPWAPPThreshold			= 0;
			AutoPWADPThreshold			= 0;
		}
	};
	//End   : AtCor-Drop2-Sprint1, TM, SWREQ2006, 6-Jun-2011



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

			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
			//structure instance to hold PWV settings
			CrxStructPwaSetting^ _pwaSettings;

			//structure instance to hold PWA settings for internal use
			CrxStructPwaSetting^ _pwaSetInternal;
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
			//structure instance to hold BP settings
			CrxStructBpSetting^ _bpSettings;

			//structure instance to hold BP settings for internal use
			CrxStructBpSetting^ _bpSetInternal;
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

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

				//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
				_pwaSettings = gcnew CrxStructPwaSetting();
				//End  : AtCor-Drop2-Sprint, TM, SWREQ2009, 13-Jun-2011

				//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
				_bpSettings = gcnew CrxStructBpSetting();
				//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

				//Create internal instance General Settings Structure
				_gSetInternal = gcnew CrxStructGeneralSetting();

				//Create internal instance PWV Settings Structure
				_pSetInternal = gcnew CrxStructPwvSetting();
			
				//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
				_pwaSetInternal = gcnew CrxStructPwaSetting();
				//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

				//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
				_bpSetInternal = gcnew CrxStructBpSetting();
				//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
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
			//void SetSettings(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs , CrxStructPwvSetting^ ps);
			void SetSettings(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs , CrxStructPwvSetting^ ps , CrxStructPwaSetting^ pwas, CrxStructBpSetting^ bps);

			//Set data in the file as per Section, Subsection and node
			//void SetSettingsNode(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs, CrxStructPwvSetting^ ps, XmlNode^ node);
			void SetSettingsNode(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs, CrxStructPwvSetting^ ps, CrxStructPwaSetting^ pwas,  CrxStructBpSetting^ bps, XmlNode^ node);
		
			//Get data from the XML file as per Subsection node
			void SetGeneralSettingsNode(CrxStructGeneralSetting^ gs, XmlNode^ node);

			//Get data from the XML file as per Subsection node
			void SetPwvSettingsNode(CrxStructPwvSetting^ gs, XmlNode^ node);

			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
			//Get data from the XML file as per Subsection node
			void SetPwaSettingsNode(CrxStructPwaSetting^ gs, XmlNode^ node);
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
			//Get data from the XML file as per Subsection node
			void SetBpSettingsNode(CrxStructBpSetting^ bps, XmlNode^ node);
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

			//Get data from the XML file as per Subsection node
			void GetSettingsNode(String^ Section, String^ SubSection, String^ SubSectionNode , String^ ReaderValue);

			//Get data from the XML file as per Subsection node
			void GetGeneralSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue);

			//Get data from the XML file as per Subsection node
			void GetPwvSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue);
			
			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
			//Get data from the XML file as per Subsection node
			void GetPwaSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue);
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
			//Get data from the XML file as per Subsection node
			void GetBpSettingsNode(String^ SubSection, String^ SubSectionNode , String^ ReaderValue);
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

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
			//Get System Key from config file
			void GetSystemKey(String^ SubSection, String^ ReaderValue);
			
			////Begin: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
			////Get Id (System Key) from config file
			//void GetId(String^ SubSection, String^ ReaderValue);
			////Get SN (System Key) from config file
			//void GetSn(String^ SubSection, String^ ReaderValue);
			////Get Verify (System Key) from config file
			//void GetVerify(String^ SubSection, String^ ReaderValue);
			////Get CheckSum (System Key) from config file
			//void GetCkSum(String^ SubSection, String^ ReaderValue);
			////End  : AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
			
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
			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
			void SetStartupMode(CrxStructGeneralSetting^ gs, XmlNode^ node);
			void SetStartupScreen(CrxStructGeneralSetting^ gs, XmlNode^ node);
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
			//Set System Key in config file
			void SetSystemKey(CrxStructGeneralSetting^ gs, XmlNode^ node);
			////Begin: AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
			////Set Id (System Key) in config file
			//void SetId(CrxStructGeneralSetting^ gs, XmlNode^ node);
			////Set SN (System Key) in config file
			//void SetSn(CrxStructGeneralSetting^ gs, XmlNode^ node);
			////Set Verify (System Key) in config file
			//void SetVerify(CrxStructGeneralSetting^ gs, XmlNode^ node);
			////Set CheckSum (System Key) in config file
			//void SetCkSum(CrxStructGeneralSetting^ gs, XmlNode^ node);
			////End  : AtCor-Drop2-Sprint1, TM, SWREQ2001, 9-Jun-2011
			
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

			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
			//-------------------Get PWA Setting Values-------------------
			//Get Capture Time value from config file
			void GetPwaCaptureTime(String^ SubSection, String^ ReaderValue);
			//Get Guidance Bar value from config file
			void GetPwaGuidanceBars(String^ SubSection, String^ ReaderValue);
			//Get Auto Capture value from config file
			void GetPwaAutoCapture(String^ SubSection, String^ ReaderValue);
			//Get Min Pulse Height value from config file
			//void GetPwaMinPulseHeight(String^ SubSection, String^ ReaderValue);
			//Get Max Pulse Height value from config file
			//void GetPwaMaxPulseHeightVariation(String^ SubSection, String^ ReaderValue);
			//Get Max Diastolic Variation value from config file
			//void GetPwaMaxDiastolicVariation(String^ SubSection, String^ ReaderValue);
			//Get Augmentation Index value from config file
			void GetPwaAugmentationIndex(String^ SubSection, String^ ReaderValue);
			//Get Augmentation Index @HR75 value from config file
			void GetPwaAugmentationIndexAtHR75(String^ SubSection, String^ ReaderValue);
			//Get Blind Study value from config file
			//void GetPwaBlindStudy(String^ SubSection, String^ ReaderValue);
			//Get Capture Input value from config file
			void GetPwaCaptureInput(String^ SubSection, String^ ReaderValue);
			//Get Default Report Screen value from config file
			//void GetPwaDefaultReportScreen(String^ SubSection, String^ ReaderValue);
			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
			//Get Simulation Type value from config file
			void GetPwaSimulationType(String^ SubSection, String^ ReaderValue);
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011


			//-------------------Set PWA Setting Values-------------------
			//Set Capture Time value from config file
			void SetPwaCaptureTime(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Guidance Bar value from config file
			void SetPwaGuidanceBars(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Auto Capture value from config file
			void SetPwaAutoCapture(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Min Pulse Height value from config file
			//void SetPwaMinPulseHeight(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Max Pulse Height value from config file
			//void SetPwaMaxPulseHeightVariation(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Max Diastolic Variation value from config file
			//void SetPwaMaxDiastolicVariation(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Augmentation Index value from config file
			void SetPwaAugmentationIndex(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Augmentation Index @HR75 value from config file
			void SetPwaAugmentationIndexAtHR75(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Blind Study value from config file
			//void SetPwaBlindStudy(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Capture Input value from config file
			void SetPwaCaptureInput(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//Set Default Report Screen value from config file
			//void SetPwaDefaultReportScreen(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011
			//Set Simulation Type value in config file
			void SetPwaSimulationType(CrxStructPwaSetting^ pwas, XmlNode^ node);
			//End  : AtCor-Drop2-Sprint1, TM, SWREQ2245, 17-Jun-2011


			//-------------------Get BP Setting Values-------------------
			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
			//Get BP Device from config file
			void GetBpDevice(String^ SubSection, String^ ReaderValue);
			//Get Number of Assessments from config file
			void GetBpNumberofAssessments(String^ SubSection, String^ ReaderValue);
			//Get Auto PWA from config file
			void GetBpAutoPWA(String^ SubSection, String^ ReaderValue);
			//Get Blood Pressure from config file
			void GetBpBloodPressure(String^ SubSection, String^ ReaderValue);
			//Get Auto PWV SP from config file
			void GetBpAutoPWASP(String^ SubSection, String^ ReaderValue);
			//Get Auto PWV PP from config file
			void GetBpAutoPWAPP(String^ SubSection, String^ ReaderValue);
			//Get Auto PWV DP from config file
			void GetBpAutoPWADP(String^ SubSection, String^ ReaderValue);
			//Get Auto PWV SP Threshold from config file
			void GetBpAutoPWASPThreshold(String^ SubSection, String^ ReaderValue);
			//Get Auto PWV PP Threshold from config file
			void GetBPAutoPWAPPThreshold(String^ SubSection, String^ ReaderValue);
			//Get Auto PWV DP Threshold  from config file
			void GetBpAutoPWADPThreshold(String^ SubSection, String^ ReaderValue);

			//-------------------Set BP Setting Values-------------------
			//Set BP Device from config file
			void SetBpDevice(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Number of Assessments from config file
			void SetBpNumberofAssessments(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Auto PWA from config file
			void SetBpAutoPWA(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Blood Pressure from config file
			void SetBpBloodPressure(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Auto PWV SP from config file
			void SetBpAutoPWASP(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Auto PWV PP from config file
			void SetBpAutoPWAPP(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Auto PWV DP from config file
			void SetBpAutoPWADP(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Auto PWV SP Threshold from config file
			void SetBpAutoPWASPThreshold(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Auto PWV PP Threshold from config file
			void SetBpAutoPWAPPThreshold(CrxStructBpSetting^ bps, XmlNode^ node);
			//Set Auto PWV DP Threshold  from config file
			void SetBpAutoPWADPThreshold(CrxStructBpSetting^ bps, XmlNode^ node);
			//End: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

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
			
			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
			property CrxStructPwaSetting^ PwaSettings
			{
				CrxStructPwaSetting^ get()
				{
					return CrxConfigManager::_pwaSettings;
				};

				void set(CrxStructPwaSetting^ ps)
				{
					_pwaSettings = ps;
				}
			};	
			//End: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011

			//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
			property CrxStructBpSetting^ BpSettings
			{
				CrxStructBpSetting^ get()
				{
					return CrxConfigManager::_bpSettings;
				};

				void set(CrxStructBpSetting^ bps)
				{
					_bpSettings = bps;
				}
			};	
			//End: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011

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

		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		/**
		* To get PWA Default Settings from file
		* @param[out] objPwaSettings CrxStructPwaSetting handle to PWA Settings structure
		*/
		void GetPwaDefaultSettings(CrxStructPwaSetting^ objPwaSettings);
		/**
		* To get PWA User Settings from the file
		*/
		void GetPwaUserSettings();
		
		/**
		* To Set PWA User Setting 
		* @param[in] pwas CrxStructPwaSetting Handle to the PWA setting structure
		*/
		void SetPwaUserSettings(CrxStructPwaSetting^ pwas);	
		//End  : AtCor-Drop2-Sprint1, TM, SWREQ2009, 13-Jun-2011
		
		//Begin: AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
		/**
		* To get BP Default Settings from file
		* @param[out] objBpSettings CrxStructBpSetting handle to BP Settings structure
		*/
		void GetBpDefaultSettings(CrxStructBpSetting^ objBpSettings);
		/**
		* To get PWA User Settings from the file
		*/
		void GetBpUserSettings();
		
		/**
		* To Set PWA User Setting 
		* @param[in] bps CrxStructPwaSetting Handle to the PWA setting structure
		*/
		void SetBpUserSettings(CrxStructBpSetting^ bps);	
		//End  : AtCor-Drop2-Sprint1, TM, SWREQ2006, 8-Jun-2011
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
