
#include "StdAfx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalConfigurationAndUsagesTest;
    
    
    /// <summary>
///This is a test class for DalConfigurationAndUsagesTest and is intended
///to contain all DalConfigurationAndUsagesTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalConfigurationAndUsagesTest
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
			///A test for TestDate
			///</summary>
	public: [TestMethod]
			void TestDateTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				DateTime expected = DateTime(); // TODO: Initialize to an appropriate value
				DateTime actual;
				target->TestDate = expected;
				actual = target->TestDate;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SystemConfigurationId
			///</summary>
	public: [TestMethod]
			void SystemConfigurationIdTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				unsigned short expected = 0; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->SystemConfigurationId = expected;
				actual = target->SystemConfigurationId;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SystemConfigurationChangeDate
			///</summary>
	public: [TestMethod]
			void SystemConfigurationChangeDateTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				DateTime expected = DateTime(); // TODO: Initialize to an appropriate value
				DateTime actual;
				target->SystemConfigurationChangeDate = expected;
				actual = target->SystemConfigurationChangeDate;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SerialNumberSuntechPcb
			///</summary>
	public: [TestMethod]
			void SerialNumberSuntechPcbTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				target->SerialNumberSuntechPcb = expected;
				actual = target->SerialNumberSuntechPcb;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SerialNumberMpb
			///</summary>
	public: [TestMethod]
			void SerialNumberMpbTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual ;
				//target->SerialNumberMpb = expected;
				try
				{
					actual = target->SerialNumberMpb;
				}
				catch(Exception^ ex)
				{
					Assert::Fail;;
				}
				Assert::IsNotNull(actual);
				//Assert::AreEqual(expected, actual);
				
			}
			/// <summary>
			///A test for SerialNumberEm4
			///</summary>
	public: [TestMethod]
			void SerialNumberEm4Test()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				target->SerialNumberEm4 = expected;
				actual = target->SerialNumberEm4;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for SafetyFirmwareVersionSuntech
			///</summary>
	public: [TestMethod]
			void SafetyFirmwareVersionSuntechTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				target->SafetyFirmwareVersionSuntech = expected;
				actual = target->SafetyFirmwareVersionSuntech;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ProcessorFirmwareVersionMpb
			///</summary>
	public: [TestMethod]
			void ProcessorFirmwareVersionMpbTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				target->ProcessorFirmwareVersionMpb = expected;
				actual = target->ProcessorFirmwareVersionMpb;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for PldSafetyFirmwareVersionMpb
			///</summary>
	public: [TestMethod]
			void PldSafetyFirmwareVersionMpbTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				target->PldSafetyFirmwareVersionMpb = expected;
				actual = target->PldSafetyFirmwareVersionMpb;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for NumberofPWVmeasurements
			///</summary>
	public: [TestMethod]
			void NumberofPWVmeasurementsTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				unsigned int expected = 0; // TODO: Initialize to an appropriate value
				unsigned int actual;
				target->NumberofPWVmeasurements = expected;
				actual = target->NumberofPWVmeasurements;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for NumberofPWAtonometermeasurements
			///</summary>
	public: [TestMethod]
			void NumberofPWAtonometermeasurementsTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				unsigned int expected = 0; // TODO: Initialize to an appropriate value
				unsigned int actual;
				target->NumberofPWAtonometermeasurements = expected;
				actual = target->NumberofPWAtonometermeasurements;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for NumberofPWAcuffmeasurements
			///</summary>
	public: [TestMethod]
			void NumberofPWAcuffmeasurementsTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				unsigned int expected = 0; // TODO: Initialize to an appropriate value
				unsigned int actual;
				target->NumberofPWAcuffmeasurements = expected;
				actual = target->NumberofPWAcuffmeasurements;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for NumberOfNibpMeasurements
			///</summary>
	public: [TestMethod]
			void NumberOfNibpMeasurementsTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				unsigned int expected = 0; // TODO: Initialize to an appropriate value
				unsigned int actual;
				target->NumberOfNibpMeasurements = expected;
				actual = target->NumberOfNibpMeasurements;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				DalConfigurationAndUsages^  actual;
				actual = DalConfigurationAndUsages::Instance;
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for HWConfigurationMpb
			///</summary>
	public: [TestMethod]
			void HWConfigurationMpbTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				unsigned short expected = 0; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->HWConfigurationMpb = expected;
				actual = target->HWConfigurationMpb;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CalibrationDateSuntech
			///</summary>
	public: [TestMethod]
			void CalibrationDateSuntechTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				DateTime expected = DateTime(); // TODO: Initialize to an appropriate value
				DateTime actual;
				target->CalibrationDateSuntech = expected;
				actual = target->CalibrationDateSuntech;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CalibrationDateMpb
			///</summary>
	public: [TestMethod]
			void CalibrationDateMpbTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				DateTime expected = DateTime(); // TODO: Initialize to an appropriate value
				DateTime actual;
				target->CalibrationDateMpb = expected;
				actual = target->CalibrationDateMpb;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for BPFirmwareVersionSuntech
			///</summary>
	public: [TestMethod]
			void BPFirmwareVersionSuntechTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				target->BPFirmwareVersionSuntech = expected;
				actual = target->BPFirmwareVersionSuntech;
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor()); // TODO: Initialize to an appropriate value
				//DalConfigurationAndUsages unnamed; // TODO: Initialize to an appropriate value
				DalConfigurationAndUsages^  expected = nullptr; // TODO: Initialize to an appropriate value
				DalConfigurationAndUsages^  actual;
				//actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DalConfigurationAndUsages Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalConfigurationAndUsagesConstructorTest1()
			{
				DalConfigurationAndUsages^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor(unnamed));
				Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for DalConfigurationAndUsages Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalConfigurationAndUsagesConstructorTest()
			{
				DalConfigurationAndUsages_Accessor^  target = (gcnew DalConfigurationAndUsages_Accessor());
				Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestDal {
    
}
