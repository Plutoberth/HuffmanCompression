#pragma once

#include "HuffmanNode.h"
#include "BufferedBitFile.h"

#include <map>
#include <queue>
#include <fstream>
#include <memory>
#include <iostream>

typedef std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNode> HuffmanPriorityQueue;

typedef std::unique_ptr<HuffmanNode> HuffmanNodeSmartPtr;

//A charmap to encode the char to its bit value
typedef std::map<char, BitArray> CharMap;

class HuffmanCoding
{
public:
	HuffmanCoding(string filename);

	HuffmanNodeSmartPtr getHuffmanTree();
	//Get the char map to encode the string to its constituent bytes.
	CharMap getHuffmanCharMap();
	CharMap getHuffmanCharMap(HuffmanNode tree);

private:
	string filename;
	HuffmanPriorityQueue getFrequencyQueue();
	void _scanBinaryTree(HuffmanNode* tree, CharMap& map, BitArray currentLocation);
};