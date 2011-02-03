
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalCountdownTimerEventArgsTest;
    
    
    /// <summary>
///This is a test class for DalCountdownTimerEventArgsTest and is intended
///to contain all DalCountdownTimerEventArgsTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalCountdownTimerEventArgsTest
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
			///A test for data
			///</summary>
	public: [TestMethod]
			void dataTest()
			{
				unsigned short data = 0; // TODO: Initialize to an appropriate value
				DalCountdownTimerEventArgs^  target = (gcnew DalCountdownTimerEventArgs(data)); // TODO: Initialize to an appropriate value
				unsigned short expected = 0; // TODO: Initialize to an appropriate value
				unsigned short actual;
				target->data = expected;
				actual = target->data;
				Assert::AreEqual(expected, actual);
			//	Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DalCountdownTimerEventArgs Constructor
			///</summary>
	public: [TestMethod]
			void DalCountdownTimerEventArgsConstructorTest()
			{
				unsigned short data = 99; // TODO: Initialize to an appropriate value
				DalCountdownTimerEventArgs^  target = (gcnew DalCountdownTimerEventArgs(data));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
				Assert::AreEqual(data, target->data);

			}
	};
}
namespace TestDal {
    
}
