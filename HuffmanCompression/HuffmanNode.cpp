#include "HuffmanNode.h"

HuffmanNode::~HuffmanNode()
{
	//It's safe to delete a nullptr
	delete this->_right;
	delete this->_left;
}

HuffmanPair HuffmanNode::getData() const
{
	return this->_data;
}

HuffmanNode * HuffmanNode::getRightChild() const
{
	return this->_right;
}

HuffmanNode * HuffmanNode::getLeftChild() const
{
	return this->_left;
}

void HuffmanNode::setRightChild(HuffmanNode* node)
{
	this->_right = node;
}

void HuffmanNode::setLeftChild(HuffmanNode* node)
{
	this->_left = node;
}
