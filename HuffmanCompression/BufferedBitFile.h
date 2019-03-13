#pragma once
#include <fstream>
#include <deque>
#include <vector>
#include <string>

//This buffered file will accept BitArrays and write them to file according to the ctor parameter.

using std::string;

typedef uint8_t byte;

/*I elected to use a deque of bytes for my bit array. This was chosen because the efficiency of
/*the container doesn't really matter in this project, and in most implementations of bit writing.
/*Here, the maximum number of bits that we'll need to store is not very high, at most a couple of kilobytes.
/*This is excusable because bitsets are much, much slower and do not allow deletions from the beginning and the end,
/*or easy extractions. I preferred the time and usage efficiency over the space efficiency.
/*I could have used the specialized vector<bool> that stores bools as bits, but it would've been slower and a deque
/* is better for this purpose as it allows deletions both from the beginning and the end and that's useful in bit buffering.*/
typedef std::deque<byte> BitArray;

//This buffered bit file class will accept arrays of bytes, with each element as a single bit.
//It'll write the bits to file when it reaches the threshold in bufferSize.
//It's not responsible for an incomplete byte, and it'll not be written.
class BufferedBitFile
{
public:
	BufferedBitFile(string filename, int bufferSize);
	~BufferedBitFile();

	//Write the actual bits to the buffer
	void write(BitArray arr);

	//Returns whether it opened the file successfully.
	//If a file is already open, this function will flush and close it.
	bool open(string filename);
	bool is_open();

	//The function will return the number of bytes written to file. 
	//It'll be called automatically when the current number of bytes is >= than the buffer size.
	int flush();

	void close();

private:
	int _bufferSize;
	byte _workingByte;
	//No reason to use a whole byte for a value that can only be 0-7
	uint8_t _current_bit;
	std::ofstream _file;
	std::vector<byte> _buffer;
};