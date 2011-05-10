﻿
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalDeviceConfigUsageStructTest;
    
    
    /// <summary>
///This is a test class for DalDeviceConfigUsageStructTest and is intended
///to contain all DalDeviceConfigUsageStructTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalDeviceConfigUsageStructTest
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
			///A test for ModuleType
			///</summary>
	public: [TestMethod]
			void ModuleTypeTest()
			{
				DalDeviceConfigUsageStruct^  target = (gcnew DalDeviceConfigUsageStruct()); 
				String^  expected = "Test Module Type";  //assigning a dummy value
				String^  actual;
				target->ModuleType = expected;
				actual = target->ModuleType;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ModuleSerialNumber
			///</summary>
	public: [TestMethod]
			void ModuleSerialNumberTest()
			{
				DalDeviceConfigUsageStruct^  target = (gcnew DalDeviceConfigUsageStruct()); 
				String^  expected = L"Sim - 1234567890"; //assigning a dummy value 
				String^  actual;
				target->ModuleSerialNumber = expected;
				actual = target->ModuleSerialNumber;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ModuleMainFWVersion
			///</summary>
	public: [TestMethod]
			void ModuleMainFWVersionTest()
			{
				DalDeviceConfigUsageStruct^  target = (gcnew DalDeviceConfigUsageStruct()); 
				String^  expected =  L"Sim - 0.1"; //assigning a dummy value.
				String^  actual;
				target->ModuleMainFWVersion = expected;
				actual = target->ModuleMainFWVersion;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ModuleConfigId
			///</summary>
	public: [TestMethod]
			void ModuleConfigIdTest()
			{
				DalDeviceConfigUsageStruct^  target = (gcnew DalDeviceConfigUsageStruct()); 
				unsigned short expected = 0; 
				unsigned short actual;
				target->ModuleConfigId = expected;
				actual = target->ModuleConfigId;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ModuleConfigDate
			///</summary>
	public: [TestMethod]
			void ModuleConfigDateTest()
			{
				DalDeviceConfigUsageStruct^  target = (gcnew DalDeviceConfigUsageStruct()); 
				DateTime expected = DateTime(); 
				DateTime actual;
				target->ModuleConfigDate = expected;
				actual = target->ModuleConfigDate;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ModuleCalibrationDate
			///</summary>
	public: [TestMethod]
			void ModuleCalibrationDateTest()
			{
				DalDeviceConfigUsageStruct^  target = (gcnew DalDeviceConfigUsageStruct()); 
				DateTime expected = DateTime(); 
				DateTime actual;
				target->ModuleCalibrationDate = expected;
				actual = target->ModuleCalibrationDate;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for DalDeviceConfigUsageStruct Constructor
			///</summary>
	public: [TestMethod]
			void DalDeviceConfigUsageStructConstructorTest()
			{
				DalDeviceConfigUsageStruct^  target = (gcnew DalDeviceConfigUsageStruct());
				Assert::IsNotNull(target);
			}
	};
}
namespace TestDal {
    
}
