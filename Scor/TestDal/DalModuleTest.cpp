
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
		void SetDeviceStrategyTest2()
		{
			SetPath();
			DalModule_Accessor ^ target = gcnew DalModule_Accessor();
			try
			{
				//We have reverted the change in signature.
				//it will be done later so the test for return value is commented out.

				//bool returnValue = false;
				target->SetDeviceStrategy("Simulation");
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
			DalModule_Accessor^ target = gcnew DalModule_Accessor();
			target->SetDeviceStrategy("Simulation");

			String^  commPort = comPortName ; 
			
			//We have reverted the change in signature.
			//it will be done later so the test for return value is commented out.

			try
			{
				//bool returnValue = false;

				target->SetDeviceStrategy(commPort);
				//Assert::IsTrue(returnValue);
			}
			catch(ScorException ^excepObj)
			{
				Assert::Fail("Excetion thrown: " + excepObj->ErrorMessageKey );
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
					target->SetDeviceStrategy(commPort);
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
			/// <summary>
			///A test for SearchAllPortsforDevice
			///</summary>
	public: [TestMethod]
			void SearchAllPortsforDeviceTest()
			{
				DalModule_Accessor^  target = (gcnew DalModule_Accessor()); 
				String^  foundPortName = System::String::Empty; 
				String^  foundPortNameExpected = comPortName; //expected result COM3
				String^  excludePort = System::String::Empty; //null value let it search for all ports
				bool expected = true; 
				bool actual;

				actual = target->SearchAllPortsforDevice(foundPortName, excludePort);
				Assert::AreEqual(foundPortNameExpected, foundPortName);
				Assert::AreEqual(expected, actual);
			}
			/// Call find moduke to search on all ports
			///A test for FindModule
			///</summary>
	public: [TestMethod]
			void FindModuleTest()
			{
				SetPath();
				DalModule_Accessor^  target = (gcnew DalModule_Accessor()); 
				target->SetDeviceStrategy("Simulation"); //Set to simulation so that it will search all ports
				 
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
				target->SetDeviceStrategy(comPortName ); //Set to the correct port
				String^  deviceFoundPort = System::String::Empty; 
				String^  deviceFoundPortExpected =  comPortName; 
				int expected = 1; //we should get 1 here
				DalFindModuleResult  actual;
				actual = target->FindModule(deviceFoundPort);
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(deviceFoundPortExpected, deviceFoundPort);
			}



			/// <summary>
			///A test for ConfigCommsPortSettingChangeHandler
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConfigCommsPortSettingChangeHandlerTest()
			{
				SetPath();
				DalModule_Accessor ^ target = gcnew DalModule_Accessor();
				Object^  sender = this; 
				CommsPortEventArgs^  args = gcnew  CommsPortEventArgs(comPortName); 
				target->ConfigCommsPortSettingChangeHandler(sender, args);
				DalDeviceHandler_Accessor ^currentDalDevice = dynamic_cast<DalDeviceHandler_Accessor^>(target->_currentDevice);
				Assert::AreEqual(comPortName, currentDalDevice->_commandInterface->ActiveSerialPortName);

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
				target->SetDeviceStrategy("Simulation");
				Assert::IsNotNull(target);
				Assert::IsNotNull(target->_currentDevice);
			}
	};
}
namespace TestDal {
    
}
