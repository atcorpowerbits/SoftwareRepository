
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
using namespace System::IO;
namespace TestDal {
    using namespace System;
    ref class DalSimulationFileTest;
	using namespace AtCor::Scor::DataAccess;
    
    
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

			void SetPath()
			{
				String^ path = Directory::GetCurrentDirectory(); 
				//Directory::SetCurrentDirectory("D:\\Deepak Share\\Sprint 5\\Scor\\TestResults");
				
				Directory::SetCurrentDirectory("D:\\Deepak\\Scor\\TestResults");
				
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

		/*	public: [TestMethod]
			void ConstructorTestTest()
			{
				SetPath();

				DalSimulationFile ^actual = gcnew DalSimulationFile();
				Assert::IsNotNull(actual);
			}*/

			//public: [TestMethod]
			//void GetNextValuesFourTest()
			//{
			//	DalSimulationFile  ^actual = gcnew DalSimulationFile();
			//	int val1, val2, val3, val4;
			//	bool retVal;

			//	//test null reader;
			//	try
			//	{
			//		actual->GetNextValues(val1, val2, val3, val4);
			//	}
			//	catch(DaleXception ^Dalex)
			//	{
			//		Assert::IsTrue(true);

			//	}

			//	DalSimulationFile ^ _cuffTimerSimulationFile = gcnew DalSimulationFile("cuff_timer.dat");
			//	for (int i = 0; i<100; i++)
			//	{
			//		retVal = _cuffTimerSimulationFile->GetNextValues(val1, val2, val3, val4);
			//		Assert::IsTrue(retVal);
			//	}
			//
			//}

			//public: [TestMethod]
			//void GetNextValuesTwoTest()
			//{
			//	DalSimulationFile  ^actual = gcnew DalSimulationFile();
			//	int val1, val2, val3, val4;
			//	bool retVal;

			//	//test null reader;
			//	try
			//	{
			//		actual->GetNextValues(val1, val2);
			//	}
			//	catch(DaleXception ^Dalex)
			//	{
			//		Assert::IsTrue(true);

			//	}

			//	DalSimulationFile ^ _cuffTimerSimulationFile = gcnew DalSimulationFile("Simulation.dat");
			//	for (int i = 0; i<2000; i++)
			//	{
			//		retVal = _cuffTimerSimulationFile->GetNextValues(val1, val2);
			//		Assert::IsTrue(retVal);
			//	}
			//
			//}


			//public: [TestMethod]
			//void OpenTest()
			//{
			//	

			//	try
			//	{
			//		DalSimulationFile  ^File1 = gcnew DalSimulationFile();
			//		File1->Open();
			//	}
			//	catch (DalExceptio ^dalEx)
			//	{
			//		Assert::IsTrue(true);
			//	}

			//	try
			//	{
			//		DalSimulationFile  ^File2 = gcnew DalSimulationFile("DoesNotExist.dat");
			//		File2->Open();
			//	}
			//	catch (DalExceptio ^dalEx)
			//	{
			//		Assert::IsTrue(true);
			//	}

			//	try
			//	{
			//		//zero length file
			//		DalSimulationFile  ^File3 = gcnew DalSimulationFile("xyz.dat");
			//		File3->Open();
			//	}
			//	catch (DalExceptio ^dalEx)
			//	{
			//		Assert::IsTrue(true);
			//	}


			//	try
			//	{
			//		//zero length file
			//		DalSimulationFile  ^File4 = gcnew DalSimulationFile("Simulation.dat");
			//		bool retVal = File4->Open();
			//		Assert::IsTrue(retVal);
			//	}
			//	catch (DalExceptio ^dalEx)
			//	{
			//		Assert::IsTrue(true);
			//	}
			//}

			//public: [TestMethod]
			//void DestructorTest()
			//		{
			//			DalSimulationFile  ^actual = gcnew DalSimulationFile();
			//			Assert::IsNotNull(actual);
			//			delete actual;
			//			Assert::ISNull(actual);

			//		}

	};
}
namespace TestDal {
    
}
