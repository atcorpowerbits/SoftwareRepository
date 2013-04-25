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

typedef struct command_state_t* command_state_ptr;

typedef void (*start_cbp_func)(command_state_ptr, int);
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

struct command_state_t
{
	start_cbp_func start_cbp;
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
};

void default_command_init (command_state_ptr state);
void push_command_state (command_state_ptr state);
void pop_command_state (command_state_ptr state);
void respond_busy (command_state_ptr state, int cmd);
void respond_error (command_state_ptr state, int cmd);
void respond_undefined (command_state_ptr state, int cmd);

extern void print_debug(char *msg, ...);
extern int cmd_error;

#endif /* CMD_STATE_H_ */