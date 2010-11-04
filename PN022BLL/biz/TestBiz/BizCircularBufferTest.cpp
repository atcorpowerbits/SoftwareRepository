
#include "StdAfx.h"
#include <biz.h>
#include "StdAfx.h"
#include "StdAfx.h"
using namespace AtCor::Scor::BusinessLogic;
using namespace BIZ_NAMESPACE;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
    ref class BizCircularBufferTest;
    
    
    /// <summary>
///This is a test class for BizCircularBufferTest and is intended
///to contain all BizCircularBufferTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizCircularBufferTest
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
			///A test for Reset
			///</summary>
	public: [TestMethod]
			void ResetTest()
			{
				unsigned short expected;
				unsigned short actual;
				unsigned int bufferSize = 5; // TODO: Initialize to an appropriate value
				BizCircularBuffer^  target = (gcnew BizCircularBuffer(bufferSize)); // TODO: Initialize to an appropriate value
				target->Append(1);
				target->Reset();
				expected = 2;
				target->Append(expected);
				target->ReadNext(actual);
				Assert::AreEqual(expected, actual);
			}
/*
			/// <summary>
			///A test for Dispose
			///</summary>
	public: [TestMethod]
			void DisposeTest()
			{
				unsigned int bufferSize = 0; // TODO: Initialize to an appropriate value
				BizCircularBuffer^  target = (gcnew BizCircularBuffer(bufferSize)); // TODO: Initialize to an appropriate value
				target->Dispose();
				Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
*/
			/// <summary>
			///A test for Append
			///</summary>
	public: [TestMethod]
			void AppendTest()
			{
				unsigned int bufferSize = 3; // TODO: Initialize to an appropriate value
				BizCircularBuffer^  target = (gcnew BizCircularBuffer(bufferSize)); // TODO: Initialize to an appropriate value
				unsigned short data = 10; // TODO: Initialize to an appropriate value
				bool expected = true; // TODO: Initialize to an appropriate value
				bool actual;
				actual = target->Append(data);
				Assert::AreEqual(expected, actual);
				actual = target->Append(data++);
				Assert::AreEqual(expected, actual);
				actual = target->Append(data++);
				Assert::AreEqual(expected, actual);
				actual = target->Append(data++);
				Assert::AreEqual(expected, actual);
				actual = target->Append(data++);
				Assert::AreEqual(expected, actual);
				actual = target->Append(data++);
				Assert::AreEqual(expected, actual);
			}
/*			/// <summary>
			///A test for ~BizCircularBuffer
			///</summary>
	public: [TestMethod]
			void ~BizCircularBufferTest()
			{
				unsigned int bufferSize = 0; // TODO: Initialize to an appropriate value
				BizCircularBuffer^  target = (gcnew BizCircularBuffer(bufferSize)); // TODO: Initialize to an appropriate value
				target->~BizCircularBuffer();
				Assert::Inconclusive(L"A method that does not return a value cannot be verified.");
			}
*/
			/// <summary>
			///A test for BizCircularBuffer Constructor
			///</summary>
	public: [TestMethod]
			void BizCircularBufferConstructorTest()
			{
				unsigned int bufferSize = 100000000; // TODO: Initialize to an appropriate value
				BizCircularBuffer^  target = (gcnew BizCircularBuffer(bufferSize));
				Assert::AreNotEqual(target, nullptr);
			}
			/// <summary>
			///A test for ReadNext
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\BizCircularBufferRead.csv", L"BizCircularBufferRead#csv", DataAccessMethod::Sequential),
				TestMethod]
			void ReadNextTest()
			{
				unsigned int bufferSize = 3; // TODO: Initialize to an appropriate value
				BizCircularBuffer^  target = (gcnew BizCircularBuffer(bufferSize)); // TODO: Initialize to an appropriate value
				bool expected = Convert::ToBoolean(testContextInstance->DataRow["Expected"]); // TODO: Initialize to an appropriate value
				bool actual;
				unsigned short data; // TODO: Initialize to an appropriate value
				unsigned short dataSource = Convert::ToUInt16(testContextInstance->DataRow["AppendData"]); // TODO: Initialize to an appropriate value
				unsigned short dataRead = Convert::ToUInt16(testContextInstance->DataRow["ReadData"]); // TODO: Initialize to an appropriate value
				actual = target->Append(dataSource);
				Assert::AreEqual(expected, actual);

				actual = target->ReadNext(data);
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(dataRead, data);

				actual = target->Append(dataSource);
				Assert::AreEqual(expected, actual);

				actual = target->Append(dataSource);
				Assert::AreEqual(expected, actual);

				actual = target->Append(dataSource);
				Assert::AreEqual(expected, actual);

				actual = target->Append(dataSource);
				Assert::AreEqual(expected, actual);

				actual = target->Append(dataSource);
				Assert::AreEqual(expected, actual);

				actual = target->Append(dataSource);
				Assert::AreEqual(expected, actual);

				actual = target->Append(dataSource);
				Assert::AreEqual(expected, actual);

				actual = target->ReadNext(data);
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(dataRead, data);

				actual = target->ReadNext(data);
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(dataRead, data);

				actual = target->ReadNext(data);
				Assert::AreEqual(expected, actual);
				Assert::AreEqual(dataRead, data);

				actual = target->ReadNext(data);
				Assert::AreNotEqual(expected, actual);
			}
			/// <summary>
			///A test for ReadBuffer
			///</summary>
public: [TestMethod]
		void ReadBufferTest()
		{
			unsigned int bufferSize = 10; 
			BizCircularBuffer^  target = (gcnew BizCircularBuffer(bufferSize)); 
			cli::array< unsigned short >^  buffer; 
			unsigned int bufferSizeExpected = 10; 
			bufferSize = 0;
			unsigned short startIndexExpected = 0; 
			unsigned short startIndex = 0; 
			unsigned short endIndexExpected = 1; 
			unsigned short endIndex = 0; 
			unsigned short data = 5;
			target->Append(data);
			buffer = target->ReadBuffer( bufferSize, startIndex, endIndex );
			Assert::AreEqual(buffer[0], data);
			Assert::AreEqual(bufferSizeExpected, bufferSize);
			Assert::AreEqual(startIndexExpected, startIndex);
			Assert::AreEqual(endIndexExpected, endIndex);
		}
};
}
namespace TestBiz {
    
}
