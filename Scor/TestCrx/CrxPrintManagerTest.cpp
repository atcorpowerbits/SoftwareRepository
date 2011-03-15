
#include "StdAfx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Printer;
using namespace AtCor::Scor::CrossCutting::Configuration;

using namespace System;
using namespace System::Text;
using namespace System::Data;
using namespace System::Windows;
using namespace System::Windows::Forms;
using namespace System::Data::Common;
using namespace System::Data::SqlClient;
using namespace System::IO;
using namespace System::Diagnostics;
using namespace System::ComponentModel;
using namespace System::Data::OleDb;
using namespace System::Drawing;
using namespace System::Drawing::Printing;
namespace TestCrx {
    using namespace System;
    ref class CrxPrintManagerTest;
    
    
    /// <summary>
///This is a test class for CrxPrintManagerTest and is intended
///to contain all CrxPrintManagerTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxPrintManagerTest
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
				CrxPrintManager^  actual;
				actual = CrxPrintManager::Instance;
				Assert::IsNotNull(actual);
			}
			
			// This tests the assigment operator which is private and blank implmentation
			// we do not need to test this as of now: 02/12/2011: Alok Sahu
			/// <summary>
			///A test for op_Assign
			///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxPrintManager_Accessor^  target = (gcnew CrxPrintManager_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxPrintManager^  unnamed = nullptr; // TODO: Initialize to an appropriate value
	//			CrxPrintManager^  expected = nullptr; // TODO: Initialize to an appropriate value
	//			CrxPrintManager^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
			/// <summary>
			///A test for AtCorprintstatus
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void AtCorprintstatusTest()
			{
				CrxPrintManager_Accessor^  target = (gcnew CrxPrintManager_Accessor()); // TODO: Initialize to an appropriate value
				Object^  sender = nullptr; // TODO: Initialize to an appropriate value
				PrintPageEventArgs^  e = nullptr;
				
				//This is private function of print manager which called from AtCorPrintDocumentTest and requires 
				//PrintPageEventArgs, which raised from print dialog.
				//because of this, function can not test automatically.
				//We have tested this function in the application while testing the print functionality.
				Assert::Inconclusive("Function can not test automatically");
			}

			
			/// <summary>
			///A test for AtCorPrintDocument
			///</summary>
	public: [TestMethod]
			void AtCorPrintDocumentTest()
			{
				CrxPrintManager_Accessor^  target = (gcnew CrxPrintManager_Accessor()); // TODO: Initialize to an appropriate value
				String^  prnString = "Print String"; // TODO: Initialize to an appropriate value
				
				//This function opens print dialog box which requires user to click on print/cancel. 
				//because of this, function can not test automatically.
				//We have tested this function in the application while testing the print functionality.
				Assert::Inconclusive("Function can not test automatically");
			
			}
			/// <summary>
			///A test for CrxPrintManager Copy Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxPrintManagerConstructorTest1()
			{
				CrxPrintManager^  unnamed = nullptr;
				CrxPrintManager_Accessor^  target = (gcnew CrxPrintManager_Accessor(unnamed));
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for CrxPrintManager Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxPrintManagerConstructorTest()
			{
				CrxPrintManager_Accessor^  target = (gcnew CrxPrintManager_Accessor());
				Assert::IsNotNull(target);
			}
	};
}
namespace TestCrx {
    
}
