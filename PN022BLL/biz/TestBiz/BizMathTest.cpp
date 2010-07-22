
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
#include "StdAfx.h"
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
namespace TestBiz {
    using namespace System;
    using namespace Biz;
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
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"|DataDirectory|\\TimeToIndex.csv", L"TimeToIndex#csv", DataAccessMethod::Sequential),
				DeploymentItem(L"TestBiz\\TimeToIndex.csv"),
				TestMethod]
			void TimeToIndexTest()
			{
				float pTime = Convert::ToDouble(testContextInstance->DataRow[L"Time"]); 
				int pExpandRate = Convert::ToInt32(testContextInstance->DataRow[L"ExpandRate"]); 
				int pSampleRate = Convert::ToInt32(testContextInstance->DataRow[L"SampleRate"]); 
				int expected = Convert::ToInt32(testContextInstance->DataRow[L"Expected"]); 
				int actual;
				actual = BizMath::TimeToIndex(pTime, pExpandRate, pSampleRate);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for RoundNearest20
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"|DataDirectory|\\RoundNearest20.csv", L"RoundNearest20#csv", DataAccessMethod::Sequential),
				DeploymentItem(L"TestBiz\\RoundNearest20.csv"),
				TestMethod]
			void RoundNearest20Test()
			{
				int pValue = Convert::ToDouble(testContextInstance->DataRow[L"Value"]); 
				int expected = Convert::ToInt32(testContextInstance->DataRow[L"Expected"]); 
				int actual;
				actual = BizMath::RoundNearest20(pValue);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for Round
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"|DataDirectory|\\Round.csv", L"Round#csv", DataAccessMethod::Sequential),
				DeploymentItem(L"TestBiz\\Round.csv"),
				TestMethod]
			void RoundTest()
			{
				double pValue = Convert::ToDouble(testContextInstance->DataRow[L"Value"]); 
				int expected = Convert::ToInt32(testContextInstance->DataRow[L"Expected"]);
				int actual;
				actual = BizMath::Round(pValue);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for IndexToTime
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"|DataDirectory|\\IndexToTime.csv", L"IndexToTime#csv", DataAccessMethod::Sequential),
				DeploymentItem(L"TestBiz\\IndexToTime.csv"),
				TestMethod]
			void IndexToTimeTest()
			{
				int pIndex = Convert::ToInt32(testContextInstance->DataRow[L"Index"]); 
				int pExpandRate = Convert::ToInt32(testContextInstance->DataRow[L"ExpandRate"]); 
				int pSampleRate = Convert::ToInt32(testContextInstance->DataRow[L"SampleRate"]); 
				float expected = Convert::ToDouble(testContextInstance->DataRow[L"Expected"]); 
				float actual;
				actual = BizMath::IndexToTime(pIndex, pExpandRate, pSampleRate);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for GetSplineIndex
			///</summary>
	public: [DataSource(L"Microsoft.VisualStudio.TestTools.DataSource.CSV", L"|DataDirectory|\\GetSplineIndex.csv", L"GetSplineIndex#csv", DataAccessMethod::Sequential),
				DeploymentItem(L"TestBiz\\GetSplineIndex.csv"),
				TestMethod]
			void GetSplineIndexTest()
			{
				float x = Convert::ToDouble(testContextInstance->DataRow[L"X"]);
				int SplineIndex = Convert::ToInt32(testContextInstance->DataRow[L"SplineIndex"]);
				int SplineOrder = Convert::ToInt32(testContextInstance->DataRow[L"SplineOrder"]);
				int pPulseLength = Convert::ToInt32(testContextInstance->DataRow[L"PulseLength"]);
				int expected = Convert::ToInt32(testContextInstance->DataRow[L"Expected"]);
				int actual;
				actual = BizMath::GetSplineIndex(x, SplineIndex, SplineOrder, pPulseLength);
				Assert::AreEqual(expected, actual);
			}
			/// <summary>
			///A test for MaxInArray
			///</summary>
public: [
			DeploymentItem(L"TestBiz\\MaxInArray.csv"),
			TestMethod]
		void MaxInArrayTest()
		{
			cli::array< float >^  pA = {0,1,2,3,4,5};
			int pSize = 6;
			float expected = 5; 
			float actual;
			actual = BizMath::MaxInArray(pA, pSize);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for SmoothArray
		///</summary>
public: [TestMethod]
		void SmoothArrayTest()
		{
			cli::array< float >^  pArray = {0,1,2,3,4,5};
			int pSize = 6;
			int pSmoothOrder = 2;
			bool expected = true;
			bool actual;
			actual = BizMath::SmoothArray(pArray, pSize, pSmoothOrder);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for MinInArray
		///</summary>
public: [TestMethod]
		void MinInArrayTest()
		{
			cli::array< float >^  pA = {0,1,2,3,4,5};
			int pSize = 6;
			float expected = 0;
			float actual;
			actual = BizMath::MinInArray(pA, pSize);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for MaxInArrayIndex
		///</summary>
public: [TestMethod]
		void MaxInArrayIndexTest()
		{
			cli::array< float >^  pA = {0,1,2,3,4,5};
			int pSize = 6;
			int expected = 5;
			int actual;
			actual = BizMath::MaxInArrayIndex(pA, pSize);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for IndexOfExtremum
		///</summary>
public: [TestMethod]
		void IndexOfExtremumTest()
		{
			cli::array< float >^  pProfile = {0,1,2,3,4,5,4,3,2,1,0};
			bool pMinOrMax = true; 
			bool pOnlyFirst = true; 
			int i1 = 1; 
			int i2 = 11; 
			bool pLessOrMore = true; 
			float pLessOrMoreThan = 0; 
			int expected = 5;
			int actual;
			actual = BizMath::IndexOfExtremum(pProfile, pMinOrMax, pOnlyFirst, i1, i2, pLessOrMore, pLessOrMoreThan);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for FunctionValue
		///</summary>
public: [TestMethod]
		void FunctionValueTest()
		{
			cli::array< float >^  pF = {0,1,2,3,4,5,4,3,2,1,0};
			int pNofPoints = 11;
			float pX = 6;
			float expected = 4;
			float actual;
			actual = BizMath::FunctionValue(pF, pNofPoints, pX);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for SmoothDerivative1
		///</summary>
public: [TestMethod]
		void SmoothDerivative1Test()
		{
			cli::array< float >^  F = {0,1,2,3,4,5,4,3,2,1,0};
			int NofPoints = 11;
			int SmoothOrder = 3;
			float pDt = 1; 
			cli::array< float >^  pDer1 = gcnew array< float >(11);
			float pMax = 0;
			float pMaxExpected = 1;
			BizMath::SmoothDerivative1(F, NofPoints, SmoothOrder, pDt, pDer1, pMax);
			Assert::AreEqual(pMaxExpected, pMax);
		}
		/// <summary>
		///A test for Spline
		///</summary>
public: [TestMethod]
		void SplineTest()
		{
			float x = 1.5; 
			cli::array< float >^  Profile = {0,1,2,3,4,5,4,3,2,1,0};
			int SplineOrder = 3; 
			float Value = 0;
			float ValueExpected = 1.5; 
			BizMath::Spline(x, Profile, SplineOrder, Value);
			Assert::AreEqual(ValueExpected, Value);
		}
		/// <summary>
		///A test for MinMaxInArray
		///</summary>
public: [TestMethod]
		void MinMaxInArrayTest1()
		{
			cli::array< short >^  pA = {0,1,2,3,4,5,4,3,2,1,0};
			int pSize = 11;
			short pMin = 0; 
			short pMinExpected = 0; 
			short pMax = 0; 
			short pMaxExpected = 5; 
			bool expected = true;
			bool actual;
			actual = BizMath::MinMaxInArray(pA, pSize, pMin, pMax);
			Assert::AreEqual(pMinExpected, pMin);
			Assert::AreEqual(pMaxExpected, pMax);
			Assert::AreEqual(expected, actual);
		}
		/// <summary>
		///A test for MinMaxInArray
		///</summary>
public: [TestMethod]
		void MinMaxInArrayTest()
		{
			cli::array< float >^  pA = {0,1,2,3,4,5,4,3,2,1,0};
			int pSize = 11; 
			float pMin = 0; 
			float pMinExpected = 0; 
			float pMax = 0;
			float pMaxExpected = 5; 
			bool expected = true; 
			bool actual;
			actual = BizMath::MinMaxInArray(pA, pSize, pMin, pMax);
			Assert::AreEqual(pMinExpected, pMin);
			Assert::AreEqual(pMaxExpected, pMax);
			Assert::AreEqual(expected, actual);
		}
};
}
namespace TestBiz {
    
}
