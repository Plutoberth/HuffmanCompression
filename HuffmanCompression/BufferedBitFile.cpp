#include "BufferedBitFile.h"

BufferedBitFile::BufferedBitFile(string filename, int bufferSize)
{
	this->_file.open(filename, std::ios::binary);
	this->_bufferSize = bufferSize;
}

void BufferedBitFile::close()
{
	this->_file.close();
}

bool BufferedBitFile::is_open()
{
	return this->_file.is_open();
}
