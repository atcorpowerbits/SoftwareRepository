
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AtCor::Scor::DataAccess;
namespace TestDal {
    using namespace System;
    ref class DalActivePortTest;
    
    
    /// <summary>
///This is a test class for DalActivePortTest and is intended
///to contain all DalActivePortTest Unit Tests
///</summary>
	[TestClass]
	public ref class DalActivePortTest
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

	private: static String^ comPortName  = "COM3";
	public:	static DalActivePort_Accessor ^commInterfaceObject = DalActivePort_Accessor::Instance;

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
				DalActivePort_Accessor^  actual;
				actual = DalActivePort_Accessor::Instance;
				Assert::IsNotNull(actual);
			}
			/// <summary>
			///A test for ActiveSerialPortName
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void ActiveSerialPortNameTest()
			{
				String^ actual;
				DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); // TODO: Initialize to an appropriate value
				Assert::IsNotNull(target);
				actual = target->ActiveSerialPortName;
				Assert::IsNull(actual);
			}
			/// <summary>
			///A test for SetSerialPortProperties
			///Run this Test case individually
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetSerialPortPropertiesTest()
			{
				DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); // TODO: Initialize to an appropriate value
				bool actual = false;
				bool expected = true;

				try
				{
					target->CloseActivePort();
				}
				catch(Exception ^ scorex)
				{
					delete scorex;
				}

				actual = target->CreateAndOpenNewSerialPort(comPortName);
				Assert::AreEqual(expected, actual, "Run this Test case individually");

				target->SetSerialPortProperties();
				Assert::AreEqual(115200, target->_serialPort->BaudRate);
			}
			/// <summary>
			///A test for SetActivePortInstance
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetActivePortInstanceTest()
			{
				//DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); // TODO: Initialize to an appropriate value
				//SetActivePortInstance is called internally by SetActivePort. 
				//we cannot Call it seperately since SetActivePortName expects that the _serialPort meber is set
				DalActivePort_Accessor^ target = commInterfaceObject ;
				
				//now call the method
				bool retValue = target->SetActivePortInstance(comPortName);
				Assert::IsTrue(retValue, "Ensure that the portnames are valid and run individually.");
				Assert::AreEqual(comPortName, target->_serialPort->PortName, "Ensure that the portnames are valid and run individually.");
			}
			/// <summary>
			///A test for SetActivePort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void SetActivePortTest()
			{
				DalActivePort_Accessor^  target = commInterfaceObject; 
				target->SetActivePort(comPortName);
				Assert::IsNotNull(target->ActiveSerialPortName);
				Assert::AreEqual(comPortName, target->ActiveSerialPortName);
			}
			/// <summary>
			///A test for op_Assign
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void op_AssignTest()
			{
				DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor()); 
				DalActivePort_Accessor^ unnamed; 
				DalActivePort_Accessor^  expected = nullptr; 
				DalActivePort_Accessor^  actual;
				actual = (target = unnamed);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for CreateAndOpenNewSerialPort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CreateAndOpenNewSerialPortTest()
			{
				DalActivePort_Accessor^ target = commInterfaceObject;
				//Assert::IsNull(target->_serialPort);
				target->CreateAndOpenNewSerialPort(comPortName);
				Assert::IsNotNull(target->_serialPort);
			}
			/// <summary>
			///A test for CloseActivePort
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void CloseActivePortTest()
			{
				bool status; 
				DalActivePort_Accessor^ target = DalActivePort_Accessor::Instance;
				target->SetActivePort(comPortName);
				if (target->_serialPort != nullptr)
				{
					status = target->CloseActivePort();
					Assert::IsTrue(status);
				}
				else
				{
					Assert::Fail("Could not conduct CloseActivePortTest since there is no port");
				}
			}
			/// <summary>
			///A test for DalActivePort Constructor
			///</summary>
	public: [TestMethod]
			[DeploymentItem(L"dal.dll")]
			void DalActivePortConstructorTest()
			{
				bool exceptionOccured = false;
				try
				{
					DalActivePort_Accessor^  target = (gcnew DalActivePort_Accessor());
					target->CreateAndOpenNewSerialPort(comPortName);
					Assert::IsNotNull(target->_serialPort);
					Assert::IsTrue(target->_serialPort->IsOpen);

					target->_serialPort->Close();
				}
				catch(Exception^) 
				{
					exceptionOccured = true;
				}
				
				Assert::IsFalse(exceptionOccured, "Run this test individually");

			}
	};
}
namespace TestDal {
    
}
