#pragma once

#include "HuffmanPair.h"

using std::string;

class HuffmanNode
{
public:
	HuffmanNode();
	HuffmanNode(HuffmanPair pair);
	HuffmanNode(HuffmanPair pair, HuffmanNode* right, HuffmanNode* left);

	HuffmanNode(const HuffmanNode& other);
	HuffmanNode& operator=(const HuffmanNode& other);

	~HuffmanNode();

	HuffmanPair getData() const;

	HuffmanNode* getRightChild() const;
	HuffmanNode* getLeftChild() const;

	void setRightChild(HuffmanNode* node);
	void setLeftChild(HuffmanNode* node);

private:
	HuffmanPair _data;
	HuffmanNode* _right;
	HuffmanNode* _left;
};