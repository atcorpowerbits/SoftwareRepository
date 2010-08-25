/*
    Copyright (C) ATCOR MEDICAL PTY LTD, 2010

    Filename	 :	buffer.h
	
	Author       :  Victor Aung

    Description  :	DECLARATION of business buffer classes.
*/

#pragma once

using namespace System;
using namespace System::Threading;

namespace Biz {

	// Buffer strategy
	public ref class BizBuffer abstract
	{
	public:
		virtual bool Append(unsigned short data) { return false; };
		virtual bool ReadNext(unsigned short^ data) { return false; };
		virtual void Reset() {};
	protected:
		property unsigned int bufferSize;
	};

	public ref class BizCircularBuffer : BizBuffer
	{
	public:
		BizCircularBuffer(unsigned int bufferSize);
		virtual bool Append(unsigned short data) override;
		virtual bool ReadNext(unsigned short^ data) override;
		virtual void Reset() override;
	private:
		array<unsigned short>^ _buffer;
		Mutex lockData;
		unsigned short startBuffer;
		unsigned short endBuffer;
		unsigned short nextToRead;
	};
}

