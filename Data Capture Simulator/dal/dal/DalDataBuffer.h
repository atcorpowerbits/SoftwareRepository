/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalDataBuffer.h
        
     Author       :		 Deepak D'Souza
 
     Description  :      Header fle for DalDataBuffer class and related structures.
*/

#pragma once

#include "stdafx.h"
#include "DalCommon.h"

using namespace System::Threading;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

/**
* @struct DalPwvDataStruct
* @brief Structure that holds PWV data signals.
*/
			public ref struct DalPwvDataStruct
			{
						public:
							unsigned short tonometerData; /**< Tonometer data */   
							unsigned short cuffPulseData; /**< Cuff Pulse data */
							unsigned short cuffPressure; /**< Cuff Pressure data */
							unsigned short countdownTimer; /**< Countdown Timer interval */

							/**
							* Constructor for the structure. @n
							* Initializes all elements to -1 to indicate that the value is unusable.
							*/
							DalPwvDataStruct();

							/**
							* Copy constructor to work around the reference copy function
							*
							* @param[in]	valueParameter	The value to copy from
							*/
							DalPwvDataStruct(DalPwvDataStruct% valueParameter);
			};
			

			/**
			* @class DalDataBuffer
			* @brief Class to handle the data buffer and provide access methods.
			*/
			public ref class DalDataBuffer{
									private:
										int bufferIndex; /**< Index to the next writing spot in the array. */
										int startIndex; /**< Pointer to the oldest unread element. */
										int _arraySize; /**< Internal element to hold the array size. */
										
										int arrayLastElementIndex; /**< Pointer to the last element in the array. Always equals arraysize-1  */
										bool rollOverFlag; /**< flag to indicate that the rollover has taken place at least once. Needed only for GetAllValues() function. */
										static Mutex^ lockArray = gcnew Mutex(); /**<Mutex to lock the array while writing.*/

										//making private as per fxCop
										Array^ bufferPointer; /**< internal pointer to the array. */
										
										static DalDataBuffer^ _instance = gcnew DalDataBuffer(); /**< Internal pointer to thuis instance. Used to implement singleton.*/
										
										/**
										* Overloaded constructor.@n
										* Resets all indices and pointers.
										*/
										DalDataBuffer();

										/**
										* Overloaded copy constructor. 
										* Used to implement singleton.
										*/
										DalDataBuffer(const DalDataBuffer^);

										/**
										* Overloaded assignment operator. 
										* Used to implement singleton.
										*/
										DalDataBuffer^ operator= (const DalDataBuffer);
										
										
									public:

										/**
										* Returns the current singleton instance.
										*/
										static property DalDataBuffer^ Instance
										{
											DalDataBuffer^ get()
											{
												return DalDataBuffer::_instance;
											};
										};

										/**
										* Returns the current size of the array. @n
										* Hides the actuall arraysize element
										*/
										property int ArraySize
										{
											int get()
											{
												return _arraySize;
											};
										};
										
										/**
										* Returns a pointer to the array. @n
										* Hides the actuall array.t
										*/
										property Array^ DataBuffer
										{
											Array^ get()
											{
												return bufferPointer ;
											};
										};

										/**
										* Creates a circular buffer for the specified capture time and sampling rate. @n
										* The actual buffer size will be :@n
										* ( Capture Time + 2) X Sampling rate + 1 @n
										* The additional 1 ius used because the buffer uses one empty element to prevent conflict between empty and full buffer.
										*
										* @param[in]	captureTime	The capture time in seconds
										* @param[in]	samplingRate	Number of samples per second
										*
										* @return	@c true if the operation was successful @n
										*			@c flase if an error occured.
										*/
										bool CreateBuffer(int captureTime, int samplingRate);

										/**
										* Returns the indices of the first and last data in the buffer.
										* This method should be called by biz layer only. The indices do not reflect the latest data all the time.
										*
										* @param[out]	readStartIndex	Contains the starting index of the buffer. @n
										*								If the buffer has been written to at least once, this parameter will always return 0. 
										*								This is regardless of the actual values of startIndex and bufferIndex.
										* @param[out]	readEndIndex	The ending index of the available data.
										*								Till the first rollver takes place, this always points to the last written data.
										*								After a rollover has taken place it will always point to the last array element.
										*
										* @return	@c true if there is data in the buffer @n
										*			@c false if no data has been written to the buffer at all
										*/
										bool GetAllValues(int& readStartIndex, int& readEndIndex);
										
										/**
										* Returns the value at one specific index.@n
										* This method should only be used after calling GetNextValues() to obtain the next reading position and number of avaible elements.
										*
										* @param[in]	readStartIndex	The index at which the reading should begin
										* @param[in]	offsetFromReadStartIndex	The offset from @c readStartIndex at which the data is to be read.
										*											This should start from @c 0 and loop to (number returned by GetNextValues() - @c 1)
										*
										* @return	Pointer to the requested value
										*
										* @warning	GetValueAt does not do any bound checking. Please restrict to the the values returned by GetNextValues().
										*
										* @see	GetNextValues() 
										*/
										DalPwvDataStruct^ GetValueAt(int readStartIndex, int offsetFromReadStartIndex);
										
										/**
										* Writes the specifed value to the next available spot. @n
										* This method pushes the StartIndex by one if the array is full. It does not return any "buffer full" exception.
										* 
										* @param[in]	dataToWrite	A	DalPwvDataStruct variable filled with the data to be put in the buffer.
										*
										* @return	@c true if the operation was successful @n
										*			@c flase if an error occured.
										*/
										bool WriteDataToBuffer(DalPwvDataStruct dataToWrite) ; //needs to be passed as a value type to prevent reference copy problem
										
										/**
										* Returns an index to the next reading position and the number of readable values.
										* This method should be called first to get the range of available data and then GetValueAt() should be called in a loop to read each individual value.
										*
										* @param[in]	requestedValues	The number of values requested at a time. @n
										*								There is no guaruntee that the reuqested number of values will be returned . To know the actual amount check the return value.
										* @param[out]	readStartIndex	Index to the next readable position in the buffer.
										*
										* @return The actual number of elements that can be read. This can be less than @c requestedValues.
										*
										* @see	GetValueAt()
										*/
										int DalDataBuffer::GetNextValues(int requestedValues, int % readStartIndex );

			};

		}
	}
}