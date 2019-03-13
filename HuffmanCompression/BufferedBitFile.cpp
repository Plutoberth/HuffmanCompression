#include "BufferedBitFile.h"

BufferedBitFile::BufferedBitFile(string filename, int bufferSize)
{
	this->open(filename);
	this->_bufferSize = bufferSize;
}

BufferedBitFile::~BufferedBitFile()
{
	//Flush and close the file
	//Note: the incomplete byte is discarded.
	this->flush();
	this->close();
}

void BufferedBitFile::write(const BitArray& arr)
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
		if (bit) //avoids errors with nonbinary values
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

int BufferedBitFile::flush()
{
	int bytesWritten = 0;
	if (this->_file.is_open())
	{
		//Cast byte ptr to const char*. Both are of the same size so this works well.
		this->_file.write((const char*) this->_buffer.data(), this->_buffer.size());
		bytesWritten = this->_buffer.size();
		this->_buffer.clear();
	}
	return bytesWritten;
}

void BufferedBitFile::close()
{
	this->flush();
	this->_file.close();
}

bool BufferedBitFile::open(const string filename)
{
	this->close();
	this->_file.open(filename, std::ios::binary);
	return this->_file.is_open();
}

bool BufferedBitFile::is_open() const
{
	return this->_file.is_open();
}
