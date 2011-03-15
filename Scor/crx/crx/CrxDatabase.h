/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxDatabase.h
        
	 Author       :      Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting DatabaseManager namespace
*/
#pragma once

#include "CrxCrossCutting.h"
#include "CrxConfiguration.h"
#include "CrxLogger.h"
#include "ScorException.h"

using namespace System;
using namespace System::Text;
using namespace System::Data;

using namespace System::Data::Common;
using namespace System::Data::SqlClient;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::ComponentModel;
using namespace System::Data::OleDb;

using namespace Microsoft::Practices::EnterpriseLibrary::Data;
using namespace Microsoft::Practices::EnterpriseLibrary::Data::Sql;
using namespace Microsoft::Practices::EnterpriseLibrary::Common;
using namespace Microsoft::Practices::EnterpriseLibrary::Common::Configuration;

// Added application specific namespaces
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Logging;

/**
 * @namespace	AtCor::Scor::CrossCutting::DatabaseManager
 * @brief		This namespace implements Database related functionality.
 * 
 */

namespace AtCor { namespace Scor { namespace CrossCutting { namespace DatabaseManager
{	
	// Creating CrxStructPatientDemographicData Structure and variables
	
	/**
	 * @struct CrxStructPatientDemographicData
	 * @brief Container for patient  Demographic Data. 	
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

	// Creating CrxStructPWVMeasurementData Structure and variables
	
	/**
	 * @struct CrxStructPWVMeasurementData
	 * @brief Container for PWV measurement data. 	
	 */
	public ref struct CrxStructPWVMeasurementData
	{
		bool	IsStandardDeviationValid;
		bool	IsFemoralSignalValid;
		bool	IsCarotidSignalValid;
		bool	Simulation;
		int		SystemIdentifier;
		int		GroupIdentifier;
		int		PatientNumberInternal;		
		short	SP;
		short	DP;
		short	MP;		
		short	Age;
		short	PWVDistance;		
		short	Carotid;
		short	FemoraltoCuff;
		short	Cuff;
		short	Direct;
		short	CaptureTime;
		short	SampleRate;		
		short	WeightInKilograms;
		short	WeightInPounds;
		short	HeightInCentimetres;
		short	HeightInInches;
		short	CarotidSignalOnSetsLength;
		short	CarotidSignalLength;
		short	DataRevision;
		short	FemoralSignalOnSetsLength;
		short	FemoralSignalLength;
		short	NumberOfDeltas;
		short	NumberOfValidDeltas;	
		float	MeanCorrectedTime;
		float	MeanDeltaTime;
		float	MeanHeartRate;
		float	MeanPulseWaveVelocity;
		float	StandardDeviation;
		float	BodyMassIndex;		
		float	CarotidSignalPulseHeight;
		float	CarotidSignalPulseHeightVariation;	
		float	CorrectionTime;
		float	FemoralSignalPulseHeight;
		float	FemoralSignalPulseHeightVariation;	
		float	ReferenceRangeDistance;	
		float	ReferenceRangePulseWaveVelocity;	
		String^ Notes;
		String^ Operator;
		short	PWVDistanceMethod;
		String^	BloodPressureRange;
		short	BloodPressureEntryOption;
		DateTime StudyDateTime;
		array<unsigned short>^ CarotidSignal;				
		array<unsigned short>^ FemoralSignal;
		array<float>^ NormalRange;
		array<float>^ ReferenceRange;		
		array<float>^ CarotidSignalFloatOnSets;			
		array<float>^ FemoralSignalFloatOnSets;		
		//Other Variables will be added later		
	};	
	
	// Creating CrxStructPWVTrendData Structure and variables
	
	/**
	 * @struct CrxStructPWVTrendData
	 * @brief Container for PWV trend data. 	
	 */
	public ref struct CrxStructPWVTrendData
	{
		String^ HeartRateArrStr;
		String^ PulseWaveVelocityArrStr;
		String^ StandardDeviationArrStr;
		String^ IsStdDevValidArrStr;
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

		// holds the location of the migration file
        String^ _nameOfAccessFile;

		// holds the location of the new migration file
		String^ _nameOfAccessFileNew;

		//Declaring static variables names for exception numbers
		static const int CRX_ERR_MSACCESS_FILE_NOT_EXIST	= 605;
		static const int CRX_ERR_DBMGR_CONVERSION			= 600;
		static const int CRX_ERR_DBMGR_NO_PROVIDER			= 601;
		static const int CRX_ERR_DBPERMISSION_REFER_MANUAL  = 610;
		static const int BACKUP_DONE						= 609;
		static const int CRX_ERR_MIGRATION_REFER_MANUAL     = 611;
		static const int CRX_ERR_RESTORE_REFER_MANUAL		= 612;

		static const int DBMGR_COLUMN_PAT_LAST_NAME			= 3;
		static const int DBMGR_COLUMN_PAT_FIRST_NAME		= 4;
		static const int DBMGR_COLUMN_PAT_GENDER			= 6;
		static const int DBMGR_COLUMN_PAT_DOB				= 7;
		static const int DBMGR_COLUMN_PAT_EXT_NAME			= 8;

		/**
		* Default Constructor
		*/
		CrxDBManager()
		{
			_objDB = nullptr;
			
			// Set the database type to SQL, we can change the DB type dynamically,
			// just by changing the _dbType property, and calling SetConnection again
			// with new server name. 
			// As currently application is configured to run only on SQL Express data base, hence _dbType is hardcoded to SqlClient
			// Eg. Use "OracleClient" for oracle database, "Odbc" for any data source that can be connected with ODBC, etc.
			_dbType = "SqlClient";
			DBname = "AtCor"; 

			//set path of the migration file, name of the old database file is always "scor.xyz"
			// and hence this is hard coded.
            _nameOfAccessFile = L".\\system\\data\\scor.xyz";

			//set path of the migration file, this is hard coded, as after migration old db file will
			// always be renamed to .old extension
            _nameOfAccessFileNew = L".\\system\\data\\scor.xyz.old";
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
		* String DataProviderType property with Get & Set accessor
		*/
		property String^ DataProviderType
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

		///**
		//* To reset database permission, set to multiuser  
		//*/
		//void ResetDatabaseToMultiuser();

		/**
		* To migrate data from scor.xyz to AtCor database 
		*/
		int MigrationInternal(OleDbDataReader^ rdr, CrxLogger^ objLog, int rowNum, int systemIdentifier, String^ groupName);
		/**
		* To log final data in the log file  
		*/
		void MigrationLogDetail(CrxLogger^ objLog, array<String^>^ skipPatientlog, int totskipresult);

		
	public:		
		
		static String^ DBname;

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
		* @return if 0 connection established else return 1
		* @param[in] serverName to set the server to be used
		* @param[in] sourceName to set the sourcename to be used 
		*/
		//void SetConnection(String^ serverName, String^ sourceName);
		int SetConnection(String^ serverName, String^ sourceName);
		
		/**
		* To Check Connection can be established as per selection from user in the gui
		* @return if 0 connection established else return 1
		* @param[in] serverName to set the server to be used
		* @param[in] sourceName to set the sourcename to be used 
		*/
		int CheckConnection(String^ serverName, String^ sourceName);

		/**
		* To check patient record exists or not in Database
		* @return if 1 five field record exist else no record
		* @param[in] pd CrxStructPatientDemographicData handle to Patient Demographic structure
		*/
		int PatientRecordExists(CrxStructPatientDemographicData^ pd);
		
		/**
		* To check Group name record exists or not in Database
		* @return if true record else no record
		* @param[in] systemIdentifier Integer system identifier of the SystemInstallationID
		* @param[in] groupName Group name in Group record for search
		*/
		bool GroupRecordExits(int systemIdentifier, String^ groupName);
		
		/**
		* To check specific patient id exists or not in Database
		* @return if true record else no record
		* @param[in] systemIdentifier Identifier of the SystemInstallationID
		* @param[in] patientIdExternalReference External reference in Patient record for search
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
		* @param[in] patientNumberInternal Patient internal number in database
		* @param[in] systemIdentifier SystemInstallationID in database		
		* @param[in] groupIdentifier Group Identifier is related to the patient in database
		*/
		DataSet^ GetPatientDemographicRecords(int patientNumberInternal , int systemIdentifier, int groupIdentifier);

		/**
		* To get whole group records from the database
		* @return Return group data
		*/
		DataSet^ GetGroupLists();
		
		/**
		* To get specific patient measurement details from database by joining the tables Patient,Group,PatientGroupRelation,PWVMeasurement
		* @return Return One or more than one assessments records related to patient number, group id, system id
		* @param[in] patientNumberInternal Patient internal number in database
		* @param[in] systemIdentifier SystemInstallationID in database		
		* @param[in] groupIdentifier Group Identifier is related to the patient in database
		*/
		DataSet^ GetPWVMeasurementDetails(int patientNumberInternal, int groupIdentifier, int systemIdentifier );
		
		/**
		* Overloaded Function, To get specific patient measurement details from database by joining the tables Patient,Group,PatientGroupRelation,PWVMeasurement
		* @return Return one assessment record related to patient number, group id, system id, date time@n
		*		  Conversion of byte arrays to short/float arrays values from database and store all values in structure
		* @param[in,out] md CrxStructPWVMeasurementData handle to Measurement Details structure@n	
		*					As output, handle to Measurement Details structure storing all the values got from the database in proper datatype format.	
		*/
		DataSet^ GetPWVMeasurementDetails(CrxStructPWVMeasurementData^ md);

		/**
		* To save patient record in the database 
		* @return 1 if successfully saved else not successful
		* @param[in,out] pd CrxStructPatientDemographicData handle to Patient Demographic structure@n
		*				As output, handle updated patient no and group id 
		*/
		int SavePatientData(CrxStructPatientDemographicData^ pd);
		
		/**
		* To delete patient record in the database 
		* @return if 1 if successfully saved else not successful
		* @param[in] pd CrxStructPatientDemographicData handle to Patient Demographic structure
		*/
		int DeletePatientData(CrxStructPatientDemographicData^ pd);

		/**
		* To update patient record in the database 
		* @return if 1 if successfully saved else not successful
		* @param[in,out] pd CrxStructPatientDemographicData handle to Patient Demographic structure@n
		*				As output, handle updated patient no and group id 
		* @param[in] spCheck Flag for validation of patient record transfer
		*/
		int UpdatePatientData(CrxStructPatientDemographicData^ pd, bool spCheck);

		/**
		* To save measurement record in the database @n
		* Conversion of short/float arrays to byte arrays values to store in varbinary type at database
		* @return if 1 if successfully saved else not successful
		* @param[in] md CrxStructPWVMeasurementData handle to Measurement Details structure
		*/
		int SavePWVMeasurementDetails(CrxStructPWVMeasurementData^ md);
		
		/**
		* To update measurement record in the database @n
		* Conversion of short/float arrays to byte arrays values to store in varbinary type at database
		* @return if 1 if successfully saved else not successful
		* @param[in] md CrxStructPWVMeasurementData handle to Measurement Details structure
		*/
		int UpdatePWVMeasurementDetails(CrxStructPWVMeasurementData^ md);

		/**
		* To update measurement record in the database @n
		* Conversion of short/float arrays to byte arrays values to store in varbinary type at database
		* @return if 1 if successfully saved else not successful
		* @param[in] md CrxStructPWVMeasurementData handle to Measurement Details structure
		* @param[in] studyDateTimeArrStr String to store the study datetime list to be deleted
		*/
		int DeletePWVMeasurementDetails(CrxStructPWVMeasurementData^ md, String^ studyDateTimeArrStr);

		/**
		* To convert Byte Array to float Array 
		* @return float array data
		* @param[in] len Length of the array
		* @param[in] bytearr Byte array values
		*/
		array<float>^ CommonByteArrtoFloatArr(int len, array<Byte>^ bytearr);
		/**
		* To convert Byte Array to short Array 
		* @return short array data
		* @param[in] len Length of the array
		* @param[in] bytearr Byte array values
		*/
		array<unsigned short>^ CommonByteArrtoShortArr(int len, array<Byte>^ bytearr);
		/**
		* To convert float Array to Byte Array 
		* @return Byte array data
		* @param[in] len Length of the array
		* @param[in] fltarr Float array values
		*/
		array<Byte>^ CommonFloatArrtoByteArr(int len, array<float>^ fltarr);
		/**
		* To convert short Array to Byte Array 
		* @return Byte array data
		* @param[in] len Length of the array
		* @param[in] shrtarr Short array values
		*/
		array<Byte>^ CommonShortArrtoByteArr(int len, array<unsigned short>^ shrtarr);

		/**
		* To take backup of the database 
		* @return if 0 if successfully saved else not successful
		* @param[in] filePath to store the backup file
		*/
		int DatabaseBackup(String^ filePath);
		
		/**
		* To restore back file to database 
		* @return if 0 if successfully saved else not successful
		* @param[in] filePath to get the backup file
		*/
		int DatabaseRestore(String^ filePath);
		
		/**
		* To check migration file exist in .\\system\\data\\scor.xyz location or not
		* @return if true file exist
		*/
		bool MigrationFileExist();

		/**
		* To migrate data from .\\system\\data\\scor.xyz to AtCor database
		* @return if 0 successful else not
		* @param[in] systemIdentifier Identifier of the SystemInstallationID
		* @param[in] groupName Group name on which the data will be migrated
		*/
		int MigrateAtCorData(int systemIdentifier, String^ groupName);
		/**
		* To get PWV Trend Data from AtCor database
		* @param[in] patientNumberInternal Patient internal number in database
		* @param[in] systemIdentifier SystemInstallationID in database		
		* @param[in] groupIdentifier Group Identifier is related to the patient in database
		* @param[in] studyDateTimeArrStr String to store the study datetime list
		* @param[out] trendDataStruct CrxStructPWVTrendData handle to PWV Trend Details
		*/
		void GetPWVTrendData(int patientNumberInternal, int groupIdentifier, int systemIdentifier, String^ studyDateTimeArrStr, CrxStructPWVTrendData^ trendDataStruct);
	
	};
}
}
}
}