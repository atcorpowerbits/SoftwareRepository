
#include "StdAfx.h"
using namespace System::IO;
using namespace System::Globalization;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting;

namespace TestCrx {
    using namespace System;
    ref class CrxCommonTest;
    
    
	/// <summary>
	///This is a test class for CrxCommonTest and is intended
	///to contain all CrxCommonTest Unit Tests
	///</summary>
	[TestClass]
	public ref class CrxCommonTest
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


#pragma endregion

			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				CrxCommon^  actual;
				actual = CrxCommon::Instance;
				Assert::IsNotNull(actual);
			}
	//		/// <summary>
	//		///A test for op_Assign
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxCommon_Accessor^  target = (gcnew CrxCommon_Accessor()); 
	//			CrxCommon^  unnamed = nullptr; 
	//			CrxCommon^  expected = nullptr; 
	//			CrxCommon^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}

			/// <summary>
			///A test for GetCommCultureInfo
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetCommCultureInfoTest()
			{
				CrxCommon_Accessor^  target = (gcnew CrxCommon_Accessor()); 
				CultureInfo^  expected = nullptr; 
				CultureInfo^  actual;
				String^ expectedOut;

				expected = target->gCI;

				actual = target->GetCommCultureInfo();
				Assert::AreEqual(expected, actual);

				expectedOut = "fr-FR";
				expected = gcnew CultureInfo(expectedOut);
				
				actual = target->GetCommCultureInfo();
				Assert::AreNotEqual(expected, actual);
			}

			/// <summary>
			///A test for CrxCommon Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxCommonConstructorTest1()
			{
				CrxCommon^  unnamed = nullptr; 
				CrxCommon_Accessor^  target = (gcnew CrxCommon_Accessor(unnamed));
				Assert::IsNotNull(target);
			}
			
			/// <summary>
			///A test for CrxCommon Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxCommonConstructorTest()
			{
				CrxCommon_Accessor^  target = (gcnew CrxCommon_Accessor());
				Assert::IsNotNull(target);
			}
	};
}
namespace TestCrx {
    
}
