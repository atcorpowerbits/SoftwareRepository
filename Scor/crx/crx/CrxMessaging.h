/*
     Copyright (C) ATCOR MEDICAL PTY LTD, 2010
 
     Filename     :      CrxMessaging.h
        
	 Author       :      Smarajit Mishra
 
     Description  :      Declaration for Cross-cutting Messaging namespace
*/

#include "CrxCrossCutting.h"

using namespace System;
using namespace System::IO;// For FileStream

//For reading resource file
using namespace System::Resources;
using namespace System::Globalization;
using namespace System::Threading;
using namespace System::Reflection;	
using namespace System::Drawing;

/**
 * @namespace	AtCor::Scor::CrossCutting::Messaging
 * @brief		This namespace implements messaging related cross-cutting functionalities.
 * 
 */
namespace AtCor {
	namespace Scor { 
		namespace CrossCutting { 
			namespace Messaging {	

			// Creating CrxStructCommonResourceMsg Structure and variables
			/**
			* @struct CrxStructCommonResourceMsg
			 * @brief Container for application message resource string name and code. 
			 */
			public ref struct CrxStructCommonResourceMsg
			{
				static  String^ const  ErrorStringNotFound						=	"201 : Error code not found.";
				static	String^ const  ResourceFileNotFound						=	"200 : Resource file not found.";
				static  String^ const  ApplicationError                         =   "Application Error";

				static  String^ const  Activestatus								=	"ActiveStatus";
				static  String^ const  AgeNotSafe								=	"AGE_NOT_SAFE";
				static  String^ const  AgeWarningCuffFitting					=	"AGE_WARNING_CUFF_FITTING";
				static  String^ const  AgeWarningNoClinicalData					=	"AGE_WARNING_NO_CLINICAL_DATA";
				static  String^ const  Alarmsourceunknown						=	"AlarmSourceUnknown";
				static  String^ const  Alarmstatus								=	"AlarmStatus";
				static  String^ const  AnalysisXaxisTitle						=	"ANALYSIS_XAXIS_TITLE";
				static  String^ const  AppMode									=	"APP_MODE";
				static  String^ const  AppMsg									=	"APP_MSG";
				static  String^ const  AppName									=	"APP_NAME";
				static  String^ const  AppVersion								=	"APP_VERSION";
				static  String^ const  ApplicationMessage						=	"APPLICATION_MESSAGE";
				static  String^ const  BackupDone								=	"BACKUP_DONE";
				static  String^ const  BackupFail								=	"BACKUP_FAIL";
				static  String^ const  BackupProgress							=	"BACKUP_PROGRESS";
				static  String^ const  BackupTitle								=	"BACKUP_TITLE";
				static  String^ const  BirthDateCannotBeFutureDate				=	"BIRTH_DATE_CANNOT_BE_FUTURE_DATE";
				static  String^ const  BllCuffDeflating							=	"BLL_CUFF_DEFLATING";
				static  String^ const  BllStartCaptureFailed					=	"BLL_START_CAPTURE_FAILED";
				static  String^ const  BllStopCaptureFailed						=	"BLL_STOP_CAPTURE_FAILED";
				static  String^ const  BpGradeIht								=	"BP_GRADE_I_HT";
				static  String^ const  BpGradeIhtRange							=	"BP_GRADE_I_HT_RANGE";
				static  String^ const  BpGradeIiAndIiiHt						=	"BP_GRADE_II_AND_III_HT";
				static  String^ const  BpGradeIiAndIiiHtRange					=	"BP_GRADE_II_AND_III_HT_RANGE";
				static  String^ const  BpHighNormal								=	"BP_HIGH_NORMAL";
				static  String^ const  BpHighNormalRange						=	"BP_HIGH_NORMAL_RANGE";
				static  String^ const  BpLblAnalysis							=	"BP_LBL_ANALYSIS";
				static  String^ const  BpNormal									=	"BP_NORMAL";
				static  String^ const  BpNormalRange							=	"BP_NORMAL_RANGE";
				static  String^ const  BpOptimal								=	"BP_OPTIMAL";
				static  String^ const  BpOptimalRange							=	"BP_OPTIMAL_RANGE";

				static  String^ const  BpSettingsDpThresholdValidation			=	"BP_SETTINGS_DP_THRESHOLD_VALIDATION";
				static  String^ const  BpSettingsDpValidation					=	"BP_SETTINGS_DP_VALIDATION";
				static  String^ const  BpSettingsPpThresholdValidation			=	"BP_SETTINGS_PP_THRESHOLD_VALIDATION";
				static  String^ const  BpSettingsPpValidation					=	"BP_SETTINGS_PP_VALIDATION";
				static  String^ const  BpSettingsSpThresholdValidation			=	"BP_SETTINGS_SP_THRESHOLD_VALIDATION";
				static  String^ const  BpSettingsSpValidation					=	"BP_SETTINGS_SP_VALIDATION";
				
				static  String^ const  BtnCancel								=	"BTN_CANCEL";
				static  String^ const  BtnCapture								=	"BTN_CAPTURE";
				static  String^ const  BtnChange								=	"BTN_CHANGE";
				static  String^ const  BtnDefaults								=	"BTN_DEFAULTS";
				static  String^ const  BtnDelete								=	"BTN_DELETE";
				static  String^ const  BtnEdit									=	"BTN_EDIT";
				static  String^ const  BtnExit									=	"BTN_EXIT";
				static  String^ const  BtnFindmodule							=	"BTN_FINDMODULE";
				static  String^ const  BtnGetBp									=	"BTN_GET_BP";
				static  String^ const  BtnMigrate								=	"BTN_MIGRATE";
				static  String^ const  BtnNew									=	"BTN_NEW";
				static  String^ const  BtnOk									=	"BTN_OK";
				static  String^ const  BtnOkTxt									=	"BTN_OK_TXT";
				static  String^ const  BtnPrint									=	"BTN_PRINT";
				static  String^ const  BtnPrintersetup							=	"BTN_PRINTERSETUP";
				static  String^ const  BtnRepeat								=	"BTN_REPEAT";
				static  String^ const  BtnSave									=	"BTN_SAVE";
				static  String^ const  BtnSearch								=	"BTN_SEARCH";
				static  String^ const  BtnSettings								=	"BTN_SETTINGS";
				static  String^ const  BtnStart									=	"BTN_START";
				static  String^ const  BtnStop									=	"BTN_STOP";
				static  String^ const  BtnWait									=   "BTN_WAIT";
				static  String^ const  CDrive									=	"C_DRIVE";
				static  String^ const  CaptureDeviceErrMsg						=	"CAPTURE_DEVICE_ERR_MSG";
				static  String^ const  CaptureFailed							=	"CAPTURE_FAILED";
				static  String^ const  CaptureFailedToStop						=	"CAPTURE_FAILED_TO_STOP";
				static  String^ const  CaptureReportGenMsgForQuickStart			=	"CAPTURE_REPORT_GEN_MSG_FOR_QUICKSTART";
				static  String^ const  CaptureTickMsg							=	"CAPTURE_TICK_MSG";
				static  String^ const  CaptureTimeOutOfRange					=	"CAPTURE_TIME_OUT_OF_RANGE";
				static  String^ const  CaptureTimeToInflation					=	"CAPTURE_TIME_TO_INFLATION";
				static  String^ const  CarotidDistOutOfRange					=	"CAROTID_DIST_OUT_OF_RANGE";
				static  String^ const  CarotidSignalBufferNotFullYet			=	"CAROTID_SIGNAL_BUFFER_NOT_FULL_YET";
				static  String^ const  CarotidSignalCaptureFailed				=	"CAROTID_SIGNAL_CAPTURE_FAILED";
				static  String^ const  ChkFemoralCuff							=	"CHK_FEMORAL_CUFF";
				static  String^ const  ChkNormalRange							=	"CHK_NORMAL_RANGE";
				static  String^ const  ChkPatientPrivacy						=	"CHK_PATIENT_PRIVACY";
				static  String^ const  ChkReferenceRange						=	"CHK_REFERENCE_RANGE";
				static  String^ const  ClinicalEnv								=	"CLINICAL_ENV";
				static  String^ const  Cm										=	"CM";
				static  String^ const  CompanyCopyright							=	"COMPANY_COPYRIGHT";
				static  String^ const  CompanyName								=	"COMPANY_NAME";
				static  String^ const  ComportSimulation						=	"COMPORT_SIMULATION";
				static  String^ const  ConfigNameInvalid						=	"CONFIG_NAME_INVALID";
				static  String^ const  ConfigNamePwv							=	"CONFIG_NAME_PWV";
				static  String^ const  ConfigurationId							=	"CONFIGURATION_ID";
				static  String^ const  ContactAtcorSupport						=	"CONTACT_ATCOR_SUPPORT";
				static  String^ const  ContactAtcorSupport1						=	"CONTACT_ATCOR_SUPPORT1";
				static  String^ const  ContactAtcorSupport2						=	"CONTACT_ATCOR_SUPPORT2";
				static  const   int    CrxErrRestoreReferManualErrCd			=	612;

				static  String^ const  CrxErrDbMgrConversion					=	"CRX_ERR_DBMGR_CONVERSION";
				static  const	int	   CrxErrDbMgrConversionErrCd				=	600;

				static  String^ const  CrxErrDbMgrNoProvider					=	"CRX_ERR_DBMGR_NO_PROVIDER";
				static  const   int    CrxErrDbMgrNoProviderErrCd				=	601;

				static  String^ const  CrxErrDbMgrNoServerName					=	"CRX_ERR_DBMGR_NO_SERVER_NAME";
				static	const   int	   CrxErrDbMgrNoServerNameErrCd				=	602;

				static  String^ const  CrxErrDbMgrNoSourceName					=	"CRX_ERR_DBMGR_NO_SOURCE_NAME";
				static	const   int	   CrxErrDbMgrNoSourceNameErrCd				=	603;

				static  String^ const  CrxErrDbMgrTransFailed					=	"CRX_ERR_DBMGR_TRANS_FAILED";
				static	const   int	   CrxErrDbMgrTransFailedErrCd				=	604;

				static  String^ const  CrxErrDbPermissionReferManual			=	"CRX_ERR_DBPERMISSION_REFER_MANUAL";
				static  const   int    CrxErrDbPermissionReferManualErrCd		=	610;

				static  String^ const  CrxErrFileAlreadyExist					=	"CRX_ERR_FILE_ALREADY_EXIST";
				static  const int      CrxErrFileAlreadyExistErrCd				=	102;

				static  String^ const  CrxErrFileCannotAccess					=	"CRX_ERR_FILE_CANNOT_ACCESS";
				static  const   int    CrxErrFileCannotAccessErrCd				=	103;

				static  String^ const  CrxErrFileCorrupt						=	"CRX_ERR_FILE_CORRUPT";
				static  const int      CrxErrFileCorruptErrCd					=	100;

				static  String^ const  CrxErrFileNotExist						=	"CRX_ERR_FILE_NOT_EXIST";
				static  const   int    CrxErrFileNotExistErrCd					=	101;

				static  String^ const  CrxErrMessagingCannotAccessResoruceFile	="CRX_ERR_MESSAGING_CANNOT_ACCESS_RESORUCE_FILE";
				static	const   int	   CrxErrMessagingcannotAccessResoruceFileErrCd	= 202;

				static  String^ const  CrxErrMessagingGeneral					=	"CRX_ERR_MESSAGING_GENERAL";
				static	const   int	   CrxErrMessagingGeneralErrCd				=	203;

				static  String^ const  CrxErrMigrationReferManual				=	"CRX_ERR_MIGRATION_REFER_MANUAL";
				static  const   int    CrxErrMigrationReferManualErrCd			=	611;				

				static  String^ const  CrxErrMsAccessFileNotExist				=	"CRX_ERR_MSACCESS_FILE_NOT_EXIST";
				static  const   int	   CrxErrMsAccessFileNotExistErrCd			=	605;

				static  String^ const  CrxErrMsaccessFileOldAlreadyExist		=	"CRX_ERR_MSACCESS_FILE_OLD_ALREADY_EXIST";
				
				static  String^ const  CrxErrXmlTagIncorrect					=	"CRX_ERR_XML_TAG_INCORRECT";
				static  const   int	   CrxErrXmlTagIncorrectErrCd				=	301;

				static  String^ const  CrxErrXmlTagIncorrectText				=	"CRX_ERR_XML_TAG_INCORRECT_TEXT";

				static  String^ const  CrxLogFileHeaderLine						=	"CRX_LOG_FILE_HEADER_LINE";
				static  const   int	   CrxLogFileHeaderLineErrCd				=	300;
				
				static  String^ const  CrxLogFileHeaderSeperator				=	"CRX_LOG_FILE_HEADER_SEPERATOR";
				static	const   int	   CrxLogFileHeaderSeperatorErrCd			=	301;

				static  String^ const  CrxUnknownException						=	"CRX_UNKNOWN_EXCEPTION";
				static  const   int	   CrxUnknownExceptionErrCd					=	104;

				static  String^ const  CuffDeflatedTimeNotMonitored				=	"CUFF_DEFLATED_TIME_NOT_MONITORED";
				static  String^ const  CuffDeflationFailed						=	"CUFF_DEFLATION_FAILED";
				static  String^ const  CuffDeflationTimedOut					=	"CUFF_DEFLATION_TIMED_OUT";
				static  String^ const  CuffDistOutOfRange						=	"CUFF_DIST_OUT_OF_RANGE";
				static  String^ const  CuffInflatedTimeNotMonitored				=	"CUFF_INFLATED_TIME_NOT_MONITORED";
				static  String^ const  CuffInflationFailed						=	"CUFF_INFLATION_FAILED";
				static  String^ const  CuffInflationTimedOut					=	"CUFF_INFLATION_TIMED_OUT";


				static  String^ const  CuffPulseAppendFailed					=	"CUFF_PULSE_APPEND_FAILED";
				static  String^ const  CuffReinflating							=	"CUFF_REINFLATING";
				static  String^ const  CuffReinflationFailed					=	"CUFF_REINFLATION_FAILED";
				static  String^ const  CuffStateInvalid							=	"CUFF_STATE_INVALID";
				static  String^ const  Cuffleak									=	"CuffLeak";

				static  String^ const  DalConstCaptureFilePrefix				=	"DAL_CONST_CAPTURE_FILE_PREFIX";
				static  String^ const  DalConstCufftimerFilePath				=	"DAL_CONST_CUFFTIMER_FILE_PATH";
				static  String^ const  DalConstDatFileExtn						=	"DAL_CONST_DAT_FILE_EXTN";
				static  String^ const  DalConstGciFirmwareVersion				=	"DAL_CONST_GCI_FIRMWARE_VERSION";
				static  String^ const  DalConstGciSerialNumber					=	"DAL_CONST_GCI_SERIAL_NUMBER";
				static  String^ const  DalConstGciType							=	"DAL_CONST_GCI_TYPE";
				static  String^ const  DalConstSimFolderPath					=	"DAL_CONST_SIM_FOLDER_PATH";
				static  String^ const  DalConstSimFolderPathPwa					=	"DAL_CONST_SIM_FOLDER_PATH_PWA";
				static  String^ const  Dal_DeviceIdling_Message		            =   "DAL_DEVICE_IDLING_MESSAGE";
				static  String^ const  Dal_DeviceNotReady_Message				=   "DAL_DEVICE_NOT_READY_MESSAGE";      
				static  String^ const  DalErrActivePortCloseFailed				=	"DAL_ERR_ACTIVE_PORT_CLOSE_FAILED";
				static	const   int	   DalErrActivePortCloseFailedErrCd			=	1025;

				static  String^ const  DalErrInvalidPortClose					=	"DAL_ERR_INVALID_PORT_CLOSE";
				static	const   int	   DalErrInvalidPortCloseErrCd				=	1027;

				static  String^ const  DalErrNibpPacketD						=	"DAL_ERR_NIBP_PACKET_D";
				static	const   int	   DalErrNibpPacketDErrCd					=	1030;

				static  String^ const  DalErrNibpPacketE						=	"DAL_ERR_NIBP_PACKET_E";
				static	const   int	   DalErrNibpPacketEErrCd					=	1031;

				static  String^ const  DalErrNibpPacketN						=	"DAL_ERR_NIBP_PACKET_N";
				static	const   int	   DalErrNibpPacketNErrCd					=	1032;

				static  String^ const  DalErrNibpPacketT						=	"DAL_ERR_NIBP_PACKET_T";
				static	const   int	   DalErrNibpPacketTErrCd					=	1033;

				static  String^ const  DalErrPortOpenFailed						=	"DAL_ERR_PORT_OPEN_FAILED";
				static	const   int	   DalErrPortOpenFailedErrCd				=	1026;
				
				static  String^ const  DalErrArrayCreateFailed					=	"DAL_ERR_ARRAY_CREATE_FAILED";
				static	const   int	   DalErrArrayCreateFailedErrCd				=	1000;

				static  String^ const  DalErrBufferNotCreated					=	"DAL_ERR_BUFFER_NOT_CREATED";
				static  const   int	   DalErrBufferNotCreatedErrCd				=	1001;

				static  String^ const  DalErrBufferWriteFailed					=	"DAL_ERR_BUFFER_WRITE_FAILED";
				static  const   int	   DalErrBufferWriteFailedErrCd				=	1015;

				static  String^ const  DalErrCaptureInvalidPacket				=	"DAL_ERR_CAPTURE_INVALID_PACKET";
				static  const   int    DalErrCaptureInvalidPacketErrCd			=   1029;
	
				static  String^ const  DalErrCommandFailed						=	"DAL_ERR_COMMAND_FAILED";
				static  const   int	   DalErrCommandFailedErrCd					=	1021;

				static  String^ const  DalErrCommdPacketCreateFail				=	"DAL_ERR_COMMD_PACKET_CREATE_FAIL";
				static	const   int	   DalErrCommdPacketCreateFailErrCd			=	1023;

				static  String^ const  DalErrComportNotSet						=	"DAL_ERR_COMPORT_NOT_SET";
				static  const	int	   DalErrComportNotSetErrCd					=	1002;

				static  String^ const  DalErrConfigPortNotConnected				=	"DAL_ERR_CONFIG_PORT_NOT_CONNECTED";
				static  const   int	   DalErrConfigPortNotConnectedErrCd		=	1019;

				static  String^ const  DalErrCrcCalcFailed						=	"DAL_ERR_CRC_CALC_FAILED";
				static  const   int	   DalErrCrcCalcFailedErrCd					=	1010;

				static  String^ const  DalErrCrcTableFailed						=	"DAL_ERR_CRC_TABLE_FAILED";
				static  const   int	   DalErrCrcTableFailedErrCd				=	1009;

				static  String^ const  DalErrEmptSimulationFile					=	"DAL_ERR_EMPT_SIMULATION_FILE";
				static  const	int	   DalErrEmptSimulationFileErrCd			=	1003;

				static  String^ const  DalErrEmptyCommand						=	"DAL_ERR_EMPTY_COMMAND";
				static  const   int	   DalErrEmptyCommandErrCd					=	1012;
				

				static  String^ const  DalErrEmptyResponseValidation			=	"DAL_ERR_EMPTY_RESPONSE_VALIDATION";
				static  const   int	   DalErrEmptyResponseValidationErrCd		=	1017;

				static  String^ const  DalErrFileNotSet							=	"DAL_ERR_FILE_NOT_SET";
				static  const   int	   DalErrFileNotSetErrCd					=	1004;

				static  String^ const  DalErrInvalidArgs						=	"DAL_ERR_INVALID_ARGS";
				static	const	int	   DalErrInvalidArgsErrCd					=	1005;

				static  String^ const  DalErrNoCommportName						=	"DAL_ERR_NO_COMMPORT_NAME";
				static  const   int	   DalErrNoCommportNameErrCd				=	1011;

				static  String^ const  DalErrNoInterface						=	"DAL_ERR_NO_INTERFACE";
				static  const   int	   DalErrNoInterfaceErrCd					=	1022;

				static  String^ const  DalErrPortNotOpen						=	"DAL_ERR_PORT_NOT_OPEN";
				static  const   int	   DalErrPortNotOpenErrCd					=	1013;

				static  String^ const  DalErrPortSimulation						=	"DAL_ERR_PORT_SIMULATION";
				static  const   int	   DalErrPortSimulationErrCd				=	1018;

				static  String^ const  DalErrRequestTooLarge					=	"DAL_ERR_REQUEST_TOO_LARGE";
				static  const   int	   DalErrRequestTooLargeErrCd				=	1006;

				static  String^ const  DalErrResponseInvalid					=	"DAL_ERR_RESPONSE_INVALID";
				static  const   int	   DalErrResponseInvalidErrCd				=	1016;

				static  String^ const  DalErrResponseResolveFailure				=	"DAL_ERR_RESPONSE_RESOLVE_FAILURE";
				static  const   int	   DalErrResponseResolveFailureErrCd		=	1014;

				static  String^ const  DalErrTonoNotConnected					=	"DAL_ERR_TONO_NOT_CONNECTED";
				static  const   int	   DalErrTonoNotConnectedErrCd				=	1020;

				static  String^ const  DalErrUnknownBitFlag						=	"DAL_ERR_UNKNOWN_BIT_FLAG";
				static  const   int	   DalErrUnknownBitFlagErrCd				=	1007;

				static  String^ const  DalErrorNullParam						=	"DAL_ERROR_NULL_PARAM";
				static  const   int    DalErrorNullParamErrCd                   =   1028;

				static  String^ const  DalMsgBpError88							=	"DAL_MSG_BP_ERROR_88";
				static  String^ const  DalMsgBpErrorOther						=	"DAL_MSG_BP_ERROR_OTHER";

				static  String^ const  DalMsgDefaultModeSelectedSim				=	"DAL_MSG_DEFAULT_MODE_SELECTED_SIM";
				static  String^ const  DalMsgIllegalPacketRcvd					=	"DAL_MSG_ILLEGAL_PACKET_RCVD";
				static  String^ const  DalMsgPortBufferDump						=	"DAL_MSG_PORT_BUFFER_DUMP";
				static  String^ const  Dalunknownmodulestatus					=	"DALUnknownModuleStatus";
				static  String^ const  DataCaptureInconsistent					=	"DATA_CAPTURE_INCONSISTENT";
				static  String^ const  DataRevInvalid							=	"DATA_REV_INVALID";
				static  String^ const  Day										=	"DAY";
				static  String^ const  DbCorrupt								=	"DB_CORRUPT";
				static  String^ const  DeletePateint							=	"DELETE_PATEINT";
				static  String^ const  DeletePwvMsg								=	"DELETE_PWV_MSG";
				static  String^ const  Direct									=	"DIRECT";
				static  String^ const  DirectMethod								=	"DIRECT_METHOD";
				static  String^ const  DobNotEntered							=	"DOB_NOT_ENTERED";
				static  String^ const  DocBpSettings							=	"DOC_BP_SETTINGS";
				static  String^ const  DocGeneralSettings						=	"DOC_GENERAL_SETTINGS";
				static  String^ const  DocPwaSettings							=	"DOC_PWA_SETTINGS";
				static  String^ const  DocPwvSettings							=	"DOC_PWV_SETTINGS";
				static  String^ const  Dp										=	"DP";
				static  String^ const  DpOutOfRange								=	"DP_OUT_OF_RANGE";
				static  String^ const  Dualsensors								=	"DualSensors";
				static  String^ const  EditMode									=	"EDIT_MODE";
				static  String^ const  EnterLastName							=	"ENTER_LAST_NAME";
				static  String^ const  EnvClinicalText							=	"ENV_CLINICAL_TEXT";
				static  String^ const  ErrUnknownError							=	"ERR_UNKNOWN_ERROR";
				static  String^ const  ErrorValidating							=	"ERROR_VALIDATING";
				static  String^ const  Errorandalarmstatus						=	"ErrorAndAlarmStatus";
				static  String^ const  Errorsourceunknown							=	"ErrorSourceUnknown";
				static  String^ const  Errorstatus								=	"ErrorStatus";
				static  String^ const  ExecError								=	"EXEC_ERROR";
				static  String^ const  Exitstr									=	"EXITSTR";
				static  String^ const  ExpanderInital							=	"EXPANDER_INITAL";
				static  String^ const  Feet										=	"FEET";
				static  String^ const  FemaleTxt								=	"FEMALE";
				static  String^ const  Femoral2CuffOutOfRange					=	"FEMORAL_2_CUFF_OUT_OF_RANGE";
				static  String^ const  FemoralSignalBufferNotFullYet			=	"FEMORAL_SIGNAL_BUFFER_NOT_FULL_YET";
				static  String^ const  FemoralSignalCaptureFailed				=	"FEMORAL_SIGNAL_CAPTURE_FAILED";
				static  String^ const  FemoralDistanceCarotidToFemoralCuff		=	"FIELD_DISTANCE_CAROTID_TO_FEMORAL_CUFF";
				static  String^ const  FemoralDistanceCarotidToSternalCuff		=	"FIELD_DISTANCE_CAROTID_TO_STERNAL_NOTCH";
				static  String^ const  FemoralDistanceFemoraltoCuff				=	"FIELD_DISTANCE_FEMORAL_TO_CUFF";
				static  String^ const  FemoralDistanceSternalNotchToFemoralCuff	=	"FIELD_DISTANCE_STERNAL_NOTCH_TO_FEMORAL_CUFF";
				static  String^ const  FieldPatientDp							=	"FIELD_PATIENT_DP";
				static  String^ const  FieldPatientHeight						=	"FIELD_PATIENT_HEIGHT";
				static  String^ const  FieldPatientHeightFoot					=	"FIELD_PATIENT_HEIGHT_FOOT";
				static  String^ const  FieldPatientHeightInch					=	"FIELD_PATIENT_HEIGHT_INCH";
				static  String^ const  FieldPatientHr							=	"FIELD_PATIENT_HR";
				static  String^ const  FieldPatientPp							=	"FIELD_PATIENT_PP";
				static  String^ const  FieldPatientSp							=	"FIELD_PATIENT_SP";
				static  String^ const  FieldPatientWeight						=	"FIELD_PATIENT_WEIGHT";
				static  String^ const  FieldValidationLimitsAre					=	"FIELD_VALIDATION_LIMITS_ARE";
				static  String^ const  FieldValidationMustBeNumber				=	"FIELD_VALIDATION_MUST_BE_NUMBER";
				static  String^ const  FileNotFound								=	"FILE_NOT_FOUND";
				static  String^ const  FrmBrachialBpConfiguration				=	"FRM_BRACHIAL_BP_CONFIGURATION";
				static  String^ const  FrmGeneralConfiguration					=   "FRM_GENERAL_CONFIGURATION";
				static  String^ const  FrmNewSystemKey							=	"FRM_NEWSYSTEM_KEY";
				static  String^ const  FrmPwaConfiguration						=	"FRM_PWA_CONFIGURATION";
				static  String^ const  FrmPwvConfiguration						=	"FRM_PWV_CONFIGURATION";
				static  String^ const  FrmSystemKey								=	"FRM_SYSTEM_KEY";
				static  String^ const  GroupnameEmpty							=	"GROUPNAME_EMPTY";
				static  String^ const  GroupnameExists							=	"GROUPNAME_EXISTS";
				static  String^ const  GrpAugmentationIndex						=	"GRP_AUGMENTATION_INDEX";
				static  String^ const  GrpAugmentationIndexHr75					=	"GRP_AUGMENTATION_INDEX_@HR75";
				static  String^ const  GrpAutoCapture							=	"GRP_AUTO_CAPTURE";
				static  String^ const  GrpAutoInflate							=	"GRP_AUTO_INFLATE";
				static  String^ const  GrpAutoPwa								=	"GRP_AUTO_PWA";
				static  String^ const  GrpBlindStudy							=	"GRP_BLIND_STUDY";
				static  String^ const  GrpBloodPressure							=	"GRP_BLOOD_PRESSURE";
				static  String^ const  GrpBpDevice								=	"GRP_BP_DEVICE";
				static  String^ const  GrpCaptureGuide							=	"GRP_CAPTURE_GUIDE";
				static  String^ const  GrpCaptureInput							=	"GRP_CAPTURE_INPUT";
				static  String^ const  GrpCaptureTime							=	"GRP_CAPTURE_TIME";
				static  String^ const  GrpClinicalReport						=	"GRP_CLINICAL_REPORT";
				static  String^ const  GrpCommsPort								=	"GRP_COMMS_PORT";
				static  String^ const  GrpCuffLocation							=	"GRP_CUFF_LOCATION";
				static  String^ const  GrpDefaultPrintedReport					=	"GRP_DEFAULT_PRINTED_REPORT";
				static  String^ const  GrpGuidanceBars                          =   "GRP_GUIDANCE_BAR";
				static  String^ const  GrpHeightWeightUnits						=	"GRP_HEIGHT_WEIGHT_UNITS";
				static  String^ const  GrpIfDp									=	"GRP_IF_DP";
				static  String^ const  GrpIfPp									=	"GRP_IF_PP";
				static  String^ const  GrpIfSp									=	"GRP_IF_SP";
				static  String^ const  GrpNoOfAssessments						=	"GRP_NO_OF_ASSESSMENTS";
				static  String^ const  GrpOther									=	"GRP_OTHER";
				static  String^ const  GrpPressureCuff							=	"GRP_PRESSURE_CUFF";
				//static  String^ const  GrpPwa									=	"GRP_PWA";
				//static  String^ const  GrpPwv									=	"GRP_PWV";
				static  String^ const  GrpPwvDistanceMethod						=	"GRP_PWV_DISTANCE_METHOD";
				static  String^ const  GrpPwvDistanceUnits						=	"GRP_PWV_DISTANCE_UNITS";
				//static  String^ const  GrpQuickStart							=	"GRP_QUICK_START";
				static  String^ const  GrpReportScreen							=	"GRP_REPORT_SCREEN";
				static  String^ const  GrpReports								=	"GRP_REPORTS";
				static  String^ const  GrpSetupScreen							=	"GRP_SETUP_SCREEN";
				static  String^ const  GrpSimulationFiles						=	"GRP_SIMULATION_FILES";
				static  String^ const  GrpSphycomor								=	"GRP_SPHYCOMOR";
				static  String^ const  GrpStartupMode							=	"GRP_STARTUP_MODE";
				static  String^ const  GrpStartupScreen							=	"GRP_STARTUP_SCREEN";
				static  String^ const  GrpTonometer								=	"GRP_TONOMETER";
				static  String^ const  GuiAboutCalibDate						=	"GUI_ABOUT_CALIB_DATE";
				static  String^ const  GuiAboutCapabilityTxt					=	"GUI_ABOUT_CAPABILITY_TXT";
				static  String^ const  GuiAboutCeMark							=	"GUI_ABOUT_CE_MARK";
				static  String^ const  GuiAboutCompany							=	"GUI_ABOUT_COMPANY";
				static  String^ const  GuiAboutCopyright						=	"GUI_ABOUT_COPYRIGHT";
				static  String^ const  GuiAboutFirmVersion						=	"GUI_ABOUT_FIRM_VERSION";
				static  String^ const  GuiAboutInstallId						=	"GUI_ABOUT_INSTALL_ID";
				static  String^ const  GuiAboutMeasuremtBp						=	"GUI_ABOUT_MEASUREMT_BP";
				static  String^ const  GuiAboutMeasuremtPwa						=	"GUI_ABOUT_MEASUREMT_PWA";
				static  String^ const  GuiAboutMenu								=	"GUI_ABOUT_MENU";
				static  String^ const  GuiAboutModType							=	"GUI_ABOUT_MOD_TYPE";
				static  String^ const  GuiAboutModuleTxt						=	"GUI_ABOUT_MODULE_TXT";
				static  String^ const  GuiAboutNoMeasuremtPwv					=	"GUI_ABOUT_NO_MEASUREMT_PWV";
				static  String^ const  GuiAboutSecMode						=	"GUI_ABOUT_SEC_MODE";
				static  String^ const  GuiAboutSerialNo						=	"GUI_ABOUT_SERIAL_NO";
				static  String^ const  GuiAboutVersion						=	"GUI_ABOUT_VERSION";
				static  String^ const  GuiAnnualCallibrationMesg			=	"GUI_ANNUAL_CALLIBRATION_MESSAGE";
				static  String^ const  GuiAtcorHomepageMenu					=	"GUI_ATCOR_HOMEPAGE_MENU";
				static  String^ const  GuiBackupMenu						=	"GUI_BACKUP_MENU";
				static  String^ const  GuiCaptureCanNotContinue				=	"GUI_CAPTURE_CANNOT_CONTINUE";
				static  String^ const  GuiCaptureCuffInflated				=	"GUI_CAPTURE_CUFF_INFLATED";
				static  String^ const  GuiCaptureCuffInflatingMsg			=	"GUI_CAPTURE_CUFF_INFLATING_MSG";
				static  String^ const  GuiCaptureDeflatedMsg				=	"GUI_CAPTURE_DEFLATED_MSG";
				static  String^ const  GuiCaptureError						=	"GUI_CAPTURE_ERROR";
				static  String^ const  GuiCaptureGeneratingReport			=	"GUI_CAPTURE_GENERATING_REPORT";
				static  String^ const  GuiCaptureSavingReport				=	"GUI_CAPTURE_SAVING_REPORT";
				static  String^ const  GuiDatetimeTxt						=	"GUI_DATETIME_TXT";
				
				static  String^ const  GuiDirect							=	"GUI_DIRECT";
				static  String^ const  GuiDisplayAmpersand					=	"GUI_DISPLAY_AMPERSAND";
				static  String^ const  GuiDisplayAsteriskColon				=	"GUI_DISPLAY_ASTERISK_COLON";

				static  String^ const  GuiDisplayColon						=	"GUI_DISPLAY_COLON";
				static  String^ const  GuiDisplayComma						=	"GUI_DISPLAY_COMMA";

				static  String^ const  GuiDisplaydmyyyy						=	"GUI_DISPLAY_D_M_YYYY";
				static  String^ const  GuiDisplayddmmyyyy					=	"GUI_DISPLAY_DD_MM_YYYY";
				static  String^ const  GuiDisplayErrorException				=	"GUI_DISPLAY_ERROR_EXCEPTION";
				static  String^ const  GuiDisplayFirstName					=	"GUI_DISPLAY_FIRST_NAME";
				static  String^ const  GuiDisplayGender						=	"GUI_DISPLAY_GENDER";
				static  String^ const  GuiDisplayGroup						=	"GUI_DISPLAY_GROUP";
				static  String^ const  GuiDisplayLastName					=	"GUI_DISPLAY_LAST_NAME";

				static  String^ const  GuiDisplayLeftCurlyBracket			=	"GUI_DISPLAY_LEFT_CURLY_BRACKET";
				static  String^ const  GuiDisplayLeftSqrBracket				=	"GUI_DISPLAY_LEFT_SQR_BRACKET";

				static  String^ const  GuiDisplayNoValueResourceString		=	"GUI_DISPLAY_NO_VALUE_RESOURCE_STRING";
				static  String^ const  GuiDisplayPatientId					=	"GUI_DISPLAY_PATIENT_ID";


				static  String^ const  GuiDisplayRightCurlyBracket			=	"GUI_DISPLAY_RIGHT_CURLY_BRACKET";
				static  String^ const  GuiDisplayRightSqrBracket			=	"GUI_DISPLAY_RIGHT_SQR_BRACKET";
				static  String^ const  GuiDisplaySemiColon					=	"GUI_DISPLAY_SEMICOLON";
				static  String^ const  GuiDisplaySingleQuote				=	"GUI_DISPLAY_SINGLE_QUOTE";
				static  String^ const  GuiDisplaySlash						=	"GUI_DISPLAY_SLASH";
				static  String^ const  GuiDisplayStudyDateTime				=	"GUI_DISPLAY_STUDY_DATE_TIME";

				static  String^ const  GuiElectronicModFnd					=	"GUI_ELECTRONIC_MOD_FND";
				static  String^ const  GuiElectronicModFndport				=	"GUI_ELECTRONIC_MOD_FNDPORT";
				static  String^ const  GuiElectronicModNotfnd				=	"GUI_ELECTRONIC_MOD_NOTFND";
				static  String^ const  GuiErrorTxt							=	"GUI_ERROR_TXT";
				static  String^ const  GuiExitMenu							=	"GUI_EXIT_MENU";
				static  String^ const  GuiExitMsg							=	"GUI_EXIT_MSG";
				static  String^ const  GuiFemoral							=	"GUI_FEMORAL";
				static  String^ const  GuiFindModuleMenu					=	"GUI_FIND_MODULE_MENU";
				static  String^ const  GuiGrpDefaultReport					=	"GUI_GRP_DEFAULT_REPORT";
				static  String^ const  GuiInConclusivePwaReportInitialMesg	=	"GUI_INCONCLUSIVE_PWA_REPORT_INITIAL_MESSAGE";
				static  String^ const  GuiInfoTxt							=	"GUI_INFO_TXT";
				static  String^ const  GuiLimitsFormat						=	"GUI_LIMITS_FORMAT";
				static  String^ const  GuiMenuSupport						=	"GUI_MENU_SUPPORT";
				static  String^ const  GuiMonthApr							=	"GUI_MONTH_APR";
				static  String^ const  GuiMonthAug							=	"GUI_MONTH_AUG";
				static  String^ const  GuiMonthDec							=	"GUI_MONTH_DEC";
				static  String^ const  GuiMonthFeb							=	"GUI_MONTH_FEB";
				static  String^ const  GuiMonthJan							=	"GUI_MONTH_JAN";
				static  String^ const  GuiMonthJul							=	"GUI_MONTH_JUL";
				static  String^ const  GuiMonthJun							=	"GUI_MONTH_JUN";
				static  String^ const  GuiMonthMar							=	"GUI_MONTH_MAR";
				static  String^ const  GuiMonthMay							=	"GUI_MONTH_MAY";
				static  String^ const  GuiMonthNov							=	"GUI_MONTH_NOV";
				static  String^ const  GuiMonthOct							=	"GUI_MONTH_OCT";
				static  String^ const  GuiMonthSep							=	"GUI_MONTH_SEP";
				
				static  String^ const  GuiNibpAssessmentProgressMsg			=	"GUI_NIBP_ASSESSMENT_PROGRESS_MSG";
				static  String^ const  GuiNibpCuffPressure					=	"GUI_NIBP_CUFF_PRESSURE";
				static  String^ const  GuiOperatorGuideMenu					=	"GUI_OPERATOR_GUIDE_MENU";
				static  String^ const  GuiPleaseEnterFormat					=	"GUI_PLEASE_ENTER_FORMAT";
				static  String^ const  GuiPrintPwaClinicalTitle				=	"GUI_PRINT_PWA_CLINICAL_TITLE";
				static  String^ const  GuiPrintPwaEvaluationTitle			=	"GUI_PRINT_PWA_EVALUATION_TITLE";
				static  String^ const  GuiPrintPwaQuickStartTitle			=	"GUI_PRINT_PWA_QUICK_START_TITLE";
				static  String^ const  GuiPrintPwaTrendAnalysisTitle		=	"GUI_PRINT_PWA_TREND_ANALYSIS_TITLE";
				static  String^ const  GuiPrintPwvAnalysisBpChartValue		=	"GUI_PRINT_PWV_ANALYSIS_BPCHART_VALUE";
				static  String^ const  GuiPrintPwvAnalysisLegendTitle		=	"GUI_PRINT_PWV_ANALYSIS_LEGEND_TITLE";
				static  String^ const  GuiPrintPwvAnalysisTitle				=	"GUI_PRINT_PWV_ANALYSIS_TITLE";
				static  String^ const  GuiPrintPwvRptTitle					=	"GUI_PRINT_PWV_RPT_TITLE";
				static  String^ const  GuiPrinterSetup						=	"GUI_PRINTER_SETUP";
				static  String^ const  GuiReportActual						=	"GUI_REPORT_ACTUAL";
				static  String^ const  GuiReportAgeOutsideRange				=	"GUI_REPORT_AGE_OUTSIDE_RANGE";
				static  String^ const  GuiReportBpColon						=	"GUI_REPORT_BP_COLON";
				static  String^ const  GuiReportGenPopDesc					=	"GUI_REPORT_GENERAL_POP_DESCRIPTION";
				static  String^ const  GuiReportGenPopText					=	"GUI_REPORT_GENERAL_POP_TEXT";
				static  String^ const  GuiReportGreenArea					=	"GUI_REPORT_GREEN_AREA";
				static  String^ const  GuiReportLblBpRange					=	"GUI_REPORT_LBL_BP_RANGE";
				static  String^ const  GuiReportNoBp						=	"GUI_REPORT_NO_BP";
				static  String^ const  GuiReportPatientHeightOutsideRange	=	"GUI_REPORT_PATIENT_HEIGHT_OUTSIDE_RANGE";
				static  String^ const  GuiReportPwvColon					=	"GUI_REPORT_PWV_COLON";
				static  String^ const  GuiReportRedArea						=	"GUI_REPORT_RED_AREA";
				static  String^ const  GuiReportTypical						=	"GUI_REPORT_TYPICAL";
				static  String^ const  GuiRestoreMenu						=	"GUI_RESTORE_MENU";
				static  String^ const  GuiResultCalFailMsg					=	"GUI_RESULT_CAL_FAIL_MSG";
				static  String^ const  GuiResultDataLossMsg					=   "GUI_RESULT_DATA_LOSS_MSG";
				static  String^ const  GuiRptRefRangeDesc					=	"GUI_RPT_REF_RANGE_DESC";
				static  String^ const  GuiScreenResolutionMsg				=	"GUI_SCREEN_RESOLUTION_MSG";
				static  String^ const  GuiSearchElectronicMod				=	"GUI_SEARCH_ELECTRONIC_MOD";
				static  String^ const  GuiSelectSimulationFile				=	"GUI_SELECT_SIMULATION_FILE";
				static  String^ const  GuiSelectSqlInstance					=	"GUI_SELECT_SQL_INSTANCE";
				static  String^ const  GuiServiceManualMenu					=	"GUI_SERVICE_MANUAL_MENU";
				static  String^ const  GuiSettingsMenu						=	"GUI_SETTINGS_MENU";
				static  String^ const  GuiSettingsPwvAnalysis				=	"GUI_SETTINGS_PWV_ANALYSIS";
				static  String^ const  GuiSettingsPwvPatientReport			=	"GUI_SETTINGS_PWV_PATIENT_REPORT";
				static  String^ const  GuiSettingsPwvReport					=	"GUI_SETTINGS_PWV_REPORT";
				static  String^ const  GuiSettingsWindow					=	"GUI_SETTINGS_WINDOW";
				static  String^ const  GuiSetupSearchExitMsg				=	"GUI_SETUP_SEARCH_EXIT_MSG";
				static  String^ const  GuiSimulationModeMessage				=	"GUI_SIMULATION_MODE_MESSAGE";
				static  String^ const  GuiSqlInstanceConnect				=	"GUI_SQL_INSTANCE_CONNECT";
				static  String^ const  GuiStartCaptureFailed				=	"GUI_START_CAPTURE_FAILED";
				static  String^ const  GuiWarningTxt						=	"GUI_WARNING_TXT";
				static  String^ const  GuiWaveformSaveMsg					=	"GUI_WAVEFORM_SAVE_MSG";
				static  String^ const  HeartrateLblAnalysis					=	"HEARTRATE_LBL_ANALYSIS";
				static  String^ const  HeartrateUnit						=	"HEARTRATE_UNIT";
				static  String^ const  HeightRequired						=	"HEIGHT_REQUIRED";
				static  String^ const  HideCaps								=	"HIDE_CAPS";
				static  String^ const  HideSmall							=	"HIDE_SMALL";
				static  String^ const  Inch									=	"INCH";
				static  String^ const  InconclusiveNoteAORTIC_AIX			=	"INCONCLUSIVE_NOTE_AORTIC_AIX";
				static  String^ const  InconclusiveNoteAORTIC_TI			=	"INCONCLUSIVE_NOTE_AORTIC_TI";
				static  String^ const  InconclusiveNotePERIPHERAL_TI		=	"INCONCLUSIVE_NOTE_PERIPHERAL_TI";
				static  String^ const  InconclusiveNoteT1_RATIO				=	"INCONCLUSIVE_NOTE_T1_RATIO";
				static  String^ const  InconclusiveNoteOPERATOR_INDEX		=	"INCONCLUSIVE_NOTE_OPERATOR_INDEX";
				static  String^ const  InconclusiveNoteMAXDPDT				=	"INCONCLUSIVE_NOTE_MAXDPDT";
				static  String^ const  Inflatedovertime						=	"InflatedOverTime";
				static  String^ const  Information							=	"INFORMATION";
				static  String^ const  InsertMode							=	"INSERT_MODE";
				static  String^ const  Kg									=	"KG";
				static  String^ const  LabelCarotid							=	"LABEL_CAROTID";
				static  String^ const  LabelCuff							=	"LABEL_CUFF";
				static  String^ const  LabelDirect							=	"LABEL_DIRECT";
				static  String^ const  LabelDp								=	"LABEL_DP";
				static  String^ const  LabelFemoralCuff						=	"LABEL_FEMORAL_CUFF";
				static  String^ const  LabelMp								=	"LABEL_MP";
				static  String^ const  LabelPwvDistance						=	"LABEL_PWV_DISTANCE";
				static  String^ const  LabelSp								=	"LABEL_SP";
				static  String^ const  LabelSubtracting						=	"LABEL_SUBTRACTING";
				static  String^ const  LblAix								=	"LBL_AIX";
				static  String^ const  LblAp								=	"LBL_AP";
				static  String^ const  LblAvgCentralAorticPulse				=	"LBL_AVG_CENTRAL_AORTIC_PULSE";
				static  String^ const  LblBrachialSpDpMp					=	"LBL_BRACHIAL_SP_DP_MP";
				static  String^ const  LblBrachialCuff						=	"LBL_BRACHIALCUFF";
				static  String^ const  LblCentralAorticClinicalParameters	=	"LBL_CENTRAL_AORTIC_CLINICAL_PARAMETERS";
				static  String^ const  LblCentralDp							=	"LBL_CENTRAL_DP";
				static  String^ const  LblCpwa								=	"LBL_CPWA";
				static  String^ const  LblDisplay							=	"LBL_DISPLAY";
				static  String^ const  LblDob								=	"LBL_DOB";
				static  String^ const  LblDp								=	"LBL_DP";
				static  String^ const  LblDpStar							=	"LBL_DP*";
				static  String^ const  LblFemoralToCuff						=	"LBL_FEMORAL_TO_CUFF";
				static  String^ const  LblFemoralcuff						=	"LBL_FEMORALCUFF";
				static  String^ const  LblFirstName							=	"LBL_FIRST_NAME";
				static  String^ const  LblGender							=	"LBL_GENDER";
				static  String^ const  LblGroup								=	"LBL_GROUP";
				static  String^ const  LblHeight							=	"LBL_HEIGHT";
				static  String^ const  LblHr								=	"LBL_HR";
				static  String^ const  LblInches							=	"LBL_INCHES";
				static  String^ const  LblInvalidKey						=	"LBL_INVALID_KEY";
				static  String^ const  LblKey								=	"LBL_KEY";
				static  String^ const  LblLastName							=	"LBL_LAST_NAME";
				static  String^ const  LblNotes								=	"LBL_NOTES";
				static  String^ const  LblOperator							=	"LBL_OPERATOR";
				static  String^ const  LblOptionAuditTrial					=	"LBL_OPTIONAUDITTRAIL";
				static  String^ const  LblOptionCaptureGuide				=	"LBL_OPTIONCAPTUREGUIDE";
				static  String^ const  LblOptionClinical					=	"LBL_OPTIONCLINICAL";
				static  String^ const  LblOptioncPwa						=	"LBL_OPTIONCPWA";
				static  String^ const  LblOptionNibp						=	"LBL_OPTIONNIBP";
				static  String^ const  LblOptionPwv							=	"LBL_OPTIONPWV";
				static  String^ const  LblOptionResearch					=	"LBL_OPTIONRESEARCH";
				static  String^ const  LblOptiontPwa						=	"LBL_OPTIONTPWA";
				static  String^ const  LblPateints							=	"LBL_PATEINTS";
				static  String^ const  LblPatientDefaultName				=	"LBL_PATIENT_DEFAULT_NAME";
				static  String^ const  LblPatientId							=	"LBL_PATIENT_ID";
				static  String^ const  LblPatientName						=	"LBL_PATIENT_NAME";
				static  String^ const  LblPleaseEnterKey					=	"LBL_PLEASE_ENTER_KEY";
				static  String^ const  LblPP								=	"LBL_PP";
				static  String^ const  LblPwaAnalysisClosingBrace			=	"LBL_PWA_ANALYSIS_CLOSINGBRACE";
				static  String^ const  LblPwaAnalysisOpeningBrace			=	"LBL_PWA_ANALYSIS_OPENINGBRACE";
				static  String^ const  LblPwaCuffPressure					=	"LBL_PWA_CUFF_PRESSURE";
				static  String^ const  LblPwaInterpretation					=	"LBL_PWA_INTERPRETATION";
				static  String^ const  LblPwaQualityControl					=	"LBL_PWA_QUALITY_CONTROL";
				static  String^ const  LblPwaReportAIX75					=	"LBL_PWA_REPORT_ AIX75";
				static  String^ const  LblPwaSetupProgressBarStartMsg		=	"LBL_PWA_SETUP_PROGRESSBAR_START_MSG";
				static  String^ const  LblPwaSyphymocorRefAge				=	"LBL_PWA_SYPHYMOCOR_REF_AGE";
				static  String^ const  LblPwvReportTime						=	"LBL_PWV_REPORT_TIME";
				static  String^ const  LblReportAge							=	"LBL_REPORT_AGE";
				static  String^ const  LblReportAssessment					=	"LBL_REPORT_ASSESSMENT";
				static  String^ const  LblReportAssessments					=	"LBL_REPORT_ASSESSMENTS";
				static  String^ const  LblReportBloodPressure				=	"LBL_REPORT_BLOOD_PRESSURE";
				static  String^ const  LblReportBmi							=	"LBL_REPORT_BMI";
				static  String^ const  LblReportBp							=	"LBL_REPORT_BP";
				static  String^ const  LblReportCarotid						=	"LBL_REPORT_CAROTID";
				static  String^ const  LblReportCarotidWithcolon			=	"LBL_REPORT_CAROTID_WITHCOLON";
				static  String^ const  LblReportCuffWithcolon				=	"LBL_REPORT_CUFF_WITHCOLON";
				static  String^ const  LblReportDiatance					=	"LBL_REPORT_DISTANCE";
				static  String^ const  LblReportDob							=	"LBL_REPORT_DOB";
				static  String^ const  LblReportFemoral						=	"LBL_REPORT_FEMORAL";
				static  String^ const  LblReportGender						=	"LBL_REPORT_GENDER";
				static  String^ const  LblReportHeartRate					=	"LBL_REPORT_HEART_RATE";
				static  String^ const  LblReportHR							=	"LBL_REPORT_HR";
				static  String^ const  LblReportLogo						=	"LBL_REPORT_LOGO";
				static  String^ const  LblReportNormalRange					=	"LBL_REPORT_NORMAL_RANGE";
				static  String^ const  LblReportPatientData					=	"LBL_REPORT_PATIENTDATA";
				static  String^ const  LblReportPwaBrachialMp				=	"LBL_REPORT_PWA_BRACHIAL_MP";
				static  String^ const  LblReportPwaNotCalculated			=	"LBL_REPORT_PWA_NOT_CALCULATED";
				static  String^ const  LblReportPwv							=	"LBL_REPORT_PWV";
				static  String^ const  LblReportPwvLbl						=	"LBL_REPORT_PWV_LBL";
				static  String^ const  LblReportPwvmethod					=	"LBL_REPORT_PWVMETHOD";
				static  String^ const  LblReportRecordedCarotid				=	"LBL_REPORT_RECORED_CAROTID";
				static  String^ const  LblReportRecordedFemoral				=	"LBL_REPORT_RECORED_FEMORAL";
				static  String^ const  LblReportReferenceRange				=	"LBL_REPORT_REFERENCE_RANGE";
				static  String^ const  LblReportStdLbl						=	"LBL_REPORT_SD_LBL";
				static  String^ const  LblReportStdDeviation				=	"LBL_REPORT_STD_DEVIATION";
				static  String^ const  LblReportStudyData					=	"LBL_REPORT_STUDYDATA";
				static  String^ const  LblReportTitle						=	"LBL_REPORT_TITLE";
				static  String^ const  LblSetupBrachialBp				    =   "LBL_SETUP_BRACHIALBP";
				static  String^ const  LblSpStar							=	"LBL_SP*";
				static  String^ const  LblSphygmoCorReferenceAgeNotCalculated=	"LBL_SPHYGMOCOR_REFERENCE_AGE_NOT_CALCULTED";
				static  String^ const  LblTimestatus						=	"LBL_TIMESTATUS";
				static  String^ const  LblTonometer							=	"LBL_TONOMETER";
				static  String^ const  LblWeight							=	"LBL_WEIGHT";
				static  String^ const  Lbs									=	"LBS";
				static  String^ const  MaleTxt								=	"MALE";
				static  String^ const  MathError							=	"MATH_ERROR";
				static  String^ const  MeasureInvalidCaptureTime			=	"MEASURE_INVALID_CAPTURE_TIME";
				static  String^ const  MeasureInvalidSampleRate				=	"MEASURE_INVALID_SAMPLE_RATE";
				static  String^ const  MenuDatabase							=	"MENU_DATABASE";
				static  String^ const  MenuHelp								=	"MENU_HELP";
				static  String^ const  MenuSystem							=	"MENU_SYSTEM";
				static  String^ const  Message								=	"MESSAGE";
				static  String^ const  MigrateFileMsg1						=	"MIGRATE_FILE_MSG1";
				static  String^ const  MigrateFileMsg2						=	"MIGRATE_FILE_MSG2";
				static  String^ const  MigrateHeaderTxt						=	"MIGRATE_HEADER_TXT";
				static  String^ const  MigrateTitleTxt						=	"MIGRATE_TITLE_TXT";
				static  String^ const  MigrateValidationMsg					=	"MIGRATE_VALIDATION_MSG";
				static  String^ const  MigrationFail						=	"MIGRATION_FAIL";
				static  String^ const  MigrationSuccessMessage				=	"MIGRATION_SUCCESS_MESSAGE";
				static  String^ const  Mm									=	"MM";
				static  String^ const  Mode									=	"MODE";
				static  String^ const  ModeMismatchMsg						=	"MODE_MISMATCH_MSG";
				static  String^ const  ModuleCapability						=	"MODULE_CAPABILITY";
				static  String^ const  ModuleConfigId						=	"MODULE_CONFIG_ID";
				static  String^ const  ModuleSn								=	"MODULE_SN";
				static  String^ const  ModuleType							=	"MODULE_TYPE";
				static  String^ const  ModuleVersion						=	"MODULE_VERSION";
				static  String^ const  Month								=	"MONTH";
				static  String^ const  Mp									=	"MP";
				static  String^ const  MpDpTooClose							=	"MP_DP_TOO_CLOSE";
				static  String^ const  MpOutOfRange							=	"MP_OUT_OF_RANGE";
				static  String^ const  MsgDesert							=	"MSG_DESERT";
				static  String^ const  MsgInProgress						=	"MSG_IN_PROGRESS";
				static  String^ const  MsgPleaseRelaunch					=	"MSG_PLEASE_RELAUNCH";
				static  String^ const  MsgSaveChange						=	"MSG_SAVE_CHANGE";
				static  String^ const  MsgSaveSettings						=	"MSG_SAVE_SETTINGS";
				static  String^ const  MsgSelectLogo						=	"MSG_SELECT_LOGO";
				static  String^ const  MsgSpecialCharacter					=	"MSG_SPECIALCHARACTER";
				static  String^ const  MsgThresholdBlankValue  			    =   "MSG_THRESHOLDBLANKVALUE";
				static  String^ const  MsgThresholdNumericValue  			=   "MSG_THRESHOLDNUMERICVALUE";
				static  String^ const  MsgValidatingSystemKey				=	"MSG_VALIDATING_SYSTEM_KEY";
				static  String^ const  NoRecordsToDelete					=	"NO_RECORDS_TO_DELETE";
				static  String^ const  NoRecordsToEdit						=	"NO_RECORDS_TO_EDIT";
				static  String^ const  Noerroralarm							=	"NoErrorAlarm";
				static  String^ const  NullMeasurementRecord				=	"NULL_MEASUREMENT_RECORD";
				static  String^ const  Overpressure							=	"OverPressure";
				static  String^ const  PatientAdded							=	"PATIENT_ADDED";
				static  String^ const  PatientAlreadyExist					=	"PATIENT_ALREADY_EXIST";
				static  String^ const  PatientAlreadyExistforGroup			=	"PATIENT_ALREADY_EXIST_FOR_GROUP";
				static  String^ const  PatientAlreadyExists					=	"PATIENT_ALREADY_EXISTS";
				static  String^ const  PatientNotSaved						=	"PATIENT_NOT_SAVED";
				static  String^ const  PatientNoInvalid						=	"PATIENT_NUM_INVALID";
				static  String^ const  PdfFileError							=	"PDF_FILE_ERROR";
				static  String^ const  PowerUpStatus						=	"PowerUpStatus";
				static  String^ const  PrtPwaTextRptDesc					=	"PRT_PWA_TEXT_RPT_DESCRIPTION";

				static  String^ const  PrtPwvBoxText1						=	"PRT_PWV_BOX_TEXT_1";
				static  String^ const  PrtPwvBoxText2						=	"PRT_PWV_BOX_TEXT_2";
				static  String^ const  PrtPwvText1							=	"PRT_PWV_TEXT_1";
				static  String^ const  PrtPwvText2							=	"PRT_PWV_TEXT_2";
				static  String^ const  PrtPwvText3							=	"PRT_PWV_TEXT_3";
				static  String^ const  PrtPwvText4							=	"PRT_PWV_TEXT_4";
				static  String^ const  PrtPwvText5							=	"PRT_PWV_TEXT_5";
				static  String^ const  PrtPwvText6							=	"PRT_PWV_TEXT_6";
				static  String^ const  PrtPwvText7							=	"PRT_PWV_TEXT_7";
				static  String^ const  PrtPwvText8							=	"PRT_PWV_TEXT_8";
				static  String^ const  PrtPwvText9							=	"PRT_PWV_TEXT_9";
				static  String^ const  PrtPwvText10							=	"PRT_PWV_TEXT_10";
				static  String^ const  PrtPwvText11							=	"PRT_PWV_TEXT_11";
				static  String^ const  PrtPwvText12							=	"PRT_PWV_TEXT_12";
				static  String^ const  PrtPwvText13							=	"PRT_PWV_TEXT_13";
				static  String^ const  PrtPwvText14							=	"PRT_PWV_TEXT_14";
				static  String^ const  PrtPwvText15							=	"PRT_PWV_TEXT_15";
				static  String^ const  PrtPwvText16							=	"PRT_PWV_TEXT_16";
				static  String^ const  PrtPwvText17							=	"PRT_PWV_TEXT_17";
				static  String^ const  PrtPwvText18							=	"PRT_PWV_TEXT_18";
				static  String^ const  PrtPwvText19							=	"PRT_PWV_TEXT_19";
				static  String^ const  PrtPwvText20							=	"PRT_PWV_TEXT_20";
				static  String^ const  PrtPwvText21							=	"PRT_PWV_TEXT_21";
				static  String^ const  PrtPwvText22							=	"PRT_PWV_TEXT_22";
				static  String^ const  PrtPwvTextGreen						=	"PRT_PWV_TEXT_GREEN";
				static  String^ const  PrtPwvTextNameLbl					=	"PRT_PWV_TEXT_NAME_LBL";
				static  String^ const  PrtPwvTextPage						=	"PRT_PWV_TEXT_PAGE";
				static  String^ const  PrtPwvTextPatientDetails				=	"PRT_PWV_TEXT_PATIENT_DETAILS";
				static  String^ const  PrtPwvTextPatientReport				=	"PRT_PWV_TEXT_PATIENT_REPORT";
				static  String^ const  PrtPwvTextRed						=	"PRT_PWV_TEXT_RED";
				static  String^ const  PrtPwvTextRptDesc					=	"PRT_PWV_TEXT_RPT_DESCRIPTION";
				static  String^ const  PrtPwvTextRptHeader					=	"PRT_PWV_TEXT_RPT_HEADER";
				static  String^ const  PrtPwvTextScor						=	"PRT_PWV_TEXT_SCOR";
				static  String^ const  Pwa									=	"PWA";
				static  String^ const  PwaAnalysisReport					=	"PWA ANALYSIS REPORT";
				static  String^ const  PwaClinicalReport					=	"PWA CLINICAL REPORT";
				static  String^ const  PwaEvaluationReport					=	"PWA EVALUATION REPORT";
				static  String^ const  PwaPatientReport						=	"PWA PATIENT REPORT";
				static  String^ const  PWA_ERROR_LoadBizExt					=	"PWA_ERROR_LOAD_BIZEXT";
				static  String^ const  PWA_ERROR_UnloadBizExt				=	"PWA_ERROR_UNLOAD_BIZEXT";
				static  String^ const  PWA_ERROR_NotLoadedBizExt			=	"PWA_ERROR_NOTLOADED_BIZEXT";
				static  String^ const  PWA_ERROR_InitialiseBizExt			=	"PWA_ERROR_INITIALISE_BIZEXT";
				static  String^ const  PWA_ERROR_Populate					=	"PWA_ERROR_POPULATE";
				static  String^ const  PWA_ERROR_Store						=	"PWA_ERROR_STORE";
				static  String^ const  PWA_ERROR_Database					=	"PWA_ERROR_DATABASE";
				static  String^ const  PWA_ERROR_InvalidMeasureType			=	"PWA_ERROR_INVALID_MEASURETYPE";
				static  String^ const  PWA_ERROR_InvalidUpSampleRate		=	"PWA_ERROR_INVALID_UPSAMPLERATE";
				static  String^ const  PWA_ERROR_Append						=	"PWA_ERROR_APPEND";
				static  String^ const  PWA_ERROR_BufferNotFull				=	"PWA_ERROR_BUFFER_NOT_FULL";
				static  String^ const  PWA_ERROR_Calculate					=	"PWA_ERROR_CALCULATE";
				static  String^ const  PWA_ERROR_NoPeriphED					=	"PWA_ERROR_NO_PERIPH_ED";
				static  String^ const  PWA_MSG_MPS_OUT						=	"PWA_MSG_MPS_OUT";
				static  String^ const  PWA_MSG_MPD_OUT						=	"PWA_MSG_MPD_OUT";
				static  String^ const  PWA_MSG_ESP_OUT						=	"PWA_MSG_ESP_OUT";
				static  String^ const  PWA_MSG_P1H_OUT						=	"PWA_MSG_P1H_OUT";
				static  String^ const  PWA_MSG_AI_OUT						=	"PWA_MSG_AI_OUT";
				static  String^ const  PWA_MSG_DPDT_OUT						=	"PWA_MSG_DPDT_OUT";
				static  String^ const  PWA_MSG_OUT_OF_PULSE					=	"PWA_MSG_OUT_OF_PULSE";
				static  String^ const  PWA_ERROR_WRONG_PULSE				=	"PWA_ERROR_WRONG_PULSE";
				static  String^ const  PWA_ERROR_WRONG_PULSE_SAMPLERATE		=	"PWA_ERROR_WRONG_PULSE_SAMPLERATE";
				static  String^ const  PWA_ERROR_TIME_OUT_OF_RANGE			=	"PWA_ERROR_TIME_OUT_OF_RANGE";
				static  String^ const  PWA_MSG_SIGNAL_TOO_SHORT				=	"PWA_MSG_SIGNAL_TOO_SHORT";
				static  String^ const  PWA_MSG_TRIGGER_TOO_SHORT			=	"PWA_MSG_TRIGGER_TOO_SHORT";
				static  String^ const  PWA_MSG_SP_OUT						=	"PWA_MSG_SP_OUT";
				static  String^ const  PWA_MSG_DP_OUT						=	"PWA_MSG_DP_OUT";
				static  String^ const  PWA_MSG_MP_OUT						=	"PWA_MSG_MP_OUT";
				static  String^ const  PWA_MSG_NEG_AVPULSE					=	"PWA_MSG_NEG_AVPULSE";
				static  String^ const  PWA_MSG_NEG_SIGNAL					=	"PWA_MSG_NEG_SIGNAL";
				static  String^ const  PWA_MSG_SIGNAL_TOO_LONG				=	"PWA_MSG_SIGNAL_TOO_LONG";
				static  String^ const  PWA_MSG_TRIGGER_ERR					=	"PWA_MSG_TRIGGER_ERR";
				static  String^ const  PWA_MSG_TOO_BAD_SIGNAL				=	"PWA_MSG_TOO_BAD_SIGNAL";
				static  String^ const  PWA_MSG_WRONG_RANGE					=	"PWA_MSG_WRONG_RANGE";
				static  String^ const  PWA_MSG_POINT_OUT_OF_PULSE			=	"PWA_MSG_POINT_OUT_OF_PULSE";
				static  String^ const  PWA_MSG_PERIPH_CENTRAL_LENGTH		=	"PWA_MSG_PERIPH_CENTRAL_LENGTH";
				static  String^ const  PWA_MSG_PERIPH_CENTRAL_ED			=	"PWA_MSG_PERIPH_CENTRAL_ED";
				static  String^ const  PWA_MSG_CALCPULSES_ERR				=	"PWA_MSG_CALCPULSES_ERR";
				static  String^ const  PWA_MSG_AVPULSE_ERR					=	"PWA_MSG_AVPULSE_ERR";
				static  String^ const  PWA_MSG_CALCSYSTONSET_ERR			=	"PWA_MSG_CALCSYSTONSET_ERR";
				static  String^ const  PWA_MSG_NOT_FOUND_PEAK				=	"PWA_MSG_NOT_FOUND_PEAK";
				static  String^ const  PWA_MSG_WRONG_PERIPH_ED				=	"PWA_MSG_WRONG_PERIPH_ED";
				static  String^ const  PWA_MSG_HR_OUT						=	"PWA_MSG_HR_OUT";
				static  String^ const  Pwv									=	"PWV";
				static  String^ const  PwvPatientReport						=	"PWV PATIENT REPORT";
				static  String^ const  PwvSummaryReport						=	"PWV SUMMARY REPORT";


				static  String^ const  PwvBlText							=	"PWV_BL_TEXT";
				static  String^ const  PwvCalcDistOutOfRange				=	"PWV_CALC_DIST_OUT_OF_RANGE";
				static  String^ const  PwvCounterFailed						=	"PWV_COUNTER_FAILED";
				static  String^ const  PwvDeltasNotEnough					=	"PWV_DELTAS_NOT_ENOUGH";
				static  String^ const  PwvDeviationHigh						=	"PWV_DEVIATION_HIGH";
				static  String^ const  PwvDeviationTooBig					=	"PWV_DEVIATION_TOO_BIG";
				static  String^ const  PwvDirectDistOutOfRange				=	"PWV_DIRECT_DIST_OUT_OF_RANGE";
				static  String^ const  PwvInvalid							=	"PWV_INVALID";
				static  String^ const  PwvInvalidAdult						=	"PWV_INVALID_ADULT";
				static  String^ const  PwvInvalidDistance					=	"PWV_INVALID_DISTANCE";
				static  String^ const  PwvInvalidHeartRate					=	"PWV_INVALID_HEART_RATE";
				static  String^ const  PwvLblAnalysis						=	"PWV_LBL_ANALYSIS";
				static  String^ const  PwvNotEnoughDeltas					=	"PWV_NOT_ENOUGH_DELTAS";
				static  String^ const  PwvSetDefaultsFailed					=	"PWV_SET_DEFAULTS_FAILED";
				static  String^ const  PwvSettings							=	"PWV_SETTINGS";
				static  String^ const  PwvSignalTooBad						=	"PWV_SIGNAL_TOO_BAD";
				//static  String^ const  PwvStartCaptureFailed				=	"PWV_START_CAPTURE_FAILED";
				static  String^ const  PwvStartCaptureFailed				=	"BLL_START_CAPTURE_FAILED";
				static  String^ const  PwvStdDevToLarge						=	"PWV_STD_DEV_TO_LARGE";
				static  String^ const  PwvTooSmallForAdult					=	"PWV_TOO_SMALL_FOR_ADULT";
				static  String^ const  PwvUnit								=	"PWV_UNIT";
				static  String^ const  PwvValidDeltasNotEnough				=	"PWV_VALID_DELTAS_NOT_ENOUGH";
				static  String^ const  QuickStart							=	"QUICK START";
				static  String^ const  QuickStartWarning					=	"QUICKSTART_WARNING";
				static  String^ const  Rad10Sec								=	"RAD_10_SEC";
				static  String^ const  Rad20Sec								=	"RAD_20_SEC";
				static  String^ const  Rad5Sec								=	"RAD_5_SEC";
				static  String^ const  RadCm								=	"RAD_CM";
				static  String^ const  RadDirect							=	"RAD_DIRECT";
				static  String^ const  RadImperial							=	"RAD_IMPERIAL";
				static  String^ const  RadMetric							=	"RAD_METRIC";
				static  String^ const  RadMm								=	"RAD_MM";
				static  String^ const  RadMpDp								=	"RAD_MP_DP";
				static  String^ const  RadSpDp								=	"RAD_SP_DP";
				static  String^ const  RadSpMp								=	"RAD_SP_MP";
				static  String^ const  RadSubtracting						=	"RAD_SUBTRACTING";
				static  String^ const  Recoverablestatus					=	"RecoverableStatus";
				static  String^ const  ReportAssesmentRecordCount			=	"REPORT_ASSESMENT_RECORD_COUNT";
				static  String^ const  ReportAssesmentsFormat				=	"REPORT_ASSESMENTS_FORMAT";
				static  String^ const  ReportCalFailMsg						=	"REPORT_CAL_FAIL_MSG";
				static  String^ const  ReportCalculateError					=	"REPORT_CALCULATE_ERROR";
				static  String^ const  ReportDateTimeFormat					=	"REPORT_DATE_TIME_FORMAT";
				static  String^ const  ReportLblCarotid						=	"REPORT_LBL_CAROTID";
				static  String^ const  ReportLblDirect						=	"REPORT_LBL_DIRECT";
				static  String^ const  ReportLblSubtracting					=	"REPORT_LBL_SUBTRACTING";
				static  String^ const  ReportNormalrangeXAxisTitle			=	"REPORT_NORMALRANGE_X_AXIS_TITLE";
				static  String^ const  ReportNormalrangeYAxisTitle			=	"REPORT_NORMALRANGE_Y_AXIS_TITLE";
				static  String^ const  ReportSaveErr						=	"REPORT_SAVE_ERR";
				static  String^ const  ResearchEnv							=	"RESEARCH_ENV";
				static  String^ const  RestoreDone							=	"RESTORE_DONE";
				static  String^ const  RestoreFail							=	"RESTORE_FAIL";
				static  String^ const  RestoreFileMsg						=	"RESTORE_FILE_MSG";
				static  String^ const  RestoreMsg							=	"RESTORE_MSG";
				static  String^ const  RestoreProgress						=	"RESTORE_PROGRESS";
				static  String^ const  RestoreTitle							=	"RESTORE_TITLE";
				static  String^ const  RibbionbarText						=	"RIBBIONBAR_TEXT";
				static  String^ const  RptAgeTitle							=	"RPT_AGE_TITLE";
				static  String^ const  RptAorticAIxHR75Title				=	"RPT_AORTIC_AIXHR75_TITLE";
				static  String^ const  RptAorticAugmentationAP_PPTitle		=	"RPT_AORTIC_AUGMENTATION_AP_PP_TITLE";
				static  String^ const  RptAorticAixTitle					=	"RPT_AORTICAIX_TITLE";
				static  String^ const  RptAroticT1T2Title					=	"RPT_AROTIC_T1T2_TITLE";
				static  String^ const  RptAroticTitle						=	"RPT_AROTIC_TITLE";
				static  String^ const  RptBrachialBp						=	"RPT_BRACHIAL_BP";
				static  String^ const  RptBrachialTitle						=	"RPT_BRACHIAL_TITLE";
				static  String^ const  RptCentralPressureWaveformTitle		=	"RPT_CENTRAL_PRESSURE_WAVEFORM_TITLE";
				static  String^ const  RptCentralHaemodynamicParametersTitle=	"RPT_CENTRALHAEMODYNAMIC_PARAMETERS_TITLE";
				static  String^ const  RptClinicalParametersTitle			=	"RPT_CLINICAL_PARAMETERS_TITLE";
				static  String^ const  RptDatabaseVersionTitle				=	"RPT_DATABASE_VERSION_TITLE";
				static  String^ const  RptDateAndMeasurement				=	"RPT_DATE_AND_MEASUREMENT";
				static  String^ const  RptDateAndTime						=	"RPT_DATE_AND_TIME";
				static  String^ const  RptDiastolicBpValue					=	"RPT_DIASTOLIC_BP_VALUE";
				static	String^ const  RptEndSystolicPressureTitle			=	"RPT_ENDSYSTOLIC_PRESSURE_TITLE";
				static	String^ const  RptHeartRatePeriodTitle				=	"RPT_HEARTRATE_PERIOD_TITLE";
				static	String^ const  RptInterpretationTitle				=	"RPT_INTERPRETATION_TITLE";
				static  String^ const  RptMapTitle							=	"RPT_MAP_TITLE";
				static  String^ const  RptMeasurementData					=	"RPT_MEASUREMENT_DATA";
				static  String^ const  RptMPSystoleDiastoleTitle			=	"RPT_MP_SYSTOLE_DIASTOLE_TITLE";
				static  String^ const  RptNoteTitle							=	"RPT_NOTE_TITLE";
				static  String^ const  RptNumberOfWaveformsTitle			=	"RPT_NUMBEROFWAVEFORMS_TITLE";
				static  String^ const  RptP1HeightTitle						=	"RPT_P1HEIGHT_TITLE";
				static  String^ const  RptPatientDataTitle					=	"RPT_PATIENTDATA_TITLE";
				static  String^ const  RptPhysicianTitle					=	"RPT_PHYSICIAN_TITLE";
				static  String^ const  RptPwaAboveAverageText				= 	"RPT_PWA_ABOVE_AVERAGE_TEXT";
				static  String^ const  RptPwaAixChartText					= 	"RPT_PWA_AIX_CHART_TEXT";
				static  String^ const  RptPwaApChartText					= 	"RPT_PWA_AP_CHART_TEXT";
				static  String^ const  RptPwaAverageText					= 	"RPT_PWA_AVERAGE_TEXT";
				static  String^ const  RptPwaBelowAverageText				= 	"RPT_PWA_BELOW_AVERAGE_TEXT";
				static  String^ const  RptPwaDot							= 	"RPT_PWA_DOT";
				static  String^ const  RptPwaExcellentText					= 	"RPT_PWA_EXCELLENT_TEXT";
				static  String^ const  RptPwaGoodText						= 	"RPT_PWA_GOOD_TEXT";
				static  String^ const  RptPwaHighNormalText					= 	"RPT_PWA_HIGH_NORMAL_TEXT";
				static  String^ const  RptPwaMildHypertensionText			= 	"RPT_PWA_MILD_HYPERTENSION_TEXT";
				static  String^ const  RptPwaModerateHypertensionText		= 	"RPT_PWA_MODERATE_HYPERTENSION_TEXT";
				static  String^ const  RptPwaNormalText						= 	"RPT_PWA_NORMAL_TEXT";
				static  String^ const  RptPwaPoorText						=	"RPT_PWA_POOR_TEXT";
				static  String^ const  RptPwaPpChartText					=	"RPT_PWA_PP_CHART_TEXT";
				static  String^ const  RptPwaReferenceNorange				=	"RPT_PWA_REFERENCE_NORANGE";
				static  String^ const  RptPwaReferenceRange					=	"RPT_PWA_REFERENCE_RANGE";
				static  String^ const  RptPwaSevereText						= 	"RPT_PWA_SEVERE_TEXT";
				static  String^ const  RptPwaSpChartText					= 	"RPT_PWA_SP_CHART_TEXT";
				static  String^ const  RptPwaTxtPatientRptFooter			=	"RPT_PWA_TXT_PATIENT_RPT_FOOTER";
				static  String^ const  RptPwaTxt1							=	"RPT_PWATEXT1";
				static  String^ const  RptPwaTxt2							=	"RPT_PWATEXT2";
				static  String^ const  RptPwaTxt3							=	"RPT_PWATEXT3";
				static  String^ const  RptPwaTxt4							=	"RPT_PWATEXT4";
				static  String^ const  RptPwaTxt5							=	"RPT_PWATEXT5";
				static  String^ const  RptPwaTxt6							=	"RPT_PWATEXT6";
				static  String^ const  RptPwaTxt7							=	"RPT_PWATEXT7";
				static  String^ const  RptPwaTxt8							=	"RPT_PWATEXT8";
				static  String^ const  RptPwaTxt9							=	"RPT_PWATEXT9";
				static  String^ const  RptPwaTxt10							=	"RPT_PWATEXT10";
				static  String^ const  RptPwaTxt11							=	"RPT_PWATEXT11";
				static  String^ const  RptPwaTxt12							=	"RPT_PWATEXT12";
				static  String^ const  RptPwaTxt13							=	"RPT_PWATEXT13";
				static  String^ const  RptPwaTxt14							=	"RPT_PWATEXT14";
				static  String^ const  RptPwaTxt15							=	"RPT_PWATEXT15";
				static  String^ const  RptPwaTxt16							=	"RPT_PWATEXT16";
				static  String^ const  RptPwaTxt17							=	"RPT_PWATEXT17";
				static  String^ const  RptPwaTxt18							=	"RPT_PWATEXT18";
				static  String^ const  RptPwaTxt19							=	"RPT_PWATEXT19";
				static  String^ const  RptPwaTxt20							=	"RPT_PWATEXT20";
				static  String^ const  RptPwaTxt21							=	"RPT_PWATEXT21";
				static  String^ const  RptPwaTxt22							=	"RPT_PWATEXT22";
				static  String^ const  RptPwaTxt23							=	"RPT_PWATEXT23";
				static  String^ const  RptPwaTxt24							=	"RPT_PWATEXT24";
				static  String^ const  RptPwaTxt25							=	"RPT_PWATEXT25";
				static  String^ const  RptPwaTxt26							=	"RPT_PWATEXT26";
				static  String^ const  RptPwaTxt27							=	"RPT_PWATEXT27";
				static  String^ const  RptPwaTxt28							=	"RPT_PWATEXT28";
				static  String^ const  RptPwaTxt29							=	"RPT_PWATEXT29";
				static  String^ const  RptPwaTxt30							=	"RPT_PWATEXT30";
				static  String^ const  RptPwaTxt31							=	"RPT_PWATEXT31";
				static  String^ const  RptPwaTxt32							=	"RPT_PWATEXT32";
				static  String^ const  RptPwaTxt33							=	"RPT_PWATEXT33";
				static  String^ const  RptPwaTxt34							=	"RPT_PWATEXT34";
				static  String^ const  RptPwaTxt35							=	"RPT_PWATEXT35";
				static  String^ const  RptPwaTxt36							=	"RPT_PWATEXT36";
				static  String^ const  RptPwaTxt37							=	"RPT_PWATEXT37";
				static  String^ const  RptPwaTxt38							=	"RPT_PWATEXT38";
				static  String^ const  RptPwaTxt39							=	"RPT_PWATEXT39";
				static  String^ const  RptPwaTxt40							=	"RPT_PWATEXT40";
				static  String^ const  RptPwaTxt41							=	"RPT_PWATEXT41";
				static  String^ const  RptPwaTxt42							=	"RPT_PWATEXT42";
				static  String^ const  RptPwaTxt43							=	"RPT_PWATEXT43";
				static  String^ const  RptPwaTxt44							=	"RPT_PWATEXT44";

				static  String^ const  RptPwaTxtPage						=	"RPT_PWATXT_PAGE";
				static  String^ const  RptPwaTxtPatientRptHeader			=	"RPT_PWATXT_PATIENT_RPT_HEADER";
				static  String^ const  RptQualityControlTitle				=	"RPT_QUALITY_CONTROL_TITLE";
				static  String^ const  RptSignatureTitle					=	"RPT_SIGNATURE_TITLE";
				static  String^ const  RptSimulationModeTitle				=	"RPT_SIMULATIONMODE_TITLE";
				static  String^ const  RptSystolicBpValue					=	"RPT_SYSTOLIC_BP_VALUE";
				static  String^ const  RptWaveformPlotTitle					=	"RPT_WAVEFORM_PLOT_TITLE";
				static  String^ const  SampleRateOutOfRange					=	"SAMPLE_RATE_OUT_OF_RANGE";
				static  String^ const  SearchMode							=	"SEARCH_MODE";
				static  String^ const  SecurityMode							=	"SECURITY_MODE";
				static  String^ const  SelectCaps							=	"SELECT_CAPS";
				static  String^ const  SelectDob							=	"SELECT_DOB";
				static  String^ const  SelectGender							=	"SELECT_GENDER";
				static  String^ const  SelectSmall							=	"SELECT_SMALL";
				static  String^ const  Setup								=	"SETUP";
				static  String^ const  SetupScreen							=	"SETUP_SCREEN";
				static  String^ const  ShowCaps								=	"SHOW_CAPS";
				static  String^ const  ShowSmall							=	"SHOW_SMALL";
				static  String^ const  SignalFindOnsetsFailed				=	"SIGNAL_FIND_ONSETS_FAILED";
				static  String^ const  SignalHeightMinMaxOutOfRange			=	"SIGNAL_HEIGHT_MIN_MAX_OUT_OF_RANGE";
				static  String^ const  SignalHeightMinTooLarge				=	"SIGNAL_HEIGHT_MIN_TOO_LARGE";
				static  String^ const  SignalHeightMinTooSmall				=	"SIGNAL_HEIGHT_MIN_TOO_SMALL";
				static  String^ const  SignalHeightTooShort					=	"SIGNAL_HEIGHT_TOO_SHORT";
				static  String^ const  SignalInvalidSampleRate				=	"SIGNAL_INVALID_SAMPLE_RATE";
				static  String^ const  SignalLenMinMaxOutOfRange			=	"SIGNAL_LEN_MIN_MAX_OUT_OF_RANGE";
				static  String^ const  SignalLenTooShort					=	"SIGNAL_LEN_TOO_SHORT";
				static  String^ const  SignalNotEnoughOnsets				=	"SIGNAL_NOT_ENOUGH_ONSETS";
				static  String^ const  SignalOnsetsError					=	"SIGNAL_ONSETS_ERROR";
				static  String^ const  SignalTooLong						=	"SIGNAL_TOO_LONG";
				static  String^ const  SignalTooManyOnsets					=	"SIGNAL_TOO_MANY_ONSETS";
				static  String^ const  SignalTooShort						=	"SIGNAL_TOO_SHORT";
				static  String^ const  SignalTooSmall						=	"SIGNAL_TOO_SMALL";
				static  String^ const  Simulation							=	"SIMULATION";
				static  String^ const  Sp									=	"SP";
				static  String^ const  SpDpTooClose							=	"SP_DP_TOO_CLOSE";
				static  String^ const  SpMpTooClose							=	"SP_MP_TOO_CLOSE";
				static  String^ const  SpOutOfRange							=	"SP_OUT_OF_RANGE";
				static  String^ const  SpRequired							=	"SP_REQUIRED";
				static  String^ const  SpalshCopyrtTxt						=	"SPALSH_COPYRT_TXT";
				static  String^ const  SplashIniMsg							=	"SPLASH_INI_MSG";
				static  String^ const  SplashLblScorTxt						=	"SPLASH_LBL_SCOR_TXT";
				static  String^ const  SplashLblVersionTxt					=	"SPLASH_LBL_VERSION_TXT";
				static  String^ const  SplashSqlConn						=	"SPLASH_SQL_CONN";
				static  String^ const  SplashWaitMsg						=	"SPLASH_WAIT_MSG";
				static  String^ const  SqlExpress							=	"SQL_EXPRESS";
				static  String^ const  SqlLocalErrorStrg					=	"SQL_LOCAL_ERROR_STRG";
				static  String^ const  SqlNetworkErrorStrg					=	"SQL_NETWORK_ERROR_STRG";
				static  String^ const  SqlRetryConnStrg						=	"SQL_RETRY_CONN_STRG";
				static  String^ const  SqlServerChangedToDefault			=	"SQL_SERVER_CHANGED_TO_DEFAULT";
				static  String^ const  SqlServerChangedToLocal				=	"SQL_SERVER_CHANGED_TO_LOCAL";
				static  String^ const  SqlServerConnFailed					=	"SQL_SERVER_CONN_FAILED";
				static  String^ const  SqlServerConnected					=	"SQL_SERVER_CONNECTED";
				static  String^ const  SqlServerFailed						=	"SQL_SERVER_FAILED";
				static  String^ const  SqlServerUnableToConnect				=	"SQL_SERVER_UNABLE_TO_CONNECT";
				static  String^ const  Standard								=	"STANDARD";
				static  String^ const  Startstr								=	"STARTSTR";
				static  String^ const  SubtractingMethod					=	"SUBTRACTING_METHOD";
				static  String^ const  SysDefaultLowcase					=	"SYS_DEFAULT_LOWCASE";
				static  String^ const  SysDefaultUppercase					=	"SYS_DEFAULT_UPPERCASE";
				static  String^ const  SysImageFileWildcard					=	"SYS_IMAGE_FILE_WILDCARD";
				static  String^ const  SysSimFilePath						=	"SYS_SIM_FILE_PATH";
				static  String^ const  SysSimFilePathDebug					=	"SYS_SIM_FILE_PATH_DEBUG";
				static  String^ const  SysSimFilePathPwa					=	"SYS_SIM_FILE_PATH_PWA";
				static  String^ const  SysSimFileWildcard					=	"SYS_SIM_FILE_WILDCARD";
				static  String^ const  SystemError							=	"SYSTEM_ERROR";
				static  String^ const  SystemId								=	"SYSTEM_ID";
				static  String^ const  SystemIdInvalid						=	"SYSTEM_ID_INVALID";
				static  String^ const  TabAnalysis							=	"TAB_ANALYSIS";
				static  String^ const  TabCapture							=	"TAB_CAPTURE";
				static  String^ const  TabPatient							=	"TAB_PATIENT";
				static  String^ const  TabQuickStart						=	"TAB_QUICK_START";
				static  String^ const  TabReport							=	"TAB_REPORT";
				static  String^ const  TabResult							=	"TAB_RESULT";
				//static  String^ const  TabSetup								=	"TAB_SETUP";
				static  String^ const  TonometerDataAppendFailed			=	"TONOMETER_DATA_APPEND_FAILED";
				static  String^ const  TransferPatient						=	"TRANSFER_PATIENT";
				static  String^ const  UnitsDistanceCm						=	"UNITS_DISTANCE_CM";
				static  String^ const  UnitsDistanceFoot					=	"UNITS_DISTANCE_FOOT";
				static  String^ const  UnitsDistanceInch					=	"UNITS_DISTANCE_INCH";
				static  String^ const  UnitsDistanceMm						=	"UNITS_DISTANCE_MM";
				static  String^ const  UnitsPressureMmhg					=	"UNITS_PRESSURE_MMHG";
				static  String^ const  UnitsTimeMs							=	"UNITS_TIME_MS";
				static  String^ const  UnitsWeightKg						=	"UNITS_WEIGHT_KG";
				static  String^ const  UnitsWeightLbs						=	"UNITS_WEIGHT_LBS";
				static  String^ const  Unrecoverablestatus					=	"UnrecoverableStatus";
				static  String^ const  ValidationError						=	"VALIDATION_ERROR";
				static  String^ const  WeightOutOfRange						=	"WEIGHT_OUT_OF_RANGE";
				static  String^ const  Year									=	"YEAR";
				static  String^ const  ZeroAge								=	"ZERO_AGE";			
			}; // End CrxStructCommonResourceMsg


			/**
			 * @struct CrxMsgStructInternal
			 * @brief Container for internal string. 	
			 */
			private ref struct CrxMsgStructInternal
			{
				// holds the location of the configuration file
				static String^ NameOfAppResxfile				=	"Scor.ApplicationMessages";
				static String^ NameOfAppResxfilePath			=	".\\system\\resources\\Scor.ApplicationMessages.resources";
			};
			

			/**
			* @class CrxMessagingManager
			* @brief Class to manage message handling related functions. @n
			* This Class is mainly responsible for maintaining Scor.ApplicationMessages.resources file located in \“system\\Resources\” folder. @n
			* It has methods that enable read the value related to provided string.
			*/
			public ref class CrxMessagingManager
			{
				private:					

					//singleton instance
					static CrxMessagingManager^ _instance = gcnew CrxMessagingManager(); /**< Instance to implement singleton. */
					
					// holds the location of the configuration file
					//static String^ _nameOfAppResxfile = L".\\system\\resources\\Scor.ApplicationMessages.resources";
					
					//Create Resource manager object
					ResourceManager^ errRsrcMsg;

					/**
					* Default constructor.
					*/
					CrxMessagingManager();
						
					/**
					* Copy Constructor
					*/
					CrxMessagingManager(CrxMessagingManager^)
					{
					}
		          
					/**
					* Assignment Operator
					*/
					CrxMessagingManager^ operator=(CrxMessagingManager^) 
				    {
						 return this;
					} 

					
				public:
					/**
					* Property with overriden get method to supply instance
					*/
					static property CrxMessagingManager^ Instance
					{
						  CrxMessagingManager^ get()
						  {
								return CrxMessagingManager::_instance;
						  };
					};
										
					/**
					* Returns an error message corresponding to the specified integer error code.
					*
					* @return The error message for the specified code. Calls Overloaded GetMessage String internally
					*
					* @param[in] errorCode	The error code for which message is required.
					*/
					String ^GetMessage(int errorCode); //Method to pass an error code as an integer and obtain corresponding error message
					
					/**
					* Returns an error message corresponding to the specified string code.
					*
					* @return The error message for the specified code
					*
					* @param[in] strCode	The error string for which message is required.
					*/
					String ^GetMessage(String^ strCode); //Method to pass an error Stringcode as a string and obtain corresponding error message
					
					/**
					* Returns an image corresponding to the specified string.
					*
					* @return The image for the specified string code
					*
					* @param[in] strCode	The image file name for which image is required.
					*/
					Image ^GetImage(String^ strCode); //Method to pass an image name as string and obtain corresponding Image
					
					/**
					* To check resource file exists.
					*
					* @return The bool value, if true resource file exists else not
					*
					*/
					bool CheckResourceFileExist(); //Method to check resource file exist or not.

			};

									
}
}
}
}


