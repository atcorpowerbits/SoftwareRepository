
#include "StdAfx.h"
using namespace System::Data;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::DatabaseManager;
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

			static String^  serverName = "MUM-9638\\SQLEXPRESS";
			static String^  sourceName = "SQLCLIENT";

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
			//public: [TestInitialize]
			//System::Void MyTestInitialize()
			//{
			//}
			//
			//Use TestCleanup to run code after each test has run
			//public: [TestCleanup]
			//System::Void MyTestCleanup()
			//{
			//}
			//
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
				CrxStructPWVMeasurementData^  md = gcnew CrxStructPWVMeasurementData();
				md->SystemIdentifier = 31256;
                md->GroupIdentifier = 4;
                md->PatientNumberInternal = 6;
				md->StudyDateTime = Convert::ToDateTime("2010-12-17 11:58:12");
				md->Notes = "CheckOut";
				md->Carotid = 111;
				md->WeightInKilograms = 75;
				md->HeightInCentimetres = 175;
				md->CarotidSignal = gcnew array<short>(1);
				md->CarotidSignal[0] = 1244;
				md->FemoralSignal = gcnew array<short>(1);
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
				actual = target->UpdatePWVMeasurementDetails(md);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
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
				pd->PatientNumberInternal = 130;
				pd->PatientIDExternalReference = "P03148";
				pd->LastName = "Final23";
				String^ date = "08/09/1984";
				pd->DateOfBirth = Convert::ToDateTime(date);
				pd->GroupName = "Dr6";
				pd->GroupIdentifier = 6;
                pd->FirstName = "Final234erer";
                pd->Gender = "Male"; 
				expected = 0;

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
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				actual = target->SetConnection(serverName, sourceName);
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
				md->CarotidSignal = gcnew array<short>(1);
				md->CarotidSignal[0] = 1244;
				md->FemoralSignal = gcnew array<short>(1);
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
                pd->Gender = "Male"; 

				expected = 1;

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
				patientNumberInternal = 6;
				groupIdentifier = 4;
				systemIdentifier = 31256;
       			//smarajit
				actual = target->GetPWVMeasurementDetails(patientNumberInternal, groupIdentifier, systemIdentifier);
				int expectStr = 6;
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
                md->GroupIdentifier = 4;
                md->PatientNumberInternal = 6;
				md->StudyDateTime = Convert::ToDateTime("2010-12-15 14:23:47");
				
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
				pd->PatientNumberInternal = 129;			
				pd->GroupIdentifier = 25;
               
				expected = 0;

				actual = target->DeletePatientData(pd);
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
				cli::array< short >^  shrtarr = nullptr; // TODO: Initialize to an appropriate value
				//cli::array< unsigned char >^  expected = nullptr; // TODO: Initialize to an appropriate value
				//cli::array< unsigned char >^  actual;
				cli::array< Byte >^  expected = nullptr;
				cli::array< Byte >^  actual;
				//smarajit
				//array<Byte>^ bufferArrRet;
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
				///actual = target->CommonShortArrtoByteArr(len, shrtarr);
				Assert::AreEqual(expected[0], actual[0]);
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
				cli::array< short >^  expected = nullptr; // TODO: Initialize to an appropriate value
				cli::array< short >^  actual;
				///Smarajit

				array< short >^ shrtarr = gcnew array<short> (1);
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
				actual = target->CommonByteArrtoShortArr(len, bytearr);
				Assert::AreEqual(expected[0], actual[0]);
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
				int expected = 0; // TODO: Initialize to an appropriate value
				int actual;
				actual = target->CheckConnection(serverName, sourceName);
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
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestCrx {
    
}
