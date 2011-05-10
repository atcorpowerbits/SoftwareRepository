/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalDataBuffer.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :      DalDataBuffer class code file.
*/

#include "stdafx.h"
#include "DalDataBuffer.h"

using namespace System::Threading;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			
				// Constructor for the structure. 
				DalPwvDataStruct::DalPwvDataStruct()
				{
					//Initialize all elements to -1 to indicate that the value is unusable.
					tonometerData = -1;
					cuffPulseData = -1;
					cuffPressure = -1;
					countdownTimer = -1;
				}

				//Copy constructor to work around the reference copy function
				DalPwvDataStruct::DalPwvDataStruct(DalPwvDataStruct% valueParameter)
				{
					//copy the values from the parameter to the calling object.
					tonometerData = valueParameter.tonometerData;
					cuffPulseData = valueParameter.cuffPulseData;
					cuffPressure = valueParameter.cuffPressure;
					countdownTimer = valueParameter.countdownTimer;
				}

			DalDataBuffer::DalDataBuffer()
			{
				//rollOverFlag = false; //remove as per fxCop
				
				//Set all values to -1 to indicate an unready state.
				_arraySize = arrayLastElementIndex = startIndex  = bufferIndex  = -1;

				//make pointer null
				DalDataBuffer::bufferPointer = nullptr;
			}

			DalDataBuffer::DalDataBuffer(const AtCor::Scor::DataAccess::DalDataBuffer ^)
			{
				//overloaded copy constructor.
				//Does nothing
			}

			DalDataBuffer^ DalDataBuffer::operator =(const DalDataBuffer)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}

			//create the array
			bool DalDataBuffer::CreateBuffer(int captureTime, int samplingRate)
			{
				System::Type^ typevar ; //the type of element to create an array
				DalPwvDataStruct tempStructVaraiable; //temporary structure valriable to create array

				if ((captureTime <=0) || (samplingRate <=0))
				{
					//check if either parameter is negative and signall error.
					
					//Arguements are invalid
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs,ErrorSeverity::Exception);
				}
				
				//first clear all variables
				rollOverFlag = false;

				//reset values to indicate unready state
				_arraySize = arrayLastElementIndex = startIndex  = bufferIndex  = -1;
				DalDataBuffer::bufferPointer = nullptr;//clear the array before recreating

				//Find the size of the array.
				//We will add two seconds to the capture time to compensate for cuff inflation.
				//Since this array uses one empty element to avoid the buffer full/ buffer emepty conflic. We are adding 1 to the size as compensation.
				_arraySize = (((captureTime +2)*samplingRate) + 1);

				//The index of the last element, needed for calculations
				arrayLastElementIndex = _arraySize-1;
				
				//set indices to the first element
				startIndex = 0;
				bufferIndex = 0;

				try 
				{
					//get the type of the structure and store it in typevar
					typevar = tempStructVaraiable.GetType();

					//create an array using the obtained type.
					bufferPointer = Array::CreateInstance(typevar , DalDataBuffer::_arraySize);
				}
				catch(Exception^)
				{
					//first reset all indices to -1 so as to signal that the array creation was unsuccesful.
					_arraySize = arrayLastElementIndex=startIndex= bufferIndex =-1;
					bufferPointer = nullptr;

					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrArrayCreateFailedErrCd, CrxStructCommonResourceMsg::DalErrArrayCreateFailed, ErrorSeverity::Exception);
				}

				return true; //if we reach here then it was successful

			}

			//obtain the range of values.
			bool DalDataBuffer::GetAllValues(int& readStartIndex, int& readEndIndex)
			{

				if (bufferPointer == nullptr)
				{
					//array hasnt been created yet
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferNotCreatedErrCd, CrxStructCommonResourceMsg::DalErrBufferNotCreated, ErrorSeverity::Exception);
				}

				//check if a rollover has happened only once.
				if (rollOverFlag == false)
				{
					if ((startIndex == 0) && (bufferIndex == 0))
					{
						//both indices point to the start so we will return -1 to signal that the buffer is empty.
						//we wont check for buffer empty condition as it is irrelevant to the BLL
						readStartIndex = readEndIndex = -1;
						return false;
					}
					else
					{
						readStartIndex = 0;// BL will always read from the first to the latest element in any order
						readEndIndex = bufferIndex - 1; //bufferIndex point to the next writable location so -1
					}

				}
				else
				{
					//if rollover has taken place at least once then we will send the entire array
					readStartIndex = 0;
					readEndIndex = arrayLastElementIndex;
				}
				return true;
			}


			//retun the requested rannge of values.
			int DalDataBuffer::GetNextValues(int requestedValues, int % readStartIndex )
			{
				int returnedvalues = -1; //to singnal unready

				if (bufferPointer == nullptr)
				{
					//array hasnt been created yet
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferNotCreatedErrCd, CrxStructCommonResourceMsg::DalErrBufferNotCreated, ErrorSeverity::Exception);
				}

				if (requestedValues <=0)
				{
					//illegal parameter: the number of requested values must be positive integer
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs,ErrorSeverity::Exception);
				}
				
				if (requestedValues > (_arraySize -1))
				{
					//request size is larger than size of array.
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrRequestTooLargeErrCd, CrxStructCommonResourceMsg::DalErrRequestTooLarge, ErrorSeverity::Exception);
				}

				
				if (bufferIndex == startIndex)
				{
					//if buffer is empty
					readStartIndex  = -1;
					
					return 0; //no elements to read
				}
				else if ( bufferIndex > startIndex)
				{
					//caluclate the start position and offset.
					if ((startIndex) <= (bufferIndex -1))
					{
						//Set ReadstartIndex from the oldest element
						readStartIndex =  startIndex ;
					}
					
					if ((startIndex  + requestedValues -1 ) <= ( bufferIndex -1))
					{ 
						//if the requested values are less than or equal to the available values
						returnedvalues = requestedValues;
					}
					else if ((startIndex  + requestedValues -1 ) > ( bufferIndex -1))
					{
						//if the requested values are too many then only return the actual number of events
						returnedvalues =  (bufferIndex - 1) - startIndex + 1;
					}

					//increment the SI by the actual number of returned values only.
					//ensure rollover is accounted for
					startIndex= ((startIndex + returnedvalues)% _arraySize) ;
				}
				else if (bufferIndex < startIndex)
				{
					//set reading start position
					readStartIndex = startIndex;

					if ( (startIndex + requestedValues - 1) <=  (_arraySize - 1))
					{
						//if the requested values will not result in a rollover.
						returnedvalues = requestedValues ;
						//increment SI
						startIndex = (startIndex + returnedvalues) % _arraySize;
					}
					else if ( (startIndex + requestedValues - 1) >  (_arraySize - 1))
					{
						//if the request will result in a rollover
						int tempCount = 0; 
						
						// store the count of reads before a rollover
						tempCount = (_arraySize - 1) - startIndex + 1;

						if (bufferIndex == 0)
						{
							//If BI is at 0 there are no more elements to read from the front of the array
							returnedvalues = tempCount;
							startIndex = 0;
						}
						else
						{
							//elements to be read from front of array.

							//fin the number of elements remaining to be read
							//check if they will exceed the available range
							if ((requestedValues - tempCount -1) <= (bufferIndex -1)) 
							{
								//the requested range is available
								returnedvalues = requestedValues;
								startIndex = (requestedValues - tempCount);
							}
							else
							{
								//calulate the available range taking rollover into account
								//return only the actual 
								returnedvalues = tempCount + (bufferIndex -1) + 1;
								startIndex = bufferIndex;
							}

						}
					}
				}

				//finally return the actual count
				return returnedvalues; 
			}


		//get the value at a specified index. Account for rollover.
			DalPwvDataStruct^ DalDataBuffer::GetValueAt(int readStartIndex, int offsetFromReadStartIndex)
			{
				int indexCurElement; //to store the current element index

				if (bufferPointer == nullptr)
				{
					//array hasnt been created yet
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferNotCreatedErrCd, CrxStructCommonResourceMsg::DalErrBufferNotCreated, ErrorSeverity::Exception);
				}

				//caclulate aexact index from offset and account for rollover.
				indexCurElement = (readStartIndex + offsetFromReadStartIndex)%_arraySize;
				
				//return the element at the specified index.
				return (DalPwvDataStruct^)bufferPointer->GetValue(indexCurElement);
			}


			//write an element to the array
	
			bool DalDataBuffer::WriteDataToBuffer(DalPwvDataStruct dataToWrite)
			{
				try
				{
					if (bufferIndex == -1)
					{
						//array hasnt been created yet
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferNotCreatedErrCd, CrxStructCommonResourceMsg::DalErrBufferNotCreated, ErrorSeverity::Exception);
					}
					
					lockArray->WaitOne(); //lock the array to prevent simultaneous access.

					//check if array is full( BI = SI-1)
					//if it is then push SI further as we add elements
					if (bufferIndex == (startIndex-1))
					{
						//increment SI and rollover
						startIndex= (startIndex+1)%_arraySize;
					}
					else if(( bufferIndex == arrayLastElementIndex) && (startIndex == 0 ))
					{
						//check if BI is at the last element and ensure that the rollover of SI is done
						startIndex= (startIndex+1)%_arraySize;
					}

					//set the value at the position
					bufferPointer->SetValue(%dataToWrite, bufferIndex);

					//check if the rolover condition is about to be fullfiled before it actually takes place
					if ((rollOverFlag == false) && (bufferIndex == arrayLastElementIndex))
					{
						//this is only needed for BLL
						rollOverFlag = true;
					}
					//increment the BI
					bufferIndex = (bufferIndex+1)%_arraySize;
					
					//release lock
					lockArray->ReleaseMutex();
					return true;
				}
				catch(ScorException^)
				{
					throw;
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
			}

			bool DalDataBuffer::IsBufferEmpty()
			{
				if (bufferPointer == nullptr)
				{
					//array hasnt been created yet
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrBufferNotCreatedErrCd, CrxStructCommonResourceMsg::DalErrBufferNotCreated, ErrorSeverity::Exception);
				}

				if (bufferIndex == startIndex)
				{
					///the buffer is empty
					return true;
				}
				else
				{
					//in any other condition it is untrue
					return false;
				}
			}

		}
	}
}
