/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : COMMS\EVENT.CPP
**
** PROJECT       : S32 SWCI
**
** OBJECT        : COMMS (Communications)
**
** DESCRIPTION   : Implementation of objects event handling services.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 25/05/98
**
*/
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include <stdlib.h>
#include <AdPort.hpp>
#include <AdPacket.hpp>

#include <inc/std.h>
#include <meas/pubserv.h>
#include <capture/pubserv.h>
#include <comms/pubserv.h>
#include <log/pubserv.h>
#include "attrib.h"
#include "comms.h"




void __fastcall COMMS_EVENT_HANDLER_CLASS::pwa_data_packet_event(TObject  *Sender,
                                                                 Pointer  Data,
                                                                 int      Size)
{
   INT16          sample = 0;
   int            i;
   char           *raw_data;
   UINT8          sample_byte;
   bool           is_data_valid = true;
   UINT8          check_cmd_byte;
   UINT8          chksum_calc_val = 0;
   UINT8          chksum_send_val = 0;

   if (comms_emod == COMMS_OLD_MODULE)
   {
      if (Size == COMMS_PACKET_OLD_PWA_LEN)
      {
         raw_data = (char *)Data;
         sample_byte = (UINT8)raw_data[1];
         if (sample_byte & 0xF0)
         {
            comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
            is_data_valid = false;
         }
         else
         {
            sample_byte = (UINT8)((UINT8)raw_data[2] ^ 0x80);
            if ((sample_byte & 0xC0) != 0xC0)
            {
               comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
               is_data_valid = false;
            }
            if (comms_error == COMMS_ERROR_NONE)
            {
               sample = (INT16)(((((UINT16)(raw_data[1])) << 8) | ((((UINT16)(raw_data[2])) << 2) & 0xff)) >> 2);
            }
         }
         capture_add_sample(sample, is_data_valid, false);
         comms_reset_error();
         if (is_data_valid)
         {
            comms_data_packet->Enabled = true;
         }
      }
   }
   else if (comms_emod == COMMS_EM3_MODULE)
   {
      if (Size == COMMS_PACKET_EM3_PWA_LEN)
      {
         raw_data = (char *)Data;
         check_cmd_byte = (UINT8)raw_data[COMMS_PACKET_EM3_PWA_LEN - 2];
         chksum_calc_val = 0;
         if (comms_decode_check_byte(check_cmd_byte))
         {
            for (i = 0; i < (COMMS_PACKET_EM3_PWA_LEN - 2); i++)
            {
               chksum_calc_val = chksum_calc_val + (UINT8)raw_data[i];
            }
            chksum_send_val = (UINT8)raw_data[COMMS_PACKET_EM3_PWA_LEN - 1];
            if (chksum_calc_val == chksum_send_val)
            {
               is_data_valid = true;
               i = 0;
               while (is_data_valid && i < 4)
               {
                  sample = SCOR_MAKEWORD(raw_data[i * 2 + 1], raw_data[i * 2]);
                  if (!capture_add_sample(sample, is_data_valid, false))
                  {
                     is_data_valid = false;
                  }
                  ++i;
               }
            }
            else
            {
               comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
               is_data_valid = false;
               sample = 0;
               capture_add_sample(sample, is_data_valid, false);
            }
         }
         else
         {
            comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
            is_data_valid = false;
            sample = 0;
            capture_add_sample(sample, is_data_valid, false);
         }
         comms_reset_error();
         if (is_data_valid)
         {
            comms_data_packet->Enabled = true;
         }
      }
   }
   else
   {
      if (Size == COMMS_PACKET_TITAN_PWA_LEN)
      {
         raw_data = (char *)Data;
         check_cmd_byte = (UINT8)raw_data[8];
         chksum_calc_val = 0;
         if (comms_decode_check_byte(check_cmd_byte))
         {
            for (i = 0; i < 8; i++)
            {
               chksum_calc_val = chksum_calc_val + (UINT8)raw_data[i];
            }
            chksum_send_val = (UINT8)raw_data[9];

            if (chksum_calc_val == chksum_send_val)
            {
               is_data_valid = true;
               sample = raw_data[1];
               sample = (INT16)((UINT16)(sample  << 4) & 0x0F00);
               sample = sample | ((UINT16)(raw_data[0] & 0x00FF));
               if (capture_add_sample(sample, is_data_valid, false))
               {
                  sample = raw_data[3];
                  sample = (INT16)((UINT16)(sample  << 4) & 0x0F00);
                  sample = sample | ((UINT16)(raw_data[2] & 0x00FF));
                  if (capture_add_sample(sample, is_data_valid, false))
                  {
                     sample = raw_data[5];
                     sample = (INT16)((UINT16)(sample  << 4) & 0x0F00);
                     sample = sample | ((UINT16)(raw_data[4] & 0x00FF));
                     if (capture_add_sample(sample, is_data_valid, false))
                     {
                        sample = raw_data[7];
                        sample = (INT16)((UINT16)(sample  << 4) & 0x0F00);
                        sample = sample | ((UINT16)(raw_data[6] & 0x00FF));
                        capture_add_sample(sample, is_data_valid, true);
                     }
                     else
                     {
                        is_data_valid = false;
                     }
                  }
                  else
                  {
                     is_data_valid = false;
                  }
               }
               else
               {
                  is_data_valid = false;
               }
            }
            else
            {
               comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
               is_data_valid = false;
               capture_add_sample(sample, is_data_valid, false);
            }
         }
         else
         {
            comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
            is_data_valid = false;
            capture_add_sample(sample, is_data_valid, false);
         }
         comms_reset_error();
         if (is_data_valid)
         {
            comms_data_packet->Enabled = true;
         }
      }
      chksum_calc_val = 0;
   }
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::pwv_data_packet_event(TObject  *Sender,
                                                                 Pointer  Data,
                                                                 int      Size)
{
   INT16      sample_ton = 0;
   INT16      sample_ecg = 0;
   int        i = 0;
   char       *raw_data;
   UINT8      sample_byte;
   UINT8      check_cmd_byte;
   UINT8      chksum_calc_val = 0;
   UINT8      chksum_send_val = 0;
   bool       is_data_valid = true;

   if (comms_emod == COMMS_OLD_MODULE)
   {
      if (Size == COMMS_PACKET_OLD_PWV_LEN)
      {
         raw_data = (char *)Data;
         sample_byte = (UINT8)raw_data[1];
         if (sample_byte & 0xF0)
         {
            comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
            is_data_valid = false;
         }
         else
         {
            sample_byte = (UINT8)((UINT8)raw_data[2] ^ 0x80);
            if ((sample_byte & 0xC0) != 0xC0)
            {
               comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
               is_data_valid = false;
            }

            if (comms_error == COMMS_ERROR_NONE)
            {
               sample_ton = (INT16)(((((UINT16)(raw_data[1])) << 8) | ((((UINT16)(raw_data[2])) << 2) & 0xff)) >> 2);
               sample_byte = (UINT8)raw_data[3];
               if (sample_byte & 0xF0)
               {
                  comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
                  is_data_valid = false;
               }
               else
               {
                  sample_byte = (UINT8) ((UINT8)raw_data[4] ^ 0x80);
                  if ((sample_byte & 0xC0) != 0xC0)
                  {
                     comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
                     is_data_valid = false;
                  }

                  if (comms_error == COMMS_ERROR_NONE)
                  {
                     sample_ecg = (INT16)(((((UINT16)(raw_data[3])) << 8) | ((((UINT16)(raw_data[4])) << 2) & 0xff) ) >> 2);
                  }
               }
            }
         }
         capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false);
         comms_reset_error();
         if (is_data_valid)
         {
            comms_data_packet->Enabled = true;
         }
      }
   }
   else if (comms_emod == COMMS_EM3_MODULE)
   {
      if (Size == COMMS_PACKET_EM3_PWV_LEN)
      {
         raw_data = (char *)Data;
         chksum_calc_val = 0;
         check_cmd_byte = (UINT8)raw_data[COMMS_PACKET_EM3_PWV_LEN - 2];
         if (comms_decode_check_byte(check_cmd_byte))
         {
            for (i = 0; i < (COMMS_PACKET_EM3_PWV_LEN - 2); i++)
            {
               chksum_calc_val = chksum_calc_val + (UINT8)raw_data[i];
            }
            chksum_send_val = (UINT8)raw_data[COMMS_PACKET_EM3_PWV_LEN - 1];
            if (chksum_calc_val == chksum_send_val)
            {
               is_data_valid = true;
               i = 0;
               while (is_data_valid && i < 4)
               {
                  sample_ton = SCOR_MAKEWORD(raw_data[i * 4 + 1], raw_data[i * 4]);
                  sample_ecg = SCOR_MAKEWORD(raw_data[i * 4 + 3], raw_data[i * 4 + 2]);
                  if (!capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false))
                  {
                     is_data_valid = false;
                  }
                  ++i;
               }
            }
            else
            {
               comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
               is_data_valid = false;
               sample_ton = 0;
               sample_ecg = 0;
               capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false);
            }
         }
         else
         {
            comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
            is_data_valid = false;
            sample_ton = 0;
            sample_ecg = 0;
            capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false);
         }
         comms_reset_error();
         if (is_data_valid)
         {
            comms_data_packet->Enabled = true;
         }
      }
   }
   else
   {
      if (Size == COMMS_PACKET_TITAN_PWV_LEN)
      {
         raw_data = (char *)Data;
         check_cmd_byte = (UINT8)raw_data[12];
         chksum_calc_val = 0;
         if (comms_decode_check_byte(check_cmd_byte))
         {
            for (i = 0; i < 12; i++)
            {
               chksum_calc_val = chksum_calc_val + (UINT8)raw_data[i];
            }
            chksum_send_val = (UINT8)raw_data[13];
            if (chksum_calc_val == chksum_send_val)
            {
               is_data_valid = true;
               sample_ton = raw_data[1];
               sample_ton = (INT16)((UINT16)(sample_ton  << 4) & 0x0F00);
               sample_ton = sample_ton | ((UINT16)(raw_data[0] & 0x00FF));

               sample_ecg = raw_data[1];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 8) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[2] & 0x00FF));
               if (capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false))
               {
                  sample_ton = raw_data[4];
                  sample_ton = (INT16)((UINT16)(sample_ton  << 4) & 0x0F00);
                  sample_ton = sample_ton | ((UINT16)(raw_data[3] & 0x00FF));

                  sample_ecg = raw_data[4];
                  sample_ecg = (INT16)((UINT16)(sample_ecg  << 8) & 0x0F00);
                  sample_ecg = sample_ecg | ((UINT16)(raw_data[5] & 0x00FF));
                  if (capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false))
                  {
                     sample_ton = raw_data[7];
                     sample_ton = (INT16)((UINT16)(sample_ton  << 4) & 0x0F00);
                     sample_ton = sample_ton | ((UINT16)(raw_data[6] & 0x00FF));

                     sample_ecg = raw_data[7];
                     sample_ecg = (INT16)((UINT16)(sample_ecg  << 8) & 0x0F00);
                     sample_ecg = sample_ecg | ((UINT16)(raw_data[8] & 0x00FF));
                     if (capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false))
                     {
                        sample_ton = raw_data[10];
                        sample_ton = (INT16)((UINT16)(sample_ton  << 4) & 0x0F00);
                        sample_ton = sample_ton | ((UINT16)(raw_data[9] & 0x00FF));

                        sample_ecg = raw_data[10];
                        sample_ecg = (INT16)((UINT16)(sample_ecg  << 8) & 0x0F00);
                        sample_ecg = sample_ecg | ((UINT16)(raw_data[11] & 0x00FF));
                        capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, true);
                     }
                     else
                     {
                        is_data_valid = false;
                     }
                  }
                  else
                  {
                     is_data_valid = false;
                  }
               }
               else
               {
                  is_data_valid = false;
               }
            }
            else
            {
               comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
               is_data_valid = false;
               capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false);
            }
         }
         else
         {
            comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
            is_data_valid = false;
            capture_pwv_add_sample(sample_ton, sample_ecg, is_data_valid, false);
         }
         comms_reset_error();
         if (is_data_valid)
         {
            comms_data_packet->Enabled = true;
         }
      }
      chksum_calc_val = 0;
   }
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::hrv_data_packet_event(TObject  *Sender,
                                                                 Pointer  Data,
                                                                 int      Size)
{
   INT16      sample_ecg_values[8];
   INT16      sample_ecg = 0;
   char       *raw_data;
   UINT8      check_cmd_byte;
   UINT8      chksum_calc_val = 0;
   UINT8      chksum_send_val = 0;
   bool       is_data_valid = true;
   int        i = 0;
   int        j = 0;

   if (comms_emod == COMMS_MM3_MODULE)
   {
      if (Size == COMMS_PACKET_TITAN_HRV_LEN)
      {
         raw_data = (char *)Data;
         check_cmd_byte = (UINT8)raw_data[COMMS_PACKET_TITAN_HRV_LEN - 2];
         chksum_calc_val = 0;
         if (comms_decode_check_byte(check_cmd_byte))
         {
            for (i = 0; i < (COMMS_PACKET_TITAN_HRV_LEN - 2); i++)
            {
               chksum_calc_val = chksum_calc_val + (UINT8)raw_data[i];
            }
            chksum_send_val = (UINT8)raw_data[COMMS_PACKET_TITAN_HRV_LEN - 1];
            if (chksum_calc_val == chksum_send_val)
            {
               is_data_valid = true;
               sample_ecg = raw_data[1];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 4) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[0] & 0x00FF));
               sample_ecg_values[0] = sample_ecg;

               sample_ecg = raw_data[1];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 8) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[2] & 0x00FF));
               sample_ecg_values[1] = sample_ecg;

               sample_ecg = raw_data[4];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 4) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[3] & 0x00FF));
               sample_ecg_values[2] = sample_ecg;

               sample_ecg = raw_data[4];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 8) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[5] & 0x00FF));
               sample_ecg_values[3] = sample_ecg;

               sample_ecg = raw_data[7];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 4) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[6] & 0x00FF));
               sample_ecg_values[4] = sample_ecg;

               sample_ecg = raw_data[7];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 8) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[8] & 0x00FF));
               sample_ecg_values[5] = sample_ecg;

               sample_ecg = raw_data[10];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 4) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[9] & 0x00FF));
               sample_ecg_values[6] = sample_ecg;

               sample_ecg = raw_data[10];
               sample_ecg = (INT16)((UINT16)(sample_ecg  << 8) & 0x0F00);
               sample_ecg = sample_ecg | ((UINT16)(raw_data[11] & 0x00FF));
               sample_ecg_values[7] = sample_ecg;

               capture_hrv_add_sample(&sample_ecg_values[0], 8, is_data_valid, true);
            }
            else
            {
               comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
               is_data_valid = false;
               sample_ecg = 0;
               capture_hrv_add_sample(&sample_ecg, 0, is_data_valid, false);
            }
         }
         else
         {
            comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
            is_data_valid = false;
            sample_ecg = 0;
            capture_hrv_add_sample(&sample_ecg, 0, is_data_valid, false);
         }
         comms_reset_error();
         if (is_data_valid)
         {
            comms_data_packet->Enabled = true;
         }
      }
   }
   else if (comms_emod == COMMS_EM3_MODULE)
   {
      if (Size == COMMS_PACKET_EM3_HRV_LEN)
      {
         raw_data = (char *)Data;
         chksum_calc_val = 0;
         check_cmd_byte = (UINT8)raw_data[COMMS_PACKET_EM3_HRV_LEN - 2];
         if (comms_decode_check_byte(check_cmd_byte))
         {
            for (i = 0; i < (COMMS_PACKET_EM3_HRV_LEN - 2); i++)
            {
               chksum_calc_val = chksum_calc_val + (UINT8)raw_data[i];
            }
            chksum_send_val = (UINT8)raw_data[COMMS_PACKET_EM3_HRV_LEN - 1];
            if (chksum_calc_val == chksum_send_val)
            {
               is_data_valid = true;
               for (i = 0; i < 8; i++)
               {
                  sample_ecg_values[i] = SCOR_MAKEWORD(raw_data[i * 2 + 1], raw_data[i * 2]);
               }
               if (!capture_hrv_add_sample(&sample_ecg_values[0], 8, is_data_valid, true))
               {
                  is_data_valid = false;
               }
            }
            else
            {
               comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
               is_data_valid = false;
               sample_ecg = 0;
               capture_hrv_add_sample(&sample_ecg, 0, is_data_valid, false);
            }
         }
         else
         {
            comms_set_error(COMMS_ERROR_PACKET_CORRUPT);
            is_data_valid = false;
            sample_ecg = 0;
            capture_hrv_add_sample(&sample_ecg, 0, is_data_valid, false);
         }
         comms_reset_error();
         if (is_data_valid)
         {
            comms_data_packet->Enabled = true;
         }
      }
   }
   chksum_calc_val = 0;
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::detect_packet_event(TObject  *Sender,
                                                               Pointer  Data,
                                                               int      Size)
{
   AnsiString  S;
   CHAR       msg[COMMS_PACKET_OLD_DETECT_LEN + 1];

   if ((Size) && (Size <= COMMS_PACKET_OLD_DETECT_LEN))
   {
      memcpy(msg, Data, Size);
      comms_determine_module_type(msg, (UCOUNT)Size);
   }
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::ack_packet_event(TObject  *Sender,
                                                            Pointer  Data,
                                                            int      Size)
{
   char   *raw_data;
   UINT8  ack_byte;
   INT16  sample;

   if (Size)
   {
      if (Size == comms_ack_packet->PacketSize)
      {
         raw_data = (char *)Data;
         ack_byte = (UINT8)raw_data[0];
         if (Size == COMMS_PACKET_TITAN_ACK_LEN)
         {
            if (ack_byte == COMMS_CMDBYTE_PWA_ACK ||
                ack_byte == COMMS_CMDBYTE_PWV_ACK ||
                ack_byte == COMMS_CMDBYTE_PWM_ACK ||
                ack_byte == COMMS_CMDBYTE_HRV_ACK ||
                ack_byte == COMMS_CMDBYTE_LOOPBACK_ACK)
            {
               comms_ack_received = true;
            }
         }
         else if (Size == COMMS_PACKET_TITAN_PWM_CAL_LEN)
         {
            if (ack_byte == COMMS_CMDBYTE_PWM_CAL_IP_RESPONSE ||
                ack_byte == COMMS_CMDBYTE_PWM_CAL_OP1_RESPONSE ||
                ack_byte == COMMS_CMDBYTE_PWM_CAL_OP2_RESPONSE)
            {
               sample = raw_data[2];
               sample = (INT16)((UINT16)(sample << 4) & 0x0F00);
               sample = sample | ((UINT16)(raw_data[1] & 0x00FF));

               if (ack_byte == COMMS_CMDBYTE_PWM_CAL_IP_RESPONSE)
               {
                  capture_set_calibration_factor(CAPTURE_PWM_INPUT_CHANNEL, (UCOUNT)sample);
               }
               else if (ack_byte == COMMS_CMDBYTE_PWM_CAL_OP1_RESPONSE)
               {
                  capture_set_calibration_factor(CAPTURE_PWM_OUTPUT_CHANNEL_ONE, (UCOUNT)sample);
               }
               else
               {
                  capture_set_calibration_factor(CAPTURE_PWM_OUTPUT_CHANNEL_TWO, (UCOUNT)sample);
               }
               comms_ack_received = true;
            }

         }
         else if (Size == COMMS_PACKET_TITAN_HWCONFIG_LEN)
         {
            if (ack_byte == COMMS_CMDBYTE_HWCONFIG_RESPONSE)
            {
               comms_ack_received = true;
               comms_decode_hwconfig((UINT8)raw_data[1]);
            }
         }
      }
   }
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::byte_timeout_event(TObject  *Sender)
{
   MEAS_ID_TYPE meas_id;
   short int  hrv_data = 0;

   meas_id = capture_get_current();

   comms_data_packet->Enabled = false;

   comms_set_error(COMMS_ERROR_BYTE_TIMEOUT);
   switch (meas_id)
   {
      case MEAS_PWA_ID:
         capture_pwa_add_sample(0, false, false);
         break;
      case MEAS_PWV_ID:
         capture_pwv_add_sample(0, 0, false, false);
         break;
      case MEAS_PWM_ID:
         capture_pwm_add_sample(0, false, false);
         break;
      case MEAS_HRV_ID:
         capture_hrv_add_sample(&hrv_data, 0, false, false);
         break;
      case MEAS_NONE:
         break;
      default:
         break;
   }
   comms_reset_error();
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::ack_timeout_event(TObject  *Sender)
{
   comms_dmod_timer_expired = true;
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::data_timeout_event(TObject *CP,
                                                              WORD    TriggerHandle)
{
   MEAS_ID_TYPE meas_id;
   short int  hrv_data = 0;

   if (TriggerHandle == comms_data_timer)
   {
      comms_data_packet->Enabled = false;
      if (comms_port->InBuffUsed == 0)
      {
         meas_id = capture_get_current();
         comms_set_error(COMMS_ERROR_PACKET_TIMEOUT);
         switch (meas_id)
         {
            case MEAS_PWA_ID:
               capture_pwa_add_sample(0, false, false);
               break;
            case MEAS_PWV_ID:
               capture_pwv_add_sample(0, 0, false, false);
               break;
            case MEAS_PWM_ID:
               capture_pwm_add_sample(0, false, false);
               break;
            case MEAS_HRV_ID:
               capture_hrv_add_sample(&hrv_data, 0, false, false);
               break;
            case MEAS_NONE:
               break;
            default:
               break;
         }
         comms_reset_error();
      }
   }
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::dmod_timer_event(TObject *Sender)
{
   comms_dmod_timer_expired = true;
}

void __fastcall COMMS_EVENT_HANDLER_CLASS::simulate_data_event(TObject *Sender)
{
   capture_simulation_get_data();
}

/*
__fastcall COMMS_USB_DATA_EVENT_HANDLER::COMMS_USB_DATA_EVENT_HANDLER(bool CreateSuspended) :TThread(CreateSuspended)
{
   ;
}

__fastcall COMMS_USB_DATA_EVENT_HANDLER::~COMMS_USB_DATA_EVENT_HANDLER()
{
   ;
}

void __fastcall COMMS_USB_DATA_EVENT_HANDLER::comms_usb_encode_data(void)
{
   unsigned char usb_rx_buff[BULK_TRANSFER_SIZE];
   ULONG         bytes_rxd;
   INT16         sample_ecg[8];
   INT16         sample_ton;
   MEAS_ID_TYPE  meas_id;
   int           i;

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
                  if (bytes_rxd == 16)
                  {
                     if (usb_rx_buff[0] != 0xFF)
                     {
                        sample_ton = SCOR_MAKEWORD(usb_rx_buff[3], usb_rx_buff[2]);
                        capture_add_sample(sample_ton, true, false);

                        sample_ton = SCOR_MAKEWORD(usb_rx_buff[7], usb_rx_buff[6]);
                        capture_add_sample(sample_ton, true, false);

                        sample_ton = SCOR_MAKEWORD(usb_rx_buff[11], usb_rx_buff[10]);
                        capture_add_sample(sample_ton, true, false);

                        sample_ton = SCOR_MAKEWORD(usb_rx_buff[15], usb_rx_buff[14]);
                        capture_add_sample(sample_ton, true, false);


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
                  if (bytes_rxd == 16)
                  {
                     if (usb_rx_buff[0] != 0xFF)
                     {
                        sample_ecg[0] = SCOR_MAKEWORD(usb_rx_buff[1], usb_rx_buff[0]);
                        sample_ton = SCOR_MAKEWORD(usb_rx_buff[3], usb_rx_buff[2]);
                        capture_pwv_add_sample(sample_ton, sample_ecg[0], true, false);

                        sample_ecg[0] = SCOR_MAKEWORD(usb_rx_buff[5], usb_rx_buff[4]);
                        sample_ton = SCOR_MAKEWORD(usb_rx_buff[7], usb_rx_buff[6]);
                        capture_pwv_add_sample(sample_ton, sample_ecg[0], true, false);

                        sample_ecg[0] = SCOR_MAKEWORD(usb_rx_buff[9], usb_rx_buff[8]);
                        sample_ton = SCOR_MAKEWORD(usb_rx_buff[11], usb_rx_buff[10]);
                        capture_pwv_add_sample(sample_ton, sample_ecg[0], true, false);

                        sample_ecg[0] = SCOR_MAKEWORD(usb_rx_buff[13], usb_rx_buff[12]);
                        sample_ton = SCOR_MAKEWORD(usb_rx_buff[15], usb_rx_buff[14]);
                        capture_pwv_add_sample(sample_ton, sample_ecg[0], true, false);
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
                  if (bytes_rxd == 16)
                  {
                     if (usb_rx_buff[0] != 0xFF)
                     {
                        i = 0;
                        while (i < 8)
                        {
                           sample_ecg[i] = SCOR_MAKEWORD(usb_rx_buff[i * 2 + 1], usb_rx_buff[i * 2]);
                           ++i;
                        }
                        capture_hrv_add_sample(&sample_ecg[0], 8, true, true);
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

void __fastcall COMMS_USB_DATA_EVENT_HANDLER::Execute()
{
   while(!Terminated)
   {
      Synchronize(comms_usb_encode_data);
      Sleep(0);
   }
}
*/


