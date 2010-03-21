//---------------------------------------------------------------------------
// USB Comms module
// File: usbComms.h
//
// Description:
//    The usbComms module contains USB transmission control functionality
//    developed for bulk transmission protocol as first available transmission
//    protocol. The module has been designed allow and accept easy attachment
//    of other handler objects for othe USB transmission protocols
//    designed in future. The module encapsulates simple communications
//    functionality available in only one object at a time.
//    The usbComms module creates main object USB_Comms and uses two supporting
//    objects to execute detailed communication algirithm,
//    the objects are following: usbProtocol and usbLoop.
//    The usbProtocol provides the base for a tranfer protocol, which must
//    implement at least the five basic members: Open, Close, Execute, Receive
//    and Transmit. The developed derived class - usbBulk can be used as an
//    architectural example of a transmission protocol class deriverd from
//    the usbProtocol.
//    The supporting objects have been designed and implemented without multiple
//    object handling fuction - operators and copy facilities are not included.
//    Objects doe not handle functional exceptions, they use fall though design
//    where a member function's performance precceds or not based on last
//    operation's result.
//
//    Communications are present to the public though USB_Comms object.
//
//    The object provides to the publiccontrol of the USB transmition
//    through the following main member functions:
//       Open  - establish connection for a device and a protocol,
//       Close - tear off connection with a device,
//       Start - start transmission,
//       Stop  - stop transmission;
//
//    transmits and receives data through members:
//       Transmit - send a databuffer to the device
//       Receive  - receive data from the device.
//
//    The object's state na be analyzed through the following members:
//       IsInitialized     - communications are open
//       IsActivated       - communications transmission is active
//       IsDataFlow        - data is being received at least for the last
//                           second period of time
//       IsDeviceConnected - communications device has not lost connection
//       IsLoopRunning     - the communications loop is not stopped
//
//    The hte object can absorb up to 1280 transmission items in each: receive
//    and trnasmit list and after data overflow, clears the lists and starts
//    collecting data again.
//
//    The object uses the usbLoop to continuously lookup USB transmission,
//    the usbLoop does not perform any side-effect functionality and can accept
//    custom functionality to be performed during transmission executions
//    through publically available function hook.
//
//    The object describes it's simple error conditions thorugh lastErro access
//    and data members.
//---------------------------------------------------------------------------
#ifndef __USB_COMMS_H__
#define __USB_COMMS_H__

// System declarations
#include <Classes.hpp>
#include <winbase.h>
#include <devioctl.h>
#include <ezusbsys.h>
#include <stdio.h>
#include <time.h>

// Driver declarations
#include "usbDriver.h"

// Communications declarations
#define COMMS_USB_MAX_DEVICE_NUM     32
#define USB_COMMS_ACTIVE_WAIT        (INT32)2

// Communications error code declarations
typedef enum _USB_Error
{
   USB_OK,
   USB_INVALID_PROTOCOL_ID,
   USB_PROTOCOL_CREATE_FAILED,
   USB_PROTOCOL_OPEN_FAILED,
   USB_TRANSMISSION_NOT_ACTIVE,
   USB_COMMUICATIONS_NOT_INITIALIZED,
   USB_DEVICE_NOT_PRESENT,
   USB_PARAMETER_POINTER_NULL
} USB_Error;

// Communications custom functionality hook declaration
typedef void (*functionHook)(void);

// USB protocol type declarations
typedef enum _USB_ProtocolType
{
   invalid,
   bulkTransfer,
   interruptTransfer,
   isochronusTransfer,
   controlTransfer
} USB_ProtocolType;

// USB Bulk protocol definitions
#define MAX_BULK_COUNT               640
#define BULK_TRANSFER_SIZE           64
#define IN_PIPE_INDEX                8
#define OUT_PIPE_CMD_INDEX           3
#define OUT_PIPE_DATA_INDEX          1
#define USB_TIMEOUT_SLOT_SECONDS     10

// Custom device signature definitions
#define USB_PRODUCT_EZUSB1_ID        (USHORT) 0x1002
#define USB_PRODUCT_EZUSB2_ID        (USHORT) 0x2131
#define USB_VENDOR_ID                (USHORT) 0x0547

// Device signature holder
typedef struct _USB_ProductIDs
{
   USHORT  idVendor;
   USHORT  idProduct;
} USB_ProductIDs;

// Forward declaration for protocol classes
class USB_Comms;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Protocol handler base class.
// This class holds basic protocol data and provides functional interface
// for derrived protocol classes.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class usbProtocol
{
public:

   // Object construction
   __fastcall      usbProtocol(USB_ProtocolType protocolTypeId,
                               USB_Comms &protocolComms,
                               bool debug)
                     : protocolType(protocolTypeId),
                       comms(protocolComms),
                       hReadDevice(NULL),
                       hWriteDevice(NULL),
                       hControlDevice(NULL),
                       debugger(debug) {}

   // Object destruction
   __fastcall      virtual ~usbProtocol() {}

   // Intialization member, must be overryden by derived class
   virtual bool Open() = 0;

   // De-intialization, must be overryden by derived class
   virtual bool Close() = 0;

   // Performance member, must be overryden by derived class
   virtual bool Execute() = 0;

   // Transmisssion receive member, must be overidden by derived class
   virtual bool Receive(void *data) = 0;

   // Transmisssion transmit member, must be overidden by derived class
   virtual bool Transmit(void *data) = 0;

   // Transmisssion transmit member, must be overidden by derived class
   virtual bool TransmitCommand(BYTE *txdata, UCOUNT txlen) = 0;

   // Current set transmission protocol type access member
   USB_ProtocolType GetType()
   {
      return protocolType;
   }

   ULONG GetTransferredBytes()
   {
      return bytes;
   }

protected:
   // Protocol signature
   USB_ProtocolType protocolType;

   // Device access handles

   HANDLE             hReadDevice;
   HANDLE             hWriteDevice;
   HANDLE             hControlDevice;

   // Object owner access member
   USB_Comms          &comms;

   // Transferred bytes count buffer
   ULONG              bytes;

   // Debugger request state buffer
   bool               debugger;

private:
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Bulk protocol handler class.
// This class defines the USB Bulk protocol crass inherirted from usbProtocol.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class usbBulk : public usbProtocol
{
public:
   // Object construction & destruction members
   __fastcall      usbBulk(USB_Comms &comms, bool debug = false);
   __fastcall      ~usbBulk();


      // Pipe idex buffers
   BULK_TRANSFER_CONTROL inControl;
   BULK_TRANSFER_CONTROL outControl;
   //BULK_TRANSFER_CONTROL outDataControl;

   // Read request buffer
   USB_requestBulkRead   readRequest;

   // Write request buffer
   USB_requestBulkWrite  writeRequest;

   // Data buffer memebers
   BYTE readBuffer[BULK_TRANSFER_SIZE];
   BYTE writeBuffer[BULK_TRANSFER_SIZE];

   // Pipe index access set members
   void SetInPipe(ULONG pipeNumber)
   {
      InPipe = pipeNumber;
      inControl.pipeNum = InPipe;
   }

   void SetOutPipe(ULONG pipeNumber)
   {
      OutPipe = pipeNumber;
      outControl.pipeNum = OutPipe;
   }

   // Intialization member
   bool Open();

   // De-intialization member
   bool Close();

   // Performance member
   bool Execute();

   // receive member
   bool Receive(void *data);

   // Transmisssion transmit member
   bool Transmit(void *data);

   // Immediate transmission member
   bool TransmitCommand(BYTE *txdata, UCOUNT txlen);

protected:
   ULONG              InPipe;
   ULONG              OutPipe;

   // Protocol tranfer buffer size in bytes buffer
   ULONG              transferSize;

   // USB polling event attributes
   HANDLE   USBEvent;
   DWORD    WaitStatus;
   LONG     TimeOut;
   bool     first_time;
private:

};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Communications loop class.
// This class defines the usb loop derrived from windows thread class
// implementated by Borland TThread class.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class usbLoop : public TThread
{
public:
      // Object construction & destruction members
      __fastcall      usbLoop(bool suspended, USB_Comms& comms);
      __fastcall      ~usbLoop();

      // USB loop termination member
      void __fastcall Terminate();

protected:
      // Communications functionality execution member
      void __fastcall Execute();

private:
      // Reference to owner object
      USB_Comms       &commsUSB;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Communications class accessed by communicating application.
// This class defines communications main object.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class USB_Comms
{
public :
      // Object construction & destruction members
      USB_Comms(bool debug);
      ~USB_Comms();

      // Communications module state access member
      bool IsInitialized()
      {
         return initialized;
      }

      // Transmission state access member
      bool IsActivated()
      {
          return activated;
      }

      // Data flow exists state member
      bool IsDataFlow()
      {
         return dataFlow;
      }

      // Device connected sate member
      bool IsDeviceConnected()
      {
         return deviceConnected;
      }

      // USB Loop physically running state member
      bool IsLoopRunning()
      {
         return loopRunning;
      }

      // Set loop running state
      void SetLoopRunning(bool running)
      {
         loopRunning = running;
      }

      // Device connection set access member used by protocols
      void SetDeviceConnected(bool connected)
      {
         deviceConnected = connected;
      }

      // Member assuring that USB environment contains exactly numbered
      // deviced, which carries signatures of vendor and product.
      bool DeviceCorrect(String &name);

      // Transmission setup and clear functions
      bool Open(String           *deviceName,
                USB_ProtocolType protocol,
                bool             start = false);

      void Close();

      void ResetDevice();

      // Transmission start and stop functions
      bool Start();
      bool Stop();

      // Application access to USB data functions
      bool  Transmit(VOID *data = NULL);
      ULONG Receive(VOID *data = NULL);
      bool TransmitCommand(BYTE *txdata = NULL, UCOUNT txlen = 0);

      // Custom usbLoop functionality setup and clear members
      void   RegisterProcessHook(functionHook hook)
      {
         processHook = hook;
      }

      void   ClearProcessHook()
      {
         processHook = NULL;
      }

      // USB Loop executed member to perform transmission protocol
      void __fastcall Execute();

      // USB Loop executed member to invoke custom processing if defined
      void __fastcall Process();

      // Operating System state error string retrieving member
      String GetSystemErrorText()
      {
         return String(driver.GetSystemErrorText());
      }

      // Operating System state error code member
      ULONG GetSystemErrorCode()
      {
         return GetLastError();
      }

      // Member returning module's last operation detailed result code
      USB_Error GetError()
      {
         return lastError;
      }

      // Member setting error of the last operation
      void SetError()
      {
      }

      // Current device name access member
      String GetDeviceName()
      {
         return deviceName;
      }

      // Current device name access member
      String GetProtocolType(USB_ProtocolType &type)
      {
         if(protocol != NULL)
         {
            type = protocol->GetType();
         }
         else
         {
            type = invalid;
         }
      }

      // Driver object member
      usbDriver       driver;

      // Transmission data lists
      TList           *receiveList;
      TList           *transmitList;

protected:
      // Access to USB loop function for additional flexibility
      // of transmission control member
      usbLoop *GetCommsLoop()
      {
         return commsLoop;
      }

      // USB data list clearing member, to be used during transmision
      // stop and restart operations
      void ClearLists()
      {
         if(receiveList)
         {
            receiveList->Clear();
         }

         if(transmitList)
         {
            transmitList->Clear();
         }
      }

      // Member assuring that USB environment contains a desired named device
      bool DevicePresent(String &name);

private:
      // Transmission state buffer
      bool            initialized;

      // Communications state buffer
      bool            activated;

      // Data flow state buffer
      bool            dataFlow;

      // Device connected state buffer
      bool            deviceConnected;

      // USB loop thread executing flag, set when when loop physically
      // executes at least once
      bool            loopRunning;

      // USB loop object
      usbLoop         *commsLoop;

      // Address of custom fuctionality member
      void            (*processHook)();


      // Currently accessed device name
      String          deviceName;

      // Device signatures member
      USB_ProductIDs  productIDs[2];

      // Bulk protocol object
      usbProtocol     *protocol;

      // Timer start and now stamps
      time_t          dataFlowTimeStart;
      time_t          dataFlowTimeNow;

      // Debugger state buffer
      bool            debugger;

      // Module's last operation detailed result code
      USB_Error       lastError;
};
#endif  // __USB_COMMS_H__

