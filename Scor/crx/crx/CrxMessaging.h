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
				static  String^ const  Alarmsourceunknown						=	"Alarmsourceunknown";
				static  String^ const  Alarmstatus								=	"AlarmStatus";
				static  String^ const  AnalysisXaxisTitle						=	"ANALYSIS_XAXIS_TITLE";
				static  String^ const  AppMsg									=	"APP_MSG";
				static  String^ const  AppName									=	"APP_NAME";
				static  String^ const  AppVersion								=	"APP_VERSION";
				static  String^ const  ApplicationMessage						=	"APPLICATION_MESSAGE";
				static  String^ const  AprCondition								=	"APR_CONDITION";
				static  String^ const  AugCondition								=	"AUG_CONDITION";
				static  String^ const  BackupDone								=	"BACKUP_DONE";
				static  String^ const  BackupFail								=	"BACKUP_FAIL";
				static  String^ const  BackupProgress							=	"BACKUP_PROGRESS";
				static  String^ const  BackupTitle								=	"BACKUP_TITLE";
				
				static  String^ const  BpGradeIht								=	"BP_GRADE_I_HT";
				static  String^ const  BpGradeIhtRange							=	"BP_GRADE_I_HT_RANGE";
				static  String^ const  BpGradeIiAndIiiHt						=	"BP_GRADE_II_AND_III_HT";
				static  String^ const  BpGradeIiAndIiiHtRange					=	"BP_GRADE_II_AND_III_HT_RANGE";
				static  String^ const  BpHighNormal								=	"BP_HIGH_NORMAL";
				static  String^ const  BpHighNormalRange						=	"BP_HIGH_NORMAL_RANGE";
				static  String^ const  BpNormal									=	"BP_NORMAL";
				static  String^ const  BpNormalRange							=	"BP_NORMAL_RANGE";
				static  String^ const  BpOptimal								=	"BP_OPTIMAL";
				static  String^ const  BpOptimalRange							=	"BP_OPTIMAL_RANGE";
				
				static  String^ const  BtnCancel								=	"BTN_CANCEL";
				static  String^ const  BtnCapture								=	"BTN_CAPTURE";
				static  String^ const  BtnChange								=	"BTN_CHANGE";
				static  String^ const  BtnDefaults								=	"BTN_DEFAULTS";
				static  String^ const  BtnDelete								=	"BTN_DELETE";
				static  String^ const  BtnEdit									=	"BTN_EDIT";
				static  String^ const  BtnExit									=	"BTN_EXIT";
				static  String^ const  BtnFindmodule							=	"BTN_FINDMODULE";
				static  String^ const  BtnMigrate								=	"BTN_MIGRATE";
				static  String^ const  BtnNew									=	"BTN_NEW";
				static  String^ const  BtnOk									=	"BTN_OK";
				static  String^ const  BtnPrint									=	"BTN_PRINT";
				static  String^ const  BtnPrintersetup							=	"BTN_PRINTERSETUP";
				static  String^ const  BtnRepeat								=	"BTN_REPEAT";
				static  String^ const  BtnSave									=	"BTN_SAVE";
				static  String^ const  BtnSearch								=	"BTN_SEARCH";
				static  String^ const  BtnSettings								=	"BTN_SETTINGS";
				static  String^ const  CDrive									=	"C_DRIVE";
				static  String^ const  CaptureDeviceErrMsg						=	"CAPTURE_DEVICE_ERR_MSG";
				static  String^ const  CaptureFailed							=	"CAPTURE_FAILED";
				static  String^ const  CaptureTickMsg							=	"CAPTURE_TICK_MSG";
				static  String^ const  CaptureTimeOutOfRange					=	"CAPTURE_TIME_OUT_OF_RANGE";
				static  String^ const  CaptureTimeToInflation					=	"CAPTURE_TIME_TO_INFLATION";
				static  String^ const  CarotidDistOutOfRange					=	"CAROTID_DIST_OUT_OF_RANGE";
				static  String^ const  CarotidSignalBufferNotFullYet			=	"CAROTID_SIGNAL_BUFFER_NOT_FULL_YET";
				static  String^ const  CarotidSignalCaptureFailed				=	"CAROTID_SIGNAL_CAPTURE_FAILED";
				static  String^ const  ChkFemoralCuff							=	"CHK_FEMORAL_CUFF";
				static  String^ const  ChkPatientPrivacy						=	"CHK_PATIENT_PRIVACY";
				static  String^ const  ChkReferenceRange						=	"CHK_REFERENCE_RANGE";
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
				
				static  String^ const  CrxLogFileHeaderLine						=	"CRX_LOG_FILE_HEADER_LINE";
				static  const   int	   CrxLogFileHeaderLineErrCd				=	300;
				
				static  String^ const  CrxLogFileHeaderSeperator				=	"CRX_LOG_FILE_HEADER_SEPERATOR";
				static	const   int	   CrxLogFileHeaderSeperatorErrCd			=	301;

				static  String^ const  CrxUnknownException						=	"CRX_UNKNOWN_EXCEPTION";
				static  const   int	   CrxUnknownExceptionErrCd					=	104;

				static  String^ const  CuffDistOutOfRange						=	"CUFF_DIST_OUT_OF_RANGE";
				static  String^ const  CuffPulseAppendFailed					=	"CUFF_PULSE_APPEND_FAILED";
				static  String^ const  CuffStateInvalid							=	"CUFF_STATE_INVALID";
				static  String^ const  Cuffleak									=	"CuffLeak";

				static  String^ const  DalConstCaptureFilePrefix				=	"DAL_CONST_CAPTURE_FILE_PREFIX";
				static  String^ const  DalConstCufftimerFilePath				=	"DAL_CONST_CUFFTIMER_FILE_PATH";
				static  String^ const  DalConstDatFileExtn						=	"DAL_CONST_DAT_FILE_EXTN";
				static  String^ const  DalConstGciFirmwareVersion				=	"DAL_CONST_GCI_FIRMWARE_VERSION";
				static  String^ const  DalConstGciSerialNumber					=	"DAL_CONST_GCI_SERIAL_NUMBER";
				static  String^ const  DalConstGciType							=	"DAL_CONST_GCI_TYPE";
				static  String^ const  DalConstSimFolderPath					=	"DAL_CONST_SIM_FOLDER_PATH";

				static  String^ const  DalErrActivePortCloseFailed				=	"DAL_ERR_ACTIVE_PORT_CLOSE_FAILED";
				static	const   int	   DalErrActivePortCloseFailedErrCd			=	1025;

				static  String^ const  DalErrInvalidPortClose					=	"DAL_ERR_INVALID_PORT_CLOSE";
				static	const   int	   DalErrInvalidPortCloseErrCd				=	1027;

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
	
				static  String^ const  DalMsgDefaultModeSelectedSim				=	"DAL_MSG_DEFAULT_MODE_SELECTED_SIM";
				static  String^ const  DalMsgIllegalPacketRcvd					=	"DAL_MSG_ILLEGAL_PACKET_RCVD";
				static  String^ const  DalMsgPortBufferDump						=	"DAL_MSG_PORT_BUFFER_DUMP";
				static  String^ const  Dalunknownmodulestatus					=	"DALUnknownModuleStatus";
				static  String^ const  DataRevInvalid							=	"DATA_REV_INVALID";
				static  String^ const  Day										=	"DAY";
				static  String^ const  DbCorrupt								=	"DB_CORRUPT";
				static  String^ const  DecCondition								=	"DEC_CONDITION";
				static  String^ const  DeletePateint							=	"DELETE_PATEINT";
				static  String^ const  DeletePwvMsg								=	"DELETE_PWV_MSG";
				static  String^ const  Direct									=	"DIRECT";
				static  String^ const  DirectMethod								=	"DIRECT_METHOD";
				static  String^ const  DobNotEntered							=	"DOB_NOT_ENTERED";
				static  String^ const  DocGeneralSettings						=	"DOC_GENERAL_SETTINGS";
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
				static  String^ const  FebCondition								=	"FEB_CONDITION";
				static  String^ const  Feet										=	"FEET";
				static  String^ const  FemaleTxt								=	"FEMALE_TXT";
				static  String^ const  Femoral2CuffOutOfRange					=	"FEMORAL_2_CUFF_OUT_OF_RANGE";
				static  String^ const  FemoralSignalBufferNotFullYet			=	"FEMORAL_SIGNAL_BUFFER_NOT_FULL_YET";
				static  String^ const  FemoralSignalCaptureFailed				=	"FEMORAL_SIGNAL_CAPTURE_FAILED";
				static  String^ const  FieldDistanceCarotid						=	"FIELD_DISTANCE_CAROTID";
				static  String^ const  FieldDistanceCuffOrDirect				=	"FIELD_DISTANCE_CUFF_OR_DIRECT";
				static  String^ const  FieldDistanceFemoral						=	"FIELD_DISTANCE_FEMORAL";
				static  String^ const  FieldPatientDp							=	"FIELD_PATIENT_DP";
				static  String^ const  FieldPatientHeight						=	"FIELD_PATIENT_HEIGHT";
				static  String^ const  FieldPatientHeightFoot					=	"FIELD_PATIENT_HEIGHT_FOOT";
				static  String^ const  FieldPatientHeightInch					=	"FIELD_PATIENT_HEIGHT_INCH";
				static  String^ const  FieldPatientSp							=	"FIELD_PATIENT_SP";
				static  String^ const  FieldPatientWeight						=	"FIELD_PATIENT_WEIGHT";
				static  String^ const  FieldValidationLimitsAre					=	"FIELD_VALIDATION_LIMITS_ARE";
				static  String^ const  FieldValidationMustBeNumber				=	"FIELD_VALIDATION_MUST_BE_NUMBER";
				static  String^ const  FileNotFound								=	"FILE_NOT_FOUND";
				static  String^ const  GroupnameEmpty							=	"GROUPNAME_EMPTY";
				static  String^ const  GroupnameExists							=	"GROUPNAME_EXISTS";
				static  String^ const  GrpBloodPressure							=	"GRP_BLOOD_PRESSURE";
				static  String^ const  GrpCaptureTime							=	"GRP_CAPTURE_TIME";
				static  String^ const  GrpCommsPort								=	"GRP_COMMS_PORT";
				static  String^ const  GrpCuffLocation							=	"GRP_CUFF_LOCATION";
				static  String^ const  GrpHeightWeightUnits						=	"GRP_HEIGHT_WEIGHT_UNITS";
				static  String^ const  GrpPwvDistanceMethod						=	"GRP_PWV_DISTANCE_METHOD";
				static  String^ const  GrpPwvDistanceUnits						=	"GRP_PWV_DISTANCE_UNITS";
				static  String^ const  GrpReportScreen							=	"GRP_REPORT_SCREEN";
				static  String^ const  GrpReports								=	"GRP_REPORTS";
				static  String^ const  GrpSetupScreen							=	"GRP_SETUP_SCREEN";
				static  String^ const  GrpSimulationFiles						=	"GRP_SIMULATION_FILES";
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
				static  String^ const  GuiAtcorHomepageMenu					=	"GUI_ATCOR_HOMEPAGE_MENU";
				static  String^ const  GuiBackupMenu						=	"GUI_BACKUP_MENU";
				static  String^ const  GuiCaptureCuffInflated				=	"GUI_CAPTURE_CUFF_INFLATED";
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
				static  String^ const  GuiInfoTxt							=	"GUI_INFO_TXT";
				static  String^ const  GuiLimitsFormat						=	"GUI_LIMITS_FORMAT";
				static  String^ const  GuiOperatorGuideMenu					=	"GUI_OPERATOR_GUIDE_MENU";
				static  String^ const  GuiPleaseEnterFormat					=	"GUI_PLEASE_ENTER_FORMAT";
				static  String^ const  GuiPrinterSetup						=	"GUI_PRINTER_SETUP";
				static  String^ const  GuiReportAgeOutsideRange				=	"GUI_REPORT_AGE_OUTSIDE_RANGE";
				static  String^ const  GuiReportBpColon						=	"GUI_REPORT_BP_COLON";
				static  String^ const  GuiReportGenPopText					=	"GUI_REPORT_GENERAL_POP_TEXT";
				static  String^ const  GuiReportGreenArea					=	"GUI_REPORT_GREEN_AREA";
				static  String^ const  GuiReportLblBpRange					=	"GUI_REPORT_LBL_BP_RANGE";
				static  String^ const  GuiReportNoBp						=	"GUI_REPORT_NO_BP";
				static  String^ const  GuiReportPwvColon					=	"GUI_REPORT_PWV_COLON";
				static  String^ const  GuiReportRedArea						=	"GUI_REPORT_RED_AREA";
				static  String^ const  GuiRestoreMenu						=	"GUI_RESTORE_MENU";
				static  String^ const  GuiSearchElectronicMod				=	"GUI_SEARCH_ELECTRONIC_MOD";
				static  String^ const  GuiSelectSimulationFile				=	"GUI_SELECT_SIMULATION_FILE";
				static  String^ const  GuiSelectSqlInstance					=	"GUI_SELECT_SQL_INSTANCE";
				static  String^ const  GuiServiceManualMenu					=	"GUI_SERVICE_MANUAL_MENU";
				static  String^ const  GuiSettingsMenu						=	"GUI_SETTINGS_MENU";
				static  String^ const  GuiSettingsPwvPatientReport			=	"GUI_SETTINGS_PWV_PATIENT_REPORT";
				static  String^ const  GuiSettingsPwvReport					=	"GUI_SETTINGS_PWV_REPORT";
				static  String^ const  GuiSetupSearchExitMsg				=	"GUI_SETUP_SEARCH_EXIT_MSG";
				static  String^ const  GuiWarningTxt						=	"GUI_WARNING_TXT";
				static  String^ const  GuiWaveformSaveMsg					=	"GUI_WAVEFORM_SAVE_MSG";
				static  String^ const  HeartrateLblAnalysis					=	"HEARTRATE_LBL_ANALYSIS";
				static  String^ const  HeartrateUnit						=	"HEARTRATE_UNIT";
				static  String^ const  HeightOutOfRange						=	"HEIGHT_OUT_OF_RANGE";
				static  String^ const  HeightRequired						=	"HEIGHT_REQUIRED";
				static  String^ const  HideCaps								=	"HIDE_CAPS";
				static  String^ const  HideSmall							=	"HIDE_SMALL";
				static  String^ const  Inch									=	"INCH";
				static  String^ const  Inflatedovertime						=	"InflatedOverTime";
				static  String^ const  Information							=	"INFORMATION";
				static  String^ const  InsertMode							=	"INSERT_MODE";
				static  String^ const  JanCondition							=	"JAN_CONDITION";
				static  String^ const  JulCondition							=	"JUL_CONDITION";
				static  String^ const  JunCondition							=	"JUN_CONDITION";
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
				static  String^ const  LblDob								=	"LBL_DOB";
				static  String^ const  LblFemoralcuff						=	"LBL_FEMORALCUFF";
				static  String^ const  LblFirstName							=	"LBL_FIRST_NAME";
				static  String^ const  LblGender							=	"LBL_GENDER";
				static  String^ const  LblGroup								=	"LBL_GROUP";
				static  String^ const  LblHeight							=	"LBL_HEIGHT";
				static  String^ const  LblInches							=	"LBL_INCHES";
				static  String^ const  LblLastName							=	"LBL_LAST_NAME";
				static  String^ const  LblNotes								=	"LBL_NOTES";
				static  String^ const  LblOperator							=	"LBL_OPERATOR";
				static  String^ const  LblPateints							=	"LBL_PATEINTS";
				static  String^ const  LblPatientId							=	"LBL_PATIENT_ID";
				static  String^ const  LblPatientName						=	"LBL_PATIENT_NAME";
				static  String^ const  LblPatientDefaultName				=	"LBL_PATIENT_DEFAULT_NAME";
				static  String^ const  LblReportAge							=	"LBL_REPORT_AGE";
				static  String^ const  LblReportAssessment					=	"LBL_REPORT_ASSESSMENT";
				static  String^ const  LblReportAssessments					=	"LBL_REPORT_ASSESSMENTS";
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
				static  String^ const  LblTimestatus						=	"LBL_TIMESTATUS";
				static  String^ const  LblTonometer							=	"LBL_TONOMETER";
				static  String^ const  LblWeight							=	"LBL_WEIGHT";
				static  String^ const  Lbs									=	"LBS";
				static  String^ const  MaleTxt								=	"MALE_TXT";
				static  String^ const  MarCondition							=	"MAR_CONDITION";
				static  String^ const  MathError							=	"MATH_ERROR";
				static  String^ const  MayCondition							=	"MAY_CONDITION";
				static  String^ const  MeasureInvalidCaptureTime			=	"MEASURE_INVALID_CAPTURE_TIME";
				static  String^ const  MeasureInvalidSampleRate				=	"MEASURE_INVALID_SAMPLE_RATE";
				static  String^ const  MeasurementDateInFuture				=	"MEASUREMENT_DATE_IN_FUTURE";
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
				static  String^ const  MsgSaveChange						=	"MSG_SAVE_CHANGE";
				static  String^ const  MsgSaveSettings						=	"MSG_SAVE_SETTINGS";
				static  String^ const  MsgSelectLogo						=	"MSG_SELECT_LOGO";
				static  String^ const  NoRecordsToDelete					=	"NO_RECORDS_TO_DELETE";
				static  String^ const  NoRecordsToEdit						=	"NO_RECORDS_TO_EDIT";
				static  String^ const  Noerroralarm							=	"NoErrorAlarm";
				static  String^ const  NovCondition							=	"NOV_CONDITION";
				static  String^ const  NullMeasurementRecord				=	"NULL_MEASUREMENT_RECORD";
				static  String^ const  OctCondition							=	"OCT_CONDITION";
				static  String^ const  Overpressure							=	"OverPressure";
				static  String^ const  PatientAdded							=	"PATIENT_ADDED";
				static  String^ const  PatientAlreadyExist					=	"PATIENT_ALREADY_EXIST";
				static  String^ const  PatientAlreadyExistforGroup			=	"PATIENT_ALREADY_EXIST_FOR_GROUP";
				static  String^ const  PatientAlreadyExists					=	"PATIENT_ALREADY_EXISTS";
				static  String^ const  PatientNotSaved						=	"PATIENT_NOT_SAVED";
				static  String^ const  PatientNoInvalid						=	"PATIENT_NUM_INVALID";
				static  String^ const  PdfFileError							=	"PDF_FILE_ERROR";

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
				static  String^ const  PwvStartCaptureFailed				=	"PWV_START_CAPTURE_FAILED";
				static  String^ const  PwvStdDevToLarge						=	"PWV_STD_DEV_TO_LARGE";
				static  String^ const  PwvTooSmallForAdult					=	"PWV_TOO_SMALL_FOR_ADULT";
				static  String^ const  PwvUnit								=	"PWV_UNIT";
				static  String^ const  PwvValidDeltasNotEnough				=	"PWV_VALID_DELTAS_NOT_ENOUGH";
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
				static  String^ const  RestoreDone							=	"RESTORE_DONE";
				static  String^ const  RestoreFail							=	"RESTORE_FAIL";
				static  String^ const  RestoreFileMsg						=	"RESTORE_FILE_MSG";
				static  String^ const  RestoreMsg							=	"RESTORE_MSG";
				static  String^ const  RestoreProgress						=	"RESTORE_PROGRESS";
				static  String^ const  RestoreTitle							=	"RESTORE_TITLE";
				static  String^ const  RibbionbarText						=	"RIBBIONBAR_TEXT";
				static  String^ const  SampleRateOutOfRange					=	"SAMPLE_RATE_OUT_OF_RANGE";
				static  String^ const  SearchMode							=	"SEARCH_MODE";
				static  String^ const  SecurityMode							=	"SECURITY_MODE";
				static  String^ const  SelectCaps							=	"SELECT_CAPS";
				static  String^ const  SelectDob							=	"SELECT_DOB";
				static  String^ const  SelectGender							=	"SELECT_GENDER";
				static  String^ const  SelectSmall							=	"SELECT_SMALL";
				static  String^ const  SepCondition							=	"SEP_CONDITION";
				static  String^ const  SetupScreen							=	"SETUP_SCREEN";
				static  String^ const  ShowCaps								=	"SHOW_CAPS";
				static  String^ const  ShowSmall							=	"SHOW_SMALL";
				static  String^ const  SignalFindOnsetsFailed				=	"SIGNAL_FIND_ONSETS_FAILED";
				static  String^ const  SignalHeightMinMaxOutOfRange			=	"SIGNAL_HEIGHT_MIN_MAX_OUT_OF_RANGE";
				static  String^ const  SignalHeightMinTooLarge				=	"SIGNAL_HEIGHT_MIN_TOO_LARGE";
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
				static  String^ const  Startstr								=	"STARTSTR";
				static  String^ const  SubtractingMethod					=	"SUBTRACTING_METHOD";
				static  String^ const  SysDefaultLowcase					=	"SYS_DEFAULT_LOWCASE";
				static  String^ const  SysDefaultUppercase					=	"SYS_DEFAULT_UPPERCASE";
				static  String^ const  SysImageFileWildcard					=	"SYS_IMAGE_FILE_WILDCARD";
				static  String^ const  SysSimFilePath						=	"SYS_SIM_FILE_PATH";
				static  String^ const  SysSimFilePathDebug					=	"SYS_SIM_FILE_PATH_DEBUG";
				static  String^ const  SysSimFileWildcard					=	"SYS_SIM_FILE_WILDCARD";
				static  String^ const  SystemError							=	"SYSTEM_ERROR";
				static  String^ const  SystemId								=	"SYSTEM_ID";
				static  String^ const  SystemIdInvalid						=	"SYSTEM_ID_INVALID";
				static  String^ const  TabAnalysis							=	"TAB_ANALYSIS";
				static  String^ const  TabCapture							=	"TAB_CAPTURE";
				static  String^ const  TabReport							=	"TAB_REPORT";
				static  String^ const  TabSetup								=	"TAB_SETUP";
				static  String^ const  TonometerDataAppendFailed			=	"TONOMETER_DATA_APPEND_FAILED";
				static  String^ const  TransferPatient						=	"TRANSFER_PATIENT";
				static  String^ const  UnitsDistanceCm						=	"UNITS_DISTANCE_CM";
				static  String^ const  UnitsDistanceFoot					=	"UNITS_DISTANCE_FOOT";
				static  String^ const  UnitsDistanceInch					=	"UNITS_DISTANCE_INCH";
				static  String^ const  UnitsDistanceMm						=	"UNITS_DISTANCE_MM";
				static  String^ const  UnitsPressureMmhg					=	"UNITS_PRESSURE_MMHG";
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
					CrxMessagingManager(const CrxMessagingManager^)
					{
					}
		          
					/**
					* Assignment Operator
					*/
					CrxMessagingManager^ operator=(const CrxMessagingManager^) 
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


