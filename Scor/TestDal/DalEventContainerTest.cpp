
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalEventContainerTest;
    
    
    /// <summary>
///This is a test class for DalEventContainerTest and is intended
///to contain all DalEventContainerTest Unit Tests
///</summary>
    [TestClass]
    public ref class DalEventContainerTest
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
            ///A test for Instance
            ///</summary>
    public: [TestMethod]
            void InstanceTest()
            {
                DalEventContainer^  actual;
                actual = DalEventContainer::Instance;

                // check if we are getting the right type of object
                Assert::IsInstanceOfType(actual, actual->GetType());
                
                //Assert::Inconclusive(L"Verify the correctness of this test method.");
            }

// No need to run test case for assigment operator as it is private and does nothing,
// implemented for singleton pattern
    //        /// <summary>
    //        ///A test for op_Assign
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void op_AssignTest()
    //        {
    //            DalEventContainer_Accessor^  target = (gcnew DalEventContainer_Accessor()); // TODO: Initialize to an appropriate value
    //            DalEventContainer unnamed; // TODO: Initialize to an appropriate value
    //            DalEventContainer^  expected = nullptr; // TODO: Initialize to an appropriate value
    //            DalEventContainer^  actual;
    //            actual = (target = unnamed);
    //            Assert::AreEqual(expected, actual);
    //            Assert::Inconclusive(L"Verify the correctness of this test method.");
    //        }

// No need to run test case for copy constructor as it is private and does nothing,
// implemented for singleton pattern
    //        /// <summary>
    //        ///A test for DalEventContainer Constructor
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void DalEventContainerConstructorTest1()
    //        {
    //            DalEventContainer^  unnamed = nullptr; // TODO: Initialize to an appropriate value
    //            DalEventContainer_Accessor^  target = (gcnew DalEventContainer_Accessor(unnamed));
    //            Assert::Inconclusive(L"TODO: Implement code to verify target");
    //        }

// No need to run test case for constructor as it is private and does nothing as of now,
// implemented for singleton pattern
    //        /// <summary>
    //        ///A test for DalEventContainer Constructor
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void DalEventContainerConstructorTest()
    //        {
    //            DalEventContainer_Accessor^  target = (gcnew DalEventContainer_Accessor());
    //            Assert::Inconclusive(L"TODO: Implement code to verify target");
    //        }
    };
}
namespace TestDal {
    
}
