#include "HuffmanPair.h"

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
