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

void BufferedBitFile::close()
{
	this->_file.close();
}

bool BufferedBitFile::is_open()
{
	return this->_file.is_open();
}
