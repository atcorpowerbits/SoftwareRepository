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
		if (_endBuffer == _bufferSize) 
		{
			// Wrap the end pointer
			_endBuffer = 0;
		}
		_buffer[_endBuffer++] = data;
		if (_endBuffer == _startBuffer) 
		{
			// Circular buffer is full.
			// Rotate the buffer 
			// and wrap if necessary
			_startBuffer++;
			if (_startBuffer == _bufferSize)
			{
				// Wrap the start pointer
				_startBuffer = 0;
			}
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
		int unreadData;

		// Should be thread safe
		_lockData.WaitOne();
		unreadData = _endBuffer - _nextToRead;

		// Adjust the unreadData when the end point has wrapped, 
		// i.e. negative unreadData
		if (unreadData < 0)
		{
			unreadData += _bufferSize;
		}
		if (unreadData > 0)
		{
			*data = _buffer[_nextToRead++];
			isRead = true;
			// Wrap the next read point if necessary
			if (_nextToRead == _bufferSize)
			{
				_nextToRead = 0;
			}
		}
		_lockData.ReleaseMutex();
		return isRead;
	}

	void BizCircularBuffer::Reset()
	{
		// Should be thread safe
		_lockData.WaitOne();
		_startBuffer = 0;
		_endBuffer = 0;
		_nextToRead = 0;
		_lockData.ReleaseMutex();
	}
}

