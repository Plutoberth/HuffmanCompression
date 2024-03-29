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
	HuffmanNode(HuffmanNode&& other) noexcept;
	//Assignment operator
	HuffmanNode& operator=(const HuffmanNode& other);

	~HuffmanNode();

	HuffmanPair getData() const;
	const HuffmanPair& getDataRef() const;

	HuffmanNode* getRightChild() const;
	HuffmanNode* getLeftChild() const;

	bool isLeaf() const;

	//Comparison op for huffman node with huffman data
	bool operator() (const HuffmanNode* first, const HuffmanNode* second) const;

	byteArray serialize();

private:
	void _recursiveSerialization(byteArray& tree) const;
	int _deserializeInto(const byteArray& rep, int firstLocation=0);
	HuffmanPair _data;
	HuffmanNode* _right;
	HuffmanNode* _left;
};