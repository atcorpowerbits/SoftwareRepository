
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalPwvDataStructTest;
    
    
    /// <summary>
///This is a test class for DalPwvDataStructTest and is intended
///to contain all DalPwvDataStructTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalPwvDataStructTest
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
			///A test for DalPwvDataStruct Constructor
			///</summary>
	public: [TestMethod]
			void DalPwvDataStructConstructorTest1()
			{
				DalPwvDataStruct valueParameter; // TODO: Initialize to an appropriate value
				DalPwvDataStruct valueParameterExpected; // TODO: Initialize to an appropriate value
				
				
				// TODO: valueParameter and valueParameterExpected must be manually verified for equality.
				valueParameter.countdownTimer = 100;
				valueParameter.cuffPressure = 100;
				valueParameter.cuffPulseData = 100;
				valueParameter.tonometerData = 100;

				valueParameterExpected.countdownTimer = 100;
				valueParameterExpected.cuffPressure = 100;
				valueParameterExpected.cuffPulseData = 100;
				valueParameterExpected.tonometerData = 100;

				DalPwvDataStruct^  target = (gcnew DalPwvDataStruct(valueParameter));
				
				//Assert::AreEqual(valueParameterExpected, target);
				Assert::AreEqual(valueParameterExpected.tonometerData , target->tonometerData);
			}
			/// <summary>
			///A test for DalPwvDataStruct Constructor
			///</summary>
	public: [TestMethod]
			void DalPwvDataStructConstructorTest()
			{
				DalPwvDataStruct^  target = (gcnew DalPwvDataStruct());
				short expectedValue = -1;

				Assert::AreEqual(target->tonometerData, expectedValue);
				Assert::AreEqual(target->cuffPulseData, expectedValue);
				Assert::AreEqual(target->cuffPressure, expectedValue);
				Assert::AreEqual(target->countdownTimer, expectedValue);
 			}
	};
}
namespace TestDal {
    
}
