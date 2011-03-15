/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
	 Filename     :		DalCommon.h      
        
     Author       :		 Deepak D'Souza
 
     Description  :		All common and public elements and constants for DAL layer
*/

#pragma once

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		/**
		* @namespace AtCor::Scor::DataAccess
		* @brief	Namepsace to contain Data Access Layer related classes.
		*/
		namespace DataAccess{

								/**
								* @class DalConstants
								* @brief THis class stores all constants needed for the dal layer.
								*/
								public ref class DalConstants
								{
									public:
										static const unsigned int DataSamplingInterval = 4; // in msec
										static const unsigned int SimulationTimerInterval   = 4; // in msec
										static const unsigned int SimulationWriteTimerInterval = 1000; /**< This is to signify the time interval in which the simulation will pick the number of values*/
										static const unsigned int SimulationNumberOfReadsPerInterval = 256; /**< Number of items to read from tonometer sim file in each interval.*/
										static const unsigned int EM4NumberofRetires = 3; /**< Default number of retries for a command before failure*/
										static const unsigned int EM4ResponseTimeout = 50; /**< Default timout to wait for an EM4 response*/
										static const int PWVCaptureDataSize = 8; /**< Size of data in bytes for data capture in PWV */
										static const int EM4ZeroDataResponsePacketSize = 5; /**< size of EM4 packet which does not contain data*/
										static const int EM4SerialPortBaudRate = 115200; /**< Baud rate for serial port for EM4 device */
										static const int EM4SerialPortBits = 8; /**< Number of bits for Serial port to communicate with EM4*/
										static const int EM4LatencyPeriod = 1; /**< Time in ms for which the sending command should sleep before expecting a response. This is not the same as timeout*/
										static const unsigned int DeviceNumberOfReadsPerInterval = 32; /**< Number of items to read from COM port in each read. This is used to set the Serial Port treshold.*/
										
								};

								/**
								* @enum	CaptureType
								* @brief	The type of data capture .	
								*/
								public enum class CaptureType { 
													Tonometer, /**< Tonometer only */
													CuffPulseCombination, /**< Cuff Pulse combination */
													TonometerAndCuffPulseCombination, /**< Tonometer and Cuff Pulse  reading combination */
													CuffAbsPressure, /**< Cuff Absolute pressure */
													CuffNibp, /**< Cuff NIBP reading */
													CuffPulse /**< Cuff Pulse only */

												  }; // End CaptureType

								/**
								* @enum	DalDeviceConfigUsageEnum
								* @brief	The configuration information item requested in DalDeviceConfigUsageStruct
								*/
								public enum class DalDeviceConfigUsageEnum
								{
									ModuleType, /**< Module type of the device */
									ModuleSerialNumber, /**< Serial number of the device */
									ModuleMainFirmwareVersion, /**< Firmware version */
									ModuleConfigId, /**< Config ID */
									ModuleConfigDate, /**< Configuation Date */
									ModuleCalibrationDate /**< Last calibration date */

								}; // End DalDeviceConfigUsageEnum

								/**
								* @struct DalDeviceConfigUsageStruct
								* @brief	Holds the configuration information for the device.
								*/
								public ref struct DalDeviceConfigUsageStruct
								{
									public:
										property String^ ModuleType; /**< Module type of the device */
										property String^ ModuleSerialNumber; /**< Serial number of the device */
										property String^ ModuleMainFWVersion; /**< Firmware version */
										property unsigned short ModuleConfigId; /**< Config ID */
										property DateTime ModuleConfigDate; /**< Configuation Date */
										property DateTime ModuleCalibrationDate; /**< Last calibration date */

								}; // End DalDeviceConfigUsageStruct

								/**
								* @enum DalCuffStatusBitMask
								* @brief	Contains the bit masks against which the status flags will be comapred to obtain the cuff status bits.
								* This will be used in combination with DalCuffStateFlags.
								*/
								public enum class DalCuffStatusBitMask{
									CUFF_STATUS_BITS_UNKNOWN = 0x0000, 
									CUFF_DISCONNECTED_STATUS_BITS = 0x2000,
									CUFF_DEFLATED_STATUS_BITS     = 0x0100,
									CUFF_INFLATING_STATUS_BITS    = 0x0400,
									CUFF_INFLATED_STATUS_BITS     = 0x0900,
									CUFF_DEFLATING_STATUS_BITS    = 0x0200
								};

								/**
								* @enum DalCuffStateFlags
								* @brief	Contains the translated cuff status obtained by comparing the cuff status bits agains predifned bit masks.
								* This will be used in combination with DalCuffStatusBitMask.
								*/
								public enum class DalCuffStateFlags {
									CUFF_STATE_UNKNOWN = 0, 
									CUFF_STATE_DISCONNECTED = 1,
									CUFF_STATE_DEFLATED = 2,
									CUFF_STATE_INFLATING = 3,
									CUFF_STATE_INFLATED = 4,
									CUFF_STATE_DEFLATING = 5
								};



								/**
								* @enum DalModuleErrorAlarmBitMask
								* @brief	Contains the bit masks against which the error alarm flags will be compared to obtain alarm error status.
								* This will be used in combination with DalErrorAlarmStatusFlag.
								*/
								public enum class DalModuleErrorAlarmBitMask{
									NoErrorAlarm = 0x0000,
									ErrorStatus = 0x0020,
									AlarmStatus = 0x0008,
									ErrorAndAlarmStatus = 0x0028
								};



								/**
								* @enum DalErrorAlarmStatusFlag
								* @brief Contains translated status for Error Alarm events.
								* To be used in combination with DalModuleErrorAlarmBitMask
								*/
								public enum class DalErrorAlarmStatusFlag{
									ActiveStatus = 0,
									RecoverableStatus = 1,
									UnrecoverableStatus = 2
								};


								/**
								* @enum DalErrorSource
								* @brief	This enum contains a mapping of bit flags from the Error Alarm Status flag against various error source.
								*/
								public enum class DalErrorSource {
									ErrorSourceUnknown = 0x0000, 
									CuffLeak    = 0x0008,
									DualSensors = 0x0020	
								};

								/**
								* @enum DalAlarmSource
								* @brief	This enum contains a mapping of bit flags from the Error Alarm Status flag against various alarm source.
								*/
								public enum class DalAlarmSource {
									AlarmSourceUnknown = 0x0000,
									OverPressure     = 0x0001,
									InflatedOverTime = 0x0004
								};


								/**
								* @class DalException
								* @brief Exception class for DataAccess namespace.
								*/
								public ref class DalException:Exception
								{
								private:
									int _errCode;
                                    String^		_errMsg;
                                    Exception^	_exceptionObject;
								public: 
									/**
									* Default constructor
									*/
									DalException(): _errCode(0), _errMsg(""), _exceptionObject(nullptr) { }
									
									/**
									* Overloaded constructor
									* @param[in]	exError	The error code to intitialize this constructor with.
									*/
									DalException(int exError): _errCode(exError), _errMsg(""), _exceptionObject(nullptr) { }
									
									/**
				                    * Overloaded constructor for Exception object
				                    * @param[in]	errExp	The Unknown (System) Exception object to intitialize this constructor with.
				                    */
                                    //DalException(Exception^ eExp): _errCode(0), _errMsg(eExp->Message), _eObj(eExp) { }//reducing as per FxCop
									DalException(Exception^ errExp) 
									{
										if (errExp != nullptr)
										{
											_errMsg= errExp->Message;
											_exceptionObject = errExp;
										}
									}

                                    /**
				                    /* Overloaded constructor for String
				                    * @param[in]	errExpStr	The String to intitialize this constructor with.
				                    */
				                    DalException(String^ errExpStr):  _errMsg(errExpStr), _exceptionObject(nullptr) { }

                                    /**
				                    /* Overloaded constructor for String
                                    * @param[in]	exError	The error code to intitialize this constructor with.
				                    * @param[in]	errExpStr	The String to intitialize this constructor with.
                                    * @param[in]	errExp	The Unknown (System) Exception object to intitialize this constructor with.
				                    */
				                    DalException(int exError, String^ errExpStr, Exception^ errExp): _errCode(exError), _errMsg(errExpStr), _exceptionObject(errExp) { }
									
									/**
									* Error code property of the exception.
									*/ 
									property int ErrorCode
									{
										int get()
										{
											return _errCode;
										}

										void set(int exError)
										{
											_errCode = exError;
										}
									}

                                    /**
				                    * Error code String property of the exception
				                    */ 
				                    property String^ ErrorString
				                    {
					                    String^ get()
					                    {
						                    return _errMsg;
					                    }

					                    void set(String^ exError)
					                    {
						                    _errMsg = exError;
					                    }
				                    }

                                    /**
			                        * Exception Object property of the exception
			                        */ 
			                        property Exception^ ExceptionObject
			                        {
				                        Exception^ get()
				                        {
					                        return _exceptionObject;
				                        }
			                        }
								}; // End DalException


								/**
								* @enum DalReturnValue
								* @brief Status of failure/succes and reasons
								*/
								public enum class DalReturnValue
								{
									Failure,
									Success,
									Timeout,
									NoAck
								};

								/**
								* @union EM44StatusFlag
								* @brief Two byte union to translate EM4 status bits into an integer
								*/
								private union EM44StatusFlag
								{
									unsigned char ucStatusBytes[2];
									unsigned short ulStatusFlag;
								};

								/**
								* @union EM44ErrorAlarmSourceFlag
								* @brief Four byte union to translate EM4 error alarm source flag into a long integer
								*/
								private union EM44ErrorAlarmSourceFlag
								{
									unsigned char ucStatusBytes[4];
									unsigned long ulStatusFlag;
								};

								/**
								* @enum EM4CuffBoard
								* @brief Board to be used to set pressure
								*/
								public enum class EM4CuffBoard
								{
									MainBoard,
									SuntechBoard
								};

								/**
								* @enum DalTonometerState
								* @brief Tonometer states indicating whter the device is connected or not
								*/
								public enum class DalTonometerState
								{
									Disconnected = 1,
									Connected  = 0

								};

								/**
								* @enum DalTonometerStatusBitMask
								* @brief Bit masks to check Tonometer state
								*/
								public enum class DalTonometerStatusBitMask
								{
									TonometerNotConnectedBits = 0x1000

								};




							

		} // End Namespace DataAccess
	} // End Namespace Scor
} // End Namespace AtCor

