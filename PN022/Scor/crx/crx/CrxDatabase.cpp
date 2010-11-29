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
		_objDB->AddInParameter(addCommand,"@GroupIdentifier",DbType::Int32,groupID);

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
	return measurementdataset;
}
DataSet^ CrxDBManager::GetPWVMeasurementDetails(int patientNo, int groupID , int systemIdentifier, String^ dateTime)
{
	DataSet^ measurementdataset = nullptr; // patientdataset object to return measurement data
	return measurementdataset;
}

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
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::Int32,pd->GroupIdentifier);
		_objDB->AddInParameter(addCommand,"@groupName",DbType::String,pd->GroupName);

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
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::Int32,pd->GroupIdentifier);
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
		_objDB->AddInParameter(addCommand,"@groupIdentifier",DbType::Int32,pd->GroupIdentifier);
		_objDB->AddInParameter(addCommand,"@groupName",DbType::String,pd->GroupName);
		_objDB->AddInParameter(addCommand,"@spValidation",DbType::Boolean,spCheck);

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
void CrxDBManager::SetConnection(String^ serverName, String^ sourceName)
{
	String^ ConnStr		= nullptr;//To store the reformated connection string,intializes to nullptr

	ConnStr  = String::Format("server={0};database=AtCor;Integrated Security=true" , serverName);
	
	_connString = ConnStr;//initialize _connString for further use in the application
	_dbType		= sourceName;//initialize _dbType for further use in the application

	try
	{
		if(serverName->Length == 0)
		{
			throw gcnew CrxException("CRX_ERR_DBMGR_NO_SERVER_NAME");
		}

		if(serverName->Length == 0)
		{
			throw gcnew CrxException("CRX_ERR_DBMGR_NO_SOURCE_NAME");
		}

		if(_objDB != nullptr)
		{
			_objDB = nullptr;
		}

		sourceName = sourceName->ToUpper();

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
		
	}
	catch(CrxException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^)
	{
		//throw the exception
		throw gcnew CrxException("CRX_ERR_DBMGR_NO_PROVIDER");
	}
}


