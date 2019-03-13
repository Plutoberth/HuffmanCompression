#pragma once
#include <fstream>
#include <deque>
#include <vector>
#include <string>

//This buffered file will accept BitArrays and write them to file according to the ctor parameter.

using std::string;

typedef uint8_t byte;

//Because
typedef std::deque<byte> BitArray;

class BufferedBitFile
{
public:
	BufferedBitFile(string filename, int bufferSize);

	//Write the actual bits to the buffer
	void write(BitArray arr);

	void close();
	bool is_open();

private:
	int _bufferSize;
	byte _workingByte;
	//No reason to use a whole byte for a value that can only be 0-7
	uint8_t _current_bit;
	std::ofstream _file;
	std::vector<byte> _buffer;
};