
#include "StdAfx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;
using namespace System::Threading;

namespace TestDal {
    using namespace System;
    ref class DalNibpDeviceHandlerTest;
    
    
    /// <summary>
///This is a test class for DalNibpDeviceHandlerTest and is intended
///to contain all DalNibpDeviceHandlerTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalNibpDeviceHandlerTest
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

			

			static void RaiseDummyNibpDataEvent(array<unsigned char>^ dummyNibpPacket)
			{
				Thread^ _dummyEventRaiser = gcnew Thread(gcnew ParameterizedThreadStart(DoEventRaiseWork));
				_dummyEventRaiser->Start(dummyNibpPacket);

			}

			static void DoEventRaiseWork(Object^ workObject)
			{
				array<unsigned char>^ nibpPacket = (array<unsigned char>^)workObject;

				//sleep for some time to allow the test case to start
				Thread::Sleep(500);
				
				DalEventContainer_Accessor::Instance->OnDalNibpPacketEvent(nullptr, gcnew NibPacketArrivedEventArgs(nibpPacket));
			}

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
				DalNibpDeviceHandler_Accessor^  actual;
				actual = DalNibpDeviceHandler_Accessor::Instance;
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for StartBP
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void StartBPTest1()
			{
				DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
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
				DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); 
				DalNIBPMode nibpMode = DalNIBPMode::Adult ; 
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
				DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->FinishBP();
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for ConnectToNibpModule
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConnectToNibpModuleTest()
			{
				SetPath(); //for all the extra files
				DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); 
				bool expected = true; 
				bool actual;

				DalActivePort_Accessor::Instance->SetActivePort("COM9");

				actual = target->ConnectToNibpModule();
				Assert::AreEqual(expected, actual);
				
			}
			/// <summary>
			///A test for AbortBP
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void AbortBPTest()
			{
				DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
				bool expected = false; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->AbortBP();
				Assert::AreEqual(expected, actual);
				Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for DalNibpDeviceHandler Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalNibpDeviceHandlerConstructorTest()
			{
				DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor());
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for SendNibpConnectCommand
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SendNibpConnectCommandTest()
		{
			SetPath(); //for all the extra files
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); 
			DalReturnValue expected = DalReturnValue::Ack; 
			DalReturnValue actual;

			//Force the sequence number to be what we want for processing
			DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber = 0x00;

			//Set to acutal EM4 port when testing
			DalActivePort_Accessor::Instance->SetActivePort("COM8");

			////Mock the response keep the response ready in the staging area
			//DalStagingQueue_Accessor::Instance->LookForResponseToCommand(0x05,5, 0);
			//DalStagingQueue_Accessor::Instance->EnqueueArray(gcnew array<unsigned char> {0x85, 0x05, 0x00, 0x20, 0x00, 0x9A});
			////DalStagingQueue_Accessor::Instance->SignalDataAvailable();


			actual = target->SendNibpConnectCommand();
			Assert::AreEqual(expected, actual);
		}


		/// <summary>
			///A test for SendNibpConnectCommand
			///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SendNibpDisonnectCommandTest()
		{
			SetPath(); //for all the extra files
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); 
			DalReturnValue expected = DalReturnValue::Ack; 
			DalReturnValue actual;

			//Force the sequence number to be what we want for processing
			DalSequenceNumberManager_Accessor::_nextCommandSequenceNumber = 0x00;

			//Set to acutal EM4 port when testing
			DalActivePort_Accessor::Instance->SetActivePort("COM8");

			//PRE test
			actual = target->SendNibpConnectCommand();
			Assert::AreEqual(expected, actual);

			//now send the disconnect command
			actual = target->SendNibpDisconnectCommand();
			Assert::AreEqual(expected, actual);

		}

		/// <summary>
		///A test for SetCommandInterface
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SetCommandInterfaceTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); 
			target->_commandInterface = nullptr; //clear the current pointer for the purpose of the test
			DalCommandInterface_Accessor^  unnamed = gcnew DalCommandInterface_Accessor() ; 
			target->SetCommandInterface(unnamed);
			Assert::IsNotNull(target->_commandInterface);
			Assert::AreEqual(unnamed,target->_commandInterface);
			
		}
		/// <summary>
		///A test for SendCommandToNibpModule
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SendCommandToNibpModuleTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); 
			DalReturnValue expected = DalReturnValue::Success ; 
			DalReturnValue actual;

			//Create an array to embed and send to test 
			array<unsigned char>^ nibpCommandByteArray = gcnew array<unsigned char> {0x3A, 0x17, 0xB4, 0x00, 0xFB}; //Set initial inflate


			DalActivePort_Accessor::Instance->SetActivePort("COM9");

//			actual = target->SendCommandToNibpModule(nibpCommandByteArray); TODO
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for GetCuffPressure
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void GetCuffPressureTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); 
			bool expected = true; 
			bool actual;

			DalActivePort_Accessor::Instance->SetActivePort("COM8");

			////mock the data
			//array<unsigned char>^ dummyNibpData = gcnew array<unsigned char> {0x3E, 0x05, 0x00, 0x00, 0xBD};
			//RaiseDummyNibpDataEvent(dummyNibpData);

			unsigned int cuffPresureValue = 60; //any arbitrary value. While running the test it will probably return zero


			if (!target->ConnectToNibpModule())
			{
				Assert::Fail("Could not connect to NiBP module to run the test");
			}

			Assert::AreNotEqual((unsigned int)0, cuffPresureValue);

			actual = target->GetCuffPressure(cuffPresureValue);
			Assert::AreEqual(expected, actual);

			Assert::AreEqual((unsigned int)0, cuffPresureValue);
	
		}
		/// <summary>
		///A test for Instance
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void InstanceTest1()
		{
			DalNibpDeviceHandler_Accessor^  actual;
			actual = DalNibpDeviceHandler_Accessor::Instance;
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for StopCuffPressurePlotting
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StopCuffPressurePlottingTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			target->StopCuffPressurePlotting();
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for StartBpProcess
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StartBpProcessTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); 
			DalNIBPMode nibpMode = DalNIBPMode::Adult ; 
			unsigned short initialPressure = 100; // doesnt matter
			bool initialInflate = false; // No Initial inflate for now
			bool expected = true; 
			bool actual;

			DalActivePort_Accessor::Instance->SetActivePort("COM9");

			//Start Bp Internally connects to Nibp Module
			/*if (!target->ConnectToNibpModule())
			{
				Assert::Fail("Could not connect to NiBP module to run the test");
			}*/

			actual = target->StartBpProcess(nibpMode, initialPressure, initialInflate);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for StartBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StartBPTest3()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			DalNIBPMode nibpMode = DalNIBPMode(); // TODO: Initialize to an appropriate value
			unsigned short initialPressure = 0; // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->StartBP(nibpMode, initialPressure);
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for StartBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void StartBPTest2()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			DalNIBPMode nibpMode = DalNIBPMode(); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->StartBP(nibpMode);
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SetCommandInterface
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SetCommandInterfaceTest1()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			DalCommandInterface_Accessor^  unnamed = nullptr; // TODO: Initialize to an appropriate value
			target->SetCommandInterface(unnamed);
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for SendNibpDisconnectCommand
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SendNibpDisconnectCommandTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			DalReturnValue expected = DalReturnValue(); // TODO: Initialize to an appropriate value
			DalReturnValue actual;
			actual = target->SendNibpDisconnectCommand();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SendNibpConnectDisconnectCommand
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SendNibpConnectDisconnectCommandTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			bool connect = false; // TODO: Initialize to an appropriate value
			DalReturnValue expected = DalReturnValue(); // TODO: Initialize to an appropriate value
			DalReturnValue actual;
			actual = target->SendNibpConnectDisconnectCommand(connect);
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for SendNibpConnectCommand
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void SendNibpConnectCommandTest1()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			DalReturnValue expected = DalReturnValue(); // TODO: Initialize to an appropriate value
			DalReturnValue actual;
			actual = target->SendNibpConnectCommand();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for FinishBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void FinishBPTest1()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->FinishBP();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for CuffPressurePlottingThreadMethod
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CuffPressurePlottingThreadMethodTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			target->CuffPressurePlottingThreadMethod();
			Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
		}
		/// <summary>
		///A test for CreateDataBuffer
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void CreateDataBufferTest()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->CreateDataBuffer();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for ConnectToNibpModule
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void ConnectToNibpModuleTest1()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->ConnectToNibpModule();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		//removed
//		/// <summary>
//		///A test for CheckIfCuffHasDeflated
//		///</summary>
//public: [TestMethod]
//		[DeploymentItem(L"dal.dll")]
//		void CheckIfCuffHasDeflatedTest()
//		{
//			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
//			bool expected = false; // TODO: Initialize to an appropriate value
//			bool actual;
//			actual = target->CheckIfCuffHasDeflated();
//			Assert::AreEqual(expected, actual);
//			Assert::Inconclusive(L"Verify the correctness of this test method.");
//		}
		/// <summary>
		///A test for AbortBP
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void AbortBPTest1()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->AbortBP();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for DalNibpDeviceHandler Constructor
		///</summary>
public: [TestMethod]
		[DeploymentItem(L"dal.dll")]
		void DalNibpDeviceHandlerConstructorTest1()
		{
			DalNibpDeviceHandler_Accessor^  target = (gcnew DalNibpDeviceHandler_Accessor());
			Assert::Inconclusive(L"TODO: Implement code to verify target");
		}
};
}
namespace TestDal {
    
}
