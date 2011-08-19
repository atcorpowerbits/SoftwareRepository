
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace AtCor::Scor::CrossCutting;
using namespace System::IO;
namespace TestDal {
    using namespace System;
    ref class DalStatusHandlerTest;
    
    
    /// <summary>
///This is a test class for DalStatusHandlerTest and is intended
///to contain all DalStatusHandlerTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalStatusHandlerTest
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

	private: String^ _currDir;
	public:	static bool eventRaised = false;
	public: static DalUnusedStatusFlagBit unusedFlagName;
	public: static DalErrorAlarmStatusFlag alarmStatusFlag;
	public: static String^ alarmSourceName;
	public: static DalCuffStateFlags cufffStateValue;
	public: static DalTonometerState tonoStateValue;




			 static void SetPath()
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

			 static void MyUnusedBitEventTester(Object ^sender, DalUnusedStatusFlagEventArgs  ^args)
			{
				eventRaised = true;
				unusedFlagName = args->UnusedStatusFlagChanged;
			}

			 static void MyAlarmEventRaisedTester(Object ^sender, DalModuleErrorAlarmEventArgs ^ args)
			 {
				 eventRaised = true;
				alarmStatusFlag =  args->ErrorAlarmStatus;
				alarmSourceName =  args->AlarmSourceName; 
			 }

			static void MyCuffStatusEventTester(Object ^sender, DalCuffStatusEventArgs ^ args)
			{
				eventRaised = true;
				cufffStateValue = args->CuffStateFlag ;
			}

			static void MyTonoStatusEventTester(Object ^sender, DalTonometerStatusEventArgs ^ args)
			{
				eventRaised = true;
				tonoStateValue = args->TonometerStateFlag ;
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
						//Deepak: Since this test verifies static values it is bound to fil
			/// <summary>
			///A test for DalStatusHandler Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalStatusHandlerConstructorTest()
			{
				DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor());
				Assert::IsNotNull(target);
				target->ResetAllStaticMembers();
				Assert::AreEqual((unsigned long)0xFFFF, (unsigned long)target->_currentCuffStatusFlag, "Run this test independently");
				Assert::AreEqual((unsigned long)0, (unsigned long)target->_currentAlarmStatusFlag  , "Run this test independently");
				Assert::AreEqual((unsigned long)0, (unsigned long)target->_currentEASourceFlag, "Run this test independently");
				Assert::AreEqual((unsigned long)0, (unsigned long)target->_currentUnusedStatusFlag , "Run this test independently");
				Assert::IsNull(target->_savedDataFilePath, "Run this test independently");
			}
			/// <summary>
			///A test for TranslateAlarmStatusBits 
			///</summary>
		public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void TranslateAlarmStatusBitsTest()
			{
				unsigned long statusFlags;
					
				//no error or alarm
				statusFlags = 0x0000 ;
				DalErrorAlarmStatusFlag expected = DalErrorAlarmStatusFlag::ActiveStatus; 
				DalErrorAlarmStatusFlag actual;
				actual = DalStatusHandler_Accessor::TranslateAlarmStatusBits (statusFlags);
				Assert::AreEqual(expected, actual);

				//alarm status
				statusFlags = 0x0008 ;
				expected = DalErrorAlarmStatusFlag::RecoverableStatus; 
				actual = DalStatusHandler_Accessor::TranslateAlarmStatusBits (statusFlags);
				Assert::AreEqual(expected, actual);

				
			}
	//		/// <summary>
	//		///A test for TranslateCuffStatusBits
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void TranslateCuffStatusBitsTest()
	//		{
	//			unsigned long cuffStatusFlags = 0 ; 
	//			
	//			// cuff inflating status
	//			//cuffStatusFlags = 0x0400 ;//old value
	//			cuffStatusFlags = 0x0100 ;
	//			DalCuffStateFlags expected = DalCuffStateFlags::CUFF_STATE_INFLATING ; 
	//			DalCuffStateFlags actual;
	//			actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
	//			Assert::AreEqual(expected, actual);

	//			// cuff inflated status
	//			//cuffStatusFlags = 0x0900 ;
	//			cuffStatusFlags = 0x0A00 ;
	//			expected = DalCuffStateFlags::CUFF_STATE_INFLATED ; 
	//			actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
	//			Assert::AreEqual(expected, actual);

	//			// cuff deflating status
	//			//cuffStatusFlags = 0x0200 ;
	//			cuffStatusFlags = 0x0300;
	//			expected = DalCuffStateFlags::CUFF_STATE_DEFLATING  ; 
	//			actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
	//			Assert::AreEqual(expected, actual);

	//			// cuff deflated status
	//			//cuffStatusFlags = 0x0100 ;
	//			cuffStatusFlags = 0x0000 ;
	//			expected = DalCuffStateFlags::CUFF_STATE_DEFLATED ; 
	//			actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
	//			Assert::AreEqual(expected, actual);

	//			// cuff disconnected status
	//			cuffStatusFlags = 0x2000 ; //same as before
	//			expected = DalCuffStateFlags::CUFF_STATE_DISCONNECTED  ; 
	//			actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
	//			Assert::AreEqual(expected, actual);
	//		}

			/// <summary>
			///A test for TranslateCuffStatusBits
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void TranslateCuffStatusBitsTest()
			{
				unsigned long cuffStatusFlags = 0 ; 
				
				// cuff inflating status
				//cuffStatusFlags = 0x0400 ;//old value
				cuffStatusFlags = 0x0100 ;
				DalCuffStateFlags expected = DalCuffStateFlags::CUFF_STATE_INFLATING ; 
				DalCuffStateFlags actual;
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
				Assert::AreEqual(expected, actual);

				// cuff inflated status
				cuffStatusFlags = 0x0200 ;
				expected = DalCuffStateFlags::CUFF_STATE_INFLATED ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
				Assert::AreEqual(expected, actual);

				// cuff deflating status
				cuffStatusFlags = 0x0300;
				expected = DalCuffStateFlags::CUFF_STATE_DEFLATING  ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
				Assert::AreEqual(expected, actual);

				// cuff deflated status
				cuffStatusFlags = 0x0000 ;
				expected = DalCuffStateFlags::CUFF_STATE_DEFLATED ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
				Assert::AreEqual(expected, actual);
			}


			///Test Cuff status bits for the new values of cuff flags 
			//noted on 27th July
			//TranslateCuffStatusBitsTest may be outdated and need to be modified
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void TranslateCuffStatusBitsForAllInflatingConditionsTest()
			{
				unsigned long cuffStatusFlags = 0 ; 
				DalCuffStateFlags expected;
				DalCuffStateFlags actual;
				
				// cuff inflating status
				cuffStatusFlags = 0x2100 & (unsigned long)0x0700 ;
				//Use the actual status flag we obtained and extract the cuff status only
				 expected = DalCuffStateFlags::CUFF_STATE_INFLATING ; 
				
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
				Assert::AreEqual(expected, actual);

				// cuff inflating status
				cuffStatusFlags = 0x0100 & (unsigned long)0x0700;
				 expected = DalCuffStateFlags::CUFF_STATE_INFLATING ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
				Assert::AreEqual(expected, actual);

				// cuff inflating status
				cuffStatusFlags = 0x0900 & (unsigned long)0x0700 ;
				expected = DalCuffStateFlags::CUFF_STATE_INFLATING ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
				Assert::AreEqual(expected, actual);
			}


			//negative test
			///Pas a non acceptable value. should throw an exception
			///A test for TranslateCuffStatusBits
			///</summary>
			public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void TranslateCuffStatusBitsTestNeg()
			{
				SetPath();
				unsigned long cuffStatusFlags = 0 ; 
				bool exceptionRaised = false;
				
				try
				{
					cuffStatusFlags = 0x0001 ;
					DalCuffStateFlags actual;
					actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
					Assert::IsNull(actual);
				}
				catch(ScorException^)
				{
					exceptionRaised = true;
				}
				Assert::IsTrue(exceptionRaised);
			}

			///Usae this test to check any previusly uninncluded bit combinations
			///A test for TranslateCuffStatusBits
			///</summary>
			public: 
			[DeploymentItem(L"dal.dll")]
			void TranslateCuffStatusBitsTestNewFlag()
			{
				SetPath();
				unsigned long cuffStatusFlags = 0 ; 
				bool exceptionRaised = false;
				
				try
				{
					cuffStatusFlags = 0x2300 ; //New flag not previously added to the enum
					DalCuffStateFlags actual;
					DalCuffStateFlags expected = DalCuffStateFlags::CUFF_STATE_DEFLATING  ; 
					actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
					Assert::IsNotNull(actual);
					Assert::AreEqual(expected, actual);
				}
				catch(ScorException^)
				{
					exceptionRaised = true;
				}
				Assert::IsFalse(exceptionRaised); //exception should not be raised once this flag is added
			}

			//Error flag has been removed
	//		/// <summary>
	//		///A test for MapErrorSourceToString
	//		///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void MapErrorSourceToStringTest()
	//		{
	//			//dual sensor
	//			unsigned long sourceFlags = 0x20; 
	//			String^  expected = DalAlarmSource::DualSensors.ToString();
	//			String^  actual;
	//			actual = DalStatusHandler_Accessor::MapErrorSourceToString(sourceFlags);
	//			Assert::AreEqual(expected, actual);

	//			//cuff leak
	//			sourceFlags = 0x0008; 
	//			expected = DalAlarmSource::CuffLeak.ToString();
	//			actual = DalStatusHandler_Accessor::MapErrorSourceToString(sourceFlags);
	//			Assert::AreEqual(expected, actual);
	//		}

			//obsolete
		/*	/// <summary>
			///A test for MapAlarmSourceToString
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void MapAlarmSourceToStringTest()
			{
				DalStatusHandler_Accessor::_currentEASourceFlag = 0x10000 ;
				DalStatusHandler_Accessor::_currentAlarmStatusFlag  = 0x0408 ;
				unsigned long sourceFlags = 0x10000; 
				String^  expected = DalAlarmSource::OverPressure.ToString() ; 
				String^  actual;
				actual = DalStatusHandler_Accessor::MapAlarmSourceToString((sourceFlags >> 16) & 0x0000FFFF);
				Assert::AreEqual(expected, actual);

				sourceFlags = 0x40000 ; 
				expected = DalAlarmSource::InflatedOverTime.ToString() ; 
				actual = DalStatusHandler_Accessor::MapAlarmSourceToString((sourceFlags >> 16) & 0x0000FFFF);
				Assert::AreEqual(expected, actual);
			}*/
			/// <summary>
			///A test for GetAlarmSource
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetAlarmSourceTest()
			{
				DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
				target->_currentEASourceFlag =0x10000;
				String^  expected = DalAlarmSource::OverPressure.ToString();
		
				String^  actual;
				actual = target->GetAlarmSource();
				Assert::AreEqual(expected, actual);

				target->_currentEASourceFlag =0x20;
				expected = DalAlarmSource::DualSensors.ToString();
		
				actual = target->GetAlarmSource();
				Assert::AreEqual(expected, actual);
			
			}
			/// <summary>
			///A test for CheckAlarmStatusFlagChanged
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckAlarmStatusFlagChangedTest()
			{
				DalStatusHandler_Accessor::_currentAlarmStatusFlag  = 0x0400;
				unsigned long newEAStatusFlag = 0x0408; 
				bool expected = true; 
				bool actual;
				actual = DalStatusHandler_Accessor::CheckAlarmStatusFlagChanged(newEAStatusFlag);
				Assert::AreEqual(expected, actual);

				//call again to chek if the status is the same or not
				expected = false; 
				actual = DalStatusHandler_Accessor::CheckAlarmStatusFlagChanged(newEAStatusFlag);
				Assert::AreEqual(expected, actual);
				
			}
			/// <summary>
			///A test for CheckCuffStatusFlagsChanged
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckCuffStatusFlagsChangedTest()
			{
				DalStatusHandler_Accessor::_currentCuffStatusFlag = 0x0400;
				unsigned long newCuffStatusFlags = 0x900; 
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				actual = DalStatusHandler_Accessor::CheckCuffStatusFlagsChanged(newCuffStatusFlags);
				Assert::AreEqual(expected, actual);
				
				//calling this again with the same values shoud give false
				expected = false;
				actual = DalStatusHandler_Accessor::CheckCuffStatusFlagsChanged(newCuffStatusFlags);
				Assert::AreEqual(expected, actual);
			}


			/// <summary>
			///A test for GetSavedFileName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetSavedFileNameTest1()
			{
				SetPath();
				DalStatusHandler_Accessor^  target = gcnew DalStatusHandler_Accessor(); 
				cli::array< unsigned short >^  tonometerData = gcnew array< unsigned short > {0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6}; 
				cli::array< unsigned short >^  cuffPulse = gcnew array< unsigned short > {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6}; 
				unsigned short bufferSize = 6; 
			
				//create a filestring with a wildcard character. Remove the seconds since it is not always reliable
				DateTime currentDateTime;
				currentDateTime = System::DateTime::Now;
				String^ tempCapture = "capture_";
				String  ^ currentDateTimeStr = currentDateTime.ToString("yyyyMMMddHHmm");
				currentDateTimeStr = tempCapture+ currentDateTimeStr ;


				target->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
				
				String^  expected = System::String::Empty; 
				String^  actual;
				actual = target->GetSavedFileName();
				Assert::IsTrue(actual->Contains(currentDateTimeStr));
			}
			
			
			
			/// <summary>
			///A test for SaveCaptureData
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SaveCaptureDataTest1()
			{
				SetPath();
				DalStatusHandler_Accessor^  target = gcnew DalStatusHandler_Accessor(); 
				cli::array< unsigned short >^  tonometerData = gcnew array< unsigned short > {0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6}; 
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

				Assert::IsFalse(excepRaised);
				

			}

			/// Negative test case. calling the GetSavedFileName without first calling the  SaveCapturedata
			///A test for GetSavedFileName
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GetSavedFileNameTest()
		{
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
			String^  expected = System::String::Empty; 
			String^  actual;
			actual = target->GetSavedFileName();
			Assert::AreEqual(expected, actual);
			
		}
		/// <summary>
		///A test for SaveCaptureData
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SaveCaptureDataTest()
		{
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); // TODO: Initialize to an appropriate value
			cli::array< unsigned short >^  tonometerData = nullptr; // TODO: Initialize to an appropriate value
			cli::array< unsigned short >^  cuffPulse = nullptr; // TODO: Initialize to an appropriate value
			unsigned short bufferSize = 0; // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->SaveCaptureData(tonometerData, cuffPulse, bufferSize);
			Assert::AreEqual(expected, actual);
			
		}
		/// <summary>
		///A test for ProcessUnusedBitsStatusFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessUnusedBitsStatusFlagTest()
		{
			SetPath();
			/*DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
			dalModule->SetDeviceStrategy("Simulation");*/
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
			target->_newUnusedStatusBytes = 0x8000; //BPRR
			DalUnusedStatusFlagBit expected = DalUnusedStatusFlagBit::UnusedBitBprr ;
			eventRaised = false;
			//Register an event handler
			DalEventContainer::Instance->OnDalUnusedStatusFlagChangedEvent += gcnew DalUnusedStatusFlagChangedEventHandler(&TestDal::DalStatusHandlerTest::MyUnusedBitEventTester);
			

			target->ProcessUnusedBitsStatusFlag(target->_newUnusedStatusBytes);
			Assert::AreEqual(target->_currentUnusedStatusFlag, 	target->_newUnusedStatusBytes);
			Assert::IsTrue(eventRaised);
			Assert::AreEqual(expected, unusedFlagName);
		}

		/// <summary>
		///A test for ProcessTonoStatusFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessTonoStatusFlagTest()
		{
			SetPath();
			DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
			dalModule->SetDeviceStrategy("Simulation");
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
			target->ResetAllStaticMembers();

			//reset the event raised flag
			eventRaised = false;

			//register the event handler
			DalEventContainer::Instance->OnDalTonometerStatusEvent += gcnew DalTonometerStatusEventHandler(&TestDal::DalStatusHandlerTest::MyTonoStatusEventTester);

			target->ProcessTonoStatusFlag();
			Assert::IsFalse(eventRaised);

			eventRaised = false; //reset

			//Now change the value of the split new flag values before calling them
			target->_newTonoStatusBytes = 0x4000;//Tonometer not connected
			target->ProcessTonoStatusFlag();
			Assert::IsTrue(eventRaised);
			Assert::AreEqual(DalTonometerState::Disconnected , tonoStateValue);
		
			eventRaised = false; //reset
			//same flag again. event should NOT be raised
			target->_newTonoStatusBytes = 0x4000;//Tonometer not connected
			target->ProcessTonoStatusFlag();
			Assert::IsFalse(eventRaised);

			//now change the flag
			eventRaised = false; //reset
			target->_newTonoStatusBytes = 0x0000;
			target->ProcessTonoStatusFlag();
			Assert::IsTrue(eventRaised);
			Assert::AreEqual(DalTonometerState::Connected , tonoStateValue);
		}
		/// <summary>
		///A test for ProcessStopButtonBitMask
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessStopButtonBitMaskTest()
		{

			SetPath();
			DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
			dalModule->SetDeviceStrategy("Simulation");
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 

			//initialize a handler for the event that will be raised
			DalEventContainer::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalStatusHandlerTest::MyAlarmEventRaisedTester);

			// reset the bit to zero. Event SHOULD NOT be raised.
			eventRaised = false; //reset the flag
			target->_newStopButtonStatusBytes = 0x0000; //SRB bit is reset
			target->ProcessStopButtonBitMask();
			Assert::IsFalse(eventRaised);

			eventRaised = false; //reset the flag
			String^ expectedSourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::StopButtonPressed, DalFormatterStrings_Accessor::PrintEnumName);
					
			target->_newStopButtonStatusBytes = 0x0002; //SRB bit is set
			target->ProcessStopButtonBitMask();
			Assert::IsTrue(eventRaised);
			Assert::AreEqual(expectedSourceName,  alarmSourceName);
			Assert::AreEqual( DalErrorAlarmStatusFlag::StopButtonPressed, alarmStatusFlag);

			//Again reset the bit to zero. Event SHOULD NOT be raised.
			eventRaised = false; //reset the flag
			target->_newStopButtonStatusBytes = 0x0000; //SRB bit is reset
			target->ProcessStopButtonBitMask();
			Assert::IsFalse(eventRaised);
		}
		/// This test checks if the flags are split properly 
		///A test for ProcessStatusFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessStatusFlagTest()
		{
			SetPath();
			DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
			dalModule->SetDeviceStrategy();
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
			unsigned long statusBytes = 0xD0FF; //valid cuff flag
			bool actual = false;
			bool exceptionThrown = false;
			try
			{
				actual = DalStatusHandler_Accessor::ProcessStatusFlag(statusBytes);
			}
			catch(ScorException^ ex)
			{
				ex; //Just keep it since we may need it again
				//do nothing. this exception is expcectd since the flags are not correct
				//we just want to test if the flags have been split properly
				exceptionThrown = true;
			}
			
			Assert::IsTrue(exceptionThrown);
			Assert::AreEqual( statusBytes, target->_currentStatusFlag);
			Assert::AreEqual((unsigned long)0x0000, (target->_currentCuffStatusFlag) );
			Assert::AreEqual((unsigned long)0x5000, (target->_currentTonoStatusFlag));
			Assert::AreEqual((unsigned long)0x0008, (target->_currentAlarmStatusFlag)); //AS bit has changed
		}
		/// <summary>
		///A test for ProcessPowerUpBitMask
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessPowerUpBitMaskTest()
		{
				SetPath();
			DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
			dalModule->SetDeviceStrategy("Simulation");
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 

			//initialize a handler for the event that will be raised
			DalEventContainer::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalStatusHandlerTest::MyAlarmEventRaisedTester);

			// reset the bit to zero. Event SHOULD NOT be raised.
			eventRaised = false; //reset the flag
			target->_newPowerUpStatusBytes = 0x0000; //PU bit is reset
			target->ProcessPowerUpBitMask();
			Assert::IsFalse(eventRaised);

			eventRaised = false; //reset the flag
			String^ expectedSourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::PowerUpEvent, DalFormatterStrings_Accessor::PrintEnumName);
					
			target->_newPowerUpStatusBytes = 0x0001; //PU bit is set
			target->ProcessPowerUpBitMask();
			Assert::IsTrue(eventRaised);
			Assert::AreEqual(expectedSourceName,  alarmSourceName);
			Assert::AreEqual( DalErrorAlarmStatusFlag::PowerUpEvent, alarmStatusFlag);

			//Again reset the bit to zero. Event SHOULD NOT be raised.
			eventRaised = false; //reset the flag
			target->_newPowerUpStatusBytes = 0x0000; //PU bit is reset
			target->ProcessPowerUpBitMask();
			Assert::IsFalse(eventRaised);
		}
//		/// <summary>
//		///A test for ProcessCuffStatusFlag
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void ProcessCuffStatusFlagTest()
//		{
//			SetPath();
//			DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
//			dalModule->SetDeviceStrategy("Simulation");
//			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
//			//reset the event raised flaf
//			eventRaised = false;
//
//			//register the event handler
//			DalEventContainer::Instance->OnDalCuffStatusEvent += gcnew DalCuffStatusEventHandler(&TestDal::DalStatusHandlerTest::MyCuffStatusEventTester );
//
//
//			target->_currentCuffStatusFlag =  0xFFFF;  //clear the current flag
//
//			//Now change the value of the split new flag values before calling them
//			target->_newCuffStatusBytes  = 0x2000;//Disconnected
//			target->ProcessCuffStatusFlag();
//			Assert::IsTrue(eventRaised);
//			Assert::AreEqual(DalCuffStateFlags::CUFF_STATE_DISCONNECTED , cufffStateValue);
//			//now change the flag to another value and test
//
//			//raise the SAME event 
//			eventRaised = false;
//			target->_newCuffStatusBytes = 0x2000;//Disconnected
//			target->ProcessCuffStatusFlag();
//			Assert::IsFalse(eventRaised);
//
//			//raise another event
//			eventRaised = false; //reset
//			target->_newCuffStatusBytes = 0x0000;//CUFF_DEFLATED_STATUS_BITS
//			target->ProcessCuffStatusFlag();
//			Assert::IsTrue(eventRaised);
//			Assert::AreEqual(DalCuffStateFlags::CUFF_STATE_DEFLATED , cufffStateValue);
//
//			bool exceptionRaised = false;
//			//now test an incorrect value
//			try
//			{
//				//raise another event
//				eventRaised = false; //reset
//				target->_newCuffStatusBytes = 0x0010;//an invalid value
//				target->ProcessCuffStatusFlag();
//				Assert::IsFalse(eventRaised);
//			
//			}
//			catch(ScorException^ )
//			{
//				exceptionRaised = true;
//			}
//			
//			Assert::IsTrue(exceptionRaised); //exception should be raised.
//		}

		/// <summary>
		///A test for ProcessCuffStatusFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessCuffStatusFlagTest()
		{
			SetPath();
			DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
			dalModule->SetDeviceStrategy("Simulation");
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
			//reset the event raised flaf
			eventRaised = false;

			//register the event handler
			DalEventContainer::Instance->OnDalCuffStatusEvent += gcnew DalCuffStatusEventHandler(&TestDal::DalStatusHandlerTest::MyCuffStatusEventTester );


			target->_currentCuffStatusFlag =  0xFFFF;  //clear the current flag

			//Now change the value of the split new flag values before calling them
			target->_newCuffStatusBytes  = 0x0100;//Inflating
			target->ProcessCuffStatusFlag();
			Assert::IsTrue(eventRaised);
			Assert::AreEqual(DalCuffStateFlags::CUFF_STATE_INFLATING , cufffStateValue);
			//now change the flag to another value and test

			//raise the SAME event 
			eventRaised = false;
			target->_newCuffStatusBytes = 0x0100;//Inflating
			target->ProcessCuffStatusFlag();
			Assert::IsFalse(eventRaised);

			//raise another event
			eventRaised = false; //reset
			target->_newCuffStatusBytes = 0x0000;//CUFF_DEFLATED_STATUS_BITS
			target->ProcessCuffStatusFlag();
			Assert::IsTrue(eventRaised);
			Assert::AreEqual(DalCuffStateFlags::CUFF_STATE_DEFLATED , cufffStateValue);

			bool exceptionRaised = false;
			//now test an incorrect value
			try
			{
				//raise another event
				eventRaised = false; //reset
				target->_newCuffStatusBytes = 0x0010;//an invalid value
				target->ProcessCuffStatusFlag();
				Assert::IsFalse(eventRaised);
			
			}
			catch(ScorException^ )
			{
				exceptionRaised = true;
			}
			
			Assert::IsTrue(exceptionRaised); //exception should be raised.
		}

		/// <summary>
		///A test for ProcessAlarmStatusFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessAlarmStatusFlagTest()
		{
			
				SetPath();
				DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
				dalModule->SetDeviceStrategy("Simulation");
				DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
				target->ResetAllStaticMembers();
				
				//first give a "clear flag
				unsigned long statusBytes = 0x0; 
				/*target->ProcessStatusFlag(statusBytes);
				Assert::AreEqual((unsigned long)0x0, (unsigned long)target->_currentAlarmStatusFlag);*/

				//now raise an alarm
				statusBytes = 0x0008;
				//set the current value of the Alarm source to a known value
				target->_currentEASourceFlag = 0x20 ; //Dual sensors
				//set the eventraised indicator to false
				eventRaised = false;
				//Register the event handler before calling
				DalEventContainer::Instance->OnDalModuleErrorAlarmEvent  += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalStatusHandlerTest::MyAlarmEventRaisedTester);
		
				target->ProcessStatusFlag(statusBytes);
				Assert::AreEqual((unsigned long)0x0008, (unsigned long)target->_currentAlarmStatusFlag);
				Assert::IsTrue(eventRaised);
				Assert::AreEqual(DalErrorAlarmStatusFlag::RecoverableStatus , alarmStatusFlag);
				Assert::AreEqual("DualSensors", alarmSourceName);
		}

		/// The alarm b
		///A test for ProcessAlarmStatusFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ProcessAlarmStatusFlagOnlyWhenAlarmBitIsSetTest()
		{
			
				SetPath();
				DalModule_Accessor^ dalModule = gcnew DalModule_Accessor();
				dalModule->SetDeviceStrategy("Simulation");
				DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
				target->ResetAllStaticMembers();
				
				//first give a "clear flag
				unsigned long statusBytes = 0x0; 
				/*target->ProcessStatusFlag(statusBytes);
				Assert::AreEqual((unsigned long)0x0, (unsigned long)target->_currentAlarmStatusFlag);*/

				//now raise an alarm
				statusBytes = 0x0008;
				//set the current value of the Alarm source to a known value
				target->_currentEASourceFlag = 0x20 ; //Dual sensors
				//set the eventraised indicator to false
				eventRaised = false;
				//Register the event handler before calling
				DalEventContainer::Instance->OnDalModuleErrorAlarmEvent  += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalStatusHandlerTest::MyAlarmEventRaisedTester);
		
				target->ProcessStatusFlag(statusBytes);
				Assert::AreEqual((unsigned long)0x0008, (unsigned long)target->_currentAlarmStatusFlag);
				Assert::IsTrue(eventRaised);
				
				//now when the alarm bit is reset, an event should not be raised
				eventRaised = false; //reset
				statusBytes = 0x0000; //reset the alarm bit
				target->ProcessStatusFlag(statusBytes);
				Assert::IsFalse(eventRaised);
		}


		/// <summary>
		///A test for ResetAllStaticMembers
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ResetAllStaticMembersTest()
		{
			DalStatusHandler_Accessor^ target = gcnew DalStatusHandler_Accessor();
	
			//Assign some values to the current flags. just to test

			target->_currentCuffStatusFlag = 0x1234;
			target->_currentAlarmStatusFlag = 0x1234;
			target->_currentEASourceFlag = 0x1234;
			target->_currentStatusFlag = 0x1234;
			target->_currentTonoStatusFlag = 0x1234;
			target->_currentUnusedStatusFlag = 0x1234;
			
			DalStatusHandler_Accessor::ResetAllStaticMembers();
			Assert::AreEqual((unsigned long)0xFFFF, target->_currentCuffStatusFlag);
			Assert::AreEqual((unsigned long)0x0, (target->_currentAlarmStatusFlag));
			Assert::AreEqual((unsigned long)0, target->_currentEASourceFlag);
			Assert::AreEqual((unsigned long)0, target->_currentStatusFlag);
			Assert::AreEqual((unsigned long)0xFFFF, target->_currentTonoStatusFlag);
			Assert::AreEqual((unsigned long)0, target->_currentUnusedStatusFlag);
		}
		/// Testing for no supplu alarm
		///A test for GetSupplyRailsAlarmSource
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GetSupplyRailsAlarmSourceTest()
		{
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
			target->_currentEASourceFlag = 0x00000001; //this one has an alarm but not supply rails error

			String^  expected = System::String::Empty;  //empty string expected
			String^  actual;
			actual = target->GetSupplyRailsAlarmSource();
			Assert::AreEqual(expected, actual);
		}
		/// Testing for a supply error
		///A test for GetSupplyRailsAlarmSource
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GetSupplyRailsAlarmSourceTest1()
		{
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
			target->_currentEASourceFlag = 0x0D00;
			String^  expected = "Source5VA";  //expected 5Va for flag
			String^  actual;
			actual = target->GetSupplyRailsAlarmSource();
			Assert::AreEqual(expected, actual);
		}
		/// Test alarm for non supplyh related alarm
		///A test for GetNameofRaisedAlarmFlag
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GetNameofRaisedAlarmFlagTest()
		{
			DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); 
			target->_currentEASourceFlag = 0x010000;  //expected to raise OverPressure
			
			String^  expected = "OverPressure"; 
			String^  actual;
			actual = target->GetNameofRaisedAlarmFlag();
			Assert::AreEqual(expected, actual);
		}

		/// <summary>
		///A test for TranslateTonoStatusBits
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void TranslateTonoStatusBitsTest()
		{
			unsigned long tonoStatusFlags ; 
			DalTonometerState expected ;
			DalTonometerState actual;
			
			//Disconnected state
			tonoStatusFlags = 0x4000; 
			expected = DalTonometerState::Disconnected ;
			actual = DalStatusHandler_Accessor::TranslateTonoStatusBits(tonoStatusFlags);
			Assert::AreEqual(expected, actual);

			//Disconnected state
			tonoStatusFlags = 0x0000; 
			expected = DalTonometerState::Connected ;
			actual = DalStatusHandler_Accessor::TranslateTonoStatusBits(tonoStatusFlags);
			Assert::AreEqual(expected, actual);
			
		}


		///Pas a non acceptable value. should throw an exception
		///A test for TranslateCuffStatusBits
		///</summary>
		public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void TranslateTonoStatusBitsTestNeg()
		{
			SetPath();
			unsigned long tonoStatusFlags = 0 ; 
			bool exceptionRaised = false;
			
			try
			{
				tonoStatusFlags = 0x0001 ;
				DalTonometerState actual;
				actual = DalStatusHandler_Accessor::TranslateTonoStatusBits(tonoStatusFlags);
				Assert::IsNull(actual);
			}
			catch(ScorException^)
			{
				exceptionRaised = true;
			}
			Assert::IsTrue(exceptionRaised);
		}


		/// <summary>
		///A test for SplitStatusFlagComponents
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SplitStatusFlagComponentsTest()
		{
			unsigned long statusBytes = 0xFFFF; 
			DalStatusHandler_Accessor::SplitStatusFlagComponents(statusBytes);
			Assert::AreEqual((unsigned long)0x0700, DalStatusHandler_Accessor::_newCuffStatusBytes );
			Assert::AreEqual((unsigned long)0x5000, DalStatusHandler_Accessor::_newTonoStatusBytes);
			Assert::AreEqual((unsigned long)0x0008, DalStatusHandler_Accessor::_newAlarmStatusBytes);
			Assert::AreEqual((unsigned long)0x0002, DalStatusHandler_Accessor::_newStopButtonStatusBytes);
			Assert::AreEqual((unsigned long)0x0001, DalStatusHandler_Accessor::_newPowerUpStatusBytes);
			Assert::AreEqual((unsigned long)0x80F4,DalStatusHandler_Accessor::_newUnusedStatusBytes);
		}
//		/// <summary>
//		///A test for TranslateCuffStatusBits
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void TranslateCuffStatusBitsTest1()
//		{
//			unsigned long cuffStatusFlags = 0; // TODO: Initialize to an appropriate value
//			DalCuffStateFlags expected = DalCuffStateFlags(); // TODO: Initialize to an appropriate value
//			DalCuffStateFlags actual;
//			actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(cuffStatusFlags);
//			Assert::AreEqual(expected, actual);
//			Assert::Inconclusive(L"Verify the correctness of this test method.");
//		}
};
}
namespace TestDal {
    
}
