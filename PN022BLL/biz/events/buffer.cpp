/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	buffer.cpp
	
	Author       :  Victor Aung

    Description  :	Business buffer classes
*/

#include "StdAfx.h"
#include "buffer.h"

namespace Biz {
	/**
	BizCircularBuffer

	DESCRIPTION

		Constructor for Buffer abstract strategy
	
	INPUT
	
		None.
	
	OUTPUT
	
		None.
	
	RETURN
	
		None.
	
	*/
	BizCircularBuffer::BizCircularBuffer(unsigned int bufferSize)
	{
		this->bufferSize = bufferSize;
		_buffer = gcnew array<unsigned short>(bufferSize);
	}

	bool BizCircularBuffer::Append(unsigned short data)
	{
		// Should be thread safe
		lockData.WaitOne();
		if (endBuffer == bufferSize) 
		{
			endBuffer = 0;
		}
		_buffer[endBuffer++] = data;
		if (endBuffer == startBuffer) 
		{
			// Rotate the buffer 
			// and wrap if necessary
			startBuffer++;
			if (startBuffer == bufferSize)
			{
				startBuffer = 0;
			}
		}
		lockData.ReleaseMutex();

		// Always successful to append to a circular buffer
		return true;
	}

	bool BizCircularBuffer::ReadNext(unsigned short^ data)
	{
		int unreadData;

		// Should be thread safe
		lockData.WaitOne();
		unreadData = endBuffer - nextToRead;
		// Adjust the unreadData when the end point has wrapped, 
		// i.e. negative unreadData
		if (unreadData < 0)
		{
			unreadData += bufferSize;
		}
		if (unreadData > 0)
		{
			*data = _buffer[nextToRead++];
			// Wrap the next read point if necessary
			if (nextToRead == bufferSize)
			{
				nextToRead = 0;
			}
		}
		lockData.ReleaseMutex();
		return (unreadData > 0);
	}

	void BizCircularBuffer::Reset()
	{
		// Should be thread safe
		lockData.WaitOne();
		startBuffer = 0;
		endBuffer = 0;
		nextToRead = 0;
		lockData.ReleaseMutex();
	}
}

