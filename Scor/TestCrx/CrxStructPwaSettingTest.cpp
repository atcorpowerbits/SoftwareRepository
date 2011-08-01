
#include "StdAfx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Configuration;
namespace TestCrx {
    using namespace System;
    ref class CrxStructPwaSettingTest;
    
    
    /// <summary>
///This is a test class for CrxStructPwaSettingTest and is intended
///to contain all CrxStructPwaSettingTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxStructPwaSettingTest
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
			///A test for CrxStructPwaSetting Constructor
			///</summary>
	public: [TestMethod]
			void CrxStructPwaSettingConstructorTest()
			{
				CrxStructPwaSetting^  target = (gcnew CrxStructPwaSetting());
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for CrxStructPwaSetting Constructor
			///</summary>
	public: [TestMethod]
			void CrxStructPwaSettingConstructorTest1()
			{
				CrxStructPwaSetting^  target = (gcnew CrxStructPwaSetting());
				Assert::IsNotNull(target);

				Assert::AreEqual(target->CaptureTime,5);
				Assert::IsTrue(target->AugmentationIndex);
				Assert::IsFalse(target->AugmentationIndexAtHR75,"False");
				Assert::AreEqual(target->CaptureInput,"Pressure Cuff");
				Assert::AreEqual(target->GuidanceBars, true);
					

			}
	};
}
namespace TestCrx {
    
}
