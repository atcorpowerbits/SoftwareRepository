/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : COMMS\COMMS.CPP
**
** PROJECT       : TITAN SWCI
**
** OBJECT        : COMMS (Communications)
**

** DESCRIPTION   : Implementation of objects Public services.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 18/05/98
**
*/
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <AdPort.hpp>
#include <AdPacket.hpp>

#include <inc/std.h>
#include <config/pubserv.h>
#include <log/pubserv.h>
#include <msg/pubserv.h>
#include <meas/pubserv.h>
#include <capture/pubserv.h>
#include <comms/pubserv.h>
#include <patient/pubserv.h>
#include "attrib.h"
#include "comms.h"

VAR_EXPORT  COMMS_EMODULE_TYPE            comms_emod;
VAR_EXPORT  CONFIG_SYSTEM_OPTIONS         comms_emod_modes;

VAR_EXPORT  TApdComPort                   *comms_port;
VAR_EXPORT  TApdComPort                   *comms_second_port;
VAR_EXPORT  TApdDataPacket                *comms_data_packet;
VAR_EXPORT  TApdDataPacket                *comms_detect_packet;
VAR_EXPORT  TApdDataPacket                *comms_ack_packet;
VAR_EXPORT  TApdDataPacket                *comms_old_detect_packet;
VAR_EXPORT  USB_Comms                     *comms_usb_port;
//VAR_EXPORT  COMMS_USB_DATA_EVENT_HANDLER  *comms_usb_rx_thread;
VAR_EXPORT  WORD                          comms_data_timer;
VAR_EXPORT  bool                          comms_module_detected;
VAR_EXPORT  bool                          comms_ack_received;
VAR_EXPORT  COMMS_ERROR_TYPE              comms_error;
VAR_EXPORT  COMMS_FOOTSWITCH_STATUS_TYPE  comms_footswitch_status;
VAR_EXPORT  bool                          comms_dmod_timer_expired;
VAR_EXPORT  TTimer                        *comms_simulation_timer;

const int COMMS_PORT_BAUD_OLD = 9600;
const int COMMS_PORT_BAUD_MM3 = 38400;
const int COMMS_PORT_BAUD_EM3 = 57600;

const int COMMS_TIMER_INTERVAL = 300;
const int COMMS_ACK_TIMER_INTERVAL = 500;
const int COMMS_CALIBRATE_TIMER_INTERVAL = 2000;
const int COMMS_PORT_INSIZE = 8192;
const int COMMS_PORT_OUTSIZE = 8192;

// PM V9
const int COMMS_PORTS_AVAILABLE = 30;

bool   comms_initialised;
bool   comms_port_opened;
int    comms_rx_timer_period;
UINT8  comms_send_packet[COMMS_CMD_MAX_SEND_LEN];
INT8   comms_parameter_packet[COMMS_CMD_MAX_SEND_LEN];
UCOUNT comms_usb_tx_counter;

static COMMS_EVENT_HANDLER_CLASS  handler;

String comms_usb_device_name;
String comms_emod_modes_string;
String comms_emod_string;

bool comms_initialise(void)
{
   comms_initialised = true;
   comms_port_opened = false;

   comms_usb_tx_counter = 0;
   for (int i = 0; i < COMMS_CMD_MAX_SEND_LEN; i++)
   {
      comms_send_packet[i] = 0;
      comms_parameter_packet[i] = 0;
   }

   comms_emod = COMMS_UNKNOWN_MODULE;
   comms_emod_modes = CONFIG_NO_OPTION;
   comms_emod_modes_string = CONFIG_NO_OPTION_STRING;
   comms_footswitch_status = COMMS_FOOTSWITCH_NONE;
   comms_module_detected = false;
   comms_ack_received = false;
   comms_dmod_timer_expired = false;
   comms_error = COMMS_ERROR_NONE;
   comms_port = (TApdComPort *)NULL;

   comms_port = new TApdComPort(NULL);

   comms_port->AutoOpen = false;

   comms_port->ComNumber = COMMS_PORT_TWO;
   comms_port->Baud = COMMS_PORT_BAUD_MM3;
   comms_port->DataBits = 8;
   comms_port->StopBits = 1;
   comms_port->Parity = pNone;

   comms_port->DTR = false;
   comms_port->RTS = false;
   comms_port->InSize = COMMS_PORT_INSIZE;
   comms_port->OutSize = COMMS_PORT_OUTSIZE;
   comms_port->SWFlowOptions = swfNone;

   comms_port->DeviceLayer = dlWin32;
   comms_port->PromptForPort = false;
   comms_port->RS485Mode = false;
   comms_port->TapiMode = tmOff;

   comms_port->Tracing = tlOff;

   // Initialise the second port the same as the first
   comms_second_port = (TApdComPort *)NULL;
   comms_second_port = new TApdComPort(NULL);

   comms_second_port->AutoOpen = false;

   comms_second_port->ComNumber = COMMS_PORT_TWO;
   comms_second_port->Baud = COMMS_PORT_BAUD_MM3;
   comms_second_port->DataBits = 8;
   comms_second_port->StopBits = 1;
   comms_second_port->Parity = pNone;

   comms_second_port->DTR = false;
   comms_second_port->RTS = false;
   comms_second_port->InSize = COMMS_PORT_INSIZE;
   comms_second_port->OutSize = COMMS_PORT_OUTSIZE;
   comms_second_port->SWFlowOptions = swfNone;

   comms_second_port->DeviceLayer = dlWin32;
   comms_second_port->PromptForPort = false;
   comms_second_port->RS485Mode = false;
   comms_second_port->TapiMode = tmOff;

   comms_second_port->Tracing = tlOff;

   //comms_data_timer = 0;
   //comms_port->OnTriggerTimer = handler.data_timeout_event;

   comms_data_packet = new TApdDataPacket(NULL);
   comms_data_packet->ComPort = comms_port;

   comms_ack_packet = new TApdDataPacket(NULL);
   comms_ack_packet->ComPort = comms_port;

   comms_ack_packet->AutoEnable = false;
   comms_ack_packet->Enabled = false;

   comms_ack_packet->StartCond = scAnyData;
   comms_ack_packet->EndCond << ecPacketSize;
   comms_ack_packet->PacketSize = COMMS_PACKET_TITAN_ACK_LEN;
   comms_ack_packet->IgnoreCase = true;
   comms_ack_packet->IncludeStrings = true;

   comms_ack_packet->OnPacket = handler.ack_packet_event;
   comms_ack_packet->OnTimeout = NULL;

   comms_detect_packet = new TApdDataPacket(NULL);
   comms_detect_packet->ComPort = comms_port;

   comms_detect_packet->AutoEnable = false;
   comms_detect_packet->Enabled = false;

   comms_detect_packet->StartCond = scString;
   comms_detect_packet->StartString = COMMS_PACKET_NEW_DETECT_SYNCH;
   comms_detect_packet->EndCond << ecPacketSize;
   comms_detect_packet->PacketSize = COMMS_PACKET_NEW_DETECT_LEN;
   comms_detect_packet->IgnoreCase = false;
   comms_detect_packet->IncludeStrings = true;

   comms_detect_packet->TimeOut = COMMS_PACKET_BYTE_TIMEOUT;
   comms_detect_packet->OnPacket = handler.detect_packet_event;
   comms_detect_packet->OnTimeout = handler.byte_timeout_event;

   comms_old_detect_packet = new TApdDataPacket(NULL);
   comms_old_detect_packet->ComPort = comms_port;

   comms_old_detect_packet->AutoEnable = false;
   comms_old_detect_packet->Enabled = false;

   comms_old_detect_packet->StartCond = scString;
   comms_old_detect_packet->StartString = COMMS_PACKET_OLD_DETECT_SYNCH;
   comms_old_detect_packet->EndCond << ecPacketSize;
   comms_old_detect_packet->PacketSize = COMMS_PACKET_OLD_DETECT_LEN;
   comms_old_detect_packet->IgnoreCase = false;
   comms_old_detect_packet->IncludeStrings = true;

   comms_old_detect_packet->TimeOut = COMMS_PACKET_BYTE_TIMEOUT;
   comms_old_detect_packet->OnPacket = handler.detect_packet_event;
   comms_old_detect_packet->OnTimeout = handler.byte_timeout_event;

   comms_rx_timer_period = COMMS_TIMER_INTERVAL;
   comms_simulation_timer = new TTimer(NULL);
   if (comms_simulation_timer != NULL)
   {
      comms_simulation_timer->Enabled = false;
      comms_simulation_timer->Interval = 100;
      comms_simulation_timer->OnTimer = handler.simulate_data_event;
   }
   //comms_usb_rx_thread = NULL;
   comms_usb_device_name = "Ezusb-0";
   if (config_get_comms_port() == COMMS_PORT_USB)
   {
      comms_usb_port = new USB_Comms(false);
   }
   else
   {
      comms_usb_port = NULL;
   }
   return (comms_initialised);
}

void comms_destroy(void)
{
   if (comms_initialised && comms_port != NULL)
   {
      comms_initialised = false;
      comms_close();
      if (comms_port->Open)
      {
         comms_port->Open = false;
      }
      comms_port->OnTriggerTimer = NULL;

      // Destroy second port
      if (comms_second_port != NULL)
      {
         if (comms_second_port->Open)
         {
            comms_second_port->Open = false;
         }
         comms_second_port->OnTriggerTimer = NULL;
         
         delete (comms_second_port);
      }

      if (comms_simulation_timer != NULL)
      {
         delete comms_simulation_timer;
      }

      if (comms_data_packet != NULL)
      {
         comms_data_packet->OnPacket = NULL;
         comms_data_packet->OnTimeout = NULL;
         delete (comms_data_packet);
         comms_data_packet = NULL;
      }

      if (comms_detect_packet != NULL)
      {
         comms_detect_packet->OnPacket = NULL;
         comms_detect_packet->OnTimeout = NULL;
         delete (comms_detect_packet);
         comms_detect_packet = NULL;
      }

      if (comms_ack_packet != NULL)
      {
         comms_ack_packet->OnPacket = NULL;
         comms_ack_packet->OnTimeout = NULL;
         delete (comms_ack_packet);
         comms_ack_packet = NULL;
      }

      if (comms_old_detect_packet != NULL)
      {
         comms_old_detect_packet->OnPacket = NULL;
         comms_old_detect_packet->OnTimeout = NULL;
         delete (comms_old_detect_packet);
         comms_old_detect_packet = NULL;
      }

      if (comms_usb_port != NULL)
      {
         comms_usb_stop_thread();
         /*
         if (comms_usb_rx_thread != NULL)
         {
            comms_usb_stop_thread();
            comms_usb_rx_thread->Terminate();
            Sleep(10);
            delete comms_usb_rx_thread;
         }
         */
         comms_usb_port->Close();
         delete comms_usb_port;
         comms_usb_port = NULL;
      }
      Sleep(10);

      if (comms_port != NULL)
      {
         delete (comms_port);
      }
   }
}

void comms_reset(void)
{
   COMMS_ID_TYPE port_id;

   port_id = config_get_comms_port();

   if (port_id == COMMS_PORT_USB)
   {
      if (comms_usb_port != NULL)
      {
         comms_usb_port->ResetDevice();
      }
   }
}

// Returns a TStringList of the computer's communication ports

void comms_detect_ports(TStringList *port_list)
{
   int         cport;
   AnsiString  cport_name;
   COMMCONFIG  cc;
   DWORD       size;

   for (cport = 1; cport < COMMS_PORTS_AVAILABLE; cport++)
   {
      cport_name = "COM" +IntToStr(cport);
      size = sizeof(COMMCONFIG);
      if (GetDefaultCommConfig(cport_name.c_str(), &cc, &size))
      {
         port_list->Add(IntToStr(cport));
      }
   }
}

// Returns true if the communication port exists
bool comms_port_exists(void)
{
   int         cport;
   AnsiString  cport_name;
   COMMCONFIG  cc;
   DWORD       size;
   bool        exists = false;
 
   cport = 1;
   while (cport < COMMS_PORTS_AVAILABLE && !exists)
   {
      cport_name = "COM" +IntToStr(cport);
      size = sizeof(COMMCONFIG);
      if (GetDefaultCommConfig(cport_name.c_str(), &cc, &size))
      {
         if (cport == comms_port->ComNumber)
         {
            exists = true;
         }
      }
      ++cport;
   }
   return exists;
}

bool comms_open(COMMS_ID_TYPE port_id, bool disable_errors, bool second_port)
{
   bool           do_open = false;
   TApdComPort    *port;

   if (second_port)
   {
      port = comms_second_port;
   }
   else
   {
      port = comms_port;
   }

   if (port_id == COMMS_PORT_SIMULATE)
   {
      return true;
   }

   if (port_id == COMMS_PORT_USB)
   {
      if (comms_usb_port == NULL)
      {
         comms_usb_port = new USB_Comms(false);
      }
      if (comms_usb_port == NULL)
      {
         return false;
      }
      else
      {
         if (!comms_port_opened)
         {
            comms_usb_device_name = "Ezusb-0";
            if (comms_usb_port->Open(&String(comms_usb_device_name), bulkTransfer))
            {
               comms_port_opened = true;
            }
            else
            {
               comms_usb_device_name = "Ezusb-1";
               if (comms_usb_port->Open(&String(comms_usb_device_name), bulkTransfer))
               {
                  comms_port_opened = true;
               }
               else
               {
                  comms_port_opened = false;
               }
            }

         }
         return comms_port_opened;
      }
   }
   else
   {
      if (port)
      {
         if (port_id == port->ComNumber)
         {
            if (!port->Open)
            {
               do_open = true;
            }
         }
         else
         {
            do_open = true;
            comms_close(second_port);
         }

         if (do_open)
         {
            port->ComNumber = port_id;
            try
            {
               port->Open = true;
               comms_port_opened = true;
            }
            catch(Exception &exception)
            {
               if (!disable_errors)
               {
                  String S = LoadStr(MSG_COMMS_BUSY_PORT) + " PortID = " + IntToStr((int)port_id);
                  MsgBox_show(TWARNING,
                              MSG_COMMS_ERROR,
                              S,
                              MSG_COMMS_BUSY_PORT, "");
                  config_show();
               }
               comms_port_opened = false;
            }
         }
         return (port->Open);
      }
      else
      {
         return false;
      }
   }
}

void comms_close(bool second_port)
{
   COMMS_ID_TYPE       port_id;
   MEAS_ID_TYPE        study_mode;

   port_id = config_get_comms_port();
   study_mode = patient_get_study_mode();

   if (!second_port)
   {
      if (port_id == COMMS_PORT_SIMULATE)
      {
         ;
      }
      else if (port_id == COMMS_PORT_USB)
      {
         if (comms_usb_port)
         {
            comms_usb_port->Close();
            comms_port_opened = false;
         }
         ;
      }
      else
      {
         if (comms_port->Open)
         {
            // PM CR
            // This is a fix for PWM freezing issues with Windows 7
            if (study_mode == MEAS_PWM_ID)
            {
               comms_stop();
            }
            comms_port->Open = false;
            comms_port_opened = false;
         }
      }
   }
   else
   {
      // Always close the second port if open as it cannot be simulate or usb
      if (comms_second_port->Open)
      {
         comms_second_port->Open = false;
      }
   }
}

bool comms_start(MEAS_ID_TYPE meas_id)
{
   bool                started = false;
   COMMS_COMMAND_TYPE  start_cmd;
   COMMS_COMMAND_TYPE  ack_cmd;
   UINT8               send_packet[COMMS_CMD_MAX_SEND_LEN];
   UCOUNT              send_length;
   COMMS_ID_TYPE       port_id;

   port_id = config_get_comms_port();

   if (port_id == COMMS_PORT_SIMULATE)
   {
      if (comms_simulation_start())
      {
         return true;
      }
      else
      {
         return false;
      }
   }

   switch (meas_id)
   {
      case MEAS_PWA_ID:
         start_cmd = COMMS_CMD_PWA_START;
         ack_cmd = COMMS_CMD_REQUEST_PWA_ACK;
         break;
      case MEAS_PWV_ID:
         start_cmd = COMMS_CMD_PWV_START;
         ack_cmd = COMMS_CMD_REQUEST_PWV_ACK;
         break;
      case MEAS_PWM_ID:
         start_cmd = COMMS_CMD_PWM_START;
         ack_cmd = COMMS_CMD_REQUEST_PWM_ACK;
         break;
      case MEAS_HRV_ID:
         start_cmd = COMMS_CMD_HRV_START;
         ack_cmd = COMMS_CMD_REQUEST_HRV_ACK;
         break;
       default:
         break;
   }
   comms_usb_tx_counter = 0;
   
   if (port_id == COMMS_PORT_USB)
   {
      started = false;
      if (comms_usb_port)
      {
         if (comms_usb_port->Start())
         {
            comms_usb_start_thread();
            for (int i = 0; i < COMMS_CMD_MAX_SEND_LEN; i++)
            {
               send_packet[i] = 0;
            }
            send_length = comms_build_packet(ack_cmd, send_packet);
            if (send_length)
            {
               if (comms_usb_port->TransmitCommand(send_packet, send_length))
               {
                  Sleep(5);
                  if ((capture_is_calibrated() || !capture_from_tonometer()) && (start_cmd == COMMS_CMD_PWM_START))
                  {
                     send_length = comms_build_packet(COMMS_CMD_REQUEST_PWM_CALIBRATE_IP, send_packet);
                     if (send_length)
                     {
                        comms_usb_port->TransmitCommand(send_packet, send_length);
                        Sleep(5);
                     }
                  }
                  if (((start_cmd == COMMS_CMD_PWV_START) ||(start_cmd == COMMS_CMD_PWA_START) || (start_cmd == COMMS_CMD_HRV_START)) && capture_do_loopback())
                  {
                     send_length = comms_build_packet(COMMS_CMD_REQUEST_LOOPBACK, send_packet);
                     if (send_length)
                     {
                        comms_usb_port->TransmitCommand(send_packet, send_length);
                        Sleep(5);
                     }
                  }
                  send_length = comms_build_packet(start_cmd, send_packet);
                  if (send_length)
                  {
                     if (comms_usb_port->TransmitCommand(send_packet, send_length))
                     {
                        started = true;
                     }
                  }
               }
            }
         }
      }
      return started;
   }

   if (comms_port)
   {
      if (comms_port->Open)
      {
         if (comms_get_ack(start_cmd))
         {
            if (((start_cmd == COMMS_CMD_PWV_START) ||(start_cmd == COMMS_CMD_PWA_START) || (start_cmd == COMMS_CMD_HRV_START)) && capture_do_loopback())
            {
               comms_get_ack(COMMS_CMD_REQUEST_LOOPBACK);
            }
            (void)comms_packet_setup(start_cmd);
            send_length = comms_build_packet(start_cmd, send_packet);
            if (send_length)
            {
               comms_port->FlushInBuffer();
               comms_port->PutBlock(send_packet, send_length);
               comms_data_packet->Enabled = true;
               started = true;
            }
         }
      }
   }
   return (started);
}

void comms_stop(void)
{
   UINT8          send_packet[COMMS_CMD_MAX_SEND_LEN];
   UCOUNT         send_length;
   COMMS_ID_TYPE  port_id;

   // PM V9
   // This prevents the freezing problem at the end of capture screens
   comms_data_packet->OnPacket = NULL;
   
   port_id = config_get_comms_port();
   
   if (port_id == COMMS_PORT_SIMULATE)
   {
      comms_simulation_stop();
      return;
   }
   else if (port_id == COMMS_PORT_USB)
   {
      if (comms_usb_port)
      {
         for (int i = 0; i < COMMS_CMD_MAX_SEND_LEN; i++)
         {
            send_packet[i] = 0;
         }
         send_length = comms_build_packet(COMMS_CMD_CAPTURE_STOP,
                                          send_packet);
         comms_usb_port->TransmitCommand(send_packet, send_length);
         Sleep(5);
         comms_usb_stop_thread();
         comms_usb_port->Stop();
      }
      return;
   }


         
   if (comms_port)
   {
      if (comms_port->Open)
      {
         comms_data_packet->Enabled = false;

         // If the port is still available
         if (comms_port_exists())
         {
            comms_port->FlushInBuffer();
            send_length = comms_build_packet(COMMS_CMD_CAPTURE_STOP,
                                          send_packet);
            comms_port->PutBlock(send_packet, send_length);
         }
      }
   }
}

bool comms_packet_setup(COMMS_COMMAND_TYPE cmd_id)
{
   switch (cmd_id)
   {
      case COMMS_CMD_PWA_START:
      case COMMS_CMD_PWM_START:
         comms_data_packet->AutoEnable = false;
         comms_data_packet->Enabled = false;

         if ((comms_emod == COMMS_OLD_MODULE) ||
             (comms_emod == COMMS_MM3_MODULE) ||
             (comms_emod == COMMS_EM3_MODULE))
         {
            if (comms_emod == COMMS_OLD_MODULE)
            {
               comms_data_packet->StartCond = scString;
               comms_data_packet->StartString = COMMS_PACKET_OLD_SYNCH;
               comms_data_packet->EndCond << ecPacketSize;
               comms_data_packet->PacketSize = COMMS_PACKET_OLD_PWA_LEN;
               comms_data_packet->IgnoreCase = true;
               comms_data_packet->IncludeStrings = true;
            }
            else
            {
               comms_data_packet->StartCond = scAnyData;
               comms_data_packet->StartString = NULL;
               comms_data_packet->EndCond << ecPacketSize;
               if (comms_emod == COMMS_MM3_MODULE)
               {
                  comms_data_packet->PacketSize = COMMS_PACKET_TITAN_PWA_LEN;
               }
               else
               {
                  comms_data_packet->PacketSize = COMMS_PACKET_EM3_PWA_LEN;
                  /*
                  ** PCH Sleep to allow the Tonometer circuit to power up
                  */
                  Sleep(100);
               }
               comms_data_packet->IgnoreCase = true;
               comms_data_packet->IncludeStrings = true;
            }

            comms_data_packet->TimeOut = COMMS_PACKET_BYTE_TIMEOUT;
            comms_data_packet->OnPacket = handler.pwa_data_packet_event;
            comms_data_packet->OnTimeout = handler.byte_timeout_event;
         }
         break;

      case COMMS_CMD_PWV_START:
         comms_data_packet->AutoEnable = false;
         comms_data_packet->Enabled = false;
         if ((comms_emod == COMMS_OLD_MODULE) ||
             (comms_emod == COMMS_MM3_MODULE) ||
             (comms_emod == COMMS_EM3_MODULE))
         {
            if (comms_emod == COMMS_OLD_MODULE)
            {
               comms_data_packet->StartCond = scString;
               comms_data_packet->StartString = COMMS_PACKET_OLD_SYNCH;
               comms_data_packet->EndCond << ecPacketSize;
               comms_data_packet->PacketSize = COMMS_PACKET_OLD_PWV_LEN;
               comms_data_packet->IgnoreCase = true;
               comms_data_packet->IncludeStrings = true;
            }
            else
            {
               comms_data_packet->StartCond = scAnyData;
               comms_data_packet->StartString = NULL;
               comms_data_packet->EndCond << ecPacketSize;
               if (comms_emod == COMMS_MM3_MODULE)
               {
                  comms_data_packet->PacketSize = COMMS_PACKET_TITAN_PWV_LEN;
               }
               else
               {
                  comms_data_packet->PacketSize = COMMS_PACKET_EM3_PWV_LEN;
                  /*
                  ** PCH Sleep to allow the Tonometer && ECG circuit to power up
                  */
                  Sleep(250);
               }
               comms_data_packet->IgnoreCase = true;
               comms_data_packet->IncludeStrings = true;
            }
            comms_data_packet->TimeOut = COMMS_PACKET_BYTE_TIMEOUT;
            comms_data_packet->OnPacket = handler.pwv_data_packet_event;
            comms_data_packet->OnTimeout = handler.byte_timeout_event;
         }
         break;

      case COMMS_CMD_HRV_START:
         comms_data_packet->AutoEnable = false;
         comms_data_packet->Enabled = false;
         if (comms_emod == COMMS_MM3_MODULE || comms_emod == COMMS_EM3_MODULE)
         {
            comms_data_packet->StartCond = scAnyData;
            comms_data_packet->StartString = NULL;
            comms_data_packet->EndCond << ecPacketSize;
            if (comms_emod == COMMS_MM3_MODULE)
            {
               comms_data_packet->PacketSize = COMMS_PACKET_TITAN_HRV_LEN;
            }
            else
            {
               comms_data_packet->PacketSize = COMMS_PACKET_EM3_HRV_LEN;
               /*
               ** PCH Sleep to allow the ECG circuit to power up
               */
               Sleep(100);
            }
            comms_data_packet->IgnoreCase = true;
            comms_data_packet->IncludeStrings = true;
            comms_data_packet->TimeOut = COMMS_PACKET_BYTE_TIMEOUT;
            comms_data_packet->OnPacket = handler.hrv_data_packet_event;
            comms_data_packet->OnTimeout = handler.byte_timeout_event;
         }

         break;

      default:
         break;
   }
   return (true);
}

UCOUNT comms_build_packet(COMMS_COMMAND_TYPE cmd, UINT8 *packet)
{
   UCOUNT packet_len = 0;
   switch (cmd)
   {
      case COMMS_CMD_PWA_START:
         if (comms_emod == COMMS_OLD_MODULE)
         {
            packet[0] = COMMS_PACKET_OLD_PWA_START;
            packet_len = 1;
         }
         else if (comms_emod == COMMS_MM3_MODULE || comms_emod == COMMS_USB_MODULE || comms_emod == COMMS_EM3_MODULE)
         {
            packet[0] = (UINT8)COMMS_CMDBYTE_CAPTURE_START;
            packet_len = 1;
         }
         break;

      case COMMS_CMD_PWV_START:
         if (comms_emod == COMMS_OLD_MODULE)
         {
            packet[0] = COMMS_PACKET_OLD_PWV_START;
            packet_len = 1;
         }
         else if (comms_emod == COMMS_MM3_MODULE ||
                  comms_emod == COMMS_USB_MODULE ||
                  comms_emod == COMMS_EM3_MODULE)
         {
            packet[0] = (UINT8)COMMS_CMDBYTE_CAPTURE_START;
            packet_len = 1;
         }
         break;

      case COMMS_CMD_PWM_START:
         if (comms_emod == COMMS_OLD_MODULE)
         {
            packet[0] = COMMS_PACKET_OLD_PWM_START;
            packet_len = 1;
         }
         else if (comms_emod == COMMS_MM3_MODULE  ||
                  comms_emod == COMMS_USB_MODULE ||
                  comms_emod == COMMS_EM3_MODULE)
         {
            packet[0] = (UINT8)COMMS_CMDBYTE_CAPTURE_START;
            packet_len = 1;
         }
         break;

      case COMMS_CMD_HRV_START:
         if (comms_emod == COMMS_MM3_MODULE ||
             comms_emod == COMMS_USB_MODULE ||
             comms_emod == COMMS_EM3_MODULE)
         {
            packet[0] = (UINT8)COMMS_CMDBYTE_CAPTURE_START;
            packet_len = 1;
         }
         break;

      case COMMS_CMD_EMOD_DETECT:
         if (comms_port->Baud == COMMS_PORT_BAUD_OLD)
         {
            packet[0] = COMMS_PACKET_OLD_DETECT;
            packet_len = 1;
            comms_old_detect_packet->Enabled = true;
         }
         else
         {
            packet[0] = (UINT8)COMMS_CMDBYTE_TITAN_DETECT;
            packet_len = 1;
            comms_data_packet->Enabled = false;
            comms_detect_packet->Enabled = true;
         }
         comms_rx_timer_period = COMMS_TIMER_INTERVAL;
         break;

      case COMMS_CMD_REQUEST_PWA_ACK:
      case COMMS_CMD_REQUEST_PWV_ACK:
      case COMMS_CMD_REQUEST_PWM_ACK:
      case COMMS_CMD_REQUEST_HRV_ACK:
      case COMMS_CMD_REQUEST_LOOPBACK:
         if (comms_emod == COMMS_MM3_MODULE || comms_emod == COMMS_USB_MODULE || comms_emod == COMMS_EM3_MODULE)
         {
            if (cmd == COMMS_CMD_REQUEST_PWA_ACK)
            {
               packet[0] = (UINT8)COMMS_CMDBYTE_PWA_ACK_RQST;
               packet_len = 1;
            }
            else if (cmd == COMMS_CMD_REQUEST_PWV_ACK)
            {
               packet[0] = (UINT8)COMMS_CMDBYTE_PWV_ACK_RQST;
               packet_len = 1;
            }
            else if (cmd == COMMS_CMD_REQUEST_PWM_ACK)
            {
               packet[0] = (UINT8)COMMS_CMDBYTE_PWM_ACK_RQST;
               packet_len = 1;
            }
             else if (cmd == COMMS_CMD_REQUEST_HRV_ACK)
            {
               packet[0] = (UINT8)COMMS_CMDBYTE_HRV_ACK_RQST;
               packet_len = 1;
            }
            else if (cmd == COMMS_CMD_REQUEST_LOOPBACK)
            {
               packet[0] = (UINT8)COMMS_CMDBYTE_LOOPBACK_RQST;
               packet_len = 1;
            }

            if (packet_len && ((comms_emod == COMMS_MM3_MODULE || comms_emod == COMMS_EM3_MODULE)))
            {
               comms_rx_timer_period = COMMS_ACK_TIMER_INTERVAL;
               comms_ack_packet->PacketSize = COMMS_PACKET_TITAN_ACK_LEN;
               comms_ack_packet->Enabled = true;
               comms_data_packet->Enabled = false;
            }
         }
         break;

      case COMMS_CMD_REQUEST_PWM_CALIBRATE_IP:
      case COMMS_CMD_REQUEST_PWM_CALIBRATE_OP1:
      case COMMS_CMD_REQUEST_PWM_CALIBRATE_OP2:
         if (comms_emod == COMMS_MM3_MODULE || comms_emod == COMMS_USB_MODULE)
         {
            if (cmd == COMMS_CMD_REQUEST_PWM_CALIBRATE_IP)
            {
               packet[0] = (UINT8)COMMS_CMDBYTE_PWM_CAL_IP_RQST;
               packet_len = 1;
            }
            else if (cmd == COMMS_CMD_REQUEST_PWM_CALIBRATE_OP1)
            {
               packet[0] = (UINT8)COMMS_CMDBYTE_PWM_CAL_OP1_RQST;
               packet_len = 1;
            }
            else
            {
               packet[0] = (UINT8)COMMS_CMDBYTE_PWM_CAL_OP2_RQST;
               packet_len = 1;
            }
            if (packet_len && (comms_emod == COMMS_MM3_MODULE))
            {
               comms_rx_timer_period = COMMS_CALIBRATE_TIMER_INTERVAL;
               comms_ack_packet->PacketSize = COMMS_PACKET_TITAN_PWM_CAL_LEN;
               comms_ack_packet->Enabled = true;
               comms_data_packet->Enabled = false;
            }
         }
         break;

      case COMMS_CMD_REQUEST_HWCONFIG:
         if (comms_emod == COMMS_MM3_MODULE || comms_emod == COMMS_EM3_MODULE)
         {
            packet[0] = (UINT8)COMMS_CMDBYTE_HWCONFIG_RQST;
            packet_len = 1;
            if (packet_len)
            {
               comms_rx_timer_period = COMMS_ACK_TIMER_INTERVAL;
               comms_ack_packet->PacketSize = COMMS_PACKET_TITAN_HWCONFIG_LEN;
               comms_ack_packet->Enabled = true;
               comms_data_packet->Enabled = false;
            }
         }
         break;

      case COMMS_CMD_CAPTURE_STOP:
         if (comms_emod == COMMS_OLD_MODULE)
         {
            packet[0] = COMMS_PACKET_OLD_STOP;
            packet_len = 1;
         }
         else if (comms_emod == COMMS_MM3_MODULE  ||
                  comms_emod == COMMS_USB_MODULE ||
                  comms_emod == COMMS_EM3_MODULE)
         {
            packet[0] = (UINT8)COMMS_CMDBYTE_CAPTURE_STOP;
            packet_len = 1;
         }
         break;
      default:
         break;
   }
   return (packet_len);
}

void comms_send_event_mark(void)
{
   UINT16  event_marker_data[2];

   event_marker_data[0] = 4000;
   event_marker_data[1] = 4000;

   comms_send(event_marker_data, 2);
}

void comms_send(UINT16 *send_data, UCOUNT send_length)
{
   UINT8          high1_byte;
   UINT8          low_byte;
   UINT8          high2_byte;
   int            i, j;
   COMMS_ID_TYPE  port_id;

   port_id = config_get_comms_port();

   // Only send data to the usb and titan modules when real data is being captured
   if (port_id != COMMS_PORT_SIMULATE)
   {
      if (comms_emod == COMMS_MM3_MODULE)
      {
         if (send_length)
         {
            i = 0;
            j = 0;
            while (j < send_length)
            {
               high1_byte = (UINT8)(SCOR_HIGH(send_data[j]));
               low_byte = (UINT8)(SCOR_LOW(send_data[j]));

               comms_send_packet[i] = low_byte;
               ++i;
               ++j;
               high2_byte = (UINT8)(SCOR_HIGH(send_data[j]));
               low_byte = (UINT8)(SCOR_LOW(send_data[j]));
               comms_send_packet[i] = (((high1_byte << 4) & 0xF0) | (high2_byte & 0x0F));
               ++i;
               comms_send_packet[i] = low_byte;
               ++j;
            }
            ++i;
            comms_send_packet[i] = (UINT8)COMMS_CMDBYTE_CHECK_OK;
            ++i;
            comms_send_packet[i] = 0xe0;
            if (comms_send_packet[0] == (UINT8)COMMS_CMDBYTE_CAPTURE_STOP)
            {
               comms_send_packet[0] = comms_send_packet[0] + 1;
            }
            comms_port->PutBlock(comms_send_packet, i + 1);
         }
      }
      else if (comms_emod == COMMS_USB_MODULE)
      {
         ++comms_usb_tx_counter;
         if (comms_usb_tx_counter == 1)
         {
            for (i = 0; i < COMMS_CMD_MAX_SEND_LEN; i++)
            {
               comms_send_packet[i] = 0;
            }
         }
         if (send_length)
         {
            i = (comms_usb_tx_counter * 4) - 4;
            j = 0;
            while (j < send_length)
            {
               high1_byte = (UINT8)(SCOR_HIGH(send_data[j]));
               low_byte = (UINT8)(SCOR_LOW(send_data[j]));

               comms_send_packet[i] = high1_byte;
               ++i;
               comms_send_packet[i] = low_byte;
               ++i;
               ++j;
            }

            if (comms_usb_tx_counter >= 4)
            {
               comms_usb_tx_counter = 0;
               comms_usb_port->Transmit(comms_send_packet);
            }
         }
      }
   }
}

void comms_send_parameter(INT8 *send_data, UCOUNT send_length)
{
   int            i;
   COMMS_ID_TYPE  port_id;
   INT8           checkSum;

   if (send_length)
   {
      i = 0;
      checkSum = 0;
      while (i < send_length)
      {
         comms_parameter_packet[i] = send_data[i];
         checkSum += send_data[i];
         ++i;
      }
      comms_parameter_packet[i] = checkSum;
      ++i;
      comms_second_port->PutBlock(comms_parameter_packet, i);
   }
}

void comms_set_error(COMMS_ERROR_TYPE error)
{
   int error_num;
   comms_error = error;

   switch (comms_error)
   {
      case COMMS_ERROR_BYTE_TIMEOUT:
         error_num = MSG_COMMS_BYTE_TIMEOUT;
         break;
      case COMMS_ERROR_PACKET_TIMEOUT:
         error_num = MSG_COMMS_PACKET_TIMEOUT;
         break;
      case COMMS_ERROR_PACKET_CORRUPT:
         error_num = MSG_COMMS_PACKET_CORRUPT;
         break;
      default:
         break;
   }

   if (comms_error != COMMS_ERROR_NONE)
   {
      comms_stop();
      MsgBox(TERROR, MSG_COMMS_ERROR, error_num);
   }
}

void comms_reset_error(void)
{
   comms_error = COMMS_ERROR_NONE;
}

void comms_display_error(void)
{
   int error_num = 0;

   switch (comms_error)
   {
      case COMMS_ERROR_BYTE_TIMEOUT:
         error_num = MSG_COMMS_BYTE_TIMEOUT;
         break;
      case COMMS_ERROR_PACKET_TIMEOUT:
         error_num = MSG_COMMS_PACKET_TIMEOUT;
         break;
      case COMMS_ERROR_PACKET_CORRUPT:
         error_num = MSG_COMMS_PACKET_CORRUPT;
         break;
      default:
         break;
   }

   if (comms_error != COMMS_ERROR_NONE)
   {
      MsgBox(TERROR, MSG_COMMS_ERROR, error_num);
   }
}

void comms_detect_module(void)
{
   TTimer         *dmod_timer;
   bool           baud_rates_stepped;
   long           initial_baud;
   int            nof_retries;
   UINT8          send_packet[COMMS_CMD_MAX_SEND_LEN];
   UCOUNT         send_length;
   COMMS_ID_TYPE  port_id;
   
   port_id = config_get_comms_port();

   if (port_id == COMMS_PORT_SIMULATE)
   {
      comms_module_detected = true;
      return;
   }

   if (port_id == COMMS_PORT_USB)
   {
      if (comms_usb_port != NULL)
      {
         comms_usb_device_name = "Ezusb-0";
         if (comms_usb_port->DeviceCorrect(comms_usb_device_name))
         {
            comms_module_detected = true;
            comms_emod = COMMS_USB_MODULE;
         }
         else
         {
            comms_usb_device_name = "Ezusb-1";
            if (comms_usb_port->DeviceCorrect(comms_usb_device_name))
            {
               comms_module_detected = true;
               comms_emod = COMMS_USB_MODULE;
            }
            else
            {
               comms_module_detected = false;
               comms_emod = COMMS_UNKNOWN_MODULE;
               log_write("Unrecognised USB Module: " +comms_usb_device_name);
            }
         }
        return;
      }
   }

   
   if (comms_port)
   {
      if (comms_port->Open)
      {
         initial_baud = comms_port->Baud;
         baud_rates_stepped = false;
         comms_module_detected = false;

         // If the port is still available
         if (comms_port_exists())
         {
            try
            {
            while (!baud_rates_stepped)
            {
               nof_retries = 0;
               comms_dmod_timer_expired = false;
               comms_detect_packet->Enabled = false;
               comms_old_detect_packet->Enabled = false;

               while (!comms_module_detected && nof_retries < 2)
               {
                  send_length = comms_build_packet(COMMS_CMD_EMOD_DETECT,
                                                   send_packet);
                  if (send_length)
                  {
                     if (comms_port->InBuffUsed != 0)
                     {
                        comms_port->FlushInBuffer();
                     }

                     dmod_timer = new TTimer((TComponent *)NULL);
                     dmod_timer->Enabled = false;
                     dmod_timer->Interval = comms_rx_timer_period;
                     dmod_timer->OnTimer = handler.dmod_timer_event;

                     comms_port->PutBlock(send_packet, send_length);
                     dmod_timer->Enabled = true;
                     while (!comms_dmod_timer_expired && !comms_module_detected)
                     {
                        Application->ProcessMessages();
                     }
                     dmod_timer->Enabled = false;
                     dmod_timer->OnTimer = NULL;
                     delete dmod_timer;
                  }
                  ++nof_retries;
               }
               if (comms_module_detected)
               {
                  baud_rates_stepped = true;
               }
               else
               {
                  if (comms_port->Baud == COMMS_PORT_BAUD_MM3)
                  {
                     comms_detect_packet->Enabled = false;
                     comms_port->Baud = COMMS_PORT_BAUD_OLD;
                  }
                  else if (comms_port->Baud == COMMS_PORT_BAUD_OLD)
                  {
                     comms_old_detect_packet->Enabled = false;
                     comms_port->Baud = COMMS_PORT_BAUD_EM3;
                  }
                  else if (comms_port->Baud == COMMS_PORT_BAUD_EM3)
                  {
                     comms_old_detect_packet->Enabled = false;
                     comms_port->Baud = COMMS_PORT_BAUD_MM3;
                  }
                  if (comms_port->Baud == initial_baud)
                  {
                     baud_rates_stepped = true;
                     comms_detect_packet->Enabled = false;
                     comms_old_detect_packet->Enabled = false;
                  }
                  else
                  {
                     baud_rates_stepped = false;
                  }
               }
            }
            }
            catch(Exception &exception)
            {
               MsgBox_show(TWARNING,
                           MSG_COMMS_ERROR,
                           LoadStr(MSG_COMMS_DETECT_MODULE),
                           MSG_COMMS_DETECT_MODULE, "");
               config_show();
            }
         }
      }
   }
}

bool comms_is_module_usb(void)
{
   bool is_usb = false;

   if (comms_emod == COMMS_USB_MODULE)
   {
      is_usb = true;
   }
   return is_usb;
}

bool comms_get_ack(COMMS_COMMAND_TYPE cmd_id)
{

   COMMS_ID_TYPE       port_id;
   COMMS_COMMAND_TYPE  cmd_ack_id;
   bool                rxd_ack;
   bool                check_for_hwtype = false;

   port_id = config_get_comms_port();

   if (port_id == COMMS_PORT_SIMULATE || (port_id == COMMS_PORT_USB) ||
      (comms_emod == COMMS_OLD_MODULE) || (comms_emod == COMMS_USB_MODULE))
   {
      comms_ack_received = true;
      rxd_ack = comms_ack_received;
   }
   else
   {
      rxd_ack = false;
      if (comms_port)
      {
         if (comms_port->Open)
         {
            switch (cmd_id)
            {
               case COMMS_CMD_PWA_START:
                  cmd_ack_id = COMMS_CMD_REQUEST_PWA_ACK;
                  check_for_hwtype = true;
                  break;
               case COMMS_CMD_PWV_START:
                  cmd_ack_id = COMMS_CMD_REQUEST_PWV_ACK;
                  check_for_hwtype = true;
                  break;
               case COMMS_CMD_PWM_START:
                  cmd_ack_id = COMMS_CMD_REQUEST_PWM_ACK;
                  check_for_hwtype = true;
                  break;
               case COMMS_CMD_HRV_START:
                  cmd_ack_id = COMMS_CMD_REQUEST_HRV_ACK;
                  check_for_hwtype = true;
                  break;
               case COMMS_CMD_REQUEST_LOOPBACK:
                  cmd_ack_id = COMMS_CMD_REQUEST_LOOPBACK;
                  break;
               case COMMS_CMD_REQUEST_HWCONFIG:
                  cmd_ack_id = COMMS_CMD_REQUEST_HWCONFIG;
                  break;
               default:
                  // PM CR
                  cmd_ack_id = COMMS_CMD_UNKNOWN;
                  break;
            }
            if (check_for_hwtype)
            {
               rxd_ack = comms_process_request(COMMS_CMD_REQUEST_HWCONFIG);
               if (rxd_ack)
               {
                  if (comms_emod_modes == CONFIG_NO_OPTION)
                  {
                     MsgBox_show(TWARNING,
                                 MSG_SYSTEM_ERROR,
                                 LoadStr(MSG_COMMS_MODULE_UNDEFINED),
                                 MSG_COMMS_MODULE_UNDEFINED,
                                 " Could not determine the hardware capabilities of the module.");
                     rxd_ack = false;
                  }
                  else
                  {
                     if (cmd_id == COMMS_CMD_PWV_START)
                     {
                        if (comms_emod_modes == CONFIG_PWA_OPTION ||
                            comms_emod_modes == CONFIG_HRV_OPTION ||
                            comms_emod_modes == CONFIG_PWM_ONLY_OPTION)
                        {
                           rxd_ack = false;
                        }
                     }
                     else if (cmd_id == COMMS_CMD_PWM_START)
                     {
                        if (comms_emod_modes == CONFIG_PWA_OPTION ||
                            comms_emod_modes == CONFIG_HRV_OPTION ||
                            comms_emod_modes == CONFIG_PWV_OPTION ||
                            comms_emod_modes == CONFIG_PWV_ONLY_OPTION)
                        {
                           rxd_ack = false;
                        }
                     }
                     else if (cmd_id == COMMS_CMD_HRV_START)
                     {
                        if (comms_emod_modes == CONFIG_PWA_OPTION ||
                            comms_emod_modes == CONFIG_PWV_OPTION ||
                            comms_emod_modes == CONFIG_PWV_ONLY_OPTION ||
                            comms_emod_modes == CONFIG_PWM_ONLY_OPTION ||
                            comms_emod_modes == CONFIG_STANDARD_ALL_OPTION)
                        {
                           rxd_ack = false;
                        }
                     }
                     if (!rxd_ack)
                     {
                        MsgBox_show(TWARNING,
                                    MSG_SYSTEM_ERROR,
                                    LoadStr(MSG_COMMS_MODULE_CONFLICT),
                                    MSG_COMMS_MODULE_CONFLICT,
                                    " Software does not correspond to Electronics Module settings.");
                     }
                  }
               }
               else
               {
                  // PM CR
                  comms_emod_modes = CONFIG_NO_OPTION;
                  MsgBox_show(TWARNING,
                              MSG_COMMS_ERROR,
                              LoadStr(MSG_COMMS_NO_ACK_RXD),
                              MSG_COMMS_NO_ACK_RXD,
                              LoadStr(MSG_COMMS_NO_ACK_RXD) +" (Hardware Config");
               }
            }
            else
            {
               rxd_ack = true;
            }

            if (rxd_ack)
            {
               rxd_ack = comms_process_request(cmd_ack_id);
               if (rxd_ack)
               {
                  if ((capture_is_calibrated() || !capture_from_tonometer()) && (cmd_id == COMMS_CMD_PWM_START))
                  {
                     rxd_ack = comms_process_request(COMMS_CMD_REQUEST_PWM_CALIBRATE_IP);
                     if (capture_send_output(CAPTURE_PWM_OUTPUT_CHANNEL_ONE))
                     {
                        rxd_ack = comms_process_request(COMMS_CMD_REQUEST_PWM_CALIBRATE_OP1);
                     }
                     if (capture_send_output(CAPTURE_PWM_OUTPUT_CHANNEL_TWO))
                     {
                        rxd_ack = comms_process_request(COMMS_CMD_REQUEST_PWM_CALIBRATE_OP2);
                     }
                     if (!rxd_ack)
                     {
                         MsgBox_show(TWARNING,
                                     MSG_COMMS_ERROR,
                                     LoadStr(MSG_COMMS_NO_ACK_RXD) +" (I/O Calibration)",
                                     MSG_COMMS_NO_ACK_RXD,
                                     LoadStr(MSG_COMMS_NO_ACK_RXD) +" (I/O Calibration)");
                     }
                  }
               }
               else
               {
                  MsgBox_show(TNOTIFICATION,
                              MSG_COMMS_ERROR,
                              LoadStr(MSG_COMMS_NO_ACK_RXD),
                              MSG_COMMS_NO_ACK_RXD, "");
               }
            }
         }
      }
   }
   return (rxd_ack);
}

bool comms_request_hwconfig(void)
{
   return comms_get_ack(COMMS_CMD_REQUEST_HWCONFIG);
}

bool comms_process_request(COMMS_COMMAND_TYPE cmd_rqst_id)
{
   TTimer              *ack_timer;
   UINT8               send_packet[COMMS_CMD_MAX_SEND_LEN];
   UCOUNT              send_length;
   int                 nof_retries;

   if (cmd_rqst_id == COMMS_CMD_UNKNOWN)
   {
      return false;
   }

   nof_retries = 0;
   comms_dmod_timer_expired = false;
   comms_ack_received = false;

   while (!comms_ack_received && nof_retries < 3)
   {
      send_length = comms_build_packet(cmd_rqst_id,
                                       send_packet);
      if (send_length)
      {
         if (comms_port->InBuffUsed != 0)
         {
            comms_port->FlushInBuffer();
         }
         ack_timer = new TTimer((TComponent *)NULL);
         ack_timer->Enabled = false;
         ack_timer->Interval = comms_rx_timer_period;
         ack_timer->OnTimer = handler.dmod_timer_event;
         if (comms_port->OutBuffFree > send_length)
         {
            comms_port->PutBlock(send_packet, send_length);
            ack_timer->Enabled = true;
            while (!comms_dmod_timer_expired && !comms_ack_received)
            {
               Application->ProcessMessages();
            }
            ack_timer->Enabled = false;
         }
         ack_timer->OnTimer = NULL;
         delete ack_timer;
      }
      ++nof_retries;

      if (!comms_ack_received)
      {
         comms_ack_packet->Enabled = true;
      }
   }
   comms_ack_packet->Enabled = false;
   return (comms_ack_received);
}

void comms_usb_start_thread(void)
{
   comms_usb_port->RegisterProcessHook(comms_usb_encode_data);
   /*
   if (comms_usb_rx_thread == NULL)
   {
      comms_usb_rx_thread = new COMMS_USB_DATA_EVENT_HANDLER(true);

      if (comms_usb_rx_thread)
      {
         comms_usb_rx_thread->Resume();
      }
   }
   else
   {
      comms_usb_rx_thread->Resume();
   }
   */
}

void comms_usb_stop_thread(void)
{
   comms_usb_port->ClearProcessHook();
   /*
   if (comms_usb_rx_thread)
   {
      if (comms_usb_rx_thread->Suspended == false)
      {
         comms_usb_rx_thread->Suspend();
      }
   }
   */
}

bool comms_is_module_available(void)
{
   return (comms_module_detected);
}

bool comms_is_module_12bit(void)
{
   bool           is_module_12bit = false;
   COMMS_ID_TYPE  port_id;

   port_id = config_get_comms_port();

   if (comms_emod == COMMS_MM3_MODULE || comms_emod == COMMS_USB_MODULE || comms_emod == COMMS_EM3_MODULE)
   {
      if (port_id != COMMS_PORT_SIMULATE)
      {
         is_module_12bit = true;
      }
   }
   return (is_module_12bit);
}

void comms_determine_module_type(CHAR *data_packet, UCOUNT packet_len)
{
   AnsiString  S;

   if (packet_len)
   {
      data_packet[packet_len] = '\0';
      S = data_packet;
      if (packet_len == COMMS_PACKET_OLD_DETECT_LEN)
      {
         if (S == COMMS_PACKET_OLD_DETECT_RESPONSE)
         {
            comms_module_detected = true;
            comms_emod = COMMS_OLD_MODULE;
         }
      }
      else if (packet_len == COMMS_PACKET_NEW_DETECT_LEN)
      {
         if (S == COMMS_PACKET_MM3_DETECT_RESPONSE)
         {
            comms_module_detected = true;
            comms_emod = COMMS_MM3_MODULE;
         }
         else if (S == COMMS_PACKET_EM3_DETECT_RESPONSE)
         {
            comms_module_detected = true;
            comms_emod = COMMS_EM3_MODULE;
         }
      }
   }
}

void comms_decode_hwconfig(UINT8 cfg_byte)
{
   switch (cfg_byte)
   {
      case 0x00:
        comms_emod_modes = CONFIG_NO_OPTION;
        comms_emod_modes_string = CONFIG_NO_OPTION_STRING;
        break;
      case 0x01:
        comms_emod_modes = CONFIG_PWA_OPTION;
        comms_emod_modes_string = CONFIG_PWA_OPTION_STRING;
        break;
      case 0x03:
         comms_emod_modes = CONFIG_PWV_OPTION;
         comms_emod_modes_string = CONFIG_PWV_OPTION_STRING;
         break;
      case 0x05:
         comms_emod_modes = CONFIG_PWM_OPTION;
         comms_emod_modes_string = CONFIG_PWM_OPTION_STRING;
         break;
      case 0x07:
         comms_emod_modes = CONFIG_STANDARD_ALL_OPTION;
         comms_emod_modes_string = CONFIG_STANDARD_ALL_OPTION_STRING;
         break;
      case 0x09:
         comms_emod_modes = CONFIG_HRV_OPTION;
         comms_emod_modes_string = CONFIG_HRV_OPTION_STRING;
         break;
      case 0x0F:
      case 0x77:
         comms_emod_modes = CONFIG_EXTENDED_ALL_OPTION;
         comms_emod_modes_string = CONFIG_EXTENDED_ALL_OPTION_STRING;
         break;
      default:
         comms_emod_modes = CONFIG_NO_OPTION;
         comms_emod_modes_string = CONFIG_NO_OPTION_STRING;
         break;
   }
}

String comms_get_modes_string(void)
{
   return comms_emod_modes_string;
}

String comms_get_emod_string(void)
{
   switch (comms_emod)
   {
      case COMMS_UNKNOWN_MODULE:
         comms_emod_string = COMMS_UNKNOWN_MODULE_STRING;
         break;
      case COMMS_OLD_MODULE:
         comms_emod_string = COMMS_OLD_MODULE_STRING;
         break;
      case COMMS_MM3_MODULE:
         comms_emod_string = COMMS_MM3_MODULE_STRING;
         break;
      case COMMS_USB_MODULE:
         comms_emod_string = COMMS_USB_MODULE_STRING;
         break;
      case COMMS_EM3_MODULE:
         comms_emod_string = COMMS_EM3_MODULE_STRING;
         break;
      case COMMS_MM4_MODULE:
         comms_emod_string = COMMS_MM4_MODULE_STRING;
         break;
      default:
         comms_emod_string = COMMS_UNKNOWN_MODULE_STRING;
         break;
   }
   return comms_emod_string;
}

COMMS_FOOTSWITCH_STATUS_TYPE comms_get_footswitch_status(void)
{
   COMMS_FOOTSWITCH_STATUS_TYPE  ret_status;

   ret_status = comms_footswitch_status;
   comms_footswitch_status = COMMS_FOOTSWITCH_NONE;

   return (ret_status);
}

void comms_reset_footswitch(void)
{
   comms_footswitch_status = COMMS_FOOTSWITCH_NONE;
}

bool comms_decode_check_byte(UINT8 check_byte)
{
   bool status = false;

   //comms_footswitch_status = COMMS_FOOTSWITCH_NONE;

   switch (check_byte)
   {
      case (UINT8)COMMS_CMDBYTE_CHECK_OK:
         status = true;
         break;
      case (UINT8)COMMS_CMDBYTE_CHECK_FSWITCH1:
         status = true;
         comms_footswitch_status = COMMS_FOOTSWITCH_ONE;
         break;
      case (UINT8)COMMS_CMDBYTE_CHECK_FSWITCH2:
         comms_footswitch_status = COMMS_FOOTSWITCH_TWO;
         status = true;
         break;
      case (UINT8)COMMS_CMDBYTE_CHECK_CRC_ERROR:
         break;
      case (UINT8)COMMS_CMDBYTE_CHECK_HW_ERROR:
         break;
      default:
         break;
   }
   return (status);
}

UINT8 comms_calculate_crc(UINT8 *data_packet, UCOUNT packet_len)
{
   int     i, j;
   UINT16  check_sum;
   UINT8   crc8;
   UINT8   byte;

   check_sum = 0;
   for (i = 0; i < packet_len; i++)
   {
      byte = data_packet[i];
      for (j = 1; j <= 8; j++)
      {
         if ((byte & 1) != (check_sum & 1))
         {
            check_sum = (UINT16)((check_sum / 2) ^ 0xa001);
         }
         else
         {
            check_sum = (UINT16)(check_sum / 2);
         }
         byte = (UINT8)(byte / 2);
      }
   }
   crc8 = (UINT8)(check_sum & 0x00FF);
   return crc8;
}

bool comms_simulation_start(void)
{
   bool started = false;

   if (comms_simulation_timer != NULL)
   {
      if (capture_simulation_start())
      {
         comms_simulation_timer->Enabled = true;
         comms_simulation_timer->Interval = 100;
         started = true;
      }
   }
   return started;
}

void comms_simulation_stop(void)
{
   if (comms_simulation_timer != NULL)
   {
      comms_simulation_timer->Enabled = false;
      capture_simulation_stop();
   }
}

void comms_usb_encode_data(void)
{
   unsigned char usb_rx_buff[BULK_TRANSFER_SIZE];
   ULONG         bytes_rxd;
   INT16         sample_ecg[8];
   INT16         sample_ton;
   MEAS_ID_TYPE  meas_id;
   int           i, j, loop_counter;

   if (comms_usb_port != NULL)
   {
      meas_id = capture_get_current();
      if (comms_usb_port->IsDataFlow() && comms_usb_port->IsDeviceConnected())
      {
         memset(usb_rx_buff, 0, BULK_TRANSFER_SIZE);
         bytes_rxd = comms_usb_port->Receive(usb_rx_buff);
         if (bytes_rxd)
         {
            switch (meas_id)
            {
               case MEAS_PWA_ID:
               case MEAS_PWM_ID:
                  if (bytes_rxd == 16 || bytes_rxd == 64)
                  {
                     if (usb_rx_buff[0] != 0xFF)
                     {
                        loop_counter = 1;
                        if (bytes_rxd == 64)
                        {
                           loop_counter = 4;
                        }
                        j = 0;
                        while (j < loop_counter)
                        {
                           sample_ton = SCOR_MAKEWORD(usb_rx_buff[3 + (j * 16)], usb_rx_buff[2 + (j * 16)]);
                           capture_add_sample(sample_ton, true, false);

                           sample_ton = SCOR_MAKEWORD(usb_rx_buff[7 + (j * 16)], usb_rx_buff[6 + (j * 16)]);
                           capture_add_sample(sample_ton, true, false);

                           sample_ton = SCOR_MAKEWORD(usb_rx_buff[11 + (j * 16)], usb_rx_buff[10 + (j * 16)]);
                           capture_add_sample(sample_ton, true, false);

                           sample_ton = SCOR_MAKEWORD(usb_rx_buff[15 + (j * 16)], usb_rx_buff[14 + (j * 16)]);
                           capture_add_sample(sample_ton, true, false);
                           ++j;
                        }
                     }
                   }
                   else
                   {
                      comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
                      log_write("PWA Data Comms : " +IntToStr(usb_rx_buff[2]) +", " +IntToStr(usb_rx_buff[3]));
                      capture_add_sample(0, false, false);
                   }
                   bytes_rxd = 0;
                   break;

               case MEAS_PWV_ID:
                  if (bytes_rxd == 16 || bytes_rxd == 64)
                  {
                     if (usb_rx_buff[0] != 0xFF)
                     {
                        loop_counter = 1;
                        if (bytes_rxd == 64)
                        {
                           loop_counter = 4;
                        }
                        j = 0;
                        while (j < loop_counter)
                        {
                           sample_ecg[0] = SCOR_MAKEWORD(usb_rx_buff[1 + (j * 16)], usb_rx_buff[0 + (j * 16)]);
                           sample_ton = SCOR_MAKEWORD(usb_rx_buff[3 + (j * 16)], usb_rx_buff[2 + (j * 16)]);
                           capture_pwv_add_sample(sample_ton, sample_ecg[0], true, false);

                           sample_ecg[0] = SCOR_MAKEWORD(usb_rx_buff[5 + (j * 16)], usb_rx_buff[4 + (j * 16)]);
                           sample_ton = SCOR_MAKEWORD(usb_rx_buff[7 + (j * 16)], usb_rx_buff[6 + (j * 16)]);
                           capture_pwv_add_sample(sample_ton, sample_ecg[0], true, false);

                           sample_ecg[0] = SCOR_MAKEWORD(usb_rx_buff[9 + (j * 16)], usb_rx_buff[8 + (j * 16)]);
                           sample_ton = SCOR_MAKEWORD(usb_rx_buff[11 + (j * 16)], usb_rx_buff[10 + (j * 16)]);
                           capture_pwv_add_sample(sample_ton, sample_ecg[0], true, false);

                           sample_ecg[0] = SCOR_MAKEWORD(usb_rx_buff[13 + (j * 16)], usb_rx_buff[12 + (j * 16)]);
                           sample_ton = SCOR_MAKEWORD(usb_rx_buff[15 + (j * 16)], usb_rx_buff[14 + (j * 16)]);
                           capture_pwv_add_sample(sample_ton, sample_ecg[0], true, false);
                           ++j;
                        }
                     }
                   }
                   else
                   {
                      comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
                      log_write("PWV Data Comms : " +IntToStr(usb_rx_buff[2]) +", " +IntToStr(usb_rx_buff[3]));
                      capture_pwv_add_sample(0, 0, false, false);
                   }
                   bytes_rxd = 0;
                   break;
               case MEAS_HRV_ID:
                  if (bytes_rxd == 16 || bytes_rxd == 64)
                  {
                     if (usb_rx_buff[0] != 0xFF)
                     {
                        loop_counter = 1;
                        if (bytes_rxd == 64)
                        {
                           loop_counter = 4;
                        }
                        j = 0;
                        while (j < loop_counter)
                        {
                           i = 0;
                           while (i < 8)
                           {
                              sample_ecg[i] = SCOR_MAKEWORD(usb_rx_buff[(i + (j * 8)) * 2 + 1], usb_rx_buff[(i + (j * 8)) * 2]);
                              ++i;
                           }
                           capture_hrv_add_sample(&sample_ecg[0], 8, true, true);
                           ++j;
                        }
                     }
                  }
                  else
                  {
                     comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
                     log_write("HRV Data Comms : Bytes Rxd = " +IntToStr(bytes_rxd) +" - " +IntToStr(usb_rx_buff[0]) +", " +IntToStr(usb_rx_buff[1]));
                     capture_hrv_add_sample(&sample_ecg[0], 8, false, true);
                  }
                  break;
               default:
                  break;
            }
         }
      }
      else
      {
          switch (meas_id)
          {
             case MEAS_PWA_ID:
             case MEAS_PWM_ID:
                capture_add_sample(0, false, false);
                break;
             case MEAS_PWV_ID:
                capture_pwv_add_sample(0, 0, false, false);
                break;
             case MEAS_HRV_ID:
                capture_hrv_add_sample(&sample_ecg[0], 8, false, false);
                break;
          }
      }
   }
}
