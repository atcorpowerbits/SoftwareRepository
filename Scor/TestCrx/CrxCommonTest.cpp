
#include "StdAfx.h"
using namespace System;
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
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				CrxCommon^  actual;
				actual = CrxCommon::Instance;
				Assert::IsNotNull(actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
	//		/// <summary>
	//		///A test for op_Assign
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxCommon_Accessor^  target = (gcnew CrxCommon_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxCommon^  unnamed = nullptr; // TODO: Initialize to an appropriate value
	//			CrxCommon^  expected = nullptr; // TODO: Initialize to an appropriate value
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
				CrxCommon_Accessor^  target = (gcnew CrxCommon_Accessor()); // TODO: Initialize to an appropriate value
				CultureInfo^  expected = nullptr; // TODO: Initialize to an appropriate value
				CultureInfo^  actual;
				//Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\Scor_Source_code");
				expected = target->gCI;
				String^ expectedOut;
				//expectedOut = "fr-FR";
				//expected = gcnew CultureInfo(expectedOut);
				actual = target->GetCommCultureInfo();
				Assert::AreEqual(expected, actual);

				String^ path = Directory::GetCurrentDirectory(); 
				//Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\Scor_Source_code");
				expectedOut = "fr-FR";
				expected = gcnew CultureInfo(expectedOut);
				actual = target->GetCommCultureInfo();
				Assert::AreEqual(expected, actual);

				//Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\Scor_Source_code\\TestResults");

				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CrxCommon Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxCommonConstructorTest1()
			{
				CrxCommon^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				CrxCommon_Accessor^  target = (gcnew CrxCommon_Accessor(unnamed));
				Assert::IsNotNull(target);
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
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
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestCrx {
    
}
