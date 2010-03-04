//---------------------------------------------------------------------------
#ifndef MsgPubtypeH
#define MsgPubtypeH
//---------------------------------------------------------------------------
typedef enum
{
  TFATAL,
  TERROR,
  TWARNING,
  TNOTIFICATION,
} TMsgType;
//---------------------------------------------------------------------------
const String CONFIRMATION = "Confirmation";
//---------------------------------------------------------------------------
const String SCONFIRMATION = "Confirmation ";
const String SFATAL = "Fatal Error ";
const String SERROR = "Error ";
const String SWARNING = "Warning ";
const String SNOTIFICATION = "Notification ";
const String SEXCEPTION = " Exception :";
const String SVALIDATION = "Validation warning ";
const String SADVISE = "Advise ";
const String SOBJECTINIT = "Failed Initialisation. ";
//---------------------------------------------------------------------------
// Error types
#define MSG_MATH_ERROR          1
#define MSG_EXCEPTION           2
#define MSG_VALIDATION_ERROR    3
#define MSG_DBREADWRITE_ERROR   4
#define MSG_SYSTEM_ERROR        5
#define MSG_MULTDB_ERROR        6
#define MSG_COMMS_ERROR         7
#define MSG_CAPTURE             8
#define MSG_IMPORT_ERROR        9
#define MSG_DBMGR_ERROR        10
#define MSG_CONFIG_ERROR       11
#define MSG_PATIENT_ERROR      12
#define MSG_SECURITY           13
#define MSG_AUDIT              14
#define MSG_EMR_ERROR          15

// Pulse messages
#define MSG_WRONG_PULSE         100
#define MSG_WRONG_RANGE         101
#define MSG_OUT_OF_PULSE        102
#define MSG_POINT_OUT_OF_PULSE  103
#define MSG_WRONG_RECORD        104
#define MSG_ERR_READDB          105
#define MSG_SP_OUT              106
#define MSG_DP_OUT              107
#define MSG_MP_OUT              108
#define MSG_ESP_OUT             109
#define MSG_INVALID_T1          110
#define MSG_INVALID_T2          111
#define MSG_INVALID_ED          112
#define MSG_SIGNAL_TOO_SHORT    113
#define MSG_SIGNAL_TOO_LONG     114
#define MSG_TRIGGER_ERR         115
#define MSG_CALCPULSES_ERR      116
#define MSG_TRIGGER_ERRDB       117
#define MSG_AVPULSE_ERR         118
#define MSG_NOT_FOUND_PEAK      119
#define MSG_WRONG_PERIPH_ED     120
#define MSG_WRONG_INTERVAL_TO_FIND_ED 121
#define MSG_MPS_OUT             122
#define MSG_MPD_OUT             123
#define MSG_HR_OUT              124
#define MSG_POP_EXC             125
#define MSG_NO_STORE            126
#define MSG_POST_ERROR          127
#define MSG_STORE_ERROR         128
#define MSG_ENT_SP_OUT          129
#define MSG_ENT_DP_OUT          130
#define MSG_CALC_EXC            131
#define MSG_NO_PERIPHED         132
#define MSG_NO_SYSTEMID         133
#define MSG_NO_PATIENTNO        134
#define MSG_INVALID_MTYPE       135
#define MSG_ENT_HT_OUT          136
#define MSG_ENT_WT_OUT          137
#define MSG_WRONG_SPLINE        140
#define MSG_NEG_AVPULSE         150
#define MSG_NEG_SIGNAL          151
#define MSG_ENT_MP_OUT          152
#define MSG_MEAS_ERROR_CALC     153
#define MSG_MEAS_ERROR_STORE    154
#define MSG_SIGNAL_GRADIENT_TOO_BIG 155
#define MSG_DB3_SIGNAL_TRUNCATED 156
#define MSG_DB3_CORRUPTED       157
#define MSG_SIGNAL_TOO_SMALL    158
#define MSG_AI_OUT              159
#define MSG_P1H_OUT             160
#define MSG_CALCSYSTONSET_ERR   161
#define MSG_TIME_OUT_OF_RANGE   162
#define MSG_WRONG_PULSE_SAMPLERATE 163
#define MSG_INVALID_UPSAMPLERATE 164

#define MSG_PERIPH_CENTRAL_ED    165
#define MSG_PERIPH_CENTRAL_SP    166
#define MSG_PERIPH_CENTRAL_DP    167
#define MSG_DPDT_OUT             168
#define MSG_PWA_TOO_BAD_SIGNAL   169
#define MSG_PERIPH_CENTRAL_LENGTH 170
#define MSG_PERIPH_CENTRAL_ONSETS 171
#define MSG_PH_TOO_SMALL          172
#define MSG_SPDPMP_VALIDATION_ERROR 173

#define MSG_ENT_SP_LESS_DP_OUT      174

#define MSG_APP_ALREADY_RUNNING          200
#define MSG_CHECK_CONNECTION             201
#define MSG_ELECTR_NOT_FOUND             202
#define MSG_NO_REPORTS_FOR_PATIENT       203
#define MSG_NO_REPORTS                   204
#define MSG_NO_STUDIES_FOR_ANALYSIS      205
#define MSG_NO_STUDIES                   206
#define MSG_POSTED_CHANGES               207
#define MSG_SUCCESSFUL_UPDATE            208
#define MSG_CHECK_INPUT                  209
#define MSG_INSUFFICIENT_INFORMATION     210
#define MSG_ACCEPT_CHANGES               211
#define MSG_SAVE_CHANGES                 212
#define MSG_NEW_PATIENT_RECORD           213
#define MSG_INSERT_NEW_PATIENT           214
#define MSG_ABORT_CHANGES                215
#define MSG_CANCEL_OPERATION             216
#define MSG_DELETE_PATIENT               217
#define MSG_DELETE_MEAS1                 218
#define MSG_ARE_YOU_SURE                 219
#define MSG_NO_REPORTS_TO_DISPLAY        220
#define MSG_DELETE_MEAS2                 221
#define MSG_CREATE_REPORT                222
#define MSG_DATA_CAPTURED                223
#define MSG_NEED_11_SECONDS              224
#define MSG_NOT_ENOUGH_POINTS            225
#define MSG_YOUNG_PATIENT                226
#define MSG_OLD_PATIENT                  227
#define MSG_ANALYSIS_INVALID_COUNT       228
#define MSG_PATIENT_INSERT_ERROR         229
#define MSG_PATIENT_NUMBER_ERROR         230
#define MSG_PATIENT_DELETE_ERROR         231
#define MSG_PWM_NO_TREND_POINTS          234
#define MSG_PATIENT_LISTING              240
#define MSG_PATIENT_STRINGS              241
#define MSG_PATIENT_SURNAME              242
#define MSG_PATIENT_FIRST_NAME           243
#define MSG_PATIENT_DOB                  244
#define MSG_PATIENT_SEX                  245
#define MSG_PATIENT_ID                   246
#define MSG_PATIENT_DUPLICATE            247
#define MSG_PATIENT_NO_SEARCH_PARAMETERS 248
#define MSG_PATIENT_NO_PATIENTS          249

#define MSG_INTERVIEW_FILE               250
#define MSG_INTERVIEW_CODES              251
#define MSG_INTERVIEW_CODE               252
#define MSG_INTERVIEW_QUESTIONS          253

#define MSG_NOT_ENOUGH_ONSETS            260
#define MSG_TOO_MUCH_ONSETS              261

#define MSG_COMMS_CHECK_POWER_CONNECTION 500
#define MSG_COMMS_EL_MODULE_NOT_FOUND    501
#define MSG_COMMS_TRY_AGAIN              502
#define MSG_COMMS_COMMUNICATIONS_PROBLEM 503
#define MSG_COMMS_BUSY_PORT              504
#define MSG_COMMS_PORT_ERROR             505
#define MSG_COMMS_BYTE_TIMEOUT           506
#define MSG_COMMS_PACKET_TIMEOUT         507
#define MSG_COMMS_PACKET_CORRUPT         508
#define MSG_COMMS_TURN_ON                510
#define MSG_COMMS_NO_FILE                511
#define MSG_COMMS_CHECK_FILENAME         512
#define MSG_COMMS_MODULE_CONFLICT        513
#define MSG_COMMS_MODULE_UNDEFINED       514
#define MSG_COMMS_NO_ACK_RXD             515
#define MSG_COMMS_DETECT_MODULE          516

#define MSG_CAPTURE_SIGNAL_TOO_LOW       520
#define MSG_CAPTURE_SIGNAL_HEIGHT_TOO_LOW    521
#define MSG_CAPTURE_SIGNAL_ECG_CLIPPED   522

#define MSG_PWV_CALCDELTAT_ERR           300
#define MSG_PWV_INVALID_HEART_RATE       301
#define MSG_PWV_INVALID_ALGORITHM        302
#define MSG_INVALID_SAMPLERATE           303
#define MSG_PWV_TOO_BAD_SIGNAL           304
#define MSG_PWV_INVALID_RANGE            305
#define MSG_PWV_CALC_ERROR               306
#define MSG_PWV_INVALID_PULSE_HEIGHT_PERCENT 307
#define MSG_PWV_INVALID_DISTANCES        308
#define MSG_PWV_INVALID_DISTANCE         309
#define MSG_PWV_INVALID_CAPTURE_TIME     310
#define MSG_PWV_THE_SAME_TYPE            311
#define MSG_PWV_SITEA_DISTAL             312
#define MSG_PWV_SITEB_PROXIMAL           313
#define MSG_PWV_DEVIATION_TOO_BIG        314
#define MSG_PWV_TRIGGER_ERR              315
#define MSG_PWV_NEGATIVE_DT              316
#define MSG_PWV_SWAP_SITES               317
#define MSG_PWV_HR_DIFFERENCE            318
#define MSG_PWV_NEED_SECONDS             320


// Export-import
#define MSG_EXPORT_ERROR                 400
#define MSG_NO_EXPORT                    401
#define MSG_IMPORT_NO_DIR                402
#define MSG_IMPORT_NO_FILE               403
#define MSG_IMPORT_NO_SPACE              404
#define MSG_EXPORT_NO_SPACE              405
#define MSG_EXPORT_ERROR_FILE            406
#define MSG_EXPORT_EXCEPTION             407
#define MSG_EXPORT_DATABASE              408

// Confirmation questions
#define MSG_PRINT_REPORT                 600
#define MSG_CLOSE_PROGRAM                601
#define MSG_UPDATE_ALL                   602

// Configuration messages
#define MSG_NO_SYSTEM_SUBDIR             700
#define MSG_NO_DATA_SUBDIR               701
#define MSG_NO_DATABASE                  702
#define MSG_NO_DB_IN_SYSTEM_DIR          703
#define MSG_CONFIG_OUT_OF_RANGE          704
#define MSG_CONFIG_NO_SYSID              705
#define MSG_CONFIG_CHECKSUM_FAILED       706
#define MSG_OLD_DATABASE                 707
#define MSG_CONFIG_SENSITIVITY_OUT_OF_RANGE   710
#define MSG_CONFIG_DISPLAY_SETTINGS           712
#define MSG_CONFIG_CHECK_FILENAME        713

// Multiple DB
#define MSG_MULTDB_INCORRECT_DATASET     800
#define MSG_MULTDB_TOO_MANY              801
#define MSG_MULTDB_INCORRECT_HEADER      802
#define MSG_MULTDB_FILEOPENERROR         803
#define MSG_MULTDB_RECOVERED             804
#define MSG_MULTDB_CANT_CREATE           805
#define MSG_MULTDB_CANT_DELETE           806
#define MSG_MULTDB_MISSING_DB            807
#define MSG_MULTDB_NO_SPACE              808
#define MSG_MULTDB_ALREADY_EXIST         809
#define MSG_MULTDB_MAX_EXCEEDED          810
#define MSG_MULTDB_OPERATION_PERFORMED   811
#define MSG_MULTDB_WAS_ACTIVE            812
#define MSG_MULTDB_WILL_DELETE           813
#define MSG_MULTDB_SURE                  814
#define MSG_MULTDB_ABSOLUTELY_SURE       815
#define MSG_MULTDB_COULDNOT_DELETE       816
#define MSG_MULTDB_NOT_EXIST             817
#define MSG_MULTDB_CANT_DELETE_DIR       818
#define MSG_MULTDB_NO_DELETE_DEFAULT     819
#define MSG_MULTDB_REMOVED               820
#define MSG_MULTDB_FAIL_TO_DELETE        821
#define MSG_MULTDB_DESCRIPTION           822
#define MSG_MULTDB_CANT_COPY_TO_ITSELF   823
#define MSG_MULTDB_UPDATE_FAILED         824
#define MSG_MULTDB_UPDATE_NO_SPACE       825
#define MSG_MULTDB_COPY_NO_SPACE         826
#define MSG_MULTDB_UPDATE_WRONG          827
#define MSG_MULTDB_UPDATE_SUCCESS        828
#define MSG_MULTDB_CANT_COPY             829
#define MSG_MULTDB_CANT_CREATE_DEST      830
#define MSG_MULTDB_CHECK_COPY            831
#define MSG_MULTDB_COPY_SUCCESS          832
#define MSG_MULTDB_CANT_UPDATE           833
#define MSG_MULTDB_UPDATE_WAS_ACTIVE     834
#define MSG_MULTDB_COPY_FAILED           835
#define MSG_MULTDB_SELECT_FAILED         840
#define MSG_MULTDB_CONVERSION_FAILED     841
#define MSG_MULTDB_RENAME_FAILED         842
#define MSG_MULTDB_DATABASE_EXISTS       843

#define MSG_DBMGR_FAIL_INIT              900
#define MSG_DBMGR_NO_DB                  901
#define MSG_DBMGR_ERROR_DB               902
#define MSG_DBMGR_ERROR_OPEN_TABLE       903
#define MSG_DBMGR_ERROR_QUERY            904
#define MSG_DBMGR_ERROR_INDEX            905
#define MSG_DBMGR_NO_HRV_TABLE           906
#define MSG_DBMGR_MISSING_PWA_FIELDS     907
#define MSG_DBMGR_NO_SPACE               908
#define MSG_DBMGR_OVERWRITE              909
#define MSG_DBMGR_NO_AUDIT_TABLE         910

#define MSG_NO_RECORDS_FOR_THIS_PERIOD   1000

#define MSG_PWM_NO_DEVICE                1050

#define MSG_HRV_NEG_HISTOGRAM            1100
#define MSG_HRV_MEAN_OUT                 1101
#define MSG_HRV_MAX_OUT                  1102
#define MSG_HRV_MIN_OUT                  1103
#define MSG_HRV_MAX_MIN_OUT              1104
#define MSG_HRV_RANGE_OUT                1105
#define MSG_HRV_NEG_SD                   1106
#define MSG_HRV_NEG_NN50                 1107
#define MSG_HRV_PNN50_OUT                1108
#define MSG_HRV_NEG_RMS_SD               1109
#define MSG_HRV_INDEX_OUT                1110
#define MSG_HRV_TRIANGULAR_INDEX_OUT     1111
#define MSG_HRV_NEG_SDANN                1112
#define MSG_HRV_NEG_SDNN                 1113
#define MSG_HRV_PULSES_OUT               1114
#define MSG_HRV_NEG_START_PULSE          1115
#define MSG_HRV_END_PULSE_OUT            1116
#define MSG_HRV_NEG_RTOR                 1117
#define MSG_HRV_POINTS_OUT               1118
#define MSG_HRV_NEG_POWER                1119
#define MSG_HRV_NEG_FREQUENCY            1120
#define MSG_HRV_NEG_LF_POWER             1121
#define MSG_HRV_NEG_HF_POWER             1122
#define MSG_HRV_LF_POWER_NORM_OUT        1123
#define MSG_HRV_HF_POWER_NORM_OUT        1124
#define MSG_HRV_LF_MAX_OUT               1125
#define MSG_HRV_HF_MAX_OUT               1126
#define MSG_HRV_REJECTED_OUT             1127
#define MSG_HRV_REJECTED_INDEX_OUT       1128
#define MSG_HRV_TIME_OUT                 1129
#define MSG_HRV_NO_PULSES                1130
#define MSG_HRV_NEG_ECG                  1131
#define MSG_HRV_VALSALVA_HIGH            1132
#define MSG_HRV_VALSALVA_LOW             1133
#define MSG_HRV_VALSALVA_RATIO           1134
#define MSG_HRV_STAND_HIGH               1135
#define MSG_HRV_STAND_LOW                1136
#define MSG_HRV_STAND_RATIO              1137

#define MSG_AVI_NO_T1                    1200
#define MSG_AVI_NO_ED                    1201
#define MSG_AVI_T1_OUT                   1202
#define MSG_AVI_ERROR_CALC               1203
#define MSG_AVI_REFLECTION_INDEX_OUT     1204
#define MSG_AVI_PEAK_TIMES               1205
#define MSG_AVI_VELOCITY_OUT             1206
#define MSG_AVI_AORTIC_REFLECTION_TIME_OUT      1207
#define MSG_AVI_TRANSMISSION_TIME_OUT    1208

#define MSG_SECURITY_CHECK_INPUT         1300
#define MSG_SECURITY_SUCCESS             1301
#define MSG_SECURITY_FAILED              1302
#define MSG_SECURITY_EXIT                1303
#define MSG_SECURITY_LOCKED              1304
#define MSG_SECURITY_TONOMETER           1305
#define MSG_SECURITY_GUEST               1306

#define MSG_AUDIT_PATIENT_EDIT_ERROR     1350
#define MSG_AUDIT_PATIENT_CHECK_INPUT    1351
#define MSG_AUDIT_PATIENT_NO_REPORTS_TO_DISPLAY 1352
#define MSG_AUDIT_CHECK_INPUT            1353
#define MSG_AUDIT_DELETE                 1354
#define MSG_AUDIT_NO_REPORTS_TO_DISPLAY  1355
#define MSG_AUDIT_MODE                   1356
#define MSG_AUDIT_NO_STUDIES_FOR_ANALYSIS       1357

#define MSG_EMR_NO_REQUIRED_SECTION      1400
#define MSG_EMR_NO_SYSTEM_ID             1401
#define MSG_EMR_NO_LAST_NAME             1402
#define MSG_EMR_NO_FIRST_NAME            1403
#define MSG_EMR_NO_DOB                   1404
#define MSG_EMR_NO_SEX                   1405
#define MSG_EMR_NO_INBOUND_FILE          1406
#define MSG_EMR_DEFAULT_MODE             1407
#define MSG_EMR_NO_INI_FILE              1408
#define MSG_EMR_SYSTEM_ID_ERROR          1409
#define MSG_EMR_LAST_NAME_ERROR          1410
#define MSG_EMR_FIRST_NAME_ERROR         1411
#define MSG_EMR_DOB_ERROR                1412
#define MSG_EMR_SEX_ERROR                1413
#define MSG_EMR_DP_OUT                   1414
#define MSG_EMR_SP_OUT                   1415
#define MSG_EMR_MP_OUT                   1416
#define MSG_EMR_PH_TOO_SMALL             1417
#define MSG_EMR_NO_SPMP                  1418
#define MSG_EMR_HT_OUT                   1419
#define MSG_EMR_WT_OUT                   1420
#define MSG_EMR_OUTBOUND_ERROR           1421
#define MSG_EMR_OPTION_ERROR             1422
#define MSG_EMR_OUTBOUND_CREATE          1423
#define MSG_EMR_OUTBOUND_DEFAULT         1424
#define MSG_EMR_PDF_ERROR                1425
#define MSG_EMR_CFR11                    1426
//---------------------------------------------------------------------------
#endif
