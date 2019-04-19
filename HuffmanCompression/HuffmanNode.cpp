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

HuffmanNode::HuffmanNode(byteArray binaryRep)
{
	this->_left = nullptr;
	this->_right = nullptr;
	this->_deserializeInto(binaryRep);
}

HuffmanNode::HuffmanNode(const HuffmanNode & other)
{
	this->_right = nullptr;
	this->_left = nullptr;
	*this = other;
}

HuffmanNode::HuffmanNode(const HuffmanNode && other) noexcept
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

bool HuffmanNode::operator()(const HuffmanNode* first, const HuffmanNode* second) const
{
	return first->getDataRef().second > second->getDataRef().second;
}

byteArray HuffmanNode::serialize()
{
	byteArray tree;
	this->_recursiveSerialization(tree);
	return tree;
}

void HuffmanNode::_recursiveSerialization(byteArray& treeBytes) const
{
	treeBytes.push_back(this->_data.first);
	if (this->_left != nullptr)
	{
		this->_left->_recursiveSerialization(treeBytes);
	}
	else
	{
		treeBytes.push_back(SERIALIZATION_SENTRY);
	}

	if (this->_right)
	{
		this->_right->_recursiveSerialization(treeBytes);
	}
	else
	{
		treeBytes.push_back(SERIALIZATION_SENTRY);
	}
}

int HuffmanNode::_deserializeInto(const byteArray& rep, int location)
{
	this->_data = { rep[location++], 0 };

	//Left side isn't present
	if (rep[location] == SERIALIZATION_SENTRY)
	{
		location++;
	}
	else
	{
		this->_left = new HuffmanNode();
		location = this->_left->_deserializeInto(rep, location);
	}

	//Right side isn't present
	if (rep[location] == SERIALIZATION_SENTRY)
	{
		location++;
	}
	else
	{
		this->_right = new HuffmanNode();
		location = this->_right->_deserializeInto(rep, location);
	}
	return location;
}
