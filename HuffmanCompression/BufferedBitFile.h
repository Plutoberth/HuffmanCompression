#pragma once
#include <fstream>
#include <deque>
#include <vector>
#include <string>

//This buffered file will accept BitArrays and write them to file according to the ctor parameter.

using std::string;

#define BYTE_SIZE 8

typedef uint8_t byte;

/*TODO: Check whether a vector<bool> or a vector<byte> are faster
/*This might seem obvious, but vector<bool> has a specialization that makes it store each bool as a single bit.
/*It makes it much more space efficient, but I need to check if the performance decrease isn't significant.*/
typedef std::vector<byte> BitArray;

//This buffered bit file class will accept arrays of bytes, with each element as a single bit.
//It'll write the bits to file when it reaches the threshold in bufferSize.
//It's not responsible for an incomplete byte, and it'll not be written.
class BufferedBitFile
{
public:
	BufferedBitFile(string filename, unsigned int bufferSize);
	~BufferedBitFile();

	//Write the actual bits to the buffer
	void write(const BitArray& arr);

	//Returns whether it opened the file successfully.
	//If a file is already open, this function will flush and close it.
	bool open(const string filename);
	bool is_open() const;

	//The function will return the number of bytes written to file. 
	//It'll be called automatically when the current number of bytes is >= than the buffer size.
	int flush();

	void close();

private:
	unsigned int _bufferSize;
	byte _workingByte;
	//No reason to use a whole byte for a value that can only be 0-7
	uint8_t _nextBit;
	std::ofstream _file;
	std::vector<byte> _buffer;
};