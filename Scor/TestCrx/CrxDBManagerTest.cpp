
#include "StdAfx.h"
using namespace System::Data;
using namespace System::IO;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::DatabaseManager;
using namespace AtCor::Scor::CrossCutting::Logging;

using namespace System;
using namespace System::Text;
using namespace System::Data;
using namespace System::Data::Common;
using namespace System::Data::SqlClient;
using namespace System::Data::OleDb;

using namespace Microsoft::Practices::EnterpriseLibrary::Data;
using namespace Microsoft::Practices::EnterpriseLibrary::Data::Sql;

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

			static String^  serverName = "MUM-9696";
			static String^  sourceName = "SQLCLIENT";

			void SetPath()
			{
				String^ path = Directory::GetCurrentDirectory(); 
				int i = path->IndexOf("\\TestResults");
				path = path->Substring(0,i + 12);
				Directory::SetCurrentDirectory(path);
				
			}
#pragma region Additional test attributes
			// 
			//You can use the following additional attributes as you write your tests:
			//
			//Use ClassInitialize to run code before running the first test in the class
			//public: [ClassInitialize]
			//static System::Void MyClassInitialize(TestContext^  testContext)
			//{
			//}
			//
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

				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DataProviderType
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void DataProviderTypeTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  expected = "SQLEXPRESS";
				String^  actual;
				target->DataProviderType = expected;
				actual = target->DataProviderType;
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ConnString
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void ConnStringTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  expected = "server=serverName;database=AtCor;Integrated Security=true";
				String^  actual;
				target->ConnString = expected;
				actual = target->ConnString;
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for UpdatePWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void UpdatePWVMeasurementDetailsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPWVMeasurementData^  md = nullptr; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				target->SetConnection(serverName, sourceName);

				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
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
					pwvmd->MeanPulseWaveVelocity = 4.4000;
					pwvmd->StandardDeviation = 3.300;
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
					
					Assert::AreEqual(pwvmd->PWVDistance,Convert::ToDateTime(msrds->Tables[0]->Rows[0]["PWVDistance"]));
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
				}
			}
			/// <summary>
			///A test for UpdatePatientData
			///</summary>
	public: [TestMethod]
			void UpdatePatientDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPatientDemographicData^  pd = nullptr; // TODO: Initialize to an appropriate value
				bool spCheck = false; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;

				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				pd->SystemIdentifier = 31256;
				pd->PatientNumberInternal = 12;
				pd->PatientIDExternalReference = "P03148";
				pd->LastName = "Final23";
				String^ date = "08/09/1984";
				pd->DateOfBirth = Convert::ToDateTime(date);
				pd->GroupName = "Dr8";
				pd->GroupIdentifier = 9;
                pd->FirstName = "Final234erer";
                pd->Gender = "Male"; 
				expected = 1;

				actual = target->UpdatePatientData(pd, spCheck);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SetConnection
			///</summary>
	public: [TestMethod]
			void SetConnectionTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  serverName = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  sourceName = System::String::Empty; // TODO: Initialize to an appropriate value
				int expected = 1; // TODO: Initialize to an appropriate value
				int actual;
				String^ serverNameTest = "MUM-9696\\SQLEXPRESS";
				String^  sourceNameTest = "SQLCLIENT";
				try
				{
					actual = target->SetConnection(serverNameTest, sourceNameTest);
				}
				catch(Exception^)
				{

				}
				Assert::AreEqual(expected, actual);
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


				///Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SavePWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void SavePWVMeasurementDetailsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPWVMeasurementData^  md = nullptr; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;

				target->SetConnection(serverName, sourceName);
				CrxStructPWVMeasurementData^  md = gcnew CrxStructPWVMeasurementData();
				md->SystemIdentifier = 31256;
                md->GroupIdentifier = 4;
                md->PatientNumberInternal = 6;

				md->Notes = "CheckOut";
				md->Carotid = 111;
				md->WeightInKilograms = 75;
				md->HeightInCentimetres = 175;
				md->CarotidSignal = gcnew array<unsigned short>(1);
				md->CarotidSignal[0] = 1244;
				md->FemoralSignal = gcnew array<unsigned short>(1);
				md->FemoralSignal[0] = 1344;
				md->CarotidSignalFloatOnSets = gcnew array<float>(1);
				md->CarotidSignalFloatOnSets[0] = 1234.12f;
				md->FemoralSignalFloatOnSets = gcnew array<float>(1);
				md->FemoralSignalFloatOnSets[0] = 2345.23f;
				md->ReferenceRange = gcnew array<float>(1);
				md->ReferenceRange[0] = 3456.34f;
				md->NormalRange = gcnew array<float>(1);
				md->NormalRange[0] =  4567.45f;
				expected  = 1;
				actual = target->SavePWVMeasurementDetails(md);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SavePatientData
			///</summary>
	public: [TestMethod]
			void SavePatientDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPatientDemographicData^  pd = nullptr; // TODO: Initialize to an appropriate value
				//int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				int expected = 1; 

				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				pd->SystemIdentifier = 31256;				
				pd->PatientIDExternalReference = "P03149";
				pd->LastName = "Final23";
				String^ date = "08/09/1984";
				pd->DateOfBirth = Convert::ToDateTime(date);
				pd->GroupName = "Dr8";
                pd->FirstName = "Final234erer";
                pd->Gender = "Male"; 

				actual = target->SavePatientData(pd);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ResetDatabaseToMultiuser
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void ResetDatabaseToMultiuserTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value

				try
				{
					target->ResetDatabaseToMultiuser();
					//If in this case no exception occurs, means test case failed
					Assert::Fail();
				}
				catch(Exception^)
				{
					//If exception occurs, means test case passed
					Assert::IsTrue(true);
				}

				try
				{
					target->SetConnection(serverName, sourceName);
					target->ResetDatabaseToMultiuser();
					//If in this case exception occurs, means test case failed
					Assert::IsTrue(true);
				}
				catch(Exception^)
				{
					//If exception occurs, means test case failed
					Assert::Fail();
				}

				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for PatientRecordExists
			///</summary>
	public: [TestMethod]
			void PatientRecordExistsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPatientDemographicData^  pd = nullptr; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;

				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				pd->SystemIdentifier = 31256;
				pd->PatientIDExternalReference = "P03148";
				pd->LastName = "Final23";
				String^ date = "08/09/1984";
				pd->DateOfBirth = Convert::ToDateTime(date);
				pd->GroupName = "Dr8";
                pd->FirstName = "Final234erer";
                pd->Gender = "Female"; 

				expected = 0;

				actual = target->PatientRecordExists(pd);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for PatientIdExists
			///</summary>
	public: [TestMethod]
			void PatientIdExistsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int systemIdentifier = 0; // TODO: Initialize to an appropriate value
				String^  patientIdExternalReference = System::String::Empty; // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;

				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				systemIdentifier = 31256;
				patientIdExternalReference = "P03148";
				expected = true;

				actual = target->PatientIdExists(systemIdentifier, patientIdExternalReference);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
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
	//			CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxDBManager^  unnamed = nullptr; // TODO: Initialize to an appropriate value
	//			CrxDBManager^  expected = nullptr; // TODO: Initialize to an appropriate value
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
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxLogger^  objLog = nullptr; // TODO: Initialize to an appropriate value
				cli::array< String^  >^  skipPatientlog = gcnew array<String^>(2);; // TODO: Initialize to an appropriate value
				
				objLog = CrxLogger::Instance ; // TODO: Initialize to an appropriate value
				
				skipPatientlog[0] = "ThisIsForTestOnly";
				target->MigrationLogDetail(objLog, skipPatientlog);

				StreamReader ^curLogFileFileStream;
				String ^ path = Directory::GetCurrentDirectory() + "\\system\\logs\\";
				
				if(!Directory::Exists(path))
				{
					Directory::CreateDirectory(path);
					File::Create(path + "Scor.xyz");
				}

				if(File::Exists(path+"scor_test.log"))
				{
					File::Delete(path+"scor_test.log");	
				}
				File::Copy(path+"scor.log",path+"scor_test.log"); 
				
				curLogFileFileStream =gcnew StreamReader(File::Open(path+"scor_test.log", FileMode::Open,FileAccess::Read,FileShare::Read ));

				String ^fileStr = curLogFileFileStream->ReadToEnd();
				String ^lastLine = fileStr->Substring(fileStr->LastIndexOf('\n',(fileStr->Length) - 5) + 1);

				lastLine = lastLine->Trim();

				lastLine= lastLine->Substring(lastLine->LastIndexOf('\t')+1); 
				Assert::AreEqual(lastLine, skipPatientlog[0]);
				curLogFileFileStream->Close();
			}
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void MigrationLogDetailTest1()
			{
				///////////Negative test case////////////////

				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxLogger^  objLog = nullptr; // TODO: Initialize to an appropriate value
				cli::array< String^  >^  skipPatientlog = gcnew array<String^>(2);; // TODO: Initialize to an appropriate value
				
				objLog = CrxLogger::Instance ; // TODO: Initialize to an appropriate value
				
				StreamReader ^curLogFileFileStream;
				objLog = nullptr ; // TODO: Initialize to an appropriate value	
				skipPatientlog[0] = "";
				try
				{
					target->MigrationLogDetail(objLog, skipPatientlog);
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
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				OleDbDataReader^  rdr = nullptr; // TODO: Initialize to an appropriate value
				CrxLogger^  objLog = nullptr; // TODO: Initialize to an appropriate value
				int rowNum = 0; // TODO: Initialize to an appropriate value
				int systemIdentifier = 0; // TODO: Initialize to an appropriate value
				String^  groupName = System::String::Empty; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;

				/// testing woth no data in rdr
				objLog = CrxLogger::Instance;
				systemIdentifier = 11;
				groupName = "Test";
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
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				OleDbDataReader^  rdr = nullptr; // TODO: Initialize to an appropriate value
				CrxLogger^  objLog = nullptr; // TODO: Initialize to an appropriate value
				int rowNum = 0; // TODO: Initialize to an appropriate value
				int systemIdentifier = 0; // TODO: Initialize to an appropriate value
				String^  groupName = System::String::Empty; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;

				/// testing woth no data in rdr
				objLog = CrxLogger::Instance;
				systemIdentifier = 11;
				groupName = "Test";
				target->SetConnection(serverName, sourceName);
				// passing OleDbDataReader as null ptr, function is suppose to rollback transaction on this
				actual = target->MigrationInternal(rdr, objLog, rowNum, systemIdentifier, groupName);
				
				///testing transaction rollback
				StreamReader ^curLogFileFileStream;
				String ^ path = Directory::GetCurrentDirectory() + "\\system\\logs\\";
				if(!Directory::Exists(path))
				{
					Directory::CreateDirectory(path);
				}
				if(File::Exists(path+"scor_test.log"))
				{
					File::Delete(path+"scor_test.log");	
				}
				File::Copy(path+"scor.log",path+"scor_test.log"); 
				
				curLogFileFileStream =gcnew StreamReader(File::Open(path+"scor_test.log", FileMode::Open,FileAccess::Read,FileShare::Read ));

				String ^fileStr = curLogFileFileStream->ReadToEnd();
				String ^lastLine = fileStr->Substring(fileStr->LastIndexOf('\n',(fileStr->Length) - 5) + 1);

				lastLine = lastLine->Trim();

				lastLine= lastLine->Substring(lastLine->LastIndexOf('\t')+1); 
				
				//Checking that transction rollback execution
				Assert::IsNotNull(lastLine);
				//Assert::AreEqual(lastLine, "Migration failed.");
				curLogFileFileStream->Close();

			}
			/// <summary>
			///A test for MigrationFileExist
			///</summary>
	public: [TestMethod]
			void MigrationFileExistTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;

				//Alok
				String^ curDir = Directory::GetCurrentDirectory();
				String ^ path = curDir + "\\system\\data\\";
				target->SetConnection(serverName, sourceName);
				//File not exists, so checking IsFalse
				if(File::Exists(path + "scor.xyz"))
				{
					File::Delete(path + "scor.xyz");
				}
				Assert::IsFalse(target->MigrationFileExist());

				//Creating a file
				if(!Directory::Exists(path))
				{
					Directory::CreateDirectory(path);
				}
				String^ filePath = path + "scor.xyz";
				File::Create(filePath);
				//File exists, so checking IsTrue
				Assert::IsTrue(target->MigrationFileExist());

				
			}
			/// <summary>
			///A test for MigrateAtCorData
			///</summary>
	public: [TestMethod]
			void MigrateAtCorDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int systemIdentifier = 0; // TODO: Initialize to an appropriate value
				String^  groupName = System::String::Empty; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				
				groupName = "Dr.Alok";
				systemIdentifier = 31256;
				
				SetPath();
				//Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\Scor_Source_code\\TestResults\\");
				target->SetConnection(serverName, sourceName);

				if(File::Exists(Directory::GetCurrentDirectory() + "\\system\\data\\scor.xyz"))
				{
					actual = target->MigrateAtCorData(systemIdentifier, groupName);
					Assert::AreEqual(expected, actual);
				}
				
				Directory::SetCurrentDirectory(_currDir);
				expected = 2; 
				try
				{
					if(File::Exists(Directory::GetCurrentDirectory() + "\\system\\data\\scor.xyz"))
					{
						groupName = "Dr.Alok";
						actual = target->MigrateAtCorData(systemIdentifier, groupName);
					}
				}
				catch(Exception^ )
				{
					actual = 2;
				}
				Assert::AreEqual(expected, actual);

			}
			/// <summary>
			///A test for GroupRecordExits
			///</summary>
	public: [TestMethod]
			void GroupRecordExitsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int systemIdentifier = 0; // TODO: Initialize to an appropriate value
				String^  groupName = System::String::Empty; // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();

				systemIdentifier = 31256;
				groupName = "Dr6";
				expected = true;

				actual = target->GroupRecordExits(systemIdentifier, groupName);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
						/// <summary>
			///A test for GetPWVTrendData
			///</summary>
	public: [TestMethod]
			void GetPWVTrendDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int patientNumberInternal = 0; // TODO: Initialize to an appropriate value
				int groupIdentifier = 0; // TODO: Initialize to an appropriate value
				int systemIdentifier = 0; // TODO: Initialize to an appropriate value
				String^  studyDateTimeArrStr = System::String::Empty; // TODO: Initialize to an appropriate value
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

				// now connect to db
				target->SetConnection(serverName, sourceName);
				////preparing test data into database//////
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
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
					pwvmd->MeanPulseWaveVelocity = 4.4000;
					pwvmd->StandardDeviation = 3.300;
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
					String^ studyDateTimeArrStr = ( pwvmd->StudyDateTime) + ",";

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
					trendDataStruct->HeartRateArrStr = "";
					trendDataStruct->PulseWaveVelocityArrStr = "";
					trendDataStruct->StandardDeviationArrStr = "";
					trendDataStruct->IsStdDevValidArrStr = "";

					//Testing with double value
					studyDateTimeArrStr = studyDateTimeArrStr + "2011-01-31 17:46:01,";
					target->GetPWVTrendData(patientNumberInternal, groupIdentifier, systemIdentifier, studyDateTimeArrStr, trendDataStruct);
					Assert::AreEqual(trendDataStruct->HeartRateArrStr	,"150");
					Assert::AreEqual(trendDataStruct->PulseWaveVelocityArrStr	,"4.4");
					Assert::AreEqual(trendDataStruct->StandardDeviationArrStr	,"3.3");
					Assert::AreEqual(trendDataStruct->IsStdDevValidArrStr	,"1");

					//Clearing the structure
					trendDataStruct->HeartRateArrStr = "";
					trendDataStruct->PulseWaveVelocityArrStr = "";
					trendDataStruct->StandardDeviationArrStr = "";
					trendDataStruct->IsStdDevValidArrStr = "";

					//Testing with invalid value
					patientNumberInternal = 0;
					groupIdentifier = 3;
					systemIdentifier = 31256;
					studyDateTimeArrStr = "2010-12-15 14:23:47,2011-01-31 17:46:01,";
					target->GetPWVTrendData(patientNumberInternal, groupIdentifier, systemIdentifier, studyDateTimeArrStr, trendDataStruct);
					Assert::AreEqual(trendDataStruct->HeartRateArrStr	,"");
					Assert::AreEqual(trendDataStruct->PulseWaveVelocityArrStr	,"");
					Assert::AreEqual(trendDataStruct->StandardDeviationArrStr	,"");
					Assert::AreEqual(trendDataStruct->IsStdDevValidArrStr	,"");
					
					target->DeletePatientData(pd);
				}
				catch(Exception^)
				{
					target->DeletePatientData(pd);
					//exception occur if any assert statement fails - test failed 
					Assert::Fail();
				}
			}
			/// <summary>
			///A test for GetPWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void GetPWVMeasurementDetailsTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int patientNumberInternal = 0; // TODO: Initialize to an appropriate value
				int groupIdentifier = 0; // TODO: Initialize to an appropriate value
				int systemIdentifier = 0; // TODO: Initialize to an appropriate value
				DataSet^  expected = nullptr; // TODO: Initialize to an appropriate value
				DataSet^  actual;
				//smarajit
				target->SetConnection(serverName, sourceName);
				patientNumberInternal = 2;
				groupIdentifier = 3;
				systemIdentifier = 31256;
       			//smarajit
				actual = target->GetPWVMeasurementDetails(patientNumberInternal, groupIdentifier, systemIdentifier);
				int expectStr = patientNumberInternal;
				int actualStr = Convert::ToInt32(actual->Tables[0]->Rows[0]["PatientNumberInternal"]->ToString());
				Assert::AreEqual(expectStr, actualStr);
				//Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for GetPWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void GetPWVMeasurementDetailsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPWVMeasurementData^  md = nullptr; // TODO: Initialize to an appropriate value
				DataSet^  expected = nullptr; // TODO: Initialize to an appropriate value
				DataSet^  actual;
				//smarajit
				target->SetConnection(serverName, sourceName);
				CrxStructPWVMeasurementData^  md = gcnew CrxStructPWVMeasurementData();
				md->SystemIdentifier = 31256;
                md->GroupIdentifier = 3;
                md->PatientNumberInternal = 2;

				DataSet^ msrds = target->GetPWVMeasurementDetails(md->PatientNumberInternal,md->GroupIdentifier, md->SystemIdentifier);
				md->StudyDateTime	= Convert::ToDateTime(msrds->Tables[0]->Rows[0]["StudyDateTime"]);
				//String^ studyDateTimeArrStr = Convert::ToString( pwvmd->StudyDateTime) + ",";

				//md->StudyDateTime = Convert::ToDateTime("2010-12-14 14:14:05.000");
				
				//smarajit
				int expectStr = md->PatientNumberInternal;
				actual = target->GetPWVMeasurementDetails(md);
				
				int actualStr = md->PatientNumberInternal;
				Assert::AreEqual(expectStr, actualStr);
				//Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for GetPatientDemographicRecords
			///</summary>
	public: [TestMethod]
			void GetPatientDemographicRecordsTest1()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				DataSet^  expected = nullptr; // TODO: Initialize to an appropriate value
				DataSet^  actual;
				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				actual = target->GetPatientDemographicRecords();
				
				String^ ExpectedStr = "P03148";	
				String^ actualStr = nullptr;
				
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

				//Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for GetPatientDemographicRecords
			///</summary>
	public: [TestMethod]
			void GetPatientDemographicRecordsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int patientNumberInternal = 0; // TODO: Initialize to an appropriate value
				int systemIdentifier = 0; // TODO: Initialize to an appropriate value
				int groupIdentifier = 0; // TODO: Initialize to an appropriate value
				DataSet^  expected = nullptr; // TODO: Initialize to an appropriate value
				DataSet^  actual;
				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				systemIdentifier = 31256;
				patientNumberInternal = 12;
				groupIdentifier = 9;

				actual = target->GetPatientDemographicRecords(patientNumberInternal, systemIdentifier, groupIdentifier);

				String^ actualStr = actual->Tables[0]->Rows[0]["PatientIDExternalReference"]->ToString();
				String^ ExpectedStr = "P03148";				
				Assert::AreEqual(ExpectedStr, actualStr);

				//actual = target->GetPatientDemographicRecords(patientNumberInternal, systemIdentifier, groupIdentifier);
				//Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for GetGroupLists
			///</summary>
	public: [TestMethod]
			void GetGroupListsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				DataSet^  expected = nullptr; // TODO: Initialize to an appropriate value
				DataSet^  actual;
				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				actual = target->GetGroupLists();

				String^ ExpectedStr = "Dr6";	
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
				//Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DeletePWVMeasurementDetails
			///</summary>
	public: [TestMethod]
			void DeletePWVMeasurementDetailsTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				CrxStructPWVMeasurementData^  md = nullptr; // TODO: Initialize to an appropriate value
				String^  studyDateTimeArrStr = System::String::Empty; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				
				///////////////////
				//called the database connection to connect database
				//input parameters to call method
				
				target->SetConnection(serverName, sourceName);
				////preparing test data into database//////
				CrxStructPatientDemographicData^ pd = gcnew CrxStructPatientDemographicData();
				CrxStructPWVMeasurementData ^ pwvmd = gcnew CrxStructPWVMeasurementData ();
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
					pwvmd->MeanPulseWaveVelocity = 4.4000;
					pwvmd->StandardDeviation = 3.300;
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
				///////////////////
			}
			/// <summary>
			///A test for DeletePatientData
			///</summary>
	public: [TestMethod]
			void DeletePatientDataTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//CrxStructPatientDemographicData^  pd = nullptr; // TODO: Initialize to an appropriate value
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				//Smarajit
				//called the database connection to connect database
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				CrxStructPatientDemographicData^  pd = gcnew CrxStructPatientDemographicData();
				
				pd->SystemIdentifier = 31256;
				pd->PatientNumberInternal = 52;			
				pd->GroupIdentifier = 18;
               
				expected = 0;

				actual = target->DeletePatientData(pd);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DatabaseRestore
			///</summary>
	public: [TestMethod]
			void DatabaseRestoreTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  FilePath = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  FilePath = "\\\\MUM-9638\\Atcor_Backup\\Test_For120110105.BAK";
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				//input parameters to call method
				target->SetConnection(serverName, sourceName);

				actual = target->DatabaseRestore(FilePath);
				Assert::AreEqual(expected, actual);

				FilePath = "\\\\MUM-9638\\Atcor_2009\\Test_For120110105.BAK";
				//expected = 0; // TODO: Initialize to an appropriate value
				//int actual;
				//input parameters to call method
				try
				{
					actual = target->DatabaseRestore(FilePath);
				}
				catch(Exception^)
				{
					expected =0;
				}
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DatabaseBackup
			///</summary>
	public: [TestMethod]
			void DatabaseBackupTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  FilePath = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  FilePath = "\\\\MUM-9638\\Atcor_Backup\\Test_For120110105.BAK";
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				//input parameters to call method
				target->SetConnection(serverName, sourceName);
				try
				{

					actual = target->DatabaseBackup(FilePath);
				}
				catch(Exception^ e)
				{
					String^ check = e->Message;
				}
				Assert::AreEqual(expected, actual);

				//String^  FilePath = "\\\\MUM-9638\\Atcor_2008\\Test_For120110105.BAK";
				//int expected = 0; // TODO: Initialize to an appropriate value
				//int actual;
				//input parameters to call method
				FilePath = "\\\\MUM-9638\\Atcor_2009\\Test_For120110105.BAK";
				try
				{
					actual = target->DatabaseBackup(FilePath);
				}
				catch(Exception^)
				{
					expected =0;
				}
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CommonShortArrtoByteArr
			///</summary>
	public: [TestMethod]
			void CommonShortArrtoByteArrTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int len = 0; // TODO: Initialize to an appropriate value
				cli::array< unsigned short >^  shrtarr = nullptr; // TODO: Initialize to an appropriate value
				//cli::array< unsigned char >^  expected = nullptr; // TODO: Initialize to an appropriate value
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
				//Assert::AreSame(expected,actual);
				//Assert::AreNotEqual(expected,actual);
				//smarajit
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CommonFloatArrtoByteArr
			///</summary>
	public: [TestMethod]
			void CommonFloatArrtoByteArrTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int len = 0; // TODO: Initialize to an appropriate value
				cli::array< float >^  fltarr = nullptr; // TODO: Initialize to an appropriate value
				//cli::array< unsigned char >^  expected = nullptr; // TODO: Initialize to an appropriate value
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

				//Assert::AreSame(expected,actual);
				//Assert::AreNotEqual(expected,actual);

				//smarajit
				//actual = target->CommonFloatArrtoByteArr(len, fltarr);
				//Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CommonByteArrtoShortArr
			///</summary>
	public: [TestMethod]
			void CommonByteArrtoShortArrTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int len = 0; // TODO: Initialize to an appropriate value
				cli::array< unsigned char >^  bytearr = nullptr; // TODO: Initialize to an appropriate value
				cli::array< unsigned short >^  expected = nullptr; // TODO: Initialize to an appropriate value
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
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CommonByteArrtoFloatArr
			///</summary>
	public: [TestMethod]
			void CommonByteArrtoFloatArrTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				int len = 0; // TODO: Initialize to an appropriate value
				cli::array< unsigned char >^  bytearr = nullptr; // TODO: Initialize to an appropriate value
				cli::array< float >^  expected = nullptr; // TODO: Initialize to an appropriate value
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
				
				

				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CheckConnection
			///</summary>
	public: [TestMethod]
			void CheckConnectionTest()
			{
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  serverName = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  sourceName = System::String::Empty; // TODO: Initialize to an appropriate value
				int expected = 1; // TODO: Initialize to an appropriate value
				int actual;
				String^ serverNameTest = "MUM-9696\\SQLEXPRESS";
				String^  sourceNameTest = "SQLCLIENT";
				try
				{
					actual = target->CheckConnection(serverNameTest, sourceNameTest);
				}
				catch(Exception^)
				{
					
				}
				//actual = target->CheckConnection(serverName, sourceName);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CrxDBManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxDBManagerConstructorTest1()
			{
				CrxDBManager^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				CrxDBManager_Accessor^  target = (gcnew CrxDBManager_Accessor(unnamed));
				Assert::IsNotNull(target);
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
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
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestCrx {
    
}
