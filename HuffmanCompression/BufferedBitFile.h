#pragma once
#include <fstream>
#include <vector>
#include <bitset>
#include <string>

//This buffered bit file will accept bitsets and write them to file whenever a byte (or more) accumulates.
using std::string;
using std::bitset;

typedef uint8_t byte;

//This struct will be used when you know your max size, but you don't know how many bits you'll use.
template <size_t MAX_BITS>
struct CountedBitPair
{
	bitset<MAX_BITS> bitset;
	int bits_used;
};

template <size_t MAX_BITS>
class BufferedBitFile
{
public:
	BufferedBitFile(string filename);

	//Write the actual bits to the buffer
	void write(CountedBitPair<MAX_BITS> pair);
	//Write the full set to the buffer
	void write(bitset<MAX_BITS> set);

	void close();
	bool is_open();

private:
	int _current_bit;
	std::ofstream _file;
	std::vector<byte> _buffer;
};

template<size_t MAX_BITS>
inline BufferedBitFile<MAX_BITS>::BufferedBitFile(string filename)
{
	this->_file = std::ofstream(filename);
}

template<size_t MAX_BITS>
inline void BufferedBitFile<MAX_BITS>::write(CountedBitPair<MAX_BITS> pair)
{
	//Fill in bit counting code
}

template<size_t MAX_BITS>
inline void BufferedBitFile<MAX_BITS>::write(bitset<MAX_BITS> set)
{
	this->write({ set, MAX_BITS });
}

template<size_t MAX_BITS>
inline void BufferedBitFile<MAX_BITS>::close()
{
	this->_file.close();
}

template<size_t MAX_BITS>
inline bool BufferedBitFile<MAX_BITS>::is_open()
{
	return this->_file.is_open;
}
