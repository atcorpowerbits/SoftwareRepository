#include "Stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace System::IO;
using namespace AtCor::Scor::CrossCutting::Configuration;

//using namespace AtCor::Scor::CrossCutting::CrxConfiguration;


using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Logging;
namespace TestCrx {
    using namespace System;
    ref class CrxLoggerTest;
    
    
    /// <summary>
///This is a test class for CrxLoggerTest and is intended
///to contain all CrxLoggerTest Unit Tests
///</summary>
	[TestClass]
	public ref class CrxLoggerTest
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
				CrxLogger^  actual;
				actual = CrxLogger::Instance;
				Assert::IsNotNull(actual);
				///Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for Write
			///</summary>
			public: [TestMethod]
			void WriteTest()
			{
				/*
				This test case fails because Filestream cannot open the specified log file.
				The file is present in the specified location and the test string is beign written to the file.
				This can be verified by manually opening the log file.
				However it is not possible to verify it using this test case because the logger has a lock on the 
				scor.log file and when Filestream tries to open it it results in a XXX exception.
				Enterprise Lib Logger does not allow us to read from the log file, only write to it.
				In order to test it we will have to add a destructor which releases the log file.
				This will be done in the next sprint when the specific user story for logging is picked up.
				*/
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
				//String^  message = System::String::Empty; // TODO: Initialize to an appropriate value
				String^  message = "Dummy String Test Case";
				target->Write(message);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");

				FileStream^ LogFS = gcnew FileStream("system\\logs\\scor.log",FileMode::Open);
				Assert::IsNotNull(LogFS,"FileCould not be opened");
							
				StreamReader ^LogReader = gcnew StreamReader(LogFS);
				String ^TempString;
	
				TempString = LogReader->ReadLine();
				if (TempString->EndsWith(message) == false)
				{
					Assert::Fail("Failed to write to log file");
				}
				
			}
			/// <summary>
			///A test for op_Assign
			///</summary>
			// This tests the assigment operator which is private and blank implmentation
			// we do not need to test this as of now: 11/02/2010: Smarajit Mishra
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void op_AssignTest()
			{
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
				CrxLogger_Accessor^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				CrxLogger_Accessor^  expected = nullptr; // TODO: Initialize to an appropriate value
				CrxLogger_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for CrxLogger Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxLoggerConstructorTest1()
			{
				CrxLogger^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor(unnamed));
				Assert::AreEqual(target, unnamed);
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
			/// <summary>
			///A test for CrxLogger Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxLoggerConstructorTest()
			{
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor());
				Assert::IsNotNull(target);
				//Assert::Inconclusive(L"TODO: Implement code to verify target");
			}
	};
}
namespace TestCrx {
    
}
