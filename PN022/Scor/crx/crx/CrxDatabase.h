/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxDatabase.h
        
	 Author       :      Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting DatabaseManager namespace
*/
#pragma once

using namespace System;
using namespace System::Data;
using namespace System::Data::Common;

using namespace Microsoft::Practices::EnterpriseLibrary::Data;
using namespace Microsoft::Practices::EnterpriseLibrary::Data::Sql;
using namespace Microsoft::Practices::EnterpriseLibrary::Common;
using namespace Microsoft::Practices::EnterpriseLibrary::Common::Configuration;

/**
 * @namespace	CrxDatabase
 * @brief		This namespace implements Database related functionality.
 * 
 */

namespace AtCor { namespace Scor { namespace CrossCutting { namespace DatabaseManager
{	
	// Creating CrxStructSetting Structure and variables
	/**
	 * Container for Patient DemographicData settings. 
	 */
	public ref struct CrxStructPatientDemographicData
	{
		int SystemIdentifier;
		int GroupIdentifier;
		int PatientNumberInternal;
		String^ PatientIDExternalReference;
		String^ LastName;
		String^ FirstName;
		DateTime DateOfBirth;
		String^ Gender;
		String^ GroupName;

	};

	/**
	 * Container for PWV MeasurementData settings. 
	 */
	public ref struct CrxStructPWVMeasurementData
	{
		int SystemIdentifier;
		int GroupIdentifier;
		int PatientNumberInternal;
		String^ StudyDateTime;
		//Other Variables will be added later
	};

	/**
	* @class CrxDBManager
	* @brief Class to manage database related functions. @n
	* This Class is mainly responsible for maintaining Database. @n
	* It has methods that save and modify in to specific fields in the database.
	*/
	public ref class CrxDBManager
	{
	private:
		//singleton instance
		static CrxDBManager^ _instance = gcnew CrxDBManager(); 
		
		String^ _connString;
		String^ _systemIdentityID;
		String^ _dbType;
		
		//Database Object
		Database^ _objDB;

		/**
		* Default Constructor
		*/
		CrxDBManager()
		{
			_objDB = nullptr;
			
			// Set the database type to SQL, we can change the DB type dynamically,
			// just by changing the _dbType property, and calling SetConnection again
			// with new server name.
			// Eg. Use "OracleClient" for oracle database, "Odbc" for any data source that can be connected with ODBC, etc.
			_dbType = "SqlClient";
		}


		/**
		* Copy Constructor
		*/
		CrxDBManager(const CrxDBManager^)
		{
			
		}
		
		/**
		* Assignment Operator
		*/
		CrxDBManager^ operator=(const CrxDBManager^) 
		{
			 return this;
		}  

		/** 
		* String ConnString property with Get & Set accessor
		*/
		property String^ ConnString
		{
			String ^ get() 
			{ 
				return _connString; 
			}
			void set(String ^ value) 
			{ 
				_connString = value; 
			}
		}

		/** 
		* String DataProvType property with Get & Set accessor
		*/
		property String^ DataProvType
		{
			String ^ get() 
			{ 
				return _dbType; 
			}
			void set(String ^ value) 
			{ 
				_dbType = value; 
			}
		}

	public:		
		
		/**
		* Singleton Instance property with Only Get accessor
		*/
		static property CrxDBManager^ Instance
		{
			CrxDBManager^ get()
			{
				return CrxDBManager::_instance;
			};
		};
		
		/**
		* To set the connection as per selection from user in the gui
		* @param[in] String serverName to set the server to be used
		* @param[in] String sourceName to set the sourcename to be used 
		*/
		void SetConnection(String^ serverName, String^ sourceName);

		/**
		* To check patient record exists or not in Database
		* @return if 1 five field record exist else no record
		* @param[in] CrxStructPatientDemographicData handle to Patient Demographic structure
		* @param[out] int value, if 1 six field record exist if 2 five field record exist else no record
		*/
		int PatientRecordExists(CrxStructPatientDemographicData^ pd);
		
		/**
		* To check Group name record exists or not in Database
		* @return if true record else no record
		* @param[in] int systemIdentifier of the SystemInstallationID
		* @param[in] String groupName in Group record for search
		*/
		bool GroupRecordExits(int systemIdentifier, String^ groupName);
		
		/**
		* To check specific patient id exists or not in Database
		* @return if true record else no record
		* @param[in] int systemIdentifier of the SystemInstallationID
		* @param[in] int patientIdExternalReference in Patient record for search
		*/
		bool PatientIdExists(int systemIdentifier, String^ patientIdExternalReference);
		
		/**
		* To get whole patient records from the database
		* @return Return whole patient data
		*/
		DataSet^ GetPatientDemographicRecords();
		
		/**
		* Overloaded Function, To get specific patient records from the database
		* @return Return data related to patient number
		* @param[in] int patientNumberInternal, patient internal number in database
		* @param[in] int systemIdentifier, SystemInstallationID in database		
		* @param[in] int groupIdentifier, Group is related to the patient in database
		*/
		DataSet^ GetPatientDemographicRecords(int patientNumberInternal , int systemIdentifier, int groupIdentifier);

		/**
		* To get whole group records from the database
		* @return Return group data
		*/
		DataSet^ GetGroupLists();

		/**
		* To get measurement details from database
		*/
		DataSet^ GetPWVMeasurementDetails(int patientNumberInternal, int groupIdentifier, int systemIdentifier );
		
		/**
		* Overloaded Function,To get measurement details from database
		*/
		DataSet^ GetPWVMeasurementDetails(int patientNumberInternal, int groupIdentifier , int systemIdentifier,String^ dateTime);

		/**
		* To save patient record in the database 
		* @return if 1 if successfully saved else not successful
		* @param[in] CrxStructPatientDemographicData handle to Patient Demographic structure
		*/
		int SavePatientData(CrxStructPatientDemographicData^ pd);
		
		/**
		* To delete patient record in the database 
		* @return if 1 if successfully saved else not successful
		* @param[in] CrxStructPatientDemographicData handle to Patient Demographic structure
		*/
		int DeletePatientData(CrxStructPatientDemographicData^ pd);

		/**
		* To update patient record in the database 
		* @return if 1 if successfully saved else not successful
		* @param[in] CrxStructPatientDemographicData handle to Patient Demographic structure
		* @param[in] bool spCheck to validation of patient record transfer
		*/
		int UpdatePatientData(CrxStructPatientDemographicData^ pd, bool spCheck);
		

	};
}
}
}
}