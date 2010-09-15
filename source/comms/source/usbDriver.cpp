//---------------------------------------------------------------------------
// USB Driver module
// File: usbDriver.cpp
//
// Description:
//    The usbDriver module creates interface with EZ-USB Device Driver installed
//    in the operating system environment. The module does not perform any
//    functions in the driver's functional area. The module has been designed
//    to provide convenience in opening, closing and controling EZ-USB device.
//
//    usbDriver module defines a set of classes describing IOCTL parameter
//    sequences to execute all documented IOCTL functions provided by the
//    EZ-USB device driver vendor. Each of the provided classes after it will
//    have been instanciated must be set with required parameter(s).
//    If the data object is not set before DeviceIoControl call is invoked,
//    that call will not take place, only error working will be issued.
//    The DeviceIoCOntrol call is provided in the modules class member function
//    ExecuteIOCTL. The function verifies basic quality of a data object for
//    which the control call is to be issued.
//    All control data objects are derived from ont common class:
//    usbIoControlParameters. This class if necessary can hold data content dump
//    functionality if desired. This class hold the basic data validation flag
//    and the flag is checked by the drivers device control ExecuteIOCTL member
//    function.
//
//    usbDriver module defines OpenDevice and CloseDevice member functions,
//    which accept desired device's name, and opened device's handle as their
//    parameters. Function OpenDevice expands the device name according to the
//    operating system requirement.
//
//    usbDriver module defines supporting member functions such as:
//
//    GetSystemErrorText - collects the last system error message and
//                           in debugger mode displays a message box.
//    GetDeviceStatus - collects driver current status for a desired
//                      device.
//---------------------------------------------------------------------------

// System declarations
#include <windows.h>
#include <winioctl.h>
#include <stdlib.h>
#include <stdio.h>

// Module declarations
#include <inc/std.h>
#include <ezusbsys.h>
#include "usbDriver.h"

//---------------------------------------------------------------------------
// Name:         usbDriver
//
// Parameters:   debug - debugger mode positive for debugger on
//
// Return:       none
//
// Description:  Only constructs the driver access object and does not attempt
//               to send or receive control or data requests to/from the driver.
//               Object for it's own use creates error text buffers.
//---------------------------------------------------------------------------
usbDriver::usbDriver(bool debug)
 : debugger(debug),
   systemErrorText(NULL),
   deviceControlErrorText(NULL)
{
   // Create error message text buffers
   systemErrorText = (char*) new BYTE[DEBUGGER_MESSAGE_LENGTH];
   deviceControlErrorText = (char*) new BYTE[DEBUGGER_MESSAGE_LENGTH];
}

//---------------------------------------------------------------------------
// Name:         ~usbDriver
//
// Parameters:   none
//
// Return:       none
//
// Description:  Destroys the driver access object and error text buffers.
//---------------------------------------------------------------------------
usbDriver::~usbDriver()
{
   // Destroy system error message text buffer
   if(systemErrorText)
   {
      delete [] systemErrorText;
   }

   // Destroy device error message text buffer
   if(deviceControlErrorText)
   {
      delete [] systemErrorText;
   }
}

//---------------------------------------------------------------------------
// Name:         GetSystemErrorText
//
// Parameters:   none
//
// Return:       error text message buffer member address
//
// Description:  Retrieves system error code stored for the last performed
//               operation. Retrieves the system text string message
//               appropriate for the found error code and if debugger mode
//               is switched on displays the message in Windows non-parrent
//               message box. In non-debug mode only returns the message
//               text to the caller.
//---------------------------------------------------------------------------
char *usbDriver::GetSystemErrorText()
{
   // Only in debugger mode
   if(debugger)
   {
      LPVOID lpMsgBuf;

      // Get last operating system error code and form
      // error text message for that coed
      ::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                      NULL,
                      ::GetLastError(),
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                      (LPTSTR) &lpMsgBuf,
                      0,
                      NULL);

      // displaay the message in a box
      ::MessageBox(NULL,
                   (LPCTSTR) lpMsgBuf,
                   "System Error",
                   MB_OK | MB_ICONINFORMATION);

      // Copy the last operating error text message into the messafge buffer
      ::memset(systemErrorText, '\0', DEBUGGER_MESSAGE_LENGTH);
      ::strcpy(systemErrorText, (char*) lpMsgBuf);

      // Free memory allocated by ::FormatMessage call
      ::LocalFree(lpMsgBuf);
   }

   // Return text message buffer address
   return systemErrorText;
}

//---------------------------------------------------------------------------
// Name:         OpenDevice
//
// Parameters:   hDevice       - not a valid device
//               deviceName    - array of characters
//               desiredAccess - device desired access parameter
//               sharedMode    - device shared access parameter
//
// Return:       success flag - positive if open operation succeeded
//
// Description:  Attempts to open the specified by deviceName device in mode
//               specified by desiredAccess and sharedMode. The member
//               constructs full, correct for the operating system device name.
//               To open the device, the member issues CreateDevice call.
//               If the member fails to open the desired device, returns not
//               positive and in debug mode displays operating system
//               error message. In parameter hDevice the member provides to
//               the caller the device handle.
//---------------------------------------------------------------------------
bool usbDriver::OpenDevice(HANDLE        *hDevice,
                           char          *deviceName,
                           ULONG         desiredAccess,
                           ULONG         sharedMode)
{
   char complete_device_name[1024];

   // Create the comlete legal for the operating system device name
   ::memset(complete_device_name, 0, 1024);
   ::sprintf(complete_device_name, "%s%s", "\\\\.\\", deviceName);

   // Acquire the file handle for the specified device
   *hDevice = ::CreateFile(complete_device_name,
                           desiredAccess,
                           sharedMode,
                           NULL,
                           OPEN_EXISTING,
                           0,
                           NULL);

   // If creation performance failed
   if(*hDevice == INVALID_HANDLE_VALUE)
   {
      // Display syhstem error message
      GetSystemErrorText();
      // Reswt handle
      *hDevice = NULL;
      // Assume not success result
      return (false);
   }
   else
   {
      // Assume success result
      return (true);
   }
}

//---------------------------------------------------------------------------
// Name:         CloseDevice
//
// Parameters:   hDevice - valid device
//
// Return:       status flag - positive if close operation succeeded
//
// Description:  Attempts to close the provided device if the handle
//               of the device is valid. If the operation could not succeed
//               for any reason, the member returns not success and in debugger
//               mode displays operating system error message box.
//---------------------------------------------------------------------------
bool usbDriver::CloseDevice(HANDLE *hDevice)
{
   // Assume not success result
   bool result = false;

   // If the device handle is not valid
   if(*hDevice == INVALID_HANDLE_VALUE)
   {
      // Display operating system last error message
      GetSystemErrorText();
      // Provide not success status
      return result;
   }

   // Close the requested device
   if(::CloseHandle(*hDevice))
   {
      result = true;
   }

   // If device close failed
   if(!result)
   {
      // Display operation system error message
      GetSystemErrorText();
   }

   // Provide result
   return result;
}

//---------------------------------------------------------------------------
// Name:         ExecuteRequest
//
// Parameters:   hDevice          - valid device
//               request          - driver request object reference
//               transferredBytes - address of a buffer to receive actual count
//                                  of read or written bytes
//               overlapped       - synchronisation event address
//
// Return:       status flag - positive if the issued request has been performed
//
// Description:  Issues request for the driver. If the provided request is not
//               valid (parameters have not been set), displays error Message
//               box if debugger mode is set. If request is issued successfuly
//               but it cannot be executed by driver, in debugger mode
//               this member displays operating system's error message.
//---------------------------------------------------------------------------
bool usbDriver::IssueRequest(HANDLE     hDevice,
                             usbRequest &request,
                             ULONG      *transferredBytes,
                             OVERLAPPED *overlapped)
{
   // Assume not success result
   bool result = false;

   // If request parameters are setup valid
   if(request.IsValid())
   {
      // If the issued device control request succeeded
      if(::DeviceIoControl(hDevice,
                           request.code(),
                           request.inBufferAddress(),
                           request.inBufferSize(),
                           request.outBufferAddress(),
                           request.outBufferSize(),
                           transferredBytes,
                           overlapped))
      {
         // Assume success result
         result = true;
      }
      else
      {
         // Request performance failed,
         // display operating system last error text message
         GetSystemErrorText();
      }
   }
   // In debugger more
   else if(debugger)
   {
      // Construct the device error text message,
      // to communicate request parameters not set.
      ::sprintf(deviceControlErrorText, "%s", "IO Control parameters not set!");
      // Display the message
      ::MessageBox(NULL,
                   (LPCTSTR) deviceControlErrorText,
                   "USB Control Error",
                   MB_OK | MB_ICONINFORMATION);
   }

   // Provide status
   return result;
}

//---------------------------------------------------------------------------
// Name:         GetDeviceStatus
//
// Parameters:   hDevice - device handle
//
// Return:       driver status value if device handle valid
//
// Description:  Retrieves driver last error value by issuing
//               IOCTL_EZUSB_GET_LAST_ERROR request.
//---------------------------------------------------------------------------
ULONG usbDriver::GetDeviceStatus(HANDLE hDevice)
{
   USB_requestGetDriverLastError statusControl;
   ULONG                         status;
   ULONG                         bytes;

   // Set request data parameter
   statusControl.Set(&status);

   // Issue the request to the device
   IssueRequest(hDevice, statusControl, &bytes, NULL);

   // Provide aquired status code
   return status;
}

