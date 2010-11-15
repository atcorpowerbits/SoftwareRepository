
#include "StdAfx.h"
#include <biz.h>
using namespace BIZ_NAMESPACE;
using namespace CRX_CONFIG_NAMESPACE;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
    ref class BizHeightAndWeightTest;
    
    
    /// <summary>
///This is a test class for BizHeightAndWeightTest and is intended
///to contain all BizHeightAndWeightTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizHeightAndWeightTest
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
			///A test for ValidateAndCalculate
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizHeightAndWeight.csv", L"BizHeightAndWeight#csv", DataAccessMethod::Sequential),
				TestMethod]
			void ValidateAndCalculateTest()
			{
				BizHeightAndWeight^  target = (gcnew BizHeightAndWeight()); // TODO: Initialize to an appropriate value
				CrxConfigManager::Instance->GeneralSettings->HeightandWeightUnit = Convert::ToInt32(testContextInstance->DataRow["HeightAndWeightUnit"]);
				target->heightInCentimetres = Convert::ToUInt16(testContextInstance->DataRow["HeightInCentimetres"]);
				target->heightInInches = Convert::ToUInt16(testContextInstance->DataRow["HeightInInches"]);
				target->weightInKilograms = Convert::ToUInt16(testContextInstance->DataRow["WeightInKilograms"]);
				target->weightInPounds = Convert::ToUInt16(testContextInstance->DataRow["WeightInPounds"]);
				unsigned short heightInCentimetresExpected = Convert::ToUInt16(testContextInstance->DataRow[L"HeightInCentimetresExpected"]);
				unsigned short heightInInchesExpected = Convert::ToUInt16(testContextInstance->DataRow[L"HeightInInchesExpected"]);
				unsigned short weightInKilogramsExpected = Convert::ToUInt16(testContextInstance->DataRow[L"WeightInKilogramsExpected"]);
				unsigned short weightInPoundsExpected = Convert::ToUInt16(testContextInstance->DataRow[L"WeightInPoundsExpected"]);
				float bodyMassIndex = Convert::ToSingle(testContextInstance->DataRow[L"BodyMassIndex"]);
				bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
				bool actual;
				actual = target->ValidateAndCalculate();
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(heightInCentimetresExpected, target->heightInCentimetres);
				Assert::AreEqual(heightInInchesExpected, target->heightInInches);
				Assert::AreEqual(weightInKilogramsExpected, target->weightInKilograms);
				Assert::AreEqual(weightInPoundsExpected, target->weightInPounds);
				Assert::AreEqual(bodyMassIndex, target->bodyMassIndex);
			}
	};
}
namespace TestBiz {
    
}
