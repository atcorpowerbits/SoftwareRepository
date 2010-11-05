
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
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

    private: static DalModule_Accessor^  target;

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
            public: [ClassInitialize]
            static System::Void MyClassInitialize(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^  testContext)
            {
                // set the path to appropriet folder
                System::IO::Directory::SetCurrentDirectory("D:\\Shriganesh\\ProjectData\\AtCor\\src\\dal\\TestResults\\");

                if(target == nullptr)
                    target = (gcnew DalModule_Accessor());
                
            }
            
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
                // set the path to appropriet folder
                System::IO::Directory::SetCurrentDirectory("D:\\Shriganesh\\ProjectData\\AtCor\\src\\dal\\TestResults\\");
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
                DalModule^  actual;
                actual = DalModule::Instance;
                
                Assert::IsInstanceOfType(actual, actual->GetType());
                //Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
// redirects the call to the appropriet strategy, hence no need to test any thing as of now
            /// <summary>
            ///A test for StopCapture
            ///</summary>
    public: [TestMethod]
            void StopCaptureTest()
            {
                //DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
                //target->StopCapture();
                //Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
// redirects the call to the appropriet strategy, hence no need to test any thing as of now
            /// <summary>
            ///A test for StartCapture
            ///</summary>
    public: [TestMethod]
            void StartCaptureTest()
            {
                // set the path to appropriet folder
                //System::IO::Directory::SetCurrentDirectory("D:\\Shriganesh\\ProjectData\\AtCor\\src\\dal\\TestResults");
                String^ str = System::IO::Directory::GetCurrentDirectory();
                //DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
                target->StartCapture();
                //Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for SetDeviceStrategy
            ///</summary>
    public: [TestMethod]
            void SetDeviceStrategyTest1()
            {
                //DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
                
                String^  commPort = "COM1";
                target->SetDeviceStrategy(commPort);

                Assert::IsInstanceOfType(target->_currentDevice, target->_currentDevice->GetType());

                commPort = "SIMULATION";
                target->SetDeviceStrategy(commPort);

                Assert::IsInstanceOfType(target->_currentDevice, target->_currentDevice->GetType());

                //Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
// No need to test as it does the same job of settingup of strategy but reads the comms port from
// config file
    //        /// <summary>
    //        ///A test for SetDeviceStrategy
    //        ///</summary>
    //public: [TestMethod]
    //        void SetDeviceStrategyTest()
    //        {
    //            DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
    //            target->SetDeviceStrategy();
    //            //Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
    //        }

// does nothing hence no need to test, written for singleton class
    //        /// <summary>
    //        ///A test for op_Assign
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void op_AssignTest()
    //        {
    //            DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
    //            DalModule unnamed; // TODO: Initialize to an appropriate value
    //            DalModule^  expected = nullptr; // TODO: Initialize to an appropriate value
    //            DalModule^  actual;
    //            actual = (target = unnamed);
    //            Assert::AreEqual(expected, actual);
    //            Assert::Inconclusive(L"Verify the correctness of this test method.");
    //        }

// redirects the call hence no need to test
    //        /// <summary>
    //        ///A test for GetConnectionStatus
    //        ///</summary>
    //public: [TestMethod]
    //        void GetConnectionStatusTest()
    //        {
    //            DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
    //            bool expected = false; // TODO: Initialize to an appropriate value
    //            bool actual;
    //            actual = target->GetConnectionStatus();
    //            //Assert::AreEqual(expected, actual);
    //            //Assert::Inconclusive(L"Verify the correctness of this test method.");
    //        }

// redirects the call hence no need to test
    //        /// <summary>
    //        ///A test for GetConfigurationInfo
    //        ///</summary>
    //public: [TestMethod]
    //        void GetConfigurationInfoTest()
    //        {
    //            DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
    //            DalDeviceConfigUsageEnum deviceConfigItem = DalDeviceConfigUsageEnum(); // TODO: Initialize to an appropriate value
    //            DalDeviceConfigUsageStruct^  deviceConfigInfo = nullptr; // TODO: Initialize to an appropriate value
    //            bool expected = false; // TODO: Initialize to an appropriate value
    //            bool actual;
    //            actual = target->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
    //            //Assert::AreEqual(expected, actual);
    //            //Assert::Inconclusive(L"Verify the correctness of this test method.");
    //        }

// This function does nothing as of now
            /// <summary>
            ///A test for FindModule
            ///</summary>
    public: [TestMethod]
            void FindModuleTest()
            {
                // set the path to appropriet folder
                //System::IO::Directory::SetCurrentDirectory("D:\\Shriganesh\\ProjectData\\AtCor\\src\\dal\\TestResults");

                //DalModule_Accessor^  target = (gcnew DalModule_Accessor()); // TODO: Initialize to an appropriate value
                String^  expected = nullptr; // TODO: Initialize to an appropriate value
                String^  actual;
                actual = target->FindModule();
                Assert::AreEqual(expected, actual);
                //Assert::Inconclusive(L"Verify the correctness of this test method.");
            }

// Copy constructor, does nothing hence, no need to test, written for singleton
    //        /// <summary>
    //        ///A test for DalModule Constructor
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void DalModuleConstructorTest1()
    //        {
    //            DalModule^  unnamed = nullptr; // TODO: Initialize to an appropriate value
    //            DalModule_Accessor^  target = (gcnew DalModule_Accessor(unnamed));
    //            Assert::Inconclusive(L"TODO: Implement code to verify target");
    //        }

// This is a private constructor
            /// <summary>
            ///A test for DalModule Constructor
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void DalModuleConstructorTest()
            {
                // set the path to appropriet folder
                //System::IO::Directory::SetCurrentDirectory("D:\\Shriganesh\\ProjectData\\AtCor\\src\\dal\\TestResults");

                //DalModule_Accessor^  target = (gcnew DalModule_Accessor());

                Assert::IsInstanceOfType(target, target->GetType());
                //Assert::Inconclusive(L"TODO: Implement code to verify target");
            }
    };
}
namespace TestDal {
    
}
