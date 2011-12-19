
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"

using namespace System::Timers;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;

namespace TestDal {
    using namespace System;
    ref class DalActivePortTest;
    
    
    /// <summary>
///This is a test class for DalActivePortTest and is intended
///to contain all DalActivePortTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalActivePortTest
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

		private: static String^ comPortName  = "COM1";
		public:	
			static bool eventRaised = false;
			static DalErrorAlarmStatusFlag alarmStatusFlag;
			static String^ alarmSourceName;
	
			 
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

			 static void MyAlarmEventRaisedTester(Object ^sender, DalModuleErrorAlarmEventArgs ^ args)
			 {
				 eventRaised = true;
				alarmStatusFlag =  args->ErrorAlarmStatus;
				alarmSourceName =  args->AlarmSourceName; 
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
				DalActivePort_Accessor^  actual;
				actual = DalActivePort_Accessor::Instance;
				Assert::IsNotNull(actual);
				delete actual;
			}
			/// <summary>
			///A test for ActiveSerialPortName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ActiveSerialPortNameTest()
			{
				String^ actual;
				DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); 
				Assert::IsNotNull(target);
				actual = target->ActiveSerialPortName;
				Assert::IsNotNull(actual); //By default when a SerialPort class is opened it sets COM1

				target->CloseActivePort();

				delete target;
			}
			/// <summary>
			///A test for SetSerialPortProperties
			///Run this Test case individually
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetSerialPortPropertiesTest()
			{
				DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); // TODO: Initialize to an appropriate value
				bool actual = false;
				bool expected = true;

				try
				{
					target->CloseActivePort();
				}
				catch(Exception ^ scorex)
				{
					delete scorex;
				}

				actual = target->CreateAndOpenNewSerialPort(comPortName);
				Assert::AreEqual(expected, actual, "Run this Test case individually");

				target->SetSerialPortProperties();
				Assert::AreEqual(115200, target->_serialPort->BaudRate);

				target->CloseActivePort();
				delete target;
			}
			/// <summary>
			///A test for SetActivePortInstance
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetActivePortInstanceTest()
			{
				DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); // TODO: Initialize to an appropriate value
				//SetActivePortInstance is called internally by SetActivePort. 
				//we cannot Call it seperately since SetActivePortName expects that the _serialPort meber is set
				//DalActivePort_Accessor^ target = commInterfaceObject ;
				
				//now call the method
				bool retValue = target->SetActivePortInstance(comPortName);
				Assert::IsTrue(retValue, "Ensure that the portnames are valid and run individually.");
				Assert::AreEqual(comPortName, target->_serialPort->PortName, "Ensure that the portnames are valid and run individually.");

				target->CloseActivePort();
				delete target;
			}
			/// <summary>
			///A test for SetActivePort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetActivePortTest()
			{
				DalActivePort_Accessor^  target = gcnew DalActivePort_Accessor(); 
				target->SetActivePort(comPortName);
				Assert::IsNotNull(target->ActiveSerialPortName);
				Assert::AreEqual(comPortName, target->ActiveSerialPortName);

				target->CloseActivePort();
				delete target;
			}
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalActivePort_Accessor^  unnamed = (gcnew DalActivePort_Accessor()); 
				DalActivePort_Accessor^ target; 
				DalActivePort_Accessor^  expected = unnamed; 
				DalActivePort_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);

				unnamed->CloseActivePort();
				delete unnamed;
			}
			/// <summary>
			///A test for CreateAndOpenNewSerialPort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CreateAndOpenNewSerialPortTest()
			{
				DalActivePort_Accessor^ target = gcnew DalActivePort_Accessor();
				//Assert::IsNull(target->_serialPort);
				target->CreateAndOpenNewSerialPort(comPortName);
				Assert::IsNotNull(target->_serialPort);

				target->CloseActivePort();
				delete target;
			}
			/// <summary>
			///A test for CloseActivePort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CloseActivePortTest()
			{
				bool status; 
				DalActivePort_Accessor^ target = gcnew DalActivePort_Accessor();
				target->SetActivePort(comPortName);

				if (target->_serialPort != nullptr)
				{
					status = target->CloseActivePort();
					Assert::IsTrue(status);
				}
				else
				{
					Assert::Fail("Could not conduct CloseActivePortTest since there is no port");
				}

				//target->CloseActivePort();
				delete target;
			}
			/// <summary>
			///A test for DalActivePort Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalActivePortConstructorTest()
			{
				bool exceptionOccured = false;
				try
				{
					DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor());
					target->CreateAndOpenNewSerialPort(comPortName);
					Assert::IsNotNull(target->_serialPort);
					Assert::IsTrue(target->_serialPort->IsOpen);

					target->_serialPort->Close();
					target->CloseActivePort();

					//Assert::IsTrue(target->serialDataWasRecieved);
					delete target;
				}
				catch(Exception^ ) 
				{
					exceptionOccured = true;
				}
				
				Assert::IsFalse(exceptionOccured, "Run this test individually");
				

			}
			
			//removed
//			/// Positive Test case
//			///A test for CheckStreamingTimeout
//			///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void CheckStreamingTimeoutNotOccuredTest()
//		{
//			DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor());
//			Object^  sender = nullptr; 
//			ElapsedEventArgs^  args = nullptr; 
//			//target->serialDataWasRecieved = true; //Set to tru as intitally done
//			eventRaised = false; //should remain false 
//
//			//Register a handler for the event that will be raised
//			DalEventContainer::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalActivePortTest::MyAlarmEventRaisedTester);
//
//
//			target->CheckStreamingTimeout(sender, args);
//
//			Assert::IsFalse(target->serialDataWasRecieved);
//			Assert::IsFalse(eventRaised);
//		}

			//removed
//		/// Positive Test case: event should be raise and the flag shoudl be reset
//		///A test for CheckStreamingTimeout
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void CheckStreamingTimeoutOccuredTest()
//		{
//			DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor());
//			Object^  sender = nullptr; 
//			ElapsedEventArgs^  args = nullptr; 
//			target->serialDataWasRecieved = false; //Set to false to indicate that data was not recived since previous check
//			eventRaised = false; //should remain false 
//			String^ expectedSourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureTimeout, DalFormatterStrings_Accessor::PrintEnumName);
//			
//
//			//Register a handler for the event that will be raised
//			DalEventContainer::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalActivePortTest::MyAlarmEventRaisedTester);
//			target->CheckStreamingTimeout(sender, args);
//			Assert::IsFalse(target->serialDataWasRecieved);
//			Assert::IsFalse(eventRaised); //Since this is the first check it should not raise the event
//
//			//call the method a second time. This time it should raise an event
//			target->CheckStreamingTimeout(sender, args);
//			Assert::IsFalse(target->serialDataWasRecieved);
//			Assert::IsTrue(eventRaised); //Should be true this time
//
//			Assert::AreEqual( DalErrorAlarmStatusFlag::DataCaptureTimeout, alarmStatusFlag);
//		}

//removed
//		/// <summary>
//		///A test for StopStreamingTimeoutChecker
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void StopStreamingTimeoutCheckerTest()
//		{
//			DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); 
//			//prerquisite: timer should be enabled
//			target->StartStreamingTimeoutChecker();
//			Assert::IsTrue(target->timeoutCheckTimer->Enabled ); //precheck
//
//			target->StopStreamingTimeoutChecker();
//			Assert::IsFalse(target->timeoutCheckTimer->Enabled); //timer should be disabled
//			
//		}

//removed
//		/// <summary>
//		///A test for StartStreamingTimeoutChecker
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void StartStreamingTimeoutCheckerTest()
//		{
//			DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); // TODO: Initialize to an appropriate value
//			Assert::IsFalse(target->timeoutCheckTimer->Enabled); //timer should be false by default
//			target->StartStreamingTimeoutChecker();
//			Assert::IsTrue(target->timeoutCheckTimer->Enabled ); //method should start the timer
//		}


			//removed
		//	/// Positive Test case: event should be raise and the flag should be reset
		//	//Also checks that the timer has been turned off after a timout occured.
		//	///A test for CheckStreamingTimeout
		//	///</summary>
		//public: [TestMethod]
		//[DeploymentItem(L"dal.dll")]
		//void CheckStreamingTimeoutTimerDisabledAfterTimeoutTest()
		//{
		//	DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor());
		//	Object^  sender = nullptr; 
		//	ElapsedEventArgs^  args = nullptr; 
		//	target->serialDataWasRecieved = false; //Set to false to indicate that data was not recived since previous check
		//	eventRaised = false; //should remain false 
		//	String^ expectedSourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureTimeout, DalFormatterStrings_Accessor::PrintEnumName);
		//	target->timeoutCheckTimer->Enabled = true; //to check that the timer is turned off after timout.

		//	//Register a handler for the event that will be raised
		//	DalEventContainer::Instance->OnDalModuleErrorAlarmEvent += gcnew DalModuleErrorAlarmEventHandler(&TestDal::DalActivePortTest::MyAlarmEventRaisedTester);
		//	target->CheckStreamingTimeout(sender, args);
		//	Assert::IsFalse(target->serialDataWasRecieved);
		//	Assert::IsTrue(eventRaised);//event should be raised
		//	Assert::AreEqual( DalErrorAlarmStatusFlag::DataCaptureTimeout, alarmStatusFlag);
		//	Assert::IsFalse(target->timeoutCheckTimer->Enabled); //timer should be disabled
		//}
};
}
namespace TestDal {
    
}
