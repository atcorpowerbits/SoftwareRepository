
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting;
namespace TestCrx {
    using namespace System;
    ref class CrxEventContainerTest;
    
    
    /// <summary>
///This is a test class for CrxEventContainerTest and is intended
///to contain all CrxEventContainerTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxEventContainerTest
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
				CrxEventContainer^  actual;
				actual = CrxEventContainer::Instance;
				Assert::IsNotNull(actual);
			}
			
			/// <summary>
			///A test for op_Assign, this private assignment operator test, it has empty implementation and
			/// is a private member of class, hence no test needed.
			///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxEventContainer_Accessor^  target = (gcnew CrxEventContainer_Accessor()); 
	//			CrxEventContainer unnamed; 
	//			CrxEventContainer^  expected = nullptr; 
	//			CrxEventContainer^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
			
			/// <summary>
			///A test for CrxEventContainer Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxEventContainerConstructorTest1()
			{
				CrxEventContainer^  unnamed = nullptr; 
				CrxEventContainer_Accessor^  target = (gcnew CrxEventContainer_Accessor(unnamed));
				Assert::IsNotNull(target);
			}
			
			/// <summary>
			///A test for CrxEventContainer Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxEventContainerConstructorTest()
			{
				CrxEventContainer_Accessor^  target = (gcnew CrxEventContainer_Accessor());
				Assert::IsNotNull(target);
			}
	};
}
namespace TestCrx {
    
}
