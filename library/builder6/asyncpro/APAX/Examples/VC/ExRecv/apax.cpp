// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "apax.h"

// Dispatch interfaces referenced by this interface
#include "Font.h"

/////////////////////////////////////////////////////////////////////////////
// CApax

IMPLEMENT_DYNCREATE(CApax, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CApax properties

/////////////////////////////////////////////////////////////////////////////
// CApax operations

long CApax::PortOpen()
{
	long result;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CApax::TapiDial()
{
	long result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CApax::TapiAnswer()
{
	long result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CApax::WinsockConnect()
{
	long result;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CApax::WinsockListen()
{
	long result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CApax::Close()
{
	long result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::AddStringToLog(LPCTSTR S)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 S);
}

void CApax::FlushInBuffer()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::FlushOutBuffer()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::PutData(const VARIANT& Data)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &Data);
}

void CApax::PutString(LPCTSTR S)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 S);
}

void CApax::PutStringCRLF(LPCTSTR S)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 S);
}

void CApax::SendBreak(long Ticks, BOOL Yield)
{
	static BYTE parms[] =
		VTS_I4 VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Ticks, Yield);
}

long CApax::AddDataTrigger(LPCTSTR TriggerString, long PacketSize, long Timeout, BOOL IncludeStrings, BOOL IgnoreCase)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_BOOL VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		TriggerString, PacketSize, Timeout, IncludeStrings, IgnoreCase);
	return result;
}

void CApax::DisableDataTrigger(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void CApax::EnableDataTrigger(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void CApax::RemoveDataTrigger(long Index)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index);
}

void CApax::Clear()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::ClearAll()
{
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::CopyToClipboard()
{
	InvokeHelper(0x14, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CApax::GetAttributes(long aRow, long aCol)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		aRow, aCol);
	return result;
}

void CApax::SetAttributes(long aRow, long aCol, long Value)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 aRow, aCol, Value);
}

CString CApax::GetLine(long Index)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Index);
	return result;
}

void CApax::SetLine(long Index, LPCTSTR Value)
{
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Index, Value);
}

void CApax::TerminalSetFocus()
{
	InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::TerminalWriteString(LPCTSTR S)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 S);
}

void CApax::TerminalWriteStringCRLF(LPCTSTR S)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 S);
}

void CApax::TapiAutoAnswer()
{
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::TapiCancelCall()
{
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::TapiConfigAndOpen()
{
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::TapiSelectDevice()
{
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::TapiSendTone(LPCTSTR Digits)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Digits);
}

void CApax::TapiSetRecordingParams(long NumChannels, long NumSamplesPerSecond, long NumBitsPerSample)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumChannels, NumSamplesPerSecond, NumBitsPerSample);
}

void CApax::TapiShowConfigDialog(BOOL AllowEdit)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AllowEdit);
}

void CApax::TapiPlayWaveFile(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

void CApax::TapiRecordWaveFile(LPCTSTR FileName, BOOL Overwrite)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName, Overwrite);
}

void CApax::TapiStopWaveFile()
{
	InvokeHelper(0x25, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CApax::TapiTranslatePhoneNo(LPCTSTR CanonicalAddr)
{
	CString result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		CanonicalAddr);
	return result;
}

void CApax::CancelProtocol()
{
	InvokeHelper(0x27, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CApax::EstimateTransferSecs(long Size)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Size);
	return result;
}

void CApax::StartTransmit()
{
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::StartReceive()
{
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CApax::GetBaud()
{
	long result;
	InvokeHelper(0x4c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetBaud(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CApax::GetComNumber()
{
	long result;
	InvokeHelper(0x4d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetComNumber(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CApax::GetDeviceType()
{
	long result;
	InvokeHelper(0x4e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetDeviceType(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CApax::GetDataBits()
{
	long result;
	InvokeHelper(0x4f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetDataBits(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CApax::GetDtr()
{
	BOOL result;
	InvokeHelper(0x50, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetDtr(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x50, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CApax::GetLogging()
{
	long result;
	InvokeHelper(0x56, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetLogging(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x56, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CApax::GetLogHex()
{
	BOOL result;
	InvokeHelper(0x57, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetLogHex(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x57, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CApax::GetLogName()
{
	CString result;
	InvokeHelper(0x58, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetLogName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x58, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CApax::GetParity()
{
	long result;
	InvokeHelper(0x5a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetParity(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CApax::GetPromptForPort()
{
	BOOL result;
	InvokeHelper(0x5b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetPromptForPort(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetRS485Mode()
{
	BOOL result;
	InvokeHelper(0x5c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetRS485Mode(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetRts()
{
	BOOL result;
	InvokeHelper(0x5d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetRts(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x5d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CApax::GetStopBits()
{
	long result;
	InvokeHelper(0x5e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetStopBits(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CApax::GetWinsockMode()
{
	long result;
	InvokeHelper(0x62, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetWinsockMode(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x62, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CApax::GetWinsockAddress()
{
	CString result;
	InvokeHelper(0x63, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetWinsockAddress(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x63, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CApax::GetWinsockPort()
{
	CString result;
	InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetWinsockPort(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x64, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CApax::GetAnswerOnRing()
{
	long result;
	InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetAnswerOnRing(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x66, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CApax::GetEnableVoice()
{
	BOOL result;
	InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetEnableVoice(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x67, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CApax::GetMaxAttempts()
{
	long result;
	InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetMaxAttempts(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x68, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CString CApax::GetSelectedDevice()
{
	CString result;
	InvokeHelper(0x6b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetSelectedDevice(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CApax::GetTapiNumber()
{
	CString result;
	InvokeHelper(0x6d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetTapiNumber(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

unsigned long CApax::GetColor()
{
	unsigned long result;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(DISPID_BACKCOLOR, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CApax::GetColumns()
{
	long result;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetColumns(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CApax::GetEmulation()
{
	long result;
	InvokeHelper(0x74, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetEmulation(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x74, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

COleFont CApax::GetFont()
{
	LPDISPATCH pDispatch;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return COleFont(pDispatch);
}

void CApax::SetFont(LPDISPATCH newValue)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CApax::SetRefFont(LPDISPATCH* newValue)
{
	static BYTE parms[] =
		VTS_PDISPATCH;
	InvokeHelper(DISPID_FONT, DISPATCH_PROPERTYPUTREF, VT_EMPTY, NULL, parms,
		 newValue);
}

long CApax::GetRows()
{
	long result;
	InvokeHelper(0x75, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x75, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CApax::GetScrollbackEnabled()
{
	BOOL result;
	InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetScrollbackEnabled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x76, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CApax::GetScrollbackRows()
{
	long result;
	InvokeHelper(0x77, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetScrollbackRows(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x77, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CApax::GetTerminalActive()
{
	BOOL result;
	InvokeHelper(0x78, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetTerminalActive(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x78, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetTerminalHalfDuplex()
{
	BOOL result;
	InvokeHelper(0x7a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetTerminalHalfDuplex(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetTerminalWantAllKeys()
{
	BOOL result;
	InvokeHelper(0x7e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetTerminalWantAllKeys(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x7e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CApax::GetVersion()
{
	CString result;
	InvokeHelper(0x7f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetVersion(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CApax::GetVisible()
{
	BOOL result;
	InvokeHelper(0x80, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetVisible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x80, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CApax::GetDataTriggerString()
{
	CString result;
	InvokeHelper(0x81, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetDataTriggerString(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x81, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

BOOL CApax::GetProtocolStatusDisplay()
{
	BOOL result;
	InvokeHelper(0x82, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetProtocolStatusDisplay(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x82, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CApax::GetProtocol()
{
	long result;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetProtocol(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x83, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CApax::GetHonorDirectory()
{
	BOOL result;
	InvokeHelper(0x90, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetHonorDirectory(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x90, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetIncludeDirectory()
{
	BOOL result;
	InvokeHelper(0x91, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetIncludeDirectory(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x91, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CString CApax::GetReceiveDirectory()
{
	CString result;
	InvokeHelper(0x9c, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetReceiveDirectory(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CApax::GetReceiveFileName()
{
	CString result;
	InvokeHelper(0x9d, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetReceiveFileName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CApax::GetSendFileName()
{
	CString result;
	InvokeHelper(0x9f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetSendFileName(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x9f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

CString CApax::GetCaption()
{
	CString result;
	InvokeHelper(DISPID_CAPTION, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
	return result;
}

void CApax::SetCaption(LPCTSTR lpszNewValue)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(DISPID_CAPTION, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 lpszNewValue);
}

long CApax::GetCaptionAlignment()
{
	long result;
	InvokeHelper(0xab, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetCaptionAlignment(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xab, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CApax::GetCaptionWidth()
{
	long result;
	InvokeHelper(0xac, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetCaptionWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xac, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CApax::GetLightWidth()
{
	long result;
	InvokeHelper(0xad, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetLightWidth(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xad, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

unsigned long CApax::GetLightsLitColor()
{
	unsigned long result;
	InvokeHelper(0xae, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetLightsLitColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xae, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CApax::GetLightsNotLitColor()
{
	unsigned long result;
	InvokeHelper(0xaf, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::SetLightsNotLitColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xaf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CApax::GetShowLightCaptions()
{
	BOOL result;
	InvokeHelper(0xb0, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetShowLightCaptions(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetShowLights()
{
	BOOL result;
	InvokeHelper(0xb1, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetShowLights(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetShowStatusBar()
{
	BOOL result;
	InvokeHelper(0xb2, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetShowStatusBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetShowToolBar()
{
	BOOL result;
	InvokeHelper(0xb3, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetShowToolBar(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb3, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetShowDeviceSelButton()
{
	BOOL result;
	InvokeHelper(0xb4, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetShowDeviceSelButton(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetShowConnectButtons()
{
	BOOL result;
	InvokeHelper(0xb5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetShowConnectButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetShowProtocolButtons()
{
	BOOL result;
	InvokeHelper(0xb6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetShowProtocolButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CApax::GetShowTerminalButtons()
{
	BOOL result;
	InvokeHelper(0xb7, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetShowTerminalButtons(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CApax::DrawTextBiDiModeFlagsReadingOnly()
{
	long result;
	InvokeHelper(0xbb, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CApax::InitiateAction()
{
	InvokeHelper(0xbc, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CApax::IsRightToLeft()
{
	BOOL result;
	InvokeHelper(0xbd, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CApax::UseRightToLeftReading()
{
	BOOL result;
	InvokeHelper(0xc0, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL CApax::UseRightToLeftScrollBar()
{
	BOOL result;
	InvokeHelper(0xc1, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

short CApax::GetCursor()
{
	short result;
	InvokeHelper(0xc2, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CApax::SetCursor(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xc2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

void CApax::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CApax::RemoveAllDataTriggers()
{
	InvokeHelper(0xba, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString CApax::TapiStatusMsg(long Message, long State, long Reason)
{
	CString result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0xbe, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		Message, State, Reason);
	return result;
}

BOOL CApax::GetTapiStatusDisplay()
{
	BOOL result;
	InvokeHelper(0xbf, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetTapiStatusDisplay(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xbf, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

short CApax::GetInBufferSize()
{
	short result;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CApax::SetInBufferSize(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xc9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

short CApax::GetOutBufferSize()
{
	short result;
	InvokeHelper(0xcc, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
	return result;
}

void CApax::SetOutBufferSize(short nNewValue)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xcc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CApax::GetMSCommCompatible()
{
	BOOL result;
	InvokeHelper(0xce, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CApax::SetMSCommCompatible(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xce, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}
