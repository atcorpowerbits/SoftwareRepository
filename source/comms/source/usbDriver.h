//---------------------------------------------------------------------------
// USB Driver module
// File: usbDriver.h
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
//    usbRequest. This class if necessary can hold data content dump
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
//
//---------------------------------------------------------------------------
#ifndef __USB_DRIVER_H__
#define __USB_DRIVER_H__

// Helper declarations
#define KILO_BYTE_LENGTH                1024
#define DEBUGGER_MESSAGE_LENGTH          256
#define MAX_DRIVER_NAME                   64

// Structure wrapper for an array for one kilo storage.
typedef struct _KILO_BYTE_BUFFER
{
  UCHAR   a[KILO_BYTE_LENGTH];
} KILO_BYTE_BUFFER, *PKILO_BYTE_BUFFER;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Control Data Structure Definitions
//
// The included definitions re to expand definitions provided in the
// EZ-USB device driver header file, and that is to allow all provided
// by the driver IOCTL requests to be executed, without additional declarations
// and definitions within the comms module.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Device Descriptor
typedef struct _USB_DEVICE_DESCRIPTOR
{
    UINT8   bLength;
    UINT8   bDescriptorType;
    USHORT  bcdUSB;
    UINT8   bDeviceClass;
    UINT8   bDeviceSubClass;
    UINT8   bDeviceProtocol;
    UINT8   bMaxPacketSize0;
    USHORT  idVendor;
    USHORT  idProduct;
    USHORT  bcdDevice;
    UINT8   iManufacturer;
    UINT8   iProduct;
    UINT8   iSerialNumber;
    UINT8   bNumConfigurations;
} USB_DEVICE_DESCRIPTOR, *PUSB_DEVICE_DESCRIPTOR;

// Configuration Descriptor
typedef struct _USB_CONFIGURATION_DESCRIPTOR
{
    UINT8   bLength;
    UINT8   bDescriptorType;
    USHORT  wTotalLength;
    UINT8   bNumInterfaces;
    UINT8   bConfigurationValue;
    UINT8   iConfiguration;
    UINT8   bmAttributes;
    UINT8   MaxPower;
} USB_CONFIGURATION_DESCRIPTOR, *PUSB_CONFIGURATION_DESCRIPTOR;

// Interface Descriptor
typedef struct _USB_INTERFACE_DESCRIPTOR
{
    UINT8   bLength;
    UINT8   bDescriptorType;
    UINT8   bInterfaceNumber;
    UINT8   bAlternateSetting;
    UINT8   bNumEndpoints;
    UINT8   bInterfaceClass;
    UINT8   bInterfaceSubClass;
    UINT8   bInterfaceProtocol;
    UINT8   iInterface;
} USB_INTERFFACE_DESCRIPTOR, *PUSB_INTERFACE_DESCRIPTOR;

// Endpoint Descriptor
typedef struct _USB_ENDPOINT_DESCRIPTOR
{
    UINT8   bLength;
    UINT8   bDescriptorType;
    UINT8   bEndpointAddress;
    UINT8   bmAttributes;
    USHORT  wMaxPacketSize;
    UINT8   bInterval;
} USB_ENDPOINT_DESCRIPTOR, *PUSB_ENDPOINT_DESCRIPTOR;

// Interface IN descriptor
typedef struct _USB_INTERFACE_IN
{
   UINT8    interfaceNum;
   UINT8    alternateSetting;
} USB_INTERFACE_IN, *PUSB_INTERFACE_IN;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Operation Request Data Classes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// The folowing section of this file defines classes holding a set
// of correctly fomatted parameters necessary for a single EZ-USB device
// driver ioctl request each class. All request data set classes are derived
// from the generic class usbRequest. The base class defines buffers for
// necessary parameter set as well as basic set of members:
// Clear - to reset all held parameter values, Set - to set correct parameters
// for a requesrt and IsValid - to allow verification if the request parameters
// have been set at least once.
//
// Set of request classes provides basic security for data set definition for
// a USB request. This way basic necessary data structure is proposed to the
// developer. The classes save development time.
// ExecuteRequest member accepts a set of parameters as defined by usbRequest
// class and verifies if the paramerter set is valid - set by the caller with
// initial values. This approach prevents the developer from forgetting
// to initialize request parameters. When a request is defined, initial values
// are assigned to it's parameters. After the request's set member is called,
// correct values are assigned for the request by the developer.

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Request data definition base class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class usbRequest
{
public:
   // Constructor resetting all data
   usbRequest()
    : Code(0),
      InBufferAddress(NULL),
      InBufferSize(0),
      OutBufferAddress(NULL),
      OutBufferSize(0),
      RequestValid(false) {}

   // Destructor
   ~usbRequest() {}

   // All data reset maeber, when invoked the request becomes invalid
   // and must be set again
   void Clear()
   {
      Code             = 0;
      InBufferAddress  = NULL;
      InBufferSize     = 0;
      OutBufferAddress = NULL;
      OutBufferSize    = 0;
      RequestValid     = false;
   }

   // Valid data flag access member
   bool     IsValid() { return RequestValid; }

   // Data access members
   ULONG&   code()             { return Code; }
   PVOID&   inBufferAddress()  { return InBufferAddress;}
   ULONG&   inBufferSize()     { return InBufferSize; }
   PVOID&   outBufferAddress() { return OutBufferAddress; }
   ULONG&   outBufferSize()    { return OutBufferSize; }


protected:
   // Protected constructor for derived classes to allow preset the request
   // data, when invoket sets the request state to valid
   usbRequest(ULONG requestCode,
              void  *requestInBufferAddress,
              ULONG requestInBufferSize,
              void  *requestOutBufferAddress,
              ULONG requestOutBufferSize)
    : Code(requestCode),
      InBufferAddress(requestInBufferAddress),
      InBufferSize(requestInBufferSize),
      OutBufferAddress(requestOutBufferAddress),
      OutBufferSize(requestOutBufferSize),
      RequestValid(true) {}

   // Request data set member to be used by derived classes in their overriden
   // Set members, when invoked sets the request status to valid
   void Set(ULONG requestCode,
            VOID  *requestInBufferAddress,
            ULONG requestInBufferSize,
            VOID  *requestOutBufferAddress,
            ULONG requestOutBufferSize)
   {
      Code             = requestCode;
      InBufferAddress  = requestInBufferAddress;
      InBufferSize     = requestInBufferSize;
      OutBufferAddress = requestOutBufferAddress;
      OutBufferSize    = requestOutBufferSize;
      RequestValid     = true;
   }

private:
   // Request's data isolated from any uncontrolled access
   ULONG    Code;
   PVOID    InBufferAddress;
   ULONG    InBufferSize;
   PVOID    OutBufferAddress;
   ULONG    OutBufferSize;
   bool     RequestValid;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Request data definition classes
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_GET_DEVICE_DESCRIPTOR request
////////////////////////////////////////////////////////////////////////////////
class USB_requestGetDeviceDescriptor : public usbRequest
{
public:
   USB_requestGetDeviceDescriptor() {}
   ~USB_requestGetDeviceDescriptor() {}

   void Set(USB_DEVICE_DESCRIPTOR *descriptorAddresss)
   {
      usbRequest::Set(IOCTL_Ezusb_GET_DEVICE_DESCRIPTOR,
                      descriptorAddresss,
                      sizeof(USB_DEVICE_DESCRIPTOR),
                      descriptorAddresss,
                      sizeof(USB_DEVICE_DESCRIPTOR));
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_GET_CONFIGURATION_DESCRIPTOR request
////////////////////////////////////////////////////////////////////////////////
class USB_requestGetConfigurationDescriptor : public usbRequest
{
public:
   USB_requestGetConfigurationDescriptor() {}
   ~USB_requestGetConfigurationDescriptor() {}

   void Set(USB_CONFIGURATION_DESCRIPTOR *descriptorAddress)
   {
      usbRequest::Set(IOCTL_Ezusb_GET_CONFIGURATION_DESCRIPTOR,
                      descriptorAddress,
                      sizeof(USB_CONFIGURATION_DESCRIPTOR),
                      descriptorAddress,
                      sizeof(USB_CONFIGURATION_DESCRIPTOR));
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_GET_PIPE_INFO request
////////////////////////////////////////////////////////////////////////////////
class USB_requestGetPipeInfo : public usbRequest
{
public:
   USB_requestGetPipeInfo() {}
   ~USB_requestGetPipeInfo() {}

   void Set(UINT8 *interfaceInfoAddress,
            ULONG interfaceInfoSize)
   {
      usbRequest::Set(IOCTL_Ezusb_GET_PIPE_INFO,
                      NULL,
                      0,
                      interfaceInfoAddress,
                      interfaceInfoSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_VENDOR_REQUEST request
////////////////////////////////////////////////////////////////////////////////
class USB_requestVendorRequest : public usbRequest
{
public:
   USB_requestVendorRequest() {}
   ~USB_requestVendorRequest() {}

   void Set(VENDOR_REQUEST_IN *vendorRequestInAddress)
   {
      usbRequest::Set(IOCTL_Ezusb_VENDOR_REQUEST,
                      vendorRequestInAddress,
                      sizeof(VENDOR_REQUEST_IN),
                      NULL,
                      0);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_ANCHOR_DOWNLOAD request
////////////////////////////////////////////////////////////////////////////////
class USB_requestAnchorDownload : public usbRequest
{
public:
   USB_requestAnchorDownload() {}
   ~USB_requestAnchorDownload() {}

   void Set(UINT8   *downloadBufferAddress,
            ULONG  downloadBytes)
   {
      usbRequest::Set(IOCTL_Ezusb_ANCHOR_DOWNLOAD,
                      downloadBufferAddress,
                      downloadBytes,
                      NULL,
                      0);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_RESET request
////////////////////////////////////////////////////////////////////////////////
class USB_requestReset : public usbRequest
{
public:
   USB_requestReset()
    : usbRequest(IOCTL_Ezusb_RESET,
                 NULL,
                 0,
                 NULL,
                 0) {}

   ~USB_requestReset() {}
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_RESETPIPE request
////////////////////////////////////////////////////////////////////////////////
class USB_requestResetPipe : public usbRequest
{
public:
   USB_requestResetPipe() {}
   ~USB_requestResetPipe() {}

   void Set(ULONG  *pipeNumberAddress)
   {
      usbRequest::Set(IOCTL_Ezusb_RESETPIPE,
                      pipeNumberAddress,
                      sizeof(ULONG),
                      NULL,
                      0);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_ABORTPIPE request
////////////////////////////////////////////////////////////////////////////////
class USB_requestAbortPipe : public usbRequest
{
public:
   USB_requestAbortPipe() {}
   ~USB_requestAbortPipe() {}

   void Set(ULONG  *pipeNumberAddress)
   {
      usbRequest::Set(IOCTL_Ezusb_ABORTPIPE,
                      pipeNumberAddress,
                      sizeof(ULONG),
                      NULL,
                      0);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_SETINTERFACE request
////////////////////////////////////////////////////////////////////////////////
class USB_requestSetInterface : public usbRequest
{
public:
   USB_requestSetInterface() {}
   ~USB_requestSetInterface() {}

   void Set(SET_INTERFACE_IN *setInterfaceInAddress)
   {
      usbRequest::Set(IOCTL_Ezusb_SETINTERFACE,
                      setInterfaceInAddress,
                      sizeof(SET_INTERFACE_IN),
                      NULL,
                      0);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_Ezusb_GET_STRING_DESCRIPTOR request
////////////////////////////////////////////////////////////////////////////////
class USB_requestGetStringDescriptor : public usbRequest
{
public:
   USB_requestGetStringDescriptor() {}
   ~USB_requestGetStringDescriptor() {}

   void Set(GET_STRING_DESCRIPTOR_IN *stringDescriptorIn,
            INT8                     *stringDescriptorBuffer,
            ULONG                    stringDescriptorBufferSize)
   {
      usbRequest::Set(IOCTL_Ezusb_GET_STRING_DESCRIPTOR,
                      stringDescriptorIn,
                      sizeof(GET_STRING_DESCRIPTOR_IN),
                      stringDescriptorBuffer,
                      stringDescriptorBufferSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_BULK_READ request
////////////////////////////////////////////////////////////////////////////////
class USB_requestBulkRead : public usbRequest
{
public:
   USB_requestBulkRead() {}
   ~USB_requestBulkRead() {}

   void Set(BULK_TRANSFER_CONTROL *bulkTransferControlBufferAddress,
            UINT8                 *bulkReadBufferAddress,
            ULONG                 bulkReadBufferSize)
   {
      usbRequest::Set(IOCTL_EZUSB_BULK_READ,
                      bulkTransferControlBufferAddress,
                      sizeof(BULK_TRANSFER_CONTROL),
                      bulkReadBufferAddress,
                      bulkReadBufferSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_BULK_WRITE request
////////////////////////////////////////////////////////////////////////////////
class USB_requestBulkWrite : public usbRequest
{
public:
   USB_requestBulkWrite() {}
   ~USB_requestBulkWrite() {}

   void Set(BULK_TRANSFER_CONTROL *bulkTransferControlBufferAddress,
            UINT8                 *bulkWriteBufferAddress,
            ULONG                 bulkWriteBufferSize)
   {
      usbRequest::Set(IOCTL_EZUSB_BULK_WRITE,
                      bulkTransferControlBufferAddress,
                      sizeof(BULK_TRANSFER_CONTROL),
                      bulkWriteBufferAddress,
                      bulkWriteBufferSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_ISO_READ request
////////////////////////////////////////////////////////////////////////////////
class USB_requestIsoRead_IOCTL : public usbRequest
{
public:
   USB_requestIsoRead_IOCTL() {}
   ~USB_requestIsoRead_IOCTL() {}

   void Set(ISO_TRANSFER_CONTROL *isoControlBufferAddress,
            UINT8                *isoReadBufferAddress,
            ULONG                isoReadBufferSize)
   {
      usbRequest::Set(IOCTL_EZUSB_ISO_READ,
                      isoControlBufferAddress,
                      sizeof(ISO_TRANSFER_CONTROL),
                      isoReadBufferAddress,
                      isoReadBufferSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_ISO_WRITE request
////////////////////////////////////////////////////////////////////////////////
class USB_requestIsoWrite : public usbRequest
{
public:
   USB_requestIsoWrite() {}
   ~USB_requestIsoWrite() {}

   void Set(ISO_TRANSFER_CONTROL  *isoControlBufferAddress,
            UINT8                 *isoWriteBufferAddress,
            ULONG                 isoWriteBufferSize)
   {
      usbRequest::Set(IOCTL_EZUSB_ISO_WRITE,
                      isoControlBufferAddress,
                      sizeof(ISO_TRANSFER_CONTROL),
                      isoWriteBufferAddress,
                      isoWriteBufferSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_START_ISO_STREAM request
////////////////////////////////////////////////////////////////////////////////
class USB_requestIsoStartStream : public usbRequest
{
public:
   USB_requestIsoStartStream() {}
   ~USB_requestIsoStartStream() {}

   void Set(ISO_TRANSFER_CONTROL   *isoControlBufferAddress)
   {
      usbRequest::Set(IOCTL_EZUSB_START_ISO_STREAM,
                      isoControlBufferAddress,
                      sizeof(ISO_TRANSFER_CONTROL),
                      NULL,
                      0);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_STOP_ISO_STREAM request
////////////////////////////////////////////////////////////////////////////////
class USB_requestIsoStopStream : public usbRequest
{
public:
   USB_requestIsoStopStream()
      : usbRequest(IOCTL_EZUSB_STOP_ISO_STREAM,
                   NULL,
                   0,
                   NULL,
                   0) {}

   ~USB_requestIsoStopStream() {}
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_READ_ISO_BUFFER request
////////////////////////////////////////////////////////////////////////////////
class USB_requestIsoReadBuffer : public usbRequest
{
public:
   USB_requestIsoReadBuffer() {}
   ~USB_requestIsoReadBuffer() {}

   void Set(ISO_TRANSFER_CONTROL  *isoControlBufferAddress,
            UINT8                 *isoBufferReadAddress,
            ULONG                 isoBufferReadSize)
   {
      usbRequest::Set(IOCTL_EZUSB_READ_ISO_BUFFER,
                      isoControlBufferAddress,
                      sizeof(ISO_TRANSFER_CONTROL),
                      isoBufferReadAddress,
                      isoBufferReadSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_ANCHOR_DOWNLOAD request
////////////////////////////////////////////////////////////////////////////////
class USB_requestControlledAnchorDownload : public usbRequest
{
public:
   USB_requestControlledAnchorDownload() {}
   ~USB_requestControlledAnchorDownload() {}

   void Set(ANCHOR_DOWNLOAD_CONTROL *downloadControlBufferAddress,
            UINT                    *downloadBufferAddress,
            ULONG                   downloadBufferSize)
   {
      usbRequest::Set(IOCTL_EZUSB_ANCHOR_DOWNLOAD,
                      downloadControlBufferAddress,
                      sizeof(ANCHOR_DOWNLOAD_CONTROL),
                      downloadBufferAddress,
                      downloadBufferSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_GET_DRIVER_VERSION request
////////////////////////////////////////////////////////////////////////////////
class USB_requestGetDriverVersion : public usbRequest
{
public:
   USB_requestGetDriverVersion() {}
   ~USB_requestGetDriverVersion() {}

   void Set(EZUSB_DRIVER_VERSION  *driverVersion)
   {
      usbRequest::Set(IOCTL_EZUSB_GET_DRIVER_VERSION,
                      NULL,
                      0,
                      driverVersion,
                      sizeof(EZUSB_DRIVER_VERSION));
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_SET_FEATURE request
////////////////////////////////////////////////////////////////////////////////
class USB_requestSetFeature : public usbRequest
{
public:
   USB_requestSetFeature() {}
   ~USB_requestSetFeature() {}

   void Set(SET_FEATURE_CONTROL *setFeatureControl)
   {
      usbRequest::Set(IOCTL_EZUSB_SET_FEATURE,
                      setFeatureControl,
                      sizeof(SET_FEATURE_CONTROL),
                      NULL,
                      0);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_GET_CURRENT_FRAME_NUMBER request
////////////////////////////////////////////////////////////////////////////////
class USB_requestGetCurrentFrameNumber : public usbRequest
{
public:
   USB_requestGetCurrentFrameNumber() {}
   ~USB_requestGetCurrentFrameNumber() {}

   void Set(ULONG  *frameNumber)
   {
      usbRequest::Set(IOCTL_EZUSB_GET_CURRENT_FRAME_NUMBER,
                      NULL,
                      0,
                      frameNumber,
                      sizeof(ULONG));
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_VENDOR_OR_CLASS_REQUEST request
////////////////////////////////////////////////////////////////////////////////
class USB_requestVendorOrClasRequest : public usbRequest
{
public:
   USB_requestVendorOrClasRequest() {}
   ~USB_requestVendorOrClasRequest() {}

   void Set(VENDOR_OR_CLASS_REQUEST_CONTROL *vcRequest,
            INT8                            *requestBuffer,
            ULONG                           requestBufferSize)
   {
      usbRequest::Set(IOCTL_EZUSB_VENDOR_OR_CLASS_REQUEST,
                      vcRequest,
                      sizeof(VENDOR_OR_CLASS_REQUEST_CONTROL),
                      requestBuffer,
                      requestBufferSize);
   }
};

////////////////////////////////////////////////////////////////////////////////
// Request data definition for IOCTL_EZUSB_GET_LAST_ERROR request
////////////////////////////////////////////////////////////////////////////////
class USB_requestGetDriverLastError : public usbRequest
{
public:
   USB_requestGetDriverLastError() {}
   ~USB_requestGetDriverLastError() {}

   void Set(ULONG *status)
   {
      usbRequest::Set(IOCTL_EZUSB_GET_LAST_ERROR,
                      NULL,
                      0,
                      status,
                      sizeof(ULONG));
    }
};

// Forward declaration
class USB_Comms;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// USB Driver access class
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class usbDriver
{
public:
      // Construction and destruction omembers
      usbDriver(bool debug = false);
      ~usbDriver();

      // Current system last error provider member
      char *GetSystemErrorText();

      // Debugger active/inactive setup member
      void SetDebugger(bool debug) { debugger = debug; }

      // Driver status for selected device provider member
      ULONG GetDeviceStatus(HANDLE hDevice);

      // Open driver device member
      bool OpenDevice(HANDLE *hDevice,
                      char   *deviceName,
                      ULONG  desiredAccess,
                      ULONG  sharedMode);

      // Close driver device member
      bool CloseDevice(HANDLE *hDevice);

      // Driver request execution member
      bool IssueRequest(HANDLE     hDevice,
                        usbRequest &request,
                        ULONG      *transferredBytes,
                        OVERLAPPED *overlapped);

protected:

private:
      // Last request status buffer member
      ULONG         operationStatus;

      // Buffer holding last acquired system error text message
      char          *systemErrorText;

      // Buffer holding last set device error text
      char          *deviceControlErrorText;

      // Debugger state buffer
      BOOL          debugger;
};

#endif // __USB_DRIVER_H__

