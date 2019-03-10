#include "HuffmanPair.h"

HuffmanPair::HuffmanPair()
{
}

HuffmanPair::HuffmanPair(string data, int frequency)
{
	this->_data = data;
	this->_frequency = frequency;
}

string HuffmanPair::getData()
{
	return this->_data;
}

int HuffmanPair::getFrequency()
{
	return this->_frequency;
}

void HuffmanPair::incFrequency()
{
	this->_frequency++;
}

void HuffmanPair::setFrequency(int frequency)
{
	this->_frequency = frequency;
}

bool HuffmanPair::operator==(const HuffmanPair & other)
{
	return this->_frequency == other._frequency;
}

bool HuffmanPair::operator>(const HuffmanPair & other)
{
	return this->_frequency > other._frequency;
}

bool HuffmanPair::operator<(const HuffmanPair & other)
{
	return this->_frequency < other._frequency;
}
