/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxDatabase.h
        
	 Author       :      Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting DatabaseManager namespace
*/
#pragma once

#include "CrxMessaging.h"
#include "CrxLogger.h"
#include "ScorException.h"

using namespace System;						
using namespace System::Data;

using namespace System::Data::Common;
using namespace System::Data::SqlClient;
using namespace System::IO;
using namespace System::Data::OleDb;

using namespace Microsoft::Practices::EnterpriseLibrary::Data;
using namespace Microsoft::Practices::EnterpriseLibrary::Data::Sql;

// Added application specific namespaces
using namespace AtCor::Scor::CrossCutting::Logging;		
using namespace AtCor::Scor::CrossCutting::Messaging;

/**
 * @namespace	AtCor::Scor::CrossCutting::DatabaseManager
 * @brief		This namespace implements Database related functionality.
 * 
 */

namespace AtCor { namespace Scor { namespace CrossCutting { namespace DatabaseManager
{	

	// Declaring global static numbers for structure variables
	/**
	* @enum CrxDBMsAccessPatientInfo
	 * @brief Container for Ms-Access Database Patient Info. 
	 */
	public enum class CrxDBMsAccessPatientInfo
	{
		DBMgrColumnPatLastName		= 3,
		DBMgrColumnPatFirstName		= 4,
		DBMgrColumnPatGender		= 6,
		DBMgrColumnPatDob			= 7,
		DBMgrColumnPatExtName		= 8,
	};         
	
	/**
	* @enum CrxDBPatientTableList
	 * @brief Container for Database Patient Table Info. 
	 */
	public enum class CrxDBPatientTableList
	{
		SystemIdentifier					=	0,
		PatientNumberInternal				=	1,
		PatientIdExternalReference			=	2,
		LastName							=	3,
		FirstName							=	4,
		DateOfBirth							=	5,
		Gender								=	6,
		CharSpare1							=	7,
		CharSpare2							=	8,	
		IntSpare1							=	9,
		IntSpare2							=	10,
		FloatSpare1							=	11,
		FloatSpare2							=	12,
		ArraySpare1							=	13,
		ArraySpare2							=	14,
	
	};
	
	
	/**
	* @enum CrxDBGetPatientDetailsById
	 * @brief Container for Database Patient Details by Id. 
	 */
	public enum class CrxDBGetPatientDetailsById
	{
		PatientNumberInternal				=	0,
		PatientIdExternalReference			=	1,
		LastName							=	2,
		FirstName							=	3,
		DateOfBirth							=	4,
		Gender								=	5,
		GroupName							=	6,	
	};

	/**
	* @enum CrxDBGetPatientDetails
	 * @brief Container for Database Patient Details by Id. 
	 */
	public enum class CrxDBGetPatientDetails
	{
		SystemIdentifier					=	0,
		PatientNumberInternal				=	1,
		PatientIdExternalReference			=	2,
		LastName							=	3,
		FirstName							=	4,
		DateOfBirth							=	5,
		Gender								=	6,
		GroupName							=	7,
		GroupIdentifier						=	8,
		PatientGroupTimeStamp				=	9,

	};

	/**
	* @enum CrxDBGroupTableList
	 * @brief Container for Database Group Table Info. 
	 */
	public enum class CrxDBGroupTableList
	{
		SystemIdentifier				=	0,
		GroupIdentifier					=	1,
		GroupName						=	2,
		CharSpare1						=	3,
		CharSpare2						=	4,
		IntSpare1						=	5,
		IntSpare2						=	6,
	};

	/**
	* @enum CrxDBPatientGroupTableList
	 * @brief Container for Database Patinet Group Relation Table Info. 
	 */
	public enum class CrxDBPatientGroupTableList
	{
		SystemIdentifier				=	0,
		GroupIdentifier					=	1,
		PatientNumberInternal			=	2,
		PatientGroupTimeStamp			=	3,
		CharSpare1						=	4,
		CharSpare2						=	5,
		IntSpare1						=	6,
		IntSpare2						=	7,
	};

	/**
	* @enum CrxDBGroupList
	 * @brief Container for Database Groups list Info. 
	 */
	public enum class CrxDBGroupList
	{
		GroupIdentifier					=	0,
		GroupName						=	1,
	};

	/**
	* @enum CrxDBPWVMeasurementTableList
	 * @brief Container for Database PWV Measurement Table Info. 
	 */
	public enum class CrxDBPWVMeasurementTableList
	{
		SystemIdentifier					=	0,
		GroupIdentifier						=	1,
		PatientNumberInternal				=	2,
		StudyDateTime						=	3,
		Notes								=	4,
		SP									=	5,
		DP									=	6,
		MP									=	7,
		Operator							=	8,
		PWVDistance							=	9,
		PWVDistanceMethod					=	10,
		Carotid								=	11,
		FemoraltoCuff						=	12,
		Cuff								=	13,
		Simulation							=	14,
		BloodPressureRange					=	15,
		BloodPressureEntryOption			=	16,
		NormalRange							=	17,
		ReferenceRange						=	18,
		Age									=	19,
		IsStandardDeviationValid			=	20,
		IsFemoralSignalValid				=	21,
		IsCarotidSignalValid				=	22,
		Direct								=	23,
		CaptureTime							=	24,
		MeanCorrectedTime					=	25,
		MeanDeltaTime						=	26,
		MeanHeartRate						=	27,
		MeanPulseWaveVelocity				=	28,
		SampleRate							=	29,
		StandardDeviation					=	30,
		WeightInKilograms					=	31,
		WeightInPounds						=	32,
		HeightInCentimetres					=	33,
		HeightInInches						=	34,
		BodyMassIndex						=	35,
		CarotidSignalFloatOnSets			=	36,
		CarotidSignalOnSetsLength			=	37,
		CarotidSignalPulseHeight			=	38,
		CarotidSignalPulseHeightVariation	=	39,
		CarotidSignal						=	40,
		CarotidSignalLength					=	41,
		CorrectionTime						=	42,
		DataRevision						=	43,
		FemoralSignalFloatOnSets			=	44,
		FemoralSignalOnSetsLength			=	45,
		FemoralSignalPulseHeight			=	46,
		FemoralSignal						=	47,
		FemoralSignalLength					=	48,
		NumberOfDeltas						=	49,
		NumberOfValidDeltas					=	50,
		CharSpare1							=	51,
		CharSpare2							=	52,
		IntSpare1							=	53,
		IntSpare2							=	54,
		FloatSpare1							=	55,
		FloatSpare2							=	56,
		ArraySpare1							=	57,
		ArraySpare2							=	58,
	};

	/**
	* @enum CrxDBAccessFileNameList
	 * @brief Container for Migration Access File List. 
	 */
	private enum class CrxDBAccessFileNameList
	{
		MigrationFileNotPresent,
		ScorXyzFileType,
		ScorMdbFileType,
	};

	/**
	 * @struct CrxDbStructSpList
	 * @brief Container for stored procedure name list. 	
	 */
	private ref struct CrxDbStructSpList
	{
		static	String^	BackUpDatabase						=	"BackUpDatabase";
		static	String^	CheckGroupNameExist					=	"CheckGroupNameExist";
		static	String^	CheckPatientIDExist					=	"CheckPatientIDExist";
		static	String^	CheckPatientRecordExists			=	"CheckPatientRecordExists";
		static	String^	DeleteMeasurementDetails			=	"DeleteMeasurementDetails";
		static	String^	DeletePatientDetails				=	"DeletePatientDetails";
		static	String^	GetGroupList						=	"GetGroupList";
		static	String^	GetMeasurementDetails				=	"GetMeasurementDetails";
		static	String^	GetPatientDetails					=	"GetPatientDetails";
		static	String^	GetPatientDetailsByPatientID		=	"GetPatientDetailsByPatientID";
		static	String^	GetPWVTrendData						=	"GetPWVTrendData";
		static	String^	InsertMeasurementDetails			=	"InsertMeasurementDetails";
		static	String^	InsertPatientDetails				=	"InsertPatientDetails";
		static	String^	MigratePatientDetails				=	"MigratePatientDetails";
		static	String^	UpdateMeasurementDetails			=	"UpdateMeasurementDetails";
		static	String^	UpdatePatientDetails				=	"UpdatePatientDetails";
	};

	/**
	 * @struct CrxDbStructParameterList
	 * @brief Container for parameters list. 	
	 */
	private ref struct CrxDbStructParametersList
	{
		static	String^	SystemIdentifier					=	"@systemIdentifier";
		static	String^	PatientIDExternalReference			=	"@patientIDExternalReference";
		static	String^	LastName							=	"@LastName";
		static	String^	FirstName							=	"@FirstName";
		static	String^	DateOfBirth							=	"@DateOfBirth";
		static	String^	Gender								=	"@gender";
		static	String^	GroupIdentifier						=	"@groupIdentifier";
		static	String^	GroupName							=	"@groupName";
		static	String^	PatientInternalId					=	"@patientInternalId";
		static	String^	GroupId								=	"@groupId";
		static	String^	PatientNumberInternal				=	"@PatientNumberInternal";
		static	String^	StudyDateTime						=	"@studyDateTime";
		static  String^	StudyDateTimeArrStr					=	"@studyDateTimeArrStr";
		static	String^	Notes								=	"@notes";
		static	String^	SP									=	"@SP";
		static	String^	DP									=	"@DP";
		static	String^	MP									=	"@MP";
		static	String^	Operator							=	"@operator";
		static	String^	PwvDistance							=	"@pwvDistance";
		static	String^	PwvDistanceMethod					=	"@pwvDistanceMethod";
		static	String^	Carotid								=	"@carotid";
		static	String^	FemoraltoCuff						=	"@femoraltoCuff";
		static	String^	Cuff								=	"@cuff";
		static	String^	Simulation							=	"@simulation";	
		static	String^	BloodPressureRange					=	"@bloodPressureRange";
		static	String^	BloodPressureEntryOption			=	"@bloodPressureEntryOption";
		static	String^	NormalRange							=	"@normalRange";
		static	String^	ReferenceRange						=	"@referenceRange";
		static	String^	Age									=	"@age";
		static	String^	IsStandardDeviationValid			=	"@isStandardDeviationValid";	
		static	String^	IsFemoralSignalValid				=	"@isFemoralSignalValid";	
		static	String^	IsCarotidSignalValid				=	"@isCarotidSignalValid";	
		static	String^	Direct								=	"@direct";
		static	String^	CaptureTime							=	"@captureTime";
		static	String^	MeanCorrectedTime					=	"@meanCorrectedTime";
		static	String^	MeanDeltaTime						=	"@meanDeltaTime";
		static	String^	MeanHeartRate						=	"@meanHeartRate";
		static	String^	MeanPulseWaveVelocity				=	"@meanPulseWaveVelocity";
		static	String^	SampleRate							=	"@sampleRate";
		static	String^	StandardDeviation					=	"@standardDeviation";
		static	String^	WeightInKilograms					=	"@weightInKilograms";
		static	String^	WeightInPounds						=	"@weightInPounds";
		static	String^	HeightInCentimetres					=	"@heightInCentimetres";
		static	String^	HeightInInches						=	"@heightInInches";
		static	String^	BodyMassIndex						=	"@bodyMassIndex";
		static	String^	CarotidSignalOnSets					=	"@carotidSignalFloatOnSets";
		static	String^	CarotidSignalOnSetsLength			=	"@carotidSignalOnSetsLength";
		static	String^	CarotidSignalPulseHeight			=	"@carotidSignalPulseHeight";
		static	String^	CarotidSignalPulseHeightVariation	=	"@carotidSignalPulseHeightVariation";
		static	String^	CarotidSignal						=	"@carotidSignal";
		static	String^	CarotidSignalLength					=	"@carotidSignalLength";
		static	String^	CorrectionTime						=	"@correctionTime";
		static	String^	DataRevision						=	"@dataRevision";
		static	String^	FemoralSignalOnSets					=	"@femoralSignalFloatOnSets";
		static	String^	FemoralSignalOnSetsLength			=	"@femoralSignalOnSetsLength";
		static	String^	FemoralSignalPulseHeight			=	"@femoralSignalPulseHeight";
		static	String^	FemoralSignal						=	"@femoralSignal";
		static	String^	FemoralSignalLength					=	"@femoralSignalLength";
		static	String^	NumberOfDeltas						=	"@numberOfDeltas";
		static	String^	NumberOfValidDeltas					=	"@numberOfValidDeltas";

		static String^	SpValidation						=	"@spValidation";
		static String^	GroupIdentifier_modified			=	"@groupIdentifier_modified";
		static String^	PatientIdExtRef						=	"@patientIdExtRef";
		static String^	ReturnStudyDatetime					=	"@returnStudyDatetime";
		static String^	HeartRateArrStr						=	"@heartRateArrStr";
		static String^	PulseWaveVelocityArrStr				=	"@pulseWaveVelocityArrStr";
		static String^	StandardDeviationArrStr				=	"@StandardDeviationArrStr";
		static String^	IsStdDevValidArrStr					=	"@IsStdDevValidArrStr";
		static String^	SpValidArrStr						=	"@SpValidArrStr";
		static String^	DpValidArrStr						=	"@DpValidArrStr";
		static String^	MpValidArrStr						=	"@MpValidArrStr";
		static String^  FilePath							=	"@FilePath";
	};


	/**
	 * @struct CrxDbStructInternal
	 * @brief Container for internal string. 	
	 */
	private ref struct CrxDbStructInternal
	{
		static	String^	DbRestoreFormat						=	"USE [master] RESTORE DATABASE  {0}  FROM DISK =  {1}  WITH REPLACE";
		static	String^	DbConnectionFormat					=	"server={0};database={1};Integrated Security=true";
		static  String^	MsAccessConnectionFormat			=	"PROVIDER=Microsoft.Jet.OLEDB.4.0;Data Source={0}";
		static	String^	MsAccessQueryCount					=	"Select Count(1) from patient";
		static	String^	MsAccessQueryAllRecord				=	"Select * from patient";
		static	String^	MigrationRenameError				=	"Unable to rename scor.xyz to scor.xyz.old";
		static	String^	MigrationStartedStr					=	"Migration started.";
		static	String^	MigrationCompletedStr				=	"Migration completed.";
		static	String^	MigrationFailedStr					=	"Migration failed.";
		static	String^	MigrationPatientListHeaderFormat	=	"Patients skipped : Id         First Name                Last Name                 Gender DOB ";
		static	String^	MigrationPatientTotMigratedFormat	=	"Total patients migrated: {0}";
		static	String^	MigrationPatientTotSkippedFormat	=	"Total patients skipped : {0}";
		//set path of the migration file, name of the old database file is always "scor.xyz"
		// and hence this is hard coded.
        static  String^ NameOfAccessFile					=	".\\system\\data\\scor.xyz";
		//set path of the migration file, name of the old database file is always "scor.mdb"
		// and hence this is hard coded.
        static  String^ NameOfMSAccessFile					=	".\\system\\data\\scor.mdb";
		//set path of the migration file, this is hard coded, as after migration old db file will
		// always be renamed to .old extension
         static  String^ NameOfAccessFileNew				=	".\\system\\data\\scor.xyz.old";
		 //set path of the migration file, this is hard coded, as after migration old db file will
		// always be renamed to .old extension
         static  String^ NameOfMSAccessFileNew				=	".\\system\\data\\scor.mdb.old";
		
		 static String^  DbType								=	"SqlClient";
		 static String^  DbName								=	"AtCor";
		 static int	FloatSize								=	4;
		 static int	ShortSize								=	2;
		 static int AppWaitTime								=	2000;

		 static String^ SqlClient							=	"SQLCLIENT";
		 static String^ OracleClient						=	"ORACLECLIENT";
		 static String^ ZeroParameterFormat					=	"'{0}'";
		 static	String^	MigrationPatientListFormat			=	"{0} {1} {2} {3} {4} {5}";
		 static	String^	BackupDone							=	"Backup completed successfully";
		 static	String^	BackupFail							=	"Backup fail";
		 static	String^	RestoreDone							=	"Database restored successfully";
		 static	String^	RestoreFail							=	"Restore fail";
	};

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
		String^ SpValidArrStr;
		String^ DpValidArrStr;
		String^ MpValidArrStr;
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
        //String^ _nameOfAccessFile;

		// holds the location of the new migration file
		//String^ _nameOfAccessFileNew;		

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
			_dbType = CrxDbStructInternal::DbType;
			DBname = CrxDbStructInternal::DbName; 

			//set path of the migration file, name of the old database file is always "scor.xyz"
			// and hence this is hard coded.
           // _nameOfAccessFile = L".\\system\\data\\scor.xyz";

			//set path of the migration file, this is hard coded, as after migration old db file will
			// always be renamed to .old extension
           // _nameOfAccessFileNew = L".\\system\\data\\scor.xyz.old";
		}


		/**
		* Copy Constructor
		*/
		CrxDBManager(CrxDBManager^)
		{
			
		}
		
		/**
		* Assignment Operator
		*/
		CrxDBManager^ operator=(CrxDBManager^) 
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

		/**
		* To check migration file exist in .\\system\\data\\ location or not
		* @return if true file exist
		*/
		int MigrationFileExistInternal();

		/**
		* To remove old migration file as per migration file type
		*/
		void RemoveOldAccessFile(int fileType);
		
		/**
		* To return migration file name as per file type
		* @return The Migration file name to migrate
		*/
		String^ MigrationFileName(int fileType); 

		/**
		* To rename migration file to old as per the file type(e.g scor.xyz to scor.xyz.old)
		*/
		void MigrationFileRename(int fileType);

		
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