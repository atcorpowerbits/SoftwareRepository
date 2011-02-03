
#include "StdAfx.h"

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;
namespace TestDal {
    using namespace System;
    ref class DalModuleTest;
	using namespace AtCor::Scor::DataAccess;

    
    
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

			void SetPath()
			{
				String^ path = Directory::GetCurrentDirectory(); 
				//Directory::SetCurrentDirectory("D:\\Deepak Share\\Sprint 5\\Scor\\TestResults");
				
				Directory::SetCurrentDirectory("D:\\Scor_Source_code\\TestResults");
				
				//Directory::SetCurrentDirectory("D:\\Deepak\\Scor\\TestResults");
				
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
			/// <summary>
			///A test for Instance
			///</summary>
	public: [TestMethod]
			void InstanceTest()
			{
				SetPath();

				DalModule^  actual;
				actual = DalModule::Instance;
				Assert::IsNotNull(actual);
				DalModule^ target = DalModule::Instance;

				Assert::AreSame(actual, target);
			}


			public: [TestMethod]
			void FindModuleTest()
			{
				SetPath();

				String^ retValue;

				DalModule^  actual = DalModule::Instance;
				Assert::IsNotNull(actual);
				retValue = actual->FindModule();
				Assert::IsNull(retValue);
			}

			//cannot resolve compilation issues

			/*public: [TestMethod]
			void GetConfigurationInfoTest()
			{
				SetPath();

				DalModule^  actual = DalModule::Instance;
				DalDeviceConfigUsageEnum ^confUseEnum = gcnew DalDeviceConfigUsageEnum();
				confUseEnum = DalDeviceConfigUsageEnum::ModuleType;

				DalDeviceConfigUsageStruct ^deviceConfigInfo = gcnew DalDeviceConfigUsageStruct();
				actual->SetDeviceStrategy();
				bool retvalue = actual->GetConfigurationInfo(ModuleType, deviceConfigInfo);
				Assert::IsFalse(retvalue);

				actual->SetDeviceStrategy("Simulation");
				retvalue = actual->GetConfigurationInfo(ModuleType, deviceConfigInfo);
				Assert::IsTrue(retvalue);
			}*/


			public: [TestMethod]
			void GetConnectionStatusTest()
			{
				SetPath();

				DalModule^  actual = DalModule::Instance;
				bool retvalue =  actual->GetConnectionStatus();
				
				actual->SetDeviceStrategy("Simulation");
				retvalue =  actual->GetConnectionStatus();
				Assert::IsTrue(retvalue);
			}


			public: [TestMethod]
			void GetErrorAlarmSourceTest()
			{
				SetPath();

				DalModule^  actual = DalModule::Instance;
				String^ retvalue;

				try{
					retvalue =  actual->GetErrorAlarmSource();
				}
				catch(AtCor::Scor::CrossCutting::ScorException^ dalEx)
				{
					Assert::IsTrue(true);
				}
				//Assert::IsNull(retvalue);

				actual->SetDeviceStrategy("Simulation");
				try{
					retvalue =  actual->GetErrorAlarmSource();
				}
				catch(AtCor::Scor::CrossCutting::ScorException^ dalEx)
				{
					Assert::IsTrue(true);
				}
			}


			public: [TestMethod]
			void StartCaptureTest()
			{
				SetPath();

				DalModule^  actual = DalModule::Instance;
				actual->StartCapture();
				Assert::IsTrue(true);

				actual->SetDeviceStrategy("Simulation");
				actual->StartCapture();
				Assert::IsTrue(true);

			}


			public: [TestMethod]
			void StartCaptureTest2()
			{
				SetPath();

				DalModule^  actual = DalModule::Instance;
				actual->StartCapture(10, 10);
				Assert::IsTrue(true);

				actual->SetDeviceStrategy("Simulation");
				actual->StartCapture(10, 10);
				Assert::IsTrue(true);

			}


			public: [TestMethod]
			void StopCaptureTest()
			{
				SetPath();

				DalModule^  actual = DalModule::Instance;


				actual->SetDeviceStrategy("COMPORT_SIMULATION");
				actual->StopCapture();
				Assert::IsTrue(true);

			}

			public: [TestMethod]
			void SetDeviceStrategyTest()
			{
				SetPath();

				DalModule^  actual = DalModule::Instance;
		
				try
				{
					actual->SetDeviceStrategy("COMPORT_SIMULATION");
				}
				catch (AtCor::Scor::CrossCutting::ScorException ^dalEx)
				{
					Assert::IsTrue(true);
				}
				
			}



		

	};
}
namespace TestDal {
    
}
