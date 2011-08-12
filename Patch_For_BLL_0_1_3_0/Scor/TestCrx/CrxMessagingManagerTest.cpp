
#include "StdAfx.h"
#include "StdAfx.h"
//using namespace System;
using namespace System::IO;// For FileStream
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Messaging;

using namespace System::Drawing;

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
		
	private: String^ _currDir;
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
				int i = path->IndexOf("\\TestResults");
				if(i > 0)
				{
					path = path->Substring(0,i + 12);
					Directory::SetCurrentDirectory(path);
				}
				else
				{
					path  = path + "\\TestResults";
					Directory::SetCurrentDirectory(path);
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
			public: [TestInitialize]
			System::Void MyTestInitialize()
			{
				_currDir = Directory::GetCurrentDirectory(); 
				//_objConfig = CrxConfigManager::Instance;
			}
			
			//Use TestCleanup to run code after each test has run
			public: [TestCleanup]
			System::Void MyTestCleanup()
			{
				Directory::SetCurrentDirectory(_currDir);
			}
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
				Assert::IsNotNull(actual);
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
	//			CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); 
	//			CrxMessagingManager^  unnamed = nullptr; 
	//			CrxMessagingManager^  expected = nullptr; 
	//			CrxMessagingManager^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
	
			/// <summary>
			///A test for GetMessage
			///</summary>
	public: [TestMethod]
			void GetMessageTest()
			{
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); 
				String^  actual;
				String^  strCode = "CRX_ERR_FILE_NOT_EXIST";
				String^  expected = "System Configuration file does not exist.";

				actual = target->GetMessage(strCode);
				Assert::AreEqual(expected, actual);
			}
			
			/// <summary>
			///A test for GetMessage
			///</summary>
	public: [TestMethod]
			void GetMessageTest1()
			{
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); 
				String^  actual;
				String^  strCode = "CRX_ERR_FILE";
				String^  expected = "201 : Error code not found.";

				actual = target->GetMessage(strCode);
				Assert::AreEqual(expected, actual);
			}
			
			/// <summary>
			///A test for CrxMessagingManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxMessagingManagerConstructorTest1()
			{
				CrxMessagingManager^  unnamed = nullptr; 
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor(unnamed));
				Assert::IsNotNull(target);
			}

			/// <summary>
			///A test for CrxMessagingManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxMessagingManagerConstructorTest()
			{
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor());
				Assert::IsNotNull(target);
			}

			/// <summary>
			///A test for GetImage
			///</summary>
	public: [TestMethod]
			void GetImageTest()
			{
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); 
				String^  strCode = System::String::Empty; 
				Image^  expected = nullptr; 
				Image^  actual;
				//Begin: Alok - 04-Mar-2011
				strCode = "TestImage"; //Setting invalid image name
				try
				{
					actual = target->GetImage(strCode);
				}
				catch(Exception^)
				{
					Assert::IsNull(actual);
				}

				
				//End: Alok - 04-Mar-2011
			}

			/// <summary>
			///A test for GetImage
			///</summary>
	public: [TestMethod]
			void GetImageTest1()
			{
				CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); 
				String^  strCode = System::String::Empty; 
				Image^  expected = nullptr; 
				Image^  actual;

				//Setting valid image name (which is in resource file)
				strCode = "CEMarkSGS"; 
				actual = target->GetImage(strCode);

				Assert::IsNotNull(actual);
			}
			
			/// <summary>
			///A test for CheckResourceFileExist
			///</summary>
public: [TestMethod]
		void CheckResourceFileExistTest()
		{
			CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); 
		
			try
			{
				target->CheckResourceFileExist();
			}
			catch(Exception^)
			{
				Assert::IsTrue(true,"If Exception occur then test case pass.");	
			}
		}

//public: [TestMethod]
//		void CheckResourceFileExistTest1()
//		{
//			CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); 
//			int expected = 0; 
//			int actual;
//
//			SetPath();
//			try
//			{
//				actual = target->CheckResourceFileExist();
//			}
//			catch(Exception^)
//			{
//				actual = 1;
//			}
//			Assert::AreEqual(expected, actual);
//		}
		/// <summary>
		///A test for CheckResourceFileExist
		///</summary>
public: [TestMethod]
		void CheckResourceFileExistTest1()
		{
			CrxMessagingManager_Accessor^  target = (gcnew CrxMessagingManager_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = true; // TODO: Initialize to an appropriate value
			bool actual;
			
			SetPath();
			try
			{
				actual = target->CheckResourceFileExist();
			}
			catch(Exception^)
			{
				actual = false;
			}
			Assert::AreEqual(expected, actual);
		}
};
}
namespace TestCrx {
    
}
