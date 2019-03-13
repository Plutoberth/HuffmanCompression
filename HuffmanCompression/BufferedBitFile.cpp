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
