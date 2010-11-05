
#include "StdAfx.h"
using namespace AtCor::Scor::DataAccess;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace msclr;
namespace TestDal {
    using namespace System;
    ref class lockTest;
    
    
    /// <summary>
///This is a test class for lockTest and is intended
///to contain all lockTest Unit Tests
///</summary>
    [TestClass]
    public ref class lockTest
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
            ///A test for try_acquire
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void try_acquireTest1()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                TimeSpan _timeout = TimeSpan(); // TODO: Initialize to an appropriate value
                bool expected = false; // TODO: Initialize to an appropriate value
                bool actual;
                actual = target->try_acquire(_timeout);
                Assert::AreEqual(expected, actual);
                Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
            /// <summary>
            ///A test for try_acquire
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void try_acquireTest()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                int _timeout = 0; // TODO: Initialize to an appropriate value
                bool expected = false; // TODO: Initialize to an appropriate value
                bool actual;
                actual = target->try_acquire(_timeout);
                Assert::AreEqual(expected, actual);
                Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
            /// <summary>
            ///A test for release
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void releaseTest()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                target->release();
                Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for op_Implicit
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void op_ImplicitTest()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                String^  expected = System::String::Empty; // TODO: Initialize to an appropriate value
                String^  actual;
                actual = target;
                Assert::AreEqual(expected, actual);
                Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
            /// <summary>
            ///A test for is_locked
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void is_lockedTest()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                bool expected = false; // TODO: Initialize to an appropriate value
                bool actual;
                actual = target->is_locked();
                Assert::AreEqual(expected, actual);
                Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
            /// <summary>
            ///A test for Dispose
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void DisposeTest1()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                target->Dispose();
                Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for Dispose
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void DisposeTest()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                bool unnamed = false; // TODO: Initialize to an appropriate value
                target->Dispose(unnamed);
                Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for acquire
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void acquireTest2()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                TimeSpan _timeout = TimeSpan(); // TODO: Initialize to an appropriate value
                target->acquire(_timeout);
                Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for acquire
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void acquireTest1()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                int _timeout = 0; // TODO: Initialize to an appropriate value
                target->acquire(_timeout);
                Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for acquire
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void acquireTest()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                target->acquire();
                Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for ~lock
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void ~lockTest()
            {
                PrivateObject^  param0 = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(param0)); // TODO: Initialize to an appropriate value
                target->~lock();
                Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
            }
            /// <summary>
            ///A test for lock Constructor
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void lockConstructorTest()
            {
                DalEventContainer^  _object = nullptr; // TODO: Initialize to an appropriate value
                lock_Accessor^  target = (gcnew lock_Accessor(_object));
                Assert::Inconclusive(L"TODO: Implement code to verify target");
            }
    };
}
namespace TestDal {
    
}
