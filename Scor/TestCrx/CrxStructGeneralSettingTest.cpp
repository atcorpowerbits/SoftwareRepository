
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Configuration;
namespace TestCrx {
    using namespace System;
    ref class CrxStructGeneralSettingTest;
    
    
    /// <summary>
///This is a test class for CrxStructGeneralSettingTest and is intended
///to contain all CrxStructGeneralSettingTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxStructGeneralSettingTest
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
			///A test for CrxStructGeneralSetting Constructor
			///</summary>
	public: [TestMethod]
			void CrxStructGeneralSettingConstructorTest()
			{
				CrxStructGeneralSetting^  target = (gcnew CrxStructGeneralSetting());
				Assert::IsNotNull(target);

				Assert::AreEqual(target->PatientPrivacy,false);
				Assert::AreEqual(target->HeightandWeightUnit, 0);
				Assert::AreEqual(target->BloodPressureEntryOptions, 0);
				Assert::IsNull(target->CommsPort);
				Assert::IsNull(target->ReportTitle);
				Assert::IsNull(target->ReportLogoPath);
				Assert::IsNull(target->ServerName);
				Assert::IsNull(target->SourceData);
				Assert::IsNull(target->CultureInfo);
				Assert::IsNull(target->MachineName);
				Assert::IsNull(target->StartupMode);
				Assert::IsNull(target->StartupScreen);
				Assert::IsNull(target->EnvironmentSettings);
				Assert::IsNull(target->PrinterName);
			}
	};
}
namespace TestCrx {
    
}
