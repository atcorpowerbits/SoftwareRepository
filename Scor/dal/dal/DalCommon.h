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
										
										//this should be the same as the GUI frequencey 125 ms
										static const unsigned int SimulationWriteTimerInterval = 125; // = 1000; /**< This is to signify the time interval in which the simulation will pick the number of values*/
										
										//Keep this at 32 and run the thread every 125 ms
										static const unsigned int SimulationNumberOfReadsPerInterval = 32; //= 256; /**< Number of items to read from tonometer sim file in each interval.*/
										
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

										static const unsigned int StreamingTimeoutCheckerInterval = 100; /**< time interval in which the capture process should check for timeout*/
										static const int	MaxStreamingTimeoutOccurrences = 2; /**< number of times the StreamingTimout check should be done before raising a timeout event*/

										static const unsigned int RightShiftOneNibble = 4;
										static const unsigned int EM4NackPacketDataLength = 1; //Nack packet contains only one packet
										static const unsigned int StreamingPacketReadInterval = 125; /**< Interval at which the timer for reading packets should fire.*/
										static String^ PwaCuffMeasurementsCounter  = "1"; /**< PwaCuffMeasurementsCounter */
										//unsigned short NibpCuffDataInterval; /**< Interval at which the timer for reading NIBP packets should fire. */
								};

								/**
								* @enum	CaptureType
								* @brief	The type of data capture .	
								*/
								public enum class CaptureType 
								{ 
									Tonometer, /**< Tonometer only */
									CuffPulseCombination, /**< Cuff Pulse combination */
									TonometerAndCuffPulseCombination, /**< Tonometer and Cuff Pulse  reading combination */
									CuffAbsPressure, /**< Cuff Absolute pressure */
									CuffNibp, /**< Cuff NIBP reading */
									CuffPulse /**< Cuff Pulse only */
								}; // End CaptureType

								/**
								* @enum	DalStreamingMode
								* @brief	The mode of operation such as PWV, PWA	
								*/
								public enum class DalStreamingMode
								{
									None, /**<Default*/
									Pwv, /**< Pulse Wave Velocity */
									cPwa, /**< Pulse Wave Analysis - Cuff */
									tPwa /**< Pulse Wave Analysis - Cuff */
								};

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
									ModuleCalibrationDate, /**< Last calibration date */
									PwaCuffMeasurementsCounter /**< Number of PWA cuff measurements */

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
										property String^ PwaCuffMeasurementsCounter; /**< Number of PWA cuff measurements */
								}; // End DalDeviceConfigUsageStruct

								//Replaced with a new version of the flags. Wait for TS to approve before finalizing
								/**
								* @enum DalCuffStatusBitMask
								* @brief	Contains the bit masks against which the status flags will be comapred to obtain the cuff status bits.
								* This will be used in combination with DalCuffStateFlags.
								*/
								public enum class DalCuffStatusBitMask{
									CUFF_STATUS_BITS_UNKNOWN = 0xFFFF,  //marked as a clear flag. cannot use 0 becuase it is another valid value
									
									//CUFF_DISCONNECTED_STATUS_BITS = 0x2000,
																		
									CUFF_DEFLATED_STATUS_BITS     = 0x0000,
								
									CUFF_INFLATING_STATUS_BITS    = 0x0100,
									
									//CUFF_DISCONNECTED_INFLATING_STATUS_BITS    = 0x2100, //same as INFLATING but thhe CN bit changes
									
									//CUFF_INFLATED_STATUS_BITS     = 0x0A00,
									CUFF_INFLATED_STATUS_BITS     = 0x0200,
									
									
									CUFF_DEFLATING_STATUS_BITS    = 0x0300,

									//CUFF_DISCONNECTED_DEFLATING_STATUS_BITS    = 0x2300//Same as deflating with the CN bit set to 1
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
								* @enum DalAlarmStatusBitMask
								* @brief	Contains the bit masks against which the error alarm flags will be compared to obtain alarm error status.
								* This will be used in combination with DalErrorAlarmStatusFlag.
								*/
								public enum class DalAlarmStatusBitMask{
									NoAlarm = 0x0000,
									//ErrorStatus = 0x0020, //obsolete
									AlarmStatus = 0x0008,
									//AlarmStatus = 0x0020, 
									//ErrorAndAlarmStatus = 0x0028 //obsolete
								};



								/**
								* @enum DalErrorAlarmStatusFlag
								* @brief Contains translated status for Error Alarm events.
								* To be used in combination with DalAlarmStatusBitMask
								*/
								public enum class DalErrorAlarmStatusFlag{
									ActiveStatus = 0,
									RecoverableStatus = 1,
									UnrecoverableStatus = 2,
									DataCaptureErrorInvalidPacket = 3,
									DataCaptureTimeout = 4,
									StopButtonPressed = 5,
									PowerUpEvent = 6,
									ThreadException = 7,
									
								};

								//replaced by newer enum Delete
								///*
								//* @enum DalAlarmSource
								//* @brief	This enum contains a mapping of bit flags from the Error Alarm Status flag against various alarm source.
								//*/
								//public enum class DalAlarmSource {
								//	AlarmSourceUnknown = 0x0000,
								//	OverPressure     = 0x0001,
								//	InflatedOverTime = 0x0004,
								//	//Brought over from the older DalErrorSource Enum for mergin
								//	//TODO: verify and add anyu more if necessary
								//	CuffLeak    = 0x0008,
								//	DualSensors = 0x0020	
								//};


								/**
								* @enum DalReturnValue
								* @brief Status of failure/succes and reasons
								*/
								public enum class DalReturnValue
								{
									Failure,
									Success,
									Timeout,
									NoAck,
									Ack,
									Busy
								};

								/**
								* @union TwoBytesUnsignedShort
								* @brief Two byte union to translate EM4 status bits into an integer
								*/
								private union TwoBytesUnsignedShort
								{
									unsigned char ucStatusBytes[2];
									unsigned short ulStatusFlag;
								};

								/**
								* @union TwoBytesSignedShort
								* @brief Two byte union to translate EM4 status bits into a signed integer
								*/
								private union TwoBytesSignedShort
								{
									unsigned char ucStatusBytes[2];
									signed short ssStatusFlag;
								};

								/**
								* @union FourBytesUnsignedLong
								* @brief Four byte union to translate EM4 error alarm source flag into a long integer
								*/
								private union FourBytesUnsignedLong
								{
									unsigned char ucStatusBytes[4];
									unsigned long ulStatusFlag;
								};

								/**
								* @union ThreeBytesUnsignedLong
								* @brief Three byte union to translate EM4 error alarm source flag into a long integer
								*/
								private union ThreeBytesUnsignedInt
								{
									unsigned char ucStatusBytes[4];
									unsigned int uiStatusFlag;
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
									Unknown = 0,
									Disconnected = 1,
									Connected  = 2
								};

								/**
								* @enum DalTonometerStatusBitMask
								* @brief Bit masks to check Tonometer state
								*/
								private enum class DalTonometerStatusBitMask
								{
									TonometerStatusUnknown = 0xFFFF,
									//TonometerNotConnectedBits = 0x1000 //Incorrect
									TonometerNotConnectedBits = 0x4000,
									TonometerConnectedBits= 0x0000
								};


								/**
								* @enum DalStatusFlagBitMask
								* @brief Masks used to check various parts of the status flags
								*/
								private enum class DalStatusFlagBitMask
								{
									AlarmStatusBitsMask = 0x0008,

									//CuffStatusBitsMask = 0x2F00,// This mask uses all 5 cuff buts whereas we need only three bits for the status
									CuffStatusBitsMask = 0x0700, //Only count Cs0, Cs1, Cs2
									
									TonoStatusBitsMask = 0x5000,
									PowerUpBitMask = 0x0001,
									StopButtonBitMask = 0x0002,

									//UnusedStatusBitsMask = 0x80DC //changed
									UnusedStatusBitsMask = 0x80F4 //THis flag is used to rasie an event for any of the other unused bits

								};

								private enum class DalAlarmSourceFlagBitMask
								{
									SupplyRailsBitMask = 0x0F00
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
									DataCaptureCodeAckedByte = 0x87,
									Em4NibpToHostCommandCode = 0x93,

								};


								/**
								* @class Em4CommandCodes
								* @brief Contains all the EM4 command codes
								*/
								private class Em4CommandCodes
								{
									public:
										static const unsigned char CaptureCommandDataCPWAMode = 0x02;
										static const unsigned char CaptureCommandDataPWVMode = 0x03;
										static const unsigned char StartDataCapture = 0x06;
										static const unsigned char StopDataCapture = 0x08;
										static const unsigned char SetPressureSuntechBoard = 0x09;
										static const unsigned char SetPressureMainBoard = 0x0A;
										static const unsigned char GetConfigInfo = 0x0B;
										static const unsigned char GetConfigInfoDataDeviceSerialNumber = 0x08;
										static const unsigned char GetAlarmStatus = 0x11;
										static const unsigned char SetIdleMode = 0x1A;
										static const unsigned char GetConfigInfoDataPwaCuffMeasurementsCounter = 0x0B;
										static const unsigned char NibpConnectDisconnect = 0x05;
										static const unsigned char SetConfigInfo = 0x0C;
										static const unsigned char SerialNumberMpb = 0x00;
										static const unsigned char ProcessorFirmwareVersionMpb = 0x01;
										static const unsigned char PldSafetyFirmwareVersionMpb = 0x02;
										static const unsigned char HWConfigurationMpb = 0x03;
										static const unsigned char SerialNumberSuntechPcb = 0x04;
										static const unsigned char BPFirmwareVersionSuntech = 0x05;
										static const unsigned char SafetyFirmwareVersionSuntech = 0x06;
										static const unsigned char SystemConfigurationId = 0x07;
										static const unsigned char SerialNumberEm4 = 0x08;
										static const unsigned char NumberofPWVmeasurements = 0x09;
										static const unsigned char NumberofPWAtonometermeasurements = 0x0A;
										static const unsigned char NumberofPWAcuffmeasurements = 0x0B;
										static const unsigned char NumberOfNibpMeasurements = 0x0C;
										static const unsigned char CalibrationDateMpb = 0x0D;
										static const unsigned char CalibrationDateSuntech = 0x0E;
										static const unsigned char TestDate = 0x0F;
										static const unsigned char SystemConfigurationChangeDate = 0x10;
										static const unsigned char NotchFilterEnable = 0x11;
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
										static const int GetConfigInfoDataPwaCuffMeasurementsCounter = 3;
										static const int ZeroDataResponsePacket = 5;
										static const int SerialNumberMpb = 25;
										static const int ProcessorFirmwareVersionMpb = 9;
										static const int PldSafetyFirmwareVersionMpb = 9;
										static const int HWConfigurationMpb = 6;
										static const int SerialNumberSuntechPcb = 21;
										static const int BPFirmwareVersionSuntech = 12;
										static const int SafetyFirmwareVersionSuntech = 12;
										static const int SystemConfigurationId = 6;
										static const int SerialNumberEm4 = 17;
										static const int NumberofPWVmeasurements = 8;
										static const int NumberofPWAtonometermeasurements = 8;
										static const int NumberofPWAcuffmeasurements = 8;
										static const int NumberOfNibpMeasurements = 8;
										static const int CalibrationDateMpb = 11;
										static const int CalibrationDateSuntech = 11;
										static const int TestDate = 11;
										static const int SystemConfigurationChangeDate = 11;
										static const int NotchFilterEnable = 6;
								};

								/**
								* @class Em4ConfigurationFieldLength
								* @brief Contains the length of the each EM4 code
								*/
								private class Em4ConfigurationFieldLength
								{
									public:
										static const int SerialNumberMpb = 20;
										static const int ProcessorFirmwareVersionMpb = 4;
										static const int PldSafetyFirmwareVersionMpb = 4;
										static const int HWConfigurationMpb = 1;
										static const int SerialNumberSuntechPcb = 16;
										static const int BPFirmwareVersionSuntech = 7;
										static const int SafetyFirmwareVersionSuntech = 7;
										static const int SystemConfigurationId = 1;
										static const int SerialNumberEm4 = 12;
										static const int NumberofPWVmeasurements = 3;
										static const int NumberofPWAtonometermeasurements = 3;
										static const int NumberofPWAcuffmeasurements = 3;
										static const int NumberOfNibpMeasurements = 3;
										static const int CalibrationDateMpb = 6;
										static const int CalibrationDateSuntech = 6;
										static const int TestDate = 6;
										static const int SystemConfigurationChangeDate = 6;
										static const int NotchFilterEnable = 1;
								};

								/**
								* @enum	DalUnusedStatusFlagBit
								* @brief	Contains the translated unused status bit masks
								*/
								public enum class DalUnusedStatusFlagBit 
								{
									UnusedBitBprr = 0x8000,
									UnusedBitReservedLSB7 = 0x0080,
									UnusedBitReservedLSB6 = 0x0040,
									UnusedBitReservedLSB4 = 0x0010,
									UnusedBitReservedLSB3 = 0x0008 //TODO: This may be incorrect. Recheck
								};

								/**
								* @enum	DalAlarmFlagBitPosition
								* @brief	Contains the postions and names of various bits in the Alarm flag
								*/
								public enum class DalAlarmFlagBitPosition
								{
									PowerUp= 0,
									HighInflationRate = 1,
									CuffMPower = 2,
									CuffLeak = 3,
									HighDeflationRate = 4,
									DualSensors = 5,
									Temperature = 6,
									LowPumpSpeed = 7,
									SupplyRails = 8,
									SourceID0 = 9,
									SourceID1 = 10,
									SourceID2 = 11,
									Spare = 12,
									LowDeflationRate= 13,
									Reserved14 = 14,
									Reserved15 = 15,
									OverPressure = 16,
									InflatedOvertimeOverpressure = 17,
									InflatedOvertime = 18,
									ShortWaitPeriod = 19,
									Reserved20 = 20,
									Reserved21 = 21,
									Reserved22 = 22,
									Reserved23 = 23,
									Reserved24 = 24,
									Reserved25 = 25,
									Reserved26 = 26,
									Reserved27 = 27,
									Reserved28 = 28,
									Reserved29 = 29,
									Reserved30 = 30,
									Reserved31 = 31,
									TotalBitCount = 32
								};

								/**
								* @enum	DalAlarmSupplyRailFlag
								* @brief	Contains the bit mask combination for the various supply rail alarm bits
								*/
								public enum class DalAlarmSupplyRailFlag
								{
									SupplyRailNoAlarm = 0x0000,
									Vin = 0x0300,
									Source5VD = 0x0500,
									VPump = 0x0700,
									VValve = 0x0900,
									VTono = 0x0B00,
									Source5VA = 0x0D00,
									Reserved = 0x0F00
								};

								/**
								* @enum	DalFindModuleResult
								* @brief	An enum defining the return values for FindModule function.
								*/
								public enum class DalFindModuleResult
								{
									ModuleNotFound = 0, /**< The device was not found on any port and DAL is in simulation mode. */
									ModuleFoundOnConfigPort = 1, /**<A comm port was set in configuration and the EM4 was found on the same port. */
									ModuleFoundOnDifferentPort = 2 /**< The EM4 device was found on a different port as specified in configuration*/
								};

								/**
								* @class DalParameterNames
								* @brief Names of various system parameter tags to be extracted from ScorSystemParameters.xml
								*/
								private ref class DalSystemParameterNames
								{
									private:
										DalSystemParameterNames()
										{
											//empty private constructor to prevent compiler from adding a default constructor. FxCop.
										};

									internal:
										static String^ TagStdEM4Timeout = "StdEM4Timeout";
										static String^ TagEM4NumberOfRetriesAllowed = "EM4NumberOfRetriesAllowed";
										static String^ TagNibpCuffDataInterval = "NibpCuffDataInterval";
										
								};

								/**
								* @enum DalPacketType
								* @brief The type of the dal packet 
								*/
								private enum class DalPacketType
								{
									Unknown, /**< The type could not be determined*/
									StreamingDataPacket,	 /**< A streaming packet type*/
									AckedResponsePakcet,	 /**< Acked response t a particular command*/
									NackedResponsePacket,	 /**< Nacked response*/
									NibpPacket,		/**<Packet from Nibp module to host*/
									NibpProcessAbortedPacket /**<Em4 signal stating that Nibp module has been timedout*/
								};

								public enum class DalAlarmSource
								{
									PowerUp= 0, // From DalAlarmFlagBitPosition
									HighInflationRate = 1,
									CuffMPower = 2,
									CuffLeak = 3,
									HighDeflationRate = 4,
									DualSensors = 5,
									Temperature = 6,
									LowPumpSpeed = 7,
									SupplyRails = 8,
									SourceID0 = 9,
									SourceID1 = 10,
									SourceID2 = 11,
									Spare = 12,
									LowDeflationRate= 13,
									Reserved14 = 14,
									Reserved15 = 15,
									OverPressure = 16,
									InflatedOvertimeOverpressure = 17,
									InflatedOvertime = 18,
									ShortWaitPeriod = 19,
									Reserved20 = 20,
									Reserved21 = 21,
									Reserved22 = 22,
									Reserved23 = 23,
									Reserved24 = 24,
									Reserved25 = 25,
									Reserved26 = 26,
									Reserved27 = 27,
									Reserved28 = 28,
									Reserved29 = 29,
									Reserved30 = 30,
									Reserved31 = 31,
									TotalBitCount = 32, // From DalAlarmFlagBitPosition

									SupplyRailNoAlarm  = 100, //Form DalAlarmSupplyRailFlag
									Vin ,
									Source5VD ,
									VPump ,
									VValve ,
									VTono ,
									Source5VA ,
									Reserved, //Form DalAlarmSupplyRailFlag

									ActiveStatus = 200,
									RecoverableStatus ,
									UnrecoverableStatus ,
									DataCaptureErrorInvalidPacket ,
									DataCaptureTimeout ,
									StopButtonPressed ,
									PowerUpEvent, 
									ThreadException,

									NoAlarmDefined, //Default value

								};

								/* @enum	DalFindModuleResult
								* @brief	An enum defining the return values for FindModule function.
								*/
								public enum class DalNIBPMode
								{
									Adult = 0, /**< Adult mode blood pressure measurement. */
									Pediatric = 1, /**< Pediatric mode blood pressure measurement. */
									Neonate = 2 /**< Neonate mode blood pressure measurement. */
								};

								/* @enum	DalNibpCommandType
								* @brief	The type of NIBP command
								*/
								public enum class DalNibpCommandType
								{
									ForeGroundCommand, /**<foreground command (o & K) reponses  */
									BackgroundCommand /**< Background type. (recieves specific data */
								};

								/**
								* @enum	DalNibpForegroundCommandState
								* @brief	The tate of the command object w.r.t. the response recieved
								*/
								public enum class DalNibpForegroundCommandState
								{
									NotSent, /**<  Object has been created but not sent */
									WaitingForO, /**< Command has been sent but no response so far */
									RecievedO, /**< O packet recieved  */
									RecievedK, /**< K packet recieved */
									RecievedA, /**< A packet recieved */
									Busy /**<  Busy packet recieved*/

								};

								/**
								* @enum	DalNibpBackGroundCommandState
								* @brief	The state of the command object w.r.t. the response recieved
								*/
								public enum class DalNibpBackGroundCommandState
								{
									NotSent, /**<  */
									WaitingForResponse, /**<  */
									ResponseRecieved /**<  */
								};

								/**
								* @struct DalNibpData
								* @brief Structure to store NIBP Data
								*/
								public ref struct DalNibpData
								{
									internal:
										unsigned int Sss; /**< Systolic value */
										unsigned int Ddd; /**< Diastolic value */
										//unsigned char Btc; //unused for now
										unsigned char Bps; /**< status of this BP measurement */
										unsigned int Rate; /**< Heart rate in Bpm */
										unsigned int Map; /**< Mean Arterial Pressure */
										unsigned char Ec; /**< Error Code */
								};


								private ref class DalNibpEnvironmentVariables
								{
									private:
										DalNibpEnvironmentVariables()
										{
											//FxCop
										}

									internal:
										static bool bpMeasurementInProgress; 
										//TODO: see if we can shift all such variables accessed accross classes into a common class?
			
								};
								
								/**
								* @enum	NibpMeasurementStatus
								* @brief	The result of the NIBP measurement session.
								*/
								public enum class NibpMeasurementStatus
								{
									Successful, /**< The measurement was successful and the data can be used.*/
									Unsuccessful /**< Measurement was unsuccesfully terminated. Do not use the data. Check the error message.*/
								};


		} // End Namespace DataAccess
	} // End Namespace Scor
} // End Namespace AtCor

