/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	buffer.cpp
	
	Author       :  Victor Aung

    Description  :	Business buffer classes
*/

#include "StdAfx.h"
#include <buffer.h>

namespace Biz {
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
	BizCircularBuffer::BizCircularBuffer(unsigned int bufferSize)
	{
		this->_bufferSize = bufferSize;
		_buffer = gcnew array<unsigned short>(bufferSize);
		Reset();
	}

	/**
	Append

	DESCRIPTION

		Append data at the end of the circular buffer.
	
	INPUT
	
		data - Data to be appended.
	
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

			// Rotate the start buffer.
			// If start and next to read were together then
			// bring along the next to read position.
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
			// Wrap the start buffer position if necessary
			if (_startIndex == _bufferSize)
			{
				_startIndex = 0;
			}
			// Wrap the next to read position if necessary
			if (_nextReadIndex == _bufferSize)
			{
				_nextReadIndex = 0;
			}
		}
		_firstAppend = false;

		// Inc for next append and 
		// wrap the end buffer if necessary
		_endIndex++;
		if (_endIndex == _bufferSize) 
		{
			_endIndex = 0;
		}

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
	bool BizCircularBuffer::ReadNext(unsigned short^ data)
	{
		bool isRead = false;

		// Should be thread safe
		_lockData.WaitOne();

		// See if there's any data to read
		if (_unreadData)
		{
			*data = _buffer[_nextReadIndex++];
			isRead = true;
			// Wrap the next read position if necessary
			if (_nextReadIndex == _bufferSize)
			{
				_nextReadIndex = 0;
			}
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
}

