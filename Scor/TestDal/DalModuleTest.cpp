
#include "StdAfx.h"

using namespace AtCor::Scor::CrossCutting;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;
namespace TestDal {
    using namespace System;
    ref class DalModuleTest;
    
    
    /// <summary>
///This is a test class for DalModuleTest and is intended
///to contain all DalModuleTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalModuleTest
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
			//##########################################
			//TODO: Set this varaible to the serial port on which device is connected.
			//##########################################
	private:	static String^ comPortName  = "COM3";
	//public:		static DalModule_Accessor^ dalModuleTestObj = gcnew DalModule_Accessor();

	private: String^ _currDir;

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
			void InstanceTest()
			{
				try
				{
					SetPath();
					DalModule_Accessor^  actual = gcnew DalModule_Accessor();
					Assert::IsNotNull(actual);

					DalModule^ target = DalModule_Accessor::Instance;
					Assert::IsNotNull(target);

					DalModule^ expected = DalModule_Accessor::Instance;
					Assert::AreSame(expected, target);
				}
				catch (ScorException ^ scorExcepObj)
				{
					Assert::Fail("Exception thrown:" + scorExcepObj->ErrorMessageKey);
				}
			}

		
		/// <summary>
		///A test for SetDeviceStrategy
		///</summary>
		public: [TestMethod]
		void SetDeviceStrategyTest3()
		{
			String^  commPort = "SIMULATION";
			
			SetPath();
			//DalModule_Accessor ^ target = gcnew DalModule_Accessor();
			DalActiveDevice_Accessor^ target = gcnew DalActiveDevice_Accessor();
			try
			{
				//We have reverted the change in signature.
				//it will be done later so the test for return value is commented out.

				//bool returnValue = false;
				target->SetDeviceStrategy(commPort, DalStreamingMode::Pwv );
				
				Assert::IsNotNull(target->_currentDevice);
				
			}
			catch(ScorException ^ scorexObj)
			{
				Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
			}
			
		}

		/// <summary>
		///A test for SetDeviceStrategy
		///</summary>
		public: [TestMethod]
		void SetDeviceStrategyTest2()
		{
			SetPath();
			//DalModule_Accessor ^ target = gcnew DalModule_Accessor();
			DalActiveDevice_Accessor^ target = gcnew DalActiveDevice_Accessor();
			try
			{
				//We have reverted the change in signature.
				//it will be done later so the test for return value is commented out.

				//bool returnValue = false;
				target->SetDeviceStrategy("Simulation",  DalStreamingMode::Pwv);
				Assert::IsNotNull(target->_currentDevice);
				//Assert::IsTrue(returnValue);
			}
			catch(ScorException ^ scorexObj)
			{
				Assert::Fail("Exception thrown: " + scorexObj->ErrorMessageKey);
			}
			
		}		
	
		/// Tests the method when the current device is set to simulation
		//and then set to port
		///A test for SetDeviceStrategy
		///</summary>
public: [TestMethod]
		void SetDeviceStrategyTest1()
		{
			SetPath();
			//DalModule_Accessor ^ target = gcnew DalModule_Accessor();
			DalActiveDevice_Accessor^ target = gcnew DalActiveDevice_Accessor();
			
			target->SetDeviceStrategy("Simulation", DalStreamingMode::Pwv);

			String^  commPort = comPortName ; 
			
			//We have reverted the change in signature.
			//it will be done later so the test for return value is commented out.
			
			String^  foundPortName = System::String::Empty; 
			//String^  foundPortNameExpected = comPortName; //expected result COM3
			String^  excludePort = System::String::Empty; //null value let it search for all ports
			bool expected = true; 
			bool actual;

			actual = target->SearchAllPortsforDevice(foundPortName, excludePort);
			
			if (actual)
			{
				try
				{
					//bool returnValue = false;
					if (foundPortName != nullptr)
					{
						target->SetDeviceStrategy(commPort, DalStreamingMode::Pwv);
					}
					//Assert::IsTrue(returnValue);
				}
				catch(ScorException ^excepObj)
				{
					Assert::Fail("Excetion thrown: " + excepObj->ErrorMessageKey );
				}
			}
			//For some reason GetType does not reveal the class type of the IDalHandler derived class
			//Trying to cast the IDalHandler_Impl pointer has also not produced the derised effect so we cannot  test this

			/*deviceHandler = safe_cast<DalDeviceHandler_Accessor^>((safe_cast<IDalHandler_Accessor^>)(target->_currentDevice)) ;
			Assert::AreEqual(commPort , deviceHandler->_commandInterface->ActiveSerialPortName);*/
			
		}
			/// Tests for the specific valid com port
			///A test for SetDeviceStrategy
			///</summary>
	public: [TestMethod]
			void SetDeviceStrategyTest()
			{
				SetPath();
				String^  commPort = "Simulation"; 
				try
				{
					IDalHandler_Accessor ^target_currentDevice =  nullptr;

					DalModule_Accessor^ target = gcnew DalModule_Accessor();

					try
					{

					//We have reverted the change in signature.
					//it will be done later so the test for return value is commented out.

					//	bool returnValue = false;
					target->SetDeviceStrategy(commPort, DalStreamingMode::Pwv);
					//Assert::IsTrue(returnValue);
					}
					catch(ScorException ^excepObj)
					{
						Assert::Fail("Excetion thrown: " + excepObj->ErrorMessageKey );
					}
					
					//Note: GetType doesnt work as expected here so we cannt do this test

					//strategy should be automatically set to device
					//target_currentDevice = target->_currentDevice ;
					//Assert::AreEqual(target_deviceHandler::typeid, (target_currentDevice)->GetType());

				}
				catch(ScorException ^ scorEx)
				{
					Assert::Fail("Exception thrown : " + scorEx->ErrorMessageKey);
				}
				
			}
			
			/// Call find moduke to search on all ports
			///A test for FindModule
			///</summary>
	public: [TestMethod]
			void FindModuleTest()
			{
				SetPath();
				DalModule_Accessor^  target = (gcnew DalModule_Accessor()); 
				target->SetDeviceStrategy("Simulation", DalStreamingMode::Pwv); //Set to simulation so that it will search all ports
				 
				String^  deviceFoundPort = System::String::Empty; 
				String^  deviceFoundPortExpected =  comPortName; 
				DalFindModuleResult  actual;
				actual = target->FindModule(deviceFoundPort);
				Assert::AreNotEqual(DalFindModuleResult::ModuleNotFound , actual); //FindModule may return either 1 0r 2 but should not retirn zero
				Assert::AreEqual(deviceFoundPortExpected, deviceFoundPort);
			}

			/// Call find  module after the port is already set to the correct  device port
			///A test for FindModule
			///</summary>
	public: [TestMethod]
			void FindModuleTest2()
			{
				SetPath();
				DalModule_Accessor^  target = (gcnew DalModule_Accessor()); 
				target->SetDeviceStrategy(comPortName, DalStreamingMode::Pwv ); //Set to the correct port
				String^  deviceFoundPort = System::String::Empty; 
				String^  deviceFoundPortExpected =  comPortName; 
				int expected = 1; //we should get 1 here
				DalFindModuleResult  actual;
				actual = target->FindModule(deviceFoundPort);
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(deviceFoundPortExpected, deviceFoundPort);
			}

			
			/// <summary>
			///A test for DalModule Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalModuleConstructorTest1()
			{
				SetPath();
				DalModule_Accessor^  unnamed = gcnew DalModule_Accessor(); 
				Assert::IsNotNull(unnamed);
				PrivateObject^  param0 = gcnew PrivateObject(unnamed);
				DalModule_Accessor^  target = (gcnew DalModule_Accessor(param0));
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for DalModule Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalModuleConstructorTest()
			{
				SetPath();
				DalModule_Accessor^  target = gcnew DalModule_Accessor(); 
				target->SetDeviceStrategy("Simulation", DalStreamingMode::Pwv);
				Assert::IsNotNull(target);

			}
			/// <summary>
			///A test for SetStreamingMode
			///</summary>
public: [TestMethod]
		void SetStreamingModeTest()
		{
			DalModule_Accessor^  target = (gcnew DalModule_Accessor()); 
			DalStreamingMode newMode = DalStreamingMode::cPwa; 
			target->_currentStreamingMode = DalStreamingMode::None;
			
			target->SetStreamingMode(newMode);
			Assert::AreEqual(newMode, target->_currentStreamingMode);
		}
		/// <summary>
		///A test for StreamingMode
		///</summary>
public: [TestMethod]
		void StreamingModeTest()
		{
			DalModule_Accessor^  target = (gcnew DalModule_Accessor()); 
			DalStreamingMode expected = DalStreamingMode::cPwa;
			target->_currentStreamingMode = expected;
			DalStreamingMode actual;
			actual = target->StreamingMode;
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for SaveCaptureData
		///</summary>
public: [TestMethod]
		void SaveCaptureDataTest()
		{
				SetPath();
				//Creating child class object as DalSimulationHandler class is abstuct class
				DalPwvSimulationHandler_Accessor^  target = (gcnew DalPwvSimulationHandler_Accessor()); 

				cli::array< unsigned short >^  cuffPulse = gcnew array< unsigned short > {0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6}; 
				unsigned short bufferSize = 6;  
				bool expected = true; 
				bool actual;
				bool excepRaised = false;

				actual = target->SaveCaptureData(cuffPulse, bufferSize);
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
				Assert::AreNotEqual(excepRaised, expected);

		}
		/// <summary>
		///A test for StartBP
		///</summary>
public: [TestMethod]
		void StartBPTest1()
		{
			DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
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
		void StartBPTest()
		{
			DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
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
		void FinishBPTest()
		{
			DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->FinishBP();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
		/// <summary>
		///A test for AbortBP
		///</summary>
public: [TestMethod]
		void AbortBPTest()
		{
			DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
			bool expected = false; // TODO: Initialize to an appropriate value
			bool actual;
			actual = target->AbortBP();
			Assert::AreEqual(expected, actual);
			Assert::Inconclusive(L"Verify the correctness of this test method.");
		}
};
}
namespace TestDal {
    
}
