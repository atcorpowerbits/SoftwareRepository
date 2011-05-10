
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
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
				Assert::AreEqual((unsigned long)0, (unsigned long)target->_currentCuffStatusFlag, "Run this test independently");
				Assert::AreEqual((unsigned long)0, (unsigned long)target->_currentEAStatusFlag , "Run this test independently");
				Assert::AreEqual((unsigned long)0, (unsigned long)target->_currentEASourceFlag, "Run this test independently");

				Assert::IsNull(target->dalErrorAlarmSourceName, "Run this test independently");
				Assert::IsNull(target->_savedDataFilePath, "Run this test independently");
			}
			/// <summary>
			///A test for TranslateErrorAlarmStatusBits
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void TranslateErrorAlarmStatusBitsTest()
			{
				unsigned long statusFlags;
					
				//no error or alarm
				statusFlags = 0x0400 ;
				DalErrorAlarmStatusFlag expected = DalErrorAlarmStatusFlag::ActiveStatus; 
				DalErrorAlarmStatusFlag actual;
				actual = DalStatusHandler_Accessor::TranslateErrorAlarmStatusBits(statusFlags);
				Assert::AreEqual(expected, actual);

				//alarm status
				statusFlags = 0x0408 ;
				 expected = DalErrorAlarmStatusFlag::RecoverableStatus; 
				
				actual = DalStatusHandler_Accessor::TranslateErrorAlarmStatusBits(statusFlags);
				Assert::AreEqual(expected, actual);

				//error status
				statusFlags =0x0920 ;
				expected = DalErrorAlarmStatusFlag::UnrecoverableStatus; 
				actual = DalStatusHandler_Accessor::TranslateErrorAlarmStatusBits(statusFlags);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for TranslateCuffStatusBits
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void TranslateCuffStatusBitsTest()
			{
				unsigned long statusFlags = 0 ; 
				
				// cuff inflating status
				statusFlags = 0x0400 ;
				DalCuffStateFlags expected = DalCuffStateFlags::CUFF_STATE_INFLATING ; 
				DalCuffStateFlags actual;
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(statusFlags);
				Assert::AreEqual(expected, actual);

				// cuff inflated status
				statusFlags = 0x0900 ;
				expected = DalCuffStateFlags::CUFF_STATE_INFLATED ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(statusFlags);
				Assert::AreEqual(expected, actual);

				// cuff deflating status
				statusFlags = 0x0200 ;
				expected = DalCuffStateFlags::CUFF_STATE_DEFLATING  ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(statusFlags);
				Assert::AreEqual(expected, actual);

				// cuff deflated status
				statusFlags = 0x0100 ;
				expected = DalCuffStateFlags::CUFF_STATE_DEFLATED ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(statusFlags);
				Assert::AreEqual(expected, actual);

				// cuff disconnected status
				statusFlags = 0x2000 ;
				expected = DalCuffStateFlags::CUFF_STATE_DISCONNECTED  ; 
				actual = DalStatusHandler_Accessor::TranslateCuffStatusBits(statusFlags);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for MapErrorSourceToString
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void MapErrorSourceToStringTest()
			{
				//dual sensor
				unsigned long sourceFlags = 0x20; 
				String^  expected = DalErrorSource::DualSensors.ToString();
				String^  actual;
				actual = DalStatusHandler_Accessor::MapErrorSourceToString(sourceFlags);
				Assert::AreEqual(expected, actual);

				//cuff leak
				sourceFlags = 0x0008; 
				expected = DalErrorSource::CuffLeak.ToString();
				actual = DalStatusHandler_Accessor::MapErrorSourceToString(sourceFlags);
				Assert::AreEqual(expected, actual);
			}

			/// <summary>
			///A test for MapAlarmSourceToString
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void MapAlarmSourceToStringTest()
			{
				DalStatusHandler_Accessor::_currentEASourceFlag = 0x10000 ;
				DalStatusHandler_Accessor::_currentEAStatusFlag = 0x0408 ;
				unsigned long sourceFlags = 0x10000; 
				String^  expected = DalAlarmSource::OverPressure.ToString() ; 
				String^  actual;
				actual = DalStatusHandler_Accessor::MapAlarmSourceToString((sourceFlags >> 16) & 0x0000FFFF);
				Assert::AreEqual(expected, actual);

				sourceFlags = 0x40000 ; 
				expected = DalAlarmSource::InflatedOverTime.ToString() ; 
				actual = DalStatusHandler_Accessor::MapAlarmSourceToString((sourceFlags >> 16) & 0x0000FFFF);
				Assert::AreEqual(expected, actual);

				
			}
			/// <summary>
			///A test for GetErrorAlarmSource
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void GetErrorAlarmSourceTest()
			{
				DalStatusHandler_Accessor^  target = (gcnew DalStatusHandler_Accessor()); // TODO: Initialize to an appropriate value
				target->_currentEAStatusFlag = 0x0408;
				target->_currentEASourceFlag =0x10000;
				String^  expected = DalAlarmSource::OverPressure.ToString();
		
				String^  actual;
				actual = target->GetErrorAlarmSource();
				Assert::AreEqual(expected, actual);


				target->_currentEAStatusFlag = 0x0920;
				target->_currentEASourceFlag =0x20;
				 expected = DalErrorSource::DualSensors.ToString();
		
				actual = target->GetErrorAlarmSource();
				Assert::AreEqual(expected, actual);
			
			}
			/// <summary>
			///A test for CheckEAStatusFlagChanged
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CheckEAStatusFlagChangedTest()
			{
				DalStatusHandler_Accessor::_currentEAStatusFlag = 0x0400;
				unsigned long newEAStatusFlag = 0x0408; 
				bool expected = true; 
				bool actual;
				actual = DalStatusHandler_Accessor::CheckEAStatusFlagChanged(newEAStatusFlag);
				Assert::AreEqual(expected, actual);

				//call again to chek if the status is the same or not
				expected = false; 
				actual = DalStatusHandler_Accessor::CheckEAStatusFlagChanged(newEAStatusFlag);
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
};
}
namespace TestDal {
    
}
