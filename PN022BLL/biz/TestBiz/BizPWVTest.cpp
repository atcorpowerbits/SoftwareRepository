
#include "StdAfx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace Biz;
using namespace CrossCutting;
namespace TestBiz {
    using namespace System;
    ref class BizPWVTest;
    
#define USHRT_MAX 0xffff
    
    /// <summary>
///This is a test class for BizPWVTest and is intended
///to contain all BizPWVTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizPWVTest
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
			///A test for PWVDistance
			///</summary>
	public: [TestMethod]
			void PWVDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				unsigned short expected = USHRT_MAX; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->myPWVDirectDistance->distance = expected;
				actual = target->myPWVDirectDistance->distance;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Femoral2CuffDistance
			///</summary>
	public: [TestMethod]
			void Femoral2CuffDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				unsigned short expected = USHRT_MAX; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->myFemoral2CuffDistance->distance = expected;
				actual = target->myFemoral2CuffDistance->distance;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for CuffDistance
			///</summary>
	public: [TestMethod]
			void CuffDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				unsigned short expected = USHRT_MAX; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->myCuffDistance->distance = expected;
				actual = target->myCuffDistance->distance;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for CarotidDistance
			///</summary>
	public: [TestMethod]
			void CarotidDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				unsigned short expected = USHRT_MAX; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->myCarotidDistance->distance = expected;
				actual = target->myCarotidDistance->distance;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ValidatePWVDistance
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\ValidatePWVDistance.csv", L"ValidatePWVDistance#csv", DataAccessMethod::Sequential),
				TestMethod]
			void ValidatePWVDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				bool expected = Convert::ToBoolean(testContextInstance->DataRow["Expected"]); // TODO: Initialize to an appropriate value
				bool actual;
				CrxConfigFacade::Instance()->PWVSubtractingMethod = Convert::ToBoolean(testContextInstance->DataRow["Method"]);
				target->myCarotidDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Carotid"]);
				target->myCuffDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["Cuff"]);
				target->myPWVDirectDistance->distance = Convert::ToUInt16(testContextInstance->DataRow["PWVDist"]);
				actual = target->ValidatePWVDistance();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ValidateFemoral2CuffDistance
			///</summary>
	public: [TestMethod]
			void ValidateFemoral2CuffDistanceTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->myFemoral2CuffDistance->Validate();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Validate
			///</summary>
	public: [TestMethod]
			void ValidateTest()
			{
				BizPWV^  target = (gcnew BizPWV()); // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->Validate();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for BizPWV Constructor
			///</summary>
	public: [TestMethod]
			void BizPWVConstructorTest()
			{
				BizPWV^  target = (gcnew BizPWV());
				Assert::AreNotEqual(nullptr, target);
			}
	};
}
namespace TestBiz {
    
}
