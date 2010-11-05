
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class IDalHandlerTest;
    
    
    /// <summary>
///This is a test class for IDalHandlerTest and is intended
///to contain all IDalHandlerTest Unit Tests
///</summary>
    [TestClass]
    public ref class IDalHandlerTest
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

// This is Interface class and does not have any implmentation hence , none of the unit tests are needed

    //        /// <summary>
    //        ///A test for StopCapture
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void StopCaptureTest()
    //        {
    //            IDalHandler_Accessor^  target = CreateIDalHandler_Accessor(); // TODO: Initialize to an appropriate value
    //            target->StopCapture();
    //            Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
    //        }
    //        /// <summary>
    //        ///A test for StartCapture
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void StartCaptureTest()
    //        {
    //            IDalHandler_Accessor^  target = CreateIDalHandler_Accessor(); // TODO: Initialize to an appropriate value
    //            target->StartCapture();
    //            Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
    //        }
    //        /// <summary>
    //        ///A test for GetConnectionStatus
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void GetConnectionStatusTest()
    //        {
    //            IDalHandler_Accessor^  target = CreateIDalHandler_Accessor(); // TODO: Initialize to an appropriate value
    //            bool expected = false; // TODO: Initialize to an appropriate value
    //            bool actual;
    //            actual = target->GetConnectionStatus();
    //            Assert::AreEqual(expected, actual);
    //            Assert::Inconclusive(L"Verify the correctness of this test method.");
    //        }
    //internal: IDalHandler_Accessor^  CreateIDalHandler_Accessor()
    //          {
    //              // TODO: Instantiate an appropriate concrete class.
    //              IDalHandler_Accessor^  target = nullptr;
    //              return target;
    //          }
    //          /// <summary>
    //          ///A test for GetConfigurationInfo
    //          ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void GetConfigurationInfoTest()
    //        {
    //            IDalHandler_Accessor^  target = CreateIDalHandler_Accessor(); // TODO: Initialize to an appropriate value
    //            DalDeviceConfigUsageEnum deviceConfigItem = DalDeviceConfigUsageEnum(); // TODO: Initialize to an appropriate value
    //            DalDeviceConfigUsageStruct^  deviceConfigInfo = nullptr; // TODO: Initialize to an appropriate value
    //            bool expected = false; // TODO: Initialize to an appropriate value
    //            bool actual;
    //            actual = target->GetConfigurationInfo(deviceConfigItem, deviceConfigInfo);
    //            Assert::AreEqual(expected, actual);
    //            Assert::Inconclusive(L"Verify the correctness of this test method.");
    //        }
    };
}
namespace TestDal {
    
}
