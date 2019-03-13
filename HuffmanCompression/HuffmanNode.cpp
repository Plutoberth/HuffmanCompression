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

HuffmanNode::HuffmanNode(HuffmanPair pair, HuffmanNode * left, HuffmanNode * right)
{
	this->_data = pair;
	this->_right = right;
	this->_left = left;
}

HuffmanNode::HuffmanNode(const HuffmanNode & other)
{
	this->_right = nullptr;
	this->_left = nullptr;
	*this = other;
}

HuffmanNode::HuffmanNode(const HuffmanNode && other)
{
	//Move constructor - only transfers the ownership of resources
	//Used with rvalues, such as function return values.
	//Will trigger with: HuffmanNode node = getNode(), for example
	this->_data = other._data;
	this->_left = other._left;
	this->_right = other._right;
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

const HuffmanPair & HuffmanNode::getDataRef() const
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

bool HuffmanNode::operator()(const HuffmanNode* first, const HuffmanNode* second) const
{
	return first->getDataRef() > second->getDataRef();
}

bool HuffmanNode::serialize(std::string filename)
{
	std::ofstream file(filename, std::ios::binary);
	bool opened = file.is_open();
	if (file.is_open())
	{
		this->_recursiveWrite(file, this);
	}
	
	file.close();
	return opened;
}

void HuffmanNode::_recursiveWrite(std::ofstream& file, HuffmanNode const* node)
{
	file << node->getDataRef().getData();
	if (node->getLeftChild())
	{
		HuffmanNode::_recursiveWrite(file, node->getLeftChild());
	}
	else
	{
		file.write((char*)&SERIALIZATION_SENTRY, 1);
	}

	if (node->getRightChild())
	{
		HuffmanNode::_recursiveWrite(file, node->getRightChild());
	}
	else
	{
		file << SERIALIZATION_SENTRY;
	}
}
