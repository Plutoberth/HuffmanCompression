#pragma once

#include "HuffmanNode.h"
#include "BufferedBitFile.h"

#include <map>
#include <queue>
#include <fstream>
#include <iostream>

typedef std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNode> HuffmanPriorityQueue;

//A charmap to encode the char to its bit value
typedef std::map<char, BitArray> CharMap;

class HuffmanCoding
{
public:
	HuffmanCoding(string file);

	HuffmanNode getHuffmanTree();
	//Get the char map to encode the string to its constituent bytes.
	//CharMap getHuffmanCharMap();

private:
	string filename;
	HuffmanPriorityQueue getFrequencyQueue();
};