#include "stdafx.h"
#include "DalDataProvider.h"
//#include "DalCommandInterface.h"

using namespace System;
using namespace System::Threading;
using namespace AtCor::Scor::CrossCutting;
using namespace AtCor::Scor::CrossCutting::Configuration;
using namespace AtCor::Scor::CrossCutting::Logging;
using namespace AtCor::Scor::CrossCutting::Messaging;
using namespace AtCor::Scor::DataAccess;

namespace AtCor{
	namespace Scor{
		namespace DataAccess{

			DalDataProvider::DalDataProvider()
			{

				if (_tonometerSimulationFile != nullptr)
				{
					_tonometerSimulationFile->CloseFile();
					_tonometerSimulationFile = nullptr;
				}

				if (_cuffTimerSimulationFile != nullptr)
				{
					_cuffTimerSimulationFile->CloseFile();
					_cuffTimerSimulationFile = nullptr;
				}

				if (dci == nullptr)
				{
					try
					{
						dci= gcnew DalCommandInterface("COM1"); //hardcoded, remove later
					}
					catch(ScorException^)
					{
						dci = nullptr;
						throw;
					}
				}

				 try
                {
                    _tonometerSimulationFile = gcnew DalSimulationFile(".\\simulation\\pwv\\Simulation.dat");
					_cuffTimerSimulationFile = gcnew DalSimulationFile(".\\simulation\\cuff_timer\\cuff_timer.dat");
			    }
				catch(ScorException^)
				{
					throw;
				}
                catch(Exception^ sysExObj)
                {
                    throw gcnew ScorException(sysExObj);
                }
			}

			bool DalDataProvider::StartSendingData() //Start the simulation capture 
			{
				try
				{
					
					//move file to start in case it isn't alreay at start.
					_tonometerSimulationFile->ResetFileStreamPosition();
					_cuffTimerSimulationFile->ResetFileStreamPosition();
					
					//The interval should come from a global value
					//initialize a new timer object
					captureTimer = gcnew Timers::Timer(DalConstants::SimulationTimerInterval);
					
					//specify the event handler to handle timer events
					captureTimer->Elapsed += gcnew ElapsedEventHandler(&DalDataProvider::OnTimerGetValuesAndSendData); 
					
					//Start the timer.
					captureTimer->Enabled = true; //TODO temporarily commented
					///*for (int i = 0; i <5; i++)
					//{*/
					//	ReadAndSendSerialData(nullptr);
					///*}*/

					return true;
				}
				catch(ScorException^)
				{
					throw;
				}
                catch(Exception^ sysExObj)
                {
                    throw gcnew ScorException(sysExObj);
                }
				return false;
			}
					
			bool DalDataProvider::StopSendingData() //Stop the simulation capture
			{
				try
				{
					//Stop the capture timer
					captureTimer->Enabled = false;

					//reset the filestrea position
					_tonometerSimulationFile->ResetFileStreamPosition();
					_cuffTimerSimulationFile->ResetFileStreamPosition();
					return true;
				}
				catch(ScorException^)
				{
					throw;
				}
                catch(Exception^ sysExObj)
                {
                    throw gcnew ScorException(sysExObj);
                }
			}


			void DalDataProvider::OnTimerGetValuesAndSendData(Object^ sender, ElapsedEventArgs^ args)
			{
				ReadAndSendSerialData( sender);
				
			}

			//new method to to read data in a loop 
			void DalDataProvider::ReadAndSendSerialData(Object^ sender)
			{
				DalEM4Command ^ em4Command;
			
				//variables to hold the tonometer and cuff pulse readings
				static unsigned long tonoData, cuffPulseData;
				static unsigned long cuffAbsolutePressure;
				static unsigned long locCountdownTimer = 0;
				static unsigned long statusBytes, locEASourceFlag;
				static unsigned long cuffStatusBytes, errorAlarmStatusBytes; 
				static bool currentCuffStateIsInflated = false;
				array<unsigned char>^ dataPlusStatus = gcnew array<unsigned char> (10); //8 for data 2 for status
						
				try
				{
					for (int i = 0 ; i < DalConstants::SimulationNumberOfReadsPerInterval; i++)
					{
						if (locCountdownTimer <=0) 
						{
							//get next set of values from the cuff simulation file
							_cuffTimerSimulationFile->GetNextValues(&locCountdownTimer, &cuffAbsolutePressure, &statusBytes, &locEASourceFlag);
							//CrxLogger::Instance->Write("locCountdownTimer" + locCountdownTimer + ", cuffAbsolutePressure:" + cuffAbsolutePressure + ", statusBytes" + statusBytes.ToString("X") + " ,locEASourceFlag" + locEASourceFlag.ToString("X"));
						}

						//CrxLogger::Instance->Write("statusBytes:" + statusBytes.ToString("X4") +" cuffStatusBytes:" + cuffStatusBytes.ToString("X4") + " errorAlarmStatusBytes:"+errorAlarmStatusBytes.ToString("X4") );
						

						//get the next set of values from the tonometer simulation file.
						_tonometerSimulationFile->GetNextValues(&tonoData, &cuffPulseData);

						//CREATE A NEW ARRAY FOR THre data parts also include status
						DalCommandInterface::TranslateUnsignedShort(dataPlusStatus, 0, (unsigned short)tonoData);
						DalCommandInterface::TranslateUnsignedShort(dataPlusStatus, 2, (unsigned short)cuffPulseData);
						DalCommandInterface::TranslateUnsignedShort(dataPlusStatus, 4, (unsigned short)cuffAbsolutePressure);
						DalCommandInterface::TranslateUnsignedShort(dataPlusStatus, 6, (unsigned short)locCountdownTimer/1000);
						DalCommandInterface::TranslateUnsignedShort(dataPlusStatus, 8, (unsigned short)statusBytes);
						
						//send a serial port data here TODO
						em4Command = gcnew DalEM4Command(0x87, dataPlusStatus);
						if (nullptr == dci )
						{
							dci = gcnew DalCommandInterface("COM1");
						}

						dci->SendDataCapturePacket(em4Command);
						Thread::Sleep(0);
						
						//decrement the timer after every write operation
						locCountdownTimer -= DalConstants::DataSamplingInterval;
						delete em4Command;
						
					}

					delete dataPlusStatus;

				}
				catch(Exception^ excepObj)
				{
					//CrxLogger::Instance->Write("ReadAndSendSerialData failed: " + excepObj->Message);
					throw gcnew ScorException(excepObj);
				}
				
			}


			void DalDataProvider::PcCommandResolver(System::Object ^sender, AtCor::Scor::DataAccess::PCCommandRecievedEventArgs ^args)
			{
				if (nullptr == args)
				{
					throw gcnew ScorException(111, "KEY", ErrorSeverity::Exception );
				}

				DalEM4Command ^ pcCommandObj = args->pcCommandPacket ;
				DalEM4Command ^ em4ReplyPacket ;
				unsigned char ackNackbyte;
				unsigned char seqNo;

				//first validate crc
				bool retval ;
				retval = pcCommandObj->ValidateCommandCRC();

				if (false == retval)
				{
					//TODO// send nack
					em4ReplyPacket = GenerateNackPacket(pcCommandObj);
					if (nullptr == dci )
					{
						dci = gcnew DalCommandInterface("COM1");
					}
					dci->SendDataCapturePacket(em4ReplyPacket);
					return;
				}
				else
				{
					array<unsigned char> ^ dataArray ;
					//call the fuction that will sendus the appropriate data
					bool retVal; 
					retVal = ReplyToPCRequest(pcCommandObj->commandCode, dataArray);
					if (false == retVal)
					{
						throw gcnew ScorException(111, "DAL_ERR_CANNOT_CREATE_REPLY_DATA", ErrorSeverity::Information );
					}
					//modify first byte to ACK
					ackNackbyte = (pcCommandObj->commandCode) | 0x80;
					//make the sequence number the same as command
					seqNo = (pcCommandObj->commandSequenceNumber)<<4;
					
					//add the made-up data
					//add the ack nack
					//send it once only
					
					em4ReplyPacket = gcnew DalEM4Command(ackNackbyte, seqNo, dataArray, (unsigned short)0x0100); 
					if (nullptr == dci )
					{
						dci = gcnew DalCommandInterface("COM1");
					}
					dci->SendDataCapturePacket(em4ReplyPacket);

					//after sending response check if it was a start caputre request
					//if yes then wait for 1 sec before calling the method
					if ( 0x06 == pcCommandObj->commandCode)
					{
						Thread::Sleep(1000);
						StartSendingData();
					}
				
				}

				
						

			}

			bool DalDataProvider::StartListeningToPCCommands()
			{
				dci->_serialPort->ReceivedBytesThreshold ;
				dci->_serialPort->DataReceived += gcnew SerialDataReceivedEventHandler(DalCommandInterface::PCCommandHandler); 
				DalEventContainer::Instance->OnPcCommandRecievedEvent += gcnew PCCommandRecievedEventHandler(&DalDataProvider::PcCommandResolver);
			
				return true;
			}

			bool DalDataProvider::StopListeningToPCCommands()
			{
				dci->_serialPort->DataReceived -= gcnew SerialDataReceivedEventHandler(DalCommandInterface::PCCommandHandler); 
				DalEventContainer::Instance->OnPcCommandRecievedEvent -= gcnew PCCommandRecievedEventHandler(&DalDataProvider::PcCommandResolver);
			
				return true;
			}

			DalEM4Command ^ DalDataProvider::GenerateNackPacket(AtCor::Scor::DataAccess::DalEM4Command ^commandSource)
			{
				DalEM4Command^ replyPacket;

				unsigned char replySeqNo = (commandSource->commandSequenceNumber)<<4;

				unsigned short statusBytes = 0x0100; //this doesnt really matter

				//assuming corrupt CRC
				array <unsigned char>^ dataArray = gcnew array <unsigned char> (1);
				dataArray[0] = 0x00;
				replyPacket = gcnew DalEM4Command(commandSource->commandCode, replySeqNo,dataArray , statusBytes);

				return replyPacket;
			}


			bool DalDataProvider::ReplyToPCRequest(unsigned char inCommandCode, cli::array<unsigned char,1> ^%outReplyData)
			{
				
				switch (inCommandCode)
				{
					case 0x0B:
						{
							outReplyData = gcnew array<unsigned char> (12) {0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xB0, 0xB1, 0xB2 };
							break;
						}
					case 0x40: //dummy command
						{
							outReplyData = gcnew array<unsigned char> (2) {0x01, 0x00};
							break;
						}
					case 0x11:
						{
							outReplyData = gcnew array<unsigned char> (4) ;
							DalCommandInterface::TranslateUnsignedLong(outReplyData, 0, (unsigned long)0x010000);
							break;
						}
					case 0x06: //Start Streaming Data
						{
							outReplyData = nullptr;
							//call start sending data only after the reply was send
							break;
						}
					case 0x08: //stop streaming data
						{
							StopSendingData();
							outReplyData = nullptr;
							break;
						}
					case 0x09: //Set Cuff initial to pressure (via Suntech board)
					case 0x0A: //Set Cuff to pressure (via main processor board)
						{
							outReplyData = nullptr;
							//call start sending data only after the reply was send
							break;
						}

					default:
						return false;

				}

				return true;
			}



	}//end namespace DataAccess
	}// end namespace Scor
}//end namespace AtCor