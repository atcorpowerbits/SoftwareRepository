
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalCuffStatusEventArgs_ORITest;
    
    
    /// <summary>
///This is a test class for DalCuffStatusEventArgs_ORITest and is intended
///to contain all DalCuffStatusEventArgs_ORITest Unit Tests
///</summary>
	[TestClass]
	public ref class DalCuffStatusEventArgs_ORITest
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
			///A test for CuffStateFlag
			///</summary>
	public: [TestMethod]
			void CuffStateFlagTest()
			{
				DalCuffStateFlags cuffStateFlag = DalCuffStateFlags(); // TODO: Initialize to an appropriate value
				cuffStateFlag = DalCuffStateFlags::CUFF_STATE_INFLATED ;
				long countDownTimerValue = 999; // TODO: Initialize to an appropriate value
				long cuffPressure = 999; // TODO: Initialize to an appropriate value
				DalCuffStatusEventArgs_ORI^  target = (gcnew DalCuffStatusEventArgs_ORI(cuffStateFlag)); // TODO: Initialize to an appropriate value
				DalCuffStateFlags expected = DalCuffStateFlags(); // TODO: Initialize to an appropriate value
				DalCuffStateFlags actual;
				target->CuffStateFlag = expected;
				actual = target->CuffStateFlag;
				Assert::AreEqual(expected, actual);
			//	Assert::Inconclusive(L"Verify the correctness of this test method.");
			}

			//Deepak: This test is invalid after the DalCuffStatusEventArgs_ORI has been changed to single parameter
	//		/// <summary>
	//		///A test for cuffPressure
	//		///</summary>
	//public: [TestMethod]
	//		void cuffPressureTest()
	//		{
	//			DalCuffStateFlags cuffStateFlag = DalCuffStateFlags();
	//			cuffStateFlag = DalCuffStateFlags::CUFF_STATE_INFLATED; // TODO: Initialize to an appropriate value
	//			long countDownTimerValue = 999; // TODO: Initialize to an appropriate value
	//			long cuffPressure = 999; // TODO: Initialize to an appropriate value
	//			DalCuffStatusEventArgs_ORI^  target = (gcnew DalCuffStatusEventArgs_ORI(cuffStateFlag)); // TODO: Initialize to an appropriate value
	//			long expected = 0; // TODO: Initialize to an appropriate value
	//			long actual;
	//			//target->cuffPressure = expected;
	//			//actual = target->cuffPressure;
	//			Assert::AreEqual(expected, actual);
	//			
	//		}

			//Deepak: This test is invalid after the DalCuffStatusEventArgs_ORI has been changed to single parameter
	//		/// <summary>
	//		///A test for countDownTimerValue
	//		///</summary>
	//public: [TestMethod]
	//		void countDownTimerValueTest()
	//		{
	//			DalCuffStateFlags cuffStateFlag = DalCuffStateFlags(); // TODO: Initialize to an appropriate value
	//			long countDownTimerValue = 0; // TODO: Initialize to an appropriate value
	//			long cuffPressure = 0; // TODO: Initialize to an appropriate value
	//			DalCuffStatusEventArgs_ORI^  target = (gcnew DalCuffStatusEventArgs_ORI(cuffStateFlag)); // TODO: Initialize to an appropriate value
	//			long expected = 0; // TODO: Initialize to an appropriate value
	//			long actual;
	//			//target->countDownTimerValue = expected;
	//			actual = target->countDownTimerValue;
	//			Assert::AreEqual(expected, actual);
	//			//Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
			/// <summary>
			///A test for DalCuffStatusEventArgs_ORI Constructor
			///</summary>
	public: [TestMethod]
			void DalCuffStatusEventArgs_ORIConstructorTest()
			{
				DalCuffStateFlags cuffStateFlag = DalCuffStateFlags(); // TODO: Initialize to an appropriate value
				cuffStateFlag = DalCuffStateFlags::CUFF_STATE_UNKNOWN;
				long countDownTimerValue = 777; // TODO: Initialize to an appropriate value
				long cuffPressure = 777; // TODO: Initialize to an appropriate value
				DalCuffStatusEventArgs_ORI^  target = (gcnew DalCuffStatusEventArgs_ORI(cuffStateFlag));
				Assert::AreEqual(target->CuffStateFlag , DalCuffStateFlags::CUFF_STATE_UNKNOWN); 
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestDal {
    
}
