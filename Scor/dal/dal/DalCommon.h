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
								* @brief This class stores all constants needed for the dal layer.
								*/
								public ref class DalConstants
								{
									public:
										static const unsigned int DataSamplingInterval = 4; // in msec
										static const unsigned int SimulationTimerInterval   = 4; // in msec
										static const unsigned int SimulationWriteTimerInterval = 1000; /**< This is to signify the time interval in which the simulation will pick the number of values*/
										static const unsigned int SimulationNumberOfReadsPerInterval = 256; /**< Number of items to read from tonometer sim file in each interval.*/
										static const unsigned int EM4NumberofRetries = 3; /**< Default number of retries for a command before failure*/
										static const unsigned int EM4ResponseTimeout = 50; /**< Default timout to wait for an EM4 response*/
										static const int PWVCaptureDataSize = 8; /**< Size of data in bytes for data capture in PWV */
										static const int EM4ZeroDataResponsePacketSize = 5; /**< size of EM4 packet which does not contain data*/
										static const int EM4SerialPortBaudRate = 115200; /**< Baud rate for serial port for EM4 device */
										static const int EM4SerialPortBits = 8; /**< Number of bits for Serial port to communicate with EM4*/
										//TODO: this is temporary to enable testing -Deepak
										static const int EM4LatencyPeriod = 40; /**< Time in ms for which the sending command should sleep before expecting a response. This is not the same as timeout*/
										static const unsigned int DeviceNumberOfReadsPerInterval = 32; /**< Number of items to read from COM port in each read. This is used to set the Serial Port treshold.*/
										static const int EM4CommandLengthWithNoData = 3; /**< The length of an EM4 command without any data . Also Excludes CRC count*/
										static const int EM4CommandDataFirstIndex = 3;/**<Index of the first byte in command array */
										static const int CRCTableSize = 256;/**< Size of the CRC table*/

										static const unsigned int StreamingTimeoutCheckerInterval = 125; /**< time interval in which the capture process should check for timeout*/
										static const int	MaxStreamingTimeoutOccurrences = 2; /**< number of times the StreamingTimout check should be done before raising a timeout event*/
										
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
									UnrecoverableStatus = 2,
									DataCaptureErrorInvalidPacket = 3,
									DataCaptureTimeout = 4
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
								* @union EM4StatusFlag
								* @brief Two byte union to translate EM4 status bits into an integer
								*/
								private union EM4StatusFlag
								{
									unsigned char ucStatusBytes[2];
									unsigned short ulStatusFlag;
								};

								/**
								* @union EM4ErrorAlarmSourceFlag
								* @brief Four byte union to translate EM4 error alarm source flag into a long integer
								*/
								private union EM4ErrorAlarmSourceFlag
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
								private enum class DalTonometerStatusBitMask
								{
									TonometerNotConnectedBits = 0x1000

								};


								/**
								* @enum DalStatusFlagBitMask
								* @brief Masks used to check various parts of the status flags
								*/
								private enum class DalStatusFlagBitMask
								{
									ErrorAlarmStatusBitsMask = 0x00000028,
									CuffStatusBitsMask = 0x2F00,
									ErrorAlarmSourceBitMask = 0x0000FFFF,

								};


								/**
								* @class DalFormatterStrings
								* @brief Strings needed for various formatting purposes
								*/
								private ref class DalFormatterStrings
								{
									internal:
										static String^ PrintEnumName = "G";
										static String^ SingleSpaceString = " ";
										static String^ PrintByte = "X2";
										static String^ FullDateTimeFormat = "yyyyMMMddHHmmss";
										static char    tabSeparator = '\t';
										static String^ tabSeparatorString = "\t";
										static String^ FourSlashes = "\\\\";
										static String^ TwoSlashes = "\\";
								};

								/**
								* @enum Em4ResponseByteIndex
								* @brief Index of various parts of the EM4 response
								*/
								private enum class Em4ResponseByteIndex
								{
									AckNackByte = 0,
									ResponseLengthByte = 1,
									SequenceNumberByte = 2,
									DataChunkFirstByte = 3
								};

								/**
								* @enum DalAckNackByteMask
								* @brief Masks used to check the first byte of EM4 response.
								*/
								private enum class DalAckNackByteMask
								{
									CommandCodeBitsMask = 0x7F,
									AckNackStatusBitMask = 0x80,
									DataCaptureCodeAckedByte = 0x87

								};


								/**
								* @class Em4CommandCodes
								* @brief Contains all the EM4 command codes
								*/
								private class Em4CommandCodes
								{
									public:
										static const unsigned char CaptureCommandDataPWVMode = 0x03;
										static const unsigned char StartDataCapture = 0x06;
										static const unsigned char StopDataCapture = 0x08;
										static const unsigned char SetPressureSuntechBoard = 0x09;
										static const unsigned char SetPressureMainBoard = 0x0A;
										static const unsigned char GetConfigInfo = 0x0B;
										static const unsigned char GetConfigInfoDataDeviceSerialNumber = 0x08;
										static const unsigned char GetAlarmStatus = 0x11;
								};

								/**
								* @class Em4ResponseRequiredLength
								* @brief Contains the length of the response required for each EM4 code
								*/
								private class Em4ResponseRequiredLength
								{
									public:
										static const int StartDataCapture = 5;
										static const int StopDataCapture = 5;
										static const int SetPressure = 5;
										static const int GetConfigInfoDataDeviceSerialNumber = 17;
										static const int GetAlarmStatus = 9;
								};

		} // End Namespace DataAccess
	} // End Namespace Scor
} // End Namespace AtCor

