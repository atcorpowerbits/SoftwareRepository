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
		String^ GroupIdentifier;
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
		bool	IsStandardDeviationValid;
		bool	IsFemoralSignalValid;
		bool	IsCarotidSignalValid;
		bool	Simulation;
		int		SystemIdentifier;
		String^	GroupIdentifier;
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
		* @return if 0 connection established else return 1
		* @param[in] String serverName to set the server to be used
		* @param[in] String sourceName to set the sourcename to be used 
		*/
		//void SetConnection(String^ serverName, String^ sourceName);
		int SetConnection(String^ serverName, String^ sourceName);
		/**
		* To Check Connection can be established as per selection from user in the gui
		* @return if 0 connection established else return 1
		* @param[in] String serverName to set the server to be used
		* @param[in] String sourceName to set the sourcename to be used 
		*/
		int CheckConnection(String^ serverName, String^ sourceName);

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
		* To get specific patient measurement details from database
		* @return Return data related to patient number, group id, system id
		* @param[in] int patientNumberInternal, patient internal number in database
		* @param[in] int systemIdentifier, SystemInstallationID in database		
		* @param[in] int groupIdentifier, Group is related to the patient in database
		*/
		DataSet^ GetPWVMeasurementDetails(int patientNumberInternal, int groupIdentifier, int systemIdentifier );
		
		/**
		* Overloaded Function, To get specific patient measurement details from database
		* @return Return data related to patient number, group id, system id, date time
		* @param[in] CrxStructPWVMeasurementData handle to Measurement Details structure		
		*/
		//DataSet^ GetPWVMeasurementDetails(int patientNumberInternal, int groupIdentifier , int systemIdentifier,String^ dateTime);
		DataSet^ GetPWVMeasurementDetails(CrxStructPWVMeasurementData^ md);

		/**
		* To save patient record in the database 
		* @return if 1 if successfully saved else not successful
		* @param[in] CrxStructPatientDemographicData handle to Patient Demographic structure
		* @param[out] CrxStructPatientDemographicData handle updated patient no and group id 
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
		* @param[out] CrxStructPatientDemographicData handle updated group id 
		*/
		int UpdatePatientData(CrxStructPatientDemographicData^ pd, bool spCheck);

		/**
		* To save measurement record in the database 
		* @return if 1 if successfully saved else not successful
		* @param[in] CrxStructPWVMeasurementData handle to Measurement Details structure
		*/
		int SavePWVMeasurementDetails(CrxStructPWVMeasurementData^ md);
		
		/**
		* To update measurement record in the database 
		* @return if 1 if successfully saved else not successful
		* @param[in] CrxStructPWVMeasurementData handle to Measurement Details structure
		*/
		int UpdatePWVMeasurementDetails(CrxStructPWVMeasurementData^ md);

		/**
		* To convert Byte Array to float Array 
		* @return float array data
		* @param[in] length of the array
		* @param[in] Byte array values
		*/
		array<float>^ CommonByteArrtoFloatArr(int len, array<Byte>^ bytearr);
		/**
		* To convert Byte Array to short Array 
		* @return short array data
		* @param[in] length of the array
		* @param[in] Byte array values
		*/
		array<unsigned short>^ CommonByteArrtoShortArr(int len, array<Byte>^ bytearr);
		/**
		* To convert float Array to Byte Array 
		* @return Byte array data
		* @param[in] length of the array
		* @param[in] float array values
		*/
		array<Byte>^ CommonFloatArrtoByteArr(int len, array<float>^ fltarr);
		/**
		* To convert short Array to Byte Array 
		* @return Byte array data
		* @param[in] length of the array
		* @param[in] short array values
		*/
		array<Byte>^ CommonShortArrtoByteArr(int len, array<unsigned short>^ shrtarr);

	};
}
}
}
}