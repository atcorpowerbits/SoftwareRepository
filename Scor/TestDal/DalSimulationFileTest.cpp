
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;

using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
namespace TestDal {
    using namespace System;
    ref class DalSimulationFileTest;
    
    
    /// <summary>
///This is a test class for DalSimulationFileTest and is intended
///to contain all DalSimulationFileTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalSimulationFileTest
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
				SetPath();
			}
			//
			//Use TestCleanup to run code after each test has run
			//public: [TestCleanup]
			//System::Void MyTestCleanup()
			//{
			//}
			//
#pragma endregion
			/// <summary>
			///A test for SaveCurrentValues
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SaveCurrentValuesTest()
			{
				SetPath();

				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); 
				unsigned short tonometerData = 123; 
				unsigned short cuffPulse = 456;
				bool expected = true; 
				bool actual;

				String^ path = Directory::GetCurrentDirectory(); 
				String^ filePath = path + "\\simulation\\pwv\\test.dat";

				try
				{
					//Create the file and pass it to new streamwiter.
					target->writer = File::CreateText(filePath);
				}
				catch(ScorException ^ scorexObj)
				{
					Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
				}
			
				actual = target->SaveCurrentValues(tonometerData, cuffPulse);
				//close file
				target->CloseFile();
				Assert::AreEqual(expected, actual);

				//now open the file manually and check if the value is written

				FileStream ^ checkFileStream = File::Open(filePath, FileMode::Open );
				 StreamReader ^ checkFileReader = gcnew StreamReader(checkFileStream);

				String ^singleLine = checkFileReader->ReadLine();
				array<String^> ^ DataStrings = singleLine->Split('\t', 2); //Parse only first two numbers
				unsigned short value1 , value2;

				//Read the values of the first line
				value1 = (short)Single::Parse(DataStrings[0]);
				value2 = (short)Single::Parse(DataStrings[1]);

				//compare with the values we have put in
				Assert::AreEqual(tonometerData, value1);
				Assert::AreEqual(cuffPulse, value2);
			}


			/// <summary>
			///A test for ResetFileStreamPosition
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ResetFileStreamPositionTest()
			{
				SetPath();
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor(Directory::GetCurrentDirectory() + "\\simulation\\pwv\\Simulation.dat")); 
				bool expected = true; 
				bool actual;
				
				//String^ path = Directory::GetCurrentDirectory(); 
				//String^ filePath = path + "\\simulation\\pwv\\simulation.dat";
				//try
				//{
				//	FileStream ^ openFileStream = File::Open(filePath, FileMode::Open);
				//	//Open the file and pass it to new streamreader.
				//	target->reader = gcnew StreamReader(openFileStream);
				//}
				//catch(ScorException ^ scorexObj)
				//{
				//	Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
				//}

				//Open the file and pass it to new streamreader.
				//target->reader = gcnew StreamReader(openFileStream);

				//This causes a crash in the execution engine so we will move the possition manually
				////call the GetNextvalues for a few times so that the pointer points to a nonzero index
				//unsigned int value1, value2;
				//target->GetNextValues(&value1, &value2);
				//target->GetNextValues(&value1, &value2);
				//target->GetNextValues(&value1, &value2);

				target->reader->BaseStream->Position  = 11;

				Assert::AreNotEqual((unsigned long)0, (unsigned long)target->reader->BaseStream->Position );
				
				actual = target->ResetFileStreamPosition();
				Assert::AreEqual(expected, actual);
				Assert::AreEqual((System::Int64)0, target->reader->BaseStream->Position );

			}
			/// <summary>
			///A test for OpenFile
			///</summary>
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void OpenFileTest()
			{
				SetPath();
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); // TODO: Initialize to an appropriate value
				bool expected = true; 
				bool actual;
				
				bool fileOpenTest;

				String^ path = Directory::GetCurrentDirectory();
				target->filePath = path + "\\simulation\\pwv\\Default.dat"; 
				try
				{
					actual = target->OpenFile();
				}
				catch(ScorException ^ scorexObj)
				{
					Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
				}
				Assert::AreEqual(expected, actual);
				

				//trying again to open the same file
				try
				{
					actual = target->OpenFile();
				}
				catch(ScorException ^)
				{
					fileOpenTest = true;
				}
				Assert::IsTrue(fileOpenTest); //Is true because file already been open

			}
			/// <summary>
			///A test for Dispose
			///</summary>
	/*public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DisposeTest1()
			{
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); // TODO: Initialize to an appropriate value
				bool unnamed = false; // TODO: Initialize to an appropriate value
				//target->Dispose(unnamed);
				Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
			/// <summary>
			///A test for Dispose
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DisposeTest()
			{
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); // TODO: Initialize to an appropriate value
				Assert::IsNotNull(target);
				//	target->Dispose();
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}*/
			/// Ceating files dynamically so that if run the test case twice will not give an error
			///A test for CreateFile
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CreateFileTest()
			{
				SetPath();
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); 
				
				String^ path = Directory::GetCurrentDirectory();

				//String^  outputFilePath = path + "\\simulation\\pwv\\abc.dat";
				DateTime currentDateTime;
				currentDateTime = System::DateTime::Now;
				String^ tempCapture = "CreateFileTest";
				String  ^ outputFilePath = currentDateTime.ToString("yyyyMMMddHHmmss");
				outputFilePath = tempCapture + outputFilePath ;
				outputFilePath = path + "\\simulation\\pwv\\" + outputFilePath;
				

				bool expected = true; 
				bool actual;
				try
				{
					actual = target->CreateFile(outputFilePath);
				}
				catch(ScorException ^ scorexObj)
				{
					Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
				}
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for CloseFile
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CloseFileTest()
			{
				SetPath();
				String^ path = Directory::GetCurrentDirectory(); 
				String^ filePath = path + "\\simulation\\pwv\\test.dat";
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor(filePath)); 
				bool expected = true;

				try
				{
					Assert::IsNotNull(target->reader);
					target->CloseFile();
					Assert::IsNull(target->reader);
				}
				catch(ScorException ^ scorexObj)
				{
					Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
				}
			}

			///for wrriter
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CloseFileTest2()
			{
				SetPath();
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); 
				
				String^ path = Directory::GetCurrentDirectory();

				DateTime currentDateTime;
				currentDateTime = System::DateTime::Now;
				String^ tempCapture = "CloseFileTest2";
				String  ^ outputFilePath = currentDateTime.ToString("yyyyMMMddHHmmss");
				outputFilePath = tempCapture + outputFilePath ;
				outputFilePath = path + "\\simulation\\pwv\\" + outputFilePath;
				
				bool expected = true; 
				bool actual;
				try
				{
					
					actual = target->CreateFile(outputFilePath);
					Assert::IsTrue(actual);

					Assert::IsNotNull(target->writer);
					//now call close to check if it wores on a write
					actual = target->CloseFile();
					Assert::IsTrue(actual);

					Assert::IsNull(target->writer);

				}
				catch(ScorException ^ scorexObj)
				{
					Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
				}
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for ~DalSimulationFile
			///</summary>
			/*public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			//void ~DalSimulationFileTest()
			~DalSimulationFileTest()
			{
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); // TODO: Initialize to an appropriate value
				target->~DalSimulationFile();
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");

			}*/
			/// <summary>
			///A test for DalSimulationFile Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalSimulationFileConstructorTest1()
			{
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor());
				Assert::IsNotNull(target);
				Assert::IsNull(target->filePath);
				Assert::IsNull(target->reader);
			}
			/// <summary>
			///A test for DalSimulationFile Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalSimulationFileConstructorTest()
			{
				SetPath();
				String^ path = Directory::GetCurrentDirectory(); 
				String^ filePath = path + "\\simulation\\pwv\\test.dat";
				DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor(filePath));
				
				Assert::IsNotNull(target->reader);
			}

			//This test fails because the call to GetNextValues causes the test engine to crash/
			//We have tried usingh unsigned long values just like we do in the code.
			//However MStest does not allow automatic type casting and throws an error.
			//We also tried using unsigned int pointers but MS test does not allow it.
			//Cannot run this test hence comment it.

			//public: [TestMethod]
			//void GetNextValuesTest()
			//{

			//	//variables to hold the tonometer and cuff pulse readings
			//	unsigned int tonoData, cuffPulseData;

			//	bool expected;
			//	bool actual = true;

			//	SetPath();
			//	String^ path = Directory::GetCurrentDirectory();

			//	//get the next set of values from the simulation file.
			//	DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor());
			//	//access file
			//	target->filePath = path + "\\simulation\\pwv\\capture_2011Mar15151631.dat"; 

			//	try
			//	{
			//			expected = target->GetNextValues(&tonoData, &cuffPulseData);
			//			Assert::AreEqual(expected, actual);
			//	}
			//	catch( AtCor::Scor::CrossCutting::ScorException^ scExcepObj)
			//	{
			//		Assert::IsTrue(true);
			//	}

			//}

			//This test fails because the call to GetNextValues causes the test engine to crash/
			//We have tried using unsigned long values just like we do in the code.
			//However MStest does not allow automatic type casting and throws an error.
			//We also tried using unsigned int pointers but MS test does not allow it.
			//Cannot run this test hence comment it.
			//public: [TestMethod]
			//void GetNextValuesTest1()
			//{
			//	//variables to hold the tonometer and cuff pulse readings
			//	unsigned int tonoData1, cuffPulseData1;
			//	unsigned int tonoData2, cuffPulseData2;

			//	bool expected;
			//	bool actual = true;

			//	SetPath();
			//	String^ path = Directory::GetCurrentDirectory();

			//	//get the next set of values from the simulation file.
			//	DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor());
			//	//access file
			//	target->filePath = path + "\\simulation\\pwv\\capture_2011Mar15151631.dat"; 

			//	try
			//	{
			//			expected = target->GetNextValues(&tonoData1, &cuffPulseData1, &tonoData2, &cuffPulseData2);
			//			Assert::AreEqual(expected, actual);
			//	}
			//	catch( AtCor::Scor::CrossCutting::ScorException^ scExcepObj)
			//	{
			//		Assert::IsTrue(true);
			//	}

			//}

			/// <summary>
			///A test for SaveCurrentValues
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SaveCurrentValuesTest1()
		{
			SetPath();

			DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); 
			unsigned short cuffPulse = 456;
			bool expected = true; 
			bool actual;

			String^ path = Directory::GetCurrentDirectory(); 
			String^ filePath = path + "\\simulation\\pwa\\test.dat";

			try
			{
				//Create the file and pass it to new streamwiter.
				target->writer = File::CreateText(filePath);
			}
			catch(ScorException ^ scorexObj)
			{
				Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
			}
		
			actual = target->SaveCurrentValues(cuffPulse);
			target->CloseFile();	//close file
			Assert::AreEqual(expected, actual);

			//now open the file manually and check if the value is written
			FileStream ^ checkFileStream = File::Open(filePath, FileMode::Open );
			StreamReader ^ checkFileReader = gcnew StreamReader(checkFileStream);

			String ^singleLine = checkFileReader->ReadLine();
			unsigned short value1;

			singleLine = target->RemoveSpecialCharacters(singleLine);
			value1 = (short)Single::Parse(singleLine);
			Assert::AreEqual(cuffPulse, value1);
		}
};
}
namespace TestDal {
    
}
