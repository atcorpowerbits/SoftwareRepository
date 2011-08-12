
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace System::IO;
using namespace AtCor::Scor::CrossCutting;

namespace TestCrx {
    using namespace System;
    ref class CrxSytemParametersTest;
    
    
    /// <summary>
///This is a test class for CrxSytemParametersTest and is intended
///to contain all CrxSytemParametersTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxSytemParametersTest
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
				SetPath();
				CrxSytemParameters^  actual;
				actual = CrxSytemParameters_Accessor::Instance;
				Assert::IsNotNull(actual);
			}
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void op_AssignTest()
			{
				SetPath();
				CrxSytemParameters_Accessor^  target; 
				CrxSytemParameters_Accessor^ unnamed = (gcnew CrxSytemParameters_Accessor()); 
				CrxSytemParameters_Accessor^  expected = unnamed; 
				CrxSytemParameters_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for GetStringTagValue
			///</summary>
	public: [TestMethod]
			void GetStringTagValueTest()
			{
				SetPath();
				CrxSytemParameters_Accessor^  target = (gcnew CrxSytemParameters_Accessor()); 
				String^  tagName = "TestValue"; 
				String^  expected = "999"; 
				String^  actual;
				actual = target->GetStringTagValue(tagName);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for GetNestedTagValue
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetNestedTagValueTest()
			{
				SetPath();

				CrxSytemParameters_Accessor^  target = (gcnew CrxSytemParameters_Accessor()); 
				String^  nestedTags = "MyTestValues.Value2"; 
				String^  expected = "2";
				String^  actual;
				actual = target->GetNestedTagValue(nestedTags);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///Test the exception throwing mechanism 
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetNestedTagValueExceptionTest()
			{
				SetPath();
				bool exceptionRaised = false;

				try
				{
					CrxSytemParameters_Accessor^  target = (gcnew CrxSytemParameters_Accessor()); 
					String^  nestedTags = "MyTestValues.NotPresent"; 
					
					target->GetNestedTagValue(nestedTags);
				}
				catch(ScorException^)
				{
					exceptionRaised = true;
				}
				Assert::IsTrue(exceptionRaised);
			}
			/// <summary>
			///A test for GetIntegerTagValue
			///</summary>
	public: [TestMethod]
			void GetIntegerTagValueTest()
			{
				SetPath();

				CrxSytemParameters_Accessor^  target = (gcnew CrxSytemParameters_Accessor()); 
				String^  tagName =  "MyTestValues.Value1"; 
				int expected = 1; 
				int actual;
				actual = target->GetIntegerTagValue(tagName);
				Assert::AreEqual(expected, actual);
			}
			
			/// <summary>
			///A test for CrxSytemParameters Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxSytemParametersConstructorTest()
			{
				SetPath();

				CrxSytemParameters_Accessor^  unnamed = gcnew CrxSytemParameters_Accessor();
				CrxSytemParameters_Accessor^  target = (unnamed);
				Assert::AreEqual (unnamed, target);
			}
	};
}
namespace TestCrx {
    
}
