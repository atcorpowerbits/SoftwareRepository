/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxDatabase.cpp
        
     Author       :		 Smarajit Mishra
 
     Description  :      Functionality implementation for Database manager
*/

#include "stdafx.h"
#include "CrxDatabase.h"
#include "CrxCrossCutting.h"

using namespace System;
using namespace System::Text;

using namespace System::Data::SqlClient;

// Added application specific namespaces
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::DatabaseManager;

//To get patient record from the database as per inputs
DataSet^ CrxDBManager::GetPatientDemographicRecords(int patientNo , int systemID , int groupID)
{
	DataSet^ patientdataset	= nullptr; // patientdataset object to return patient data
	DbCommand^ addCommand	= nullptr; // store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("GetPatientDetailsByPatientID");
	
		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,systemID);
		_objDB->AddInParameter(addCommand,"@patientNumberInternal",DbType::Int32,patientNo);
		_objDB->AddInParameter(addCommand,"@GroupIdentifier",DbType::String,groupID);

		//Execute stored procedure and return Dataset
		patientdataset = _objDB->ExecuteDataSet(addCommand);	

		return patientdataset;	
	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// rethrow the wrapped exception
		throw gcnew CrxException(eObj);
	}
}

//To get whole patient record from the database
DataSet^ CrxDBManager::GetPatientDemographicRecords()
{
	DataSet^ patientdataset = nullptr; // patientdataset object to return patient data
	DbCommand^ addCommand   = nullptr; // store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("GetPatientDetails");

		//Execute stored procedure and return Dataset
		patientdataset = _objDB->ExecuteDataSet(addCommand);

		return patientdataset;

	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		//throw the exception
		throw gcnew CrxException(eObj);
	}
}
//Get the whole Group lists in the Group table
DataSet^ CrxDBManager::GetGroupLists()
{
	DataSet^ groupdataset = nullptr; // patientdataset object to return patient data
	DbCommand^ addCommand = nullptr; // store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("GetGroupList");

		//Execute stored procedure and return Dataset
		groupdataset = _objDB->ExecuteDataSet(addCommand);

		return groupdataset;

	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}	
}

DataSet^ CrxDBManager::GetPWVMeasurementDetails(int patientNo, int groupID, int systemIdentifier)
{
	DataSet^ measurementdataset = nullptr; // patientdataset object to return measurement data
	DbCommand^ addCommand = nullptr; // store the stored procedure in addCommand object
	
	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("GetMeasurementDetails");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,systemIdentifier);
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::Int32,groupID);
		_objDB->AddInParameter(addCommand,"@PatientNumberInternal",DbType::Int32,patientNo);
		_objDB->AddInParameter(addCommand,"@studyDateTime",DbType::DateTime,nullptr);

		//Execute stored procedure and return Dataset
		measurementdataset = _objDB->ExecuteDataSet(addCommand);

		return measurementdataset;

	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}		
}
//DataSet^ CrxDBManager::GetPWVMeasurementDetails(int patientNo, int groupID , int systemIdentifier, String^ dateTime)
DataSet^ CrxDBManager::GetPWVMeasurementDetails(CrxStructPWVMeasurementData^ md)
{
	DataSet^		measurementdataset = nullptr; // patientdataset object to return measurement data
	DbCommand^		addCommand		   = nullptr; // store the stored procedure in addCommand object
	int				len				   = 0;//Gets the length of the array
	array<Byte>^	buffarr; //Temporary byte array object for manipulation

	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("GetMeasurementDetails");

		////Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,md->SystemIdentifier);
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::String,md->GroupIdentifier);
		_objDB->AddInParameter(addCommand,"@PatientNumberInternal",DbType::Int32,md->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,"@studyDateTime",DbType::DateTime,md->StudyDateTime);

		//Execute stored procedure and return Dataset
		measurementdataset = _objDB->ExecuteDataSet(addCommand);		
		
		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0]["NormalRange"]);
		len = buffarr->Length/4;
		md->NormalRange = gcnew array<float>(len);;
		md->NormalRange = CommonByteArrtoFloatArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0]["ReferenceRange"]);
		len = buffarr->Length/4;
		md->ReferenceRange = gcnew array<float>(len);;
		md->ReferenceRange = CommonByteArrtoFloatArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0]["CarotidSignalFloatOnSets"]);
		len = buffarr->Length/4;
		md->CarotidSignalFloatOnSets = gcnew array<float>(len);
		md->CarotidSignalFloatOnSets = CommonByteArrtoFloatArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0]["FemoralSignalFloatOnSets"]);
		len = buffarr->Length/4;
		md->FemoralSignalFloatOnSets = gcnew array<float>(len);
		md->FemoralSignalFloatOnSets = CommonByteArrtoFloatArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0]["CarotidSignal"]);
		len = buffarr->Length/2;
		md->CarotidSignal = gcnew array<unsigned short>(len);
		md->CarotidSignal = CommonByteArrtoShortArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0]["FemoralSignal"]);
		len = buffarr->Length/2;
		md->FemoralSignal = gcnew array<unsigned short>(len);
		md->FemoralSignal = CommonByteArrtoShortArr(len,buffarr);
			
		md->SystemIdentifier			= Convert::ToInt32(measurementdataset->Tables[0]->Rows[0]["SystemIdentifier"]);
		md->GroupIdentifier				= Convert::ToString(measurementdataset->Tables[0]->Rows[0]["GroupIdentifier"]);
		md->PatientNumberInternal		= Convert::ToInt32(measurementdataset->Tables[0]->Rows[0]["PatientNumberInternal"]);
		md->StudyDateTime				= Convert::ToDateTime(measurementdataset->Tables[0]->Rows[0]["StudyDateTime"]);
		md->Notes						= Convert::ToString(measurementdataset->Tables[0]->Rows[0]["Notes"]);
		md->SP							= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["SP"]);
		md->DP							= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["DP"]);
		md->MP							= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["MP"]);
		md->Operator					= Convert::ToString(measurementdataset->Tables[0]->Rows[0]["Operator"]);

		md->PWVDistance					= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["PWVDistance"]);
		md->PWVDistanceMethod			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["PWVDistanceMethod"]);
		md->Carotid						= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["Carotid"]);
		md->FemoraltoCuff				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["FemoraltoCuff"]);
		md->Cuff						= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["Cuff"]);
		md->Simulation					= Convert::ToBoolean(measurementdataset->Tables[0]->Rows[0]["Simulation"]);
		md->BloodPressureRange			= Convert::ToString(measurementdataset->Tables[0]->Rows[0]["BloodPressureRange"]);
		md->BloodPressureEntryOption	= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["BloodPressureEntryOption"]);

		md->Age							= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["Age"]);
		md->IsStandardDeviationValid	= Convert::ToBoolean(measurementdataset->Tables[0]->Rows[0]["IsStandardDeviationValid"]);
		md->IsFemoralSignalValid		= Convert::ToBoolean(measurementdataset->Tables[0]->Rows[0]["IsFemoralSignalValid"]);
		md->IsCarotidSignalValid		= Convert::ToBoolean(measurementdataset->Tables[0]->Rows[0]["IsCarotidSignalValid"]);
		md->Direct						= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["Direct"]);
		md->CaptureTime					= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["CaptureTime"]);
		md->MeanCorrectedTime			= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["MeanCorrectedTime"]);
		md->MeanDeltaTime				= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["MeanDeltaTime"]);

		md->MeanHeartRate				= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["MeanHeartRate"]);
		md->MeanPulseWaveVelocity		= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["MeanPulseWaveVelocity"]);
		md->SampleRate					= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["SampleRate"]);
		md->StandardDeviation			= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["StandardDeviation"]);
		md->WeightInKilograms			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["WeightInKilograms"]);
		md->WeightInPounds				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["WeightInPounds"]);
		md->HeightInCentimetres			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["HeightInCentimetres"]);
		md->HeightInInches				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["HeightInInches"]);
		md->BodyMassIndex				= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["BodyMassIndex"]);

		md->CarotidSignalOnSetsLength	= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["CarotidSignalOnSetsLength"]);
		md->CarotidSignalPulseHeight	= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["CarotidSignalPulseHeight"]);
		md->CarotidSignalPulseHeightVariation = Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["CarotidSignalPulseHeightVariation"]);
		md->CarotidSignalLength			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["CarotidSignalLength"]);
		md->CorrectionTime				= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["CorrectionTime"]);
		md->DataRevision				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["DataRevision"]);

		md->FemoralSignalOnSetsLength	= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["FemoralSignalOnSetsLength"]);
		md->FemoralSignalPulseHeight	= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0]["FemoralSignalPulseHeight"]);
		md->FemoralSignalLength			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["FemoralSignalLength"]);
		md->NumberOfDeltas				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["NumberOfDeltas"]);
		md->NumberOfValidDeltas			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0]["NumberOfValidDeltas"]);
		
		
		return measurementdataset;

	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}		
}

//*************************************
//Add Patient Record in the database
int CrxDBManager::SavePatientData(CrxStructPatientDemographicData^ pd)
{
	int result			  = 0;//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand = nullptr; // store the stored procedure in addCommand object
	
	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("InsertPatientDetails");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,pd->SystemIdentifier);
		_objDB->AddInParameter(addCommand,"@patientIDExternalReference",DbType::String,pd->PatientIDExternalReference);
		_objDB->AddInParameter(addCommand,"@LastName",DbType::String,pd->LastName);
		_objDB->AddInParameter(addCommand,"@FirstName",DbType::String,pd->FirstName);
		_objDB->AddInParameter(addCommand,"@DateOfBirth",DbType::Date,pd->DateOfBirth);
		_objDB->AddInParameter(addCommand,"@gender",DbType::String,pd->Gender);
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::String,pd->GroupIdentifier);
		_objDB->AddInParameter(addCommand,"@groupName",DbType::String,pd->GroupName);

		_objDB->AddOutParameter(addCommand,"@patientInternalId",DbType::Int32,sizeof(int));
		_objDB->AddOutParameter(addCommand,"@groupId",DbType::Int32,sizeof(int));

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		pd->PatientNumberInternal = Int32::Parse((_objDB->GetParameterValue(addCommand,"@patientInternalId")->ToString()));
		//pd->GroupIdentifier		  = String::Parse((_objDB->GetParameterValue(addCommand,"@groupId")->ToString()));

		return result;
		
	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}
	
}
//Delete Patient Record in the database
int CrxDBManager::DeletePatientData(CrxStructPatientDemographicData^ pd)
{
	int result            = 0;//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand = nullptr; // store the stored procedure in addCommand object

	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("DeletePatientDetails");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,pd->SystemIdentifier);
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::String,pd->GroupIdentifier);
		_objDB->AddInParameter(addCommand,"@PatientNumberInternal",DbType::Int32,pd->PatientNumberInternal);
		
		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		return result;
		
	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}
}

int CrxDBManager::UpdatePatientData(CrxStructPatientDemographicData^ pd, bool spCheck)
{
	int result			  = 0;//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand = nullptr; // store the stored procedure in addCommand object

	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("UpdatePatientDetails");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,pd->SystemIdentifier);
		_objDB->AddInParameter(addCommand,"@PatientNumberInternal",DbType::Int32,pd->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,"@patientIDExternalReference",DbType::String,pd->PatientIDExternalReference);
		_objDB->AddInParameter(addCommand,"@LastName",DbType::String,pd->LastName);
		_objDB->AddInParameter(addCommand,"@FirstName",DbType::String,pd->FirstName);
		_objDB->AddInParameter(addCommand,"@DateOfBirth",DbType::Date,pd->DateOfBirth);
		_objDB->AddInParameter(addCommand,"@gender",DbType::String,pd->Gender);
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::String,pd->GroupIdentifier);
		_objDB->AddInParameter(addCommand,"@groupName",DbType::String,pd->GroupName);
		_objDB->AddInParameter(addCommand,"@spValidation",DbType::Boolean,spCheck);

		_objDB->AddOutParameter(addCommand,"@groupIdentifier_modified",DbType::Int32,sizeof(int));

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		//pd->GroupIdentifier	= String::Parse((_objDB->GetParameterValue(addCommand,"@groupIdentifier_modified")->ToString()));

		return result;
		
	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}
}

int CrxDBManager::PatientRecordExists(CrxStructPatientDemographicData^ pd)
{
	int result				= 0;//initializes to 0, if 1 six field exists, if 2 five field exists
	DbCommand^ addCommand	= nullptr; // store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("CheckPatientRecordExists");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,pd->SystemIdentifier);
		_objDB->AddInParameter(addCommand,"@patientIDExternalReference",DbType::String,pd->PatientIDExternalReference);
		_objDB->AddInParameter(addCommand,"@LastName",DbType::String,pd->LastName);
		_objDB->AddInParameter(addCommand,"@FirstName",DbType::String,pd->FirstName);
		_objDB->AddInParameter(addCommand,"@DateOfBirth",DbType::Date,pd->DateOfBirth);
		_objDB->AddInParameter(addCommand,"@gender",DbType::String,pd->Gender);
		_objDB->AddInParameter(addCommand,"@groupname",DbType::String,pd->GroupName);

		//Execute stored procedure and return int value records exist or not
		//if returns 1 then six field else if returns 2 then five field exist else not exist
		result = Int32::Parse((_objDB->ExecuteScalar(addCommand))->ToString());			

		return result;

	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}
}

bool CrxDBManager::GroupRecordExits(int systemIdentifier, String^ groupName)
{
	int result				= 0;//initializes to 0, if 1 group name exist
	bool check				= false;//initializes to false, if true exist else not exist
	DbCommand^ addCommand	= nullptr; // store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("CheckGroupNameExist");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,systemIdentifier);
		_objDB->AddInParameter(addCommand,"@groupname",DbType::String,groupName);

		//Execute stored procedure and return int value records exist or not
		//if returns 1 then exist else not exist
		result = Int32::Parse((_objDB->ExecuteScalar(addCommand))->ToString());	

		if(result == 1)
		{
			check = true;
		}

		return check;

	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}
}

bool CrxDBManager::PatientIdExists(int systemIdentifier, String^ patientIdExternalReference)
{
	int result				= 0;//initializes to 0, if 1 successful
	bool check				= false;//initializes to false, if true exist else not exist
	DbCommand^ addCommand	= nullptr; // store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("CheckPatientIDExist");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,systemIdentifier);
		_objDB->AddInParameter(addCommand,"@patientIdExtRef",DbType::String,patientIdExternalReference);

		//Execute stored procedure and return int value records exist or not
		//if returns 1 then exist else not exist
		result = Int32::Parse((_objDB->ExecuteScalar(addCommand))->ToString());	

		if(result == 1)
		{
			check = true;
		}

		return check;

	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}
}

//establish connection to the database provided by server name and source name
//void CrxDBManager::SetConnection(String^ serverName, String^ sourceName)
int CrxDBManager::SetConnection(String^ serverName, String^ sourceName)
{
	String^ ConnStr		= nullptr;//To store the reformated connection string,intializes to nullptr
	int ConnectionStatus = 0;//return result onnection can be established or not

	ConnStr  = String::Format("server={0};database=AtCor_Test1;Integrated Security=true" , serverName);
	
	_connString = ConnStr;//initialize _connString for further use in the application
	_dbType		= sourceName;//initialize _dbType for further use in the application

	try
	{
		sourceName = sourceName->ToUpper();

		//Check connection can be established as per provided server name and source name
		ConnectionStatus = CheckConnection(serverName,sourceName);

		if(ConnectionStatus == 1)
		{
			return ConnectionStatus;
		}

		if(_objDB != nullptr)
		{
			_objDB = nullptr;
		}		

		//Comparing with the source names to create database connection using sqldatabase or oracledatabase
		/* This validation may be changed later according to futher design*/
		if(sourceName->Equals("SQLCLIENT"))
		{
			_objDB = gcnew SqlDatabase(ConnStr);
		}
		else if(sourceName->Equals("ORACLECLIENT"))	
		{
			_objDB = gcnew Oracle::OracleDatabase(ConnStr);
		}		
		/* Similarly further databases can be added (if required)*/

		return ConnectionStatus;
		
	}	
	catch(Exception^)
	{
		//throw the exception
		throw gcnew CrxException("CRX_ERR_DBMGR_NO_PROVIDER");		
	}
	
}
//Check Connection can be established as per provided string and source name
int CrxDBManager::CheckConnection(String^ serverName, String^ sourceName)
{
	String^ ConnStr		= nullptr;//To store the reformated connection string,intializes to nullptr
	int ConnectionCheck = 0;//return result onnection can be established or not
	
	ConnStr  = String::Format("server={0};database=AtCor_Test1;Integrated Security=true" , serverName);

	try
	{		
		if(sourceName->Equals("SQLCLIENT"))
		{
			//Create Connection object to check connection
			SqlConnection^ connection = gcnew SqlConnection(ConnStr);

			//Open the connection to check connection can be established or not
			connection->Open();

			//Close the connection after check
			connection->Close();
		}		

		return ConnectionCheck;
	}
	catch(Exception^)
	{
		//throw the exception
		return ConnectionCheck = 1;
	}
}

//Add Measurement Record in the database
int CrxDBManager::SavePWVMeasurementDetails(CrxStructPWVMeasurementData^ md)
{
	int result				 = 0;		//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand	 = nullptr; // store the stored procedure in addCommand object
	SqlParameter^ parameter;			//creating sqlparameter object to pass parameter values
	int len					 = 0;		//Get the length of the array
	array<Byte>^	buffarr;			//Temporary byte array object for manipulation

	try
	{
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter(); 

		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("InsertMeasurementDetails");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,md->SystemIdentifier);
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::String,md->GroupIdentifier);
		_objDB->AddInParameter(addCommand,"@PatientNumberInternal",DbType::Int32,md->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,"@Notes",DbType::String,md->Notes);
		_objDB->AddInParameter(addCommand,"@SP",DbType::Int16,md->SP);
		_objDB->AddInParameter(addCommand,"@DP",DbType::Int16,md->DP);
		_objDB->AddInParameter(addCommand,"@MP",DbType::Int16,md->MP);
		_objDB->AddInParameter(addCommand,"@Operator",DbType::String,md->Operator);
		_objDB->AddInParameter(addCommand,"@PWVDistance",DbType::Int16,md->PWVDistance);
		_objDB->AddInParameter(addCommand,"@PWVDistanceMethod",DbType::Int16,md->PWVDistanceMethod);
		_objDB->AddInParameter(addCommand,"@Carotid",DbType::Int16,md->Carotid);
		_objDB->AddInParameter(addCommand,"@FemoraltoCuff",DbType::Int16,md->FemoraltoCuff);
		_objDB->AddInParameter(addCommand,"@Cuff",DbType::Int16,md->Cuff);

		_objDB->AddInParameter(addCommand,"@simulation",DbType::Boolean,md->Simulation);
		_objDB->AddInParameter(addCommand,"@bloodPressureRange",DbType::String,md->BloodPressureRange);
		_objDB->AddInParameter(addCommand,"@bloodPressureEntryOption",DbType::Int16,md->BloodPressureEntryOption);
		
		//get the length of array
		len = md->NormalRange->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->NormalRange);
		//initializing sqlparameter object to pass the parameter value
		parameter->ParameterName = "@normalRange";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = md->ReferenceRange->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->ReferenceRange);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@referenceRange";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		_objDB->AddInParameter(addCommand,"@age",DbType::Int16,md->Age);
		_objDB->AddInParameter(addCommand,"@isStandardDeviationValid",DbType::Boolean,md->IsStandardDeviationValid);
		_objDB->AddInParameter(addCommand,"@isFemoralSignalValid",DbType::Boolean,md->IsFemoralSignalValid);
		_objDB->AddInParameter(addCommand,"@isCarotidSignalValid",DbType::Boolean,md->IsCarotidSignalValid);
		_objDB->AddInParameter(addCommand,"@direct",DbType::Int16,md->Direct);

		_objDB->AddInParameter(addCommand,"@captureTime",DbType::Int16,md->CaptureTime);
		_objDB->AddInParameter(addCommand,"@meanCorrectedTime",DbType::Single,md->MeanCorrectedTime);
		_objDB->AddInParameter(addCommand,"@meanDeltaTime",DbType::Single,md->MeanDeltaTime);
		_objDB->AddInParameter(addCommand,"@meanHeartRate",DbType::Single,md->MeanHeartRate);
		_objDB->AddInParameter(addCommand,"@meanPulseWaveVelocity",DbType::Single,md->MeanPulseWaveVelocity);
		_objDB->AddInParameter(addCommand,"@sampleRate",DbType::Int16,md->SampleRate);
		_objDB->AddInParameter(addCommand,"@standardDeviation",DbType::Single,md->StandardDeviation);
		_objDB->AddInParameter(addCommand,"@weightInKilograms",DbType::Int16,md->WeightInKilograms);
		_objDB->AddInParameter(addCommand,"@weightInPounds",DbType::Int16,md->WeightInPounds);
		_objDB->AddInParameter(addCommand,"@heightInCentimetres",DbType::Int16,md->HeightInCentimetres);
		_objDB->AddInParameter(addCommand,"@heightInInches",DbType::Int16,md->HeightInInches);
		_objDB->AddInParameter(addCommand,"@bodyMassIndex",DbType::Single,md->BodyMassIndex);

		//get the length of array
		len = md->CarotidSignalFloatOnSets->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->CarotidSignalFloatOnSets);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@carotidSignalFloatOnSets";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,"@carotidSignalOnSetsLength",DbType::Int16,md->CarotidSignalOnSetsLength);
		_objDB->AddInParameter(addCommand,"@carotidSignalPulseHeight",DbType::Single,md->CarotidSignalPulseHeight);
		_objDB->AddInParameter(addCommand,"@carotidSignalPulseHeightVariation",DbType::Single,md->CarotidSignalPulseHeightVariation);
		
		//get the length of array
		len = md->CarotidSignal->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(unsigned short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,md->CarotidSignal);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@carotidSignal";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,"@carotidSignalLength",DbType::Int16,md->CarotidSignalLength);
		_objDB->AddInParameter(addCommand,"@correctionTime",DbType::Single,md->CorrectionTime);
		_objDB->AddInParameter(addCommand,"@dataRevision",DbType::Int16,md->DataRevision);
		
		//get the length of array
		len = md->FemoralSignalFloatOnSets->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->FemoralSignalFloatOnSets);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@femoralSignalFloatOnSets";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,"@femoralSignalOnSetsLength",DbType::Int16,md->FemoralSignalOnSetsLength);
		_objDB->AddInParameter(addCommand,"@femoralSignalPulseHeight",DbType::Single,md->FemoralSignalPulseHeight);
		
		//get the length of array
		len = md->FemoralSignal->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(unsigned short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,md->FemoralSignal);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@femoralSignal";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,"@femoralSignalLength",DbType::Int16,md->FemoralSignalLength);
		_objDB->AddInParameter(addCommand,"@numberOfDeltas",DbType::Int16,md->NumberOfDeltas);
		_objDB->AddInParameter(addCommand,"@numberOfValidDeltas",DbType::Int16,md->NumberOfValidDeltas);

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		return result;
		
	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}
	
}

//Add Measurement Record in the database
int CrxDBManager::UpdatePWVMeasurementDetails(CrxStructPWVMeasurementData^ md)
{
	int result			  = 0;//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand = nullptr; // store the stored procedure in addCommand object
	SqlParameter^ parameter;//creating sqlparameter object to pass parameter values
	int len					 = 0;		//Get the length of the array
	array<Byte>^	buffarr;			//Temporary byte array object for manipulation

	try
	{			
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter(); 

		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand("UpdateMeasurementDetails");

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,"@systemIdentifier",DbType::Int32,md->SystemIdentifier);
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::String,md->GroupIdentifier);
		_objDB->AddInParameter(addCommand,"@PatientNumberInternal",DbType::Int32,md->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,"@studyDateTime",DbType::DateTime,md->StudyDateTime);
		_objDB->AddInParameter(addCommand,"@Notes",DbType::String,md->Notes);
		_objDB->AddInParameter(addCommand,"@SP",DbType::Int16,md->SP);
		_objDB->AddInParameter(addCommand,"@DP",DbType::Int16,md->DP);
		_objDB->AddInParameter(addCommand,"@MP",DbType::Int16,md->MP);
		_objDB->AddInParameter(addCommand,"@Operator",DbType::String,md->Operator);
		_objDB->AddInParameter(addCommand,"@PWVDistance",DbType::Int16,md->PWVDistance);
		_objDB->AddInParameter(addCommand,"@PWVDistanceMethod",DbType::Int16,md->PWVDistanceMethod);
		_objDB->AddInParameter(addCommand,"@Carotid",DbType::Int16,md->Carotid);
		_objDB->AddInParameter(addCommand,"@FemoraltoCuff",DbType::Int16,md->FemoraltoCuff);
		_objDB->AddInParameter(addCommand,"@Cuff",DbType::Int16,md->Cuff);

		_objDB->AddInParameter(addCommand,"@simulation",DbType::Boolean,md->Simulation);
		_objDB->AddInParameter(addCommand,"@bloodPressureRange",DbType::String,md->BloodPressureRange);
		_objDB->AddInParameter(addCommand,"@bloodPressureEntryOption",DbType::Int16,md->BloodPressureEntryOption);
		
		//get the length of array
		len = md->NormalRange->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->NormalRange);
		//initializing sqlparameter object to pass the parameter value
		parameter->ParameterName = "@normalRange";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = md->ReferenceRange->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->ReferenceRange);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@referenceRange";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		_objDB->AddInParameter(addCommand,"@age",DbType::Int16,md->Age);
		_objDB->AddInParameter(addCommand,"@isStandardDeviationValid",DbType::Boolean,md->IsStandardDeviationValid);
		_objDB->AddInParameter(addCommand,"@isFemoralSignalValid",DbType::Boolean,md->IsFemoralSignalValid);
		_objDB->AddInParameter(addCommand,"@isCarotidSignalValid",DbType::Boolean,md->IsCarotidSignalValid);
		_objDB->AddInParameter(addCommand,"@direct",DbType::Int16,md->Direct);

		_objDB->AddInParameter(addCommand,"@captureTime",DbType::Int16,md->CaptureTime);
		_objDB->AddInParameter(addCommand,"@meanCorrectedTime",DbType::Single,md->MeanCorrectedTime);
		_objDB->AddInParameter(addCommand,"@meanDeltaTime",DbType::Single,md->MeanDeltaTime);
		_objDB->AddInParameter(addCommand,"@meanHeartRate",DbType::Single,md->MeanHeartRate);
		_objDB->AddInParameter(addCommand,"@meanPulseWaveVelocity",DbType::Single,md->MeanPulseWaveVelocity);
		_objDB->AddInParameter(addCommand,"@sampleRate",DbType::Int16,md->SampleRate);
		_objDB->AddInParameter(addCommand,"@standardDeviation",DbType::Single,md->StandardDeviation);
		_objDB->AddInParameter(addCommand,"@weightInKilograms",DbType::Int16,md->WeightInKilograms);
		_objDB->AddInParameter(addCommand,"@weightInPounds",DbType::Int16,md->WeightInPounds);
		_objDB->AddInParameter(addCommand,"@heightInCentimetres",DbType::Int16,md->HeightInCentimetres);
		_objDB->AddInParameter(addCommand,"@heightInInches",DbType::Int16,md->HeightInInches);
		_objDB->AddInParameter(addCommand,"@bodyMassIndex",DbType::Single,md->BodyMassIndex);

		//get the length of array
		len = md->CarotidSignalFloatOnSets->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->CarotidSignalFloatOnSets);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@carotidSignalFloatOnSets";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,"@carotidSignalOnSetsLength",DbType::Int16,md->CarotidSignalOnSetsLength);
		_objDB->AddInParameter(addCommand,"@carotidSignalPulseHeight",DbType::Single,md->CarotidSignalPulseHeight);
		_objDB->AddInParameter(addCommand,"@carotidSignalPulseHeightVariation",DbType::Single,md->CarotidSignalPulseHeightVariation);
		
		//get the length of array
		len = md->CarotidSignal->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(unsigned short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,md->CarotidSignal);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@carotidSignal";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,"@carotidSignalLength",DbType::Int16,md->CarotidSignalLength);
		_objDB->AddInParameter(addCommand,"@correctionTime",DbType::Single,md->CorrectionTime);
		_objDB->AddInParameter(addCommand,"@dataRevision",DbType::Int16,md->DataRevision);
		
		//get the length of array
		len = md->FemoralSignalFloatOnSets->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->FemoralSignalFloatOnSets);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@femoralSignalFloatOnSets";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,"@femoralSignalOnSetsLength",DbType::Int16,md->FemoralSignalOnSetsLength);
		_objDB->AddInParameter(addCommand,"@femoralSignalPulseHeight",DbType::Single,md->FemoralSignalPulseHeight);
		
		//get the length of array
		len = md->FemoralSignal->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(unsigned short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,md->FemoralSignal);
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter();
		parameter->ParameterName = "@femoralSignal";         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,"@femoralSignalLength",DbType::Int16,md->FemoralSignalLength);
		_objDB->AddInParameter(addCommand,"@numberOfDeltas",DbType::Int16,md->NumberOfDeltas);
		_objDB->AddInParameter(addCommand,"@numberOfValidDeltas",DbType::Int16,md->NumberOfValidDeltas);

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		return result;
		
	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew CrxException(eObj);
	}
	
}

//*********************************************//
//Byte array function
array<Byte>^ CrxDBManager::CommonShortArrtoByteArr(int len, array<unsigned short>^ shrtarr)
{
	int val =0;//value to run number of loops
	int byt =0;//value to store data in array location	
	array<Byte>^ bufferarr;//Temporary byte array object for manipulation
	array<Byte>^ bufferArrRet;//Temporary byte array object for manipulation and returning

	if(len != 0)
	{		
		//initiaze the size of the array
		bufferArrRet = gcnew array<Byte>(len*sizeof(unsigned short));
		
		for(val=0, byt=0; val<len; val++,byt=byt+2)
		{
			bufferarr = BitConverter::GetBytes(shrtarr[val]);			
			bufferArrRet[byt] = bufferarr[0];
			bufferArrRet[byt+1] = bufferarr[1];
		}
	}
	else
	{
		bufferArrRet = gcnew array<Byte>(len*sizeof(unsigned short));
	}
	return bufferArrRet;
}
array<Byte>^ CrxDBManager::CommonFloatArrtoByteArr(int len, array<float>^ fltarr)
{
	int val =0;//value to run number of loops
	int byt =0;//value to store data in array location	
	array<Byte>^ bufferarr;//Temporary byte array object for manipulation
	array<Byte>^ bufferArrRet;//Temporary byte array object for manipulation and returning
	float tempflt = 0.0f;//Temporary float vlaue for storing rounded decimal value

	if(len != 0)
	{		
		//initiaze the size of the array
		bufferArrRet = gcnew array<Byte>(len*sizeof(float));
		
		for(val=0, byt=0; val<len; val++,byt=byt+4)
		{
			tempflt  = Convert::ToSingle(Math::Round(fltarr[val],2));
			bufferarr = BitConverter::GetBytes(tempflt);			
			bufferArrRet[byt] = bufferarr[0];
			bufferArrRet[byt+1] = bufferarr[1];
			bufferArrRet[byt+2] = bufferarr[2];
			bufferArrRet[byt+3] = bufferarr[3];
		}
	}
	else
	{
		bufferArrRet = gcnew array<Byte>(len*sizeof(short));
	}
	return bufferArrRet;
}


//*********************************************//
//**************************************
//Varbinary to related arrays
//Common function

array<float>^ CrxDBManager::CommonByteArrtoFloatArr(int len, array<Byte>^ bytearr)
{
	int val = 0;//value to run number of loops
	int arr = 0;//value to get data in array location
	float value =0.0f;//Temporary value for the manipulation	
	array<float>^  tempbuffer;//Temporary float array object for manipulation and returning

	//initiaze the size of the array
	tempbuffer = gcnew array<float>(len);

	for(val=0, arr=0; val<len; val++,arr=arr+4 )
	{		
		value = BitConverter::ToSingle(bytearr,arr);			
		tempbuffer[val] = value;
	}

	return tempbuffer;
}

array<unsigned short>^ CrxDBManager::CommonByteArrtoShortArr(int len, array<Byte>^ bytearr)
{
	int val = 0;//value to run number of loops
	int arr = 0;//value to get data in array location
	short value =0;//Temporary value for the manipulation	
	array<unsigned short>^  tempbuffer;//Temporary short array object for manipulation and returning

	//initiaze the size of the array
	tempbuffer = gcnew array<unsigned short>(len);

	for(val=0, arr=0; val<len; val++,arr=arr+2 )
	{		
		value = BitConverter::ToUInt16(bytearr,arr);		
		tempbuffer[val] = value;
	}

	return tempbuffer;
}