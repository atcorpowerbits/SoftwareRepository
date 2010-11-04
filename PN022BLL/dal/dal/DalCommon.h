#pragma once

using namespace System;


namespace AtCor{ 
	namespace Scor { 
		/**
		* @namespace DataAccess
		* @brief	Namepsace to contain Data Access Layer related classes.
		*/
		namespace DataAccess{

								/**
								* @enum	CaptureType
								* @brief	The type of data capture .	
								*/
								public enum CaptureType { 
													Tonometer, /**< Tonometer only */
													CuffPulseCombination, /**< Cuff Pulse combination */
													TonometerAndCuffPulseCombination, /**< Tonometer and Cuff Pulse  reading combination */
													CuffAbsPressure, /**< Cuff Absolute pressure */
													CuffNIBP, /**< Cuff NIBP reading */
													CuffPulse /**< Cuff Pulse only */

												  }; // End CaptureType

								/**
								* @enum	DalDeviceConfigUseageEnum
								* @brief	The configuration information item requested in DalDeviceConfigUsageStruct
								*/
								public enum DalDeviceConfigUseageEnum
								{
									ModuleType, /**< Module type of the device */
									ModuleSerialNumber, /**< Serial number of the device */
									ModuleMainFirmwareVersion, /**< Firmware version */
									ModuleConfigID, /**< Config ID */
									ModuleConfigDate, /**< Configuation Date */
									ModuleCalibrationDate /**< Last calibration date */

								}; // End DalDeviceConfigUseageEnum

								/**
								* @struct DalDeviceConfigUsageStruct
								* @brief	Holds the configuration information for the device.
								*/
								public ref struct DalDeviceConfigUsageStruct
								{
									public:
										property String^ moduleType;
										property String^ moduleSN;
										property String^ moduleMainFWVersion;
										property unsigned short moduleConfigId;
										property DateTime moduleConfigDate;
										property DateTime moduleCalibrationDate;

								}; // End DalDeviceConfigUsageStruct

								/**
								* @class DalException
								* Exception class for DataAccess namespace.
								*/
								public ref class DalException:Exception
								{
								private:
									int _errCode;
								public: 
									/**
									* Default constructor
									*/
									DalException(): _errCode(0) { }
									
									/**
									* Overloaded constructor
									* @param[in]	exError	The error code to intitialize this constructor with.
									*/
									DalException(int exError): _errCode(exError) { }
									
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
								}; // End DalException

		} // End Namespace DataAccess
	} // End Namespace Scor
} // End Namespace AtCor

