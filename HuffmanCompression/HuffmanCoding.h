#pragma once

#include "HuffmanNode.h"

#include <map>
#include <queue>


class HuffmanCoding
{
public:
	HuffmanCoding(string file);

	HuffmanNode getHuffmanTree();

	//

private:
	string filename;
};