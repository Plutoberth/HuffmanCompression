#include "HuffmanCoding.h"

HuffmanCoding::HuffmanCoding(string file)
{
	this->filename = file;
}

HuffmanNodeSmartPtr HuffmanCoding::getHuffmanTree()
{
	HuffmanNode* first = nullptr;
	HuffmanNode* second = nullptr;
	HuffmanPriorityQueue pqueue = this->getFrequencyQueue();
	HuffmanNode res;

	while (!pqueue.empty())
	{
		first = pqueue.top();
		pqueue.pop();
		if (!pqueue.empty())
		{
			second = pqueue.top();
			pqueue.pop();
			//Create a new huffman node with the combined frequencies
			pqueue.push(new HuffmanNode(HuffmanPair(0, first->getDataRef().getFrequency() + second->getDataRef().getFrequency()),
				first, second));
		}
	}

	//Because we're returning a smart ptr to a class that manages its resources, the caller doesn't need to think about memory allocations.
	return HuffmanNodeSmartPtr(first);
}

CharMap HuffmanCoding::getHuffmanCharMap()
{
	return this->getHuffmanCharMap(*this->getHuffmanTree());
}

CharMap HuffmanCoding::getHuffmanCharMap(const HuffmanNode& tree)
{
	CharMap map;
	bitArray arr;
	//Scan the binary tree with our function
	HuffmanCoding::_scanBinaryTree(&tree, map, arr);
	return map;
}

bool HuffmanCoding::write(string filename)
{
	//[2 BYTES: Size of binary tree][Binary tree][4 BYTES: Length of data in bits][Huffman data] 

	uint16_t sizeOfTree = 0;
	BufferedBitFile file(filename);
	bool success = file.is_open();
	
	if (success)
	{
		HuffmanNodeSmartPtr tree = this->getHuffmanTree();
		byteArray bytes = tree->serialize();
		CharMap map = this->getHuffmanCharMap(*tree);
		
	}
	return success;
}

HuffmanPriorityQueue HuffmanCoding::getFrequencyQueue()
{
	//A sorted map to store our frequencies
	std::map<char, int> frequencyMap;
	//Input stream to read the file
	std::ifstream datafile(this->filename);
	HuffmanPriorityQueue pqueue;
	char currentChar;

	//Make sure that we opened the file
	if (datafile.is_open())
	{
		//Iterate over the file, char by char, without skipping whitespace
		while (datafile >> std::noskipws >> currentChar)
		{
			frequencyMap[currentChar]++;
		}
	}
	else
	{
		//TODO: Replace with my own exception
		throw new std::exception();
	}

	for (auto pair: frequencyMap)
	{
		pqueue.push(new HuffmanNode(HuffmanPair(pair.first, pair.second)));
	}

	return pqueue;
}

//Pre-order scanning for the binary tree
void HuffmanCoding::_scanBinaryTree(HuffmanNode const* tree, CharMap & map, bitArray currentLocation)
{
	const HuffmanPair& nodeData = tree->getDataRef();
	if (nodeData.getData() != 0)
	{
		map[nodeData.getData()] = currentLocation;
	}
	
	//Scan left child
	if (tree->getLeftChild())
	{
		//Add a 0 to signify a left turn and send the bit vector, then pop it
		currentLocation.push_back(0);
		HuffmanCoding::_scanBinaryTree(tree->getLeftChild(), map, currentLocation);
		currentLocation.pop_back();
	}

	if (tree->getRightChild())
	{
		//Add a 1 to signify a right turn and then send the bit vector.
		//No need to pop it as it dies in the next line anyway.
		currentLocation.push_back(1);
		HuffmanCoding::_scanBinaryTree(tree->getRightChild(), map, currentLocation);
	}
}
