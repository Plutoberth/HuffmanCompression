#pragma once

#include <string>

using std::string;

class HuffmanPair
{
	HuffmanPair(string data, int frequency);

	string getData();
	int getFrequency();

	void incFrequency();
	void setFrequency(int frequency);

	//Overloaded comparison ops
	bool operator==(const HuffmanPair& other);
	bool operator>(const HuffmanPair& other);
	bool operator<(const HuffmanPair& other);

private:
	string _data;
	int _frequency;

};