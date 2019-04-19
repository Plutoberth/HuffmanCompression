#include "BufferedBitFile.h"

BufferedBitFile::BufferedBitFile(string filename, unsigned int bufferSize)
	: std::ofstream(filename, std::ios::binary)
{
	this->_maxBufferSize = bufferSize;
	//Allocate now for performance reasons. This isn't significant unless the bufferSize is really large.
	this->_buffer.reserve(bufferSize);
	this->_workingByte = 0;
	this->_nextBit = 0;
}

BufferedBitFile::~BufferedBitFile()
{
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
		this->_workingByte = this->_workingByte << 1;
		if (bit)
		{
			this->_workingByte |= 1;
		}
		this->_nextBit++;
	}

	//Flush if buffer size exceeds the limit
	if (this->_buffer.size() >= this->_maxBufferSize)
	{
		this->flush();
	}
}

void BufferedBitFile::write(const byteArray & arr)
{
	this->write(arr.data(), arr.size());
}

void BufferedBitFile::write(const byte* s, int n)
{
	this->_buffer.insert(this->_buffer.end(), s, s + n);

	if (this->_buffer.size() >= this->_maxBufferSize)
	{
		this->flush();
	}
}

int BufferedBitFile::flush()
{
	int bytesWritten = 0;
	if (this->is_open())
	{
		//Make sure that they're the same size because we're going to use the data pointer
		static_assert(sizeof(const char) == sizeof(byte), ASSERT_SIZE_ERROR);
		std::ofstream::write((const char*) this->_buffer.data(), this->_buffer.size());
		bytesWritten = this->_buffer.size();
		this->_buffer.clear();
	}
	return bytesWritten;
}

uint8_t BufferedBitFile::flush_and_fill(bit fillingBit)
{
	uint8_t bitsFilled = 0;
	if (this->_nextBit != 0)
	{
		bitsFilled = 8 - this->_nextBit;
		this->write(std::vector<bit>(bitsFilled, fillingBit));
		
		//Add byte to byte array and reset values
		this->_buffer.push_back(this->_workingByte);
		this->_workingByte = 0;
		this->_nextBit = 0;
	}
	this->flush();

	return bitsFilled;
}

void BufferedBitFile::close()
{
	this->flush();
	this->_workingByte = 0;
	this->_nextBit = 0;
	std::ofstream::close();
}

void BufferedBitFile::open(const string filename)
{
	this->close();
	std::ofstream::open(filename, std::ios::binary);
}