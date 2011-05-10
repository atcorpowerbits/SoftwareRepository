
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
    ref class DalSimulationHandlerTest;
    
    
    /// <summary>
///This is a test class for DalSimulationHandlerTest and is intended
///to contain all DalSimulationHandlerTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalSimulationHandlerTest
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
private:	static String^ comPortName  = "Simulation";
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
			///A test for Instance
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void InstanceTest()
			{
				DalSimulationHandler_Accessor^  actual;
				actual = DalSimulationHandler_Accessor::Instance;
				Assert::IsNotNull(actual);	
			}
			/// <summary>
			///A test for StopCapture
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StopCaptureTest()
			{
				SetPath();
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				
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
			///A test for StartCapture
			///</summary>
			//Commeneted as per disscussion
			/*public: [TestMethod]             
			[DeploymentItem(L"dal.dll")]
			void StartCaptureTest1()
			{
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
				bool expected = false; 
				bool actual;
				SetPath();
				actual = target->StartCapture();
				Assert::AreEqual(expected, actual);
			}*/
			/// <summary>
			///A test for StartCapture
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StartCaptureTest()
			{
				SetPath();
				
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				int captureTime = 10; 
				int samplingRate = 256; 
				bool expected = true;
				bool actual;
				try
				{
					//target->dataBufferObj->GetAllValues(startIndex, endIndex);
					//Assert::AreEqual(-1, startIndex); //values will be -1 if no data has been put in buffer
					//Assert::AreEqual(-1, endIndex);

					actual = target->StartCapture(captureTime, samplingRate);
					Assert::AreEqual(expected, actual);

					//Deepak: recheck why this is giving -1
					//Threading::Thread::Sleep(3000); //Sleep to give the process enough time to add data to the buffer
					//target->StopCapture();
					//target->dataBufferObj->GetAllValues(startIndex, endIndex); //call to get the updated indices from buffer.
					//Assert::AreNotEqual(-1, endIndex); //This should not be true. If true it means that the buffer hassned been updated.
					//Assert::AreNotEqual(0, endIndex);
				}
				catch(ScorException ^ scorExObj)
				{
					Assert::Fail("Scor Exception thrown: " + scorExObj->ErrorMessageKey );
				}
			}
			/// <summary>
			///A test for SetPressure
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetPressureTest()
			{
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				int newPressure = 0; 
				EM4CuffBoard cuffBoard = EM4CuffBoard(); 
				bool expected = false; 
				bool actual;
				try
				{
					actual = target->SetPressure(newPressure, cuffBoard);
					Assert::AreEqual(expected, actual);
				}
				catch(ScorException ^ scorExObj)
				{
					Assert::Fail("Scor Exception thrown: " + scorExObj->ErrorMessageKey );
				}
			}
			/// <summary>
			///A test for SaveCaptureData
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SaveCaptureDataTest()
			{
				SetPath();
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 				
				cli::array< unsigned short >^  tonometerData = gcnew array< unsigned short > {0xA1, 0xA1, 0xA1, 0xA1, 0xA1, 0xA1}; 
				cli::array< unsigned short >^  cuffPulse = gcnew array< unsigned short > {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6}; 
				unsigned short bufferSize = 6;  
				bool expected = true; 
				bool actual;
				bool excepRaised = false;

				actual = target->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
				Assert::AreEqual(expected, actual);
				//verify that the file exists in the specified path
				String^ savedFileName = target->GetSavedFileName();
				Assert::IsNotNull(savedFileName);
				StreamReader ^ savedFileReader = gcnew StreamReader(savedFileName);

				try
				{
					for(int i = 0; i<bufferSize; i++)
					{
						Assert::IsNotNull(savedFileReader->ReadLine());
					}
				}
				catch(Exception^)
				{
					excepRaised = true;
				}
				//Assert::IsFalse(excepRaised);
				Assert::AreNotEqual(excepRaised, expected);
				
			}
			/// Confing file should have any valid simulaation file set
			///A test for ReadMultipleEventsInLoop
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ReadMultipleEventsInLoopTest()
			{
				SetPath();
				int startIndex = -1;
				int endIndex = -1;

				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 				
				Object^  sender = this; 

				
				target->dataBufferObj = DalDataBuffer::Instance;
				//create array
				target->dataBufferObj->CreateBuffer(10, 256);
					
				
				//call the method which will open the simulation file specified in config.
				
				//target->GetFileNameFromConfgAndOpen();
				
				target->_cuffTimerSimulationFile = gcnew DalSimulationFile_Accessor(".\\simulation\\cuff_timer\\cuff_timer.dat");
				target->_tonometerSimulationFile = gcnew DalSimulationFile_Accessor(".\\simulation\\pwv\\Simulation.dat");
				

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
			/*public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); // TODO: Initialize to an appropriate value
				DalSimulationHandler_Accessor^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				DalSimulationHandler_Accessor^  expected = nullptr; // TODO: Initialize to an appropriate value
				DalSimulationHandler_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}*/
			/// <summary>
			///A test for OnTimerReadMultipleEvents
			///</summary>
			//This Test need to be made run individually
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void OnTimerReadMultipleEventsTest()
			{
				SetPath();
				Object^  sender = this; 
				ElapsedEventArgs^  args = nullptr; //Diesnt matter , unused in actual method
				
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 				

				int startIndex = 0;
				int endIndex = 0;
				
				target->dataBufferObj = DalDataBuffer::Instance;
				//create array
				target->dataBufferObj->CreateBuffer(10, 256);
					
				
				//call the method which will open the simulation file specified in config.
				
				//target->GetFileNameFromConfgAndOpen();
				
				String^ path = Directory::GetCurrentDirectory();
				String^ fileName1 = path + ".\\simulation\\cuff_timer\\cuff_timer.dat";
				String^ fileName2 = path + ".\\simulation\\pwv\\Simulation.dat";

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
			///A test for OnTimerGetValuesAndRaiseEvents
			///</summary>
			//This method is no longer used, So it is commented
			//public: [TestMethod]
			//[DeploymentItem(L"dal.dll")]
			//void OnTimerGetValuesAndRaiseEventsTest()
			//{
			//	SetPath();
			//	//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
			//	DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); 
			//	//initialize reader
			//	FileStream ^ openFileStream;
			//	String^ path = Directory::GetCurrentDirectory();
			//	String^ filePath = path + "\\simulation\\pwv\\Simulation.dat";
			//	//Open the file and pass it to new streamreader.
			//	openFileStream = File::Open(filePath, FileMode::Open);
			//	
			//	target->reader = gcnew StreamReader(openFileStream);
			//	
			//	Object^  sender = nullptr; // TODO: Initialize to an appropriate value
			//	ElapsedEventArgs^  args = nullptr; // TODO: Initialize to an appropriate value

			//	DalSimulationHandler_Accessor::OnTimerGetValuesAndRaiseEvents(sender, args);
			//}
			/// <summary>
			///A test for GetSavedFileName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetSavedFileNameTest()				
			{
				SetPath();
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				//target->_commandInterface->CreateAndOpenNewSerialPort(comPortName);
				
				cli::array< unsigned short >^  tonometerData = gcnew array< unsigned short > {0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6}; 
				cli::array< unsigned short >^  cuffPulse = gcnew array< unsigned short > {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6}; 
				unsigned short bufferSize = 6; 

				//create a filestring with a wildcard character. Remove the seconds since it is not always reliable
				DateTime currentDateTime;
				currentDateTime = System::DateTime::Now;
				String^ tempCapture = "capture_";
				String  ^ currentDateTimeStr = currentDateTime.ToString("yyyyMMMddHHmm");
				currentDateTimeStr = tempCapture+ currentDateTimeStr ;

				

				//target->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
				
				String^  expected = target->_savedDataFilePath;
				String^  actual;
				actual = target->GetSavedFileName();

				Assert::AreEqual(expected, actual);
				//Assert::IsTrue(actual->Contains(currentDateTimeStr));
				//Assert::IsNotNull(actual->Contains(currentDateTimeStr));
			}
			/// <summary>
			///A test for GetFileNameFromConfgAndOpen
			///</summary>
			//this test need to be made run indipendently.
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetFileNameFromConfgAndOpenTest()
			{

				SetPath();
				String^ path = Directory::GetCurrentDirectory(); 
				
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				bool expected = true;
				bool actual;
				
				actual = target->GetFileNameFromConfgAndOpen();
				Assert::AreEqual(expected, actual);

				//check if the objects have been created
				Assert::IsNotNull(target->_cuffTimerSimulationFile);
				Assert::IsNotNull(target->_tonometerSimulationFile);
				
				String^ cuffTimerFilePath = target->_cuffTimerSimulationFile->filePath ;
				String^ tonometerSimFilePath = target->_tonometerSimulationFile->filePath ;

				//get the settings from config directly to test if the correct tono file is opened
				String^ tonoFileNameInConfig;
				CrxConfigManager ^configMgr = CrxConfigManager::Instance;
				configMgr->GetGeneralUserSettings();
				configMgr->GetPwvUserSettings();
				tonoFileNameInConfig = configMgr->PwvSettings->SimulationType+ ".dat";
				bool retValue = tonometerSimFilePath->Contains(tonoFileNameInConfig);
				Assert::IsTrue(retValue);

				//Now test if cuff file is opened properly
				Assert::AreEqual(".\\simulation\\cuff_timer\\cuff_timer.dat", cuffTimerFilePath);

			}
			/// <summary>
			///A test for GetConnectionStatus
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetConnectionStatusTest()
			{
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				
				bool expected = true; 
				bool actual;
				actual = target->GetConnectionStatus();
				Assert::AreEqual(expected, actual);
				//This method will always return true for simulation mode
			}


			/// Check varios flag combinations to test the output
			///A test for GetConnectionStatus
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckStatusFlagTest()
			{
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
			
				target->_currentCuffStatusFlag = 0;
				target->_currentEAStatusFlag = 0;
			
				unsigned long Current_cuffStatusBytes = 0x0400; //first expected value
				unsigned long Current_eaStatusBytes = 0x0000; //first expected value
				unsigned long statusBytes = 0x0400; 
				bool expected = true; 
				bool actual;
				bool cuffIsInflated;  

				actual = target->CheckStatusFlag(statusBytes, cuffIsInflated);
			
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
				Assert::AreEqual(Current_eaStatusBytes, target->_currentEAStatusFlag);

				//now assign the current values for checking
				Current_cuffStatusBytes = target->_currentCuffStatusFlag;
				Current_eaStatusBytes = target->_currentEAStatusFlag;

				//change alarm flags without changing cuff flags
				statusBytes = 0x0408;
				target->CheckStatusFlag(statusBytes, cuffIsInflated);
				Assert::AreEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
				Assert::AreNotEqual(Current_eaStatusBytes, target->_currentEAStatusFlag);
				Assert::IsFalse(cuffIsInflated);

				//reset back to normal position . we wont chek the status this time
				statusBytes = 0x0400;
				target->CheckStatusFlag(statusBytes, cuffIsInflated);
				Current_cuffStatusBytes = target->_currentCuffStatusFlag;
				Current_eaStatusBytes = target->_currentEAStatusFlag;
				Assert::IsFalse(cuffIsInflated);

				//now change cuff flags without changing alarm
				statusBytes = 0x0900;
				target->CheckStatusFlag(statusBytes, cuffIsInflated);
				Assert::AreNotEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
				Assert::AreEqual(Current_eaStatusBytes, target->_currentEAStatusFlag);
				Assert::IsTrue(cuffIsInflated); //0x900 means cuff is inflated so this should be true

			}


			/// <summary>
			///A test for GetConfigurationInfo
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetConfigurationInfoTest()
			{
				SetPath();
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				DalDeviceConfigUsageEnum deviceConfigItem = DalDeviceConfigUsageEnum::ModuleSerialNumber ; 
				DalDeviceConfigUsageStruct^  deviceConfigInfo = gcnew  DalDeviceConfigUsageStruct() ; 
				bool expected = true; 
				bool actual;
				actual = target->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
				Assert::AreEqual(expected, actual);
				Assert::IsNotNull(deviceConfigInfo->ModuleSerialNumber);
			}

			
			/// <summary>
			///A test for CheckIfDeviceIsConnected
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckIfDeviceIsConnectedTest()
			{
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				bool expected = true; 
				bool actual;
				actual = target->CheckIfDeviceIsConnected();
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for DalSimulationHandler Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalSimulationHandlerConstructorTest()
			{
				DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor());
				Assert::IsNotNull(target);
			}
	};
}
namespace TestDal {
    
}
