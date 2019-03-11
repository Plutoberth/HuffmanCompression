#pragma once

#include "HuffmanNode.h"

#include <map>
#include <queue>
#include <fstream>
#include <iostream>
#include <bitset>

using std::bitset;

typedef std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNode> HuffmanPriorityQueue;
//This should probably be changed to a smarter solution later.
//For now, 256 bits is the max size of a huffman codeword for a 256 value alphabet (a byte, 2^8).
#define MAX_BITS 256
typedef std::map<char, bitset<MAX_BITS>> CharMap;

class HuffmanCoding
{
public:
	HuffmanCoding(string file);

	HuffmanNode getHuffmanTree();
	//Get the char map to encode the string to its constituent bytes.
	CharMap getHuffmanCharMap();

	

//private:
	string filename;
	HuffmanPriorityQueue getFrequencyQueue();
};