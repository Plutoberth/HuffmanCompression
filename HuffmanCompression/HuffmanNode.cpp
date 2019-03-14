#include "HuffmanNode.h"

HuffmanNode::HuffmanNode()
{
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
	return first->getDataRef().second > second->getDataRef().second;
}

byteArray HuffmanNode::serialize()
{
	byteArray tree;
	this->_recursiveSerialization(tree, this);
	return tree;
}

void HuffmanNode::_recursiveSerialization(byteArray& tree, HuffmanNode const* node)
{
	tree.push_back(node->getDataRef().first);
	if (node->getLeftChild())
	{
		HuffmanNode::_recursiveSerialization(tree, node->getLeftChild());
	}
	else
	{
		tree.push_back(SERIALIZATION_SENTRY);
	}

	if (node->getRightChild())
	{
		HuffmanNode::_recursiveSerialization(tree, node->getRightChild());
	}
	else
	{
		tree.push_back(SERIALIZATION_SENTRY);
	}
}

void HuffmanNode::_recursiveDeserialization(const byteArray& rep)
{

}
