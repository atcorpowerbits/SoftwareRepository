
#include "StdAfx.h"
using namespace AtCor::Scor::CrossCutting;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;

namespace TestDal {
    using namespace System;
    ref class DalActiveDeviceTest;
    
    
    /// <summary>
///This is a test class for DalActiveDeviceTest and is intended
///to contain all DalActiveDeviceTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalActiveDeviceTest
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

			private:	static String^ comPortName  = "COM1";
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
			[DeploymentItem(L"dal.dll")]
			void InstanceTest()
			{
				try
				{
					SetPath();
					DalActiveDevice_Accessor^  actual = gcnew DalActiveDevice_Accessor();
					Assert::IsNotNull(actual);

					DalActiveDevice_Accessor^ target = DalActiveDevice_Accessor::Instance;
					Assert::IsNotNull(target);

					DalActiveDevice_Accessor^ expected = DalActiveDevice_Accessor::Instance;
					Assert::AreSame(expected, target);
				}
				catch (ScorException ^ scorExcepObj)
				{
					Assert::Fail("Exception thrown:" + scorExcepObj->ErrorMessageKey);
				}
		}
			/// <summary>
			///A test for CurrentDevice
			///</summary>
	//public: [TestMethod]
	//		[DeploymentItem(L"dal.dll")]
	//		void CurrentDeviceTest()
	//		{
	//			IDalHandler_Accessor^  actual;
	//			actual = DalActiveDevice_Accessor::CurrentDevice;
	//			Assert::IsNotNull(actual);
	//		}
			/// <summary>
			///A test for SetDeviceStrategy
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetDeviceStrategyTest1()
			{
				bool expected = true;
				bool actual;

				SetPath();
				//String^  commPort = "Simulation";

				actual = DalActiveDevice_Accessor::SetDeviceStrategy();
				Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}

			/// <summary>
			///A test for SetDeviceStrategy
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetDeviceStrategyTest()
			{
				String^  commPort = "Simulation"; 
				bool expected = true;
				bool actual;

				actual = DalActiveDevice_Accessor::SetDeviceStrategy(commPort, DalStreamingMode::Pwv);
				
				Assert::AreEqual(expected, actual);
				
				SetPath();
				/*String^*/  commPort = "Simulation"; 
				try
				{
					IDalHandler_Accessor ^target_currentDevice =  nullptr;
					DalActiveDevice_Accessor^ target = gcnew DalActiveDevice_Accessor();

					try
					{
						target->SetDeviceStrategy(commPort, DalStreamingMode::Pwv);
					}
					catch(ScorException ^excepObj)
					{
						Assert::Fail("Excetion thrown: " + excepObj->ErrorMessageKey );
					}
				}
				catch(ScorException ^ scorEx)
				{
					Assert::Fail("Exception thrown : " + scorEx->ErrorMessageKey);
				}
			}

			/// <summary>
			///A test for SetDeviceNull
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetDeviceNullTest()
			{
				DalActiveDevice_Accessor^  target = (gcnew DalActiveDevice_Accessor()); // TODO: Initialize to an appropriate value
				target->SetDeviceNull();
				Assert::IsNull(target->_currentDevice);
			}
			/// <summary>
			///A test for SearchAllPortsforDevice
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SearchAllPortsforDeviceTest()
			{
				DalActiveDevice_Accessor^  target = (gcnew DalActiveDevice_Accessor()); // TODO: Initialize to an appropriate value
				String^  foundPortName = System::String::Empty; 
				String^  foundPortNameExpected = comPortName;
				String^  excludePort = System::String::Empty; 
				bool expected = true; 
				bool actual = 0;
				
				try
				{
					actual = target->SearchAllPortsforDevice(foundPortName, excludePort);
				
					Assert::IsTrue(actual);
				}
				catch(Exception^ )
				{
					Assert::IsFalse(actual);
				}
			}
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				//DalActiveDevice_Accessor^  target = (gcnew DalActiveDevice_Accessor()); // TODO: Initialize to an appropriate value
				//DalActiveDevice_Accessor unnamed; // TODO: Initialize to an appropriate value
				//DalActiveDevice_Accessor^  expected = nullptr; // TODO: Initialize to an appropriate value
				//DalActiveDevice_Accessor^  actual;
				//actual = (target = unnamed);
				//Assert::AreEqual(expected, actual);
				//Assert::Inconclusive(L"Verify the correctness of this test method.");
			}
			/// <summary>
			///A test for FindModule
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void FindModuleTest()
			{
				SetPath();
				
				DalActiveDevice_Accessor^  target = (gcnew DalActiveDevice_Accessor()); // TODO: Initialize to an appropriate value
				target->SetDeviceStrategy("Simulation", DalStreamingMode::Pwv); //Set to simulation so that it will search all ports
				
				String^  deviceFoundPort = System::String::Empty; // TODO: Initialize to an appropriate value
				DalFindModuleResult  actual;
				
				actual = target->FindModule(deviceFoundPort);
				Assert::AreEqual(DalFindModuleResult::ModuleNotFound , actual); //FindModule may return either 1 0r 2 but should not retirn zero
				
			}
		
public: [TestMethod]
			void FindModuleTest2()
			{
				SetPath();

				DalActiveDevice_Accessor^  target = (gcnew DalActiveDevice_Accessor()); 
				try
				{
					target->SetDeviceStrategy(comPortName, DalStreamingMode::Pwv ); //Set to the correct port
				}
				catch(Exception^ )
				{
					
				}
				String^  deviceFoundPort = System::String::Empty; 
				String^  deviceFoundPortExpected =  comPortName; 
				int expected = 1; //we should get 1 here
				DalFindModuleResult  actual;
				try
				{
					actual = target->FindModule(deviceFoundPort);
					Assert::AreEqual(expected, actual);
					Assert::AreEqual(deviceFoundPortExpected, deviceFoundPort);
				}
				catch(Exception^ )
				{
					
				}
				
			}
			/// <summary>
			///A test for ConfigCommsPortSettingChangeHandler
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ConfigCommsPortSettingChangeHandlerTest()
			{
				//Object^  sender = nullptr; // TODO: Initialize to an appropriate value
				//CommsPortEventArgs^  args = nullptr; // TODO: Initialize to an appropriate value
				//DalActiveDevice_Accessor::ConfigCommsPortSettingChangeHandler(sender, args);
				//Assert::Inconclusive(L"A method that does not return a value cannot be verified.");

				SetPath();
				//DalModule_Accessor ^ target = gcnew DalModule_Accessor();
				Object^  sender = this; 
				CommsPortEventArgs^  args = gcnew  CommsPortEventArgs(comPortName); 
				//target->ConfigCommsPortSettingChangeHandler(sender, args);
				DalActiveDevice_Accessor::ConfigCommsPortSettingChangeHandler(sender, args);
				DalDeviceHandler_Accessor ^currentDalDevice = dynamic_cast<DalDeviceHandler_Accessor^>(DalActiveDevice_Accessor::_currentDevice);
				Assert::AreEqual(comPortName, DalActivePort_Accessor::Instance->ActiveSerialPortName);

			}
			/// <summary>
			///A test for DalActiveDevice Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalActiveDeviceConstructorTest1()
			{
				DalActiveDevice_Accessor^  unnamed = nullptr; // TODO: Initialize to an appropriate value
				DalActiveDevice_Accessor^  target = (gcnew DalActiveDevice_Accessor(unnamed));
				Assert::IsNotNull(target);
			}
			/// <summary>
			///A test for DalActiveDevice Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalActiveDeviceConstructorTest()
			{
				DalActiveDevice_Accessor^  target = (gcnew DalActiveDevice_Accessor());
				Assert::IsNotNull(target);
			}
	};
}
namespace TestDal {
    
}
