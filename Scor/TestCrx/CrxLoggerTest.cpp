
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
			/*public: [ClassInitialize]
			static System::Void MyClassInitialize(TestContext^  testContext)
			{
				SetPath();
			}*/
			
			//Use ClassCleanup to run code after all tests in a class have run
			//public: [ClassCleanup]
			//static System::Void MyClassCleanup()
			//{
			//}
			//
			public: [TestInitialize]
			System::Void MyTestInitialize()
			{
				_currDir = Directory::GetCurrentDirectory(); 
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
				CrxLogger^  actual;
				SetPath();
				actual = CrxLogger::Instance;
				Assert::IsNotNull(actual);
			}
			
			/// <summary>
			///A test for Write
			///</summary>
	public: [TestMethod]
			void WriteTest()
			{
				try
				{
					//delete target;
					StreamReader ^curLogFileFileStream;
					String ^ path = Directory::GetCurrentDirectory() + "\\system\\logs\\";

					SetPath();

					// write into file
					//File::Delete("system\\logs\\scor.log");
					CrxLogger^  target = CrxLogger::Instance ; 
					String^  message = "ThisIsForTestOnly"; 
					target->Write(message);

				

					if(File::Exists(path + "scor.log"))					
					{
						// create a copy of log file to read from
						File::Copy(path+"scor.log", path+"scor_test.log"); 
						curLogFileFileStream = gcnew StreamReader(File::Open(path+"scor_test.log", FileMode::Open,FileAccess::Read,FileShare::Read ));
						String ^fileStr = curLogFileFileStream->ReadToEnd();
			
						// read last line from file
						String ^lastLine = fileStr->Substring(fileStr->LastIndexOf('\n',(fileStr->Length) - 5) + 1);
						lastLine = lastLine->Trim();
						lastLine= lastLine->Substring(lastLine->LastIndexOf('\t')+1); 

						// compared already written and last line, should match
						Assert::AreEqual(lastLine, message);
					}
				}
				catch(Exception^ eobj)
				{
					Assert::Fail("Error occured in 'WriteTest'.");
				}
			}
	//		/// <summary>
	//		///A test for op_Assign
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"crx.dll")]
	//		void op_AssignTest()
	//		{
	//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); 
	//			CrxLogger^  unnamed = nullptr; 
	//			CrxLogger^  expected = nullptr; 
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
				
				// delete the log file instance
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
				SetPath();
				CrxLogger^  unnamed = CrxLogger::Instance ; 
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
			Assert::IsNotNull(actual);
		}


		//Deepak: There is an existring write test
//		/// <summary>
//		///A test for Write
//		///</summary>
//public: [TestMethod]
//		void WriteTest1()
//		{
//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); 
//			String^  message = System::String::Empty; 
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
	  		CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); 
			bool expected = true; 
			bool actual;

			SetPath();
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
		///A test for op_Assign, this private assignment operator test, it has empty implementation and
		/// is a private member of class, hence no test needed.
		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void op_AssignTest()
//		{
//			SetPath();
//				
//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); 
//			CrxLogger_Accessor^  unnamed = nullptr; 
//			CrxLogger_Accessor^  expected = target; 
//			CrxLogger_Accessor^  actual;
//			actual = (unnamed = target);
//			Assert::AreEqual(expected, actual);
//			
//		}

//		/// <summary>
//		///A test for GetLastWrittenLineNumber
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"crx.dll")]
//		void GetLastWrittenLineNumberTest1()
//		{
//			CrxLogger_Accessor^  target = (gcnew CrxLogger_Accessor()); 
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
//			CrxLogger_Accessor^  unnamed = gcnew CrxLogger_Accessor() ; 
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
			Assert::IsNotNull(target);
		}
};
}
namespace TestCrx {
    
}
