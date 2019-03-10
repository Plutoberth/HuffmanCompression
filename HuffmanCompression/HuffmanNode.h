#pragma once

#include "HuffmanPair.h"

using std::string;

class HuffmanNode
{
public:
	//TODO: Move constructor
	HuffmanNode();
	HuffmanNode(HuffmanPair pair);
	HuffmanNode(HuffmanPair pair, HuffmanNode* right, HuffmanNode* left);

	HuffmanNode(const HuffmanNode& other);
	HuffmanNode& operator=(const HuffmanNode& other);

	~HuffmanNode();

	HuffmanPair getData() const;
	HuffmanPair& getDataRef();

	HuffmanNode* getRightChild() const;
	HuffmanNode* getLeftChild() const;

	void setRightChild(HuffmanNode* node);
	void setLeftChild(HuffmanNode* node);

	//Comparison op for huffman node with huffman data
	bool operator() (HuffmanNode first, HuffmanNode second);

private:
	HuffmanPair _data;
	HuffmanNode* _right;
	HuffmanNode* _left;
};