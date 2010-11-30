
#include "StdAfx.h"
using namespace System;
using namespace System::IO;// For FileStream
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Messaging;
namespace TestCrx {
    using namespace System;
    ref class CrxMessagingManagerTest;
    
    
    /// <summary>
///This is a test class for CrxMessagingManagerTest and is intended
///to contain all CrxMessagingManagerTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxMessagingManagerTest
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
			//Smarajit Mishra
			//Customized function to Set the path
			void SetPath()
			{
				String^ path = Directory::GetCurrentDirectory(); 
//TM				Directory::SetCurrentDirectory("D:\\Atcor_2008\\Deepak\\Sprint1-Scor-Code\\Scor\\TestResults");
				Directory::SetCurrentDirectory("C:\\Projects\\PN022\\Scor\\TestResults");
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
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				CrxMessagingManager^  actual;
				actual = CrxMessagingManager::Instance;
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			// This tests the assigment operator which is private and blank implmentation
// we do not need to test this as of now: 11/02/2010: Smarajit Mishra
	//		/// <summary>
	//		///A test for op_Assign
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxMessagingManager^  unnamed = nullptr; // TODO: Initialize to an appropriate value
	//			CrxMessagingManager^  expected = nullptr; // TODO: Initialize to an appropriate value
	//			CrxMessagingManager^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
	//		/// <summary>
	//		///A test for GetMessage
	//		///</summary>
	//public: [TestMethod]
	//		void GetMessageTest1()
	//		{
	//			CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); // TODO: Initialize to an appropriate value
	//			int errorCode = 0; // TODO: Initialize to an appropriate value
	//			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
	//			String^  actual;
	//			actual = target->GetMessage(errorCode);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
			/// <summary>
			///A test for GetMessage
			///</summary>
	public: [TestMethod]
			void GetMessageTest()
			{
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); // TODO: Initialize to an appropriate value
				//String^  strCode = System::String::Empty; // TODO: Initialize to an appropriate value
				//String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  strCode = "CRX_ERR_FILE_NOT_EXIST";
				String^ expected = "File does not exist.";
				String^  actual;
				CrxMessagingManagerTest::SetPath();
				actual = target->GetMessage(strCode);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CrxMessagingManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxMessagingManagerConstructorTest1()
			{
				CrxMessagingManager^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor(unnamed));
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for CrxMessagingManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxMessagingManagerConstructorTest()
			{
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor());
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestCrx {
    
}
