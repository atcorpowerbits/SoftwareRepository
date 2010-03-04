/*
**
** Copyright (C) PWV MEDICAL PTY LTD, 1998
**
**
** FILE NAME     : COMMS\ATTRIB.H
**
** PROJECT       : S32 SWCI
**
** OBJECT        : COMMS (Communications)
**
** DESCRIPTION   : Definition of objects attributes.
**
** AUTHOR        : Peter Harpas
**
** DATE CREATED  : 19/05/98
**
*/
#ifndef COMMS_ATTRIB
#define COMMS_ATTRIB
#include <inc/std.h>
#include <config/pubtype.h>
#include "usbComms.h"

typedef enum
{
   COMMS_UNKNOWN_MODULE,
   COMMS_OLD_MODULE,  // EM2, MM2, EM1
   COMMS_MM3_MODULE,  // MM3
   COMMS_USB_MODULE,
   COMMS_EM3_MODULE,
   COMMS_MM4_MODULE    
} COMMS_EMODULE_TYPE;

typedef enum
{
   COMMS_ERROR_NONE,
   COMMS_ERROR_BYTE_TIMEOUT,
   COMMS_ERROR_PACKET_TIMEOUT,
   COMMS_ERROR_PACKET_CORRUPT,
   COMMS_ERROR_HARDWARE,
   COMMS_ERROR_CRC
} COMMS_ERROR_TYPE;

/*
class COMMS_USB_DATA_EVENT_HANDLER : public TThread
{
   private:

   protected:
      void __fastcall Execute();
      void __fastcall comms_usb_encode_data(void);

   public:
      __fastcall COMMS_USB_DATA_EVENT_HANDLER(bool CreateSuspended);
      __fastcall ~COMMS_USB_DATA_EVENT_HANDLER();
};
*/

extern COMMS_EMODULE_TYPE     comms_emod;
extern CONFIG_SYSTEM_OPTIONS  comms_emod_modes;

extern TApdComPort                   *comms_port;
extern TApdDataPacket                *comms_data_packet;
extern TApdDataPacket                *comms_ack_packet;
extern TApdDataPacket                *comms_detect_packet;
extern TApdDataPacket                *comms_old_detect_packet;
extern USB_Comms                     *comms_usb_port;
//extern COMMS_USB_DATA_EVENT_HANDLER  *comms_usb_rx_thread;
extern TTimer                        *comms_simulation_timer;
extern WORD                          comms_data_timer;
extern bool                          comms_module_detected;
extern bool                          comms_ack_received;
extern COMMS_ERROR_TYPE              comms_error;
extern COMMS_FOOTSWITCH_STATUS_TYPE  comms_footswitch_status;
extern bool                          comms_dmod_timer_expired;
extern bool                          comms_hrv_first_packet;

class COMMS_EVENT_HANDLER_CLASS
{
   public:
      void __fastcall pwa_data_packet_event(TObject  *Sender,
                                            Pointer  Data,
                                            int      Size);

      void __fastcall pwv_data_packet_event(TObject  *Sender,
                                           Pointer  Data,
                                           int      Size);

      void __fastcall hrv_data_packet_event(TObject  *Sender,
                                            Pointer  Data,
                                            int      Size);

      void __fastcall ack_packet_event(TObject  *Sender,
                                       Pointer  Data,
                                       int      Size);

      void __fastcall detect_packet_event(TObject  *Sender,
                                          Pointer  Data,
                                          int      Size);

      void __fastcall byte_timeout_event(TObject  *Sender);

      void __fastcall ack_timeout_event(TObject  *Sender);

      void __fastcall data_timeout_event(TObject *CP,
                                         WORD    TriggerHandle);

      void __fastcall simulate_data_event(TObject  *Sender);

      void __fastcall COMMS_EVENT_HANDLER_CLASS::dmod_timer_event(TObject *Sender);
};


#endif
