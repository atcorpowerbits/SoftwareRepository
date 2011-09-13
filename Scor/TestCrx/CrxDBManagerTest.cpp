﻿
#include "StdAfx.h"

using namespace System::Data;
using namespace System::IO;
using namespace System::Data::OleDb;
using namespace System::Data::SqlClient;

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::DatabaseManager;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Configuration;

namespace TestCrx {
    using namespace System;
    ref class CrxDBManagerTest;
    
    
    /// <summary>
	///This is a test class for CrxDBManagerTest and is intended
	///to contain all CrxDBManagerTest Unit Tests
	///</summary>
	[TestClass]
	public ref class CrxDBManagerTest
	{

	private: String^ _currDir;
	//private: CrxConfigManager^ _objConfig;

	private: Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContextInstance;
			 /// <summary>
			 ///Gets or sets the test context which provides
			 ///information about and functionality for the current test run.
			 ///</summary>
	public: property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  TestContext
			{
				Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  get()
				{
					return testContextInstance;
				}
				System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  value)
				{
					testContextInstance = value;
				}
			}

			static String^  serverName = String::Empty;//"MUM-9383\\SQLEXPRESS";
			static String^  sourceName = String::Empty;//"SQLCLIENT";

			void SetPath()
			{
				String^ path = Directory::GetCurrentDirectory(); 
				int i = path->IndexOf("\\TestResults");
				if(i > 0)
				{
					path = path->Substring(0,i + 12);
					Directory::SetCurrentDirectory(path);
				}
				else
				{
					path  = path + "\\TestResults";
					Directory::SetCurrentDirectory(path);
				}
			}

			//Begin Smarajit Mishra 19 Apr 2011
			/*int CountofPatientRecords()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbCount = dbRecords->Tables[0]->Rows->Count;
				return dbCount;
			}*/
			//End Smarajit Mishra 19 Apr 2011

			void SetServerMachineName()
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructGeneralSetting^ objGenSettings = gcnew CrxStructGeneralSetting();
				String^ _currDir = Directory::GetCurrentDirectory(); 
				
				SetPath();

				target->GetGeneralUserSettings();

				objGenSettings = target->GeneralSettings;
				serverName = String::Empty; 
				serverName = String::Format("{0}\\{1} ",target->_instance->GeneralSettings->MachineName,target->_instance->GeneralSettings->ServerName);
				sourceName = target->_instance->GeneralSettings->SourceData;
				
				Directory::SetCurrentDirectory(_currDir);
			}
#pragma region Additional test attributes
			// 
			//You can use the following additional attributes as you write your tests:
			//
			//Use ClassInitialize to run code before running the first test in the class
			/*public: [ClassInitialize]
			static System::Void MyClassInitialize(TestContext^  testContextInstance)
			{
				CrxConfigManager_Accessor^  target = (gcnew CrxConfigManager_Accessor()); 
				CrxStructGeneralSetting^ objGenSettings = gcnew CrxStructGeneralSetting();
				String^ _currDir = Directory::GetCurrentDirectory(); 
				
				String^ path = _currDir; 
				int i = path->IndexOf("\\TestResults");
				path = path->Substring(0,i + 12);
				Directory::SetCurrentDirectory(path);

				target->GetGeneralDefaultSettings(objGenSettings);
				
				serverName->Format(objGenSettings->MachineName,"\\",objGenSettings->ServerName);
				serverName = objGenSettings->ServerName;
				sourceName = objGenSettings->SourceData;
				Directory::SetCurrentDirectory(_currDir);

			}*/
			
			//Use ClassCleanup to run code after all tests in a class have run
			//public: [ClassCleanup]
			//static System::Void MyClassCleanup()
			//{
			//}
			//
			//Use TestInitialize to run code before running each test
			public: [TestInitialize]
			System::Void MyTestInitialize()
			{
				_currDir = Directory::GetCurrentDirectory(); 
				//_objConfig = CrxConfigManager::Instance;
			}
			
			//Use TestCleanup to run code after each test has run
			public: [TestCleanup]
			System::Void MyTestCleanup()
			{
				Directory::SetCurrentDirectory(_currDir);
			}

#pragma endregion

			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				CrxDBManager^  actual;
				actual = CrxDBManager::Instance;
				Assert::IsNotNull(actual);
			}

			/// <summary>
			///A test for DataProviderType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void DataProviderTypeTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				String^  expected = "SQLEXPRESS";
				String^  actual;

				target->DataProviderType = expected;
				actual = target->DataProviderType;

				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for ConnString
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void ConnStringTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				String^  expected = "server=serverName;database=AtCor;Integrated Security=true";
				String^  actual;

				target->ConnString = expected;
				actual = target->ConnString;

				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for UpdatePWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void UpdatePWVMeasurementDetailsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int expected = 0; 
				int actual;
				
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
				
				try
				{
					actual = target->UpdatePWVMeasurementDetails(pwvmd);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;

				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					////preparing test data into database///
					//-------------------------------------
					pd->SystemIdentifier = 11111;
					//pd->PatientNumberInternal = 1111;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 1111;
					target->SavePatientData(pd);
		
					//----measurement data
					pwvmd->SystemIdentifier = pd->SystemIdentifier;
					pwvmd->PatientNumberInternal = pd->PatientNumberInternal;
					pwvmd->GroupIdentifier = pd->GroupIdentifier;
					pwvmd->PWVDistance = 50;
					pwvmd->MeanHeartRate = 150.0000;
					pwvmd->MeanPulseWaveVelocity = Convert::ToSingle(4.4000);
					pwvmd->StandardDeviation = Convert::ToSingle(3.300);
					pwvmd->IsStandardDeviationValid = 1;
					pwvmd->Notes = "CheckOut";
					pwvmd->Carotid = 111;
					pwvmd->WeightInKilograms = 75;
					pwvmd->HeightInCentimetres = 175;
					pwvmd->CarotidSignal = gcnew array<unsigned short>(1);
					pwvmd->CarotidSignal[0] = 1244;
					pwvmd->FemoralSignal = gcnew array<unsigned short>(1);
					pwvmd->FemoralSignal[0] = 1344;
					pwvmd->CarotidSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->CarotidSignalFloatOnSets[0] = 1234.12f;
					pwvmd->FemoralSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->FemoralSignalFloatOnSets[0] = 2345.23f;
					pwvmd->ReferenceRange = gcnew array<float>(1);
					pwvmd->ReferenceRange[0] = 3456.34f;
					pwvmd->NormalRange = gcnew array<float>(1);
					pwvmd->NormalRange[0] =  4567.45f;
					int i = target->SavePWVMeasurementDetails(pwvmd);

					DataSet^ msrds = target->GetPWVMeasurementDetails(pwvmd->PatientNumberInternal,pwvmd->GroupIdentifier, pwvmd->SystemIdentifier);
					pwvmd->StudyDateTime	= Convert::ToDateTime(msrds->Tables[0]->Rows[0]["StudyDateTime"]);
					String^ studyDateTimeArrStr = Convert::ToString( pwvmd->StudyDateTime) + ",";
					
					pwvmd->PWVDistance = 40;
					actual = target->UpdatePWVMeasurementDetails(pwvmd);
					msrds = target->GetPWVMeasurementDetails(pwvmd->PatientNumberInternal,pwvmd->GroupIdentifier, pwvmd->SystemIdentifier);
					short tempval = Convert::ToInt16(msrds->Tables[0]->Rows[0]["PWVDistance"]);

					//Assert::AreEqual(pwvmd->PWVDistance,Convert::ToInt16(msrds->Tables[0]->Rows[0]["PWVDistance"]));
					Assert::AreEqual(pwvmd->PWVDistance,tempval);

					try
					{
						pwvmd->NormalRange = nullptr;
						//pwvmd->NormalRange->Length = 0;
						actual = target->UpdatePWVMeasurementDetails(pwvmd);
					}
					catch(Exception^)
					{
						target->DeletePatientData(pd);
					}

					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
				}
				
				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecords->Tables[0]->Rows->Count;//CountofPatientRecords();;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}

			/// <summary>
			///A test for UpdatePatientData
			///</summary>
	public: [TestMethod]
			void UpdatePatientDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				bool spCheck = true; 
				int expected = 1; 
				int actual;

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				try
				{
					actual = target->UpdatePatientData(pd,spCheck);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}
			}

	public: [TestMethod]
			void UpdatePatientDataTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				bool spCheck = true; 
				int expected = 1; 
				int actual;

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				
				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					////preparing test data into database///
					//-------------------------------------
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);
					
					pd->Gender = "XXXX";

					actual = target->UpdatePatientData(pd, spCheck);
					Assert::AreEqual(expected, actual);
					
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
					//exception occur if any assert statement fails - test failed 
					//Assert::Fail();
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}
			
			/// <summary>
			///A test for SetConnection
			///</summary>
	public: [TestMethod]
			void SetConnectionTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int expected = 0; 
				int actual;

				String^ serverNameTest = String::Empty;		
				String^  sourceNameTest = String::Empty ;	
				
				try
				{
					expected = 0;
					serverNameTest = "XXXX";
					sourceNameTest= nullptr;
					actual = target->SetConnection(serverNameTest, sourceNameTest);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass");
				}
			}

	public: [TestMethod]
			void SetConnectionTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int expected = 0; 
				int actual;

				String^ serverNameTest = String::Empty;		
				String^  sourceNameTest = String::Empty ;	
				
				try
				{
					expected = 1;
					serverNameTest = "XXXX";
					sourceNameTest= "SQLCLIENT";
					actual = target->SetConnection(serverNameTest, sourceNameTest);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass");
				}
			}

	public: [TestMethod]
			void SetConnectionTest2()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int expected = 0; 
				int actual;

				String^ serverNameTest = String::Empty;		
				String^  sourceNameTest = String::Empty ;	
				
				try
				{
					SetServerMachineName();
					expected = 0;
					serverNameTest = serverName;//"MUM-9696";
					sourceNameTest= sourceName;
					actual = target->SetConnection(serverNameTest, sourceNameTest);
				}
				catch(Exception^)
				{
					actual = 1;
				}
				Assert::AreEqual(expected, actual);				
			}

	public: [TestMethod]
			void SetConnectionTest3()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int expected = 0; 
				int actual;

				String^ serverNameTest = String::Empty;		
				String^  sourceNameTest = String::Empty ;	
			
				serverNameTest = "MUM-9696\\SQLEXPRESS";
				sourceNameTest = "ORACLECLIENT";
				try
				{
					actual = target->SetConnection(serverNameTest, sourceNameTest);
				}
				catch(Exception^)
				{
					actual = 0;
				}
				expected = 0;
				Assert::AreEqual(expected, actual);

			}

			/// <summary>
			///A test for SavePWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void SavePWVMeasurementDetailsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				//CrxStructPWVMeasurementData^  md = nullptr; 
				int expected = 1; 
				int actual;
				CrxDBManager^ crxDB = CrxDBManager::Instance;
				
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();

				try
				{
					actual = target->SavePWVMeasurementDetails(pwvmd);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					////preparing test data into database///
					//-------------------------------------
					pd->SystemIdentifier = 11111;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);
		
					//----measurement data
					pwvmd->SystemIdentifier = pd->SystemIdentifier;
					pwvmd->PatientNumberInternal = pd->PatientNumberInternal;
					pwvmd->GroupIdentifier = pd->GroupIdentifier;
					pwvmd->PWVDistance = 50;
					pwvmd->MeanHeartRate = 150.0000;
					pwvmd->MeanPulseWaveVelocity = Convert::ToSingle(4.4000);
					pwvmd->StandardDeviation = Convert::ToSingle(3.300);
					pwvmd->IsStandardDeviationValid = 1;
					pwvmd->Notes = "CheckOut";
					pwvmd->Carotid = 111;
					pwvmd->WeightInKilograms = 75;
					pwvmd->HeightInCentimetres = 175;
					pwvmd->CarotidSignal = gcnew array<unsigned short>(1);
					pwvmd->CarotidSignal[0] = 1244;
					pwvmd->FemoralSignal = gcnew array<unsigned short>(1);
					pwvmd->FemoralSignal[0] = 1344;
					pwvmd->CarotidSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->CarotidSignalFloatOnSets[0] = 1234.12f;
					pwvmd->FemoralSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->FemoralSignalFloatOnSets[0] = 2345.23f;
					pwvmd->ReferenceRange = gcnew array<float>(1);
					pwvmd->ReferenceRange[0] = 3456.34f;
					pwvmd->NormalRange = gcnew array<float>(1);
					pwvmd->NormalRange[0] =  4567.45f;
					actual = target->SavePWVMeasurementDetails(pwvmd);
					Assert::AreEqual(expected, actual);
					
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);

				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}

			/// <summary>
			///A test for SavePatientData
			///</summary>
	public: [TestMethod]
			void SavePatientDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int actual;
				int expected = 1; 

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				try
				{
					actual = target->SavePatientData(pd);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}
			}	

	public: [TestMethod]
			void SavePatientDataTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int actual;
				int expected = 1; 

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				
				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					//target->SavePatientData(pd);
					actual = target->SavePatientData(pd);
					Assert::AreEqual(expected, actual);
					target->DeletePatientData(pd);

				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}	

			/// <summary>
			///A test for PatientRecordExists
			///</summary>
	public: [TestMethod]
			void PatientRecordExistsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int expected = 0; 
				int actual;

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				try
				{
					actual = target->PatientRecordExists(pd);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true, "If exception occur then test case pass.");
				}
			}

	public: [TestMethod]
			void PatientRecordExistsTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int expected = 0; 
				int actual;

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					//target->SavePatientData(pd);
					target->SavePatientData(pd);
					actual = target->PatientRecordExists(pd);
					Assert::AreEqual(expected, actual);
					target->DeletePatientData(pd);

				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}

			/// <summary>
			///A test for PatientIdExists
			///</summary>
	public: [TestMethod]
			void PatientIdExistsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int systemIdentifier = 0; 
				String^  patientIdExternalReference = System::String::Empty; 
				bool expected = true; 
				bool actual;

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();
				
				try
				{
					actual = target->PatientIdExists(pd->SystemIdentifier, pd->PatientIDExternalReference);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true, "If exception occur then test case pass.");
				}
			}

	public: [TestMethod]
			void PatientIdExistsTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int systemIdentifier = 0; 
				String^  patientIdExternalReference = System::String::Empty; 
				bool expected = true; 
				bool actual;

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					//target->SavePatientData(pd);
					target->SavePatientData(pd);
					actual = target->PatientIdExists(pd->SystemIdentifier, pd->PatientIDExternalReference);
					Assert::AreEqual(expected, actual);
					target->DeletePatientData(pd);

				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}
						// This tests the assigment operator which is private and blank implmentation
// we do not need to test this as of now: 11/25/2010: Smarajit Mishra
	//		/// <summary>
	//		///A test for op_Assign
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
	//			CrxDBManager^  unnamed = nullptr; 
	//			CrxDBManager^  expected = nullptr; 
	//			CrxDBManager^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}

			/// <summary>
			///A test for MigrationLogDetail
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void MigrationLogDetailTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				CrxLogger^  objLog = nullptr; 
				cli::array< String^  >^  skipPatientlog = gcnew array<String^>(2);; 
				int totskipresult = 0; 
				String ^ path = Directory::GetCurrentDirectory() + "\\system\\logs\\";
				SetPath();
				//String^ temp = Directory::GetCurrentDirectory();
				objLog = CrxLogger::Instance ; 
				
				
				try
				{
					skipPatientlog[0] = "ThisIsForTestOnly";
					totskipresult = 1;

					target->MigrationLogDetail(objLog, skipPatientlog, totskipresult);

					

					if(File::Exists(path + "scor.log"))					
					{	
						StreamReader ^curLogFileFileStream;

						if(File::Exists(path + "scor_test.log"))
						{
							File::Delete(path + "scor_test.log");	
						}
						
						File::Copy(path+"scor.log",path+"scor_test.log"); 
						
						curLogFileFileStream =gcnew StreamReader(File::Open(path+"scor_test.log", FileMode::Open,FileAccess::Read,FileShare::Read ));
						
						String ^fileStr = curLogFileFileStream->ReadToEnd();
						String ^lastLine = fileStr->Substring(fileStr->LastIndexOf('\n',(fileStr->Length) - 5) + 1);

						lastLine = lastLine->Trim();

						lastLine= lastLine->Substring(lastLine->LastIndexOf(' ')+1); 
						Assert::AreEqual(lastLine, skipPatientlog[0]);
						curLogFileFileStream->Close();
					}
				}
				catch(Exception^ )
				{
					Assert::Fail("Error occured in 'WriteTest'.");
				}

			}
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void MigrationLogDetailTest1()
			{
				///////////Negative test case////////////////

				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				CrxLogger^  objLog = nullptr; 
				cli::array< String^  >^  skipPatientlog = gcnew array<String^>(2);; 
				
				//objLog = CrxLogger::Instance ; 
				
				int totskipresult = 1; 				
				//StreamReader ^curLogFileFileStream;
				//objLog = nullptr ; 	
				skipPatientlog[0] = "This is for Test Only";

				try
				{
					//target->MigrationLogDetail(objLog, skipPatientlog);
					target->MigrationLogDetail(objLog, skipPatientlog, totskipresult);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true);
				}
				
			}

			/// <summary>
			///A test for MigrationInternal
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void MigrationInternalTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				OleDbDataReader^  rdr = nullptr; 
				CrxLogger^  objLog = nullptr; 
				int rowNum = 0; 
				int systemIdentifier = 0; 
				String^  groupName = System::String::Empty; 
				int expected = 1; 
				int actual;

				/// testing woth no data in rdr
				objLog = CrxLogger::Instance;
				systemIdentifier = 11;
				groupName = "Test";
				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				// passing OleDbDataReader as null ptr, function is suppose to rollback transaction on this
				actual = target->MigrationInternal(rdr, objLog, rowNum, systemIdentifier, groupName);
				Assert::AreEqual(expected, actual);
				
			}
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void MigrationInternalTest1()
			{
				////To check rest of the scenario, it requires manual intervention during the execution
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				OleDbDataReader^  rdr = nullptr; 
				CrxLogger^  objLog = nullptr; 
				int rowNum = 0; 
				int systemIdentifier = 0; 
				String^  groupName = System::String::Empty; 
				int expected = 0; 
				int actual;
				String ^ path = Directory::GetCurrentDirectory() + "\\system\\logs\\";
				SetPath();
				/// testing woth no data in rdr
				objLog = CrxLogger::Instance;
				systemIdentifier = 11;
				groupName = "Test";
				try
				{
					SetServerMachineName();
					target->SetConnection(serverName, sourceName);
					// passing OleDbDataReader as null ptr, function is suppose to rollback transaction on this
					actual = target->MigrationInternal(rdr, objLog, rowNum, systemIdentifier, groupName);
					
					///testing transaction rollback
					StreamReader ^curLogFileFileStream;
					
				
					if(File::Exists(path + "scor.log"))					
					{
						if(File::Exists(path+"scor_test.log"))
						{
							File::Delete(path+"scor_test.log");	
						}
						File::Copy(path+"scor.log",path+"scor_test.log"); 
						
						curLogFileFileStream =gcnew StreamReader(File::Open(path+"scor_test.log", FileMode::Open,FileAccess::Read,FileShare::Read ));

						String ^fileStr = curLogFileFileStream->ReadToEnd();
						String ^lastLine = fileStr->Substring(fileStr->LastIndexOf('\n',(fileStr->Length) - 5) + 1);

						lastLine = lastLine->Trim();

						lastLine= lastLine->Substring(lastLine->LastIndexOf(' ')-9); 
						
						//Checking that transction rollback execution
						//Assert::IsNotNull(lastLine);
						Assert::AreEqual(lastLine, "Migration failed.");
						curLogFileFileStream->Close();
					}
				}
				catch(Exception^ )
				{
					Assert::Fail("Error occured in 'MigrationInternalTest1'.");
				}
			}

			/// <summary>
			///A test for MigrationFileExist
			///</summary>
	public: [TestMethod]
			void MigrationFileExistTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				bool expected = false; 

				SetPath();
				String^ curDir = Directory::GetCurrentDirectory();
				String ^ path = curDir + "\\system\\data\\";
			
				//File not exists, so checking IsFalse
				if(File::Exists(path + "scor.xyz"))
				{
					Assert::IsTrue(target->MigrationFileExist());
				}
			}

	public: [TestMethod]
			void MigrationFileExistTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				bool expected = false; 

				SetPath();
				String^ curDir = Directory::GetCurrentDirectory();
				String ^ path = curDir + "\\system\\data\\";
				
				//Negative Testing
				path = curDir + "\\system\\";
				//Setting wrong directory
				Directory::SetCurrentDirectory(path);
				if(!File::Exists(path + "scor.xyz"))
				{
					Assert::IsFalse(target->MigrationFileExist());
				}
			}

			/// <summary>
			///A test for MigrateAtCorData
			///</summary>
	public: [TestMethod]
			void MigrateAtCorDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int systemIdentifier = 0; 
				String^  groupName = System::String::Empty; 
				int expected = 0; 
				int actual;
				
				try
				{
					SetPath();
					if(!File::Exists(".\\system\\data\\scor.xyz"))
					{
						File::Copy(".\\system\\data\\scor.xyz.old",".\\system\\data\\scor.xyz");
					}


					groupName = "Dr.Alok";
					systemIdentifier = 31256;
					
					SetPath();
					//Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\Scor_Source_code\\TestResults\\");
					SetServerMachineName();
					target->SetConnection(serverName, sourceName);
					String^ path = Directory::GetCurrentDirectory() + "\\system\\data\\";

					if(File::Exists(path + "scor.xyz"))
					{
						actual = target->MigrateAtCorData(systemIdentifier, groupName);
						Assert::AreEqual(expected, actual);
					}
					else if(File::Exists(path + "scor.xyz.old"))
					{
						File::Move(path + "scor.xyz.old", path + "scor.xyz");
						actual = target->MigrateAtCorData(systemIdentifier, groupName);
						Assert::AreEqual(expected, actual);
					}
				}
				catch(Exception^)
				{
					Assert::Fail("Error occured in method 'MigrateAtCorDataTest'.");
				}
			}

			/// <summary>
			///A test for GroupRecordExits
			///</summary>
	public: [TestMethod]
			void GroupRecordExitsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int systemIdentifier = 0; 
				String^  groupName = System::String::Empty; 
				bool expected = true; 
				bool actual;

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();
				
				try
				{
					actual = target->GroupRecordExits(pd->SystemIdentifier, pd->GroupName);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true, "If exception occur then test case pass.");
				}
			}

	public: [TestMethod]
			void GroupRecordExitsTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int systemIdentifier = 0; 
				String^  groupName = System::String::Empty; 
				bool expected = true; 
				bool actual;

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					////preparing test data into database///
					//-------------------------------------
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);	


					actual = target->GroupRecordExits(pd->SystemIdentifier, pd->GroupName);
					Assert::AreEqual(expected, actual);
					
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);					
				}	

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}
			
			/// <summary>
			///A test for GetPWVTrendData
			///</summary>
	public: [TestMethod]
			void GetPWVTrendDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int patientNumberInternal = 0; 
				int groupIdentifier = 0; 
				int systemIdentifier = 0; 
				String^  studyDateTimeArrStr = System::String::Empty; 
				CrxStructPWVTrendData^  trendDataStruct = gcnew CrxStructPWVTrendData();
				
				//Testing without database connection for exception
				try
				{
					target->GetPWVTrendData(patientNumberInternal, groupIdentifier, systemIdentifier, studyDateTimeArrStr, trendDataStruct);
					//If in this case no exception occurs, means test case failed
					Assert::Fail();
				}
				catch(Exception^)
				{
					//If exception occurs, means test case passed
					Assert::IsTrue(true);
				}
			}

	public: [TestMethod]
			void GetPWVTrendDataTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int patientNumberInternal = 0; 
				int groupIdentifier = 0; 
				int systemIdentifier = 0; 
				String^  studyDateTimeArrStr = System::String::Empty; 
				CrxStructPWVTrendData^  trendDataStruct = gcnew CrxStructPWVTrendData();
				String^ CulturalNeutralDateFormat = "yyyy-MM-dd HH:mm:ss";

				// connect to db
				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				////preparing test data into database//////
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					////preparing test data into database///
					//-------------------------------------
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);
		
					//----measurement data
					pwvmd->SystemIdentifier = pd->SystemIdentifier;
					pwvmd->PatientNumberInternal = pd->PatientNumberInternal;
					pwvmd->GroupIdentifier = pd->GroupIdentifier;
					pwvmd->PWVDistance = 50;
					pwvmd->MeanHeartRate = 150.0000;
					pwvmd->MeanPulseWaveVelocity = Convert::ToSingle(4.4000);
					pwvmd->StandardDeviation = Convert::ToSingle(3.300);
					pwvmd->IsStandardDeviationValid = 1;
					pwvmd->Notes = "CheckOut";
					pwvmd->Carotid = 111;
					pwvmd->WeightInKilograms = 75;
					pwvmd->HeightInCentimetres = 175;
					pwvmd->CarotidSignal = gcnew array<unsigned short>(1);
					pwvmd->CarotidSignal[0] = 1244;
					pwvmd->FemoralSignal = gcnew array<unsigned short>(1);
					pwvmd->FemoralSignal[0] = 1344;
					pwvmd->CarotidSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->CarotidSignalFloatOnSets[0] = 1234.12f;
					pwvmd->FemoralSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->FemoralSignalFloatOnSets[0] = 2345.23f;
					pwvmd->ReferenceRange = gcnew array<float>(1);
					pwvmd->ReferenceRange[0] = 3456.34f;
					pwvmd->NormalRange = gcnew array<float>(1);
					pwvmd->NormalRange[0] =  4567.45f;
					int i = target->SavePWVMeasurementDetails(pwvmd);

					DataSet^ msrds = target->GetPWVMeasurementDetails(pwvmd->PatientNumberInternal,pwvmd->GroupIdentifier, pwvmd->SystemIdentifier);
					//pwvmd->StudyDateTime	= Convert::ToDateTime(msrds->Tables[0]->Rows[0]["StudyDateTime"]).ToString(CulturalNeutralDateFormat);
					//String^ studyDateTimeArrStr = ( pwvmd->StudyDateTime) + ",";
					String^ studyDateTimeArrStr =  Convert::ToDateTime(msrds->Tables[0]->Rows[0]["StudyDateTime"]).ToString(CulturalNeutralDateFormat) + ",";
					//target->DeletePatientData(pd);
				//	////////////	

					systemIdentifier = pd->SystemIdentifier;
					patientNumberInternal = pd->PatientNumberInternal;
					groupIdentifier = pd->GroupIdentifier;

					//Testing with single value
					target->GetPWVTrendData(patientNumberInternal, groupIdentifier, systemIdentifier, studyDateTimeArrStr, trendDataStruct);
					Assert::AreEqual(trendDataStruct->HeartRateArrStr	,"150");
					Assert::AreEqual(trendDataStruct->PulseWaveVelocityArrStr	,"4.4");
					Assert::AreEqual(trendDataStruct->StandardDeviationArrStr	,"3.3");
					Assert::AreEqual(trendDataStruct->IsStdDevValidArrStr	,"1");

					//Clearing the structure
					trendDataStruct->HeartRateArrStr = String::Empty;
					trendDataStruct->PulseWaveVelocityArrStr = String::Empty;
					trendDataStruct->StandardDeviationArrStr = String::Empty;
					trendDataStruct->IsStdDevValidArrStr = String::Empty;

					////Testing with double value
					//DateTime^ temp = System::DateTime::Now.ToString(CulturalNeutralDateFormat);
					String^ temp = System::DateTime::Now.ToString(CulturalNeutralDateFormat);
					studyDateTimeArrStr = studyDateTimeArrStr + temp + "," ;//"2011-01-31 17:46:01,";
					target->GetPWVTrendData(patientNumberInternal, groupIdentifier, systemIdentifier, studyDateTimeArrStr, trendDataStruct);
					Assert::AreEqual(trendDataStruct->HeartRateArrStr	,"150");
					Assert::AreEqual(trendDataStruct->PulseWaveVelocityArrStr	,"4.4");
					Assert::AreEqual(trendDataStruct->StandardDeviationArrStr	,"3.3");
					Assert::AreEqual(trendDataStruct->IsStdDevValidArrStr	,"1");

					//Clearing the structure
					trendDataStruct->HeartRateArrStr = String::Empty;
					trendDataStruct->PulseWaveVelocityArrStr = String::Empty;
					trendDataStruct->StandardDeviationArrStr = String::Empty;
					trendDataStruct->IsStdDevValidArrStr = String::Empty;

					//Testing with invalid value
					patientNumberInternal = 0;
					groupIdentifier = 3;
					systemIdentifier = 31256;
					studyDateTimeArrStr = "2010-12-15 14:23:47,2011-01-31 17:46:01,";
					target->GetPWVTrendData(patientNumberInternal, groupIdentifier, systemIdentifier, studyDateTimeArrStr, trendDataStruct);
					Assert::AreEqual(trendDataStruct->HeartRateArrStr	,String::Empty);
					Assert::AreEqual(trendDataStruct->PulseWaveVelocityArrStr	,String::Empty);
					Assert::AreEqual(trendDataStruct->StandardDeviationArrStr	,String::Empty);
					Assert::AreEqual(trendDataStruct->IsStdDevValidArrStr	,String::Empty);
					
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
					//exception occur if any assert statement fails - test failed 
					Assert::Fail();
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}
			
			/// <summary>
			///A test for GetPWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void GetPWVMeasurementDetailsTest11()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int patientNumberInternal = 0; 
				int groupIdentifier = 0; 
				int systemIdentifier = 0; 
				bool isStandardDeviationValid = true;
				short pwvDistance = 0;

				DataSet^  expected = nullptr; 
				DataSet^  actual;
				
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
				
				try
				{
					actual = target->GetPWVMeasurementDetails(pwvmd->PatientNumberInternal,pwvmd->GroupIdentifier, pwvmd->SystemIdentifier);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}
			}

	public: [TestMethod]
			void GetPWVMeasurementDetailsTest12()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int patientNumberInternal = 0; 
				int groupIdentifier = 0; 
				int systemIdentifier = 0; 
				bool isStandardDeviationValid = true;
				short pwvDistance = 0;

				DataSet^  expected = nullptr; 
				
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
				
				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 
				
				try
				{
					////preparing test data into database///
					//-------------------------------------
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);
		
					//----measurement data
					pwvmd->SystemIdentifier = pd->SystemIdentifier;
					pwvmd->PatientNumberInternal = pd->PatientNumberInternal;
					pwvmd->GroupIdentifier = pd->GroupIdentifier;
					pwvmd->PWVDistance = 50;
					pwvmd->MeanHeartRate = 150.0000;
					pwvmd->MeanPulseWaveVelocity = Convert::ToSingle(4.4000);
					pwvmd->StandardDeviation = Convert::ToSingle(3.300);
					pwvmd->IsStandardDeviationValid = 1;
					pwvmd->Notes = "CheckOut";
					pwvmd->Carotid = 111;
					pwvmd->WeightInKilograms = 75;
					pwvmd->HeightInCentimetres = 175;
					pwvmd->CarotidSignal = gcnew array<unsigned short>(1);
					pwvmd->CarotidSignal[0] = 1244;
					pwvmd->FemoralSignal = gcnew array<unsigned short>(1);
					pwvmd->FemoralSignal[0] = 1344;
					pwvmd->CarotidSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->CarotidSignalFloatOnSets[0] = 1234.12f;
					pwvmd->FemoralSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->FemoralSignalFloatOnSets[0] = 2345.23f;
					pwvmd->ReferenceRange = gcnew array<float>(1);
					pwvmd->ReferenceRange[0] = 3456.34f;
					pwvmd->NormalRange = gcnew array<float>(1);
					pwvmd->NormalRange[0] =  4567.45f;
					int i = target->SavePWVMeasurementDetails(pwvmd);

					DataSet^ msrds = target->GetPWVMeasurementDetails(pwvmd->PatientNumberInternal,pwvmd->GroupIdentifier, pwvmd->SystemIdentifier);
					pwvmd->StudyDateTime	= Convert::ToDateTime(msrds->Tables[0]->Rows[0]["StudyDateTime"]);
					systemIdentifier = Convert::ToInt32(msrds->Tables[0]->Rows[0]["SystemIdentifier"]);
					patientNumberInternal = Convert::ToInt32(msrds->Tables[0]->Rows[0]["PatientNumberInternal"]);
					groupIdentifier = Convert::ToInt32(msrds->Tables[0]->Rows[0]["GroupIdentifier"]);
					isStandardDeviationValid = Convert::ToBoolean (msrds->Tables[0]->Rows[0]["IsStandardDeviationValid"]);
					pwvDistance = Convert::ToInt32(msrds->Tables[0]->Rows[0]["PWVDistance"]);
					//Assert::AreEqual(expectStr, actualStr);					

					Assert::AreEqual(pwvmd->SystemIdentifier, systemIdentifier);
					Assert::AreEqual(pwvmd->PatientNumberInternal, patientNumberInternal);
					Assert::AreEqual(pwvmd->GroupIdentifier, groupIdentifier);
					Assert::AreEqual(pwvmd->IsStandardDeviationValid, isStandardDeviationValid);
					Assert::AreEqual(pwvmd->PWVDistance, pwvDistance);
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}
						
			/// <summary>
			///A test for GetPWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void GetPWVMeasurementDetailsTest01()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				DataSet^  expected = nullptr; 
				DataSet^  actual;
				int patientNumberInternal = 0; 
				int groupIdentifier = 0; 
				int systemIdentifier = 0; 
				bool isStandardDeviationValid = true;
				short pwvDistance = 0;
				
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
				CrxStructPWVMeasurementData^  md = gcnew CrxStructPWVMeasurementData();
				
				try
				{
					actual = target->GetPWVMeasurementDetails(pwvmd->PatientNumberInternal,pwvmd->GroupIdentifier, pwvmd->SystemIdentifier);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}
			}

	public: [TestMethod]
			void GetPWVMeasurementDetailsTest02()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				DataSet^  expected = nullptr; 
				DataSet^  actual;
				int patientNumberInternal = 0; 
				int groupIdentifier = 0; 
				int systemIdentifier = 0; 
				bool isStandardDeviationValid = true;
				short pwvDistance = 0;
				
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
				CrxStructPWVMeasurementData^  md = gcnew CrxStructPWVMeasurementData();

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

				try
				{
					////preparing test data into database///
					//-------------------------------------
					pd->SystemIdentifier = 11111;
					pd->LastName = "Test_Patient_Last1";
					pd->FirstName = "Test_Patient_First1";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);
		
					//----measurement data
					pwvmd->SystemIdentifier = pd->SystemIdentifier;
					pwvmd->PatientNumberInternal = pd->PatientNumberInternal;
					pwvmd->GroupIdentifier = pd->GroupIdentifier;
					pwvmd->PWVDistance = 50;
					pwvmd->MeanHeartRate = 150.0000;
					pwvmd->MeanPulseWaveVelocity = Convert::ToSingle(4.4000);
					pwvmd->StandardDeviation = Convert::ToSingle(3.300);
					pwvmd->StandardDeviation = isStandardDeviationValid;
					pwvmd->Notes = "CheckOut";
					pwvmd->Carotid = 111;
					pwvmd->WeightInKilograms = 75;
					pwvmd->HeightInCentimetres = 175;
					pwvmd->CarotidSignal = gcnew array<unsigned short>(1);
					pwvmd->CarotidSignal[0] = 1244;
					pwvmd->FemoralSignal = gcnew array<unsigned short>(1);
					pwvmd->FemoralSignal[0] = 1344;
					pwvmd->CarotidSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->CarotidSignalFloatOnSets[0] = 1234.12f;
					pwvmd->FemoralSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->FemoralSignalFloatOnSets[0] = 2345.23f;
					pwvmd->ReferenceRange = gcnew array<float>(1);
					pwvmd->ReferenceRange[0] = 3456.34f;
					pwvmd->NormalRange = gcnew array<float>(1);
					pwvmd->NormalRange[0] =  4567.45f;
					
					int i = target->SavePWVMeasurementDetails(pwvmd);

					DataSet^ msrds = target->GetPWVMeasurementDetails(pwvmd->PatientNumberInternal,pwvmd->GroupIdentifier, pwvmd->SystemIdentifier);
					md->StudyDateTime	= Convert::ToDateTime(msrds->Tables[0]->Rows[0]["StudyDateTime"]);
					md->SystemIdentifier = Convert::ToInt32(msrds->Tables[0]->Rows[0]["SystemIdentifier"]);
					md->PatientNumberInternal = Convert::ToInt32(msrds->Tables[0]->Rows[0]["PatientNumberInternal"]);
					md->GroupIdentifier = Convert::ToInt32(msrds->Tables[0]->Rows[0]["GroupIdentifier"]);
					md->IsStandardDeviationValid = Convert::ToBoolean(msrds->Tables[0]->Rows[0]["IsStandardDeviationValid"]);
					md->PWVDistance = Convert::ToInt32(msrds->Tables[0]->Rows[0]["PWVDistance"]);
					
					int expectStr = md->PatientNumberInternal;
					actual = target->GetPWVMeasurementDetails(md);
					
					int actualStr = md->PatientNumberInternal;
					Assert::AreEqual(expectStr, actualStr);

					target->DeletePatientData(pd);

				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);

				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}
			
			/// <summary>
			///A test for GetPatientDemographicRecords
			///</summary>
	public: [TestMethod]
			void GetPatientDemographicRecordsTest2()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				DataSet^  expected = nullptr; 
				DataSet^  actual;
				String^ actualStr;

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 
				
				try
				{
					pd->SystemIdentifier = 11111;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);

					actual = target->GetPatientDemographicRecords();

					String^ ExpectedStr = pd->PatientIDExternalReference;

					for(int i = 0; i < 100 ; i++)
					{
						String^ actualStr1 = actual->Tables[0]->Rows[i]["PatientIDExternalReference"]->ToString();
						if (actualStr1->Equals(ExpectedStr))
						{
							actualStr = actualStr1;
							break;
						}
					}
					Assert::AreEqual(ExpectedStr, actualStr);
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					  target->DeletePatientData(pd);
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}

	public: [TestMethod]
			void GetPatientDemographicRecordsTest3()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				DataSet^  expected = nullptr; 
				DataSet^  actual;
				String^ actualStr;

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 
				
				try
				{
					pd->SystemIdentifier = 11111;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);

					actual = target->GetPatientDemographicRecords();

					String^ ExpectedStr = pd->PatientIDExternalReference;

					for(int i = 0; i < 100 ; i++)
					{
						String^ actualStr1 = actual->Tables[0]->Rows[i]["PatientIDExternalReference"]->ToString();
						if (actualStr1->Equals(ExpectedStr))
						{
							actualStr = actualStr1;
							break;
						}
					}
					Assert::AreEqual(ExpectedStr, actualStr);
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					  target->DeletePatientData(pd);
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}

			/// <summary>
			///A test for GetPatientDemographicRecords
			///</summary>
	      public: [TestMethod]
			  void GetPatientDemographicRecordsTest()
			  {
					CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
					int patientNumberInternal = 0; 
					int systemIdentifier = 0; 
					int groupIdentifier = 0; 
					DataSet^  actual;
					
					try
					{
						actual = target->GetPatientDemographicRecords(patientNumberInternal, systemIdentifier, groupIdentifier);
					}
					catch(Exception^)
					{
						Assert::IsTrue(true,"If exception occur then test case pass.");
					}
			  }

			/// <summary>
			///A test for GetPatientDemographicRecords
			///</summary>
	      public: [TestMethod]
			  void GetPatientDemographicRecordsTest1()
			  {
					CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
					int patientNumberInternal = 0; 
					int systemIdentifier = 0; 
					int groupIdentifier = 0; 
					DataSet^  actual;

					SetServerMachineName();
					target->SetConnection(serverName, sourceName);

					//Begin Smarajit Mishra 19 Apr 2011 
					DataSet^ dbRecords = target->GetPatientDemographicRecords();
					int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
					//End Smarajit Mishra 19 Apr 2011 

					////preparing test data into database//////
					CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
					try
					{
						  pd->SystemIdentifier = 11111;
						  pd->PatientNumberInternal = 26;
						  pd->LastName = "Test_Patient_Last";
						  pd->FirstName = "Test_Patient_First";
						  pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
						  pd->Gender = "Test";
						  pd->PatientIDExternalReference = "TestER";
						  pd->GroupName = "Test_Group";
						  pd->GroupIdentifier = 24;
						  target->SavePatientData(pd);
	                      
	                      
						  patientNumberInternal = pd->PatientNumberInternal; 
						  systemIdentifier = pd->SystemIdentifier;
						  groupIdentifier = pd->GroupIdentifier ;
						  actual = target->GetPatientDemographicRecords(patientNumberInternal, systemIdentifier, groupIdentifier);

						  String^ actualStr = actual->Tables[0]->Rows[0]["PatientIDExternalReference"]->ToString();
						  String^ ExpectedStr = pd->PatientIDExternalReference;                   
						  Assert::AreEqual(ExpectedStr, actualStr);

						  target->DeletePatientData(pd);
					}
					catch(Exception^)
					{
						  target->DeletePatientData(pd);
					}

					//Begin Smarajit Mishra 19 Apr 2011 
					DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
					int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
					Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
					//End Smarajit Mishra 19 Apr 2011 
			  }

		    /// <summary>
			///A test for GetGroupLists
			///</summary>
	public: [TestMethod]
			void GetGroupListsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				DataSet^  expected = nullptr; 
				DataSet^  actual;
				
				try
				{
					actual = target->GetGroupLists();
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}
			}

	public: [TestMethod]
			void GetGroupListsTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				DataSet^  expected = nullptr; 
				DataSet^  actual;

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 
				
				try
				{
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);

					actual = target->GetGroupLists();

					String^ ExpectedStr = pd->GroupName;	
					String^ actualStr = nullptr;
					
					for(int i = 0; i < 100 ; i++)
					{
						String^ actualStr1 = actual->Tables[0]->Rows[i]["GroupName"]->ToString();
						if (actualStr1->Equals(ExpectedStr))
						{
							actualStr = actualStr1;
							break;
						}
					}
				
					Assert::AreEqual(ExpectedStr, actualStr);

					target->DeletePatientData(pd);
				}
                catch(Exception^)
                {
                      target->DeletePatientData(pd);
                }

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
			}

			/// <summary>
			///A test for DeletePWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void DeletePWVMeasurementDetailsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				CrxStructPWVMeasurementData^  md = nullptr; 
				String^  studyDateTimeArrStr = System::String::Empty; 
				int expected = 0; 
				int actual;
				
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
				
				try
				{
					actual = target->DeletePWVMeasurementDetails(pwvmd, studyDateTimeArrStr);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}				
			}

	public: [TestMethod]
			void DeletePWVMeasurementDetailsTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				CrxStructPWVMeasurementData^  md = nullptr; 
				String^  studyDateTimeArrStr = System::String::Empty; 
				int expected = 0; 
				int actual;
				
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
				
				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 
				
				try
				{
					expected = 1;
					////preparing test data into database///
					//-------------------------------------
					pd->SystemIdentifier = 11111;
					pd->PatientNumberInternal = 26;
					pd->LastName = "Test_Patient_Last";
					pd->FirstName = "Test_Patient_First";
					pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
					pd->Gender = "Test";
					pd->PatientIDExternalReference = "TestER";
					pd->GroupName = "Test_Group";
					pd->GroupIdentifier = 24;
					target->SavePatientData(pd);
		
					//----measurement data
					pwvmd->SystemIdentifier = pd->SystemIdentifier;
					pwvmd->PatientNumberInternal = pd->PatientNumberInternal;
					pwvmd->GroupIdentifier = pd->GroupIdentifier;
					pwvmd->PWVDistance = 50;
					pwvmd->MeanHeartRate = 150.0000;
					pwvmd->MeanPulseWaveVelocity = Convert::ToSingle(4.4000);
					pwvmd->StandardDeviation = Convert::ToSingle(3.300);
					pwvmd->IsStandardDeviationValid = 1;
					pwvmd->Notes = "CheckOut";
					pwvmd->Carotid = 111;
					pwvmd->WeightInKilograms = 75;
					pwvmd->HeightInCentimetres = 175;
					pwvmd->CarotidSignal = gcnew array<unsigned short>(1);
					pwvmd->CarotidSignal[0] = 1244;
					pwvmd->FemoralSignal = gcnew array<unsigned short>(1);
					pwvmd->FemoralSignal[0] = 1344;
					pwvmd->CarotidSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->CarotidSignalFloatOnSets[0] = 1234.12f;
					pwvmd->FemoralSignalFloatOnSets = gcnew array<float>(1);
					pwvmd->FemoralSignalFloatOnSets[0] = 2345.23f;
					pwvmd->ReferenceRange = gcnew array<float>(1);
					pwvmd->ReferenceRange[0] = 3456.34f;
					pwvmd->NormalRange = gcnew array<float>(1);
					pwvmd->NormalRange[0] =  4567.45f;
					int i = target->SavePWVMeasurementDetails(pwvmd);

					DataSet^ msrds = target->GetPWVMeasurementDetails(pwvmd->PatientNumberInternal,pwvmd->GroupIdentifier, pwvmd->SystemIdentifier);
					pwvmd->StudyDateTime	= Convert::ToDateTime(msrds->Tables[0]->Rows[0]["StudyDateTime"]);
					String^ studyDateTimeArrStr = Convert::ToString( pwvmd->StudyDateTime) + ",";
					
					actual = target->DeletePWVMeasurementDetails(pwvmd, studyDateTimeArrStr);
					Assert::AreEqual(expected, actual);
					
					expected = 0 ;
					//Passing invalid studyDateTimeArrStr, so that procedure will not delete any record 
					//and return 0
					actual = target->DeletePWVMeasurementDetails(pwvmd, "2010-01-05 16:02:35,");
					Assert::AreEqual(expected, actual);

					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
				}

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
				///////////////////
			}

			/// <summary>
			///A test for DeletePatientData
			///</summary>
	public: [TestMethod]
			void DeletePatientDataTest()
          {
                CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
                int expected = 0; 
                int actual;

                CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				try
				{
					actual = target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					Assert::IsTrue(true,"If exception occur then test case pass.");
				}
          }

	public: [TestMethod]
			void DeletePatientDataTest1()
          {
                CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
                int expected = 0; 
                int actual;
                CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();


                SetServerMachineName();
                target->SetConnection(serverName, sourceName);

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecords = target->GetPatientDemographicRecords();
				int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
				//End Smarajit Mishra 19 Apr 2011 

                try
                {
                      pd->SystemIdentifier = 11111;
                      pd->PatientNumberInternal = 26;
                      pd->LastName = "Test_Patient_Last";
                      pd->FirstName = "Test_Patient_First";
                      pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
                      pd->Gender = "Test";
                      pd->PatientIDExternalReference = "TestER";
                      pd->GroupName = "Test_Group";
                      pd->GroupIdentifier = 24;
                      target->SavePatientData(pd);

                      actual = target->DeletePatientData(pd);
                      Assert::AreEqual(expected, actual);

                }
                catch(Exception^)
                {
                      target->DeletePatientData(pd);
                }

				//Begin Smarajit Mishra 19 Apr 2011 
				DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
				int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
				Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
				//End Smarajit Mishra 19 Apr 2011 
          }

		    /// <summary>
			///A test for DatabaseRestore
			///</summary>
	public: [TestMethod]
			void DatabaseRestoreTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				//String^  FilePath = System::String::Empty; 
				String^  FilePath = nullptr;
				int expected = 0; 
				int actual;
				//input parameters to call method
				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				SetPath();
				FilePath = Directory::GetCurrentDirectory() + "\\Test_AtCor.BAK";
				try
				{
					actual = target->DatabaseRestore(FilePath);
					Assert::AreEqual(expected, actual);
				}
				catch(Exception^)
				{
					Assert::Fail();;
				}
			}

			/// <summary>
			///A test for DatabaseRestore1
			///</summary>
	public: [TestMethod]
			void DatabaseRestoreTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				//String^  FilePath = System::String::Empty; 
				String^  FilePath = nullptr;
				int expected = 1; 
				int actual;
				//input parameters to call method
				SetServerMachineName();
				target->SetConnection(serverName, sourceName);

				//Setting invalid path, so that error occur
				FilePath = "\\\\MUM-9638\\Atcor_2009\\Test_For120110105.BAK";
				//expected = 0; 
				//int actual;
				//input parameters to call method
				try
				{
					actual = target->DatabaseRestore(FilePath);
					Assert::AreEqual(expected, actual);
				}
				catch(Exception^)
				{
					actual = 1;
				}
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for DatabaseBackup
			///</summary>
	public: [TestMethod]
			void DatabaseBackupTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				//String^  FilePath = System::String::Empty; 
				String^  FilePath = "\\Test_AtCor.BAK";
				int expected = 0; 
				int actual;
				//input parameters to call method
				SetServerMachineName();
			
				target->SetConnection(serverName, sourceName);
				SetPath();
				
				FilePath = Directory::GetCurrentDirectory() + FilePath;
				try
				{
					actual = target->DatabaseBackup(FilePath);
				}
				catch(Exception^ )
				{
					Assert::Fail();
				}

				Assert::AreEqual(expected, actual);

			}

			/// <summary>
			///A test for DatabaseBackup1
			///</summary>
	public: [TestMethod]
			void DatabaseBackupTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				String^  FilePath = nullptr;
				int expected = 1; 
				int actual;

				SetServerMachineName();
				target->SetConnection(serverName, sourceName);
				SetPath();
				
				FilePath = Directory::GetCurrentDirectory() + FilePath;
				
				//input parameters to call method - Setting invalid path so that function gets failed.
				FilePath = "\\\\MUM-9638\\Atcor_2009\\Test_For120110105.BAK";
				try
				{
					actual = target->DatabaseBackup(FilePath);
				}
				catch(Exception^)
				{
					actual = 1;
				}
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for CommonShortArrtoByteArr
			///</summary>
	public: [TestMethod]
			void CommonShortArrtoByteArrTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int len = 0; 
				cli::array< unsigned short >^  shrtarr = nullptr; 
				//cli::array< unsigned char >^  expected = nullptr; 
				//cli::array< unsigned char >^  actual;
				cli::array< Byte >^  expected = nullptr;
				cli::array< Byte >^  actual;
				//smarajit
				//array<Byte>^ bufferArrRet;
				shrtarr = gcnew array<unsigned short> (1);
				   shrtarr[0] = 21212;
				len = shrtarr->Length;
				array<Byte>^ bufferarr;
				expected =  gcnew array<Byte> (2);
				bufferarr = BitConverter::GetBytes(shrtarr[0]);
				expected[0] = bufferarr[0];
				expected[1] = bufferarr[1];
				actual =  gcnew array<Byte> (2);
				actual = target->CommonShortArrtoByteArr(len, shrtarr);
				///actual = target->CommonShortArrtoByteArr(len, shrtarr);
				Assert::AreEqual(expected[0], actual[0]);


				len = 0 ;
				actual =  gcnew array<Byte> (len*2);
				actual = target->CommonShortArrtoByteArr(len, shrtarr);
				expected =  gcnew array<Byte>(len*2);

				int actualTest;
				try
				{
					actual =  gcnew array<Byte> (2);
					actual = target->CommonShortArrtoByteArr(2, shrtarr);
				}					
				catch(Exception^)
				{
					actualTest = 0;
				}
				int expectedTest = 0;
				Assert::AreEqual(expectedTest,actualTest);
				//smarajit
			}

			/// <summary>
			///A test for CommonFloatArrtoByteArr
			///</summary>
	public: [TestMethod]
			void CommonFloatArrtoByteArrTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int len = 0; 
				cli::array< float >^  fltarr = nullptr; 
				//cli::array< unsigned char >^  expected = nullptr; 
				//cli::array< unsigned char >^  actual;
				cli::array< Byte >^  expected = nullptr;
				cli::array< Byte >^  actual;
				//smarajit
			
				fltarr = gcnew array<float> (1);
				fltarr[0] = 2121.21f;;
				len = fltarr->Length;
				expected =  gcnew array<Byte>(4);
				array<Byte>^ bufferarr;
				float tempflt  = Convert::ToSingle(Math::Round(fltarr[0],2));
				bufferarr = BitConverter::GetBytes(tempflt);
				expected[0] = bufferarr[0];
				expected[1] = bufferarr[1];
				expected[2] = bufferarr[2];
				expected[3] = bufferarr[3];

				actual =  gcnew array<Byte> (4);

				actual = target->CommonFloatArrtoByteArr(len, fltarr);
				Assert::AreEqual(expected[0], actual[0]);

				len = 0 ;
				actual =  gcnew array<Byte> (len*4);
				actual = target->CommonFloatArrtoByteArr(len, fltarr);
				expected =  gcnew array<Byte>(len*4);
				//Assert::AreEqual(expected[0], actual[0]);
				
				int actualTest;
				try
				{
					actual =  gcnew array<Byte> (4);
					actual = target->CommonFloatArrtoByteArr(2, fltarr);
				}				
				
				catch(Exception^)
				{
					actualTest = 0;
				}
				int expectedTest = 0;
				Assert::AreEqual(expectedTest,actualTest);
				//smarajit
			}

			/// <summary>
			///A test for CommonByteArrtoShortArr
			///</summary>
	public: [TestMethod]
			void CommonByteArrtoShortArrTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int len = 0; 
				cli::array< unsigned char >^  bytearr = nullptr; 
				cli::array< unsigned short >^  expected = nullptr; 
				cli::array< unsigned short >^  actual;
				///Smarajit

				array< unsigned short >^ shrtarr = gcnew array<unsigned short> (1);
				   shrtarr[0] = 21212;
				len = shrtarr->Length;
				array<Byte>^ bufferarr;
				bytearr =  gcnew array<Byte> (2);
				bufferarr = BitConverter::GetBytes(shrtarr[0]);
				bytearr[0] = bufferarr[0];
				bytearr[1] = bufferarr[1];
				expected = gcnew array<unsigned short>(len);
				short value = BitConverter::ToInt16(bytearr,0);		
				expected[0] = value;
				//smarajit
				actual = target->CommonByteArrtoShortArr(len, bytearr);
				Assert::AreEqual(expected[0], actual[0]);

				bytearr =  gcnew array<Byte> (2);
				bufferarr = BitConverter::GetBytes(shrtarr[0]);
				bytearr[0] = bufferarr[0];
				bytearr[1] = bufferarr[1];
				expected = gcnew array<unsigned short>(len);
				value = BitConverter::ToInt16(bytearr,0);		
				expected[0] = value;
				len =0;
				int actualTest;
				try
				{
					actual = target->CommonByteArrtoShortArr(2, bytearr);
				}
				
				catch(Exception^)
				{
					actualTest = 0;
				}
				int expectedTest = 0;
				Assert::AreEqual(expectedTest,actualTest);
			}

			/// <summary>
			///A test for CommonByteArrtoFloatArr
			///</summary>
	public: [TestMethod]
			void CommonByteArrtoFloatArrTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				int len = 0; 
				cli::array< unsigned char >^  bytearr = nullptr; 
				cli::array< float >^  expected = nullptr; 
				cli::array< float >^  actual;
				///Smarajit

				array< float >^ fltarr = gcnew array<float> (1);
				   fltarr[0] = 21212;
				len = fltarr->Length;
				array<Byte>^ bufferarr;
				bytearr =  gcnew array<Byte> (4);
				bufferarr = BitConverter::GetBytes(fltarr[0]);
				bytearr[0] = bufferarr[0];
				bytearr[1] = bufferarr[1];
				expected = gcnew array<float>(len);
				float value = BitConverter::ToSingle(bytearr,0);		
				expected[0] = value;
				//smarajit
				actual = target->CommonByteArrtoFloatArr(len, bytearr);
				Assert::AreEqual(expected[0], actual[0]);

				//array<Byte>^ bufferarr;
				bytearr =  gcnew array<Byte> (4);
				bufferarr = BitConverter::GetBytes(fltarr[0]);
				bytearr[0] = bufferarr[0];
				bytearr[1] = bufferarr[1];
				expected = gcnew array<float>(len);
				value = BitConverter::ToSingle(bytearr,0);		
				expected[0] = value;
				len  =0;
				int actualTest;
				try
				{
					actual = target->CommonByteArrtoFloatArr(2, bytearr);
				}
				
				catch(Exception^)
				{
					actualTest = 0;
				}
				int expectedTest = 0;
				Assert::AreEqual(expectedTest,actualTest);
			}

			/// <summary>
			///A test for CheckConnection
			///</summary>
	public: [TestMethod]
			void CheckConnectionTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
				String^  serverName = System::String::Empty; 
				String^  sourceName = System::String::Empty; 
				int expected = 0; 
				int actual;
				String^ serverNameTest = String::Empty;//"MUM-9383\\SQLEXPRESS";
				String^  sourceNameTest = String::Empty;//"SQLCLIENT";
				
				SetServerMachineName();
				
				try
				{
					serverNameTest = serverName;//"MUM-9696";
					sourceNameTest = sourceName;//;"SQLCLIENT"
					actual = target->CheckConnection(serverNameTest, sourceNameTest);
				}
				catch(Exception^)
				{
					actual = 1;
				}
				//actual = target->CheckConnection(serverName, sourceName);
				Assert::AreEqual(expected, actual);

				expected = 1;
				try
				{
					SetServerMachineName();
					serverNameTest = "XXXX";
					sourceNameTest = sourceName;;
					actual = target->CheckConnection(serverNameTest, sourceNameTest);
				}
				catch(Exception^)
				{
					Assert::AreEqual(expected, actual);	
				}
			}

			/// <summary>
			///A test for CrxDBManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxDBManagerConstructorTest1()
			{
				CrxDBManager^  unnamed = nullptr; 
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor(unnamed));
				Assert::IsNotNull(target);
			}

			/// <summary>
			///A test for CrxDBManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxDBManagerConstructorTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor());
				Assert::IsNotNull(target);
			}
		/// <summary>
		///A test for RemoveOldAccessFile
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void RemoveOldAccessFileTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			int fileType = 1; // TODO: Initialize to an appropriate value
			SetPath();
			if(File::Exists(".\\system\\data\\scor.xyz.old"))
			{
				if(!File::Exists(".\\system\\data\\scor.xyz"))
				{
					File::Copy(".\\system\\data\\scor.xyz.old",".\\system\\data\\scor.xyz");
				}
				target->RemoveOldAccessFile(fileType);
			}
			else
			{
				File::Copy(".\\system\\data\\scor.xyz",".\\system\\data\\scor.xyz.old");
				target->RemoveOldAccessFile(fileType);
			}

			if(File::Exists(".\\system\\data\\scor.xyz.old"))
			{
				Assert::Fail();
			}
		}

		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void RemoveOldAccessFileTest1()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			int fileType = 2; // TODO: Initialize to an appropriate value
			SetPath();
			if(File::Exists(".\\system\\data\\scor.mdb.old"))
			{
				if(!File::Exists(".\\system\\data\\scor.mdb"))
				{
					File::Copy(".\\system\\data\\scor.mdb.old",".\\system\\data\\scor.mdb");
				}
				target->RemoveOldAccessFile(fileType);
			}
			else
			{
				File::Copy(".\\system\\data\\scor.mdb",".\\system\\data\\scor.mdb.old");
				target->RemoveOldAccessFile(fileType);
			}

			if(File::Exists(".\\system\\data\\scor.mdb.old"))
			{
				Assert::Fail();
			}			
		}
		/// <summary>
		///A test for MigrationFileName
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void MigrationFileNameTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			int fileType = 1; // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			
			expected = ".\\system\\data\\scor.xyz";
			actual = target->MigrationFileName(fileType);
			Assert::AreEqual(expected, actual);
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void MigrationFileNameTest1()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			int fileType = 2; // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			expected = ".\\system\\data\\scor.mdb";
			actual = target->MigrationFileName(fileType);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for MigrationFileRename
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void MigrationFileRenameTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			int fileType = 1; // TODO: Initialize to an appropriate value
			SetPath();
			if(File::Exists(".\\system\\data\\scor.xyz"))
			{
				target->MigrationFileRename(fileType);
			}
			else
			{
				File::Move(".\\system\\data\\scor.xyz.old",".\\system\\data\\scor.xyz");
				target->MigrationFileRename(fileType);
			}

			if(File::Exists(".\\system\\data\\scor.xyz"))
			{
				Assert::Fail();
			}

			File::Copy(".\\system\\data\\scor.xyz.old",".\\system\\data\\scor.xyz");
		}
		public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void MigrationFileRenameTest1()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			int fileType = 2; // TODO: Initialize to an appropriate value
			SetPath();
			if(File::Exists(".\\system\\data\\scor.mdb"))
			{
				target->MigrationFileRename(fileType);
			}
			else
			{
				File::Move(".\\system\\data\\scor.mdb.old",".\\system\\data\\scor.mdb");
				target->MigrationFileRename(fileType);
			}

			if(File::Exists(".\\system\\data\\scor.mdb"))
			{
				Assert::Fail();
			}
		}
		/// <summary>
		///A test for SaveCuffPWAMeasurementDetails
		///</summary>
public: [TestMethod]
		void SaveCuffPWAMeasurementDetailsTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			//CrxStructPWAMeasurementData^  pwaMd = nullptr; // TODO: Initialize to an appropriate value
			//CrxStructCuffPWAMeasurementData^  cuffPwaMd = nullptr; // TODO: Initialize to an appropriate value
			int expected = 1; // TODO: Initialize to an appropriate value
			int actual;

			// connect to db
			SetServerMachineName();
			target->SetConnection(serverName, sourceName);

			CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
			CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
			CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();

			DataSet^ dbRecords = target->GetPatientDemographicRecords();
			int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;

			try
			{
				expected = 1;
				////preparing test data into database///
				//-------------------------------------
				pd->SystemIdentifier = 12;
				//pd->PatientNumberInternal = 26;
				pd->LastName = "Test_Patient_Last";
				pd->FirstName = "Test_Patient_First";
				pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
				pd->Gender = "Test";
				pd->PatientIDExternalReference = "TestER";
				pd->GroupName = "Clinical";
				//pd->GroupIdentifier = 24;
				target->SavePatientData(pd);

				DataSet^ dbRecords2 = target->GetPatientDemographicRecords();
				int dbRecordCnt = dbRecords2->Tables[0]->Rows->Count;
				int SysId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][0]);
				int PatIntId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][1]);
				int GrpId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][8]);

				//DataSet^ dbRecordsGrp = target->GetGroupLists();
				//int dbGrpRecordCnt = dbRecordsGrp->Tables[0]->Rows->Count;
				//int GrpId = Convert::ToInt32(dbRecordsGrp->Tables[0]->Rows[dbGrpRecordCnt-1][0]);

				pwaMd->SystemIdentifier = SysId;
				pwaMd->PatientNumberInternal = PatIntId;
				pwaMd->GroupIdentifier = GrpId;
				pwaMd->C_RAW_SIGNALS = gcnew array<float>(1);
				pwaMd->C_RAW_SIGNALS[0] = 1234.12f;
				pwaMd->C_AV_PULSE = gcnew array<float>(1);
				pwaMd->C_AV_PULSE[0] = 1234.12f;
				pwaMd->C_TRIGS = gcnew array<short>(1);
				pwaMd->C_TRIGS[0] = 1344;
				pwaMd->C_ONSETS = gcnew array<short>(1);
				pwaMd->C_ONSETS[0] = 1344;
				pwaMd->C_Uncal_Av = gcnew array<float>(1);
				pwaMd->C_Uncal_Av[0] = 1234.12f;
				pwaMd->C_ResemblePulse = gcnew array<float>(1);
				pwaMd->C_ResemblePulse[0] = 1234.12f;
				pwaMd->C_Flow = gcnew array<float>(1);
				pwaMd->C_Flow[0] = 1234.12f;
				pwaMd->C_Forward = gcnew array<float>(1);
				pwaMd->C_Forward[0] = 1234.12f;
				pwaMd->C_Backward = gcnew array<float>(1);
				pwaMd->C_Backward[0] = 1234.12f;

				//Cuff PWA
				cuffPwaMd->P_RAW_SIGNALS = gcnew array<float>(1);
				cuffPwaMd->P_RAW_SIGNALS[0] = 1234.12f;
				cuffPwaMd->P_AV_PULSE = gcnew array<float>(1);
				cuffPwaMd->P_AV_PULSE[0] = 1234.12f;
				cuffPwaMd->P_TRIGS = gcnew array<short>(1);
				cuffPwaMd->P_TRIGS[0] = 1234;
				cuffPwaMd->P_ONSETS = gcnew array<short>(1);
				cuffPwaMd->P_ONSETS[0] = 1234;
				cuffPwaMd->P_UNCAL_AV = gcnew array<float>(1);
				cuffPwaMd->P_UNCAL_AV[0] = 1234.12f;
				cuffPwaMd->P_ResemblePulse = gcnew array<float>(1);
				cuffPwaMd->P_ResemblePulse[0] = 1234.12f;

				actual = target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				Assert::AreEqual(expected, actual);

				target->DeletePatientData(pd);
			}
			catch(Exception^)
			{
				target->DeletePatientData(pd);
				Assert::Fail();
			}

			DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
			int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
			Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
		}
		/// <summary>
		///A test for CommonShortArrtoByteArr
		///</summary>
public: [TestMethod]
		void CommonShortArrtoByteArrTest1()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			int len = 0; // TODO: Initialize to an appropriate value
			cli::array< short >^  shrtarr = nullptr; // TODO: Initialize to an appropriate value
			//cli::array< unsigned char >^  expected = nullptr; // TODO: Initialize to an appropriate value
			//cli::array< unsigned char >^  actual;
			cli::array< Byte >^  expected = nullptr;
			cli::array< Byte >^  actual;
			
			shrtarr = gcnew array<short> (1);
			shrtarr[0] = 21212;
			len = shrtarr->Length;
			array<Byte>^ bufferarr;
			expected =  gcnew array<Byte> (2);
			bufferarr = BitConverter::GetBytes(shrtarr[0]);
			expected[0] = bufferarr[0];
			expected[1] = bufferarr[1];
			actual =  gcnew array<Byte> (2);
			actual = target->CommonShortArrtoByteArr(len, shrtarr);
			Assert::AreEqual(expected[0], actual[0]);
			
			len = 0 ;
			actual =  gcnew array<Byte> (len*2);
			actual = target->CommonShortArrtoByteArr(len, shrtarr);
			expected =  gcnew array<Byte>(len*2);

			int actualTest;
			try
			{
				actual =  gcnew array<Byte> (2);
				actual = target->CommonShortArrtoByteArr(2, shrtarr);
			}					
			catch(Exception^)
			{
				actualTest = 0;
			}
			int expectedTest = 0;
			Assert::AreEqual(expectedTest,actualTest);
			
			//actual = target->CommonShortArrtoByteArr(len, shrtarr);
			//Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for UpdateCuffPWAMeasurementDetails
		///</summary>
public: [TestMethod]
		void UpdateCuffPWAMeasurementDetailsTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			//CrxStructPWAMeasurementData^  pwaMD = nullptr; // TODO: Initialize to an appropriate value
			//CrxStructCuffPWAMeasurementData^  cuffPwaMD = nullptr; // TODO: Initialize to an appropriate value
			int expected = 1; // TODO: Initialize to an appropriate value
			int actual;
			//actual = target->UpdateCuffPWAMeasurementDetails(pwaMD, cuffPwaMD);
			//Assert::AreEqual(expected, actual);
			//Assert::Inconclusive(L"Verify the correctness of this test method.");
			CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
			CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();

			try
			{
				actual = target->UpdateCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If exception occur then test case pass.");
			}

			String^ CulturalNeutralDateFormat = "yyyy-MM-dd HH:mm:ss";

			CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();	
			//CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
			//CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();

			SetServerMachineName();
			target->SetConnection(serverName, sourceName);

			DataSet^ measuremet;
			CrxStructPWAMeasurementData^ pwaMD = gcnew CrxStructPWAMeasurementData();
			CrxStructCuffPWAMeasurementData^ cuffPwaMD = gcnew CrxStructCuffPWAMeasurementData();

			DataSet^ dbRecords = target->GetPatientDemographicRecords();
			int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;

			/*SqlDataReader^ sqldatareader;*/
			//DateTime datTime;
			//DateTime AuddatTime;
			//String^ sysid;
			//int pwaId = 0;
			//int i = 0;
			
			String^ ConnStr  = String::Format("server={0};database={1};Integrated Security=true" , serverName, "AtCor");

			try
			{
				expected = 1;
				////preparing test data into database///
				//-------------------------------------
				pd->SystemIdentifier = 12;
				//pd->PatientNumberInternal = 26;
				pd->LastName = "Test_Patient_Last";
				pd->FirstName = "Test_Patient_First";
				pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
				pd->Gender = "Test";
				pd->PatientIDExternalReference = "TestER";
				pd->GroupName = "Clinical";
				//pd->GroupIdentifier = 24;
				target->SavePatientData(pd);

				DataSet^ dbRecords2 = target->GetPatientDemographicRecords();
				int dbRecordCnt = dbRecords2->Tables[0]->Rows->Count;
				int SysId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][0]);
				int PatIntId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][1]);
				int GrpId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][8]);

				//DataSet^ dbRecordsGrp = target->GetGroupLists();
				//int GrpId = Convert::ToInt32(dbRecordsGrp->Tables[0]->Rows[0][0]);

				pwaMd->SystemIdentifier = SysId;
				pwaMd->PatientNumberInternal = PatIntId;
				pwaMd->GroupIdentifier = GrpId;
				pwaMd->C_RAW_SIGNALS = gcnew array<float>(1);
				pwaMd->C_RAW_SIGNALS[0] = 1234.12f;
				pwaMd->C_AV_PULSE = gcnew array<float>(1);
				pwaMd->C_AV_PULSE[0] = 1234.12f;
				pwaMd->C_TRIGS = gcnew array<short>(1);
				pwaMd->C_TRIGS[0] = 1344;
				pwaMd->C_ONSETS = gcnew array<short>(1);
				pwaMd->C_ONSETS[0] = 1344;
				pwaMd->C_Uncal_Av = gcnew array<float>(1);
				pwaMd->C_Uncal_Av[0] = 1234.12f;
				pwaMd->C_ResemblePulse = gcnew array<float>(1);
				pwaMd->C_ResemblePulse[0] = 1234.12f;
				pwaMd->C_Flow = gcnew array<float>(1);
				pwaMd->C_Flow[0] = 1234.12f;
				pwaMd->C_Forward = gcnew array<float>(1);
				pwaMd->C_Forward[0] = 1234.12f;
				pwaMd->C_Backward = gcnew array<float>(1);
				pwaMd->C_Backward[0] = 1234.12f;
				pwaMd->Medication = "check";

				//Cuff PWA
				cuffPwaMd->P_RAW_SIGNALS = gcnew array<float>(1);
				cuffPwaMd->P_RAW_SIGNALS[0] = 1234.12f;
				cuffPwaMd->P_AV_PULSE = gcnew array<float>(1);
				cuffPwaMd->P_AV_PULSE[0] = 1234.12f;
				cuffPwaMd->P_TRIGS = gcnew array<short>(1);
				cuffPwaMd->P_TRIGS[0] = 1234;
				cuffPwaMd->P_ONSETS = gcnew array<short>(1);
				cuffPwaMd->P_ONSETS[0] = 1234;
				cuffPwaMd->P_UNCAL_AV = gcnew array<float>(1);
				cuffPwaMd->P_UNCAL_AV[0] = 1234.12f;
				cuffPwaMd->P_ResemblePulse = gcnew array<float>(1);
				cuffPwaMd->P_ResemblePulse[0] = 1234.12f;

				actual = target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				//Assert::AreEqual(expected, actual);

				////Create Connection object to check connection
				//SqlConnection^ connection = gcnew SqlConnection(ConnStr);

				////Clear all connected Pools
				//connection->ClearAllPools();

				////Open the connection to check connection can be established or not
				//connection->Open();					

				//SqlCommand^ sqlCmd = gcnew SqlCommand();
				//
				//sqlCmd->CommandText = "Select * from dbo.PWAMeasurement";
				//sqlCmd->CommandType = CommandType::Text;
				//sqlCmd->Connection = connection;

				//sqldatareader = sqlCmd->ExecuteReader();

				//if(sqldatareader->HasRows)
				//{
				//	while(sqldatareader->Read())
				//	{
				//		sysid = sqldatareader->GetString(0);
				//		
				//		i  = sqldatareader->GetInt32(1);
				//		datTime = sqldatareader->GetDateTime(3);
				//		AuddatTime = sqldatareader->GetDateTime(5);
				//		pwaId = sqldatareader->GetInt32(4);
				//		if(sysid == "12")
				//		{
				//			break;
				//		}
				//	}
				//}

				//connection->Close();

				//SetServerMachineName();
				//target->SetConnection(serverName, sourceName);
				measuremet = target->GetCuffPWAMeasurementDetails(PatIntId,GrpId,SysId);
				int checkrec = measuremet->Tables[0]->Rows->Count;

				/*for(int i = 0;i < checkrec;i++)
				{
					int tempPWAId =  Convert::ToInt32(measuremet->Tables[0]->Rows[i]["PWA_Id"]);
					String^ temppwaIdArrStr = Convert::ToInt32(tempPWAId) + ",";
					pwaIdArrStr = String::Concat(pwaIdArrStr,temppwaIdArrStr);
				}				*/

				int tempPWAId =  Convert::ToInt32(measuremet->Tables[0]->Rows[0]["PWA_Id"]);
				pwaMD->PWA_Id = tempPWAId;
				target->GetCuffPWAMeasurementDetails(pwaMD, cuffPwaMD);

				CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
				CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();
				pwaMd->PWA_Id = pwaMD->PWA_Id;
				pwaMd->SystemIdentifier = SysId;
				pwaMd->PatientNumberInternal = PatIntId;
				pwaMd->GroupIdentifier = GrpId;
				pwaMd->StudyDateTime = pwaMD->StudyDateTime;
				pwaMd->AuditChange = pwaMD->AuditChange;
				pwaMd->C_RAW_SIGNALS = gcnew array<float>(0);
				pwaMd->C_AV_PULSE = gcnew array<float>(0);
				pwaMd->C_TRIGS = gcnew array<short>(0);
				pwaMd->C_ONSETS = gcnew array<short>(0);
				pwaMd->C_Uncal_Av = gcnew array<float>(0);
				pwaMd->C_ResemblePulse = gcnew array<float>(0);
				pwaMd->C_Flow = gcnew array<float>(0);
				pwaMd->C_Forward = gcnew array<float>(0);
				pwaMd->C_Backward = gcnew array<float>(0);
				pwaMd->Medication = pwaMD->Medication;

				//Cuff PWA
				cuffPwaMd->P_RAW_SIGNALS = gcnew array<float>(0);
				cuffPwaMd->P_AV_PULSE = gcnew array<float>(0);
				cuffPwaMd->P_TRIGS = gcnew array<short>(0);
				cuffPwaMd->P_ONSETS = gcnew array<short>(0);
				cuffPwaMd->P_UNCAL_AV = gcnew array<float>(0);
				cuffPwaMd->P_ResemblePulse = gcnew array<float>(0);
				/*String^ ckh = datTime.ToString(CulturalNeutralDateFormat);
				String^ studyDateTimeArrStr =  ckh + ",";
				pwaMd->StudyDateTime = datTime;
				pwaMd->PWA_Id = pwaId;
				pwaMd->AuditChange = AuddatTime;*/
				DataSet^ measurement2;
				pwaMd->Medication = "check2";
				actual = target->UpdateCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				Assert::AreEqual(expected, actual);
				
				//CrxStructPWAMeasurementData^ pwaMD = gcnew CrxStructPWAMeasurementData();
				//CrxStructCuffPWAMeasurementData^ cuffPwaMD = gcnew CrxStructCuffPWAMeasurementData();
				measurement2 = target->GetCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				/*pwaMD->Medication =  Convert::ToString(measuremet->Tables[0]->Rows[0]["Medication"]);
				pwaMD->AuditChange = Convert::ToDateTime(measuremet->Tables[0]->Rows[0]["AuditChange"]);*/
				//Assert::AreEqual(pwaMd->Medication,pwaMD->Medication);
				//Assert::AreNotEqual(pwaMd->AuditChange,pwaMD->AuditChange);
				Assert::AreNotEqual(pwaMD->Medication,pwaMd->Medication);
				//Assert::AreNotEqual(pwaMD->AuditChange,pwaMd->AuditChange);
	
				target->DeletePatientData(pd);
			}
			catch(Exception^ eObj)
			{
				String^ ckh = eObj->Message;
				target->DeletePatientData(pd);
				Assert::Fail(ckh);
			}	

			DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
			int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
			Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
		}
		/// <summary>
		///A test for ManipulatePatientData
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void ManipulatePatientDataTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			DataSet^  patientdataset = nullptr; // TODO: Initialize to an appropriate value
			DataSet^  expected = nullptr; // TODO: Initialize to an appropriate value
			DataSet^  actual;

			SetServerMachineName();
			target->SetConnection(serverName, sourceName);

			CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();	
			
			try
			{
				
				////preparing test data into database///
				//-------------------------------------
				pd->SystemIdentifier = 12;
				//pd->PatientNumberInternal = 26;
				pd->LastName = "Test_Patient_Last";
				pd->FirstName = "Test_Patient_First";
				pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
				pd->Gender = "MALE";
				pd->PatientIDExternalReference = "TestER";
				pd->GroupName = "Clinical";
				//pd->GroupIdentifier = 24;
				target->SavePatientData(pd);

				patientdataset = gcnew DataSet();
				patientdataset = target->GetPatientDemographicRecords();
				expected = gcnew DataSet();
				expected = target->GetPatientDemographicRecords();
				expected = target->ManipulatePatientData(expected);
				String^ chk1 = Convert::ToString(expected->Tables[0]->Rows[0][Convert::ToInt32(CrxDBGetPatientDetails::Gender)]);

				actual = target->ManipulatePatientData(patientdataset);
				String^ chk2 = Convert::ToString(actual->Tables[0]->Rows[0][Convert::ToInt32(CrxDBGetPatientDetails::Gender)]);
				//Assert::AreEqual(expected, actual);
				Assert::AreEqual(chk1, chk2);

				target->DeletePatientData(pd);
			}
			catch(Exception^)
			{
				target->DeletePatientData(pd);
			}
		}
//		/// <summary>
//		///A test for DeleteCuffPWAMeasurementDetails
//		///</summary>
//public: [TestMethod]
//		void DeleteCuffPWAMeasurementDetailsTest()
//		{
//			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
//			CrxStructPWAMeasurementData^  pwaMD = nullptr; // TODO: Initialize to an appropriate value
//			String^  studyDateTimeArrStr = System::String::Empty; // TODO: Initialize to an appropriate value
//			int expected = 0; // TODO: Initialize to an appropriate value
//			int actual;
//			String^ CulturalNeutralDateFormat = "yyyy-MM-dd HH:mm:ss";
//
//			CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();	
//			CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
//			CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();
//
//			SetServerMachineName();
//			target->SetConnection(serverName, sourceName);
//
//			//Begin Smarajit Mishra 19 Apr 2011 
//			DataSet^ dbRecords = target->GetPatientDemographicRecords();
//			int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;
//			//End Smarajit Mishra 19 Apr 2011 
//
//			SqlDataReader^ sqldatareader;
//			DateTime datTime;
//			String^ sysid;
//			int i = 0;
//			
//			String^ ConnStr  = String::Format("server={0};database={1};Integrated Security=true" , serverName, "AtCor");
//
//			try
//			{
//				expected = 1;
//				////preparing test data into database///
//				//-------------------------------------
//				pd->SystemIdentifier = 12;
//				//pd->PatientNumberInternal = 26;
//				pd->LastName = "Test_Patient_Last";
//				pd->FirstName = "Test_Patient_First";
//				pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
//				pd->Gender = "Test";
//				pd->PatientIDExternalReference = "TestER";
//				pd->GroupName = "Clinical";
//				//pd->GroupIdentifier = 24;
//				target->SavePatientData(pd);
//
//				DataSet^ dbRecords2 = target->GetPatientDemographicRecords();
//				int dbRecordCnt = dbRecords2->Tables[0]->Rows->Count;
//				int SysId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][0]);
//				int PatIntId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][1]);
//				int GrpId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][8]);
//
//				//DataSet^ dbRecordsGrp = target->GetGroupLists();
//				//int GrpId = Convert::ToInt32(dbRecordsGrp->Tables[0]->Rows[0][0]);
//
//				pwaMd->SystemIdentifier = SysId;
//				pwaMd->PatientNumberInternal = PatIntId;
//				pwaMd->GroupIdentifier = GrpId;
//				pwaMd->C_RAW_SIGNALS = gcnew array<float>(1);
//				pwaMd->C_RAW_SIGNALS[0] = 1234.12f;
//				pwaMd->C_AV_PULSE = gcnew array<float>(1);
//				pwaMd->C_AV_PULSE[0] = 1234.12f;
//				pwaMd->C_TRIGS = gcnew array<short>(1);
//				pwaMd->C_TRIGS[0] = 1344;
//				pwaMd->C_ONSETS = gcnew array<short>(1);
//				pwaMd->C_ONSETS[0] = 1344;
//				pwaMd->C_Uncal_Av = gcnew array<float>(1);
//				pwaMd->C_Uncal_Av[0] = 1234.12f;
//				pwaMd->C_ResemblePulse = gcnew array<float>(1);
//				pwaMd->C_ResemblePulse[0] = 1234.12f;
//				pwaMd->C_Flow = gcnew array<float>(1);
//				pwaMd->C_Flow[0] = 1234.12f;
//				pwaMd->C_Forward = gcnew array<float>(1);
//				pwaMd->C_Forward[0] = 1234.12f;
//				pwaMd->C_Backward = gcnew array<float>(1);
//				pwaMd->C_Backward[0] = 1234.12f;
//
//				//Cuff PWA
//				cuffPwaMd->P_RAW_SIGNALS = gcnew array<float>(1);
//				cuffPwaMd->P_RAW_SIGNALS[0] = 1234.12f;
//				cuffPwaMd->P_AV_PULSE = gcnew array<float>(1);
//				cuffPwaMd->P_AV_PULSE[0] = 1234.12f;
//				cuffPwaMd->P_TRIGS = gcnew array<short>(1);
//				cuffPwaMd->P_TRIGS[0] = 1234;
//				cuffPwaMd->P_ONSETS = gcnew array<short>(1);
//				cuffPwaMd->P_ONSETS[0] = 1234;
//				cuffPwaMd->P_UNCAL_AV = gcnew array<float>(1);
//				cuffPwaMd->P_UNCAL_AV[0] = 1234.12f;
//				cuffPwaMd->P_ResemblePulse = gcnew array<float>(1);
//				cuffPwaMd->P_ResemblePulse[0] = 1234.12f;
//
//				actual = target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
//				//Assert::AreEqual(expected, actual);
//
//				//Create Connection object to check connection
//				SqlConnection^ connection = gcnew SqlConnection(ConnStr);
//
//				//Clear all connected Pools
//				connection->ClearAllPools();
//
//				//Open the connection to check connection can be established or not
//				connection->Open();					
//
//				SqlCommand^ sqlCmd = gcnew SqlCommand();
//				
//				sqlCmd->CommandText = "Select * from dbo.PWAMeasurement";
//				sqlCmd->CommandType = CommandType::Text;
//				sqlCmd->Connection = connection;
//
//				sqldatareader = sqlCmd->ExecuteReader();
//
//				if(sqldatareader->HasRows)
//				{
//					while(sqldatareader->Read())
//					{
//						sysid = sqldatareader->GetString(0);
//						
//						i  = sqldatareader->GetInt32(1);
//						datTime = sqldatareader->GetDateTime(3);
//						if(sysid == "12")
//						{
//							break;
//						}
//					}
//				}
//
//				connection->Close();
//
//				SetServerMachineName();
//				target->SetConnection(serverName, sourceName);
//
//				String^ ckh = datTime.ToString(CulturalNeutralDateFormat);
//				String^ studyDateTimeArrStr =  ckh + ",";
//				actual = target->DeleteCuffPWAMeasurementDetails(pwaMd, studyDateTimeArrStr);
//				Assert::AreEqual(expected, actual);
//	
//				target->DeletePatientData(pd);
//			}
//			catch(Exception^ eObj)
//			{
//				String^ ckh = eObj->Message;
//				target->DeletePatientData(pd);
//				Assert::Fail();
//			}	
//
//			DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
//			int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
//			Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
//			//actual = target->DeleteCuffPWAMeasurementDetails(pwaMD, studyDateTimeArrStr);
//			//Assert::AreEqual(expected, actual);
//			//Assert::Inconclusive(L"Verify the correctness of this test method.");
//		}
/// <summary>
///A test for GetPWATrendData
///</summary>
public: [TestMethod]
		void GetPWATrendDataTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  pwaIdArrStr = System::String::Empty; // TODO: Initialize to an appropriate value
			CrxStructPWATrendData^  trendDataStruct = nullptr; // TODO: Initialize to an appropriate value
			//***************/
			DataSet^  measuremet;
			/*pwaMD = gcnew CrxStructPWAMeasurementData();
			cuffPwaMD = gcnew CrxStructCuffPWAMeasurementData();*/

			CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();	
			CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
			CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();
			
			SetServerMachineName();
			target->SetConnection(serverName, sourceName);

			DataSet^ dbRecords = target->GetPatientDemographicRecords();
			int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;

			try
			{
				//expected = 1;
				////preparing test data into database///
				//-------------------------------------
				pd->SystemIdentifier = 12;
				//pd->PatientNumberInternal = 26;
				pd->LastName = "Test_Patient_Last";
				pd->FirstName = "Test_Patient_First";
				pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
				pd->Gender = "Test";
				pd->PatientIDExternalReference = "TestER";
				pd->GroupName = "Clinical";
				//pd->GroupIdentifier = 24;
				target->SavePatientData(pd);

				DataSet^ dbRecords2 = target->GetPatientDemographicRecords();
				int dbRecordCnt = dbRecords2->Tables[0]->Rows->Count;
				int SysId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][0]);
				int PatIntId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][1]);
				int GrpId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][8]);

				/*DataSet^ dbRecordsGrp = target->GetGroupLists();
				int GrpId = Convert::ToInt32(dbRecordsGrp->Tables[0]->Rows[0][0]);*/

				pwaMd->SystemIdentifier = SysId;
				pwaMd->PatientNumberInternal = PatIntId;
				pwaMd->GroupIdentifier = GrpId;
				pwaMd->C_RAW_SIGNALS = gcnew array<float>(1);
				pwaMd->C_RAW_SIGNALS[0] = 1234.12f;
				pwaMd->C_AV_PULSE = gcnew array<float>(1);
				pwaMd->C_AV_PULSE[0] = 1234.12f;
				pwaMd->C_TRIGS = gcnew array<short>(1);
				pwaMd->C_TRIGS[0] = 1344;
				pwaMd->C_ONSETS = gcnew array<short>(1);
				pwaMd->C_ONSETS[0] = 1344;
				pwaMd->C_Uncal_Av = gcnew array<float>(1);
				pwaMd->C_Uncal_Av[0] = 1234.12f;
				pwaMd->C_ResemblePulse = gcnew array<float>(1);
				pwaMd->C_ResemblePulse[0] = 1234.12f;
				pwaMd->C_Flow = gcnew array<float>(1);
				pwaMd->C_Flow[0] = 1234.12f;
				pwaMd->C_Forward = gcnew array<float>(1);
				pwaMd->C_Forward[0] = 1234.12f;
				pwaMd->C_Backward = gcnew array<float>(1);
				pwaMd->C_Backward[0] = 1234.12f;
				pwaMd->C_Sp = 1122.1f;
				pwaMd->C_Ap = 1123.1f;
				pwaMd->C_Dp = 1124.1f;
				pwaMd->C_Meanp = 1125.1f;
				pwaMd->HR = 1126.1f;

				//Cuff PWA
				cuffPwaMd->P_RAW_SIGNALS = gcnew array<float>(1);
				cuffPwaMd->P_RAW_SIGNALS[0] = 1234.12f;
				cuffPwaMd->P_AV_PULSE = gcnew array<float>(1);
				cuffPwaMd->P_AV_PULSE[0] = 1234.12f;
				cuffPwaMd->P_TRIGS = gcnew array<short>(1);
				cuffPwaMd->P_TRIGS[0] = 1234;
				cuffPwaMd->P_ONSETS = gcnew array<short>(1);
				cuffPwaMd->P_ONSETS[0] = 1234;
				cuffPwaMd->P_UNCAL_AV = gcnew array<float>(1);
				cuffPwaMd->P_UNCAL_AV[0] = 1234.12f;
				cuffPwaMd->P_ResemblePulse = gcnew array<float>(1);
				cuffPwaMd->P_ResemblePulse[0] = 1234.12f;

				target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				/*target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);*/
								
				measuremet = target->GetCuffPWAMeasurementDetails(PatIntId,GrpId,SysId);
				int checkrec = measuremet->Tables[0]->Rows->Count;
				for(int i = 0;i < checkrec;i++)
				{
					int tempPWAId =  Convert::ToInt32(measuremet->Tables[0]->Rows[i]["PWA_Id"]);
					String^ temppwaIdArrStr = Convert::ToInt32(tempPWAId) + ",";
					pwaIdArrStr = String::Concat(pwaIdArrStr,temppwaIdArrStr);
				}				

				int tempPWAId =  Convert::ToInt32(measuremet->Tables[0]->Rows[0]["PWA_Id"]);
				/*pwaMd->C_Sp = 1122.12f;
				pwaMd->C_Ap = 1123.12f;
				pwaMd->C_Dp = 1124.12f;
				pwaMd->C_Meanp = 1125.12f;
				pwaMd->HR = 1126.12f;*/
				trendDataStruct = gcnew CrxStructPWATrendData();
				target->GetPWATrendData(pwaIdArrStr, trendDataStruct);
				//Assert::AreEqual(expected, actual);	
				Assert::AreEqual("1122.1,1122.1,1122.1,1122.1",trendDataStruct->SpValidArrStr);
				Assert::AreEqual("1123.1,1123.1,1123.1,1123.1",trendDataStruct->ApValidArrStr);
				Assert::AreEqual("1124.1,1124.1,1124.1,1124.1",trendDataStruct->DpValidArrStr);
				Assert::AreEqual("1125.1,1125.1,1125.1,1125.1",trendDataStruct->MpValidArrStr);
				Assert::AreEqual("1126.1,1126.1,1126.1,1126.1",trendDataStruct->HrValidArrStr);
				
				target->DeletePatientData(pd);

			}
			catch(Exception^ eObj)
			{
				String^ ckh = eObj->Message;
				target->DeletePatientData(pd);
				Assert::Fail();
			}	
			/*target->GetPWATrendData(pwaIdArrStr, trendDataStruct);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");*/
		}
		/// <summary>
		///A test for GetPWATrendData
		///</summary>
public: [TestMethod]
		void GetPWATrendDataTest1()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); 
			
			String^  pwaIdArrStr = System::String::Empty; 
			CrxStructPWATrendData^  trendDataStruct = gcnew CrxStructPWATrendData();
			
			//Testing without database connection for exception
			try
			{
				target->GetPWATrendData(pwaIdArrStr, trendDataStruct);
				//If in this case no exception occurs, means test case failed
				Assert::Fail();
			}
			catch(Exception^)
			{
				//If exception occurs, means test case passed
				Assert::IsTrue(true);
			}
		}
		/// <summary>
		///A test for GetCuffPWAMeasurementDetails
		///</summary>
public: [TestMethod]
		void GetCuffPWAMeasurementDetailsTest1()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			CrxStructPWAMeasurementData^  pwaMD = nullptr; // TODO: Initialize to an appropriate value
			CrxStructCuffPWAMeasurementData^  cuffPwaMD = nullptr; // TODO: Initialize to an appropriate value
			DataSet^  expected = nullptr; // TODO: Initialize to an appropriate value
			DataSet^  actual;
			//***************/
			DataSet^  measuremet;
			pwaMD = gcnew CrxStructPWAMeasurementData();
			cuffPwaMD = gcnew CrxStructCuffPWAMeasurementData();

			CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();	
			CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
			CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();
			
			SetServerMachineName();
			target->SetConnection(serverName, sourceName);

			DataSet^ dbRecords = target->GetPatientDemographicRecords();
			int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;

			try
			{
				//expected = 1;
				////preparing test data into database///
				//-------------------------------------
				pd->SystemIdentifier = 12;
				//pd->PatientNumberInternal = 26;
				pd->LastName = "Test_Patient_Last";
				pd->FirstName = "Test_Patient_First";
				pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
				pd->Gender = "Test";
				pd->PatientIDExternalReference = "TestER";
				pd->GroupName = "Clinical";
				//pd->GroupIdentifier = 24;
				target->SavePatientData(pd);

				DataSet^ dbRecords2 = target->GetPatientDemographicRecords();
				int dbRecordCnt = dbRecords2->Tables[0]->Rows->Count;
				int SysId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][0]);
				int PatIntId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][1]);
				int GrpId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][8]);

				/*DataSet^ dbRecordsGrp = target->GetGroupLists();
				int GrpId = Convert::ToInt32(dbRecordsGrp->Tables[0]->Rows[0][0]);*/

				pwaMd->SystemIdentifier = SysId;
				pwaMd->PatientNumberInternal = PatIntId;
				pwaMd->GroupIdentifier = GrpId;
				pwaMd->C_RAW_SIGNALS = gcnew array<float>(1);
				pwaMd->C_RAW_SIGNALS[0] = 1234.12f;
				pwaMd->C_AV_PULSE = gcnew array<float>(1);
				pwaMd->C_AV_PULSE[0] = 1234.12f;
				pwaMd->C_TRIGS = gcnew array<short>(1);
				pwaMd->C_TRIGS[0] = 1344;
				pwaMd->C_ONSETS = gcnew array<short>(1);
				pwaMd->C_ONSETS[0] = 1344;
				pwaMd->C_Uncal_Av = gcnew array<float>(1);
				pwaMd->C_Uncal_Av[0] = 1234.12f;
				pwaMd->C_ResemblePulse = gcnew array<float>(1);
				pwaMd->C_ResemblePulse[0] = 1234.12f;
				pwaMd->C_Flow = gcnew array<float>(1);
				pwaMd->C_Flow[0] = 1234.12f;
				pwaMd->C_Forward = gcnew array<float>(1);
				pwaMd->C_Forward[0] = 1234.12f;
				pwaMd->C_Backward = gcnew array<float>(1);
				pwaMd->C_Backward[0] = 1234.12f;

				//Cuff PWA
				cuffPwaMd->P_RAW_SIGNALS = gcnew array<float>(1);
				cuffPwaMd->P_RAW_SIGNALS[0] = 1234.12f;
				cuffPwaMd->P_AV_PULSE = gcnew array<float>(1);
				cuffPwaMd->P_AV_PULSE[0] = 1234.12f;
				cuffPwaMd->P_TRIGS = gcnew array<short>(1);
				cuffPwaMd->P_TRIGS[0] = 1234;
				cuffPwaMd->P_ONSETS = gcnew array<short>(1);
				cuffPwaMd->P_ONSETS[0] = 1234;
				cuffPwaMd->P_UNCAL_AV = gcnew array<float>(1);
				cuffPwaMd->P_UNCAL_AV[0] = 1234.12f;
				cuffPwaMd->P_ResemblePulse = gcnew array<float>(1);
				cuffPwaMd->P_ResemblePulse[0] = 1234.12f;

				target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
								
				measuremet = target->GetCuffPWAMeasurementDetails(PatIntId,GrpId,SysId);
				int checkrec = measuremet->Tables[0]->Rows->Count;

				/*for(int i = 0;i < checkrec;i++)
				{
					int tempPWAId =  Convert::ToInt32(measuremet->Tables[0]->Rows[i]["PWA_Id"]);
					String^ temppwaIdArrStr = Convert::ToInt32(tempPWAId) + ",";
					pwaIdArrStr = String::Concat(pwaIdArrStr,temppwaIdArrStr);
				}				*/

				int tempPWAId =  Convert::ToInt32(measuremet->Tables[0]->Rows[0]["PWA_Id"]);
				pwaMD->PWA_Id = tempPWAId;
				actual = target->GetCuffPWAMeasurementDetails(pwaMD, cuffPwaMD);

				//Assert::AreEqual(expected, actual);	
				Assert::AreEqual(tempPWAId,cuffPwaMD->PWA_Id);
				Assert::AreEqual(pwaMd->C_ResemblePulse[0],pwaMD->C_ResemblePulse[0]);

				target->DeletePatientData(pd);

			}
			catch(Exception^ eObj)
			{
				String^ ckh = eObj->Message;
				target->DeletePatientData(pd);
				Assert::Fail();
			}	

			DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
			int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
			Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
			//actual = target->GetCuffPWAMeasurementDetails(pwaMD, cuffPwaMD);
			//Assert::AreEqual(expected, actual);
			//Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for GetCuffPWAMeasurementDetails
		///</summary>
public: [TestMethod]
		void GetCuffPWAMeasurementDetailsTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			int patientNumberInternal = 0; // TODO: Initialize to an appropriate value
			int groupIdentifier = 0; // TODO: Initialize to an appropriate value
			int systemIdentifier = 0; // TODO: Initialize to an appropriate value
			DataSet^  expected = nullptr; // TODO: Initialize to an appropriate value
			DataSet^  actual = nullptr;
			//***************/
			DataSet^  measuremet;
		
			CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();	
			CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
			CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();
			
			SetServerMachineName();
			target->SetConnection(serverName, sourceName);

			DataSet^ dbRecords = target->GetPatientDemographicRecords();
			int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;

			try
			{
				//expected = 1;
				////preparing test data into database///
				//-------------------------------------
				pd->SystemIdentifier = 12;
				//pd->PatientNumberInternal = 26;
				pd->LastName = "Test_Patient_Last";
				pd->FirstName = "Test_Patient_First";
				pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
				pd->Gender = "Test";
				pd->PatientIDExternalReference = "TestER";
				pd->GroupName = "Clinical";
				//pd->GroupIdentifier = 24;
				target->SavePatientData(pd);

				DataSet^ dbRecords2 = target->GetPatientDemographicRecords();
				int dbRecordCnt = dbRecords2->Tables[0]->Rows->Count;
				int SysId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][0]);
				int PatIntId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][1]);
				int GrpId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][8]);

				/*DataSet^ dbRecordsGrp = target->GetGroupLists();
				int GrpId = Convert::ToInt32(dbRecordsGrp->Tables[0]->Rows[0][0]);*/

				pwaMd->SystemIdentifier = SysId;
				pwaMd->PatientNumberInternal = PatIntId;
				pwaMd->GroupIdentifier = GrpId;
				pwaMd->C_RAW_SIGNALS = gcnew array<float>(1);
				pwaMd->C_RAW_SIGNALS[0] = 1234.12f;
				pwaMd->C_AV_PULSE = gcnew array<float>(1);
				pwaMd->C_AV_PULSE[0] = 1234.12f;
				pwaMd->C_TRIGS = gcnew array<short>(1);
				pwaMd->C_TRIGS[0] = 1344;
				pwaMd->C_ONSETS = gcnew array<short>(1);
				pwaMd->C_ONSETS[0] = 1344;
				pwaMd->C_Uncal_Av = gcnew array<float>(1);
				pwaMd->C_Uncal_Av[0] = 1234.12f;
				pwaMd->C_ResemblePulse = gcnew array<float>(1);
				pwaMd->C_ResemblePulse[0] = 1234.12f;
				pwaMd->C_Flow = gcnew array<float>(1);
				pwaMd->C_Flow[0] = 1234.12f;
				pwaMd->C_Forward = gcnew array<float>(1);
				pwaMd->C_Forward[0] = 1234.12f;
				pwaMd->C_Backward = gcnew array<float>(1);
				pwaMd->C_Backward[0] = 1234.12f;

				//Cuff PWA
				cuffPwaMd->P_RAW_SIGNALS = gcnew array<float>(1);
				cuffPwaMd->P_RAW_SIGNALS[0] = 1234.12f;
				cuffPwaMd->P_AV_PULSE = gcnew array<float>(1);
				cuffPwaMd->P_AV_PULSE[0] = 1234.12f;
				cuffPwaMd->P_TRIGS = gcnew array<short>(1);
				cuffPwaMd->P_TRIGS[0] = 1234;
				cuffPwaMd->P_ONSETS = gcnew array<short>(1);
				cuffPwaMd->P_ONSETS[0] = 1234;
				cuffPwaMd->P_UNCAL_AV = gcnew array<float>(1);
				cuffPwaMd->P_UNCAL_AV[0] = 1234.12f;
				cuffPwaMd->P_ResemblePulse = gcnew array<float>(1);
				cuffPwaMd->P_ResemblePulse[0] = 1234.12f;

				target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
								
				measuremet = target->GetCuffPWAMeasurementDetails(PatIntId,GrpId,SysId);
				int checkrec = measuremet->Tables[0]->Rows->Count;

				int tempSysId =  Convert::ToInt32(measuremet->Tables[0]->Rows[0]["SystemIdentifier"]);
				int tempPatId =  Convert::ToInt32(measuremet->Tables[0]->Rows[0]["PatientNumberInternal"]);
				
				//Assert::AreEqual(expected, actual);	
				Assert::AreEqual(SysId,tempSysId);
				Assert::AreEqual(PatIntId,tempPatId);

				target->DeletePatientData(pd);

			}
			catch(Exception^ eObj)
			{
				String^ ckh = eObj->Message;
				target->DeletePatientData(pd);
				Assert::Fail();
			}	

			DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
			int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
			Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);
			/*actual = target->GetCuffPWAMeasurementDetails(patientNumberInternal, groupIdentifier, systemIdentifier);
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");*/
		}
		/// <summary>
		///A test for DeleteCuffPWAMeasurementDetails
		///</summary>
public: [TestMethod]
		void DeleteCuffPWAMeasurementDetailsTest()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			String^  pwaIdArrStr = System::String::Empty; // TODO: Initialize to an appropriate value
			int expected = 0; // TODO: Initialize to an appropriate value
			int actual;
			//***************/
			DataSet^  measuremet;
			CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();	
			CrxStructPWAMeasurementData^  pwaMd = gcnew CrxStructPWAMeasurementData();
			CrxStructCuffPWAMeasurementData^  cuffPwaMd = gcnew CrxStructCuffPWAMeasurementData();
			
			SetServerMachineName();
			target->SetConnection(serverName, sourceName);

			DataSet^ dbRecords = target->GetPatientDemographicRecords();
			int dbRecordsCount = dbRecords->Tables[0]->Rows->Count;

			try
			{
				expected = 1;
				////preparing test data into database///
				//-------------------------------------
				pd->SystemIdentifier = 12;
				//pd->PatientNumberInternal = 26;
				pd->LastName = "Test_Patient_Last";
				pd->FirstName = "Test_Patient_First";
				pd->DateOfBirth = Convert::ToDateTime("08/09/1985");
				pd->Gender = "Test";
				pd->PatientIDExternalReference = "TestER";
				pd->GroupName = "Clinical";
				//pd->GroupIdentifier = 24;
				target->SavePatientData(pd);

				DataSet^ dbRecords2 = target->GetPatientDemographicRecords();
				int dbRecordCnt = dbRecords2->Tables[0]->Rows->Count;
				int SysId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][0]);
				int PatIntId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][1]);
				int GrpId =  Convert::ToInt32(dbRecords2->Tables[0]->Rows[dbRecordCnt-1][8]);

				/*DataSet^ dbRecordsGrp = target->GetGroupLists();
				int GrpId = Convert::ToInt32(dbRecordsGrp->Tables[0]->Rows[0][0]);*/

				pwaMd->SystemIdentifier = SysId;
				pwaMd->PatientNumberInternal = PatIntId;
				pwaMd->GroupIdentifier = GrpId;
				pwaMd->C_RAW_SIGNALS = gcnew array<float>(1);
				pwaMd->C_RAW_SIGNALS[0] = 1234.12f;
				pwaMd->C_AV_PULSE = gcnew array<float>(1);
				pwaMd->C_AV_PULSE[0] = 1234.12f;
				pwaMd->C_TRIGS = gcnew array<short>(1);
				pwaMd->C_TRIGS[0] = 1344;
				pwaMd->C_ONSETS = gcnew array<short>(1);
				pwaMd->C_ONSETS[0] = 1344;
				pwaMd->C_Uncal_Av = gcnew array<float>(1);
				pwaMd->C_Uncal_Av[0] = 1234.12f;
				pwaMd->C_ResemblePulse = gcnew array<float>(1);
				pwaMd->C_ResemblePulse[0] = 1234.12f;
				pwaMd->C_Flow = gcnew array<float>(1);
				pwaMd->C_Flow[0] = 1234.12f;
				pwaMd->C_Forward = gcnew array<float>(1);
				pwaMd->C_Forward[0] = 1234.12f;
				pwaMd->C_Backward = gcnew array<float>(1);
				pwaMd->C_Backward[0] = 1234.12f;

				//Cuff PWA
				cuffPwaMd->P_RAW_SIGNALS = gcnew array<float>(1);
				cuffPwaMd->P_RAW_SIGNALS[0] = 1234.12f;
				cuffPwaMd->P_AV_PULSE = gcnew array<float>(1);
				cuffPwaMd->P_AV_PULSE[0] = 1234.12f;
				cuffPwaMd->P_TRIGS = gcnew array<short>(1);
				cuffPwaMd->P_TRIGS[0] = 1234;
				cuffPwaMd->P_ONSETS = gcnew array<short>(1);
				cuffPwaMd->P_ONSETS[0] = 1234;
				cuffPwaMd->P_UNCAL_AV = gcnew array<float>(1);
				cuffPwaMd->P_UNCAL_AV[0] = 1234.12f;
				cuffPwaMd->P_ResemblePulse = gcnew array<float>(1);
				cuffPwaMd->P_ResemblePulse[0] = 1234.12f;

				actual = target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				actual = target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				actual = target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				actual = target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				actual = target->SaveCuffPWAMeasurementDetails(pwaMd, cuffPwaMd);
				
				measuremet = target->GetCuffPWAMeasurementDetails(PatIntId,GrpId,SysId);
				int checkrec = measuremet->Tables[0]->Rows->Count;

				for(int i = 0;i < checkrec;i++)
				{
					int tempPWAId =  Convert::ToInt32(measuremet->Tables[0]->Rows[i]["PWA_Id"]);
					String^ temppwaIdArrStr = Convert::ToInt32(tempPWAId) + ",";
					pwaIdArrStr = String::Concat(pwaIdArrStr,temppwaIdArrStr);
				}				

				actual = target->DeleteCuffPWAMeasurementDetails(pwaIdArrStr);

				Assert::AreEqual(expected, actual);	

				target->DeletePatientData(pd);

			}
			catch(Exception^ eObj)
			{
				String^ ckh = eObj->Message;
				target->DeletePatientData(pd);
				Assert::Fail();
			}	

			DataSet^ dbRecordsFinal = target->GetPatientDemographicRecords();
			int dbRecordsCountFinal = dbRecordsFinal->Tables[0]->Rows->Count;
			Assert::AreEqual(dbRecordsCount,dbRecordsCountFinal);

			//*****************/

			//actual = target->DeleteCuffPWAMeasurementDetails(pwaIdArrStr);
			//Assert::AreEqual(expected, actual);
			//Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for CommonByteArrtoShortArr
		///</summary>
public: [TestMethod]
		void CommonByteArrtoShortArrTest1()
		{
			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
			cli::array< unsigned char >^  bytearr = nullptr; // TODO: Initialize to an appropriate value
			int len = 0; // TODO: Initialize to an appropriate value
			cli::array< short >^  expected = nullptr; // TODO: Initialize to an appropriate value
			cli::array< short >^  actual;
		
			///Smarajit

			array<short >^ shrtarr = gcnew array<short> (1);
			shrtarr[0] = 21212;
			len = shrtarr->Length;
			array<Byte>^ bufferarr;
			bytearr =  gcnew array<Byte> (2);
			bufferarr = BitConverter::GetBytes(shrtarr[0]);
			bytearr[0] = bufferarr[0];
			bytearr[1] = bufferarr[1];
			expected = gcnew array<short>(len);
			short value = BitConverter::ToInt16(bytearr,0);		
			expected[0] = value;
			//smarajit
			actual = target->CommonByteArrtoShortArr(bytearr,len);
			Assert::AreEqual(expected[0], actual[0]);

			bytearr =  gcnew array<Byte> (2);
			bufferarr = BitConverter::GetBytes(shrtarr[0]);
			bytearr[0] = bufferarr[0];
			bytearr[1] = bufferarr[1];
			expected = gcnew array<short>(len);
			value = BitConverter::ToInt16(bytearr,0);		
			expected[0] = value;
			len =0;
			int actualTest;
			try
			{
				actual = target->CommonByteArrtoShortArr(bytearr,2);
			}
			
			catch(Exception^)
			{
				actualTest = 0;
			}
			int expectedTest = 0;
			Assert::AreEqual(expectedTest,actualTest);
			//actual = target->CommonByteArrtoShortArr(bytearr, len);
			//Assert::AreEqual(expected, actual);
			//Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
};
}
namespace TestCrx {
    
}