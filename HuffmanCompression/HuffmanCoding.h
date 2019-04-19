#pragma once

#include "HuffmanNode.h"
#include "BufferedBitFile.h"

#include <map>
#include <queue>
#include <fstream>
#include <memory>
#include <iostream>

#define FILE_BYTES_ERROR "Error: The file and the tree inside it are corrupt."

typedef std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, HuffmanNode> HuffmanPriorityQueue;

typedef std::unique_ptr<HuffmanNode> HuffmanNodeSmartPtr;

//A charmap to encode the char to its bit value
typedef std::map<char, bitArray> CharMap;

class HuffmanCoding
{
public:
	//Write the tree and compressed text to file
	static bool compress(string source, string target);
	static bool decompress(string source, string target);

private:
	static int _getNumberOfBytesToEnd(std::istream& file);
	static HuffmanNodeSmartPtr _getHuffmanTree(string filename);
	static CharMap _getHuffmanCharMap(const HuffmanNode& tree);

	static HuffmanPriorityQueue _getFrequencyQueue(string filename);
	static void _scanBinaryTree(HuffmanNode const* tree, CharMap& map, bitArray currentLocation = {});
};