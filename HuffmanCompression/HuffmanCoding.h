#pragma once

#include "HuffmanNode.h"

#include <map>
#include <queue>
#include <fstream>
#include <iostream>

typedef std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, HuffmanNode> HuffmanPriorityQueue;

class HuffmanCoding
{
public:
	HuffmanCoding(string file);

	HuffmanNode getHuffmanTree();

	//

//private:
	string filename;
	HuffmanPriorityQueue getFrequencyQueue();
};