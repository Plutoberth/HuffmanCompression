#pragma once

#include <string>

using std::string;

class HuffmanPair
{
public:
	HuffmanPair();
	HuffmanPair(char data, int frequency);

	char getData();
	int getFrequency();

	void incFrequency();
	void setFrequency(int frequency);

	//Overloaded comparison ops
	bool operator==(const HuffmanPair& other);
	bool operator>(const HuffmanPair& other);
	bool operator<(const HuffmanPair& other);

private:
	char _data;
	int _frequency;
};