/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	buffer.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of business buffer classes.
*/

#pragma once

#include <biz_namespace.h>

using namespace System;
using namespace System::Threading;

START_BIZ_NAMESPACE

#define WRAP_IF_NEEDED(index, maxSize)	\
		if (index == maxSize)			\
		{								\
			index = 0;					\
		}

	// Buffer strategy
public ref class BizBuffer abstract
{
public:
	virtual bool Append(unsigned short data) { return false; };
	virtual bool ReadNext(unsigned short% data) { return false; };
	virtual void Reset() = 0;
	virtual array<unsigned short>^ ReadBuffer(unsigned int% bufferSize,
									unsigned short% startIndex,
									unsigned short% endIndex) = 0;
protected:
	BizBuffer() {};
	property unsigned short bufferSize;
};

public ref class BizCircularBuffer : BizBuffer
{
public:
	BizCircularBuffer(unsigned short bufferSize);
	virtual bool Append(unsigned short data) override;
	virtual bool ReadNext(unsigned short% data) override;
	virtual void Reset() override sealed;
	virtual array<unsigned short>^ ReadBuffer(unsigned int% bufferSize,
									unsigned short% startIndex,
									unsigned short% endIndex) override;
private:
	array<unsigned short>^ _buffer;
	Mutex _lockData;
	unsigned short _startIndex;
	unsigned short _endIndex;
	unsigned short _nextReadIndex;
	bool _unreadData;
	bool _firstAppend;
	// A flag to indicate _nextReadIndex should be moved along with _startIndex
	// when the latter is rotated due to buffer full.
	bool _bringAlongNextRead;
};

END_BIZ_NAMESPACE
