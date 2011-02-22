
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
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
				Assert::AreEqual((unsigned long)0, target->_currentCuffStatusFlag, "Run this test independently");
				Assert::AreEqual((unsigned long)0, target->_currentEAStatusFlag , "Run this test independently");
				Assert::AreEqual((unsigned long)0, target->_currentEASourceFlag, "Run this test independently");

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

	};
}
namespace TestDal {
    
}
