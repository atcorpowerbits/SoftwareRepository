// CrxComponents.h

#pragma once

using namespace System;


/**
 * @namespace	CrxConfiguration
 * @brief		This namespace implements configuration related functionality.
 * 
 */
namespace AtCor {
namespace Scor {
namespace CrossCutting {
namespace Configuration {

	/**
	* @class ConfigException
	* Exception class for CrxConfiguration namespace.
	*/
	public ref class ConfigException:Exception
	{
	private:
		int _errCode;
	public: 
		/**
		* Default constructor
		*/
		ConfigException(): _errCode(0) { }
		
		/**
		* Overloaded constructor
		* @param[in]	exError	The error code to intitialize this constructor with.
		*/
		ConfigException(int exError): _errCode(exError) { }
		
		/**
		* Error code property of the exception
		*/ 
		property int ErrorCode
		{
			int get()
			{
				return _errCode;
			}

			void set(int exError)
			{
				_errCode = exError;
			}
		}
	};

	// Creating CrxStructSetting Structure and variables
	/**
	 * Container for general configuration settings. 
	 */
	public ref struct CrxStructGeneralSetting
	{
		bool PatientPrivacy; /**< true: if patient privacy is selected, false: if not selcted */
		short HeightandWeightUnit; /**<0 : if metric is selcted, 1: If immperial is selected */
		short BloodPressureEntryOptions; /**<0 : if SP and DP is selected 1:SP and MP is selected 2:MP and DP is selected */
		String^ CommsPort; /**< Shows the string selected */
		String^ ReportTitle;	/**< Shows the report tile */
		String^ ReportLogoPath; /**< Shows the report logo path */

		/**
		* Default contructor to initialize the structure members
		*/
		CrxStructGeneralSetting()
		{
			PatientPrivacy = false;
			HeightandWeightUnit = 0;
			BloodPressureEntryOptions = 0;
			CommsPort = nullptr;
			ReportTitle = nullptr;
			ReportLogoPath = nullptr;
		}
	};
	
	/**
	* @class CrxConfigManager
	* @brief Class to manage cofiguration related functions
	*/
	public ref class CrxConfigManager
	{
		private:
			//singleton instance
			static CrxConfigManager^ _instance = gcnew CrxConfigManager();
			
			//structure instance to hold general settings
			CrxStructGeneralSetting^ _generalSettings;

            String^ _nameOfFile;

			//Default Constructor
			CrxConfigManager()
			{
                //set path of the configuration file, this is hard coded.
                _nameOfFile = L".\\system\\config\\scor.config";

				_generalSettings = gcnew CrxStructGeneralSetting();
			}

			//Copy Constructor
			CrxConfigManager(const CrxConfigManager^)
			{
				
			}
			
			//Assignment Operator
			CrxConfigManager^ operator=(const CrxConfigManager^) 
			{
				 return this;
			}     

			// Internal Function / Methods.
			//Get data from the file as per Section and Subsection
			void GetSettings(String^ Section, String^ SubSection);

			//Set data in the file as per Section and Subsection
			void SetSettings(String^ Section, String^ SubSection, CrxStructGeneralSetting^ gs);

		public:
			/**
			* Singleton instance property with Only Get accessor
			*/
			static property CrxConfigManager^ Instance
			{
				CrxConfigManager^ get()
				{
					return CrxConfigManager::_instance;
				};
			};
		
			/** 
			* Structure instance property with Get & Set accessor
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
		* To get General Default Settings from file
		*/
		void GetGeneralDefaultSettings();
		/**
		* To get User Settings from the file
		*/
		void GetGeneralUserSettings();	
		/**
		* To Set General User Setting 
		* @param CrxStructGeneralSetting Handle to the general setting structure
		*/
		void SetGeneralUserSettings(CrxStructGeneralSetting^);	
		
	};
}
}
}
}
