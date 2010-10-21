﻿
#include "StdAfx.h"
#include <biz.h>
using namespace BIZ_NAMESPACE;

using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
	ref class BizMathTest;
    
    
    /// <summary>
///This is a test class for BizMathTest and is intended
///to contain all BizMathTest Unit Tests
///</summary>
	[TestClass]
	public ref class BizMathTest
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
			///A test for TimeToIndex
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\TimeToIndex.csv", L"TimeToIndex#csv", DataAccessMethod::Sequential),

				TestMethod]
			void TimeToIndexTest()
			{
				float time = Convert::ToSingle(testContextInstance->DataRow[L"Time"]); 
				unsigned short expandRate = Convert::ToUInt16(testContextInstance->DataRow[L"ExpandRate"]); 
				unsigned short sampleRate = Convert::ToUInt16(testContextInstance->DataRow[L"SampleRate"]); 
				short indexExpected = Convert::ToInt16(testContextInstance->DataRow[L"Index"]); 
				short index = 0;
				bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
				bool actual;
				actual = BizMath::TimeToIndex(time, expandRate, sampleRate, index);
				Assert::AreEqual(indexExpected, index);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for RoundNearest20
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\RoundNearest20.csv", L"RoundNearest20#csv", DataAccessMethod::Sequential),

				TestMethod]
			void RoundNearest20Test()
			{
				short input = Convert::ToInt16(testContextInstance->DataRow[L"Input"]); 
				short outputExpected = Convert::ToInt16(testContextInstance->DataRow[L"Output"]); 
				short output = 0;
				bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
				bool actual;
				actual = BizMath::RoundNearest20(input, output);
				Assert::AreEqual(outputExpected, output);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Round
			///</summary>
	public: [
				DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\Round.csv", L"Round#csv", DataAccessMethod::Sequential),

				TestMethod]
			void RoundTest()
			{
				float input = Convert::ToSingle(testContextInstance->DataRow[L"Input"]); 
				short outputExpected = Convert::ToInt16(testContextInstance->DataRow[L"Output"]); 
				short output = 0;
				bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
				bool actual;
				actual = BizMath::Round(input, output);
				Assert::AreEqual(outputExpected, output);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for IndexToTime
			///</summary>
	public: [

				DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\IndexToTime.csv", L"IndexToTime#csv", DataAccessMethod::Sequential),
					TestMethod]
			void IndexToTimeTest()
			{
				unsigned short index = Convert::ToUInt16(testContextInstance->DataRow[L"Index"]); 
				unsigned short expandRate = Convert::ToUInt16(testContextInstance->DataRow[L"ExpandRate"]); 
				unsigned short sampleRate = Convert::ToUInt16(testContextInstance->DataRow[L"SampleRate"]); 
				float timeExpected = Convert::ToSingle(testContextInstance->DataRow[L"Time"]); 
				float time = 0;
				bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]); 
				bool actual;
				actual = BizMath::IndexToTime(index, expandRate, sampleRate, time);
				Assert::AreEqual(timeExpected, time);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for GetSplineIndex
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\GetSplineIndex.csv", L"GetSplineIndex#csv", DataAccessMethod::Sequential),

				TestMethod]
			void GetSplineIndexTest()
			{
				float abscissa = Convert::ToSingle(testContextInstance->DataRow[L"Abscissa"]);
				unsigned short splineIndex = Convert::ToUInt16(testContextInstance->DataRow[L"SplineIndex"]);
				unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);
				unsigned short newSplineIndexExpected = Convert::ToUInt16(testContextInstance->DataRow[L"NewSplineIndex"]);
				unsigned short newSplineIndex = 0;
				bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
				bool actual;
				actual = BizMath::GetSplineIndex(abscissa, splineIndex, size, newSplineIndex);
				Assert::AreEqual(newSplineIndexExpected, newSplineIndex);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for MaximumInArray
			///</summary>
public: [

			DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\MaxInArray.csv", L"MaxInArray#csv", DataAccessMethod::Sequential),

				TestMethod]
		void MaxInArrayTest()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< float >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);;
			float maximumExpected = Convert::ToSingle(testContextInstance->DataRow[L"Maximum"]);; 
			float maximum = 0;
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);; 
			bool actual;
			actual = BizMath::MaximumInArray(input, size, maximum);
			Assert::AreEqual(maximumExpected, maximum);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for SmoothArray
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\SmoothArray.csv", L"SmoothArray#csv", DataAccessMethod::Sequential),
			TestMethod]
		void SmoothArrayTest()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< float >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);;
			String^ outputs = Convert::ToString(testContextInstance->DataRow[L"Output"]);
			cli::array< float >^  outputExpected = nullptr;
			if (outputs != "nullptr")
			{
				array<String^>^ outputsArray = outputs->Split(',');
				outputExpected = Array::ConvertAll(outputsArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);; 
			bool actual;
			actual = BizMath::SmoothArray(input, size);
			CollectionAssert::AreEqual(outputExpected, input);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for MinimumInArray
		///</summary>
public: [

			DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\MinInArray.csv", L"MinInArray#csv", DataAccessMethod::Sequential),
				TestMethod]
		void MinimumInArrayTest()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< float >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);;
			float minimumExpected = Convert::ToSingle(testContextInstance->DataRow[L"Minimum"]);; 
			float minimum = 0;
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);; 
			bool actual;
			actual = BizMath::MinimumInArray(input, size, minimum);
			Assert::AreEqual(minimumExpected, minimum);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for MaximumInArrayIndex
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\MaxInArrayIndex.csv", L"MaxInArrayIndex#csv", DataAccessMethod::Sequential),
			TestMethod]
		void MaximumInArrayIndexTest()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< float >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);;
			unsigned short maximumIndexExpected = Convert::ToUInt16(testContextInstance->DataRow[L"MaximumIndex"]);; 
			unsigned short maximumIndex = 0;
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);; 
			bool actual;
			actual = BizMath::MaximumInArrayIndex(input, size, maximumIndex);
			Assert::AreEqual(maximumIndexExpected, maximumIndex);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for IndexOfExtremum
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\IndexOfExtremum.csv", L"IndexOfExtremum#csv", DataAccessMethod::Sequential),
			TestMethod]
		void IndexOfExtremumTest()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< float >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			unsigned short start = Convert::ToUInt16(testContextInstance->DataRow[L"Start"]);;
			unsigned short end = Convert::ToUInt16(testContextInstance->DataRow[L"End"]);;
			float threshold = Convert::ToSingle(testContextInstance->DataRow[L"Threshold"]);;
			unsigned short indexExpected = Convert::ToUInt16(testContextInstance->DataRow[L"Index"]);; 
			unsigned short index = 0;
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);; 
			bool actual;
			actual = BizMath::IndexOfExtremum(input, start, end, threshold, index);
			Assert::AreEqual(indexExpected, index);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for FunctionValue
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\FunctionValue.csv", L"FunctionValue#csv", DataAccessMethod::Sequential),
			TestMethod]
		void FunctionValueTest()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Function"]);
			cli::array< unsigned short >^  function = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				function = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);;
			float argument = Convert::ToSingle(testContextInstance->DataRow[L"Argument"]);;
			float valueExpected = Convert::ToSingle(testContextInstance->DataRow[L"Value"]);; 
			float value = 0;
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);; 
			bool actual;
			actual = BizMath::FunctionValue(function, size, argument, value);
			Assert::AreEqual(valueExpected, value);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for SmoothFirstDerivative
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\SmoothDerivative1.csv", L"SmoothDerivative1#csv", DataAccessMethod::Sequential),
			TestMethod]
		void SmoothDerivative1Test()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< unsigned short >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);
			unsigned short smoothOrder = Convert::ToUInt16(testContextInstance->DataRow[L"SmoothOrder"]);
			float step = Convert::ToSingle(testContextInstance->DataRow[L"Step"]);
			String^ derivatives = Convert::ToString(testContextInstance->DataRow[L"FirstDerivative"]);
			array<String^>^ derivativesArray = derivatives->Split(',');
			cli::array< float >^  firstDerivativeExpected = Array::ConvertAll(derivativesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			cli::array< float >^  firstDerivative = gcnew array< float >(firstDerivativeExpected->Length);
			float maximumExpected = Convert::ToSingle(testContextInstance->DataRow[L"Maximum"]);; 
			float maximum = 0;
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);; 
			bool actual;
			actual = BizMath::SmoothFirstDerivative(input, size, smoothOrder, step, firstDerivative, maximum);
			CollectionAssert::AreEqual(firstDerivativeExpected, firstDerivative);
			Assert::AreEqual(maximumExpected, maximum);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for Spline
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\Spline.csv", L"Spline#csv", DataAccessMethod::Sequential),
			TestMethod]
		void SplineTest()
		{
			float abscissa = Convert::ToSingle(testContextInstance->DataRow[L"Abscissa"]);;
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< float >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			float outputExpected = Convert::ToSingle(testContextInstance->DataRow[L"Output"]);; 
			float output = 0;
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);; 
			bool actual;
			actual = BizMath::Spline(abscissa, input, output);
			Assert::AreEqual(outputExpected, output);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for MinimumMaximumInArray
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\MinMaxInArray1.csv", L"MinMaxInArray1#csv", DataAccessMethod::Sequential),
			TestMethod]
		void MinimumMaximumInArrayTest1()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< unsigned short >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			unsigned short pMinimum = 0; 
			unsigned short pMinimumExpected = Convert::ToUInt16(testContextInstance->DataRow[L"Minimum"]);
			unsigned short pMaximum = 0;
			unsigned short pMaximumExpected = Convert::ToUInt16(testContextInstance->DataRow[L"Maximum"]); 
			bool actual;
			actual = BizMath::MinimumMaximumInArray(input, size, pMinimum, pMaximum);
			Assert::AreEqual(pMinimumExpected, pMinimum);
			Assert::AreEqual(pMaximumExpected, pMaximum);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for MinimumMaximumInArray
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\MinMaxInArray.csv", L"MinMaxInArray#csv", DataAccessMethod::Sequential),
			TestMethod]
		void MinimumMaximumInArrayTest()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< float >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			float pMinimum = 0; 
			float pMinimumExpected = Convert::ToSingle(testContextInstance->DataRow[L"Minimum"]);
			float pMaximum = 0;
			float pMaximumExpected = Convert::ToSingle(testContextInstance->DataRow[L"Maximum"]); 
			bool actual;
			actual = BizMath::MinimumMaximumInArray(input, size, pMinimum, pMaximum);
			Assert::AreEqual(pMinimumExpected, pMinimum);
			Assert::AreEqual(pMaximumExpected, pMaximum);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for ValidateArray
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\ValidateArray.csv", L"ValidateArray#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateArrayTest()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< float >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, float>(Convert::ToSingle));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = BizMath::ValidateArray(input, size);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for ValidateArray
		///</summary>
public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"C:\\projects\\PN022BLL\\biz\\Debug\\ValidateArray1.csv", L"ValidateArray1#csv", DataAccessMethod::Sequential),
			TestMethod]
		void ValidateArrayTest1()
		{
			String^ values = Convert::ToString(testContextInstance->DataRow[L"Input"]);
			cli::array< unsigned short >^  input = nullptr;
			if (values != "nullptr")
			{
				array<String^>^ valuesArray = values->Split(',');
				input = Array::ConvertAll(valuesArray, gcnew Converter<String^, unsigned short>(Convert::ToUInt16));
			}
			unsigned short size = Convert::ToUInt16(testContextInstance->DataRow[L"Size"]);
			bool expected = Convert::ToBoolean(testContextInstance->DataRow[L"Expected"]);
			bool actual;
			actual = BizMath::ValidateArray(input, size);
			Assert::AreEqual(expected, actual);
		}
};
}
namespace TestBiz {
    
}
