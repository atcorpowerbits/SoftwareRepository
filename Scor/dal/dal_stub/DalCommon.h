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
			* @class DalConstants
			* @brief THis class stores all constants needed for the dal layer.
			*/
			public ref class DalConstants
			{
				public:
					static const unsigned int DataSamplingInterval      = 4; // in msec
					static const unsigned int SimulationTimerInterval   = 4; // in msec
			};

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
								* @enum	DalDeviceConfigUsageEnum
								* @brief	The configuration information item requested in DalDeviceConfigUsageStruct
								*/
								public enum DalDeviceConfigUsageEnum
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
								* @class DalException
								* Exception class for DataAccess namespace.
								*/
								public ref class DalException:Exception
								{
								private:
									int         _errCode;
                                    String^		_errMsg;
                                    Exception^	_eObj;
								public: 
									/**
									* Default constructor
									*/
									DalException(): _errCode(0), _errMsg(""), _eObj(nullptr) { }
									
									/**
									* Overloaded constructor
									* @param[in]	exError	The error code to intitialize this constructor with.
									*/
									DalException(int exError): _errCode(exError), _errMsg(""), _eObj(nullptr) { }

                                    /**
				                    * Overloaded constructor for Exception object
				                    * @param[in]	eExp	The Unknown (System) Exception object to intitialize this constructor with.
				                    */
                                    DalException(Exception^ eExp): _errCode(0), _errMsg(eExp->Message), _eObj(eExp) { }

                                    /**
				                    /* Overloaded constructor for String
				                    * @param[in]	errExpStr	The String to intitialize this constructor with.
				                    */
				                    DalException(String^ errExpStr): _errCode(0), _errMsg(errExpStr), _eObj(nullptr) { }

                                    /**
				                    /* Overloaded constructor for String
                                    * @param[in]	exError	The error code to intitialize this constructor with.
				                    * @param[in]	errExpStr	The String to intitialize this constructor with.
                                    * @param[in]	eExp	The Unknown (System) Exception object to intitialize this constructor with.
				                    */
				                    DalException(int exError, String^ errExpStr, Exception^ eExp): _errCode(exError), _errMsg(errExpStr), _eObj(eExp) { }
									
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
					                        return _eObj;
				                        }
			                        }
								}; // End DalException

		} // End Namespace DataAccess
	} // End Namespace Scor
} // End Namespace AtCor

