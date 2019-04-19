#pragma once
#include <fstream>
#include <deque>
#include <vector>
#include <string>

//This buffered file will accept BitArrays and write them to file according to the ctor parameter.

using std::string;

#define BYTE_SIZE 8
#define DEFAULT_BUFFER_SIZE 4096

#define ASSERT_SIZE_ERROR "Error: sizeof(char) is not a byte"

typedef uint8_t byte;
typedef bool bit;

//Despite the odd template specialization for vector<bool> it's still faster and it's clearer in the code.
typedef std::vector<bit> bitArray;

typedef std::vector<byte> byteArray;

//This buffered bit file class will accept arrays of bytes, with each element as a single bit.
//It'll write the bits to file when it reaches the threshold in bufferSize.
class BufferedBitFile : public std::ofstream
{
public:
	BufferedBitFile(string filename, unsigned int maxBufferSize=DEFAULT_BUFFER_SIZE);
	~BufferedBitFile();

	//Write the actual bits to the buffer
	void write(const bitArray& arr);
	void write(const byteArray& arr);
	void write(const byte* s, int n);

	//If a file is already open, this function will flush and close it.
	void open(const string filename);

	//The function will return the number of bytes written to file. 
	//It'll be called automatically when the current number of bytes exceeds the buffer size.
	int flush();
	//Returns the number of bits that were filled in
	uint8_t flush_and_fill(bit fillingBit);

	//Flushes the current full bytes and closes the file. 
	//Note: the incomplete byte is discarded.
	void close();

private:
	unsigned int _maxBufferSize;
	byte _workingByte;
	uint8_t _nextBit;
	byteArray _buffer;
};