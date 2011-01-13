
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting;
namespace TestCrx {
    using namespace System;
    ref class CommsPortEventArgsTest;
    
    
    /// <summary>
///This is a test class for CommsPortEventArgsTest and is intended
///to contain all CommsPortEventArgsTest Unit Tests
///</summary>
	[TestClass]
	public ref class CommsPortEventArgsTest
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
			///A test for commsPortSetting
			///</summary>
	public: [TestMethod]
			void commsPortSettingTest()
			{
				String^  commsPortSetting = System::String::Empty; // TODO: Initialize to an appropriate value
				CommsPortEventArgs^  target = (gcnew CommsPortEventArgs(commsPortSetting)); // TODO: Initialize to an appropriate value
				String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  actual;
				target->commsPortSetting = expected;
				actual = target->commsPortSetting;
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CommsPortEventArgs Constructor
			///</summary>
	public: [TestMethod]
			void CommsPortEventArgsConstructorTest()
			{
				String^  commsPortSetting = System::String::Empty; // TODO: Initialize to an appropriate value
				CommsPortEventArgs^  target = (gcnew CommsPortEventArgs(commsPortSetting));
				Assert::IsNotNull(target);
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestCrx {
    
}
