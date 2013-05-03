/**
 * \file 
 *
 * \brief Command Default State
 *
 * Copyright (c) Atcor Medical Pty. Ltd., 2013
 *
 * \date Created: 22/04/2013 10:31:03 AM
 * \author victora
 */ 

#ifndef CMD_STATE_H_
#define CMD_STATE_H_

#include "config/conf_abpm.h"

#define CMD_START_CBP 0x01
#define CMD_ABORT_CBP 0x02
#define CMD_GET_CBP_STATUS 0x03
#define CMD_GET_CBP_RESULTS 0x04
#define CMD_GET_CBP_UP_STATUS 0x05
#define CMD_SET_CBP_CONFIG 0x06
#define CMD_GET_CBP_CONFIG 0x07
#define CMD_GET_CBP_ADC_DATA 0x08
#define CMD_SET_SLEEP_MODE 0x09
#define CMD_WRITE_DATA_FLASH 0x0A
#define CMD_GET_CBP_PRESSURE 0x0B

// CBP configuration
#define CBP_CONFIG_DATA_LEN 4

typedef struct
{
	uint8_t data[CBP_CONFIG_DATA_LEN]; // multibyte configuration parameters
} cbp_config_t;

cbp_config_t current_cbp_config;

// Brachial calibration from BP
typedef struct
{
	uint16_t sys;
	uint16_t dia;
} bp_calibration_t;

// Date time stamp from BP when CPB is started
typedef struct
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} bp_timestamp_t;

// CBP results
typedef struct
{
	uint16_t central_sys;
	uint16_t central_dia;
	uint16_t map; // recalculated result from cbp
	uint16_t hr; // recalculated result from cbp
	uint16_t central_aix;
	uint16_t central_ap;
	uint16_t central_pp;
	uint8_t qc; // 0: poor; 1: good
	uint8_t result_status; // 0: old; 1: new
	uint8_t central_error_code;
	uint8_t central_test_code[8];
	uint8_t central_spare_1;
	uint8_t central_spare_2;
} cbp_results_t;

// Command and response error codes; range 3000-3999
extern uint16_t cmd_resp_error_code;

typedef enum
{
	CMD_UNDEFINED = 3000,
	CMD_ABORT_UNKNOWN_FOREGROUND,
	CMD_EXE_UNKNOWN_FOREGROUND,
	RESP_XMIT_PACKET_BUFF_OVERFLOW,
	RESP_XMIT_PACKET_OUTSTANDING,
} cmd_resp_error_code_t;

// CBP status
#define CBP_SYSTEM_STATUS_DATA_LEN 1
#define CBP_OTHER_STATUS_DATA_LEN 7  // <TBD> Break down other 7 status bytes
#define CBP_STATUS_DATA_LEN (CBP_SYSTEM_STATUS_DATA_LEN + CBP_OTHER_STATUS_DATA_LEN)

// CBP system status; one of CBP status
typedef enum
{
	CBP_SYSTEM_STATUS_POWER_ON,
	CBP_SYSTEM_STATUS_IDLE,
	CBP_SYSTEM_STATUS_CAPTURING,
	CBP_SYSTEM_STATUS_CALCULATING,
	CBP_SYSTEM_STATUS_SAVING_RESULTS,
	CBP_SYSTEM_STATUS_SETTING_CONFIG,
	CBP_SYSTEM_STATUS_WRITING_FLASH,
} cbp_system_status_t;

// CBP Command and Response State
typedef struct _command_state_type_ * command_state_ptr;

typedef void (*start_cbp_func)(command_state_ptr, int);
typedef void (*finish_cbp_func)(command_state_ptr, int);
typedef void (*abort_cbp_func)(command_state_ptr, int);
typedef void (*get_cbp_status_func)(command_state_ptr, int);
typedef void (*get_cbp_results_func)(command_state_ptr, int);
typedef void (*get_cbp_up_status_func)(command_state_ptr, int);
typedef void (*set_cbp_config_func)(command_state_ptr, int);
typedef void (*get_cbp_config_func)(command_state_ptr, int);
typedef void (*get_cbp_adc_data_func)(command_state_ptr, int);
typedef void (*set_sleep_mode_func)(command_state_ptr, int);
typedef void (*write_data_flash_func)(command_state_ptr, int);
typedef void (*get_cbp_pressure_func)(command_state_ptr, int);

typedef struct _command_state_type_
{
	start_cbp_func start_cbp;
	finish_cbp_func finish_cbp; // to handle internal event when pwa calculation is finished
	abort_cbp_func abort_cbp;
	get_cbp_status_func get_cbp_status;
	get_cbp_results_func get_cbp_results;
	get_cbp_up_status_func get_cbp_up_status;
	set_cbp_config_func set_cbp_config;
	get_cbp_config_func get_cbp_config;
	get_cbp_adc_data_func get_cbp_adc_data;
	set_sleep_mode_func set_sleep_mode ;
	write_data_flash_func write_data_flash;
	get_cbp_pressure_func get_cbp_pressure;
	char * name;
} command_state_t;

void default_command_init (command_state_ptr state);
void push_command_state (command_state_ptr state);
void pop_command_state (command_state_ptr state);
void respond_busy (command_state_ptr state, int cmd);
void respond_error (command_state_ptr state, int cmd);
void respond_undefined (command_state_ptr state, int cmd);
void update_cbp_system_status (cbp_system_status_t new_status);
cbp_system_status_t * get_current_cbp_system_status (void);
cbp_config_t * get_current_cbp_config (void);

#endif /* CMD_STATE_H_ */