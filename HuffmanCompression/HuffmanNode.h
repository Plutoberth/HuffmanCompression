#pragma once

#include "HuffmanPair.h"

using std::string;

class HuffmanNode
{
public:
	
	HuffmanNode();
	HuffmanNode(HuffmanPair pair);
	HuffmanNode(HuffmanPair pair, HuffmanNode* right, HuffmanNode* left);
	//Copy ctor
	HuffmanNode(const HuffmanNode& other);
	//Move ctor - effective when transferring ownership like with rvalues
	HuffmanNode(const HuffmanNode&& other);
	//Assignment operator
	HuffmanNode& operator=(const HuffmanNode& other);

	~HuffmanNode();

	HuffmanPair getData() const;
	const HuffmanPair& getDataRef() const;

	HuffmanNode* getRightChild() const;
	HuffmanNode* getLeftChild() const;

	void setRightChild(HuffmanNode* node);
	void setLeftChild(HuffmanNode* node);

	//Comparison op for huffman node with huffman data
	bool operator() (const HuffmanNode* first, const HuffmanNode* second) const;

private:
	HuffmanPair _data;
	HuffmanNode* _right;
	HuffmanNode* _left;
};