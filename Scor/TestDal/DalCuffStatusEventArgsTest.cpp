
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalCuffStatusEventArgsTest;
    
    
    /// <summary>
///This is a test class for DalCuffStatusEventArgsTest and is intended
///to contain all DalCuffStatusEventArgsTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalCuffStatusEventArgsTest
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
				DalCuffStateFlags data = DalCuffStateFlags::CUFF_STATE_DISCONNECTED ; 
				DalCuffStatusEventArgs^  target = (gcnew DalCuffStatusEventArgs(data)); 
				DalCuffStateFlags expected = DalCuffStateFlags::CUFF_STATE_DISCONNECTED; 
				DalCuffStateFlags actual;
				target->CuffStateFlag = expected;
				actual = target->CuffStateFlag;
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for DalCuffStatusEventArgs Constructor
			///</summary>
	public: [TestMethod]
			void DalCuffStatusEventArgsConstructorTest()
			{
				DalCuffStateFlags data = DalCuffStateFlags::CUFF_STATE_INFLATING; 
				DalCuffStatusEventArgs^  target = (gcnew DalCuffStatusEventArgs(data));
				Assert::IsNotNull(target);
			}
	};
}
namespace TestDal {
    
}
