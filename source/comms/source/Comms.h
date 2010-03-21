#ifndef COMMS_H
#define COMMS_H
#include <meas/pubtype.h>

/*
** This macro returns the high byte of an integer.
*/
#define SCOR_HIGH(word)   ((word >> 8) & 0xFF)

/*
** This macro returns the low byte of an integer.
*/
#define SCOR_LOW(word)   (UINT8)(word & 0xFF)
#define SCOR_MAKEWORD(low, high) ((UINT16)(((UINT8)(low)) | (((UINT16)((UINT8)(high))) << 8)))

const char COMMS_PACKET_OLD_PWA_START = 'N';
const char COMMS_PACKET_OLD_PWV_START = 'P';
const char COMMS_PACKET_OLD_PWM_START = 'N';
const char COMMS_PACKET_OLD_STOP      = 'O';
const char COMMS_PACKET_OLD_DETECT    = 'C';

const unsigned char COMMS_USB_TONOM_SYNCH_BYTE = 0xAA;
const unsigned char COMMS_USB_ECG_SYNCH_BYTE = 0xBB;

const String COMMS_PACKET_OLD_DETECT_SYNCH    = "SphygmoCor, (c)";
const String COMMS_PACKET_OLD_DETECT_RESPONSE = "SphygmoCor, (c) 1995 PWV Medical Pty Ltd";

const int COMMS_PACKET_OLD_DETECT_LEN  = 40;
const int COMMS_PACKET_OLD_PWA_LEN     = 3;
const int COMMS_PACKET_OLD_PWV_LEN     = 6;
const int COMMS_PACKET_OLD_PWM_LEN     = 3;

#define COMMS_PACKET_OLD_SYNCH     "\xAA"

typedef enum
{
   COMMS_CMD_PWA_START = 1,
   COMMS_CMD_PWV_START,
   COMMS_CMD_PWM_START,
   COMMS_CMD_HRV_START,
   COMMS_CMD_EMOD_DETECT,
   COMMS_CMD_REQUEST_PWA_ACK,
   COMMS_CMD_REQUEST_PWV_ACK,
   COMMS_CMD_REQUEST_PWM_ACK,
   COMMS_CMD_REQUEST_HRV_ACK,
   COMMS_CMD_REQUEST_LOOPBACK,
   COMMS_CMD_REQUEST_HWCONFIG,
   COMMS_CMD_REQUEST_PWM_CALIBRATE_IP,
   COMMS_CMD_REQUEST_PWM_CALIBRATE_OP1,
   COMMS_CMD_REQUEST_PWM_CALIBRATE_OP2,
   COMMS_CMD_CAPTURE_STOP,
   COMMS_CMD_UNKNOWN
} COMMS_COMMAND_TYPE;


#define COMMS_CMDBYTE_CAPTURE_START  0x40
#define COMMS_CMDBYTE_TITAN_DETECT   0x50
#define COMMS_CMDBYTE_CAPTURE_STOP   0x60

#define COMMS_CMDBYTE_PWA_ACK_RQST   0x0A
#define COMMS_CMDBYTE_PWA_ACK        0x0B                                 

#define COMMS_CMDBYTE_PWV_ACK_RQST   0x12
#define COMMS_CMDBYTE_PWV_ACK        0x13

#define COMMS_CMDBYTE_HRV_ACK_RQST  0x14
#define COMMS_CMDBYTE_HRV_ACK       0x15

#define COMMS_CMDBYTE_PWM_ACK_RQST          0x1A
#define COMMS_CMDBYTE_PWM_ACK               0x1B
#define COMMS_CMDBYTE_PWM_CAL_IP_RQST       0x79
#define COMMS_CMDBYTE_PWM_CAL_IP_RESPONSE   0x78
#define COMMS_CMDBYTE_PWM_CAL_OP1_RQST      0x7B
#define COMMS_CMDBYTE_PWM_CAL_OP1_RESPONSE  0x7A
#define COMMS_CMDBYTE_PWM_CAL_OP2_RQST      0x7D
#define COMMS_CMDBYTE_PWM_CAL_OP2_RESPONSE  0x7C

#define COMMS_CMDBYTE_CHECK_CRC_ERROR  0x70
#define COMMS_CMDBYTE_CHECK_OK         0x71
#define COMMS_CMDBYTE_CHECK_FSWITCH1   0x73
#define COMMS_CMDBYTE_CHECK_FSWITCH2   0x75
#define COMMS_CMDBYTE_CHECK_HW_ERROR   0x77

#define COMMS_CMDBYTE_LOOPBACK_RQST  0x48
#define COMMS_CMDBYTE_LOOPBACK_ACK   0x49

#define COMMS_CMDBYTE_HWCONFIG_RQST      0x68
#define COMMS_CMDBYTE_HWCONFIG_RESPONSE  0x69

#define COMMS_PACKET_CHANNEL1_MASK  0x02
#define COMMS_PACKET_CHANNEL2_MASK  0x04
#define COMMS_PACKET_CHANNEL3_MASK  0x08

const int COMMS_PACKET_NEW_DETECT_LEN   = 20;

const int COMMS_PACKET_TITAN_ACK_LEN      = 1;
const int COMMS_PACKET_TITAN_PWA_LEN      = 10;
const int COMMS_PACKET_TITAN_PWV_LEN      = 14;
const int COMMS_PACKET_TITAN_HRV_LEN      = 14;

const int COMMS_PACKET_EM3_DETECT_LEN   = 20;
const int COMMS_PACKET_EM3_PWA_LEN      = 10;
const int COMMS_PACKET_EM3_PWV_LEN      = 18;
const int COMMS_PACKET_EM3_HRV_LEN      = 18;

const int COMMS_PACKET_TITAN_PWM_CAL_LEN  = 3;
const int COMMS_PACKET_TITAN_HWCONFIG_LEN = 2;

const int COMMS_PACKET_BYTE_TIMEOUT    = 8;
const int COMMS_PACKET_TIMEOUT         = 80;
const int COMMS_CMD_MAX_SEND_LEN       = 20;


const String COMMS_PACKET_NEW_DETECT_SYNCH    = "SphygmoCor";
const String COMMS_PACKET_MM3_DETECT_RESPONSE = "SphygmoCor 2000, (c)";

const String COMMS_PACKET_EM3_DETECT_RESPONSE =   "SphygmoCor 2006, EM3";


bool comms_packet_setup(COMMS_COMMAND_TYPE cmd_id);

bool comms_get_ack(COMMS_COMMAND_TYPE cmd_id);

bool comms_process_request(COMMS_COMMAND_TYPE cmd_rqst_id);

void comms_reset_error(void);

void comms_set_error(COMMS_ERROR_TYPE error);

UCOUNT comms_build_packet(COMMS_COMMAND_TYPE cmd, UINT8 *packet);

UINT8 comms_calculate_crc(UINT8 *data_packet, UCOUNT packet_len);

void comms_decode_hwconfig(UINT8 cfg_byte);

bool comms_decode_check_byte(UINT8 check_byte);

void comms_determine_module_type(CHAR *data_packet, UCOUNT packet_len);

bool comms_simulation_start(void);

void comms_simulation_stop(void);

void comms_simulation_get_data(void);

void comms_usb_start_thread(void);

void comms_usb_stop_thread(void);

void comms_usb_encode_data(void);

#endif
