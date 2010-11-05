
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalCuffPulseEventArgsTest;
    
    
    /// <summary>
///This is a test class for DalCuffPulseEventArgsTest and is intended
///to contain all DalCuffPulseEventArgsTest Unit Tests
///</summary>
    [TestClass]
    public ref class DalCuffPulseEventArgsTest
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
            ///A test for data
            ///</summary>
    public: [TestMethod]
            void dataTest()
            {
                unsigned short data = 100; // set data
                // Initialize to an appropriate data value
                DalCuffPulseEventArgs^  target = (gcnew DalCuffPulseEventArgs(data)); 
                unsigned short expected = 100; // expected set data
                unsigned short actual;
                
                actual = target->data;
                Assert::AreEqual(expected, actual); // should be same as what is passed to contructor
                //Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
            /// <summary>
            ///A test for DalCuffPulseEventArgs Constructor
            ///</summary>
    public: [TestMethod]
            void DalCuffPulseEventArgsConstructorTest()
            {
                unsigned short data = 555; // Initialize to an some value
                DalCuffPulseEventArgs^  target = (gcnew DalCuffPulseEventArgs(data));

                unsigned short expected = 555; // expected set data
                unsigned short actual;
                
                actual = target->data;
                Assert::AreEqual(expected, actual); // should be same as what is passed to contructor

                //Assert::Inconclusive(L"TODO: Implement code to verify target");
            }
    };
}
namespace TestDal {
    
}
