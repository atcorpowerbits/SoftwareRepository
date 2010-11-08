
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::BusinessLogic;
namespace TestBiz {
    using namespace System;
    ref class BizPatientTest;
    
    
    /// <summary>
///This is a test class for BizPatientTest and is intended
///to contain all BizPatientTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizPatientTest
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
			///A test for Initialise
			///</summary>
	public: [TestMethod]
			void BizPatientInitialiseTest()
			{
				BizPatient^  target = BizPatient::Instance();
				target->Initialise();
				Assert::AreEqual((String^) "", target->systemId);
				Assert::AreEqual((unsigned int) 0, target->patientNumber);
				Assert::AreEqual((String^) "", target->groupStudyId);
				Assert::AreEqual((String^) "", target->patientId);
				Assert::AreEqual((String^) "", target->lastName);
				Assert::AreEqual((String^) "", target->firstName);
				Assert::AreEqual((String^) "", target->gender);
				Assert::AreEqual((DateTime) BizConstants::PATIENT_INITIAL_DATE, target->dateOfBirth);
			}
	};
}
namespace TestBiz {
    
}
