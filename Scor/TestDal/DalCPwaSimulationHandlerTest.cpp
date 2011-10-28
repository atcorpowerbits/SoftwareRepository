
#include "StdAfx.h"

using namespace System::Timers;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;

using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::CrossCutting::Configuration;


namespace TestDal {
    using namespace System;
    ref class DalCPwaSimulationHandlerTest;
    
    
    /// <summary>
///This is a test class for DalCPwaSimulationHandlerTest and is intended
///to contain all DalCPwaSimulationHandlerTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalCPwaSimulationHandlerTest
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
			[DeploymentItem(L"dal.dll")]
			void InstanceTest()
			{
				DalCPwaSimulationHandler_Accessor^  actual;
				actual = DalCPwaSimulationHandler_Accessor::Instance;
				Assert::IsNotNull(actual);	
			}
			/// <summary>
			///A test for StartCapture
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StartCaptureTest()
			{
				SetPath();

				DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
				bool expected = true; 
				bool actual;
				try
				{
					actual = target->StartCapture(10, 256);
					Assert::AreEqual(expected, actual);
					actual = target->StopCapture();
					Assert::AreEqual(expected, actual);
					Assert::IsFalse(target->captureTimer->Enabled) ;
				}
				catch(ScorException ^ scorExObj)
				{
					Assert::Fail("Scor Exception thrown: " + scorExObj->ErrorMessageKey );
				}
			}
			/// <summary>
			///A test for ReadMultipleEventsInLoop
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ReadMultipleEventsInLoopTest()
			{
				//Object^  sender = nullptr; // TODO: Initialize to an appropriate value
				//DalCPwaSimulationHandler_Accessor::ReadMultipleEventsInLoop(sender);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
				//---------------
				SetPath();
				int startIndex = -1;
				int endIndex = -1;

				//Creating child class object as DalSimulationHandler class is abstuct class
				DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); 
				
				Object^  sender = this; 
				
				target->dataBufferObj = DalDataBuffer::Instance;
				//create array
				target->dataBufferObj->CreateBuffer(10, 256);
			
				//call the method which will open the simulation file specified in config.
				
				target->GetFileNameFromConfgAndOpen();
				
				//target->_cuffTimerSimulationFile = gcnew DalSimulationFile_Accessor(".\\simulation\\cuff_timer\\cuff_timer.dat");
				//target->_tonometerSimulationFile = gcnew DalSimulationFile_Accessor(".\\simulation\\pwa\\Simulation.dat");
				

				//move file to start in case it isn't alreay at start.
				target->_tonometerSimulationFile->ResetFileStreamPosition();
				target->_cuffTimerSimulationFile->ResetFileStreamPosition();

				target->ReadMultipleEventsInLoop(sender);
				target->dataBufferObj->GetAllValues(startIndex, endIndex);

				Assert::AreEqual(startIndex, 0);
				Assert::AreEqual(endIndex, (int)DalConstants::SimulationNumberOfReadsPerInterval-1);
	
			}
			
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
				DalCPwaSimulationHandler_Accessor^  unnamed = DalCPwaSimulationHandler_Accessor::Instance; // TODO: Initialize to an appropriate value
				DalCPwaSimulationHandler_Accessor^  expected = DalCPwaSimulationHandler_Accessor::Instance; // TODO: Initialize to an appropriate value
				DalCPwaSimulationHandler_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for OnTimerReadMultipleEvents
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void OnTimerReadMultipleEventsTest()
			{
				SetPath();
				Object^  sender = this; 
				ElapsedEventArgs^  args = nullptr; //Diesnt matter , unused in actual method
				
				DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); 				
				int startIndex = 0;
				int endIndex = 0;
				
				target->dataBufferObj = DalDataBuffer::Instance;
				//create array
				target->dataBufferObj->CreateBuffer(10, 256);
					
				
				//call the method which will open the simulation file specified in config.
				
				//target->GetFileNameFromConfgAndOpen();
				
				String^ path = Directory::GetCurrentDirectory();
				String^ fileName1 = path + ".\\simulation\\cuff_timer\\cuff_timer.dat";
				String^ fileName2 = path + ".\\simulation\\pwa\\Simulation.dat";

				target->_cuffTimerSimulationFile = gcnew DalSimulationFile_Accessor(fileName1); //(".\\simulation\\cuff_timer\\cuff_timer.dat");


				target->_tonometerSimulationFile = gcnew DalSimulationFile_Accessor(fileName2); //(".\\simulation\\pwv\\Simulation.dat");				
				
				target->dataBufferObj->GetAllValues(startIndex, endIndex);
				Assert::AreEqual(-1, startIndex); //values will be -1 if no data has been put in buffer
				Assert::AreEqual(-1, endIndex);

				target->OnTimerReadMultipleEvents(sender, args);
				Threading::Thread::Sleep(10000); //Sleep to give the process enough time to add data to the buffer
				target->dataBufferObj->GetAllValues(startIndex, endIndex); //call to get the updated indices from buffer.
				Assert::AreNotEqual(-1, endIndex); //This should not be true. If true it means that the buffer hassned been updated.
				Assert::AreNotEqual(0, endIndex);
			}
			/// <summary>
			///A test for GetFileNameFromConfgAndOpen
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetFileNameFromConfgAndOpenTest()
			{
				SetPath();
				DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
				
				cli::array< unsigned short >^  tonometerData = gcnew array< unsigned short > {0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6}; 
				cli::array< unsigned short >^  cuffPulse = gcnew array< unsigned short > {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6}; 
				unsigned short bufferSize = 6; 

				//create a filestring with a wildcard character. Remove the seconds since it is not always reliable
				DateTime currentDateTime;
				currentDateTime = System::DateTime::Now;
				String^ tempCapture = "capture_";
				String  ^ currentDateTimeStr = currentDateTime.ToString("yyyyMMMddHHmm");
				currentDateTimeStr = tempCapture+ currentDateTimeStr ;

				String^  expected = target->_savedDataFilePath;
				String^  actual;
				actual = target->GetSavedFileName();

				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Dispose
			///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void DisposeTest()
	//		{
	//			DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
	//			bool unnamed = false; // TODO: Initialize to an appropriate value
	//			//target->Dispose(unnamed);
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			/// <summary>
			///A test for CloseFiles
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CloseFilesTest()
			{
				DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
				target->GetFileNameFromConfgAndOpen();
				Assert::IsNotNull(target->_cuffTimerSimulationFile);
				target->CloseFiles();

				Assert::IsNull(target->_cuffTimerSimulationFile);
			}
			/// <summary>
			///A test for ~DalCPwaSimulationHandler
			///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		~DalCPwaSimulationHandlerTest()
	//		{
	//			DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
	//			//target->~DalCPwaSimulationHandler();
	//			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
	//		}
			/// <summary>
			///A test for DalCPwaSimulationHandler Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalCPwaSimulationHandlerConstructorTest()
			{
				DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor());
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for StartBP
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StartBPTest1()
		{
			DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
			DalNIBPMode nibpMode = DalNIBPMode(); // TODO: Initialize to an appropriate value
			bool expected = true; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->StartBP(nibpMode);
			Assert::AreEqual(expected, actual);
			
		}
		/// <summary>
		///A test for StartBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StartBPTest()
		{
			DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
			DalNIBPMode nibpMode = DalNIBPMode(); // TODO: Initialize to an appropriate value
			unsigned short initialPressure = 0; // TODO: Initialize to an appropriate value
			bool expected = true; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->StartBP(nibpMode, initialPressure);
			Assert::AreEqual(expected, actual);
			
		}
		/// <summary>
		///A test for FinishBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void FinishBPTest()
		{
			DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = true; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->FinishBP();
			Assert::AreEqual(expected, actual);
			
		}
		/// <summary>
		///A test for AbortBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void AbortBPTest()
		{
			DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = true; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->AbortBP();
			Assert::AreEqual(expected, actual);
		}
};
}
namespace TestDal {
    
}
