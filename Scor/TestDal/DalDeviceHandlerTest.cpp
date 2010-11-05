
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalDeviceHandlerTest;
    
    
    /// <summary>
///This is a test class for DalDeviceHandlerTest and is intended
///to contain all DalDeviceHandlerTest Unit Tests
///</summary>
    [TestClass]
    public ref class DalDeviceHandlerTest
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
            /// <summary>
            ///A test for StopCapture
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void StopCaptureTest()
            {
                // As this method does nothing as now, hence kept empty
                DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
                target->StopCapture();
                //Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for StartCapture
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void StartCaptureTest()
            {
                // As this method does nothing as now, hence kept empty
                DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); // TODO: Initialize to an appropriate value
                target->StartCapture();
                //Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for GetConnectionStatus
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void GetConnectionStatusTest()
            {
                // As this method does nothing as now, hence checked for default return value
                DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor()); 
                bool expected = false; // TODO: Initialize to an appropriate value
                bool actual;
                actual = target->GetConnectionStatus();
                Assert::AreEqual(expected, actual);
                //Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
// dummy method does nothing, hence not tested
    //        /// <summary>
    //        ///A test for GetConfigurationInfo
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void GetConfigurationInfoTest()
    //        {
    //            DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor());
    //            //DalDeviceConfigUsageEnum deviceConfigItem = DalDeviceConfigUsageEnum();
    //            DalDeviceConfigUsageStruct^  deviceConfigInfo = (gcnew DalDeviceConfigUsageStruct());
    //            bool expected = false; // TODO: Initialize to an appropriate value
    //            bool actual;
    //            actual = target->GetConfigurationInfo((AtCor::Scor::DataAccess::DalDeviceConfigUsageEnum)0, deviceConfigInfo);
    //            Assert::AreEqual(expected, actual);

    //            // check for set value
    //            Assert::AreEqual(System::DateTime::Today, deviceConfigInfo->ModuleConfigDate);

    //            //Assert::Inconclusive(L"Verify the correctness of this test method.");
    //        }
            /// <summary>
            ///A test for DalDeviceHandler Constructor
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void DalDeviceHandlerConstructorTest1()
            {
                String^  commPort = "COM1";
                DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor(commPort));
                
                Assert::AreEqual(commPort, target->_commPort);
                //Assert::Inconclusive(L"TODO: Implement code to verify target");
            }
            /// <summary>
            ///A test for DalDeviceHandler Constructor
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void DalDeviceHandlerConstructorTest()
            {
                DalDeviceHandler_Accessor^  target = (gcnew DalDeviceHandler_Accessor());
                Assert::AreNotEqual(nullptr, target);
                //Assert::Inconclusive(L"TODO: Implement code to verify target");
            }
    };
}
namespace TestDal {
    
}
