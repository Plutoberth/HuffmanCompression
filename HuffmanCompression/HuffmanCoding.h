#pragma once

#include "HuffmanNode.h"

#include <map>
#include <queue>

typedef std::priority_queue<HuffmanNode, std::vector<HuffmanNode>, HuffmanNode> HuffmanPriorityQueue;

class HuffmanCoding
{
public:
	HuffmanCoding(string file);

	HuffmanNode getHuffmanTree();

	//

private:
	string filename;
	HuffmanPriorityQueue getFrequencyQueue();
};