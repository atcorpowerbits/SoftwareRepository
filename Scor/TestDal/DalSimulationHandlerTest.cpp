
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
	/*public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void InstanceTest()
			{
				DalSimulationHandler_Accessor^  actual;
				actual = DalSimulationHandler_Accessor::Instance;
				Assert::IsNotNull(actual);	
			}*/

			/// <summary>
			///A test for StopCapture
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StopCaptureTest()
			{
				SetPath();

				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				
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
			public: [TestMethod]             
			[DeploymentItem(L"dal.dll")]
			void StartCaptureTest1()
			{
				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				
				bool expected = false; 
				bool actual;
				SetPath();
				actual = target->StartCapture(10,20);
				Assert::IsTrue(actual);
			}

			/// <summary>
			///A test for StartCapture
			///</summary>
				
			//TODO: This test will move to DalPWVSimulationHandler
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void StartCaptureTest()
	//		{
	//			SetPath();
	//			
	//			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
	//			int captureTime = 10; 
	//			int samplingRate = 256; 
	//			bool expected = true;
	//			bool actual;
	//			try
	//			{
	//				//target->dataBufferObj->GetAllValues(startIndex, endIndex);
	//				//Assert::AreEqual(-1, startIndex); //values will be -1 if no data has been put in buffer
	//				//Assert::AreEqual(-1, endIndex);

	//				actual = target->StartCapture(captureTime, samplingRate);
	//				Assert::AreEqual(expected, actual);

	//				//Deepak: recheck why this is giving -1
	//				//Threading::Thread::Sleep(3000); //Sleep to give the process enough time to add data to the buffer
	//				//target->StopCapture();
	//				//target->dataBufferObj->GetAllValues(startIndex, endIndex); //call to get the updated indices from buffer.
	//				//Assert::AreNotEqual(-1, endIndex); //This should not be true. If true it means that the buffer hassned been updated.
	//				//Assert::AreNotEqual(0, endIndex);
	//			}
	//			catch(ScorException ^ scorExObj)
	//			{
	//				Assert::Fail("Scor Exception thrown: " + scorExObj->ErrorMessageKey );
	//			}
	//		}

			/// <summary>
			///A test for SetPressure
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetPressureTest()
			{
				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				
				int newPressure = 0; 
				EM4CuffBoard cuffBoard = EM4CuffBoard(); 
				bool expected = true; 
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
				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 				
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

				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 				
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
				
				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 				

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
				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
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
				
				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				DalModule^ DalModuleAccessor = DalModule::Instance;
				DalModuleAccessor->SetStreamingMode(DalStreamingMode::Pwv);
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
				Assert::AreEqual(".\\\\simulation\\\\cuff_timer\\\\cuff_timer.dat", cuffTimerFilePath);
			}

			/// Will test for cPwaMode
			///A test for GetFileNameFromConfgAndOpen
			///</summary>
			//this test need to be made run indipendently.
			//TODO: This test will be moved to DalCPwcSimulationHandler; 
	//			
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
			//void GetFileNameFromConfgAndOpenForCPwaModeTest()
			//{
				
			//	SetPath();
			//	String^ path = Directory::GetCurrentDirectory(); 
			//	
			//	//Creating child class object as DalSimulationHandler class is abstuct class
			//	DalCPwaSimulationHandler_Accessor^  target = (gcnew DalCPwaSimulationHandler_Accessor()); 
			//	//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
			//	DalModule^ DalModuleAccessor = DalModule::Instance;
			//	DalModuleAccessor->SetStreamingMode(DalStreamingMode::cPwa);
			//	bool expected = true;
			//	bool actual;
			//	
			//	actual = target->GetFileNameFromConfgAndOpen();
			//	Assert::AreEqual(expected, actual);

			//	//check if the objects have been created
			//	Assert::IsNotNull(target->_cuffTimerSimulationFile);
			//	Assert::IsNotNull(target->_tonometerSimulationFile);
			//	
			//	String^ cuffTimerFilePath = target->_cuffTimerSimulationFile->filePath ;
			//	String^ tonometerSimFilePath = target->_tonometerSimulationFile->filePath ;
				
			//	//get the settings from config directly to test if the correct tono file is opened
			//	String^ tonoFileNameInConfig;
			//	CrxConfigManager ^configMgr = CrxConfigManager::Instance;
			//	configMgr->GetGeneralUserSettings();
			//	configMgr->GetPwaUserSettings();
			//	tonoFileNameInConfig = configMgr->PwaSettings->SimulationType+ ".dat";
			//	bool retValue = tonometerSimFilePath->Contains(tonoFileNameInConfig);
			//	Assert::IsTrue(retValue);

			//	//Now test if cuff file is opened properly
			//	Assert::AreEqual(".\\\\simulation\\\\cuff_timer\\\\cuff_timer.dat", cuffTimerFilePath);
			//}

			/// <summary>
			///A test for GetConnectionStatus
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetConnectionStatusTest()
			{
				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
				
				bool expected = true; 
				bool actual;
				actual = target->GetConnectionStatus();
				Assert::AreEqual(expected, actual);
				//This method will always return true for simulation mode
			}

			/// Check varios flag combinations to test the output
			///A test for GetConnectionStatus
			///</summary>
			//TODO: this test will be moved to some other file
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void CheckStatusFlagsChangedTest()
	//		{
	//			//Creating child class object as DalSimulationHandler class is abstuct class
	//			DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
	//			//DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor()); 
	//			
	//			target->_currentCuffStatusFlag = 0;
	//			target->_currentAlarmStatusFlag  = 0;
	//		
	//			unsigned long Current_cuffStatusBytes = 0x0400; //first expected value
	//			unsigned long Current_eaStatusBytes = 0x0000; //first expected value
	//			unsigned long statusBytes = 0x0400; 
	//			bool expected = true; 
	//			bool actual;
	//			bool cuffIsInflated;  

	//			actual = target->CheckStatusFlagsChanged(statusBytes);
	//		
	//			Assert::AreEqual(expected, actual);
	//			//Assert::AreEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
	//			Assert::AreEqual(Current_eaStatusBytes, target->_currentAlarmStatusFlag );

	//			//now assign the current values for checking
	//			Current_cuffStatusBytes = target->_currentCuffStatusFlag;
	//			Current_eaStatusBytes = target->_currentAlarmStatusFlag ;

	//			//change alarm flags without changing cuff flags
	//			statusBytes = 0x0408;
	//			Current_eaStatusBytes = 0x0080; 
	//			target->CheckStatusFlagsChanged(statusBytes);
	//			Assert::AreEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
	//			Assert::AreNotEqual(Current_eaStatusBytes, target->_currentAlarmStatusFlag );
	//			Assert::IsFalse(cuffIsInflated);

	//			//reset back to normal position . we wont chek the status this time
	//			statusBytes = 0x0400;
	//			target->CheckStatusFlagsChanged(statusBytes);
	//			Current_cuffStatusBytes = target->_currentCuffStatusFlag;
	//			Current_eaStatusBytes = target->_currentAlarmStatusFlag ;
	//			Assert::IsFalse(cuffIsInflated);

	//			//now change cuff flags without changing alarm
	//			statusBytes = 0x1000;
	//			//Current_eaStatusBytes = 0x0000; 
	//			target->CheckStatusFlagsChanged(statusBytes);
	//			Assert::AreNotEqual(Current_cuffStatusBytes, target->_currentCuffStatusFlag);
	//			Assert::AreEqual(Current_eaStatusBytes, target->_currentAlarmStatusFlag );
	//			Assert::IsTrue(cuffIsInflated); //0x900 means cuff is inflated so this should be true
	//		}

			/// <summary>
			///A test for GetConfigurationInfo
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetConfigurationInfoTest()
			{
				SetPath();
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
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
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
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
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for StartBP
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StartBPTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DalNIBPMode nibpMode = DalNIBPMode(); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->StartBP(nibpMode);
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for StartBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StartBPTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DalNIBPMode nibpMode = DalNIBPMode(); // TODO: Initialize to an appropriate value
			unsigned short initialPressure = 0; // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->StartBP(nibpMode, initialPressure);
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for FinishBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void FinishBPTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->FinishBP();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
internal: DalSimulationHandler_Accessor^  CreateDalSimulationHandler_Accessor()
		  {
			  // TODO: Instantiate an appropriate concrete class.
			  DalSimulationHandler_Accessor^  target = nullptr;
			  return target;
		  }
		  /// <summary>
		  ///A test for AbortBP
		  ///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void AbortBPTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->AbortBP();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for TestDate
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void TestDateTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DateTime expected = DateTime(); // TODO: Initialize to an appropriate value
			DateTime actual;
			actual = target->TestDate();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for TestDate
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void TestDateTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DateTime data = DateTime(); // TODO: Initialize to an appropriate value
			target->TestDate(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for SystemConfigurationId
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SystemConfigurationIdTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned short expected = 0; // TODO: Initialize to an appropriate value
			unsigned short actual;
			actual = target->SystemConfigurationId();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SystemConfigurationId
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SystemConfigurationIdTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned short data = 0; // TODO: Initialize to an appropriate value
			target->SystemConfigurationId(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for SystemConfigurationChangeDate
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SystemConfigurationChangeDateTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DateTime expected = DateTime(); // TODO: Initialize to an appropriate value
			DateTime actual;
			actual = target->SystemConfigurationChangeDate();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SystemConfigurationChangeDate
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SystemConfigurationChangeDateTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DateTime data = DateTime(); // TODO: Initialize to an appropriate value
			target->SystemConfigurationChangeDate(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for SerialNumberSuntechPcb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SerialNumberSuntechPcbTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			actual = target->SerialNumberSuntechPcb();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SerialNumberSuntechPcb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SerialNumberSuntechPcbTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  data = System::String::Empty; // TODO: Initialize to an appropriate value
			target->SerialNumberSuntechPcb(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for SerialNumberMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SerialNumberMpbTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  data = System::String::Empty; // TODO: Initialize to an appropriate value
			target->SerialNumberMpb(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for SerialNumberMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SerialNumberMpbTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			actual = target->SerialNumberMpb();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SerialNumberEm4
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SerialNumberEm4Test1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  data = System::String::Empty; // TODO: Initialize to an appropriate value
			target->SerialNumberEm4(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for SerialNumberEm4
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SerialNumberEm4Test()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			actual = target->SerialNumberEm4();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SafetyFirmwareVersionSuntech
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SafetyFirmwareVersionSuntechTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			actual = target->SafetyFirmwareVersionSuntech();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SafetyFirmwareVersionSuntech
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SafetyFirmwareVersionSuntechTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  data = System::String::Empty; // TODO: Initialize to an appropriate value
			target->SafetyFirmwareVersionSuntech(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for ProcessorFirmwareVersionMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessorFirmwareVersionMpbTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  data = System::String::Empty; // TODO: Initialize to an appropriate value
			target->ProcessorFirmwareVersionMpb(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for ProcessorFirmwareVersionMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessorFirmwareVersionMpbTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			actual = target->ProcessorFirmwareVersionMpb();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for PldSafetyFirmwareVersionMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void PldSafetyFirmwareVersionMpbTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			actual = target->PldSafetyFirmwareVersionMpb();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for PldSafetyFirmwareVersionMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void PldSafetyFirmwareVersionMpbTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  data = System::String::Empty; // TODO: Initialize to an appropriate value
			target->PldSafetyFirmwareVersionMpb(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for NumberofPWVmeasurements
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void NumberofPWVmeasurementsTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned int expected = 0; // TODO: Initialize to an appropriate value
			unsigned int actual;
			actual = target->NumberofPWVmeasurements();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for NumberofPWVmeasurements
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void NumberofPWVmeasurementsTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned int data = 0; // TODO: Initialize to an appropriate value
			target->NumberofPWVmeasurements(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for NumberofPWAtonometermeasurements
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void NumberofPWAtonometermeasurementsTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned int expected = 0; // TODO: Initialize to an appropriate value
			unsigned int actual;
			actual = target->NumberofPWAtonometermeasurements();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for NumberofPWAtonometermeasurements
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void NumberofPWAtonometermeasurementsTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned int data = 0; // TODO: Initialize to an appropriate value
			target->NumberofPWAtonometermeasurements(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for NumberofPWAcuffmeasurements
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void NumberofPWAcuffmeasurementsTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned int expected = 0; // TODO: Initialize to an appropriate value
			unsigned int actual;
			actual = target->NumberofPWAcuffmeasurements();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for NumberofPWAcuffmeasurements
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void NumberofPWAcuffmeasurementsTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned int data = 0; // TODO: Initialize to an appropriate value
			target->NumberofPWAcuffmeasurements(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for NumberOfNibpMeasurements
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void NumberOfNibpMeasurementsTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned int data = 0; // TODO: Initialize to an appropriate value
			target->NumberOfNibpMeasurements(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for NumberOfNibpMeasurements
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void NumberOfNibpMeasurementsTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned int expected = 0; // TODO: Initialize to an appropriate value
			unsigned int actual;
			actual = target->NumberOfNibpMeasurements();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for HWConfigurationMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void HWConfigurationMpbTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned short data = 0; // TODO: Initialize to an appropriate value
			target->HWConfigurationMpb(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for HWConfigurationMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void HWConfigurationMpbTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			unsigned short expected = 0; // TODO: Initialize to an appropriate value
			unsigned short actual;
			actual = target->HWConfigurationMpb();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for CalibrationDateSuntech
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CalibrationDateSuntechTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DateTime data = DateTime(); // TODO: Initialize to an appropriate value
			target->CalibrationDateSuntech(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for CalibrationDateSuntech
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CalibrationDateSuntechTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DateTime expected = DateTime(); // TODO: Initialize to an appropriate value
			DateTime actual;
			actual = target->CalibrationDateSuntech();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for CalibrationDateMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CalibrationDateMpbTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DateTime expected = DateTime(); // TODO: Initialize to an appropriate value
			DateTime actual;
			actual = target->CalibrationDateMpb();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for CalibrationDateMpb
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CalibrationDateMpbTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			DateTime data = DateTime(); // TODO: Initialize to an appropriate value
			target->CalibrationDateMpb(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for BPFirmwareVersionSuntech
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BPFirmwareVersionSuntechTest1()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  data = System::String::Empty; // TODO: Initialize to an appropriate value
			target->BPFirmwareVersionSuntech(data);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for BPFirmwareVersionSuntech
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void BPFirmwareVersionSuntechTest()
		{
			PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
			DalSimulationHandler_Accessor^  target = (gcnew DalSimulationHandler_Accessor(param0)); // TODO: Initialize to an appropriate value
			String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
			String^  actual;
			actual = target->BPFirmwareVersionSuntech();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
};
}
namespace TestDal {
    
}
