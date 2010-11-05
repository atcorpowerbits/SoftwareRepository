
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalSimulationFileTest;
    
    
    /// <summary>
///This is a test class for DalSimulationFileTest and is intended
///to contain all DalSimulationFileTest Unit Tests
///</summary>
    [TestClass]
    public ref class DalSimulationFileTest
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
            public: [TestInitialize]
            System::Void MyTestInitialize()
            {
                // set the path to appropriet folder
                System::IO::Directory::SetCurrentDirectory("D:\\Shriganesh\\ProjectData\\AtCor\\src\\dal\\TestResults");
            }
            
            //Use TestCleanup to run code after each test has run
            //public: [TestCleanup]
            //System::Void MyTestCleanup()
            //{
            //}
            //
#pragma endregion
            /// <summary>
            ///A test for ResetFileStreamPosition
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void ResetFileStreamPositionTest()
            {
                // set the path to appropriet folder
                //System::IO::Directory::SetCurrentDirectory("D:\\Shriganesh\\Project Data\\AtCor\\src\\dal\\TestResults");
                String^ strp = System::IO::Directory::GetCurrentDirectory();
                DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor(".\\simulation\\pwv\\Default.dat")); 
                bool expected = true; 
                bool actual;
                actual = target->ResetFileStreamPosition();
                Assert::AreEqual(expected, actual);
                target->CloseFile();
//                Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
            /// <summary>
            ///A test for OpenFile
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void OpenFileTest()
            {
                // set the path to appropriet folder
                //System::IO::Directory::SetCurrentDirectory("D:\\Shriganesh\\Project Data\\AtCor\\src\\dal\\TestResults");

                DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); 
                
                target->filePath = ".\\simulation\\pwv\\Default.dat";

                bool expected = true; // TODO: Initialize to an appropriate value
                bool actual;
                actual = target->OpenFile();
                Assert::AreEqual(expected, actual);
                target->CloseFile();
                //Assert::Inconclusive(L"Verify the correctness of this test method.");
            }
// These methods are added by the compiler
    //        /// <summary>
    //        ///A test for Dispose
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void DisposeTest1()
    //        {
    //            DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); // TODO: Initialize to an appropriate value
    //            target->Dispose();
    //            Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
    //        }
    //        /// <summary>
    //        ///A test for Dispose
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        void DisposeTest()
    //        {
    //            DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); // TODO: Initialize to an appropriate value
    //            bool unnamed = false; // TODO: Initialize to an appropriate value
    //            target->Dispose(unnamed);
    //            Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
    //        }
            /// <summary>
            ///A test for CloseFile
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void CloseFileTest()
            {
                DalSimulationFile_Accessor^  target;
                try{
                // first open the file and then close it again and check return value
                target = (gcnew DalSimulationFile_Accessor("simulation\\pwv\\Default.dat")); 
                bool expected = true; 
                bool actual;
                actual = target->CloseFile();
                Assert::AreEqual(expected, actual);
                }
                catch (DalException^ errDal)
                {
                    // if file is already open, then close it here
                    String^ errMsg = errDal->ErrorString;
                    target->CloseFile();
                }
                //Assert::Inconclusive(L"Verify the correctness of this test method.");
            }

// Cannot test destructor
    //        /// <summary>
    //        ///A test for ~DalSimulationFile
    //        ///</summary>
    //public: [TestMethod]
    //        [DeploymentItem(L"dal.dll")]
    //        ~DalSimulationFileTest()
    //        {
    //            DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor()); // TODO: Initialize to an appropriate value
    //            //target->~DalSimulationFile();
    //            //Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
    //        }
            /// <summary>
            ///A test for DalSimulationFile Constructor
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void DalSimulationFileConstructorTest1()
            {
                String^  sourceFilePath = ".\\simulation\\pwv\\Default.dat";
                DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor(sourceFilePath));

                Assert::AreEqual(sourceFilePath, target->filePath);
                target->CloseFile();
                //Assert::Inconclusive(L"TODO: Implement code to verify target");
            }

// this constructor does nothing
            /// <summary>
            ///A test for DalSimulationFile Constructor
            ///</summary>
    public: [TestMethod]
            [DeploymentItem(L"dal.dll")]
            void DalSimulationFileConstructorTest()
            {
                DalSimulationFile_Accessor^  target = (gcnew DalSimulationFile_Accessor());
                target->CloseFile();
                //Assert::Inconclusive(L"TODO: Implement code to verify target");
            }
    };
}
namespace TestDal {
    
}
