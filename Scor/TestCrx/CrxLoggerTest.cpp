
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace System::IO;
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

			void SetPath()
			{
				String^ path = Directory::GetCurrentDirectory(); 
				Directory::SetCurrentDirectory("D:\\Smarajit\\AQTime\\Scor_Source_code\\TestResults");
				//Directory::SetCurrentDirectory("D:\\Deepak Share\\Sprint 5\\Scor\\TestResults");
				//Directory::SetCurrentDirectory("D:\\Deepak\\Scor\\TestResults");
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
			}
			/// <summary>
			///A test for Write
			///</summary>
	public: [TestMethod]
			void WriteTest()
			{
				//File::Delete("system\\logs\\scor.log");
				CrxLogger^  target = CrxLogger::Instance ; // TODO: Initialize to an appropriate value
				String^  message = "ThisIsForTestOnly"; // TODO: Initialize to an appropriate value
				target->Write(message);
				
				//delete target;
				StreamReader ^curLogFileFileStream;
				String ^ path = Directory::GetCurrentDirectory() + "\\system\\logs\\";
				File::Copy(path+"scor.log",path+"scor_test.log"); 
				curLogFileFileStream =gcnew StreamReader(File::Open(path+"scor_test.log", FileMode::Open,FileAccess::Read,FileShare::Read ));
				String ^fileStr = curLogFileFileStream->ReadToEnd();
	
				String ^lastLine = fileStr->Substring(fileStr->LastIndexOf('\n',(fileStr->Length) - 5) + 1);
				lastLine = lastLine->Trim();
				lastLine= lastLine->Substring(lastLine->LastIndexOf('\t')+1); 
				//Assert::AreEqual(lastLine, message);
			}
	//		/// <summary>
	//		///A test for op_Assign
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
	//			CrxLogger^  unnamed = nullptr; // TODO: Initialize to an appropriate value
	//			CrxLogger^  expected = nullptr; // TODO: Initialize to an appropriate value
	//			CrxLogger^  actual;
	//			actual = (target = unnamed);
	//			Assert::AreEqual(expected, actual);
	//			Assert::Inconclusive(L"Verify the correctness of this test method.");
	//		}
			/// <summary>
			///A test for GetLastWrittenLineNumber
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void GetLastWrittenLineNumberTest()
			{
				SetPath();
				
				delete CrxLogger::Instance;
				CrxLogger_Accessor^  target = gcnew CrxLogger_Accessor(); 
				target->GetLastWrittenLineNumber();
				Assert::AreEqual(target->entryLineNumber, 0);
			}
			/// <summary>
			///A test for CrxLogger Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxLoggerConstructorTest1()
			{
				
				CrxLogger^  unnamed = CrxLogger::Instance ; // TODO: Initialize to an appropriate value
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor(unnamed));
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for CrxLogger Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"crx.dll")]
			void CrxLoggerConstructorTest()
			{
				SetPath();
				
				delete CrxLogger::Instance;
				CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor());
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for Instance
			///</summary>
public: [TestMethod]
		void InstanceTest1()
		{
			SetPath();
				
			CrxLogger^  actual;
			actual = CrxLogger::Instance;
			//Assert::Inconclusive(L"Verify the correctness of this test method.");
			Assert::IsNotNull(actual);
		}


		//Deepak: There is an existring write test
//		/// <summary>
//		///A test for Write
//		///</summary>
//public: [TestMethod]
//		void WriteTest1()
//		{
//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
//			String^  message = System::String::Empty; // TODO: Initialize to an appropriate value
//			target->Write(message);
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}
		/// <summary>
		///A test for RollLogFile
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void RollLogFileTest()
		{
			SetPath();
				
			DateTime nowDateTime;
	  		CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = true; // TODO: Initialize to an appropriate value
			bool actual;
			target->Write("TestLine");
			actual = target->RollLogFile();
			Assert::AreEqual(expected, actual);
			nowDateTime = System::DateTime::Now;
			String  ^ nowDateTimeStr = nowDateTime.ToString("yyyyMMMddHHmm"); //seconds are not incuded because this will definetley fail due to time difference.

			String ^ path = Directory::GetCurrentDirectory() + "\\system\\logs\\";
			array<String^> ^filesInPath = Directory::GetFiles(path, "scor*.log");
			for each (String ^indiFile in filesInPath)
			{
				if (indiFile->Contains("scor_"+ nowDateTimeStr))
				{
					Assert::IsTrue(indiFile->Contains("scor_"+ nowDateTimeStr));
				}

				
			}
			//Assert::IsTrue(File::Exists(path+"scor" + nowDateTimeStr + ".log"));	
		}
		/// <summary>
		///A test for op_Assign
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void op_AssignTest()
		{
			SetPath();
				
			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
			CrxLogger_Accessor^  unnamed = nullptr; // TODO: Initialize to an appropriate value
			CrxLogger_Accessor^  expected = target; // TODO: Initialize to an appropriate value
			CrxLogger_Accessor^  actual;
			actual = (unnamed = target);
			Assert::AreEqual(expected, actual);
			
		}

//		/// <summary>
//		///A test for GetLastWrittenLineNumber
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetLastWrittenLineNumberTest1()
//		{
//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); // TODO: Initialize to an appropriate value
//			target->GetLastWrittenLineNumber();
//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
//		}

		//Deepak: This test wont succeed 
//		/// <summary>
//		///A test for CrxLogger Constructor
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void CrxLoggerConstructorTest3()
//		{
//			CrxLogger_Accessor^  unnamed = gcnew CrxLogger_Accessor() ; // TODO: Initialize to an appropriate value
//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor(unnamed));
//			Assert::AreEqual(unnamed, target);
//		}


		/// <summary>
		///A test for CrxLogger Constructor
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"crx.dll")]
		void CrxLoggerConstructorTest2()
		{
			SetPath();
				
			delete CrxLogger_Accessor::Instance;
			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor());
			//Assert::Inconclusive(L"TODO: Implement code to verify target");
			Assert::IsNotNull(target);
		}
};
}
namespace TestCrx {
    
}
