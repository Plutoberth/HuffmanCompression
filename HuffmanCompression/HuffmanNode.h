#pragma once

#include "HuffmanPair.h"

using std::string;

class HuffmanNode
{
	HuffmanNode();
	HuffmanNode(HuffmanPair pair);
	HuffmanNode(HuffmanPair pair, HuffmanNode* right, HuffmanNode* left);

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