#include "HuffmanNode.h"

HuffmanNode::HuffmanNode()
{
	//Let all values be constructed with default ctors
	this->_right = nullptr;
	this->_left = nullptr;
}

HuffmanNode::HuffmanNode(HuffmanPair pair)
{
	this->_data = pair;
	this->_right = nullptr;
	this->_left = nullptr;
}

HuffmanNode::HuffmanNode(HuffmanPair pair, HuffmanNode * right, HuffmanNode * left)
{
	this->_data = pair;
	this->_right = right;
	this->_left = left;
}

HuffmanNode::HuffmanNode(const HuffmanNode & other)
{
	*this = other;
}

HuffmanNode& HuffmanNode::operator=(const HuffmanNode & other)
{
	if (this == &other)
	{
		return *this; //No need to copy onto ourselves
	}
	delete this->_left;
	delete this->_right;

	//Recursively copy
	this->_left = other._left ? new HuffmanNode(*other._left) : nullptr;
	this->_right = other._right ? new HuffmanNode(*other._right) : nullptr;

	this->_data = other._data;
	
	return *this;
}

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

HuffmanPair & HuffmanNode::getDataRef()
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

bool HuffmanNode::operator()(HuffmanNode first, HuffmanNode second)
{
	return first.getDataRef().getFrequency() > second.getDataRef().getFrequency();
}
