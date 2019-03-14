#include "BufferedBitFile.h"

BufferedBitFile::BufferedBitFile(string filename, unsigned int bufferSize)
	: std::ofstream(filename, std::ios::binary)
{
	this->_bufferSize = bufferSize;
	//Allocate now for performance reasons. This isn't significant unless the bufferSize is really large.
	this->_buffer.reserve(bufferSize);
}

BufferedBitFile::~BufferedBitFile()
{
	//Flush and close the file
	//Note: the incomplete byte is discarded.
	this->flush();
	this->close();
}

void BufferedBitFile::write(const bitArray& arr)
{
	for (auto bit: arr)
	{
		if (this->_nextBit == BYTE_SIZE)
		{
			//Add byte to byte array and reset values
			this->_buffer.push_back(this->_workingByte);
			this->_workingByte = 0;
			this->_nextBit = 0;
		}

		//Shift left by one bit
		this->_workingByte << 1;
		if (bit) //Makes our class more generic
		{
			this->_workingByte | 1;
		}
		this->_nextBit++;
	}

	//Flush if buffer size is >= max buffer size received in ctor
	if (this->_buffer.size() >= this->_bufferSize)
	{
		this->flush();
	}
}

void BufferedBitFile::write(const byteArray & arr)
{
	//Concatenate the byte vectors
	this->_buffer.insert(this->_buffer.end(), arr.begin(), arr.end());
	//Flush if buffer size is >= max buffer size received in ctor
	if (this->_buffer.size() >= this->_bufferSize)
	{
		this->flush();
	}
}

void BufferedBitFile::write(byte* s, int n)
{
	this->_buffer.insert(this->_buffer.end(), s, s + n);

	if (this->_buffer.size() >= this->_bufferSize)
	{
		this->flush();
	}
}

int BufferedBitFile::flush()
{
	int bytesWritten = 0;
	if (this->is_open())
	{
		//Cast byte ptr to const char*. Both are of the same size so this works well.
		std::ofstream::write((const char*) this->_buffer.data(), this->_buffer.size());
		bytesWritten = this->_buffer.size();
		this->_buffer.clear();
	}
	return bytesWritten;
}

void BufferedBitFile::close()
{
	this->flush();
	std::ofstream::close();
}

void BufferedBitFile::open(const string filename)
{
	this->close();
	std::ofstream::open(filename, std::ios::binary);
}