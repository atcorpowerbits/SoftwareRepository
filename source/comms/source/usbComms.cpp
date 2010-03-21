//---------------------------------------------------------------------------
// USB Comms module
// File: usbComms.cpp
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
// System declarations
#include <vcl.h>
#pragma hdrstop

// Module daclarations
#include <mmsystem.h>
#include <inc/std.h>
#include <log/pubserv.h>
#include "usbComms.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Bulk protocol handler class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//---------------------------------------------------------------------------
// Name:         usbBulk
//
// Parameters:   comms  - communications object reference to provide
//                        communications flags and buffers and run
//                        functionality
//               debug  - debugger active - positive to switch debugger mode on
//
// Return:       none
//
// Description:  Constructs bulk transfer protocol object
//---------------------------------------------------------------------------
__fastcall usbBulk::usbBulk(USB_Comms &usbComms, bool debug)
 : usbProtocol(bulkTransfer, usbComms, debug),
   InPipe(IN_PIPE_INDEX),
   OutPipe(OUT_PIPE_CMD_INDEX),
   transferSize(BULK_TRANSFER_SIZE)
{
   // Set Timeout to 6 milliseconds for HRV, 30 milliseconds otherwise
   TimeOut = 6;
   first_time = true;
   //USBEvent = CreateEvent(NULL, false, false, NULL);
}

//---------------------------------------------------------------------------
// Name:         ~usbBulk
//
// Parameters:   none
//
// Return:       none
//
// Description:  Constructs the bulk protocol object without initializing it.
//---------------------------------------------------------------------------
__fastcall usbBulk::~usbBulk()
{
}

//---------------------------------------------------------------------------
// Name:         Protocol
//
// Parameters:   none
//
// Return:       success flag - positive if data has been received from the
//               read request, the operation success or failure return value
//               is used by the object for dataFlow timer maintenance
//
// Description:  Performs USB transmission routine directly invoking the device
//               driver read and write requests. During perdormance, the member
//               verifies device connection state.
//---------------------------------------------------------------------------
bool usbBulk::Execute()
{
   // Assume not success result
   bool result = false;
   

   // I transmit data list contains at least one bulk
   if(comms.transmitList->Count)
   {
      // Clear the write buffer
      memset(writeBuffer, 0, transferSize);

      // Copy the head bulk from the list into the write buffer
      memcpy(writeBuffer, comms.transmitList->Items[0], transferSize);

      SetOutPipe(OUT_PIPE_DATA_INDEX);
      writeRequest.Set(&outControl, writeBuffer, transferSize);
      // Execute USB write reauest
      if(comms.driver.IssueRequest(hWriteDevice,
                                   writeRequest,
                                   &bytes, NULL))
      {
         // If bytes have been transferred
         if (bytes)
         {
            // Delete transmitted bulk from the transmit list
            comms.transmitList->Delete(0);
         }
         // Request performance successfull, device is still connected
         comms.SetDeviceConnected(true);
         result = true;
      }
      else
      {
         // Request performance failed, device is not connected
         comms.SetDeviceConnected(false);
      }
   }
   else
   {
      // Clear read buffer
      memset(readBuffer, 0, transferSize);

      //if (first_time)
      //{

         if (comms.driver.IssueRequest(hReadDevice,
                                    readRequest,
                                    &bytes, NULL))
         {
            // If bytes have been transferred

            if (bytes)
            {
               // If the receive list contains more bulks than allowed maximum
               if(comms.receiveList->Count > MAX_BULK_COUNT)
               {
                  // Clear the list discarding the bulks
                  comms.receiveList->Clear();
               }

               // Add read bulk to the receive list
               comms.receiveList->Add(readBuffer);

               // Assume success result
               result = true;
            }
            // Request performance successfull, device is still connected
            comms.SetDeviceConnected(true);
         }
         else
         {
            // Request performance failed, device is not connected
            comms.SetDeviceConnected(false);
         }
         /*first_time = false;
      }
      else
      {
         // Execute USB read request every Timeout milliseconds
         // after the first USB read
         WaitStatus = WaitForSingleObject(USBEvent, TimeOut);
         if (WaitStatus == WAIT_TIMEOUT)
         {
            if (comms.driver.IssueRequest(hReadDevice,
                                          readRequest,
                                          &bytes, NULL))
            {
               // If bytes have been transferred

               if (bytes)
               {
                  // If the receive list contains more bulks than allowed maximum
                  if(comms.receiveList->Count > MAX_BULK_COUNT)
                  {
                     // Clear the list discarding the bulks
                     comms.receiveList->Clear();
                  }

                  // Add read bulk to the receive list
                  comms.receiveList->Add(readBuffer);

                  // Assume success result
                  result = true;
               }
               // Request performance successfull, device is still connected
               comms.SetDeviceConnected(true);
            }
            else
            {
               // Request performance failed, device is not connected
               comms.SetDeviceConnected(false);
            }
         }
      } */
   }
   // Provide data received status
   return result;
}

//---------------------------------------------------------------------------
// Name:         Receive
//
// Parameters:   data - data buffer address
//
// Return:       success flag - positive if data has been retrieved from
//               communications' receive list into the parameter buffer
//
// Description:  Invoked by USB_Comms object, to retrieve the first found
//               in the receive list data item. The retieved item is deleted
//               from the list by this member
//---------------------------------------------------------------------------
bool usbBulk::Receive(void *data)
{
   // Assume not success relut
   bool result = false;

   // If the receive list contains at least one bulk
   if(comms.receiveList->Count)
   {
      // Copy the list head bulk into the data buffer
      memcpy(data, comms.receiveList->Items[0], transferSize);

      // And delete the list head
      comms.receiveList->Delete(0);

      // Assume success result
      result = true;
   }

   // Provide status
   return result;
}

//---------------------------------------------------------------------------
// Name:         Transmit
//
// Parameters:   data - data buffer address
//
// Return:       success flag - positive if space for a new item in the
//               communications' transmitList has been found and the data
//               from the parameter buffer has been appended to the list
//
// Description:  Invoked by USB_Comms object, to store in the transmit list
//               data provided data in the data buffer. The data is stored
//               in the list only if the allowed by communications maximum
//               item count has not yet been stored in the list.
//---------------------------------------------------------------------------
bool usbBulk::Transmit(void *data)
{
   // Assume success result
   bool result = true;

   // If the transmit list contains more bulks than the maximum allowed
   if(comms.transmitList->Count > MAX_BULK_COUNT)
   {  // Assume operation status failure
      result = false;
   }
   else
   {  // Add requested data to the transmit list

      comms.transmitList->Add(data);
   }

   // Provide the status
   return result;
}

bool usbBulk::TransmitCommand(BYTE *txdata, UCOUNT txlen)
{
   bool result = false;

   // Clear the write buffer
   memset(writeBuffer, 0, transferSize);

   // Copy the head bulk from the list into the write buffer
   memcpy(writeBuffer, txdata, txlen);

   SetOutPipe(OUT_PIPE_CMD_INDEX);
   writeRequest.Set(&outControl, writeBuffer, transferSize);
      // Execute USB write reauest
   if(comms.driver.IssueRequest(hWriteDevice,
                                writeRequest,
                                &bytes, NULL))
   {
      // Request performance successfull, device is still connected
      comms.SetDeviceConnected(true);
      result = true;
   }
   else
   {
      comms.SetDeviceConnected(false);
   }
   return result;
}

//---------------------------------------------------------------------------
// Name:         Open
//
// Parameters:   none
//
// Return:       success flag - positive if bulk data transfer mode protocol
//               has gained access to device
//
// Description:  Establishes connection with a device and presets data necessary
//               for driver read and write requests.
//---------------------------------------------------------------------------
bool usbBulk::Open()
{
   bool openIn;
   bool openOut;
   bool openControl;

   // If transmission is active
   if(!comms.IsActivated())
   {
      // Open device for read operations
      openIn = comms.driver.OpenDevice(&hReadDevice,
                                       comms.GetDeviceName().c_str(),
                                       GENERIC_READ,
                                       FILE_SHARE_READ);

      // Open device for command write operations
      openOut = comms.driver.OpenDevice(&hWriteDevice,
                                        comms.GetDeviceName().c_str(),
                                        GENERIC_WRITE,
                                        FILE_SHARE_WRITE);


      // Open device for conrtol operations
      openControl = comms.driver.OpenDevice(&hControlDevice,
                                            comms.GetDeviceName().c_str(),
                                            GENERIC_READ | GENERIC_WRITE,
                                            FILE_SHARE_READ | FILE_SHARE_WRITE);

      // Setup pipe index numbers
      inControl.pipeNum = InPipe;
      outControl.pipeNum = OutPipe;

      // Setup parameters for read and write requests
      readRequest.Set(&inControl, readBuffer, transferSize);
      writeRequest.Set(&outControl, writeBuffer, transferSize);

      // Provide success status if all opening device for all operations
      // was successful
      return (openIn && openOut && openControl);
   }

   // Provide feilure status if any of open operations failed
   return false;
}

//---------------------------------------------------------------------------
// Name:         Close
//
// Parameters:   none
//
// Return:       success flag -  positive if bulk data transfer mode protocol
//               has dropped access to device
//
// Description:  This member destroys connection with a device through closing
//               device's handles.
//---------------------------------------------------------------------------
bool usbBulk::Close()
{
   // Assume not success device close oparations
   bool closeIn = false;
   bool closeOut = false;
   bool closeControl = false;

   // If transmission is activated
   if(!comms.IsActivated())
   {
      // Close read handle
      closeIn = comms.driver.CloseDevice(&hReadDevice);

      // Cloase cmd write handle
      closeOut = comms.driver.CloseDevice(&hWriteDevice);

      // Close control handle
      closeControl = comms.driver.CloseDevice(&hControlDevice);
   }

   hReadDevice = hWriteDevice = hControlDevice = NULL;

   // If all operation succeeded provide success status failure otherwice
   return (closeIn && closeOut && closeControl);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Communications loop class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//---------------------------------------------------------------------------
// Name:         usbLoop
//
// Parameters:   createSuspended - if positive - create a non-running thread
//               comms           - communications object reference to provide
//                                 communications flags and buffers and run
//                                 functionality
//
// Return:       none
//
// Description:    Constructs the USB loop object and does not start the
//                 loop's performance, sets communications reference.
//---------------------------------------------------------------------------
__fastcall usbLoop::usbLoop(bool createSuspended, USB_Comms& comms)
 : TThread(createSuspended),
   commsUSB(comms)
{
}

//---------------------------------------------------------------------------
// Name:         ~usbLoop
//
// Parameters:   none
//
// Return:       none
//
// Description:  Destroys the USB loop object.
//---------------------------------------------------------------------------
__fastcall usbLoop::~usbLoop()
{
}

//---------------------------------------------------------------------------
// Name:         Execute
//
// Parameters:   none
//
// Return:       none
//
// Description:  Executes communications object's selected protocol
//               and communications object's custom function, which has been
//               designed for continuous use during transmission.
//---------------------------------------------------------------------------
void __fastcall usbLoop::Execute()
{
   while(!Terminated)
   {
      // If transmission is activated
      if(commsUSB.IsActivated())
      {
         // Invoke communications protocol execution
         Synchronize(commsUSB.Execute);
         //Sleep(0);

         // Invoke communications custom functionality execution
         Synchronize(commsUSB.Process);
         Sleep(0);
      }
      // Set loop running flag to make comms object aware of the loop's
      // performance
      commsUSB.SetLoopRunning(true);
   }
   // Clear loop running flag to make comms object aware of the loop's
   // no performance
   commsUSB.SetLoopRunning(false);
}

//---------------------------------------------------------------------------
// Name:         Terminate
//
// Parameters:   none
//
// Return:       none
//
// Description:  Destroys the USB loop's performance.
//---------------------------------------------------------------------------
void  __fastcall usbLoop::Terminate()
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Communications class accessed by communicating application
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//---------------------------------------------------------------------------
// Name:         USB_Comms
//
// Parameters:   debug - debugger mode positive for debugger on
//
// Return:       none
//
// Description:  Constructs the communications object and initializes object's
//               data. Passes the debubber mode to drive object and crates
//               transmission lists.
//---------------------------------------------------------------------------
USB_Comms::USB_Comms(bool debug)
 : initialized(false),
   activated(false),
   dataFlow(true ),
   deviceConnected(true),
   dataFlowTimeStart(0),
   dataFlowTimeNow(0),
   receiveList(NULL),
   transmitList(NULL),
   commsLoop(NULL),
   protocol(NULL),
   processHook(NULL),
   debugger(debug),
   loopRunning(false),
   lastError(USB_OK)
{
   // Setup signatures for a desired device
   productIDs[0].idProduct = USB_PRODUCT_EZUSB1_ID;
   productIDs[0].idVendor = USB_VENDOR_ID;

   productIDs[1].idProduct = USB_PRODUCT_EZUSB2_ID;
   productIDs[1].idVendor = USB_VENDOR_ID;

   // Setup driver to provide debugging information
   driver.SetDebugger(debugger);

   // Create data lists
   receiveList = new TList();
   transmitList = new TList();
}

//---------------------------------------------------------------------------
// Name:         ~USB_COMMS
//
// Parameters:   none
//
// Return:       none
//
// Description:  Destroys the communications object and transmission lists.
//---------------------------------------------------------------------------
USB_Comms::~USB_Comms()
{
   // Clear comms transmission setup
   Close();

   // Destroy data lists
   delete receiveList;
   delete transmitList;
}

//---------------------------------------------------------------------------
// Name:         DevicePresent
//
// Parameters:   name - device name
//
// Return:       status flag - positive if device with desired name exists
//               in the system
//
// Description:  Attempts to open the desired device and if successful
//               closes device after ID verification.
//---------------------------------------------------------------------------
bool USB_Comms::DevicePresent(String &name)
{
   HANDLE deviceHandle;

   // Assume not success result
   bool   result = false;

   // Assume device not present
   lastError = USB_DEVICE_NOT_PRESENT;

   // Find if device is present
   if(driver.OpenDevice(&deviceHandle,
                        name.c_str(),
                        GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE))
   {
      // Release device
      if(driver.CloseDevice(&deviceHandle))
      {
         // Set success result
         result = true;
         lastError = USB_OK;
      }
   }

   return result;
}

//---------------------------------------------------------------------------
// Name:         DeviceCorrect
//
// Parameters:   name - device name
//
// Return:       status flag - positive if device with desired name and
//               and signature IDs exists in the system
//
// Description:  Attempts to open the desired device and if successful
//               reads USB device descriptor for that device and verifies
//               device's product and vendor IDs.
//               Closes device after ID verification.
//---------------------------------------------------------------------------
bool USB_Comms::DeviceCorrect(String &name)
{
   HANDLE deviceHandle;
   ULONG  bytes;

   // Assume not success result
   bool   result = false;

   // Assume device not present
   lastError = USB_DEVICE_NOT_PRESENT;

   // Find desired device
   if(driver.OpenDevice(&deviceHandle,
                        name.c_str(),
                        GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE))

   {
      USB_DEVICE_DESCRIPTOR          descriptor;
      USB_requestGetDeviceDescriptor deviceDescriptorControl;

      // Setup retrieve descriptor driver request
      deviceDescriptorControl.Set(&descriptor);

      // Execute the request
      if(driver.IssueRequest(deviceHandle,
                             deviceDescriptorControl,
                             &bytes, NULL))
      {
        // If transmission succeeded
         if (bytes)
         {
           // Analyse device signature
            if(descriptor.idVendor == productIDs[0].idVendor
               && descriptor.idProduct == productIDs[0].idProduct)
            {
               // Assumed and found signatures are the same
               result = true;
               lastError = USB_OK;
            }
            else
            {
               if (descriptor.idVendor == productIDs[1].idVendor &&
                   descriptor.idProduct == productIDs[1].idProduct)
               {
                  // Assumed and found signatures are the same
                  result = true;
                  lastError = USB_OK;
               }
            }
         }
      }

      // Release the device
      driver.CloseDevice(&deviceHandle);
   }

   // Provide status
   return result;
}

//---------------------------------------------------------------------------
// Name:         Open
//
// Parameters:   name              - device name
//               requestedProtocol - communications protocol
//               start             - request to start automatically
//                                   the transmission after the communications
//                                   have been initialized
//
// Return:       success flag - positive if communications have been initialized
//                              and if start parameter set, transmission
//                              has been started
//
// Description:  Initializes communications object for the desired device name
//               and specified protocol. Before initializing comunications,
//               the member verifies device's name and signature IDs.
//               If device has been found, the member attempts to stop
//               transmission and and release the device to make sure,
//               that the device will be ready for new intialization.
//               Sets and initializes the desired transmission protocol and
//               if requested, tarts transmission performance for the device.
//---------------------------------------------------------------------------
bool USB_Comms::Open(String *name,
                     USB_ProtocolType requestedProtocol, bool start)
{
   // Assume not success result
   bool result = false;

   // Device must have a valid name
   if(name != NULL)
   {
      // Verify if desired device is present
      result = DevicePresent(*name);

      // The device has been found
      if(result)
      {
         // Store the device name
         deviceName = *name;

         // Clear communications
         Close();

         // Create requested protocol
         switch(requestedProtocol)
         {
            // USB Bulk transfer request
            case bulkTransfer:
               protocol = new usbBulk(*this, debugger);
               break;

            case interruptTransfer:
               // Until the usbIterrupt object is developed
               // this selection is invalid
               lastError = USB_INVALID_PROTOCOL_ID;
               break;

            case isochronusTransfer:
               // Until the usbIsochronus object is developed
               // this selection is invalid
               lastError = USB_INVALID_PROTOCOL_ID;
               break;

            case controlTransfer:
               //protocol = new usbControl(*this, debugger);
               lastError = USB_INVALID_PROTOCOL_ID;
               break;

            default:
               // Set USB error
               lastError = USB_INVALID_PROTOCOL_ID;
               break;
         }

         if(protocol != NULL)
         {  // Store result of the protocol setup
            result = protocol->Open();

            // If protocol setup failed
            if(!result)
            {
               // Destroy the protocol object
               delete protocol;
               protocol = NULL;
               lastError = USB_PROTOCOL_OPEN_FAILED;
            }
         }
         else
         {
            lastError = USB_PROTOCOL_CREATE_FAILED;
         }
      }
   }
   else
   {
      lastError =    USB_PARAMETER_POINTER_NULL;
   }

   // If communications and protocol setup successful
   if(result)
   {
      // Create USB loop
      commsLoop = new usbLoop(true, *this);

      if(commsLoop != NULL)
      {
         // Assume that communications have been initialised
         initialized = true;
         lastError = USB_OK;

         // If automatic communications start desired
         if(start)
         {
            // Start transmission
            result = Start();
         }
      }
   }

   // Provide status
   return result;
}

//---------------------------------------------------------------------------
// Name:         Close
//
// Parameters:   none
//
// Return:       success flag - positive if communications setup has
//               been destroyed
//
// Description:  Stops communications active transmission, destroys the USB loop
//               and the transmission protocol. Clears the device name.
//---------------------------------------------------------------------------
void USB_Comms::Close()
{
   // If communications are setup
   if(initialized)
   {
      // and the transmission is active
      if(activated)
      {
         // Stop the transmission
         Stop();

         // Termite USB transmission
         if(commsLoop != NULL)
         {
            commsLoop->Terminate();

            // Destroy communications loop
            delete commsLoop;
            commsLoop = NULL;
         }
      }

      // Assume that communications have been reset to prevent any transmission
      // the object is about to destroy the protocol
      initialized = false;

      // Destroy protocol object
      if(protocol != NULL)
      {
         // Clear the bulk protocol setup
         protocol->Close();
         // Destroy the protocol object
         delete protocol;
         protocol = NULL;
      }

      // Destroy device's name
      deviceName.Delete(0, deviceName.Length());
   }

   lastError = USB_OK;
}

void USB_Comms::ResetDevice()
{
   HANDLE DeviceHandle;
   ULONG  bytes;
   unsigned char setupPacket[8];
   USB_requestReset                       DeviceResetRequest;
   USB_requestGetDriverVersion            DeviceGetDriver;
   USB_requestGetConfigurationDescriptor  DeviceConfigRequest;
   USB_requestVendorRequest               DeviceVendorRequest;
   USB_requestBulkWrite          DeviceControlWrite;
   VENDOR_REQUEST_IN             vendor_rqst;
   EZUSB_DRIVER_VERSION          drv_version;
   USB_CONFIGURATION_DESCRIPTOR  cfg_desc;
   BULK_TRANSFER_CONTROL         bulk_xfer_ctrl;


   if(driver.OpenDevice(&DeviceHandle,
                        deviceName.c_str(),
                        GENERIC_READ | GENERIC_WRITE,
                        FILE_SHARE_READ | FILE_SHARE_WRITE))
   {
      /*
      DeviceGetDriver.Set(&drv_version);
      driver.IssueRequest(DeviceHandle, DeviceGetDriver, &bytes, NULL);

      DeviceConfigRequest.Set(&cfg_desc);
      driver.IssueRequest(DeviceHandle, DeviceConfigRequest, &bytes, NULL);

      bulk_xfer_ctrl.pipeNum = 0;
      setupPacket[0] = 0x40;
      setupPacket[1] = 0xA0;
      setupPacket[2] = 0x92;
      setupPacket[3] = 0x7f;
      setupPacket[4] = 0;
      setupPacket[5] = 0;
      setupPacket[6] = 1;
      setupPacket[7] = 0;
      DeviceControlWrite.Set(&bulk_xfer_ctrl, &setupPacket[0], 8);
      driver.IssueRequest(DeviceHandle, DeviceControlWrite, &bytes, NULL);
      */
      vendor_rqst.bRequest = 0xA0;
      vendor_rqst.wValue = 0x7F92;
      vendor_rqst.wIndex = 0x00;
      vendor_rqst.wLength = 0x00;
      vendor_rqst.bData = 1;
      vendor_rqst.direction = 0x00;
      DeviceVendorRequest.Set(&vendor_rqst);
      driver.IssueRequest(DeviceHandle, DeviceVendorRequest, &bytes, NULL);

      Sleep(10);
      vendor_rqst.bRequest = 0xA0;
      vendor_rqst.wValue = 0x7F92;
      vendor_rqst.wIndex = 0x00;
      vendor_rqst.wLength = 0x00;
      vendor_rqst.bData = 0;
      vendor_rqst.direction = 0x00;
      DeviceVendorRequest.Set(&vendor_rqst);
      driver.IssueRequest(DeviceHandle, DeviceVendorRequest, &bytes, NULL);
      //if (driver.IssueRequest(DeviceHandle, DeviceResetRequest, &bytes, NULL))
      //{
         // Release device
         if(driver.CloseDevice(&DeviceHandle))
         {
            ;
         }
         else
         {
            ;
         }
      //}
   }

}

//---------------------------------------------------------------------------
// Name:         Start
//
// Parameters:   none
//
// Return:       success flag - positive if transmission is running
//
// Description:  Atempts to start communications transmission only for
//               an already initialized object. This member does not perform
//               for not initialized objects. If the transmission has already
//               been started the momber does not interfere,
//               only resets data flow timer. Transmission start is executed
//               throuh resuming the USB loop's performance.
//---------------------------------------------------------------------------
bool USB_Comms::Start()
{
   // Assume not success result
   bool   result = false;

   // If communications are setup
   if(initialized)
   {
      // and transmission is not active
      if(!activated)
      {
         time_t startTime;
         time_t nowTime;

         // Resume transmission
         if(commsLoop != NULL)
         {
            commsLoop->Resume();
         }

         // Get timer base times
         startTime = nowTime = time(NULL);

         // Wait untill the loop does not start working
         do
         {
            // Stop waiting as soon as the loop is running
            if(loopRunning)
            {
               // Assume that transmission is activated
               activated = true;
               break;
            }
            // Update timer
            nowTime = time(NULL);
         } while (nowTime - startTime < USB_COMMS_ACTIVE_WAIT);
      }

      // Get stamps for data flow timer
      dataFlowTimeStart = dataFlowTimeNow = time(NULL);

      //Assume success result
      result = true;
   }
   else
   {
      lastError =    USB_COMMUICATIONS_NOT_INITIALIZED;
   }

   // Provide srtatus
   return result;
}

//---------------------------------------------------------------------------
// Name:         Stop
//
// Parameters:   none
//
// Return:       success flag - positive if transmission is stopped
//
// Description:  Atempts to stop communications transmission only for
//               an already initialized object. This member does not perform
//               for not initialized objects. If the transmission has already
//               been stopped the momber does not interfere. The member resets
//               data flow timer values to zero.
//---------------------------------------------------------------------------
bool USB_Comms::Stop()
{
   // Assume not success result
   bool result = false;

   // If communications are setup
   if(initialized)
   {
      // and the transmission is active
      if(activated)
      {
         // Deactivate transmission
         activated = false;

         // Deactivate comms loop running flag
         loopRunning = false;

         // Suspend the comms loop
         if(commsLoop != NULL)
         {
            commsLoop->Suspend();
         }

         // Clear USB data buffers
         ClearLists();
      }

      // Rest stamps for data flow timer
      dataFlowTimeStart = dataFlowTimeNow = 0;

      // Reset loop running flag
      loopRunning = false;

      // Assume success result
      result = true;
   }
   else
   {
      lastError = USB_COMMUICATIONS_NOT_INITIALIZED;
   }

   // Provide status
   return result;
}

//---------------------------------------------------------------------------
// Name:         Execute
//
// Parameters:   none
//
// Return:       none
//
// Description:  This member invokes current protocol's ExecuteProtocol member
//               nad verifies data flow timer expiry.
//---------------------------------------------------------------------------
void __fastcall USB_Comms::Execute()
{
   // Assume not success result
   bool result;

   // If the communications setup exists
   if(IsInitialized())
   {
      // For communications current protocol
      if(protocol != NULL)
      {
          result = protocol->Execute();
      }

      // If data has been received
      if(result)
      {
         // Reset timeout start time
         dataFlowTimeStart = time(NULL);
      }

      // Update timeout now time
      dataFlowTimeNow = time(NULL);

      // If elapsed time from timeStart till timeNow is more or equal
      // to timeout slot length
      if(dataFlowTimeNow - dataFlowTimeStart >= USB_TIMEOUT_SLOT_SECONDS)
      {
         // assume, that there is no dataFlow
         dataFlow = false;
      }
      else
      {
         // Assume, that dataFlow takes place
         dataFlow = true;
      }
   }
}

//---------------------------------------------------------------------------
// Name:         Process
//
// Parameters:   none
//
// Return:       none
//
// Description:  This member invokes custom communications object's
//               functionality if the processHook has been registered.
//---------------------------------------------------------------------------
void __fastcall USB_Comms::Process()
{
   // I custom functionality has been registered with communications
   if (processHook != NULL)
   {
      // execute custom function
      processHook();
   }
}

//---------------------------------------------------------------------------
// Name:         Receive
//
// Parameters:   data -
//
// Return:       success flag - positive if data has been retrieved
//
// Description:  This member invokes current transmission protocol's Receive
//               member and returns that member's return value.
//---------------------------------------------------------------------------
ULONG USB_Comms::Receive(VOID *data)
{
   // Assume not success result
   ULONG nof_bytes = 0;

   // If data buffer exists
   if (data != NULL)
   {
      if (activated)
      {
         if (protocol->Receive(data))
         {
            nof_bytes = protocol->GetTransferredBytes();
         }
      }
      else
      {
         lastError = USB_TRANSMISSION_NOT_ACTIVE;
      }
   }
   else
   {
      lastError = USB_PARAMETER_POINTER_NULL;
   }

   // Provide status
   return nof_bytes;
}

//---------------------------------------------------------------------------
// Name:         Transmit
//
// Parameters:   data
//
// Return:       success flag - positive if data has been stored
//               to be transmitted
//
// Description:  This member invokes current transmission protocol's Transmit
//               member and returns that member's return value.
//---------------------------------------------------------------------------
bool USB_Comms::Transmit(VOID *data)
{
   // Assume not success result
   bool result = false;

   // If data buffer exists
   if(data != NULL)
   {
      if(activated)
      {
         //  Write USB bulk data into the output buffer list
         result = protocol->Transmit(data);
      }
      else
      {
         lastError = USB_TRANSMISSION_NOT_ACTIVE;
      }
   }
   else
   {
      lastError = USB_PARAMETER_POINTER_NULL;
   }

   // Provide status
   return result;
}

//---------------------------------------------------------------------------
// Name:         TransmitCommand
//
// Parameters:   data
//
// Return:       success flag - positive if data has been stored
//               to be transmitted
//
// Description:  This member invokes current transmission protocol's TransmitCommand
//               member and returns that member's return value.
//---------------------------------------------------------------------------
bool USB_Comms::TransmitCommand(BYTE *txdata, UCOUNT txlen)
{
   // Assume not success result
   bool result = false;

   // If data buffer exists
   if (txdata != NULL)
   {
      if (activated)
      {
         //  Write USB bulk data into the output buffer list
         result = protocol->TransmitCommand(txdata, txlen);
      }
      else
      {
         lastError = USB_TRANSMISSION_NOT_ACTIVE;
      }
   }
   else
   {
      lastError = USB_PARAMETER_POINTER_NULL;
   }

   // Provide status
   return result;
}
