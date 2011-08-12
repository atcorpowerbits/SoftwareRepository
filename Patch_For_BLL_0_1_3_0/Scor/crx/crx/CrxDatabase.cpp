/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      CrxDatabase.cpp
        
     Author       :		 Smarajit Mishra
 
     Description  :      Functionality implementation for Database manager
*/

#include "stdafx.h"
#include "CrxDatabase.h"

using namespace AtCor::Scor::CrossCutting::DatabaseManager;


//To get patient record from the database as per inputs
DataSet^ CrxDBManager::GetPatientDemographicRecords(int patientNo , int systemID , int groupID)
{
	DataSet^ patientdataset	= nullptr; // patientdataset object to return patient data
	DbCommand^ addCommand	= nullptr; // store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::GetPatientDetailsByPatientID);
	
		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,systemID);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,patientNo);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,groupID);

		//Execute stored procedure and return Dataset
		patientdataset = _objDB->ExecuteDataSet(addCommand);	

		return patientdataset;	
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// rethrow the wrapped exception
		throw gcnew ScorException(eObj);
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
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::GetPatientDetails);

		//Execute stored procedure and return Dataset
		patientdataset = _objDB->ExecuteDataSet(addCommand);

		return patientdataset;

	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		//throw the exception
		throw gcnew ScorException(eObj);
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
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::GetGroupList);

		//Execute stored procedure and return Dataset
		groupdataset = _objDB->ExecuteDataSet(addCommand);

		return groupdataset;

	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}	
}

DataSet^ CrxDBManager::GetPWVMeasurementDetails(int patientNumberInternal, int groupIdentifier, int systemIdentifier)
{
	DataSet^ measurementdataset = nullptr;	// patientdataset object to return measurement data
	DbCommand^ addCommand = nullptr;		// store the stored procedure in addCommand object
	
	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::GetMeasurementDetails);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,systemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,groupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,patientNumberInternal);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::StudyDateTime,DbType::DateTime,nullptr);

		//Execute stored procedure and return Dataset
		measurementdataset = _objDB->ExecuteDataSet(addCommand);

		return measurementdataset;

	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}		
}
void CrxDBManager::GetPWVTrendData(int patientNumberInternal, int groupIdentifier, int systemIdentifier, String^ studyDateTimeArrStr, CrxStructPWVTrendData^ trendDataStruct)
{
	DbCommand^ addCommand = nullptr;		// store the stored procedure in addCommand object
	
	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::GetPWVTrendData);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,systemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,groupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,patientNumberInternal);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::StudyDateTimeArrStr,DbType::String,studyDateTimeArrStr);
		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::HeartRateArrStr,DbType::String,studyDateTimeArrStr->Length);
		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::PulseWaveVelocityArrStr,DbType::String,studyDateTimeArrStr->Length);
		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::StandardDeviationArrStr,DbType::String,studyDateTimeArrStr->Length);
		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::IsStdDevValidArrStr,DbType::String,studyDateTimeArrStr->Length);
		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::SpValidArrStr,DbType::String,studyDateTimeArrStr->Length);
		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::DpValidArrStr,DbType::String,studyDateTimeArrStr->Length);
		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::MpValidArrStr,DbType::String,studyDateTimeArrStr->Length);
		
		//Execute stored procedure
		_objDB->ExecuteNonQuery(addCommand);

		trendDataStruct->HeartRateArrStr = Convert::ToString(_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::HeartRateArrStr),CrxCommon::gCI);
		trendDataStruct->PulseWaveVelocityArrStr = Convert::ToString(_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::PulseWaveVelocityArrStr),CrxCommon::gCI);
		trendDataStruct->StandardDeviationArrStr = Convert::ToString(_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::StandardDeviationArrStr),CrxCommon::gCI);
		trendDataStruct->IsStdDevValidArrStr = Convert::ToString(_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::IsStdDevValidArrStr),CrxCommon::gCI);
		trendDataStruct->SpValidArrStr = Convert::ToString(_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::SpValidArrStr),CrxCommon::gCI);
		trendDataStruct->DpValidArrStr = Convert::ToString(_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::DpValidArrStr),CrxCommon::gCI);
		trendDataStruct->MpValidArrStr = Convert::ToString(_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::MpValidArrStr),CrxCommon::gCI);
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}		
}

//DataSet^ CrxDBManager::GetPWVMeasurementDetails(int patientNo, int groupID , int systemIdentifier, String^ dateTime)
DataSet^ CrxDBManager::GetPWVMeasurementDetails(CrxStructPWVMeasurementData^ md)
{
	DataSet^		measurementdataset = nullptr;	// patientdataset object to return measurement data
	DbCommand^		addCommand		   = nullptr;	// store the stored procedure in addCommand object
	int				len				   = 0;			//Gets the length of the array
	array<Byte>^	buffarr;						//Temporary byte array object for manipulation

	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::GetMeasurementDetails);

		////Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,md->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,md->GroupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,md->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::StudyDateTime,DbType::DateTime,md->StudyDateTime);

		//Execute stored procedure and return Dataset
		measurementdataset = _objDB->ExecuteDataSet(addCommand);		
		
		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::NormalRange,CrxCommon::gCI)]);
		len = buffarr->Length/CrxDbStructInternal::FloatSize;
		md->NormalRange = gcnew array<float>(len);
		md->NormalRange = CommonByteArrtoFloatArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::ReferenceRange,CrxCommon::gCI)]);
		len = buffarr->Length/CrxDbStructInternal::FloatSize;
		md->ReferenceRange = gcnew array<float>(len);
		md->ReferenceRange = CommonByteArrtoFloatArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::CarotidSignalFloatOnSets,CrxCommon::gCI)]);
		len = buffarr->Length/CrxDbStructInternal::FloatSize;
		md->CarotidSignalFloatOnSets = gcnew array<float>(len);
		md->CarotidSignalFloatOnSets = CommonByteArrtoFloatArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::FemoralSignalFloatOnSets,CrxCommon::gCI)]);
		len = buffarr->Length/CrxDbStructInternal::FloatSize;
		md->FemoralSignalFloatOnSets = gcnew array<float>(len);
		md->FemoralSignalFloatOnSets = CommonByteArrtoFloatArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::CarotidSignal,CrxCommon::gCI)]);
		len = buffarr->Length/CrxDbStructInternal::ShortSize;
		md->CarotidSignal = gcnew array<unsigned short>(len);
		md->CarotidSignal = CommonByteArrtoShortArr(len,buffarr);

		buffarr = (array<Byte>^)(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::FemoralSignal,CrxCommon::gCI)]);
		len = buffarr->Length/CrxDbStructInternal::ShortSize;
		md->FemoralSignal = gcnew array<unsigned short>(len);
		md->FemoralSignal = CommonByteArrtoShortArr(len,buffarr);
			
		md->SystemIdentifier			= Convert::ToInt32(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::SystemIdentifier,CrxCommon::gCI)],CrxCommon::gCI);
		md->GroupIdentifier				= Convert::ToInt32(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::GroupIdentifier,CrxCommon::gCI)],CrxCommon::gCI);
		md->PatientNumberInternal		= Convert::ToInt32(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::PatientNumberInternal,CrxCommon::gCI)],CrxCommon::gCI);
		md->StudyDateTime				= Convert::ToDateTime(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::StudyDateTime,CrxCommon::gCI)],CrxCommon::gCI);
		md->Notes						= Convert::ToString(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::Notes,CrxCommon::gCI)],CrxCommon::gCI);
		md->SP							= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::SP,CrxCommon::gCI)],CrxCommon::gCI);
		md->DP							= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::DP,CrxCommon::gCI)],CrxCommon::gCI);
		md->MP							= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::MP,CrxCommon::gCI)],CrxCommon::gCI);
		md->Operator					= Convert::ToString(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::Operator,CrxCommon::gCI)],CrxCommon::gCI);

		md->PWVDistance					= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::PWVDistance,CrxCommon::gCI)],CrxCommon::gCI);
		md->PWVDistanceMethod			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::PWVDistanceMethod,CrxCommon::gCI)],CrxCommon::gCI);
		md->Carotid						= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::Carotid,CrxCommon::gCI)],CrxCommon::gCI);
		md->FemoraltoCuff				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::FemoraltoCuff,CrxCommon::gCI)],CrxCommon::gCI);
		md->Cuff						= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::Cuff,CrxCommon::gCI)],CrxCommon::gCI);
		md->Simulation					= Convert::ToBoolean(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::Simulation,CrxCommon::gCI)],CrxCommon::gCI);
		md->BloodPressureRange			= Convert::ToString(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::BloodPressureRange,CrxCommon::gCI)],CrxCommon::gCI);
		md->BloodPressureEntryOption	= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::BloodPressureEntryOption,CrxCommon::gCI)],CrxCommon::gCI);

		md->Age							= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::Age,CrxCommon::gCI)],CrxCommon::gCI);
		md->IsStandardDeviationValid	= Convert::ToBoolean(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::IsStandardDeviationValid,CrxCommon::gCI)],CrxCommon::gCI);
		md->IsFemoralSignalValid		= Convert::ToBoolean(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::IsFemoralSignalValid,CrxCommon::gCI)],CrxCommon::gCI);
		md->IsCarotidSignalValid		= Convert::ToBoolean(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::IsCarotidSignalValid,CrxCommon::gCI)],CrxCommon::gCI);
		md->Direct						= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::Direct,CrxCommon::gCI)],CrxCommon::gCI);
		md->CaptureTime					= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::CaptureTime,CrxCommon::gCI)],CrxCommon::gCI);
		md->MeanCorrectedTime			= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::MeanCorrectedTime,CrxCommon::gCI)],CrxCommon::gCI);
		md->MeanDeltaTime				= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::MeanDeltaTime,CrxCommon::gCI)],CrxCommon::gCI);

		md->MeanHeartRate				= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::MeanHeartRate,CrxCommon::gCI)],CrxCommon::gCI);
		md->MeanPulseWaveVelocity		= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::MeanPulseWaveVelocity,CrxCommon::gCI)],CrxCommon::gCI);
		md->SampleRate					= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::SampleRate,CrxCommon::gCI)],CrxCommon::gCI);
		md->StandardDeviation			= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::StandardDeviation,CrxCommon::gCI)],CrxCommon::gCI);
		md->WeightInKilograms			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::WeightInKilograms,CrxCommon::gCI)],CrxCommon::gCI);
		md->WeightInPounds				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::WeightInPounds,CrxCommon::gCI)],CrxCommon::gCI);
		md->HeightInCentimetres			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::HeightInCentimetres,CrxCommon::gCI)],CrxCommon::gCI);
		md->HeightInInches				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::HeightInInches,CrxCommon::gCI)],CrxCommon::gCI);
		md->BodyMassIndex				= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::BodyMassIndex,CrxCommon::gCI)],CrxCommon::gCI);

		md->CarotidSignalOnSetsLength	= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::CarotidSignalOnSetsLength,CrxCommon::gCI)],CrxCommon::gCI);
		md->CarotidSignalPulseHeight	= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::CarotidSignalPulseHeight,CrxCommon::gCI)],CrxCommon::gCI);
		md->CarotidSignalPulseHeightVariation = Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::CarotidSignalPulseHeightVariation,CrxCommon::gCI)],CrxCommon::gCI);
		md->CarotidSignalLength			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::CarotidSignalLength,CrxCommon::gCI)],CrxCommon::gCI);
		md->CorrectionTime				= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::CorrectionTime,CrxCommon::gCI)],CrxCommon::gCI);
		md->DataRevision				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::DataRevision,CrxCommon::gCI)],CrxCommon::gCI);

		md->FemoralSignalOnSetsLength	= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::FemoralSignalOnSetsLength,CrxCommon::gCI)],CrxCommon::gCI);
		md->FemoralSignalPulseHeight	= Convert::ToSingle(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::FemoralSignalPulseHeight,CrxCommon::gCI)],CrxCommon::gCI);
		md->FemoralSignalLength			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::FemoralSignalLength,CrxCommon::gCI)],CrxCommon::gCI);
		md->NumberOfDeltas				= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::NumberOfDeltas,CrxCommon::gCI)],CrxCommon::gCI);
		md->NumberOfValidDeltas			= Convert::ToInt16(measurementdataset->Tables[0]->Rows[0][Convert::ToInt32(CrxDBPWVMeasurementTableList::NumberOfValidDeltas,CrxCommon::gCI)],CrxCommon::gCI);
		
		
		return measurementdataset;

	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}		
}

//*************************************
//Add Patient Record in the database
int CrxDBManager::SavePatientData(CrxStructPatientDemographicData^ pd)
{
	int result			  = 0;			//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand = nullptr;	// store the stored procedure in addCommand object
	
	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::InsertPatientDetails);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,pd->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientIDExternalReference,DbType::String,pd->PatientIDExternalReference);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::LastName,DbType::String,pd->LastName);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FirstName,DbType::String,pd->FirstName);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DateOfBirth,DbType::Date,pd->DateOfBirth);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Gender,DbType::String,pd->Gender);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,pd->GroupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupName,DbType::String,pd->GroupName);

		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::PatientInternalId,DbType::Int32,sizeof(int));
		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::GroupId,DbType::Int32,sizeof(int));

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		pd->PatientNumberInternal = Int32::Parse((_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::PatientInternalId)->ToString()),CrxCommon::gCI);
		pd->GroupIdentifier		  = Int32::Parse((_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::GroupId)->ToString()),CrxCommon::gCI);

		return result;
		
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
	
}
//Delete Patient Record in the database
int CrxDBManager::DeletePatientData(CrxStructPatientDemographicData^ pd)
{
	int result            = 0;			//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand = nullptr;	// store the stored procedure in addCommand object

	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::DeletePatientDetails);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,pd->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,pd->GroupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,pd->PatientNumberInternal);
		
		//TODO: instead of returning 0 and 1 return the value returned by ExecuteNonQuery, 

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		return result;
		
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
}

int CrxDBManager::UpdatePatientData(CrxStructPatientDemographicData^ pd, bool spCheck)
{
	int result			  = 0;			//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand = nullptr;	// store the stored procedure in addCommand object

	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::UpdatePatientDetails);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,pd->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,pd->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientIDExternalReference,DbType::String,pd->PatientIDExternalReference);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::LastName,DbType::String,pd->LastName);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FirstName,DbType::String,pd->FirstName);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DateOfBirth,DbType::Date,pd->DateOfBirth);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Gender,DbType::String,pd->Gender);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,pd->GroupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupName,DbType::String,pd->GroupName);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SpValidation,DbType::Boolean,spCheck);

		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::GroupIdentifier_modified,DbType::Int32,sizeof(int));

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		pd->GroupIdentifier	= Int32::Parse((_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::GroupIdentifier_modified)->ToString()),CrxCommon::gCI);

		return result;
		
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
}

int CrxDBManager::PatientRecordExists(CrxStructPatientDemographicData^ pd)
{
	int result				= 0;		//initializes to 0, if 1 six field exists, if 2 five field exists
	DbCommand^ addCommand	= nullptr;	// store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::CheckPatientRecordExists);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,pd->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientIDExternalReference,DbType::String,pd->PatientIDExternalReference);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::LastName,DbType::String,pd->LastName);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FirstName,DbType::String,pd->FirstName);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DateOfBirth,DbType::Date,pd->DateOfBirth);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Gender,DbType::String,pd->Gender);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupName,DbType::String,pd->GroupName);

		//Execute stored procedure and return int value records exist or not
		//if returns 1 then five field exist else not exist
		result = Int32::Parse((_objDB->ExecuteScalar(addCommand))->ToString());			

		return result;

	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
}

bool CrxDBManager::GroupRecordExits(int systemIdentifier, String^ groupName)
{
	int result				= 0;		//initializes to 0, if 1 group name exist
	bool check				= false;	//initializes to false, if true exist else not exist
	DbCommand^ addCommand	= nullptr;	// store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::CheckGroupNameExist);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,systemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupName,DbType::String,groupName);

		//Execute stored procedure and return int value records exist or not
		//if returns 1 then exist else not exist
		result = Int32::Parse((_objDB->ExecuteScalar(addCommand))->ToString());	

		if(result == 1)
		{
			check = true;
		}

		return check;

	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
}

bool CrxDBManager::PatientIdExists(int systemIdentifier, String^ patientIdExternalReference)
{
	int result				= 0;		//initializes to 0, if 1 successful
	bool check				= false;	//initializes to false, if true exist else not exist
	DbCommand^ addCommand	= nullptr;	// store the stored procedure in addCommand object

	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::CheckPatientIDExist);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,systemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientIdExtRef,DbType::String,patientIdExternalReference);

		//Execute stored procedure and return int value records exist or not
		//if returns 1 then exist else not exist
		result = Int32::Parse((_objDB->ExecuteScalar(addCommand))->ToString());	

		if(result == 1)
		{
			check = true;
		}

		return check;

	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
}

//establish connection to the database provided by server name and source name
//void CrxDBManager::SetConnection(String^ serverName, String^ sourceName)
int CrxDBManager::SetConnection(String^ serverName, String^ sourceName)
{
	String^ ConnStr			= nullptr;	//To store the reformated connection string,intializes to nullptr
	int ConnectionStatus	= 0;		//return result onnection can be established or not

	ConnStr  = String::Format(CrxCommon::gCI,CrxDbStructInternal::DbConnectionFormat , serverName, DBname);
	
	ConnString = ConnStr;//initialize _connString for further use in the application
	DataProviderType = sourceName;//initialize _dbType for further use in the application

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
		if(sourceName->Equals(CrxDbStructInternal::SqlClient))
		{
			_objDB = gcnew SqlDatabase(ConnStr);
		}
		else if(sourceName->Equals(CrxDbStructInternal::OracleClient))	
		{
			_objDB = gcnew Oracle::OracleDatabase(ConnStr);
		}		
		/* Similarly further databases can be added (if required)*/

		return ConnectionStatus;
		
	}	
	catch(Exception^)
	{
		//throw the exception
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrDbMgrConversionErrCd, CrxStructCommonResourceMsg::CrxErrDbMgrNoProvider, ErrorSeverity::Exception);
	}
	
}
//Check Connection can be established as per provided string and source name
int CrxDBManager::CheckConnection(String^ serverName, String^ sourceName)
{
	String^ ConnStr		= nullptr;	//To store the reformated connection string,intializes to nullptr
	int ConnectionCheck = 0;		//return result onnection can be established or not
	
	ConnStr  = String::Format(CrxCommon::gCI,CrxDbStructInternal::DbConnectionFormat , serverName, DBname);

	try
	{	
		sourceName = sourceName->ToUpper();

		if(sourceName->Equals(CrxDbStructInternal::SqlClient))
		{
			//Create Connection object to check connection
			SqlConnection^ connection = gcnew SqlConnection(ConnStr);

			//Clear all connected Pools
			connection->ClearAllPools();

			//Open the connection to check connection can be established or not
			connection->Open();

			//Close the connection after check
			connection->Close();
		}	
		//TODO Create connection for Oracle connection to check database is connected or not
		else if(sourceName->Equals(CrxDbStructInternal::OracleClient))	
		{
			//Create Connection object to check connection
			
		}


		return ConnectionCheck;
	}
	catch(Exception^)
	{
		return ConnectionCheck = 1;
	}
}

//Add Measurement Record in the database
int CrxDBManager::SavePWVMeasurementDetails(CrxStructPWVMeasurementData^ md)
{
	int result				 = 0;		//initializes to 0, if 1 successful else return zero
	int len					 = 0;		//Get the length of the array
	DbCommand^ addCommand	 = nullptr; // store the stored procedure in addCommand object
	SqlParameter^ parameter  = nullptr;	//creating sqlparameter object to pass parameter values
	array<Byte>^	buffarr;			//Temporary byte array object for manipulation

	try
	{
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter(); 

		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::InsertMeasurementDetails);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,md->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,md->GroupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,md->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Notes,DbType::String,md->Notes);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SP,DbType::Int16,md->SP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DP,DbType::Int16,md->DP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MP,DbType::Int16,md->MP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Operator,DbType::String,md->Operator);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PwvDistance,DbType::Int16,md->PWVDistance);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PwvDistanceMethod,DbType::Int16,md->PWVDistanceMethod);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Carotid,DbType::Int16,md->Carotid);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FemoraltoCuff,DbType::Int16,md->FemoraltoCuff);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Cuff,DbType::Int16,md->Cuff);

		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Simulation,DbType::Boolean,md->Simulation);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BloodPressureRange,DbType::String,md->BloodPressureRange);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BloodPressureEntryOption,DbType::Int16,md->BloodPressureEntryOption);
		
		//get the length of array
		len = md->NormalRange->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->NormalRange);
		//initializing sqlparameter object to pass the parameter value
		parameter->ParameterName = CrxDbStructParametersList::NormalRange;         
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
		parameter  = nullptr;
		parameter  = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::ReferenceRange;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Age,DbType::Int16,md->Age);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::IsStandardDeviationValid,DbType::Boolean,md->IsStandardDeviationValid);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::IsFemoralSignalValid,DbType::Boolean,md->IsFemoralSignalValid);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::IsCarotidSignalValid,DbType::Boolean,md->IsCarotidSignalValid);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Direct,DbType::Int16,md->Direct);

		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CaptureTime,DbType::Int16,md->CaptureTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MeanCorrectedTime,DbType::Single,md->MeanCorrectedTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MeanDeltaTime,DbType::Single,md->MeanDeltaTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MeanHeartRate,DbType::Single,md->MeanHeartRate);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MeanPulseWaveVelocity,DbType::Single,md->MeanPulseWaveVelocity);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SampleRate,DbType::Int16,md->SampleRate);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::StandardDeviation,DbType::Single,md->StandardDeviation);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::WeightInKilograms,DbType::Int16,md->WeightInKilograms);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::WeightInPounds,DbType::Int16,md->WeightInPounds);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::HeightInCentimetres,DbType::Int16,md->HeightInCentimetres);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::HeightInInches,DbType::Int16,md->HeightInInches);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BodyMassIndex,DbType::Single,md->BodyMassIndex);

		//get the length of array
		len = md->CarotidSignalFloatOnSets->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->CarotidSignalFloatOnSets);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::CarotidSignalOnSets;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CarotidSignalOnSetsLength,DbType::Int16,md->CarotidSignalOnSetsLength);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CarotidSignalPulseHeight,DbType::Single,md->CarotidSignalPulseHeight);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CarotidSignalPulseHeightVariation,DbType::Single,md->CarotidSignalPulseHeightVariation);
		
		//get the length of array
		//len = md->CarotidSignal->Length;
		len = md->CarotidSignalLength;

		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(unsigned short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,md->CarotidSignal);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::CarotidSignal;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CarotidSignalLength,DbType::Int16,md->CarotidSignalLength);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CorrectionTime,DbType::Single,md->CorrectionTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DataRevision,DbType::Int16,md->DataRevision);
		
		//get the length of array
		len = md->FemoralSignalFloatOnSets->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->FemoralSignalFloatOnSets);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::FemoralSignalOnSets;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FemoralSignalOnSetsLength,DbType::Int16,md->FemoralSignalOnSetsLength);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FemoralSignalPulseHeight,DbType::Single,md->FemoralSignalPulseHeight);
		
		//get the length of array
		//len = md->FemoralSignal->Length;
		len = md->FemoralSignalLength;

		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(unsigned short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,md->FemoralSignal);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::FemoralSignal;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FemoralSignalLength,DbType::Int16,md->FemoralSignalLength);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::NumberOfDeltas,DbType::Int16,md->NumberOfDeltas);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::NumberOfValidDeltas,DbType::Int16,md->NumberOfValidDeltas);

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		return result;
		
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
	
}

//Add Measurement Record in the database
int CrxDBManager::UpdatePWVMeasurementDetails(CrxStructPWVMeasurementData^ md)
{
	int result						= 0;		//initializes to 0, if 1 successful else return zero
	int len							= 0;		//Get the length of the array
	DbCommand^ addCommand			= nullptr;	// store the stored procedure in addCommand object
	SqlParameter^ parameter;					//creating sqlparameter object to pass parameter values
	array<Byte>^	buffarr;					//Temporary byte array object for manipulation

	try
	{			
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter(); 

		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::UpdateMeasurementDetails);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,md->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,md->GroupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,md->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::StudyDateTime,DbType::DateTime,md->StudyDateTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Notes,DbType::String,md->Notes);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SP,DbType::Int16,md->SP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DP,DbType::Int16,md->DP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MP,DbType::Int16,md->MP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Operator,DbType::String,md->Operator);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PwvDistance,DbType::Int16,md->PWVDistance);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PwvDistanceMethod,DbType::Int16,md->PWVDistanceMethod);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Carotid,DbType::Int16,md->Carotid);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FemoraltoCuff,DbType::Int16,md->FemoraltoCuff);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Cuff,DbType::Int16,md->Cuff);

		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Simulation,DbType::Boolean,md->Simulation);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BloodPressureRange,DbType::String,md->BloodPressureRange);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BloodPressureEntryOption,DbType::Int16,md->BloodPressureEntryOption);
		
		//get the length of array
		len = md->NormalRange->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->NormalRange);
		//initializing sqlparameter object to pass the parameter value
		parameter->ParameterName = CrxDbStructParametersList::NormalRange;         
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
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::ReferenceRange;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Age,DbType::Int16,md->Age);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::IsStandardDeviationValid,DbType::Boolean,md->IsStandardDeviationValid);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::IsFemoralSignalValid,DbType::Boolean,md->IsFemoralSignalValid);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::IsCarotidSignalValid,DbType::Boolean,md->IsCarotidSignalValid);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Direct,DbType::Int16,md->Direct);

		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CaptureTime,DbType::Int16,md->CaptureTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MeanCorrectedTime,DbType::Single,md->MeanCorrectedTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MeanDeltaTime,DbType::Single,md->MeanDeltaTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MeanHeartRate,DbType::Single,md->MeanHeartRate);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MeanPulseWaveVelocity,DbType::Single,md->MeanPulseWaveVelocity);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SampleRate,DbType::Int16,md->SampleRate);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::StandardDeviation,DbType::Single,md->StandardDeviation);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::WeightInKilograms,DbType::Int16,md->WeightInKilograms);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::WeightInPounds,DbType::Int16,md->WeightInPounds);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::HeightInCentimetres,DbType::Int16,md->HeightInCentimetres);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::HeightInInches,DbType::Int16,md->HeightInInches);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BodyMassIndex,DbType::Single,md->BodyMassIndex);

		//get the length of array
		len = md->CarotidSignalFloatOnSets->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->CarotidSignalFloatOnSets);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::CarotidSignalOnSets;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CarotidSignalOnSetsLength,DbType::Int16,md->CarotidSignalOnSetsLength);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CarotidSignalPulseHeight,DbType::Single,md->CarotidSignalPulseHeight);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CarotidSignalPulseHeightVariation,DbType::Single,md->CarotidSignalPulseHeightVariation);
		
		//get the length of array
		//len = md->CarotidSignal->Length;
		len = md->CarotidSignalLength;

		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(unsigned short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,md->CarotidSignal);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::CarotidSignal;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CarotidSignalLength,DbType::Int16,md->CarotidSignalLength);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::CorrectionTime,DbType::Single,md->CorrectionTime);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DataRevision,DbType::Int16,md->DataRevision);
		
		//get the length of array
		len = md->FemoralSignalFloatOnSets->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,md->FemoralSignalFloatOnSets);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::FemoralSignalOnSets;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FemoralSignalOnSetsLength,DbType::Int16,md->FemoralSignalOnSetsLength);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FemoralSignalPulseHeight,DbType::Single,md->FemoralSignalPulseHeight);
		
		//get the length of array
		//len = md->FemoralSignal->Length;
		len = md->FemoralSignalLength;

		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(unsigned short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,md->FemoralSignal);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructParametersList::FemoralSignal;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FemoralSignalLength,DbType::Int16,md->FemoralSignalLength);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::NumberOfDeltas,DbType::Int16,md->NumberOfDeltas);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::NumberOfValidDeltas,DbType::Int16,md->NumberOfValidDeltas);

		_objDB->AddOutParameter(addCommand,CrxDbStructParametersList::ReturnStudyDatetime,DbType::DateTime,sizeof(DateTime));

		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		md->StudyDateTime = Convert::ToDateTime((_objDB->GetParameterValue(addCommand,CrxDbStructParametersList::ReturnStudyDatetime)),CrxCommon::gCI);

		return result;
		
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
	
}

int CrxDBManager::DeletePWVMeasurementDetails(CrxStructPWVMeasurementData^ md, String^ studyDateTimeArrStr)
{
	int result			  = 0;			//initializes to 0, if 1 successful else return zero
	DbCommand^ addCommand = nullptr;	// store the stored procedure in addCommand object
	 
	try
	{
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::DeleteMeasurementDetails);

		//Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,md->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,md->GroupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,md->PatientNumberInternal);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::StudyDateTimeArrStr,DbType::String,studyDateTimeArrStr);
		
		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		return result;
	}

	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
}

//*********************************************//
//Byte array function
array<Byte>^ CrxDBManager::CommonShortArrtoByteArr(int len, array<unsigned short>^ shrtarr)
{
	int val						=	0;	//value to run number of loops
	int byt						=	0;	//value to store data in array location	
	array<Byte>^ bufferarr;				//Temporary byte array object for manipulation
	array<Byte>^ bufferArrRet;			//Temporary byte array object for manipulation and returning

	try
	{
		if(len != 0)
		{		
			//initiaze the size of the array
			bufferArrRet = gcnew array<Byte>(len*sizeof(unsigned short));
			
			for(val=0, byt=0; val<len; val++, byt = byt + CrxDbStructInternal::ShortSize)
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
	catch(Exception^)
	{
		// throw the exception
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrDbMgrConversionErrCd, CrxStructCommonResourceMsg::CrxErrDbMgrConversion, ErrorSeverity::Exception);
	} 
}
//*********************************************//
array<Byte>^ CrxDBManager::CommonShortArrtoByteArr(int len, array<short>^ shrtarr)
{
	int val						=	0;	//value to run number of loops
	int byt						=	0;	//value to store data in array location	
	array<Byte>^ bufferarr;				//Temporary byte array object for manipulation
	array<Byte>^ bufferArrRet;			//Temporary byte array object for manipulation and returning

	try
	{
		if(len != 0)
		{		
			//initiaze the size of the array
			bufferArrRet = gcnew array<Byte>(len*sizeof(short));
			
			for(val=0, byt=0; val<len; val++, byt = byt + CrxDbStructInternal::ShortSize)
			{
				bufferarr = BitConverter::GetBytes(shrtarr[val]);			
				bufferArrRet[byt] = bufferarr[0];
				bufferArrRet[byt+1] = bufferarr[1];
			}
		}
		else
		{
			bufferArrRet = gcnew array<Byte>(len*sizeof(short));
		}
		return bufferArrRet;
	}
	catch(Exception^)
	{
		// throw the exception
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrDbMgrConversionErrCd, CrxStructCommonResourceMsg::CrxErrDbMgrConversion, ErrorSeverity::Exception);
	} 
}
//*********************************************//
array<Byte>^ CrxDBManager::CommonFloatArrtoByteArr(int len, array<float>^ fltarr)
{
	int val						=	0;	//value to run number of loops
	int byt						=	0;	//value to store data in array location	
	array<Byte>^ bufferarr;				//Temporary byte array object for manipulation
	array<Byte>^ bufferArrRet;			//Temporary byte array object for manipulation and returning
	float tempflt				= 0.0f;	//Temporary float vlaue for storing rounded decimal value

	try
	{
		if(len != 0)
		{		
			//initiaze the size of the array
			bufferArrRet = gcnew array<Byte>(len*sizeof(float));
			
			for(val=0, byt=0; val<len; val++, byt= byt + CrxDbStructInternal::FloatSize)
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
			bufferArrRet = gcnew array<Byte>(len*sizeof(float));
		}
		return bufferArrRet;
	}
	catch(Exception^)
	{
		// throw the exception
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrDbMgrConversionErrCd, CrxStructCommonResourceMsg::CrxErrDbMgrConversion, ErrorSeverity::Exception);
	} 
}


//*********************************************//
//**************************************
//Varbinary to related arrays
//Common function

array<float>^ CrxDBManager::CommonByteArrtoFloatArr(int len, array<Byte>^ bytearr)
{
	int val						= 0;	//value to run number of loops
	int arr						= 0;	//value to get data in array location
	float value					= 0.0f;	//Temporary value for the manipulation	
	array<float>^  tempbuffer;			//Temporary float array object for manipulation and returning

	try
	{
		//initiaze the size of the array
		tempbuffer = gcnew array<float>(len);

		for(val=0, arr=0; val<len; val++, arr = arr + CrxDbStructInternal::FloatSize )
		{		
			value = BitConverter::ToSingle(bytearr,arr);			
			tempbuffer[val] = value;
		}

		return tempbuffer;
	}
	catch(Exception^)
	{
		// throw the exception
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrDbMgrConversionErrCd, CrxStructCommonResourceMsg::CrxErrDbMgrConversion, ErrorSeverity::Exception);
	} 
}

array<unsigned short>^ CrxDBManager::CommonByteArrtoShortArr(int len, array<Byte>^ bytearr)
{
	int val								= 0;	//value to run number of loops
	int arr								= 0;	//value to get data in array location
	short value							= 0;	//Temporary value for the manipulation	
	array<unsigned short>^  tempbuffer;		//Temporary short array object for manipulation and returning

	try
	{
		//initiaze the size of the array
		tempbuffer = gcnew array<unsigned short>(len);

		for(val=0, arr=0; val<len; val++, arr = arr + CrxDbStructInternal::ShortSize )
		{		
			value = BitConverter::ToUInt16(bytearr,arr);		
			tempbuffer[val] = value;
		}

		return tempbuffer;
	}
	catch(Exception^)
	{
		// throw the exception
		throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrDbMgrConversionErrCd, CrxStructCommonResourceMsg::CrxErrDbMgrConversion, ErrorSeverity::Exception);
	} 
}

int CrxDBManager::DatabaseBackup(System::String ^filePath)
{
	int result						= 1;		//initializes to 1, if 0 successful else not
	DbCommand^ addCommand			= nullptr;	// store the stored procedure in addCommand object
	String^ errorMessage			= nullptr;	//To store the error message string to be logged in the scor.log file
	CrxLogger^ objLog				= nullptr;	// Object used to access logger class

	//Create logger object
	objLog = CrxLogger::Instance;
	
	try
	{		
		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::BackUpDatabase);

		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FilePath,DbType::String,filePath);
		
		//Execute stored procedure and return int result backup successful or not
		result = _objDB->ExecuteNonQuery(addCommand);	

		//If the result is -1 then the Backup is successful, so set result to 0 
		if(result < 0)
		{
			result = 0;
		}

		return result;		
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(ErrorSeverity::Exception,eObj,CrxStructCommonResourceMsg::ContactAtcorSupport2);
	}
	finally
	{
		if(result == 0)
		{
			errorMessage = CrxDbStructInternal::BackupDone;
		}
		else
		{
			errorMessage = CrxDbStructInternal::BackupFail;
		}	
		objLog->Write(errorMessage);
	}
}
int CrxDBManager::DatabaseRestore(System::String ^filePath)
{
	int result					= 1;		//initializes to 1, if 0 successful else not
	DbCommand^ addCommand		= nullptr;  //To store the stored procedure in addCommand object
	String^ filePathSet			= nullptr;  //To store the reformated connection string,intializes to nullptr
	String^ errorMessage		= nullptr;	//To store the error message string to be logged in the scor.log file
	CrxLogger^ objLog			= nullptr;  // Object used to access logger class

	filePathSet  = String::Format(CrxCommon::gCI,CrxDbStructInternal::ZeroParameterFormat , filePath);

	//Create logger object
	objLog = CrxLogger::Instance;

	try
	{		
		//TODO Restore String to be replaced with String Format type
		String^ restoreQuery = String::Format(CrxCommon::gCI,CrxDbStructInternal::DbRestoreFormat, DBname , filePathSet);
		addCommand = _objDB->GetSqlStringCommand(restoreQuery);
		result = _objDB->ExecuteNonQuery(addCommand);	

		//If the result is -1 then the Backup is successful, so set result to 0 
		if(result < 0)
		{
			result = 0;
		}
    
		return result;
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{		
		// throw the exception
		throw gcnew ScorException(ErrorSeverity::Exception,eObj,CrxStructCommonResourceMsg::ContactAtcorSupport2);
	}
	finally
	{
		if(result == 0)
		{
			errorMessage = CrxDbStructInternal::RestoreDone;
		}
		else
		{
			errorMessage = CrxDbStructInternal::RestoreFail;
		}	
		objLog->Write(errorMessage);
	}
}

//void CrxDBManager::ResetDatabaseToMultiuser()
//{
//	DbCommand^ addCommand	= nullptr; // store the stored procedure in addCommand object
//	CrxLogger^ objLog		= nullptr; // Object used to access logger class
//
//	//Create logger object
//	objLog = CrxLogger::Instance;
//
//	try
//	{		
//		addCommand = _objDB->GetSqlStringCommand("USE [master]" + " ALTER DATABASE " + DBname +  " SET MULTI_USER" + " USE [" + DBname + "]" ); 
//		
//		_objDB->ExecuteNonQuery(addCommand);
//
//		CrxMessagingManager^ oMsgMgr = CrxMessagingManager::Instance;
//		String^ errorMessage = oMsgMgr->GetMessage("RESTORE_DONE");
//		objLog->Write(errorMessage);
//
//	}
//	catch(Exception^)
//	{		
//		// throw customised exception
//		throw gcnew ScorException(CRX_ERR_DBPERMISSION_REFER_MANUAL, "CRX_ERR_DBPERMISSION_REFER_MANUAL", ErrorSeverity::Exception);// File not found
//	}
//				
//
//}

int CrxDBManager::MigrateAtCorData(int systemIdentifier, String^ groupName)
{
	//Variables Declaration
	OleDbConnection^ conn		= nullptr; // Object to store connection
	OleDbCommand^ cmd			= nullptr; // Object to store execute command
	OleDbDataReader^ rdr		= nullptr; // Object to store data reader value
	CrxLogger^ objLog			= nullptr; // Object used to access logger class
	
	int result					= 0;		// returns result value	
	int rowNum					= 0;		// stores number of rows in the migration file
	int	migrationFileType		= 0;		// stores the migration filetype
	
	String^ filePathSet			= nullptr; // stores the formatted file path location
	String^ migrationFileName	= nullptr; // stores the migration file name

	try
	{
		//Check whether file is exists or not		
		migrationFileType = MigrationFileExistInternal();		
		
		//Check whether old file is exists or not, then delete the old file
		RemoveOldAccessFile(migrationFileType);
		
		//Returns the migration file name to be migrated
		migrationFileName = MigrationFileName(migrationFileType);
		
		//Set the path for MS-Access Connection path
		filePathSet  = String::Format(CrxCommon::gCI,CrxDbStructInternal::MsAccessConnectionFormat , migrationFileName);
		
		//Create logger object
		objLog = CrxLogger::Instance;

		//Create an Connection object
		conn = gcnew OleDbConnection(filePathSet);

		//Open the connection
		conn->Open();

		//Create an OleDbCommand object and
		//pass it the SQL command and the OleDbConnection
		//object to use to connect to the database

		//Executing query to get number of records
		cmd = gcnew OleDbCommand(CrxDbStructInternal::MsAccessQueryCount,conn);

		//Create the reader object
		rdr = cmd->ExecuteReader();

		rdr->Read();

		//Get number of rows in the migration file
		rowNum = Convert::ToInt32(rdr->GetValue(0),CrxCommon::gCI);
		rdr->Close();
		rdr	= nullptr;

		//Executing query to get number patient records
		cmd = gcnew OleDbCommand(CrxDbStructInternal::MsAccessQueryAllRecord,conn);
		
		//Create the reader object
		rdr = cmd->ExecuteReader();		
	
		result = MigrationInternal(rdr, objLog, rowNum, systemIdentifier, groupName);

		rdr->Close();
		
		//Close the connection to the MS-Access database
		conn->Close();
		
		//After closing connection it takes time to close intermediate file (scor.ldb), so we are delaying processing by 2 seconds
		Thread::Sleep(CrxDbStructInternal::AppWaitTime);
		
		//Rename the migration file from scor.xyz to scor.xyz.old
		if(result == 0)
		{	
			//Rename the migration file
			MigrationFileRename(migrationFileType);
		}

		return result;
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;		
	}

	catch(IOException^ eObj)
	{
		objLog->Write(CrxDbStructInternal::MigrationRenameError);
		throw gcnew ScorException(eObj);
	}

	catch(Exception^ eObj)
	{		
		throw gcnew ScorException(eObj);
	}

	finally
	{
		//Close the connection to the database
		if(conn)
		{
			conn->Close();
		}		
	}

}
bool CrxDBManager::MigrationFileExist()
{
	bool result = true;//initializes to true, if true exist else not exist

	try
	{
		//Check whether file is exists or not
		//if(!File::Exists(CrxDbStructInternal::NameOfAccessFile))
		if(!(File::Exists(CrxDbStructInternal::NameOfAccessFile) || File::Exists(CrxDbStructInternal::NameOfMSAccessFile)))
		{ 
			result = false;
		}     
		return result;
	}
	catch(Exception^)
	{
		return result = false;
	}
}

int CrxDBManager::MigrationInternal(OleDbDataReader ^rdr, CrxLogger^ objLog, int rowNum, int systemIdentifier, System::String ^groupName)
{
	DbCommand^ addCommand			= nullptr;	// store the stored procedure in addCommand object
	DbTransaction^ dbtransaction	= nullptr;	// stores the transaction in the dbtransaction object
	DbConnection^ dbconnection		= nullptr;	// stores the connection object from database object

	int result						= 0;		// returns result value
	int totresult					= 0;		// stores total patient migrated
	int totskipresult				= 0;		// stores total patient skipped	

	
	String^ strFName				= nullptr;	// stores the patient first name
	String^ strLName				= nullptr;	// stores the patient last name
	String^ strPatientExtName		= nullptr;	// stores patient external name
	String^ details					= nullptr;	// stores the patient header details
	String^ strGender				= nullptr;	// stores the gender value
	String^ totDetailsMigrated		= nullptr;	// stores the total patient migrated header
	String^ totDetailsSkipped		= nullptr;	// stores the total patient skipped header
	String^ patDetails				= nullptr;	// stores the skipped patient details
	String^ srtDate					= nullptr;	// stores short date
	
	DateTime strDOB;							// stores the date of birth of patient

	try
	{
		//Create dbConnection
		dbconnection = _objDB->CreateConnection();

		//Create dbconnection command
		addCommand = dbconnection->CreateCommand();		

		//Open DBConnection object
		dbconnection->Open();

		//Create and begin transaction
		dbtransaction = dbconnection->BeginTransaction();

		objLog->Write(CrxDbStructInternal::MigrationStartedStr);
		details = CrxDbStructInternal::MigrationPatientListHeaderFormat;
		objLog->Write(details);
		details = nullptr;

		array<String^>^ skipPatientlog = gcnew array<String^>(rowNum);

		//Keep reading records in the forward direction
		while (rdr->Read())
		{		   
		   //Reinitialize the values
			strFName			= nullptr;
			strLName			= nullptr;
			strPatientExtName	= nullptr;
			strGender			= nullptr;
			patDetails			= nullptr;
			srtDate				= nullptr;
			details				= nullptr;
			result				= 0;
			
			strPatientExtName	= rdr->GetValue((Convert::ToInt32(CrxDBMsAccessPatientInfo::DBMgrColumnPatExtName,CrxCommon::gCI)))->ToString();
			strLName			= rdr->GetValue((Convert::ToInt32(CrxDBMsAccessPatientInfo::DBMgrColumnPatLastName,CrxCommon::gCI)))->ToString();
			strFName			= rdr->GetValue((Convert::ToInt32(CrxDBMsAccessPatientInfo::DBMgrColumnPatFirstName,CrxCommon::gCI)))->ToString();
			strDOB				= Convert::ToDateTime(rdr->GetValue((Convert::ToInt32(CrxDBMsAccessPatientInfo::DBMgrColumnPatDob,CrxCommon::gCI))),CrxCommon::gCI);
			strGender			= rdr->GetValue((Convert::ToInt32(CrxDBMsAccessPatientInfo::DBMgrColumnPatGender,CrxCommon::gCI)))->ToString();		
			
			//get the Stored Procedure query using database object
			addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::MigratePatientDetails);

			_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,systemIdentifier);
			_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientIDExternalReference,DbType::String,strPatientExtName);
			_objDB->AddInParameter(addCommand,CrxDbStructParametersList::LastName,DbType::String,strLName);
			_objDB->AddInParameter(addCommand,CrxDbStructParametersList::FirstName,DbType::String,strFName);
			_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DateOfBirth,DbType::DateTime,strDOB);
			_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Gender,DbType::String,strGender);
			_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupName,DbType::String,groupName);

			//Execute stored procedure and return positive value if successful
			result = _objDB->ExecuteNonQuery(addCommand,dbtransaction);	

			if(result > 0)
			{
				totresult = totresult + 1;
			}
			else
			{
				//Log the skipped patient details in the scor.log file
				srtDate =  strDOB.ToShortDateString();
				details = String::Empty;
				patDetails = String::Format(CrxDbStructInternal::MigrationPatientListFormat , details->PadRight(18), strPatientExtName->PadRight(10), strFName->PadRight(25), strLName->PadRight(25), strGender->PadRight(6), srtDate);
				skipPatientlog[totskipresult] = patDetails;
				totskipresult = totskipresult + 1;	
			}			
		}	
		
		// Commit the transaction.
		dbtransaction->Commit();

		dbconnection->Close();	

		MigrationLogDetail(objLog, skipPatientlog , totskipresult);

		totDetailsMigrated = String::Format(CrxDbStructInternal::MigrationPatientTotMigratedFormat,totresult); 
		totDetailsSkipped = String::Format(CrxDbStructInternal::MigrationPatientTotSkippedFormat,totskipresult); 
		objLog->Write(totDetailsSkipped);
		objLog->Write(totDetailsMigrated);	

		objLog->Write(CrxDbStructInternal::MigrationCompletedStr);

		return result = 0;	
	}
	catch(Exception^)
	{
		objLog->Write(CrxDbStructInternal::MigrationFailedStr);	

		try
		{
			// Roll back the transaction.
			dbtransaction->Rollback();		
		}
		catch(Exception^)
		{
			// throw customised exception
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrMigrationReferManualErrCd, CrxStructCommonResourceMsg::CrxErrMigrationReferManual, ErrorSeverity::Exception);
		}

		return result = 1;	
	}
	finally
	{			
		if(dbconnection)
		{
			dbconnection->Close();
		}	
	}
}

void CrxDBManager::MigrationLogDetail(CrxLogger^ objLog, array<String^>^ skipPatientlog, int totskipresult)
{
	//Log total patient migrated and skipped in the scor.log file
	for(int arr= 0; arr < totskipresult; arr++ )
	{		
		objLog->Write(skipPatientlog[arr]);
	}
}

int CrxDBManager::MigrationFileExistInternal()
{
	int result = 0;//initializes to true, if true exist else not exist

	try
	{
		//Check whether file is exists or not
		if(File::Exists(CrxDbStructInternal::NameOfAccessFile))
		{ 
			result = Convert::ToInt32(CrxDBAccessFileNameList::ScorXyzFileType,CrxCommon::gCI);
		}
		else if(File::Exists(CrxDbStructInternal::NameOfMSAccessFile))
		{
			result = Convert::ToInt32(CrxDBAccessFileNameList::ScorMdbFileType,CrxCommon::gCI);
		}
		else
		{
			result = Convert::ToInt32(CrxDBAccessFileNameList::MigrationFileNotPresent,CrxCommon::gCI);
		}

		//return result;
	}
	catch(Exception^)
	{
		//return result = false;
		result = Convert::ToInt32(CrxDBAccessFileNameList::MigrationFileNotPresent,CrxCommon::gCI);
	}
	finally
	{
		if(result == Convert::ToInt32(CrxDBAccessFileNameList::MigrationFileNotPresent,CrxCommon::gCI))
		{
			throw gcnew ScorException(CrxStructCommonResourceMsg::CrxErrMsAccessFileNotExistErrCd, CrxStructCommonResourceMsg::CrxErrMsAccessFileNotExist, ErrorSeverity::Exception);// File not found
		}		
	}
	return result;
}

void CrxDBManager::RemoveOldAccessFile(int fileType)
{
	if(fileType == Convert::ToInt32(CrxDBAccessFileNameList::ScorXyzFileType,CrxCommon::gCI))
	{ 
		File::Delete(CrxDbStructInternal::NameOfAccessFileNew);
	}
	else
	if(fileType == Convert::ToInt32(CrxDBAccessFileNameList::ScorMdbFileType,CrxCommon::gCI))
	{ 
		File::Delete(CrxDbStructInternal::NameOfMSAccessFileNew);
	}
}

String^ CrxDBManager::MigrationFileName(int fileType)
{
	String^ tempFileName = String::Empty;

	if(fileType == Convert::ToInt32(CrxDBAccessFileNameList::ScorXyzFileType,CrxCommon::gCI))
	{ 
		tempFileName = CrxDbStructInternal::NameOfAccessFile;
	}
	else
	if(fileType == Convert::ToInt32(CrxDBAccessFileNameList::ScorMdbFileType,CrxCommon::gCI))
	{ 
		tempFileName = CrxDbStructInternal::NameOfMSAccessFile;
	}

	return tempFileName;
}

void CrxDBManager::MigrationFileRename(int fileType)
{
	if(fileType == Convert::ToInt32(CrxDBAccessFileNameList::ScorXyzFileType,CrxCommon::gCI))
	{ 
		File::Move(CrxDbStructInternal::NameOfAccessFile,CrxDbStructInternal::NameOfAccessFileNew);
	}
	else
	if(fileType == Convert::ToInt32(CrxDBAccessFileNameList::ScorMdbFileType,CrxCommon::gCI))
	{ 
		File::Move(CrxDbStructInternal::NameOfMSAccessFile,CrxDbStructInternal::NameOfMSAccessFileNew);
	}
}


int CrxDBManager::SaveCuffPWAMeasurementDetails(AtCor::Scor::CrossCutting::DatabaseManager::CrxStructPWAMeasurementData ^pwaMD, AtCor::Scor::CrossCutting::DatabaseManager::CrxStructCuffPWAMeasurementData ^cuffPwaMD)
{
	int result				 = 0;		//initializes to 0, if 1 successful else return zero
	int len					 = 0;		//Get the length of the array
	DbCommand^ addCommand	 = nullptr; // store the stored procedure in addCommand object
	SqlParameter^ parameter  = nullptr;	//creating sqlparameter object to pass parameter values
	array<Byte>^	buffarr;			//Temporary byte array object for manipulation

	try
	{		
		//initializing sqlparameter object to pass the parameter value
		parameter = gcnew SqlParameter(); 

		//get the Stored Procedure query using database object
		addCommand = _objDB->GetStoredProcCommand(CrxDbStructSpList::InsertCuffPWAMeasurementDetails);

		////Adding input parameters in the DbCommand object to execute stored procedure
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SystemIdentifier,DbType::Int32,pwaMD->SystemIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::GroupIdentifier,DbType::Int32,pwaMD->GroupIdentifier);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::PatientNumberInternal,DbType::Int32,pwaMD->PatientNumberInternal);
		//_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::AuditChange,DbType::DateTime,pwaMD->AuditChange);

		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BloodPressureRange,DbType::String,pwaMD->BloodPressureRange);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BloodPressureEntryOption,DbType::Int16,pwaMD->BloodPressureEntryOption);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Age,DbType::Int16,pwaMD->Age);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Notes,DbType::String,pwaMD->Notes);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::SP,DbType::Int16,pwaMD->SP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::DP,DbType::Int16,pwaMD->DP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::MP,DbType::Int16,pwaMD->MP);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::Operator,DbType::String,pwaMD->Operator);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::WeightInKilograms,DbType::Int16,pwaMD->WeightInKilograms);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::WeightInPounds,DbType::Int16,pwaMD->WeightInPounds);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::HeightInCentimetres,DbType::Int16,pwaMD->HeightInCentimetres);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::HeightInInches,DbType::Int16,pwaMD->HeightInInches);
		_objDB->AddInParameter(addCommand,CrxDbStructParametersList::BodyMassIndex,DbType::Single,pwaMD->BodyMassIndex);

		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::MemSpare1,DbType::String,pwaMD->MemSpare1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::MemSpare2,DbType::String,pwaMD->MemSpare2);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::Simulation,DbType::Boolean,pwaMD->Simulation);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::IntSpare2,DbType::Int32,pwaMD->IntSpare2);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::FloatSpare1,DbType::Single,pwaMD->FloatSpare1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::DataRev,DbType::Int32,pwaMD->DataRev);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::SubType,DbType::String,pwaMD->SubType);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::CaptureTime,DbType::String,pwaMD->CaptureTime);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::SampleRate,DbType::Int32,pwaMD->SampleRate);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::SignalUpSampleRate,DbType::Int32,pwaMD->SignalUpSampleRate);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::ExpPulseUpSampleRate,DbType::Int32,pwaMD->ExpPulseUpSampleRate);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::Flow,DbType::Int32,pwaMD->Flow);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::Medication,DbType::String,pwaMD->Medication);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::Message,DbType::String,pwaMD->Message);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::Units,DbType::String,pwaMD->Units);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::CalSP,DbType::Int32,pwaMD->CalSP);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::CalDP,DbType::Int32,pwaMD->CalDP);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::CalMP,DbType::Int32,pwaMD->CalMP);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::HR,DbType::Int32,pwaMD->HR);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::ED,DbType::Int32,pwaMD->ED);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::CalcED,DbType::Int32,pwaMD->CalcED);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::QualityED,DbType::Int32,pwaMD->QualityED);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::EDMin,DbType::Int32,pwaMD->EDMin);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::EDMax,DbType::Int32,pwaMD->EDMax);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::EDOther,DbType::Int32,pwaMD->EDOther);	
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::CaptureInput,DbType::Int16,pwaMD->CaptureInput);
		
		//get the length of array
		len = pwaMD->C_RAW_SIGNALS->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,pwaMD->C_RAW_SIGNALS);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_Raw_Signals;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = pwaMD->C_AV_PULSE->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,pwaMD->C_AV_PULSE);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_Av_Pulses;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = pwaMD->C_TRIGS->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,pwaMD->C_TRIGS);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_Trigs;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = pwaMD->C_ONSETS->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,pwaMD->C_ONSETS);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_Onsets;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
				
		//get the length of array
		len = pwaMD->C_Uncal_Av->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,pwaMD->C_Uncal_Av);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_Uncal_Av;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = pwaMD->C_ResemblePulse->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,pwaMD->C_ResemblePulse);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_ResemblePulse;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);		

		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Ole_Spare,DbType::String,pwaMD->C_Ole_Spare);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Math_Params,DbType::Int32,pwaMD->C_Math_Params);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Sp,DbType::Single,pwaMD->C_Sp);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Dp,DbType::Single,pwaMD->C_Dp);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Meanp,DbType::Single,pwaMD->C_Meanp);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T1,DbType::Single,pwaMD->C_T1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T2,DbType::Single,pwaMD->C_T2);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T1i,DbType::Single,pwaMD->C_T1i);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T1r,DbType::Single,pwaMD->C_T1r);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T1m,DbType::Single,pwaMD->C_T1m);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T1other,DbType::Single,pwaMD->C_T1other);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T2i,DbType::Single,pwaMD->C_T2i);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T2R,DbType::Single,pwaMD->C_T2R);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T2M,DbType::Single,pwaMD->C_T2M);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T2Other,DbType::Single,pwaMD->C_T2Other);
		
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Quality_T1,DbType::Int32,pwaMD->C_Quality_T1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Quality_T2,DbType::Int32,pwaMD->C_Quality_T2);

		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_P1,DbType::Single,pwaMD->C_P1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_P2,DbType::Single,pwaMD->C_P2);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T1ED,DbType::Single,pwaMD->C_T1ED);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_T2ED,DbType::Single,pwaMD->C_T2ED);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Ai,DbType::Single,pwaMD->C_Ai);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Esp,DbType::Single,pwaMD->C_Esp);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Ap,DbType::Single,pwaMD->C_Ap);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Mps,DbType::Single,pwaMD->C_Mps);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Mpd,DbType::Single,pwaMD->C_Mpd);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Tti,DbType::Single,pwaMD->C_Tti);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Dti,DbType::Single,pwaMD->C_Dti);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Svi,DbType::Single,pwaMD->C_Svi);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Period,DbType::Single,pwaMD->C_Period);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Dd,DbType::Single,pwaMD->C_Dd);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_EdPeriod,DbType::Single,pwaMD->C_EdPeriod);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_DdPeriod,DbType::Single,pwaMD->C_DdPeriod);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Ph,DbType::Single,pwaMD->C_Ph);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_P1_Height,DbType::Single,pwaMD->C_P1_Height);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Agph,DbType::Single,pwaMD->C_Agph);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Qc_Other1,DbType::Single,pwaMD->C_Qc_Other1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Qc_Other2,DbType::Single,pwaMD->C_Qc_Other2);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Qc_Other3,DbType::Single,pwaMD->C_Qc_Other3);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Qc_Other4,DbType::Single,pwaMD->C_Qc_Other4);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_IntSpare1,DbType::Int32,pwaMD->C_IntSpare1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_IntSpare2,DbType::Int32,pwaMD->C_IntSpare2);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_FloatSpare1,DbType::Single,pwaMD->C_FloatSpare1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_FloatSpare2,DbType::Single,pwaMD->C_FloatSpare2);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_MemSpare1,DbType::Single,pwaMD->C_MemSpare1);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_MemSpare2,DbType::Single,pwaMD->C_MemSpare2);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Al,DbType::Single,pwaMD->C_Al);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Ati,DbType::Single,pwaMD->C_Ati);

		//get the length of array
		len = pwaMD->C_Flow->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,pwaMD->C_Flow);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_Flow;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = pwaMD->C_Forward->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,pwaMD->C_Forward);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_Forward;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = pwaMD->C_Backward->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,pwaMD->C_Backward);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructPwaParametersList::C_Backward;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);
		
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Avi,DbType::Single,pwaMD->C_Avi);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Pptt,DbType::Single,pwaMD->C_Pptt);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Avd,DbType::Single,pwaMD->C_Avd);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Pwv,DbType::Single,pwaMD->C_Pwv);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Forward_Area,DbType::Single,pwaMD->C_Forward_Area);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Backward_Area,DbType::Single,pwaMD->C_Backward_Area);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Area_Ratio,DbType::Single,pwaMD->C_Area_Ratio);
		_objDB->AddInParameter(addCommand,CrxDbStructPwaParametersList::C_Pulse_Ratio,DbType::Single,pwaMD->C_Pulse_Ratio);

		/////////////////////
		//Cuff PWA Measurement Input
		/////////////////////

		//get the length of array
		len = cuffPwaMD->P_RAW_SIGNALS->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,cuffPwaMD->P_RAW_SIGNALS);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructCuffPwaParametersList::P_Raw_Signals;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = cuffPwaMD->P_AV_PULSE->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,cuffPwaMD->P_AV_PULSE);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructCuffPwaParametersList::P_Av_Pulses;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

	
		//get the length of array
		len = cuffPwaMD->P_TRIGS->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,cuffPwaMD->P_TRIGS);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructCuffPwaParametersList::P_Trigs;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = cuffPwaMD->P_ONSETS->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(short));
		//Calling common function convert to byte array
		buffarr = CommonShortArrtoByteArr(len,cuffPwaMD->P_ONSETS);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructCuffPwaParametersList::P_Onsets;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = cuffPwaMD->P_UNCAL_AV->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,cuffPwaMD->P_UNCAL_AV);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructCuffPwaParametersList::P_Uncal_Av;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);

		//get the length of array
		len = cuffPwaMD->P_ResemblePulse->Length;
		//initiaze the size of the array
		buffarr = gcnew array<Byte>(len*sizeof(float));
		//Calling common function convert to byte array
		buffarr = CommonFloatArrtoByteArr(len,cuffPwaMD->P_ResemblePulse);
		//initializing sqlparameter object to pass the parameter value
		parameter = nullptr;
		parameter = gcnew SqlParameter();
		parameter->ParameterName = CrxDbStructCuffPwaParametersList::P_ResemblePulse;         
		parameter->SqlDbType = SqlDbType::VarBinary;  	
		parameter->Direction = ParameterDirection::Input;         
		parameter->Value = buffarr;
		addCommand->Parameters->Add(parameter);		

		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Ole_Spare,DbType::String,cuffPwaMD->P_OLE_SPARE);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Math_Params,DbType::Int32,cuffPwaMD->P_MATH_PARAMS);

		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Sp,DbType::Single,cuffPwaMD->P_SP);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Dp,DbType::Single,cuffPwaMD->P_DP);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Meanp,DbType::Single,cuffPwaMD->P_MEANP);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_T1i,DbType::Single,cuffPwaMD->P_T1I);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_T1r,DbType::Single,cuffPwaMD->P_T1R);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_T1m,DbType::Single,cuffPwaMD->P_T1M);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_T1other,DbType::Single,cuffPwaMD->P_T1Other);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_T2i,DbType::Single,cuffPwaMD->P_T2I);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_T2r,DbType::Single,cuffPwaMD->P_T2R);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_T2m,DbType::Single,cuffPwaMD->P_T2M);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_T2other,DbType::Single,cuffPwaMD->P_T2Other);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Max_Dpdt,DbType::Single,cuffPwaMD->P_MAX_DPDT);

		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Memspare1,DbType::Single,cuffPwaMD->P_MEMSPARE1);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Memspare2,DbType::Single,cuffPwaMD->P_MEMSPARE2);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Intspare1,DbType::Int32,cuffPwaMD->P_INTSPARE1);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Intspare2,DbType::Int32,cuffPwaMD->P_INTSPARE2);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Floatspare1,DbType::Single,cuffPwaMD->P_FLOATSPARE1);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Floatspare2,DbType::Single,cuffPwaMD->P_FLOATSPARE2);

		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Noise_Factor,DbType::Int32,cuffPwaMD->P_NOISE_FACTOR);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Qc_Ph,DbType::Single,cuffPwaMD->P_QC_PH);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Qc_Phv,DbType::Single,cuffPwaMD->P_QC_PHV);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Qc_Plv,DbType::Single,cuffPwaMD->P_QC_PLV);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Qc_Dv,DbType::Single,cuffPwaMD->P_QC_DV);

		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Qc_Other1,DbType::Single,cuffPwaMD->P_QC_OTHER1);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Qc_Other2,DbType::Single,cuffPwaMD->P_QC_OTHER2);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Qc_Other3,DbType::Single,cuffPwaMD->P_QC_OTHER3);
		_objDB->AddInParameter(addCommand,CrxDbStructCuffPwaParametersList::P_Qc_Other4,DbType::Single,cuffPwaMD->P_QC_OTHER4);		
		
		//Execute stored procedure and return int result how many rows affected
		result = _objDB->ExecuteNonQuery(addCommand);	

		if(result > 0)
		{
			result = 1;
		}

		return result;
		
	}
	catch(ScorException^ crxObj)
	{
		// rethrow the exception
		throw crxObj;
	}
	catch(Exception^ eObj)
	{
		// throw the exception
		throw gcnew ScorException(eObj);
	}
}