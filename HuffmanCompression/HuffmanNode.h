#pragma once

#include <fstream>
#include "BufferedBitFile.h"

typedef std::pair<char, int> HuffmanPair;

constexpr uint8_t SERIALIZATION_SENTRY = 0xFF;

using std::string;

class HuffmanNode
{
public:
	
	HuffmanNode();
	HuffmanNode(HuffmanPair pair);
	HuffmanNode(HuffmanPair pair, HuffmanNode* left, HuffmanNode* right);

	//Deserializing ctor
	HuffmanNode(byteArray binaryRep);
	//Copy ctor
	HuffmanNode(const HuffmanNode& other);
	//Move ctor - effective when transferring ownership like with rvalues
	HuffmanNode(const HuffmanNode&& other) noexcept;
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

	//Returns the success of the operation
	byteArray serialize();

private:
	void _recursiveSerialization(byteArray& tree) const;
	void _recursiveDeserialization(const byteArray& rep, HuffmanNode* currentNode);
	HuffmanPair _data;
	HuffmanNode* _right;
	HuffmanNode* _left;
};