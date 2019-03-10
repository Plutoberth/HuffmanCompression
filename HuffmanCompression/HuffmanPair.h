#pragma once

#include <string>

using std::string;

class HuffmanPair
{
public:
	HuffmanPair();
	HuffmanPair(char data, int frequency);

	char getData() const;
	int getFrequency() const;

	void incFrequency();
	void setFrequency(int frequency);

	//Overloaded comparison ops
	bool operator==(const HuffmanPair& other) const;
	bool operator>(const HuffmanPair& other) const;
	bool operator<(const HuffmanPair& other) const;

private:
	char _data;
	int _frequency;
};