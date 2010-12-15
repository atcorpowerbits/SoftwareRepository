/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	buffer.cpp
	
	Author       :  Victor Aung

    Description  :	Business buffer classes
*/

#include "StdAfx.h"
#include <buffer.h>

using namespace BIZ_NAMESPACE;

/**
BizCircularBuffer

DESCRIPTION

	Constructor for circular buffer strategy

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/
BizCircularBuffer::BizCircularBuffer(unsigned short bufferSize)
{
	this->bufferSize = bufferSize;
	_buffer = gcnew array<unsigned short>(bufferSize);
	Reset();
}

/**
Append

DESCRIPTION

	Append data at the end of the circular buffer.

INPUT

	data - Data to be appended.
    Note: Do not validate data here. It's called during comms event to collect a raw data 
	      so should avoid any data processing.

OUTPUT

	None.

RETURN

	true - Data is appended successfully.

	false - Data is not appended.

*/
bool BizCircularBuffer::Append(unsigned short data)
{
	// Should be thread safe
	_lockData.WaitOne();

	_buffer[_endIndex] = data;
	_unreadData = true;

	// Check if circular buffer is full.
	if (!_firstAppend && (_endIndex == _startIndex))
	{
		// Buffer is full so rotate the start buffer.
		// If start and next to read were together then
		// advance the next to read position along with the start.
		if (_bringAlongNextRead)
		{
			_nextReadIndex++;
		}
		_startIndex++;
		// If start buffer and next to read were not together and
		// now there are toghter then bring along the next read from now on.
		if (!_bringAlongNextRead && (_startIndex == _nextReadIndex))
		{
			_bringAlongNextRead = true;
		}
		WRAP_IF_NEEDED(_startIndex, bufferSize)
		WRAP_IF_NEEDED(_nextReadIndex, bufferSize)
	}
	_firstAppend = false;

	// Inc for next append and 
	// wrap the end buffer if necessary
	_endIndex++;
	WRAP_IF_NEEDED(_endIndex, bufferSize)

	_lockData.ReleaseMutex();

	// Always successful to append to a circular buffer
	return true;
}

/**
ReadNext

DESCRIPTION

	Read one data from the circular buffer and
	advance the read pointer for next read.

INPUT

	None.

OUTPUT

	data - Data handle where one data is copied into.

RETURN

	true - One data is read.

	false - There's no new data to read.

*/
bool BizCircularBuffer::ReadNext(unsigned short% data)
{
	bool isRead = false;

	// Should be thread safe
	_lockData.WaitOne();

	// See if there's any data to read
	if (_unreadData)
	{
		data = _buffer[_nextReadIndex++];
		isRead = true;
		WRAP_IF_NEEDED(_nextReadIndex, bufferSize)

		// See if all data has been read
		if (_nextReadIndex == _endIndex)
		{
			_unreadData = false;
		}
		// Data is now read so no need to keep the next to read position 
		// with the start buffer position
		_bringAlongNextRead = false;
	}
	_lockData.ReleaseMutex();
	return isRead;
}

/**
Reset

DESCRIPTION

	Reset circular buffer indices (thread safe).
	All data in circular buffer is discarded.

INPUT

	None.

OUTPUT

	None.

RETURN

	None.

*/
void BizCircularBuffer::Reset()
{
	// Should be thread safe
	_lockData.WaitOne();
	_startIndex = 0;
	_endIndex = 0;
	_nextReadIndex = 0;
	_unreadData = false;
	_firstAppend = true;
	_bringAlongNextRead = true;
	_lockData.ReleaseMutex();
}

/**
ReadBuffer

DESCRIPTION

	Read the entire buffer from start to end.

INPUT

	None.

OUTPUT

	bufferSize - reference to the size of the array,
	startIndex - reference to the start of the array,
	endIndex - reference to the end of the array.

RETURN

	buffer - reference to the buffer array.

*/
array<unsigned short>^ BizCircularBuffer::ReadBuffer(unsigned short% bufferSize,
									unsigned short% startIndex,
									unsigned short% endIndex)
{
	// Should be thread safe
	_lockData.WaitOne();
	bufferSize = this->bufferSize;
	startIndex = _startIndex;
	endIndex = _endIndex;
	_lockData.ReleaseMutex();
	return _buffer;
}
