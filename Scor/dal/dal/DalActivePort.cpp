/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :      DalActivePort.cpp
        
     Author       :		 Deepak D'Souza
 
     Description  :     Source file for DalActivePort class
*/
#include "stdafx.h"
#include "DalActivePort.h"
#include "DalCommon.h"
#include "DalStagingQueue.h"
#include "DalStatusHandler.h" //TODO remove later
#include "DalBinaryConversions.h"
#include "DalCommandInterface.h"
#include "DalEventContainer.h"


using namespace System;
using namespace System::IO::Ports;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;

namespace AtCor{ 
	namespace Scor { 
		namespace DataAccess{

			DalActivePort::DalActivePort()
			{
				 _lockObject = gcnew Object(); 
				
				try
				{
					_serialPort = gcnew SerialPort();
					SetSerialPortProperties();

					//TODO: temporary disabling handler
					//Register the handler to listen to the port events
					_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(this, &DalActivePort::DataReceviedHandler);

					//serialDataWasRecieved = true; //should be true before first check;

					//Deepak -moving logic to another class to reduce events
					////Create a timer and register its listener. Do not start it!
					/*timeoutCheckTimer= gcnew Timers::Timer(DalConstants::StreamingTimeoutCheckerInterval);
					timeoutCheckTimer->Elapsed += gcnew ElapsedEventHandler(this, &DalActivePort::CheckStreamingTimeout); */
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

			DalActivePort^ DalActivePort::operator =(AtCor::Scor::DataAccess::DalActivePort)
			{
				//overloaded assignment operator.
				//used to implement singleton.
				return this;
			}

			bool DalActivePort::SetActivePort(System::String ^serialPortName)
			{
				CrxLogger::Instance->Write("DalActivePort::SetActivePort called with port: " + serialPortName, ErrorSeverity::Debug);
				bool returnValue;
				//if ((String::Empty == serialPortName) ||(nullptr == serialPortName)) //removed by FxCop
				if (String::IsNullOrEmpty(serialPortName))
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs,ErrorSeverity::Exception);
				}

				Monitor::Enter(_lockObject);
				try
				{

				//if there is a serial port then set the portname to this 
				if (_serialPort)
				{
						//call the method to set the port name for the current serial port object.
						returnValue = SetActivePortInstance(serialPortName);
						if (!returnValue)
						{
							return false;
						}
				}
				else
				{
						if(false == CreateAndOpenNewSerialPort(serialPortName))
						{
							return false;
						}

					}
				}
				catch(ScorException^)
				{
					throw;
					}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				finally
				{
					Monitor::Exit(_lockObject);
				}

				CrxLogger::Instance->Write("DalActivePort::SetActivePort returning true." , ErrorSeverity::Debug);
				return true;
			}



			bool DalActivePort::SetActivePortInstance(String^ serialPortName)
			{
				Monitor::Enter(_lockObject);	
				try
					{
						//close the serial port if already open
						if (_serialPort->IsOpen)
						{
							_serialPort->Close();
						}

						//assign the name to the curres SP object
						_serialPort->PortName = serialPortName;
						SetSerialPortProperties();
						
						if (!(_serialPort->IsOpen))
						{
							_serialPort->Open();
						}


					}
					catch(IOException ^)
					{
						return false;
					}
					catch(Exception^  excepObj)
					{
						throw gcnew ScorException(excepObj);
					}
					finally
					{
						Monitor::Exit(_lockObject);
					}

				return true;
			}


			bool DalActivePort::CreateAndOpenNewSerialPort(String^ newPortName)
			{
				
				//do not accept null or empty string
				if(String::IsNullOrEmpty(newPortName))
				{
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidArgsErrCd, CrxStructCommonResourceMsg::DalErrInvalidArgs,ErrorSeverity::Exception);
				}
				

				Monitor::Enter(_lockObject);
				try
				{

				//check if the active port is set 
				//close it and delete it
				if (_serialPort)
				{
					if ( false == CloseActivePort())
					{
						//since there is an active port and it could not be closed
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrActivePortCloseFailedErrCd, CrxStructCommonResourceMsg::DalErrActivePortCloseFailed, ErrorSeverity::Exception);
					}
				}

				//cannopt allow default port creation

					/*try
					{*/
					_serialPort = gcnew SerialPort(newPortName);
					SetSerialPortProperties();
					/*}*/
					

				//open it and see if it is avaliable
				//ISOpen will return false even if the port is opened by us 
				//but is in use by another process so handle it
				if (!(_serialPort->IsOpen))
				{
					try
					{
						_serialPort->Open();
						//readerThread->Start();//start the thread and let it wait.
					}
					catch(Exception^ )
					{
						//give a distinct message that we could not use the port even if avaliable. 
						//the user may have some other app communicating on the same port
						//they need to shut it
						throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrPortOpenFailedErrCd, CrxStructCommonResourceMsg::DalErrPortOpenFailed, ErrorSeverity::Exception );
					}
				}
				}
				catch(ScorException^)
				{
					throw;
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				finally
				{
					Monitor::Exit(_lockObject);
				}
			
				return true;
			}



			bool DalActivePort::CloseActivePort()
			{
				if (!_serialPort)
				{
					//attempted to close nullptr
					//throw gcnew ScorException(1027, "DAL_ERR_INVALID_PORT_CLOSE", ErrorSeverity::Exception);
					throw gcnew ScorException(CrxStructCommonResourceMsg::DalErrInvalidPortCloseErrCd, CrxStructCommonResourceMsg::DalErrInvalidPortClose, ErrorSeverity::Exception);
				}

				Monitor::Enter(_lockObject);
				//if yes then close the existing
				//and set to the parameter
				try
				{
					//readerThread->Abort();//Stop the thread 
					_serialPort->Close();
					delete _serialPort ;
					_serialPort = nullptr;
				}
				catch(IOException^)
				{
					return false;
				}
				catch(Exception^  exObj)
				{
					throw gcnew  ScorException(exObj);
				}
				finally
				{
					Monitor::Exit(_lockObject);
				}
				
				return true;
			}


			bool DalActivePort::SetSerialPortProperties()
			{
				//first check if the serial port is set . if not then raise an exception
				if (nullptr == _serialPort)
				{
					return false;
				}

				Monitor::Enter(_lockObject);

				try
				{
					//set the serial port properties to match the EM4 device
					_serialPort->BaudRate = DalConstants::EM4SerialPortBaudRate ;
					_serialPort->Parity = Parity::None;
					_serialPort->StopBits = StopBits::One;
					_serialPort->DataBits = DalConstants::EM4SerialPortBits;
					_serialPort->Handshake  = Handshake::None;

					//set the read and write timeouts to the same value
					_serialPort->WriteTimeout  = DalConstants::EM4ResponseTimeout ; 
					_serialPort->ReadTimeout   = DalConstants::EM4ResponseTimeout ; 
					
					//Set the tresold to the minimum packet size we need to read
					//The minimum size is a response packet which has no data
					//_serialPort->ReceivedBytesThreshold  = DalConstants::EM4ZeroDataResponsePacketSize ;

					//Setting treshold = 1 for leftover byte problem
					_serialPort->ReceivedBytesThreshold  = 1;
				}
				catch(Exception^ excepObj)
				{
					throw gcnew ScorException(excepObj);
				}
				finally
				{
					Monitor::Exit(_lockObject);
				}

				return true;
			}

			void DalActivePort::SendPacket(array<unsigned char>^dataToSend)
			{
				Monitor::Enter(_lockObject);
				try
				{
					this->_serialPort->Write(dataToSend, 0, dataToSend->Length);
					Thread::Sleep(0); //give the system some time to send the packet 

					CrxLogger::Instance->Write("DAL>>> DalActivePort::SendPacket Command sent on port:  " +  DalBinaryConversions::ConvertBytesToString(dataToSend), ErrorSeverity::Debug);
				}
				catch(Exception^ excepObj)
				{
					CrxLogger::Instance->Write("DAL>>> DalActivePort::SendPacket Failed to send:  " +  DalBinaryConversions::ConvertBytesToString(dataToSend) + excepObj->StackTrace, ErrorSeverity::Debug);
					throw gcnew ScorException(excepObj);
				}
				finally
				{
					Monitor::Exit(_lockObject);
				}
			}




			//alternate method. instead of reading and enquing directly
			//we will simply interupt a sleeping thread.
			void DalActivePort::DataReceviedHandler(Object ^, SerialDataReceivedEventArgs ^)
			{
				try
				{
					//CrxLogger::Instance->Write("DAL>>> DalActivePort::DataReceviedHandler Event raised Avaliable "+ _serialPort->BytesToRead, ErrorSeverity::Debug);
				
					Thread::Sleep(0);

					//Call directly instead of from a thread. that wy, the event is not raised repeatedly
					ReadDataFromPort();

					//CrxLogger::Instance->Write("DAL>>> DalActivePort::DataReceviedHandler Signalling DalStagingQueue", ErrorSeverity::Debug);
					
					//Inform the DalStagingQueue that data is available
					DalStagingQueue::Instance->SignalDataAvailable();

					//serialDataWasRecieved = true; //set the marker to true to let the checker know that we got the data
				}
				catch(ScorException^ scorExObj)
				{
					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException , scorExObj);
				}
				catch(Exception^ excepObj)
				{
					//throw gcnew ScorException(excepObj);
					DalStatusHandler::RaiseEventForException(DalErrorAlarmStatusFlag::ThreadException, gcnew ScorException(excepObj));
				}

			}


			void DalActivePort::ReadDataFromPort()
			{
				
				try
				{
					Monitor::Enter(_lockObject);

					//CrxLogger::Instance->Write("DAL>>> DalActivePort::ReadDataFromPort START " , ErrorSeverity::Debug);
				int bytesAvaliable; //variable to find how many bytes of data is avaiable
				array<unsigned char>^ serialData; //to recieve the data
			
				//Find out how many bytes are available
				bytesAvaliable = _serialPort->BytesToRead;
				////CrxLogger::Instance->Write("DAL>>> DalActivePort::ReadDataFromPort Avaliable data: " +  bytesAvaliable , ErrorSeverity::Debug);

				//if no bytes are available then return back
				if (0 == bytesAvaliable)
				{
						//Dont exit monitor here and return as it will try to exit again in finally block
						//change statemen to if else and do not return here 
						
						//CrxLogger::Instance->Write("DAL>>> DalActivePort::ReadDataFromPort Zero data return back and release monitor", ErrorSeverity::Debug);
						//return; //end this process //do not return here
						;
				}
					else
					{

				//create an array of the required size
				serialData = gcnew array<unsigned char> (bytesAvaliable);

				//read whatever is available
				_serialPort->Read(serialData, 0, bytesAvaliable);
				CrxLogger::Instance->Write("DAL>>> DalActivePort::ReadDataFromPort Recieved:  " +  DalBinaryConversions::ConvertBytesToString(serialData), ErrorSeverity::Debug);


				//copy it to the staging area
				DalStagingQueue::Instance->EnqueueArray(serialData);
				////CrxLogger::Instance->Write("DAL>>> DalActivePort::ReadDataFromPort EXITING " , ErrorSeverity::Debug);
					}
				}
				catch(ScorException^)
				{
					throw;

				}
				finally
				{
					//CrxLogger::Instance->Write("DAL>>> DalActivePort::ReadDataFromPort Finally block release monitor", ErrorSeverity::Debug);
						
					Monitor::Exit(_lockObject);
				}

			}

			//void DalActivePort::ThreadMethod()
			//{
			//	////CrxLogger::Instance->Write("DAL>>> DalActivePort::ThreadMethod Enter", ErrorSeverity::Debug);
			//	
			//	do 
			//	{
			//		//////CrxLogger::Instance->Write("DAL>>> DalActivePort::ThreadMethod Inside DO_BLOCK", ErrorSeverity::Debug);
			//		try
			//		{
			//			if( _serialPort->BytesToRead)
			//			{
			//			
			//				////CrxLogger::Instance->Write("DAL>>> DalActivePort::ThreadMethod Call ReadDataFromPort", ErrorSeverity::Debug);
			//				ReadDataFromPort();
			//				//dataAvaliable = false;

			//				//Inform the DalStagingQueue that data is available
			//				DalStagingQueue::Instance->SignalDataAvailable();
			//			}
			//		
			//			////CrxLogger::Instance->Write("DAL>>> DalActivePort::ThreadMethod Sleep for infinite time", ErrorSeverity::Debug);
			//			Thread::Sleep(Timeout::Infinite ); 	//sleep until woken again
			//		}
			//		catch(ThreadInterruptedException^ ex)
			//		{
			//			delete ex;
			//			////CrxLogger::Instance->Write("DAL>>> DalActivePort::ThreadMethod ThreadInterruptedException raised", ErrorSeverity::Debug);
			//			continue;
			//		}
			//		catch(ScorException ^ scorEx)
			//		{
			//			////CrxLogger::Instance->Write("DAL>>> DalActivePort::ThreadMethod ScorException deleted" + scorEx->ErrorMessageKey, ErrorSeverity::Debug);
			//			delete scorEx;
			//		}
			//	}
			//	while(true); //will throw a warning. leave it as it is
			//	////CrxLogger::Instance->Write("DAL>>> DalActivePort::ThreadMethod Exit", ErrorSeverity::Debug);
			//}

			//void DalActivePort::CheckStreamingTimeout(Object^, ElapsedEventArgs^ )
			//{

			//	static unsigned int BufferEmptyCounter; 

			//	//the DataRecieved event sets this flag to true to indicate that the data was recieved
			//	//this handler checks wether the flag was raised . It then resets the flag. If the data was not recieved
			//	//till  the next tick it will remain false


			//	//check if the flag is false
			//	if (serialDataWasRecieved)
			//	{
			//		//CrxLogger::Instance->Write("DAL>>> DalActivePort::CheckStreamingTimeout true" , ErrorSeverity::Debug);

			//		//if true, it means that data was recieved and timeout has not occured
			//		//set the flag to false and give the reader a chance to set it to true again

			//		serialDataWasRecieved = false;
			//		BufferEmptyCounter = 0; //reset the counter
			//	}
			//	else
			//	{
			//		//increment the counter
			//		BufferEmptyCounter++;
			//		//CrxLogger::Instance->Write("DAL>>> DalActivePort::CheckStreamingTimeout false BufferEmptyCounter = " + BufferEmptyCounter, ErrorSeverity::Debug);


			//		
			//		if (BufferEmptyCounter <  DalConstants::MaxStreamingTimeoutOccurrences)
			//		{
			//			//if the treshold for number of empty tries is not reached , return
			//			return;
			//		}

			//		//if false for multipl occurences, it means that there was no data between last check and this one
			//		//raise an alarm
			//	
			//		//change the state
			//		DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateTimeout::Instance);
			//		//ChangeCaptureState(DalCaptureStateTimeout::Instance); //call directly so that it is applicable for its children too
			//							
			//		//CrxLogger::Instance->Write("DAL>>> DalActivePort::CheckStreamingTimeout Timeout occured Raising event." );

			//		
			//		//raise event 
			//		String^ sourceName = Enum::Format(DalErrorAlarmStatusFlag::typeid, DalErrorAlarmStatusFlag::DataCaptureTimeout, DalFormatterStrings::PrintEnumName);
			//		DalModuleErrorAlarmEventArgs^ eventArgs = gcnew DalModuleErrorAlarmEventArgs(DalErrorAlarmStatusFlag::DataCaptureTimeout, sourceName, DalBinaryConversions::ConvertAlarmType(DalErrorAlarmStatusFlag::DataCaptureTimeout));
			//		DalEventContainer::Instance->OnDalModuleErrorAlarmEvent(nullptr, eventArgs);

			//		//moved to another class
			//		////after raising a timout event , subsequent checks will also timout. 
			//		////so diable the timer.
			//		////timeoutCheckTimer->Enabled = false;

			//		DalCommandInterface::Instance->ChangeCaptureState(DalCaptureStateNotListening::Instance);
			//		//ChangeCaptureState(DalCaptureStateNotListening::Instance); //call directly so that it is applicable for its children too
			//	}
			//}


			//void DalActivePort::StartStreamingTimeoutChecker()
			//{
			//	//checking has been moved to dalStreamingpacketQueue
			//	//timeoutCheckTimer->Enabled = true;
			//}

			//void DalActivePort::StopStreamingTimeoutChecker()
			//{
			//	//checking has been moved to dalStreamingpacketQueue
			//	//timeoutCheckTimer->Enabled = false;
			//}

		
		} //End namespace DataAccess
	} //End namespace Scor
}//End namespace AtCor
